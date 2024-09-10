/*****************************************************************************
*
*   time2freq_adapt
*   transform to time domain data to freq. domain.
*   Blocks composed of multiple segments (i.e. all but long) have
*     input spectrums interleaved.
*   Notice: currently verified only for certain blocktypes
*   input: see below
*   output: see below
*   local static:
*     none
*   globals: none
*
*****************************************************************************/
void time2freq_adapt(faacDecHandle hDecoder,
                     WINDOW_TYPE blockType,          /* input: blockType 0-3                     */
                     Wnd_Shape *wnd_shape,   /* input/output                             */
                     Float *timeInPtr,       /* input: time domain data              */
                     Float *ffreqOutPtr)     /* output: 1/2 block of new freq values     */
{
    Float *transBuff, *transBuffPtr;
    int i, j;
    Float *srcPtr;
    Float *destPtr;
    Float *freqOutPtr;

    transBuff = AllocMemory(2*BLOCK_LEN_LONG*sizeof(Float));
    freqOutPtr = AllocMemory(BLOCK_LEN_LONG*sizeof(Float));

    if (blockType == NORM_TYPE)
    {
        srcPtr = timeInPtr;
        destPtr = transBuff;
        for (i = 2 * BLOCK_LEN_LONG / 16 - 1; i >= 0; --i)
        {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
        }
        /* Do 1 LONG transform */
        TransformBlock (hDecoder, transBuff, LONG_BLOCK, wnd_shape);

        srcPtr = transBuff;
        destPtr = freqOutPtr;
        for (i = BLOCK_LEN_LONG/16-1; i>=0; --i)
        {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
        }
    }

    else if (blockType == SHORT_TYPE)  {
        /* Do 8 SHORT transforms */

        srcPtr = timeInPtr + (BLOCK_LEN_LONG - BLOCK_LEN_SHORT) / 2;
        destPtr = freqOutPtr;

        for (i = 0; i < 8; i++) {
            transBuffPtr = transBuff;
            for (i = 2 * BLOCK_LEN_SHORT/16-1; i>=0; --i)  {
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
                *transBuffPtr++ = *srcPtr++;
            }
            srcPtr -= BLOCK_LEN_SHORT;
            TransformBlock (hDecoder, transBuff, SHORT_BLOCK, wnd_shape);

            /* Copy data to output buffer */
            transBuffPtr = transBuff;
            for (j = BLOCK_LEN_SHORT/16-1; j>=0; --j)  {
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;
                *destPtr++ = *transBuffPtr++;

            }
        }
    }

    else if (blockType == START_TYPE)  {
        srcPtr = timeInPtr;
        destPtr = transBuff;
        for (i = 2 * BLOCK_LEN_LONG/16-1; i>=0; --i)  {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;

        }
        TransformBlock (hDecoder, transBuff, START_FLAT_BLOCK, wnd_shape);

        srcPtr = transBuff;
        destPtr = freqOutPtr;
        for (i = BLOCK_LEN_LONG/16-1; i>=0; --i)  {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
        }
        hDecoder->dolbyShortOffset_t2f = 0;
    }

    else if (blockType == STOP_TYPE)  {
        srcPtr = timeInPtr;
        destPtr = transBuff;
        for (i = 2 * BLOCK_LEN_LONG/16-1; i>=0; --i)  {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
        }
        TransformBlock (hDecoder, transBuff, STOP_FLAT_BLOCK, wnd_shape);

        srcPtr = transBuff;
        destPtr = freqOutPtr;
        for (i = BLOCK_LEN_LONG/16-1; i>=0; --i)  {
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;
            *destPtr++ = *srcPtr++;

        }
    }

    srcPtr = freqOutPtr;
    destPtr = ffreqOutPtr;
    for (i = BLOCK_LEN_LONG/16-1; i>=0; --i)  {
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
        *destPtr++ = *srcPtr++;
    }

    FreeMemory(freqOutPtr);
    FreeMemory(transBuff);
}