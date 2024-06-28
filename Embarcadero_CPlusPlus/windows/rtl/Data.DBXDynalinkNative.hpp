// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDynalinkNative.pas' rev: 34.00 (Windows)

#ifndef Data_DbxdynalinknativeHPP
#define Data_DbxdynalinknativeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXDynalink.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdynalinknative
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDynalinkDriverLoader;
class DELPHICLASS TDBXDynalinkDriverNative;
class DELPHICLASS TDBXNativeMethodTable;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDynalinkDriverLoader : public Data::Dbxdynalink::TDBXDynalinkDriverCommonLoader
{
	typedef Data::Dbxdynalink::TDBXDynalinkDriverCommonLoader inherited;
	
protected:
	virtual Data::Dbxdynalink::TDBXMethodTable* __fastcall CreateMethodTable();
	virtual Data::Dbxdynalink::TDBXDynalinkDriver* __fastcall CreateDynalinkDriver();
public:
	/* TDBXDynalinkDriverCommonLoader.Create */ inline __fastcall virtual TDBXDynalinkDriverLoader() : Data::Dbxdynalink::TDBXDynalinkDriverCommonLoader() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDynalinkDriverLoader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef int __stdcall (*TGetDriverFunc)(System::WideChar * SVendorLib, System::WideChar * SResourceFile, /* out */ void *Obj);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDynalinkDriverNative : public Data::Dbxdynalink::TDBXDynalinkDriver
{
	typedef Data::Dbxdynalink::TDBXDynalinkDriver inherited;
	
protected:
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	
public:
	__fastcall TDBXDynalinkDriverNative(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */;
	__fastcall TDBXDynalinkDriverNative(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */;
	__fastcall TDBXDynalinkDriverNative(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */;
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXDynalinkDriverNative() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall virtual TDBXDynalinkDriverNative(const Data::Dbxcommon::TDBXDriverDef &DriverDef)/* overload */ : Data::Dbxdynalink::TDBXDynalinkDriver(DriverDef) { }
	/* TDBXDriver.Create */ inline __fastcall TDBXDynalinkDriverNative()/* overload */ : Data::Dbxdynalink::TDBXDynalinkDriver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXNativeMethodTable : public Data::Dbxdynalink::TDBXMethodTable
{
	typedef Data::Dbxdynalink::TDBXMethodTable inherited;
	
private:
	NativeUInt FLibraryHandle;
	
public:
	__fastcall TDBXNativeMethodTable(NativeUInt LibraryHandle);
	__fastcall virtual ~TDBXNativeMethodTable();
	virtual void __fastcall LoadMethods();
	virtual void * __fastcall LoadMethod(System::UnicodeString MethodName);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdynalinknative */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDYNALINKNATIVE)
using namespace Data::Dbxdynalinknative;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxdynalinknativeHPP
