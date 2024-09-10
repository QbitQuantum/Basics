void	TargetNode::Wildcards()
{
	TargetNode	*pTarget, *pTargetFile;
	if ( GetType() == TARGET_PROJECT )
		{
		GetNodeC()->Wildcards();
		GetNodeH()->Wildcards();
		pTarget = GetFirstChildPRJ();
		while ( pTarget )
			{
			 pTarget->Wildcards();
			 pTarget= pTarget->GetNext();
			}
		}
	else if ( GetType() == NODE_FILE_C || GetType() == NODE_FILE_H )
		{
		 char		szDrive						[_MAX_DRIVE	+1],	szFoundDrive[_MAX_DRIVE	+1];
		 char		szDir							[_MAX_DIR		+1],	szFoundDir	[_MAX_DIR		+1];
		 char		szFname						[_MAX_PATH	+1],	szFoundFname[_MAX_PATH	+1];
		 char		szExt							[_MAX_EXT		+1],	szFoundExt	[_MAX_EXT		+1];
		 char		szWildcardsPath		[_MAX_PATH	+1],	szFoundFile	[_MAX_DIR		+1];
		 char		szEmpty[] = "";

		 WIN32_FIND_DATA	FileFindData;

		 SetAllWorkFlagsToTrue();
		 while ( TRUE )
			{
			 pTargetFile = GetFirstChildTarget();
			 while ( pTargetFile )
			 {
				if ( pTargetFile-> GetWorkFlag() )
					{
					 _splitpath( pTargetFile->GetFileName(), szDrive, szDir, szFname, szExt );
					 if ( szFname[0] != '*' )
							break;
					}
				pTargetFile= pTargetFile->GetNext();
			 }
			 if ( pTargetFile == NULL )
				 break;

			 pTargetFile->SetWorkFlagToFalse();
			 _splitpath( pTargetFile->GetFilePath(), szFoundDrive, szFoundDir, szFoundFname, szFoundExt );
			 strcpy( szFoundFname, "*" );
			 _makepath( szWildcardsPath, szFoundDrive, szFoundDir, szFoundFname, szFoundExt );

			 int		nMatchedFiles=0, nNoMatchedFiles = 0;
			 HANDLE hFindFile = FindFirstFile( szWildcardsPath, &FileFindData );
			 if ( hFindFile != INVALID_HANDLE_VALUE )
			 do
			 	{
					 _makepath( szFoundFile, szFoundDrive, szFoundDir, FileFindData.cFileName, szEmpty );
					 pTarget = GetFirstChildTarget();
					 while ( pTarget )
					 {
						 if ( stricmp( pTarget->GetFilePath(), szFoundFile ) == 0 )
								break;
						 pTarget= pTarget->GetNext();
					 }
					 if ( pTarget )
						{
						 nMatchedFiles++;
						 pTarget->SetWorkFlagToFalse();
						}
					 else
						 nNoMatchedFiles++;
				}
			 while ( FindNextFile( hFindFile, &FileFindData ) );

			 if ( nMatchedFiles && (nNoMatchedFiles==0 || (nNoMatchedFiles*100)/nMatchedFiles<=50) )
				{
				 hFindFile = FindFirstFile( szWildcardsPath, &FileFindData );
				 do
					{
					 _makepath( szFoundFile, szFoundDrive, szFoundDir, FileFindData.cFileName, szEmpty );
					 pTarget = GetFirstChildTarget();
					 while ( pTarget )
					 {
						 if ( stricmp( pTarget->GetFilePath(), szFoundFile ) == 0 )
								break;
						 pTarget= pTarget->GetNext();
					 }
					 if ( pTarget )
							pTarget->SetDeleteFlag();
					 else	// szFoundFile is not matched to project's files, insert new one
						{
						 char*		pszPath = GetParentPRJ()->GetFilePath();
						 int			nPathLen = strlen( pszPath );

						 pTargetFile = new TargetNode (szFoundFile, this, GetFirstChildTarget()->GetType());
						 if ( strstr( pTargetFile->GetFilePath(), pszPath) )
							 pTargetFile->SetFileName( pTargetFile->GetFilePath() + nPathLen);
						 else
							 pTargetFile->SetFileName( pTargetFile->GetFilePath() );
						 pTargetFile->SetExclusionFlag();
						 pTargetFile->SetWorkFlagToFalse();
						}
					}
					while ( FindNextFile( hFindFile, &FileFindData ) );

					// ----------------- delete matched files
					pTargetFile = GetFirstChildTarget();
					BOOL	bFirstFlag = TRUE;
					while ( pTargetFile )
					{
						pTarget = pTargetFile->GetNext();
						if ( pTargetFile-> GetDeleteFlag() )
							{
							 if ( bFirstFlag )
							 {
								 _splitpath( pTargetFile->GetFileName(), szDrive, szDir, szFname, szExt );
								 strcpy( szFname, "*" );
								 _makepath( pTargetFile->GetFileName(), szDrive, szDir, szFname, szExt );
								 _splitpath( pTargetFile->GetFilePath(), szDrive, szDir, szFname, szExt );
								 strcpy( szFname, "*" );
								 _makepath( pTargetFile->GetFilePath(), szDrive, szDir, szFname, szExt );
								 bFirstFlag = FALSE;
							 }
							 else
								 delete pTargetFile;
							}
						pTargetFile= pTarget;
					}

				}	// if ( bFindAllFilesFlag )
			}	// while (TRUE )
	}	// else if ( GetType() == NODE_FILE_C || GetType() == NODE_FILE_H )
}