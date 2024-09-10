int XmlWriteHeader (FILE *file)
{
	return fputs ("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<TrueCrypt64>", file);
}