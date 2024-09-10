// our application-specific read function
HFileInputResult HSolidModel::Read(const wchar_t * FileName,
								   HBaseView * pHView,
								   bool clean_include,
								   HInputHandlerOptions * options) 
{   
	// This process is going to take sometime, convey that to the user
	CWaitCursor show_hourglass_cursor_through_this_function;

	HFileInputResult success = InputOK;
	wchar_t extension[64];
	wchar_t const * ext = wcsrchr(FileName, L'.');

	if(!ext)
		return InputBadFileName;

	++ext; //move one past the dot;

	// in case we have a Pro/E file which ends with a number, e.g., *.prt.1 or *.xas.1
	bool good_filename = true;
	wchar_t *filename_copy = 0;
	if ( good_filename && ext[0] >= L'0' && ext[0] <= L'9' ) { 
		if (filename_copy == 0) {
			int original_filename_len = (int)wcslen(FileName);
			filename_copy = new wchar_t [original_filename_len + 1];
			swprintf(filename_copy, original_filename_len, L"%ls", FileName);
			filename_copy[original_filename_len] = '\0';
		}
		wchar_t *bad_ext = wcsrchr(filename_copy, L'.');
		bad_ext[0] = '\0';
		ext = wcsrchr(filename_copy, L'.');
		if (!ext)
			good_filename = false;
		else
			ext++;
	}

	if (ext)
		swprintf(extension, 64, L"%ls", ext);

	if (filename_copy)
		delete [] filename_copy;

	if (!good_filename)
		return InputBadFileName;


	HC_Open_Segment_By_Key(GetModelKey());	
	// we should maybe read ach file into it's own subsegment of the main model segment 
	// however I am keeping with reading it into the modelkey directly so that reading
	// and writing out a file doesn't result in nesting occuring.  Gavin
#ifdef INTEROP
	if (wcsieq(extension, L"catpart") || wcsieq(extension, L"catproduct") || wcsieq(extension, L"cgr") ||
		wcsieq(extension, L"model")   || wcsieq(extension, L"session")    || wcsieq(extension, L"exp") ||
		wcsieq(extension, L"prt")     || wcsieq(extension, L"xpr")        ||
		wcsieq(extension, L"asm")     || wcsieq(extension, L"xas")        ||
		wcsieq(extension, L"igs")     || wcsieq(extension, L"iges")       ||
		wcsieq(extension, L"stp")     || wcsieq(extension, L"step")       ||
		wcsieq(extension, L"vda")     ||
		wcsieq(extension, L"sldprt")  || wcsieq(extension, L"sldasm")	  ||
		wcsieq(extension, L"ipt")	  || wcsieq(extension, L"iam")
#ifdef ACIS
		|| wcsieq(extension, L"x_t") || wcsieq(extension, L"x_b")
#endif // ACIS
		) {
			m_bSolidModel = true;
			m_bSolidData = true;
			SetBRepGeometry(true);
			SetModelHandedness(HandednessSetLeft);
#ifdef ACIS
			DELTA_STATE *ds;
			outcome o = api_note_state(ds);
			CHECK_OUTCOME(o);
#endif // ACIS
			success = iop_fio->Import(FileName, extension, (HBaseView *)pHView);
#ifdef ACIS
			o = api_note_state(ds);
			CHECK_OUTCOME(o);

			SetHistoryStream();
			o = api_note_state(ds);
			CHECK_OUTCOME(o);
#endif // ACIS
	}
#endif // INTEROP
#ifdef ACIS
#ifdef INTEROP
	else
#endif // INTEROP
		if  (!wcsnicmp(extension, L"sat", wcslen(L"sat")))
		{  
			ENTITY_LIST elist;
			ENTITY* entity;

			m_bSolidModel = true;
			m_bSolidData = true;
			SetBRepGeometry(true);
			SetModelHandedness(HandednessSetLeft);

			logical read_sat_result = HA_Read_Sat_File(H_ASCII_TEXT(FileName), elist);	// read an SAT file
			if( read_sat_result == FALSE )
			{
				AfxMessageBox(_T("Failed to read SAT file. The file may be corrupt or from later version of ACIS."));
				success = InputFail;
			}

			elist.init();						// set next() function to return first element in "list"
			while (entity = elist.next())
			{
				m_entityList.add(entity);
			}
		} 
		else if( !wcsnicmp(extension, L"asat", wcslen(L"asat")) )
		{  
			m_bSolidModel = true;
			m_bSolidData = true;
			SetBRepGeometry(true);
			SetModelHandedness(HandednessSetLeft);

			logical read_asat_result = HA_Read_Asat_File(H_ASCII_TEXT(FileName), m_modelList);
			if( read_asat_result == FALSE )
			{
				AfxMessageBox(_T("Failed to read ASAT file. The file may be corrupt or from later version of ACIS."));
				success = InputFail;
			}
			else
			{
				// render the entities
				m_modelList.init();
				asm_model* this_model = m_modelList.next();
				while (this_model)
				{
					MODEL_BEGIN(this_model)
						HA_Render_Model(this_model, "entity");
					this_model->get_top_level_entities(m_entityList, TRUE);
					HA_Render_Entities(m_entityList);
					MODEL_END(ASM_NO_CHANGE)

					this_model = m_modelList.next();
				}
			}

		} 

#endif // ACIS
#ifdef HOOPS_ONLY
		if(	wcsieq(extension, L"") )
		{
			AfxMessageBox(_T("Failed to read file. Unrecognized file extension."));
		}
#endif // HOOPS_ONLY			
		else
		{
			// we don't know what extensions the base class is capable of handling
			// let it try and read the file whatever the extension might be

//#ifndef HOOPS_ONLY				
//			if (wcsieq(extension, _T(KERN_STREAM_FILE)))
//				m_bSolidModel = true;
//			else
//#endif
			m_bSolidModel = true;

			SetBRepGeometry(false);
			if (wcsieq(extension, L"dwg") || wcsieq(extension, L"dxf")|| wcsieq(extension, L"dgn"))
			{
				//HInputHandlerOptions options;
				//wchar_t * p_dwg_textures_dir = 0;
				//if(CAppSettings::DWGTextureDirectory.IsEmpty() == FALSE)
				//{
				//	H_WCS wcs(CAppSettings::DWGTextureDirectory);
				//	p_dwg_textures_dir = wcsdup(wcs.encodedText());
				//}
				//options.m_pHBaseView = view;
				//options.m_pExtendedData = (void*) p_dwg_textures_dir;
				//options.m_bInputViaHSF = CAppSettings::bImportDWGviaBstream;
				//options.m_Deviation = atof(H_ASCII_TEXT(CAppSettings::DWGDeviation));
				//options.m_bImportMetadata = CAppSettings::bImportDWGXData;
				//options.m_bMergeEntityShells = true;
				//options.m_bImportAllLayouts = CAppSettings::bImportAllLayouts;

				////For DGN
				//options.m_bIgnoreOffLayer = CAppSettings::bIgnoreInvisibleLayers;
				//options.m_bIgnoreOffEntity = CAppSettings::bIgnoreInvisibleEntity;
				//options.m_coneFactor = atof(H_ASCII_TEXT(CAppSettings::DGNFactorForCone));
				//options.m_factorForSmartSolids = atof(H_ASCII_TEXT(CAppSettings::DGNFactorForSmartSolids ));

				//success = HBaseModel::Read(FileName, 0, true, &options);

				//if(p_dwg_textures_dir)
				//	free(p_dwg_textures_dir);
			}
			else
			{					
				//HInputHandlerOptions opt;
				//// PRC options
				//opt.m_pPRCPMIConnector = m_pPMIConnector;
				//opt.m_pPRCTopologyManager = m_TopologyManager;
				//opt.m_bPRCMergeFaces = !CAppSettings::bPrcFaceEdgeVertexSelectability;
				//opt.m_pPRCMultiModelSelectionCallback = MultiModelSelectionCallback;

				//// Other options
				//opt.m_pConnector = m_pConnector;
				//opt.m_tk = GetStreamFileTK();
				//opt.m_pHBaseView = view;
				//opt.m_bImportMetadata = CAppSettings::bImportDWGXData;;
				success = HBaseModel::Read(FileName/*, view, true, &opt*/);
				/*m_pPRCAsmModelFile = opt.m_pPRCAsmModelFile;
				HObjectManager::FileLoadHObjectCheck(GetModelKey());
				if (opt.m_bPRCWrongVersion)
				{
					MessageBox(0, H_TEXT(L"PRC Import requires functionality that is not available in your version of Acrobat.\nPlease update to the latest version of Acrobat to view this file."), _T("ERROR!"), MB_OK);
					success = InputOK;
				}*/
			}
		}
		// update the polygon handedness for this model
		//UpdateModelHandedness();


		HC_Close_Segment();
#if 0
		if( m_bSolidModel )
			GenerateLODsForBodies();
#endif
		return success;
}