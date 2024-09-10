static BOOL
OrgLoadImplicitLittleEndian(DICOMDataObject* pDDO, FILE* fp, unsigned int iVrSizeLimit)
{
	DICOMDataObject*	pNewDDO;
	VR*					pVR;
	char				Buf[2 + 2 + 4];

	while (fread(Buf, 1, sizeof(Buf), fp) == sizeof(Buf))
	{
		/* Group, Element and Size could be read */
		pVR = new VR;
		if (!pVR)
			return FALSE;
#if NATIVE_ENDIAN == LITTLE_ENDIAN //Little Endian
		pVR->Group   = *((unsigned short*) Buf);
		pVR->Element = *((unsigned short*)(Buf + 2));
		pVR->Length  = *((unsigned int*)  (Buf + 2 + 2));
#else //Big Endian like Apple power pc
		pVR->Group   = SwitchEndian( *((UINT16*) Buf));
		pVR->Element = SwitchEndian( *((UINT16*)(Buf + 2)));
		pVR->Length  = SwitchEndian( *((UINT32*)  (Buf + 2 + 2)));
#endif //Big Endian

		if (pVR->Group == 0xfffe)
		{
			/* A deliminator */
			if ((pVR->Element == 0xe0dd) || (pVR->Element == 0xe00d))
			{
				delete pVR;
				return TRUE;
			}
			if (pVR->Length == 0xffffffff)
			{
				/* Implicit length... Go until deliminator */
				pVR->Length = 0;
				delete pVR;
				pNewDDO = new DICOMDataObject;
				if (OrgLoadImplicitLittleEndian(pNewDDO, fp, iVrSizeLimit))
				{
					pDDO->Push(pNewDDO);
					continue;
				}
				else
				{
					delete pNewDDO;
					return FALSE;
				}
			}
			if (pVR->Element == 0xe000)
			{
				/* Sequence begin ? */
				pVR->Length = 0;
				delete pVR;
				pNewDDO = new DICOMDataObject;
				if (OrgLoadImplicitLittleEndian(pNewDDO, fp, iVrSizeLimit))
				{
					pDDO->Push(pNewDDO);
					continue;
				}
				else
				{
					delete pNewDDO;
					return FALSE;
				}
			}
		}
		if (pVR->Length == 0xffffffff)
		{
			pVR->Length = 0;
			pDDO->Push(pVR);
			if (!OrgLoadImplicitLittleEndian(pDDO, fp, iVrSizeLimit))
				return FALSE;
			continue;
		}
		/* Check whether the current VR has to be read.
		   NKI DicomNodes can restrict what has to be read
		   Following code assumes that reading is finished when pixeldata
		   are encountered. (Maybe a problem here!!!)
		*/
		if (pVR->Length > iVrSizeLimit)
		{
			if (((pVR->Group == 0x7fdf) || (pVR->Group == 0x7fe0)) &&
				(pVR->Element == 0x0010))
			{
				/* Ready !? */
				pVR->Length = 0;
				delete pVR;
				return TRUE;
			}
			else
			{	/* Read it, throw it away and continue */
//				pVR->Data = new char [pVR->Length];
				pVR->ReAlloc(pVR->Length);
				if (!pVR->Data)
					return FALSE;
				fread(pVR->Data, 1, pVR->Length, fp);
				delete pVR;
				continue;
			}
		}
		if (pVR->Length)
		{
//			pVR->Data = new char [pVR->Length];
			pVR->ReAlloc(pVR->Length);
			if (!pVR->Data)
				return FALSE;
			fread(pVR->Data, 1, pVR->Length, fp);
/*			if ((pVR->Group == 0x7fdf) && (pVR->Element == 0x0010))
			{ 
				VR* v;
				signed char *CompressedData = ((signed char *)(pVR->Data));
				int UncompressedLength = get_nki_private_decompressed_length(CompressedData);
				v = new VR(0x7fe0, 0x0010, UncompressedLength, TRUE);
     				nki_private_decompress((short *)(v->Data), CompressedData);
				delete pVR;
				pVR = v;
			}
*/		}
		else
			pVR->Data = NULL;
		pDDO->Push(pVR);
	}
	return TRUE;
}