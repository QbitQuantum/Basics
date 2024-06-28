// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPListTypes.pas' rev: 34.00 (iOS)

#ifndef IdftplisttypesHPP
#define IdftplisttypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdFTPList.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftplisttypes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDOSAttributes;
class DELPHICLASS TIdWin32ea;
class DELPHICLASS TIdMinimalFTPListItem;
class DELPHICLASS TIdRecFTPListItem;
class DELPHICLASS TIdCreationDateFTPListItem;
class DELPHICLASS TIdMLSTFTPListItem;
class DELPHICLASS TIdOwnerFTPListItem;
class DELPHICLASS TIdNovellBaseFTPListItem;
class DELPHICLASS TIdUnixPermFTPListItem;
class DELPHICLASS TIdUnixBaseFTPListItem;
class DELPHICLASS TIdDOSBaseFTPListItem;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDOSAttributes : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	unsigned FFileAttributes;
	bool __fastcall GetRead_Only();
	void __fastcall SetRead_Only(const bool AValue);
	bool __fastcall GetHidden();
	void __fastcall SetHidden(const bool AValue);
	bool __fastcall GetSystem();
	void __fastcall SetSystem(const bool AValue);
	bool __fastcall GetArchive();
	void __fastcall SetArchive(const bool AValue);
	bool __fastcall GetDirectory();
	void __fastcall SetDirectory(const bool AValue);
	bool __fastcall GetNormal();
	void __fastcall SetNormal(const bool AValue);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual System::UnicodeString __fastcall GetAsString();
	bool __fastcall AddAttribute(const System::UnicodeString AString);
	
__published:
	__property unsigned FileAttributes = {read=FFileAttributes, write=FFileAttributes, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString};
	__property bool Read_Only = {read=GetRead_Only, write=SetRead_Only, nodefault};
	__property bool Archive = {read=GetArchive, write=SetArchive, nodefault};
	__property bool System = {read=GetSystem, write=SetSystem, nodefault};
	__property bool Directory = {read=GetDirectory, write=SetDirectory, nodefault};
	__property bool Hidden = {read=GetHidden, write=SetHidden, nodefault};
	__property bool Normal = {read=GetNormal, write=SetNormal, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdDOSAttributes() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdDOSAttributes() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TIdWin32ea : public TIdDOSAttributes
{
	typedef TIdDOSAttributes inherited;
	
protected:
	bool __fastcall GetDevice();
	void __fastcall SetDevice(const bool AValue);
	bool __fastcall GetTemporary();
	void __fastcall SetTemporary(const bool AValue);
	bool __fastcall GetSparseFile();
	void __fastcall SetSparseFile(const bool AValue);
	bool __fastcall GetReparsePoint();
	void __fastcall SetReparsePoint(const bool AValue);
	bool __fastcall GetCompressed();
	void __fastcall SetCompressed(const bool AValue);
	bool __fastcall GetOffline();
	void __fastcall SetOffline(const bool AValue);
	bool __fastcall GetNotContextIndexed();
	void __fastcall SetNotContextIndexed(const bool AValue);
	bool __fastcall GetEncrypted();
	void __fastcall SetEncrypted(const bool AValue);
	
public:
	virtual System::UnicodeString __fastcall GetAsString();
	
__published:
	__property bool Device = {read=GetDevice, write=SetDevice, nodefault};
	__property bool Temporary = {read=GetTemporary, write=SetTemporary, nodefault};
	__property bool SparseFile = {read=GetSparseFile, write=SetSparseFile, nodefault};
	__property bool ReparsePoint = {read=GetReparsePoint, write=SetReparsePoint, nodefault};
	__property bool Compressed = {read=GetCompressed, write=SetCompressed, nodefault};
	__property bool Offline = {read=GetOffline, write=SetOffline, nodefault};
	__property bool NotContextIndexed = {read=GetNotContextIndexed, write=SetNotContextIndexed, nodefault};
	__property bool Encrypted = {read=GetEncrypted, write=SetEncrypted, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdWin32ea() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdWin32ea() : TIdDOSAttributes() { }
	
};


class PASCALIMPLEMENTATION TIdMinimalFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
public:
	__fastcall virtual TIdMinimalFTPListItem(System::Classes::TCollection* AOwner);
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdMinimalFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdRecFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	int FRecLength;
	System::UnicodeString FRecFormat;
	int FNumberRecs;
	__property int RecLength = {read=FRecLength, write=FRecLength, nodefault};
	__property System::UnicodeString RecFormat = {read=FRecFormat, write=FRecFormat};
	__property int NumberRecs = {read=FNumberRecs, write=FNumberRecs, nodefault};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdRecFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdRecFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdCreationDateFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	System::TDateTime FCreationDate;
	
public:
	__fastcall virtual TIdCreationDateFTPListItem(System::Classes::TCollection* AOwner);
	__property System::TDateTime CreationDate = {read=FCreationDate, write=FCreationDate};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdCreationDateFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdMLSTFTPListItem : public TIdCreationDateFTPListItem
{
	typedef TIdCreationDateFTPListItem inherited;
	
protected:
	bool FAttributesAvail;
	TIdWin32ea* FAttributes;
	System::TDateTime FCreationDateGMT;
	System::TDateTime FLastAccessDate;
	System::TDateTime FLastAccessDateGMT;
	System::UnicodeString FLinkedItemName;
	System::UnicodeString FUniqueID;
	System::UnicodeString FMLISTPermissions;
	System::UnicodeString __fastcall GetFact(const System::UnicodeString AName);
	
public:
	__fastcall virtual TIdMLSTFTPListItem(System::Classes::TCollection* AOwner);
	__fastcall virtual ~TIdMLSTFTPListItem();
	__property ModifiedDateGMT = {default=0};
	__property System::TDateTime CreationDateGMT = {read=FCreationDateGMT, write=FCreationDateGMT};
	__property System::TDateTime LastAccessDate = {read=FLastAccessDate, write=FLastAccessDate};
	__property System::TDateTime LastAccessDateGMT = {read=FLastAccessDateGMT, write=FLastAccessDateGMT};
	__property System::UnicodeString UniqueID = {read=FUniqueID, write=FUniqueID};
	__property System::UnicodeString MLISTPermissions = {read=FMLISTPermissions, write=FMLISTPermissions};
	__property System::UnicodeString Facts[const System::UnicodeString Name] = {read=GetFact};
	__property bool AttributesAvail = {read=FAttributesAvail, write=FAttributesAvail, nodefault};
	__property TIdWin32ea* Attributes = {read=FAttributes};
	__property System::UnicodeString LinkedItemName = {read=FLinkedItemName, write=FLinkedItemName};
};


class PASCALIMPLEMENTATION TIdOwnerFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	System::UnicodeString FOwnerName;
	
public:
	__property System::UnicodeString OwnerName = {read=FOwnerName, write=FOwnerName};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdOwnerFTPListItem(System::Classes::TCollection* AOwner) : Idftplist::TIdFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdOwnerFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdNovellBaseFTPListItem : public TIdOwnerFTPListItem
{
	typedef TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FNovellPermissions;
	
public:
	__property System::UnicodeString NovellPermissions = {read=FNovellPermissions, write=FNovellPermissions};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdNovellBaseFTPListItem(System::Classes::TCollection* AOwner) : TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdNovellBaseFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdUnixPermFTPListItem : public TIdOwnerFTPListItem
{
	typedef TIdOwnerFTPListItem inherited;
	
protected:
	System::UnicodeString FUnixGroupPermissions;
	System::UnicodeString FUnixOwnerPermissions;
	System::UnicodeString FUnixOtherPermissions;
	
public:
	__property System::UnicodeString UnixOwnerPermissions = {read=FUnixOwnerPermissions, write=FUnixOwnerPermissions};
	__property System::UnicodeString UnixGroupPermissions = {read=FUnixGroupPermissions, write=FUnixGroupPermissions};
	__property System::UnicodeString UnixOtherPermissions = {read=FUnixOtherPermissions, write=FUnixOtherPermissions};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdUnixPermFTPListItem(System::Classes::TCollection* AOwner) : TIdOwnerFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdUnixPermFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdUnixBaseFTPListItem : public TIdUnixPermFTPListItem
{
	typedef TIdUnixPermFTPListItem inherited;
	
protected:
	int FLinkCount;
	System::UnicodeString FGroupName;
	System::UnicodeString FLinkedItemName;
	
public:
	__property int LinkCount = {read=FLinkCount, write=FLinkCount, nodefault};
	__property System::UnicodeString GroupName = {read=FGroupName, write=FGroupName};
	__property System::UnicodeString LinkedItemName = {read=FLinkedItemName, write=FLinkedItemName};
public:
	/* TIdFTPListItem.Create */ inline __fastcall virtual TIdUnixBaseFTPListItem(System::Classes::TCollection* AOwner) : TIdUnixPermFTPListItem(AOwner) { }
	
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdUnixBaseFTPListItem() { }
	
};


class PASCALIMPLEMENTATION TIdDOSBaseFTPListItem : public Idftplist::TIdFTPListItem
{
	typedef Idftplist::TIdFTPListItem inherited;
	
protected:
	TIdDOSAttributes* FAttributes;
	void __fastcall SetAttributes(TIdDOSAttributes* AAttributes);
	
public:
	__fastcall virtual TIdDOSBaseFTPListItem(System::Classes::TCollection* AOwner);
	__fastcall virtual ~TIdDOSBaseFTPListItem();
	__property TIdDOSAttributes* Attributes = {read=FAttributes, write=SetAttributes};
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 IdFILE_ATTRIBUTE_READONLY = System::Int8(0x1);
static constexpr System::Int8 IdFILE_ATTRIBUTE_HIDDEN = System::Int8(0x2);
static constexpr System::Int8 IdFILE_ATTRIBUTE_SYSTEM = System::Int8(0x4);
static constexpr System::Int8 IdFILE_ATTRIBUTE_DIRECTORY = System::Int8(0x10);
static constexpr System::Int8 IdFILE_ATTRIBUTE_ARCHIVE = System::Int8(0x20);
static constexpr System::Int8 IdFILE_ATTRIBUTE_DEVICE = System::Int8(0x40);
static constexpr System::Byte IdFILE_ATTRIBUTE_NORMAL = System::Byte(0x80);
static constexpr System::Word IdFILE_ATTRIBUTE_TEMPORARY = System::Word(0x100);
static constexpr System::Word IdFILE_ATTRIBUTE_SPARSE_FILE = System::Word(0x200);
static constexpr System::Word IdFILE_ATTRIBUTE_REPARSE_POINT = System::Word(0x400);
static constexpr System::Word IdFILE_ATTRIBUTE_COMPRESSED = System::Word(0x800);
static constexpr System::Word IdFILE_ATTRIBUTE_OFFLINE = System::Word(0x1000);
static constexpr System::Word IdFILE_ATTRIBUTE_NOT_CONTENT_INDEXED = System::Word(0x2000);
static constexpr System::Word IdFILE_ATTRIBUTE_ENCRYPTED = System::Word(0x4000);
}	/* namespace Idftplisttypes */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPLISTTYPES)
using namespace Idftplisttypes;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftplisttypesHPP
