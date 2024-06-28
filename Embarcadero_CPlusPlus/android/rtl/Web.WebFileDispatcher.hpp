// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.WebFileDispatcher.pas' rev: 34.00 (Android)

#ifndef Web_WebfiledispatcherHPP
#define Web_WebfiledispatcherHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Masks.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Webfiledispatcher
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDispatchFileRequest;
class DELPHICLASS TWebFileDispatcherProperties;
class DELPHICLASS TWebFileExtensionItem;
class DELPHICLASS TWebFileExtensions;
class DELPHICLASS TWebDirectoryItem;
class DELPHICLASS TWebDirectories;
__interface DELPHIINTERFACE TExtensionMethod;
typedef System::DelphiInterface<TExtensionMethod> _di_TExtensionMethod;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDispatchFileRequest : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TWebFileDispatcherProperties* FProperties;
	System::UnicodeString __fastcall QualifyFileName(System::UnicodeString AFileName);
	bool __fastcall IsDispatchFileName(const System::UnicodeString APathInfo);
	bool __fastcall GetDispatchFileName(const System::UnicodeString APathInfo, /* out */ System::UnicodeString &AFileName);
	bool __fastcall CanDispatchFileName(const System::UnicodeString AFileName);
	bool __fastcall IsIncludeDirectory(const System::UnicodeString ADirectory);
	bool __fastcall SetResponse(const System::UnicodeString AFileName);
	System::UnicodeString __fastcall GetMimeType(const System::UnicodeString FileName);
	void __fastcall UpdateExtensionMimeType();
	System::UnicodeString __fastcall FixupPath(const System::UnicodeString APath, /* out */ bool &AIgnorePath);
	
protected:
	virtual System::UnicodeString __fastcall GetApplicationPath();
	virtual bool __fastcall IsGetRequest() = 0 ;
	virtual bool __fastcall IsHeadRequest() = 0 ;
	virtual void __fastcall SetErrorCode(int AStatusCode) = 0 ;
	virtual System::TDateTime __fastcall GetIfModifiedSince() = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* AStream) = 0 ;
	virtual void __fastcall SetContentLength(int ALength) = 0 ;
	virtual void __fastcall SetContentType(const System::UnicodeString AValue) = 0 ;
	virtual void __fastcall SetLastModified(System::TDateTime AValue) = 0 ;
	virtual System::TClass __fastcall GetExceptionClass() = 0 ;
	virtual void __fastcall DoBeforeDispatch(const System::UnicodeString AFileName, bool &AHandled) = 0 ;
	virtual void __fastcall DoAfterDispatch(const System::UnicodeString AFileName, bool &AHandled) = 0 ;
	virtual System::UnicodeString __fastcall GetRequestPathInfo() = 0 ;
	virtual bool __fastcall GetResponseSent() = 0 ;
	
public:
	__fastcall TDispatchFileRequest(TWebFileDispatcherProperties* AProperties);
	__fastcall virtual ~TDispatchFileRequest();
	bool __fastcall DispatchFileRequest();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebFileDispatcherProperties : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FRootDirectory;
	System::UnicodeString FVirtualPath;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FExtensionMimeType;
	TWebFileExtensions* FWebFileExtensions;
	TWebDirectories* FWebDirectories;
	System::UnicodeString FDefaultFile;
	void __fastcall SetWebFileExtension(TWebFileExtensions* const Value);
	void __fastcall SetWebDirectories(TWebDirectories* const Value);
	System::UnicodeString __fastcall GetRootDirectory();
	System::UnicodeString __fastcall GetVirtualPath();
	void __fastcall SetVirtualPath(const System::UnicodeString Value);
	
public:
	__fastcall virtual TWebFileDispatcherProperties(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TWebFileDispatcherProperties();
	__property System::UnicodeString RootDirectory = {read=GetRootDirectory, write=FRootDirectory};
	__property TWebFileExtensions* WebFileExtensions = {read=FWebFileExtensions, write=SetWebFileExtension};
	__property TWebDirectories* WebDirectories = {read=FWebDirectories, write=SetWebDirectories};
	__property System::UnicodeString VirtualPath = {read=GetVirtualPath, write=SetVirtualPath};
	__property System::UnicodeString DefaultFile = {read=FDefaultFile, write=FDefaultFile};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebFileExtensionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FExtensions;
	System::UnicodeString FMimeType;
	void __fastcall SetMimeType(const System::UnicodeString Value);
	void __fastcall SetExtensions(const System::UnicodeString Value);
	System::Classes::TComponentState __fastcall GetComponentState();
	__property System::Classes::TComponentState ComponentState = {read=GetComponentState, nodefault};
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall TWebFileExtensionItem(System::Classes::TCollection* AOwner, const System::UnicodeString AMimeType, const System::UnicodeString AExtensions);
	
__published:
	__property System::UnicodeString MimeType = {read=FMimeType, write=SetMimeType};
	__property System::UnicodeString Extensions = {read=FExtensions, write=SetExtensions};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TWebFileExtensionItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebFileExtensions : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TWebFileExtensionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TComponent* FOwner;
	void __fastcall SetDefaultExtensions();
	
protected:
	HIDESBASE TWebFileExtensionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TWebFileExtensionItem* const Value);
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TWebFileExtensions(System::Classes::TComponent* AOwner);
	HIDESBASE TWebFileExtensionItem* __fastcall Add();
	__property TWebFileExtensionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWebFileExtensions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TWebDirectoryAction : unsigned char { dirInclude, dirExclude };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebDirectoryItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TWebDirectoryAction FDirectoryAction;
	System::UnicodeString FDirectoryMask;
	System::Masks::TMask* FMask;
	void __fastcall UpdateMask();
	void __fastcall SetDirectoryMask(const System::UnicodeString Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall TWebDirectoryItem(System::Classes::TCollection* AOwner, TWebDirectoryAction ADirectoryAction, const System::UnicodeString ADirectoryMask);
	__fastcall virtual ~TWebDirectoryItem();
	
__published:
	__property TWebDirectoryAction DirectoryAction = {read=FDirectoryAction, write=FDirectoryAction, nodefault};
	__property System::UnicodeString DirectoryMask = {read=FDirectoryMask, write=SetDirectoryMask};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWebDirectories : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TWebDirectoryItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::Classes::TComponent* FOwner;
	void __fastcall SetDefaultDirectories();
	
protected:
	HIDESBASE TWebDirectoryItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TWebDirectoryItem* const Value);
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TWebDirectories(System::Classes::TComponent* AOwner);
	HIDESBASE TWebDirectoryItem* __fastcall Add();
	__property TWebDirectoryItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TWebDirectories() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::UnicodeString __fastcall (*TLookupMimeType)(const System::UnicodeString AExtensions);

typedef System::UnicodeString __fastcall (*TLookupExtensions)(const System::UnicodeString AMimeType);

__interface TExtensionMethod  : public System::IInterface 
{
	virtual bool __fastcall Invoke(System::WideChar * AExt, int ALength) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TLookupMimeType FLookupMimeType;
extern DELPHI_PACKAGE TLookupExtensions FLookupExtensions;
extern DELPHI_PACKAGE bool __fastcall EnumerateExtensions(const System::UnicodeString Extensions, bool WithDot, _di_TExtensionMethod Method);
}	/* namespace Webfiledispatcher */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_WEBFILEDISPATCHER)
using namespace Web::Webfiledispatcher;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_WebfiledispatcherHPP
