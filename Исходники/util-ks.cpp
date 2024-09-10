BOOL 
GeneratePCMTestTone(LPVOID          pDataBuffer, 
					DWORD           cbDataBuffer,
					UINT            nSamplesPerSec,
					UINT            nChannels,
					WORD            wBitsPerSample,
					double          dFreq,
					double          dAmpFactor)
{
	static HANDLE hInput = CreateFile("input.pcm", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, NULL, NULL);
	DWORD t;
    BOOL        fRes = TRUE;
    double      dSinVal,
                dAmpVal,
                dK = dFreq * _2pi / (double)nSamplesPerSec;

    UINT i, iend, c;
    UINT j;

    UINT cwf = _clearfp();

    _controlfp(_MCW_RC, _RC_NEAR);
 
    switch(wBitsPerSample)
    {
        case 8:
        {
            PBYTE pbData;

            // Initialize the buffer to silence
            memset( pDataBuffer, _8BIT_SILENCE, cbDataBuffer );

            pbData = (PBYTE)pDataBuffer;

            iend = cbDataBuffer;
            for(j = 0, i = 0; i < iend;)
            {
                dSinVal = cos( (double)j * dK );
                dAmpVal = _8BIT_AMPLITUDE * dSinVal + _8BIT_SILENCE;
                dAmpVal *= dAmpFactor;
                for(c = 0; (c < nChannels) && (i < iend); c++)
                    pbData[i++] = (BYTE)(dAmpVal);
                
                j++;
            }
            break;
        }

        case 16:
        {
            //PSHORT psData;

            // Initialize the buffer to silence
            if(hInput == INVALID_HANDLE_VALUE)
			{
				memset( pDataBuffer, _16BIT_SILENCE, cbDataBuffer );
			}
			else
			{
				ReadFile(hInput, pDataBuffer, cbDataBuffer, &t, NULL);
				if(t != cbDataBuffer)	// reached EOF
					SetFilePointer(hInput, 0, NULL, FILE_BEGIN);
			}
            
			break;
        }
    
        case 20:
        {
            PDWORD  pdwData;

            // Initialize the buffer to silence
            memset( pDataBuffer, _20BIT_SILENCE, cbDataBuffer );

            pdwData = (PDWORD)pDataBuffer;

            iend = cbDataBuffer / 4;
            for(j = 0, i = 0; i < iend; )
            {
                dSinVal = cos( (double)j * dK );
                dAmpVal = _20BIT_AMPLITUDE * dSinVal;
                dAmpVal *= dAmpFactor;

                for(c = 0; (c < nChannels) && (i < iend); c++)
                    pdwData[i++] = ((DWORD)(dAmpVal)<< 12);

                j++;
            }
            break;
        }
    
        case 24:
        {
            PDWORD  pdwData;

            // Initialize the buffer to silence
            memset( pDataBuffer, _24BIT_SILENCE, cbDataBuffer );

            pdwData = (PDWORD)pDataBuffer;

            iend = cbDataBuffer / 4;
            for(j = 0, i = 0; i < iend; )
            {
                dSinVal = cos( (double)j * dK );
                dAmpVal = _24BIT_AMPLITUDE * dSinVal;
                dAmpVal *= dAmpFactor;

                for(c = 0; (c < nChannels) && (i < iend); c++)
                    pdwData[i++] = ((DWORD)(dAmpVal) << 8);

                j++;
            }
            break;
        }

        case 32:
        {
            PFLOAT  pdData;

            // Initialize the buffer to silence
            memset( pDataBuffer, (DWORD)_FLOAT_SILENCE, cbDataBuffer );

            pdData = (PFLOAT)pDataBuffer;

            iend = cbDataBuffer / 4;
            for(j = 0, i = 0; i < iend; )
            {
                dSinVal = cos( (double)j * dK );
                dAmpVal = _FLOAT_AMPLITUDE * dSinVal;
                dAmpVal *= dAmpFactor;

                for(c = 0; (c < nChannels) && (i < iend); c++)
                    pdData[i++] = (FLOAT)dAmpVal;

                j++;
            }
            break;
        }

        default:
            fRes = FALSE;
            break;
    }

    _controlfp(_MCW_RC, (cwf & _MCW_RC));

    return fRes;
}