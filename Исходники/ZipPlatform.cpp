ZIPINLINE void ZipPlatform::AnsiOem(CZipAutoBuffer& buffer, bool bAnsiToOem)
{
	if (bAnsiToOem)
		CharToOemBuffA(buffer, buffer, buffer.GetSize());
	else
		OemToCharBuffA(buffer, buffer, buffer.GetSize());
}