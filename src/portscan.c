/*!
* \file portscan.c
* \brief Fichero fuente principal del proyecto
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#include "portscan.h"

int main( int argc, char *argv[] )
{
   struct options_t  options;
   in_addr_t         ip;
   int               fd;
   int               buflen;
   unsigned short    port;
   unsigned short    minport;
   unsigned short    maxport;
   unsigned short    timeout;
   char              str[MAX_MESSAGE_LEN];
   int               pid;
   int               childs;
   ps_scan_t         ret;
   int               i;
   int               j;

   // Parsear las opciones recibidas por la linea de comando
   ps_parse_options( argc, argv, &options );
   if (options.log == 0)
   {
      if ((fd = open( options.filename, O_WRONLY | O_CREAT | O_TRUNC )) < 0)
      {
         ps_error( WARNING_LOG_FILENAME );
         options.log == -1;
      }
   }
   do
   {
      // Leer destino de la entrada estándar
      if (options.from_stdin == -1)
         if (scanf( "%s", options.ip ) == -1)
            break;

      // Convertir la cadena IP al tipo in_addr_t
      if ((ip = inet_addr( options.ip )) == (in_addr_t)(-1))
         if ((ip = ps_getip( options.ip )) == (-1))
            ps_error( ERROR_HOST_INCORRECT );
      // Convertir la cadena a unsigned short
      if (!(minport = options.minport))
         ps_error( ERROR_PORT_MIN );
      // Convertir la cadena a unsigned short
      if (!(maxport = options.maxport))
         ps_error( ERROR_PORT_MAX );
      // Convertir la cadena a unsigned short
      if (!(timeout = options.timeout))
         ps_error( ERROR_TIMEOUT );
      // Comprobar si el rango introducido es coherente
      if (maxport < minport)
         ps_error( ERROR_PORT_RANGE );

      // Calcular el número máximo de hijos a crear
      if (!(childs = options.maxchilds))
         ps_error( ERROR_MAX_CHILDS );
      if (childs > maxport - minport + 1)
         childs = maxport - minport + 1;

      // Preparar las pipes necesarias en función del número de hijos
      int                  pfd[childs][2];
      struct scan_info_t   scan_info;

      // Bucle encargado de crear los hijos necesarios para comenzar a escanear
      for (i = 0; i < childs; i++)
      {
         // Creamos la pipe entre padre e hijo y creamos el hijo
         if (pipe( pfd[i] ) < 0)
            ps_error( ERROR_PIPE );
         pid = fork();
         if (pid < 0)
            ps_error( ERROR_FORK );
         else if (!pid)
         {
            // Cerramos la pipe de escritura del hijo
            close( pfd[i][1] );
            // Cerramos las pipes de escritura innecesarias hereadas del padre
            for (j = 0; j < i; j++)
               close( pfd[j][1] );
            // Mientras nos queden destinos, seguimos escaneando
            while (read( pfd[i][0], &scan_info, sizeof (struct scan_info_t) ) == sizeof (struct scan_info_t))
            {
               // Escribir el log si es preciso
               if (options.log == 0)
               {
                  sprintf( str, "Child %d started scanning...\n", i );
                  write( fd, str, strlen( str ) );
               }
               // Realizamos la conexión al destino y guardamos los resultados en la variable ret
               ret = ps_scan( scan_info.ip, scan_info.port, timeout );
               // Escribir el log si es preciso
               if (options.log == 0)
               {
                  sprintf( str, "Child %d finished.\n", i );
                  write( fd, str, strlen( str ) );
               }
               // Aquí mostramos por pantalla el resultado
               if (ret == SCAN_ERROR)
                  sprintf( str, "%s %d ERROR\n", options.ip, scan_info.port );
               if (ret == SCAN_SUCCESS)
                  sprintf( str, "%s %d SUCCESS\n", options.ip, scan_info.port );
               if (ret == SCAN_TIMEOUT)
                  sprintf( str, "%s %d TIMEOUT\n", options.ip, scan_info.port );
               write( 1, str, strlen( str ) );
            }
            // Cerramos la pipe de lectura del hijo
            close( pfd[i][0] );
            return (PS_EXIT_STATUS_SUCCESS);
         }
         // Cerramos la pipe de lectura del padre
         close( pfd[i][0] );
      }
      // Bloquear las signals
      if (signal( SIGINT, ps_cancel ) < 0)
         ps_error( WARNING_SIGNAL );
      // Una vez hemos creado los hijos, el padre reparte las tareas entre ellos
      for (i = 0; i < maxport - minport + 1; i++)
      {
         // Le pasamos la info al hijo
         scan_info.ip   = ip;
         scan_info.port = minport + i;
         if (write( pfd[i % childs][1], &scan_info, sizeof (struct scan_info_t) ) != sizeof (struct scan_info_t))
            ps_error( ERROR_PIPE_WRITE );
      }
      // Cerramos todas las pipes de escritura a los hijos
      for (i = 0; i < childs; i++)
         close( pfd[i][1] );
      // Esperamos la muerte de los hijos
      for (i = 0; i < childs; i++)
         wait( NULL );
      // Desprogramamos la signal
      if (signal( SIGINT, SIG_DFL ) < 0)
         ps_error( WARNING_SIGNAL );
   } while (options.from_stdin == -1);
   if (options.log == 0)
      close( fd );
   return (PS_EXIT_STATUS_SUCCESS);
}

int ps_parse_options( int argc, char *argv[], struct options_t *options )
{
   int         ret;
   extern char *optarg;
   // Opciones por defecto
   options->log         = -1;
   options->maxchilds   = CONFIG_MAX_CHILDS;
   options->minport     = CONFIG_MINPORT;
   options->maxport     = CONFIG_MAXPORT;
   options->timeout     = CONFIG_TIMEOUT_MSEC;
   options->from_stdin  = -1;
   while ((ret = getopt( argc, argv, "l:c:t:d:s:e:hv" )) != -1)
   {
      switch (ret)
      {
         case 'l':
            options->filename = optarg;
            options->log      = 0;
            break;
         case 'c':
            options->maxchilds = atoi( optarg );
            break;
         case 't':
            options->timeout = atoi( optarg );
            break;
         case 'd':
            strcpy( options->ip, optarg );
            options->from_stdin = 0;
            break;
         case 's':
            options->minport = atoi( optarg );
            break;
         case 'e':
            options->maxport = atoi( optarg );
            break;
         case 'h':
            ps_show_help();
            exit (PS_EXIT_STATUS_NOTHING);
         case 'v':
            ps_show_version();
            exit (PS_EXIT_STATUS_NOTHING);
         default:
            break;
      }
   }
   return (0);
}

void ps_cancel( int sig )
{
   char str[MAX_MESSAGE_LEN];
   sprintf( str, "Killing childs...\n" );
   write( 2, str, strlen( str ) );
   kill( 0, SIGINT );
   while (waitpid( -1, NULL, WNOHANG) > 0) ;
   exit (PS_EXIT_STATUS_CANCEL);
}

void ps_show_help()
{
   printf( PS_VERSION );
   printf( PS_USAGE );
   exit (PS_EXIT_STATUS_NOTHING);
}

void ps_show_version()
{
   printf( PS_VERSION );
   exit (PS_EXIT_STATUS_NOTHING);
}
