/*Write the binary PCM frames to the given file*/
void JRS_PCM_write(JRS_PCM *p,const char *fName)
{
	FILE *f=FOPEN(fName,"wb");
	int i;
	for (i=0;i<p->nFrames;i++)
		FWRITE(&p->frames[i*128],128,1,f);
	FCLOSE(f);
	asfPrintStatus("Wrote %d 128-byte frames of JRS PCM data to '%s'.\n",p->nFrames,fName);
}