void PublishExcelToPDFWithWorkBook(Excel::_WorkbookPtr spWorkbook, const CStdString& sOutputFile, int from, int to)
{
	LOG_WS_FUNCTION_SCOPE();

	CStdString restrictionLevel = c_sNoRestriction;
	CStdString classification = c_sNoClassification;

	try
	{
		_variant_t vSaved = spWorkbook->Saved;
		restrictionLevel = GetRestrictionLevel(spWorkbook);
		classification = GetClassification(spWorkbook);

		// TODO: Switch off Excel's attempt to match the printer's paper size
		// by temporarily setting spWorkbook->Application->MapPaperSize = VARIANT_FALSE.
		// But that option isn't available in the Excel 2000 API that we're using.
		bool bIsNotExcel97 = (atof(spWorkbook->Application->Version) > 8.0);

		if( !PDFConverterController::UseExcelPrintArea() )
		{
			for (int iIndex = 1; iIndex <= spWorkbook->Worksheets->Count; iIndex++)
			{
				Excel::_WorksheetPtr spWorksheet = spWorkbook->Worksheets->Item[ iIndex ];
				spWorksheet->PageSetup->PrintArea = _T("");
			}
		}

		PDFConverterController pdfConverter;
		pdfConverter.InitialisePDFConverterUseFileName(sOutputFile, VARIANT_TRUE);
		_variant_t vtPrintToFile(false);
		_variant_t vtActivePrinter(c_sPDFDriverName);
		_variant_t vtOutputFile(sOutputFile);
		_variant_t vtFrom(vtMissing);
		_variant_t vtTo(vtMissing);

		if (from != 0 || to != 0)
		{
			vtFrom = from;
			vtTo = to;
		}

		if(bIsNotExcel97)
		{
			//60.18: This msg loop is to prevent the 'known' issue with Workshare events from crashing. 
			DoEvents();

			spWorkbook->PrintOut(&vtFrom, &vtTo, &vtMissing, &vtMissing, &vtActivePrinter, &vtPrintToFile, &vtMissing, &vtOutputFile);
		}
		else
		{
			if (::PathFileExists(sOutputFile) && !::DeleteFile(sOutputFile))
			{
				CStdString sMsg;
				sMsg.Format(_T("Failed to overwrite file %s"), sOutputFile.c_str());
				throw Workshare::System::IO::IOException(sMsg);
			}

			DismissPrintDialog(sOutputFile);

			_variant_t vtResult;
			IDispatchPtr spDispDocument = spWorkbook;
			HRESULT hr = CCOMDispatchHelper::AutoWrap(DISPATCH_METHOD, &vtResult, spDispDocument, L"PrintOut", 7,
				vtMissing, vtPrintToFile, vtActivePrinter, vtMissing, vtMissing, vtMissing, vtMissing);
			if (FAILED(hr))
				throw Workshare::Com::ComException(_T("Failed to invoke PrintOut method"), hr, spDispDocument);
		}
		pdfConverter.UnInitialisePDFConverter();

		// Setting the following property fixes an issue in the Office - iManage integration, 
		// in which iManage appears to query the Saved flag on Close and pops up a dialog, 
		// even though we have specified to Close with no Save:
		LCID lCid = LocaleHelper::GetLocaleIDForInstalledExcel(spWorkbook);
		spWorkbook->put_Saved(lCid, vSaved);


		if(c_sNoRestriction != restrictionLevel)
			SetPdfRestrictionLevel(sOutputFile, restrictionLevel);

		if (c_sNoClassification != classification)
			SetPdfClassification(sOutputFile, classification);
	}
	catch(const Workshare::Exception&)
	{
		throw;
	}
	catch(...)
	{
		unexpected(); 
	}
}