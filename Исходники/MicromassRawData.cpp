		void MicromassRawData::InitializeForV4()
		{
	#ifdef MASSLYNX_4_INSTALLED
			CLSID clsid ; 
			IID riid ;
			HRESULT res ; 
			
			// DACHeader		
			res =  CLSIDFromString(L"{111A3111-8A5C-11D5-809C-00508B5FFEC8}", &clsid ); 	
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate MassLynx objects: IDACHeader from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = IIDFromString(L"{111A3110-8A5C-11D5-809C-00508B5FFEC8}", &riid) ; 
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate MassLynx objects: IDACHeader from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mptr_dac_header);
			if(res != S_OK)
			{
				throw "Unable to instantiate MassLynx objects: IDACHeader from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
		
			// DACSpectrum
			res =  CLSIDFromString(L"{42BAE6E4-3D52-11D5-8043-00508B5FFEC8}", &clsid ); 	
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate MassLynx objects: IDACSpectrum from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = IIDFromString(L"{42BAE6E3-3D52-11D5-8043-00508B5FFEC8}", &riid) ; 
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate MassLynx objects: IDACSpectrum from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mptr_dac_spectrum);
			if(res != S_OK)
			{
				throw "Unable to instantiate MassLynx objects: IDACSpectrum from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			// DACScanStats
			res =  CLSIDFromString(L"{0D0678C2-3A1B-11D5-8040-00508B5FFEC8}", &clsid ); 	
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate MassLynx objects: IDACScanStats from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = IIDFromString(L"{0D0678C1-3A1B-11D5-8040-00508B5FFEC8}", &riid) ; 
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate MassLynx objects: IDACScanStats from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mptr_dac_scan_stat);
			if(res != S_OK)
			{
				throw "Unable to instantiate MassLynx objects: IDACScanStats from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}

			// DACFunctionInfo
			res =  CLSIDFromString(L"{63E4A0C2-5684-11D5-8063-00508B5FFEC8}", &clsid ); 	
			if (res ==REGDB_E_WRITEREGDB)
			{
				throw "Unable to instantiate MassLynx objects: IDACFunctionInfo from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = IIDFromString(L"{63E4A0C1-5684-11D5-8063-00508B5FFEC8}", &riid) ; 
			if (res == E_INVALIDARG)
			{
				throw "Unable to instantiate MassLynx objects: IDACFunctionInfo from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
			res = CoCreateInstance(clsid, NULL,CLSCTX_INPROC_SERVER, riid, (void **) &mptr_dac_func_info);
			if(res != S_OK)
			{
				throw "Unable to instantiate MassLynx objects: IDACFunctionInfo from DacServer.dll . Please install MassLynxV4 on this computer or convert file to MZXml file format using MassWolf on http://sashimi.sourceforge.net/software_glossolalia.html." ;
			}
	#endif 
		}