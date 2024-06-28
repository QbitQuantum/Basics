// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxHTTPLayer.pas' rev: 34.00 (Windows)

#ifndef Data_DbxhttplayerHPP
#define Data_DbxhttplayerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxHTTPLayer"

namespace Data
{
namespace Dbxhttplayer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EHTTPProtocolException;
class DELPHICLASS TDBXHTTPLayer;
class DELPHICLASS TDBXHTTPSLayer;
class DELPHICLASS TDSHTTPClient;
class DELPHICLASS TDSHTTPResponseStream;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EHTTPProtocolException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	System::UnicodeString FErrorMessage;
	int FErrorCode;
	
public:
	__fastcall EHTTPProtocolException(int AErrorCode, const System::UnicodeString AErrorMessage, const System::UnicodeString AMessage);
	__property int ErrorCode = {read=FErrorCode, nodefault};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage};
public:
	/* Exception.CreateFmt */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPProtocolException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHTTPProtocolException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDBXHTTPLayer : public Data::Dbxcommon::TDBXCommunicationLayer
{
	typedef Data::Dbxcommon::TDBXCommunicationLayer inherited;
	
protected:
	System::UnicodeString FURITunnel;
	System::UnicodeString FSessionId;
	TDSHTTPClient* Fhttp;
	System::UnicodeString FIPImplementationID;
	virtual void __fastcall InitHTTPClient();
	virtual System::UnicodeString __fastcall HTTPProtocol();
	
public:
	__fastcall virtual TDBXHTTPLayer();
	__fastcall virtual ~TDBXHTTPLayer();
	virtual void __fastcall Close();
	virtual void __fastcall Open(Data::Dbxcommon::TDBXProperties* const DBXProperties);
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall Info();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDBXHTTPSLayer : public TDBXHTTPLayer
{
	typedef TDBXHTTPLayer inherited;
	
protected:
	virtual void __fastcall InitHTTPClient();
	virtual System::UnicodeString __fastcall HTTPProtocol();
	
public:
	virtual void __fastcall Open(Data::Dbxcommon::TDBXProperties* const DBXProperties);
public:
	/* TDBXHTTPLayer.Create */ inline __fastcall virtual TDBXHTTPSLayer() : TDBXHTTPLayer() { }
	/* TDBXHTTPLayer.Destroy */ inline __fastcall virtual ~TDBXHTTPSLayer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPClient : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual int __fastcall GetResponseCode() = 0 ;
	virtual System::UnicodeString __fastcall GetResponseText() = 0 ;
	
public:
	virtual System::UnicodeString __fastcall Post(System::UnicodeString AURL, System::Classes::TStrings* ASource) = 0 ;
	virtual System::UnicodeString __fastcall Put(System::UnicodeString AURL, System::Classes::TStream* ASource) = 0 ;
	virtual TDSHTTPResponseStream* __fastcall Get(System::UnicodeString AURL) = 0 ;
	virtual void __fastcall SetConnectTimeout(int AMilisec);
	virtual void __fastcall SetReadTimeout(int AMilisec);
	virtual void __fastcall SetBasicAuthentication(const System::UnicodeString user, const System::UnicodeString password) = 0 ;
	__property int ResponseCode = {read=GetResponseCode, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText};
public:
	/* TObject.Create */ inline __fastcall TDSHTTPClient() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPClient() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPResponseStream : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual __int64 __fastcall GetContentLength() = 0 ;
	
public:
#ifndef _WIN64
	virtual int __fastcall Read(System::DynamicArray<System::Byte> Buffer, int Count) = 0 ;
#else /* _WIN64 */
	virtual int __fastcall Read(System::TArray__1<System::Byte> Buffer, int Count) = 0 ;
#endif /* _WIN64 */
	virtual void __fastcall Close() = 0 ;
	__property __int64 ContentLength = {read=GetContentLength};
public:
	/* TObject.Create */ inline __fastcall TDSHTTPResponseStream() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPResponseStream() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxhttplayer */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXHTTPLAYER)
using namespace Data::Dbxhttplayer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxhttplayerHPP
