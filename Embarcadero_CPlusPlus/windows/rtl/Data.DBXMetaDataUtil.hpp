// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataUtil.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmetadatautilHPP
#define Data_DbxmetadatautilHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatautil
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMetaDataUtil;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMetaDataUtil : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::UnicodeString __fastcall QuoteIdentifier(const System::UnicodeString UnquotedIdentifier, const System::UnicodeString QuoteChar, const System::UnicodeString QuotePrefix, const System::UnicodeString QuoteSuffix);
	static System::UnicodeString __fastcall UnquotedIdentifier(const System::UnicodeString QuotedIdentifier, const System::UnicodeString QuoteChar, const System::UnicodeString QuotePrefix, const System::UnicodeString QuoteSuffix);
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataUtil() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataUtil() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatautil */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATAUTIL)
using namespace Data::Dbxmetadatautil;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatautilHPP
