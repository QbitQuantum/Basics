		int	AgilentRawData::GetSpecData(void)
		{
			HRESULT	res	= IIDFromString(L"{26E42183-9803-11D1-A9F6-0060977F5C78}", &mriid_wiff_file) ; 
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate Agilent object: IFMANWiffFile from ExploreDataObjects.dll.  You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			CoInitialize( NULL );
			CLSID clsid	; 

			res	=  CLSIDFromString(L"{C09D0EF8-926D-11D1-A9F2-0060977F5C78}", &clsid );		
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate Agilent object: FManSpecData from ExploreDataObjects.dll. You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			IID	riid ;
			res	= IIDFromString(L"{C09D0EF7-926D-11D1-A9F2-0060977F5C78}", &riid) ;	
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate Agilent object: FMANSpecData from ExploreDataObjects.dll.  You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			res	= CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mobj_spec_data);
			if(res != S_OK)
			{
				throw "Unable to instantiate Agilent object: FMANSpecData from ExploreDataObjects.dll.  You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			// clsid for FMANChromData
			res	= IIDFromString(L"{C09D0EF5-926D-11D1-A9F2-0060977F5C78}", &riid) ;	
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate Agilent object: IFMANChromData from ExploreDataObjects.dll.  You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			res	=  CLSIDFromString(L"{C09D0EF6-926D-11D1-A9F2-0060977F5C78}", &clsid );		
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate Agilent object: IFMANChromData from ExploreDataObjects.dll. You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res	= CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mobj_chrom_data);
			if(res != S_OK)
			{
				throw "Unable to instantiate Agilent object: IFMANChromData from ExploreDataObjects.dll.  You will need to install Analyst on this computer first or convert your file to MZXml format using mzStar on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			if(res != S_OK)
				return 1;


			return 0;
		}