// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageCollection.pas' rev: 34.00 (Android)

#ifndef IdmessagecollectionHPP
#define IdmessagecollectionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdMessage.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessagecollection
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMessageItem;
class DELPHICLASS TIdMessageCollection;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TIdMessageItems);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMessageItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	int FAttempt;
	Idmessage::TIdMessage* FMsg;
	bool FQueued;
	
public:
	__fastcall virtual TIdMessageItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TIdMessageItem();
	__property int Attempt = {read=FAttempt, write=FAttempt, nodefault};
	__property Idmessage::TIdMessage* Msg = {read=FMsg};
	__property bool Queued = {read=FQueued, write=FQueued, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMessageCollection : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	Idmessage::TIdMessage* operator[](int index) { return this->Messages[index]; }
	
private:
	Idmessage::TIdMessage* __fastcall GetIdMessage(int index);
	void __fastcall SetIdMessage(int index, Idmessage::TIdMessage* const Value);
	
public:
	__fastcall TIdMessageCollection();
	HIDESBASE TIdMessageItem* __fastcall Add();
	__property Idmessage::TIdMessage* Messages[int index] = {read=GetIdMessage, write=SetIdMessage/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdMessageCollection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessagecollection */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECOLLECTION)
using namespace Idmessagecollection;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessagecollectionHPP
