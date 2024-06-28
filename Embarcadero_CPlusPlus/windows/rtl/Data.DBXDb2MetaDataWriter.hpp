// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDb2MetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_Dbxdb2metadatawriterHPP
#define Data_Dbxdb2metadatawriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMetaDataWriter.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdb2metadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDb2MetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDb2MetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
public:
	__fastcall TDBXDb2MetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual bool __fastcall IsIndexNamesGlobal();
	virtual bool __fastcall IsDescendingIndexConstraintsSupported();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXDb2MetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdb2metadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDB2METADATAWRITER)
using namespace Data::Dbxdb2metadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Dbxdb2metadatawriterHPP
