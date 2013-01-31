/*!
* \file ps_scan.c
* \brief Fichero fuente de escaneo de puertos
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#include "ps_scan.h"

ps_scan_t ps_scan( in_addr_t ip, unsigned short port, unsigned short timeout_msec )
{
   int                  sock;
   struct sockaddr_in   target;
   struct timeval       timeout;
   fd_set               fdset;
   socklen_t            lon;
   int                  valopt;
   ps_scan_t            ret;

   // Crear el descriptor del socket
   if ((sock = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP )) < 0)
      ps_error( ERROR_SOCKET_SOCKET );

   // Llamar a la función ps_set_nonblock para configurar el socket como no bloqueante
   // para evitar bloqueos en la función connect()
   if (ps_set_nonblock( sock ) < 0)
      ps_error( ERROR_SOCKET_NONBLOCK );

   // Configurar el tipo de protocolo
   target.sin_family        = AF_INET;
   // Indicar la dirección IP de destino
   target.sin_addr.s_addr   = ip;
   // Intercambiar los bits de lugar mediante htons()
   target.sin_port          = htons( port );

   // Conectarse al destino
   connect( sock, (struct sockaddr *) &target, sizeof (struct sockaddr) );
   // Al no ser bloqueante, aún estaremos en progreso
   if (errno == EINPROGRESS)
   {
      FD_ZERO( &fdset );
      FD_SET( sock, &fdset );
      // Configuramos el tiempo máximo de espera
      timeout.tv_sec = timeout_msec / 1000;
      timeout.tv_usec = (timeout_msec - timeout.tv_sec * 1000) * 1000;
      // Observamos el estado del socket y esperamos según el valor de timeout
      if (select( sock + 1, NULL, &fdset, NULL, &timeout ))
      {
         lon = sizeof (int);
         // Comprobamos si hemos podido conectarnos o no
         getsockopt( sock, SOL_SOCKET, SO_ERROR, (void*)(&valopt), &lon ); 
         if (valopt)
            ret = SCAN_ERROR;
         else
            ret = SCAN_SUCCESS;
      }
      else
         ret = SCAN_TIMEOUT;
   }
   else
      ret = SCAN_ERROR;
   close( sock );

   return (ret);
}

int ps_set_nonblock( int sock )
{
   int flags;
   flags = fcntl( sock, F_GETFL, NULL );
   return (fcntl( sock, F_SETFL, flags | O_NONBLOCK ));
}
