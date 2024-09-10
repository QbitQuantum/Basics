void DeleteVideo(LINKEDLIST* list){
	int temp = 0;
	printf("찾을 값 : ");
	scanf_s("%d", &temp);
	fflush(stdin);
	NODE * pFindFlag = SSearchNumber(list, temp);
	if (pFindFlag)
	{
		list->DeleteAt(list, pFindFlag);
	}
	else
	{
		printf("그런거 없다.");
	}
}