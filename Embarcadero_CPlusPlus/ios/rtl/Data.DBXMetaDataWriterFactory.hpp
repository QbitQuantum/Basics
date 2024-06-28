// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataWriterFactory.pas' rev: 34.00 (iOS)

#ifndef Data_DbxmetadatawriterfactoryHPP
#define Data_DbxmetadatawriterfactoryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <Data.DBXMetaDataWriter.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatawriterfactory
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMetaDataWriterFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXMetaDataWriterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TClass>* FProviderRegistry;
	
public:
	__classmethod void __fastcall RegisterWriter(System::UnicodeString DialectName, System::TClass WriterClass);
	__classmethod void __fastcall UnRegisterWriter(System::UnicodeString DialectName, System::TClass WriterClass);
	__classmethod void __fastcall FreeWriterRegistry();
	__classmethod Data::Dbxmetadatawriter::TDBXMetaDataWriter* __fastcall CreateWriter(System::UnicodeString DialectName);
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataWriterFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataWriterFactory() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define SWriterPrefix u"Borland.MetaDataWriter."
}	/* namespace Dbxmetadatawriterfactory */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATAWRITERFACTORY)
using namespace Data::Dbxmetadatawriterfactory;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatawriterfactoryHPP
