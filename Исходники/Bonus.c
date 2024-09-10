//This code checks what the user wants for special feature when reaching the end of the GameBoard
int bonus()
{
	int i;
	printf("Choose which choice you want :  1. Delete a oppponent  \n");
	scanf_s("%d", &i);

	if (i == 1) {
		printf("Delete oppponent !\n");
		return 1;
	}
	else
	{
		printf("Invalid choice , bonus lost!\n");
		return 0;
	}
}