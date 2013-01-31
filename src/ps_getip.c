/*!
* \file ps_getip.c
* \brief Fichero fuente de resolver hosts
* \ingroup portscan
* \author Dídac Pérez <didac.perez@upc.edu>
* \author Aitor Hernández <aitorhdez@gmail.com>
* \date 09-01-2010
*/

#include "ps_getip.h"

in_addr_t ps_getip( char *host )
{
   struct hostent *hent;
   char ip[16];
   if ((hent = gethostbyname( host )) == NULL)
      return (-1);
   if (inet_ntop( AF_INET, (void *)hent->h_addr, ip, sizeof (ip) ) == 0)
      return (-1);
   return (inet_addr( ip ));
}
