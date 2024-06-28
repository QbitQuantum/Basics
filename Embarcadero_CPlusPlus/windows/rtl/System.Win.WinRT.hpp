// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.WinRT.pas' rev: 34.00 (Windows)

#ifndef System_Win_WinrtHPP
#define System_Win_WinrtHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Rtti.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Winrt
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EWinRTException;
class DELPHICLASS TInspectableObject;
struct TWindowsString;
#ifndef _WIN64
struct THStringHelper /* Helper for Ordinal 'HSTRING' */;
#else /* _WIN64 */
struct THStringHelper /* Helper for long 'HSTRING' */;
#endif /* _WIN64 */
class DELPHICLASS WinRTClassNameAttribute;
class DELPHICLASS TWinRTImportHelper;
class DELPHICLASS TWinRTImport;
template<typename F> class DELPHICLASS TWinRTGenericImportF__1;
template<typename S> class DELPHICLASS TWinRTGenericImportS__1;
template<typename I> class DELPHICLASS TWinRTGenericImportI__1;
template<typename F1, typename F2> class DELPHICLASS TWinRTGenericImportF2__2;
template<typename F1, typename F2, typename S> class DELPHICLASS TWinRTGenericImportF2S__3;
template<typename F, typename S> class DELPHICLASS TWinRTGenericImportFS__2;
template<typename F, typename I> class DELPHICLASS TWinRTGenericImportFI__2;
template<typename S1, typename S2> class DELPHICLASS TWinRTGenericImportS2__2;
template<typename S, typename I> class DELPHICLASS TWinRTGenericImportSI__2;
template<typename F1, typename F2, typename I> class DELPHICLASS TWinRTGenericImportF2I__3;
template<typename F, typename S1, typename S2> class DELPHICLASS TWinRTGenericImportFS2__3;
template<typename F, typename S, typename I> class DELPHICLASS TWinRTGenericImportFSI__3;
template<typename S1, typename S2, typename I> class DELPHICLASS TWinRTGenericImportS2I__3;
template<typename S1, typename S2, typename S3> class DELPHICLASS TWinRTGenericImportS3__3;
template<typename S1, typename S2, typename S3, typename I> class DELPHICLASS TWinRTGenericImportS3I__4;
template<typename S1, typename S2, typename S3, typename S4> class DELPHICLASS TWinRTGenericImportS4__4;
template<typename S1, typename S2, typename S3, typename S4, typename S5> class DELPHICLASS TWinRTGenericImportS5__5;
template<typename S1, typename S2, typename S3, typename S4, typename S5, typename S6> class DELPHICLASS TWinRTGenericImportS6__6;
template<typename S1, typename S2, typename S3, typename O> class DELPHICLASS TWinRTGenericImportS3O__4;
template<typename S, typename O> class DELPHICLASS TWinRTGenericImportSO__2;
template<typename S1, typename S2, typename O> class DELPHICLASS TWinRTGenericImportS2O__3;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWinRTException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWinRTException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWinRTException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWinRTException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWinRTException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWinRTException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWinRTException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWinRTException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWinRTException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWinRTException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWinRTException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWinRTException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWinRTException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWinRTException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInspectableObject : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	typedef System::DynamicArray<GUID> _TInspectableObject__1;
	
	
protected:
	_TInspectableObject__1 FIIDS;
	
public:
	HRESULT __stdcall GetIids(/* out */ unsigned &iidCount, /* out */ System::PGUID &iids);
	HRESULT __stdcall GetRuntimeClassName(/* out */ HSTRING &className);
	HRESULT __stdcall GetTrustLevel(/* out */ Winapi::Winrt::TrustLevel &trust);
public:
	/* TObject.Create */ inline __fastcall TInspectableObject() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInspectableObject() { }
	
private:
	void *__IInspectable;	// Winapi::Winrt::IInspectable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AF86E2E0-B12D-4C6A-9C5A-D7AA65101E90}
	operator Winapi::Winrt::_di_IInspectable()
	{
		Winapi::Winrt::_di_IInspectable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Winrt::IInspectable*(void) { return (Winapi::Winrt::IInspectable*)&__IInspectable; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TWindowsString
{
	
private:
	class DELPHICLASS TWindowsStringNexus;
#ifndef _WIN64
	#pragma pack(push,4)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TWindowsStringNexus : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		HSTRING FString;
		
	public:
		__fastcall TWindowsStringNexus(HSTRING AString);
		__fastcall virtual ~TWindowsStringNexus();
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	typedef TWindowsString *PWindowsString;
	
	
private:
	System::_di_IInterface FNexus;
	HSTRING FHandle;
	bool FValid;
	
public:
	__fastcall TWindowsString(const System::UnicodeString S)/* overload */;
	__property bool Valid = {read=FValid};
	__fastcall operator HSTRING();
	static TWindowsString __fastcall _op_Explicit(const System::UnicodeString S);
	static System::UnicodeString __fastcall HStringToString(const HSTRING hs);
	TWindowsString() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION WinRTClassNameAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FSignature;
	
public:
	__fastcall WinRTClassNameAttribute(const System::UnicodeString S);
	__property System::UnicodeString Signature = {read=FSignature};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~WinRTClassNameAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinRTImportHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Rtti::TRttiContext FContext;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	template<typename T> static GUID __fastcall GetUIID();
	__classmethod Winapi::Winrt::_di_IInspectable __fastcall GetFactoryOrStatics(System::Typinfo::PTypeInfo ATypeInfo, HSTRING &AClassName);
	__classmethod Winapi::Winrt::_di_IInspectable __fastcall CreateInstance(System::Typinfo::PTypeInfo ATypeInfo, HSTRING &AClassName);
	__classmethod HSTRING __fastcall GetClassName(System::Rtti::TRttiType* const ClassType);
	/* static */ __property System::Rtti::TRttiContext Context = {read=FContext};
public:
	/* TObject.Create */ inline __fastcall TWinRTImportHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTImportHelper() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinRTImport : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	__classmethod Winapi::Winrt::_di_IInspectable __fastcall GetFactoryOrStatics(System::Typinfo::PTypeInfo ATypeInfo, HSTRING &AClassName);
	__classmethod Winapi::Winrt::_di_IInspectable __fastcall CreateInstance(System::Typinfo::PTypeInfo ATypeInfo, HSTRING &AClassName);
public:
	/* TObject.Create */ inline __fastcall TWinRTImport() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTImport() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F> class PASCALIMPLEMENTATION TWinRTGenericImportF__1 : public TWinRTImport
{
	typedef TWinRTImport inherited;
	
private:
	static HSTRING FRTClassName;
	static F FFactory;
	static F __fastcall GetFactory();
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
	/* static */ __property F Factory = {read=GetFactory};
#ifndef _WIN64
	/* static */ __property HSTRING RTClassName = {read=FRTClassName, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING RTClassName = {read=FRTClassName};
#endif /* _WIN64 */
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportF__1() : TWinRTImport() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportF__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S> class PASCALIMPLEMENTATION TWinRTGenericImportS__1 : public TWinRTImport
{
	typedef TWinRTImport inherited;
	
private:
	static HSTRING FRTClassName;
	static S FStatics;
	static S __fastcall GetStatics();
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
#ifndef _WIN64
	/* static */ __property HSTRING RTClassName = {read=FRTClassName, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING RTClassName = {read=FRTClassName};
#endif /* _WIN64 */
	/* static */ __property S Statics = {read=GetStatics};
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS__1() : TWinRTImport() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename I> class PASCALIMPLEMENTATION TWinRTGenericImportI__1 : public TWinRTImport
{
	typedef TWinRTImport inherited;
	
private:
	static HSTRING FRTClassName;
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
	static I __fastcall Create();
#ifndef _WIN64
	/* static */ __property HSTRING RTClassName = {read=FRTClassName, nodefault};
#else /* _WIN64 */
	/* static */ __property HSTRING RTClassName = {read=FRTClassName};
#endif /* _WIN64 */
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportI__1() : TWinRTImport() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportI__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F1, typename F2> class PASCALIMPLEMENTATION TWinRTGenericImportF2__2 : public TWinRTGenericImportF__1<F1>
{
	typedef TWinRTGenericImportF__1<F1> inherited;
	
private:
	static F2 FFactory2;
	static F2 __fastcall GetFactory2();
	
public:
	/* static */ __property F2 Factory2 = {read=GetFactory2};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportF2__2() : TWinRTGenericImportF__1<F1>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportF2__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F1, typename F2, typename S> class PASCALIMPLEMENTATION TWinRTGenericImportF2S__3 : public TWinRTGenericImportF2__2<F1,F2>
{
	typedef TWinRTGenericImportF2__2<F1,F2> inherited;
	
private:
	static S FStatics;
	static S __fastcall GetStatics();
	
public:
	/* static */ __property S Statics = {read=GetStatics};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportF2S__3() : TWinRTGenericImportF2__2<F1,F2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportF2S__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F, typename S> class PASCALIMPLEMENTATION TWinRTGenericImportFS__2 : public TWinRTGenericImportF__1<F>
{
	typedef TWinRTGenericImportF__1<F> inherited;
	
private:
	static S FStatics;
	static S __fastcall GetStatics();
	
public:
	/* static */ __property S Statics = {read=GetStatics};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportFS__2() : TWinRTGenericImportF__1<F>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportFS__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportFI__2 : public TWinRTGenericImportF__1<F>
{
	typedef TWinRTGenericImportF__1<F> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportFI__2() : TWinRTGenericImportF__1<F>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportFI__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2> class PASCALIMPLEMENTATION TWinRTGenericImportS2__2 : public TWinRTGenericImportS__1<S1>
{
	typedef TWinRTGenericImportS__1<S1> inherited;
	
private:
	static S2 FStatics2;
	static S2 __fastcall GetStatics2();
	
public:
	/* static */ __property S2 Statics2 = {read=GetStatics2};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS2__2() : TWinRTGenericImportS__1<S1>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS2__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportSI__2 : public TWinRTGenericImportS__1<S>
{
	typedef TWinRTGenericImportS__1<S> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportSI__2() : TWinRTGenericImportS__1<S>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportSI__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F1, typename F2, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportF2I__3 : public TWinRTGenericImportF2__2<F1,F2>
{
	typedef TWinRTGenericImportF2__2<F1,F2> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportF2I__3() : TWinRTGenericImportF2__2<F1,F2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportF2I__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F, typename S1, typename S2> class PASCALIMPLEMENTATION TWinRTGenericImportFS2__3 : public TWinRTGenericImportFS__2<F,S1>
{
	typedef TWinRTGenericImportFS__2<F,S1> inherited;
	
private:
	static S2 FStatics2;
	static S2 __fastcall GetStatics2();
	
public:
	/* static */ __property S2 Statics2 = {read=GetStatics2};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportFS2__3() : TWinRTGenericImportFS__2<F,S1>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportFS2__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename F, typename S, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportFSI__3 : public TWinRTGenericImportFS__2<F,S>
{
	typedef TWinRTGenericImportFS__2<F,S> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportFSI__3() : TWinRTGenericImportFS__2<F,S>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportFSI__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportS2I__3 : public TWinRTGenericImportS2__2<S1,S2>
{
	typedef TWinRTGenericImportS2__2<S1,S2> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS2I__3() : TWinRTGenericImportS2__2<S1,S2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS2I__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3> class PASCALIMPLEMENTATION TWinRTGenericImportS3__3 : public TWinRTGenericImportS2__2<S1,S2>
{
	typedef TWinRTGenericImportS2__2<S1,S2> inherited;
	
private:
	static S3 FStatics3;
	static S3 __fastcall GetStatics3();
	
public:
	/* static */ __property S3 Statics3 = {read=GetStatics3};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS3__3() : TWinRTGenericImportS2__2<S1,S2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS3__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3, typename I> class PASCALIMPLEMENTATION TWinRTGenericImportS3I__4 : public TWinRTGenericImportS3__3<S1,S2,S3>
{
	typedef TWinRTGenericImportS3__3<S1,S2,S3> inherited;
	
public:
	static I __fastcall Create();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS3I__4() : TWinRTGenericImportS3__3<S1,S2,S3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS3I__4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3, typename S4> class PASCALIMPLEMENTATION TWinRTGenericImportS4__4 : public TWinRTGenericImportS3__3<S1,S2,S3>
{
	typedef TWinRTGenericImportS3__3<S1,S2,S3> inherited;
	
private:
	static S4 FStatics4;
	static S4 __fastcall GetStatics4();
	
public:
	/* static */ __property S4 Statics4 = {read=GetStatics4};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS4__4() : TWinRTGenericImportS3__3<S1,S2,S3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS4__4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3, typename S4, typename S5> class PASCALIMPLEMENTATION TWinRTGenericImportS5__5 : public TWinRTGenericImportS4__4<S1,S2,S3,S4>
{
	typedef TWinRTGenericImportS4__4<S1,S2,S3,S4> inherited;
	
private:
	static S5 FStatics5;
	static S5 __fastcall GetStatics5();
	
public:
	/* static */ __property S5 Statics5 = {read=GetStatics5};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS5__5() : TWinRTGenericImportS4__4<S1,S2,S3,S4>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS5__5() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3, typename S4, typename S5, typename S6> class PASCALIMPLEMENTATION TWinRTGenericImportS6__6 : public TWinRTGenericImportS5__5<S1,S2,S3,S4,S5>
{
	typedef TWinRTGenericImportS5__5<S1,S2,S3,S4,S5> inherited;
	
private:
	static S6 FStatics6;
	static S6 __fastcall GetStatics6();
	
public:
	/* static */ __property S6 Statics6 = {read=GetStatics6};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS6__6() : TWinRTGenericImportS5__5<S1,S2,S3,S4,S5>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS6__6() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename S3, typename O> class PASCALIMPLEMENTATION TWinRTGenericImportS3O__4 : public TWinRTGenericImportS3__3<S1,S2,S3>
{
	typedef TWinRTGenericImportS3__3<S1,S2,S3> inherited;
	
private:
	static O FInterop;
	static O __fastcall GetInterop();
	
public:
	/* static */ __property O Interop = {read=GetInterop};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS3O__4() : TWinRTGenericImportS3__3<S1,S2,S3>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS3O__4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S, typename O> class PASCALIMPLEMENTATION TWinRTGenericImportSO__2 : public TWinRTGenericImportS__1<S>
{
	typedef TWinRTGenericImportS__1<S> inherited;
	
private:
	static O FInterop;
	static O __fastcall GetInterop();
	
public:
	/* static */ __property O Interop = {read=GetInterop};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportSO__2() : TWinRTGenericImportS__1<S>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportSO__2() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename S1, typename S2, typename O> class PASCALIMPLEMENTATION TWinRTGenericImportS2O__3 : public TWinRTGenericImportS2__2<S1,S2>
{
	typedef TWinRTGenericImportS2__2<S1,S2> inherited;
	
private:
	static O FInterop;
	static O __fastcall GetInterop();
	
public:
	/* static */ __property O Interop = {read=GetInterop};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TWinRTGenericImportS2O__3() : TWinRTGenericImportS2__2<S1,S2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWinRTGenericImportS2O__3() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Winapi::Winrt::RO_INIT_TYPE RoInitType;
}	/* namespace Winrt */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_WINRT)
using namespace System::Win::Winrt;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_WinrtHPP
