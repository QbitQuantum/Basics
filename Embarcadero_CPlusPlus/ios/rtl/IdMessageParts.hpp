// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageParts.pas' rev: 34.00 (iOS)

#ifndef IdmessagepartsHPP
#define IdmessagepartsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdHeaderList.hpp>
#include <IdExceptionCore.hpp>
#include <IdGlobal.hpp>
#include <IdException.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessageparts
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessagePart;
class DELPHICLASS TIdMessageParts;
class DELPHICLASS EIdCanNotCreateMessagePart;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TOnGetMessagePartStream)(System::Classes::TStream* AStream);

enum DECLSPEC_DENUM TIdMessagePartType : unsigned char { mptText, mptAttachment };

class PASCALIMPLEMENTATION TIdMessagePart : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	System::UnicodeString FContentMD5;
	System::UnicodeString FCharSet;
	System::UnicodeString FEndBoundary;
	Idheaderlist::TIdHeaderList* FExtraHeaders;
	System::UnicodeString FFileName;
	System::UnicodeString FName;
	Idheaderlist::TIdHeaderList* FHeaders;
	bool FIsEncoded;
	TOnGetMessagePartStream FOnGetMessagePartStream;
	int FParentPart;
	virtual System::UnicodeString __fastcall GetContentDisposition();
	virtual System::UnicodeString __fastcall GetContentType();
	virtual System::UnicodeString __fastcall GetContentTransfer();
	virtual System::UnicodeString __fastcall GetContentID();
	virtual System::UnicodeString __fastcall GetContentLocation();
	virtual System::UnicodeString __fastcall GetContentDescription();
	TIdMessageParts* __fastcall GetMessageParts();
	System::Classes::TPersistent* __fastcall GetOwnerMessage();
	virtual void __fastcall SetContentDisposition(const System::UnicodeString Value);
	virtual void __fastcall SetContentType(const System::UnicodeString Value);
	virtual void __fastcall SetContentTransfer(const System::UnicodeString Value);
	void __fastcall SetExtraHeaders(Idheaderlist::TIdHeaderList* const Value);
	virtual void __fastcall SetContentID(const System::UnicodeString Value);
	virtual void __fastcall SetContentDescription(const System::UnicodeString Value);
	virtual void __fastcall SetContentLocation(const System::UnicodeString Value);
	
public:
	__fastcall virtual TIdMessagePart(System::Classes::TCollection* Collection);
	__fastcall virtual ~TIdMessagePart();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::UnicodeString __fastcall GetCharSet(System::UnicodeString AHeader);
	System::UnicodeString __fastcall ResolveContentType(System::UnicodeString AContentType);
	__classmethod virtual TIdMessagePartType __fastcall PartType();
	__property bool IsEncoded = {read=FIsEncoded, nodefault};
	__property TIdMessageParts* MessageParts = {read=GetMessageParts};
	__property System::Classes::TPersistent* OwnerMessage = {read=GetOwnerMessage};
	__property TOnGetMessagePartStream OnGetMessagePartStream = {read=FOnGetMessagePartStream, write=FOnGetMessagePartStream};
	__property Idheaderlist::TIdHeaderList* Headers = {read=FHeaders};
	
__published:
	__property System::UnicodeString CharSet = {read=FCharSet, write=FCharSet};
	__property System::UnicodeString ContentDescription = {read=GetContentDescription, write=SetContentDescription};
	__property System::UnicodeString ContentDisposition = {read=GetContentDisposition, write=SetContentDisposition};
	__property System::UnicodeString ContentID = {read=GetContentID, write=SetContentID};
	__property System::UnicodeString ContentLocation = {read=GetContentLocation, write=SetContentLocation};
	__property System::UnicodeString ContentTransfer = {read=GetContentTransfer, write=SetContentTransfer};
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
	__property Idheaderlist::TIdHeaderList* ExtraHeaders = {read=FExtraHeaders, write=SetExtraHeaders};
	__property System::UnicodeString FileName = {read=FFileName, write=FFileName};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property int ParentPart = {read=FParentPart, write=FParentPart, nodefault};
};


_DECLARE_METACLASS(System::TMetaClass, TIdMessagePartClass);

class PASCALIMPLEMENTATION TIdMessageParts : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TIdMessagePart* operator[](int Index) { return this->Items[Index]; }
	
protected:
	System::UnicodeString FAttachmentEncoding;
	int FAttachmentCount;
	System::TObject* FMessageEncoderInfo;
	int FRelatedPartCount;
	int FTextPartCount;
	HIDESBASE TIdMessagePart* __fastcall GetItem(int Index);
	System::Classes::TPersistent* __fastcall GetOwnerMessage();
	void __fastcall SetAttachmentEncoding(const System::UnicodeString AValue);
	HIDESBASE void __fastcall SetItem(int Index, TIdMessagePart* const Value);
	
public:
	HIDESBASE TIdMessagePart* __fastcall Add();
	void __fastcall CountParts();
	__fastcall TIdMessageParts(System::Classes::TPersistent* AOwner);
	__property int AttachmentCount = {read=FAttachmentCount, nodefault};
	__property System::UnicodeString AttachmentEncoding = {read=FAttachmentEncoding, write=SetAttachmentEncoding};
	__property TIdMessagePart* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property System::TObject* MessageEncoderInfo = {read=FMessageEncoderInfo};
	__property System::Classes::TPersistent* OwnerMessage = {read=GetOwnerMessage};
	__property int RelatedPartCount = {read=FRelatedPartCount, nodefault};
	__property int TextPartCount = {read=FTextPartCount, nodefault};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdMessageParts() { }
	
};


class PASCALIMPLEMENTATION EIdCanNotCreateMessagePart : public Idexceptioncore::EIdMessageException
{
	typedef Idexceptioncore::EIdMessageException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdCanNotCreateMessagePart(const System::UnicodeString AMsg)/* overload */ : Idexceptioncore::EIdMessageException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdCanNotCreateMessagePart(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexceptioncore::EIdMessageException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdCanNotCreateMessagePart(NativeUInt Ident)/* overload */ : Idexceptioncore::EIdMessageException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdCanNotCreateMessagePart(System::PResStringRec ResStringRec)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCanNotCreateMessagePart(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexceptioncore::EIdMessageException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdCanNotCreateMessagePart(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdCanNotCreateMessagePart(const System::UnicodeString Msg, int AHelpContext) : Idexceptioncore::EIdMessageException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdCanNotCreateMessagePart(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexceptioncore::EIdMessageException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCanNotCreateMessagePart(NativeUInt Ident, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdCanNotCreateMessagePart(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCanNotCreateMessagePart(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdCanNotCreateMessagePart(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexceptioncore::EIdMessageException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdCanNotCreateMessagePart() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessageparts */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGEPARTS)
using namespace Idmessageparts;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagepartsHPP
