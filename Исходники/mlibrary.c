void helpHandler(MainPlayerData *mpd, int help_choice[]) {
	int i = 0;
	int choice;
	int prob, rand;
	int ans = mpd->ques.ans - 1; //ans can be 0 1 2 3
	int flag = 0;
	for (i = 0; i < HELP_CHOICES; i++) {
		if (help_choice[i] != INVALID) {
			flag = 1;
			break;
		}
	}
	if (flag == 0) {
		printf("You have used all the help choices!\n");
		return;
	}
	switch (mpd->help_choice) {
	case 0: //50/50
		if (help_choice[0] == INVALID) {
			printf("You have used this help !\n");
			return;
		} else {
			char c;
			fifty_fifty(mpd);
			displayQuesWithFtyFty(mpd);
			help_choice[0] = INVALID;
			return;
		}
	case 1: //phone
		if (help_choice[1] == INVALID) {
			printf("You have used this help !\n");
			return;
		} else {
			int i;
			printf("\t>>>Lua chon nguoi tro giup<<<\n");
			printf("\t1.Isaac Newton.\n");
			printf("\t2.Mark Zuckerberg.\n");
			printf("\t3.Barack Obama.\n");
			printf(">>>Your choice :");
			while (1) {
				if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 3) {
					break;
				} else {
					printf("Wrong input ! Please type your choice again !\n");
				}
			}
			switch (choice) {
			case 1: //chon Newton
				prob = randomNumber(100) + 1;
				if (prob >= 15) {
					printf("Answer of Newton : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Newton : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}

				}
				help_choice[1] = INVALID;
				break;
			case 2: //chon Mark
				prob = randomNumber(100) + 1;
				if (prob >= 25) {
					printf("Answer of Mark Zuckerberg : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Mark Zuckerberg : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}
				}
				help_choice[1] = INVALID;
				break;
			case 3: //chon Barack Obama
				prob = randomNumber(100) + 1;
				if (prob >= 20) {
					printf("Answer of Barack Obama : %c.%s\n",
							IntToChar(mpd->ques.ans),
							mpd->ques.answerList[ans]);
				} else {
					for (i = 0; i < 4; i++) {
						if (i != ans && mpd->selectionStatus[i] == AVAILABLE) {
							printf("Answer of Barack Obama : %c.%s\n",
									IntToChar(i + 1), mpd->ques.answerList[i]);
							break;
						}
					}
				}
				help_choice[1] = INVALID;
				break;
			}
			return;
		}
	case 2: //Ask the Audience
		if (help_choice[2] == INVALID) {
			printf("You have used this help !\n");

		} else {
			askTheAudience(mpd);
			help_choice[2] = INVALID;
		}
		break;

	default:
		return;
	}
}