// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.Custom.pas' rev: 34.00 (Android)

#ifndef Firedac_Moni_CustomHPP
#define Firedac_Moni_CustomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Moni.Base.hpp>
#include <FireDAC.Stan.Factory.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Moni
{
namespace Custom
{
  _INIT_UNIT(Firedac_Moni_Custom);
}	/* namespace Custom */
}	/* namespace Moni */
}	/* namespace Firedac */

namespace Firedac
{
namespace Moni
{
namespace Custom
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMoniCustomClientLink;
class DELPHICLASS TFDMoniCustomClient;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDMoniCustomClientLink : public Firedac::Moni::Base::TFDMoniClientLinkBase
{
	typedef Firedac::Moni::Base::TFDMoniClientLinkBase inherited;
	
private:
	Firedac::Stan::Intf::_di_IFDMoniCustomClient FCClient;
	bool __fastcall GetSynchronize();
	void __fastcall SetSynchronize(bool AValue);
	
protected:
	virtual Firedac::Stan::Intf::_di_IFDMoniClient __fastcall GetMoniClient();
	
public:
	__fastcall virtual TFDMoniCustomClientLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDMoniCustomClientLink();
	__property Firedac::Stan::Intf::_di_IFDMoniCustomClient CClient = {read=FCClient};
	
__published:
	__property Tracing = {default=0};
	__property bool Synchronize = {read=GetSynchronize, write=SetSynchronize, default=0};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDMoniCustomClient : public Firedac::Moni::Base::TFDMoniClientBase
{
	typedef Firedac::Moni::Base::TFDMoniClientBase inherited;
	
private:
	int FLevel;
	bool FSynchronize;
	
protected:
	virtual void __fastcall Notify(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, System::TObject* ASender, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	bool __fastcall GetSynchronize();
	void __fastcall SetSynchronize(bool AValue);
	virtual bool __fastcall DoTracingChanged();
	virtual void __fastcall DoTraceMsg(const System::UnicodeString AClassName, const System::UnicodeString AObjName, const System::UnicodeString AMessage);
	
public:
	__fastcall virtual ~TFDMoniCustomClient();
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDMoniCustomClient() : Firedac::Moni::Base::TFDMoniClientBase() { }
	
private:
	void *__IFDMoniCustomClient;	// Firedac::Stan::Intf::IFDMoniCustomClient 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2030}
	operator Firedac::Stan::Intf::_di_IFDMoniCustomClient()
	{
		Firedac::Stan::Intf::_di_IFDMoniCustomClient intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniCustomClient*(void) { return (Firedac::Stan::Intf::IFDMoniCustomClient*)&__IFDMoniCustomClient; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Custom */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_CUSTOM)
using namespace Firedac::Moni::Custom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI)
using namespace Firedac::Moni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Moni_CustomHPP
