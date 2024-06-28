// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdBlockCipherIntercept.pas' rev: 34.00 (Android)

#ifndef IdblockcipherinterceptHPP
#define IdblockcipherinterceptHPP

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
#include <IdResourceStringsProtocols.hpp>
#include <IdIntercept.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idblockcipherintercept
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdBlockCipherIntercept;
class DELPHICLASS TIdServerBlockCipherIntercept;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdBlockCipherIntercept : public Idintercept::TIdConnectionIntercept
{
	typedef Idintercept::TIdConnectionIntercept inherited;
	
protected:
	int FBlockSize;
	Idglobal::TIdBytes FIncoming;
	virtual void __fastcall Decrypt(Idglobal::TIdBytes &VData);
	virtual void __fastcall Encrypt(Idglobal::TIdBytes &VData);
	void __fastcall SetBlockSize(const int Value);
	virtual void __fastcall InitComponent();
	
public:
	virtual void __fastcall Receive(Idglobal::TIdBytes &VBuffer);
	virtual void __fastcall Send(Idglobal::TIdBytes &VBuffer);
	void __fastcall CopySettingsFrom(TIdBlockCipherIntercept* ASrcBlockCipherIntercept);
	
__published:
	__property int BlockSize = {read=FBlockSize, write=SetBlockSize, default=16};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdBlockCipherIntercept(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdConnectionIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdBlockCipherIntercept()/* overload */ : Idintercept::TIdConnectionIntercept() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdBlockCipherIntercept() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIdServerBlockCipherIntercept : public Idintercept::TIdServerIntercept
{
	typedef Idintercept::TIdServerIntercept inherited;
	
protected:
	int FBlockSize;
	virtual void __fastcall InitComponent();
	
public:
	virtual void __fastcall Init();
	virtual Idintercept::TIdConnectionIntercept* __fastcall Accept(System::Classes::TComponent* AConnection);
	
__published:
	__property int BlockSize = {read=FBlockSize, write=FBlockSize, default=16};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdServerBlockCipherIntercept(System::Classes::TComponent* AOwner)/* overload */ : Idintercept::TIdServerIntercept(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdServerBlockCipherIntercept()/* overload */ : Idintercept::TIdServerIntercept() { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TIdServerBlockCipherIntercept() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef Idexception::EIdException EIdBlockCipherInterceptException;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 IdBlockCipherBlockSizeDefault = System::Int8(0x10);
static constexpr System::Word IdBlockCipherBlockSizeMax = System::Word(0x100);
}	/* namespace Idblockcipherintercept */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDBLOCKCIPHERINTERCEPT)
using namespace Idblockcipherintercept;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdblockcipherinterceptHPP
