/*!
* \file ps_scan.h
* \brief Fichero cabecera de escaneo de puertos
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#ifndef  PS_SCAN_H
#define  PS_SCAN_H

#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "ps_error.h"

//! Enumeración con los posibles valores que devuelve la función ps_scan
typedef enum
{
   SCAN_ERROR,                   ///< Imposible establecer conexión
   SCAN_SUCCESS,                 ///< Conexión realizada satisfactoriamente
   SCAN_TIMEOUT                  ///< Tiempo de espera superado
} ps_scan_t;

/*!
* \brief Escanear puerto
*
* Función encargada de conectarse al host por el puerto indicado para comprobar su estado.
*
* \param    ip Dirección IP del destino.
* \param    port Puerto de destino.
* \param    timeout_msec Tiempo de espera en msec.
* \return   Devuelve un ps_scan_t con el resultado del escaneo.
* \see      ps_set_nonblock( int sock )
* \see      ps_error( ps_error_t err )
*/
ps_scan_t ps_scan( in_addr_t ip, unsigned short port, unsigned short timeout_msec );

/*!
* \brief Configurar descriptor no bloqueante
*
* Función encargada de modificar el descriptor sock.
*
* \param    sock Descriptor del socket.
* \return   Devuelve menor que 0 si ha habido error.
*/
int ps_set_nonblock( int sock );

#endif
