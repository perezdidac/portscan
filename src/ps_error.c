/*!
* \file ps_error.c
* \brief Fichero fuente de control de errores
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#include "ps_error.h"

void ps_error( ps_error_t err )
{
   char str[MAX_MESSAGE_LEN];
   switch (err)
   {
      case WARNING_LOG_FILENAME:
         sprintf( str, "Failed while opening the log file.\n" );
         write( 2, str, strlen( str ) );
         break;
      case WARNING_SIGNAL:
         sprintf( str, "Failed while executing signal() function.\n" );
         write( 2, str, strlen( str ) );
         break;
      case ERROR_MAX_CHILDS:
         sprintf( str, "Incorrect number of max childs.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_HOST_INCORRECT:
         sprintf( str, "Incorrect host address.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PORT_MIN:
         sprintf( str, "Incorrect start port.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PORT_MAX:
         sprintf( str, "Incorrect final port.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PORT_RANGE:
         sprintf( str, "Initial port must be equal or higher than final port.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_TIMEOUT:
         sprintf( str, "Incorrect timeout.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PIPE:
         sprintf( str, "Error while executing pipe() function.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_FORK:
         sprintf( str, "Error while executing fork() function.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_SOCKET_SOCKET:
         sprintf( str, "Error while executing socket() function.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_SOCKET_NONBLOCK:
         sprintf( str, "Cannot set the unblocking socket mode.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PIPE_READ:
         sprintf( str, "Error while executing read() to read from the pipe.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      case ERROR_PIPE_WRITE:
         sprintf( str, "Error while executing write() to write to the pipe.\n" );
         write( 2, str, strlen( str ) );
         exit (PS_EXIT_STATUS_ERROR);
      default:
         break;
   }
}
