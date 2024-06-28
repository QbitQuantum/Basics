// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ApplicationModel.Contacts.pas' rev: 34.00 (Windows)

#ifndef Winapi_Applicationmodel_ContactsHPP
#define Winapi_Applicationmodel_ContactsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Applicationmodel
{
namespace Contacts
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__ContactFieldType_Base;
typedef System::DelphiInterface<IIterator_1__ContactFieldType_Base> _di_IIterator_1__ContactFieldType_Base;
__interface DELPHIINTERFACE IIterator_1__ContactFieldType;
typedef System::DelphiInterface<IIterator_1__ContactFieldType> _di_IIterator_1__ContactFieldType;
__interface DELPHIINTERFACE IIterable_1__ContactFieldType_Base;
typedef System::DelphiInterface<IIterable_1__ContactFieldType_Base> _di_IIterable_1__ContactFieldType_Base;
__interface DELPHIINTERFACE IIterable_1__ContactFieldType;
typedef System::DelphiInterface<IIterable_1__ContactFieldType> _di_IIterable_1__ContactFieldType;
__interface DELPHIINTERFACE IVectorView_1__ContactFieldType;
typedef System::DelphiInterface<IVectorView_1__ContactFieldType> _di_IVectorView_1__ContactFieldType;
__interface DELPHIINTERFACE IVector_1__ContactFieldType;
typedef System::DelphiInterface<IVector_1__ContactFieldType> _di_IVector_1__ContactFieldType;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__ContactFieldType *PIIterator_1__ContactFieldType;

typedef _di_IIterable_1__ContactFieldType *PIIterable_1__ContactFieldType;

typedef _di_IVectorView_1__ContactFieldType *PIVectorView_1__ContactFieldType;

typedef _di_IVector_1__ContactFieldType *PIVector_1__ContactFieldType;

__interface  INTERFACE_UUID("{2F6D856A-50D4-5173-ABEA-DB6C6B8FC530}") IIterator_1__ContactFieldType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__ContactFieldType  : public IIterator_1__ContactFieldType_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::ContactFieldType &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PContactFieldType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ContactFieldType _scw_get_Current() { Winapi::Commontypes::ContactFieldType __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ContactFieldType Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{384B8B1B-CE8E-5781-B3DC-0776D684F658}") IIterable_1__ContactFieldType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__ContactFieldType  : public IIterable_1__ContactFieldType_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ContactFieldType &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__ContactFieldType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::ContactFieldType &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::ContactFieldType value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PContactFieldType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A4739064-B54E-55D4-8012-317E2B6A807B}") IVector_1__ContactFieldType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::ContactFieldType &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ContactFieldType &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::ContactFieldType value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::ContactFieldType value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::ContactFieldType value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::ContactFieldType value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PContactFieldType items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PContactFieldType items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Contacts */
}	/* namespace Applicationmodel */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Applicationmodel_ContactsHPP
