void HIDDEN
xbps_transaction_revdeps(struct xbps_handle *xhp, xbps_array_t pkgs)
{
	xbps_array_t mdeps;

	mdeps = xbps_dictionary_get(xhp->transd, "missing_deps");

	for (unsigned int i = 0; i < xbps_array_count(pkgs); i++) {
		xbps_array_t pkgrdeps;
		xbps_object_t obj;
		const char *pkgver, *tract;
		char *pkgname;

		obj = xbps_array_get(pkgs, i);
		/*
		 * if pkg in transaction is not installed,
		 * pass to next one.
		 */
		xbps_dictionary_get_cstring_nocopy(obj, "pkgver", &pkgver);
		xbps_dictionary_get_cstring_nocopy(obj, "transaction", &tract);

		pkgname = xbps_pkg_name(pkgver);
		assert(pkgname);
		if (xbps_pkg_is_installed(xhp, pkgname) == 0) {
			free(pkgname);
			continue;
		}
		/*
		 * If pkg is installed but does not have revdeps,
		 * pass to next one.
		 */
		pkgrdeps = xbps_pkgdb_get_pkg_revdeps(xhp, pkgname);
		if (!xbps_array_count(pkgrdeps)) {
			free(pkgname);
			continue;
		}
		free(pkgname);
		/*
		 * Time to validate revdeps for current pkg.
		 */
		for (unsigned int x = 0; x < xbps_array_count(pkgrdeps); x++) {
			xbps_array_t rundeps;
			xbps_dictionary_t revpkgd;
			const char *curpkgver, *revpkgver, *curdep, *curtract;
			char *curpkgname, *curdepname;
			bool found = false;

			xbps_array_get_cstring_nocopy(pkgrdeps, x, &curpkgver);
			pkgname = xbps_pkg_name(curpkgver);
			assert(pkgname);
			if ((revpkgd = xbps_find_pkg_in_array(pkgs, pkgname, NULL))) {
				xbps_dictionary_get_cstring_nocopy(revpkgd, "transaction", &curtract);
				if (strcmp(curtract, "remove") == 0)
					revpkgd = NULL;
			}
			if (revpkgd == NULL)
				revpkgd = xbps_pkgdb_get_pkg(xhp, curpkgver);

			xbps_dictionary_get_cstring_nocopy(revpkgd, "pkgver", &revpkgver);
			/*
			 * If target pkg is being removed, all its revdeps
			 * will be broken unless those revdeps are also in
			 * the transaction.
			 */
			if (strcmp(tract, "remove") == 0) {
				if (xbps_dictionary_get(obj, "replaced")) {
					free(pkgname);
					continue;
				}
				if (xbps_find_pkg_in_array(pkgs, pkgname, "remove")) {
					free(pkgname);
					continue;
				}
				free(pkgname);
				broken_pkg(mdeps, curpkgver, pkgver, tract);
				continue;
			}
			/*
			 * First try to match any supported virtual package.
			 */
			if (check_virtual_pkgs(mdeps, obj, revpkgd)) {
				free(pkgname);
				continue;
			}
			/*
			 * Try to match real dependencies.
			 */
			rundeps = xbps_dictionary_get(revpkgd, "run_depends");
			/*
			 * Find out what dependency is it.
			 */
			curpkgname = xbps_pkg_name(pkgver);
			assert(curpkgname);

			for (unsigned int j = 0; j < xbps_array_count(rundeps); j++) {
				xbps_array_get_cstring_nocopy(rundeps, j, &curdep);
				if (((curdepname = xbps_pkg_name(curdep)) == NULL) &&
				    ((curdepname = xbps_pkgpattern_name(curdep)) == NULL))
					abort();

				if (strcmp(curdepname, curpkgname) == 0) {
					free(curdepname);
					found = true;
					break;
				}
				free(curdepname);
			}
			free(curpkgname);

			if (!found) {
				free(pkgname);
				continue;
			}
			if (xbps_match_pkgdep_in_array(rundeps, pkgver)) {
				free(pkgname);
				continue;
			}
			/*
			 * Installed package conflicts with package
			 * in transaction being updated, check
			 * if a new version of this conflicting package
			 * is in the transaction.
			 */
			if (xbps_find_pkg_in_array(pkgs, pkgname, "update")) {
				free(pkgname);
				continue;
			}
			free(pkgname);
			broken_pkg(mdeps, curpkgver, pkgver, tract);
		}

	}
}