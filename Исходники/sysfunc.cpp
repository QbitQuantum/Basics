// Convert the number 'n' to a string representation.
const char* DUQSys::itoa(int n)
{
	static Dnchar result;
	result.sprintf("%i",n);
	return result;
}