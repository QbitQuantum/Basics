OleProperties::OleProperties(OleStorage& storage) :
   m_pStorage(storage), m_wCodePage(ENCODING_NONE)
{     
   USES_CONVERSION;
   
   IPropertySetStoragePtr spPropertySetStorage(storage.GetInternalObject());

   IPropertyStorage* pPropertyStorage = 0;
   HRESULT hr = spPropertySetStorage->Open(FMTID_UserDefinedProperties, STGM_READWRITE | STGM_SHARE_EXCLUSIVE, &pPropertyStorage);
   if(STG_E_FILENOTFOUND == hr)
      return;

   if(FAILED(hr))  
   {
      std::wostringstream os; 
      os << L"Failed to open the user defined property set" << FMTID_UserDefinedProperties << std::ends; 
      LOG_WS_INFO(os.str().c_str());
      return;
   }

   IPropertyStoragePtr spPropertyStorage(pPropertyStorage, false);

   IEnumSTATPROPSTG* pEnumProp = 0;	
	hr = spPropertyStorage->Enum(&pEnumProp);
	if(FAILED(hr))  // if fails, it is an Office bug
   {
      std::wostringstream os; 
      os << _T("Failed to get an IEnumSTATPROPSTG enumerator from the property set. PropertySet ID:[") << FMTID_UserDefinedProperties << _T("]. Continue process as this is not critical.") << std::ends; 
      LOG_WS_INFO(os.str().c_str());
      return;
   }
	
   SetCodePageProperty(spPropertyStorage);

   CollectionType collection;
   try
   {
      IEnumSTATPROPSTGPtr spEnumProp(pEnumProp, false);

      STATPROPSTG propertyInfo;
	   ZeroMemory(&propertyInfo, sizeof(STATPROPSTG));   
      hr = pEnumProp->Next(1, &propertyInfo, NULL);  

      while(S_OK == hr)
      {
         PROPVARIANT propertyVariant;  
         PropVariantInit(&propertyVariant);		
         PROPSPEC propSpec;
         ZeroMemory(&propSpec, sizeof(PROPSPEC));
         propSpec.ulKind = PRSPEC_PROPID;
         propSpec.propid = propertyInfo.propid;

         // Read this property.
         hr = spPropertyStorage->ReadMultiple(1, &propSpec, &propertyVariant);
         if(SUCCEEDED(hr))
         {		   		   
            bool visibleInExplorer = false;
            switch(propertyVariant.vt)
            {
            case VT_LPSTR:
            case VT_FILETIME:
            case VT_I4:
            case VT_BOOL:
               visibleInExplorer = true;
            }

            std::wstring name; 
            if(propertyInfo.lpwstrName != 0)
               name = W2T(propertyInfo.lpwstrName);

            std::wstring value;

            if(PIDSI_EDITTIME == propSpec.propid)
               value =FiletimeAsTimeSpan(propertyVariant);
            else
			{
				if (m_wCodePage == ENCODING_UTF8 && propertyVariant.vt == VT_LPSTR)
					value = ConvertPropertyFromUTF8(propertyVariant.pszVal);
				else
					value = (LPCTSTR)PropVariantToString(propertyVariant);
			}

            collection.push_back(new OleProperty(OlePropertySetGroupUserProperties, propSpec.propid, name, value, visibleInExplorer));
         }		      
         hr = pEnumProp->Next(1, &propertyInfo, NULL);
      }
      
      m_collection = collection;
   }
   catch(...)
   {
      for(CollectionType::iterator i = collection.begin(); i != collection.end(); i++)
         delete *i;

      std::wostringstream os; 
      os << _T("Failed to read a property. PropertySet ID:[") << FMTID_UserDefinedProperties  << _T("]. Continue process as this is not critical.") << std::ends; 
      LOG_WS_INFO(os.str().c_str());
   }
}