/***
	Write bytes in a file from a given buffer.
	Parameters:
		- pvBuf: User buffer with data to write in file
		- tsSize: Size of iten to write
		- tsNumItens: Number of itens to write
	Return:
		Number of writtem itens in succes or E_NOTOPEN,
		E_BUFFNULL or E_WRITE.
***/
size_t
C_File::Write( void FAR *pvBuf, size_t tsSize, size_t tsNumItens )
{
	C_FileCritSect	cCS0( this, CRITSECT0 );

	size_t	i = 0;
	BOOL	bContinue = TRUE;


#ifdef _USE_PRINTF_
	Printf( "C_File: Estou em Write. (arq %s)", szFileName );
#endif
	int iFlag = FALSE;
	if( !pvBuf ){
		return( (size_t) E_BUFFNULL );
	}
	if( (_bIs32s && iFile == -1) || (!_bIs32s && hFile == INVALID_HANDLE_VALUE) ){
		if( ReOpen() != OK ){		   
			if( !_xFile ){
				return( 0 );
			}
			_xFile->PseudoClose();
			ReOpen();		   
			iFlag = TRUE;
		}
	}
	LockStruct ls( this, CurPos(), (tsSize * tsNumItens) );
	if( IsLocked( &ls ) ){
		if( iFlag ){
			PseudoClose();
			_xFile->ReOpen();
		}
#ifdef _USE_PRINTF_
		Printf( "C_File: Write: IsLocked." );
#endif
		return( (size_t) E_WRITE );
	}

	if( cCriptoOn ){
		Encrypt( pvBuf, szKey, tsSize );
	}

	// MMF
	BOOL	bWriteHeader = FALSE;
	if( !_bIs32s && hMMF ){
		// preparar gravacao a partir do MMF

		long	lFSize = FileSize();
		long	lCPos = CurPos();
		if( ( lCPos + (int) (tsNumItens * tsSize) ) > lFSize ){
			// este write vai exceder os limites do arquivo. vamos aumentar-lo.
			if( GrowFile( lCPos + (tsNumItens * tsSize) ) != OK ){
				// nao foi possivel aumentar o arquivo.
				bContinue = FALSE;
			}
		}
		if( bContinue ){
			if( (lCPos == iHeadInit)  && (((int) tsSize) == iHeadSize) ){
				bWriteHeader = TRUE;
				// vamos fazer write no header do arquivo.
				if( !pHeadView ){
					// o header ainda nao esta' mapeado. vamos fazer isso.
					CreateViewOfHead();
				}
			} else {
				if( !pWinView ){
					// o arquivo ainda nao esta' mapeado. vamos fazer isso.
					CreateViewOfFile();
				}
			}
		}
	}

	if( bContinue ){
		for( i = 0; i < tsNumItens; i++ ){
			if( _bIs32s ){
				if( write( iFile, pvBuf, (unsigned) tsSize ) < (int) tsSize ){
					break;
				}
			} else {
				if( bWriteHeader ){
					// gravar header no MMF.
					memcpy( pHeadView, pvBuf, tsSize );
				} else {
					if( pWinView ){
						// gravar no MMF.
						int	iNumBytes = ((iMMFWinSize * iPageSize) - iSeekWin) - (iHeadSize + 1);
						memcpy( (void*) ((char*) PWINVIEW + iSeekWin), pvBuf, min( iNumBytes, ((int) tsSize) ) );
						if( iNumBytes < ((int) tsSize) ){
							// precisamos mapear outra janela e continuar a gravacao
							++iWinNum;	// proxima janela
							CreateViewOfFile();
							if( !pWinView ){
								// mapeamento nao foi feito. fudeu.
								break;
							}
							// gravacao do restante
							memcpy( (void*) ((char*) PWINVIEW + iSeekWin), (void*) ((char*) pvBuf + iNumBytes), (tsSize - iNumBytes) );
							iSeekWin += (tsSize - iNumBytes);
						} else {
							iSeekWin += tsSize;
						}
					} else {
						DWORD	dwWrittenBytes;
						BOOL	bResult = WriteFile( hFile, pvBuf, (unsigned) tsSize, &dwWrittenBytes, NULL );
						if( !bResult || ( dwWrittenBytes < tsSize ) ){
							DWORD	dwErr = GetLastError();
							break;
						}
					}
				}
			}
		}
	}
//	if( ::GetTypeInt() == PE_REDE ){
//		Flush();
//	}
	dwLastUse = GetTickCount();
	if( cCriptoOn ){
		Decrypt( pvBuf, szKey, tsSize );
	}
	if( i < tsNumItens ){
#ifdef _USE_PRINTF_
		Printf( "C_File: Write: E_WRITE." );
#endif
		i = (size_t) E_WRITE;
	}
	if( iFlag ){
		PseudoClose();
		_xFile->ReOpen();
	}
#ifdef _USE_PRINTF_
	Printf( "C_File: Write: Vou retornar %d.", i );
#endif
	return( i );
}