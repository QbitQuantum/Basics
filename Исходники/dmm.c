/*************************************************************************
* Date last modified: June 16th, 2013
* Description: Asks user for input to create new node
* Input parameters: 
* Returns: pointer to new user defined node (dynamically allocated)
* Precondition: Memory must be available
* Postcondition: Pointer to valid node is returned
*************************************************************************/
Node *createItem(void)
{
	char *pStr;
	char str[100];
	Node *pMem = NULL;

	_flushall();
	pMem = (Node*)malloc(sizeof(Node));
	printf("\nEnter artist: ");
	gets(str);
	pStr = (char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(pStr, str);
	pMem->pArtist = pStr;
	printf("Enter song title: ");
	gets(str);
	pStr = (char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(pStr, str);
	pMem->pSongTitle = pStr;
	printf("Enter album title: ");
	gets(str);
	pStr = (char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(pStr, str);
	pMem->pAlbumTitle = pStr;
	printf("Enter Genre: ");
	gets(str);
	pStr = (char*)malloc(sizeof(char)*(strlen(str)+1));
	strcpy(pStr, str);
	pMem->pGenre = pStr;
	printf("Enter song length: ");
	scanf("%lf", &(pMem->songLength));
	printf("Enter number of plays: ");
	scanf("%d", &(pMem->numTimesPlayed));
	printf("Enter rating: ");
	scanf("%d", &(pMem->rating));
	
	return pMem;
}