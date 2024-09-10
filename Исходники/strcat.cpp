int main()
{
	char someString[80] = {};
	/* concatenate strings */
	strcat( someString, "these ");
	strcat( someString, "strings ");
	strcat( someString, "are ");
	strcat( someString, "concatentated");
	puts( someString ); /* print string */
	return 0;	
}