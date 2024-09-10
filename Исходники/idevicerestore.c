int main(int argc, char* argv[]) {
	int opt = 0;
	int optindex = 0;
	char* ipsw = NULL;
	char* uuid = NULL;
	int tss_enabled = 0;
	int shsh_only = 0;
	char* shsh_dir = NULL;
	use_apple_server=1;

	// create an instance of our context
	struct idevicerestore_client_t* client = (struct idevicerestore_client_t*) malloc(sizeof(struct idevicerestore_client_t));
	if (client == NULL) {
		error("ERROR: Out of memory\n");
		return -1;
	}
	memset(client, '\0', sizeof(struct idevicerestore_client_t));

	while ((opt = getopt_long(argc, argv, "dhcesxtpi:u:", longopts, &optindex)) > 0) {
		switch (opt) {
		case 'h':
			usage(argc, argv);
			return 0;

		case 'd':
			client->flags |= FLAG_DEBUG;
			idevicerestore_debug = 1;
			break;

		case 'e':
			client->flags |= FLAG_ERASE;
			break;

		case 'c':
			client->flags |= FLAG_CUSTOM;
			break;

		case 's':
			use_apple_server=0;
			break;

		case 'x':
			client->flags |= FLAG_EXCLUDE;
			break;

		case 'i':
			if (optarg) {
				char* tail = NULL;
				client->ecid = strtoull(optarg, &tail, 16);
				if (tail && (tail[0] != '\0')) {
					client->ecid = 0;
				}
				if (client->ecid == 0) {
					error("ERROR: Could not parse ECID from '%s'\n", optarg);
					return -1;
				}
			}
			break;

		case 'u':
			uuid = optarg;
			break;

		case 't':
			shsh_only = 1;
			break;

		case 'p':
			client->flags |= FLAG_PWN;
			break;

		default:
			usage(argc, argv);
			return -1;
		}
	}

	if (((argc-optind) == 1) || (client->flags & FLAG_PWN)) {
		argc -= optind;
		argv += optind;

		ipsw = argv[0];
	} else {
		usage(argc, argv);
		return -1;
	}

	if (client->flags & FLAG_DEBUG) {
		idevice_set_debug_level(1);
		irecv_set_debug_level(1);
	}

	client->uuid = uuid;
	client->ipsw = ipsw;

	// update version data (from cache, or apple if too old)
	load_version_data(client);

	// check which mode the device is currently in so we know where to start
	if (check_mode(client) < 0 || client->mode->index == MODE_UNKNOWN) {
		error("ERROR: Unable to discover device mode. Please make sure a device is attached.\n");
		return -1;
	}
	info("Found device in %s mode\n", client->mode->string);

	if (client->mode->index == MODE_WTF) {
		int cpid = 0;

		if (dfu_client_new(client) != 0) {
			error("ERROR: Could not open device in WTF mode\n");
			return -1;
		}
		if ((dfu_get_cpid(client, &cpid) < 0) || (cpid == 0)) { 
			error("ERROR: Could not get CPID for WTF mode device\n");
			dfu_client_free(client);
			return -1;
		}

		char* s_wtfurl = NULL;
		plist_t wtfurl = plist_access_path(client->version_data, 7, "MobileDeviceSoftwareVersionsByVersion", "5", "RecoverySoftwareVersions", "WTF", "304218112", "5", "FirmwareURL");
		if (wtfurl && (plist_get_node_type(wtfurl) == PLIST_STRING)) {
			plist_get_string_val(wtfurl, &s_wtfurl);
		}
		if (!s_wtfurl) {
			info("Using hardcoded x12220000_5_Recovery.ipsw URL\n");
			s_wtfurl = strdup("http://appldnld.apple.com.edgesuite.net/content.info.apple.com/iPhone/061-6618.20090617.Xse7Y/x12220000_5_Recovery.ipsw");
		}

		// make a local file name
		char* fnpart = strrchr(s_wtfurl, '/');
		if (!fnpart) {
			fnpart = "x12220000_5_Recovery.ipsw";
		} else {
			fnpart++;
		}
		struct stat fst;
		char wtfipsw[256];
		sprintf(wtfipsw, "cache/%s", fnpart);
		if (stat(wtfipsw, &fst) != 0) {
			__mkdir("cache", 0755);
			download_to_file(s_wtfurl, wtfipsw);
		}

		char wtfname[256];
		sprintf(wtfname, "Firmware/dfu/WTF.s5l%04xxall.RELEASE.dfu", cpid);
		char* wtftmp = NULL;
		uint32_t wtfsize = 0;
		ipsw_extract_to_memory(wtfipsw, wtfname, &wtftmp, &wtfsize);
		if (!wtftmp) {
			error("ERROR: Could not extract WTF\n");
		} else {
			if (dfu_send_buffer(client, wtftmp, wtfsize) != 0) {
				error("ERROR: Could not send WTF...\n");
			}
		}
		dfu_client_free(client);

		sleep(1);

		free(wtftmp);
		client->mode = &idevicerestore_modes[MODE_DFU];
	}

	// discover the device type
	if (check_device(client) < 0 || client->device->index == DEVICE_UNKNOWN) {
		error("ERROR: Unable to discover device type\n");
		return -1;
	}
	info("Identified device as %s\n", client->device->product);

	if ((client->flags & FLAG_PWN) && (client->mode->index != MODE_DFU)) {
		error("ERROR: you need to put your device into DFU mode to pwn it.\n");
		return -1;
	}

	if (client->flags & FLAG_PWN) {
		recovery_client_free(client);

		info("connecting to DFU\n");
		if (dfu_client_new(client) < 0) {
			return -1;
		}
		info("exploiting with limera1n...\n");
		// TODO: check for non-limera1n device and fail
		if (limera1n_exploit(client->device, client->dfu->client) != 0) {
			error("ERROR: limera1n exploit failed\n");
			dfu_client_free(client);
			return -1;
		}
		dfu_client_free(client);
		info("Device should be in pwned DFU state now.\n");

		return 0;
	}

	if (client->mode->index == MODE_RESTORE) {
		if (restore_reboot(client) < 0) {
			error("ERROR: Unable to exit restore mode\n");
			return -1;
		}
	}

	// extract buildmanifest
	plist_t buildmanifest = NULL;
	if (client->flags & FLAG_CUSTOM) {
		info("Extracting Restore.plist from IPSW\n");
		if (ipsw_extract_restore_plist(ipsw, &buildmanifest) < 0) {
			error("ERROR: Unable to extract Restore.plist from %s\n", ipsw);
			return -1;
		}
	} else {
		info("Extracting BuildManifest from IPSW\n");
		if (ipsw_extract_build_manifest(ipsw, &buildmanifest, &tss_enabled) < 0) {
			error("ERROR: Unable to extract BuildManifest from %s\n", ipsw);
			return -1;
		}
	}

	/* check if device type is supported by the given build manifest */
	if (build_manifest_check_compatibility(buildmanifest, client->device->product) < 0) {
		error("ERROR: could not make sure this firmware is suitable for the current device. refusing to continue.\n");
		return -1;
	}

	/* print iOS information from the manifest */
	build_manifest_get_version_information(buildmanifest, &client->version, &client->build);

	info("Product Version: %s\n", client->version);
	info("Product Build: %s\n", client->build);

	if (client->flags & FLAG_CUSTOM) {
		/* prevent signing custom firmware */
		tss_enabled = 0;
		info("Custom firmware requested. Disabled TSS request.\n");
	}

	// choose whether this is an upgrade or a restore (default to upgrade)
	client->tss = NULL;
	plist_t build_identity = NULL;
	if (client->flags & FLAG_CUSTOM) {
		build_identity = plist_new_dict();
		{
			plist_t node;
			plist_t comp;
			plist_t info;
			plist_t manifest;

			info = plist_new_dict();
			plist_dict_insert_item(info, "RestoreBehavior", plist_new_string((client->flags & FLAG_ERASE) ? "Erase" : "Update"));
			plist_dict_insert_item(info, "Variant", plist_new_string((client->flags & FLAG_ERASE) ? "Customer Erase Install (IPSW)" : "Customer Upgrade Install (IPSW)"));
			plist_dict_insert_item(build_identity, "Info", info);

			manifest = plist_new_dict();

			char tmpstr[256];
			char p_all_flash[128];
			char lcmodel[8];
			strcpy(lcmodel, client->device->model);
			int x = 0;
			while (lcmodel[x]) {
				lcmodel[x] = tolower(lcmodel[x]);
				x++;
			}

			sprintf(p_all_flash, "Firmware/all_flash/all_flash.%s.%s", lcmodel, "production");
			strcpy(tmpstr, p_all_flash);
			strcat(tmpstr, "/manifest");

			// get all_flash file manifest
			char *files[16];
			char *fmanifest = NULL;
			uint32_t msize = 0;
			if (ipsw_extract_to_memory(ipsw, tmpstr, &fmanifest, &msize) < 0) {
				error("ERROR: could not extract %s from IPSW\n", tmpstr);
				return -1;
			}

			char *tok = strtok(fmanifest, "\r\n");
			int fc = 0;
			while (tok) {
				files[fc++] = strdup(tok);
				if (fc >= 16) {
					break;
				}
				tok = strtok(NULL, "\r\n");
			}
			free(fmanifest);

			for (x = 0; x < fc; x++) {
				info = plist_new_dict();
				strcpy(tmpstr, p_all_flash);
				strcat(tmpstr, "/");
				strcat(tmpstr, files[x]);
				plist_dict_insert_item(info, "Path", plist_new_string(tmpstr));
				comp = plist_new_dict();
				plist_dict_insert_item(comp, "Info", info);
				const char* compname = get_component_name(files[x]);
				if (compname) {
					plist_dict_insert_item(manifest, compname, comp);
					if (!strncmp(files[x], "DeviceTree", 10)) {
						plist_dict_insert_item(manifest, "RestoreDeviceTree", plist_copy(comp));
					}
				} else {
					error("WARNING: unhandled component %s\n", files[x]);
					plist_free(comp);
				}
				free(files[x]);
				files[x] = NULL;
			}

			// add iBSS
			sprintf(tmpstr, "Firmware/dfu/iBSS.%s.%s.dfu", lcmodel, "RELEASE");
			info = plist_new_dict();
			plist_dict_insert_item(info, "Path", plist_new_string(tmpstr));
			comp = plist_new_dict();
			plist_dict_insert_item(comp, "Info", info);
			plist_dict_insert_item(manifest, "iBSS", comp);

			// add iBEC
			sprintf(tmpstr, "Firmware/dfu/iBEC.%s.%s.dfu", lcmodel, "RELEASE");
			info = plist_new_dict();
			plist_dict_insert_item(info, "Path", plist_new_string(tmpstr));
			comp = plist_new_dict();
			plist_dict_insert_item(comp, "Info", info);
			plist_dict_insert_item(manifest, "iBEC", comp);

			// add kernel cache
			node = plist_dict_get_item(buildmanifest, "KernelCachesByTarget");
			if (node && (plist_get_node_type(node) == PLIST_DICT)) {
				char tt[4];
				strncpy(tt, lcmodel, 3);
				tt[3] = 0;
				plist_t kdict = plist_dict_get_item(node, tt);
				if (kdict && (plist_get_node_type(kdict) == PLIST_DICT)) {
					plist_t kc = plist_dict_get_item(kdict, "Release");
					if (kc && (plist_get_node_type(kc) == PLIST_STRING)) {
						info = plist_new_dict();
						plist_dict_insert_item(info, "Path", plist_copy(kc));
						comp = plist_new_dict();
						plist_dict_insert_item(comp, "Info", info);
						plist_dict_insert_item(manifest, "KernelCache", comp);
						plist_dict_insert_item(manifest, "RestoreKernelCache", plist_copy(comp));

					}
				}
			}

			// add ramdisk
			node = plist_dict_get_item(buildmanifest, "RestoreRamDisks");
			if (node && (plist_get_node_type(node) == PLIST_DICT)) {
				plist_t rd = plist_dict_get_item(node, (client->flags & FLAG_ERASE) ? "User" : "Update");
				if (rd && (plist_get_node_type(rd) == PLIST_STRING)) {
					info = plist_new_dict();
					plist_dict_insert_item(info, "Path", plist_copy(rd));
					comp = plist_new_dict();
					plist_dict_insert_item(comp, "Info", info);
					plist_dict_insert_item(manifest, "RestoreRamDisk", comp);
				}
			}

			// add OS filesystem
			node = plist_dict_get_item(buildmanifest, "SystemRestoreImages");
			if (!node) {
				error("ERROR: missing SystemRestoreImages in Restore.plist\n");
			}
			plist_t os = plist_dict_get_item(node, "User");
			if (!os) {
				error("ERROR: missing filesystem in Restore.plist\n");
			} else {
				info = plist_new_dict();
				plist_dict_insert_item(info, "Path", plist_copy(os));
				comp = plist_new_dict();
				plist_dict_insert_item(comp, "Info", info);
				plist_dict_insert_item(manifest, "OS", comp);
			}

			// finally add manifest
			plist_dict_insert_item(build_identity, "Manifest", manifest);
		}
	} else if (client->flags & FLAG_ERASE) {
		build_identity = build_manifest_get_build_identity(buildmanifest, 0);
		if (build_identity == NULL) {
			error("ERROR: Unable to find any build identities\n");
			plist_free(buildmanifest);
			return -1;
		}
	} else {
		// loop through all build identities in the build manifest
		// and list the valid ones
		int i = 0;
		int valid_builds = 0;
		int build_count = build_manifest_get_identity_count(buildmanifest);
		for (i = 0; i < build_count; i++) {
			build_identity = build_manifest_get_build_identity(buildmanifest, i);
			valid_builds++;
		}
	}

	/* print information about current build identity */
	build_identity_print_information(build_identity);

	/* retrieve shsh blobs if required */
	if (tss_enabled) {
		debug("Getting device's ECID for TSS request\n");
		/* fetch the device's ECID for the TSS request */
		if (get_ecid(client, &client->ecid) < 0) {
			error("ERROR: Unable to find device ECID\n");
			return -1;
		}
		info("Found ECID " FMT_qu "\n", (long long unsigned int)client->ecid);

		if (get_shsh_blobs(client, client->ecid, NULL, 0, build_identity, &client->tss) < 0) {
			error("ERROR: Unable to get SHSH blobs for this device\n");
			return -1;
		}
	}

	if (shsh_only) {
		if (!tss_enabled) {
			info("This device does not require a TSS record");
			return 0;
		}
		if (!client->tss) {
			error("ERROR: could not fetch TSS record");
			plist_free(buildmanifest);
			return -1;
		} else {
			char *bin = NULL;
			uint32_t blen = 0;
			plist_to_bin(client->tss, &bin, &blen);
			if (bin) {
				char zfn[512];
				sprintf(zfn, "shsh/" FMT_qu "-%s-%s.shsh", (long long int)client->ecid, client->device->product, client->version);
				__mkdir("shsh", 0755);
				struct stat fst;
				if (stat(zfn, &fst) != 0) {
					gzFile zf = gzopen(zfn, "wb");
					gzwrite(zf, bin, blen);
					gzclose(zf);
					info("SHSH saved to '%s'\n", zfn);
				} else {
					info("SHSH '%s' already present.\n", zfn);
				}
				free(bin);
			} else {
				error("ERROR: could not get TSS record data\n");
			}
			plist_free(client->tss);
			plist_free(buildmanifest);
			return 0;
		}
	}

	/* verify if we have tss records if required */
	if ((tss_enabled) && (client->tss == NULL)) {
		error("ERROR: Unable to proceed without a TSS record.\n");
		plist_free(buildmanifest);
		return -1;
	}

	if ((tss_enabled) && client->tss) {
		/* fix empty dicts */
		fixup_tss(client->tss);
	}

	// Extract filesystem from IPSW and return its name
	char* filesystem = NULL;
	if (ipsw_extract_filesystem(client->ipsw, build_identity, &filesystem) < 0) {
		error("ERROR: Unable to extract filesystem from IPSW\n");
		if (client->tss)
			plist_free(client->tss);
		plist_free(buildmanifest);
		return -1;
	}

	// if the device is in normal mode, place device into recovery mode
	if (client->mode->index == MODE_NORMAL) {
		info("Entering recovery mode...\n");
		if (normal_enter_recovery(client) < 0) {
			error("ERROR: Unable to place device into recovery mode\n");
			if (client->tss)
				plist_free(client->tss);
			plist_free(buildmanifest);
			return -1;
		}
	}

	// if the device is in DFU mode, place device into recovery mode
	if (client->mode->index == MODE_DFU) {
		recovery_client_free(client);
		if (client->flags & FLAG_CUSTOM) {
			info("connecting to DFU\n");
			if (dfu_client_new(client) < 0) {
				return -1;
			}
			info("exploiting with limera1n\n");
			// TODO: check for non-limera1n device and fail
			if (limera1n_exploit(client->device, client->dfu->client) != 0) {
				error("ERROR: limera1n exploit failed\n");
				dfu_client_free(client);
				return -1;
			}
			dfu_client_free(client);
			info("exploited\n");
		}
		if (dfu_enter_recovery(client, build_identity) < 0) {
			error("ERROR: Unable to place device into recovery mode\n");
			plist_free(buildmanifest);
			if (client->tss)
				plist_free(client->tss);
			return -1;
		}
	}

	if (client->mode->index == MODE_DFU) {
		client->mode = &idevicerestore_modes[MODE_RECOVERY];
	} else {
		/* now we load the iBEC */
		if (recovery_send_ibec(client, build_identity) < 0) {
			error("ERROR: Unable to send iBEC\n");
			return -1;
		}
		recovery_client_free(client);
	
		/* this must be long enough to allow the device to run the iBEC */
		/* FIXME: Probably better to detect if the device is back then */
		sleep(7);
	}

	if (client->build[0] > '8') {
		// we need another tss request with nonce.
		unsigned char* nonce = NULL;
		int nonce_size = 0;
		int nonce_changed = 0;
		if (get_nonce(client, &nonce, &nonce_size) < 0) {
			error("ERROR: Unable to get nonce from device!\n");
			recovery_send_reset(client);
			return -1;
		}

		if (!client->nonce || (nonce_size != client->nonce_size) || (memcmp(nonce, client->nonce, nonce_size) != 0)) {
			nonce_changed = 1;
			if (client->nonce) {
				free(client->nonce);
			}
			client->nonce = nonce;
			client->nonce_size = nonce_size;
		} else {
			free(nonce);
		}

		info("Nonce: ");
		int i;
		for (i = 0; i < client->nonce_size; i++) {
			info("%02x ", client->nonce[i]);
		}
		info("\n");

		if (nonce_changed && !(client->flags & FLAG_CUSTOM)) {
			// Welcome iOS5. We have to re-request the TSS with our nonce.
			plist_free(client->tss);
			if (get_shsh_blobs(client, client->ecid, client->nonce, client->nonce_size, build_identity, &client->tss) < 0) {
				error("ERROR: Unable to get SHSH blobs for this device\n");
				return -1;
			}
			if (!client->tss) {
				error("ERROR: can't continue without TSS\n");
				return -1;
			}
			fixup_tss(client->tss);
		}
	}

	// now finally do the magic to put the device into restore mode
	if (client->mode->index == MODE_RECOVERY) {
		if (client->srnm == NULL) {
			error("ERROR: could not retrieve device serial number. Can't continue.\n");
			return -1;
		}
		if (recovery_enter_restore(client, build_identity) < 0) {
			error("ERROR: Unable to place device into restore mode\n");
			plist_free(buildmanifest);
			if (client->tss)
				plist_free(client->tss);
			return -1;
		}
	}

	// device is finally in restore mode, let's do this
	if (client->mode->index == MODE_RESTORE) {
		info("About to restore device... \n");
		if (restore_device(client, build_identity, filesystem) < 0) {
			error("ERROR: Unable to restore device\n");
			return -1;
		}
	}

	info("Cleaning up...\n");
	if (filesystem)
		unlink(filesystem);

	info("DONE\n");
	return 0;
}