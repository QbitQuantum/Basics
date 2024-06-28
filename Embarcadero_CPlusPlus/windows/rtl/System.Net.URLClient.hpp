// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.URLClient.pas' rev: 34.00 (Windows)

#ifndef System_Net_UrlclientHPP
#define System_Net_UrlclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Net.Mime.hpp>

//-- user supplied -----------------------------------------------------------
#pragma comment(lib, "winhttp")
#pragma comment(lib, "crypt32")

namespace System
{
namespace Net
{
namespace Urlclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ENetException;
class DELPHICLASS ENetCredentialException;
class DELPHICLASS ENetURIException;
class DELPHICLASS ENetURIClientException;
class DELPHICLASS ENetURIRequestException;
class DELPHICLASS ENetURIResponseException;
struct TNameValuePair;
struct TURI;
class DELPHICLASS TCredentialsStorage;
struct TProxySettings;
class DELPHICLASS TURLHeaders;
__interface DELPHIINTERFACE IURLRequest;
typedef System::DelphiInterface<IURLRequest> _di_IURLRequest;
class DELPHICLASS TURLRequest;
__interface DELPHIINTERFACE IURLResponse;
typedef System::DelphiInterface<IURLResponse> _di_IURLResponse;
class DELPHICLASS TURLResponse;
class DELPHICLASS TURLClient;
struct TCertificate;
class DELPHICLASS TCertificateList;
class DELPHICLASS TURLSchemes;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetCredentialException : public ENetException
{
	typedef ENetException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetCredentialException(const System::UnicodeString Msg) : ENetException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetCredentialException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetCredentialException(NativeUInt Ident)/* overload */ : ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetCredentialException(System::PResStringRec ResStringRec)/* overload */ : ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetCredentialException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetCredentialException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetCredentialException(const System::UnicodeString Msg, int AHelpContext) : ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetCredentialException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetCredentialException(NativeUInt Ident, int AHelpContext)/* overload */ : ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetCredentialException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetCredentialException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetCredentialException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetCredentialException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetURIException : public ENetException
{
	typedef ENetException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetURIException(const System::UnicodeString Msg) : ENetException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetURIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIException(NativeUInt Ident)/* overload */ : ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIException(System::PResStringRec ResStringRec)/* overload */ : ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetURIException(const System::UnicodeString Msg, int AHelpContext) : ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetURIException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIException(NativeUInt Ident, int AHelpContext)/* overload */ : ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetURIException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetURIClientException : public ENetException
{
	typedef ENetException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetURIClientException(const System::UnicodeString Msg) : ENetException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetURIClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIClientException(NativeUInt Ident)/* overload */ : ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIClientException(System::PResStringRec ResStringRec)/* overload */ : ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetURIClientException(const System::UnicodeString Msg, int AHelpContext) : ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetURIClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIClientException(NativeUInt Ident, int AHelpContext)/* overload */ : ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIClientException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetURIClientException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetURIRequestException : public ENetException
{
	typedef ENetException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetURIRequestException(const System::UnicodeString Msg) : ENetException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetURIRequestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIRequestException(NativeUInt Ident)/* overload */ : ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIRequestException(System::PResStringRec ResStringRec)/* overload */ : ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIRequestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIRequestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetURIRequestException(const System::UnicodeString Msg, int AHelpContext) : ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetURIRequestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIRequestException(NativeUInt Ident, int AHelpContext)/* overload */ : ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIRequestException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIRequestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIRequestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetURIRequestException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ENetURIResponseException : public ENetException
{
	typedef ENetException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetURIResponseException(const System::UnicodeString Msg) : ENetException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetURIResponseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIResponseException(NativeUInt Ident)/* overload */ : ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetURIResponseException(System::PResStringRec ResStringRec)/* overload */ : ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIResponseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetURIResponseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetURIResponseException(const System::UnicodeString Msg, int AHelpContext) : ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetURIResponseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIResponseException(NativeUInt Ident, int AHelpContext)/* overload */ : ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetURIResponseException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIResponseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetURIResponseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetURIResponseException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TNameValuePair
{
public:
	System::UnicodeString Name;
	System::UnicodeString Value;
	__fastcall TNameValuePair(const System::UnicodeString AName, const System::UnicodeString AValue);
	TNameValuePair() {}
};


#ifndef _WIN64
typedef System::DynamicArray<TNameValuePair> TNameValueArray;
#else /* _WIN64 */
typedef System::TArray__1<TNameValuePair> TNameValueArray;
#endif /* _WIN64 */

typedef TNameValuePair TURIParameter;

#ifndef _WIN64
typedef System::DynamicArray<TNameValuePair> TURIParameters;
#else /* _WIN64 */
typedef System::TArray__1<TNameValuePair> TURIParameters;
#endif /* _WIN64 */

struct DECLSPEC_DRECORD TURI
{
	
private:
	enum class DECLSPEC_DENUM TEncType : unsigned char { URLEnc, FormEnc };
	
	typedef void __fastcall (__closure *TSchemeDecomposeProc)(const System::UnicodeString AURIStr, int Pos, int Limit, int SlashCount);
	
	
private:
	System::UnicodeString FScheme;
	System::UnicodeString FUsername;
	System::UnicodeString FPassword;
	System::UnicodeString FHost;
	int FPort;
	System::UnicodeString FPath;
	System::UnicodeString FQuery;
#ifndef _WIN64
	System::DynamicArray<TNameValuePair> FParams;
#else /* _WIN64 */
	System::TArray__1<TNameValuePair> FParams;
#endif /* _WIN64 */
	System::UnicodeString FFragment;
	void __fastcall DecomposeBaseScheme(const System::UnicodeString AURIStr, int Pos, int Limit, int SlashCount);
	void __fastcall DecomposeNoAuthorityScheme(const System::UnicodeString AURIStr, int Pos, int Limit, int SlashCount);
	bool __fastcall IsMailtoScheme();
	bool __fastcall IsSchemeNoAuthority();
	bool __fastcall IsValidPort();
	int __fastcall GetDefaultPort(const System::UnicodeString AScheme);
	void __fastcall ParseParams(bool Encode = false);
	int __fastcall FindParameterIndex(const System::UnicodeString AName);
	TNameValuePair __fastcall GetParameter(const int I);
	System::UnicodeString __fastcall GetParameterByName(const System::UnicodeString AName);
	void __fastcall SetParameter(const int I, const TNameValuePair &Value);
	void __fastcall SetParameterByName(const System::UnicodeString AName, const System::UnicodeString Value);
	System::UnicodeString __fastcall GetQuery();
	void __fastcall DecomposeURI(const System::UnicodeString AURIStr, bool ARaiseNoSchema);
	void __fastcall SetScheme(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetHost(const System::UnicodeString Value);
	void __fastcall SetPath(const System::UnicodeString Value);
	void __fastcall SetQuery(const System::UnicodeString Value);
#ifndef _WIN64
	void __fastcall SetParams(const System::DynamicArray<TNameValuePair> Value);
#else /* _WIN64 */
	void __fastcall SetParams(const System::TArray__1<TNameValuePair> Value);
#endif /* _WIN64 */
	
public:
	#define TURI_SCHEME_HTTP L"http"
	
	#define TURI_SCHEME_HTTPS L"https"
	
	#define TURI_SCHEME_MAILTO L"mailto"
	
	#define TURI_SCHEME_NEWS L"news"
	
	#define TURI_SCHEME_TEL L"tel"
	
	#define TURI_SCHEME_URN L"urn"
	
	__fastcall TURI(const System::UnicodeString AURIStr);
	System::UnicodeString __fastcall ToString();
#ifndef _WIN64
	void __fastcall ComposeURI(const System::UnicodeString AScheme, const System::UnicodeString AUsername, const System::UnicodeString APassword, const System::UnicodeString AHostname, int APort, const System::UnicodeString APath, const System::DynamicArray<TNameValuePair> AParams, const System::UnicodeString AFragment);
#else /* _WIN64 */
	void __fastcall ComposeURI(const System::UnicodeString AScheme, const System::UnicodeString AUsername, const System::UnicodeString APassword, const System::UnicodeString AHostname, int APort, const System::UnicodeString APath, const System::TArray__1<TNameValuePair> AParams, const System::UnicodeString AFragment);
#endif /* _WIN64 */
	void __fastcall AddParameter(const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
	void __fastcall AddParameter(const TNameValuePair &AParameter)/* overload */;
	void __fastcall DeleteParameter(int AIndex)/* overload */;
	void __fastcall DeleteParameter(const System::UnicodeString AName)/* overload */;
	static System::UnicodeString __fastcall URLEncode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.URL.Encode") (const System::UnicodeString AValue, bool SpacesAsPlus = false);
	static System::UnicodeString __fastcall URLDecode _DEPRECATED_ATTRIBUTE1("Use TNetEncoding.URL.Decode") (const System::UnicodeString AValue, bool PlusAsSpaces = false);
	System::UnicodeString __fastcall Encode();
	static System::UnicodeString __fastcall UnicodeToIDNA(const System::UnicodeString AHostName);
	static System::UnicodeString __fastcall IDNAToUnicode(const System::UnicodeString AHostName);
	static System::UnicodeString __fastcall PathRelativeToAbs(const System::UnicodeString RelPath, const TURI &Base);
	static System::UnicodeString __fastcall FixupForREST(const System::UnicodeString AURL);
	__property TNameValuePair Parameter[const int I] = {read=GetParameter, write=SetParameter};
	__property System::UnicodeString ParameterByName[const System::UnicodeString AName] = {read=GetParameterByName, write=SetParameterByName};
	__property System::UnicodeString Scheme = {read=FScheme, write=SetScheme};
	__property System::UnicodeString Username = {read=FUsername, write=SetUserName};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property System::UnicodeString Host = {read=FHost, write=SetHost};
	__property int Port = {read=FPort, write=FPort};
	__property System::UnicodeString Path = {read=FPath, write=SetPath};
	__property System::UnicodeString Query = {read=FQuery, write=SetQuery};
#ifndef _WIN64
	__property System::DynamicArray<TNameValuePair> Params = {read=FParams, write=SetParams};
#else /* _WIN64 */
	__property System::TArray__1<TNameValuePair> Params = {read=FParams, write=SetParams};
#endif /* _WIN64 */
	__property System::UnicodeString Fragment = {read=FFragment, write=FFragment};
	TURI() {}
};


enum class DECLSPEC_DENUM TAuthPersistenceType : unsigned char { Request, Client };

enum class DECLSPEC_DENUM TAuthTargetType : unsigned char { Proxy, Server };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCredentialsStorage : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TAuthSchemeType : unsigned char { Basic, Digest, NTLM, Negotiate };
	
	typedef void __fastcall (*TCredentialAuthCallback)(System::TObject* const Sender, TAuthTargetType AnAuthTarget, const System::UnicodeString ARealm, const System::UnicodeString AURL, System::UnicodeString &AUserName, System::UnicodeString &APassword, bool &AbortAuth, TAuthPersistenceType &Persistence);
	
	typedef void __fastcall (__closure *TCredentialAuthEvent)(System::TObject* const Sender, TAuthTargetType AnAuthTarget, const System::UnicodeString ARealm, const System::UnicodeString AURL, System::UnicodeString &AUserName, System::UnicodeString &APassword, bool &AbortAuth, TAuthPersistenceType &Persistence);
	
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TCredential
	{
	public:
		TAuthTargetType AuthTarget;
		System::UnicodeString Realm;
		System::UnicodeString URL;
		System::UnicodeString UserName;
		System::UnicodeString Password;
		__fastcall TCredential(TAuthTargetType AnAuthTarget, const System::UnicodeString ARealm, const System::UnicodeString AURL, const System::UnicodeString AUserName, const System::UnicodeString APassword);
		bool __fastcall IsEmpty();
		TCredential() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
#ifndef _WIN64
	typedef System::DynamicArray<TCredential> TCredentialArray;
#else /* _WIN64 */
	typedef System::TArray__1<TCredential> TCredentialArray;
#endif /* _WIN64 */
	
	class DELPHICLASS TCredentialComparer;
	class PASCALIMPLEMENTATION TCredentialComparer : public System::Generics::Defaults::TComparer__1<TCredentialsStorage::TCredential>
	{
		typedef System::Generics::Defaults::TComparer__1<TCredentialsStorage::TCredential> inherited;
		
	public:
		virtual int __fastcall Compare(const TCredentialsStorage::TCredential &Left, const TCredentialsStorage::TCredential &Right);
	public:
		/* TObject.Create */ inline __fastcall TCredentialComparer() : System::Generics::Defaults::TComparer__1<TCredentialsStorage::TCredential>() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TCredentialComparer() { }
		
	};
	
	
	typedef System::DelphiInterface<System::Generics::Defaults::IComparer__1<TCredential> > ICredComparer;
	
	
private:
#ifndef _WIN64
	System::DynamicArray<TCredential> __fastcall GetCredentials();
#else /* _WIN64 */
	System::TArray__1<TCredential> __fastcall GetCredentials();
#endif /* _WIN64 */
	
protected:
	System::Generics::Collections::TList__1<TCredential>* FCredentials;
	static TCredentialComparer* FCredComparer;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__fastcall TCredentialsStorage();
	__fastcall virtual ~TCredentialsStorage();
	void __fastcall ClearCredentials();
	bool __fastcall AddCredential(const TCredential &ACredential);
	bool __fastcall RemoveCredential(TAuthTargetType AnAuthTargetType, const System::UnicodeString ARealm, const System::UnicodeString AURL = System::UnicodeString(), const System::UnicodeString AUser = System::UnicodeString());
#ifndef _WIN64
	System::DynamicArray<TCredential> __fastcall FindCredentials(TAuthTargetType AnAuthTargetType, const System::UnicodeString ARealm, const System::UnicodeString AURL = System::UnicodeString(), const System::UnicodeString AUser = System::UnicodeString());
#else /* _WIN64 */
	System::TArray__1<TCredential> __fastcall FindCredentials(TAuthTargetType AnAuthTargetType, const System::UnicodeString ARealm, const System::UnicodeString AURL = System::UnicodeString(), const System::UnicodeString AUser = System::UnicodeString());
#endif /* _WIN64 */
	TCredential __fastcall FindAccurateCredential(TAuthTargetType AnAuthTargetType, const System::UnicodeString ARealm, const System::UnicodeString AURL = System::UnicodeString(), const System::UnicodeString AUser = System::UnicodeString());
#ifndef _WIN64
	__property System::DynamicArray<TCredential> Credentials = {read=GetCredentials};
	__classmethod System::DynamicArray<TCredential> __fastcall SortCredentials(const System::DynamicArray<TCredential> ACredentials);
#else /* _WIN64 */
	__property System::TArray__1<TCredential> Credentials = {read=GetCredentials};
	__classmethod System::TArray__1<TCredential> __fastcall SortCredentials(const System::TArray__1<TCredential> ACredentials);
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TProxySettings
{
private:
	System::UnicodeString FHost;
	int FPort;
	System::UnicodeString FScheme;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	TCredentialsStorage::TCredential FCredential;
	TCredentialsStorage::TCredential __fastcall GetCredential();
	
public:
	__fastcall TProxySettings(const System::UnicodeString AURL)/* overload */;
	__fastcall TProxySettings(const System::UnicodeString AHost, int APort, const System::UnicodeString AUserName, const System::UnicodeString APassword, const System::UnicodeString AScheme)/* overload */;
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property int Port = {read=FPort, write=FPort};
	__property System::UnicodeString Scheme = {read=FScheme, write=FScheme};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property TCredentialsStorage::TCredential Credential = {read=GetCredential};
	TProxySettings() {}
};


typedef TNameValuePair TNetHeader;

#ifndef _WIN64
typedef System::DynamicArray<TNameValuePair> TNetHeaders;
#else /* _WIN64 */
typedef System::TArray__1<TNameValuePair> TNetHeaders;
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TURLHeaders : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TEnumerator
	{
	private:
		TURLHeaders* FHeaders;
		int FIndex;
		TNameValuePair __fastcall GetCurrent();
		void __fastcall Create(TURLHeaders* const AHeaders);
		
	public:
		bool __fastcall MoveNext();
		__property TNameValuePair Current = {read=GetCurrent};
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	class DELPHICLASS TValueList;
	class PASCALIMPLEMENTATION TValueList : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Net::Mime::THeaderValueList* FList;
		TURLHeaders* FHeaders;
		System::UnicodeString FName;
		
	protected:
		__fastcall TValueList(TURLHeaders* AHeaders, const System::UnicodeString AName);
		
	public:
		__fastcall virtual ~TValueList();
		TURLHeaders::TValueList* __fastcall SetSubject(const System::UnicodeString AValue);
		TURLHeaders::TValueList* __fastcall Clear();
		TURLHeaders::TValueList* __fastcall Delete(int AIndex);
		TURLHeaders::TValueList* __fastcall Add(const System::UnicodeString AName)/* overload */;
		TURLHeaders::TValueList* __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AValue, bool AQuoteVal = true)/* overload */;
		TURLHeaders* __fastcall End();
		__property System::Net::Mime::THeaderValueList* List = {read=FList};
	};
	
	
	class DELPHICLASS TAcceptList;
	class PASCALIMPLEMENTATION TAcceptList : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* FList;
		TURLHeaders* FHeaders;
		System::UnicodeString FName;
		
	protected:
		__fastcall TAcceptList(TURLHeaders* AHeaders, const System::UnicodeString AName);
		
	public:
		__fastcall virtual ~TAcceptList();
		TURLHeaders::TAcceptList* __fastcall Clear();
		TURLHeaders::TAcceptList* __fastcall Delete(int AIndex);
		TURLHeaders::TAcceptList* __fastcall Add(const System::UnicodeString AName, double AWeight = 1.000000E+00, System::Classes::TStrings* AExtra = (System::Classes::TStrings*)(0x0));
		TURLHeaders* __fastcall End();
		__property System::Net::Mime::TAcceptValueListBase__1<System::Net::Mime::TAcceptValueItem*>* List = {read=FList};
	};
	
	
	
public:
	System::UnicodeString operator[](const System::UnicodeString AName) { return this->Value[AName]; }
	
private:
#ifndef _WIN64
	System::DynamicArray<TNameValuePair> FHeaders;
#else /* _WIN64 */
	System::TArray__1<TNameValuePair> FHeaders;
#endif /* _WIN64 */
	int __fastcall GetCount();
	void __fastcall CheckRange(int AIndex);
	System::UnicodeString __fastcall GetNames(int AIndex);
	System::UnicodeString __fastcall GetValues(int AIndex);
	System::UnicodeString __fastcall GetValue(const System::UnicodeString AName);
	void __fastcall SetValue(const System::UnicodeString AName, const System::UnicodeString AValue);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* ADest);
	
public:
	virtual System::UnicodeString __fastcall ToString();
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource)/* overload */;
#ifndef _WIN64
	HIDESBASE void __fastcall Assign(const System::DynamicArray<TNameValuePair> AHeaders)/* overload */;
#else /* _WIN64 */
	HIDESBASE void __fastcall Assign(const System::TArray__1<TNameValuePair> AHeaders)/* overload */;
#endif /* _WIN64 */
	int __fastcall FindItem(const System::UnicodeString AName);
	TURLHeaders* __fastcall Add(const TNameValuePair &AHeader)/* overload */;
	TURLHeaders* __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AValue)/* overload */;
#ifndef _WIN64
	TURLHeaders* __fastcall Append(const System::DynamicArray<TNameValuePair> AHeaders)/* overload */;
#else /* _WIN64 */
	TURLHeaders* __fastcall Append(const System::TArray__1<TNameValuePair> AHeaders)/* overload */;
#endif /* _WIN64 */
	TURLHeaders* __fastcall Append(TURLHeaders* const AHeaders)/* overload */;
	TURLHeaders* __fastcall Clear();
	TURLHeaders* __fastcall Delete(int AIndex)/* overload */;
	TURLHeaders* __fastcall Delete(const System::UnicodeString AName)/* overload */;
	TValueList* __fastcall ValueList(const System::UnicodeString AName);
	TAcceptList* __fastcall AcceptList(const System::UnicodeString AName);
	TEnumerator __fastcall GetEnumerator();
#ifndef _WIN64
	__property System::DynamicArray<TNameValuePair> Headers = {read=FHeaders};
#else /* _WIN64 */
	__property System::TArray__1<TNameValuePair> Headers = {read=FHeaders};
#endif /* _WIN64 */
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Names[int AIndex] = {read=GetNames};
	__property System::UnicodeString Values[int AIndex] = {read=GetValues};
	__property System::UnicodeString Value[const System::UnicodeString AName] = {read=GetValue, write=SetValue/*, default*/};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TURLHeaders() { }
	
public:
	/* TObject.Create */ inline __fastcall TURLHeaders() : System::Classes::TPersistent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IURLRequest  : public System::IInterface 
{
	virtual TCredentialsStorage::TCredential __fastcall GetCredential() = 0 ;
	virtual void __fastcall SetCredential(const TCredentialsStorage::TCredential &ACredential) = 0 /* overload */;
	virtual void __fastcall SetCredential(const System::UnicodeString AUserName, const System::UnicodeString APassword) = 0 /* overload */;
	__property TCredentialsStorage::TCredential Credential = {read=GetCredential, write=SetCredential};
	virtual TURI __fastcall GetURL() = 0 ;
	virtual void __fastcall SetURL(const TURI &AValue) = 0 ;
	__property TURI URL = {read=GetURL, write=SetURL};
	virtual System::UnicodeString __fastcall GetMethodString() = 0 ;
	virtual void __fastcall SetMethodString(const System::UnicodeString AValue) = 0 ;
	__property System::UnicodeString MethodString = {read=GetMethodString, write=SetMethodString};
	virtual System::Classes::TStream* __fastcall GetSourceStream() = 0 ;
	virtual void __fastcall SetSourceStream(System::Classes::TStream* const ASourceStream) = 0 ;
	__property System::Classes::TStream* SourceStream = {read=GetSourceStream, write=SetSourceStream};
	virtual void __fastcall Cancel() = 0 ;
	virtual bool __fastcall GetIsCancelled() = 0 ;
	__property bool IsCancelled = {read=GetIsCancelled};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TURLRequest : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	int FConnectionTimeout;
	int FSendTimeout;
	int FResponseTimeout;
	bool FSendTimeoutChanged;
	int __fastcall GetSendTimeout();
	
protected:
	TURI FURL;
	System::UnicodeString FMethodString;
	TCredentialsStorage::TCredential FLocalCredential;
	TURLClient* FClient;
	System::Classes::TStream* FSourceStream;
	bool FCancelled;
	TCredentialsStorage::TCredential __fastcall GetCredential();
	virtual void __fastcall SetCredential(const TCredentialsStorage::TCredential &ACredential)/* overload */;
	virtual void __fastcall SetCredential(const System::UnicodeString AUserName, const System::UnicodeString APassword)/* overload */;
	TURI __fastcall GetURL();
	void __fastcall SetURL(const TURI &AValue);
	System::UnicodeString __fastcall GetMethodString();
	void __fastcall SetMethodString(const System::UnicodeString AValue);
	virtual System::Classes::TStream* __fastcall GetSourceStream();
	virtual void __fastcall SetSourceStream(System::Classes::TStream* const ASourceStream);
	bool __fastcall GetIsCancelled();
	virtual void __fastcall DoCancel();
	virtual void __fastcall DoResetCancel();
	void __fastcall Cancel();
	__fastcall TURLRequest(TURLClient* const AClient, const System::UnicodeString AMethodString, const TURI &AURI);
	virtual void __fastcall SetConnectionTimeout(const int Value);
	virtual void __fastcall SetSendTimeout(const int Value);
	virtual void __fastcall SetResponseTimeout(const int Value);
	
public:
	__fastcall virtual ~TURLRequest();
	__property int ConnectionTimeout = {read=FConnectionTimeout, write=SetConnectionTimeout, nodefault};
	__property int SendTimeout = {read=GetSendTimeout, write=SetSendTimeout, nodefault};
	__property int ResponseTimeout = {read=FResponseTimeout, write=SetResponseTimeout, nodefault};
private:
	void *__IURLRequest;	// IURLRequest 
	
public:
	operator IURLRequest*(void) { return (IURLRequest*)&__IURLRequest; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{5D687C75-5C36-4302-B0AB-989DDB7558FE}") IURLResponse  : public System::IInterface 
{
#ifndef _WIN64
	virtual System::DynamicArray<TNameValuePair> __fastcall GetHeaders() = 0 ;
	__property System::DynamicArray<TNameValuePair> Headers = {read=GetHeaders};
#else /* _WIN64 */
	virtual System::TArray__1<TNameValuePair> __fastcall GetHeaders() = 0 ;
	__property System::TArray__1<TNameValuePair> Headers = {read=GetHeaders};
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetMimeType() = 0 ;
	__property System::UnicodeString MimeType = {read=GetMimeType};
	virtual System::Classes::TStream* __fastcall GetContentStream() = 0 ;
	__property System::Classes::TStream* ContentStream = {read=GetContentStream};
	virtual System::UnicodeString __fastcall ContentAsString(System::Sysutils::TEncoding* const AnEncoding = (System::Sysutils::TEncoding*)(0x0)) = 0 ;
	virtual System::Types::_di_IAsyncResult __fastcall GetAsyncResult() = 0 ;
	__property System::Types::_di_IAsyncResult AsyncResult = {read=GetAsyncResult};
};

class PASCALIMPLEMENTATION TURLResponse : public System::Classes::TBaseAsyncResult
{
	typedef System::Classes::TBaseAsyncResult inherited;
	
private:
	System::Classes::_di_TAsyncCallback FAsyncCallback;
	System::Classes::TAsyncProcedureEvent FAsyncCallbackEvent;
	System::Sysutils::_di_TProc FProc;
	
protected:
	_di_IURLRequest FRequest;
	System::Classes::TStream* FInternalStream;
	System::Classes::TStream* FStream;
	__fastcall TURLResponse(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AAsyncCallback, const System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent, const _di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */;
	__fastcall TURLResponse(System::TObject* const AContext, const _di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */;
	virtual System::Classes::TStream* __fastcall DoCreateInternalStream();
	virtual void __fastcall AsyncDispatch();
	virtual void __fastcall Complete();
	virtual void __fastcall Schedule();
	virtual bool __fastcall DoCancel();
	System::Types::_di_IAsyncResult __fastcall GetAsyncResult();
	
public:
	__fastcall virtual ~TURLResponse();
	System::Classes::TStream* __fastcall GetContentStream();
	virtual System::UnicodeString __fastcall GetMimeType() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<TNameValuePair> __fastcall GetHeaders() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<TNameValuePair> __fastcall GetHeaders() = 0 ;
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall ContentAsString(System::Sysutils::TEncoding* const AnEncoding = (System::Sysutils::TEncoding*)(0x0)) = 0 ;
protected:
	/* TBaseAsyncResult.Create */ inline __fastcall TURLResponse(System::TObject* const AContext)/* overload */ : System::Classes::TBaseAsyncResult(AContext) { }
	
public:
	/* TBaseAsyncResult.Create */ inline __fastcall TURLResponse()/* overload */ : System::Classes::TBaseAsyncResult() { }
	
private:
	void *__IURLResponse;	// IURLResponse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5D687C75-5C36-4302-B0AB-989DDB7558FE}
	operator _di_IURLResponse()
	{
		_di_IURLResponse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IURLResponse*(void) { return (IURLResponse*)&__IURLResponse; }
	#endif
	
};


class PASCALIMPLEMENTATION TURLClient : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Word DefaultConnectionTimeout = System::Word(0xea60);
	
	static const System::Word DefaultSendTimeout = System::Word(0xea60);
	
	static const System::Word DefaultResponseTimeout = System::Word(0xea60);
	
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TURLClient*>* FInstances;
	TCredentialsStorage::TCredentialAuthCallback FAuthCallback;
	TCredentialsStorage::TCredentialAuthEvent FAuthEvent;
	TCredentialsStorage* FInternalCredentialsStorage;
	TProxySettings FProxySettings;
	TCredentialsStorage* FCredentialsStorage;
	int FConnectionTimeout;
	int FSendTimeout;
	int FResponseTimeout;
	TURLClient* __fastcall GetInternalInstance(const System::UnicodeString AScheme);
	System::UnicodeString __fastcall GetUserAgent();
	void __fastcall SetUserAgent(const System::UnicodeString Value);
	
protected:
	TURLHeaders* FCustomHeaders;
	void __fastcall SetConnectionTimeout(const int Value);
	void __fastcall SetSendTimeout(const int Value);
	void __fastcall SetResponseTimeout(const int Value);
	System::UnicodeString __fastcall GetCustomHeaderValue(const System::UnicodeString Name);
	void __fastcall SetCustomHeaderValue(const System::UnicodeString Name, const System::UnicodeString Value);
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall SupportedSchemes();
	virtual _di_IURLResponse __fastcall DoExecute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::DynamicArray<TNameValuePair> AHeaders);
	virtual System::Types::_di_IAsyncResult __fastcall DoExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::DynamicArray<TNameValuePair> AHeaders, bool AOwnsSourceStream = false);
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall SupportedSchemes();
	virtual _di_IURLResponse __fastcall DoExecute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::TArray__1<TNameValuePair> AHeaders);
	virtual System::Types::_di_IAsyncResult __fastcall DoExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::TArray__1<TNameValuePair> AHeaders, bool AOwnsSourceStream = false);
#endif /* _WIN64 */
	virtual System::Types::_di_IAsyncResult __fastcall DoGetResponseInstance(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const _di_IURLRequest ARequest, System::Classes::TStream* const AContentStream);
	virtual _di_IURLRequest __fastcall DoGetRequestInstance(const System::UnicodeString ARequestMethod, const TURI &AURI);
	virtual void __fastcall DoAuthCallback(TAuthTargetType AnAuthTarget, const System::UnicodeString ARealm, const System::UnicodeString AURL, System::UnicodeString &AUserName, System::UnicodeString &APassword, bool &AbortAuth, TAuthPersistenceType &Persistence);
	__classmethod virtual TURLClient* __fastcall CreateInstance();
	static TURLClient* __fastcall GetInstance(const System::UnicodeString AScheme);
	virtual void __fastcall SetCredentialsStorage(TCredentialsStorage* const Value);
#ifndef _WIN64
	virtual System::DynamicArray<TCredentialsStorage::TCredential> __fastcall GetCredentials(TAuthTargetType AuthTarget, const System::UnicodeString ARealm, const System::UnicodeString URL);
#else /* _WIN64 */
	virtual System::TArray__1<TCredentialsStorage::TCredential> __fastcall GetCredentials(TAuthTargetType AuthTarget, const System::UnicodeString ARealm, const System::UnicodeString URL);
#endif /* _WIN64 */
	virtual void __fastcall SetProxySettings(const TProxySettings &Value);
	
public:
	__fastcall TURLClient();
	__fastcall virtual ~TURLClient();
	_di_IURLRequest __fastcall GetRequest(const System::UnicodeString ARequestMethod, const TURI &AURI)/* overload */;
	_di_IURLRequest __fastcall GetRequest(const System::UnicodeString ARequestMethod, const System::UnicodeString AURI)/* overload */;
#ifndef _WIN64
	_di_IURLResponse __fastcall Execute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	_di_IURLResponse __fastcall Execute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::DynamicArray<TNameValuePair> AHeaders = System::DynamicArray<TNameValuePair>())/* overload */;
#else /* _WIN64 */
	_di_IURLResponse __fastcall Execute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	_di_IURLResponse __fastcall Execute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<TNameValuePair> AHeaders = System::TArray__1<TNameValuePair>())/* overload */;
#endif /* _WIN64 */
	__classmethod _di_IURLResponse __fastcall EndAsyncURL(const System::Types::_di_IAsyncResult AAsyncResult)/* overload */;
	__classmethod _di_IURLResponse __fastcall EndAsyncURL(const _di_IURLResponse AAsyncResult)/* overload */;
	__property int ConnectionTimeout = {read=FConnectionTimeout, write=SetConnectionTimeout, nodefault};
	__property int SendTimeout = {read=FSendTimeout, write=SetSendTimeout, nodefault};
	__property int ResponseTimeout = {read=FResponseTimeout, write=SetResponseTimeout, nodefault};
	__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
	__property TCredentialsStorage::TCredentialAuthCallback AuthCallback = {read=FAuthCallback, write=FAuthCallback};
	__property TCredentialsStorage::TCredentialAuthEvent AuthEvent = {read=FAuthEvent, write=FAuthEvent};
	__property TCredentialsStorage* CredentialsStorage = {read=FCredentialsStorage, write=SetCredentialsStorage};
	__property TProxySettings ProxySettings = {read=FProxySettings, write=SetProxySettings};
	__property System::UnicodeString CustomHeaders[const System::UnicodeString AName] = {read=GetCustomHeaderValue, write=SetCustomHeaderValue};
	__property TURLHeaders* CustHeaders = {read=FCustomHeaders};
};


struct DECLSPEC_DRECORD TCertificate
{
public:
	System::UnicodeString CertName;
	System::UnicodeString SerialNum;
	System::TDateTime Expiry;
	System::TDateTime Start;
	System::UnicodeString Subject;
	System::UnicodeString Issuer;
	System::UnicodeString ProtocolName;
	System::UnicodeString AlgSignature;
	System::UnicodeString AlgEncryption;
	int KeySize;
	bool __fastcall IsEmpty();
};


class PASCALIMPLEMENTATION TCertificateList : public System::Generics::Collections::TList__1<TCertificate>
{
	typedef System::Generics::Collections::TList__1<TCertificate> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_Net_URLClient_TCertificate>.Create */ inline __fastcall TCertificateList()/* overload */ : System::Generics::Collections::TList__1<TCertificate>() { }
	/* {System_Generics_Collections}TList<System_Net_URLClient_TCertificate>.Create */ inline __fastcall TCertificateList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TCertificate> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TCertificate>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Net_URLClient_TCertificate>.Create */ inline __fastcall TCertificateList(System::Generics::Collections::TEnumerable__1<TCertificate>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TCertificate>(Collection) { }
	/* {System_Generics_Collections}TList<System_Net_URLClient_TCertificate>.Destroy */ inline __fastcall virtual ~TCertificateList() { }
	
};


typedef void __fastcall (*TNeedClientCertificateCallback)(System::TObject* const Sender, TURLRequest* const ARequest, TCertificateList* const ACertificateList, int &AnIndex);

typedef void __fastcall (__closure *TNeedClientCertificateEvent)(System::TObject* const Sender, TURLRequest* const ARequest, TCertificateList* const ACertificateList, int &AnIndex);

typedef void __fastcall (*TValidateCertificateCallback)(System::TObject* const Sender, TURLRequest* const ARequest, const TCertificate &Certificate, bool &Accepted);

typedef void __fastcall (__closure *TValidateCertificateEvent)(System::TObject* const Sender, TURLRequest* const ARequest, const TCertificate &Certificate, bool &Accepted);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TURLSchemes : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef _WIN64
	typedef System::TMetaClass* TURLClientClass;
#else /* _WIN64 */
	_DECLARE_METACLASS(System::TMetaClass, TURLClientClass);
#endif /* _WIN64 */
	
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,TURLClientClass>* FSchemeClients;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall RegisterURLClientScheme(const TURLClientClass AURLClientClass, const System::UnicodeString AScheme);
	__classmethod void __fastcall UnRegisterURLClientScheme(const System::UnicodeString AScheme);
	__classmethod TURLClient* __fastcall GetURLClientInstance(const System::UnicodeString AScheme);
public:
	/* TObject.Create */ inline __fastcall TURLSchemes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TURLSchemes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Urlclient */
}	/* namespace Net */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET_URLCLIENT)
using namespace System::Net::Urlclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET)
using namespace System::Net;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Net_UrlclientHPP
