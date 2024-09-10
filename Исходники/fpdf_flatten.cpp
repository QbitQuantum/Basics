DLLEXPORT int STDCALL FPDFPage_Flatten( FPDF_PAGE page, int nFlag)
{
	if (!page)
	{
		return FLATTEN_FAIL;
	}

	CPDF_Page * pPage = (CPDF_Page*)( page );
	CPDF_Document * pDocument = pPage->m_pDocument;
	CPDF_Dictionary * pPageDict = pPage->m_pFormDict;
	
	if ( !pDocument || !pPageDict )
	{
		return FLATTEN_FAIL;
	}

	CPDF_ObjectArray ObjectArray;
	CPDF_RectArray  RectArray;

	int iRet = FLATTEN_FAIL;
	iRet = ParserAnnots( pDocument, pPageDict, &RectArray, &ObjectArray, nFlag);
	if (iRet == FLATTEN_NOTINGTODO)
	{
		return FLATTEN_NOTINGTODO;
	}else if (iRet == FLATTEN_FAIL)
	{
		return FLATTEN_FAIL;
	}
	
	CPDF_Rect rcOriginalCB;
	CPDF_Rect rcMerger = CalculateRect( &RectArray );
	CPDF_Rect rcOriginalMB = pPageDict->GetRect("MediaBox");

	if (pPageDict->KeyExist("CropBox"))
		rcOriginalMB = pPageDict->GetRect("CropBox");
	
	if (rcOriginalMB.IsEmpty()) 	
	{
		rcOriginalMB = CPDF_Rect(0.0f, 0.0f, 612.0f, 792.0f);
	}
	
	rcMerger.left = rcMerger.left < rcOriginalMB.left? rcOriginalMB.left : rcMerger.left;
	rcMerger.right = rcMerger.right > rcOriginalMB.right? rcOriginalMB.right : rcMerger.right;
	rcMerger.top = rcMerger.top > rcOriginalMB.top? rcOriginalMB.top : rcMerger.top;
	rcMerger.bottom = rcMerger.bottom < rcOriginalMB.bottom? rcOriginalMB.bottom : rcMerger.bottom;
	
	if (pPageDict->KeyExist("ArtBox"))
		rcOriginalCB = pPageDict->GetRect("ArtBox");
	else
		rcOriginalCB = rcOriginalMB;

	if (!rcOriginalMB.IsEmpty())
	{
		CPDF_Array* pMediaBox = FX_NEW CPDF_Array();	

		pMediaBox->Add(FX_NEW CPDF_Number(rcOriginalMB.left));
		pMediaBox->Add(FX_NEW CPDF_Number(rcOriginalMB.bottom));
		pMediaBox->Add(FX_NEW CPDF_Number(rcOriginalMB.right));
		pMediaBox->Add(FX_NEW CPDF_Number(rcOriginalMB.top));

		pPageDict->SetAt("MediaBox",pMediaBox);
	}
	
	if (!rcOriginalCB.IsEmpty())
	{
		CPDF_Array* pCropBox = FX_NEW CPDF_Array();
		pCropBox->Add(FX_NEW CPDF_Number(rcOriginalCB.left));
		pCropBox->Add(FX_NEW CPDF_Number(rcOriginalCB.bottom));
		pCropBox->Add(FX_NEW CPDF_Number(rcOriginalCB.right));
		pCropBox->Add(FX_NEW CPDF_Number(rcOriginalCB.top));
		pPageDict->SetAt("ArtBox", pCropBox);
	}

	CPDF_Dictionary* pRes = NULL;
	pRes = pPageDict->GetDict("Resources");
	if (!pRes)
	{
		pRes = FX_NEW CPDF_Dictionary;
		pPageDict->SetAt( "Resources", pRes );
	}

	CPDF_Stream* pNewXObject = FX_NEW CPDF_Stream(NULL, 0, FX_NEW CPDF_Dictionary);
	FX_DWORD dwObjNum = pDocument->AddIndirectObject(pNewXObject);
	CPDF_Dictionary* pPageXObject = pRes->GetDict("XObject");
	if (!pPageXObject)
	{
		pPageXObject = FX_NEW CPDF_Dictionary;
		pRes->SetAt("XObject", pPageXObject);
	}

	CFX_ByteString key = "";
	int nStreams = ObjectArray.GetSize();

	if (nStreams > 0)
	{
		for (int iKey = 0; /*iKey < 100*/; iKey++)
		{
			char sExtend[5] = {0};
			FXSYS_itoa(iKey, sExtend, 10);
			key = CFX_ByteString("FFT") + CFX_ByteString(sExtend);

			if (!pPageXObject->KeyExist(key))
				break;
		}
	}

	SetPageContents(key, pPageDict, pDocument);

	CPDF_Dictionary* pNewXORes = NULL;

	if (!key.IsEmpty())
	{
		pPageXObject->SetAtReference(key, pDocument, dwObjNum);
		CPDF_Dictionary* pNewOXbjectDic = pNewXObject->GetDict();
		pNewXORes = FX_NEW CPDF_Dictionary;
		pNewOXbjectDic->SetAt("Resources", pNewXORes);
		pNewOXbjectDic->SetAtName("Type", "XObject");
		pNewOXbjectDic->SetAtName("Subtype", "Form");
		pNewOXbjectDic->SetAtInteger("FormType", 1);
		pNewOXbjectDic->SetAtName("Name", "FRM");
		CPDF_Rect rcBBox = pPageDict->GetRect("ArtBox"); 
		pNewOXbjectDic->SetAtRect("BBox", rcBBox);
	}
	
	for (int i = 0; i < nStreams; i++)
	{
		CPDF_Dictionary* pAnnotDic = ObjectArray.GetAt(i);
		if (!pAnnotDic)continue;

		CPDF_Rect rcAnnot = pAnnotDic->GetRect("Rect");
		rcAnnot.Normalize();

		CFX_ByteString sAnnotState = pAnnotDic->GetString("AS");
		CPDF_Dictionary* pAnnotAP = pAnnotDic->GetDict("AP");
		if (!pAnnotAP)continue;

		CPDF_Stream* pAPStream = pAnnotAP->GetStream("N");
		if (!pAPStream)
		{
			CPDF_Dictionary* pAPDic = pAnnotAP->GetDict("N");
			if (!pAPDic)continue;

			if (!sAnnotState.IsEmpty())
			{
				pAPStream = pAPDic->GetStream(sAnnotState);
			}
			else
			{
				FX_POSITION pos = pAPDic->GetStartPos();
				if (pos)
				{
					CFX_ByteString sKey;
					CPDF_Object* pFirstObj = pAPDic->GetNextElement(pos, sKey);
					if (pFirstObj)
					{
						if (pFirstObj->GetType() == PDFOBJ_REFERENCE)
							pFirstObj = pFirstObj->GetDirect();
						
						if (pFirstObj->GetType() != PDFOBJ_STREAM)
							continue;

						pAPStream = (CPDF_Stream*)pFirstObj;
					}
				}
			}
		}

		if (!pAPStream)continue;

		CPDF_Dictionary* pAPDic = pAPStream->GetDict();
		CFX_AffineMatrix matrix = pAPDic->GetMatrix("Matrix");

		CPDF_Rect rcStream;
		if (pAPDic->KeyExist("Rect"))
			rcStream = pAPDic->GetRect("Rect");
		else if (pAPDic->KeyExist("BBox"))
			rcStream = pAPDic->GetRect("BBox");

		if (rcStream.IsEmpty())continue;

		CPDF_Object* pObj = pAPStream;

		if (pObj)
		{		
			CPDF_Dictionary* pObjDic = pObj->GetDict();
			if (pObjDic)
			{
				pObjDic->SetAtName("Type", "XObject");
				pObjDic->SetAtName("Subtype", "Form");
			}
		}

		CPDF_Dictionary* pXObject = pNewXORes->GetDict("XObject");
		if (!pXObject)
		{
			pXObject = FX_NEW CPDF_Dictionary;
			pNewXORes->SetAt("XObject", pXObject);
		}

		CFX_ByteString sFormName;
		sFormName.Format("F%d", i);
		FX_DWORD dwObjNum = pDocument->AddIndirectObject(pObj);
		pXObject->SetAtReference(sFormName, pDocument, dwObjNum);

		CPDF_StreamAcc acc;
		acc.LoadAllData(pNewXObject);

		FX_LPCBYTE pData = acc.GetData();
		CFX_ByteString sStream(pData, acc.GetSize());
		CFX_ByteString sTemp;

		if (matrix.IsIdentity())
		{
			matrix.a = 1.0f;
			matrix.b = 0.0f;
			matrix.c = 0.0f;
			matrix.d = 1.0f;
			matrix.e = 0.0f;
			matrix.f = 0.0f;
		}

		CFX_AffineMatrix m = GetMatrix(rcAnnot, rcStream, matrix);
		sTemp.Format("q %f 0 0 %f %f %f cm /%s Do Q\n", m.a, m.d, m.e, m.f, sFormName.c_str());
		sStream += sTemp;

		pNewXObject->SetData((FX_LPCBYTE)sStream, sStream.GetLength(), FALSE, FALSE);
	}
	pPageDict->RemoveAt( "Annots" );

	ObjectArray.RemoveAll();
	RectArray.RemoveAll();

	return FLATTEN_SUCCESS;
}