// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxCompressionFilter.pas' rev: 34.00 (iOS)

#ifndef Data_DbxcompressionfilterHPP
#define Data_DbxcompressionfilterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXTransport.hpp>
#include <System.SysUtils.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Dbxcompressionfilter
{
  _INIT_UNIT(Data_Dbxcompressionfilter);
}	/* namespace Dbxcompressionfilter */
}	/* namespace Data */

namespace Data
{
namespace Dbxcompressionfilter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTransportCompressionFilter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTransportCompressionFilter : public Data::Dbxtransport::TTransportFilter
{
	typedef Data::Dbxtransport::TTransportFilter inherited;
	
private:
	int FMinThreshold;
	
protected:
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetParameters();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetUserParameters();
	
public:
	__fastcall virtual TTransportCompressionFilter();
	virtual System::TArray__1<System::Byte> __fastcall ProcessInput(const System::TArray__1<System::Byte> Data);
	virtual System::TArray__1<System::Byte> __fastcall ProcessOutput(const System::TArray__1<System::Byte> Data);
	virtual System::UnicodeString __fastcall Id();
	virtual bool __fastcall SetConfederateParameter(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	virtual System::UnicodeString __fastcall GetParameterValue(const System::UnicodeString ParamName);
	virtual bool __fastcall SetParameterValue(const System::UnicodeString ParamName, const System::UnicodeString ParamValue);
	__property int MinThreshold = {read=FMinThreshold, write=FMinThreshold, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTransportCompressionFilter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxcompressionfilter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCOMPRESSIONFILTER)
using namespace Data::Dbxcompressionfilter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxcompressionfilterHPP
