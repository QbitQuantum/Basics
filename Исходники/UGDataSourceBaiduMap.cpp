	void UGDataSourceBaiduMap::Create3DMapDatasetS()
	{   
		UGString strXmlPath =  UGFile::GetModulePath(_U("SuBase"))+_U("Resource/BMapCitySetting.xml");
		UGMarkup markup;
		UGMapServiceStub* pMapServiceStub = NULL;
		UGBaiDuMapsParams* pBaiduMapsParams = NULL;
		if (markup.Load(strXmlPath)) //加载xml文件
		{
			UGString strElemData =_U("");
			if (markup.FindElem(_U("CityParameters")))
			{   
				while (markup.FindChildElem(_U("sml:CityElem")))
				{
					pMapServiceStub = UGMapServiceStubManager::CreateMapServiceStub(UGC::BaiDu);
					pBaiduMapsParams = (UGBaiDuMapsParams*)UGMapServiceParamsManager::MakeParams(UGC::BaiDu);
					if (pBaiduMapsParams!=NULL&&pMapServiceStub!=NULL)
					{
						markup.IntoElem();
						if (markup.FindChildElem(_U("sml:CityName")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_strMapType = strElemData;
						}
						if (markup.FindChildElem(_U("sml:CityMark")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_strCityMark = strElemData;
						}
						if (markup.FindChildElem(_U("sml:CityNumber")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_nCityNumber = strElemData.ToInt();
						}
						if (markup.FindChildElem(_U("sml:Left")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.left = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Right")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.right = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Top")))
						{
							strElemData  = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.top = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:Bottom")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_rcBounds.bottom =strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:OrignX")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_pntOrigin.x = strElemData.ToDouble();
						}
						if (markup.FindChildElem(_U("sml:OrignY")))
						{
							strElemData = markup.GetChildData();
							pBaiduMapsParams->m_pntOrigin.y = strElemData.ToDouble();
						}
						markup.OutOfElem();

						//创建栅格数据集
						UGDatasetRasterBaiduMaps * pBaiduDataSetRaster = new UGDatasetRasterBaiduMaps;
						if (pBaiduDataSetRaster!=NULL)
						{   
							pBaiduDataSetRaster->SetDataSource(this);
							pBaiduDataSetRaster->SetMapServiceParams(pBaiduMapsParams);
							pBaiduDataSetRaster->SetMapServiceStub(pMapServiceStub);
							UGDatasetRasterInfo  * pDtRasterinfo = pBaiduDataSetRaster->GetInfo();
							pDtRasterinfo->m_strName	  = pBaiduMapsParams->m_strMapType;
							pDtRasterinfo->m_strTableName = pBaiduMapsParams->m_strMapType;
							pDtRasterinfo->m_nType = UGDataset::MBImage;
							UGBandInfo bandInfo;
							bandInfo.SetPixelFormat(IPF_RGBA);
							pDtRasterinfo->Add(bandInfo);
							//pDtRasterInfo->m_nBandCount = 1;
							//pDtRasterInfo->SetPixelFormat(IPF_RGBA);
							pDtRasterinfo->m_nWidth= pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
							pDtRasterinfo->m_nHeight=pBaiduMapsParams->m_nTileSize * pow(2.0, pBaiduMapsParams->m_nLevel);
							pDtRasterinfo->m_rc2Bounds = pBaiduMapsParams->m_rcBounds;
							pBaiduDataSetRaster->SetPrjCoordSys(pBaiduMapsParams->m_prjCoordSys);
							m_Datasets.Add(pBaiduDataSetRaster);
						}

					}
				}	
			}
		}		
	}