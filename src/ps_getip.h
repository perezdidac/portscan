/*!
* \file ps_getip.h
* \brief Fichero cabecera de resolver hosts
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#ifndef  PS_GETIP_H
#define  PS_GETIP_H

#include <netdb.h>
#include <stdlib.h>

/*!
* \brief Resolver hostname
*
* Función encargada de resolver un hostname a dirección IP
*
* \param    host Nombre del hostname.
* \return   Devuelve un in_addr_t con la IP resuelta o -1 si ha habido error.
*/
in_addr_t ps_getip( char *host );

#endif
