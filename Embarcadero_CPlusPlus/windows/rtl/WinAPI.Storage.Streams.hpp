// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Storage.Streams.pas' rev: 34.00 (Windows)

#ifndef Winapi_Storage_StreamsHPP
#define Winapi_Storage_StreamsHPP

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
namespace Storage
{
namespace Streams
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IRandomAccessStreamReference> _di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference> _di_IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference> _di_IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IBuffer_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IBuffer_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IBuffer_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IBuffer;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IBuffer> _di_AsyncOperationCompletedHandler_1__IBuffer;
__interface DELPHIINTERFACE IAsyncOperation_1__IBuffer_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IBuffer_Base> _di_IAsyncOperation_1__IBuffer_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IBuffer;
typedef System::DelphiInterface<IAsyncOperation_1__IBuffer> _di_IAsyncOperation_1__IBuffer;
__interface DELPHIINTERFACE IIterator_1__IBuffer_Base;
typedef System::DelphiInterface<IIterator_1__IBuffer_Base> _di_IIterator_1__IBuffer_Base;
__interface DELPHIINTERFACE IIterator_1__IBuffer;
typedef System::DelphiInterface<IIterator_1__IBuffer> _di_IIterator_1__IBuffer;
__interface DELPHIINTERFACE IIterable_1__IBuffer_Base;
typedef System::DelphiInterface<IIterable_1__IBuffer_Base> _di_IIterable_1__IBuffer_Base;
__interface DELPHIINTERFACE IIterable_1__IBuffer;
typedef System::DelphiInterface<IIterable_1__IBuffer> _di_IIterable_1__IBuffer;
__interface DELPHIINTERFACE IVector_1__IBuffer;
typedef System::DelphiInterface<IVector_1__IBuffer> _di_IVector_1__IBuffer;
__interface DELPHIINTERFACE IKeyValuePair_2__Cardinal__IBuffer;
typedef System::DelphiInterface<IKeyValuePair_2__Cardinal__IBuffer> _di_IKeyValuePair_2__Cardinal__IBuffer;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__Cardinal__IBuffer_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__Cardinal__IBuffer_Base> _di_IIterator_1__IKeyValuePair_2__Cardinal__IBuffer_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__Cardinal__IBuffer;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__Cardinal__IBuffer> _di_IIterator_1__IKeyValuePair_2__Cardinal__IBuffer;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__Cardinal__IBuffer_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__Cardinal__IBuffer_Base> _di_IIterable_1__IKeyValuePair_2__Cardinal__IBuffer_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__Cardinal__IBuffer;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__Cardinal__IBuffer> _di_IIterable_1__IKeyValuePair_2__Cardinal__IBuffer;
__interface DELPHIINTERFACE IMap_2__Cardinal__IBuffer;
typedef System::DelphiInterface<IMap_2__Cardinal__IBuffer> _di_IMap_2__Cardinal__IBuffer;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IOutputStream_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IOutputStream_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IOutputStream_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IOutputStream;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IOutputStream> _di_AsyncOperationCompletedHandler_1__IOutputStream;
__interface DELPHIINTERFACE IAsyncOperation_1__IOutputStream_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IOutputStream_Base> _di_IAsyncOperation_1__IOutputStream_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IOutputStream;
typedef System::DelphiInterface<IAsyncOperation_1__IOutputStream> _di_IAsyncOperation_1__IOutputStream;
__interface DELPHIINTERFACE IDataReader;
typedef System::DelphiInterface<IDataReader> _di_IDataReader;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__IBuffer__Cardinal> _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal> _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__IBuffer__Cardinal;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__IBuffer__Cardinal> _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IBuffer;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IBuffer> _di_IKeyValuePair_2__HSTRING__IBuffer;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IBuffer_Base;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IBuffer_Base> _di_IIterator_1__IKeyValuePair_2__HSTRING__IBuffer_Base;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IBuffer;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IBuffer> _di_IIterator_1__IKeyValuePair_2__HSTRING__IBuffer;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IBuffer_Base;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IBuffer_Base> _di_IIterable_1__IKeyValuePair_2__HSTRING__IBuffer_Base;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IBuffer;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IBuffer> _di_IIterable_1__IKeyValuePair_2__HSTRING__IBuffer;
__interface DELPHIINTERFACE IMapView_2__HSTRING__IBuffer_Base;
typedef System::DelphiInterface<IMapView_2__HSTRING__IBuffer_Base> _di_IMapView_2__HSTRING__IBuffer_Base;
__interface DELPHIINTERFACE IMapView_2__HSTRING__IBuffer;
typedef System::DelphiInterface<IMapView_2__HSTRING__IBuffer> _di_IMapView_2__HSTRING__IBuffer;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStreamWithContentType_Base;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStreamWithContentType_Base> _di_IIterator_1__IRandomAccessStreamWithContentType_Base;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStreamWithContentType;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStreamWithContentType> _di_IIterator_1__IRandomAccessStreamWithContentType;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStreamWithContentType_Base;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStreamWithContentType_Base> _di_IIterable_1__IRandomAccessStreamWithContentType_Base;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStreamWithContentType;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStreamWithContentType> _di_IIterable_1__IRandomAccessStreamWithContentType;
__interface DELPHIINTERFACE IVectorView_1__IRandomAccessStreamWithContentType;
typedef System::DelphiInterface<IVectorView_1__IRandomAccessStreamWithContentType> _di_IVectorView_1__IRandomAccessStreamWithContentType;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType> _di_IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStreamReference_Base;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStreamReference_Base> _di_IIterator_1__IRandomAccessStreamReference_Base;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStreamReference;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStreamReference> _di_IIterator_1__IRandomAccessStreamReference;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStreamReference_Base;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStreamReference_Base> _di_IIterable_1__IRandomAccessStreamReference_Base;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStreamReference;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStreamReference> _di_IIterable_1__IRandomAccessStreamReference;
__interface DELPHIINTERFACE IVectorView_1__IRandomAccessStreamReference;
typedef System::DelphiInterface<IVectorView_1__IRandomAccessStreamReference> _di_IVectorView_1__IRandomAccessStreamReference;
__interface DELPHIINTERFACE IDataReaderFactory;
typedef System::DelphiInterface<IDataReaderFactory> _di_IDataReaderFactory;
__interface DELPHIINTERFACE IDataReaderStatics;
typedef System::DelphiInterface<IDataReaderStatics> _di_IDataReaderStatics;
__interface DELPHIINTERFACE IDataWriter;
typedef System::DelphiInterface<IDataWriter> _di_IDataWriter;
__interface DELPHIINTERFACE IDataWriterFactory;
typedef System::DelphiInterface<IDataWriterFactory> _di_IDataWriterFactory;
__interface DELPHIINTERFACE IContentTypeProvider;
typedef System::DelphiInterface<IContentTypeProvider> _di_IContentTypeProvider;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IInputStream_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IInputStream_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IInputStream_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IInputStream;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IInputStream> _di_AsyncOperationCompletedHandler_1__IInputStream;
__interface DELPHIINTERFACE IAsyncOperation_1__IInputStream_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IInputStream_Base> _di_IAsyncOperation_1__IInputStream_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IInputStream;
typedef System::DelphiInterface<IAsyncOperation_1__IInputStream> _di_IAsyncOperation_1__IInputStream;
__interface DELPHIINTERFACE IInputStreamReference;
typedef System::DelphiInterface<IInputStreamReference> _di_IInputStreamReference;
__interface DELPHIINTERFACE IRandomAccessStreamReferenceStatics;
typedef System::DelphiInterface<IRandomAccessStreamReferenceStatics> _di_IRandomAccessStreamReferenceStatics;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStream_Base;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStream_Base> _di_IIterator_1__IRandomAccessStream_Base;
__interface DELPHIINTERFACE IIterator_1__IRandomAccessStream;
typedef System::DelphiInterface<IIterator_1__IRandomAccessStream> _di_IIterator_1__IRandomAccessStream;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStream_Base;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStream_Base> _di_IIterable_1__IRandomAccessStream_Base;
__interface DELPHIINTERFACE IIterable_1__IRandomAccessStream;
typedef System::DelphiInterface<IIterable_1__IRandomAccessStream> _di_IIterable_1__IRandomAccessStream;
__interface DELPHIINTERFACE IVectorView_1__IRandomAccessStream;
typedef System::DelphiInterface<IVectorView_1__IRandomAccessStream> _di_IVectorView_1__IRandomAccessStream;
__interface DELPHIINTERFACE IVector_1__IRandomAccessStream;
typedef System::DelphiInterface<IVector_1__IRandomAccessStream> _di_IVector_1__IRandomAccessStream;
class DELPHICLASS TDataReader;
class DELPHICLASS TDataWriter;
class DELPHICLASS TRandomAccessStreamReference;
//-- type declarations -------------------------------------------------------
;

typedef _di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference *PIKeyValuePair_2__HSTRING__IRandomAccessStreamReference;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference *PIIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference *PIIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference;

typedef _di_AsyncOperationCompletedHandler_1__IBuffer *PAsyncOperationCompletedHandler_1__IBuffer;

typedef _di_IAsyncOperation_1__IBuffer *PIAsyncOperation_1__IBuffer;

typedef _di_IIterator_1__IBuffer *PIIterator_1__IBuffer;

typedef _di_IIterable_1__IBuffer *PIIterable_1__IBuffer;

typedef _di_IVector_1__IBuffer *PIVector_1__IBuffer;

typedef _di_IKeyValuePair_2__Cardinal__IBuffer *PIKeyValuePair_2__Cardinal__IBuffer;

typedef _di_IIterator_1__IKeyValuePair_2__Cardinal__IBuffer *PIIterator_1__IKeyValuePair_2__Cardinal__IBuffer;

typedef _di_IIterable_1__IKeyValuePair_2__Cardinal__IBuffer *PIIterable_1__IKeyValuePair_2__Cardinal__IBuffer;

typedef _di_IMap_2__Cardinal__IBuffer *PIMap_2__Cardinal__IBuffer;

typedef _di_AsyncOperationCompletedHandler_1__IOutputStream *PAsyncOperationCompletedHandler_1__IOutputStream;

typedef _di_IAsyncOperation_1__IOutputStream *PIAsyncOperation_1__IOutputStream;

typedef _di_IDataReader *PIDataReader;

typedef _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal *PAsyncOperationProgressHandler_2__IBuffer__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal *PIAsyncOperationWithProgress_2__IBuffer__Cardinal;

typedef _di_IKeyValuePair_2__HSTRING__IBuffer *PIKeyValuePair_2__HSTRING__IBuffer;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IBuffer *PIIterator_1__IKeyValuePair_2__HSTRING__IBuffer;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IBuffer *PIIterable_1__IKeyValuePair_2__HSTRING__IBuffer;

typedef _di_IMapView_2__HSTRING__IBuffer *PIMapView_2__HSTRING__IBuffer;

typedef _di_IIterator_1__IRandomAccessStreamWithContentType *PIIterator_1__IRandomAccessStreamWithContentType;

typedef _di_IIterable_1__IRandomAccessStreamWithContentType *PIIterable_1__IRandomAccessStreamWithContentType;

typedef _di_IVectorView_1__IRandomAccessStreamWithContentType *PIVectorView_1__IRandomAccessStreamWithContentType;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType *PAsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType;

typedef _di_IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType *PIAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType;

typedef _di_IIterator_1__IRandomAccessStreamReference *PIIterator_1__IRandomAccessStreamReference;

typedef _di_IIterable_1__IRandomAccessStreamReference *PIIterable_1__IRandomAccessStreamReference;

typedef _di_IVectorView_1__IRandomAccessStreamReference *PIVectorView_1__IRandomAccessStreamReference;

typedef _di_IDataReaderFactory *PIDataReaderFactory;

typedef _di_IDataReaderStatics *PIDataReaderStatics;

typedef _di_IDataWriter *PIDataWriter;

typedef _di_IDataWriterFactory *PIDataWriterFactory;

typedef _di_IContentTypeProvider *PIContentTypeProvider;

typedef _di_AsyncOperationCompletedHandler_1__IInputStream *PAsyncOperationCompletedHandler_1__IInputStream;

typedef _di_IAsyncOperation_1__IInputStream *PIAsyncOperation_1__IInputStream;

typedef _di_IInputStreamReference *PIInputStreamReference;

typedef _di_IRandomAccessStreamReferenceStatics *PIRandomAccessStreamReferenceStatics;

typedef _di_IIterator_1__IRandomAccessStream *PIIterator_1__IRandomAccessStream;

typedef _di_IIterable_1__IRandomAccessStream *PIIterable_1__IRandomAccessStream;

typedef _di_IVectorView_1__IRandomAccessStream *PIVectorView_1__IRandomAccessStream;

typedef _di_IVector_1__IRandomAccessStream *PIVector_1__IRandomAccessStream;

__interface  INTERFACE_UUID("{02C75FC1-0806-5B2B-A690-DA0F3E03EF45}") IKeyValuePair_2__HSTRING__IRandomAccessStreamReference  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_Value() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{9419AF53-ACB8-5328-8853-70BA87EB6AD5}") IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F68346CB-785C-5C53-A795-4A270766A47A}") IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference  : public IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IRandomAccessStreamReference items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IRandomAccessStreamReference Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{C9729BA7-5E20-569D-A3D1-97A4E653E5BB}") IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{8D579E1F-0FF6-5010-A14B-6C7DE8433955}") IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference  : public IIterable_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IRandomAccessStreamReference &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{51C3D2FD-B8A1-5620-B746-7EE6D533ACA3}") AsyncOperationCompletedHandler_1__IBuffer_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{51C3D2FD-B8A1-5620-B746-7EE6D533ACA3}") AsyncOperationCompletedHandler_1__IBuffer  : public AsyncOperationCompletedHandler_1__IBuffer_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IBuffer asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{3BEE8834-B9A7-5A80-A746-5EF097227878}") IAsyncOperation_1__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3BEE8834-B9A7-5A80-A746-5EF097227878}") IAsyncOperation_1__IBuffer  : public IAsyncOperation_1__IBuffer_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IBuffer handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IBuffer &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IBuffer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IBuffer _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IBuffer __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IBuffer Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{AFEE38E0-F882-5F10-9655-1FC98CC8CCE5}") IIterator_1__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{AFEE38E0-F882-5F10-9655-1FC98CC8CCE5}") IIterator_1__IBuffer  : public IIterator_1__IBuffer_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IBuffer &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIBuffer items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Current() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{902972BF-A984-5443-B1C5-2F04A99E1FCA}") IIterable_1__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{902972BF-A984-5443-B1C5-2F04A99E1FCA}") IIterable_1__IBuffer  : public IIterable_1__IBuffer_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IBuffer &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{308FE894-CC06-5007-BC85-CBE94AC1A70C}") IVector_1__IBuffer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IBuffer &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(Winapi::Commontypes::_di_IVectorView_1__IBuffer &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IBuffer value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::_di_IBuffer value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::_di_IBuffer value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::_di_IBuffer value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIBuffer items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PIBuffer items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{82A3A3B7-E04A-5395-8487-7F94F1508CE7}") IKeyValuePair_2__Cardinal__IBuffer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(unsigned &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IBuffer &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Key() { unsigned __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Value() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{A295FA0C-C99F-5109-8AB9-91534BB48C9B}") IIterator_1__IKeyValuePair_2__Cardinal__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A295FA0C-C99F-5109-8AB9-91534BB48C9B}") IIterator_1__IKeyValuePair_2__Cardinal__IBuffer  : public IIterator_1__IKeyValuePair_2__Cardinal__IBuffer_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__Cardinal__IBuffer &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__Cardinal__IBuffer items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__Cardinal__IBuffer _scw_get_Current() { _di_IKeyValuePair_2__Cardinal__IBuffer __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__Cardinal__IBuffer Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{4FE7FE23-22B1-528C-881D-A4ECEAEF0F11}") IIterable_1__IKeyValuePair_2__Cardinal__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4FE7FE23-22B1-528C-881D-A4ECEAEF0F11}") IIterable_1__IKeyValuePair_2__Cardinal__IBuffer  : public IIterable_1__IKeyValuePair_2__Cardinal__IBuffer_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__Cardinal__IBuffer &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{5D2591DF-48C5-5734-9EF1-BD639B032007}") IMap_2__Cardinal__IBuffer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(unsigned key, Winapi::Commontypes::_di_IBuffer &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(unsigned key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall GetView(Winapi::Commontypes::_di_IMapView_2__Cardinal__IBuffer &__GetView_result) = 0 ;
	virtual HRESULT __safecall Insert(unsigned key, Winapi::Commontypes::_di_IBuffer value, bool &__Insert_result) = 0 ;
	virtual HRESULT __safecall Remove(unsigned key) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{BCB37F4F-3AF4-561C-A9E3-EEF1738494D7}") AsyncOperationCompletedHandler_1__IOutputStream_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{BCB37F4F-3AF4-561C-A9E3-EEF1738494D7}") AsyncOperationCompletedHandler_1__IOutputStream  : public AsyncOperationCompletedHandler_1__IOutputStream_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IOutputStream asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{E8736833-D013-5361-977D-C5E99934680E}") IAsyncOperation_1__IOutputStream_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E8736833-D013-5361-977D-C5E99934680E}") IAsyncOperation_1__IOutputStream  : public IAsyncOperation_1__IOutputStream_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IOutputStream handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IOutputStream &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IOutputStream &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IOutputStream _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IOutputStream __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IOutputStream Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{E2B50029-B4C1-4314-A4B8-FB813A2F275E}") IDataReader  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UnconsumedBufferLength(unsigned &__get_UnconsumedBufferLength_result) = 0 ;
	virtual HRESULT __safecall get_UnicodeEncoding(Winapi::Commontypes::UnicodeEncoding &__get_UnicodeEncoding_result) = 0 ;
	virtual HRESULT __safecall put_UnicodeEncoding(Winapi::Commontypes::UnicodeEncoding value) = 0 ;
	virtual HRESULT __safecall get_ByteOrder(Winapi::Commontypes::ByteOrder &__get_ByteOrder_result) = 0 ;
	virtual HRESULT __safecall put_ByteOrder(Winapi::Commontypes::ByteOrder value) = 0 ;
	virtual HRESULT __safecall get_InputStreamOptions(Winapi::Commontypes::InputStreamOptions &__get_InputStreamOptions_result) = 0 ;
	virtual HRESULT __safecall put_InputStreamOptions(Winapi::Commontypes::InputStreamOptions value) = 0 ;
	virtual HRESULT __safecall ReadByte(System::Byte &__ReadByte_result) = 0 ;
	virtual HRESULT __safecall ReadBytes(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall ReadBuffer(unsigned length, Winapi::Commontypes::_di_IBuffer &__ReadBuffer_result) = 0 ;
	virtual HRESULT __safecall ReadBoolean(bool &__ReadBoolean_result) = 0 ;
	virtual HRESULT __safecall ReadGuid(GUID &__ReadGuid_result) = 0 ;
	virtual HRESULT __safecall ReadInt16(short &__ReadInt16_result) = 0 ;
	virtual HRESULT __safecall ReadInt32(int &__ReadInt32_result) = 0 ;
	virtual HRESULT __safecall ReadInt64(__int64 &__ReadInt64_result) = 0 ;
	virtual HRESULT __safecall ReadUInt16(System::Word &__ReadUInt16_result) = 0 ;
	virtual HRESULT __safecall ReadUInt32(unsigned &__ReadUInt32_result) = 0 ;
	virtual HRESULT __safecall ReadUInt64(unsigned __int64 &__ReadUInt64_result) = 0 ;
	virtual HRESULT __safecall ReadSingle(float &__ReadSingle_result) = 0 ;
	virtual HRESULT __safecall ReadDouble(double &__ReadDouble_result) = 0 ;
	virtual HRESULT __safecall ReadString(unsigned codeUnitCount, HSTRING &__ReadString_result) = 0 ;
	virtual HRESULT __safecall ReadDateTime(Winapi::Commontypes::DateTime &__ReadDateTime_result) = 0 ;
	virtual HRESULT __safecall ReadTimeSpan(Winapi::Commontypes::TimeSpan &__ReadTimeSpan_result) = 0 ;
	virtual HRESULT __safecall LoadAsync(unsigned count, Winapi::Commontypes::_di_IAsyncOperation_1__Cardinal &__LoadAsync_result) = 0 ;
	virtual HRESULT __safecall DetachBuffer(Winapi::Commontypes::_di_IBuffer &__DetachBuffer_result) = 0 ;
	virtual HRESULT __safecall DetachStream(Winapi::Commontypes::_di_IInputStream &__DetachStream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ByteOrder _scw_get_ByteOrder() { Winapi::Commontypes::ByteOrder __r; HRESULT __hr = get_ByteOrder(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ByteOrder ByteOrder = {read=_scw_get_ByteOrder, write=put_ByteOrder};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::InputStreamOptions _scw_get_InputStreamOptions() { Winapi::Commontypes::InputStreamOptions __r; HRESULT __hr = get_InputStreamOptions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::InputStreamOptions InputStreamOptions = {read=_scw_get_InputStreamOptions, write=put_InputStreamOptions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_UnconsumedBufferLength() { unsigned __r; HRESULT __hr = get_UnconsumedBufferLength(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned UnconsumedBufferLength = {read=_scw_get_UnconsumedBufferLength};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnicodeEncoding _scw_get_UnicodeEncoding() { Winapi::Commontypes::UnicodeEncoding __r; HRESULT __hr = get_UnicodeEncoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnicodeEncoding UnicodeEncoding = {read=_scw_get_UnicodeEncoding, write=put_UnicodeEncoding};
};

__interface  INTERFACE_UUID("{BF666554-7605-5D9A-B14E-18D8C8472AFE}") AsyncOperationProgressHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, unsigned progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{06386A7A-E009-5B0B-AB68-A8E48B516647}") AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{D26B2819-897F-5C7D-84D6-56D796561431}") IAsyncOperationWithProgress_2__IBuffer__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IBuffer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9114F794-2CEB-5B03-9B22-36884E1F58B3}") IKeyValuePair_2__HSTRING__IBuffer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::_di_IBuffer &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Value() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{790ACB62-C4B3-57EA-A152-9E219371C6DC}") IIterator_1__IKeyValuePair_2__HSTRING__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{790ACB62-C4B3-57EA-A152-9E219371C6DC}") IIterator_1__IKeyValuePair_2__HSTRING__IBuffer  : public IIterator_1__IKeyValuePair_2__HSTRING__IBuffer_Base 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IBuffer &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IBuffer items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IBuffer _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IBuffer __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IBuffer Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{3C9FFA92-5123-5AC4-B111-03C215F0C51C}") IIterable_1__IKeyValuePair_2__HSTRING__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3C9FFA92-5123-5AC4-B111-03C215F0C51C}") IIterable_1__IKeyValuePair_2__HSTRING__IBuffer  : public IIterable_1__IKeyValuePair_2__HSTRING__IBuffer_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IBuffer &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2CFEEC4F-E261-5F4C-AEE1-C78518E9D5B9}") IMapView_2__HSTRING__IBuffer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2CFEEC4F-E261-5F4C-AEE1-C78518E9D5B9}") IMapView_2__HSTRING__IBuffer  : public IMapView_2__HSTRING__IBuffer_Base 
{
	virtual HRESULT __safecall Lookup(HSTRING key, Winapi::Commontypes::_di_IBuffer &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall Split(/* out */ _di_IMapView_2__HSTRING__IBuffer &first, /* out */ _di_IMapView_2__HSTRING__IBuffer &second) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{4A10752D-6B1A-5FEC-A59C-70389BF162A2}") IIterator_1__IRandomAccessStreamWithContentType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F225500A-EE51-56E4-BAC4-C835CF10C316}") IIterator_1__IRandomAccessStreamWithContentType  : public IIterator_1__IRandomAccessStreamWithContentType_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IRandomAccessStreamWithContentType &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStreamWithContentType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamWithContentType _scw_get_Current() { Winapi::Commontypes::_di_IRandomAccessStreamWithContentType __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamWithContentType Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{034EA0C4-C20E-5C0C-BA31-64212F28E650}") IIterable_1__IRandomAccessStreamWithContentType_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C6B83736-1F57-5E24-9238-702C585CC3BB}") IIterable_1__IRandomAccessStreamWithContentType  : public IIterable_1__IRandomAccessStreamWithContentType_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IRandomAccessStreamWithContentType &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{20A82375-0F34-55AF-AE7E-AE77BC3D542F}") IVectorView_1__IRandomAccessStreamWithContentType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStreamWithContentType &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IRandomAccessStreamWithContentType value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStreamWithContentType items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{4572C48A-AAC4-5B60-AB1E-8561D15763BE}") AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{93177A05-73F1-563E-9CB7-99C2A51D8E63}") IAsyncOperation_1__IVectorView_1__IRandomAccessStreamWithContentType  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IRandomAccessStreamWithContentType &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IRandomAccessStreamWithContentType Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{6A957F20-ED25-5019-90E7-9890D4F912F2}") IIterator_1__IRandomAccessStreamReference_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{712E1447-A302-58CA-8CF7-C3B9B4BA67EC}") IIterator_1__IRandomAccessStreamReference  : public IIterator_1__IRandomAccessStreamReference_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IRandomAccessStreamReference &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStreamReference items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStreamReference _scw_get_Current() { Winapi::Commontypes::_di_IRandomAccessStreamReference __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStreamReference Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{5F65D649-CCBD-5728-A85B-D3FF92FCA962}") IIterable_1__IRandomAccessStreamReference_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{AE075AFA-2F06-5011-9FE1-1AF33410E707}") IIterable_1__IRandomAccessStreamReference  : public IIterable_1__IRandomAccessStreamReference_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IRandomAccessStreamReference &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{4D904A36-6418-5C09-A622-A1CC8C27EEFF}") IVectorView_1__IRandomAccessStreamReference  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStreamReference &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IRandomAccessStreamReference value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStreamReference items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{D7527847-57DA-4E15-914C-06806699A098}") IDataReaderFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateDataReader(Winapi::Commontypes::_di_IInputStream inputStream, _di_IDataReader &__CreateDataReader_result) = 0 ;
};

__interface  INTERFACE_UUID("{11FCBFC8-F93A-471B-B121-F379E349313C}") IDataReaderStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromBuffer(Winapi::Commontypes::_di_IBuffer buffer, _di_IDataReader &__FromBuffer_result) = 0 ;
};

__interface  INTERFACE_UUID("{64B89265-D341-4922-B38A-DD4AF8808C4E}") IDataWriter  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UnstoredBufferLength(unsigned &__get_UnstoredBufferLength_result) = 0 ;
	virtual HRESULT __safecall get_UnicodeEncoding(Winapi::Commontypes::UnicodeEncoding &__get_UnicodeEncoding_result) = 0 ;
	virtual HRESULT __safecall put_UnicodeEncoding(Winapi::Commontypes::UnicodeEncoding value) = 0 ;
	virtual HRESULT __safecall get_ByteOrder(Winapi::Commontypes::ByteOrder &__get_ByteOrder_result) = 0 ;
	virtual HRESULT __safecall put_ByteOrder(Winapi::Commontypes::ByteOrder value) = 0 ;
	virtual HRESULT __safecall WriteByte(System::Byte value) = 0 ;
	virtual HRESULT __safecall WriteBytes(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall WriteBuffer(Winapi::Commontypes::_di_IBuffer buffer) = 0 /* overload */;
	virtual HRESULT __safecall WriteBuffer(Winapi::Commontypes::_di_IBuffer buffer, unsigned start, unsigned count) = 0 /* overload */;
	virtual HRESULT __safecall WriteBoolean(bool value) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall WriteGuid(GUID value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall WriteGuid(const GUID &value) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall WriteInt16(short value) = 0 ;
	virtual HRESULT __safecall WriteInt32(int value) = 0 ;
	virtual HRESULT __safecall WriteInt64(__int64 value) = 0 ;
	virtual HRESULT __safecall WriteUInt16(System::Word value) = 0 ;
	virtual HRESULT __safecall WriteUInt32(unsigned value) = 0 ;
	virtual HRESULT __safecall WriteUInt64(unsigned __int64 value) = 0 ;
	virtual HRESULT __safecall WriteSingle(float value) = 0 ;
	virtual HRESULT __safecall WriteDouble(double value) = 0 ;
	virtual HRESULT __safecall WriteDateTime(Winapi::Commontypes::DateTime value) = 0 ;
	virtual HRESULT __safecall WriteTimeSpan(Winapi::Commontypes::TimeSpan value) = 0 ;
	virtual HRESULT __safecall WriteString(HSTRING value, unsigned &__WriteString_result) = 0 ;
	virtual HRESULT __safecall MeasureString(HSTRING value, unsigned &__MeasureString_result) = 0 ;
	virtual HRESULT __safecall StoreAsync(Winapi::Commontypes::_di_IAsyncOperation_1__Cardinal &__StoreAsync_result) = 0 ;
	virtual HRESULT __safecall FlushAsync(Winapi::Commontypes::_di_IAsyncOperation_1__Boolean &__FlushAsync_result) = 0 ;
	virtual HRESULT __safecall DetachBuffer(Winapi::Commontypes::_di_IBuffer &__DetachBuffer_result) = 0 ;
	virtual HRESULT __safecall DetachStream(Winapi::Commontypes::_di_IOutputStream &__DetachStream_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ByteOrder _scw_get_ByteOrder() { Winapi::Commontypes::ByteOrder __r; HRESULT __hr = get_ByteOrder(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ByteOrder ByteOrder = {read=_scw_get_ByteOrder, write=put_ByteOrder};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::UnicodeEncoding _scw_get_UnicodeEncoding() { Winapi::Commontypes::UnicodeEncoding __r; HRESULT __hr = get_UnicodeEncoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::UnicodeEncoding UnicodeEncoding = {read=_scw_get_UnicodeEncoding, write=put_UnicodeEncoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_UnstoredBufferLength() { unsigned __r; HRESULT __hr = get_UnstoredBufferLength(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned UnstoredBufferLength = {read=_scw_get_UnstoredBufferLength};
};

__interface  INTERFACE_UUID("{338C67C2-8B84-4C2B-9C50-7B8767847A1F}") IDataWriterFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateDataWriter(Winapi::Commontypes::_di_IOutputStream outputStream, _di_IDataWriter &__CreateDataWriter_result) = 0 ;
};

__interface  INTERFACE_UUID("{97D098A5-3B99-4DE9-88A5-E11D2F50C795}") IContentTypeProvider  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ContentType(HSTRING &__get_ContentType_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ContentType() { HSTRING __r; HRESULT __hr = get_ContentType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ContentType = {read=_scw_get_ContentType};
};

__interface  INTERFACE_UUID("{D0BD0125-9049-57A3-BD66-E2525D98C814}") AsyncOperationCompletedHandler_1__IInputStream_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D0BD0125-9049-57A3-BD66-E2525D98C814}") AsyncOperationCompletedHandler_1__IInputStream  : public AsyncOperationCompletedHandler_1__IInputStream_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IInputStream asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{A8FE0732-556D-5841-B7EE-B3450FB52666}") IAsyncOperation_1__IInputStream_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A8FE0732-556D-5841-B7EE-B3450FB52666}") IAsyncOperation_1__IInputStream  : public IAsyncOperation_1__IInputStream_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IInputStream handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IInputStream &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IInputStream &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IInputStream _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IInputStream __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IInputStream Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{43929D18-5EC9-4B5A-919C-4205B0C804B6}") IInputStreamReference  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall OpenSequentialReadAsync(_di_IAsyncOperation_1__IInputStream &__OpenSequentialReadAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{857309DC-3FBF-4E7D-986F-EF3B1A07A964}") IRandomAccessStreamReferenceStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateFromFile(Winapi::Winrt::_di_IInspectable file, Winapi::Commontypes::_di_IRandomAccessStreamReference &__CreateFromFile_result) = 0 ;
	virtual HRESULT __safecall CreateFromUri(Winapi::Commontypes::_di_IUriRuntimeClass uri, Winapi::Commontypes::_di_IRandomAccessStreamReference &__CreateFromUri_result) = 0 ;
	virtual HRESULT __safecall CreateFromStream(Winapi::Commontypes::_di_IRandomAccessStream stream, Winapi::Commontypes::_di_IRandomAccessStreamReference &__CreateFromStream_result) = 0 ;
};

__interface  INTERFACE_UUID("{C875446A-587F-58DA-897E-3BBE5EC7C30B}") IIterator_1__IRandomAccessStream_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C875446A-587F-58DA-897E-3BBE5EC7C30B}") IIterator_1__IRandomAccessStream  : public IIterator_1__IRandomAccessStream_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IRandomAccessStream &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStream items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IRandomAccessStream _scw_get_Current() { Winapi::Commontypes::_di_IRandomAccessStream __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IRandomAccessStream Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{BA666A00-1555-5DF4-81A5-07D23F7FFCEB}") IIterable_1__IRandomAccessStream_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BA666A00-1555-5DF4-81A5-07D23F7FFCEB}") IIterable_1__IRandomAccessStream  : public IIterable_1__IRandomAccessStream_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IRandomAccessStream &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{92CD0A46-2266-5CD6-9293-E111299F2793}") IVectorView_1__IRandomAccessStream  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStream &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IRandomAccessStream value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStream items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{2736B66B-DAA3-5E0C-9842-6A0F44B5440B}") IVector_1__IRandomAccessStream  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStream &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IRandomAccessStream &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IRandomAccessStream value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::_di_IRandomAccessStream value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStream items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PIRandomAccessStream items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataReader : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_IDataReaderFactory,_di_IDataReaderStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_IDataReaderFactory,_di_IDataReaderStatics> inherited;
	
public:
	static _di_IDataReader __fastcall FromBuffer(Winapi::Commontypes::_di_IBuffer buffer);
	static _di_IDataReader __fastcall CreateDataReader(Winapi::Commontypes::_di_IInputStream inputStream);
public:
	/* TObject.Create */ inline __fastcall TDataReader() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_IDataReaderFactory,_di_IDataReaderStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDataWriter : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IDataWriterFactory,_di_IDataWriter>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IDataWriterFactory,_di_IDataWriter> inherited;
	
public:
	static _di_IDataWriter __fastcall CreateDataWriter(Winapi::Commontypes::_di_IOutputStream outputStream);
public:
	/* TObject.Create */ inline __fastcall TDataWriter() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IDataWriterFactory,_di_IDataWriter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRandomAccessStreamReference : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IRandomAccessStreamReferenceStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IRandomAccessStreamReferenceStatics> inherited;
	
public:
	static Winapi::Commontypes::_di_IRandomAccessStreamReference __fastcall CreateFromFile(Winapi::Winrt::_di_IInspectable file);
	static Winapi::Commontypes::_di_IRandomAccessStreamReference __fastcall CreateFromUri(Winapi::Commontypes::_di_IUriRuntimeClass uri);
	static Winapi::Commontypes::_di_IRandomAccessStreamReference __fastcall CreateFromStream(Winapi::Commontypes::_di_IRandomAccessStream stream);
public:
	/* TObject.Create */ inline __fastcall TRandomAccessStreamReference() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IRandomAccessStreamReferenceStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRandomAccessStreamReference() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Streams */
}	/* namespace Storage */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Storage_StreamsHPP
