// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinAPI.HSTRINGIterables.pas' rev: 34.00 (Windows)

#ifndef Winapi_HstringiterablesHPP
#define Winapi_HstringiterablesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <System.Generics.Collections.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Hstringiterables
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THSTRINGList;
class DELPHICLASS TIterableHSTRING;
class DELPHICLASS TIteratorHSTRING;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION THSTRINGList : public System::Generics::Collections::TList__1<HSTRING>
{
	typedef System::Generics::Collections::TList__1<HSTRING> inherited;
	
public:
	void __fastcall AddAsCopy(const HSTRING AHSTRING);
public:
	/* {System_Generics_Collections}TList<Winapi_WinRT_HSTRING>.Create */ inline __fastcall THSTRINGList()/* overload */ : System::Generics::Collections::TList__1<HSTRING>() { }
	/* {System_Generics_Collections}TList<Winapi_WinRT_HSTRING>.Create */ inline __fastcall THSTRINGList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<HSTRING> > AComparer)/* overload */ : System::Generics::Collections::TList__1<HSTRING>(AComparer) { }
	/* {System_Generics_Collections}TList<Winapi_WinRT_HSTRING>.Create */ inline __fastcall THSTRINGList(System::Generics::Collections::TEnumerable__1<HSTRING>* const Collection)/* overload */ : System::Generics::Collections::TList__1<HSTRING>(Collection) { }
	/* {System_Generics_Collections}TList<Winapi_WinRT_HSTRING>.Destroy */ inline __fastcall virtual ~THSTRINGList() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIterableHSTRING : public System::Win::Winrt::TInspectableObject
{
	typedef System::Win::Winrt::TInspectableObject inherited;
	
private:
	THSTRINGList* FList;
	
public:
	__fastcall TIterableHSTRING();
	__fastcall virtual ~TIterableHSTRING();
	HRESULT __safecall First(Winapi::Commontypes::_di_IIterator_1__HSTRING &__First_result);
	void __fastcall Add(HSTRING AValue);
private:
	void *__IIterable_1__HSTRING;	// Winapi::Commontypes::IIterable_1__HSTRING 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E2FCC7C1-3BFC-5A0B-B2B0-72E769D1CB7E}
	operator Winapi::Commontypes::_di_IIterable_1__HSTRING()
	{
		Winapi::Commontypes::_di_IIterable_1__HSTRING intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::IIterable_1__HSTRING*(void) { return (Winapi::Commontypes::IIterable_1__HSTRING*)&__IIterable_1__HSTRING; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIteratorHSTRING : public System::Win::Winrt::TInspectableObject
{
	typedef System::Win::Winrt::TInspectableObject inherited;
	
private:
	THSTRINGList* FList;
	int FIndex;
	
public:
	__fastcall TIteratorHSTRING(THSTRINGList* const AListOfHSTRING);
	__fastcall virtual ~TIteratorHSTRING();
	HRESULT __safecall MoveNext(bool &__MoveNext_result);
	HRESULT __safecall get_Current(HSTRING &__get_Current_result);
	HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result);
	HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result);
private:
	void *__IIterator_1__HSTRING;	// Winapi::Commontypes::IIterator_1__HSTRING 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8C304EBB-6615-50A4-8829-879ECD443236}
	operator Winapi::Commontypes::_di_IIterator_1__HSTRING()
	{
		Winapi::Commontypes::_di_IIterator_1__HSTRING intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Winapi::Commontypes::IIterator_1__HSTRING*(void) { return (Winapi::Commontypes::IIterator_1__HSTRING*)&__IIterator_1__HSTRING; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE HSTRING __fastcall CreateHSTRING(const System::UnicodeString S);
extern DELPHI_PACKAGE HSTRING __fastcall CreateHSTRINGRef(System::UnicodeString &S);
extern DELPHI_PACKAGE System::UnicodeString __fastcall HSTRINGToString(const HSTRING hs);
extern DELPHI_PACKAGE bool __fastcall HSTRINGIsNullOrEmpty(const HSTRING hs);
extern DELPHI_PACKAGE void __fastcall DeleteHSTRING(const HSTRING hs);
}	/* namespace Hstringiterables */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_HSTRINGITERABLES)
using namespace Winapi::Hstringiterables;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_HstringiterablesHPP
