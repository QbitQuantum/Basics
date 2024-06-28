// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProviderDataModuleAdapter.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproviderdatamoduleadapterHPP
#define Datasnap_DsproviderdatamoduleadapterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Data.DBXCommon.hpp>
#include <Datasnap.DataBkr.hpp>
#include <Datasnap.DSReflect.hpp>
#include <Datasnap.DSServer.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsproviderdatamoduleadapter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSProviderDataModuleAdapter;
class DELPHICLASS TDSServerModuleBase;
class DELPHICLASS TDSServerModule;
class DELPHICLASS TDSProviderServerClassAdapter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSProviderDataModuleAdapter : public Datasnap::Dsreflect::TDSDataModuleAdapterClass
{
	typedef Datasnap::Dsreflect::TDSDataModuleAdapterClass inherited;
	
private:
	Datasnap::Databkr::TProviderDataModule* FProviderDataModule;
	
protected:
	virtual System::Classes::TDataModule* __fastcall ExtractDataModule();
	
public:
	__fastcall virtual TDSProviderDataModuleAdapter(System::TObject* AdapteeInstance);
	__fastcall virtual ~TDSProviderDataModuleAdapter();
	System::OleVariant __fastcall AS_ApplyUpdates(const System::WideString ProviderName, const System::OleVariant &DeltaStream, int MaxErrors, /* out */ int &ErrorCount, Data::Dbxcommon::TDBXStreamValue* OwnerDataStream);
	System::OleVariant __fastcall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, Data::Dbxcommon::TDBXStreamValue* ParamReader, Data::Dbxcommon::TDBXStreamValue* OwnerDataStream);
	System::OleVariant __fastcall AS_DataRequest(const System::WideString ProviderName, const System::OleVariant &DataStream);
	System::OleVariant __fastcall AS_GetParams(const System::WideString ProviderName, Data::Dbxcommon::TDBXStreamValue* OwnerDataStream);
	System::OleVariant __fastcall AS_RowRequest(const System::WideString ProviderName, const System::OleVariant &RowStream, int RequestType, Data::Dbxcommon::TDBXStreamValue* OwnerDataStream);
	void __fastcall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, Data::Dbxcommon::TDBXStreamValue* ParamReader, Data::Dbxcommon::TDBXStreamValue* OwnerDataStream);
	System::UnicodeString __fastcall AS_GetProviderNames();
	__property Datasnap::Databkr::TProviderDataModule* ProviderDataModule = {read=FProviderDataModule, write=FProviderDataModule};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServerModuleBase : public Datasnap::Databkr::TProviderDataModule
{
	typedef Datasnap::Databkr::TProviderDataModule inherited;
	
public:
	virtual void __fastcall BeforeDestruction();
	__fastcall virtual ~TDSServerModuleBase();
public:
	/* TProviderDataModule.Create */ inline __fastcall virtual TDSServerModuleBase(System::Classes::TComponent* AOwner) : Datasnap::Databkr::TProviderDataModule(AOwner) { }
	
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TDSServerModuleBase(System::Classes::TComponent* AOwner, int Dummy) : Datasnap::Databkr::TProviderDataModule(AOwner, Dummy) { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSServerModule : public TDSServerModuleBase
{
	typedef TDSServerModuleBase inherited;
	
public:
	/* TDSServerModuleBase.Destroy */ inline __fastcall virtual ~TDSServerModule() { }
	
public:
	/* TProviderDataModule.Create */ inline __fastcall virtual TDSServerModule(System::Classes::TComponent* AOwner) : TDSServerModuleBase(AOwner) { }
	
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TDSServerModule(System::Classes::TComponent* AOwner, int Dummy) : TDSServerModuleBase(AOwner, Dummy) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSProviderServerClassAdapter : public Datasnap::Dsserver::TServerClassAdapter
{
	typedef Datasnap::Dsserver::TServerClassAdapter inherited;
	
public:
	virtual System::TObject* __fastcall CreateInstance(System::TObject* const Instance);
	virtual bool __fastcall IsSupportedAdapterType(System::TObject* const AObj);
	virtual bool __fastcall IsSupportedType(System::TObject* const AObj)/* overload */;
	virtual bool __fastcall IsSupportedType(const System::TClass AClass)/* overload */;
	virtual System::Classes::TPersistentClass __fastcall GetType();
	virtual System::Classes::TDataModule* __fastcall GetDataModule(System::TObject* const AObj);
	virtual void __fastcall ClearDataModule(System::TObject* const AObj);
public:
	/* TObject.Create */ inline __fastcall TDSProviderServerClassAdapter() : Datasnap::Dsserver::TServerClassAdapter() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSProviderServerClassAdapter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsproviderdatamoduleadapter */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROVIDERDATAMODULEADAPTER)
using namespace Datasnap::Dsproviderdatamoduleadapter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproviderdatamoduleadapterHPP
