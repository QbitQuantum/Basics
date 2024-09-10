/*
 * Rewrite destination address in case we will connect to loopback address.
 *
 * Returns 0 on success, EAFNOSUPPORT if the jail doesn't allow IPv6.
 */
int
prison_remote_ip6(struct ucred *cred, struct in6_addr *ia6)
{
	struct prison *pr;

	KASSERT(cred != NULL, ("%s: cred is NULL", __func__));
	KASSERT(ia6 != NULL, ("%s: ia6 is NULL", __func__));

	pr = cred->cr_prison;
	if (!(pr->pr_flags & PR_IP6))
		return (0);
	mtx_lock(&pr->pr_mtx);
	if (!(pr->pr_flags & PR_IP6)) {
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}
	if (pr->pr_ip6 == NULL) {
		mtx_unlock(&pr->pr_mtx);
		return (EAFNOSUPPORT);
	}

	if (IN6_IS_ADDR_LOOPBACK(ia6)) {
		bcopy(&pr->pr_ip6[0], ia6, sizeof(struct in6_addr));
		mtx_unlock(&pr->pr_mtx);
		return (0);
	}

	/*
	 * Return success because nothing had to be changed.
	 */
	mtx_unlock(&pr->pr_mtx);
	return (0);
}