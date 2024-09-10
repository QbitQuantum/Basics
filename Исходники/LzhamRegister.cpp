      HRESULT CDecoder::CodeSpec(ISequentialInStream *inStream, ISequentialOutStream *outStream, ICompressProgressInfo *progress)
      {
         if (_inBuf == 0 || !_propsWereSet)
            return S_FALSE;

         if (!_state)
         {
            if (CreateDecompressor() != S_OK)
               return E_FAIL;
         }

         UInt64 startInProgress = _inSizeProcessed;
         
         for (;;)
         {
            bool eofFlag = false;
            if (_inPos == _inSize)
            {
               _inPos = _inSize = 0;
               RINOK(inStream->Read(_inBuf, _inBufSizeAllocated, &_inSize));
               if (!_inSize)
                  eofFlag = true;
            }

            lzham_uint8 *pIn_bytes = _inBuf + _inPos;
            size_t num_in_bytes = _inSize - _inPos;
            lzham_uint8* pOut_bytes = _outBuf;
            size_t out_num_bytes = _outBufSize;
            if (_outSizeDefined)
            {
               UInt64 out_remaining = _outSize - _outSizeProcessed;
               if (out_num_bytes > out_remaining)
                  out_num_bytes = static_cast<size_t>(out_remaining);
            }
            
            lzham_decompress_status_t status = lzham_decompress(_state, pIn_bytes, &num_in_bytes, pOut_bytes, &out_num_bytes, eofFlag);
            
            if (num_in_bytes)
            {
               _inPos += (UInt32)num_in_bytes;
               _inSizeProcessed += (UInt32)num_in_bytes;
            }
                        
            if (out_num_bytes)
            {
               _outSizeProcessed += out_num_bytes;

               RINOK(WriteStream(outStream, _outBuf, out_num_bytes));
            }
            
            if (status >= LZHAM_DECOMP_STATUS_FIRST_FAILURE_CODE)
               return S_FALSE;

            if (status == LZHAM_DECOMP_STATUS_SUCCESS)
               break;
                        
            UInt64 inSize = _inSizeProcessed - startInProgress;
            if (progress)
            {
               RINOK(progress->SetRatioInfo(&inSize, &_outSizeProcessed));
            }
         }

         return S_OK;
      }