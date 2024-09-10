void CToolSetTileBlock::Load( const string& path )
{
	CTerrainMesh* pTerrain = CMapEditApp::GetInst()->GetTerrain();

	//////////////////////////////////////////////////////////////////////////
	string strFileName = path;
	locale loc;
	use_facet<ctype<TCHAR> >( loc ).tolower
		( &strFileName[0], &strFileName[strFileName.length()] );

	size_t npos = strFileName.rfind(".");
	if( npos != -1 )
		strFileName = strFileName.substr(0, npos);

	string strLastBlockName = strFileName + "_last.block";
	strFileName += ".block";

	FILE * fp = NULL;
	fp = fopen(strFileName.c_str(),"rb");
	if (! fp )
	{
		string log = strFileName + "阻挡文件无法打开，查看是否被删掉了";

		MessageBox(NULL,log.c_str(),"请换其他地图",MB_OK);
		return;
	}

	::CopyFile(strFileName.c_str(), strLastBlockName.c_str(), FALSE);

	//////////////////////////////////////////////////////////////////////////
	///version
	DWORD dwVersion = BLOCK_VERSION;
	fread(&dwVersion,sizeof(dwVersion),1,fp);

	switch (dwVersion)
	{
	case BLOCK_TEX_INFO:
		{
			///读取设置障纹理名
			int8 nBlockTpyeCnt = EBT_CNT - 1;
			int  nBlockTpye = -1;
			for ( int8 i = 0; i < nBlockTpyeCnt; ++i )
			{
				nBlockTpye = i + 1;
				size_t size = 0;

				fread(&size,sizeof(size),1,fp);
				if( size != 0 )
				{
					string name("");
					int nLen = 0;

					for ( size_t i = 0; i < size; ++i )
					{	
						fread(&nLen,sizeof(nLen),1,fp);
						name.resize(nLen);
						fread((TCHAR*)name.data(),nLen,1,fp);
					}
				
				}
			}
		}
	case BLOCK_VERSION:
		{
			//////////////////////////////////////////////////////////////////////////
			///grid
			int nGridCnt = pTerrain->GetGridCount();

			for ( int i  = 0; i < nGridCnt; ++i )
			{
				int nBlockType = 0;
				fread(&nBlockType,sizeof(nBlockType),1,fp);

				SGrid &grid = pTerrain->GetGrid(i);
				grid.nBlockType = nBlockType;
			}
			//////////////////////////////////////////////////////////////////////////
		}
	default:
		break;
	}

	fclose(fp);
}