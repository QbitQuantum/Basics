	virtual void Run()
	{
		SetName("ZLibCompressor");

#if defined (DURANGO)
		SetThreadAffinityMask(GetCurrentThread(), BIT(3));
#endif

		while(!m_bCancelled || !m_files.empty())
		{
			m_event.Wait();

			uint8* pZLibCompressedBuffer = AllocateBlock();

			while(!m_files.empty())
			{
				CFile* pFile = m_files.pop();
				assert(pFile);
				PREFAST_ASSUME(pFile);

				while(!pFile->Closed() || !pFile->m_blocks.empty())
				{
					if( pFile->m_blocks.empty() )
					{ 
						CrySleep(1); // yield to give other threads a chance to do some work        
					}

					while(!pFile->m_blocks.empty())
					{
						SZLibBlock* block = pFile->m_blocks.pop();
						assert(block);
						PREFAST_ASSUME(block);

						if(pFile->m_pCompressor->m_bUseZLibCompression)
						{
							size_t compressedLength = XMLCPB_ZLIB_BUFFER_SIZE;
							bool compressionOk = gEnv->pSystem->CompressDataBlock( block->m_pZLibBuffer, block->m_ZLibBufferSizeUsed, pZLibCompressedBuffer, compressedLength );

							SZLibBlockHeader zlibHeader;
							zlibHeader.m_compressedSize = compressionOk ? compressedLength : SZLibBlockHeader::NO_ZLIB_USED;
							zlibHeader.m_uncompressedSize = block->m_ZLibBufferSizeUsed;
							pFile->m_bytesWrittenIntoFileUncompressed += block->m_ZLibBufferSizeUsed;

							pFile->Write( &zlibHeader, sizeof(SZLibBlockHeader) );
							if (compressionOk)
								pFile->Write( pZLibCompressedBuffer, compressedLength );
							else
								pFile->Write( block->m_pZLibBuffer, block->m_ZLibBufferSizeUsed );
						}
						else
						{
							pFile->Write(block->m_pZLibBuffer, block->m_ZLibBufferSizeUsed);
						}

						delete block;
					}
				}

				pFile->Finish();
				delete pFile;
			}

			FreeBlock(pZLibCompressedBuffer);
		}
	}