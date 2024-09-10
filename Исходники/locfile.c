/**
 * Delete LocFile structure
 *
 * @param file pointer to LocFile which will be deleted
 */
void LocFileDelete( LocFile* file )
{
	if( file == NULL )
	{
		FERROR("Cannot free file which doesnt exist\n");
	}
	
	if( file->lf_Filename != NULL )
	{
		FFree( file->lf_Filename );
	}
	/*
	if( file->lf_Fp )
	{
		fclose( file->lf_Fp );
		file->lf_Fp = NULL;
	}
	*/
	if( file->lf_Path )
	{
		FFree( file->lf_Path );
		file->lf_Path = NULL;
	}
	if( file->lf_Buffer )
	{
#if LOCFILE_USE_MMAP == 0
		FFree( file->lf_Buffer );
#else
		munmap(file->lf_Buffer, file->lf_FileSize);
#endif
		file->lf_Buffer = NULL;
	}
	if( file->lf_Mime != NULL )
	{
		FFree( file->lf_Mime );
		file->lf_Mime = NULL;
	}

	FFree( file );	
}