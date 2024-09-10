void main()
{
	int i, choice = 1;
	startNode = NULL;

	while (choice != 0)
	{
		puts("Please select an option:\n");
		puts("---------------------------------------");
		puts("01\tInsert a Node");
		puts("02\tDelete a Node");
		puts("03\tDisplay all Nodes");
		puts("04\tSearch for a Node");
		puts("\n00\tExit");
		puts("---------------------------------------\n");

		fflush(stdin);
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			insertNode();
			break;

		case 2:
			deleteNode();
			break;

		case 3:
			displayAll();
			break;

		case 4:
			findNode();
			break;

		case 0:
			break;

		default:
			puts("Invalid selection!\n");
			break;
		}
	}
	free(startNode);
	free(currentNode);
}