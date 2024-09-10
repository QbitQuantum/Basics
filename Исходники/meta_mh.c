/*
 * open RPC connection to rpc.metamhd
 */
static mhd_handle_t *
open_metamhd(
	char		*hostname,
	md_error_t	*ep
)
{
	CLIENT		*clientp;
	mhd_handle_t	*hp;

	/* default to local host */
	if ((hostname == NULL) || (*hostname == '\0'))
		hostname = mynode();

	/* open RPC connection */
	assert(hostname != NULL);
	if ((clientp = meta_client_create(hostname, METAMHD, METAMHD_VERSION,
	    "tcp")) == NULL) {
		clnt_pcreateerror(hostname);
		(void) mdrpccreateerror(ep, hostname, "metamhd clnt_create");
		return (NULL);
	} else {
		auth_destroy(clientp->cl_auth);
		clientp->cl_auth = authsys_create_default();
		assert(clientp->cl_auth != NULL);
	}

	/* return connection */
	hp = Zalloc(sizeof (*hp));
	hp->hostname = Strdup(hostname);
	hp->clientp = clientp;
	return (hp);
}