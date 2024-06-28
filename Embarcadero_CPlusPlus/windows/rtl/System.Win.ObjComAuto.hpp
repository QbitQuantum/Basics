// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.ObjComAuto.pas' rev: 34.00 (Windows)

#ifndef System_Win_ObjcomautoHPP
#define System_Win_ObjcomautoHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.ObjAuto.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.TypInfo.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Objcomauto
{
//-- forward type declarations -----------------------------------------------
struct TDispatchInfo;
class DELPHICLASS TObjectDispatch;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDispatchKind : unsigned char { dkMethod, dkProperty, dkSubComponent };

struct DECLSPEC_DRECORD TDispatchInfo
{
public:
	System::TObject* Instance;
	
public:
	TDispatchKind Kind;
	union
	{
		struct 
		{
			int Index;
		};
		struct 
		{
			System::Typinfo::TPropInfo *PropInfo;
		};
		struct 
		{
			System::Objauto::TMethodInfoHeader *MethodInfo;
		};
		
	};
};


typedef System::DynamicArray<TDispatchInfo> TDispatchInfos;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TObjectDispatch : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	int FDispatchInfoCount;
	TDispatchInfos FDispatchInfos;
	System::TObject* FInstance;
	bool FOwned;
	int __fastcall AllocDispID(TDispatchKind AKind, void * Value, System::TObject* AInstance);
	
protected:
	virtual TObjectDispatch* __fastcall GetObjectDispatch(System::TObject* Obj);
	virtual System::Objauto::PMethodInfoHeader __fastcall GetMethodInfo(const System::ShortString &AName, System::TObject* &AInstance);
	virtual System::Typinfo::PPropInfo __fastcall GetPropInfo(const System::UnicodeString AName, System::TObject* &AInstance, int &CompIndex);
	__property System::TObject* Instance = {read=FInstance};
	
public:
	virtual HRESULT __stdcall GetIDsOfNames(const GUID &IID, void * Names, int NameCount, int LocaleID, void * DispIDs);
	HRESULT __stdcall GetTypeInfo(int Index, int LocaleID, /* out */ void *TypeInfo);
	HRESULT __stdcall GetTypeInfoCount(/* out */ int &Count);
	virtual HRESULT __stdcall Invoke(int DispID, const GUID &IID, int LocaleID, System::Word Flags, void *Params, void * VarResult, void * ExcepInfo, void * ArgErr);
	__fastcall TObjectDispatch(System::TObject* Instance, bool Owned);
	__fastcall virtual ~TObjectDispatch();
private:
	void *__IDispatch;	// IDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00020400-0000-0000-C000-000000000046}
	operator _di_IDispatch()
	{
		_di_IDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDispatch*(void) { return (IDispatch*)&__IDispatch; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::TMethod __fastcall CreateMethodPointer(const _di_IDispatch Instance, int DispID, System::Typinfo::PTypeInfo TypeInfo)/* overload */;
extern DELPHI_PACKAGE System::TMethod __fastcall CreateMethodPointer(const _di_IDispatch Instance, const System::UnicodeString MethodName, System::Typinfo::PTypeInfo TypeInfo)/* overload */;
extern DELPHI_PACKAGE void __fastcall ReleaseMethodPointer(const System::TMethod &MethodPointer);
}	/* namespace Objcomauto */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_OBJCOMAUTO)
using namespace System::Win::Objcomauto;
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
#endif	// System_Win_ObjcomautoHPP
