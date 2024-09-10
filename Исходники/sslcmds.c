int start_stunnel(int stunnel_port, int x11vnc_port, int hport, int x11vnc_hport) {
#ifdef SSLCMDS
	char extra[] = ":/usr/sbin:/usr/local/sbin:/dist/sbin";
	char *path, *p, *exe;
	char *stunnel_path = NULL;
	struct stat verify_buf;
	struct stat crl_buf;
	int status, tmp_pem = 0;

	if (stunnel_pid) {
		stop_stunnel();
	}
	stunnel_pid = 0;

	path = getenv("PATH");
	if (! path) {
		path = strdup(extra+1);
	} else {
		char *pt = path;
		path = (char *) malloc(strlen(path)+strlen(extra)+1);
		if (! path) {
			return 0;
		}
		strcpy(path, pt);
		strcat(path, extra);
	}

	exe = (char *) malloc(strlen(path) + 1 + strlen("stunnel4") + 1);

	p = strtok(path, ":");

	exe[0] = '\0';

	while (p) {
		struct stat sbuf;

		sprintf(exe, "%s/%s", p, "stunnel4");
		if (! stunnel_path && stat(exe, &sbuf) == 0) {
			if (! S_ISDIR(sbuf.st_mode)) {
				stunnel_path = exe;
				break;
			}
		}

		sprintf(exe, "%s/%s", p, "stunnel");
		if (! stunnel_path && stat(exe, &sbuf) == 0) {
			if (! S_ISDIR(sbuf.st_mode)) {
				stunnel_path = exe;
				break;
			}
		}

		p = strtok(NULL, ":");
	}
	if (path) {
		free(path);
	}

	if (getenv("STUNNEL_PROG")) {
		free(exe);
		exe = strdup(getenv("STUNNEL_PROG"));
		stunnel_path = exe;
	}

	if (! stunnel_path) {
		free(exe);
		return 0;
	}
	if (stunnel_path[0] == '\0') {
		free(exe);
		return 0;
	}

	/* stunnel */
	if (no_external_cmds || !cmd_ok("stunnel")) {
		rfbLogEnable(1);
		rfbLog("start_stunnel: cannot run external commands in -nocmds mode:\n");
		rfbLog("   \"%s\"\n", stunnel_path);
		rfbLog("   exiting.\n");
		clean_up_exit(1);
	}

	if (! quiet) {
		rfbLog("\n");
		rfbLog("starting ssl tunnel: %s  %d -> %d\n", stunnel_path,
		    stunnel_port, x11vnc_port);
	}

	if (stunnel_pem && strstr(stunnel_pem, "SAVE") == stunnel_pem) {
		stunnel_pem = get_saved_pem(stunnel_pem, 1);
		if (! stunnel_pem) {
			rfbLog("start_stunnel: could not create or open"
			    " saved PEM.\n");	
			clean_up_exit(1);
		}
	} else if (!stunnel_pem) {
		stunnel_pem = create_tmp_pem(NULL, 0);
		if (! stunnel_pem) {
			rfbLog("start_stunnel: could not create temporary,"
			    " self-signed PEM.\n");	
			clean_up_exit(1);
		}
		tmp_pem = 1;
		if (getenv("X11VNC_SHOW_TMP_PEM")) {
			FILE *in = fopen(stunnel_pem, "r");
			if (in != NULL) {
				char line[128];
				fprintf(stderr, "\n");
				while (fgets(line, 128, in) != NULL) {
					fprintf(stderr, "%s", line);
				}
				fprintf(stderr, "\n");
				fclose(in);
			}
		}
	}

	if (ssl_verify) {
		char *file = get_ssl_verify_file(ssl_verify);
		if (file) {
			ssl_verify = file;
		}
		if (stat(ssl_verify, &verify_buf) != 0) {
			rfbLog("stunnel: %s does not exist.\n", ssl_verify);
			clean_up_exit(1);
		}
	}
	if (ssl_crl) {
		if (stat(ssl_crl, &crl_buf) != 0) {
			rfbLog("stunnel: %s does not exist.\n", ssl_crl);
			clean_up_exit(1);
		}
	}

	stunnel_pid = fork();

	if (stunnel_pid < 0) {
		stunnel_pid = 0;
		free(exe);
		return 0;
	}

	if (stunnel_pid == 0) {
		FILE *in;
		char fd[20];
		int i;
		char *st_if = getenv("STUNNEL_LISTEN");

		if (st_if == NULL) {
			st_if = "";
		} else {
			st_if = (char *) malloc(strlen(st_if) + 2);
			sprintf(st_if, "%s:", getenv("STUNNEL_LISTEN"));
		}


		for (i=3; i<256; i++) {
			close(i);
		}

		if (use_stunnel == 3) {
			char sp[30], xp[30], *a = NULL;
			char *st = stunnel_path;
			char *pm = stunnel_pem;
			char *sv = ssl_verify;

			sprintf(sp, "%d", stunnel_port);
			sprintf(xp, "%d", x11vnc_port);

			if (ssl_verify) {
				if(S_ISDIR(verify_buf.st_mode)) {
					a = "-a";
				} else {
					a = "-A";
				}
			}

			if (ssl_crl) {
				rfbLog("stunnel: stunnel3 does not support CRL. %s\n", ssl_crl);
				clean_up_exit(1);
			}
			
			if (stunnel_pem && ssl_verify) {
				/* XXX double check -v 2 */
				execlp(st, st, "-f", "-d", sp, "-r", xp, "-P",
				    "none", "-p", pm, a, sv, "-v", "2",
				    (char *) NULL);
			} else if (stunnel_pem && !ssl_verify) {
				execlp(st, st, "-f", "-d", sp, "-r", xp, "-P",
				    "none", "-p", pm,
				    (char *) NULL);
			} else if (!stunnel_pem && ssl_verify) {
				execlp(st, st, "-f", "-d", sp, "-r", xp, "-P",
				    "none", a, sv, "-v", "2",
				    (char *) NULL);
			} else {
				execlp(st, st, "-f", "-d", sp, "-r", xp, "-P",
				    "none", (char *) NULL);
			}
			exit(1);
		}

		in = tmpfile();
		if (! in) {
			exit(1);
		}

		fprintf(in, "foreground = yes\n");
		fprintf(in, "pid =\n");
		if (stunnel_pem) {
			fprintf(in, "cert = %s\n", stunnel_pem);
		}
		if (ssl_crl) {
			if(S_ISDIR(crl_buf.st_mode)) {
				fprintf(in, "CRLpath = %s\n", ssl_crl);
			} else {
				fprintf(in, "CRLfile = %s\n", ssl_crl);
			}
		}
		if (ssl_verify) {
			if(S_ISDIR(verify_buf.st_mode)) {
				fprintf(in, "CApath = %s\n", ssl_verify);
			} else {
				fprintf(in, "CAfile = %s\n", ssl_verify);
			}
			fprintf(in, "verify = 2\n");
		}
		fprintf(in, ";debug = 7\n\n");
		fprintf(in, "[x11vnc_stunnel]\n");
		fprintf(in, "accept = %s%d\n", st_if, stunnel_port);
		fprintf(in, "connect = %d\n", x11vnc_port);

		if (hport > 0 && x11vnc_hport > 0) {
			fprintf(in, "\n[x11vnc_http]\n");
			fprintf(in, "accept = %s%d\n", st_if, hport);
			fprintf(in, "connect = %d\n", x11vnc_hport);
		}

		fflush(in);
		rewind(in);

		if (getenv("STUNNEL_DEBUG")) {
			char line[1000];
			fprintf(stderr, "\nstunnel config contents:\n\n");
			while (fgets(line, sizeof(line), in) != NULL) {
				fprintf(stderr, "%s", line);
			}
			fprintf(stderr, "\n");
			rewind(in);
		}
		
		sprintf(fd, "%d", fileno(in));
		execlp(stunnel_path, stunnel_path, "-fd", fd, (char *) NULL);
		exit(1);
	}

	free(exe);
	usleep(750 * 1000);

	waitpid(stunnel_pid, &status, WNOHANG); 

	if (ssl_verify && strstr(ssl_verify, "/sslverify-tmp-load-")) {
		/* temporary file */
		usleep(1000 * 1000);
		unlink(ssl_verify);
	}
	if (tmp_pem) {
		/* temporary cert */
		usleep(1500 * 1000);
		unlink(stunnel_pem);
	}

	if (kill(stunnel_pid, 0) != 0) {
		waitpid(stunnel_pid, &status, WNOHANG); 
		stunnel_pid = 0;
		return 0;
	}

	if (! quiet) {
		rfbLog("stunnel pid is: %d\n", (int) stunnel_pid);
	}

	return 1;
#else
	return 0;
#endif
}