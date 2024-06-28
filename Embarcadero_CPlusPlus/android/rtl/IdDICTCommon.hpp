// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDICTCommon.pas' rev: 34.00 (Android)

#ifndef IddictcommonHPP
#define IddictcommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddictcommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMatchItem;
class DELPHICLASS TIdMatchList;
class DELPHICLASS TIdGeneric;
class DELPHICLASS TIdStrategy;
class DELPHICLASS TIdStrategyList;
class DELPHICLASS TIdDBInfo;
class DELPHICLASS TIdDBList;
class DELPHICLASS TIdDefinition;
class DELPHICLASS TIdDefinitions;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMatchItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	System::UnicodeString FDB;
	System::UnicodeString FWord;
	
__published:
	__property System::UnicodeString DB = {read=FDB, write=FDB};
	__property System::UnicodeString Word = {read=FWord, write=FWord};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdMatchItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdMatchItem() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdMatchList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdMatchItem* operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	TIdMatchItem* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TIdMatchItem* const AValue);
	
public:
	__fastcall virtual TIdMatchList();
	int __fastcall IndexOf(TIdMatchItem* AItem);
	HIDESBASE TIdMatchItem* __fastcall Add();
	__property TIdMatchItem* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdMatchList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdGeneric : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	System::UnicodeString FName;
	System::UnicodeString FDesc;
	
__published:
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::UnicodeString Desc = {read=FDesc, write=FDesc};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdGeneric(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdGeneric() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStrategy : public TIdGeneric
{
	typedef TIdGeneric inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdStrategy(System::Classes::TCollection* Collection) : TIdGeneric(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdStrategy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdStrategyList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdStrategy* operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	TIdStrategy* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TIdStrategy* const AValue);
	
public:
	__fastcall virtual TIdStrategyList();
	int __fastcall IndexOf(TIdStrategy* AItem);
	HIDESBASE TIdStrategy* __fastcall Add();
	__property TIdStrategy* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdStrategyList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDBInfo : public TIdGeneric
{
	typedef TIdGeneric inherited;
	
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TIdDBInfo(System::Classes::TCollection* Collection) : TIdGeneric(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TIdDBInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDBList : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdDBInfo* operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	TIdDBInfo* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TIdDBInfo* const AValue);
	
public:
	__fastcall virtual TIdDBList();
	int __fastcall IndexOf(TIdDBInfo* AItem);
	HIDESBASE TIdDBInfo* __fastcall Add();
	__property TIdDBInfo* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdDBList() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDefinition : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
protected:
	System::UnicodeString FWord;
	System::Classes::TStrings* FDefinition;
	TIdDBInfo* FDB;
	void __fastcall SetDefinition(System::Classes::TStrings* AValue);
	
public:
	__fastcall virtual TIdDefinition(System::Classes::TCollection* AOwner);
	__fastcall virtual ~TIdDefinition();
	
__published:
	__property System::UnicodeString Word = {read=FWord, write=FWord};
	__property TIdDBInfo* DB = {read=FDB, write=FDB};
	__property System::Classes::TStrings* Definition = {read=FDefinition, write=SetDefinition};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdDefinitions : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TIdDefinition* operator[](int AIndex) { return this->Items[AIndex]; }
	
protected:
	TIdDefinition* __fastcall GetItems(int AIndex);
	void __fastcall SetItems(int AIndex, TIdDefinition* const AValue);
	
public:
	__fastcall virtual TIdDefinitions();
	int __fastcall IndexOf(TIdDefinition* AItem);
	HIDESBASE TIdDefinition* __fastcall Add();
	__property TIdDefinition* Items[int AIndex] = {read=GetItems, write=SetItems/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TIdDefinitions() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddictcommon */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDICTCOMMON)
using namespace Iddictcommon;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddictcommonHPP
