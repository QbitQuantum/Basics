// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.Win.AdsTypes.pas' rev: 34.00 (Windows)

#ifndef Web_Win_AdstypesHPP
#define Web_Win_AdstypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Win.ComObj.hpp>
#include <Web.Win.AdsConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Win
{
namespace Adstypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EAdsException;
class DELPHICLASS TWebDirStruct;
class DELPHICLASS TWebDirList;
__interface DELPHIINTERFACE IVirtualWebDir;
typedef System::DelphiInterface<IVirtualWebDir> _di_IVirtualWebDir;
class DELPHICLASS TVirtualWebDir;
__interface DELPHIINTERFACE IADsObject;
typedef System::DelphiInterface<IADsObject> _di_IADsObject;
__interface DELPHIINTERFACE IAdsContainer;
typedef System::DelphiInterface<IAdsContainer> _di_IAdsContainer;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TAdsOpenStyle : unsigned char { asOpenWithGet, asOpenWithOpen };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EAdsException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EAdsException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EAdsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EAdsException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EAdsException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EAdsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EAdsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EAdsException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EAdsException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAdsException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EAdsException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdsException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EAdsException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EAdsException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebDirStruct : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FPath;
	System::UnicodeString FAdsPath;
	System::UnicodeString FParent;
	System::UnicodeString FSchema;
	System::UnicodeString FAppRoot;
	bool FAccessRead;
	bool FAccessWrite;
	bool FDontLog;
	bool FGrantByDefault;
	int FAccessFlags;
	System::UnicodeString FUNCUserName;
	System::UnicodeString FUNCPassword;
	bool FAccessExecute;
	bool FAccessSource;
	bool FAccessScript;
	bool FAccessNoRemoteRead;
	bool FAccessNoRemoteWrite;
	bool FAccessNoRemoteExecute;
	bool FAccessNoRemoteScript;
	bool FAccessNoRemoteSource;
	bool FEnableDirBrowsing;
	System::Classes::TStrings* FScriptMaps;
	
public:
	__fastcall TWebDirStruct();
	__fastcall virtual ~TWebDirStruct();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString Path = {read=FPath, write=FPath};
	__property System::UnicodeString AdsPath = {read=FAdsPath, write=FAdsPath};
	__property System::UnicodeString AppRoot = {read=FAppRoot, write=FAppRoot};
	__property System::UnicodeString Parent = {read=FParent, write=FParent};
	__property System::UnicodeString Schema = {read=FSchema, write=FSchema};
	__property bool AccessRead = {read=FAccessRead, write=FAccessRead, nodefault};
	__property bool AccessWrite = {read=FAccessWrite, write=FAccessWrite, nodefault};
	__property bool DontLog = {read=FDontLog, write=FDontLog, nodefault};
	__property bool GrantByDefault = {read=FGrantByDefault, write=FGrantByDefault, nodefault};
	__property int AccessFlags = {read=FAccessFlags, write=FAccessFlags, nodefault};
	__property System::UnicodeString UNCUserName = {read=FUNCUserName, write=FUNCUserName};
	__property System::UnicodeString UNCPassword = {read=FUNCPassword, write=FUNCPassword};
	__property bool AccessExecute = {read=FAccessExecute, write=FAccessExecute, nodefault};
	__property bool AccessSource = {read=FAccessSource, write=FAccessSource, nodefault};
	__property bool AccessScript = {read=FAccessScript, write=FAccessScript, nodefault};
	__property bool AccessNoRemoteRead = {read=FAccessNoRemoteRead, write=FAccessNoRemoteRead, nodefault};
	__property bool AccessNoRemoteWrite = {read=FAccessNoRemoteWrite, write=FAccessNoRemoteWrite, nodefault};
	__property bool AccessNoRemoteExecute = {read=FAccessNoRemoteExecute, write=FAccessNoRemoteExecute, nodefault};
	__property bool AccessNoRemoteScript = {read=FAccessNoRemoteScript, write=FAccessNoRemoteScript, nodefault};
	__property bool AccessNoRemoteSource = {read=FAccessNoRemoteSource, write=FAccessNoRemoteSource, nodefault};
	__property bool EnableDirBrowsing = {read=FEnableDirBrowsing, write=FEnableDirBrowsing, nodefault};
	__property System::Classes::TStrings* ScriptMaps = {read=FScriptMaps};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebDirList : public System::Classes::TList
{
	typedef System::Classes::TList inherited;
	
private:
	TWebDirStruct* __fastcall GetWebDirStruct(const int Index);
	
public:
	__fastcall virtual ~TWebDirList();
	__property TWebDirStruct* WebDirStruct[const int Index] = {read=GetWebDirStruct};
public:
	/* TObject.Create */ inline __fastcall TWebDirList() : System::Classes::TList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{76C77D2D-D22C-11D6-BFD0-00C04F79AB6E}") IVirtualWebDir  : public System::IInvokable 
{
	virtual TWebDirList* __fastcall GetWebDirInfo() = 0 ;
	virtual TWebDirList* __fastcall GetWebDirChildInfo(const System::UnicodeString VRootName) = 0 ;
	virtual TWebDirList* __fastcall GetRemoteWebDirInfo() = 0 ;
	virtual void __fastcall CreateVRoot(TWebDirStruct* const WebDir) = 0 ;
	virtual void __fastcall DeleteVRoot(const System::WideString VRootName) = 0 ;
	virtual void __fastcall SetIISPath(const System::WideString Domain, const System::WideString Root = L"1", const System::UnicodeString Username = System::UnicodeString(), const System::UnicodeString Password = System::UnicodeString()) = 0 ;
	virtual void __fastcall SetFilter(TWebDirStruct* const WebDir) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TVirtualWebDir : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TAdsOpenStyle FOpenStyle;
	int FRefCount;
	bool FContainerLoaded;
	bool FVirtualDirsLoaded;
	System::UnicodeString FVRootParent;
	System::UnicodeString FDomain;
	System::UnicodeString FIISPathNum;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	TWebDirList* FWebDirList;
	_di_IAdsContainer FContainer;
	TWebDirStruct* FFilter;
	void __fastcall SetOpenStyle(TAdsOpenStyle Value);
	
protected:
	HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	int __stdcall _AddRef();
	int __stdcall _Release();
	void __fastcall LoadContainer();
	void __fastcall LoadWebDirList();
	void __fastcall LoadWebDirChildList(const System::UnicodeString VRootName);
	__property _di_IAdsContainer Container = {read=FContainer, write=FContainer};
	bool __fastcall MatchFilter(TWebDirStruct* Match);
	void __fastcall LoadWebDirArray(const _di_IAdsContainer Container, TWebDirList* WebDirList, const System::UnicodeString MatchParent = System::UnicodeString(), bool ChildrenOnly = false, bool Recursive = false, const System::UnicodeString Path = System::UnicodeString());
	__property TAdsOpenStyle OpenStyle = {read=FOpenStyle, write=SetOpenStyle, nodefault};
	
public:
	__fastcall TVirtualWebDir();
	__fastcall virtual ~TVirtualWebDir();
	TWebDirList* __fastcall GetWebDirInfo();
	TWebDirList* __fastcall GetWebDirChildInfo(const System::UnicodeString VRootName);
	TWebDirList* __fastcall GetRemoteWebDirInfo();
	void __fastcall CreateVRoot(TWebDirStruct* const WebDir);
	void __fastcall DeleteVRoot(const System::WideString VRootName);
	void __fastcall SetIISPath(const System::WideString Domain, const System::WideString Root = L"1", const System::UnicodeString Username = System::UnicodeString(), const System::UnicodeString Password = System::UnicodeString());
	void __fastcall SetFilter(TWebDirStruct* const WebDir);
private:
	void *__IVirtualWebDir;	// IVirtualWebDir 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {76C77D2D-D22C-11D6-BFD0-00C04F79AB6E}
	operator _di_IVirtualWebDir()
	{
		_di_IVirtualWebDir intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IVirtualWebDir*(void) { return (IVirtualWebDir*)&__IVirtualWebDir; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{FD8256D0-FD15-11CE-ABC4-02608C9E7553}") IADsObject  : public IDispatch 
{
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_Class_(System::WideString &__Get_Class__result) = 0 ;
	virtual HRESULT __safecall Get_GUID(System::WideString &__Get_GUID_result) = 0 ;
	virtual HRESULT __safecall Get_ADsPath(System::WideString &__Get_ADsPath_result) = 0 ;
	virtual HRESULT __safecall Get_Parent(System::WideString &__Get_Parent_result) = 0 ;
	virtual HRESULT __safecall Get_Schema(System::WideString &__Get_Schema_result) = 0 ;
	virtual HRESULT __safecall GetInfo() = 0 ;
	virtual HRESULT __safecall SetInfo() = 0 ;
	virtual HRESULT __safecall Get(const System::WideString bstrName, System::OleVariant &__Get_result) = 0 ;
	virtual HRESULT __safecall Put(const System::WideString bstrName, System::OleVariant vProp) = 0 ;
	virtual HRESULT __safecall GetEx(const System::WideString bstrName, System::OleVariant &__GetEx_result) = 0 ;
	virtual HRESULT __safecall PutEx(int lnControlCode, const System::WideString bstrName, System::OleVariant vProp) = 0 ;
	virtual HRESULT __safecall GetInfoEx(System::OleVariant vProperties, int lnReserved) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Class_() { System::WideString __r; HRESULT __hr = Get_Class_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Class_ = {read=_scw_Get_Class_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_GUID() { System::WideString __r; HRESULT __hr = Get_GUID(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString GUID = {read=_scw_Get_GUID};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_ADsPath() { System::WideString __r; HRESULT __hr = Get_ADsPath(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString ADsPath = {read=_scw_Get_ADsPath};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Parent() { System::WideString __r; HRESULT __hr = Get_Parent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Parent = {read=_scw_Get_Parent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Schema() { System::WideString __r; HRESULT __hr = Get_Schema(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Schema = {read=_scw_Get_Schema};
};

__interface  INTERFACE_UUID("{001677D0-FD16-11CE-ABC4-02608C9E7553}") IAdsContainer  : public IDispatch 
{
	virtual HRESULT __safecall Get_Count(int &__Get_Count_result) = 0 ;
	virtual HRESULT __safecall Get__NewEnum(System::_di_IInterface &__Get__NewEnum_result) = 0 ;
	virtual HRESULT __safecall Get_Filter(System::OleVariant &__Get_Filter_result) = 0 ;
	virtual HRESULT __safecall Set_Filter(System::OleVariant pVar) = 0 ;
	virtual HRESULT __safecall Get_Hints(System::OleVariant &__Get_Hints_result) = 0 ;
	virtual HRESULT __safecall Set_Hints(System::OleVariant pvFilter) = 0 ;
	virtual HRESULT __safecall GetObject(const System::WideString ClassName, const System::WideString RelativeName, _di_IDispatch &__GetObject_result) = 0 ;
	virtual HRESULT __safecall Create(const System::WideString ClassName, const System::WideString RelativeName, _di_IDispatch &__Create_result) = 0 ;
	virtual HRESULT __safecall Delete(const System::WideString bstrClassName, const System::WideString bstrRelativeName) = 0 ;
	virtual HRESULT __safecall CopyHere(const System::WideString SourceName, const System::WideString NewName, _di_IDispatch &__CopyHere_result) = 0 ;
	virtual HRESULT __safecall MoveHere(const System::WideString SourceName, const System::WideString NewName, _di_IDispatch &__MoveHere_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Count() { int __r; HRESULT __hr = Get_Count(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Count = {read=_scw_Get_Count};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__NewEnum() { System::_di_IInterface __r; HRESULT __hr = Get__NewEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _NewEnum = {read=_scw_Get__NewEnum};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Filter() { System::OleVariant __r; HRESULT __hr = Get_Filter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Filter = {read=_scw_Get_Filter, write=Set_Filter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Hints() { System::OleVariant __r; HRESULT __hr = Get_Hints(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Hints = {read=_scw_Get_Hints, write=Set_Hints};
};

//-- var, const, procedure ---------------------------------------------------
#define sPath L"Path"
#define sAccessRead L"AccessRead"
#define sAccessWrite L"AccessWrite"
#define sAccessExecute L"AccessExecute"
#define sAccessSource L"AccessSource"
#define sAccessScript L"AccessScript"
#define sEnableDirBrowsing L"EnableDirBrowsing"
#define sAppRoot L"AppRoot"
#define sAppFriendlyName L"AppFriendlyName"
#define sScriptMaps L"ScriptMaps"
#define sDontLog L"DontLog"
#define sIPSecurity L"IPSecurity"
#define sUNCUSERNAME L"UNCUSERNAME"
#define sUNCPASSWORD L"UNCPASSWORD"
#define sAccessFlags L"AccessFlags"
#define ActiveDSDll L"activeds.dll"
extern DELPHI_PACKAGE GUID IID_IADsContainer;
static const System::Int8 MD_ACCESS_READ = System::Int8(0x1);
static const System::Int8 MD_ACCESS_WRITE = System::Int8(0x2);
static const System::Int8 MD_ACCESS_EXECUTE = System::Int8(0x4);
static const System::Int8 MD_ACCESS_SOURCE = System::Int8(0x10);
static const System::Word MD_ACCESS_SCRIPT = System::Word(0x200);
static const System::Word MD_ACCESS_NO_REMOTE_WRITE = System::Word(0x400);
static const System::Word MD_ACCESS_NO_REMOTE_READ = System::Word(0x1000);
static const System::Word MD_ACCESS_NO_REMOTE_EXECUTE = System::Word(0x2000);
static const System::Word MD_ACCESS_NO_REMOTE_SCRIPT = System::Word(0x4000);
#define sLocalHost L"localhost"
#define sIISRoot L"IIS://"
#define sW3Svc L"/w3svc"
#define IISPath L"IIS://localhost/w3svc"
static const System::WideChar sIISPathNum = (System::WideChar)(0x31);
#define sRoot L"Root"
#define IISWebServer L"IISWebServer"
#define IISWebVirtualDir L"IISWebVirtualDir"
#define IISAppRoot L"/LM/W3SVC/1/ROOT/"
extern DELPHI_PACKAGE void __fastcall CheckForIIS(void);
extern DELPHI_PACKAGE _di_IVirtualWebDir __fastcall GetVirtualWebDirObject(void);
extern DELPHI_PACKAGE HRESULT __stdcall ADsGetObject(System::WideString lpszPathName, const GUID &riid, /* out */ void *ppObject);
extern DELPHI_PACKAGE HRESULT __stdcall ADsOpenObject(System::WideString lpszPathName, System::WideString lpszUserName, System::WideString lpszPassword, unsigned dwReserved, const GUID &riid, /* out */ void *ppObject);
extern DELPHI_PACKAGE HRESULT __stdcall ADsBuildEnumerator(const _di_IAdsContainer pADsContainer, /* out */ _di_IEnumVARIANT &ppEnumVariant);
extern DELPHI_PACKAGE HRESULT __stdcall ADsFreeEnumerator(_di_IEnumVARIANT pEnumVariant);
extern DELPHI_PACKAGE HRESULT __stdcall ADsEnumerateNext(_di_IEnumVARIANT pEnumVariant, unsigned cElements, System::OleVariant &pvar, unsigned &pcElementsFetched);
}	/* namespace Adstypes */
}	/* namespace Win */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN_ADSTYPES)
using namespace Web::Win::Adstypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WIN)
using namespace Web::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Win_AdstypesHPP
