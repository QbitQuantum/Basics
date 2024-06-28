// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.FlatFile.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Moni_FlatfileHPP
#define Firedac_Moni_FlatfileHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Consts.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Moni.Base.hpp>
#include <FireDAC.Moni.Custom.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Moni.FlatFile"

namespace Firedac
{
namespace Moni
{
namespace Flatfile
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMoniFlatFileClientLink;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDMoniFlatFileClientLink : public Firedac::Moni::Base::TFDMoniClientLinkBase
{
	typedef Firedac::Moni::Base::TFDMoniClientLinkBase inherited;
	
private:
	Firedac::Stan::Intf::_di_IFDMoniFlatFileClient FFFClient;
	bool FFileNameChanged;
	System::UnicodeString __fastcall GetFileName();
	void __fastcall SetFileName(const System::UnicodeString AValue);
	bool __fastcall GetFileAppend();
	void __fastcall SetFileAppend(const bool AValue);
	Firedac::Stan::Intf::TFDTraceFileColumns __fastcall GetFileColumns();
	void __fastcall SetFileColumns(const Firedac::Stan::Intf::TFDTraceFileColumns Value);
	bool __fastcall IsFNS();
	Firedac::Stan::Intf::TFDEncoding __fastcall GetFileEncoding();
	void __fastcall SetFileEncoding(Firedac::Stan::Intf::TFDEncoding AValue);
	bool __fastcall GetShowTraces();
	void __fastcall SetShowTraces(bool AValue);
	
protected:
	virtual Firedac::Stan::Intf::_di_IFDMoniClient __fastcall GetMoniClient();
	
public:
	__fastcall virtual TFDMoniFlatFileClientLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDMoniFlatFileClientLink();
	__property Firedac::Stan::Intf::_di_IFDMoniFlatFileClient FFClient = {read=FFFClient};
	
__published:
	__property System::UnicodeString FileName = {read=GetFileName, write=SetFileName, stored=IsFNS};
	__property bool FileAppend = {read=GetFileAppend, write=SetFileAppend, default=0};
	__property Firedac::Stan::Intf::TFDTraceFileColumns FileColumns = {read=GetFileColumns, write=SetFileColumns, default=35};
	__property Firedac::Stan::Intf::TFDEncoding FileEncoding = {read=GetFileEncoding, write=SetFileEncoding, default=0};
	__property bool ShowTraces = {read=GetShowTraces, write=SetShowTraces, default=1};
	__property Tracing = {default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Flatfile */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_FLATFILE)
using namespace Firedac::Moni::Flatfile;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI)
using namespace Firedac::Moni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Moni_FlatfileHPP
