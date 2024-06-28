// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDataExpressMetaDataProvider.pas' rev: 34.00 (Windows)

#ifndef Data_DbxdataexpressmetadataproviderHPP
#define Data_DbxdataexpressmetadataproviderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataProvider.hpp>
#include <Data.DBXMetaDataCommandFactory.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdataexpressmetadataprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDataExpressMetaDataProvider;
class DELPHICLASS TDBXDataExpressProviderWriteableContext;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataExpressMetaDataProvider : public Data::Dbxmetadataprovider::TDBXMetaDataProvider
{
	typedef Data::Dbxmetadataprovider::TDBXMetaDataProvider inherited;
	
private:
	Data::Dbxcommon::TDBXConnection* FConnection;
	
public:
	__fastcall TDBXDataExpressMetaDataProvider()/* overload */;
	__fastcall TDBXDataExpressMetaDataProvider(Data::Dbxcommon::TDBXConnection* Connection)/* overload */;
	void __fastcall Open();
	__property Data::Dbxcommon::TDBXConnection* Connection = {read=FConnection, write=FConnection};
public:
	/* TDBXMetaDataProvider.Destroy */ inline __fastcall virtual ~TDBXDataExpressMetaDataProvider() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataExpressProviderWriteableContext : public Data::Dbxmetadatacommandfactory::TDBXDataExpressProviderContext
{
	typedef Data::Dbxmetadatacommandfactory::TDBXDataExpressProviderContext inherited;
	
private:
	Data::Dbxcommon::TDBXTransaction* FTransaction;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableStorage(const System::UnicodeString CollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual Data::Dbxcommontable::TDBXTableRow* __fastcall CreateRowStorage(const System::UnicodeString CollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns);
	virtual void __fastcall StartTransaction();
	virtual void __fastcall StartSerializedTransaction();
	virtual void __fastcall Commit();
	virtual void __fastcall Rollback();
public:
	/* TDBXDataExpressProviderContext.Create */ inline __fastcall TDBXDataExpressProviderWriteableContext() : Data::Dbxmetadatacommandfactory::TDBXDataExpressProviderContext() { }
	/* TDBXDataExpressProviderContext.Destroy */ inline __fastcall virtual ~TDBXDataExpressProviderWriteableContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdataexpressmetadataprovider */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDATAEXPRESSMETADATAPROVIDER)
using namespace Data::Dbxdataexpressmetadataprovider;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdataexpressmetadataproviderHPP
