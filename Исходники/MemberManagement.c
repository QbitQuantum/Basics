//회원 삭제
void deleteMember(int num, int index)
{
	MemberInfo save[100];
	int i, j;
	char inputDeletetext[6];
	char deleteText[6];

	//파일 포인터 선언
	FILE *fp;

	//파일 열기,에러 체크
	if ((fp = _fsopen("memberInfo.txt", "r", _SH_DENYNO)) == NULL)
	{
		puts("memberInfo.txt 열기 샐패");
		return;
	}
	//용도에 맞게 쓰기
	fread(&save, sizeof(MemberInfo), index, fp);
	//파일 닫기
	fclose(fp);

	printf("정말 삭제 하시려면 아래의 문구를 정확히 입력 하세요\n");
	srand((unsigned int)time(0));
	for (j = 0; j < 5; j++)
	{
		deleteText[j] = (rand() % 26) + 65;
	}
	for (j = 0; j < 5; j++)
	{
		printf("%c", deleteText[j]);
	}
	puts("");
	printf("입력 : ");
	
	inputString(inputDeletetext);
	
	for (i = 0; i < 2; i++)
	{
		if ((strlen(inputDeletetext) != 5))
		{
			system("cls");
			printf("5개의 문자를 입력 하세요\n");

			srand((unsigned int)time(0));
			for (j = 0; j < 5; j++)
			{
				deleteText[j] = (rand() % 26) + 65;
			}
			for (j = 0; j < 5; j++)
			{
				printf("%c", deleteText[j]);
			}
			puts("");

			printf("입력 : ");
			inputString(inputDeletetext);			
		}

		else if (strlen(inputDeletetext) == 5 && (strncmp(inputDeletetext, deleteText, 5) != 0))
		{
			system("cls");
			printf("입력하신 문자가 정확하지 않습니다 다시 입력해 주세요\n");

			srand((unsigned int)time(0));
			for (j = 0; j < 5; j++)
			{
				deleteText[j] = (rand() % 26) + 65;
			}
			for (j = 0; j < 5; j++)
			{
				printf("%c", deleteText[j]);
			}
			puts("");

			printf("입력 : "); 
			inputString(inputDeletetext);
			
		}
		else if ((strlen(inputDeletetext) == 5) && (strncmp(inputDeletetext, deleteText, 5) == 0))
		{
			if (save[num - 1].bookList[0] != 0)
			{
				printf("빌린 책이 있는 회원 정보는 삭제 하실수 없습니다.");
				return;
			}
			else
			{
				save[num - 1].id = 0;
				strcpy_s(save[num - 1].name, MAX_LENGTH, "delete");
				strcpy_s(save[num - 1].email, MAX_LENGTH, "delete");
				strcpy_s(save[num - 1].address, MAX_LENGTH, "delete");
				strcpy_s(save[num - 1].signNumber, MAX_LENGTH, "delete");
				strcpy_s(save[num - 1].phoneNumber, MAX_LENGTH, "delete");
				//strcpy_s(save[num].bookList, MAXBOOK, 0);
				save[num - 1].bookList[0] = 0;
				printf("%d번 회원의 정보 삭제가 완료 되었습니다.", num);
				Sleep(1000);
				system("cls");
			}
		}
	}
	//회원정보 저장
	//파일 열기,에러 체크
	if ((fp = _fsopen("memberInfo.txt", "w", _SH_DENYNO)) == NULL)
	{
		puts("memberInfo.txt 열기 샐패");
		return;
	}
	//용도에 맞게 쓰기
	fwrite(&save, sizeof(MemberInfo), index, fp);
	//파일 닫기
	fclose(fp);
}