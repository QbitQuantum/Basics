int CMFTRecord::ExtractData(NTFS_ATTRIBUTE ntfsAttr, BYTE *&puchData, DWORD &dwDataLen) {
    DWORD dwCurPos = m_dwCurPos;

    if (!ntfsAttr.uchNonResFlag) {// residence attribute, this always resides in the MFT table itself

        puchData = new BYTE[ntfsAttr.Attr.Resident.dwLength];
        dwDataLen = ntfsAttr.Attr.Resident.dwLength;

        memcpy(puchData, &m_pMFTRecord[dwCurPos + ntfsAttr.Attr.Resident.wAttrOffset], dwDataLen);
    } else {// non-residence attribute, this resides in the other part of the physical drive

        if (!ntfsAttr.Attr.NonResident.n64AllocSize) // i don't know Y, but fails when its zero
            ntfsAttr.Attr.NonResident.n64AllocSize = (ntfsAttr.Attr.NonResident.n64EndVCN - ntfsAttr.Attr.NonResident.n64StartVCN) + 1;

        // ATTR_STANDARD size may not be correct
        dwDataLen = ntfsAttr.Attr.NonResident.n64RealSize;

        // allocate for reading data
        puchData = new BYTE[ntfsAttr.Attr.NonResident.n64AllocSize];

        BYTE chLenOffSz; // length & offset sizes
        BYTE chLenSz; // length size
        BYTE chOffsetSz; // offset size
        LONGLONG n64Len, n64Offset; // the actual lenght & offset
        LONGLONG n64LCN = 0; // the pointer pointing the actual data on a physical disk
        BYTE *pTmpBuff = puchData;
        int nRet;

        dwCurPos += ntfsAttr.Attr.NonResident.wDatarunOffset;
        ;

        for (;;) {
            ///// read the length of LCN/VCN and length ///////////////////////
            chLenOffSz = 0;

            memcpy(&chLenOffSz, &m_pMFTRecord[dwCurPos], sizeof (BYTE));

            dwCurPos += sizeof (BYTE);

            if (!chLenOffSz)
                break;

            chLenSz = chLenOffSz & 0x0F;
            chOffsetSz = (chLenOffSz & 0xF0) >> 4;

            ///// read the data length ////////////////////////////////////////

            n64Len = 0;

            memcpy(&n64Len, &m_pMFTRecord[dwCurPos], chLenSz);

            dwCurPos += chLenSz;

            ///// read the LCN/VCN offset //////////////////////////////////////

            n64Offset = 0;

            memcpy(&n64Offset, &m_pMFTRecord[dwCurPos], chOffsetSz);

            dwCurPos += chOffsetSz;

            ////// if the last bit of n64Offset is 1 then its -ve so u got to make it -ve /////
            if ((((char*) &n64Offset)[chOffsetSz - 1])&0x80)
                for (int i = sizeof (LONGLONG) - 1; i > (chOffsetSz - 1); i--)
                    ((char*) &n64Offset)[i] = 0xff;

            n64LCN += n64Offset;

            n64Len *= m_dwBytesPerCluster;
            ///// read the actual data /////////////////////////////////////////
            /// since the data is available out side the MFT table, physical drive should be accessed
            nRet = ReadRaw(n64LCN, pTmpBuff, (DWORD&) n64Len);
            if (nRet)
                return nRet;

            pTmpBuff += n64Len;
        }
    }
    return ERROR_SUCCESS;
}