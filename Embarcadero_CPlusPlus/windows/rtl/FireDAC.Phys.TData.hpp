﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.TData.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_TdataHPP
#define Firedac_Phys_TdataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>
#include <FireDAC.Phys.ODBCWrapper.hpp>
#include <FireDAC.Phys.ODBCBase.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.TData"

namespace Firedac
{
namespace Phys
{
namespace Tdata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ETDataNativeException;
class DELPHICLASS TFDPhysTDataDriverLink;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ETDataNativeException : public Firedac::Phys::Odbcwrapper::EODBCNativeException
{
	typedef Firedac::Phys::Odbcwrapper::EODBCNativeException inherited;
	
public:
	virtual Firedac::Stan::Error::TFDDBError* __fastcall AppendError(Firedac::Phys::Odbcwrapper::TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString AResultMessage, const System::UnicodeString ACommandText, const System::UnicodeString AObject, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex);
public:
	/* EODBCNativeException.Create */ inline __fastcall virtual ETDataNativeException(short AStatus, Firedac::Phys::Odbcwrapper::TODBCHandle* AOwner)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AStatus, AOwner) { }
	
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual ETDataNativeException()/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException() { }
	/* EFDDBEngineException.Create */ inline __fastcall ETDataNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~ETDataNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall ETDataNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETDataNativeException(NativeUInt Ident)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETDataNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETDataNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETDataNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETDataNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETDataNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETDataNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETDataNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETDataNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETDataNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFDPhysTDataDriverLink : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysTDataDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysTDataDriverLink() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Tdata */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_TDATA)
using namespace Firedac::Phys::Tdata;
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
#endif	// Firedac_Phys_TdataHPP
