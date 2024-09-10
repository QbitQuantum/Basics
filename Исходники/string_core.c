/// <summary>
/// Construct a new String instance by concatenating many other strings together, with a glue string between them.
/// </summary>
/// <param name="glue">The glue string to insert between successive string instances.  This will not be
/// added to the start and end of the resulting string:  Only between strings.</param>
/// <param name="strs">The array of string instances to join to create the new string.</param>
/// <param name="numStrs">The number of string instances in the array.</param>
/// <returns>The new String instance.</returns>
String String_Join(const String glue, const String *strs, Int numStrs)
{
	Int length, dest, i;
	struct StringInt *str;
	Byte *newText;
	const Byte *glueText;
	Int glueLength;

	if (numStrs <= 0) return String_Empty;

	length = 0;
	for (i = 0; i < numStrs; i++)
	{
		length += ((const struct StringInt *)(strs[i]))->length;
	}
	length += (numStrs - 1) * ((const struct StringInt *)glue)->length;

	if (length <= 0) return String_Empty;

	str = GC_MALLOC_STRUCT(struct StringInt);
	if (str == NULL) Smile_Abort_OutOfMemory();
	newText = GC_MALLOC_TEXT(length);
	if (newText == NULL) Smile_Abort_OutOfMemory();

	str->length = length;
	str->text = newText;

	glueText = ((const struct StringInt *)glue)->text;
	glueLength = ((const struct StringInt *)glue)->length;

	MemCpy(newText, ((const struct StringInt *)(strs[0]))->text, ((const struct StringInt *)(strs[0]))->length);
	dest = ((const struct StringInt *)(strs[0]))->length;

	for (i = 1; i < numStrs; i++)
	{
		MemCpy(newText + dest, glueText, glueLength);
		dest += glueLength;
		MemCpy(newText + dest, ((const struct StringInt *)(strs[i]))->text, ((const struct StringInt *)(strs[i]))->length);
		dest += ((const struct StringInt *)(strs[i]))->length;
	}

	newText[length] = '\0';

	return (String)str;
}