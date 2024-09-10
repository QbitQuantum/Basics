bool verifySignatures(struct mesgPackage mesg) {
	char certfile[50];
	bool verify;
	for (int i = 1; i <= num_hosts; i++) {
		if (mesg.pid[i] == 1) {
			printf("verifying message for pid = %d\n", i);
			strcpy(certfile, "./keys/");
			strcat(certfile, hostnames[i]);
			strcat(certfile, ".crt");
			printf("certfile is %s\n", certfile);

			verify = verifySignature(mesg.message, mesg.signatures[i], certfile);

			if (!verify) {
				printf("Verification Failed for pid=%d\n", i);
				return verify;
			}else{
				printf("Signature Verified OK! for pid=%d\n", i);
			}
		}
	}
	return verify;
}