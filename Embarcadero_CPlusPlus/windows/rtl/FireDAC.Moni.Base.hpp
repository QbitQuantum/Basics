// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Moni.Base.pas' rev: 34.00 (Windows)

#ifndef Firedac_Moni_BaseHPP
#define Firedac_Moni_BaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Factory.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Moni
{
namespace Base
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDMoniClientBase;
class DELPHICLASS TFDMoniClientLinkBase;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFDMoniClientBase : public Firedac::Stan::Factory::TFDObject
{
	typedef Firedac::Stan::Factory::TFDObject inherited;
	
private:
	System::Classes::TComponentName FName;
	bool FFailure;
	bool FTracing;
	Firedac::Stan::Intf::TFDMoniEventKinds FEventKinds;
	Firedac::Stan::Intf::_di_IFDMoniClientOutputHandler FOutputHandler;
	
protected:
	bool __fastcall GetTracing();
	void __fastcall SetTracing(const bool AValue);
	System::Classes::TComponentName __fastcall GetName();
	void __fastcall SetName(const System::Classes::TComponentName AValue);
	Firedac::Stan::Intf::TFDMoniEventKinds __fastcall GetEventKinds();
	void __fastcall SetEventKinds(const Firedac::Stan::Intf::TFDMoniEventKinds AValue);
	Firedac::Stan::Intf::_di_IFDMoniClientOutputHandler __fastcall GetOutputHandler();
	void __fastcall SetOutputHandler(const Firedac::Stan::Intf::_di_IFDMoniClientOutputHandler AValue);
	void __fastcall ResetFailure();
	virtual void __fastcall Notify(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, System::TObject* ASender, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	virtual unsigned __fastcall RegisterAdapter(const Firedac::Stan::Intf::_di_IFDMoniAdapter AAdapter);
	virtual void __fastcall UnregisterAdapter(const Firedac::Stan::Intf::_di_IFDMoniAdapter AAdapter);
	virtual void __fastcall AdapterChanged(const Firedac::Stan::Intf::_di_IFDMoniAdapter AAdapter);
	virtual bool __fastcall DoTracingChanged();
	virtual bool __fastcall OperationAllowed();
	void __fastcall GetObjectNames(System::TObject* ASender, /* out */ System::UnicodeString &AClassName, /* out */ System::UnicodeString &AName);
	virtual void __fastcall Finalize();
	
public:
	virtual void __fastcall Initialize();
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDMoniClientBase() : Firedac::Stan::Factory::TFDObject() { }
	/* TFDObject.Destroy */ inline __fastcall virtual ~TFDMoniClientBase() { }
	
private:
	void *__IFDMoniClient;	// Firedac::Stan::Intf::IFDMoniClient 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2005}
	operator Firedac::Stan::Intf::_di_IFDMoniClient()
	{
		Firedac::Stan::Intf::_di_IFDMoniClient intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniClient*(void) { return (Firedac::Stan::Intf::IFDMoniClient*)&__IFDMoniClient; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TFDMoniOutputEvent)(TFDMoniClientLinkBase* ASender, const System::UnicodeString AClassName, const System::UnicodeString AObjName, const System::UnicodeString AMessage);

class PASCALIMPLEMENTATION TFDMoniClientLinkBase : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Firedac::Stan::Intf::_di_IFDMoniClient FClient;
	TFDMoniOutputEvent FOnOutput;
	bool FDesignTracing;
	Firedac::Stan::Intf::TFDMoniEventKinds __fastcall GetEventKinds();
	void __fastcall SetEventKinds(const Firedac::Stan::Intf::TFDMoniEventKinds AValue);
	bool __fastcall GetTracing();
	void __fastcall SetTracing(const bool AValue);
	void __fastcall SetOnOutput(const TFDMoniOutputEvent AValue);
	
protected:
	virtual void __fastcall HandleOutput(const System::UnicodeString AClassName, const System::UnicodeString AObjName, const System::UnicodeString AMessage);
	virtual Firedac::Stan::Intf::_di_IFDMoniClient __fastcall GetMoniClient() = 0 ;
	
public:
	__fastcall virtual TFDMoniClientLinkBase(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDMoniClientLinkBase();
	virtual void __fastcall Notify(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, System::TObject* ASender, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	__property Firedac::Stan::Intf::_di_IFDMoniClient MoniClient = {read=FClient};
	__property bool Tracing = {read=GetTracing, write=SetTracing, default=0};
	
__published:
	__property Firedac::Stan::Intf::TFDMoniEventKinds EventKinds = {read=GetEventKinds, write=SetEventKinds, default=4095};
	__property TFDMoniOutputEvent OnOutput = {read=FOnOutput, write=SetOnOutput};
private:
	void *__IFDMoniClientOutputHandler;	// Firedac::Stan::Intf::IFDMoniClientOutputHandler 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2028}
	operator Firedac::Stan::Intf::_di_IFDMoniClientOutputHandler()
	{
		Firedac::Stan::Intf::_di_IFDMoniClientOutputHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniClientOutputHandler*(void) { return (Firedac::Stan::Intf::IFDMoniClientOutputHandler*)&__IFDMoniClientOutputHandler; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Base */
}	/* namespace Moni */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_MONI_BASE)
using namespace Firedac::Moni::Base;
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
#endif	// Firedac_Moni_BaseHPP
