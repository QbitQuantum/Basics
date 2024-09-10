// *TODO: deprecate
void LLUUID::toString(char *out) const
{
	std::string buffer;
	toString(buffer);
	strcpy(out,buffer.c_str()); /* Flawfinder: ignore */
}