void DRTDataObject::CopyMedium(STGMEDIUM* pMedDest, STGMEDIUM* pMedSrc, FORMATETC* pFmtSrc)
{
    switch (pMedSrc->tymed) {
    case TYMED_HGLOBAL:
        pMedDest->hGlobal = static_cast<HGLOBAL>(OleDuplicateData(pMedSrc->hGlobal, pFmtSrc->cfFormat, 0));
        break;
    case TYMED_GDI:
        pMedDest->hBitmap = static_cast<HBITMAP>(OleDuplicateData(pMedSrc->hBitmap, pFmtSrc->cfFormat, 0));
        break;
    case TYMED_MFPICT:
        pMedDest->hMetaFilePict = static_cast<HMETAFILEPICT>(OleDuplicateData(pMedSrc->hMetaFilePict, pFmtSrc->cfFormat, 0));
        break;
    case TYMED_ENHMF:
        pMedDest->hEnhMetaFile = static_cast<HENHMETAFILE>(OleDuplicateData(pMedSrc->hEnhMetaFile, pFmtSrc->cfFormat, 0));
        break;
    case TYMED_FILE:
        pMedSrc->lpszFileName = static_cast<LPOLESTR>(OleDuplicateData(pMedSrc->lpszFileName, pFmtSrc->cfFormat, 0));
        break;
    case TYMED_ISTREAM:
        pMedDest->pstm = pMedSrc->pstm;
        pMedSrc->pstm->AddRef();
        break;
    case TYMED_ISTORAGE:
        pMedDest->pstg = pMedSrc->pstg;
        pMedSrc->pstg->AddRef();
        break;
    default:
        break;
    }
    pMedDest->tymed = pMedSrc->tymed;
    pMedDest->pUnkForRelease = 0;
    if (pMedSrc->pUnkForRelease) {
        pMedDest->pUnkForRelease = pMedSrc->pUnkForRelease;
        pMedSrc->pUnkForRelease->AddRef();
    }
}