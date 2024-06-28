// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBConnAdmin.pas' rev: 34.00 (iOS)

#ifndef Data_DbconnadminHPP
#define Data_DbconnadminHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbconnadmin
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IConnectionAdmin;
typedef System::DelphiInterface<IConnectionAdmin> _di_IConnectionAdmin;
class DELPHICLASS TConnectionAdmin;
//-- type declarations -------------------------------------------------------
__interface IConnectionAdmin  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetDisplayDriverName(const System::UnicodeString DriverName) = 0 ;
	virtual int __fastcall GetDisplayDriverNames(System::Classes::TStrings* List) = 0 ;
	virtual int __fastcall GetDriverNames(System::Classes::TStrings* List) = 0 ;
	virtual int __fastcall GetDelegateDriverNames(System::Classes::TStrings* List) = 0 ;
	virtual int __fastcall GetDriverParams(const System::UnicodeString DriverName, System::Classes::TStrings* Params) = 0 ;
	virtual void __fastcall GetDriverLibNames(const System::UnicodeString DriverName, System::UnicodeString &LibraryName, System::UnicodeString &VendorLibrary) = 0 ;
	virtual int __fastcall GetConnectionNames(System::Classes::TStrings* List, System::UnicodeString DriverName) = 0 ;
	virtual int __fastcall GetConnectionParams(const System::UnicodeString ConnectionName, System::Classes::TStrings* Params) = 0 ;
	virtual void __fastcall AddConnection(const System::UnicodeString ConnectionName, const System::UnicodeString DriverName) = 0 ;
	virtual void __fastcall DeleteConnection(const System::UnicodeString ConnectionName) = 0 ;
	virtual void __fastcall ModifyConnection(const System::UnicodeString ConnectionName, System::Classes::TStrings* Params) = 0 ;
	virtual void __fastcall RenameConnection(const System::UnicodeString OldName, const System::UnicodeString NewName) = 0 ;
	virtual void __fastcall RegisterDriver(const System::UnicodeString DriverName) = 0 ;
	virtual void __fastcall UnregisterDriver(const System::UnicodeString DriverName) = 0 ;
};

class PASCALIMPLEMENTATION TConnectionAdmin : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Inifiles::TCustomIniFile* FConnectionConfig;
	System::Classes::TStrings* FRegisteredDriverNames;
	void __fastcall CheckConfigFile();
	void __fastcall InitializeDriverNames();
	
protected:
	System::UnicodeString __fastcall GetDisplayDriverName(const System::UnicodeString DriverName);
	int __fastcall GetDisplayDriverNames(System::Classes::TStrings* List);
	int __fastcall GetDriverNames(System::Classes::TStrings* List);
	int __fastcall GetDelegateDriverNames(System::Classes::TStrings* List);
	int __fastcall GetDriverParams(const System::UnicodeString DriverName, System::Classes::TStrings* Params);
	void __fastcall GetDriverLibNames(const System::UnicodeString DriverName, System::UnicodeString &LibraryName, System::UnicodeString &VendorLibrary);
	int __fastcall GetConnectionNames(System::Classes::TStrings* List, System::UnicodeString DriverName);
	int __fastcall GetConnectionParams(const System::UnicodeString ConnectionName, System::Classes::TStrings* Params);
	void __fastcall AddConnection(const System::UnicodeString ConnectionName, const System::UnicodeString DriverName);
	void __fastcall DeleteConnection(const System::UnicodeString ConnectionName);
	void __fastcall ModifyConnection(const System::UnicodeString ConnectionName, System::Classes::TStrings* Params);
	void __fastcall RenameConnection(const System::UnicodeString OldName, const System::UnicodeString NewName);
	void __fastcall RegisterDriver(const System::UnicodeString DriverName);
	void __fastcall UnregisterDriver(const System::UnicodeString DriverName);
	
public:
	__fastcall TConnectionAdmin();
	__fastcall virtual ~TConnectionAdmin();
	__property System::Inifiles::TCustomIniFile* ConnectionConfig = {read=FConnectionConfig};
private:
	void *__IConnectionAdmin;	// IConnectionAdmin 
	
public:
	operator IConnectionAdmin*(void) { return (IConnectionAdmin*)&__IConnectionAdmin; }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE _di_IConnectionAdmin __fastcall GetConnectionAdmin(void);
}	/* namespace Dbconnadmin */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBCONNADMIN)
using namespace Data::Dbconnadmin;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbconnadminHPP
