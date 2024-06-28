// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSAcc.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MsaccHPP
#define Firedac_Phys_MsaccHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>
#include <FireDAC.Phys.ODBCWrapper.hpp>
#include <FireDAC.Phys.ODBCBase.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.MSAcc"

namespace Firedac
{
namespace Phys
{
namespace Msacc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EMSAccessNativeException;
class DELPHICLASS TFDPhysMSAccessDriverLink;
class DELPHICLASS TFDMSAccessService;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EMSAccessNativeException : public Firedac::Phys::Odbcwrapper::EODBCNativeException
{
	typedef Firedac::Phys::Odbcwrapper::EODBCNativeException inherited;
	
public:
	virtual Firedac::Stan::Error::TFDDBError* __fastcall AppendError(Firedac::Phys::Odbcwrapper::TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString AResultMessage, const System::UnicodeString ACommandText, const System::UnicodeString AObject, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex);
public:
	/* EODBCNativeException.Create */ inline __fastcall virtual EMSAccessNativeException(short AStatus, Firedac::Phys::Odbcwrapper::TODBCHandle* AOwner)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AStatus, AOwner) { }
	
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EMSAccessNativeException()/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EMSAccessNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EMSAccessNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EMSAccessNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EMSAccessNativeException(NativeUInt Ident)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EMSAccessNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSAccessNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EMSAccessNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EMSAccessNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EMSAccessNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSAccessNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EMSAccessNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSAccessNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EMSAccessNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDPhysMSAccessDriverLink : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysMSAccessDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysMSAccessDriverLink() { }
	
};


enum DECLSPEC_DENUM TFDMSAccessDBVersion : unsigned int { avDefault, avAccess2, avAccess95, avAccess97, avAccess2000, avAccess2003, avAccess2007 };

class PASCALIMPLEMENTATION TFDMSAccessService : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseService
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseService inherited;
	
	
private:
	enum DECLSPEC_DENUM TAction : unsigned int { aaCompactDB, aaRepairDB, aaCreateDB, aaDropDB };
	
	
private:
	TAction FAction;
	System::UnicodeString FDatabase;
	System::UnicodeString FDestDatabase;
	TFDMSAccessDBVersion FDBVersion;
	System::UnicodeString FSortOrder;
	bool FEncrypted;
	System::UnicodeString FPassword;
	bool FResetPassword;
	TFDPhysMSAccessDriverLink* __fastcall GetDriverLink();
	HIDESBASE void __fastcall SetDriverLink(TFDPhysMSAccessDriverLink* const AValue);
	
protected:
	virtual void __fastcall InternalExecute();
	
public:
	void __fastcall CreateDB();
	void __fastcall Drop();
	void __fastcall Repair();
	void __fastcall Compact();
	
__published:
	__property TFDPhysMSAccessDriverLink* DriverLink = {read=GetDriverLink, write=SetDriverLink};
	__property System::UnicodeString Database = {read=FDatabase, write=FDatabase};
	__property System::UnicodeString DestDatabase = {read=FDestDatabase, write=FDestDatabase};
	__property System::UnicodeString SortOrder = {read=FSortOrder, write=FSortOrder};
	__property TFDMSAccessDBVersion DBVersion = {read=FDBVersion, write=FDBVersion, default=0};
	__property bool Encrypted = {read=FEncrypted, write=FEncrypted, default=0};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property bool ResetPassword = {read=FResetPassword, write=FResetPassword, default=0};
public:
	/* TFDPhysDriverService.Destroy */ inline __fastcall virtual ~TFDMSAccessService() { }
	
public:
	/* TComponent.Create */ inline __fastcall virtual TFDMSAccessService(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseService(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Msacc */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSACC)
using namespace Firedac::Phys::Msacc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_MsaccHPP
