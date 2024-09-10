void ILSerializeWriterDestroy(ILSerializeWriter *writer)
{
	if(writer->blob)
	{
		ILFree(writer->blob);
	}
	ILFree(writer);
}