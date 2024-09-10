int main (int argc, char *argv[]) {
	Card deck[DECK_SIZE];
	Card starting_deck[DECK_SIZE];

	char in_message[MAX_MESSAGE_LENGTH];
	char out_message[MAX_MESSAGE_LENGTH];
	int mode = 0; //encrypt = 0, decrypt = 1

	if (argc != 1) {
		printf("usage: SolitareEncryption1\n");
		printf("SEKEY environment variable must be set to the key value\n");
		exit(1);
	}

	init_deck(starting_deck);
	while (1) {
		//set the deck to the key starting position
		memcpy(deck, starting_deck, sizeof(Card) * DECK_SIZE);
		print_deck(deck);
		if (!mode) {
			printf("Enter message to be encrypted (type '/help' for help):\n");
		} else {
			printf("Enter message to be decrypted (type '/help' for help):\n");
		}
		fflush(stdout);
		if (fgets(in_message, MAX_MESSAGE_LENGTH, stdin) == NULL) {
			printf("fgets failure\n");
			exit(1);
		}

		//get rid of the newline from fgets
		int i;
		for (i = 0; in_message[i] != '\0'; i++) {
			if (in_message[i] == '\n') {
				in_message[i] = '\0';
				break;
			}
		}
		if (!strcmp(in_message, "/quit")) {
			break;
		} else if (!strcmp(in_message, "/encrypt")) {
			mode = 0;
			printf("Encryption mode\n");
		} else if (!strcmp(in_message, "/decrypt")) {
			mode = 1;
			printf("Decryption mode\n");
		} else if (!strcmp(in_message, "/help")) {
			printf("/encrypt: switch to encryption mode\n"
				   "/decrypt: switch to decryption mode\n"
				   "/quit: quit program\n");
		} else {
			if (!mode) {
				printf("Unencrypted: %s\n", in_message);
				printf("Encrypted: %s\n",
						encrypt(deck, in_message, out_message));
			} else {
				printf("Encrypted: %s\n", in_message);
				printf("Decrypted: %s\n",
						decrypt(deck, in_message, out_message));
			}
		}
	}
	return 0;
}