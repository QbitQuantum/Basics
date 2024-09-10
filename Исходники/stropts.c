/*
 * Set up mandatory non-version specific NFS mount options.
 *
 * Returns 1 if successful; otherwise zero.
 */
static int nfs_validate_options(struct nfsmount_info *mi)
{
	struct addrinfo hint = {
		.ai_protocol	= (int)IPPROTO_UDP,
	};
	sa_family_t family;
	int error;

	if (!nfs_parse_devname(mi->spec, &mi->hostname, NULL))
		return 0;

	if (!nfs_nfs_proto_family(mi->options, &family))
		return 0;

	hint.ai_family = (int)family;
	error = getaddrinfo(mi->hostname, NULL, &hint, &mi->address);
	if (error != 0) {
		nfs_error(_("%s: Failed to resolve server %s: %s"),
			progname, mi->hostname, gai_strerror(error));
		mi->address = NULL;
		return 0;
	}

	if (!nfs_set_version(mi))
		return 0;

	if (!nfs_append_sloppy_option(mi->options))
		return 0;

	if (!nfs_append_addr_option(mi->address->ai_addr,
					mi->address->ai_addrlen, mi->options))
		return 0;

	return 1;
}

/*
 * Get NFS/mnt server addresses from mount options
 *
 * Returns 1 and fills in @nfs_saddr, @nfs_salen, @mnt_saddr, and @mnt_salen
 * if all goes well; otherwise zero.
 */
static int nfs_extract_server_addresses(struct mount_options *options,
					struct sockaddr *nfs_saddr,
					socklen_t *nfs_salen,
					struct sockaddr *mnt_saddr,
					socklen_t *mnt_salen)
{
	char *option;

	option = po_get(options, "addr");
	if (option == NULL)
		return 0;
	if (!nfs_string_to_sockaddr(option, nfs_saddr, nfs_salen))
		return 0;

	option = po_get(options, "mountaddr");
	if (option == NULL) {
		memcpy(mnt_saddr, nfs_saddr, *nfs_salen);
		*mnt_salen = *nfs_salen;
	} else if (!nfs_string_to_sockaddr(option, mnt_saddr, mnt_salen))
		return 0;

	return 1;
}