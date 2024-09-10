bool mic_loadstate(EMUFILE &is, int size)
{
	is.fseek(size, SEEK_CUR);
	return true;
}