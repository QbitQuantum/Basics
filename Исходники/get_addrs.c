#endif

#include <err.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#include "talk.h"
#include "talk_ctl.h"

void
get_addrs(const char *my_machine_name __unused, const char *his_machine_name)
{
	struct hostent *hp;
	struct servent *sp;

	msg.pid = htonl(getpid());

	hp = gethostbyname(his_machine_name);
	if (hp == NULL)
		errx(1, "%s: %s", his_machine_name, hstrerror(h_errno));
	bcopy(hp->h_addr, (char *) &his_machine_addr, hp->h_length);
	if (get_iface(&his_machine_addr, &my_machine_addr) == -1)
		err(1, "failed to find my interface address");
	/* find the server's port */
	sp = getservbyname("ntalk", "udp");
	if (sp == 0)
		errx(1, "ntalk/udp: service is not registered");
	daemon_port = sp->s_port;
}
