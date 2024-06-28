// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.COMAdmin.pas' rev: 34.00 (Windows)

#ifndef Winapi_ComadminHPP
#define Winapi_ComadminHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include <comadmin.h>

namespace Winapi
{
namespace Comadmin
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE ICOMAdminCatalog;
typedef System::DelphiInterface<ICOMAdminCatalog> _di_ICOMAdminCatalog;
__interface DELPHIINTERFACE ICatalogObject;
typedef System::DelphiInterface<ICatalogObject> _di_ICatalogObject;
__interface DELPHIINTERFACE ICatalogCollection;
typedef System::DelphiInterface<ICatalogCollection> _di_ICatalogCollection;
__dispinterface ICOMAdminCatalogDisp;
typedef System::DelphiInterface<ICOMAdminCatalogDisp> _di_ICOMAdminCatalogDisp;
__dispinterface ICatalogObjectDisp;
typedef System::DelphiInterface<ICatalogObjectDisp> _di_ICatalogObjectDisp;
__dispinterface ICatalogCollectionDisp;
typedef System::DelphiInterface<ICatalogCollectionDisp> _di_ICatalogCollectionDisp;
//-- type declarations -------------------------------------------------------
typedef _di_ICOMAdminCatalog COMAdminCatalog;

typedef _di_ICatalogObject COMAdminCatalogObject;

typedef _di_ICatalogCollection COMAdminCatalogCollection;

typedef Winapi::Activex::PSafeArray *PPSafeArray1;

__interface  INTERFACE_UUID("{DD662187-DFC2-11D1-A2CF-00805FC79235}") ICOMAdminCatalog  : public IDispatch 
{
	virtual HRESULT __safecall GetCollection(const System::WideString bstrCollName, _di_IDispatch &__GetCollection_result) = 0 ;
	virtual HRESULT __safecall Connect(const System::WideString bstrConnectString, _di_IDispatch &__Connect_result) = 0 ;
	virtual HRESULT __safecall Get_MajorVersion(int &__Get_MajorVersion_result) = 0 ;
	virtual HRESULT __safecall Get_MinorVersion(int &__Get_MinorVersion_result) = 0 ;
	virtual HRESULT __safecall GetCollectionByQuery(const System::WideString bstrCollName, Winapi::Activex::PSafeArray &aQuery, _di_IDispatch &__GetCollectionByQuery_result) = 0 ;
	virtual HRESULT __safecall ImportComponent(const System::WideString bstrApplIdOrName, const System::WideString bstrCLSIDOrProgId) = 0 ;
	virtual HRESULT __safecall InstallComponent(const System::WideString bstrApplIdOrName, const System::WideString bstrDLL, const System::WideString bstrTLB, const System::WideString bstrPSDLL) = 0 ;
	virtual HRESULT __safecall ShutdownApplication(const System::WideString bstrApplIdOrName) = 0 ;
	virtual HRESULT __safecall ExportApplication(const System::WideString bstrApplIdOrName, const System::WideString bstrApplicationFile, int lOptions) = 0 ;
	virtual HRESULT __safecall InstallApplication(const System::WideString bstrApplicationFile, const System::WideString bstrDestinationDirectory, int lOptions, const System::WideString bstrUserId, const System::WideString bstrPassword, const System::WideString bstrRSN) = 0 ;
	virtual HRESULT __safecall StopRouter() = 0 ;
	virtual HRESULT __safecall RefreshRouter() = 0 ;
	virtual HRESULT __safecall StartRouter() = 0 ;
	virtual HRESULT __safecall Reserved1() = 0 ;
	virtual HRESULT __safecall Reserved2() = 0 ;
	virtual HRESULT __safecall InstallMultipleComponents(const System::WideString bstrApplIdOrName, Winapi::Activex::PSafeArray &varFileNames, Winapi::Activex::PSafeArray &varCLSIDS) = 0 ;
	virtual HRESULT __safecall GetMultipleComponentsInfo(const System::WideString bstrApplIdOrName, Winapi::Activex::PSafeArray &varFileNames, /* out */ Winapi::Activex::PSafeArray &varCLSIDS, /* out */ Winapi::Activex::PSafeArray &varClassNames, /* out */ Winapi::Activex::PSafeArray &varFileFlags, /* out */ Winapi::Activex::PSafeArray &varComponentFlags) = 0 ;
	virtual HRESULT __safecall RefreshComponents() = 0 ;
	virtual HRESULT __safecall BackupREGDB(const System::WideString bstrBackupFilePath) = 0 ;
	virtual HRESULT __safecall RestoreREGDB(const System::WideString bstrBackupFilePath) = 0 ;
	virtual HRESULT __safecall QueryApplicationFile(const System::WideString bstrApplicationFile, /* out */ System::WideString &bstrApplicationName, /* out */ System::WideString &bstrApplicationDescription, /* out */ System::WordBool &bHasUsers, /* out */ System::WordBool &bIsProxy, /* out */ Winapi::Activex::PSafeArray &varFileNames) = 0 ;
	virtual HRESULT __safecall StartApplication(const System::WideString bstrApplIdOrName) = 0 ;
	virtual HRESULT __safecall ServiceCheck(int lService, int &__ServiceCheck_result) = 0 ;
	virtual HRESULT __safecall InstallMultipleEventClasses(const System::WideString bstrApplIdOrName, Winapi::Activex::PSafeArray &varFileNames, Winapi::Activex::PSafeArray &varCLSIDS) = 0 ;
	virtual HRESULT __safecall InstallEventClass(const System::WideString bstrApplIdOrName, const System::WideString bstrDLL, const System::WideString bstrTLB, const System::WideString bstrPSDLL) = 0 ;
	virtual HRESULT __safecall GetEventClassesForIID(const System::WideString bstrIID, /* out */ Winapi::Activex::PSafeArray &varCLSIDS, /* out */ Winapi::Activex::PSafeArray &varProgIDs, /* out */ Winapi::Activex::PSafeArray &varDescriptions) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MajorVersion() { int __r; HRESULT __hr = Get_MajorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MajorVersion = {read=_scw_Get_MajorVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_MinorVersion() { int __r; HRESULT __hr = Get_MinorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int MinorVersion = {read=_scw_Get_MinorVersion};
};

__dispinterface  INTERFACE_UUID("{DD662187-DFC2-11D1-A2CF-00805FC79235}") ICOMAdminCatalogDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{6EB22871-8A19-11D0-81B6-00A0C9231C29}") ICatalogObject  : public IDispatch 
{
	virtual HRESULT __safecall Get_Value(const System::WideString bstrPropName, System::OleVariant &__Get_Value_result) = 0 ;
	virtual HRESULT __safecall Set_Value(const System::WideString bstrPropName, System::OleVariant retval) = 0 ;
	virtual HRESULT __safecall Get_Key(System::OleVariant &__Get_Key_result) = 0 ;
	virtual HRESULT __safecall Get_Name(System::OleVariant &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall IsPropertyReadOnly(const System::WideString bstrPropName, System::WordBool &__IsPropertyReadOnly_result) = 0 ;
	virtual HRESULT __safecall Get_Valid(System::WordBool &__Get_Valid_result) = 0 ;
	virtual HRESULT __safecall IsPropertyWriteOnly(const System::WideString bstrPropName, System::WordBool &__IsPropertyWriteOnly_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Value(const System::WideString bstrPropName) { System::OleVariant __r; HRESULT __hr = Get_Value(bstrPropName, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Value[const System::WideString bstrPropName] = {read=_scw_Get_Value, write=Set_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Key() { System::OleVariant __r; HRESULT __hr = Get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Key = {read=_scw_Get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Name() { System::OleVariant __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_Valid() { System::WordBool __r; HRESULT __hr = Get_Valid(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool Valid = {read=_scw_Get_Valid};
};

__dispinterface  INTERFACE_UUID("{6EB22871-8A19-11D0-81B6-00A0C9231C29}") ICatalogObjectDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{6EB22872-8A19-11D0-81B6-00A0C9231C29}") ICatalogCollection  : public IDispatch 
{
	virtual HRESULT __safecall Get__NewEnum(System::_di_IInterface &__Get__NewEnum_result) = 0 ;
	virtual HRESULT __safecall Get_Item(int lIndex, _di_IDispatch &__Get_Item_result) = 0 ;
	virtual HRESULT __safecall Get_Count(int &__Get_Count_result) = 0 ;
	virtual HRESULT __safecall Remove(int lIndex) = 0 ;
	virtual HRESULT __safecall Add(_di_IDispatch &__Add_result) = 0 ;
	virtual HRESULT __safecall Populate() = 0 ;
	virtual HRESULT __safecall SaveChanges(int &__SaveChanges_result) = 0 ;
	virtual HRESULT __safecall GetCollection(const System::WideString bstrCollName, System::OleVariant varObjectKey, _di_IDispatch &__GetCollection_result) = 0 ;
	virtual HRESULT __safecall Get_Name(System::OleVariant &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_AddEnabled(System::WordBool &__Get_AddEnabled_result) = 0 ;
	virtual HRESULT __safecall Get_RemoveEnabled(System::WordBool &__Get_RemoveEnabled_result) = 0 ;
	virtual HRESULT __safecall GetUtilInterface(_di_IDispatch &__GetUtilInterface_result) = 0 ;
	virtual HRESULT __safecall Get_DataStoreMajorVersion(int &__Get_DataStoreMajorVersion_result) = 0 ;
	virtual HRESULT __safecall Get_DataStoreMinorVersion(int &__Get_DataStoreMinorVersion_result) = 0 ;
	virtual HRESULT __safecall PopulateByKey(Winapi::Activex::PSafeArray aKeys) = 0 ;
	virtual HRESULT __safecall PopulateByQuery(const System::WideString bstrQueryString, int lQueryType) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__NewEnum() { System::_di_IInterface __r; HRESULT __hr = Get__NewEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _NewEnum = {read=_scw_Get__NewEnum};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_Item(int lIndex) { _di_IDispatch __r; HRESULT __hr = Get_Item(lIndex, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch Item[int lIndex] = {read=_scw_Get_Item};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Count() { int __r; HRESULT __hr = Get_Count(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Count = {read=_scw_Get_Count};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Name() { System::OleVariant __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_AddEnabled() { System::WordBool __r; HRESULT __hr = Get_AddEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool AddEnabled = {read=_scw_Get_AddEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_RemoveEnabled() { System::WordBool __r; HRESULT __hr = Get_RemoveEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool RemoveEnabled = {read=_scw_Get_RemoveEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_DataStoreMajorVersion() { int __r; HRESULT __hr = Get_DataStoreMajorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int DataStoreMajorVersion = {read=_scw_Get_DataStoreMajorVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_DataStoreMinorVersion() { int __r; HRESULT __hr = Get_DataStoreMinorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int DataStoreMinorVersion = {read=_scw_Get_DataStoreMinorVersion};
};

__dispinterface  INTERFACE_UUID("{6EB22872-8A19-11D0-81B6-00A0C9231C29}") ICatalogCollectionDisp  : public IDispatch 
{
	
};

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 COMAdminMajorVersion = System::Int8(0x1);
static const System::Int8 COMAdminMinorVersion = System::Int8(0x0);
extern DELPHI_PACKAGE GUID CLASS_COMAdminCatalog;
extern DELPHI_PACKAGE GUID CLASS_COMAdminCatalogObject;
extern DELPHI_PACKAGE GUID CLASS_COMAdminCatalogCollection;
}	/* namespace Comadmin */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_COMADMIN)
using namespace Winapi::Comadmin;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_ComadminHPP
