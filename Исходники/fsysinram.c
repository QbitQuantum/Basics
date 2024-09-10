int Rename( struct File *s, const char *path, const char *nname )
{
	DEBUG("Rename!\n");
	int res = 0;
	
	int error = 0;
	SpecialData *srd = (SpecialData *) s->f_SpecialData;
	INRAMFile *dir =INRAMFileGetLastPath( srd->root, path, &error );
	if( dir != NULL )
	{
		free( dir->nf_Name );
		free( dir->nf_Path );
		dir->nf_Name = StringDup( nname );
		
		int len = strlen( path );
		char *temp = calloc( len+512, sizeof(char) );
		if( temp != NULL )
		{
			int i = len;
			strcpy( temp, path );
			
			for( ; i >= 0 ; i-- )
			{
				if( temp[ i ] == '/' )
				{
					temp[ i+1 ] =  0;
				}
			}
			
			strcat( temp, nname );
			
			dir->nf_Path = temp;
		}
		else
		{
			FERROR("Cannot allocate memory\n");
		}
	}
	
	return res;
}