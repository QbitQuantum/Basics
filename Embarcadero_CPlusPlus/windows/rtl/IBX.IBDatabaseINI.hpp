// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBDatabaseINI.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbdatabaseiniHPP
#define Ibx_IbdatabaseiniHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibdatabaseini
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBDatabaseINI;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIniFilePathOpt : unsigned char { ipoPathNone, ipoPathToServer, ipoPathRelative };

class PASCALIMPLEMENTATION TIBDatabaseINI : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FDatabaseName;
	Ibx::Ibdatabase::TIBDatabase* FDatabase;
	System::UnicodeString FPassword;
	System::UnicodeString FUsername;
	System::UnicodeString FFileName;
	System::UnicodeString FSQLRole;
	TIniFilePathOpt FAppPath;
	System::UnicodeString FSection;
	System::UnicodeString FCharacterSet;
	void __fastcall SetDatabaseName(const System::UnicodeString Value);
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetFileName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUsername(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetParam(System::UnicodeString Name);
	void __fastcall AssignParam(System::UnicodeString Name, System::UnicodeString Value);
	void __fastcall DeleteParam(System::UnicodeString Name);
	void __fastcall SetSQLRole(const System::UnicodeString Value);
	void __fastcall SetSection(const System::UnicodeString Value);
	void __fastcall SetCharacterSet(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TIBDatabaseINI(System::Classes::TComponent* AOwner);
	void __fastcall SaveToINI();
	void __fastcall ReadFromINI();
	void __fastcall WriteToDatabase(Ibx::Ibdatabase::TIBDatabase* ADatabase)/* overload */;
	void __fastcall WriteToDatabase()/* overload */;
	void __fastcall ReadFromDatabase();
	System::UnicodeString __fastcall IniFileName();
	
__published:
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=FDatabase, write=SetDatabase};
	__property System::UnicodeString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property System::UnicodeString Username = {read=FUsername, write=SetUsername};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property System::UnicodeString SQLRole = {read=FSQLRole, write=SetSQLRole};
	__property System::UnicodeString CharacterSet = {read=FCharacterSet, write=SetCharacterSet};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
	__property TIniFilePathOpt UseAppPath = {read=FAppPath, write=FAppPath, nodefault};
	__property System::UnicodeString Section = {read=FSection, write=SetSection};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIBDatabaseINI() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall LocalServerPath(System::UnicodeString sFile = System::UnicodeString());
extern DELPHI_PACKAGE System::UnicodeString __fastcall SlashPath(System::UnicodeString sPath);
}	/* namespace Ibdatabaseini */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBDATABASEINI)
using namespace Ibx::Ibdatabaseini;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbdatabaseiniHPP
