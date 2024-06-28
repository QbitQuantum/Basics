// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgeListeners.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgelistenersHPP
#define Emshosting_EdgelistenersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <EMSHosting.EdgeService.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.EdgeListeners"

namespace Emshosting
{
namespace Edgelisteners
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSEdgeListenerFactory;
class DELPHICLASS TEMSEdgeListenerFactories;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEdgeListenerFactory : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual Emshosting::Edgeservice::TEMSEdgeListener* __fastcall DoCreateListener(System::Classes::TComponent* const AOwner, const System::UnicodeString AProtocolName) = 0 ;
	
public:
	Emshosting::Edgeservice::TEMSEdgeListener* __fastcall CreateListener(System::Classes::TComponent* const AOwner, const System::UnicodeString AProtocolName);
public:
	/* TObject.Create */ inline __fastcall TEMSEdgeListenerFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEMSEdgeListenerFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMSEdgeListenerFactories : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,TEMSEdgeListenerFactory*> TProtocolPair;
	
	
private:
	static TEMSEdgeListenerFactories* FInstance;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FUnitNames;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TEMSEdgeListenerFactory*>* FItems;
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetNames();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetNames();
#endif /* _WIN64 */
	
public:
	__fastcall TEMSEdgeListenerFactories();
	__fastcall virtual ~TEMSEdgeListenerFactories();
	void __fastcall Add(const System::UnicodeString AProtocolName, const System::UnicodeString AUnitName, TEMSEdgeListenerFactory* const AFactory);
	void __fastcall Remove(const System::UnicodeString AName);
	bool __fastcall TryGetFactory(const System::UnicodeString AName, /* out */ TEMSEdgeListenerFactory* &AFactory);
	bool __fastcall TryGetUnitName(const System::UnicodeString AName, /* out */ System::UnicodeString &AUnitName);
#ifndef _WIN64
	__property System::DynamicArray<System::UnicodeString> Names = {read=GetNames};
#else /* _WIN64 */
	__property System::TArray__1<System::UnicodeString> Names = {read=GetNames};
#endif /* _WIN64 */
	/* static */ __property TEMSEdgeListenerFactories* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Edgelisteners */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGELISTENERS)
using namespace Emshosting::Edgelisteners;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgelistenersHPP
