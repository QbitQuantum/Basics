// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Vcl.Shell.ShellCtrls.pas' rev: 34.00 (Windows)

#ifndef Vcl_Shell_ShellctrlsHPP
#define Vcl_Shell_ShellctrlsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Winapi.CommCtrl.hpp>
#include <Winapi.ShlObj.hpp>
#include <Winapi.ActiveX.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ImgList.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcl
{
namespace Shell
{
namespace Shellctrls
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EInvalidPath;
__interface DELPHIINTERFACE IShellCommandVerb;
typedef System::DelphiInterface<IShellCommandVerb> _di_IShellCommandVerb;
class DELPHICLASS TShellFolder;
class DELPHICLASS TShellChangeThread;
class DELPHICLASS TCustomShellChangeNotifier;
class DELPHICLASS TShellChangeNotifier;
class DELPHICLASS TCustomShellTreeView;
class DELPHICLASS TShellTreeView;
class DELPHICLASS TCustomShellComboBox;
class DELPHICLASS TShellComboBox;
class DELPHICLASS TCustomShellListView;
class DELPHICLASS TShellListView;
//-- type declarations -------------------------------------------------------
typedef System::UnicodeString TRoot;

enum DECLSPEC_DENUM TRootFolder : unsigned char { rfDesktop, rfMyComputer, rfNetwork, rfRecycleBin, rfAppData, rfCommonDesktopDirectory, rfCommonPrograms, rfCommonStartMenu, rfCommonStartup, rfControlPanel, rfDesktopDirectory, rfFavorites, rfFonts, rfInternet, rfPersonal, rfPrinters, rfPrintHood, rfPrograms, rfRecent, rfSendTo, rfStartMenu, rfStartup, rfTemplates };

enum DECLSPEC_DENUM TShellFolderCapability : unsigned char { fcCanCopy, fcCanDelete, fcCanLink, fcCanMove, fcCanRename, fcDropTarget, fcHasPropSheet };

typedef System::Set<TShellFolderCapability, TShellFolderCapability::fcCanCopy, TShellFolderCapability::fcHasPropSheet> TShellFolderCapabilities;

enum DECLSPEC_DENUM TShellFolderProperty : unsigned char { fpCut, fpIsLink, fpReadOnly, fpShared, fpFileSystem, fpFileSystemAncestor, fpRemovable, fpValidate };

typedef System::Set<TShellFolderProperty, TShellFolderProperty::fpCut, TShellFolderProperty::fpValidate> TShellFolderProperties;

enum DECLSPEC_DENUM TShellObjectType : unsigned char { otFolders, otNonFolders, otHidden };

typedef System::Set<TShellObjectType, TShellObjectType::otFolders, TShellObjectType::otHidden> TShellObjectTypes;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EInvalidPath : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EInvalidPath(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EInvalidPath(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EInvalidPath(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EInvalidPath(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalidPath(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EInvalidPath(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EInvalidPath(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EInvalidPath(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalidPath(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EInvalidPath(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidPath(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EInvalidPath(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EInvalidPath() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{7D2A7245-2376-4D33-8008-A130935A2E8B}") IShellCommandVerb  : public System::IInterface 
{
	virtual void __fastcall ExecuteCommand(System::UnicodeString Verb, bool &Handled) = 0 ;
	virtual void __fastcall CommandCompleted(System::UnicodeString Verb, bool Succeeded) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TShellFolder : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	_ITEMIDLIST *FPIDL;
	_ITEMIDLIST *FFullPIDL;
	TShellFolder* FParent;
	_di_IShellFolder FIShellFolder;
	_di_IShellFolder2 FIShellFolder2;
	_di_IShellDetails FIShellDetails;
	System::_di_IInterface FDetailInterface;
	int FLevel;
	NativeUInt FViewHandle;
	System::Classes::TStrings* FDetails;
	System::_di_IInterface __fastcall GetDetailInterface();
	_di_IShellDetails __fastcall GetShellDetails();
	_di_IShellFolder2 __fastcall GetShellFolder2();
	System::UnicodeString __fastcall GetDetails(int Index);
	void __fastcall SetDetails(int Index, const System::UnicodeString Value);
	void __fastcall LoadColumnDetails(TShellFolder* RootFolder, NativeUInt Handle, int ColumnCount);
	
public:
	__fastcall virtual TShellFolder(TShellFolder* AParent, Winapi::Shlobj::PItemIDList ID, _di_IShellFolder SF);
	__fastcall virtual ~TShellFolder();
	TShellFolderCapabilities __fastcall Capabilities();
	System::UnicodeString __fastcall DisplayName();
	int __fastcall ExecuteDefault();
	int __fastcall ImageIndex(bool LargeIcon);
	bool __fastcall IsFolder();
	_di_IShellFolder __fastcall ParentShellFolder();
	System::UnicodeString __fastcall PathName();
	TShellFolderProperties __fastcall Properties();
	bool __fastcall Rename(const System::WideString NewName);
	bool __fastcall SubFolders();
	__property Winapi::Shlobj::PItemIDList AbsoluteID = {read=FFullPIDL};
	__property System::UnicodeString Details[int Index] = {read=GetDetails, write=SetDetails};
	__property int Level = {read=FLevel, nodefault};
	__property TShellFolder* Parent = {read=FParent};
	__property Winapi::Shlobj::PItemIDList RelativeID = {read=FPIDL};
	__property _di_IShellFolder ShellFolder = {read=FIShellFolder};
	__property _di_IShellFolder2 ShellFolder2 = {read=GetShellFolder2};
	__property _di_IShellDetails ShellDetails = {read=GetShellDetails};
#ifndef _WIN64
	__property NativeUInt ViewHandle = {read=FViewHandle, write=FViewHandle, nodefault};
#else /* _WIN64 */
	__property NativeUInt ViewHandle = {read=FViewHandle, write=FViewHandle};
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TNotifyFilter : unsigned char { nfFileNameChange, nfDirNameChange, nfAttributeChange, nfSizeChange, nfWriteChange, nfSecurityChange };

typedef System::Set<TNotifyFilter, TNotifyFilter::nfFileNameChange, TNotifyFilter::nfSecurityChange> TNotifyFilters;

class PASCALIMPLEMENTATION TShellChangeThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	NativeUInt FMutex;
	NativeUInt FWaitHandle;
	System::Classes::TThreadMethod FChangeEvent;
	System::UnicodeString FDirectory;
	bool FWatchSubTree;
	bool FWaitChanged;
	unsigned FNotifyOptionFlags;
	
protected:
	virtual void __fastcall Execute();
	
public:
	__fastcall virtual TShellChangeThread(System::Classes::TThreadMethod ChangeEvent);
	__fastcall virtual ~TShellChangeThread();
	void __fastcall SetDirectoryOptions(System::UnicodeString Directory, bool WatchSubTree, unsigned NotifyOptionFlags);
	__property System::Classes::TThreadMethod ChangeEvent = {read=FChangeEvent, write=FChangeEvent};
};


class PASCALIMPLEMENTATION TCustomShellChangeNotifier : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TNotifyFilters FFilters;
	bool FWatchSubTree;
	TRoot FRoot;
	TShellChangeThread* FThread;
	System::Classes::TThreadMethod FOnChange;
	void __fastcall SetRoot(const TRoot Value);
	void __fastcall SetWatchSubTree(const bool Value);
	void __fastcall SetFilters(const TNotifyFilters Value);
	void __fastcall SetOnChange(const System::Classes::TThreadMethod Value);
	
protected:
	void __fastcall Change();
	void __fastcall Start();
	
public:
	__fastcall virtual TCustomShellChangeNotifier(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomShellChangeNotifier();
	__property TNotifyFilters NotifyFilters = {read=FFilters, write=SetFilters, nodefault};
	__property TRoot Root = {read=FRoot, write=SetRoot};
	__property bool WatchSubTree = {read=FWatchSubTree, write=SetWatchSubTree, nodefault};
	__property System::Classes::TThreadMethod OnChange = {read=FOnChange, write=SetOnChange};
};


class PASCALIMPLEMENTATION TShellChangeNotifier : public TCustomShellChangeNotifier
{
	typedef TCustomShellChangeNotifier inherited;
	
__published:
	__property NotifyFilters;
	__property Root = {default=0};
	__property WatchSubTree;
	__property OnChange;
public:
	/* TCustomShellChangeNotifier.Create */ inline __fastcall virtual TShellChangeNotifier(System::Classes::TComponent* AOwner) : TCustomShellChangeNotifier(AOwner) { }
	/* TCustomShellChangeNotifier.Destroy */ inline __fastcall virtual ~TShellChangeNotifier() { }
	
};


typedef void __fastcall (__closure *TAddFolderEvent)(System::TObject* Sender, TShellFolder* AFolder, bool &CanAdd);

typedef void __fastcall (__closure *TGetImageIndexEvent)(System::TObject* Sender, int Index, int &ImageIndex);

class PASCALIMPLEMENTATION TCustomShellTreeView : public Vcl::Comctrls::TCustomTreeView
{
	typedef Vcl::Comctrls::TCustomTreeView inherited;
	
public:
	TShellFolder* operator[](int Index) { return this->Folders[Index]; }
	
private:
	TShellObjectTypes FObjectTypes;
	int FImages;
	bool FAutoContext;
	bool FUpdating;
	TCustomShellComboBox* FComboBox;
	TCustomShellListView* FListView;
	bool FAutoRefresh;
	bool FImageListChanging;
	bool FUseShellImages;
	TShellChangeNotifier* FNotifier;
	TAddFolderEvent FOnAddFolder;
	System::UnicodeString FSavePath;
	Vcl::Comctrls::TTreeNode* FNodeToMonitor;
	Vcl::Comctrls::TTreeNode* __fastcall FolderExists(Winapi::Shlobj::PItemIDList FindID, Vcl::Comctrls::TTreeNode* InNode);
	TShellFolder* __fastcall GetFolder(int Index);
	System::UnicodeString __fastcall GetPath();
	void __fastcall SetComboBox(TCustomShellComboBox* Value);
	void __fastcall SetListView(TCustomShellListView* const Value);
	void __fastcall SetPath(const System::UnicodeString Value);
	void __fastcall SetPathFromID(Winapi::Shlobj::PItemIDList ID);
	void __fastcall SetRoot(const TRoot Value);
	void __fastcall SetUseShellImages(const bool Value);
	void __fastcall SetAutoRefresh(const bool Value);
	
protected:
	TRoot FRoot;
	TRoot FOldRoot;
	TShellFolder* FRootFolder;
	bool FLoadingRoot;
	DYNAMIC bool __fastcall CanChange(Vcl::Comctrls::TTreeNode* Node);
	DYNAMIC bool __fastcall CanExpand(Vcl::Comctrls::TTreeNode* Node);
	virtual void __fastcall CreateRoot();
	virtual void __fastcall CreateWnd();
	virtual void __fastcall DestroyWnd();
	DYNAMIC void __fastcall DoContextPopup(const System::Types::TPoint &MousePos, bool &Handled);
	DYNAMIC void __fastcall Edit(const tagTVITEMW &Item);
	virtual void __fastcall GetImageIndex(Vcl::Comctrls::TTreeNode* Node);
	virtual void __fastcall GetSelectedIndex(Vcl::Comctrls::TTreeNode* Node);
	void __fastcall InitNode(Vcl::Comctrls::TTreeNode* NewNode, Winapi::Shlobj::PItemIDList ID, Vcl::Comctrls::TTreeNode* ParentNode);
	virtual void __fastcall Loaded();
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall Delete(Vcl::Comctrls::TTreeNode* Node);
	Vcl::Comctrls::TTreeNode* __fastcall NodeFromAbsoluteID(Vcl::Comctrls::TTreeNode* StartNode, Winapi::Shlobj::PItemIDList ID);
	Vcl::Comctrls::TTreeNode* __fastcall NodeFromRelativeID(Vcl::Comctrls::TTreeNode* ParentNode, Winapi::Shlobj::PItemIDList ID);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall PopulateNode(Vcl::Comctrls::TTreeNode* Node);
	void __fastcall RootChanged();
	virtual void __fastcall SetObjectTypes(TShellObjectTypes Value);
	HIDESBASE virtual void __fastcall WMDestroy(Winapi::Messages::TWMNoParams &Message);
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	void __fastcall ClearItems();
	void __fastcall RefreshEvent();
	
public:
	__fastcall virtual TCustomShellTreeView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomShellTreeView();
	HIDESBASE void __fastcall Refresh(Vcl::Comctrls::TTreeNode* Node);
	TShellFolder* __fastcall SelectedFolder();
	__property bool AutoRefresh = {read=FAutoRefresh, write=SetAutoRefresh, nodefault};
	__property TShellFolder* Folders[int Index] = {read=GetFolder/*, default*/};
	__property Items;
	__property System::UnicodeString Path = {read=GetPath, write=SetPath};
	__property bool AutoContextMenus = {read=FAutoContext, write=FAutoContext, default=1};
	__property TShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property TRoot Root = {read=FRoot, write=SetRoot};
	__property TCustomShellComboBox* ShellComboBox = {read=FComboBox, write=SetComboBox};
	__property TCustomShellListView* ShellListView = {read=FListView, write=SetListView};
	__property bool UseShellImages = {read=FUseShellImages, write=SetUseShellImages, nodefault};
	__property TAddFolderEvent OnAddFolder = {read=FOnAddFolder, write=FOnAddFolder};
	void __fastcall CommandCompleted(System::UnicodeString Verb, bool Succeeded);
	void __fastcall ExecuteCommand(System::UnicodeString Verb, bool &Handled);
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomShellTreeView(HWND ParentWindow) : Vcl::Comctrls::TCustomTreeView(ParentWindow) { }
	
private:
	void *__IShellCommandVerb;	// IShellCommandVerb 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D2A7245-2376-4D33-8008-A130935A2E8B}
	operator _di_IShellCommandVerb()
	{
		_di_IShellCommandVerb intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IShellCommandVerb*(void) { return (IShellCommandVerb*)&__IShellCommandVerb; }
	#endif
	
};


class PASCALIMPLEMENTATION TShellTreeView : public TCustomShellTreeView
{
	typedef TCustomShellTreeView inherited;
	
__published:
	__property AutoContextMenus = {default=1};
	__property ObjectTypes;
	__property Root = {default=0};
	__property ShellComboBox;
	__property ShellListView;
	__property UseShellImages;
	__property OnAddFolder;
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property AutoRefresh;
	__property BorderStyle = {default=1};
	__property ChangeDelay = {default=0};
	__property Color = {default=-16777211};
	__property Ctl3D;
	__property Cursor = {default=0};
	__property DragCursor = {default=-12};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property Font;
	__property HideSelection = {default=1};
	__property Images;
	__property Indent;
	__property ParentColor = {default=1};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property RightClickSelect = {default=0};
	__property ShowButtons = {default=1};
	__property ShowHint;
	__property ShowLines = {default=1};
	__property ShowRoot = {default=1};
	__property StateImages;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnClick;
	__property OnEnter;
	__property OnExit;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnStartDrag;
	__property OnEndDrag;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnDblClick;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnChanging;
	__property OnChange;
	__property OnExpanding;
	__property OnCollapsing;
	__property OnCollapsed;
	__property OnExpanded;
	__property OnEditing;
	__property OnEdited;
	__property OnGetImageIndex;
	__property OnGetSelectedIndex;
public:
	/* TCustomShellTreeView.Create */ inline __fastcall virtual TShellTreeView(System::Classes::TComponent* AOwner) : TCustomShellTreeView(AOwner) { }
	/* TCustomShellTreeView.Destroy */ inline __fastcall virtual ~TShellTreeView() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TShellTreeView(HWND ParentWindow) : TCustomShellTreeView(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TCustomShellComboBox : public Vcl::Comctrls::TCustomComboBoxEx
{
	typedef Vcl::Comctrls::TCustomComboBoxEx inherited;
	
private:
	int FImages;
	int FImageHeight;
	int FImageWidth;
	Vcl::Imglist::TCustomImageList* FImageList;
	TCustomShellTreeView* FTreeView;
	TCustomShellListView* FListView;
	TShellObjectTypes FObjectTypes;
	bool FUseShellImages;
	bool FUpdating;
	TGetImageIndexEvent FOnGetImageIndex;
	void __fastcall ClearItems();
	TShellFolder* __fastcall GetFolder(int Index);
	System::UnicodeString __fastcall GetPath();
	void __fastcall SetPath(const System::UnicodeString Value);
	void __fastcall SetPathFromID(Winapi::Shlobj::PItemIDList ID);
	void __fastcall SetRoot(const TRoot Value);
	void __fastcall SetTreeView(TCustomShellTreeView* Value);
	void __fastcall SetListView(TCustomShellListView* Value);
	void __fastcall SetUseShellImages(const bool Value);
	int __fastcall GetShellImageIndex(TShellFolder* AFolder);
	
protected:
	TRoot FOldRoot;
	TRoot FRoot;
	TShellFolder* FRootFolder;
	void __fastcall AddItems(int Index, TShellFolder* ParentFolder);
	DYNAMIC void __fastcall Change();
	DYNAMIC void __fastcall Click();
	virtual void __fastcall CreateRoot();
	virtual void __fastcall CreateWnd();
	virtual void __fastcall DestroyWnd();
	int __fastcall IndexFromID(Winapi::Shlobj::PItemIDList AbsoluteID);
	virtual void __fastcall Init();
	TShellFolder* __fastcall InitItem(TShellFolder* ParentFolder, Winapi::Shlobj::PItemIDList ID);
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall RootChanged();
	void __fastcall TreeUpdate(Winapi::Shlobj::PItemIDList NewPath);
	virtual void __fastcall SetObjectTypes(TShellObjectTypes Value);
	
public:
	__fastcall virtual TCustomShellComboBox(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomShellComboBox();
	__property Items;
	__property System::UnicodeString Path = {read=GetPath, write=SetPath};
	__property TShellFolder* Folders[int Index] = {read=GetFolder};
	__property TRoot Root = {read=FRoot, write=SetRoot};
	__property TShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property TCustomShellTreeView* ShellTreeView = {read=FTreeView, write=SetTreeView};
	__property TCustomShellListView* ShellListView = {read=FListView, write=SetListView};
	__property bool UseShellImages = {read=FUseShellImages, write=SetUseShellImages, nodefault};
	__property TGetImageIndexEvent OnGetImageIndex = {read=FOnGetImageIndex, write=FOnGetImageIndex};
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomShellComboBox(HWND ParentWindow) : Vcl::Comctrls::TCustomComboBoxEx(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TShellComboBox : public TCustomShellComboBox
{
	typedef TCustomShellComboBox inherited;
	
__published:
	__property Images;
	__property Root = {default=0};
	__property ShellTreeView;
	__property ShellListView;
	__property UseShellImages;
	__property OnGetImageIndex;
	__property Anchors = {default=3};
	__property BiDiMode;
	__property Color = {default=-16777211};
	__property Constraints;
	__property Ctl3D;
	__property DragCursor = {default=-12};
	__property DragKind = {default=0};
	__property DragMode = {default=0};
	__property DropDownCount = {default=8};
	__property Enabled = {default=1};
	__property Font;
	__property ImeMode = {default=3};
	__property ImeName = {default=0};
	__property MaxLength = {default=0};
	__property ParentBiDiMode = {default=1};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnChange;
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnDropDown;
	__property OnEndDock;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnStartDock;
	__property OnStartDrag;
public:
	/* TCustomShellComboBox.Create */ inline __fastcall virtual TShellComboBox(System::Classes::TComponent* AOwner) : TCustomShellComboBox(AOwner) { }
	/* TCustomShellComboBox.Destroy */ inline __fastcall virtual ~TShellComboBox() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TShellComboBox(HWND ParentWindow) : TCustomShellComboBox(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TCustomShellListView : public Vcl::Comctrls::TCustomListView
{
	typedef Vcl::Comctrls::TCustomListView inherited;
	
private:
	bool FAutoContext;
	bool FAutoRefresh;
	bool FAutoNavigate;
	bool FSorted;
	bool FUpdating;
	TShellObjectTypes FObjectTypes;
	int FLargeImages;
	int FSmallImages;
	TAddFolderEvent FOnAddFolder;
	System::Classes::TList* FFolders;
	TCustomShellTreeView* FTreeView;
	TCustomShellComboBox* FComboBox;
	TShellChangeNotifier* FNotifier;
	Vcl::Comctrls::TLVEditingEvent FOnEditing;
	bool FSettingRoot;
	System::UnicodeString FSavePath;
	void __fastcall EnumColumns();
	TShellFolder* __fastcall GetFolder(int Index);
	void __fastcall SetAutoRefresh(const bool Value);
	void __fastcall SetSorted(const bool Value);
	void __fastcall SetTreeView(TCustomShellTreeView* Value);
	void __fastcall SetComboBox(TCustomShellComboBox* Value);
	void __fastcall TreeUpdate(Winapi::Shlobj::PItemIDList NewRoot);
	void __fastcall SetPathFromID(Winapi::Shlobj::PItemIDList ID);
	void __fastcall SynchPaths();
	
protected:
	TRoot FOldRoot;
	TRoot FRoot;
	TShellFolder* FRootFolder;
	void __fastcall ClearItems();
	virtual void __fastcall CreateRoot();
	virtual void __fastcall CreateWnd();
	virtual void __fastcall DestroyWnd();
	DYNAMIC void __fastcall DblClick();
	DYNAMIC void __fastcall DoContextPopup(const System::Types::TPoint &MousePos, bool &Handled);
	void __fastcall EditText();
	DYNAMIC void __fastcall Edit(const tagLVITEMW &Item);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall Loaded();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall OwnerDataFetch(Vcl::Comctrls::TListItem* Item, Vcl::Comctrls::TItemRequest Request);
	virtual int __fastcall OwnerDataFind(Vcl::Comctrls::TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition, void * FindData, int StartIndex, Vcl::Comctrls::TSearchDirection Direction, bool Wrap);
	virtual void __fastcall Populate();
	void __fastcall RootChanged();
	void __fastcall SetObjectTypes(TShellObjectTypes Value);
	void __fastcall SetRoot(const TRoot Value);
	virtual void __fastcall SetViewStyle(Vcl::Comctrls::TViewStyle Value);
	virtual void __fastcall WndProc(Winapi::Messages::TMessage &Message);
	
public:
	__fastcall virtual TCustomShellListView(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomShellListView();
	void __fastcall Back();
	HIDESBASE void __fastcall Refresh();
	TShellFolder* __fastcall SelectedFolder();
	__property TShellFolder* Folders[int Index] = {read=GetFolder};
	__property TShellFolder* RootFolder = {read=FRootFolder};
	__property Items;
	__property Columns;
	__property bool AutoContextMenus = {read=FAutoContext, write=FAutoContext, default=1};
	__property bool AutoRefresh = {read=FAutoRefresh, write=SetAutoRefresh, default=0};
	__property bool AutoNavigate = {read=FAutoNavigate, write=FAutoNavigate, default=1};
	__property TShellObjectTypes ObjectTypes = {read=FObjectTypes, write=SetObjectTypes, nodefault};
	__property TRoot Root = {read=FRoot, write=SetRoot};
	__property TCustomShellTreeView* ShellTreeView = {read=FTreeView, write=SetTreeView};
	__property TCustomShellComboBox* ShellComboBox = {read=FComboBox, write=SetComboBox};
	__property bool Sorted = {read=FSorted, write=SetSorted, nodefault};
	__property TAddFolderEvent OnAddFolder = {read=FOnAddFolder, write=FOnAddFolder};
	__property Vcl::Comctrls::TLVEditingEvent OnEditing = {read=FOnEditing, write=FOnEditing};
	void __fastcall CommandCompleted(System::UnicodeString Verb, bool Succeeded);
	void __fastcall ExecuteCommand(System::UnicodeString Verb, bool &Handled);
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomShellListView(HWND ParentWindow) : Vcl::Comctrls::TCustomListView(ParentWindow) { }
	
private:
	void *__IShellCommandVerb;	// IShellCommandVerb 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7D2A7245-2376-4D33-8008-A130935A2E8B}
	operator _di_IShellCommandVerb()
	{
		_di_IShellCommandVerb intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IShellCommandVerb*(void) { return (IShellCommandVerb*)&__IShellCommandVerb; }
	#endif
	
};


class PASCALIMPLEMENTATION TShellListView : public TCustomShellListView
{
	typedef TCustomShellListView inherited;
	
__published:
	__property AutoContextMenus = {default=1};
	__property AutoRefresh = {default=0};
	__property AutoNavigate = {default=1};
	__property ObjectTypes;
	__property Root = {default=0};
	__property ShellTreeView;
	__property ShellComboBox;
	__property Sorted;
	__property OnAddFolder;
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property BorderStyle = {default=1};
	__property Color = {default=-16777211};
	__property ColumnClick = {default=1};
	__property OnClick;
	__property OnDblClick;
	__property Ctl3D;
	__property DragMode = {default=0};
	__property ReadOnly = {default=1};
	__property Enabled = {default=1};
	__property Font;
	__property GridLines = {default=0};
	__property HideSelection = {default=1};
	__property HotTrack = {default=0};
	__property IconOptions;
	__property AllocBy = {default=0};
	__property MultiSelect = {default=0};
	__property RowSelect = {default=0};
	__property OnChange;
	__property OnChanging;
	__property OnColumnClick;
	__property OnContextPopup;
	__property OnEnter;
	__property OnExit;
	__property OnInsert;
	__property OnDragDrop;
	__property OnDragOver;
	__property DragCursor = {default=-12};
	__property OnStartDrag;
	__property OnEndDrag;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property ParentColor = {default=0};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property PopupMenu;
	__property ShowColumnHeaders = {default=1};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property ViewStyle = {default=0};
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnEditing;
public:
	/* TCustomShellListView.Create */ inline __fastcall virtual TShellListView(System::Classes::TComponent* AOwner) : TCustomShellListView(AOwner) { }
	/* TCustomShellListView.Destroy */ inline __fastcall virtual ~TShellListView() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TShellListView(HWND ParentWindow) : TCustomShellListView(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall InvokeContextMenu(Vcl::Controls::TWinControl* Owner, TShellFolder* AFolder, int X, int Y);
}	/* namespace Shellctrls */
}	/* namespace Shell */
}	/* namespace Vcl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL_SHELL_SHELLCTRLS)
using namespace Vcl::Shell::Shellctrls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL_SHELL)
using namespace Vcl::Shell;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCL)
using namespace Vcl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcl_Shell_ShellctrlsHPP
