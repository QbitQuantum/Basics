void dump_decrypted(running_machine& machine, UINT8* decrypt)
{
	FILE *fp;
	char filename[256];
	sprintf(filename,"dat_%s", machine.system().name);
	fp=fopen(filename, "w+b");
	if (fp)
	{
		fwrite(decrypt, 0x10000, 1, fp);
		fclose(fp);
	}
}