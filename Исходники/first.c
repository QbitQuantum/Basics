/* ParseDataArray: Stores in the data array.
 * Returns the number of entries used. */
int ParseDataArray()
{
	size_t originalDC;
	int number;
	bool notNumber;

	originalDC = DC;
	notNumber = false;
	/* construct a word for each element in the array and store it */
	while ((part = strtok(NULL, DELIMITERS_AND_COMMA)) != NULL)
	{
		NaN(part, notNumber);
		number = atoi(part);
		if (notNumber == true || (number == ZERO && *part != ZERO_CHAR))
		{
			DC = originalDC;
			SYNTAX_ASSERT(false, DATA_DEF_CONTAINS_NAN);
			return ERROR;
		}
		data[DC].Bits = number;
		DC++;
	}
	SYNTAX_ASSERT(ZERO < DC - originalDC, DATA_DEF_NO_NUMBERS);
	return DC - originalDC;
}