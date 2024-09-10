void main()
{
	LINKEDLIST LogInlist;
	LogInlist.InitList = InitLinkedList;
	LogInlist.InitList(&LogInlist, AddTop, AddBottom, AddPoint, DeleteAt, DeleteTop, DeleteBottom, DeleteAll);

	LINKEDLIST Memberlist;
	Memberlist.InitList = InitLinkedList;
	Memberlist.InitList(&Memberlist, AddTop, AddBottom, AddPoint, DeleteAt, DeleteTop, DeleteBottom, DeleteAll);

	LINKEDLIST Videolist;
	Videolist.InitList = InitLinkedList;
	Videolist.InitList(&Videolist, AddTop, AddBottom, AddPoint, DeleteAt, DeleteTop, DeleteBottom, DeleteAll);

	LINKEDLIST Rentallist;
	Rentallist.InitList = InitLinkedList;
	Rentallist.InitList(&Rentallist, AddTop, AddBottom, AddPoint, DeleteAt, DeleteTop, DeleteBottom, DeleteAll);

	LINKEDLIST pSameNameRenTalList;
	pSameNameRenTalList.InitList = InitLinkedList;
	pSameNameRenTalList.InitList(&pSameNameRenTalList, AddTop, AddBottom, AddPoint, DeleteAt, DeleteTop, DeleteBottom, DeleteAll);

	File_Read_Member(&Memberlist);
	File_Read_Video(&Videolist);
	File_Read_Rental(&Rentallist);

	LINKEDLIST list;
	memset(&list, 0, sizeof(list));

	WSADATA data;
	memset(&data, 0, sizeof(data));
	WSAStartup(MAKEWORD(2, 2), &data);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET)
	{
		printf("ServerSocket 생성실패");
		return;
	}
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(50000);

	int iError = bind(ServerSocket, (sockaddr*)&addr, sizeof(addr));
	if (iError == SOCKET_ERROR)
	{
		printf("BIND ERROR\n");
		return;
	}
	iError = listen(ServerSocket, SOMAXCONN);
	if (iError == SOCKET_ERROR)
	{
		printf("LISTEN ERROR\n");
		return;
	}
	THREADPARAM AcceptParam;
	memset(&AcceptParam, 0, sizeof(AcceptParam));
	AcceptParam.pLinkedList = &list;
	AcceptParam.pMemberLIst = &Memberlist;
	AcceptParam.pVideoList = &Videolist;
	AcceptParam.pRenTalList = &Rentallist;
	AcceptParam.pLogInList = &LogInlist;
	AcceptParam.pSameNameRenTalList = &pSameNameRenTalList;
	AcceptParam.Socket = ServerSocket;
	_beginthreadex(NULL, NULL, AcceptFunc, (void*)&AcceptParam, NULL, NULL);


	int iChoice = 1;
	int iManageMamber = 1;
	int iManageVideo = 1;
	int iManageRental = 1;
	char temp[128];
	while (iChoice != 0)		//메인 루프
	{

		printf("1. 회원 관리 2. 비디오 관리 3. 비디오 대여 목록 관리 9.서버종료 \n");
		scanf_s("%d", &iChoice);
		fflush(stdin);
		switch (iChoice)
		{
		case 1:
			while (iManageMamber != 0)
			{
				printf("1. 접속자 관리 \n");
				printf("1.회원 추가 2. 회원 목록 3. 회원 검색 4. 회원 수정 5.회원 삭제 0.메인메뉴 \n");
				scanf_s("%d", &iManageMamber);
				fflush(stdin);
				switch (iManageMamber)
				{
				case 1:
					InputMember_Server(&Memberlist, &LogInlist);
					break;
				case 2:
					vPrintMember(&Memberlist);
					break;
				case 3:
					SearchMember(&Memberlist);
					break;
				case 4:
					ModifyMember_Server(&Memberlist);
					break;
				case 5:
					DeleteMember_Server(&Memberlist);
					break;
				case 6:
					iManageMamber = 0;
					break;
				}
				printf("\n");
			}
			iManageMamber = 1;
			break;
		case 2:
			while (iManageVideo != 0)
			{
				printf("2. 비디오 관리 \n");
				printf("1.비디오추가 2. 비디오 목록 3.비디오 검색 4. 비디오 수정 5. 비디오 삭제 0.메인메뉴\n");
				scanf_s("%d", &iManageVideo);
				fflush(stdin);
				switch (iManageVideo)
				{
				case 1:
					InputVideo(&Videolist);
					break;
				case 2:
					vPrintVideo(&Videolist);
					break;
				case 3:
					SearchVideo(&Videolist);
					break;
				case 4:
					ModifyVideo(&Videolist);
					break;
				case 5:
					DeleteVideo(&Videolist);
					break;
				case 0:
					iManageVideo = 0;
					break;
				}
				printf("\n");
			}
			iManageVideo = 1;
			break;
		case 3:
			while (iManageRental !=0)
			{
				printf("3. 비디오 대여관리\n1 = 비디오 대여 , 2 = 비디오 반납 , 3 = 비디오 대여목록 4 = 회원 대여목록 검색,0 =메인메뉴\n");
				scanf_s("%d", &iManageRental);
				fflush(stdin);
				switch (iManageRental){
				case 1:
					InputRental_Server(&Memberlist, &Videolist, &Rentallist);
					break;
				case 2:
					ReturnVideo(&Rentallist,&Videolist);
					break;
				case 3:
					PrintRentallist(&Rentallist);
					break;
				case 4:
					printf("찾을 회원의 이름 \n");
					gets_s(temp, sizeof(temp));
					fflush(stdin);
					PrintMemberRentalList(&Rentallist,temp);
					break;
				case 0:
					iManageRental = 0;
					break;
				}
				printf("\n");
			}
			iManageRental = 1;
			break;
		case 9:
			iChoice = 0;
			break;
		}
		File_Write_Member(&Memberlist);
		File_Write_Video(&Videolist);
		File_Write_Rental(&Rentallist);
	}		//메인루프 끝

	closesocket(ServerSocket);
	WSACleanup();
}