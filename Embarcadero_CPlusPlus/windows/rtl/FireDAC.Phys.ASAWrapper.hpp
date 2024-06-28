// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ASAWrapper.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_AsawrapperHPP
#define Firedac_Phys_AsawrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
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
class DELPHICLASS TASATool;
class DELPHICLASS TASABackup;
class DELPHICLASS TASAValidate;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
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

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

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


enum DECLSPEC_DENUM TASAToolMessageKind : unsigned int { tmMessage, tmError, tmStatus, tmConfirm };

typedef void __fastcall (__closure *TASAToolMessageEvent)(System::TObject* ASender, System::UnicodeString AMessage, TASAToolMessageKind AKind, int &AResult);

class PASCALIMPLEMENTATION TASATool : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TASAToolLib* FLib;
	System::TObject* FOwningObj;
	Firedac::Phys::Asacli::a_dbtools_info FToolInfo;
	Firedac::Stan::Util::TFDMethodThunk* FErrorThunk;
	TASAToolMessageEvent FOnMessage;
	System::UnicodeString FError;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	int __fastcall GetVersion();
	
protected:
	void __fastcall Check(System::Int8 ACode);
	void __fastcall Init();
	void __fastcall Fini();
	System::Int8 __fastcall DoMessage(Firedac::Phys::Asacli::Pa_char str, TASAToolMessageKind AKind);
	System::Int8 __stdcall DoMessageCallback(Firedac::Phys::Asacli::Pa_char str);
	System::Int8 __stdcall DoConfirmCallback(Firedac::Phys::Asacli::Pa_char str);
	System::Int8 __stdcall DoErrorCallback(Firedac::Phys::Asacli::Pa_char str);
	System::Int8 __stdcall DoStatusCallback(Firedac::Phys::Asacli::Pa_char str);
	Firedac::Phys::Asacli::P_name __fastcall Strings2P_name(System::Classes::TStrings* AStrs);
	void __fastcall DeleteP_name(Firedac::Phys::Asacli::P_name APtr);
	
public:
	__fastcall TASATool(TASAToolLib* ALib, System::TObject* AOwningObj);
	__fastcall virtual ~TASATool();
	__property int Version = {read=GetVersion, nodefault};
	__property TASAToolMessageEvent OnMessage = {read=FOnMessage, write=FOnMessage};
};


enum DECLSPEC_DENUM TASABackupCheckpointLogType : unsigned int { bclCopy, bclNoCopy, bclRecover, bclAuto, bclDefault };

enum DECLSPEC_DENUM Firedac_Phys_Asawrapper__4 : unsigned int { bfBackupDB, bfBackupLog, bfNoConfirm, bfQuiet, bfRenameLog, bfTruncateLog, bfRenameLocalLog, bfServerBackup, bfProgressMessages };

typedef System::Set<Firedac_Phys_Asawrapper__4, Firedac_Phys_Asawrapper__4::bfBackupDB, Firedac_Phys_Asawrapper__4::bfProgressMessages> TASABackupFlags;

class PASCALIMPLEMENTATION TASABackup : public TASATool
{
	typedef TASATool inherited;
	
private:
	System::UnicodeString FConnectParams;
	TASABackupCheckpointLogType FCheckpointLogType;
	unsigned FPageBlocksize;
	System::UnicodeString FHotlogFilename;
	System::UnicodeString FOutputDir;
	TASABackupFlags FFlags;
	System::UnicodeString FStartLine;
	
public:
	void __fastcall Backup();
	__property System::UnicodeString ConnectParams = {read=FConnectParams, write=FConnectParams};
	__property System::UnicodeString StartLine = {read=FStartLine, write=FStartLine};
	__property System::UnicodeString OutputDir = {read=FOutputDir, write=FOutputDir};
	__property System::UnicodeString HotlogFilename = {read=FHotlogFilename, write=FHotlogFilename};
	__property TASABackupCheckpointLogType CheckpointLogType = {read=FCheckpointLogType, write=FCheckpointLogType, nodefault};
	__property unsigned PageBlocksize = {read=FPageBlocksize, write=FPageBlocksize, nodefault};
	__property TASABackupFlags Flags = {read=FFlags, write=FFlags, nodefault};
public:
	/* TASATool.Create */ inline __fastcall TASABackup(TASAToolLib* ALib, System::TObject* AOwningObj) : TASATool(ALib, AOwningObj) { }
	/* TASATool.Destroy */ inline __fastcall virtual ~TASABackup() { }
	
};


enum DECLSPEC_DENUM TASAValidateType : unsigned int { vtNormal, vtData, vtIndex, vtExpress, vtFull, vtChecksum, vtDatabase, vtComplete };

enum DECLSPEC_DENUM Firedac_Phys_Asawrapper__6 : unsigned int { vfQuiet, vfIndex };

typedef System::Set<Firedac_Phys_Asawrapper__6, Firedac_Phys_Asawrapper__6::vfQuiet, Firedac_Phys_Asawrapper__6::vfIndex> TASAValidateFlags;

class PASCALIMPLEMENTATION TASAValidate : public TASATool
{
	typedef TASATool inherited;
	
private:
	TASAValidateType FValidateType;
	System::UnicodeString FConnectParams;
	System::UnicodeString FStartLine;
	System::Classes::TStrings* FTables;
	TASAValidateFlags FFlags;
	void __fastcall SetTables(System::Classes::TStrings* const AValue);
	
public:
	__fastcall TASAValidate(TASAToolLib* ALib, System::TObject* AOwningObj);
	__fastcall virtual ~TASAValidate();
	void __fastcall Validate();
	__property System::UnicodeString ConnectParams = {read=FConnectParams, write=FConnectParams};
	__property System::UnicodeString StartLine = {read=FStartLine, write=FStartLine};
	__property System::Classes::TStrings* Tables = {read=FTables, write=SetTables};
	__property TASAValidateFlags Flags = {read=FFlags, write=FFlags, nodefault};
	__property TASAValidateType ValidateType = {read=FValidateType, write=FValidateType, nodefault};
};


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
