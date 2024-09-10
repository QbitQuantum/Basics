void FsFile::jumpToCursor()
{
	fseek(fh, cursor, SEEK_SET);
}