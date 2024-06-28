// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgePayload.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgepayloadHPP
#define Emshosting_EdgepayloadHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.EdgePayload"

namespace Emshosting
{
namespace Edgepayload
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IEdgeRequest;
typedef System::DelphiInterface<IEdgeRequest> _di_IEdgeRequest;
class DELPHICLASS TEdgeRequest;
__interface DELPHIINTERFACE IEdgeRequestReader;
typedef System::DelphiInterface<IEdgeRequestReader> _di_IEdgeRequestReader;
__interface DELPHIINTERFACE IEdgeResponse;
typedef System::DelphiInterface<IEdgeResponse> _di_IEdgeResponse;
class DELPHICLASS TEdgeResponse;
__interface DELPHIINTERFACE IEdgeResponseWriter;
typedef System::DelphiInterface<IEdgeResponseWriter> _di_IEdgeResponseWriter;
struct TEdgeVersion;
class DELPHICLASS TEdgeReaderWriterFactory;
class DELPHICLASS TEdgeStreamReader;
class DELPHICLASS TEdgeStreamWriter;
class DELPHICLASS EEdgeReadError;
class DELPHICLASS EEdgeReaderWriterFactoryError;
class DELPHICLASS EEdgeReaderVersionError;
//-- type declarations -------------------------------------------------------
typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TStringKeyValue;

#ifndef _WIN64
typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TStringKeyValues;
#else /* _WIN64 */
typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TStringKeyValues;
#endif /* _WIN64 */

__interface  INTERFACE_UUID("{561B2566-0DEA-40B9-9E6D-9588A9102A37}") IEdgeRequest  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetMethod() = 0 ;
	virtual System::UnicodeString __fastcall GetPath() = 0 ;
	virtual System::UnicodeString __fastcall GetSessionToken() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQuery() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQuery() = 0 ;
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetBasePath() = 0 ;
	virtual System::UnicodeString __fastcall GetServerHost() = 0 ;
	virtual System::UnicodeString __fastcall GetTenantId() = 0 ;
	__property System::UnicodeString Method = {read=GetMethod};
	__property System::UnicodeString Path = {read=GetPath};
#ifndef _WIN64
	__property System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Query = {read=GetQuery};
#else /* _WIN64 */
	__property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Query = {read=GetQuery};
#endif /* _WIN64 */
	__property System::UnicodeString SessionToken = {read=GetSessionToken};
	__property System::UnicodeString BasePath = {read=GetBasePath};
	__property System::UnicodeString ServerHost = {read=GetServerHost};
	__property System::UnicodeString TenantId = {read=GetTenantId};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeRequest : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FMethod;
	System::UnicodeString FPath;
	System::UnicodeString FBasePath;
	System::UnicodeString FServerHost;
	System::UnicodeString FSessionToken;
	System::UnicodeString FTenantId;
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > FQuery;
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > FQuery;
#endif /* _WIN64 */
	
protected:
	System::UnicodeString __fastcall GetMethod();
	System::UnicodeString __fastcall GetPath();
	System::UnicodeString __fastcall GetSessionToken();
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQuery();
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetQuery();
#endif /* _WIN64 */
	System::UnicodeString __fastcall GetBasePath();
	System::UnicodeString __fastcall GetServerHost();
	System::UnicodeString __fastcall GetTenantId();
	
public:
#ifndef _WIN64
	__fastcall TEdgeRequest(const System::UnicodeString AMethod, const System::UnicodeString AServerhost, const System::UnicodeString ABasePath, const System::UnicodeString APath, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery, const System::UnicodeString ASessionToken, const System::UnicodeString ATenantId);
#else /* _WIN64 */
	__fastcall TEdgeRequest(const System::UnicodeString AMethod, const System::UnicodeString AServerhost, const System::UnicodeString ABasePath, const System::UnicodeString APath, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AQuery, const System::UnicodeString ASessionToken, const System::UnicodeString ATenantId);
#endif /* _WIN64 */
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEdgeRequest() { }
	
private:
	void *__IEdgeRequest;	// IEdgeRequest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {561B2566-0DEA-40B9-9E6D-9588A9102A37}
	operator _di_IEdgeRequest()
	{
		_di_IEdgeRequest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IEdgeRequest*(void) { return (IEdgeRequest*)&__IEdgeRequest; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{FDC7D9B1-DCE8-4D97-98B7-3CBB5E9B9636}") IEdgeRequestReader  : public System::IInterface 
{
	virtual _di_IEdgeRequest __fastcall ReadRequest() = 0 ;
	virtual bool __fastcall ReadContentType(/* out */ System::UnicodeString &AContentType, /* out */ int &AContentLength) = 0 ;
	virtual void __fastcall ReadContent(const int ALength, /* out */ System::UnicodeString &ABody) = 0 /* overload */;
#ifndef _WIN64
	virtual void __fastcall ReadContent(const int ALength, /* out */ System::DynamicArray<System::Byte> &ABytes) = 0 /* overload */;
#else /* _WIN64 */
	virtual void __fastcall ReadContent(const int ALength, /* out */ System::TArray__1<System::Byte> &ABytes) = 0 /* overload */;
#endif /* _WIN64 */
	virtual void __fastcall ReadContent(const __int64 ALength, System::Classes::TStream* const AStream) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{7DDF5C07-A4DD-481A-99C8-4AAB309C9E57}") IEdgeResponse  : public System::IInterface 
{
	virtual System::Word __fastcall GetStatusCode() = 0 ;
	virtual System::UnicodeString __fastcall GetStatusText() = 0 ;
	__property System::Word StatusCode = {read=GetStatusCode};
	__property System::UnicodeString StatusText = {read=GetStatusText};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeResponse : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FStatusText;
	System::Word FStatusCode;
	System::UnicodeString __fastcall GetStatusText();
	System::Word __fastcall GetStatusCode();
	
public:
	__fastcall TEdgeResponse(const System::Word AStatusCode, const System::UnicodeString AStatusText);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEdgeResponse() { }
	
private:
	void *__IEdgeResponse;	// IEdgeResponse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7DDF5C07-A4DD-481A-99C8-4AAB309C9E57}
	operator _di_IEdgeResponse()
	{
		_di_IEdgeResponse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IEdgeResponse*(void) { return (IEdgeResponse*)&__IEdgeResponse; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{91E2C804-A926-4F3D-A382-79855AB383E6}") IEdgeResponseWriter  : public System::IInterface 
{
	virtual void __fastcall WriteResponse(const _di_IEdgeResponse AResponse) = 0 ;
	virtual void __fastcall WriteContent(const System::UnicodeString AContentType, const System::UnicodeString ABody) = 0 /* overload */;
	virtual void __fastcall WriteContent(const System::UnicodeString AContentType, System::Classes::TStream* const AStream) = 0 /* overload */;
#ifndef _WIN64
	virtual void __fastcall WriteContent(const System::UnicodeString AContentType, const System::DynamicArray<System::Byte> ABody) = 0 /* overload */;
#else /* _WIN64 */
	virtual void __fastcall WriteContent(const System::UnicodeString AContentType, const System::TArray__1<System::Byte> ABody) = 0 /* overload */;
#endif /* _WIN64 */
};

struct DECLSPEC_DRECORD TEdgeVersion
{
private:
	System::Byte FMajor;
	System::Byte FMinor;
	
public:
	__fastcall TEdgeVersion(System::Byte AMajor, System::Byte AMinor);
	__property System::Byte Minor = {read=FMinor};
	__property System::Byte Major = {read=FMajor};
	TEdgeVersion() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeReaderWriterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE ICreateRequestReader;
	typedef System::DelphiInterface<ICreateRequestReader> _di_ICreateRequestReader;
	__interface ICreateRequestReader  : public System::IInterface 
	{
		virtual bool __fastcall TryCreateReader(const TEdgeVersion AVersion, System::Classes::TStream* const AStream, /* out */ _di_IEdgeRequestReader &AReader) = 0 ;
	};
	
	__interface DELPHIINTERFACE ICreateResponseWriter;
	typedef System::DelphiInterface<ICreateResponseWriter> _di_ICreateResponseWriter;
	__interface ICreateResponseWriter  : public System::IInterface 
	{
		virtual bool __fastcall TryCreateWriter(const TEdgeVersion AVersion, System::Classes::TStream* const AStream, /* out */ _di_IEdgeResponseWriter &AReader) = 0 ;
	};
	
	
private:
	System::Generics::Collections::TDictionary__2<int,_di_ICreateRequestReader>* FRequestReaders;
	System::Generics::Collections::TDictionary__2<int,_di_ICreateResponseWriter>* FResponseWriters;
	static TEdgeReaderWriterFactory* FInstance;
	TEdgeVersion __fastcall ReadVersion(System::Classes::TStream* const AStream);
	void __fastcall RaiseDuplicate();
	void __fastcall RaiseNotFound();
	int FID;
	
public:
	__fastcall TEdgeReaderWriterFactory();
	__fastcall virtual ~TEdgeReaderWriterFactory();
	int __fastcall RegisterRequestReader(const _di_ICreateRequestReader AReader);
	void __fastcall UnregisterRequestReader(int AID);
	int __fastcall RegisterResponseWriter(const _di_ICreateResponseWriter AWriter);
	void __fastcall UnregisterResponseWriter(int AID);
	bool __fastcall TryCreateResponseWriter(System::Classes::TStream* const AStream, /* out */ _di_IEdgeResponseWriter &AWriter, const TEdgeVersion AVersion)/* overload */;
	bool __fastcall TryCreateResponseWriter(System::Classes::TStream* const AStream, /* out */ _di_IEdgeResponseWriter &AWriter)/* overload */;
	bool __fastcall TryCreateRequestReader(System::Classes::TStream* const AStream, /* out */ _di_IEdgeRequestReader &AReader);
	_di_IEdgeResponseWriter __fastcall CreateResponseWriter(System::Classes::TStream* const AStream, const TEdgeVersion AVersion)/* overload */;
	_di_IEdgeResponseWriter __fastcall CreateResponseWriter(System::Classes::TStream* const AStream)/* overload */;
	_di_IEdgeRequestReader __fastcall CreateRequestReader(System::Classes::TStream* const AStream);
	/* static */ __property TEdgeReaderWriterFactory* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeStreamReader : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	void __fastcall RaiseContentError();
	void __fastcall RaiseReadEOFError();
	
public:
	__fastcall TEdgeStreamReader(System::Classes::TStream* const AStream);
	TEdgeVersion __fastcall ReadVersion();
	System::Word __fastcall ReadShortUInt();
	unsigned __fastcall ReadUInt();
	System::UnicodeString __fastcall ReadShortString();
#ifndef _WIN64
	System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ReadStringKeyValues();
#else /* _WIN64 */
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall ReadStringKeyValues();
#endif /* _WIN64 */
	bool __fastcall CanReadShortString();
#ifndef _WIN64
	void __fastcall ReadBytes(const System::DynamicArray<System::Byte> ABytes, int AOffset)/* overload */;
	void __fastcall ReadBytes(const System::DynamicArray<System::Byte> ABytes)/* overload */;
#else /* _WIN64 */
	void __fastcall ReadBytes(const System::TArray__1<System::Byte> ABytes, int AOffset)/* overload */;
	void __fastcall ReadBytes(const System::TArray__1<System::Byte> ABytes)/* overload */;
#endif /* _WIN64 */
	void __fastcall ReadStream(System::Classes::TStream* const AStream, __int64 ACount)/* overload */;
	bool __fastcall CanRead(int ACount);
	__property System::Classes::TStream* Stream = {read=FStream};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEdgeStreamReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEdgeStreamWriter : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	
public:
	__fastcall TEdgeStreamWriter(System::Classes::TStream* const AStream);
	void __fastcall WriteVersion(const TEdgeVersion AVersion);
	void __fastcall WriteShortUInt(System::Word ALength);
	void __fastcall WriteUInt(unsigned ALength);
#ifndef _WIN64
	void __fastcall WriteStringKeyValues(const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > APairs);
#else /* _WIN64 */
	void __fastcall WriteStringKeyValues(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > APairs);
#endif /* _WIN64 */
	void __fastcall WriteShortString(const System::UnicodeString AValue);
#ifndef _WIN64
	void __fastcall WriteBytes(const System::DynamicArray<System::Byte> ABytes);
#else /* _WIN64 */
	void __fastcall WriteBytes(const System::TArray__1<System::Byte> ABytes);
#endif /* _WIN64 */
	void __fastcall WriteStream(System::Classes::TStream* const AStream);
	__property System::Classes::TStream* Stream = {read=FStream};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TEdgeStreamWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEdgeReadError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEdgeReadError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEdgeReadError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReadError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReadError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReadError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReadError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEdgeReadError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEdgeReadError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReadError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReadError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReadError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReadError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEdgeReadError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEdgeReaderWriterFactoryError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEdgeReaderWriterFactoryError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEdgeReaderWriterFactoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReaderWriterFactoryError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReaderWriterFactoryError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReaderWriterFactoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReaderWriterFactoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEdgeReaderWriterFactoryError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEdgeReaderWriterFactoryError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReaderWriterFactoryError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReaderWriterFactoryError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReaderWriterFactoryError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReaderWriterFactoryError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEdgeReaderWriterFactoryError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEdgeReaderVersionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEdgeReaderVersionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEdgeReaderVersionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReaderVersionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEdgeReaderVersionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReaderVersionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEdgeReaderVersionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEdgeReaderVersionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEdgeReaderVersionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReaderVersionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEdgeReaderVersionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReaderVersionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEdgeReaderVersionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEdgeReaderVersionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TEdgeVersion EdgePayloadVersion10;
extern DELPHI_PACKAGE TEdgeVersion EdgePayloadVersion20;
}	/* namespace Edgepayload */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGEPAYLOAD)
using namespace Emshosting::Edgepayload;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgepayloadHPP
