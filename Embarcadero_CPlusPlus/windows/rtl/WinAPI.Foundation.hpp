// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Foundation.pas' rev: 34.00 (Windows)

#ifndef Winapi_FoundationHPP
#define Winapi_FoundationHPP

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
#include <Winapi.Foundation.Types.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Foundation
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAsyncInfo;
typedef System::DelphiInterface<IAsyncInfo> _di_IAsyncInfo;
__interface DELPHIINTERFACE IWwwFormUrlDecoderEntry;
typedef System::DelphiInterface<IWwwFormUrlDecoderEntry> _di_IWwwFormUrlDecoderEntry;
__interface DELPHIINTERFACE IIterator_1__IWwwFormUrlDecoderEntry_Base;
typedef System::DelphiInterface<IIterator_1__IWwwFormUrlDecoderEntry_Base> _di_IIterator_1__IWwwFormUrlDecoderEntry_Base;
__interface DELPHIINTERFACE IIterator_1__IWwwFormUrlDecoderEntry;
typedef System::DelphiInterface<IIterator_1__IWwwFormUrlDecoderEntry> _di_IIterator_1__IWwwFormUrlDecoderEntry;
__interface DELPHIINTERFACE IIterable_1__IWwwFormUrlDecoderEntry_Base;
typedef System::DelphiInterface<IIterable_1__IWwwFormUrlDecoderEntry_Base> _di_IIterable_1__IWwwFormUrlDecoderEntry_Base;
__interface DELPHIINTERFACE IIterable_1__IWwwFormUrlDecoderEntry;
typedef System::DelphiInterface<IIterable_1__IWwwFormUrlDecoderEntry> _di_IIterable_1__IWwwFormUrlDecoderEntry;
__interface DELPHIINTERFACE IClosable;
typedef System::DelphiInterface<IClosable> _di_IClosable;
__interface DELPHIINTERFACE IPropertyValue;
typedef System::DelphiInterface<IPropertyValue> _di_IPropertyValue;
__interface DELPHIINTERFACE IMemoryBufferReference;
typedef System::DelphiInterface<IMemoryBufferReference> _di_IMemoryBufferReference;
__interface DELPHIINTERFACE IMemoryBuffer;
typedef System::DelphiInterface<IMemoryBuffer> _di_IMemoryBuffer;
__interface DELPHIINTERFACE IReference_1__Rect;
typedef System::DelphiInterface<IReference_1__Rect> _di_IReference_1__Rect;
__interface DELPHIINTERFACE IGetActivationFactory;
typedef System::DelphiInterface<IGetActivationFactory> _di_IGetActivationFactory;
__interface DELPHIINTERFACE IIterator_1__Size_Base;
typedef System::DelphiInterface<IIterator_1__Size_Base> _di_IIterator_1__Size_Base;
__interface DELPHIINTERFACE IIterator_1__Size;
typedef System::DelphiInterface<IIterator_1__Size> _di_IIterator_1__Size;
__interface DELPHIINTERFACE IIterable_1__Size_Base;
typedef System::DelphiInterface<IIterable_1__Size_Base> _di_IIterable_1__Size_Base;
__interface DELPHIINTERFACE IIterable_1__Size;
typedef System::DelphiInterface<IIterable_1__Size> _di_IIterable_1__Size;
__interface DELPHIINTERFACE IVectorView_1__Size;
typedef System::DelphiInterface<IVectorView_1__Size> _di_IVectorView_1__Size;
__interface DELPHIINTERFACE IPropertyValueStatics;
typedef System::DelphiInterface<IPropertyValueStatics> _di_IPropertyValueStatics;
__interface DELPHIINTERFACE IStringable;
typedef System::DelphiInterface<IStringable> _di_IStringable;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IInspectable> _di_IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IInspectable_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IInspectable_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IInspectable> _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IInspectable_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IInspectable_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IInspectable> _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IMap_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IMap_2__HSTRING__IInspectable> _di_IMap_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IMapChangedEventArgs_1__HSTRING;
typedef System::DelphiInterface<IMapChangedEventArgs_1__HSTRING> _di_IMapChangedEventArgs_1__HSTRING;
__interface DELPHIINTERFACE MapChangedEventHandler_2__HSTRING__IInspectable_Delegate_Base;
typedef System::DelphiInterface<MapChangedEventHandler_2__HSTRING__IInspectable_Delegate_Base> _di_MapChangedEventHandler_2__HSTRING__IInspectable_Delegate_Base;
__interface DELPHIINTERFACE MapChangedEventHandler_2__HSTRING__IInspectable;
typedef System::DelphiInterface<MapChangedEventHandler_2__HSTRING__IInspectable> _di_MapChangedEventHandler_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IObservableMap_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IObservableMap_2__HSTRING__IInspectable> _di_IObservableMap_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE DeferralCompletedHandler;
typedef System::DelphiInterface<DeferralCompletedHandler> _di_DeferralCompletedHandler;
__interface DELPHIINTERFACE IDeferralFactory;
typedef System::DelphiInterface<IDeferralFactory> _di_IDeferralFactory;
__interface DELPHIINTERFACE TypedEventHandler_2__IMemoryBufferReference__IInspectable_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IMemoryBufferReference__IInspectable_Delegate_Base> _di_TypedEventHandler_2__IMemoryBufferReference__IInspectable_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IMemoryBufferReference__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__IMemoryBufferReference__IInspectable> _di_TypedEventHandler_2__IMemoryBufferReference__IInspectable;
__interface DELPHIINTERFACE IUriRuntimeClassWithAbsoluteCanonicalUri;
typedef System::DelphiInterface<IUriRuntimeClassWithAbsoluteCanonicalUri> _di_IUriRuntimeClassWithAbsoluteCanonicalUri;
__interface DELPHIINTERFACE IUriEscapeStatics;
typedef System::DelphiInterface<IUriEscapeStatics> _di_IUriEscapeStatics;
__interface DELPHIINTERFACE IUriRuntimeClassFactory;
typedef System::DelphiInterface<IUriRuntimeClassFactory> _di_IUriRuntimeClassFactory;
__interface DELPHIINTERFACE IWwwFormUrlDecoderRuntimeClassFactory;
typedef System::DelphiInterface<IWwwFormUrlDecoderRuntimeClassFactory> _di_IWwwFormUrlDecoderRuntimeClassFactory;
__interface DELPHIINTERFACE IReference_1__Numerics_Matrix4x4;
typedef System::DelphiInterface<IReference_1__Numerics_Matrix4x4> _di_IReference_1__Numerics_Matrix4x4;
__interface DELPHIINTERFACE IIterator_1__IClosable;
typedef System::DelphiInterface<IIterator_1__IClosable> _di_IIterator_1__IClosable;
__interface DELPHIINTERFACE IIterable_1__IClosable;
typedef System::DelphiInterface<IIterable_1__IClosable> _di_IIterable_1__IClosable;
__interface DELPHIINTERFACE IVectorView_1__IClosable;
typedef System::DelphiInterface<IVectorView_1__IClosable> _di_IVectorView_1__IClosable;
__interface DELPHIINTERFACE IVector_1__IClosable;
typedef System::DelphiInterface<IVector_1__IClosable> _di_IVector_1__IClosable;
__interface DELPHIINTERFACE IIterator_1__IUriRuntimeClass_Base;
typedef System::DelphiInterface<IIterator_1__IUriRuntimeClass_Base> _di_IIterator_1__IUriRuntimeClass_Base;
__interface DELPHIINTERFACE IIterator_1__IUriRuntimeClass;
typedef System::DelphiInterface<IIterator_1__IUriRuntimeClass> _di_IIterator_1__IUriRuntimeClass;
__interface DELPHIINTERFACE IIterable_1__IUriRuntimeClass_Base;
typedef System::DelphiInterface<IIterable_1__IUriRuntimeClass_Base> _di_IIterable_1__IUriRuntimeClass_Base;
__interface DELPHIINTERFACE IIterable_1__IUriRuntimeClass;
typedef System::DelphiInterface<IIterable_1__IUriRuntimeClass> _di_IIterable_1__IUriRuntimeClass;
__interface DELPHIINTERFACE IIterator_1__TimeSpan_Base;
typedef System::DelphiInterface<IIterator_1__TimeSpan_Base> _di_IIterator_1__TimeSpan_Base;
__interface DELPHIINTERFACE IIterator_1__TimeSpan;
typedef System::DelphiInterface<IIterator_1__TimeSpan> _di_IIterator_1__TimeSpan;
__interface DELPHIINTERFACE IIterable_1__TimeSpan_Base;
typedef System::DelphiInterface<IIterable_1__TimeSpan_Base> _di_IIterable_1__TimeSpan_Base;
__interface DELPHIINTERFACE IIterable_1__TimeSpan;
typedef System::DelphiInterface<IIterable_1__TimeSpan> _di_IIterable_1__TimeSpan;
__interface DELPHIINTERFACE IVectorView_1__IUriRuntimeClass;
typedef System::DelphiInterface<IVectorView_1__IUriRuntimeClass> _di_IVectorView_1__IUriRuntimeClass;
__interface DELPHIINTERFACE IVector_1__IUriRuntimeClass;
typedef System::DelphiInterface<IVector_1__IUriRuntimeClass> _di_IVector_1__IUriRuntimeClass;
__interface DELPHIINTERFACE IReference_1__Point;
typedef System::DelphiInterface<IReference_1__Point> _di_IReference_1__Point;
__interface DELPHIINTERFACE IIterator_1__DateTime_Base;
typedef System::DelphiInterface<IIterator_1__DateTime_Base> _di_IIterator_1__DateTime_Base;
__interface DELPHIINTERFACE IIterator_1__DateTime;
typedef System::DelphiInterface<IIterator_1__DateTime> _di_IIterator_1__DateTime;
__interface DELPHIINTERFACE IIterable_1__DateTime_Base;
typedef System::DelphiInterface<IIterable_1__DateTime_Base> _di_IIterable_1__DateTime_Base;
__interface DELPHIINTERFACE IIterable_1__DateTime;
typedef System::DelphiInterface<IIterable_1__DateTime> _di_IIterable_1__DateTime;
__interface DELPHIINTERFACE IVectorView_1__DateTime;
typedef System::DelphiInterface<IVectorView_1__DateTime> _di_IVectorView_1__DateTime;
__interface DELPHIINTERFACE IVector_1__DateTime;
typedef System::DelphiInterface<IVector_1__DateTime> _di_IVector_1__DateTime;
__interface DELPHIINTERFACE IIterator_1__IIterable_1__Point_Base;
typedef System::DelphiInterface<IIterator_1__IIterable_1__Point_Base> _di_IIterator_1__IIterable_1__Point_Base;
__interface DELPHIINTERFACE IIterator_1__IIterable_1__Point;
typedef System::DelphiInterface<IIterator_1__IIterable_1__Point> _di_IIterator_1__IIterable_1__Point;
__interface DELPHIINTERFACE IIterable_1__IIterable_1__Point_Base;
typedef System::DelphiInterface<IIterable_1__IIterable_1__Point_Base> _di_IIterable_1__IIterable_1__Point_Base;
__interface DELPHIINTERFACE IIterable_1__IIterable_1__Point;
typedef System::DelphiInterface<IIterable_1__IIterable_1__Point> _di_IIterable_1__IIterable_1__Point;
__interface DELPHIINTERFACE IVectorView_1__Point;
typedef System::DelphiInterface<IVectorView_1__Point> _di_IVectorView_1__Point;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IReference_1__DateTime_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IReference_1__DateTime_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IReference_1__DateTime;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IReference_1__DateTime> _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime;
__interface DELPHIINTERFACE IAsyncOperation_1__IReference_1__DateTime_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IReference_1__DateTime_Base> _di_IAsyncOperation_1__IReference_1__DateTime_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IReference_1__DateTime;
typedef System::DelphiInterface<IAsyncOperation_1__IReference_1__DateTime> _di_IAsyncOperation_1__IReference_1__DateTime;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IReference_1__TimeSpan_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IReference_1__TimeSpan_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IReference_1__TimeSpan;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IReference_1__TimeSpan> _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan;
__interface DELPHIINTERFACE IAsyncOperation_1__IReference_1__TimeSpan_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IReference_1__TimeSpan_Base> _di_IAsyncOperation_1__IReference_1__TimeSpan_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IReference_1__TimeSpan;
typedef System::DelphiInterface<IAsyncOperation_1__IReference_1__TimeSpan> _di_IAsyncOperation_1__IReference_1__TimeSpan;
__interface DELPHIINTERFACE IReference_1__Numerics_Vector3;
typedef System::DelphiInterface<IReference_1__Numerics_Vector3> _di_IReference_1__Numerics_Vector3;
__interface DELPHIINTERFACE IReference_1__Numerics_Vector2;
typedef System::DelphiInterface<IReference_1__Numerics_Vector2> _di_IReference_1__Numerics_Vector2;
__interface DELPHIINTERFACE IReference_1__Numerics_Quaternion;
typedef System::DelphiInterface<IReference_1__Numerics_Quaternion> _di_IReference_1__Numerics_Quaternion;
class DELPHICLASS TPropertyValue;
class DELPHICLASS TDeferral;
class DELPHICLASS TWwwFormUrlDecoder;
class DELPHICLASS TUri;
//-- type declarations -------------------------------------------------------
typedef _di_IAsyncInfo *PIAsyncInfo;

typedef _di_IWwwFormUrlDecoderEntry *PIWwwFormUrlDecoderEntry;

typedef _di_IIterator_1__IWwwFormUrlDecoderEntry *PIIterator_1__IWwwFormUrlDecoderEntry;

typedef _di_IIterable_1__IWwwFormUrlDecoderEntry *PIIterable_1__IWwwFormUrlDecoderEntry;

typedef _di_IClosable *PIClosable;

typedef _di_IPropertyValue *PIPropertyValue;

typedef _di_IMemoryBufferReference *PIMemoryBufferReference;

typedef _di_IMemoryBuffer *PIMemoryBuffer;

typedef _di_IReference_1__Rect *PIReference_1__Rect;

typedef _di_IGetActivationFactory *PIGetActivationFactory;

typedef _di_IIterator_1__Size *PIIterator_1__Size;

typedef _di_IIterable_1__Size *PIIterable_1__Size;

typedef _di_IVectorView_1__Size *PIVectorView_1__Size;

typedef _di_IPropertyValueStatics *PIPropertyValueStatics;

typedef _di_IStringable *PIStringable;

typedef _di_IKeyValuePair_2__HSTRING__IInspectable *PIKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterator_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterable_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IMap_2__HSTRING__IInspectable *PIMap_2__HSTRING__IInspectable;

typedef _di_IMapChangedEventArgs_1__HSTRING *PIMapChangedEventArgs_1__HSTRING;

typedef _di_MapChangedEventHandler_2__HSTRING__IInspectable *PMapChangedEventHandler_2__HSTRING__IInspectable;

typedef _di_IObservableMap_2__HSTRING__IInspectable *PIObservableMap_2__HSTRING__IInspectable;

typedef _di_DeferralCompletedHandler *PDeferralCompletedHandler;

typedef _di_IDeferralFactory *PIDeferralFactory;

typedef _di_TypedEventHandler_2__IMemoryBufferReference__IInspectable *PTypedEventHandler_2__IMemoryBufferReference__IInspectable;

typedef _di_IUriRuntimeClassWithAbsoluteCanonicalUri *PIUriRuntimeClassWithAbsoluteCanonicalUri;

typedef _di_IUriEscapeStatics *PIUriEscapeStatics;

typedef _di_IUriRuntimeClassFactory *PIUriRuntimeClassFactory;

typedef _di_IWwwFormUrlDecoderRuntimeClassFactory *PIWwwFormUrlDecoderRuntimeClassFactory;

typedef _di_IReference_1__Numerics_Matrix4x4 *PIReference_1__Numerics_Matrix4x4;

typedef _di_IIterator_1__IClosable *PIIterator_1__IClosable;

typedef _di_IIterable_1__IClosable *PIIterable_1__IClosable;

typedef _di_IVectorView_1__IClosable *PIVectorView_1__IClosable;

typedef _di_IVector_1__IClosable *PIVector_1__IClosable;

typedef _di_IIterator_1__IUriRuntimeClass *PIIterator_1__IUriRuntimeClass;

typedef _di_IIterable_1__IUriRuntimeClass *PIIterable_1__IUriRuntimeClass;

typedef _di_IIterator_1__TimeSpan *PIIterator_1__TimeSpan;

typedef _di_IIterable_1__TimeSpan *PIIterable_1__TimeSpan;

typedef _di_IVectorView_1__IUriRuntimeClass *PIVectorView_1__IUriRuntimeClass;

typedef _di_IVector_1__IUriRuntimeClass *PIVector_1__IUriRuntimeClass;

typedef _di_IReference_1__Point *PIReference_1__Point;

typedef _di_IIterator_1__DateTime *PIIterator_1__DateTime;

typedef _di_IIterable_1__DateTime *PIIterable_1__DateTime;

typedef _di_IVectorView_1__DateTime *PIVectorView_1__DateTime;

typedef _di_IVector_1__DateTime *PIVector_1__DateTime;

typedef _di_IIterator_1__IIterable_1__Point *PIIterator_1__IIterable_1__Point;

typedef _di_IIterable_1__IIterable_1__Point *PIIterable_1__IIterable_1__Point;

typedef _di_IVectorView_1__Point *PIVectorView_1__Point;

typedef _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime *PAsyncOperationCompletedHandler_1__IReference_1__DateTime;

typedef _di_IAsyncOperation_1__IReference_1__DateTime *PIAsyncOperation_1__IReference_1__DateTime;

typedef _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan *PAsyncOperationCompletedHandler_1__IReference_1__TimeSpan;

typedef _di_IAsyncOperation_1__IReference_1__TimeSpan *PIAsyncOperation_1__IReference_1__TimeSpan;

typedef _di_IReference_1__Numerics_Vector3 *PIReference_1__Numerics_Vector3;

typedef _di_IReference_1__Numerics_Vector2 *PIReference_1__Numerics_Vector2;

typedef _di_IReference_1__Numerics_Quaternion *PIReference_1__Numerics_Quaternion;

__interface  INTERFACE_UUID("{00000036-0000-0000-C000-000000000046}") IAsyncInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(unsigned &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::AsyncStatus &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_ErrorCode(HRESULT &__get_ErrorCode_result) = 0 ;
	virtual HRESULT __safecall Cancel() = 0 ;
	virtual HRESULT __safecall Close() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HRESULT _scw_get_ErrorCode() { HRESULT __r; HRESULT __hr = get_ErrorCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HRESULT ErrorCode = {read=_scw_get_ErrorCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Id() { unsigned __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AsyncStatus _scw_get_Status() { Winapi::Commontypes::AsyncStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AsyncStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{125E7431-F678-4E8E-B670-20A9B06C512D}") IWwwFormUrlDecoderEntry  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Name(HSTRING &__get_Name_result) = 0 ;
	virtual HRESULT __safecall get_Value(HSTRING &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Name() { HSTRING __r; HRESULT __hr = get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Name = {read=_scw_get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Value() { HSTRING __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{32E54295-373C-50CB-80A1-468A990CA780}") IIterator_1__IWwwFormUrlDecoderEntry_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{32E54295-373C-50CB-80A1-468A990CA780}") IIterator_1__IWwwFormUrlDecoderEntry  : public IIterator_1__IWwwFormUrlDecoderEntry_Base 
{
	virtual HRESULT __safecall get_Current(_di_IWwwFormUrlDecoderEntry &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIWwwFormUrlDecoderEntry items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWwwFormUrlDecoderEntry _scw_get_Current() { _di_IWwwFormUrlDecoderEntry __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWwwFormUrlDecoderEntry Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{876BE83B-7218-5BFB-A169-83152EF7E146}") IIterable_1__IWwwFormUrlDecoderEntry_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{876BE83B-7218-5BFB-A169-83152EF7E146}") IIterable_1__IWwwFormUrlDecoderEntry  : public IIterable_1__IWwwFormUrlDecoderEntry_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IWwwFormUrlDecoderEntry &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{30D5A829-7FA4-4026-83BB-D75BAE4EA99E}") IClosable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Close() = 0 ;
};

__interface  INTERFACE_UUID("{4BD682DD-7554-40E9-9A9B-82654EDE7E62}") IPropertyValue  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Type(Winapi::Foundation::Types::PropertyType &__get_Type_result) = 0 ;
	virtual HRESULT __safecall get_IsNumericScalar(bool &__get_IsNumericScalar_result) = 0 ;
	virtual HRESULT __safecall GetUInt8(System::Byte &__GetUInt8_result) = 0 ;
	virtual HRESULT __safecall GetInt16(short &__GetInt16_result) = 0 ;
	virtual HRESULT __safecall GetUInt16(System::Word &__GetUInt16_result) = 0 ;
	virtual HRESULT __safecall GetInt32(int &__GetInt32_result) = 0 ;
	virtual HRESULT __safecall GetUInt32(unsigned &__GetUInt32_result) = 0 ;
	virtual HRESULT __safecall GetInt64(__int64 &__GetInt64_result) = 0 ;
	virtual HRESULT __safecall GetUInt64(unsigned __int64 &__GetUInt64_result) = 0 ;
	virtual HRESULT __safecall GetSingle(float &__GetSingle_result) = 0 ;
	virtual HRESULT __safecall GetDouble(double &__GetDouble_result) = 0 ;
	virtual HRESULT __safecall GetChar16(System::WideChar &__GetChar16_result) = 0 ;
	virtual HRESULT __safecall GetBoolean(bool &__GetBoolean_result) = 0 ;
	virtual HRESULT __safecall GetString(HSTRING &__GetString_result) = 0 ;
	virtual HRESULT __safecall GetGuid(GUID &__GetGuid_result) = 0 ;
	virtual HRESULT __safecall GetDateTime(Winapi::Commontypes::DateTime &__GetDateTime_result) = 0 ;
	virtual HRESULT __safecall GetTimeSpan(Winapi::Commontypes::TimeSpan &__GetTimeSpan_result) = 0 ;
	virtual HRESULT __safecall GetPoint(System::Types::TPointF &__GetPoint_result) = 0 ;
	virtual HRESULT __safecall GetSize(System::Types::TSizeF &__GetSize_result) = 0 ;
	virtual HRESULT __safecall GetRect(System::Types::TRectF &__GetRect_result) = 0 ;
	virtual HRESULT __safecall GetUInt8Array(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall GetInt16Array(unsigned valueSize, System::PSmallInt value) = 0 ;
	virtual HRESULT __safecall GetUInt16Array(unsigned valueSize, System::PWord value) = 0 ;
	virtual HRESULT __safecall GetInt32Array(unsigned valueSize, System::PInteger value) = 0 ;
	virtual HRESULT __safecall GetUInt32Array(unsigned valueSize, System::PCardinal value) = 0 ;
	virtual HRESULT __safecall GetInt64Array(unsigned valueSize, System::PInt64 value) = 0 ;
	virtual HRESULT __safecall GetUInt64Array(unsigned valueSize, System::PUInt64 value) = 0 ;
	virtual HRESULT __safecall GetSingleArray(unsigned valueSize, System::PSingle value) = 0 ;
	virtual HRESULT __safecall GetDoubleArray(unsigned valueSize, System::PDouble value) = 0 ;
	virtual HRESULT __safecall GetChar16Array(unsigned valueSize, System::WideChar * value) = 0 ;
	virtual HRESULT __safecall GetBooleanArray(unsigned valueSize, System::PBoolean value) = 0 ;
	virtual HRESULT __safecall GetStringArray(unsigned valueSize, Winapi::Winrt::PHSTRING value) = 0 ;
	virtual HRESULT __safecall GetInspectableArray(unsigned valueSize, Winapi::Winrt::PIInspectable value) = 0 ;
	virtual HRESULT __safecall GetGuidArray(unsigned valueSize, System::PGUID value) = 0 ;
	virtual HRESULT __safecall GetDateTimeArray(unsigned valueSize, Winapi::Commontypes::PDateTime value) = 0 ;
	virtual HRESULT __safecall GetTimeSpanArray(unsigned valueSize, Winapi::Commontypes::PTimeSpan value) = 0 ;
	virtual HRESULT __safecall GetPointArray(unsigned valueSize, System::Types::PPointF value) = 0 ;
	virtual HRESULT __safecall GetSizeArray(unsigned valueSize, System::Types::PSizeF value) = 0 ;
	virtual HRESULT __safecall GetRectArray(unsigned valueSize, System::Types::PRectF value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsNumericScalar() { bool __r; HRESULT __hr = get_IsNumericScalar(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsNumericScalar = {read=_scw_get_IsNumericScalar};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::PropertyType _scw_get_Type() { Winapi::Foundation::Types::PropertyType __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::PropertyType Type = {read=_scw_get_Type};
};

__interface  INTERFACE_UUID("{FBC4DD29-245B-11E4-AF98-689423260CF8}") IMemoryBufferReference  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Capacity(unsigned &__get_Capacity_result) = 0 ;
	virtual HRESULT __safecall add_Closed(_di_TypedEventHandler_2__IMemoryBufferReference__IInspectable handler, Winapi::Commontypes::EventRegistrationToken &__add_Closed_result) = 0 ;
	virtual HRESULT __safecall remove_Closed(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Capacity() { unsigned __r; HRESULT __hr = get_Capacity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Capacity = {read=_scw_get_Capacity};
};

__interface  INTERFACE_UUID("{FBC4DD2A-245B-11E4-AF98-689423260CF8}") IMemoryBuffer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateReference(_di_IMemoryBufferReference &__CreateReference_result) = 0 ;
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Rect  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(System::Types::TRectF &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_Value() { System::Types::TRectF __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{4EDB8EE2-96DD-49A7-94F7-4607DDAB8E3C}") IGetActivationFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetActivationFactory(HSTRING activatableClassId, Winapi::Winrt::_di_IInspectable &__GetActivationFactory_result) = 0 ;
};

__interface  INTERFACE_UUID("{A3508EE0-3527-5144-894D-422EADEF43D7}") IIterator_1__Size_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__Size  : public IIterator_1__Size_Base 
{
	virtual HRESULT __safecall get_Current(System::Types::TSizeF &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, System::Types::PSizeF items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TSizeF _scw_get_Current() { System::Types::TSizeF __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TSizeF Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{C9DF55C3-4D41-5E90-BA76-E89ED564446B}") IIterable_1__Size_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__Size  : public IIterable_1__Size_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Size &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__Size  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, System::Types::TSizeF &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(System::Types::TSizeF value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, System::Types::PSizeF items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{629BDBC8-D932-4FF4-96B9-8D96C5C1E858}") IPropertyValueStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateEmpty(Winapi::Winrt::_di_IInspectable &__CreateEmpty_result) = 0 ;
	virtual HRESULT __safecall CreateUInt8(System::Byte value, Winapi::Winrt::_di_IInspectable &__CreateUInt8_result) = 0 ;
	virtual HRESULT __safecall CreateInt16(short value, Winapi::Winrt::_di_IInspectable &__CreateInt16_result) = 0 ;
	virtual HRESULT __safecall CreateUInt16(System::Word value, Winapi::Winrt::_di_IInspectable &__CreateUInt16_result) = 0 ;
	virtual HRESULT __safecall CreateInt32(int value, Winapi::Winrt::_di_IInspectable &__CreateInt32_result) = 0 ;
	virtual HRESULT __safecall CreateUInt32(unsigned value, Winapi::Winrt::_di_IInspectable &__CreateUInt32_result) = 0 ;
	virtual HRESULT __safecall CreateInt64(__int64 value, Winapi::Winrt::_di_IInspectable &__CreateInt64_result) = 0 ;
	virtual HRESULT __safecall CreateUInt64(unsigned __int64 value, Winapi::Winrt::_di_IInspectable &__CreateUInt64_result) = 0 ;
	virtual HRESULT __safecall CreateSingle(float value, Winapi::Winrt::_di_IInspectable &__CreateSingle_result) = 0 ;
	virtual HRESULT __safecall CreateDouble(double value, Winapi::Winrt::_di_IInspectable &__CreateDouble_result) = 0 ;
	virtual HRESULT __safecall CreateChar16(System::WideChar value, Winapi::Winrt::_di_IInspectable &__CreateChar16_result) = 0 ;
	virtual HRESULT __safecall CreateBoolean(bool value, Winapi::Winrt::_di_IInspectable &__CreateBoolean_result) = 0 ;
	virtual HRESULT __safecall CreateString(HSTRING value, Winapi::Winrt::_di_IInspectable &__CreateString_result) = 0 ;
	virtual HRESULT __safecall CreateInspectable(Winapi::Winrt::_di_IInspectable value, Winapi::Winrt::_di_IInspectable &__CreateInspectable_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall CreateGuid(GUID value, Winapi::Winrt::_di_IInspectable &__CreateGuid_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall CreateGuid(const GUID &value, Winapi::Winrt::_di_IInspectable &__CreateGuid_result) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall CreateDateTime(Winapi::Commontypes::DateTime value, Winapi::Winrt::_di_IInspectable &__CreateDateTime_result) = 0 ;
	virtual HRESULT __safecall CreateTimeSpan(Winapi::Commontypes::TimeSpan value, Winapi::Winrt::_di_IInspectable &__CreateTimeSpan_result) = 0 ;
	virtual HRESULT __safecall CreatePoint(System::Types::TPointF value, Winapi::Winrt::_di_IInspectable &__CreatePoint_result) = 0 ;
	virtual HRESULT __safecall CreateSize(System::Types::TSizeF value, Winapi::Winrt::_di_IInspectable &__CreateSize_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall CreateRect(System::Types::TRectF value, Winapi::Winrt::_di_IInspectable &__CreateRect_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall CreateRect(const System::Types::TRectF &value, Winapi::Winrt::_di_IInspectable &__CreateRect_result) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall CreateUInt8Array(unsigned valueSize, System::PByte value, Winapi::Winrt::_di_IInspectable &__CreateUInt8Array_result) = 0 ;
	virtual HRESULT __safecall CreateInt16Array(unsigned valueSize, System::PSmallInt value, Winapi::Winrt::_di_IInspectable &__CreateInt16Array_result) = 0 ;
	virtual HRESULT __safecall CreateUInt16Array(unsigned valueSize, System::PWord value, Winapi::Winrt::_di_IInspectable &__CreateUInt16Array_result) = 0 ;
	virtual HRESULT __safecall CreateInt32Array(unsigned valueSize, System::PInteger value, Winapi::Winrt::_di_IInspectable &__CreateInt32Array_result) = 0 ;
	virtual HRESULT __safecall CreateUInt32Array(unsigned valueSize, System::PCardinal value, Winapi::Winrt::_di_IInspectable &__CreateUInt32Array_result) = 0 ;
	virtual HRESULT __safecall CreateInt64Array(unsigned valueSize, System::PInt64 value, Winapi::Winrt::_di_IInspectable &__CreateInt64Array_result) = 0 ;
	virtual HRESULT __safecall CreateUInt64Array(unsigned valueSize, System::PUInt64 value, Winapi::Winrt::_di_IInspectable &__CreateUInt64Array_result) = 0 ;
	virtual HRESULT __safecall CreateSingleArray(unsigned valueSize, System::PSingle value, Winapi::Winrt::_di_IInspectable &__CreateSingleArray_result) = 0 ;
	virtual HRESULT __safecall CreateDoubleArray(unsigned valueSize, System::PDouble value, Winapi::Winrt::_di_IInspectable &__CreateDoubleArray_result) = 0 ;
	virtual HRESULT __safecall CreateChar16Array(unsigned valueSize, System::WideChar * value, Winapi::Winrt::_di_IInspectable &__CreateChar16Array_result) = 0 ;
	virtual HRESULT __safecall CreateBooleanArray(unsigned valueSize, System::PBoolean value, Winapi::Winrt::_di_IInspectable &__CreateBooleanArray_result) = 0 ;
	virtual HRESULT __safecall CreateStringArray(unsigned valueSize, Winapi::Winrt::PHSTRING value, Winapi::Winrt::_di_IInspectable &__CreateStringArray_result) = 0 ;
	virtual HRESULT __safecall CreateInspectableArray(unsigned valueSize, Winapi::Winrt::PIInspectable value, Winapi::Winrt::_di_IInspectable &__CreateInspectableArray_result) = 0 ;
	virtual HRESULT __safecall CreateGuidArray(unsigned valueSize, System::PGUID value, Winapi::Winrt::_di_IInspectable &__CreateGuidArray_result) = 0 ;
	virtual HRESULT __safecall CreateDateTimeArray(unsigned valueSize, Winapi::Commontypes::PDateTime value, Winapi::Winrt::_di_IInspectable &__CreateDateTimeArray_result) = 0 ;
	virtual HRESULT __safecall CreateTimeSpanArray(unsigned valueSize, Winapi::Commontypes::PTimeSpan value, Winapi::Winrt::_di_IInspectable &__CreateTimeSpanArray_result) = 0 ;
	virtual HRESULT __safecall CreatePointArray(unsigned valueSize, System::Types::PPointF value, Winapi::Winrt::_di_IInspectable &__CreatePointArray_result) = 0 ;
	virtual HRESULT __safecall CreateSizeArray(unsigned valueSize, System::Types::PSizeF value, Winapi::Winrt::_di_IInspectable &__CreateSizeArray_result) = 0 ;
	virtual HRESULT __safecall CreateRectArray(unsigned valueSize, System::Types::PRectF value, Winapi::Winrt::_di_IInspectable &__CreateRectArray_result) = 0 ;
};

__interface  INTERFACE_UUID("{96369F54-8EB6-48F0-ABCE-C1B211E627C3}") IStringable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ToString(HSTRING &__ToString_result) = 0 ;
};

__interface  INTERFACE_UUID("{09335560-6C6B-5A26-9348-97B781132B20}") IKeyValuePair_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Winrt::_di_IInspectable &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Value() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{5DB5FA32-707C-5849-A06B-91C8EB9D10E8}") IIterator_1__IKeyValuePair_2__HSTRING__IInspectable_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5DB5FA32-707C-5849-A06B-91C8EB9D10E8}") IIterator_1__IKeyValuePair_2__HSTRING__IInspectable  : public IIterator_1__IKeyValuePair_2__HSTRING__IInspectable_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IInspectable &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IInspectable items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IInspectable _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IInspectable __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IInspectable Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{FE2F3D47-5D47-5499-8374-430C7CDA0204}") IIterable_1__IKeyValuePair_2__HSTRING__IInspectable_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{FE2F3D47-5D47-5499-8374-430C7CDA0204}") IIterable_1__IKeyValuePair_2__HSTRING__IInspectable  : public IIterable_1__IKeyValuePair_2__HSTRING__IInspectable_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{1B0D3570-0877-5EC2-8A2C-3B9539506ACA}") IMap_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, Winapi::Winrt::_di_IInspectable &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall GetView(Winapi::Commontypes::_di_IMapView_2__HSTRING__IInspectable &__GetView_result) = 0 ;
	virtual HRESULT __safecall Insert(HSTRING key, Winapi::Winrt::_di_IInspectable value, bool &__Insert_result) = 0 ;
	virtual HRESULT __safecall Remove(HSTRING key) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{60141EFB-F2F9-5377-96FD-F8C60D9558B5}") IMapChangedEventArgs_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CollectionChange(Winapi::Commontypes::CollectionChange &__get_CollectionChange_result) = 0 ;
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CollectionChange _scw_get_CollectionChange() { Winapi::Commontypes::CollectionChange __r; HRESULT __hr = get_CollectionChange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CollectionChange CollectionChange = {read=_scw_get_CollectionChange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
};

__interface  INTERFACE_UUID("{24F981E5-DDCA-538D-AADA-A59906084CF1}") MapChangedEventHandler_2__HSTRING__IInspectable_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{24F981E5-DDCA-538D-AADA-A59906084CF1}") MapChangedEventHandler_2__HSTRING__IInspectable  : public MapChangedEventHandler_2__HSTRING__IInspectable_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IObservableMap_2__HSTRING__IInspectable sender, _di_IMapChangedEventArgs_1__HSTRING event) = 0 ;
};

__interface  INTERFACE_UUID("{236AAC9D-FB12-5C4D-A41C-9E445FB4D7EC}") IObservableMap_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_MapChanged(_di_MapChangedEventHandler_2__HSTRING__IInspectable vhnd, Winapi::Commontypes::EventRegistrationToken &__add_MapChanged_result) = 0 ;
	virtual HRESULT __safecall remove_MapChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{ED32A372-F3C8-4FAA-9CFB-470148DA3888}") DeferralCompletedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke() = 0 ;
};

__interface  INTERFACE_UUID("{65A1ECC5-3FB5-4832-8CA9-F061B281D13A}") IDeferralFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_DeferralCompletedHandler handler, Winapi::Commontypes::_di_IDeferral &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{F4637D4A-0760-5431-BFC0-24EB1D4F6C4F}") TypedEventHandler_2__IMemoryBufferReference__IInspectable_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F4637D4A-0760-5431-BFC0-24EB1D4F6C4F}") TypedEventHandler_2__IMemoryBufferReference__IInspectable  : public TypedEventHandler_2__IMemoryBufferReference__IInspectable_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IMemoryBufferReference sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{758D9661-221C-480F-A339-50656673F46F}") IUriRuntimeClassWithAbsoluteCanonicalUri  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AbsoluteCanonicalUri(HSTRING &__get_AbsoluteCanonicalUri_result) = 0 ;
	virtual HRESULT __safecall get_DisplayIri(HSTRING &__get_DisplayIri_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AbsoluteCanonicalUri() { HSTRING __r; HRESULT __hr = get_AbsoluteCanonicalUri(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AbsoluteCanonicalUri = {read=_scw_get_AbsoluteCanonicalUri};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayIri() { HSTRING __r; HRESULT __hr = get_DisplayIri(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayIri = {read=_scw_get_DisplayIri};
};

__interface  INTERFACE_UUID("{C1D432BA-C824-4452-A7FD-512BC3BBE9A1}") IUriEscapeStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall UnescapeComponent(HSTRING toUnescape, HSTRING &__UnescapeComponent_result) = 0 ;
	virtual HRESULT __safecall EscapeComponent(HSTRING toEscape, HSTRING &__EscapeComponent_result) = 0 ;
};

__interface  INTERFACE_UUID("{44A9796F-723E-4FDF-A218-033E75B0C084}") IUriRuntimeClassFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateUri(HSTRING uri, Winapi::Commontypes::_di_IUriRuntimeClass &__CreateUri_result) = 0 ;
	virtual HRESULT __safecall CreateWithRelativeUri(HSTRING baseUri, HSTRING relativeUri, Winapi::Commontypes::_di_IUriRuntimeClass &__CreateWithRelativeUri_result) = 0 ;
};

__interface  INTERFACE_UUID("{5B8C6B3D-24AE-41B5-A1BF-F0C3D544845B}") IWwwFormUrlDecoderRuntimeClassFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWwwFormUrlDecoder(HSTRING query, Winapi::Commontypes::_di_IWwwFormUrlDecoderRuntimeClass &__CreateWwwFormUrlDecoder_result) = 0 ;
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Numerics_Matrix4x4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::Numerics_Matrix4x4 &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Numerics_Matrix4x4 _scw_get_Value() { Winapi::Commontypes::Numerics_Matrix4x4 __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Numerics_Matrix4x4 Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{C9463957-E47D-5649-9874-4B13AE23061B}") IIterator_1__IClosable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(_di_IClosable &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIClosable items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IClosable _scw_get_Current() { _di_IClosable __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IClosable Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{44DA7ECF-B8CF-5DEF-8BF1-664578A8FB16}") IIterable_1__IClosable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IClosable &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{26DEBA5E-F73B-5181-94DB-2FCBC1DBAF8F}") IVectorView_1__IClosable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IClosable &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IClosable value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIClosable items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{1BFCA4F6-2C4E-5174-9869-B39D35848FCC}") IVector_1__IClosable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IClosable &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IClosable &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IClosable value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IClosable value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IClosable value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IClosable value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIClosable items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIClosable items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{1C157D0F-5EFE-5CEC-BBD6-0C6CE9AF07A5}") IIterator_1__IUriRuntimeClass_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E070225C-CB16-5FE3-8CC4-CAB4CE987C97}") IIterator_1__IUriRuntimeClass  : public IIterator_1__IUriRuntimeClass_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IUriRuntimeClass &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIUriRuntimeClass items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_Current() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{B0D63B78-78AD-5E31-B6D8-E32A0E16C447}") IIterable_1__IUriRuntimeClass_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{EA0329A4-F285-5263-A1BA-D87F0BF8D236}") IIterable_1__IUriRuntimeClass  : public IIterable_1__IUriRuntimeClass_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IUriRuntimeClass &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{67E9EADB-324B-5661-A405-DED8445B1EEA}") IIterator_1__TimeSpan_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__TimeSpan  : public IIterator_1__TimeSpan_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::TimeSpan &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PTimeSpan items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Current() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E9F78726-829A-5F67-8D19-95EF154B7742}") IIterable_1__TimeSpan_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__TimeSpan  : public IIterable_1__TimeSpan_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__TimeSpan &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{D38FF558-9620-5253-B2C2-7B2F4B27AF6F}") IVectorView_1__IUriRuntimeClass  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IUriRuntimeClass &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IUriRuntimeClass value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIUriRuntimeClass items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{B13E7C58-8A01-5524-A397-45B4629C84C1}") IVector_1__IUriRuntimeClass  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IUriRuntimeClass &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IUriRuntimeClass &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IUriRuntimeClass value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIUriRuntimeClass items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PIUriRuntimeClass items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Point  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(System::Types::TPointF &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Value() { System::Types::TPointF __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{F56158DF-8947-5480-96ED-36C1057877EA}") IIterator_1__DateTime_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__DateTime  : public IIterator_1__DateTime_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::DateTime &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PDateTime items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::DateTime _scw_get_Current() { Winapi::Commontypes::DateTime __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::DateTime Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{576A207D-977C-5B36-B54D-624EC86C53A3}") IIterable_1__DateTime_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__DateTime  : public IIterable_1__DateTime_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__DateTime &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__DateTime  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::DateTime &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::DateTime value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PDateTime items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A4739064-B54E-55D4-8012-317E2B6A807B}") IVector_1__DateTime  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::DateTime &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__DateTime &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::DateTime value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::DateTime value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::DateTime value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::DateTime value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PDateTime items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PDateTime items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{377F6162-6E4D-574E-BF01-77F4FD021D0E}") IIterator_1__IIterable_1__Point_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{66C2C906-6BCA-5085-BBA5-C7D445D25EE6}") IIterator_1__IIterable_1__Point  : public IIterator_1__IIterable_1__Point_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IIterable_1__Point &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIIterable_1__Point items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IIterable_1__Point _scw_get_Current() { Winapi::Commontypes::_di_IIterable_1__Point __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IIterable_1__Point Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{AE44597E-D411-5B7F-BBEC-6A96C94A107A}") IIterable_1__IIterable_1__Point_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0FB49B66-3A39-5E05-B730-60ADDFB9795F}") IIterable_1__IIterable_1__Point  : public IIterable_1__IIterable_1__Point_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IIterable_1__Point &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__Point  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, System::Types::TPointF &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(System::Types::TPointF value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, System::Types::PPointF items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{C4225D5E-1B7C-571E-9B88-2AB2EEFA8C8F}") AsyncOperationCompletedHandler_1__IReference_1__DateTime_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1AD5D0F6-8398-587D-AA9A-978252B1BBA2}") AsyncOperationCompletedHandler_1__IReference_1__DateTime  : public AsyncOperationCompletedHandler_1__IReference_1__DateTime_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IReference_1__DateTime asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2025B34F-4214-56AB-ABFE-2FBE6595DA9D}") IAsyncOperation_1__IReference_1__DateTime_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{00BEDA26-245F-5D19-B775-4DE00BBDC644}") IAsyncOperation_1__IReference_1__DateTime  : public IAsyncOperation_1__IReference_1__DateTime_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IReference_1__DateTime handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IReference_1__DateTime &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IReference_1__DateTime &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IReference_1__DateTime Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{E137B677-BFEF-54B0-B200-95C5C2902A25}") AsyncOperationCompletedHandler_1__IReference_1__TimeSpan_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1AD5D0F6-8398-587D-AA9A-978252B1BBA2}") AsyncOperationCompletedHandler_1__IReference_1__TimeSpan  : public AsyncOperationCompletedHandler_1__IReference_1__TimeSpan_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IReference_1__TimeSpan asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{24A901AD-910F-5C0F-B23C-67007577A558}") IAsyncOperation_1__IReference_1__TimeSpan_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{00BEDA26-245F-5D19-B775-4DE00BBDC644}") IAsyncOperation_1__IReference_1__TimeSpan  : public IAsyncOperation_1__IReference_1__TimeSpan_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IReference_1__TimeSpan &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IReference_1__TimeSpan Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Numerics_Vector3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::Numerics_Vector3 &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Numerics_Vector3 _scw_get_Value() { Winapi::Commontypes::Numerics_Vector3 __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Numerics_Vector3 Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Numerics_Vector2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Foundation::Types::Numerics_Vector2 &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Vector2 _scw_get_Value() { Winapi::Foundation::Types::Numerics_Vector2 __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Vector2 Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Numerics_Quaternion  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::Numerics_Quaternion &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Numerics_Quaternion _scw_get_Value() { Winapi::Commontypes::Numerics_Quaternion __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Numerics_Quaternion Value = {read=_scw_get_Value};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPropertyValue : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IPropertyValueStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IPropertyValueStatics> inherited;
	
public:
	static Winapi::Winrt::_di_IInspectable __fastcall CreateEmpty();
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt8(System::Byte value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt16(short value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt16(System::Word value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt32(int value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt32(unsigned value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt64(__int64 value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt64(unsigned __int64 value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateSingle(float value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateDouble(double value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateChar16(System::WideChar value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateBoolean(bool value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateString(HSTRING value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInspectable(Winapi::Winrt::_di_IInspectable value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateGuid(const GUID &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateDateTime(const Winapi::Commontypes::DateTime &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateTimeSpan(const Winapi::Commontypes::TimeSpan &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreatePoint(const System::Types::TPointF &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateSize(const System::Types::TSizeF &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateRect(const System::Types::TRectF &value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt8Array(unsigned valueSize, System::PByte value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt16Array(unsigned valueSize, System::PSmallInt value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt16Array(unsigned valueSize, System::PWord value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt32Array(unsigned valueSize, System::PInteger value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt32Array(unsigned valueSize, System::PCardinal value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInt64Array(unsigned valueSize, System::PInt64 value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateUInt64Array(unsigned valueSize, System::PUInt64 value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateSingleArray(unsigned valueSize, System::PSingle value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateDoubleArray(unsigned valueSize, System::PDouble value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateChar16Array(unsigned valueSize, System::WideChar * value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateBooleanArray(unsigned valueSize, System::PBoolean value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateStringArray(unsigned valueSize, Winapi::Winrt::PHSTRING value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateInspectableArray(unsigned valueSize, Winapi::Winrt::PIInspectable value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateGuidArray(unsigned valueSize, System::PGUID value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateDateTimeArray(unsigned valueSize, Winapi::Commontypes::PDateTime value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateTimeSpanArray(unsigned valueSize, Winapi::Commontypes::PTimeSpan value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreatePointArray(unsigned valueSize, System::Types::PPointF value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateSizeArray(unsigned valueSize, System::Types::PSizeF value);
	static Winapi::Winrt::_di_IInspectable __fastcall CreateRectArray(unsigned valueSize, System::Types::PRectF value);
public:
	/* TObject.Create */ inline __fastcall TPropertyValue() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IPropertyValueStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPropertyValue() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDeferral : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IDeferralFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IDeferralFactory> inherited;
	
public:
	static Winapi::Commontypes::_di_IDeferral __fastcall Create(_di_DeferralCompletedHandler handler);
public:
	/* TObject.Create */ inline __fastcall TDeferral() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IDeferralFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDeferral() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWwwFormUrlDecoder : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IWwwFormUrlDecoderRuntimeClassFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IWwwFormUrlDecoderRuntimeClassFactory> inherited;
	
public:
	static Winapi::Commontypes::_di_IWwwFormUrlDecoderRuntimeClass __fastcall CreateWwwFormUrlDecoder(HSTRING query);
public:
	/* TObject.Create */ inline __fastcall TWwwFormUrlDecoder() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IWwwFormUrlDecoderRuntimeClassFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWwwFormUrlDecoder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUri : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_IUriRuntimeClassFactory,_di_IUriEscapeStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_IUriRuntimeClassFactory,_di_IUriEscapeStatics> inherited;
	
public:
	static HSTRING __fastcall UnescapeComponent(HSTRING toUnescape);
	static HSTRING __fastcall EscapeComponent(HSTRING toEscape);
	static Winapi::Commontypes::_di_IUriRuntimeClass __fastcall CreateUri(HSTRING uri);
	static Winapi::Commontypes::_di_IUriRuntimeClass __fastcall CreateWithRelativeUri(HSTRING baseUri, HSTRING relativeUri);
public:
	/* TObject.Create */ inline __fastcall TUri() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_IUriRuntimeClassFactory,_di_IUriEscapeStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUri() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Foundation */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_FoundationHPP
