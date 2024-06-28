// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSASLCollection.pas' rev: 34.00 (iOS)

#ifndef IdsaslcollectionHPP
#define IdsaslcollectionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdBaseComponent.hpp>
#include <IdCoder.hpp>
#include <IdException.hpp>
#include <IdSASL.hpp>
#include <IdTCPConnection.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsaslcollection
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdSASLListEntry;
class DELPHICLASS TIdSASLEntries;
class DELPHICLASS EIdSASLException;
class DELPHICLASS EIdSASLNotSupported;
class DELPHICLASS EIdSASLNotReady;
class DELPHICLASS EIdSASLMechNeeded;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdSASLListEntry : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	Idsasl::TIdSASL* FSASL;
	virtual System::UnicodeString __fastcall GetDisplayName();
	System::Classes::TComponent* __fastcall GetOwnerComponent();
	TIdSASLEntries* __fastcall GetSASLEntries();
	void __fastcall SetSASL(Idsasl::TIdSASL* AValue);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::Classes::TComponent* OwnerComponent = {read=GetOwnerComponent};
	__property TIdSASLEntries* SASLEntries = {read=GetSASLEntries};
	
__published:
	__property Idsasl::TIdSASL* SASL = {read=FSASL, write=SetSASL};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdSASLListEntry(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdSASLListEntry() { }
	
};


class PASCALIMPLEMENTATION TIdSASLEntries : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TIdSASLListEntry* operator[](int Index) { return this->Items[Index]; }
	
protected:
	void __fastcall CheckIfEmpty();
	HIDESBASE TIdSASLListEntry* __fastcall GetItem(int Index);
	System::Classes::TComponent* __fastcall GetOwnerComponent();
	HIDESBASE void __fastcall SetItem(int Index, TIdSASLListEntry* const Value);
	
public:
	__fastcall TIdSASLEntries(System::Classes::TPersistent* AOwner);
	HIDESBASE TIdSASLListEntry* __fastcall Add();
	void __fastcall LoginSASL(const System::UnicodeString ACmd, const System::UnicodeString AHost, const System::UnicodeString AProtocolName, const System::UnicodeString *AOkReplies, const int AOkReplies_High, const System::UnicodeString *AContinueReplies, const int AContinueReplies_High, Idtcpconnection::TIdTCPConnection* AClient, System::Classes::TStrings* ACapaReply, const System::UnicodeString AAuthString = u"AUTH", bool ACanAttemptIR = true)/* overload */;
	void __fastcall LoginSASL(const System::UnicodeString ACmd, const System::UnicodeString AHost, const System::UnicodeString AProtocolName, const System::UnicodeString AServiceName, const System::UnicodeString *AOkReplies, const int AOkReplies_High, const System::UnicodeString *AContinueReplies, const int AContinueReplies_High, Idtcpconnection::TIdTCPConnection* AClient, System::Classes::TStrings* ACapaReply, const System::UnicodeString AAuthString = u"AUTH", bool ACanAttemptIR = true)/* overload */;
	System::Classes::TStrings* __fastcall ParseCapaReply _DEPRECATED_ATTRIBUTE1("Use ParseCapaReplyToList()") (System::Classes::TStrings* ACapaReply, const System::UnicodeString AAuthString = u"AUTH");
	void __fastcall ParseCapaReplyToList(System::Classes::TStrings* ACapaReply, System::Classes::TStrings* ADestList, const System::UnicodeString AAuthString = u"AUTH");
	Idsasl::TIdSASL* __fastcall FindSASL(const System::UnicodeString AServiceName);
	HIDESBASE TIdSASLListEntry* __fastcall Insert(int Index);
	void __fastcall RemoveByComp(System::Classes::TComponent* AComponent);
	int __fastcall IndexOfComp(Idsasl::TIdSASL* AItem);
	__property TIdSASLListEntry* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property System::Classes::TComponent* OwnerComponent = {read=GetOwnerComponent};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdSASLEntries() { }
	
};


class PASCALIMPLEMENTATION EIdSASLException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLException() { }
	
};


class PASCALIMPLEMENTATION EIdSASLNotSupported : public EIdSASLException
{
	typedef EIdSASLException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLNotSupported(const System::UnicodeString AMsg)/* overload */ : EIdSASLException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLNotSupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLNotSupported(NativeUInt Ident)/* overload */ : EIdSASLException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLNotSupported(System::PResStringRec ResStringRec)/* overload */ : EIdSASLException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLNotSupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLNotSupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLNotSupported(const System::UnicodeString Msg, int AHelpContext) : EIdSASLException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLNotSupported(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLNotSupported(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLNotSupported(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLNotSupported(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLNotSupported(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLNotSupported() { }
	
};


class PASCALIMPLEMENTATION EIdSASLNotReady : public EIdSASLException
{
	typedef EIdSASLException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLNotReady(const System::UnicodeString AMsg)/* overload */ : EIdSASLException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLNotReady(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLNotReady(NativeUInt Ident)/* overload */ : EIdSASLException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLNotReady(System::PResStringRec ResStringRec)/* overload */ : EIdSASLException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLNotReady(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLNotReady(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLNotReady(const System::UnicodeString Msg, int AHelpContext) : EIdSASLException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLNotReady(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLNotReady(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLNotReady(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLNotReady(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLNotReady(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLNotReady() { }
	
};


class PASCALIMPLEMENTATION EIdSASLMechNeeded : public EIdSASLException
{
	typedef EIdSASLException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSASLMechNeeded(const System::UnicodeString AMsg)/* overload */ : EIdSASLException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSASLMechNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSASLException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLMechNeeded(NativeUInt Ident)/* overload */ : EIdSASLException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSASLMechNeeded(System::PResStringRec ResStringRec)/* overload */ : EIdSASLException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLMechNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSASLMechNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSASLMechNeeded(const System::UnicodeString Msg, int AHelpContext) : EIdSASLException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSASLMechNeeded(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSASLException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLMechNeeded(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSASLException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSASLMechNeeded(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLMechNeeded(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSASLMechNeeded(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSASLException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSASLMechNeeded() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idsaslcollection */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSASLCOLLECTION)
using namespace Idsaslcollection;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsaslcollectionHPP
