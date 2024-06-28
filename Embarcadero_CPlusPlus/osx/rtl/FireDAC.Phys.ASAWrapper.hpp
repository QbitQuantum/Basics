// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ASAWrapper.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_AsawrapperHPP
#define Firedac_Phys_AsawrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Phys.ODBCCli.hpp>
#include <FireDAC.Phys.ODBCWrapper.hpp>
#include <FireDAC.Phys.ASACli.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Asawrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EASANativeException;
class DELPHICLASS TASAToolLib;
//-- type declarations -------------------------------------------------------
#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION EASANativeException : public Firedac::Phys::Odbcwrapper::EODBCNativeException
{
	typedef Firedac::Phys::Odbcwrapper::EODBCNativeException inherited;
	
public:
	virtual Firedac::Stan::Error::TFDDBError* __fastcall AppendError(Firedac::Phys::Odbcwrapper::TODBCHandle* AHandle, short ARecNum, const System::UnicodeString ASQLState, int ANativeError, const System::UnicodeString ADiagMessage, const System::UnicodeString AResultMessage, const System::UnicodeString ACommandText, const System::UnicodeString AObject, Firedac::Stan::Error::TFDCommandExceptionKind AKind, int ACmdOffset, int ARowIndex);
public:
	/* EODBCNativeException.Create */ inline __fastcall virtual EASANativeException(short AStatus, Firedac::Phys::Odbcwrapper::TODBCHandle* AOwner)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AStatus, AOwner) { }
	
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual EASANativeException()/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException() { }
	/* EFDDBEngineException.Create */ inline __fastcall EASANativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~EASANativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EASANativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EASANativeException(NativeUInt Ident)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EASANativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EASANativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EASANativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EASANativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EASANativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Phys::Odbcwrapper::EODBCNativeException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EASANativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EASANativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EASANativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EASANativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Phys::Odbcwrapper::EODBCNativeException(Ident, Args, Args_High, AHelpContext) { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TASAToolLib : public Firedac::Stan::Util::TFDLibrary
{
	typedef Firedac::Stan::Util::TFDLibrary inherited;
	
protected:
	virtual void __fastcall LoadEntries();
	
public:
	Firedac::Phys::Asacli::TDBToolsInit DBToolsInit;
	Firedac::Phys::Asacli::TDBToolsFini DBToolsFini;
	Firedac::Phys::Asacli::TDBToolsVersion DBToolsVersion;
	Firedac::Phys::Asacli::TDBBackup DBBackup;
	Firedac::Phys::Asacli::TDBValidate DBValidate;
	__fastcall TASAToolLib(System::TObject* AOwningObj);
	HIDESBASE void __fastcall Load(const System::UnicodeString AToolHome, const System::UnicodeString AToolLib);
public:
	/* TFDLibrary.Destroy */ inline __fastcall virtual ~TASAToolLib() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString C_ASABinFolder;
}	/* namespace Asawrapper */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ASAWRAPPER)
using namespace Firedac::Phys::Asawrapper;
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
#endif	// Firedac_Phys_AsawrapperHPP
