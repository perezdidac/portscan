/*!
* \file portscan.h
* \brief Fichero cabecera principal del proyecto
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#ifndef  PORTSCAN_H
#define  PORTSCAN_H

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "ps_error.h"
#include "ps_scan.h"
#include "ps_getip.h"

//! Versión de portscan
#define  PS_PORTSCAN_VERSION     "0.3"
//! Información sobre los autores
#define  PS_AUTHORS              "D. Pérez and A. Hernández"
//! Usage de la aplicación
#define  PS_USAGE                "SYNOPSIS\n" \
                                 "       portscan [OPTION]...\n\n" \
                                 "DESCRIPTION\n" \
                                 "       Scans  a  desired  range  of  TCP/IP  ports to a remote machine and shows the\n" \
                                 "       results. The  program  can  use  multiple  number  of  sub-processes  working\n" \
                                 "       together to optimize the time of application.\n\n" \
                                 "       -l     log filename\n" \
                                 "       -d     remote hostname\n" \
                                 "       -s     initial port for start scanning\n" \
                                 "       -e     end port\n" \
                                 "       -c     max number of childs\n" \
                                 "       -h     display the usage of the program\n" \
                                 "       -v     output version information and exit\n\n" \
                                 "       By  default, the program uses 8 childs at maximum.  If -d option is not used,\n" \
                                 "       portscan reads hostnames from the standard input.\n" \
                                 "   Exit status:\n" \
                                 "       0      if OK,\n" \
                                 "       1      if nothing was done,\n" \
                                 "       2      if an error occour,\n" \
                                 "       3      if the application has been cancelled during the scan process\n\n"

//! Versión del programa
#define  PS_VERSION              "portscan version "PS_PORTSCAN_VERSION".\n" \
                                 "Developed by "PS_AUTHORS".\n\n"

//! Default time out for waiting for an answer
#define  CONFIG_TIMEOUT_MSEC     1000
//! Número máximo de hijos creados
#define  CONFIG_MAX_CHILDS       8
//! Puerto inicial por defecto
#define  CONFIG_MINPORT          1
//! Puerto final por defecto
#define  CONFIG_MAXPORT          65535

//! Información sobre el host de destino a escanear
struct scan_info_t
{
   in_addr_t      ip;            ///< Dirección IP del destino
   unsigned short port;          ///< Puerto de destino
};

//! Estructura con las opciones recibidas por linea de comandos
struct options_t
{
   int            from_stdin;    ///< Indica que se leerán destinos por entrada estándar
   int            log;           ///< Indica si se guardará un log de todo el proceso
   char           *filename;     ///< Fichero donde se guardan los resultados
   char           ip[255];       ///< Dirección IP del destino
   unsigned short maxchilds;     ///< Número máximo de hijos
   unsigned short minport;       ///< Puerto inicial
   unsigned short maxport;       ///< Puerto final
   unsigned short timeout;       ///< Time out in msec
};

/*!
* \brief Función main
*
* Función principal del proyecto.
*
* \param    argc Número de argumentos recibidos por la linea de comandos. Ver el Usage del programa.
* \param    argv Argumentos pasados por linea de comandos.
* \return   Devuelve menos que 0 si ha habido error.
* \see      ps_parse_options( int argc, char *argv[], struct options_t *options )
* \see      ps_scan( in_addr_t ip, unsigned short port, unsigned short timeout_msec )
* \see      ps_error( ps_error_t err )
*/
int   main( int argc, char *argv[] );

/*!
* \brief Parseador de opciones
*
* Rellena la estructura options con los campos recibidos por linea de comandos.
*
* \param    argc Número de argumentos recibidos por la linea de comandos. Ver el Usage del programa.
* \param    argv Argumentos pasados por linea de comandos.
* \param    *options Puntero a la estructura del tipo options_t con las opciones de linea de comandos.
* \return   Devuelve -1 para leer hosts de entrada estándar o 0 si no.
* \see      ps_show_help()
* \see      ps_show_version()
*/
int   ps_parse_options( int argc, char *argv[], struct options_t *options );

/*!
* \brief Cancelar proceso
*
* Cuando la signal es recibida, se cancela el proceso del programa.
*
* \param    sig Identificador del signal.
*/
void  ps_cancel( int sig );

/*!
* \brief Ayuda
*
* Muestra las instrucciones de uso del programa.
*
* \see      ps_show_version()
*/
void  ps_show_help();

/*!
* \brief Versión
*
* Muestra la versión e información sobre los desarrolladores.
*/
void  ps_show_version();

#endif
