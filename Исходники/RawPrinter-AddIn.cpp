//---------------------------------------------------------------------------//
bool CAddInRawPrinter::CallAsProc(const long lMethodNum,
                    tVariant* paParams, const long lSizeArray)
{ 
    switch(lMethodNum)
    { 
    case eMeth_Open:
		{
			if (hPrinter) {
				ClosePrinter(hPrinter);
				hPrinter = NULL;
			}

			WCHAR_T *m_PrinterName = paParams[0].pwstrVal;
			uint32_t len = paParams[0].wstrLen;
			uint32_t sz = sizeof(WCHAR_T)*(len + 1);
		
			if (PrinterName) {
				m_iMemory->FreeMemory(reinterpret_cast<void**>(&PrinterName));
				PrinterName = NULL;
				//delete PrinterName;
			}

			{
				m_iMemory->AllocMemory(reinterpret_cast<void**>(&PrinterName), sz);
				//PrinterName = new WCHAR_T[len + 1];
			}
			memcpy(reinterpret_cast<void*>(PrinterName), reinterpret_cast<void*>(m_PrinterName), sz);
			PrinterName[len] = 0;
			
			
			wchar_t *wp_Name = NULL;
			::convFromShortWchar(&wp_Name, PrinterName, len + 1);
			
			if (!OpenPrinterW(wp_Name, &hPrinter, NULL)) {
				wchar_t buf[512];
				wsprintf(buf, L"OpenPrinterW(%s) failed with code: %u", wp_Name, GetLastError());
				addError(1, L"Printer error", buf, 1);
			}
			
			delete [] wp_Name;
			
		}
        break;

    case eMeth_Close:
		
		if (PrinterName) {
			m_iMemory->FreeMemory(reinterpret_cast<void**>(&PrinterName));
			//delete PrinterName;
		}
		ClosePrinter(hPrinter);

		break;

    case eMeth_SendRaw:

		{
			WCHAR_T *wc = paParams[0].pwstrVal;
			char *utf8 = ConvToUtf8(wc);

			DWORD len = strlen(utf8), sent;
			if (!WritePrinter(hPrinter, utf8, len, &sent))
				addError(2, L"Failed to send data to printer!", L"Failed!", 2);

			delete [] utf8;
		}
        break;

	case eMeth_StartDocument:

		{
			
			wchar_t *doc_name = NULL;
			wchar_t *data_type = NULL;
			::convFromShortWchar(&doc_name, paParams[0].pwstrVal);
			::convFromShortWchar(&data_type, paParams[1].pwstrVal);

			DOC_INFO_1 doc;
			doc.pDocName = doc_name;
			doc.pOutputFile = NULL;
			doc.pDatatype = data_type;

			DWORD print_job = StartDocPrinter(hPrinter, 1, (LPBYTE)&doc);

			delete [] doc_name;
			delete [] data_type;
		}

		break;

	case eMeth_EndDocument:

		EndDocPrinter(hPrinter);
		break;

    default:
        return false;
    }

    return true;
}