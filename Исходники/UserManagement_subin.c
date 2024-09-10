int searchUser(UserInfo userInfo[], int menu)
{
	int id, i, input, action = 1, num;
	char key[NAME_PHONE_BUFFER];
	int overlap[OVERLAP_BUFFER];

	while (1) {
		topMessage("검색", "Search");

		switch (menu)
		{
		case 1:
			messageBoxA("회원 ID로 검색");

			if (action){
				printf("\n\n\t\t\t\t ID : "); fgets(key, NAME_PHONE_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				id = atoi(key);	//scanf는 엔터값을 무시하기 때문에 fgets로 받고 정수로 변환하였음

				num = 0;
				for (i = 1; i <= count; i++){	//검색
					if (num + 1 >= OVERLAP_BUFFER)
						break;	//검색 결과가 너무 많으면 버퍼 한계치에서 끊음
					if (userInfo[i].userId == id)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t\t ID : %d \n", id);

			/* 검색 결과가 1명일 때 */
			if (num == 1) return overlap[num];

			/* 검색 결과가 2명 이상일 때 */
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);

			/* 검색 결과가 없을 때 */
			else puts("\n\n\n\t\t\t    존재하지 않는 ID입니다 ! \n\n\n");
			break;
		case 2:
			messageBoxA("이름으로  검색");

			if (action){
				printf("\n\n\t\t\t     이름 : "); fgets(key, NAME_PHONE_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				num = 0;
				for (i = 1; i <= count; i++){
					if (num + 1 >= OVERLAP_BUFFER)
						break;
					if (strcmp(userInfo[i].userName, key) == 0)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t     이름 : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t   존재하지 않는 이름입니다 ! \n\n\n");
			break;
		case 3:
			messageBoxA("연락처로  검색");

			if (action){
				printf("\n\n\t\t\t연락처 : "); fgets(key, ADDRESS_BUFFER, stdin);

				if (*(key + strlen(key) - 1) == '\n')
					*(key + strlen(key) - 1) = '\0';
				else while (getchar() != '\n');

				num = 0;
				for (i = 1; i <= count; i++){
					if (num + 1 >= OVERLAP_BUFFER)
						break;
					if (strcmp(userInfo[i].handphone, key) == 0)
						overlap[++num] = i;
				}
			}
			else printf("\n\n\t\t\t연락처 : %s \n", key);

			if (num == 1) return overlap[num];
			else if (num > 1) return searchManyPrint(userInfo, overlap, num);
			else puts("\n\n\n\t\t\t  존재하지 않는 연락처입니다 ! \n\n\n");
			break;
		}

		bottomMessageA();

		input = getch();

		if (input == ENTER_KEY){
			inSound();
			action = 1;
		}
		else if (input == ESC_KEY){
			outSound();
			return 0;
		}
		else{
			warningMessage(input - '0', 0, 0);
			action = 0;
		}
	}
}