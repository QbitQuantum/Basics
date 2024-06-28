// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DB2.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_Db2HPP
#define Firedac_Phys_Db2HPP

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
#ifndef _WIN64
#pragma link "FireDAC.Phys.DB2.obj"
#else /* _WIN64 */
#pragma link "FireDAC.Phys.DB2.o"
#endif /* _WIN64 */

namespace Firedac
{
namespace Phys
{
namespace Db2
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDB2NativeException;
class DELPHICLASS TFDPhysDB2DriverLink;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EDB2NativeException : public Firedac::Phys::Odbcwrapper::EODBCNativeException
{
	typedef Firedac::Phys::Odbcwrapper::EODBCNativeException inherited;
	
public:
	virtual Firedac::Stan::Error::TFDDBError* __fastcall AppendError(Firedac::Phys::Odbcwrapper::TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString AResultMessage, const System::UnicodeString ACommandText, const System::UnicodeString AObject, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex);
public:
	/* EODBCNativeException.Create */ inline __fastcall virtual EDB2NativeException(short AStatus, Firedac::Phys::Odbcwrapper::TODBCHandle* AOwner)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AStatus, AOwner) { }
	
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EDB2NativeException()/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EDB2NativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EDB2NativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EDB2NativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDB2NativeException(NativeUInt Ident)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDB2NativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDB2NativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDB2NativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDB2NativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDB2NativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDB2NativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDB2NativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDB2NativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDB2NativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDPhysDB2DriverLink : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysDB2DriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysDB2DriverLink() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Db2 */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DB2)
using namespace Firedac::Phys::Db2;
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
#endif	// Firedac_Phys_Db2HPP
