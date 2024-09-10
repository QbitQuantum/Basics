void PDBFileReader::ReadEverything(DebugInfo &to)
{
  ULONG celt;
  
  Contribs = 0;
  nContribs = 0;
  
  // read section table
  IDiaEnumTables *enumTables;
  if(Session->getEnumTables(&enumTables) == S_OK)
  {
    VARIANT vIndex;
    vIndex.vt = VT_BSTR;
    vIndex.bstrVal = SysAllocString(L"Sections");

    IDiaTable *secTable;
    if(enumTables->Item(vIndex,&secTable) == S_OK)
    {
      LONG count;

      secTable->get_Count(&count);
      Contribs = new SectionContrib[count];
      nContribs = 0;

      IDiaSectionContrib *item;
      while(SUCCEEDED(secTable->Next(1,(IUnknown **)&item,&celt)) && celt == 1)
      {
        SectionContrib &contrib = Contribs[nContribs++];

        item->get_addressOffset(&contrib.Offset);
        item->get_addressSection(&contrib.Section);
        item->get_length(&contrib.Length);
        item->get_compilandId(&contrib.Compiland);

				BOOL code=FALSE,initData=FALSE,uninitData=FALSE;
				item->get_code(&code);
				item->get_initializedData(&initData);
				item->get_uninitializedData(&uninitData);

				if(code && !initData && !uninitData)
					contrib.Type = DIC_CODE;
				else if(!code && initData && !uninitData)
					contrib.Type = DIC_DATA;
				else if(!code && !initData && uninitData)
					contrib.Type = DIC_BSS;
				else
					contrib.Type = DIC_UNKNOWN;

				BSTR objFileName = 0;
				
				IDiaSymbol *compiland = 0;
				item->get_compiland(&compiland);
				if(compiland)
				{
					compiland->get_name(&objFileName);
					compiland->Release();
				}

				sChar *objFileStr = BStrToString(objFileName,"<noobjfile>");
				contrib.ObjFile = to.GetFileByName(objFileStr);

				delete[] objFileStr;
				if(objFileName)
					SysFreeString(objFileName);

        item->Release();
      }

      secTable->Release();
    }

    SysFreeString(vIndex.bstrVal);
    enumTables->Release();
  }

  // enumerate symbols by (virtual) address
  IDiaEnumSymbolsByAddr *enumByAddr;
  if(SUCCEEDED(Session->getSymbolsByAddr(&enumByAddr)))
  {
    IDiaSymbol *symbol;
    // get first symbol to get first RVA (argh)
    if(SUCCEEDED(enumByAddr->symbolByAddr(1,0,&symbol)))
    {
      DWORD rva;
      if(symbol->get_relativeVirtualAddress(&rva) == S_OK)
      {
        symbol->Release();

        // now, enumerate by rva.
        if(SUCCEEDED(enumByAddr->symbolByRVA(rva,&symbol)))
        {
          do
          {
            ProcessSymbol(symbol,to);
            symbol->Release();

            if(FAILED(enumByAddr->Next(1,&symbol,&celt)))
              break;
          }
          while(celt == 1);
        }
      }
      else
        symbol->Release();
    }

    enumByAddr->Release();
  }

  // clean up
  delete[] Contribs;
}