// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBUtils.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbutilsHPP
#define Ibx_IbutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBTimer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBProtocols : unsigned char { ibTCP, ibNamedPipe, ibSPX, ibLocal };

enum DECLSPEC_DENUM TIBProtocol : unsigned char { TCP, SPX, NamedPipe, Local };

class PASCALIMPLEMENTATION TIBTimer : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	unsigned FInterval;
	System::Classes::TNotifyEvent FOnTimer;
	bool FEnabled;
	void __fastcall UpdateTimer();
	void __fastcall SetEnabled(bool Value);
	void __fastcall SetInterval(unsigned Value);
	void __fastcall SetOnTimer(System::Classes::TNotifyEvent Value);
	
protected:
	DYNAMIC void __fastcall Timer();
	
public:
	__fastcall virtual TIBTimer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBTimer();
	
__published:
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property unsigned Interval = {read=FInterval, write=SetInterval, default=1000};
	__property System::Classes::TNotifyEvent OnTimer = {read=FOnTimer, write=SetOnTimer};
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool CopyMasterFieldToDetail;
extern DELPHI_PACKAGE System::UnicodeString __fastcall PreprocessSQL(System::UnicodeString sSQL);
extern DELPHI_PACKAGE System::UnicodeString __fastcall RandomString(int iLength);
extern DELPHI_PACKAGE int __fastcall RandomInteger(int iLow, int iHigh);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StripString(System::UnicodeString st, System::UnicodeString CharsToStrip);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FormatIdentifier(int Dialect, System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FormatIdentifierValue(int Dialect, System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ExtractIdentifier(int Dialect, System::UnicodeString Value);
extern DELPHI_PACKAGE System::UnicodeString __fastcall QuoteIdentifier(int Dialect, System::UnicodeString Value);
extern DELPHI_PACKAGE void __fastcall SplitToRelCol(int Dialect, System::UnicodeString AnOrigin, System::UnicodeString &Relation, System::UnicodeString &Column);
extern DELPHI_PACKAGE System::UnicodeString __fastcall AddIBParamSQLForDetail(Data::Db::TParams* Params, System::UnicodeString SQL, bool Native, int Dialect);
extern DELPHI_PACKAGE void __fastcall DecomposeDatabaseName _DEPRECATED_ATTRIBUTE1("use either the SSL version or the TProtocol version") (System::UnicodeString DatabaseName, System::UnicodeString &ServerName, System::UnicodeString &Protocol, System::UnicodeString &DatabasePath)/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall ComposeDatabaseName(System::UnicodeString ServerName, System::UnicodeString Port, TIBProtocol Protocol, System::UnicodeString DatabasePath, bool SSL = false, System::UnicodeString ServerPublicFile = System::UnicodeString(), System::UnicodeString ServerPublicPath = System::UnicodeString(), System::UnicodeString ClientCertFile = System::UnicodeString(), System::UnicodeString ClientPassPhraseFile = System::UnicodeString(), System::UnicodeString ClientPassPhrase = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE System::UnicodeString __fastcall ComposeDatabaseName(System::UnicodeString ServerName, System::UnicodeString Port, TIBProtocols Protocol, System::UnicodeString DatabasePath, bool SSL = false, System::UnicodeString ServerPublicFile = System::UnicodeString(), System::UnicodeString ServerPublicPath = System::UnicodeString(), System::UnicodeString ClientCertFile = System::UnicodeString(), System::UnicodeString ClientPassPhraseFile = System::UnicodeString(), System::UnicodeString ClientPassPhrase = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE void __fastcall DecomposeDatabaseName(System::UnicodeString DatabaseName, System::UnicodeString &ServerName, System::UnicodeString &Port, TIBProtocol &Protocol, System::UnicodeString &DatabasePath)/* overload */;
extern DELPHI_PACKAGE void __fastcall DecomposeDatabaseName(System::UnicodeString DatabaseName, System::UnicodeString &ServerName, System::UnicodeString &Port, TIBProtocols &Protocol, System::UnicodeString &DatabasePath)/* overload */;
extern DELPHI_PACKAGE void __fastcall DecomposeDatabaseName(System::UnicodeString DatabaseName, System::UnicodeString &ServerName, System::UnicodeString &Port, TIBProtocol &Protocol, System::UnicodeString &DatabasePath, bool &SSL, System::UnicodeString &ServerPublicFile, System::UnicodeString &ServerPublicPath, System::UnicodeString &ClientCertFile, System::UnicodeString &ClientPassPhraseFile, System::UnicodeString &ClientPassPhrase)/* overload */;
extern DELPHI_PACKAGE void __fastcall DecomposeDatabaseName(System::UnicodeString DatabaseName, System::UnicodeString &ServerName, System::UnicodeString &Port, TIBProtocols &Protocol, System::UnicodeString &DatabasePath, bool &SSL, System::UnicodeString &ServerPublicFile, System::UnicodeString &ServerPublicPath, System::UnicodeString &ClientCertFile, System::UnicodeString &ClientPassPhraseFile, System::UnicodeString &ClientPassPhrase)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsKeyword(const System::UnicodeString str);
extern DELPHI_PACKAGE bool __fastcall IsDataType(const System::UnicodeString str);
extern DELPHI_PACKAGE bool __fastcall IsIBfunction(const System::UnicodeString str);
extern DELPHI_PACKAGE bool __fastcall NeedsQuoting(const System::UnicodeString Keyword);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetKeywords(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetIBFunctions(void);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetIBDataTypes(void);
extern DELPHI_PACKAGE bool __fastcall IsMinimumServerVersion(System::UnicodeString CurVersion, System::UnicodeString MinVersion);
}	/* namespace Ibutils */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBUTILS)
using namespace Ibx::Ibutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbutilsHPP
