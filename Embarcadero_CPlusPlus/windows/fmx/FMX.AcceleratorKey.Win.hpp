// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.AcceleratorKey.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Acceleratorkey_WinHPP
#define Fmx_Acceleratorkey_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Platform.hpp>
#include <FMX.AcceleratorKey.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Acceleratorkey
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinAcceleratorKeyRegistry;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinAcceleratorKeyRegistry : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	class DELPHICLASS TAcceleratorKeyReceivers;
	class PASCALIMPLEMENTATION TAcceleratorKeyReceivers : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Generics::Collections::TObjectDictionary__2<System::WideChar,System::Generics::Collections::TList__1<Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver>*>* FReceiversDictionary;
		void __fastcall RemoveReceiver(const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver, System::Generics::Collections::TList__1<Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver>* &AList, const System::WideChar AKey);
		
	public:
		__fastcall virtual ~TAcceleratorKeyReceivers();
		void __fastcall RegisterReceiver(const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver);
		void __fastcall UnregisterReceiver(const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver);
		bool __fastcall EmitAcceleratorKey(const System::Word AKey);
		int __fastcall GetDistinctKeyCount();
	public:
		/* TObject.Create */ inline __fastcall TAcceleratorKeyReceivers() : System::TObject() { }
		
	};
	
	
	
private:
	System::Generics::Collections::TDictionary__2<Fmx::Types::_di_IRoot,TAcceleratorKeyReceivers*>* FFormRegistry;
	
public:
	__fastcall TWinAcceleratorKeyRegistry();
	__fastcall virtual ~TWinAcceleratorKeyRegistry();
	void __fastcall RegisterReceiver(const Fmx::Types::_di_IRoot ARoot, const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver);
	void __fastcall UnregisterReceiver(const Fmx::Types::_di_IRoot ARoot, const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver);
	void __fastcall RemoveRegistry(const Fmx::Types::_di_IRoot ARoot);
	bool __fastcall EmitAcceleratorKey(const Fmx::Types::_di_IRoot ARoot, const System::Word AKey);
	void __fastcall ChangeReceiverRoot(const Fmx::Acceleratorkey::_di_IAcceleratorKeyReceiver AReceiver, const Fmx::Types::_di_IRoot AOldRoot, const Fmx::Types::_di_IRoot ANewRoot);
	void __fastcall ExtractAcceleratorKey(const System::UnicodeString AText, /* out */ System::WideChar &Key, /* out */ int &KeyIndex);
private:
	void *__IFMXAcceleratorKeyRegistryService;	// Fmx::Acceleratorkey::IFMXAcceleratorKeyRegistryService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0D06B7CC-FAF2-45F8-B7AA-D4B84FD384B7}
	operator Fmx::Acceleratorkey::_di_IFMXAcceleratorKeyRegistryService()
	{
		Fmx::Acceleratorkey::_di_IFMXAcceleratorKeyRegistryService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Acceleratorkey::IFMXAcceleratorKeyRegistryService*(void) { return (Fmx::Acceleratorkey::IFMXAcceleratorKeyRegistryService*)&__IFMXAcceleratorKeyRegistryService; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Acceleratorkey */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ACCELERATORKEY_WIN)
using namespace Fmx::Acceleratorkey::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ACCELERATORKEY)
using namespace Fmx::Acceleratorkey;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Acceleratorkey_WinHPP
