// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Factory.pas' rev: 34.00 (iOS)

#ifndef Fmx_Presentation_FactoryHPP
#define Fmx_Presentation_FactoryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Factory
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EPresentationProxy;
class DELPHICLASS TPresentationProxyFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EPresentationProxy : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPresentationProxy(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPresentationProxy(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPresentationProxy(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPresentationProxy(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPresentationProxy(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPresentationProxy(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPresentationProxy(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPresentationProxy(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPresentationProxy(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPresentationProxy(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPresentationProxy(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPresentationProxy(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPresentationProxy() { }
	
};


typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,Fmx::Controls::Presentation::TPresentationProxyClass>* TPresentationDictionary;

class PASCALIMPLEMENTATION TPresentationProxyFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Fmx::Controls::Presentation::TPresentationProxyClass>* FPresentations;
	static TPresentationProxyFactory* FCurrent;
	static TPresentationProxyFactory* __fastcall GetCurrent();
	System::UnicodeString __fastcall NormalizePresentationName(const System::UnicodeString APresentationName);
	
public:
	__fastcall TPresentationProxyFactory();
	__fastcall virtual ~TPresentationProxyFactory();
	
private:
	// __classmethod void __fastcall DestroyDefault@();
	
public:
	__classmethod System::UnicodeString __fastcall GeneratePresentationName(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType);
	__classmethod System::UnicodeString __fastcall GenerateDefaultPresentationName(const Fmx::Controls::TControlType AControlType);
	void __fastcall Register(const System::UnicodeString APresentationName, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	void __fastcall RegisterDefault(const Fmx::Controls::TControlType AControlType, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass);
	void __fastcall Register(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	void __fastcall UnregisterDefault(const Fmx::Controls::TControlType AControlType);
	void __fastcall Unregister(const System::UnicodeString APresentationName)/* overload */;
	void __fastcall Unregister(const System::UnicodeString APresentationName, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	void __fastcall Unregister(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType)/* overload */;
	void __fastcall Unregister(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	void __fastcall Replace(const System::UnicodeString APresentationName, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	void __fastcall Replace(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType, const Fmx::Controls::Presentation::TPresentationProxyClass APresentationProxyClass)/* overload */;
	bool __fastcall Supported(const System::UnicodeString APresentationName)/* overload */;
	bool __fastcall Supported(const System::TClass AControlClass, const Fmx::Controls::TControlType AControlType)/* overload */;
	template<typename T> T __fastcall CreatePresentationProxy(const System::UnicodeString APresentationName);
	Fmx::Controls::Presentation::TPresentationProxyClass __fastcall FindPresentationProxyClass(const System::UnicodeString APresentationName);
	/* static */ __property TPresentationProxyFactory* Current = {read=GetCurrent};
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,Fmx::Controls::Presentation::TPresentationProxyClass>* Presentations = {read=FPresentations};
	
private:
	// __classmethod void __fastcall Create@();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Factory */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_FACTORY)
using namespace Fmx::Presentation::Factory;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION)
using namespace Fmx::Presentation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Presentation_FactoryHPP
