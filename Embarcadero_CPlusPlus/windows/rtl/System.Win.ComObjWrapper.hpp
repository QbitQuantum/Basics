// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.ComObjWrapper.pas' rev: 34.00 (Windows)

#ifndef System_Win_ComobjwrapperHPP
#define System_Win_ComobjwrapperHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Win.ComObj.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Comobjwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TComComponent;
class DELPHICLASS TWrappedComObject;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TGetComClassEvent)(TComComponent* Sender, System::Win::Comobj::TComClass &ComClass);

typedef void __fastcall (__closure *TComObjectEvent)(TComComponent* Sender, TWrappedComObject* const ComObject);

class PASCALIMPLEMENTATION TComComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FDescription;
	GUID FGUID;
	TGetComClassEvent FOnGetComClass;
	TComObjectEvent FOnCreated;
	TComObjectEvent FOnDestroy;
	void __fastcall SetGUIDString(const System::UnicodeString Value);
	virtual void __fastcall RegisterClass();
	virtual void __fastcall UnregisterClass();
	System::UnicodeString __fastcall GetGUIDString();
	
protected:
	virtual void __fastcall DoCreated(TWrappedComObject* const ComObj);
	virtual void __fastcall DoDestroy(TWrappedComObject* const ComObj);
	virtual System::Win::Comobj::TComClass __fastcall GetComClass();
	
public:
	__fastcall virtual TComComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TComComponent();
	System::_di_IInterface __fastcall CreateObject();
	__property System::UnicodeString Description = {read=FDescription, write=FDescription};
	__property System::UnicodeString GUID = {read=GetGUIDString, write=SetGUIDString};
	__property TGetComClassEvent OnGetComClass = {read=FOnGetComClass, write=FOnGetComClass};
	__property TComObjectEvent OnCreated = {read=FOnCreated, write=FOnCreated};
	__property TComObjectEvent OnDestroy = {read=FOnDestroy, write=FOnDestroy};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWrappedComObject : public System::Win::Comobj::TComObject
{
	typedef System::Win::Comobj::TComObject inherited;
	
private:
	TComComponent* FComComponent;
	
protected:
	__property TComComponent* ComComponent = {read=FComComponent};
	
public:
	__fastcall virtual ~TWrappedComObject();
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall Initialize();
public:
	/* TComObject.Create */ inline __fastcall TWrappedComObject() : System::Win::Comobj::TComObject() { }
	/* TComObject.CreateAggregated */ inline __fastcall TWrappedComObject(const System::_di_IInterface Controller) : System::Win::Comobj::TComObject(Controller) { }
	/* TComObject.CreateFromFactory */ inline __fastcall TWrappedComObject(System::Win::Comobj::TComObjectFactory* Factory, const System::_di_IInterface Controller) : System::Win::Comobj::TComObject(Factory, Controller) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Comobjwrapper */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_COMOBJWRAPPER)
using namespace System::Win::Comobjwrapper;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_ComobjwrapperHPP
