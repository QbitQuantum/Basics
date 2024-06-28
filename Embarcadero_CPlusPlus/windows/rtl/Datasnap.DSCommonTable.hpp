// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSCommonTable.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DscommontableHPP
#define Datasnap_DscommontableHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dscommontable
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClassEntity;
class DELPHICLASS TDSConnectionEntity;
class DELPHICLASS TDSMethodEntity;
class DELPHICLASS TDSPackageEntity;
class DELPHICLASS TDSProcedureEntity;
class DELPHICLASS TDSProcedureParametersEntity;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSClassEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSClassEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSClassEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString PackageName);
	System::UnicodeString __fastcall GetServerClassName();
	void __fastcall SetServerClassName(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetRoleName();
	void __fastcall SetRoleName(const System::UnicodeString RoleName);
	System::UnicodeString __fastcall GetLifeCycle();
	void __fastcall SetLifeCycle(const System::UnicodeString LifeCycle);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateClassTable();
	
public:
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
	__property System::UnicodeString ServerClassName = {read=GetServerClassName, write=SetServerClassName};
	__property System::UnicodeString RoleName = {read=GetRoleName, write=SetRoleName};
	__property System::UnicodeString LifeCycle = {read=GetLifeCycle, write=SetLifeCycle};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSClassEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSConnectionEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSConnectionEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSConnectionEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetConnectionName();
	void __fastcall SetConnectionName(const System::UnicodeString ConnectionName);
	System::UnicodeString __fastcall GetConnectionProperties();
	void __fastcall SetConnectionProperties(const System::UnicodeString ConnectionProperties);
	System::UnicodeString __fastcall GetDriverName();
	void __fastcall SetDriverName(const System::UnicodeString DriverName);
	System::UnicodeString __fastcall GetDriverProperties();
	void __fastcall SetDriverProperties(const System::UnicodeString DriverProperties);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateClassTable();
	
public:
	__property System::UnicodeString ConnectionName = {read=GetConnectionName, write=SetConnectionName};
	__property System::UnicodeString ConnectionProperties = {read=GetConnectionProperties, write=SetConnectionProperties};
	__property System::UnicodeString DriverName = {read=GetDriverName, write=SetDriverName};
	__property System::UnicodeString DriverProperties = {read=GetDriverProperties, write=SetDriverProperties};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSConnectionEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSMethodEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSMethodEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSMethodEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetMethodAlias();
	void __fastcall SetMethodAlias(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetServerClassName();
	void __fastcall SetServerClassName(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetServerMethodName();
	void __fastcall SetServerMethodName(const System::UnicodeString ClassName);
	System::UnicodeString __fastcall GetRoleName();
	void __fastcall SetRoleName(const System::UnicodeString ClassName);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateMethodTable();
	
public:
	__property System::UnicodeString MethodAlias = {read=GetMethodAlias, write=SetMethodAlias};
	__property System::UnicodeString ServerClassName = {read=GetServerClassName, write=SetServerClassName};
	__property System::UnicodeString ServerMethodName = {read=GetServerMethodName, write=SetServerMethodName};
	__property System::UnicodeString RoleName = {read=GetRoleName, write=SetRoleName};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSMethodEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSPackageEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSPackageEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSPackageEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString PackageName);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreatePackageTable();
	
public:
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSPackageEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSProcedureEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSProcedureEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSProcedureEntity(const bool OwnTable)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString CatalogName);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString SchemaName);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString ProcedureName);
	System::UnicodeString __fastcall GetProcedureType();
	void __fastcall SetProcedureType(const System::UnicodeString ClassName);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateProcedureTable();
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ProcedureType = {read=GetProcedureType, write=SetProcedureType};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSProcedureEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSProcedureParametersEntity : public Data::Dbxcommontable::TDBXTableEntity
{
	typedef Data::Dbxcommontable::TDBXTableEntity inherited;
	
public:
	__fastcall TDSProcedureParametersEntity(Data::Dbxcommontable::TDBXTable* const Table, const bool OwnTable)/* overload */;
	__fastcall TDSProcedureParametersEntity(const bool OwnTable)/* overload */;
	bool __fastcall IsNullable();
	bool __fastcall GetUnsigned();
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString CatalogName);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString SchemaName);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProceduredName(const System::UnicodeString ProcedureName);
	System::UnicodeString __fastcall GetParameterName();
	void __fastcall SetParameterName(const System::UnicodeString ParameterName);
	System::UnicodeString __fastcall GetParameterMode();
	void __fastcall SetParameterMode(const System::UnicodeString ParameterMode);
	System::UnicodeString __fastcall GetTypeName();
	void __fastcall SetTypeName(const System::UnicodeString TypeName);
	int __fastcall GetPrecision();
	void __fastcall SetPrecision(const int Precision);
	int __fastcall GetScale();
	void __fastcall SetScale(const int Scale);
	int __fastcall GetOrdinal();
	void __fastcall SetOrdinal(const int Ordinal);
	void __fastcall SetNullable(const bool Nullable);
	int __fastcall GetDBXDataType();
	void __fastcall SetDBXDataType(const int DataType);
	bool __fastcall IsFixedLength();
	void __fastcall SetFixedLength(const bool FixedLength);
	bool __fastcall IsUnicode();
	void __fastcall SetUnicode(const bool IsUnicode);
	bool __fastcall IsLong();
	void __fastcall SetLong(const bool IsLong);
	void __fastcall SetUnsigned(const bool IsUnsigned);
	
private:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateProcedureParmetersTable();
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName};
	__property System::UnicodeString ProceduredName = {write=SetProceduredName};
	__property System::UnicodeString ParameterName = {read=GetParameterName, write=SetParameterName};
	__property System::UnicodeString ParameterMode = {read=GetParameterMode, write=SetParameterMode};
	__property System::UnicodeString TypeName = {read=GetTypeName, write=SetTypeName};
	__property int Precision = {read=GetPrecision, write=SetPrecision, nodefault};
	__property int Scale = {read=GetScale, write=SetScale, nodefault};
	__property int Ordinal = {read=GetOrdinal, write=SetOrdinal, nodefault};
	__property bool Nullable = {write=SetNullable, nodefault};
	__property int DBXDataType = {read=GetDBXDataType, write=SetDBXDataType, nodefault};
	__property bool FixedLength = {read=IsFixedLength, write=SetFixedLength, nodefault};
	__property bool Unicode = {read=IsUnicode, write=SetUnicode, nodefault};
	__property bool Long = {read=IsLong, write=SetLong, nodefault};
	__property bool Unsigned = {write=SetUnsigned, nodefault};
public:
	/* TDBXTableEntity.Destroy */ inline __fastcall virtual ~TDSProcedureParametersEntity() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dscommontable */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCOMMONTABLE)
using namespace Datasnap::Dscommontable;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DscommontableHPP
