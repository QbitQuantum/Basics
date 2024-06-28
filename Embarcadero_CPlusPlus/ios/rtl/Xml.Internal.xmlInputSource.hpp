// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.XmlInputSource.pas' rev: 34.00 (iOS)

#ifndef Xml_Internal_XmlinputsourceHPP
#define Xml_Internal_XmlinputsourceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Xml.Internal.CodecUtilsWin32.hpp>
#include <Xml.Internal.XmlRulesUtils.hpp>
#include <Xml.Internal.ParserUtilsWin32.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Xmlinputsource
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EDomException;
class DELPHICLASS ENot_Supported_Err;
class DELPHICLASS TXmlInputSource;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EDomException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EDomException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EDomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EDomException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EDomException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EDomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EDomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EDomException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EDomException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDomException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EDomException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDomException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EDomException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EDomException() { }
	
};


class PASCALIMPLEMENTATION ENot_Supported_Err : public EDomException
{
	typedef EDomException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg) : EDomException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EDomException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Supported_Err(NativeUInt Ident)/* overload */ : EDomException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec)/* overload */ : EDomException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EDomException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, int AHelpContext) : EDomException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENot_Supported_Err(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EDomException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, int AHelpContext)/* overload */ : EDomException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EDomException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Supported_Err(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENot_Supported_Err(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EDomException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENot_Supported_Err() { }
	
};


enum DECLSPEC_DENUM TDomXMLDeclType : unsigned char { DT_XML_DECLARATION, DT_TEXT_DECLARATION, DT_XML_OR_TEXT_DECLARATION, DT_UNSPECIFIED };

enum DECLSPEC_DENUM TDomStandalone : unsigned char { STANDALONE_YES, STANDALONE_NO, STANDALONE_UNSPECIFIED };

class PASCALIMPLEMENTATION TXmlInputSource : public Xml::Internal::Parserutilswin32::TUtilsUCS4Reader
{
	typedef Xml::Internal::Parserutilswin32::TUtilsUCS4Reader inherited;
	
private:
	TDomXMLDeclType FDeclType;
	bool FHasMalformedDecl;
	System::UnicodeString FXmlEncoding;
	TDomStandalone FXmlStandalone;
	System::UnicodeString FXmlVersion;
	void __fastcall CheckEncoding(const System::UnicodeString Encoding);
	bool __fastcall EvaluateXmlOrTextDecl(/* out */ TDomXMLDeclType &DeclType, /* out */ System::UnicodeString &Version, /* out */ System::UnicodeString &EncName, /* out */ TDomStandalone &Standalone);
	
protected:
	__fastcall TXmlInputSource(System::Classes::TStream* const Stream, const int ABufSize, const System::UnicodeString AEncoding, const bool InclDecl, const __int64 InitialByteCount, const __int64 InitialCharCount, const __int64 InitialCharsInLine, const __int64 InitialTabsInLine, const __int64 InitialLine);
	
public:
	__classmethod void __fastcall GetXMLProlog(System::Classes::TStream* const Stream, /* out */ System::UnicodeString &Encoding, /* out */ TDomStandalone &Standalone, /* out */ System::UnicodeString &Version);
public:
	/* TUtilsUCS4Reader.Destroy */ inline __fastcall virtual ~TXmlInputSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Xmlinputsource */
}	/* namespace Internal */
}	/* namespace Xml */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_XmlinputsourceHPP
