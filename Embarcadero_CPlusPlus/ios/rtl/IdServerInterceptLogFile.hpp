// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdServerInterceptLogFile.pas' rev: 34.00 (iOS)

#ifndef IdserverinterceptlogfileHPP
#define IdserverinterceptlogfileHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdServerInterceptLogBase.hpp>
#include <IdGlobal.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idserverinterceptlogfile
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdServerInterceptLogFile;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdServerInterceptLogFile : public Idserverinterceptlogbase::TIdServerInterceptLogBase
{
	typedef Idserverinterceptlogbase::TIdServerInterceptLogBase inherited;
	
protected:
	System::Classes::TFileStream* FFileStream;
	System::UnicodeString FFilename;
	
public:
	virtual void __fastcall Init();
	__fastcall virtual ~TIdServerInterceptLogFile();
	virtual void __fastcall DoLogWriteString(const System::UnicodeString AText);
	
__published:
	__property System::UnicodeString Filename = {read=FFilename, write=FFilename};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerInterceptLogFile(System::Classes::TComponent* AOwner)/* overload */ : Idserverinterceptlogbase::TIdServerInterceptLogBase(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerInterceptLogFile()/* overload */ : Idserverinterceptlogbase::TIdServerInterceptLogBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idserverinterceptlogfile */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSERVERINTERCEPTLOGFILE)
using namespace Idserverinterceptlogfile;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdserverinterceptlogfileHPP
