// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSNames.pas' rev: 34.00 (Android)

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
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSAdminMethods : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSAdminMethods_CreateServerClasses u"DSAdmin.CreateServerClasses"
	
	#define TDSAdminMethods_CreateServerMethods u"DSAdmin.CreateServerMethods"
	
	#define TDSAdminMethods_FindClasses u"DSAdmin.FindClasses"
	
	#define TDSAdminMethods_FindMethods u"DSAdmin.FindMethods"
	
	#define TDSAdminMethods_FindPackages u"DSAdmin.FindPackages"
	
	#define TDSAdminMethods_GetPlatformName u"DSAdmin.GetPlatformName"
	
	#define TDSAdminMethods_GetServerClasses u"DSAdmin.GetServerClasses"
	
	#define TDSAdminMethods_GetServerMethods u"DSAdmin.GetServerMethods"
	
	#define TDSAdminMethods_GetServerMethodParameters u"DSAdmin.GetServerMethodParameters"
	
	#define TDSAdminMethods_DropServerClasses u"DSAdmin.DropServerClasses"
	
	#define TDSAdminMethods_DropServerMethods u"DSAdmin.DropServerMethods"
	
	#define TDSAdminMethods_GetDatabaseConnectionProperties u"DSAdmin.GetDatabaseConnectionProperties"
	
public:
	/* TObject.Create */ inline __fastcall TDSAdminMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSAdminMethods() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCacheColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSCacheColumns_CacheName u"CacheName"
	
	#define TDSCacheColumns_MaxReaders u"MaxReaders"
	
	#define TDSCacheColumns_MaxReaderBytes u"MaxReaderBytes"
	
	#define TDSCacheColumns_MaxLifeTime u"MaxLifeTime"
	
	#define TDSCacheColumns_CacheData u"CacheData"
	
	#define TDSCacheColumns_HitCount u"HitCount"
	
	#define TDSCacheColumns_MissCount u"MissCount"
	
	#define TDSCacheColumns_ExpirationCount u"ExpirationCount"
	
public:
	/* TObject.Create */ inline __fastcall TDSCacheColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSCacheColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSClassColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSClassColumns_PackageName u"PackageName"
	
	#define TDSClassColumns_ServerClassName u"ClassName"
	
	#define TDSClassColumns_RoleName u"RoleName"
	
	#define TDSClassColumns_LifeCycle u"LifeCycle"
	
public:
	/* TObject.Create */ inline __fastcall TDSClassColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClassColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSConnectionColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSConnectionColumns_ConnectionName u"ConnectionName"
	
	#define TDSConnectionColumns_ConnectionProperties u"ConnectionProperties"
	
	#define TDSConnectionColumns_DriverName u"DriverName"
	
	#define TDSConnectionColumns_DriverProperties u"DriverProperties"
	
public:
	/* TObject.Create */ inline __fastcall TDSConnectionColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSConnectionColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSLifeCycle : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSLifeCycle_Server u"Server"
	
	#define TDSLifeCycle_Session u"Session"
	
	#define TDSLifeCycle_Invocation u"Invocation"
	
public:
	/* TObject.Create */ inline __fastcall TDSLifeCycle() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSLifeCycle() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSMetadataMethods : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMetadataMethods_GetDatabase u"DSMetadata.GetDatabase"
	
	#define TDSMetadataMethods_GetProcedures u"DSMetadata.GetProcedures"
	
	#define TDSMetadataMethods_GetProcedureParameters u"DSMetadata.GetProcedureParameters"
	
public:
	/* TObject.Create */ inline __fastcall TDSMetadataMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMetadataMethods() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSMethodColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMethodColumns_MethodAlias u"MethodAlias"
	
	#define TDSMethodColumns_ServerClassName u"ServerClassName"
	
	#define TDSMethodColumns_ServerMethodName u"MethodName"
	
	#define TDSMethodColumns_RoleName u"RoleName"
	
public:
	/* TObject.Create */ inline __fastcall TDSMethodColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMethodColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSMethodParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSMethodParametersColumns_MethodAlias u"MethodAlias"
	
	#define TDSMethodParametersColumns_ServerClassName u"ServerClassName"
	
	#define TDSMethodParametersColumns_ServerMethodName u"MethodName"
	
	#define TDSMethodParametersColumns_ParameterName u"Name"
	
	#define TDSMethodParametersColumns_ParameterTypeName u"ParameterTypeName"
	
	#define TDSMethodParametersColumns_ParameterTypeUnit u"ParameterTypeUnit"
	
	#define TDSMethodParametersColumns_ParameterDirection u"ParameterDirection"
	
	#define TDSMethodParametersColumns_DbxDataType u"DBXType"
	
	#define TDSMethodParametersColumns_DbxSubDataType u"DBXSubType"
	
	#define TDSMethodParametersColumns_DbxParameterDirection u"DBXParameterDirection"
	
public:
	/* TObject.Create */ inline __fastcall TDSMethodParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSMethodParametersColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSPackageColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSPackageColumns_PackageName u"PackageName"
	
public:
	/* TObject.Create */ inline __fastcall TDSPackageColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSPackageColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

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
