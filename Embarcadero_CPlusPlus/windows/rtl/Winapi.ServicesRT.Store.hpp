// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ServicesRT.Store.pas' rev: 34.00 (Windows)

#ifndef Winapi_Servicesrt_StoreHPP
#define Winapi_Servicesrt_StoreHPP

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
namespace Servicesrt
{
namespace Store
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__IStoreImage_Base;
typedef System::DelphiInterface<IIterator_1__IStoreImage_Base> _di_IIterator_1__IStoreImage_Base;
__interface DELPHIINTERFACE IIterator_1__IStoreImage;
typedef System::DelphiInterface<IIterator_1__IStoreImage> _di_IIterator_1__IStoreImage;
__interface DELPHIINTERFACE IIterable_1__IStoreImage_Base;
typedef System::DelphiInterface<IIterable_1__IStoreImage_Base> _di_IIterable_1__IStoreImage_Base;
__interface DELPHIINTERFACE IIterable_1__IStoreImage;
typedef System::DelphiInterface<IIterable_1__IStoreImage> _di_IIterable_1__IStoreImage;
__interface DELPHIINTERFACE IIterator_1__IStoreVideo_Base;
typedef System::DelphiInterface<IIterator_1__IStoreVideo_Base> _di_IIterator_1__IStoreVideo_Base;
__interface DELPHIINTERFACE IIterator_1__IStoreVideo;
typedef System::DelphiInterface<IIterator_1__IStoreVideo> _di_IIterator_1__IStoreVideo;
__interface DELPHIINTERFACE IIterable_1__IStoreVideo_Base;
typedef System::DelphiInterface<IIterable_1__IStoreVideo_Base> _di_IIterable_1__IStoreVideo_Base;
__interface DELPHIINTERFACE IIterable_1__IStoreVideo;
typedef System::DelphiInterface<IIterable_1__IStoreVideo> _di_IIterable_1__IStoreVideo;
__interface DELPHIINTERFACE IIterator_1__IStoreAvailability_Base;
typedef System::DelphiInterface<IIterator_1__IStoreAvailability_Base> _di_IIterator_1__IStoreAvailability_Base;
__interface DELPHIINTERFACE IIterator_1__IStoreAvailability;
typedef System::DelphiInterface<IIterator_1__IStoreAvailability> _di_IIterator_1__IStoreAvailability;
__interface DELPHIINTERFACE IIterable_1__IStoreAvailability_Base;
typedef System::DelphiInterface<IIterable_1__IStoreAvailability_Base> _di_IIterable_1__IStoreAvailability_Base;
__interface DELPHIINTERFACE IIterable_1__IStoreAvailability;
typedef System::DelphiInterface<IIterable_1__IStoreAvailability> _di_IIterable_1__IStoreAvailability;
__interface DELPHIINTERFACE IIterator_1__IStoreSku_Base;
typedef System::DelphiInterface<IIterator_1__IStoreSku_Base> _di_IIterator_1__IStoreSku_Base;
__interface DELPHIINTERFACE IIterator_1__IStoreSku;
typedef System::DelphiInterface<IIterator_1__IStoreSku> _di_IIterator_1__IStoreSku;
__interface DELPHIINTERFACE IIterable_1__IStoreSku_Base;
typedef System::DelphiInterface<IIterable_1__IStoreSku_Base> _di_IIterable_1__IStoreSku_Base;
__interface DELPHIINTERFACE IIterable_1__IStoreSku;
typedef System::DelphiInterface<IIterable_1__IStoreSku> _di_IIterable_1__IStoreSku;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IStoreProduct;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IStoreProduct> _di_IKeyValuePair_2__HSTRING__IStoreProduct;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct> _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct> _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IStoreLicense;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IStoreLicense> _di_IKeyValuePair_2__HSTRING__IStoreLicense;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense> _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense> _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense;
__interface DELPHIINTERFACE IIterator_1__StorePackageUpdateStatus_Base;
typedef System::DelphiInterface<IIterator_1__StorePackageUpdateStatus_Base> _di_IIterator_1__StorePackageUpdateStatus_Base;
__interface DELPHIINTERFACE IIterator_1__StorePackageUpdateStatus;
typedef System::DelphiInterface<IIterator_1__StorePackageUpdateStatus> _di_IIterator_1__StorePackageUpdateStatus;
__interface DELPHIINTERFACE IIterable_1__StorePackageUpdateStatus_Base;
typedef System::DelphiInterface<IIterable_1__StorePackageUpdateStatus_Base> _di_IIterable_1__StorePackageUpdateStatus_Base;
__interface DELPHIINTERFACE IIterable_1__StorePackageUpdateStatus;
typedef System::DelphiInterface<IIterable_1__StorePackageUpdateStatus> _di_IIterable_1__StorePackageUpdateStatus;
__interface DELPHIINTERFACE IStoreContextStatics;
typedef System::DelphiInterface<IStoreContextStatics> _di_IStoreContextStatics;
__interface DELPHIINTERFACE IStoreContext2;
typedef System::DelphiInterface<IStoreContext2> _di_IStoreContext2;
class DELPHICLASS TStoreContext;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__IStoreImage *PIIterator_1__IStoreImage;

typedef _di_IIterable_1__IStoreImage *PIIterable_1__IStoreImage;

typedef _di_IIterator_1__IStoreVideo *PIIterator_1__IStoreVideo;

typedef _di_IIterable_1__IStoreVideo *PIIterable_1__IStoreVideo;

typedef _di_IIterator_1__IStoreAvailability *PIIterator_1__IStoreAvailability;

typedef _di_IIterable_1__IStoreAvailability *PIIterable_1__IStoreAvailability;

typedef _di_IIterator_1__IStoreSku *PIIterator_1__IStoreSku;

typedef _di_IIterable_1__IStoreSku *PIIterable_1__IStoreSku;

typedef _di_IKeyValuePair_2__HSTRING__IStoreProduct *PIKeyValuePair_2__HSTRING__IStoreProduct;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct *PIIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct *PIIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct;

typedef _di_IKeyValuePair_2__HSTRING__IStoreLicense *PIKeyValuePair_2__HSTRING__IStoreLicense;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense *PIIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense *PIIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense;

typedef _di_IIterator_1__StorePackageUpdateStatus *PIIterator_1__StorePackageUpdateStatus;

typedef _di_IIterable_1__StorePackageUpdateStatus *PIIterable_1__StorePackageUpdateStatus;

typedef _di_IStoreContextStatics *PIStoreContextStatics;

typedef _di_IStoreContext2 *PIStoreContext2;

__interface  INTERFACE_UUID("{FBE076F6-C3D2-5DF7-839F-012AC0F951C5}") IIterator_1__IStoreImage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C172A6FB-2505-5706-BCB1-9D75E14AC85C}") IIterator_1__IStoreImage  : public IIterator_1__IStoreImage_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IStoreImage &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIStoreImage items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreImage _scw_get_Current() { Winapi::Commontypes::_di_IStoreImage __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreImage Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{B2DA6DE8-AD55-56CE-8754-2C96F4FE1C2E}") IIterable_1__IStoreImage_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{01D22578-8616-5728-A0FF-7E486F3A9C4D}") IIterable_1__IStoreImage  : public IIterable_1__IStoreImage_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IStoreImage &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{91B0B554-A537-5E22-B39F-6A935D0BEF45}") IIterator_1__IStoreVideo_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{8AAEEAB6-7651-5658-8601-6553F357697F}") IIterator_1__IStoreVideo  : public IIterator_1__IStoreVideo_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IStoreVideo &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIStoreVideo items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreVideo _scw_get_Current() { Winapi::Commontypes::_di_IStoreVideo __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreVideo Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{46BE61E4-7173-565E-AED5-4A2152F1CE69}") IIterable_1__IStoreVideo_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{9D74B863-34A8-5D61-8782-4F2AB3528D08}") IIterable_1__IStoreVideo  : public IIterable_1__IStoreVideo_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IStoreVideo &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{50511CCB-089E-5B73-BB4A-4D1EF77B8F0F}") IIterator_1__IStoreAvailability_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{381E2DFF-80C3-5CC8-AD28-2C0F87720026}") IIterator_1__IStoreAvailability  : public IIterator_1__IStoreAvailability_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IStoreAvailability &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIStoreAvailability items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreAvailability _scw_get_Current() { Winapi::Commontypes::_di_IStoreAvailability __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreAvailability Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{C58DE1A0-25DE-578B-BB69-E0A26D67B203}") IIterable_1__IStoreAvailability_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{9EA2B48F-FF9D-5850-876D-CEE55741FA56}") IIterable_1__IStoreAvailability  : public IIterable_1__IStoreAvailability_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IStoreAvailability &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{365CDE92-7FE3-59D5-B8F8-8F05ACF50947}") IIterator_1__IStoreSku_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{85F25C19-9E41-5A04-8324-E7B0F04595F0}") IIterator_1__IStoreSku  : public IIterator_1__IStoreSku_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IStoreSku &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIStoreSku items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreSku _scw_get_Current() { Winapi::Commontypes::_di_IStoreSku __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreSku Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{522D34EF-4B5A-5B44-A046-7A16051D011E}") IIterable_1__IStoreSku_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0A9BDF4A-25BF-5C9C-A798-121849885E96}") IIterable_1__IStoreSku  : public IIterable_1__IStoreSku_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IStoreSku &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{7649AE79-029E-51E4-AE99-7E3AB8D9EC53}") IKeyValuePair_2__HSTRING__IStoreProduct  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IStoreProduct &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreProduct _scw_get_Value() { Winapi::Commontypes::_di_IStoreProduct __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreProduct Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{0EDB142C-9D04-532B-81E9-4C84AB09B34B}") IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{9EDA8AB5-7E61-5DF9-9D15-E8AED01A7EB6}") IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct  : public IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IStoreProduct &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IStoreProduct items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IStoreProduct _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IStoreProduct __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IStoreProduct Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{78A33722-ABFB-57C0-853F-5616A3AB8D57}") IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F0188E6C-4198-535A-9600-DF68157D5718}") IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct  : public IIterable_1__IKeyValuePair_2__HSTRING__IStoreProduct_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreProduct &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{CEB25B50-83EF-5774-B16E-4BB96C6E4C65}") IKeyValuePair_2__HSTRING__IStoreLicense  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IStoreLicense &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IStoreLicense _scw_get_Value() { Winapi::Commontypes::_di_IStoreLicense __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IStoreLicense Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{A1509348-6522-5062-AE86-CF595475926D}") IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{204D492F-1E5B-50CD-AF8A-CEADCE5B568D}") IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense  : public IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IStoreLicense &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IStoreLicense items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IStoreLicense _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IStoreLicense __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IStoreLicense Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{CA8BA445-6F4D-5DA9-95EE-42CF118DEF63}") IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2641BCF5-1955-560D-9665-96894F3EB16C}") IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense  : public IIterable_1__IKeyValuePair_2__HSTRING__IStoreLicense_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IStoreLicense &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{6181D84F-F731-57B8-9A6B-8A12FCD58D04}") IIterator_1__StorePackageUpdateStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__StorePackageUpdateStatus  : public IIterator_1__StorePackageUpdateStatus_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::StorePackageUpdateStatus &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PStorePackageUpdateStatus items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::StorePackageUpdateStatus _scw_get_Current() { Winapi::Commontypes::StorePackageUpdateStatus __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::StorePackageUpdateStatus Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{60832223-7EB4-5CD7-8340-F5077173D364}") IIterable_1__StorePackageUpdateStatus_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__StorePackageUpdateStatus  : public IIterable_1__StorePackageUpdateStatus_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__StorePackageUpdateStatus &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9C06EE5F-15C0-4E72-9330-D6191CEBD19C}") IStoreContextStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefault(Winapi::Commontypes::_di_IStoreContext &__GetDefault_result) = 0 ;
	virtual HRESULT __safecall GetForUser(Winapi::Commontypes::_di_IUser user, Winapi::Commontypes::_di_IStoreContext &__GetForUser_result) = 0 ;
};

__interface  INTERFACE_UUID("{18BC54DA-7BD9-452C-9116-3BBD06FFC63A}") IStoreContext2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FindStoreProductForPackageAsync(Winapi::Commontypes::_di_IIterable_1__HSTRING productKinds, Winapi::Commontypes::_di_IPackage package, Winapi::Commontypes::_di_IAsyncOperation_1__IStoreProductResult &__FindStoreProductForPackageAsync_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TStoreContext : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IStoreContextStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IStoreContextStatics> inherited;
	
public:
	static Winapi::Commontypes::_di_IStoreContext __fastcall GetDefault();
	static Winapi::Commontypes::_di_IStoreContext __fastcall GetForUser(Winapi::Commontypes::_di_IUser user);
public:
	/* TObject.Create */ inline __fastcall TStoreContext() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IStoreContextStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStoreContext() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Store */
}	/* namespace Servicesrt */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Servicesrt_StoreHPP
