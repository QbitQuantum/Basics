	//-----------------------------------------------------------------------------
	void GGUIDXRenderManager::AddRnederUnit(const stRenderUnit& theRenderUnit)
	{
		//检查数组容量是否足够。
		if (m_nVertexContentIndexEnd+4 >= m_nVertexContentCapacity)
		{
			//容器空间不够了，则把容器空间扩大到原来的2倍。
			SoUInt sizeOfOldArray = (SoUInt)sizeof(stVertexContent) * m_nVertexContentCapacity;
			m_nVertexContentCapacity *= 2;
			stVertexContent* pNewArray = new stVertexContent[m_nVertexContentCapacity];
			SoUInt sizeOfNewArray = (SoUInt)sizeof(stVertexContent) * m_nVertexContentCapacity;
			memset(pNewArray, 0, sizeOfNewArray);
			memcpy_s(pNewArray, sizeOfNewArray, m_arrayVertexContent, sizeOfOldArray);
			SAFE_DELETE_ARRAY(m_arrayVertexContent);
			m_arrayVertexContent = pNewArray;
			//同步的扩充顶点缓冲区和索引缓冲区。
			CreateDXVertexBuffer(m_nVertexContentCapacity);
			CreateDXIndexBuffer(m_nVertexContentCapacity / 2);
		}
		//
		SoFloat fLeft = theRenderUnit.fPositionX;
		SoFloat fRight = fLeft + theRenderUnit.fWidth;
		SoFloat fTop = theRenderUnit.fPositionY;
		SoFloat fBottom = fTop + theRenderUnit.fHeight;
		SoFloat fDepth = theRenderUnit.fPositionZ;
		SoUInt32 uiColor = SoMakeColorRGBA(theRenderUnit.fColorR, theRenderUnit.fColorG, theRenderUnit.fColorB, theRenderUnit.fColorA);
		SoFloat fUVLeft = 0.0f;
		SoFloat fUVRight = 0.0f;
		SoFloat fUVTop = 0.0f;
		SoFloat fUVBottom = 0.0f;
		//
		//s_pTargetImageset没有放到头文件中作为成员变量，是因为不想为了字节对齐而
		//考虑s_pTargetImageset在成员列表中的排序问题。
		//这样做有缺陷，如果在一系列的AddRnederUnit()调用过程中做了删除Imageset的操作，
		//s_pTargetImageset有可能变成野指针。
		static GGUIImageset* s_pTargetImageset = NULL;
		ImagesetID destImagesetID = theRenderUnit.theImagesetID;
		if (m_theTargetImagesetID != destImagesetID)
		{
			m_theTargetImagesetID = destImagesetID;
			s_pTargetImageset = GGUIImagesetManager::GetInstance()->GetImageset(destImagesetID);
			m_theTargetDXTextureID = s_pTargetImageset->GetDXTextureID();
		}
		if (s_pTargetImageset)
		{
			const GGUIRect* pRect = s_pTargetImageset->GetImageRect(theRenderUnit.theImageRectID);
			if (pRect)
			{
				fUVLeft = pRect->m_fLeft;
				fUVRight = pRect->m_fRight;
				fUVTop = pRect->m_fTop;
				fUVBottom = pRect->m_fBottom;
			}
		}
		//
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fTop;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVTop;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fTop;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVTop;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fBottom;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVRight;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVBottom;
		++m_nVertexContentIndexEnd;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fX = fLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fY = fBottom;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fZ = fDepth;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fRHW = 1.0f;
		m_arrayVertexContent[m_nVertexContentIndexEnd].uiColor = uiColor;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordX = fUVLeft;
		m_arrayVertexContent[m_nVertexContentIndexEnd].fCoordY = fUVBottom;
		++m_nVertexContentIndexEnd;
	}