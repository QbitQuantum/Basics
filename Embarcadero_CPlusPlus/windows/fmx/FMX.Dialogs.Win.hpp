// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Dialogs.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dialogs_WinHPP
#define Fmx_Dialogs_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ShlObj.hpp>
#include <Winapi.Windows.hpp>
#include <System.UITypes.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Dialogs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dialogs
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EPlatformVersionException;
class DELPHICLASS TFileTypeItem;
class DELPHICLASS TFileTypeItems;
class DELPHICLASS TFavoriteLinkItem;
class DELPHICLASS TFavoriteLinkItemsEnumerator;
class DELPHICLASS TFavoriteLinkItems;
class DELPHICLASS TCustomFileDialog;
class DELPHICLASS TCustomFileOpenDialog;
class DELPHICLASS TFileOpenDialog;
class DELPHICLASS TCustomFileSaveDialog;
class DELPHICLASS TFileSaveDialog;
class DELPHICLASS TFileDialogWrapper;
class DELPHICLASS TFileOpenDialogWrapper;
class DELPHICLASS TFileSaveDialogWrapper;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EPlatformVersionException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPlatformVersionException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPlatformVersionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPlatformVersionException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPlatformVersionException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPlatformVersionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPlatformVersionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPlatformVersionException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPlatformVersionException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPlatformVersionException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPlatformVersionException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPlatformVersionException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPlatformVersionException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPlatformVersionException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TFileDialogShareViolationResponse : unsigned char { Default, Accept, Refuse };

enum class DECLSPEC_DENUM TFileDialogOption : unsigned char { OverWritePrompt, StrictFileTypes, NoChangeDir, PickFolders, ForceFileSystem, AllNonStorageItems, NoValidate, AllowMultiSelect, PathMustExist, FileMustExist, CreatePrompt, ShareAware, NoReadOnlyReturn, NoTestFileCreate, HideMRUPlaces, HidePinnedPlaces, NoDereferenceLinks, DontAddToRecent, ForceShowHidden, DefaultNoMiniMode, ForcePreviewPaneOn };

typedef System::Set<TFileDialogOption, _DELPHI_SET_ENUMERATOR(TFileDialogOption::OverWritePrompt), _DELPHI_SET_ENUMERATOR(TFileDialogOption::ForcePreviewPaneOn)> TFileDialogOptions;

typedef void __fastcall (__closure *TFileDialogCloseEvent)(System::TObject* Sender, bool &CanClose);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileTypeItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FDisplayName;
	System::UnicodeString FFileMask;
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TFileTypeItem(System::Classes::TCollection* Collection);
	
__published:
	__property System::UnicodeString DisplayName = {read=FDisplayName, write=FDisplayName};
	__property System::UnicodeString FileMask = {read=FFileMask, write=FFileMask};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TFileTypeItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileTypeItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TFileTypeItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TFileTypeItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TFileTypeItem* const Value);
	
public:
	HIDESBASE TFileTypeItem* __fastcall Add();
	Winapi::Shlobj::TComdlgFilterSpecArray __fastcall FilterSpecArray();
	__property TFileTypeItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TFileTypeItems(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TFileTypeItems() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFavoriteLinkItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FLocation;
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
__published:
	__property System::UnicodeString Location = {read=FLocation, write=FLocation};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TFavoriteLinkItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TFavoriteLinkItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFavoriteLinkItemsEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	TFavoriteLinkItems* FCollection;
	
public:
	__fastcall TFavoriteLinkItemsEnumerator(TFavoriteLinkItems* ACollection);
	TFavoriteLinkItem* __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TFavoriteLinkItem* Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFavoriteLinkItemsEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFavoriteLinkItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TFavoriteLinkItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TFavoriteLinkItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TFavoriteLinkItem* const Value);
	
public:
	HIDESBASE TFavoriteLinkItem* __fastcall Add();
	HIDESBASE TFavoriteLinkItemsEnumerator* __fastcall GetEnumerator();
	__property TFavoriteLinkItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Create */ inline __fastcall TFavoriteLinkItems(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	/* TCollection.Destroy */ inline __fastcall virtual ~TFavoriteLinkItems() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomFileDialog : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FClientGuid;
	System::UnicodeString FDefaultExtension;
	System::UnicodeString FDefaultFolder;
	_di_IFileDialog FDialog;
	TFavoriteLinkItems* FFavoriteLinks;
	System::Sysutils::TFileName FFileName;
	System::UnicodeString FFileNameLabel;
	System::Classes::TStrings* FFiles;
	unsigned FFileTypeIndex;
	TFileTypeItems* FFileTypes;
	HWND FHandle;
	System::UnicodeString FOkButtonLabel;
	TFileDialogOptions FOptions;
	_di_IShellItem FShellItem;
	_di_IShellItemArray FShellItems;
	System::UnicodeString FTitle;
	System::Classes::TNotifyEvent FOnExecute;
	TFileDialogCloseEvent FOnFileOkClick;
	System::Sysutils::TFileName FActualFolder;
	System::UnicodeString __fastcall GetDefaultFolder();
	System::Sysutils::TFileName __fastcall GetFileName();
	System::Classes::TStrings* __fastcall GetFiles();
	void __fastcall SetClientGuid(const System::UnicodeString Value);
	void __fastcall SetDefaultFolder(const System::UnicodeString Value);
	void __fastcall SetFavoriteLinks(TFavoriteLinkItems* const Value);
	void __fastcall SetFileName(const System::Sysutils::TFileName Value);
	void __fastcall SetFileTypes(TFileTypeItems* const Value);
	
protected:
	virtual _di_IFileDialog __fastcall CreateFileDialog() = 0 ;
	DYNAMIC void __fastcall DoOnExecute();
	DYNAMIC bool __fastcall DoOnFileOkClick();
	DYNAMIC HRESULT __fastcall GetFileNames(_di_IShellItemArray Items);
	DYNAMIC HRESULT __fastcall GetItemName(_di_IShellItem Item, System::Sysutils::TFileName &ItemName);
	virtual HRESULT __fastcall GetResults();
	
protected:
	DYNAMIC HRESULT __fastcall FileOkClick();
	
public:
	__fastcall virtual TCustomFileDialog(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomFileDialog();
	virtual bool __fastcall Execute()/* overload */;
	virtual bool __fastcall Execute(HWND ParentWnd)/* overload */;
	__property System::UnicodeString ClientGuid = {read=FClientGuid, write=SetClientGuid};
	__property System::UnicodeString DefaultExtension = {read=FDefaultExtension, write=FDefaultExtension};
	__property System::UnicodeString DefaultFolder = {read=GetDefaultFolder, write=SetDefaultFolder};
	__property _di_IFileDialog Dialog = {read=FDialog};
	__property TFavoriteLinkItems* FavoriteLinks = {read=FFavoriteLinks, write=SetFavoriteLinks};
	__property System::Sysutils::TFileName FileName = {read=GetFileName, write=SetFileName};
	__property System::UnicodeString FileNameLabel = {read=FFileNameLabel, write=FFileNameLabel};
	__property System::Classes::TStrings* Files = {read=GetFiles};
	__property TFileTypeItems* FileTypes = {read=FFileTypes, write=SetFileTypes};
	__property unsigned FileTypeIndex = {read=FFileTypeIndex, write=FFileTypeIndex, default=1};
#ifndef _WIN64
	__property HWND Handle = {read=FHandle, nodefault};
#else /* _WIN64 */
	__property HWND Handle = {read=FHandle};
#endif /* _WIN64 */
	__property System::UnicodeString OkButtonLabel = {read=FOkButtonLabel, write=FOkButtonLabel};
	__property TFileDialogOptions Options = {read=FOptions, write=FOptions, nodefault};
	__property _di_IShellItem ShellItem = {read=FShellItem};
	__property _di_IShellItemArray ShellItems = {read=FShellItems};
	__property System::UnicodeString Title = {read=FTitle, write=FTitle};
	__property System::Classes::TNotifyEvent OnExecute = {read=FOnExecute, write=FOnExecute};
	__property TFileDialogCloseEvent OnFileOkClick = {read=FOnFileOkClick, write=FOnFileOkClick};
};


class PASCALIMPLEMENTATION TCustomFileOpenDialog : public TCustomFileDialog
{
	typedef TCustomFileDialog inherited;
	
protected:
	virtual _di_IFileDialog __fastcall CreateFileDialog();
	virtual HRESULT __fastcall GetResults();
public:
	/* TCustomFileDialog.Create */ inline __fastcall virtual TCustomFileOpenDialog(System::Classes::TComponent* AOwner) : TCustomFileDialog(AOwner) { }
	/* TCustomFileDialog.Destroy */ inline __fastcall virtual ~TCustomFileOpenDialog() { }
	
};


class PASCALIMPLEMENTATION TFileOpenDialog : public TCustomFileOpenDialog
{
	typedef TCustomFileOpenDialog inherited;
	
__published:
	__property ClientGuid = {default=0};
	__property DefaultExtension = {default=0};
	__property DefaultFolder = {default=0};
	__property FavoriteLinks;
	__property FileName = {default=0};
	__property FileNameLabel = {default=0};
	__property FileTypes;
	__property FileTypeIndex = {default=1};
	__property OkButtonLabel = {default=0};
	__property Options;
	__property Title = {default=0};
	__property OnExecute;
	__property OnFileOkClick;
public:
	/* TCustomFileDialog.Create */ inline __fastcall virtual TFileOpenDialog(System::Classes::TComponent* AOwner) : TCustomFileOpenDialog(AOwner) { }
	/* TCustomFileDialog.Destroy */ inline __fastcall virtual ~TFileOpenDialog() { }
	
};


class PASCALIMPLEMENTATION TCustomFileSaveDialog : public TCustomFileDialog
{
	typedef TCustomFileDialog inherited;
	
protected:
	virtual _di_IFileDialog __fastcall CreateFileDialog();
public:
	/* TCustomFileDialog.Create */ inline __fastcall virtual TCustomFileSaveDialog(System::Classes::TComponent* AOwner) : TCustomFileDialog(AOwner) { }
	/* TCustomFileDialog.Destroy */ inline __fastcall virtual ~TCustomFileSaveDialog() { }
	
};


class PASCALIMPLEMENTATION TFileSaveDialog : public TCustomFileSaveDialog
{
	typedef TCustomFileSaveDialog inherited;
	
__published:
	__property ClientGuid = {default=0};
	__property DefaultExtension = {default=0};
	__property DefaultFolder = {default=0};
	__property FavoriteLinks;
	__property FileName = {default=0};
	__property FileNameLabel = {default=0};
	__property FileTypes;
	__property FileTypeIndex = {default=1};
	__property OkButtonLabel = {default=0};
	__property Options;
	__property Title = {default=0};
	__property OnExecute;
	__property OnFileOkClick;
public:
	/* TCustomFileDialog.Create */ inline __fastcall virtual TFileSaveDialog(System::Classes::TComponent* AOwner) : TCustomFileSaveDialog(AOwner) { }
	/* TCustomFileDialog.Destroy */ inline __fastcall virtual ~TFileSaveDialog() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileDialogWrapper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	void __fastcall AssignFileTypes();
	void __fastcall AssignOptions();
	System::Sysutils::TFileName __fastcall GetFileName();
	System::Classes::TStrings* __fastcall GetFiles();
	HWND __fastcall GetHandle();
	void __fastcall OnFileOkEvent(System::TObject* Sender, bool &CanClose);
	
protected:
	TCustomFileDialog* FFileDialog;
	Fmx::Dialogs::TOpenDialog* FOpenDialog;
	virtual TCustomFileDialog* __fastcall CreateFileDialog() = 0 ;
	
public:
	__fastcall TFileDialogWrapper(Fmx::Dialogs::TOpenDialog* const OpenDialog);
	__fastcall virtual ~TFileDialogWrapper();
	bool __fastcall Execute(HWND ParentWnd, System::Uitypes::TDialogType AType = (System::Uitypes::TDialogType)(0x0));
	__property System::Sysutils::TFileName FileName = {read=GetFileName};
	__property System::Classes::TStrings* Files = {read=GetFiles};
#ifndef _WIN64
	__property HWND Handle = {read=GetHandle, nodefault};
#else /* _WIN64 */
	__property HWND Handle = {read=GetHandle};
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileOpenDialogWrapper : public TFileDialogWrapper
{
	typedef TFileDialogWrapper inherited;
	
private:
	void __fastcall OnExecuteEvent(System::TObject* Sender);
	
protected:
	virtual TCustomFileDialog* __fastcall CreateFileDialog();
public:
	/* TFileDialogWrapper.Create */ inline __fastcall TFileOpenDialogWrapper(Fmx::Dialogs::TOpenDialog* const OpenDialog) : TFileDialogWrapper(OpenDialog) { }
	/* TFileDialogWrapper.Destroy */ inline __fastcall virtual ~TFileOpenDialogWrapper() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileSaveDialogWrapper : public TFileDialogWrapper
{
	typedef TFileDialogWrapper inherited;
	
protected:
	virtual TCustomFileDialog* __fastcall CreateFileDialog();
public:
	/* TFileDialogWrapper.Create */ inline __fastcall TFileSaveDialogWrapper(Fmx::Dialogs::TOpenDialog* const OpenDialog) : TFileDialogWrapper(OpenDialog) { }
	/* TFileDialogWrapper.Destroy */ inline __fastcall virtual ~TFileSaveDialogWrapper() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Dialogs */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGS_WIN)
using namespace Fmx::Dialogs::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DIALOGS)
using namespace Fmx::Dialogs;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dialogs_WinHPP
