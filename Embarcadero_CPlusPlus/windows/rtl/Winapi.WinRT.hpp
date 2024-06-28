// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.WinRT.pas' rev: 34.00 (Windows)

#ifndef Winapi_WinrtHPP
#define Winapi_WinrtHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
DECLARE_HANDLE(HSTRING);

namespace Winapi
{
namespace Winrt
{
//-- forward type declarations -----------------------------------------------
struct HSTRING_HEADER;
class DELPHICLASS TRoSimpleMetaDataBuilder;
class DELPHICLASS TRoMetaDataLocator;
__interface DELPHIINTERFACE IInspectable;
typedef System::DelphiInterface<IInspectable> _di_IInspectable;
__interface DELPHIINTERFACE IActivationFactory;
typedef System::DelphiInterface<IActivationFactory> _di_IActivationFactory;
struct DECLSPEC_DRECORD RO_REGISTRATION_COOKIE
{
};


//-- type declarations -------------------------------------------------------
typedef System::WideChar * *PPCWSTR;

typedef HSTRING *PHSTRING;

typedef PHSTRING *PPHSTRING;

typedef NativeUInt HSTRING_BUFFER;

struct DECLSPEC_DRECORD HSTRING_HEADER
{
	
private:
	struct DECLSPEC_DRECORD _HSTRING_HEADER__1
	{
		
	public:
		union
		{
			struct 
			{
#ifndef _WIN64
				System::StaticArray<System::Byte, 20> Reserved2;
#else /* _WIN64 */
				System::StaticArray<System::Byte, 24> Reserved2;
#endif /* _WIN64 */
			};
			struct 
			{
				void *Reserved1;
			};
			
		};
	};
	
	
	
public:
	_HSTRING_HEADER__1 Reserved;
};


typedef HSTRING_HEADER *PHSTRING_HEADER;

typedef NativeUInt ROPARAMIIDHANDLE;

typedef ROPARAMIIDHANDLE *PROPARAMIIDHANDLE;

typedef HRESULT __stdcall (*PINSPECT_HSTRING_CALLBACK)(void * context, NativeUInt readAddress, unsigned length, System::PByte buffer);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRoSimpleMetaDataBuilder : public System::TObject
{
	typedef System::TObject inherited;
	
public:
#ifndef _WIN64
	virtual HRESULT __stdcall SetWinRtInterface(GUID iid) = 0 ;
	virtual HRESULT __stdcall SetDelegate(GUID iid) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __stdcall SetWinRtInterface(const GUID &iid) = 0 ;
	virtual HRESULT __stdcall SetDelegate(const GUID &iid) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __stdcall SetInterfaceGroupSimpleDefault(System::WideChar * name, System::WideChar * defaultInterfaceName, System::PGUID defaultInterfaeceIID) = 0 ;
	virtual HRESULT __stdcall SetInterfaceGroupParameterizedDefault(System::WideChar * name, unsigned elemetCount, PPCWSTR defaultInterfaceNameElements) = 0 ;
	virtual HRESULT __stdcall SetRuntimeClassSimpleDefault(System::WideChar * name, System::WideChar * defaultInterfaceName, System::PGUID defaultInterfaceIID) = 0 ;
	virtual HRESULT __stdcall SetRuntimeClassParameterizedDefault(System::WideChar * name, unsigned elementCount, PPCWSTR defaultInterfaceNameElements) = 0 ;
	virtual HRESULT __stdcall SetStruct(System::WideChar * name, unsigned numFields, PPCWSTR fieldTypeNames) = 0 ;
	virtual HRESULT __stdcall SetEnum(System::WideChar * name, System::WideChar * basetype) = 0 ;
#ifndef _WIN64
	virtual HRESULT __stdcall SetParameterizedInterface(GUID piid, unsigned numArgs) = 0 ;
	virtual HRESULT __stdcall SetParameterizedDelegate(GUID piid, unsigned numArgs) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __stdcall SetParameterizedInterface(const GUID &piid, unsigned numArgs) = 0 ;
	virtual HRESULT __stdcall SetParameterizedDelegate(const GUID &piid, unsigned numArgs) = 0 ;
#endif /* _WIN64 */
public:
	/* TObject.Create */ inline __fastcall TRoSimpleMetaDataBuilder() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRoSimpleMetaDataBuilder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TRoMetaDataLocator : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual HRESULT __stdcall Locate(System::WideChar * nameElement, TRoSimpleMetaDataBuilder* metaDataDestination) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TRoMetaDataLocator() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRoMetaDataLocator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM RO_INIT_TYPE : unsigned char { RO_INIT_SINGLETHREADED, RO_INIT_MULTITHREADED };

enum DECLSPEC_DENUM TrustLevel : unsigned char { BaseTrust, PartialTrust, FullTrust };

__interface  INTERFACE_UUID("{AF86E2E0-B12D-4C6A-9C5A-D7AA65101E90}") IInspectable  : public System::IInterface 
{
	virtual HRESULT __stdcall GetIids(/* out */ unsigned &iidCount, /* out */ System::PGUID &iids) = 0 ;
	virtual HRESULT __stdcall GetRuntimeClassName(/* out */ HSTRING &className) = 0 ;
	virtual HRESULT __stdcall GetTrustLevel(/* out */ TrustLevel &trust) = 0 ;
};

__interface  INTERFACE_UUID("{00000035-0000-0000-C000-000000000046}") IActivationFactory  : public IInspectable 
{
	virtual HRESULT __stdcall ActivateInstance(/* out */ _di_IInspectable &instance) = 0 ;
};

typedef _di_IInspectable *PIInspectable;

typedef HRESULT __stdcall (*PFNGETACTIVATIONFACTORY)(HSTRING activatableClassId, /* out */ _di_IActivationFactory &factory);

typedef PFNGETACTIVATIONFACTORY *PPFNGETACTIVATIONFACTORY;

typedef RO_REGISTRATION_COOKIE *PRO_REGISTRATION_COOKIE;

//-- var, const, procedure ---------------------------------------------------
extern "C" HRESULT __stdcall WindowsCreateString(System::WideChar * sourceString, unsigned length, /* out */ HSTRING &Str);
extern "C" HRESULT __stdcall WindowsCreateStringReference(System::WideChar * sourceString, unsigned length, /* out */ HSTRING_HEADER &hstringHeader, /* out */ HSTRING &str);
extern "C" HRESULT __stdcall WindowsDeleteString(HSTRING Str);
extern "C" HRESULT __stdcall WindowsDuplicateString(HSTRING str, /* out */ HSTRING &newStr);
extern "C" unsigned __stdcall WindowsGetStringLen(HSTRING str);
extern "C" System::WideChar * __stdcall WindowsGetStringRawBuffer(HSTRING str, System::PCardinal len);
extern "C" System::LongBool __fastcall WindowsIsStringEmpty(HSTRING str);
extern "C" HRESULT __stdcall WindowsStringHasEmbeddedNull(HSTRING str, /* out */ System::LongBool &hasEmbededNull);
extern "C" HRESULT __stdcall WindowsCompareStringOrdinal(HSTRING string1, HSTRING string2, /* out */ unsigned &res);
extern "C" HRESULT __stdcall WindowsSubstring(HSTRING str, unsigned startIndex, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsSubstringWithSpecifiedLength(HSTRING str, unsigned startIndex, unsigned length, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsConcatString(HSTRING string1, HSTRING string2, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsReplaceString(HSTRING str, HSTRING stringReplaced, HSTRING stringReplacedWith, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsTrimStringStart(HSTRING str, HSTRING trimString, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsTrimStringEnd(HSTRING str, HSTRING trimString, /* out */ HSTRING &newString);
extern "C" HRESULT __stdcall WindowsPreallocateStringBuffer(unsigned length, /* out */ System::WideChar * &charBuffer, /* out */ HSTRING_BUFFER &bufferHandle);
extern "C" HRESULT __stdcall WindowsPromoteStringBuffer(HSTRING_BUFFER bufferHandle, /* out */ HSTRING &str);
extern "C" HRESULT __stdcall WindowsDeleteStringBuffer(HSTRING_BUFFER bufferHandle);
extern "C" HRESULT __stdcall WindowsInspectString(NativeUInt targetHString, System::Word machine, PINSPECT_HSTRING_CALLBACK callback, void * context, /* out */ unsigned &length);
extern "C" HRESULT __stdcall RoGetParameterizedTypeInstanceIID(unsigned nameElementCount, PPCWSTR nameElements, TRoMetaDataLocator* const metaDataLocator, System::PGUID iid, PROPARAMIIDHANDLE pExtra);
extern "C" void __stdcall RoFreeParameterizedTypeExtra(ROPARAMIIDHANDLE extra);
extern "C" System::WideChar * __stdcall RoParameterizedTypeExtraGetTypeSignature(ROPARAMIIDHANDLE extra);
extern "C" HRESULT __stdcall RoInitialize(RO_INIT_TYPE InitType);
extern "C" void __stdcall RoUninitialize(void);
extern "C" HRESULT __stdcall RoActivateInstance(HSTRING activatableClassId, /* out */ _di_IInspectable &instance);
extern "C" HRESULT __stdcall RoRegisterActivationFactories(PHSTRING activatableClassIds, PPFNGETACTIVATIONFACTORY activationFactoryCallbacks, unsigned count, PRO_REGISTRATION_COOKIE cookie);
extern "C" HRESULT __stdcall RoRevokeActivationFactories(RO_REGISTRATION_COOKIE cookie);
extern "C" HRESULT __stdcall RoGetActivationFactory(HSTRING activatableClassId, const GUID &iid, /* out */ _di_IInspectable &outfactory);
}	/* namespace Winrt */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINRT)
using namespace Winapi::Winrt;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_WinrtHPP
