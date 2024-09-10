    /*
    * Copyright (C) 2007 Apple Inc.  All rights reserved.
    *
    * Redistribution and use in source and binary forms, with or without
    * modification, are permitted provided that the following conditions
    * are met:
    * 1. Redistributions of source code must retain the above copyright
    *    notice, this list of conditions and the following disclaimer.
    * 2. Redistributions in binary form must reproduce the above copyright
    *    notice, this list of conditions and the following disclaimer in the
    *    documentation and/or other materials provided with the distribution.
    *
    * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
    * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
    * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
    * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
    * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    */
    static void DuplicateMedium(CLIPFORMAT source_clipformat,
        STGMEDIUM* source,
        STGMEDIUM* destination)
    {
        switch(source->tymed)
        {
        case TYMED_HGLOBAL:
            destination->hGlobal =
                static_cast<HGLOBAL>(OleDuplicateData(
                source->hGlobal, source_clipformat, 0));
            break;
        case TYMED_MFPICT:
            destination->hMetaFilePict =
                static_cast<HMETAFILEPICT>(OleDuplicateData(
                source->hMetaFilePict, source_clipformat, 0));
            break;
        case TYMED_GDI:
            destination->hBitmap =
                static_cast<HBITMAP>(OleDuplicateData(
                source->hBitmap, source_clipformat, 0));
            break;
        case TYMED_ENHMF:
            destination->hEnhMetaFile =
                static_cast<HENHMETAFILE>(OleDuplicateData(
                source->hEnhMetaFile, source_clipformat, 0));
            break;
        case TYMED_FILE:
            destination->lpszFileName =
                static_cast<LPOLESTR>(OleDuplicateData(
                source->lpszFileName, source_clipformat, 0));
            break;
        case TYMED_ISTREAM:
            destination->pstm = source->pstm;
            destination->pstm->AddRef();
            break;
        case TYMED_ISTORAGE:
            destination->pstg = source->pstg;
            destination->pstg->AddRef();
            break;
        }

        destination->tymed = source->tymed;
        destination->pUnkForRelease = source->pUnkForRelease;
        if(destination->pUnkForRelease)
        {
            destination->pUnkForRelease->AddRef();
        }
    }