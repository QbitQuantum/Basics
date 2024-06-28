// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MediaLibrary.Actions.pas' rev: 34.00 (iOS)

#ifndef Fmx_Medialibrary_ActionsHPP
#define Fmx_Medialibrary_ActionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.MediaLibrary.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.StdActns.hpp>
#include <FMX.Consts.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Medialibrary
{
namespace Actions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomTakePhotoAction;
class DELPHICLASS TTakePhotoFromCameraAction;
class DELPHICLASS TTakePhotoFromLibraryAction;
class DELPHICLASS TShowShareSheetAction;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomTakePhotoAction : public Fmx::Stdactns::TSysCommonAction
{
	typedef Fmx::Stdactns::TSysCommonAction inherited;
	
public:
	static constexpr System::Word DefaultMaxWidth = System::Word(0x400);
	
	static constexpr System::Word DefaultMaxHeight = System::Word(0x400);
	
	static constexpr bool DefaultEditable = false;
	
	static constexpr bool DefaultNeedSaveToAlbum = false;
	
	
private:
	bool FEditable;
	bool FNeedSaveToAlbum;
	unsigned FMaxWidth;
	unsigned FMaxHeight;
	Fmx::Medialibrary::TOnDidCancelTaking FOnDidCancelTaking;
	Fmx::Medialibrary::TOnDidFinishTaking FOnDidFinishTaking;
	Fmx::Controls::TControl* __fastcall GetTargetControl();
	void __fastcall DidCancelTaking(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	
protected:
	virtual void __fastcall DoCancelTaking();
	virtual void __fastcall DoFinishedTakingImage(Fmx::Graphics::TBitmap* AImage);
	Fmx::Medialibrary::TParamsPhotoQuery __fastcall GetParamsPhotoQuery();
	__property bool NeedSaveToAlbum = {read=FNeedSaveToAlbum, write=FNeedSaveToAlbum, default=0};
	
public:
	__fastcall virtual TCustomTakePhotoAction(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomTakePhotoAction();
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	__property Fmx::Controls::TControl* TargetControl = {read=GetTargetControl};
	__property bool Editable = {read=FEditable, write=FEditable, default=0};
	__property unsigned MaxHeight = {read=FMaxHeight, write=FMaxHeight, default=1024};
	__property unsigned MaxWidth = {read=FMaxWidth, write=FMaxWidth, default=1024};
	__property Fmx::Medialibrary::TOnDidCancelTaking OnDidCancelTaking = {read=FOnDidCancelTaking, write=FOnDidCancelTaking};
	__property Fmx::Medialibrary::TOnDidFinishTaking OnDidFinishTaking = {read=FOnDidFinishTaking, write=FOnDidFinishTaking};
};


class PASCALIMPLEMENTATION TTakePhotoFromCameraAction : public TCustomTakePhotoAction
{
	typedef TCustomTakePhotoAction inherited;
	
private:
	Fmx::Medialibrary::_di_IFMXCameraService FCameraService;
	void __fastcall DidReceiveBitmap(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	
protected:
	virtual void __fastcall CustomTextChanged();
	virtual bool __fastcall IsSupportedInterface();
	
public:
	__fastcall virtual TTakePhotoFromCameraAction(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTakePhotoFromCameraAction();
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property Editable = {default=0};
	__property MaxHeight = {default=1024};
	__property MaxWidth = {default=1024};
	__property NeedSaveToAlbum = {default=0};
	__property OnDidCancelTaking;
	__property OnDidFinishTaking;
};


class PASCALIMPLEMENTATION TTakePhotoFromLibraryAction : public TCustomTakePhotoAction
{
	typedef TCustomTakePhotoAction inherited;
	
private:
	Fmx::Medialibrary::_di_IFMXTakenImageService FTakenImageService;
	void __fastcall DidReceiveBitmap(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	
protected:
	virtual void __fastcall CustomTextChanged();
	virtual bool __fastcall IsSupportedInterface();
	
public:
	__fastcall virtual TTakePhotoFromLibraryAction(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTakePhotoFromLibraryAction();
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property Editable = {default=0};
	__property MaxHeight = {default=1024};
	__property MaxWidth = {default=1024};
	__property OnDidCancelTaking;
	__property OnDidFinishTaking;
};


class PASCALIMPLEMENTATION TShowShareSheetAction : public Fmx::Stdactns::TSysCommonAction
{
	typedef Fmx::Stdactns::TSysCommonAction inherited;
	
private:
	Fmx::Medialibrary::_di_IFMXShareSheetActionsService FSharingService;
	Fmx::Graphics::TBitmap* FBitmap;
	System::UnicodeString FMessage;
	System::Classes::TNotifyEvent FOnBeforeExecute;
	
private:
	void __fastcall SetBitmap(Fmx::Graphics::TBitmap* const Value);
	
protected:
	void __fastcall DoBeforeExecute();
	virtual void __fastcall CustomTextChanged();
	virtual bool __fastcall IsSupportedInterface();
	
public:
	__fastcall virtual TShowShareSheetAction(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TShowShareSheetAction();
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property Fmx::Graphics::TBitmap* Bitmap = {read=FBitmap, write=SetBitmap};
	__property System::UnicodeString TextMessage = {read=FMessage, write=FMessage};
	__property System::Classes::TNotifyEvent OnBeforeExecute = {read=FOnBeforeExecute, write=FOnBeforeExecute};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Actions */
}	/* namespace Medialibrary */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEDIALIBRARY_ACTIONS)
using namespace Fmx::Medialibrary::Actions;
#endif
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
#endif	// Fmx_Medialibrary_ActionsHPP
