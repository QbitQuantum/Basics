void removeContact(struct contact *tailContact)
{
	struct contact *currentContact;
	currentContact = (struct contact *)malloc(sizeof(struct contact));
	clearContact(currentContact);

	setCursorPosition(40,4); printColouredText("please enter record id: ", 2);
	fflush(stdin);
	scanf_s("%i", &currentContact->idNum);
	

	findDeleteContact( tailContact, currentContact);

	free(currentContact);
}