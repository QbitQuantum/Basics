// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MediaLibrary.pas' rev: 34.00 (iOS)

#ifndef Fmx_MedialibraryHPP
#define Fmx_MedialibraryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------
namespace Fmx
{
namespace Medialibrary
{
  _INIT_UNIT(Fmx_Medialibrary);
}	/* namespace Medialibrary */
}	/* namespace Fmx */

namespace Fmx
{
namespace Medialibrary
{
//-- forward type declarations -----------------------------------------------
struct TLocationInfo;
class DELPHICLASS TImageInfo;
__interface DELPHIINTERFACE IFMXImageManagerService;
typedef System::DelphiInterface<IFMXImageManagerService> _di_IFMXImageManagerService;
__interface DELPHIINTERFACE IFMXPhotoLibrary;
typedef System::DelphiInterface<IFMXPhotoLibrary> _di_IFMXPhotoLibrary;
class DELPHICLASS TMessageDidCancelTaking;
class DELPHICLASS TMessageDidFinishTakingImageFromCamera;
class DELPHICLASS TMessageDidFinishTakingImageFromLibrary;
struct TParamsPhotoQuery;
__interface DELPHIINTERFACE IFMXTakenImageService;
typedef System::DelphiInterface<IFMXTakenImageService> _di_IFMXTakenImageService;
__interface DELPHIINTERFACE IFMXCameraService;
typedef System::DelphiInterface<IFMXCameraService> _di_IFMXCameraService;
class DELPHICLASS TMediaInfo;
class DELPHICLASS TAudioInfo;
class DELPHICLASS TAlbum;
class DELPHICLASS TArtist;
class DELPHICLASS TGenre;
__interface DELPHIINTERFACE IFMXAudioManagerService;
typedef System::DelphiInterface<IFMXAudioManagerService> _di_IFMXAudioManagerService;
__interface DELPHIINTERFACE IFMXTakenAudioService;
typedef System::DelphiInterface<IFMXTakenAudioService> _di_IFMXTakenAudioService;
class DELPHICLASS TVideoInfo;
__interface DELPHIINTERFACE IFMXVideoManagerService;
typedef System::DelphiInterface<IFMXVideoManagerService> _di_IFMXVideoManagerService;
__interface DELPHIINTERFACE IFMXShareSheetActionsService;
typedef System::DelphiInterface<IFMXShareSheetActionsService> _di_IFMXShareSheetActionsService;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TImageOrientation : unsigned char { Up, Right, Down, Left };

struct DECLSPEC_DRECORD TLocationInfo
{
public:
	double Latitude;
	double Longitude;
};


class PASCALIMPLEMENTATION TImageInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual Fmx::Graphics::TBitmap* __fastcall Bitmap() = 0 ;
	virtual System::TDateTime __fastcall DateTaken() = 0 ;
	virtual TImageOrientation __fastcall Orientation() = 0 ;
	virtual TLocationInfo __fastcall LocationInfo() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TImageInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TImageInfo() { }
	
};


typedef System::DynamicArray<TImageInfo*> TImages;

__interface  INTERFACE_UUID("{F06A5B8F-D4BC-4A0D-AD91-BF49208861E4}") IFMXImageManagerService  : public System::IInterface 
{
	virtual TImageInfo* __fastcall GetImage(const int Index) = 0 ;
	virtual TImages __fastcall GetAllImages() = 0 ;
	virtual int __fastcall GetCount() = 0 ;
	virtual void __fastcall InsertImage(Fmx::Graphics::TBitmap* const Bitmap) = 0 ;
};

typedef void __fastcall (__closure *TWriteImageCompletionEvent)(const bool ASaved, const System::UnicodeString AResultMessage);

__interface  INTERFACE_UUID("{D10DE62A-7398-4BC6-AA4C-AF5F4382BC46}") IFMXPhotoLibrary  : public System::IInterface 
{
	virtual void __fastcall AddImageToSavedPhotosAlbum(Fmx::Graphics::TBitmap* const ABitmap, const TWriteImageCompletionEvent AWriteImageCompletionEvent = 0x0) = 0 ;
};

typedef void __fastcall (__closure *TOnDidCancelTaking)(void);

typedef void __fastcall (__closure *TOnDidFinishTaking)(Fmx::Graphics::TBitmap* Image);

class PASCALIMPLEMENTATION TMessageDidCancelTaking : public System::Messaging::TMessageBase
{
	typedef System::Messaging::TMessageBase inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMessageDidCancelTaking() : System::Messaging::TMessageBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMessageDidCancelTaking() { }
	
};


class PASCALIMPLEMENTATION TMessageDidFinishTakingImageFromCamera : public System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*>
{
	typedef System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*> inherited;
	
public:
	/* {System_Messaging}TMessage<FMX_Graphics_TBitmap>.Create */ inline __fastcall TMessageDidFinishTakingImageFromCamera(Fmx::Graphics::TBitmap* const AValue) : System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*>(AValue) { }
	/* {System_Messaging}TMessage<FMX_Graphics_TBitmap>.Destroy */ inline __fastcall virtual ~TMessageDidFinishTakingImageFromCamera() { }
	
};


class PASCALIMPLEMENTATION TMessageDidFinishTakingImageFromLibrary : public System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*>
{
	typedef System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*> inherited;
	
public:
	/* {System_Messaging}TMessage<FMX_Graphics_TBitmap>.Create */ inline __fastcall TMessageDidFinishTakingImageFromLibrary(Fmx::Graphics::TBitmap* const AValue) : System::Messaging::TMessage__1<Fmx::Graphics::TBitmap*>(AValue) { }
	/* {System_Messaging}TMessage<FMX_Graphics_TBitmap>.Destroy */ inline __fastcall virtual ~TMessageDidFinishTakingImageFromLibrary() { }
	
};


struct DECLSPEC_DRECORD TParamsPhotoQuery
{
public:
	System::Types::TSize RequiredResolution;
	bool Editable;
	bool NeedSaveToAlbum;
	TOnDidFinishTaking OnDidFinishTaking;
	TOnDidCancelTaking OnDidCancelTaking;
};


__interface  INTERFACE_UUID("{5DADF207-B6CE-4C3A-9E0F-C45B39128DA5}") IFMXTakenImageService  : public System::IInterface 
{
	virtual void __fastcall TakeImageFromLibrary _DEPRECATED_ATTRIBUTE1("Use the similar method with another parameters") (Fmx::Controls::TControl* const AControl, const System::Types::TSize &ARequiredResolution, const bool AEditable, const TOnDidFinishTaking AOnDidFinishTaking, const TOnDidCancelTaking AOnDidCancelTaking) = 0 /* overload */;
	virtual void __fastcall TakeImageFromLibrary(Fmx::Controls::TControl* const AControl, const TParamsPhotoQuery &AParams) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{6779963D-633A-4ED0-80C8-C71AB4E26D91}") IFMXCameraService  : public System::IInterface 
{
	virtual void __fastcall TakePhoto _DEPRECATED_ATTRIBUTE1("Use the similar method with another parameters") (Fmx::Controls::TControl* const AControl, const System::Types::TSize &ARequiredResolution, const bool AEditable, const TOnDidFinishTaking AOnDidFinishTaking, const TOnDidCancelTaking AOnDidCancelTaking) = 0 /* overload */;
	virtual void __fastcall TakePhoto(Fmx::Controls::TControl* const AControl, const TParamsPhotoQuery &AParams) = 0 /* overload */;
};

class PASCALIMPLEMENTATION TMediaInfo : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMediaInfo() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMediaInfo() { }
	
};


typedef System::DynamicArray<TMediaInfo*> TPlayList;

class PASCALIMPLEMENTATION TAudioInfo : public TMediaInfo
{
	typedef TMediaInfo inherited;
	
public:
	virtual System::UnicodeString __fastcall Title() = 0 ;
	virtual System::UnicodeString __fastcall Artist() = 0 ;
	virtual System::UnicodeString __fastcall AlbumTitle() = 0 ;
	virtual System::UnicodeString __fastcall AlbumArtist() = 0 ;
	virtual System::UnicodeString __fastcall Genre() = 0 ;
	virtual System::UnicodeString __fastcall Composer() = 0 ;
	virtual System::TTime __fastcall Duration() = 0 ;
	virtual unsigned __fastcall AlbumTrackNumber() = 0 ;
	virtual unsigned __fastcall DiscNumber() = 0 ;
	virtual System::UnicodeString __fastcall Lyrics() = 0 ;
	virtual Fmx::Graphics::TBitmap* __fastcall DiscCover() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TAudioInfo() : TMediaInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAudioInfo() { }
	
};


typedef System::DynamicArray<TAudioInfo*> TAudios;

class PASCALIMPLEMENTATION TAlbum : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall Title() = 0 ;
	virtual System::UnicodeString __fastcall Artist() = 0 ;
	virtual unsigned __fastcall NumberOfSongs() = 0 ;
	virtual Fmx::Graphics::TBitmap* __fastcall Cover() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TAlbum() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAlbum() { }
	
};


typedef System::DynamicArray<TAlbum*> TAlbums;

class PASCALIMPLEMENTATION TArtist : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall Artist() = 0 ;
	virtual int __fastcall NumberOfSongs() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TArtist() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TArtist() { }
	
};


typedef System::DynamicArray<TArtist*> TArtists;

class PASCALIMPLEMENTATION TGenre : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall Genre() = 0 ;
	virtual unsigned __fastcall CountSongs() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TGenre() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGenre() { }
	
};


typedef System::DynamicArray<TGenre*> TGenres;

__interface  INTERFACE_UUID("{E2D6C4F8-F365-4E24-A461-C48288E4C710}") IFMXAudioManagerService  : public System::IInterface 
{
	virtual TAudioInfo* __fastcall GetAudio(const int Index) = 0 ;
	virtual TAudios __fastcall GetAudios() = 0 /* overload */;
	virtual TAudios __fastcall GetAudios(TAlbum* const Album) = 0 /* overload */;
	virtual TAudios __fastcall GetAudios(TArtist* const Artist) = 0 /* overload */;
	virtual TAudios __fastcall GetAudios(TGenre* const Genre) = 0 /* overload */;
	virtual TAlbums __fastcall GetAlbums() = 0 ;
	virtual TArtists __fastcall GetArtists() = 0 ;
	virtual TGenres __fastcall GetGenres() = 0 ;
};

__interface  INTERFACE_UUID("{7114C6A2-2A2A-4CDA-AB63-291C7C8D440E}") IFMXTakenAudioService  : public System::IInterface 
{
	virtual TAudios __fastcall GetAudioFromLibrary() = 0 ;
};

class PASCALIMPLEMENTATION TVideoInfo : public TMediaInfo
{
	typedef TMediaInfo inherited;
	
public:
	virtual System::UnicodeString __fastcall Title() = 0 ;
	virtual System::UnicodeString __fastcall AlbumTitle() = 0 ;
	virtual System::UnicodeString __fastcall Artist() = 0 ;
	virtual System::TTime __fastcall Duration() = 0 ;
	virtual System::Types::TSize __fastcall Resolution() = 0 ;
	virtual Fmx::Graphics::TBitmap* __fastcall Thumb() = 0 ;
public:
	/* TObject.Create */ inline __fastcall TVideoInfo() : TMediaInfo() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TVideoInfo() { }
	
};


typedef System::DynamicArray<TVideoInfo*> TVideos;

__interface  INTERFACE_UUID("{C61ECA12-EF39-4FAF-A301-B8BA43F425BD}") IFMXVideoManagerService  : public System::IInterface 
{
	virtual TVideos __fastcall GetVideoFromLibrary() = 0 ;
	virtual TVideoInfo* __fastcall GetVideo(const int Index) = 0 ;
	virtual TVideos __fastcall GetAllVideos() = 0 ;
};

__interface  INTERFACE_UUID("{79FCC7B1-C5BF-4533-B31E-084F1A6E2264}") IFMXShareSheetActionsService  : public System::IInterface 
{
	virtual void __fastcall Share(Fmx::Controls::TControl* const AControl, const System::UnicodeString AText, Fmx::Graphics::TBitmap* const AImage) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Medialibrary */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIALIBRARY)
using namespace Fmx::Medialibrary;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_MedialibraryHPP
