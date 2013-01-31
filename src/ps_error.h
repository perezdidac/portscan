/*!
* \file ps_error.h
* \brief Fichero cabecera de control de errores
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#ifndef  PS_ERROR_H
#define  PS_ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! Tamaño máximo para errores y avisos
#define  MAX_MESSAGE_LEN         255

//! Listado de posibles códigos de salida del programa
typedef enum
{
   PS_EXIT_STATUS_SUCCESS,       ///< Programa terminado sin error
   PS_EXIT_STATUS_NOTHING,       ///< No se ha realizado ninguna acción
   PS_EXIT_STATUS_ERROR,         ///< Ha habido un error
   PS_EXIT_STATUS_CANCEL,        ///< Cancelado durante el escaneo
} ps_exit_status_t;

//! Listado de posibles códigos de error del programa
typedef enum
{
   WARNING_LOG_FILENAME,         ///< Imposible escribir sobre el fichero de log
   WARNING_SIGNAL,               ///< Imposible reprogramar la signal
   ERROR_MAX_CHILDS,             ///< Número máximo de hijos incorrecto
   ERROR_HOST_INCORRECT,         ///< La dirección escrita tiene un formato incorrecto
   ERROR_PORT_MIN,               ///< Valor incorrecto
   ERROR_PORT_MAX,               ///< Valor incorrecto
   ERROR_PORT_RANGE,             ///< Rango inválido
   ERROR_TIMEOUT,                ///< Timeout introducido incorrecto
   ERROR_PIPE,                   ///< Error en la función pipe() al intentar crear una pipe
   ERROR_FORK,                   ///< fork() ha devuelto error
   ERROR_SOCKET_SOCKET,          ///< Error al crear el socket mediante socket()
   ERROR_SOCKET_NONBLOCK,        ///< Imposible configurar el socket como no bloqueante
   ERROR_PIPE_READ,              ///< Error al leer de la pipe
   ERROR_PIPE_WRITE,             ///< Error al escribir en la pipe
} ps_error_t;

/*!
* \brief Control de errores
*
* Función encargada de mostrar por pantalla el error.
*
* \param    err Código de error.
*/
void ps_error( ps_error_t err );

#endif
