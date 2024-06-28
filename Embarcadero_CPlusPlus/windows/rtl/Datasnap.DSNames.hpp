// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSNames.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsnamesHPP
#define Datasnap_DsnamesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsnames
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSAdminMethods;
class DELPHICLASS TDSCacheColumns;
class DELPHICLASS TDSClassColumns;
class DELPHICLASS TDSConnectionColumns;
class DELPHICLASS TDSLifeCycle;
class DELPHICLASS TDSMetadataMethods;
class DELPHICLASS TDSMethodColumns;
class DELPHICLASS TDSMethodParametersColumns;
class DELPHICLASS TDSPackageColumns;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSAdminMethods : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSAdminMethods_CreateServerClasses L"DSAdmin.CreateServerClasses"
	
	#define TDSAdminMethods_CreateServerMethods L"DSAdmin.CreateServerMethods"
	
	#define TDSAdminMethods_FindClasses L"DSAdmin.FindClasses"
	
	#define TDSAdminMethods_FindMethods L"DSAdmin.FindMethods"
	
	#define TDSAdminMethods_FindPackages L"DSAdmin.FindPackages"
	
	#define TDSAdminMethods_GetPlatformName L"DSAdmin.GetPlatformName"
	
	#define TDSAdminMethods_GetServerClasses L"DSAdmin.GetServerClasses"
	
	#define TDSAdminMethods_GetServerMethods L"DSAdmin.GetServerMethods"
	
	#define TDSAdminMethods_GetServerMethodParameters L"DSAdmin.GetServerMethodParameters"
	
	#define TDSAdminMethods_DropServerClasses L"DSAdmin.DropServerClasses"
	
	#define TDSAdminMethods_DropServerMethods L"DSAdmin.DropServerMethods"
	
	#define TDSAdminMethods_GetDatabaseConnectionProperties L"DSAdmin.GetDatabaseConnectionProperties"
	
public:
	/* TObject.Create */ inline __fastcall TDSAdminMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSAdminMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCacheColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSCacheColumns_CacheName L"CacheName"
	
	#define TDSCacheColumns_MaxReaders L"MaxReaders"
	
	#define TDSCacheColumns_MaxReaderBytes L"MaxReaderBytes"
	
	#define TDSCacheColumns_MaxLifeTime L"MaxLifeTime"
	
	#define TDSCacheColumns_CacheData L"CacheData"
	
	#define TDSCacheColumns_HitCount L"HitCount"
	
	#define TDSCacheColumns_MissCount L"MissCount"
	
	#define TDSCacheColumns_ExpirationCount L"ExpirationCount"
	
public:
	/* TObject.Create */ inline __fastcall TDSCacheColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSCacheColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSClassColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSClassColumns_PackageName L"PackageName"
	
	#define TDSClassColumns_ServerClassName L"ClassName"
	
	#define TDSClassColumns_RoleName L"RoleName"
	
	#define TDSClassColumns_LifeCycle L"LifeCycle"
	
public:
	/* TObject.Create */ inline __fastcall TDSClassColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClassColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSConnectionColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSConnectionColumns_ConnectionName L"ConnectionName"
	
	#define TDSConnectionColumns_ConnectionProperties L"ConnectionProperties"
	
	#define TDSConnectionColumns_DriverName L"DriverName"
	
	#define TDSConnectionColumns_DriverProperties L"DriverProperties"
	
public:
	/* TObject.Create */ inline __fastcall TDSConnectionColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSConnectionColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSLifeCycle : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSLifeCycle_Server L"Server"
	
	#define TDSLifeCycle_Session L"Session"
	
	#define TDSLifeCycle_Invocation L"Invocation"
	
public:
	/* TObject.Create */ inline __fastcall TDSLifeCycle() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSLifeCycle() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMetadataMethods : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMetadataMethods_GetDatabase L"DSMetadata.GetDatabase"
	
	#define TDSMetadataMethods_GetProcedures L"DSMetadata.GetProcedures"
	
	#define TDSMetadataMethods_GetProcedureParameters L"DSMetadata.GetProcedureParameters"
	
public:
	/* TObject.Create */ inline __fastcall TDSMetadataMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMetadataMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMethodColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMethodColumns_MethodAlias L"MethodAlias"
	
	#define TDSMethodColumns_ServerClassName L"ServerClassName"
	
	#define TDSMethodColumns_ServerMethodName L"MethodName"
	
	#define TDSMethodColumns_RoleName L"RoleName"
	
public:
	/* TObject.Create */ inline __fastcall TDSMethodColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMethodColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMethodParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMethodParametersColumns_MethodAlias L"MethodAlias"
	
	#define TDSMethodParametersColumns_ServerClassName L"ServerClassName"
	
	#define TDSMethodParametersColumns_ServerMethodName L"MethodName"
	
	#define TDSMethodParametersColumns_ParameterName L"Name"
	
	#define TDSMethodParametersColumns_ParameterTypeName L"ParameterTypeName"
	
	#define TDSMethodParametersColumns_ParameterTypeUnit L"ParameterTypeUnit"
	
	#define TDSMethodParametersColumns_ParameterDirection L"ParameterDirection"
	
	#define TDSMethodParametersColumns_DbxDataType L"DBXType"
	
	#define TDSMethodParametersColumns_DbxSubDataType L"DBXSubType"
	
	#define TDSMethodParametersColumns_DbxParameterDirection L"DBXParameterDirection"
	
public:
	/* TObject.Create */ inline __fastcall TDSMethodParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMethodParametersColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSPackageColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSPackageColumns_PackageName L"PackageName"
	
public:
	/* TObject.Create */ inline __fastcall TDSPackageColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSPackageColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dsnames */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSNAMES)
using namespace Datasnap::Dsnames;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsnamesHPP
