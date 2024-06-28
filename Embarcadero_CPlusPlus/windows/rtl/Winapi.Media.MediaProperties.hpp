// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Media.MediaProperties.pas' rev: 34.00 (Windows)

#ifndef Winapi_Media_MediapropertiesHPP
#define Winapi_Media_MediapropertiesHPP

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
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Media
{
namespace Mediaproperties
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IMediaEncodingProperties;
typedef System::DelphiInterface<IMediaEncodingProperties> _di_IMediaEncodingProperties;
__interface DELPHIINTERFACE IContainerEncodingProperties;
typedef System::DelphiInterface<IContainerEncodingProperties> _di_IContainerEncodingProperties;
__interface DELPHIINTERFACE IMediaEncodingProfile;
typedef System::DelphiInterface<IMediaEncodingProfile> _di_IMediaEncodingProfile;
__interface DELPHIINTERFACE IImageEncodingProperties;
typedef System::DelphiInterface<IImageEncodingProperties> _di_IImageEncodingProperties;
__interface DELPHIINTERFACE IIterator_1__IMediaEncodingProperties_Base;
typedef System::DelphiInterface<IIterator_1__IMediaEncodingProperties_Base> _di_IIterator_1__IMediaEncodingProperties_Base;
__interface DELPHIINTERFACE IIterator_1__IMediaEncodingProperties;
typedef System::DelphiInterface<IIterator_1__IMediaEncodingProperties> _di_IIterator_1__IMediaEncodingProperties;
__interface DELPHIINTERFACE IIterable_1__IMediaEncodingProperties_Base;
typedef System::DelphiInterface<IIterable_1__IMediaEncodingProperties_Base> _di_IIterable_1__IMediaEncodingProperties_Base;
__interface DELPHIINTERFACE IIterable_1__IMediaEncodingProperties;
typedef System::DelphiInterface<IIterable_1__IMediaEncodingProperties> _di_IIterable_1__IMediaEncodingProperties;
__interface DELPHIINTERFACE IVectorView_1__IMediaEncodingProperties;
typedef System::DelphiInterface<IVectorView_1__IMediaEncodingProperties> _di_IVectorView_1__IMediaEncodingProperties;
__interface DELPHIINTERFACE IAudioEncodingPropertiesWithFormatUserData;
typedef System::DelphiInterface<IAudioEncodingPropertiesWithFormatUserData> _di_IAudioEncodingPropertiesWithFormatUserData;
__interface DELPHIINTERFACE IAudioEncodingProperties2;
typedef System::DelphiInterface<IAudioEncodingProperties2> _di_IAudioEncodingProperties2;
__interface DELPHIINTERFACE IAudioEncodingPropertiesStatics;
typedef System::DelphiInterface<IAudioEncodingPropertiesStatics> _di_IAudioEncodingPropertiesStatics;
__interface DELPHIINTERFACE IAudioEncodingPropertiesStatics2;
typedef System::DelphiInterface<IAudioEncodingPropertiesStatics2> _di_IAudioEncodingPropertiesStatics2;
__interface DELPHIINTERFACE IVideoEncodingProperties2;
typedef System::DelphiInterface<IVideoEncodingProperties2> _di_IVideoEncodingProperties2;
__interface DELPHIINTERFACE IVideoEncodingProperties3;
typedef System::DelphiInterface<IVideoEncodingProperties3> _di_IVideoEncodingProperties3;
__interface DELPHIINTERFACE IVideoEncodingProperties4;
typedef System::DelphiInterface<IVideoEncodingProperties4> _di_IVideoEncodingProperties4;
__interface DELPHIINTERFACE IVideoEncodingPropertiesStatics;
typedef System::DelphiInterface<IVideoEncodingPropertiesStatics> _di_IVideoEncodingPropertiesStatics;
__interface DELPHIINTERFACE IVideoEncodingPropertiesStatics2;
typedef System::DelphiInterface<IVideoEncodingPropertiesStatics2> _di_IVideoEncodingPropertiesStatics2;
__interface DELPHIINTERFACE IImageEncodingPropertiesStatics;
typedef System::DelphiInterface<IImageEncodingPropertiesStatics> _di_IImageEncodingPropertiesStatics;
__interface DELPHIINTERFACE IImageEncodingPropertiesStatics2;
typedef System::DelphiInterface<IImageEncodingPropertiesStatics2> _di_IImageEncodingPropertiesStatics2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMediaEncodingProfile_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMediaEncodingProfile_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IMediaEncodingProfile;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IMediaEncodingProfile> _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile;
__interface DELPHIINTERFACE IAsyncOperation_1__IMediaEncodingProfile_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IMediaEncodingProfile_Base> _di_IAsyncOperation_1__IMediaEncodingProfile_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IMediaEncodingProfile;
typedef System::DelphiInterface<IAsyncOperation_1__IMediaEncodingProfile> _di_IAsyncOperation_1__IMediaEncodingProfile;
__interface DELPHIINTERFACE IMediaEncodingProfileStatics;
typedef System::DelphiInterface<IMediaEncodingProfileStatics> _di_IMediaEncodingProfileStatics;
__interface DELPHIINTERFACE IMediaEncodingProfileStatics2;
typedef System::DelphiInterface<IMediaEncodingProfileStatics2> _di_IMediaEncodingProfileStatics2;
__interface DELPHIINTERFACE IMediaEncodingProfileStatics3;
typedef System::DelphiInterface<IMediaEncodingProfileStatics3> _di_IMediaEncodingProfileStatics3;
__interface DELPHIINTERFACE IMediaEncodingProfile2;
typedef System::DelphiInterface<IMediaEncodingProfile2> _di_IMediaEncodingProfile2;
__interface DELPHIINTERFACE IIterator_1__IVideoEncodingProperties_Base;
typedef System::DelphiInterface<IIterator_1__IVideoEncodingProperties_Base> _di_IIterator_1__IVideoEncodingProperties_Base;
__interface DELPHIINTERFACE IIterator_1__IVideoEncodingProperties;
typedef System::DelphiInterface<IIterator_1__IVideoEncodingProperties> _di_IIterator_1__IVideoEncodingProperties;
__interface DELPHIINTERFACE IIterable_1__IVideoEncodingProperties_Base;
typedef System::DelphiInterface<IIterable_1__IVideoEncodingProperties_Base> _di_IIterable_1__IVideoEncodingProperties_Base;
__interface DELPHIINTERFACE IIterable_1__IVideoEncodingProperties;
typedef System::DelphiInterface<IIterable_1__IVideoEncodingProperties> _di_IIterable_1__IVideoEncodingProperties;
__interface DELPHIINTERFACE IVectorView_1__IVideoEncodingProperties;
typedef System::DelphiInterface<IVectorView_1__IVideoEncodingProperties> _di_IVectorView_1__IVideoEncodingProperties;
__interface DELPHIINTERFACE IIterator_1__IAudioEncodingProperties_Base;
typedef System::DelphiInterface<IIterator_1__IAudioEncodingProperties_Base> _di_IIterator_1__IAudioEncodingProperties_Base;
__interface DELPHIINTERFACE IIterator_1__IAudioEncodingProperties;
typedef System::DelphiInterface<IIterator_1__IAudioEncodingProperties> _di_IIterator_1__IAudioEncodingProperties;
__interface DELPHIINTERFACE IIterable_1__IAudioEncodingProperties_Base;
typedef System::DelphiInterface<IIterable_1__IAudioEncodingProperties_Base> _di_IIterable_1__IAudioEncodingProperties_Base;
__interface DELPHIINTERFACE IIterable_1__IAudioEncodingProperties;
typedef System::DelphiInterface<IIterable_1__IAudioEncodingProperties> _di_IIterable_1__IAudioEncodingProperties;
__interface DELPHIINTERFACE IVectorView_1__IAudioEncodingProperties;
typedef System::DelphiInterface<IVectorView_1__IAudioEncodingProperties> _di_IVectorView_1__IAudioEncodingProperties;
class DELPHICLASS TMediaPropertySet;
class DELPHICLASS TAudioEncodingProperties;
class DELPHICLASS TVideoEncodingProperties;
class DELPHICLASS TImageEncodingProperties;
class DELPHICLASS TContainerEncodingProperties;
class DELPHICLASS TMediaEncodingProfile;
//-- type declarations -------------------------------------------------------
typedef _di_IMediaEncodingProperties *PIMediaEncodingProperties;

typedef _di_IContainerEncodingProperties *PIContainerEncodingProperties;

typedef _di_IMediaEncodingProfile *PIMediaEncodingProfile;

typedef _di_IImageEncodingProperties *PIImageEncodingProperties;

typedef _di_IIterator_1__IMediaEncodingProperties *PIIterator_1__IMediaEncodingProperties;

typedef _di_IIterable_1__IMediaEncodingProperties *PIIterable_1__IMediaEncodingProperties;

typedef _di_IVectorView_1__IMediaEncodingProperties *PIVectorView_1__IMediaEncodingProperties;

typedef _di_IAudioEncodingPropertiesWithFormatUserData *PIAudioEncodingPropertiesWithFormatUserData;

typedef _di_IAudioEncodingProperties2 *PIAudioEncodingProperties2;

typedef _di_IAudioEncodingPropertiesStatics *PIAudioEncodingPropertiesStatics;

typedef _di_IAudioEncodingPropertiesStatics2 *PIAudioEncodingPropertiesStatics2;

typedef _di_IVideoEncodingProperties2 *PIVideoEncodingProperties2;

typedef _di_IVideoEncodingProperties3 *PIVideoEncodingProperties3;

typedef _di_IVideoEncodingProperties4 *PIVideoEncodingProperties4;

typedef _di_IVideoEncodingPropertiesStatics *PIVideoEncodingPropertiesStatics;

typedef _di_IVideoEncodingPropertiesStatics2 *PIVideoEncodingPropertiesStatics2;

typedef _di_IImageEncodingPropertiesStatics *PIImageEncodingPropertiesStatics;

typedef _di_IImageEncodingPropertiesStatics2 *PIImageEncodingPropertiesStatics2;

typedef _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile *PAsyncOperationCompletedHandler_1__IMediaEncodingProfile;

typedef _di_IAsyncOperation_1__IMediaEncodingProfile *PIAsyncOperation_1__IMediaEncodingProfile;

typedef _di_IMediaEncodingProfileStatics *PIMediaEncodingProfileStatics;

typedef _di_IMediaEncodingProfileStatics2 *PIMediaEncodingProfileStatics2;

typedef _di_IMediaEncodingProfileStatics3 *PIMediaEncodingProfileStatics3;

typedef _di_IMediaEncodingProfile2 *PIMediaEncodingProfile2;

typedef _di_IIterator_1__IVideoEncodingProperties *PIIterator_1__IVideoEncodingProperties;

typedef _di_IIterable_1__IVideoEncodingProperties *PIIterable_1__IVideoEncodingProperties;

typedef _di_IVectorView_1__IVideoEncodingProperties *PIVectorView_1__IVideoEncodingProperties;

typedef _di_IIterator_1__IAudioEncodingProperties *PIIterator_1__IAudioEncodingProperties;

typedef _di_IIterable_1__IAudioEncodingProperties *PIIterable_1__IAudioEncodingProperties;

typedef _di_IVectorView_1__IAudioEncodingProperties *PIVectorView_1__IAudioEncodingProperties;

__interface  INTERFACE_UUID("{B4002AF6-ACD4-4E5A-A24B-5D7498A8B8C4}") IMediaEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Properties(Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable &__get_Properties_result) = 0 ;
	virtual HRESULT __safecall get_Type(HSTRING &__get_Type_result) = 0 ;
	virtual HRESULT __safecall put_Subtype(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Subtype(HSTRING &__get_Subtype_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable _scw_get_Properties() { Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable __r; HRESULT __hr = get_Properties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable Properties = {read=_scw_get_Properties};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Subtype() { HSTRING __r; HRESULT __hr = get_Subtype(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Subtype = {read=_scw_get_Subtype, write=put_Subtype};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Type() { HSTRING __r; HRESULT __hr = get_Type(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Type = {read=_scw_get_Type};
};

__interface  INTERFACE_UUID("{59AC2A57-B32A-479E-8A61-4B7F2E9E7EA0}") IContainerEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E7DBF5A8-1DB9-4783-876B-3DFE12ACFDB3}") IMediaEncodingProfile  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Audio(Winapi::Commontypes::_di_IAudioEncodingProperties value) = 0 ;
	virtual HRESULT __safecall get_Audio(Winapi::Commontypes::_di_IAudioEncodingProperties &__get_Audio_result) = 0 ;
	virtual HRESULT __safecall put_Video(Winapi::Commontypes::_di_IVideoEncodingProperties value) = 0 ;
	virtual HRESULT __safecall get_Video(Winapi::Commontypes::_di_IVideoEncodingProperties &__get_Video_result) = 0 ;
	virtual HRESULT __safecall put_Container(_di_IContainerEncodingProperties value) = 0 ;
	virtual HRESULT __safecall get_Container(_di_IContainerEncodingProperties &__get_Container_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IAudioEncodingProperties _scw_get_Audio() { Winapi::Commontypes::_di_IAudioEncodingProperties __r; HRESULT __hr = get_Audio(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IAudioEncodingProperties Audio = {read=_scw_get_Audio, write=put_Audio};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IContainerEncodingProperties _scw_get_Container() { _di_IContainerEncodingProperties __r; HRESULT __hr = get_Container(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IContainerEncodingProperties Container = {read=_scw_get_Container, write=put_Container};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IVideoEncodingProperties _scw_get_Video() { Winapi::Commontypes::_di_IVideoEncodingProperties __r; HRESULT __hr = get_Video(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IVideoEncodingProperties Video = {read=_scw_get_Video, write=put_Video};
};

__interface  INTERFACE_UUID("{78625635-F331-4189-B1C3-B48D5AE034F1}") IImageEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Width(unsigned value) = 0 ;
	virtual HRESULT __safecall get_Width(unsigned &__get_Width_result) = 0 ;
	virtual HRESULT __safecall put_Height(unsigned value) = 0 ;
	virtual HRESULT __safecall get_Height(unsigned &__get_Height_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Height() { unsigned __r; HRESULT __hr = get_Height(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Height = {read=_scw_get_Height, write=put_Height};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Width() { unsigned __r; HRESULT __hr = get_Width(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Width = {read=_scw_get_Width, write=put_Width};
};

__interface  INTERFACE_UUID("{7C094AEC-C8F3-5F49-99C7-B66D8414200E}") IIterator_1__IMediaEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{7C094AEC-C8F3-5F49-99C7-B66D8414200E}") IIterator_1__IMediaEncodingProperties  : public IIterator_1__IMediaEncodingProperties_Base 
{
	virtual HRESULT __safecall get_Current(_di_IMediaEncodingProperties &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIMediaEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IMediaEncodingProperties _scw_get_Current() { _di_IMediaEncodingProperties __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IMediaEncodingProperties Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D7FC75D5-3492-5BBB-9B34-DAC3E24E79D0}") IIterable_1__IMediaEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D7FC75D5-3492-5BBB-9B34-DAC3E24E79D0}") IIterable_1__IMediaEncodingProperties  : public IIterable_1__IMediaEncodingProperties_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IMediaEncodingProperties &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{0F6C3B8B-5818-5CBF-BF26-6616BFC308C4}") IVectorView_1__IMediaEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IMediaEncodingProperties &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IMediaEncodingProperties value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIMediaEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{98F10D79-13EA-49FF-BE70-2673DB69702C}") IAudioEncodingPropertiesWithFormatUserData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetFormatUserData(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall GetFormatUserData(unsigned valueSize, System::PByte value) = 0 ;
};

__interface  INTERFACE_UUID("{C45D54DA-80BD-4C23-80D5-72D4A181E894}") IAudioEncodingProperties2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsSpatial(bool &__get_IsSpatial_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsSpatial() { bool __r; HRESULT __hr = get_IsSpatial(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsSpatial = {read=_scw_get_IsSpatial};
};

__interface  INTERFACE_UUID("{0CAD332C-EBE9-4527-B36D-E42A13CF38DB}") IAudioEncodingPropertiesStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateAac(unsigned sampleRate, unsigned channelCount, unsigned bitrate, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateAac_result) = 0 ;
	virtual HRESULT __safecall CreateAacAdts(unsigned sampleRate, unsigned channelCount, unsigned bitrate, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateAacAdts_result) = 0 ;
	virtual HRESULT __safecall CreateMp3(unsigned sampleRate, unsigned channelCount, unsigned bitrate, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateMp3_result) = 0 ;
	virtual HRESULT __safecall CreatePcm(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreatePcm_result) = 0 ;
	virtual HRESULT __safecall CreateWma(unsigned sampleRate, unsigned channelCount, unsigned bitrate, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateWma_result) = 0 ;
};

__interface  INTERFACE_UUID("{7489316F-77A0-433D-8ED5-4040280E8665}") IAudioEncodingPropertiesStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateAlac(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateAlac_result) = 0 ;
	virtual HRESULT __safecall CreateFlac(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample, Winapi::Commontypes::_di_IAudioEncodingProperties &__CreateFlac_result) = 0 ;
};

__interface  INTERFACE_UUID("{F743A1EF-D465-4290-A94B-EF0F1528F8E3}") IVideoEncodingProperties2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetFormatUserData(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall GetFormatUserData(unsigned valueSize, System::PByte value) = 0 ;
	virtual HRESULT __safecall put_ProfileId(int value) = 0 ;
	virtual HRESULT __safecall get_ProfileId(int &__get_ProfileId_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ProfileId() { int __r; HRESULT __hr = get_ProfileId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ProfileId = {read=_scw_get_ProfileId, write=put_ProfileId};
};

__interface  INTERFACE_UUID("{386BCDC4-873A-479F-B3EB-56C1FCBEC6D7}") IVideoEncodingProperties3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_StereoscopicVideoPackingMode(Winapi::Commontypes::StereoscopicVideoPackingMode &__get_StereoscopicVideoPackingMode_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::StereoscopicVideoPackingMode _scw_get_StereoscopicVideoPackingMode() { Winapi::Commontypes::StereoscopicVideoPackingMode __r; HRESULT __hr = get_StereoscopicVideoPackingMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::StereoscopicVideoPackingMode StereoscopicVideoPackingMode = {read=_scw_get_StereoscopicVideoPackingMode};
};

__interface  INTERFACE_UUID("{724EF014-C10C-40F2-9D72-3EE13B45FA8E}") IVideoEncodingProperties4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SphericalVideoFrameFormat(Winapi::Commontypes::SphericalVideoFrameFormat &__get_SphericalVideoFrameFormat_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SphericalVideoFrameFormat _scw_get_SphericalVideoFrameFormat() { Winapi::Commontypes::SphericalVideoFrameFormat __r; HRESULT __hr = get_SphericalVideoFrameFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SphericalVideoFrameFormat SphericalVideoFrameFormat = {read=_scw_get_SphericalVideoFrameFormat};
};

__interface  INTERFACE_UUID("{3CE14D44-1DC5-43DB-9F38-EBEBF90152CB}") IVideoEncodingPropertiesStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateH264(Winapi::Commontypes::_di_IVideoEncodingProperties &__CreateH264_result) = 0 ;
	virtual HRESULT __safecall CreateMpeg2(Winapi::Commontypes::_di_IVideoEncodingProperties &__CreateMpeg2_result) = 0 ;
	virtual HRESULT __safecall CreateUncompressed(HSTRING subtype, unsigned width, unsigned height, Winapi::Commontypes::_di_IVideoEncodingProperties &__CreateUncompressed_result) = 0 ;
};

__interface  INTERFACE_UUID("{CF1EBD5D-49FE-4D00-B59A-CFA4DFC51944}") IVideoEncodingPropertiesStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateHevc(Winapi::Commontypes::_di_IVideoEncodingProperties &__CreateHevc_result) = 0 ;
};

__interface  INTERFACE_UUID("{257C68DC-8B99-439E-AA59-913A36161297}") IImageEncodingPropertiesStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateJpeg(_di_IImageEncodingProperties &__CreateJpeg_result) = 0 ;
	virtual HRESULT __safecall CreatePng(_di_IImageEncodingProperties &__CreatePng_result) = 0 ;
	virtual HRESULT __safecall CreateJpegXR(_di_IImageEncodingProperties &__CreateJpegXR_result) = 0 ;
};

__interface  INTERFACE_UUID("{F6C25B29-3824-46B0-956E-501329E1BE3C}") IImageEncodingPropertiesStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateUncompressed(Winapi::Commontypes::MediaPixelFormat format, _di_IImageEncodingProperties &__CreateUncompressed_result) = 0 ;
	virtual HRESULT __safecall CreateBmp(_di_IImageEncodingProperties &__CreateBmp_result) = 0 ;
};

__interface  INTERFACE_UUID("{37296FC1-86DA-58A0-90C0-C807BD94395E}") AsyncOperationCompletedHandler_1__IMediaEncodingProfile_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{EA573F5C-0121-57EE-A482-BD401D22533A}") AsyncOperationCompletedHandler_1__IMediaEncodingProfile  : public AsyncOperationCompletedHandler_1__IMediaEncodingProfile_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IMediaEncodingProfile asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{D4F86F16-C6CF-57C8-9743-5EC20C31AB79}") IAsyncOperation_1__IMediaEncodingProfile_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B89AC012-9E35-5D18-A44A-CADCEB7268FC}") IAsyncOperation_1__IMediaEncodingProfile  : public IAsyncOperation_1__IMediaEncodingProfile_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IMediaEncodingProfile &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IMediaEncodingProfile Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{197F352C-2EDE-4A45-A896-817A4854F8FE}") IMediaEncodingProfileStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateM4a(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateM4a_result) = 0 ;
	virtual HRESULT __safecall CreateMp3(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateMp3_result) = 0 ;
	virtual HRESULT __safecall CreateWma(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateWma_result) = 0 ;
	virtual HRESULT __safecall CreateMp4(Winapi::Commontypes::VideoEncodingQuality quality, _di_IMediaEncodingProfile &__CreateMp4_result) = 0 ;
	virtual HRESULT __safecall CreateWmv(Winapi::Commontypes::VideoEncodingQuality quality, _di_IMediaEncodingProfile &__CreateWmv_result) = 0 ;
	virtual HRESULT __safecall CreateFromFileAsync(Winapi::Commontypes::_di_IStorageFile file, _di_IAsyncOperation_1__IMediaEncodingProfile &__CreateFromFileAsync_result) = 0 ;
	virtual HRESULT __safecall CreateFromStreamAsync(Winapi::Commontypes::_di_IRandomAccessStream stream, _di_IAsyncOperation_1__IMediaEncodingProfile &__CreateFromStreamAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{CE8DE74F-6AF4-4288-8FE2-79ADF1F79A43}") IMediaEncodingProfileStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWav(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateWav_result) = 0 ;
	virtual HRESULT __safecall CreateAvi(Winapi::Commontypes::VideoEncodingQuality quality, _di_IMediaEncodingProfile &__CreateAvi_result) = 0 ;
};

__interface  INTERFACE_UUID("{90DAC5AA-CF76-4294-A9ED-1A1420F51F6B}") IMediaEncodingProfileStatics3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateAlac(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateAlac_result) = 0 ;
	virtual HRESULT __safecall CreateFlac(Winapi::Commontypes::AudioEncodingQuality quality, _di_IMediaEncodingProfile &__CreateFlac_result) = 0 ;
	virtual HRESULT __safecall CreateHevc(Winapi::Commontypes::VideoEncodingQuality quality, _di_IMediaEncodingProfile &__CreateHevc_result) = 0 ;
};

__interface  INTERFACE_UUID("{349B3E0A-4035-488E-9877-85632865ED10}") IMediaEncodingProfile2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetAudioTracks(Winapi::Commontypes::_di_IIterable_1__Core_IAudioStreamDescriptor value) = 0 ;
	virtual HRESULT __safecall GetAudioTracks(Winapi::Commontypes::_di_IVector_1__Core_IAudioStreamDescriptor &__GetAudioTracks_result) = 0 ;
	virtual HRESULT __safecall SetVideoTracks(Winapi::Commontypes::_di_IIterable_1__Core_IVideoStreamDescriptor value) = 0 ;
	virtual HRESULT __safecall GetVideoTracks(Winapi::Commontypes::_di_IVector_1__Core_IVideoStreamDescriptor &__GetVideoTracks_result) = 0 ;
};

__interface  INTERFACE_UUID("{094166EF-AE5F-5315-A3BF-FE54E8C35FCD}") IIterator_1__IVideoEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BCF430E8-92CF-5D32-9D66-CA3BA7EB02B3}") IIterator_1__IVideoEncodingProperties  : public IIterator_1__IVideoEncodingProperties_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IVideoEncodingProperties &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIVideoEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IVideoEncodingProperties _scw_get_Current() { Winapi::Commontypes::_di_IVideoEncodingProperties __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IVideoEncodingProperties Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{73C7317C-8682-5F81-84A2-30C425FA2D24}") IIterable_1__IVideoEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{33989EE8-DF57-522A-904C-C824469A24D3}") IIterable_1__IVideoEncodingProperties  : public IIterable_1__IVideoEncodingProperties_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IVideoEncodingProperties &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{DB7651E0-A202-50EE-9814-D739E8D01CB2}") IVectorView_1__IVideoEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IVideoEncodingProperties &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IVideoEncodingProperties value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIVideoEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{064B6AEF-3BD0-5463-8450-72C6169AF5D4}") IIterator_1__IAudioEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6050A010-2204-5ACC-BB40-2151822324A4}") IIterator_1__IAudioEncodingProperties  : public IIterator_1__IAudioEncodingProperties_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IAudioEncodingProperties &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIAudioEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IAudioEncodingProperties _scw_get_Current() { Winapi::Commontypes::_di_IAudioEncodingProperties __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IAudioEncodingProperties Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{00939468-25D8-533F-854E-4F20F36C51DC}") IIterable_1__IAudioEncodingProperties_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{86D0739C-26C6-5CD4-87D1-6550DC0B634B}") IIterable_1__IAudioEncodingProperties  : public IIterable_1__IAudioEncodingProperties_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IAudioEncodingProperties &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{51F8BE1E-AB49-5465-94A7-650DE058774C}") IVectorView_1__IAudioEncodingProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::_di_IAudioEncodingProperties &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::_di_IAudioEncodingProperties value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PIAudioEncodingProperties items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMediaPropertySet : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMediaPropertySet() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Applicationmodel::_di_IMap_2__TGuid__IInspectable>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMediaPropertySet() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAudioEncodingProperties : public System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IAudioEncodingPropertiesStatics,_di_IAudioEncodingPropertiesStatics2,Winapi::Commontypes::_di_IAudioEncodingProperties>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IAudioEncodingPropertiesStatics,_di_IAudioEncodingPropertiesStatics2,Winapi::Commontypes::_di_IAudioEncodingProperties> inherited;
	
public:
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateAac(unsigned sampleRate, unsigned channelCount, unsigned bitrate);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateAacAdts(unsigned sampleRate, unsigned channelCount, unsigned bitrate);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateMp3(unsigned sampleRate, unsigned channelCount, unsigned bitrate);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreatePcm(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateWma(unsigned sampleRate, unsigned channelCount, unsigned bitrate);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateAlac(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample);
	static Winapi::Commontypes::_di_IAudioEncodingProperties __fastcall CreateFlac(unsigned sampleRate, unsigned channelCount, unsigned bitsPerSample);
public:
	/* TObject.Create */ inline __fastcall TAudioEncodingProperties() : System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IAudioEncodingPropertiesStatics,_di_IAudioEncodingPropertiesStatics2,Winapi::Commontypes::_di_IAudioEncodingProperties>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAudioEncodingProperties() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TVideoEncodingProperties : public System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IVideoEncodingPropertiesStatics,_di_IVideoEncodingPropertiesStatics2,Winapi::Commontypes::_di_IVideoEncodingProperties>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IVideoEncodingPropertiesStatics,_di_IVideoEncodingPropertiesStatics2,Winapi::Commontypes::_di_IVideoEncodingProperties> inherited;
	
public:
	static Winapi::Commontypes::_di_IVideoEncodingProperties __fastcall CreateHevc();
	static Winapi::Commontypes::_di_IVideoEncodingProperties __fastcall CreateH264();
	static Winapi::Commontypes::_di_IVideoEncodingProperties __fastcall CreateMpeg2();
	static Winapi::Commontypes::_di_IVideoEncodingProperties __fastcall CreateUncompressed(HSTRING subtype, unsigned width, unsigned height);
public:
	/* TObject.Create */ inline __fastcall TVideoEncodingProperties() : System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IVideoEncodingPropertiesStatics,_di_IVideoEncodingPropertiesStatics2,Winapi::Commontypes::_di_IVideoEncodingProperties>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TVideoEncodingProperties() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TImageEncodingProperties : public System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IImageEncodingPropertiesStatics,_di_IImageEncodingPropertiesStatics2,_di_IImageEncodingProperties>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IImageEncodingPropertiesStatics,_di_IImageEncodingPropertiesStatics2,_di_IImageEncodingProperties> inherited;
	
public:
	static _di_IImageEncodingProperties __fastcall CreateJpeg();
	static _di_IImageEncodingProperties __fastcall CreatePng();
	static _di_IImageEncodingProperties __fastcall CreateJpegXR();
	static _di_IImageEncodingProperties __fastcall CreateUncompressed(Winapi::Commontypes::MediaPixelFormat format);
	static _di_IImageEncodingProperties __fastcall CreateBmp();
public:
	/* TObject.Create */ inline __fastcall TImageEncodingProperties() : System::Win::Winrt::TWinRTGenericImportS2I__3<_di_IImageEncodingPropertiesStatics,_di_IImageEncodingPropertiesStatics2,_di_IImageEncodingProperties>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TImageEncodingProperties() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TContainerEncodingProperties : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IContainerEncodingProperties>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IContainerEncodingProperties> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TContainerEncodingProperties() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IContainerEncodingProperties>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TContainerEncodingProperties() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMediaEncodingProfile : public System::Win::Winrt::TWinRTGenericImportS3I__4<_di_IMediaEncodingProfileStatics,_di_IMediaEncodingProfileStatics2,_di_IMediaEncodingProfileStatics3,_di_IMediaEncodingProfile>
{
	typedef System::Win::Winrt::TWinRTGenericImportS3I__4<_di_IMediaEncodingProfileStatics,_di_IMediaEncodingProfileStatics2,_di_IMediaEncodingProfileStatics3,_di_IMediaEncodingProfile> inherited;
	
public:
	static _di_IMediaEncodingProfile __fastcall CreateWav(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateAvi(Winapi::Commontypes::VideoEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateM4a(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateMp3(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateWma(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateMp4(Winapi::Commontypes::VideoEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateWmv(Winapi::Commontypes::VideoEncodingQuality quality);
	static _di_IAsyncOperation_1__IMediaEncodingProfile __fastcall CreateFromFileAsync(Winapi::Commontypes::_di_IStorageFile file);
	static _di_IAsyncOperation_1__IMediaEncodingProfile __fastcall CreateFromStreamAsync(Winapi::Commontypes::_di_IRandomAccessStream stream);
	static _di_IMediaEncodingProfile __fastcall CreateAlac(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateFlac(Winapi::Commontypes::AudioEncodingQuality quality);
	static _di_IMediaEncodingProfile __fastcall CreateHevc(Winapi::Commontypes::VideoEncodingQuality quality);
public:
	/* TObject.Create */ inline __fastcall TMediaEncodingProfile() : System::Win::Winrt::TWinRTGenericImportS3I__4<_di_IMediaEncodingProfileStatics,_di_IMediaEncodingProfileStatics2,_di_IMediaEncodingProfileStatics3,_di_IMediaEncodingProfile>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMediaEncodingProfile() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mediaproperties */
}	/* namespace Media */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Media_MediapropertiesHPP
