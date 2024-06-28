// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPList.pas' rev: 34.00 (Windows)

#ifndef IdftplistHPP
#define IdftplistHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <IdFTPCommon.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftplist
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdInvalidFTPListingFormat;
class DELPHICLASS TIdFTPListItem;
class DELPHICLASS TIdFTPListItems;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdInvalidFTPListingFormat : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdInvalidFTPListingFormat(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdInvalidFTPListingFormat(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdInvalidFTPListingFormat(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdInvalidFTPListingFormat(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInvalidFTPListingFormat(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdInvalidFTPListingFormat(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdInvalidFTPListingFormat(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdInvalidFTPListingFormat(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInvalidFTPListingFormat(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdInvalidFTPListingFormat(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInvalidFTPListingFormat(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdInvalidFTPListingFormat(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdInvalidFTPListingFormat() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TIdDirItemType : unsigned char { ditDirectory, ditFile, ditSymbolicLink, ditSymbolicLinkDir, ditBlockDev, ditCharDev, ditFIFO, ditSocket };

typedef System::UnicodeString TIdFTPFileName;

class PASCALIMPLEMENTATION TIdFTPListItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	__int64 FSize;
	System::UnicodeString FData;
	System::UnicodeString FFileName;
	System::UnicodeString FLocalFileName;
	bool FSizeAvail;
	bool FModifiedAvail;
	System::TDateTime FModifiedDate;
	System::TDateTime FModifiedDateGMT;
	TIdDirItemType FItemType;
	bool FDirError;
	System::UnicodeString FPermissionDisplay;
	void __fastcall SetFileName(const System::UnicodeString AValue);
	__property System::TDateTime ModifiedDateGMT = {read=FModifiedDateGMT, write=FModifiedDateGMT};
	
public:
	__fastcall virtual TIdFTPListItem(System::Classes::TCollection* AOwner);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString Data = {read=FData, write=FData};
	__property __int64 Size = {read=FSize, write=FSize};
	__property System::TDateTime ModifiedDate = {read=FModifiedDate, write=FModifiedDate};
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
	__property System::UnicodeString LocalFileName = {read=FLocalFileName, write=FLocalFileName};
	__property TIdDirItemType ItemType = {read=FItemType, write=FItemType, nodefault};
	__property bool SizeAvail = {read=FSizeAvail, write=FSizeAvail, nodefault};
	__property bool ModifiedAvail = {read=FModifiedAvail, write=FModifiedAvail, nodefault};
	__property System::UnicodeString PermissionDisplay = {read=FPermissionDisplay, write=FPermissionDisplay};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdFTPListItem() { }
	
};


typedef void __fastcall (__closure *TIdFTPListOnGetCustomListFormat)(TIdFTPListItem* AItem, System::UnicodeString &VText);

typedef void __fastcall (__closure *TIdOnParseCustomListFormat)(TIdFTPListItem* AItem);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdFTPListItems : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdFTPListItem* operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	System::UnicodeString FDirectoryName;
	void __fastcall SetDirectoryName(const System::UnicodeString AValue);
	TIdFTPListItem* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TIdFTPListItem* const Value);
	
public:
	HIDESBASE TIdFTPListItem* __fastcall Add();
	__fastcall TIdFTPListItems();
	int __fastcall IndexOf(TIdFTPListItem* AItem);
	__property System::UnicodeString DirectoryName = {read=FDirectoryName, write=SetDirectoryName};
	__property TIdFTPListItem* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdFTPListItems() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftplist */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLIST)
using namespace Idftplist;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplistHPP
