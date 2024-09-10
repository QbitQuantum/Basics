void closeFileAuto(AutoFile* seqFile)
{
	if (!seqFile)
		return;

	if (seqFile->pid)
		_pclose(seqFile->file);
	else
		fclose(seqFile->file);
}