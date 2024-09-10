bool savestate_save(EMUFILE* outstream)
{
#ifdef HAVE_JIT 
	arm_jit_sync();
#endif

	EMUFILE_MEMORY ms;
	EMUFILE* os = outstream;
   os->fseek(32,SEEK_SET); //skip the header
   writechunks(os);

	//save the length of the file
	u32 len = os->ftell();

	u32 comprlen = 0xFFFFFFFF;
	u8* cbuf;

	//dump the header
	outstream->fseek(0,SEEK_SET);
	outstream->fwrite(magic,16);
	write32le(SAVESTATE_VERSION,outstream);
	write32le(EMU_DESMUME_VERSION_NUMERIC(),outstream); //desmume version
	write32le(len,outstream); //uncompressed length
	write32le(comprlen,outstream); //compressed length (-1 if it is not compressed)

	return true;
}