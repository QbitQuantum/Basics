// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.ObserverLinks.pas' rev: 34.00 (Windows)

#ifndef Data_Bind_ObserverlinksHPP
#define Data_Bind_ObserverlinksHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Data.Bind.Components.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Bind
{
namespace Observerlinks
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindObserver;
class DELPHICLASS TBindSingleCastObserver;
class DELPHICLASS TBindMultiCastObserver;
class DELPHICLASS TBindEditLinkObserver;
class DELPHICLASS TBindEditGridLinkObserver;
class DELPHICLASS TBindPositionLinkObserver;
class DELPHICLASS TBindControlValueLinkObserver;
class DELPHICLASS TBindIteratorLinkObserver;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindObserver : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Data::Bind::Components::_di_IBindLink FBindLink;
	System::Classes::_di_TObserverToggleEvent FOnToggle;
	
protected:
	__fastcall TBindObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */;
	
public:
	System::Classes::_di_TObserverToggleEvent __fastcall GetOnObserverToggle();
	void __fastcall SetOnObserverToggle(System::Classes::_di_TObserverToggleEvent AEvent);
	void __fastcall Removed();
	bool __fastcall GetActive();
	void __fastcall SetActive(bool Value);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindObserver() { }
	
private:
	void *__IObserver;	// System::Classes::IObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B03253D8-7720-4B68-B10A-E3E79B91ECD3}
	operator System::Classes::_di_IObserver()
	{
		System::Classes::_di_IObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IObserver*(void) { return (System::Classes::IObserver*)&__IObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindSingleCastObserver : public TBindObserver
{
	typedef TBindObserver inherited;
	
protected:
	/* TBindObserver.Create */ inline __fastcall TBindSingleCastObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindSingleCastObserver() { }
	
private:
	void *__ISingleCastObserver;	// System::Classes::ISingleCastObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D0395F17-52AA-4515-93A5-5B292F03AA7B}
	operator System::Classes::_di_ISingleCastObserver()
	{
		System::Classes::_di_ISingleCastObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::ISingleCastObserver*(void) { return (System::Classes::ISingleCastObserver*)&__ISingleCastObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindMultiCastObserver : public TBindObserver
{
	typedef TBindObserver inherited;
	
protected:
	/* TBindObserver.Create */ inline __fastcall TBindMultiCastObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindMultiCastObserver() { }
	
private:
	void *__IMultiCastObserver;	// System::Classes::IMultiCastObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C19CB01E-1233-4405-8A30-7987DF2C3690}
	operator System::Classes::_di_IMultiCastObserver()
	{
		System::Classes::_di_IMultiCastObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IMultiCastObserver*(void) { return (System::Classes::IMultiCastObserver*)&__IMultiCastObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEditLinkObserver : public TBindSingleCastObserver
{
	typedef TBindSingleCastObserver inherited;
	
private:
	bool FTrack;
	
protected:
	bool __fastcall GetTrack();
	
public:
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall GetUpdating();
	void __fastcall Update();
	bool __fastcall Edit();
	void __fastcall Reset();
	void __fastcall Modified();
	bool __fastcall IsModified();
	bool __fastcall IsValidChar(System::WideChar AKey);
	bool __fastcall IsRequired();
	bool __fastcall GetIsReadOnly();
	void __fastcall SetIsReadOnly(bool Value);
	bool __fastcall GetIsEditing();
	__fastcall TBindEditLinkObserver(Data::Bind::Components::TCustomBindLink* ABindLink)/* overload */;
	void __fastcall SetTrack(bool AValue);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
protected:
	/* TBindObserver.Create */ inline __fastcall TBindEditLinkObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindSingleCastObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindEditLinkObserver() { }
	
private:
	void *__IObserverTrack;	// System::Classes::IObserverTrack 
	void *__IEditLinkObserver;	// System::Classes::IEditLinkObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8B9F22C3-FDA3-45FD-99E1-5A88481A9F95}
	operator System::Classes::_di_IObserverTrack()
	{
		System::Classes::_di_IObserverTrack intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IObserverTrack*(void) { return (System::Classes::IObserverTrack*)&__IObserverTrack; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E88C2705-7C5A-4E66-9B81-447D05D5E640}
	operator System::Classes::_di_IEditLinkObserver()
	{
		System::Classes::_di_IEditLinkObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IEditLinkObserver*(void) { return (System::Classes::IEditLinkObserver*)&__IEditLinkObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEditGridLinkObserver : public TBindEditLinkObserver
{
	typedef TBindEditLinkObserver inherited;
	
private:
	System::Classes::_di_TObserverGetCurrentEvent FOnGetCurrent;
	
public:
	System::TVarRec __fastcall GetCurrent();
	System::Classes::_di_TObserverGetCurrentEvent __fastcall GetOnObserverCurrent();
	void __fastcall SetOnObserverCurrent(System::Classes::_di_TObserverGetCurrentEvent AEvent);
	__fastcall TBindEditGridLinkObserver(Data::Bind::Components::TCustomBindGridLink* ABindLink)/* overload */;
	__fastcall TBindEditGridLinkObserver(Data::Bind::Components::TCustomBindListLink* ABindLink)/* overload */;
	__fastcall TBindEditGridLinkObserver(Data::Bind::Components::TCustomBindGridListLink* ABindLink)/* overload */;
public:
	/* TBindEditLinkObserver.Create */ inline __fastcall TBindEditGridLinkObserver(Data::Bind::Components::TCustomBindLink* ABindLink)/* overload */ : TBindEditLinkObserver(ABindLink) { }
	
protected:
	/* TBindObserver.Create */ inline __fastcall TBindEditGridLinkObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindEditLinkObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindEditGridLinkObserver() { }
	
private:
	void *__IEditGridLinkObserver;	// System::Classes::IEditGridLinkObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A911B648-E1E5-4EEC-9FEE-D8E62FFA0E71}
	operator System::Classes::_di_IEditGridLinkObserver()
	{
		System::Classes::_di_IEditGridLinkObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IEditGridLinkObserver*(void) { return (System::Classes::IEditGridLinkObserver*)&__IEditGridLinkObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindPositionLinkObserver : public TBindMultiCastObserver
{
	typedef TBindMultiCastObserver inherited;
	
private:
	Data::Bind::Components::_di_IBindPosition FBindPosition;
	
public:
	__fastcall TBindPositionLinkObserver(Data::Bind::Components::TCustomBindGridLink* ABindLink)/* overload */;
	__fastcall TBindPositionLinkObserver(Data::Bind::Components::TCustomBindListLink* ABindLink)/* overload */;
	__fastcall TBindPositionLinkObserver(Data::Bind::Components::TCustomBindGridListLink* ABindLink)/* overload */;
	__fastcall TBindPositionLinkObserver(Data::Bind::Components::TCustomBindPosition* ABindPosition)/* overload */;
	void __fastcall PosChanged();
	void __fastcall PosChanging();
protected:
	/* TBindObserver.Create */ inline __fastcall TBindPositionLinkObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindMultiCastObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindPositionLinkObserver() { }
	
private:
	void *__IPositionLinkObserver;	// System::Classes::IPositionLinkObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E78B0035-6802-447C-A80A-0AEC04AD851F}
	operator System::Classes::_di_IPositionLinkObserver()
	{
		System::Classes::_di_IPositionLinkObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IPositionLinkObserver*(void) { return (System::Classes::IPositionLinkObserver*)&__IPositionLinkObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindControlValueLinkObserver : public TBindMultiCastObserver
{
	typedef TBindMultiCastObserver inherited;
	
private:
	Data::Bind::Components::_di_IBindControlValue FBindControlValue;
	bool FTrack;
	bool FModified;
	
protected:
	bool __fastcall GetTrack();
	
public:
	__fastcall TBindControlValueLinkObserver(Data::Bind::Components::TCustomBindControlValue* ABindControlValue)/* overload */;
	void __fastcall SetTrack(bool AValue);
	void __fastcall ValueUpdate();
	void __fastcall ValueModified();
protected:
	/* TBindObserver.Create */ inline __fastcall TBindControlValueLinkObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindMultiCastObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindControlValueLinkObserver() { }
	
private:
	void *__IObserverTrack;	// System::Classes::IObserverTrack 
	void *__IControlValueObserver;	// System::Classes::IControlValueObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8B9F22C3-FDA3-45FD-99E1-5A88481A9F95}
	operator System::Classes::_di_IObserverTrack()
	{
		System::Classes::_di_IObserverTrack intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IObserverTrack*(void) { return (System::Classes::IObserverTrack*)&__IObserverTrack; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {61DAC12C-B950-43CA-86B5-43D8E78012E8}
	operator System::Classes::_di_IControlValueObserver()
	{
		System::Classes::_di_IControlValueObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IControlValueObserver*(void) { return (System::Classes::IControlValueObserver*)&__IControlValueObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindIteratorLinkObserver : public TBindMultiCastObserver
{
	typedef TBindMultiCastObserver inherited;
	
private:
	Data::Bind::Components::_di_IScopeRecordEnumerableBuffered FEnumerableBuffered;
	Data::Bind::Components::_di_IScopeRecordEnumerable FEnumerable;
	Data::Bind::Components::_di_IScopeRecordEnumerator FRecordEnum;
	Data::Bind::Components::_di_IScopeRecordControlUpdator FRecordUpdator;
	
protected:
	__fastcall TBindIteratorLinkObserver(Data::Bind::Components::TActivatedContainedBindComponent* ABindLink);
	
public:
	__fastcall TBindIteratorLinkObserver(Data::Bind::Components::TCustomBindGridLink* ABindLink)/* overload */;
	__fastcall TBindIteratorLinkObserver(Data::Bind::Components::TCustomBindListLink* ABindLink)/* overload */;
	__fastcall TBindIteratorLinkObserver(Data::Bind::Components::TCustomBindGridListLink* ABindLink)/* overload */;
	void __fastcall StartFrom(int APosition);
	bool __fastcall MoveNext();
	void __fastcall UpdateControlComponent(System::Classes::TComponent* AControl);
	void __fastcall Finish();
protected:
	/* TBindObserver.Create */ inline __fastcall TBindIteratorLinkObserver(Data::Bind::Components::_di_IBindLink ABindLink)/* overload */ : TBindMultiCastObserver(ABindLink) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindIteratorLinkObserver() { }
	
private:
	void *__IIteratorLinkObserver;	// System::Classes::IIteratorLinkObserver 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8429848A-4447-4211-93D2-745543C7AB57}
	operator System::Classes::_di_IIteratorLinkObserver()
	{
		System::Classes::_di_IIteratorLinkObserver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Classes::IIteratorLinkObserver*(void) { return (System::Classes::IIteratorLinkObserver*)&__IIteratorLinkObserver; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Observerlinks */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_OBSERVERLINKS)
using namespace Data::Bind::Observerlinks;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND)
using namespace Data::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Bind_ObserverlinksHPP
