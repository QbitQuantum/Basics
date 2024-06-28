// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBSubscription.pas' rev: 34.00 (iOS)

#ifndef Ibx_IbsubscriptionHPP
#define Ibx_IbsubscriptionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IBX.IBDatabase.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibsubscription
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIBSubscriptionInfo;
class DELPHICLASS TIBSubscriptionInfos;
class DELPHICLASS TIBSubscriptionItem;
class DELPHICLASS TIBSubscriptionItems;
class DELPHICLASS TIBSubscriptions;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIBDmlAction : unsigned char { diInsert, diUpdate, diDelete };

typedef System::Set<TIBDmlAction, TIBDmlAction::diInsert, TIBDmlAction::diDelete> TIBDmlActions;

class PASCALIMPLEMENTATION TIBSubscriptionInfo : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FForTable;
	System::Classes::TStrings* FColumnList;
	TIBDmlActions FDmlActions;
	void __fastcall SetColumnList(System::Classes::TStrings* const Value);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TIBSubscriptionInfo(System::Classes::TCollection* Collection);
	__fastcall virtual ~TIBSubscriptionInfo();
	void __fastcall AddColumn(System::UnicodeString AColumn);
	void __fastcall AddColumns(System::Classes::TStrings* Columns);
	System::UnicodeString __fastcall CreateSQL();
	void __fastcall Clear();
	System::UnicodeString __fastcall GetColumns();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction};
	
__published:
	__property System::UnicodeString ForTable = {read=FForTable, write=FForTable};
	__property TIBDmlActions DmlActions = {read=FDmlActions, write=FDmlActions, nodefault};
	__property System::Classes::TStrings* Columns = {read=FColumnList, write=SetColumnList};
};


class PASCALIMPLEMENTATION TIBSubscriptionInfos : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TIBSubscriptionInfo* operator[](int Index) { return this->SubscriptionInfos[Index]; }
	
private:
	TIBSubscriptionInfo* __fastcall GetSubscriptionInfos(int Index);
	void __fastcall SetSubscriptionInfos(int Index, TIBSubscriptionInfo* const Value);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	
public:
	__fastcall TIBSubscriptionInfos(TIBSubscriptionItem* AOwner);
	HIDESBASE TIBSubscriptionInfo* __fastcall Add()/* overload */;
	HIDESBASE TIBSubscriptionInfo* __fastcall Add(System::UnicodeString ForTable)/* overload */;
	void __fastcall DeleteInfo(TIBSubscriptionInfo* info);
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction};
	__property TIBSubscriptionInfo* SubscriptionInfos[int Index] = {read=GetSubscriptionInfos, write=SetSubscriptionInfos/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIBSubscriptionInfos() { }
	
};


class PASCALIMPLEMENTATION TIBSubscriptionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FSubscriptionName;
	TIBSubscriptionInfos* FSubscriptionInfos;
	System::UnicodeString FDescription;
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TIBSubscriptionItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TIBSubscriptionItem();
	System::UnicodeString __fastcall CreateSQL();
	void __fastcall Clear();
	void __fastcall RetriveInfo();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::Classes::TStrings* __fastcall SubscriptionNames();
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction};
	
__published:
	__property TIBSubscriptionInfos* SubscriptionInfos = {read=FSubscriptionInfos, write=FSubscriptionInfos};
	__property System::UnicodeString SubscriptionName = {read=FSubscriptionName, write=FSubscriptionName};
	__property System::UnicodeString Description = {read=FDescription, write=FDescription};
};


class PASCALIMPLEMENTATION TIBSubscriptionItems : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TIBSubscriptionItem* operator[](int Index) { return this->SubscriptionItems[Index]; }
	
private:
	TIBSubscriptionItem* __fastcall GetSubscriptionItems(int Index);
	void __fastcall SetSubscriptionItems(int Index, TIBSubscriptionItem* const Value);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	
public:
	__fastcall TIBSubscriptionItems(TIBSubscriptions* AOwner);
	HIDESBASE TIBSubscriptionItem* __fastcall Add();
	System::UnicodeString __fastcall SubscriptionList();
	System::Classes::TStrings* __fastcall SubscriptionNames();
	void __fastcall DeleteItem(TIBSubscriptionItem* item);
	__property TIBSubscriptionItem* SubscriptionItems[int Index] = {read=GetSubscriptionItems, write=SetSubscriptionItems/*, default*/};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIBSubscriptionItems() { }
	
};


class PASCALIMPLEMENTATION TIBSubscriptions : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Ibx::Ibdatabase::TIBBase* FBase;
	System::UnicodeString FDestination;
	TIBSubscriptionItems* FSubscriptions;
	bool FActive;
	System::Classes::TStringList* FNameList;
	Ibx::Ibdatabase::TIBTransaction* __fastcall GetTransaction();
	void __fastcall SetDatabase(Ibx::Ibdatabase::TIBDatabase* const Value);
	void __fastcall SetTransaction(Ibx::Ibdatabase::TIBTransaction* const Value);
	void __fastcall SetActive(const bool Value);
	void __fastcall DoBeforeTransactionEnd(System::TObject* Sender);
	Ibx::Ibdatabase::TIBDatabase* __fastcall GetDatabase();
	
protected:
	void __fastcall ActivateConnection();
	
public:
	__fastcall virtual TIBSubscriptions(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TIBSubscriptions();
	void __fastcall CreateSubscriptions();
	System::UnicodeString __fastcall CreateScript();
	void __fastcall DropSubscriptions(bool Cascade = false);
	void __fastcall GrantTo(System::UnicodeString UserName);
	void __fastcall RevokeFrom(System::UnicodeString UserName);
	TIBSubscriptionItem* __fastcall Add(System::UnicodeString SubscriptionName);
	TIBSubscriptionItem* __fastcall Find(System::UnicodeString SubscriptionName);
	void __fastcall Delete(System::UnicodeString SubscriptionName);
	void __fastcall RetrieveFullInfo();
	void __fastcall Clear();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	System::Classes::TStrings* __fastcall SubscriptionNames();
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property System::UnicodeString Destination = {read=FDestination, write=FDestination};
	
__published:
	__property TIBSubscriptionItems* SubscriptionItems = {read=FSubscriptions, write=FSubscriptions};
	__property Ibx::Ibdatabase::TIBDatabase* Database = {read=GetDatabase, write=SetDatabase};
	__property Ibx::Ibdatabase::TIBTransaction* Transaction = {read=GetTransaction, write=SetTransaction};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ibsubscription */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBSUBSCRIPTION)
using namespace Ibx::Ibsubscription;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbsubscriptionHPP
