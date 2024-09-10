/* read keys from ssh key files */
static int
readsshkeys(netpgp_t *netpgp, char *homedir, const char *needseckey)
{
	pgp_keyring_t	*pubring;
	pgp_keyring_t	*secring;
	struct stat	 st;
	unsigned	 hashtype;
	char		*hash;
	char		 f[MAXPATHLEN];
	char		*filename;

	if ((filename = netpgp_getvar(netpgp, "sshkeyfile")) == NULL) {
		/* set reasonable default for RSA key */
		(void) snprintf(f, sizeof(f), "%s/id_rsa.pub", homedir);
		filename = f;
	} else if (strcmp(&filename[strlen(filename) - 4], ".pub") != 0) {
		/* got ssh keys, check for pub file name */
		(void) snprintf(f, sizeof(f), "%s.pub", filename);
		filename = f;
	}
	/* check the pub file exists */
	if (stat(filename, &st) != 0) {
		(void) fprintf(stderr, "readsshkeys: bad pubkey filename '%s'\n", filename);
		return 0;
	}
	if ((pubring = calloc(1, sizeof(*pubring))) == NULL) {
		(void) fprintf(stderr, "readsshkeys: bad alloc\n");
		return 0;
	}
	/* openssh2 keys use md5 by default */
	hashtype = PGP_HASH_MD5;
	if ((hash = netpgp_getvar(netpgp, "hash")) != NULL) {
		/* openssh 2 hasn't really caught up to anything else yet */
		if (netpgp_strcasecmp(hash, "md5") == 0) {
			hashtype = PGP_HASH_MD5;
		} else if (netpgp_strcasecmp(hash, "sha1") == 0) {
			hashtype = PGP_HASH_SHA1;
		} else if (netpgp_strcasecmp(hash, "sha256") == 0) {
			hashtype = PGP_HASH_SHA256;
		}
	}
	if (!pgp_ssh2_readkeys(netpgp->io, pubring, NULL, filename, NULL, hashtype)) {
		free(pubring);
		(void) fprintf(stderr, "readsshkeys: can't read %s\n",
				filename);
		return 0;
	}
	if (netpgp->pubring == NULL) {
		netpgp->pubring = pubring;
	} else {
		pgp_append_keyring(netpgp->pubring, pubring);
	}
	if (needseckey) {
		netpgp_setvar(netpgp, "sshpubfile", filename);
		/* try to take the ".pub" off the end */
		if (filename == f) {
			f[strlen(f) - 4] = 0x0;
		} else {
			(void) snprintf(f, sizeof(f), "%.*s",
					(int)strlen(filename) - 4, filename);
			filename = f;
		}
		if ((secring = calloc(1, sizeof(*secring))) == NULL) {
			free(pubring);
			(void) fprintf(stderr, "readsshkeys: bad alloc\n");
			return 0;
		}
		if (!pgp_ssh2_readkeys(netpgp->io, pubring, secring, NULL, filename, hashtype)) {
			free(pubring);
			free(secring);
			(void) fprintf(stderr, "readsshkeys: can't read sec %s\n", filename);
			return 0;
		}
		netpgp->secring = secring;
		netpgp_setvar(netpgp, "sshsecfile", filename);
	}
	return 1;
}