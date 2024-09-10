/*
 * This is the function that actually installs one volume (usually that's
 * all there is). Upon entry, the extlist is entirely correct:
 *
 *	1. It contains only those files which are to be installed
 *	   from all volumes.
 *	2. The mode bits in the ainfo structure for each file are set
 *	   correctly in accordance with administrative defaults.
 *	3. mstat.setuid/setgid reflect what the status *was* before
 *	   pkgdbmerg() processed compliance.
 */
void
instvol(struct cfextra **extlist, char *srcinst, int part,
	int nparts, VFP_T **a_cfVfp, VFP_T **a_cfTmpVfp,
	char **r_updated, char **r_skipped,
	char *a_zoneName)
{
	FILE		*listfp;
	char		*updated = (char *)NULL;
	char		*skipped = (char *)NULL;
	char		*anyPathLocal = (char *)NULL;
	char		*relocpath = (char *)NULL;
	char		*dstp;
	char		*listfile;
	char		*srcp;
	char		*pspool_loc;
	char		scrpt_dst[PATH_MAX];
	int		count;
	int		entryidx;	/* array of current package objects */
	int		n;
	int		nc = 0;
	int		pass;		/* pass count through the for loop. */
	int		tcount;
	struct cfent	*ept;
	struct cfextra	*ext;
	struct mergstat	*mstat;
	struct reg_files *rfp = NULL;

	/*
	 * r_updated and r_skipped are optional parameters that can be passed in
	 * by the caller if the caller wants to know if any objects are either
	 * updated or skipped. Do not initialize either r_updated or r_skipped;
	 * the call to instvol could be cumulative and any previous update or
	 * skipped indication must not be disturbed - these flags are only set,
	 * they must never be reset. These flags are "char *" pointers so that
	 * the object that was skipped or updated can be displayed in debugging
	 * output.
	 */

	if (part == 1) {
		pkgvolume(&pkgdev, srcinst, part, nparts);
	}

	tcount = 0;
	nc = cl_getn();

	/*
	 * For each class in this volume, install those files.
	 *
	 * NOTE : This loop index may be decremented by code below forcing a
	 * second trip through for the same class. This happens only when a
	 * class is split between an archive and the tree. Examples would be
	 * old WOS packages and the occasional class containing dynamic
	 * libraries which require special treatment.
	 */

	if (is_depend_pkginfo_DB() == B_FALSE) {
	    int		classidx;	/* the current class */

	    for (classidx = 0; classidx < nc; classidx++) {
		int pass_relative = 0;
		int rel_init = 0;

		eocflag = count = pass = 0;
		listfp = (FILE *)0;
		listfile = NULL;

		/* Now what do we pass to the class action script */

		if (cl_pthrel(classidx) == REL_2_CAS) {
			pass_relative = 1;
		}

		for (;;) {
			if (!tcount++) {
				/* first file to install */
				if (a_zoneName == (char *)NULL) {
					echo(MSG_INS_N_N, part, nparts);
				} else {
					echo(MSG_INS_N_N_LZ, part, nparts,
						a_zoneName);
				}
			}

			/*
			 * If there's an install class action script and no
			 * list file has been created yet, create that file
			 * and provide the pointer in listfp.
			 */
			if (cl_iscript(classidx) && !listfp) {
				/* create list file */
				putparam("TMPDIR", tmpdir);
				listfile = tempnam(tmpdir, "list");
				if ((listfp = fopen(listfile, "w")) == NULL) {
					progerr(ERR_WTMPFILE, listfile);
					quit(99);
				}
			}

			/*
			 * The following function goes through the package
			 * object list returning the array index of the next
			 * regular file. If it encounters a directory,
			 * symlink, named pipe or device, it just creates it.
			 */

			entryidx = domerg(extlist, (pass++ ? 0 : part), nparts,
				classidx, &srcp, &dstp, &updated, &skipped,
				&anyPathLocal);

			/* Evaluate the return code */
			if (entryidx == DMRG_DONE) {
				/*
				 * Set ept to the first entry in extlist
				 * which is guaranteed to exist so
				 * later checks against ept->ftype are
				 * not compared to NULL.
				 */
				ext = extlist[0];
				ept = &(ext->cf_ent);
				break; /* no more entries to process */
			}

			ext = extlist[entryidx];
			ept = &(ext->cf_ent);
			mstat = &(ext->mstat);

			/*
			 * If not installing from a partially spooled package
			 * (the "save/pspool" area), and the file contents can
			 * be changed (type is 'e' or 'v'), and the class is not
			 * "none": copy the file from the package (in pristine
			 * state with no actions performed) into the appropriate
			 * location in the packages destination "save/pspool"
			 * area.
			 */

			if ((!is_partial_inst()) &&
				((ept->ftype == 'e') || (ept->ftype == 'v')) &&
				(strcmp(ept->pkg_class, "none") != 0)) {

				if (absolutepath(ext->map_path) == B_TRUE &&
					parametricpath(ext->cf_ent.ainfo.local,
						&relocpath) == B_FALSE) {
					pspool_loc = ROOT;
				} else {
					pspool_loc = RELOC;
				}

				n = snprintf(scrpt_dst, PATH_MAX, "%s/%s/%s",
					saveSpoolInstallDir, pspool_loc,
					relocpath ? relocpath : ext->map_path);

				if (n >= PATH_MAX) {
					progerr(ERR_CREATE_PATH_2,
						saveSpoolInstallDir,
						ext->map_path);
					quit(99);
				}

				/* copy, preserve source file mode */

				if (cppath(MODE_SRC, srcp, scrpt_dst, 0644)) {
					warnflag++;
				}
			}

			/*
			 * If this isn't writeable anyway, it's not going
			 * into the list file. Only count it if it's going
			 * into the list file.
			 */
			if (is_fs_writeable(ext->cf_ent.path,
				&(ext->fsys_value)))
				count++;

			pkgvolume(&pkgdev, srcinst, part, nparts);

			/*
			 * If source verification is OK for this class, make
			 * sure the source we're passing to the class action
			 * script is useable.
			 */
			if (cl_svfy(classidx) != NOVERIFY) {
				if (cl_iscript(classidx) ||
					((ept->ftype == 'e') ||
					(ept->ftype == 'n'))) {
					if (ck_efile(srcp, ept)) {
						progerr(ERR_CORRUPT,
							srcp);
						logerr(getErrbufAddr());
						warnflag++;
						continue;
					}
				}
			}

			/*
			 * If there's a class action script for this class,
			 * just collect names in a temporary file
			 * that will be used as the stdin when the
			 * class action script is invoked.
			 */

			if ((cl_iscript(classidx)) &&
					((is_fs_writeable(ept->path,
						&(ext->fsys_value))))) {
				if (pass_relative) {
					if (!rel_init) {
						(void) fputs(instdir, listfp);
						(void) putc('\n', listfp);
						rel_init++;
					}
					(void) fputs(ext->map_path, listfp);
					(void) putc('\n', listfp);
				} else {
					(void) fputs(srcp ?
						srcp : "/dev/null", listfp);
					(void) putc(' ', listfp);
					(void) fputs(dstp, listfp);
					(void) putc('\n', listfp);
				}
				/*
				 * Note which entries in extlist are regular
				 * files to be installed via the class action
				 * script.
				 */
				if (regfiles_head == NULL) {
					assert(rfp == NULL);
					regfiles_head =
					    malloc(sizeof (struct reg_files));
					if (regfiles_head == NULL) {
						progerr(ERR_MEMORY, errno);
						quit(99);
					}
					regfiles_head->next = NULL;
					regfiles_head->val = entryidx;
					rfp = regfiles_head;
				} else {
					assert(rfp != NULL);
					rfp->next =
					    malloc(sizeof (struct reg_files));
					if (rfp->next == NULL) {
						progerr(ERR_MEMORY, errno);
						quit(99);
					}
					rfp = rfp->next;
					rfp->next = NULL;
					rfp->val = entryidx;
				}

				/*
				 * A warning message about unwritable targets
				 * in a class may be appropriate here.
				 */
				continue;
			}

			/*
			 * If not installing from a partially spooled package
			 * (the "save/pspool" area), and the file contents can
			 * be changed (type is 'e' or 'v') and the class
			 * identifier is not "none": copy the file from the
			 * package (in pristine state with no actions performed)
			 * into the appropriate location in the packages
			 * destination "save/pspool" area.
			 */

			if ((!is_partial_inst()) &&
			    ((ept->ftype == 'e') || (ept->ftype == 'v') &&
			    (strcmp(ept->pkg_class, "none") != 0))) {

				if (absolutepath(ext->map_path) == B_TRUE &&
					parametricpath(ext->cf_ent.ainfo.local,
						&relocpath) == B_FALSE) {
					pspool_loc = ROOT;
				} else {
					pspool_loc = RELOC;
				}

				n = snprintf(scrpt_dst, PATH_MAX, "%s/%s/%s",
					saveSpoolInstallDir, pspool_loc,
					relocpath ? relocpath : ext->map_path);

				if (n >= PATH_MAX) {
					progerr(ERR_CREATE_PATH_2,
						saveSpoolInstallDir,
						ext->map_path);
					quit(99);
				}

				/* copy, preserve source file mode */

				if (cppath(MODE_SRC, srcp, scrpt_dst, 0644)) {
					warnflag++;
				}
			}

			/*
			 * There are several tests here to determine
			 * how we're going to deal with objects
			 * intended for remote read-only filesystems.
			 * We don't use is_served() because this may be
			 * a server. We're actually interested in if
			 * it's *really* remote and *really* not
			 * writeable.
			 */

			n = is_remote_fs(ept->path, &(ext->fsys_value));
			if ((n != 0) &&
				!is_fs_writeable(ept->path,
				&(ext->fsys_value))) {

				/*
				 * Don't change the file, we can't write
				 * to it anyway.
				 */

				mstat->attrchg = 0;
				mstat->contchg = 0;

				/*
				 * If it's currently mounted, we can
				 * at least test it for existence.
				 */

				if (is_mounted(ept->path, &(ext->fsys_value))) {
					if (!isfile(NULL, dstp)) {
						echo(MSG_IS_PRESENT, dstp);
					} else {
						echo(WRN_INSTVOL_NONE, dstp);
					}
				} else {
					char *server_host;

					server_host = get_server_host(
						ext->fsys_value);

					/* If not, we're just stuck. */
					echo(WRN_INSTVOL_NOVERIFY,
						dstp, server_host);
				}

				continue;
			}

			/* echo output destination name */

			echo("%s", dstp);

			/*
			 * if no source then no need to copy/verify
			 */

			if (srcp == (char *)NULL) {
				continue;
			}

			/*
			 * If doing a partial installation (creating a
			 * non-global zone), extra steps need to be taken:
			 *
			 * 1) if the file is not type 'e' and not type 'v' and
			 * the class is "none": then the file must already
			 * exist (as a result of the initial non-global zone
			 * installation which caused all non-e/v files to be
			 * copied from the global zone to the non-global
			 * zone). If this is the case, verify that the file
			 * exists and has the correct attributes.
			 *
			 * 2) if the file is not type 'e' and not type 'v'
			 * and the class is NOT "none", *OR* if the file is
			 * type 'e' or type 'v': then check to see if the
			 * file is located in an area inherited from the
			 * global zone. If so, then there is no ability to
			 * change the file since inherited file systems are
			 * "read only" - just verify that the file exists and
			 * verify attributes only if not 'e' or 'v'.
			 */

			if (is_partial_inst() != 0) {

				/*
				 * determine if the destination package is in an
				 * area inherited from the global zone
				 */

				n = pkgMatchInherited(srcp, dstp,
					get_inst_root(), ept->ainfo.mode,
					ept->cinfo.modtime, ept->ftype,
					ept->cinfo.cksum);

				echoDebug(DBG_INSTVOL_PARTIAL_INST,
					srcp ? srcp : "", dstp ? dstp: "",
					((get_inst_root()) &&
					(strcmp(get_inst_root(), "/") != 0)) ?
					get_inst_root() : "",
					ept->ainfo.mode, ept->cinfo.modtime,
					ept->ftype, ept->cinfo.cksum, n);

				/*
				 * if not type 'e|v' and class 'none', then the
				 * file must already exist.
				 */

				if ((ept->ftype != 'e') &&
					(ept->ftype != 'v') &&
					(strcmp(cl_nam(ept->pkg_class_idx),
								"none") == 0)) {

					/*
					 * if the file is in a space inherited
					 * from the global zone, and if the
					 * contents or attributes are incorrect,
					 * then generate a warning that the
					 * global zone file contents and/or file
					 * attributes have been modified and
					 * that the modifications are extended
					 * to the non-global zone (inherited
					 * from the global zone).
					 */

					if (n == 0) {
						/* is file changed? */
						n = finalck(ept, 1, 1, B_TRUE);

						/* no - ok - continue */
						if (n == 0) {
							continue;
						}

						/* output warning message */
						logerr(NOTE_INSTVOL_FINALCKFAIL,
							pkginst, ext->map_path,
							a_zoneName, ept->path);
						continue;
					} else if (!finalck(ept, 1, 1,
								B_FALSE)) {
						/*
						 * non-e/v file of class "none"
						 * not inherited from the global
						 * zone: verify file already
						 * exists:everything checks here
						 */
						mstat->attrchg = 0;
						mstat->contchg = 0;
					}
					continue;
				}

				/*
				 * non-e/v file with class action script, or
				 * e/v file: if the file is in an area inherited
				 * from the global zone, then no need (or the
				 * ability) to update just accept the file as is
				 */

				if (n == B_TRUE) {
					/*
					 * the object is in an area inherited
					 * from the global zone and the objects
					 * attributes are verified
					 */

					mstat->attrchg = 0;
					mstat->contchg = 0;

					/* NOTE: package object skipped */

					if (skipped == (char *)NULL) {
						skipped = dstp;
					echoDebug(DBG_INSTVOL_OBJ_SKIPPED,
								skipped);
					}
					continue;
				}
			}

			/*
			 * Copy from source media to target path and fix file
			 * mode and permission now in case installation halted.
			 */

			if (z_path_is_inherited(dstp, ept->ftype,
						get_inst_root()) == B_FALSE) {
				n = cppath(MODE_SET|DIR_DISPLAY, srcp, dstp,
						ept->ainfo.mode);
				if (n != 0) {
					warnflag++;
				} else if (!finalck(ept, 1, 1, B_FALSE)) {
					/*
					 * everything checks here
					 */
					mstat->attrchg = 0;
					mstat->contchg = 0;
				}
			}

			/* NOTE: a package object was updated */

			if (updated == (char *)NULL) {
				echoDebug(DBG_INSTVOL_OBJ_UPDATED, dstp);
				updated = dstp;
			}
		}

		/*
		 * We have now completed processing of all pathnames
		 * associated with this volume and class.
		 */
		if (cl_iscript(classidx)) {
			/*
			 * Execute appropriate class action script
			 * with list of source/destination pathnames
			 * as the input to the script.
			 */

			if (chdir(pkgbin)) {
				progerr(ERR_CHGDIR, pkgbin);
				quit(99);
			}

			if (listfp) {
				(void) fclose(listfp);
			}

			/*
			 * if the object associated with the class action script
			 * is in an area inherited from the global zone, then
			 * there is no need to run the class action script -
			 * assume that anything the script would do has already
			 * been done in the area shared from the global zone.
			 */

			/* nothing updated, nothing skipped */

			echoDebug(DBG_INSTVOL_CAS_INFO, is_partial_inst(),
				updated ? updated : "",
				skipped ? skipped : "",
				anyPathLocal ? anyPathLocal : "");

			if ((is_partial_inst() != 0) &&
					(updated == (char *)NULL) &&
					(anyPathLocal == (char *)NULL)) {

				/*
				 * installing in non-global zone, and no object
				 * has been updated (installed/verified in non-
				 * inherited area), and no path delivered by the
				 * package is in an area not inherited from the
				 * global zone (all paths delivered are in
				 * areas inherited from the global zone): do not
				 * run the class action script because the only
				 * affected areas are inherited (read only).
				 */

				echoDebug(DBG_INSTVOL_NOT_RUNNING_CAS,
					a_zoneName ? a_zoneName : "?",
					eocflag ? "ENDOFCLASS" :
							cl_iscript(classidx),
					cl_nam(classidx),
					cl_iscript(classidx));

				if ((r_skipped != (char **)NULL) &&
					(*r_skipped == (char *)NULL) &&
					(skipped == (char *)NULL)) {
					skipped = "postinstall";
					echoDebug(DBG_INSTVOL_OBJ_SKIPPED,
								skipped);
				}
			} else {
				/* run the class action script */

				echoDebug(DBG_INSTVOL_RUNNING_CAS,
					a_zoneName ? a_zoneName : "?",
					eocflag ? "ENDOFCLASS" :
							cl_iscript(classidx),
					cl_nam(classidx),
					cl_iscript(classidx));

				/* Use ULIMIT if supplied. */
				set_ulimit(cl_iscript(classidx), ERR_CASFAIL);

				if (eocflag) {
					/*
					 * end of class detected.
					 * Since there are no more volumes which
					 * contain pathnames associated with
					 * this class, execute class action
					 * script with the ENDOFCLASS argument;
					 * we do this even if none of the path
					 * names associated with this class and
					 * volume needed installation to
					 * guarantee the class action script is
					 * executed at least once during package
					 * installation.
					 */
					if (pkgverbose) {
						n = pkgexecl((listfp ?
							listfile : CAS_STDIN),
							CAS_STDOUT,
							CAS_USER, CAS_GRP,
							SHELL, "-x",
							cl_iscript(classidx),
							"ENDOFCLASS", NULL);
					} else {
						n = pkgexecl(
							(listfp ?
							listfile : CAS_STDIN),
							CAS_STDOUT, CAS_USER,
							CAS_GRP, SHELL,
							cl_iscript(classidx),
							"ENDOFCLASS", NULL);
					}
					ckreturn(n, ERR_CASFAIL);
				} else if (count) {
					/* execute class action script */
					if (pkgverbose) {
						n = pkgexecl(listfile,
							CAS_STDOUT, CAS_USER,
							CAS_GRP, SHELL, "-x",
							cl_iscript(classidx),
							NULL);
					} else {
						n = pkgexecl(listfile,
							CAS_STDOUT, CAS_USER,
							CAS_GRP, SHELL,
							cl_iscript(classidx),
							NULL);
					}
					ckreturn(n, ERR_CASFAIL);
				}

				/*
				 * Ensure the mod times on disk match those
				 * in the pkgmap. In this case, call cverify
				 * with checksumming disabled, since the only
				 * action that needs to be done is to verify
				 * that the attributes are correct.
				 */

				if ((rfp = regfiles_head) != NULL) {
					while (rfp != NULL) {
					    ept = &(extlist[rfp->val]->cf_ent);
					    cverify(1, &ept->ftype, ept->path,
						&ept->cinfo, 0);
					    rfp = rfp->next;
					}
					regfiles_free();
				}

				clr_ulimit();

				if ((r_updated != (char **)NULL) &&
					(*r_updated == (char *)NULL) &&
					(updated == (char *)NULL)) {
					updated = "postinstall";
					echoDebug(DBG_INSTVOL_OBJ_UPDATED,
								updated);
				}
			}
			if (listfile) {
				(void) remove(listfile);
			}
		}

		if (eocflag && (!is_partial_inst() || (is_partial_inst() &&
			strcmp(cl_nam(classidx), "none") != 0))) {
			if (cl_dvfy(classidx) == QKVERIFY && !repl_permitted) {
				/*
				 * The quick verify just fixes everything.
				 * If it returns 0, all is well. If it
				 * returns 1, then the class installation
				 * was incomplete and we retry on the
				 * stuff that failed in the conventional
				 * way (without a CAS). this is primarily
				 * to accomodate old archives such as are
				 * found in pre-2.5 WOS; but, it is also
				 * used when a critical dynamic library
				 * is not archived with its class.
				 */
				if (!fix_attributes(extlist, classidx)) {
					/*
					 * Reset the CAS pointer. If the
					 * function returns 0 then there
					 * was no script there in the first
					 * place and we'll just have to
					 * call this a miss.
					 */
					if (cl_deliscript(classidx))
						/*
						 * Decrement classidx for
						 * next pass.
						 */
						classidx--;
				}
			} else {
				/*
				 * Finalize merge. This checks to make sure
				 * file attributes are correct and any links
				 * specified are created.
				 */
				(void) endofclass(extlist, classidx,
					(cl_iscript(classidx) ? 0 : 1),
					a_cfVfp, a_cfTmpVfp);
			}
		}
	    }
	}

	/*
	 * Instead of creating links back to the GZ files the logic is
	 * to let zdo recreate the files from the GZ then invoke pkgadd to
	 * install the editable files and skip over any 'f'type files.
	 * The commented out block is to create the links which should be
	 * removed once the current code is tested to be correct.
	 */

	/*
	 * Go through extlist creating links for 'f'type files
	 * if we're in a global zone. Note that this code lies
	 * here instead of in the main loop to support CAF packages.
	 * In a CAF package the files are installed by the i.none script
	 * and don't exist until all files are done being processed, thus
	 * the additional loop through extlist.
	 */

	/*
	 * output appropriate completion message
	 */

	if (is_depend_pkginfo_DB() == B_TRUE) {
		/* updating database only (hollow package) */
		if (a_zoneName == (char *)NULL) {
			echo(MSG_DBUPD_N_N, part, nparts);
		} else {
			echo(MSG_DBUPD_N_N_LZ, part, nparts, a_zoneName);
		}
	} else if (tcount == 0) {
		/* updating package (non-hollow package) */
		if (a_zoneName == (char *)NULL) {
			echo(MSG_INST_N_N, part, nparts);
		} else {
			echo(MSG_INST_N_N_LZ, part, nparts, a_zoneName);
		}
	}

	/*
	 * if any package objects were updated (not inherited from the
	 * global zone or otherwise already in existence), set the updated
	 * flag as appropriate
	 */

	if (updated != (char *)NULL) {
		echoDebug(DBG_INSTVOL_OBJ_UPDATED, updated);
		if (r_updated != (char **)NULL) {
			*r_updated = updated;
		}
	}

	/*
	 * if any package objects were skipped (verified inherited from the
	 * global zone), set the skipped flag as appropriate
	 */

	if (skipped != (char *)NULL) {
		echoDebug(DBG_INSTVOL_OBJ_SKIPPED, skipped);
		if (r_skipped != (char **)NULL) {
			*r_skipped = skipped;
		}
	}
}