// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.IEInterfaces.pas' rev: 34.00 (Windows)

#ifndef System_Win_IeinterfacesHPP
#define System_Win_IeinterfacesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Ieinterfaces
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IHTMLDocument;
typedef System::DelphiInterface<IHTMLDocument> _di_IHTMLDocument;
__interface DELPHIINTERFACE IHTMLElement;
typedef System::DelphiInterface<IHTMLElement> _di_IHTMLElement;
__interface DELPHIINTERFACE IHTMLFramesCollection2;
typedef System::DelphiInterface<IHTMLFramesCollection2> _di_IHTMLFramesCollection2;
__interface DELPHIINTERFACE IHTMLFormElement;
typedef System::DelphiInterface<IHTMLFormElement> _di_IHTMLFormElement;
__interface DELPHIINTERFACE IHTMLOptionElement;
typedef System::DelphiInterface<IHTMLOptionElement> _di_IHTMLOptionElement;
__interface DELPHIINTERFACE IHTMLElementCollection;
typedef System::DelphiInterface<IHTMLElementCollection> _di_IHTMLElementCollection;
__interface DELPHIINTERFACE IHTMLOptionElementFactory;
typedef System::DelphiInterface<IHTMLOptionElementFactory> _di_IHTMLOptionElementFactory;
__interface DELPHIINTERFACE IHTMLEventObj;
typedef System::DelphiInterface<IHTMLEventObj> _di_IHTMLEventObj;
__interface DELPHIINTERFACE IHTMLMimeTypesCollection;
typedef System::DelphiInterface<IHTMLMimeTypesCollection> _di_IHTMLMimeTypesCollection;
__interface DELPHIINTERFACE IHTMLPluginsCollection;
typedef System::DelphiInterface<IHTMLPluginsCollection> _di_IHTMLPluginsCollection;
__interface DELPHIINTERFACE IHTMLOpsProfile;
typedef System::DelphiInterface<IHTMLOpsProfile> _di_IHTMLOpsProfile;
__interface DELPHIINTERFACE IOmNavigator;
typedef System::DelphiInterface<IOmNavigator> _di_IOmNavigator;
__interface DELPHIINTERFACE IHTMLImgElement;
typedef System::DelphiInterface<IHTMLImgElement> _di_IHTMLImgElement;
__interface DELPHIINTERFACE IHTMLImageElementFactory;
typedef System::DelphiInterface<IHTMLImageElementFactory> _di_IHTMLImageElementFactory;
__interface DELPHIINTERFACE IHTMLLocation;
typedef System::DelphiInterface<IHTMLLocation> _di_IHTMLLocation;
__interface DELPHIINTERFACE IOmHistory;
typedef System::DelphiInterface<IOmHistory> _di_IOmHistory;
__interface DELPHIINTERFACE IHTMLScreen;
typedef System::DelphiInterface<IHTMLScreen> _di_IHTMLScreen;
__interface DELPHIINTERFACE IHTMLWindow2;
typedef System::DelphiInterface<IHTMLWindow2> _di_IHTMLWindow2;
__interface DELPHIINTERFACE IHTMLSelectionObject;
typedef System::DelphiInterface<IHTMLSelectionObject> _di_IHTMLSelectionObject;
__interface DELPHIINTERFACE IHTMLStyleSheetsCollection;
typedef System::DelphiInterface<IHTMLStyleSheetsCollection> _di_IHTMLStyleSheetsCollection;
__interface DELPHIINTERFACE IHTMLRuleStyle;
typedef System::DelphiInterface<IHTMLRuleStyle> _di_IHTMLRuleStyle;
__interface DELPHIINTERFACE IHTMLStyleSheetRule;
typedef System::DelphiInterface<IHTMLStyleSheetRule> _di_IHTMLStyleSheetRule;
__interface DELPHIINTERFACE IHTMLStyleSheetRulesCollection;
typedef System::DelphiInterface<IHTMLStyleSheetRulesCollection> _di_IHTMLStyleSheetRulesCollection;
__interface DELPHIINTERFACE IHTMLStyleSheet;
typedef System::DelphiInterface<IHTMLStyleSheet> _di_IHTMLStyleSheet;
__interface DELPHIINTERFACE IHTMLDocument2;
typedef System::DelphiInterface<IHTMLDocument2> _di_IHTMLDocument2;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{626FC520-A41E-11CF-A731-00A0C9082637}") IHTMLDocument  : public IDispatch 
{
	virtual HRESULT __safecall Get_Script(_di_IDispatch &__Get_Script_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_Script() { _di_IDispatch __r; HRESULT __hr = Get_Script(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch Script = {read=_scw_Get_Script};
};

__interface  INTERFACE_UUID("{3050F1FF-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLElement  : public IDispatch 
{
	virtual HRESULT __safecall Set_innerHTML(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_innerHTML(System::WideString &__Get_innerHTML_result) = 0 ;
	virtual HRESULT __safecall Get_document(_di_IDispatch &__Get_document_result) = 0 ;
};

__interface  INTERFACE_UUID("{332C4426-26CB-11D0-B483-00C04FD90119}") IHTMLFramesCollection2  : public IDispatch 
{
	virtual HRESULT __safecall item(const System::OleVariant &pvarIndex, System::OleVariant &__item_result) = 0 ;
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length};
};

__interface  INTERFACE_UUID("{3050F1F7-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLFormElement  : public IDispatch 
{
	virtual HRESULT __safecall Set_action(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_action(System::WideString &__Get_action_result) = 0 ;
	virtual HRESULT __safecall Set_dir(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_dir(System::WideString &__Get_dir_result) = 0 ;
	virtual HRESULT __safecall Set_encoding(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_encoding(System::WideString &__Get_encoding_result) = 0 ;
	virtual HRESULT __safecall Set_method(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_method(System::WideString &__Get_method_result) = 0 ;
	virtual HRESULT __safecall Get_elements(_di_IDispatch &__Get_elements_result) = 0 ;
	virtual HRESULT __safecall Set_target(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_target(System::WideString &__Get_target_result) = 0 ;
	virtual HRESULT __safecall Set_name(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_name(System::WideString &__Get_name_result) = 0 ;
	virtual HRESULT __safecall Set_onsubmit(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onsubmit(System::OleVariant &__Get_onsubmit_result) = 0 ;
	virtual HRESULT __safecall Set_onreset(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onreset(System::OleVariant &__Get_onreset_result) = 0 ;
	virtual HRESULT __safecall submit() = 0 ;
	virtual HRESULT __safecall reset() = 0 ;
	virtual HRESULT __safecall Set_length(int p) = 0 ;
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	virtual HRESULT __safecall Get__newEnum(System::_di_IInterface &__Get__newEnum_result) = 0 ;
	virtual HRESULT __safecall item(System::OleVariant name, System::OleVariant index, _di_IDispatch &__item_result) = 0 ;
	virtual HRESULT __safecall tags(System::OleVariant tagName, _di_IDispatch &__tags_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_action() { System::WideString __r; HRESULT __hr = Get_action(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString action = {read=_scw_Get_action, write=Set_action};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_dir() { System::WideString __r; HRESULT __hr = Get_dir(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString dir = {read=_scw_Get_dir, write=Set_dir};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_encoding() { System::WideString __r; HRESULT __hr = Get_encoding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString encoding = {read=_scw_Get_encoding, write=Set_encoding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_method() { System::WideString __r; HRESULT __hr = Get_method(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString method = {read=_scw_Get_method, write=Set_method};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_elements() { _di_IDispatch __r; HRESULT __hr = Get_elements(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch elements = {read=_scw_Get_elements};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_target() { System::WideString __r; HRESULT __hr = Get_target(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString target = {read=_scw_Get_target, write=Set_target};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_name() { System::WideString __r; HRESULT __hr = Get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString name = {read=_scw_Get_name, write=Set_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onsubmit() { System::OleVariant __r; HRESULT __hr = Get_onsubmit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onsubmit = {read=_scw_Get_onsubmit, write=Set_onsubmit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onreset() { System::OleVariant __r; HRESULT __hr = Get_onreset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onreset = {read=_scw_Get_onreset, write=Set_onreset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length, write=Set_length};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__newEnum() { System::_di_IInterface __r; HRESULT __hr = Get__newEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _newEnum = {read=_scw_Get__newEnum};
};

__interface  INTERFACE_UUID("{3050F211-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLOptionElement  : public IDispatch 
{
	virtual HRESULT __safecall Set_selected(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_selected(System::WordBool &__Get_selected_result) = 0 ;
	virtual HRESULT __safecall Set_value(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_value(System::WideString &__Get_value_result) = 0 ;
	virtual HRESULT __safecall Set_defaultSelected(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_defaultSelected(System::WordBool &__Get_defaultSelected_result) = 0 ;
	virtual HRESULT __safecall Set_index(int p) = 0 ;
	virtual HRESULT __safecall Get_index(int &__Get_index_result) = 0 ;
	virtual HRESULT __safecall Set_text(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_text(System::WideString &__Get_text_result) = 0 ;
	virtual HRESULT __safecall Get_form(_di_IHTMLFormElement &__Get_form_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_selected() { System::WordBool __r; HRESULT __hr = Get_selected(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool selected = {read=_scw_Get_selected, write=Set_selected};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_value() { System::WideString __r; HRESULT __hr = Get_value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString value = {read=_scw_Get_value, write=Set_value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_defaultSelected() { System::WordBool __r; HRESULT __hr = Get_defaultSelected(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool defaultSelected = {read=_scw_Get_defaultSelected, write=Set_defaultSelected};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_index() { int __r; HRESULT __hr = Get_index(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int index = {read=_scw_Get_index, write=Set_index};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_text() { System::WideString __r; HRESULT __hr = Get_text(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString text = {read=_scw_Get_text, write=Set_text};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLFormElement _scw_Get_form() { _di_IHTMLFormElement __r; HRESULT __hr = Get_form(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLFormElement form = {read=_scw_Get_form};
};

__interface  INTERFACE_UUID("{3050F21F-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLElementCollection  : public IDispatch 
{
	virtual HRESULT __safecall toString(System::WideString &__toString_result) = 0 ;
	virtual HRESULT __safecall Set_length(int p) = 0 ;
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	virtual HRESULT __safecall Get__newEnum(System::_di_IInterface &__Get__newEnum_result) = 0 ;
	virtual HRESULT __safecall item(System::OleVariant name, System::OleVariant index, _di_IDispatch &__item_result) = 0 ;
	virtual HRESULT __safecall tags(System::OleVariant tagName, _di_IDispatch &__tags_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length, write=Set_length};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__newEnum() { System::_di_IInterface __r; HRESULT __hr = Get__newEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _newEnum = {read=_scw_Get__newEnum};
};

__interface  INTERFACE_UUID("{3050F38C-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLOptionElementFactory  : public IDispatch 
{
	virtual HRESULT __safecall create(System::OleVariant text, System::OleVariant value, System::OleVariant defaultSelected, System::OleVariant selected, _di_IHTMLOptionElement &__create_result) = 0 ;
};

__interface  INTERFACE_UUID("{3050F32D-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLEventObj  : public IDispatch 
{
	virtual HRESULT __safecall Get_srcElement(_di_IHTMLElement &__Get_srcElement_result) = 0 ;
	virtual HRESULT __safecall Get_altKey(System::WordBool &__Get_altKey_result) = 0 ;
	virtual HRESULT __safecall Get_ctrlKey(System::WordBool &__Get_ctrlKey_result) = 0 ;
	virtual HRESULT __safecall Get_shiftKey(System::WordBool &__Get_shiftKey_result) = 0 ;
	virtual HRESULT __safecall Set_returnValue(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_returnValue(System::OleVariant &__Get_returnValue_result) = 0 ;
	virtual HRESULT __safecall Set_cancelBubble(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_cancelBubble(System::WordBool &__Get_cancelBubble_result) = 0 ;
	virtual HRESULT __safecall Get_fromElement(_di_IHTMLElement &__Get_fromElement_result) = 0 ;
	virtual HRESULT __safecall Get_toElement(_di_IHTMLElement &__Get_toElement_result) = 0 ;
	virtual HRESULT __safecall Set_keyCode(int p) = 0 ;
	virtual HRESULT __safecall Get_keyCode(int &__Get_keyCode_result) = 0 ;
	virtual HRESULT __safecall Get_button(int &__Get_button_result) = 0 ;
	virtual HRESULT __safecall Get_type_(System::WideString &__Get_type__result) = 0 ;
	virtual HRESULT __safecall Get_qualifier(System::WideString &__Get_qualifier_result) = 0 ;
	virtual HRESULT __safecall Get_reason(int &__Get_reason_result) = 0 ;
	virtual HRESULT __safecall Get_x(int &__Get_x_result) = 0 ;
	virtual HRESULT __safecall Get_y(int &__Get_y_result) = 0 ;
	virtual HRESULT __safecall Get_clientX(int &__Get_clientX_result) = 0 ;
	virtual HRESULT __safecall Get_clientY(int &__Get_clientY_result) = 0 ;
	virtual HRESULT __safecall Get_offsetX(int &__Get_offsetX_result) = 0 ;
	virtual HRESULT __safecall Get_offsetY(int &__Get_offsetY_result) = 0 ;
	virtual HRESULT __safecall Get_screenX(int &__Get_screenX_result) = 0 ;
	virtual HRESULT __safecall Get_screenY(int &__Get_screenY_result) = 0 ;
	virtual HRESULT __safecall Get_srcFilter(_di_IDispatch &__Get_srcFilter_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_srcElement() { _di_IHTMLElement __r; HRESULT __hr = Get_srcElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement srcElement = {read=_scw_Get_srcElement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_altKey() { System::WordBool __r; HRESULT __hr = Get_altKey(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool altKey = {read=_scw_Get_altKey};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_ctrlKey() { System::WordBool __r; HRESULT __hr = Get_ctrlKey(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool ctrlKey = {read=_scw_Get_ctrlKey};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_shiftKey() { System::WordBool __r; HRESULT __hr = Get_shiftKey(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool shiftKey = {read=_scw_Get_shiftKey};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_returnValue() { System::OleVariant __r; HRESULT __hr = Get_returnValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant returnValue = {read=_scw_Get_returnValue, write=Set_returnValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_cancelBubble() { System::WordBool __r; HRESULT __hr = Get_cancelBubble(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool cancelBubble = {read=_scw_Get_cancelBubble, write=Set_cancelBubble};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_fromElement() { _di_IHTMLElement __r; HRESULT __hr = Get_fromElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement fromElement = {read=_scw_Get_fromElement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_toElement() { _di_IHTMLElement __r; HRESULT __hr = Get_toElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement toElement = {read=_scw_Get_toElement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_keyCode() { int __r; HRESULT __hr = Get_keyCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int keyCode = {read=_scw_Get_keyCode, write=Set_keyCode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_button() { int __r; HRESULT __hr = Get_button(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int button = {read=_scw_Get_button};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_type_() { System::WideString __r; HRESULT __hr = Get_type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString type_ = {read=_scw_Get_type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_qualifier() { System::WideString __r; HRESULT __hr = Get_qualifier(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString qualifier = {read=_scw_Get_qualifier};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_reason() { int __r; HRESULT __hr = Get_reason(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int reason = {read=_scw_Get_reason};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_x() { int __r; HRESULT __hr = Get_x(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int x = {read=_scw_Get_x};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_y() { int __r; HRESULT __hr = Get_y(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int y = {read=_scw_Get_y};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_clientX() { int __r; HRESULT __hr = Get_clientX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int clientX = {read=_scw_Get_clientX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_clientY() { int __r; HRESULT __hr = Get_clientY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int clientY = {read=_scw_Get_clientY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_offsetX() { int __r; HRESULT __hr = Get_offsetX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int offsetX = {read=_scw_Get_offsetX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_offsetY() { int __r; HRESULT __hr = Get_offsetY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int offsetY = {read=_scw_Get_offsetY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_screenX() { int __r; HRESULT __hr = Get_screenX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int screenX = {read=_scw_Get_screenX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_screenY() { int __r; HRESULT __hr = Get_screenY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int screenY = {read=_scw_Get_screenY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_srcFilter() { _di_IDispatch __r; HRESULT __hr = Get_srcFilter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch srcFilter = {read=_scw_Get_srcFilter};
};

__interface  INTERFACE_UUID("{3050F3FC-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLMimeTypesCollection  : public IDispatch 
{
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length};
};

__interface  INTERFACE_UUID("{3050F3FD-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLPluginsCollection  : public IDispatch 
{
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	virtual HRESULT __safecall refresh(System::WordBool reload) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length};
};

__interface  INTERFACE_UUID("{3050F401-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLOpsProfile  : public IDispatch 
{
	virtual HRESULT __safecall addRequest(const System::WideString name, System::OleVariant reserved, System::WordBool &__addRequest_result) = 0 ;
	virtual HRESULT __safecall clearRequest() = 0 ;
	virtual HRESULT __safecall doRequest(System::OleVariant usage, System::OleVariant fname, System::OleVariant domain, System::OleVariant path, System::OleVariant expire, System::OleVariant reserved) = 0 ;
	virtual HRESULT __safecall getAttribute(const System::WideString name, System::WideString &__getAttribute_result) = 0 ;
	virtual HRESULT __safecall setAttribute(const System::WideString name, const System::WideString value, System::OleVariant prefs, System::WordBool &__setAttribute_result) = 0 ;
	virtual HRESULT __safecall commitChanges(System::WordBool &__commitChanges_result) = 0 ;
	virtual HRESULT __safecall addReadRequest(const System::WideString name, System::OleVariant reserved, System::WordBool &__addReadRequest_result) = 0 ;
	virtual HRESULT __safecall doReadRequest(System::OleVariant usage, System::OleVariant fname, System::OleVariant domain, System::OleVariant path, System::OleVariant expire, System::OleVariant reserved) = 0 ;
	virtual HRESULT __safecall doWriteRequest(System::WordBool &__doWriteRequest_result) = 0 ;
};

__interface  INTERFACE_UUID("{FECEAAA5-8405-11CF-8BA1-00AA00476DA6}") IOmNavigator  : public IDispatch 
{
	virtual HRESULT __safecall Get_appCodeName(System::WideString &__Get_appCodeName_result) = 0 ;
	virtual HRESULT __safecall Get_appName(System::WideString &__Get_appName_result) = 0 ;
	virtual HRESULT __safecall Get_appVersion(System::WideString &__Get_appVersion_result) = 0 ;
	virtual HRESULT __safecall Get_userAgent(System::WideString &__Get_userAgent_result) = 0 ;
	virtual HRESULT __safecall javaEnabled(System::WordBool &__javaEnabled_result) = 0 ;
	virtual HRESULT __safecall taintEnabled(System::WordBool &__taintEnabled_result) = 0 ;
	virtual HRESULT __safecall Get_mimeTypes(_di_IHTMLMimeTypesCollection &__Get_mimeTypes_result) = 0 ;
	virtual HRESULT __safecall Get_plugins(_di_IHTMLPluginsCollection &__Get_plugins_result) = 0 ;
	virtual HRESULT __safecall Get_cookieEnabled(System::WordBool &__Get_cookieEnabled_result) = 0 ;
	virtual HRESULT __safecall Get_opsProfile(_di_IHTMLOpsProfile &__Get_opsProfile_result) = 0 ;
	virtual HRESULT __safecall toString(System::WideString &__toString_result) = 0 ;
	virtual HRESULT __safecall Get_cpuClass(System::WideString &__Get_cpuClass_result) = 0 ;
	virtual HRESULT __safecall Get_systemLanguage(System::WideString &__Get_systemLanguage_result) = 0 ;
	virtual HRESULT __safecall Get_browserLanguage(System::WideString &__Get_browserLanguage_result) = 0 ;
	virtual HRESULT __safecall Get_userLanguage(System::WideString &__Get_userLanguage_result) = 0 ;
	virtual HRESULT __safecall Get_platform(System::WideString &__Get_platform_result) = 0 ;
	virtual HRESULT __safecall Get_appMinorVersion(System::WideString &__Get_appMinorVersion_result) = 0 ;
	virtual HRESULT __safecall Get_connectionSpeed(int &__Get_connectionSpeed_result) = 0 ;
	virtual HRESULT __safecall Get_onLine(System::WordBool &__Get_onLine_result) = 0 ;
	virtual HRESULT __safecall Get_userProfile(_di_IHTMLOpsProfile &__Get_userProfile_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_appCodeName() { System::WideString __r; HRESULT __hr = Get_appCodeName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString appCodeName = {read=_scw_Get_appCodeName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_appName() { System::WideString __r; HRESULT __hr = Get_appName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString appName = {read=_scw_Get_appName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_appVersion() { System::WideString __r; HRESULT __hr = Get_appVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString appVersion = {read=_scw_Get_appVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_userAgent() { System::WideString __r; HRESULT __hr = Get_userAgent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString userAgent = {read=_scw_Get_userAgent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLMimeTypesCollection _scw_Get_mimeTypes() { _di_IHTMLMimeTypesCollection __r; HRESULT __hr = Get_mimeTypes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLMimeTypesCollection mimeTypes = {read=_scw_Get_mimeTypes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLPluginsCollection _scw_Get_plugins() { _di_IHTMLPluginsCollection __r; HRESULT __hr = Get_plugins(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLPluginsCollection plugins = {read=_scw_Get_plugins};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_cookieEnabled() { System::WordBool __r; HRESULT __hr = Get_cookieEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool cookieEnabled = {read=_scw_Get_cookieEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLOpsProfile _scw_Get_opsProfile() { _di_IHTMLOpsProfile __r; HRESULT __hr = Get_opsProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLOpsProfile opsProfile = {read=_scw_Get_opsProfile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_cpuClass() { System::WideString __r; HRESULT __hr = Get_cpuClass(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString cpuClass = {read=_scw_Get_cpuClass};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_systemLanguage() { System::WideString __r; HRESULT __hr = Get_systemLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString systemLanguage = {read=_scw_Get_systemLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_browserLanguage() { System::WideString __r; HRESULT __hr = Get_browserLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString browserLanguage = {read=_scw_Get_browserLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_userLanguage() { System::WideString __r; HRESULT __hr = Get_userLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString userLanguage = {read=_scw_Get_userLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_platform() { System::WideString __r; HRESULT __hr = Get_platform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString platform = {read=_scw_Get_platform};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_appMinorVersion() { System::WideString __r; HRESULT __hr = Get_appMinorVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString appMinorVersion = {read=_scw_Get_appMinorVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_connectionSpeed() { int __r; HRESULT __hr = Get_connectionSpeed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int connectionSpeed = {read=_scw_Get_connectionSpeed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_onLine() { System::WordBool __r; HRESULT __hr = Get_onLine(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool onLine = {read=_scw_Get_onLine};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLOpsProfile _scw_Get_userProfile() { _di_IHTMLOpsProfile __r; HRESULT __hr = Get_userProfile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLOpsProfile userProfile = {read=_scw_Get_userProfile};
};

__interface  INTERFACE_UUID("{3050F240-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLImgElement  : public IDispatch 
{
	virtual HRESULT __safecall Set_isMap(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_isMap(System::WordBool &__Get_isMap_result) = 0 ;
	virtual HRESULT __safecall Set_useMap(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_useMap(System::WideString &__Get_useMap_result) = 0 ;
	virtual HRESULT __safecall Get_mimeType(System::WideString &__Get_mimeType_result) = 0 ;
	virtual HRESULT __safecall Get_fileSize(System::WideString &__Get_fileSize_result) = 0 ;
	virtual HRESULT __safecall Get_fileCreatedDate(System::WideString &__Get_fileCreatedDate_result) = 0 ;
	virtual HRESULT __safecall Get_fileModifiedDate(System::WideString &__Get_fileModifiedDate_result) = 0 ;
	virtual HRESULT __safecall Get_fileUpdatedDate(System::WideString &__Get_fileUpdatedDate_result) = 0 ;
	virtual HRESULT __safecall Get_protocol(System::WideString &__Get_protocol_result) = 0 ;
	virtual HRESULT __safecall Get_href(System::WideString &__Get_href_result) = 0 ;
	virtual HRESULT __safecall Get_nameProp(System::WideString &__Get_nameProp_result) = 0 ;
	virtual HRESULT __safecall Set_border(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_border(System::OleVariant &__Get_border_result) = 0 ;
	virtual HRESULT __safecall Set_vspace(int p) = 0 ;
	virtual HRESULT __safecall Get_vspace(int &__Get_vspace_result) = 0 ;
	virtual HRESULT __safecall Set_hspace(int p) = 0 ;
	virtual HRESULT __safecall Get_hspace(int &__Get_hspace_result) = 0 ;
	virtual HRESULT __safecall Set_alt(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_alt(System::WideString &__Get_alt_result) = 0 ;
	virtual HRESULT __safecall Set_src(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_src(System::WideString &__Get_src_result) = 0 ;
	virtual HRESULT __safecall Set_lowsrc(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_lowsrc(System::WideString &__Get_lowsrc_result) = 0 ;
	virtual HRESULT __safecall Set_vrml(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_vrml(System::WideString &__Get_vrml_result) = 0 ;
	virtual HRESULT __safecall Set_dynsrc(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_dynsrc(System::WideString &__Get_dynsrc_result) = 0 ;
	virtual HRESULT __safecall Get_readyState(System::WideString &__Get_readyState_result) = 0 ;
	virtual HRESULT __safecall Get_complete(System::WordBool &__Get_complete_result) = 0 ;
	virtual HRESULT __safecall Set_loop(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_loop(System::OleVariant &__Get_loop_result) = 0 ;
	virtual HRESULT __safecall Set_align(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_align(System::WideString &__Get_align_result) = 0 ;
	virtual HRESULT __safecall Set_onload(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onload(System::OleVariant &__Get_onload_result) = 0 ;
	virtual HRESULT __safecall Set_onerror(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onerror(System::OleVariant &__Get_onerror_result) = 0 ;
	virtual HRESULT __safecall Set_onabort(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onabort(System::OleVariant &__Get_onabort_result) = 0 ;
	virtual HRESULT __safecall Set_name(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_name(System::WideString &__Get_name_result) = 0 ;
	virtual HRESULT __safecall Set_width(int p) = 0 ;
	virtual HRESULT __safecall Get_width(int &__Get_width_result) = 0 ;
	virtual HRESULT __safecall Set_height(int p) = 0 ;
	virtual HRESULT __safecall Get_height(int &__Get_height_result) = 0 ;
	virtual HRESULT __safecall Set_start(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_start(System::WideString &__Get_start_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_isMap() { System::WordBool __r; HRESULT __hr = Get_isMap(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool isMap = {read=_scw_Get_isMap, write=Set_isMap};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_useMap() { System::WideString __r; HRESULT __hr = Get_useMap(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString useMap = {read=_scw_Get_useMap, write=Set_useMap};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_mimeType() { System::WideString __r; HRESULT __hr = Get_mimeType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString mimeType = {read=_scw_Get_mimeType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileSize() { System::WideString __r; HRESULT __hr = Get_fileSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileSize = {read=_scw_Get_fileSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileCreatedDate() { System::WideString __r; HRESULT __hr = Get_fileCreatedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileCreatedDate = {read=_scw_Get_fileCreatedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileModifiedDate() { System::WideString __r; HRESULT __hr = Get_fileModifiedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileModifiedDate = {read=_scw_Get_fileModifiedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileUpdatedDate() { System::WideString __r; HRESULT __hr = Get_fileUpdatedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileUpdatedDate = {read=_scw_Get_fileUpdatedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_protocol() { System::WideString __r; HRESULT __hr = Get_protocol(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString protocol = {read=_scw_Get_protocol};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_href() { System::WideString __r; HRESULT __hr = Get_href(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString href = {read=_scw_Get_href};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_nameProp() { System::WideString __r; HRESULT __hr = Get_nameProp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString nameProp = {read=_scw_Get_nameProp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_border() { System::OleVariant __r; HRESULT __hr = Get_border(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant border = {read=_scw_Get_border, write=Set_border};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_vspace() { int __r; HRESULT __hr = Get_vspace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int vspace = {read=_scw_Get_vspace, write=Set_vspace};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_hspace() { int __r; HRESULT __hr = Get_hspace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int hspace = {read=_scw_Get_hspace, write=Set_hspace};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_alt() { System::WideString __r; HRESULT __hr = Get_alt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString alt = {read=_scw_Get_alt, write=Set_alt};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_src() { System::WideString __r; HRESULT __hr = Get_src(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString src = {read=_scw_Get_src, write=Set_src};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_lowsrc() { System::WideString __r; HRESULT __hr = Get_lowsrc(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString lowsrc = {read=_scw_Get_lowsrc, write=Set_lowsrc};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_vrml() { System::WideString __r; HRESULT __hr = Get_vrml(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString vrml = {read=_scw_Get_vrml, write=Set_vrml};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_dynsrc() { System::WideString __r; HRESULT __hr = Get_dynsrc(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString dynsrc = {read=_scw_Get_dynsrc, write=Set_dynsrc};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_readyState() { System::WideString __r; HRESULT __hr = Get_readyState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString readyState = {read=_scw_Get_readyState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_complete() { System::WordBool __r; HRESULT __hr = Get_complete(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool complete = {read=_scw_Get_complete};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_loop() { System::OleVariant __r; HRESULT __hr = Get_loop(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant loop = {read=_scw_Get_loop, write=Set_loop};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_align() { System::WideString __r; HRESULT __hr = Get_align(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString align = {read=_scw_Get_align, write=Set_align};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onload() { System::OleVariant __r; HRESULT __hr = Get_onload(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onload = {read=_scw_Get_onload, write=Set_onload};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onerror() { System::OleVariant __r; HRESULT __hr = Get_onerror(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onerror = {read=_scw_Get_onerror, write=Set_onerror};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onabort() { System::OleVariant __r; HRESULT __hr = Get_onabort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onabort = {read=_scw_Get_onabort, write=Set_onabort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_name() { System::WideString __r; HRESULT __hr = Get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString name = {read=_scw_Get_name, write=Set_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_width() { int __r; HRESULT __hr = Get_width(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int width = {read=_scw_Get_width, write=Set_width};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_height() { int __r; HRESULT __hr = Get_height(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int height = {read=_scw_Get_height, write=Set_height};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_start() { System::WideString __r; HRESULT __hr = Get_start(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString start = {read=_scw_Get_start, write=Set_start};
};

__interface  INTERFACE_UUID("{3050F38E-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLImageElementFactory  : public IDispatch 
{
	virtual HRESULT __safecall create(System::OleVariant width, System::OleVariant height, _di_IHTMLImgElement &__create_result) = 0 ;
};

__interface  INTERFACE_UUID("{163BB1E0-6E00-11CF-837A-48DC04C10000}") IHTMLLocation  : public IDispatch 
{
	virtual HRESULT __safecall Set_href(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_href(System::WideString &__Get_href_result) = 0 ;
	virtual HRESULT __safecall Set_protocol(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_protocol(System::WideString &__Get_protocol_result) = 0 ;
	virtual HRESULT __safecall Set_host(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_host(System::WideString &__Get_host_result) = 0 ;
	virtual HRESULT __safecall Set_hostname(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_hostname(System::WideString &__Get_hostname_result) = 0 ;
	virtual HRESULT __safecall Set_port(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_port(System::WideString &__Get_port_result) = 0 ;
	virtual HRESULT __safecall Set_pathname(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_pathname(System::WideString &__Get_pathname_result) = 0 ;
	virtual HRESULT __safecall Set_search(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_search(System::WideString &__Get_search_result) = 0 ;
	virtual HRESULT __safecall Set_hash(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_hash(System::WideString &__Get_hash_result) = 0 ;
	virtual HRESULT __safecall reload(System::WordBool flag) = 0 ;
	virtual HRESULT __safecall replace(const System::WideString bstr) = 0 ;
	virtual HRESULT __safecall Assign_(const System::WideString bstr) = 0 ;
	virtual HRESULT __safecall toString(System::WideString &__toString_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_href() { System::WideString __r; HRESULT __hr = Get_href(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString href = {read=_scw_Get_href, write=Set_href};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_protocol() { System::WideString __r; HRESULT __hr = Get_protocol(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString protocol = {read=_scw_Get_protocol, write=Set_protocol};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_host() { System::WideString __r; HRESULT __hr = Get_host(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString host = {read=_scw_Get_host, write=Set_host};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_hostname() { System::WideString __r; HRESULT __hr = Get_hostname(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString hostname = {read=_scw_Get_hostname, write=Set_hostname};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_port() { System::WideString __r; HRESULT __hr = Get_port(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString port = {read=_scw_Get_port, write=Set_port};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_pathname() { System::WideString __r; HRESULT __hr = Get_pathname(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString pathname = {read=_scw_Get_pathname, write=Set_pathname};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_search() { System::WideString __r; HRESULT __hr = Get_search(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString search = {read=_scw_Get_search, write=Set_search};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_hash() { System::WideString __r; HRESULT __hr = Get_hash(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString hash = {read=_scw_Get_hash, write=Set_hash};
};

__interface  INTERFACE_UUID("{FECEAAA2-8405-11CF-8BA1-00AA00476DA6}") IOmHistory  : public IDispatch 
{
	virtual HRESULT __safecall Get_length(short &__Get_length_result) = 0 ;
	virtual HRESULT __safecall back(const System::OleVariant &pvargdistance) = 0 ;
	virtual HRESULT __safecall forward(const System::OleVariant &pvargdistance) = 0 ;
	virtual HRESULT __safecall go(const System::OleVariant &pvargdistance) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline short _scw_Get_length() { short __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property short length = {read=_scw_Get_length};
};

__interface  INTERFACE_UUID("{3050F35C-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLScreen  : public IDispatch 
{
	virtual HRESULT __safecall Get_colorDepth(int &__Get_colorDepth_result) = 0 ;
	virtual HRESULT __safecall Set_bufferDepth(int p) = 0 ;
	virtual HRESULT __safecall Get_bufferDepth(int &__Get_bufferDepth_result) = 0 ;
	virtual HRESULT __safecall Get_width(int &__Get_width_result) = 0 ;
	virtual HRESULT __safecall Get_height(int &__Get_height_result) = 0 ;
	virtual HRESULT __safecall Set_updateInterval(int p) = 0 ;
	virtual HRESULT __safecall Get_updateInterval(int &__Get_updateInterval_result) = 0 ;
	virtual HRESULT __safecall Get_availHeight(int &__Get_availHeight_result) = 0 ;
	virtual HRESULT __safecall Get_availWidth(int &__Get_availWidth_result) = 0 ;
	virtual HRESULT __safecall Get_fontSmoothingEnabled(System::WordBool &__Get_fontSmoothingEnabled_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_colorDepth() { int __r; HRESULT __hr = Get_colorDepth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int colorDepth = {read=_scw_Get_colorDepth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_bufferDepth() { int __r; HRESULT __hr = Get_bufferDepth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int bufferDepth = {read=_scw_Get_bufferDepth, write=Set_bufferDepth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_width() { int __r; HRESULT __hr = Get_width(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int width = {read=_scw_Get_width};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_height() { int __r; HRESULT __hr = Get_height(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int height = {read=_scw_Get_height};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_updateInterval() { int __r; HRESULT __hr = Get_updateInterval(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int updateInterval = {read=_scw_Get_updateInterval, write=Set_updateInterval};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_availHeight() { int __r; HRESULT __hr = Get_availHeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int availHeight = {read=_scw_Get_availHeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_availWidth() { int __r; HRESULT __hr = Get_availWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int availWidth = {read=_scw_Get_availWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_fontSmoothingEnabled() { System::WordBool __r; HRESULT __hr = Get_fontSmoothingEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool fontSmoothingEnabled = {read=_scw_Get_fontSmoothingEnabled};
};

__interface  INTERFACE_UUID("{332C4427-26CB-11D0-B483-00C04FD90119}") IHTMLWindow2  : public IHTMLFramesCollection2 
{
	virtual HRESULT __safecall Get_frames(_di_IHTMLFramesCollection2 &__Get_frames_result) = 0 ;
	virtual HRESULT __safecall Set_defaultStatus(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_defaultStatus(System::WideString &__Get_defaultStatus_result) = 0 ;
	virtual HRESULT __safecall Set_status(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_status(System::WideString &__Get_status_result) = 0 ;
	virtual HRESULT __safecall setTimeout(const System::WideString expression, int msec, const System::OleVariant &language, int &__setTimeout_result) = 0 ;
	virtual HRESULT __safecall clearTimeout(int timerID) = 0 ;
	virtual HRESULT __safecall alert(const System::WideString message) = 0 ;
	virtual HRESULT __safecall confirm(const System::WideString message, System::WordBool &__confirm_result) = 0 ;
	virtual HRESULT __safecall prompt(const System::WideString message, const System::WideString defstr, System::OleVariant &__prompt_result) = 0 ;
	virtual HRESULT __safecall Get_Image(_di_IHTMLImageElementFactory &__Get_Image_result) = 0 ;
	virtual HRESULT __safecall Get_location(_di_IHTMLLocation &__Get_location_result) = 0 ;
	virtual HRESULT __safecall Get_history(_di_IOmHistory &__Get_history_result) = 0 ;
	virtual HRESULT __safecall close() = 0 ;
	virtual HRESULT __safecall Set_opener(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_opener(System::OleVariant &__Get_opener_result) = 0 ;
	virtual HRESULT __safecall Get_navigator(_di_IOmNavigator &__Get_navigator_result) = 0 ;
	virtual HRESULT __safecall Set_name(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_name(System::WideString &__Get_name_result) = 0 ;
	virtual HRESULT __safecall Get_parent(_di_IHTMLWindow2 &__Get_parent_result) = 0 ;
	virtual HRESULT __safecall open(const System::WideString url, const System::WideString name, const System::WideString features, System::WordBool replace, _di_IHTMLWindow2 &__open_result) = 0 ;
	virtual HRESULT __safecall Get_self(_di_IHTMLWindow2 &__Get_self_result) = 0 ;
	virtual HRESULT __safecall Get_top(_di_IHTMLWindow2 &__Get_top_result) = 0 ;
	virtual HRESULT __safecall Get_window(_di_IHTMLWindow2 &__Get_window_result) = 0 ;
	virtual HRESULT __safecall navigate(const System::WideString url) = 0 ;
	virtual HRESULT __safecall Set_onfocus(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onfocus(System::OleVariant &__Get_onfocus_result) = 0 ;
	virtual HRESULT __safecall Set_onblur(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onblur(System::OleVariant &__Get_onblur_result) = 0 ;
	virtual HRESULT __safecall Set_onload(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onload(System::OleVariant &__Get_onload_result) = 0 ;
	virtual HRESULT __safecall Set_onbeforeunload(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onbeforeunload(System::OleVariant &__Get_onbeforeunload_result) = 0 ;
	virtual HRESULT __safecall Set_onunload(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onunload(System::OleVariant &__Get_onunload_result) = 0 ;
	virtual HRESULT __safecall Set_onhelp(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onhelp(System::OleVariant &__Get_onhelp_result) = 0 ;
	virtual HRESULT __safecall Set_onerror(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onerror(System::OleVariant &__Get_onerror_result) = 0 ;
	virtual HRESULT __safecall Set_onresize(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onresize(System::OleVariant &__Get_onresize_result) = 0 ;
	virtual HRESULT __safecall Set_onscroll(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onscroll(System::OleVariant &__Get_onscroll_result) = 0 ;
	virtual HRESULT __safecall Get_document(_di_IHTMLDocument2 &__Get_document_result) = 0 ;
	virtual HRESULT __safecall Get_event(_di_IHTMLEventObj &__Get_event_result) = 0 ;
	virtual HRESULT __safecall Get__newEnum(System::_di_IInterface &__Get__newEnum_result) = 0 ;
	virtual HRESULT __safecall showModalDialog(const System::WideString dialog, const System::OleVariant &varArgIn, const System::OleVariant &varOptions, System::OleVariant &__showModalDialog_result) = 0 ;
	virtual HRESULT __safecall showHelp(const System::WideString helpURL, System::OleVariant helpArg, const System::WideString features) = 0 ;
	virtual HRESULT __safecall Get_screen(_di_IHTMLScreen &__Get_screen_result) = 0 ;
	virtual HRESULT __safecall Get_Option(_di_IHTMLOptionElementFactory &__Get_Option_result) = 0 ;
	virtual HRESULT __safecall focus() = 0 ;
	virtual HRESULT __safecall Get_closed(System::WordBool &__Get_closed_result) = 0 ;
	virtual HRESULT __safecall blur() = 0 ;
	virtual HRESULT __safecall scroll(int x, int y) = 0 ;
	virtual HRESULT __safecall Get_clientInformation(_di_IOmNavigator &__Get_clientInformation_result) = 0 ;
	virtual HRESULT __safecall setInterval(const System::WideString expression, int msec, const System::OleVariant &language, int &__setInterval_result) = 0 ;
	virtual HRESULT __safecall clearInterval(int timerID) = 0 ;
	virtual HRESULT __safecall Set_offscreenBuffering(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_offscreenBuffering(System::OleVariant &__Get_offscreenBuffering_result) = 0 ;
	virtual HRESULT __safecall execScript(const System::WideString code, const System::WideString language, System::OleVariant &__execScript_result) = 0 ;
	virtual HRESULT __safecall toString(System::WideString &__toString_result) = 0 ;
	virtual HRESULT __safecall scrollBy(int x, int y) = 0 ;
	virtual HRESULT __safecall scrollTo(int x, int y) = 0 ;
	virtual HRESULT __safecall moveTo(int x, int y) = 0 ;
	virtual HRESULT __safecall moveBy(int x, int y) = 0 ;
	virtual HRESULT __safecall resizeTo(int x, int y) = 0 ;
	virtual HRESULT __safecall resizeBy(int x, int y) = 0 ;
	virtual HRESULT __safecall Get_external(_di_IDispatch &__Get_external_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLFramesCollection2 _scw_Get_frames() { _di_IHTMLFramesCollection2 __r; HRESULT __hr = Get_frames(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLFramesCollection2 frames = {read=_scw_Get_frames};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_defaultStatus() { System::WideString __r; HRESULT __hr = Get_defaultStatus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString defaultStatus = {read=_scw_Get_defaultStatus, write=Set_defaultStatus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_status() { System::WideString __r; HRESULT __hr = Get_status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString status = {read=_scw_Get_status, write=Set_status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLImageElementFactory _scw_Get_Image() { _di_IHTMLImageElementFactory __r; HRESULT __hr = Get_Image(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLImageElementFactory Image = {read=_scw_Get_Image};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLLocation _scw_Get_location() { _di_IHTMLLocation __r; HRESULT __hr = Get_location(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLLocation location = {read=_scw_Get_location};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IOmHistory _scw_Get_history() { _di_IOmHistory __r; HRESULT __hr = Get_history(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IOmHistory history = {read=_scw_Get_history};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_opener() { System::OleVariant __r; HRESULT __hr = Get_opener(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant opener = {read=_scw_Get_opener, write=Set_opener};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IOmNavigator _scw_Get_navigator() { _di_IOmNavigator __r; HRESULT __hr = Get_navigator(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IOmNavigator navigator = {read=_scw_Get_navigator};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_name() { System::WideString __r; HRESULT __hr = Get_name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString name = {read=_scw_Get_name, write=Set_name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLWindow2 _scw_Get_parent() { _di_IHTMLWindow2 __r; HRESULT __hr = Get_parent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLWindow2 parent = {read=_scw_Get_parent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLWindow2 _scw_Get_self() { _di_IHTMLWindow2 __r; HRESULT __hr = Get_self(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLWindow2 self = {read=_scw_Get_self};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLWindow2 _scw_Get_top() { _di_IHTMLWindow2 __r; HRESULT __hr = Get_top(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLWindow2 top = {read=_scw_Get_top};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLWindow2 _scw_Get_window() { _di_IHTMLWindow2 __r; HRESULT __hr = Get_window(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLWindow2 window = {read=_scw_Get_window};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onfocus() { System::OleVariant __r; HRESULT __hr = Get_onfocus(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onfocus = {read=_scw_Get_onfocus, write=Set_onfocus};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onblur() { System::OleVariant __r; HRESULT __hr = Get_onblur(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onblur = {read=_scw_Get_onblur, write=Set_onblur};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onload() { System::OleVariant __r; HRESULT __hr = Get_onload(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onload = {read=_scw_Get_onload, write=Set_onload};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onbeforeunload() { System::OleVariant __r; HRESULT __hr = Get_onbeforeunload(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onbeforeunload = {read=_scw_Get_onbeforeunload, write=Set_onbeforeunload};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onunload() { System::OleVariant __r; HRESULT __hr = Get_onunload(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onunload = {read=_scw_Get_onunload, write=Set_onunload};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onhelp() { System::OleVariant __r; HRESULT __hr = Get_onhelp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onhelp = {read=_scw_Get_onhelp, write=Set_onhelp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onerror() { System::OleVariant __r; HRESULT __hr = Get_onerror(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onerror = {read=_scw_Get_onerror, write=Set_onerror};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onresize() { System::OleVariant __r; HRESULT __hr = Get_onresize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onresize = {read=_scw_Get_onresize, write=Set_onresize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onscroll() { System::OleVariant __r; HRESULT __hr = Get_onscroll(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onscroll = {read=_scw_Get_onscroll, write=Set_onscroll};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLDocument2 _scw_Get_document() { _di_IHTMLDocument2 __r; HRESULT __hr = Get_document(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLDocument2 document = {read=_scw_Get_document};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLEventObj _scw_Get_event() { _di_IHTMLEventObj __r; HRESULT __hr = Get_event(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLEventObj event = {read=_scw_Get_event};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__newEnum() { System::_di_IInterface __r; HRESULT __hr = Get__newEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _newEnum = {read=_scw_Get__newEnum};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLScreen _scw_Get_screen() { _di_IHTMLScreen __r; HRESULT __hr = Get_screen(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLScreen screen = {read=_scw_Get_screen};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLOptionElementFactory _scw_Get_Option() { _di_IHTMLOptionElementFactory __r; HRESULT __hr = Get_Option(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLOptionElementFactory Option = {read=_scw_Get_Option};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_closed() { System::WordBool __r; HRESULT __hr = Get_closed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool closed = {read=_scw_Get_closed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IOmNavigator _scw_Get_clientInformation() { _di_IOmNavigator __r; HRESULT __hr = Get_clientInformation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IOmNavigator clientInformation = {read=_scw_Get_clientInformation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_offscreenBuffering() { System::OleVariant __r; HRESULT __hr = Get_offscreenBuffering(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant offscreenBuffering = {read=_scw_Get_offscreenBuffering, write=Set_offscreenBuffering};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_external() { _di_IDispatch __r; HRESULT __hr = Get_external(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch external = {read=_scw_Get_external};
};

__interface  INTERFACE_UUID("{3050F25A-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLSelectionObject  : public IDispatch 
{
	virtual HRESULT __safecall createRange(_di_IDispatch &__createRange_result) = 0 ;
	virtual HRESULT __safecall empty() = 0 ;
	virtual HRESULT __safecall clear() = 0 ;
	virtual HRESULT __safecall Get_type_(System::WideString &__Get_type__result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_type_() { System::WideString __r; HRESULT __hr = Get_type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString type_ = {read=_scw_Get_type_};
};

__interface  INTERFACE_UUID("{3050F37E-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLStyleSheetsCollection  : public IDispatch 
{
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	virtual HRESULT __safecall Get__newEnum(System::_di_IInterface &__Get__newEnum_result) = 0 ;
	virtual HRESULT __safecall item(const System::OleVariant &pvarIndex, System::OleVariant &__item_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get__newEnum() { System::_di_IInterface __r; HRESULT __hr = Get__newEnum(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface _newEnum = {read=_scw_Get__newEnum};
};

__interface  INTERFACE_UUID("{3050F3CF-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLRuleStyle  : public IDispatch 
{
	virtual HRESULT __safecall Set_fontFamily(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_fontFamily(System::WideString &__Get_fontFamily_result) = 0 ;
	virtual HRESULT __safecall Set_fontStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_fontStyle(System::WideString &__Get_fontStyle_result) = 0 ;
	virtual HRESULT __safecall Set_fontVariant(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_fontVariant(System::WideString &__Get_fontVariant_result) = 0 ;
	virtual HRESULT __safecall Set_fontWeight(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_fontWeight(System::WideString &__Get_fontWeight_result) = 0 ;
	virtual HRESULT __safecall Set_fontSize(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_fontSize(System::OleVariant &__Get_fontSize_result) = 0 ;
	virtual HRESULT __safecall Set_font(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_font(System::WideString &__Get_font_result) = 0 ;
	virtual HRESULT __safecall Set_color(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_color(System::OleVariant &__Get_color_result) = 0 ;
	virtual HRESULT __safecall Set_background(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_background(System::WideString &__Get_background_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_backgroundColor(System::OleVariant &__Get_backgroundColor_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundImage(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_backgroundImage(System::WideString &__Get_backgroundImage_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundRepeat(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_backgroundRepeat(System::WideString &__Get_backgroundRepeat_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundAttachment(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_backgroundAttachment(System::WideString &__Get_backgroundAttachment_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundPosition(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_backgroundPosition(System::WideString &__Get_backgroundPosition_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundPositionX(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_backgroundPositionX(System::OleVariant &__Get_backgroundPositionX_result) = 0 ;
	virtual HRESULT __safecall Set_backgroundPositionY(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_backgroundPositionY(System::OleVariant &__Get_backgroundPositionY_result) = 0 ;
	virtual HRESULT __safecall Set_wordSpacing(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_wordSpacing(System::OleVariant &__Get_wordSpacing_result) = 0 ;
	virtual HRESULT __safecall Set_letterSpacing(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_letterSpacing(System::OleVariant &__Get_letterSpacing_result) = 0 ;
	virtual HRESULT __safecall Set_textDecoration(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_textDecoration(System::WideString &__Get_textDecoration_result) = 0 ;
	virtual HRESULT __safecall Set_textDecorationNone(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_textDecorationNone(System::WordBool &__Get_textDecorationNone_result) = 0 ;
	virtual HRESULT __safecall Set_textDecorationUnderline(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_textDecorationUnderline(System::WordBool &__Get_textDecorationUnderline_result) = 0 ;
	virtual HRESULT __safecall Set_textDecorationOverline(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_textDecorationOverline(System::WordBool &__Get_textDecorationOverline_result) = 0 ;
	virtual HRESULT __safecall Set_textDecorationLineThrough(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_textDecorationLineThrough(System::WordBool &__Get_textDecorationLineThrough_result) = 0 ;
	virtual HRESULT __safecall Set_textDecorationBlink(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_textDecorationBlink(System::WordBool &__Get_textDecorationBlink_result) = 0 ;
	virtual HRESULT __safecall Set_verticalAlign(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_verticalAlign(System::OleVariant &__Get_verticalAlign_result) = 0 ;
	virtual HRESULT __safecall Set_textTransform(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_textTransform(System::WideString &__Get_textTransform_result) = 0 ;
	virtual HRESULT __safecall Set_textAlign(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_textAlign(System::WideString &__Get_textAlign_result) = 0 ;
	virtual HRESULT __safecall Set_textIndent(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_textIndent(System::OleVariant &__Get_textIndent_result) = 0 ;
	virtual HRESULT __safecall Set_lineHeight(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_lineHeight(System::OleVariant &__Get_lineHeight_result) = 0 ;
	virtual HRESULT __safecall Set_marginTop(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_marginTop(System::OleVariant &__Get_marginTop_result) = 0 ;
	virtual HRESULT __safecall Set_marginRight(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_marginRight(System::OleVariant &__Get_marginRight_result) = 0 ;
	virtual HRESULT __safecall Set_marginBottom(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_marginBottom(System::OleVariant &__Get_marginBottom_result) = 0 ;
	virtual HRESULT __safecall Set_marginLeft(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_marginLeft(System::OleVariant &__Get_marginLeft_result) = 0 ;
	virtual HRESULT __safecall Set_margin(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_margin(System::WideString &__Get_margin_result) = 0 ;
	virtual HRESULT __safecall Set_paddingTop(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_paddingTop(System::OleVariant &__Get_paddingTop_result) = 0 ;
	virtual HRESULT __safecall Set_paddingRight(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_paddingRight(System::OleVariant &__Get_paddingRight_result) = 0 ;
	virtual HRESULT __safecall Set_paddingBottom(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_paddingBottom(System::OleVariant &__Get_paddingBottom_result) = 0 ;
	virtual HRESULT __safecall Set_paddingLeft(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_paddingLeft(System::OleVariant &__Get_paddingLeft_result) = 0 ;
	virtual HRESULT __safecall Set_padding(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_padding(System::WideString &__Get_padding_result) = 0 ;
	virtual HRESULT __safecall Set_border(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_border(System::WideString &__Get_border_result) = 0 ;
	virtual HRESULT __safecall Set_borderTop(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderTop(System::WideString &__Get_borderTop_result) = 0 ;
	virtual HRESULT __safecall Set_borderRight(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderRight(System::WideString &__Get_borderRight_result) = 0 ;
	virtual HRESULT __safecall Set_borderBottom(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderBottom(System::WideString &__Get_borderBottom_result) = 0 ;
	virtual HRESULT __safecall Set_borderLeft(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderLeft(System::WideString &__Get_borderLeft_result) = 0 ;
	virtual HRESULT __safecall Set_borderColor(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderColor(System::WideString &__Get_borderColor_result) = 0 ;
	virtual HRESULT __safecall Set_borderTopColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderTopColor(System::OleVariant &__Get_borderTopColor_result) = 0 ;
	virtual HRESULT __safecall Set_borderRightColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderRightColor(System::OleVariant &__Get_borderRightColor_result) = 0 ;
	virtual HRESULT __safecall Set_borderBottomColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderBottomColor(System::OleVariant &__Get_borderBottomColor_result) = 0 ;
	virtual HRESULT __safecall Set_borderLeftColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderLeftColor(System::OleVariant &__Get_borderLeftColor_result) = 0 ;
	virtual HRESULT __safecall Set_borderWidth(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderWidth(System::WideString &__Get_borderWidth_result) = 0 ;
	virtual HRESULT __safecall Set_borderTopWidth(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderTopWidth(System::OleVariant &__Get_borderTopWidth_result) = 0 ;
	virtual HRESULT __safecall Set_borderRightWidth(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderRightWidth(System::OleVariant &__Get_borderRightWidth_result) = 0 ;
	virtual HRESULT __safecall Set_borderBottomWidth(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderBottomWidth(System::OleVariant &__Get_borderBottomWidth_result) = 0 ;
	virtual HRESULT __safecall Set_borderLeftWidth(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_borderLeftWidth(System::OleVariant &__Get_borderLeftWidth_result) = 0 ;
	virtual HRESULT __safecall Set_borderStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderStyle(System::WideString &__Get_borderStyle_result) = 0 ;
	virtual HRESULT __safecall Set_borderTopStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderTopStyle(System::WideString &__Get_borderTopStyle_result) = 0 ;
	virtual HRESULT __safecall Set_borderRightStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderRightStyle(System::WideString &__Get_borderRightStyle_result) = 0 ;
	virtual HRESULT __safecall Set_borderBottomStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderBottomStyle(System::WideString &__Get_borderBottomStyle_result) = 0 ;
	virtual HRESULT __safecall Set_borderLeftStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_borderLeftStyle(System::WideString &__Get_borderLeftStyle_result) = 0 ;
	virtual HRESULT __safecall Set_width(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_width(System::OleVariant &__Get_width_result) = 0 ;
	virtual HRESULT __safecall Set_height(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_height(System::OleVariant &__Get_height_result) = 0 ;
	virtual HRESULT __safecall Set_styleFloat(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_styleFloat(System::WideString &__Get_styleFloat_result) = 0 ;
	virtual HRESULT __safecall Set_clear(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_clear(System::WideString &__Get_clear_result) = 0 ;
	virtual HRESULT __safecall Set_display(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_display(System::WideString &__Get_display_result) = 0 ;
	virtual HRESULT __safecall Set_visibility(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_visibility(System::WideString &__Get_visibility_result) = 0 ;
	virtual HRESULT __safecall Set_listStyleType(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_listStyleType(System::WideString &__Get_listStyleType_result) = 0 ;
	virtual HRESULT __safecall Set_listStylePosition(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_listStylePosition(System::WideString &__Get_listStylePosition_result) = 0 ;
	virtual HRESULT __safecall Set_listStyleImage(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_listStyleImage(System::WideString &__Get_listStyleImage_result) = 0 ;
	virtual HRESULT __safecall Set_listStyle(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_listStyle(System::WideString &__Get_listStyle_result) = 0 ;
	virtual HRESULT __safecall Set_whiteSpace(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_whiteSpace(System::WideString &__Get_whiteSpace_result) = 0 ;
	virtual HRESULT __safecall Set_top(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_top(System::OleVariant &__Get_top_result) = 0 ;
	virtual HRESULT __safecall Set_left(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_left(System::OleVariant &__Get_left_result) = 0 ;
	virtual HRESULT __safecall Get_position(System::WideString &__Get_position_result) = 0 ;
	virtual HRESULT __safecall Set_zIndex(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_zIndex(System::OleVariant &__Get_zIndex_result) = 0 ;
	virtual HRESULT __safecall Set_overflow(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_overflow(System::WideString &__Get_overflow_result) = 0 ;
	virtual HRESULT __safecall Set_pageBreakBefore(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_pageBreakBefore(System::WideString &__Get_pageBreakBefore_result) = 0 ;
	virtual HRESULT __safecall Set_pageBreakAfter(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_pageBreakAfter(System::WideString &__Get_pageBreakAfter_result) = 0 ;
	virtual HRESULT __safecall Set_cssText(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_cssText(System::WideString &__Get_cssText_result) = 0 ;
	virtual HRESULT __safecall Set_cursor(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_cursor(System::WideString &__Get_cursor_result) = 0 ;
	virtual HRESULT __safecall Set_clip(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_clip(System::WideString &__Get_clip_result) = 0 ;
	virtual HRESULT __safecall Set_filter(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_filter(System::WideString &__Get_filter_result) = 0 ;
	virtual HRESULT __safecall setAttribute(const System::WideString strAttributeName, System::OleVariant AttributeValue, int lFlags) = 0 ;
	virtual HRESULT __safecall getAttribute(const System::WideString strAttributeName, int lFlags, System::OleVariant &__getAttribute_result) = 0 ;
	virtual HRESULT __safecall removeAttribute(const System::WideString strAttributeName, int lFlags, System::WordBool &__removeAttribute_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fontFamily() { System::WideString __r; HRESULT __hr = Get_fontFamily(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fontFamily = {read=_scw_Get_fontFamily, write=Set_fontFamily};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fontStyle() { System::WideString __r; HRESULT __hr = Get_fontStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fontStyle = {read=_scw_Get_fontStyle, write=Set_fontStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fontVariant() { System::WideString __r; HRESULT __hr = Get_fontVariant(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fontVariant = {read=_scw_Get_fontVariant, write=Set_fontVariant};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fontWeight() { System::WideString __r; HRESULT __hr = Get_fontWeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fontWeight = {read=_scw_Get_fontWeight, write=Set_fontWeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_fontSize() { System::OleVariant __r; HRESULT __hr = Get_fontSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant fontSize = {read=_scw_Get_fontSize, write=Set_fontSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_font() { System::WideString __r; HRESULT __hr = Get_font(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString font = {read=_scw_Get_font, write=Set_font};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_color() { System::OleVariant __r; HRESULT __hr = Get_color(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant color = {read=_scw_Get_color, write=Set_color};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_background() { System::WideString __r; HRESULT __hr = Get_background(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString background = {read=_scw_Get_background, write=Set_background};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_backgroundColor() { System::OleVariant __r; HRESULT __hr = Get_backgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant backgroundColor = {read=_scw_Get_backgroundColor, write=Set_backgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_backgroundImage() { System::WideString __r; HRESULT __hr = Get_backgroundImage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString backgroundImage = {read=_scw_Get_backgroundImage, write=Set_backgroundImage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_backgroundRepeat() { System::WideString __r; HRESULT __hr = Get_backgroundRepeat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString backgroundRepeat = {read=_scw_Get_backgroundRepeat, write=Set_backgroundRepeat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_backgroundAttachment() { System::WideString __r; HRESULT __hr = Get_backgroundAttachment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString backgroundAttachment = {read=_scw_Get_backgroundAttachment, write=Set_backgroundAttachment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_backgroundPosition() { System::WideString __r; HRESULT __hr = Get_backgroundPosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString backgroundPosition = {read=_scw_Get_backgroundPosition, write=Set_backgroundPosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_backgroundPositionX() { System::OleVariant __r; HRESULT __hr = Get_backgroundPositionX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant backgroundPositionX = {read=_scw_Get_backgroundPositionX, write=Set_backgroundPositionX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_backgroundPositionY() { System::OleVariant __r; HRESULT __hr = Get_backgroundPositionY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant backgroundPositionY = {read=_scw_Get_backgroundPositionY, write=Set_backgroundPositionY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_wordSpacing() { System::OleVariant __r; HRESULT __hr = Get_wordSpacing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant wordSpacing = {read=_scw_Get_wordSpacing, write=Set_wordSpacing};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_letterSpacing() { System::OleVariant __r; HRESULT __hr = Get_letterSpacing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant letterSpacing = {read=_scw_Get_letterSpacing, write=Set_letterSpacing};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_textDecoration() { System::WideString __r; HRESULT __hr = Get_textDecoration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString textDecoration = {read=_scw_Get_textDecoration, write=Set_textDecoration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_textDecorationNone() { System::WordBool __r; HRESULT __hr = Get_textDecorationNone(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool textDecorationNone = {read=_scw_Get_textDecorationNone, write=Set_textDecorationNone};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_textDecorationUnderline() { System::WordBool __r; HRESULT __hr = Get_textDecorationUnderline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool textDecorationUnderline = {read=_scw_Get_textDecorationUnderline, write=Set_textDecorationUnderline};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_textDecorationOverline() { System::WordBool __r; HRESULT __hr = Get_textDecorationOverline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool textDecorationOverline = {read=_scw_Get_textDecorationOverline, write=Set_textDecorationOverline};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_textDecorationLineThrough() { System::WordBool __r; HRESULT __hr = Get_textDecorationLineThrough(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool textDecorationLineThrough = {read=_scw_Get_textDecorationLineThrough, write=Set_textDecorationLineThrough};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_textDecorationBlink() { System::WordBool __r; HRESULT __hr = Get_textDecorationBlink(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool textDecorationBlink = {read=_scw_Get_textDecorationBlink, write=Set_textDecorationBlink};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_verticalAlign() { System::OleVariant __r; HRESULT __hr = Get_verticalAlign(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant verticalAlign = {read=_scw_Get_verticalAlign, write=Set_verticalAlign};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_textTransform() { System::WideString __r; HRESULT __hr = Get_textTransform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString textTransform = {read=_scw_Get_textTransform, write=Set_textTransform};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_textAlign() { System::WideString __r; HRESULT __hr = Get_textAlign(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString textAlign = {read=_scw_Get_textAlign, write=Set_textAlign};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_textIndent() { System::OleVariant __r; HRESULT __hr = Get_textIndent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant textIndent = {read=_scw_Get_textIndent, write=Set_textIndent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_lineHeight() { System::OleVariant __r; HRESULT __hr = Get_lineHeight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant lineHeight = {read=_scw_Get_lineHeight, write=Set_lineHeight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_marginTop() { System::OleVariant __r; HRESULT __hr = Get_marginTop(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant marginTop = {read=_scw_Get_marginTop, write=Set_marginTop};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_marginRight() { System::OleVariant __r; HRESULT __hr = Get_marginRight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant marginRight = {read=_scw_Get_marginRight, write=Set_marginRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_marginBottom() { System::OleVariant __r; HRESULT __hr = Get_marginBottom(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant marginBottom = {read=_scw_Get_marginBottom, write=Set_marginBottom};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_marginLeft() { System::OleVariant __r; HRESULT __hr = Get_marginLeft(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant marginLeft = {read=_scw_Get_marginLeft, write=Set_marginLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_margin() { System::WideString __r; HRESULT __hr = Get_margin(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString margin = {read=_scw_Get_margin, write=Set_margin};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_paddingTop() { System::OleVariant __r; HRESULT __hr = Get_paddingTop(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant paddingTop = {read=_scw_Get_paddingTop, write=Set_paddingTop};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_paddingRight() { System::OleVariant __r; HRESULT __hr = Get_paddingRight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant paddingRight = {read=_scw_Get_paddingRight, write=Set_paddingRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_paddingBottom() { System::OleVariant __r; HRESULT __hr = Get_paddingBottom(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant paddingBottom = {read=_scw_Get_paddingBottom, write=Set_paddingBottom};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_paddingLeft() { System::OleVariant __r; HRESULT __hr = Get_paddingLeft(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant paddingLeft = {read=_scw_Get_paddingLeft, write=Set_paddingLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_padding() { System::WideString __r; HRESULT __hr = Get_padding(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString padding = {read=_scw_Get_padding, write=Set_padding};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_border() { System::WideString __r; HRESULT __hr = Get_border(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString border = {read=_scw_Get_border, write=Set_border};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderTop() { System::WideString __r; HRESULT __hr = Get_borderTop(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderTop = {read=_scw_Get_borderTop, write=Set_borderTop};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderRight() { System::WideString __r; HRESULT __hr = Get_borderRight(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderRight = {read=_scw_Get_borderRight, write=Set_borderRight};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderBottom() { System::WideString __r; HRESULT __hr = Get_borderBottom(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderBottom = {read=_scw_Get_borderBottom, write=Set_borderBottom};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderLeft() { System::WideString __r; HRESULT __hr = Get_borderLeft(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderLeft = {read=_scw_Get_borderLeft, write=Set_borderLeft};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderColor() { System::WideString __r; HRESULT __hr = Get_borderColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderColor = {read=_scw_Get_borderColor, write=Set_borderColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderTopColor() { System::OleVariant __r; HRESULT __hr = Get_borderTopColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderTopColor = {read=_scw_Get_borderTopColor, write=Set_borderTopColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderRightColor() { System::OleVariant __r; HRESULT __hr = Get_borderRightColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderRightColor = {read=_scw_Get_borderRightColor, write=Set_borderRightColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderBottomColor() { System::OleVariant __r; HRESULT __hr = Get_borderBottomColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderBottomColor = {read=_scw_Get_borderBottomColor, write=Set_borderBottomColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderLeftColor() { System::OleVariant __r; HRESULT __hr = Get_borderLeftColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderLeftColor = {read=_scw_Get_borderLeftColor, write=Set_borderLeftColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderWidth() { System::WideString __r; HRESULT __hr = Get_borderWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderWidth = {read=_scw_Get_borderWidth, write=Set_borderWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderTopWidth() { System::OleVariant __r; HRESULT __hr = Get_borderTopWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderTopWidth = {read=_scw_Get_borderTopWidth, write=Set_borderTopWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderRightWidth() { System::OleVariant __r; HRESULT __hr = Get_borderRightWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderRightWidth = {read=_scw_Get_borderRightWidth, write=Set_borderRightWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderBottomWidth() { System::OleVariant __r; HRESULT __hr = Get_borderBottomWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderBottomWidth = {read=_scw_Get_borderBottomWidth, write=Set_borderBottomWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_borderLeftWidth() { System::OleVariant __r; HRESULT __hr = Get_borderLeftWidth(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant borderLeftWidth = {read=_scw_Get_borderLeftWidth, write=Set_borderLeftWidth};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderStyle() { System::WideString __r; HRESULT __hr = Get_borderStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderStyle = {read=_scw_Get_borderStyle, write=Set_borderStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderTopStyle() { System::WideString __r; HRESULT __hr = Get_borderTopStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderTopStyle = {read=_scw_Get_borderTopStyle, write=Set_borderTopStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderRightStyle() { System::WideString __r; HRESULT __hr = Get_borderRightStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderRightStyle = {read=_scw_Get_borderRightStyle, write=Set_borderRightStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderBottomStyle() { System::WideString __r; HRESULT __hr = Get_borderBottomStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderBottomStyle = {read=_scw_Get_borderBottomStyle, write=Set_borderBottomStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_borderLeftStyle() { System::WideString __r; HRESULT __hr = Get_borderLeftStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString borderLeftStyle = {read=_scw_Get_borderLeftStyle, write=Set_borderLeftStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_width() { System::OleVariant __r; HRESULT __hr = Get_width(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant width = {read=_scw_Get_width, write=Set_width};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_height() { System::OleVariant __r; HRESULT __hr = Get_height(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant height = {read=_scw_Get_height, write=Set_height};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_styleFloat() { System::WideString __r; HRESULT __hr = Get_styleFloat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString styleFloat = {read=_scw_Get_styleFloat, write=Set_styleFloat};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_clear() { System::WideString __r; HRESULT __hr = Get_clear(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString clear = {read=_scw_Get_clear, write=Set_clear};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_display() { System::WideString __r; HRESULT __hr = Get_display(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString display = {read=_scw_Get_display, write=Set_display};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_visibility() { System::WideString __r; HRESULT __hr = Get_visibility(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString visibility = {read=_scw_Get_visibility, write=Set_visibility};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_listStyleType() { System::WideString __r; HRESULT __hr = Get_listStyleType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString listStyleType = {read=_scw_Get_listStyleType, write=Set_listStyleType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_listStylePosition() { System::WideString __r; HRESULT __hr = Get_listStylePosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString listStylePosition = {read=_scw_Get_listStylePosition, write=Set_listStylePosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_listStyleImage() { System::WideString __r; HRESULT __hr = Get_listStyleImage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString listStyleImage = {read=_scw_Get_listStyleImage, write=Set_listStyleImage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_listStyle() { System::WideString __r; HRESULT __hr = Get_listStyle(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString listStyle = {read=_scw_Get_listStyle, write=Set_listStyle};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_whiteSpace() { System::WideString __r; HRESULT __hr = Get_whiteSpace(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString whiteSpace = {read=_scw_Get_whiteSpace, write=Set_whiteSpace};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_top() { System::OleVariant __r; HRESULT __hr = Get_top(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant top = {read=_scw_Get_top, write=Set_top};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_left() { System::OleVariant __r; HRESULT __hr = Get_left(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant left = {read=_scw_Get_left, write=Set_left};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_position() { System::WideString __r; HRESULT __hr = Get_position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString position = {read=_scw_Get_position};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_zIndex() { System::OleVariant __r; HRESULT __hr = Get_zIndex(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant zIndex = {read=_scw_Get_zIndex, write=Set_zIndex};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_overflow() { System::WideString __r; HRESULT __hr = Get_overflow(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString overflow = {read=_scw_Get_overflow, write=Set_overflow};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_pageBreakBefore() { System::WideString __r; HRESULT __hr = Get_pageBreakBefore(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString pageBreakBefore = {read=_scw_Get_pageBreakBefore, write=Set_pageBreakBefore};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_pageBreakAfter() { System::WideString __r; HRESULT __hr = Get_pageBreakAfter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString pageBreakAfter = {read=_scw_Get_pageBreakAfter, write=Set_pageBreakAfter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_cssText() { System::WideString __r; HRESULT __hr = Get_cssText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString cssText = {read=_scw_Get_cssText, write=Set_cssText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_cursor() { System::WideString __r; HRESULT __hr = Get_cursor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString cursor = {read=_scw_Get_cursor, write=Set_cursor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_clip() { System::WideString __r; HRESULT __hr = Get_clip(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString clip = {read=_scw_Get_clip, write=Set_clip};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_filter() { System::WideString __r; HRESULT __hr = Get_filter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString filter = {read=_scw_Get_filter, write=Set_filter};
};

__interface  INTERFACE_UUID("{3050F357-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLStyleSheetRule  : public IDispatch 
{
	virtual HRESULT __safecall Set_selectorText(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_selectorText(System::WideString &__Get_selectorText_result) = 0 ;
	virtual HRESULT __safecall Get_style(_di_IHTMLRuleStyle &__Get_style_result) = 0 ;
	virtual HRESULT __safecall Get_readOnly(System::WordBool &__Get_readOnly_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_selectorText() { System::WideString __r; HRESULT __hr = Get_selectorText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString selectorText = {read=_scw_Get_selectorText, write=Set_selectorText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLRuleStyle _scw_Get_style() { _di_IHTMLRuleStyle __r; HRESULT __hr = Get_style(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLRuleStyle style = {read=_scw_Get_style};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_readOnly() { System::WordBool __r; HRESULT __hr = Get_readOnly(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool readOnly = {read=_scw_Get_readOnly};
};

__interface  INTERFACE_UUID("{3050F2E5-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLStyleSheetRulesCollection  : public IDispatch 
{
	virtual HRESULT __safecall Get_length(int &__Get_length_result) = 0 ;
	virtual HRESULT __safecall item(int index, _di_IHTMLStyleSheetRule &__item_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_length() { int __r; HRESULT __hr = Get_length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int length = {read=_scw_Get_length};
};

__interface  INTERFACE_UUID("{3050F2E3-98B5-11CF-BB82-00AA00BDCE0B}") IHTMLStyleSheet  : public IDispatch 
{
	virtual HRESULT __safecall Set_title(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_title(System::WideString &__Get_title_result) = 0 ;
	virtual HRESULT __safecall Get_parentStyleSheet(_di_IHTMLStyleSheet &__Get_parentStyleSheet_result) = 0 ;
	virtual HRESULT __safecall Get_owningElement(_di_IHTMLElement &__Get_owningElement_result) = 0 ;
	virtual HRESULT __safecall Set_disabled(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_disabled(System::WordBool &__Get_disabled_result) = 0 ;
	virtual HRESULT __safecall Get_readOnly(System::WordBool &__Get_readOnly_result) = 0 ;
	virtual HRESULT __safecall Get_imports(_di_IHTMLStyleSheetsCollection &__Get_imports_result) = 0 ;
	virtual HRESULT __safecall Set_href(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_href(System::WideString &__Get_href_result) = 0 ;
	virtual HRESULT __safecall Get_type_(System::WideString &__Get_type__result) = 0 ;
	virtual HRESULT __safecall Get_id(System::WideString &__Get_id_result) = 0 ;
	virtual HRESULT __safecall addImport(const System::WideString bstrURL, int lIndex, int &__addImport_result) = 0 ;
	virtual HRESULT __safecall addRule(const System::WideString bstrSelector, const System::WideString bstrStyle, int lIndex, int &__addRule_result) = 0 ;
	virtual HRESULT __safecall removeImport(int lIndex) = 0 ;
	virtual HRESULT __safecall removeRule(int lIndex) = 0 ;
	virtual HRESULT __safecall Set_media(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_media(System::WideString &__Get_media_result) = 0 ;
	virtual HRESULT __safecall Set_cssText(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_cssText(System::WideString &__Get_cssText_result) = 0 ;
	virtual HRESULT __safecall Get_rules(_di_IHTMLStyleSheetRulesCollection &__Get_rules_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_title() { System::WideString __r; HRESULT __hr = Get_title(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString title = {read=_scw_Get_title, write=Set_title};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLStyleSheet _scw_Get_parentStyleSheet() { _di_IHTMLStyleSheet __r; HRESULT __hr = Get_parentStyleSheet(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLStyleSheet parentStyleSheet = {read=_scw_Get_parentStyleSheet};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_owningElement() { _di_IHTMLElement __r; HRESULT __hr = Get_owningElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement owningElement = {read=_scw_Get_owningElement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_disabled() { System::WordBool __r; HRESULT __hr = Get_disabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool disabled = {read=_scw_Get_disabled, write=Set_disabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_readOnly() { System::WordBool __r; HRESULT __hr = Get_readOnly(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool readOnly = {read=_scw_Get_readOnly};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLStyleSheetsCollection _scw_Get_imports() { _di_IHTMLStyleSheetsCollection __r; HRESULT __hr = Get_imports(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLStyleSheetsCollection imports = {read=_scw_Get_imports};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_href() { System::WideString __r; HRESULT __hr = Get_href(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString href = {read=_scw_Get_href, write=Set_href};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_type_() { System::WideString __r; HRESULT __hr = Get_type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString type_ = {read=_scw_Get_type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_id() { System::WideString __r; HRESULT __hr = Get_id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString id = {read=_scw_Get_id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_media() { System::WideString __r; HRESULT __hr = Get_media(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString media = {read=_scw_Get_media, write=Set_media};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_cssText() { System::WideString __r; HRESULT __hr = Get_cssText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString cssText = {read=_scw_Get_cssText, write=Set_cssText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLStyleSheetRulesCollection _scw_Get_rules() { _di_IHTMLStyleSheetRulesCollection __r; HRESULT __hr = Get_rules(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLStyleSheetRulesCollection rules = {read=_scw_Get_rules};
};

__interface  INTERFACE_UUID("{332C4425-26CB-11D0-B483-00C04FD90119}") IHTMLDocument2  : public IHTMLDocument 
{
	virtual HRESULT __safecall Get_all(_di_IHTMLElementCollection &__Get_all_result) = 0 ;
	virtual HRESULT __safecall Get_body(_di_IHTMLElement &__Get_body_result) = 0 ;
	virtual HRESULT __safecall Get_activeElement(_di_IHTMLElement &__Get_activeElement_result) = 0 ;
	virtual HRESULT __safecall Get_images(_di_IHTMLElementCollection &__Get_images_result) = 0 ;
	virtual HRESULT __safecall Get_applets(_di_IHTMLElementCollection &__Get_applets_result) = 0 ;
	virtual HRESULT __safecall Get_links(_di_IHTMLElementCollection &__Get_links_result) = 0 ;
	virtual HRESULT __safecall Get_forms(_di_IHTMLElementCollection &__Get_forms_result) = 0 ;
	virtual HRESULT __safecall Get_anchors(_di_IHTMLElementCollection &__Get_anchors_result) = 0 ;
	virtual HRESULT __safecall Set_title(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_title(System::WideString &__Get_title_result) = 0 ;
	virtual HRESULT __safecall Get_scripts(_di_IHTMLElementCollection &__Get_scripts_result) = 0 ;
	virtual HRESULT __safecall Set_designMode(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_designMode(System::WideString &__Get_designMode_result) = 0 ;
	virtual HRESULT __safecall Get_selection(_di_IHTMLSelectionObject &__Get_selection_result) = 0 ;
	virtual HRESULT __safecall Get_readyState(System::WideString &__Get_readyState_result) = 0 ;
	virtual HRESULT __safecall Get_frames(_di_IHTMLFramesCollection2 &__Get_frames_result) = 0 ;
	virtual HRESULT __safecall Get_embeds(_di_IHTMLElementCollection &__Get_embeds_result) = 0 ;
	virtual HRESULT __safecall Get_plugins(_di_IHTMLElementCollection &__Get_plugins_result) = 0 ;
	virtual HRESULT __safecall Set_alinkColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_alinkColor(System::OleVariant &__Get_alinkColor_result) = 0 ;
	virtual HRESULT __safecall Set_bgColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_bgColor(System::OleVariant &__Get_bgColor_result) = 0 ;
	virtual HRESULT __safecall Set_fgColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_fgColor(System::OleVariant &__Get_fgColor_result) = 0 ;
	virtual HRESULT __safecall Set_linkColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_linkColor(System::OleVariant &__Get_linkColor_result) = 0 ;
	virtual HRESULT __safecall Set_vlinkColor(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_vlinkColor(System::OleVariant &__Get_vlinkColor_result) = 0 ;
	virtual HRESULT __safecall Get_referrer(System::WideString &__Get_referrer_result) = 0 ;
	virtual HRESULT __safecall Get_location(_di_IHTMLLocation &__Get_location_result) = 0 ;
	virtual HRESULT __safecall Get_lastModified(System::WideString &__Get_lastModified_result) = 0 ;
	virtual HRESULT __safecall Set_url(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_url(System::WideString &__Get_url_result) = 0 ;
	virtual HRESULT __safecall Set_domain(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_domain(System::WideString &__Get_domain_result) = 0 ;
	virtual HRESULT __safecall Set_cookie(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_cookie(System::WideString &__Get_cookie_result) = 0 ;
	virtual HRESULT __safecall Set_expando(System::WordBool p) = 0 ;
	virtual HRESULT __safecall Get_expando(System::WordBool &__Get_expando_result) = 0 ;
	virtual HRESULT __safecall Set_charset(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_charset(System::WideString &__Get_charset_result) = 0 ;
	virtual HRESULT __safecall Set_defaultCharset(const System::WideString p) = 0 ;
	virtual HRESULT __safecall Get_defaultCharset(System::WideString &__Get_defaultCharset_result) = 0 ;
	virtual HRESULT __safecall Get_mimeType(System::WideString &__Get_mimeType_result) = 0 ;
	virtual HRESULT __safecall Get_fileSize(System::WideString &__Get_fileSize_result) = 0 ;
	virtual HRESULT __safecall Get_fileCreatedDate(System::WideString &__Get_fileCreatedDate_result) = 0 ;
	virtual HRESULT __safecall Get_fileModifiedDate(System::WideString &__Get_fileModifiedDate_result) = 0 ;
	virtual HRESULT __safecall Get_fileUpdatedDate(System::WideString &__Get_fileUpdatedDate_result) = 0 ;
	virtual HRESULT __safecall Get_security(System::WideString &__Get_security_result) = 0 ;
	virtual HRESULT __safecall Get_protocol(System::WideString &__Get_protocol_result) = 0 ;
	virtual HRESULT __safecall Get_nameProp(System::WideString &__Get_nameProp_result) = 0 ;
	virtual HRESULT __safecall write(Winapi::Activex::PSafeArray psarray) = 0 ;
	virtual HRESULT __safecall writeln(Winapi::Activex::PSafeArray psarray) = 0 ;
	virtual HRESULT __safecall open(const System::WideString url, System::OleVariant name, System::OleVariant features, System::OleVariant replace, _di_IDispatch &__open_result) = 0 ;
	virtual HRESULT __safecall close() = 0 ;
	virtual HRESULT __safecall clear() = 0 ;
	virtual HRESULT __safecall queryCommandSupported(const System::WideString cmdID, System::WordBool &__queryCommandSupported_result) = 0 ;
	virtual HRESULT __safecall queryCommandEnabled(const System::WideString cmdID, System::WordBool &__queryCommandEnabled_result) = 0 ;
	virtual HRESULT __safecall queryCommandState(const System::WideString cmdID, System::WordBool &__queryCommandState_result) = 0 ;
	virtual HRESULT __safecall queryCommandIndeterm(const System::WideString cmdID, System::WordBool &__queryCommandIndeterm_result) = 0 ;
	virtual HRESULT __safecall queryCommandText(const System::WideString cmdID, System::WideString &__queryCommandText_result) = 0 ;
	virtual HRESULT __safecall queryCommandValue(const System::WideString cmdID, System::OleVariant &__queryCommandValue_result) = 0 ;
	virtual HRESULT __safecall execCommand(const System::WideString cmdID, System::WordBool showUI, System::OleVariant value, System::WordBool &__execCommand_result) = 0 ;
	virtual HRESULT __safecall execCommandShowHelp(const System::WideString cmdID, System::WordBool &__execCommandShowHelp_result) = 0 ;
	virtual HRESULT __safecall createElement(const System::WideString eTag, _di_IHTMLElement &__createElement_result) = 0 ;
	virtual HRESULT __safecall Set_onhelp(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onhelp(System::OleVariant &__Get_onhelp_result) = 0 ;
	virtual HRESULT __safecall Set_onclick(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onclick(System::OleVariant &__Get_onclick_result) = 0 ;
	virtual HRESULT __safecall Set_ondblclick(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_ondblclick(System::OleVariant &__Get_ondblclick_result) = 0 ;
	virtual HRESULT __safecall Set_onkeyup(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onkeyup(System::OleVariant &__Get_onkeyup_result) = 0 ;
	virtual HRESULT __safecall Set_onkeydown(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onkeydown(System::OleVariant &__Get_onkeydown_result) = 0 ;
	virtual HRESULT __safecall Set_onkeypress(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onkeypress(System::OleVariant &__Get_onkeypress_result) = 0 ;
	virtual HRESULT __safecall Set_onmouseup(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onmouseup(System::OleVariant &__Get_onmouseup_result) = 0 ;
	virtual HRESULT __safecall Set_onmousedown(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onmousedown(System::OleVariant &__Get_onmousedown_result) = 0 ;
	virtual HRESULT __safecall Set_onmousemove(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onmousemove(System::OleVariant &__Get_onmousemove_result) = 0 ;
	virtual HRESULT __safecall Set_onmouseout(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onmouseout(System::OleVariant &__Get_onmouseout_result) = 0 ;
	virtual HRESULT __safecall Set_onmouseover(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onmouseover(System::OleVariant &__Get_onmouseover_result) = 0 ;
	virtual HRESULT __safecall Set_onreadystatechange(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onreadystatechange(System::OleVariant &__Get_onreadystatechange_result) = 0 ;
	virtual HRESULT __safecall Set_onafterupdate(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onafterupdate(System::OleVariant &__Get_onafterupdate_result) = 0 ;
	virtual HRESULT __safecall Set_onrowexit(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onrowexit(System::OleVariant &__Get_onrowexit_result) = 0 ;
	virtual HRESULT __safecall Set_onrowenter(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onrowenter(System::OleVariant &__Get_onrowenter_result) = 0 ;
	virtual HRESULT __safecall Set_ondragstart(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_ondragstart(System::OleVariant &__Get_ondragstart_result) = 0 ;
	virtual HRESULT __safecall Set_onselectstart(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onselectstart(System::OleVariant &__Get_onselectstart_result) = 0 ;
	virtual HRESULT __safecall elementFromPoint(int x, int y, _di_IHTMLElement &__elementFromPoint_result) = 0 ;
	virtual HRESULT __safecall Get_parentWindow(_di_IHTMLWindow2 &__Get_parentWindow_result) = 0 ;
	virtual HRESULT __safecall Get_styleSheets(_di_IHTMLStyleSheetsCollection &__Get_styleSheets_result) = 0 ;
	virtual HRESULT __safecall Set_onbeforeupdate(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onbeforeupdate(System::OleVariant &__Get_onbeforeupdate_result) = 0 ;
	virtual HRESULT __safecall Set_onerrorupdate(System::OleVariant p) = 0 ;
	virtual HRESULT __safecall Get_onerrorupdate(System::OleVariant &__Get_onerrorupdate_result) = 0 ;
	virtual HRESULT __safecall toString(System::WideString &__toString_result) = 0 ;
	virtual HRESULT __safecall createStyleSheet(const System::WideString bstrHref, int lIndex, _di_IHTMLStyleSheet &__createStyleSheet_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_all() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_all(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection all = {read=_scw_Get_all};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_body() { _di_IHTMLElement __r; HRESULT __hr = Get_body(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement body = {read=_scw_Get_body};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElement _scw_Get_activeElement() { _di_IHTMLElement __r; HRESULT __hr = Get_activeElement(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElement activeElement = {read=_scw_Get_activeElement};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_images() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_images(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection images = {read=_scw_Get_images};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_applets() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_applets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection applets = {read=_scw_Get_applets};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_links() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_links(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection links = {read=_scw_Get_links};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_forms() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_forms(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection forms = {read=_scw_Get_forms};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_anchors() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_anchors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection anchors = {read=_scw_Get_anchors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_title() { System::WideString __r; HRESULT __hr = Get_title(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString title = {read=_scw_Get_title, write=Set_title};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_scripts() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_scripts(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection scripts = {read=_scw_Get_scripts};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_designMode() { System::WideString __r; HRESULT __hr = Get_designMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString designMode = {read=_scw_Get_designMode, write=Set_designMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLSelectionObject _scw_Get_selection() { _di_IHTMLSelectionObject __r; HRESULT __hr = Get_selection(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLSelectionObject selection = {read=_scw_Get_selection};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_readyState() { System::WideString __r; HRESULT __hr = Get_readyState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString readyState = {read=_scw_Get_readyState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLFramesCollection2 _scw_Get_frames() { _di_IHTMLFramesCollection2 __r; HRESULT __hr = Get_frames(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLFramesCollection2 frames = {read=_scw_Get_frames};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_embeds() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_embeds(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection embeds = {read=_scw_Get_embeds};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLElementCollection _scw_Get_plugins() { _di_IHTMLElementCollection __r; HRESULT __hr = Get_plugins(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLElementCollection plugins = {read=_scw_Get_plugins};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_alinkColor() { System::OleVariant __r; HRESULT __hr = Get_alinkColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant alinkColor = {read=_scw_Get_alinkColor, write=Set_alinkColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_bgColor() { System::OleVariant __r; HRESULT __hr = Get_bgColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant bgColor = {read=_scw_Get_bgColor, write=Set_bgColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_fgColor() { System::OleVariant __r; HRESULT __hr = Get_fgColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant fgColor = {read=_scw_Get_fgColor, write=Set_fgColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_linkColor() { System::OleVariant __r; HRESULT __hr = Get_linkColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant linkColor = {read=_scw_Get_linkColor, write=Set_linkColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_vlinkColor() { System::OleVariant __r; HRESULT __hr = Get_vlinkColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant vlinkColor = {read=_scw_Get_vlinkColor, write=Set_vlinkColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_referrer() { System::WideString __r; HRESULT __hr = Get_referrer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString referrer = {read=_scw_Get_referrer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLLocation _scw_Get_location() { _di_IHTMLLocation __r; HRESULT __hr = Get_location(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLLocation location = {read=_scw_Get_location};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_lastModified() { System::WideString __r; HRESULT __hr = Get_lastModified(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString lastModified = {read=_scw_Get_lastModified};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_url() { System::WideString __r; HRESULT __hr = Get_url(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString url = {read=_scw_Get_url, write=Set_url};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_domain() { System::WideString __r; HRESULT __hr = Get_domain(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString domain = {read=_scw_Get_domain, write=Set_domain};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_cookie() { System::WideString __r; HRESULT __hr = Get_cookie(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString cookie = {read=_scw_Get_cookie, write=Set_cookie};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_expando() { System::WordBool __r; HRESULT __hr = Get_expando(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool expando = {read=_scw_Get_expando, write=Set_expando};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_charset() { System::WideString __r; HRESULT __hr = Get_charset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString charset = {read=_scw_Get_charset, write=Set_charset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_defaultCharset() { System::WideString __r; HRESULT __hr = Get_defaultCharset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString defaultCharset = {read=_scw_Get_defaultCharset, write=Set_defaultCharset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_mimeType() { System::WideString __r; HRESULT __hr = Get_mimeType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString mimeType = {read=_scw_Get_mimeType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileSize() { System::WideString __r; HRESULT __hr = Get_fileSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileSize = {read=_scw_Get_fileSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileCreatedDate() { System::WideString __r; HRESULT __hr = Get_fileCreatedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileCreatedDate = {read=_scw_Get_fileCreatedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileModifiedDate() { System::WideString __r; HRESULT __hr = Get_fileModifiedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileModifiedDate = {read=_scw_Get_fileModifiedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_fileUpdatedDate() { System::WideString __r; HRESULT __hr = Get_fileUpdatedDate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString fileUpdatedDate = {read=_scw_Get_fileUpdatedDate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_security() { System::WideString __r; HRESULT __hr = Get_security(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString security = {read=_scw_Get_security};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_protocol() { System::WideString __r; HRESULT __hr = Get_protocol(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString protocol = {read=_scw_Get_protocol};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_nameProp() { System::WideString __r; HRESULT __hr = Get_nameProp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString nameProp = {read=_scw_Get_nameProp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onhelp() { System::OleVariant __r; HRESULT __hr = Get_onhelp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onhelp = {read=_scw_Get_onhelp, write=Set_onhelp};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onclick() { System::OleVariant __r; HRESULT __hr = Get_onclick(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onclick = {read=_scw_Get_onclick, write=Set_onclick};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_ondblclick() { System::OleVariant __r; HRESULT __hr = Get_ondblclick(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant ondblclick = {read=_scw_Get_ondblclick, write=Set_ondblclick};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onkeyup() { System::OleVariant __r; HRESULT __hr = Get_onkeyup(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onkeyup = {read=_scw_Get_onkeyup, write=Set_onkeyup};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onkeydown() { System::OleVariant __r; HRESULT __hr = Get_onkeydown(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onkeydown = {read=_scw_Get_onkeydown, write=Set_onkeydown};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onkeypress() { System::OleVariant __r; HRESULT __hr = Get_onkeypress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onkeypress = {read=_scw_Get_onkeypress, write=Set_onkeypress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onmouseup() { System::OleVariant __r; HRESULT __hr = Get_onmouseup(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onmouseup = {read=_scw_Get_onmouseup, write=Set_onmouseup};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onmousedown() { System::OleVariant __r; HRESULT __hr = Get_onmousedown(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onmousedown = {read=_scw_Get_onmousedown, write=Set_onmousedown};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onmousemove() { System::OleVariant __r; HRESULT __hr = Get_onmousemove(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onmousemove = {read=_scw_Get_onmousemove, write=Set_onmousemove};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onmouseout() { System::OleVariant __r; HRESULT __hr = Get_onmouseout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onmouseout = {read=_scw_Get_onmouseout, write=Set_onmouseout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onmouseover() { System::OleVariant __r; HRESULT __hr = Get_onmouseover(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onmouseover = {read=_scw_Get_onmouseover, write=Set_onmouseover};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onreadystatechange() { System::OleVariant __r; HRESULT __hr = Get_onreadystatechange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onreadystatechange = {read=_scw_Get_onreadystatechange, write=Set_onreadystatechange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onafterupdate() { System::OleVariant __r; HRESULT __hr = Get_onafterupdate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onafterupdate = {read=_scw_Get_onafterupdate, write=Set_onafterupdate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onrowexit() { System::OleVariant __r; HRESULT __hr = Get_onrowexit(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onrowexit = {read=_scw_Get_onrowexit, write=Set_onrowexit};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onrowenter() { System::OleVariant __r; HRESULT __hr = Get_onrowenter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onrowenter = {read=_scw_Get_onrowenter, write=Set_onrowenter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_ondragstart() { System::OleVariant __r; HRESULT __hr = Get_ondragstart(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant ondragstart = {read=_scw_Get_ondragstart, write=Set_ondragstart};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onselectstart() { System::OleVariant __r; HRESULT __hr = Get_onselectstart(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onselectstart = {read=_scw_Get_onselectstart, write=Set_onselectstart};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLWindow2 _scw_Get_parentWindow() { _di_IHTMLWindow2 __r; HRESULT __hr = Get_parentWindow(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLWindow2 parentWindow = {read=_scw_Get_parentWindow};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IHTMLStyleSheetsCollection _scw_Get_styleSheets() { _di_IHTMLStyleSheetsCollection __r; HRESULT __hr = Get_styleSheets(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IHTMLStyleSheetsCollection styleSheets = {read=_scw_Get_styleSheets};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onbeforeupdate() { System::OleVariant __r; HRESULT __hr = Get_onbeforeupdate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onbeforeupdate = {read=_scw_Get_onbeforeupdate, write=Set_onbeforeupdate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_onerrorupdate() { System::OleVariant __r; HRESULT __hr = Get_onerrorupdate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant onerrorupdate = {read=_scw_Get_onerrorupdate, write=Set_onerrorupdate};
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ieinterfaces */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_IEINTERFACES)
using namespace System::Win::Ieinterfaces;
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
#endif	// System_Win_IeinterfacesHPP
