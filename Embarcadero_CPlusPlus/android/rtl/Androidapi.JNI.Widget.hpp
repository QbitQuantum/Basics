// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Widget.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_WidgetHPP
#define Androidapi_Jni_WidgetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Widget
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAdapterViewClass;
typedef System::DelphiInterface<JAdapterViewClass> _di_JAdapterViewClass;
__interface DELPHIINTERFACE JAdapterView;
typedef System::DelphiInterface<JAdapterView> _di_JAdapterView;
class DELPHICLASS TJAdapterView;
__interface DELPHIINTERFACE JAbsListViewClass;
typedef System::DelphiInterface<JAbsListViewClass> _di_JAbsListViewClass;
__interface DELPHIINTERFACE JAbsListView;
typedef System::DelphiInterface<JAbsListView> _di_JAbsListView;
class DELPHICLASS TJAbsListView;
__interface DELPHIINTERFACE JAbsListView_LayoutParamsClass;
typedef System::DelphiInterface<JAbsListView_LayoutParamsClass> _di_JAbsListView_LayoutParamsClass;
__interface DELPHIINTERFACE JAbsListView_LayoutParams;
typedef System::DelphiInterface<JAbsListView_LayoutParams> _di_JAbsListView_LayoutParams;
class DELPHICLASS TJAbsListView_LayoutParams;
__interface DELPHIINTERFACE JAbsListView_MultiChoiceModeListenerClass;
typedef System::DelphiInterface<JAbsListView_MultiChoiceModeListenerClass> _di_JAbsListView_MultiChoiceModeListenerClass;
__interface DELPHIINTERFACE JAbsListView_MultiChoiceModeListener;
typedef System::DelphiInterface<JAbsListView_MultiChoiceModeListener> _di_JAbsListView_MultiChoiceModeListener;
class DELPHICLASS TJAbsListView_MultiChoiceModeListener;
__interface DELPHIINTERFACE JAbsListView_OnScrollListenerClass;
typedef System::DelphiInterface<JAbsListView_OnScrollListenerClass> _di_JAbsListView_OnScrollListenerClass;
__interface DELPHIINTERFACE JAbsListView_OnScrollListener;
typedef System::DelphiInterface<JAbsListView_OnScrollListener> _di_JAbsListView_OnScrollListener;
class DELPHICLASS TJAbsListView_OnScrollListener;
__interface DELPHIINTERFACE JAbsListView_RecyclerListenerClass;
typedef System::DelphiInterface<JAbsListView_RecyclerListenerClass> _di_JAbsListView_RecyclerListenerClass;
__interface DELPHIINTERFACE JAbsListView_RecyclerListener;
typedef System::DelphiInterface<JAbsListView_RecyclerListener> _di_JAbsListView_RecyclerListener;
class DELPHICLASS TJAbsListView_RecyclerListener;
__interface DELPHIINTERFACE JAbsoluteLayoutClass;
typedef System::DelphiInterface<JAbsoluteLayoutClass> _di_JAbsoluteLayoutClass;
__interface DELPHIINTERFACE JAbsoluteLayout;
typedef System::DelphiInterface<JAbsoluteLayout> _di_JAbsoluteLayout;
class DELPHICLASS TJAbsoluteLayout;
__interface DELPHIINTERFACE JAdapterClass;
typedef System::DelphiInterface<JAdapterClass> _di_JAdapterClass;
__interface DELPHIINTERFACE JAdapter;
typedef System::DelphiInterface<JAdapter> _di_JAdapter;
class DELPHICLASS TJAdapter;
__interface DELPHIINTERFACE JAdapterView_OnItemClickListenerClass;
typedef System::DelphiInterface<JAdapterView_OnItemClickListenerClass> _di_JAdapterView_OnItemClickListenerClass;
__interface DELPHIINTERFACE JAdapterView_OnItemClickListener;
typedef System::DelphiInterface<JAdapterView_OnItemClickListener> _di_JAdapterView_OnItemClickListener;
class DELPHICLASS TJAdapterView_OnItemClickListener;
__interface DELPHIINTERFACE JAdapterView_OnItemLongClickListenerClass;
typedef System::DelphiInterface<JAdapterView_OnItemLongClickListenerClass> _di_JAdapterView_OnItemLongClickListenerClass;
__interface DELPHIINTERFACE JAdapterView_OnItemLongClickListener;
typedef System::DelphiInterface<JAdapterView_OnItemLongClickListener> _di_JAdapterView_OnItemLongClickListener;
class DELPHICLASS TJAdapterView_OnItemLongClickListener;
__interface DELPHIINTERFACE JAdapterView_OnItemSelectedListenerClass;
typedef System::DelphiInterface<JAdapterView_OnItemSelectedListenerClass> _di_JAdapterView_OnItemSelectedListenerClass;
__interface DELPHIINTERFACE JAdapterView_OnItemSelectedListener;
typedef System::DelphiInterface<JAdapterView_OnItemSelectedListener> _di_JAdapterView_OnItemSelectedListener;
class DELPHICLASS TJAdapterView_OnItemSelectedListener;
__interface DELPHIINTERFACE JBaseAdapterClass;
typedef System::DelphiInterface<JBaseAdapterClass> _di_JBaseAdapterClass;
__interface DELPHIINTERFACE JBaseAdapter;
typedef System::DelphiInterface<JBaseAdapter> _di_JBaseAdapter;
class DELPHICLASS TJBaseAdapter;
__interface DELPHIINTERFACE JTextViewClass;
typedef System::DelphiInterface<JTextViewClass> _di_JTextViewClass;
__interface DELPHIINTERFACE JTextView;
typedef System::DelphiInterface<JTextView> _di_JTextView;
class DELPHICLASS TJTextView;
__interface DELPHIINTERFACE JButtonClass;
typedef System::DelphiInterface<JButtonClass> _di_JButtonClass;
__interface DELPHIINTERFACE JButton;
typedef System::DelphiInterface<JButton> _di_JButton;
class DELPHICLASS TJButton;
__interface DELPHIINTERFACE JFrameLayoutClass;
typedef System::DelphiInterface<JFrameLayoutClass> _di_JFrameLayoutClass;
__interface DELPHIINTERFACE JFrameLayout;
typedef System::DelphiInterface<JFrameLayout> _di_JFrameLayout;
class DELPHICLASS TJFrameLayout;
__interface DELPHIINTERFACE JCalendarViewClass;
typedef System::DelphiInterface<JCalendarViewClass> _di_JCalendarViewClass;
__interface DELPHIINTERFACE JCalendarView;
typedef System::DelphiInterface<JCalendarView> _di_JCalendarView;
class DELPHICLASS TJCalendarView;
__interface DELPHIINTERFACE JCalendarView_OnDateChangeListenerClass;
typedef System::DelphiInterface<JCalendarView_OnDateChangeListenerClass> _di_JCalendarView_OnDateChangeListenerClass;
__interface DELPHIINTERFACE JCalendarView_OnDateChangeListener;
typedef System::DelphiInterface<JCalendarView_OnDateChangeListener> _di_JCalendarView_OnDateChangeListener;
class DELPHICLASS TJCalendarView_OnDateChangeListener;
__interface DELPHIINTERFACE JCompoundButtonClass;
typedef System::DelphiInterface<JCompoundButtonClass> _di_JCompoundButtonClass;
__interface DELPHIINTERFACE JCompoundButton;
typedef System::DelphiInterface<JCompoundButton> _di_JCompoundButton;
class DELPHICLASS TJCompoundButton;
__interface DELPHIINTERFACE JCompoundButton_OnCheckedChangeListenerClass;
typedef System::DelphiInterface<JCompoundButton_OnCheckedChangeListenerClass> _di_JCompoundButton_OnCheckedChangeListenerClass;
__interface DELPHIINTERFACE JCompoundButton_OnCheckedChangeListener;
typedef System::DelphiInterface<JCompoundButton_OnCheckedChangeListener> _di_JCompoundButton_OnCheckedChangeListener;
class DELPHICLASS TJCompoundButton_OnCheckedChangeListener;
__interface DELPHIINTERFACE JDatePickerClass;
typedef System::DelphiInterface<JDatePickerClass> _di_JDatePickerClass;
__interface DELPHIINTERFACE JDatePicker;
typedef System::DelphiInterface<JDatePicker> _di_JDatePicker;
class DELPHICLASS TJDatePicker;
__interface DELPHIINTERFACE JDatePicker_OnDateChangedListenerClass;
typedef System::DelphiInterface<JDatePicker_OnDateChangedListenerClass> _di_JDatePicker_OnDateChangedListenerClass;
__interface DELPHIINTERFACE JDatePicker_OnDateChangedListener;
typedef System::DelphiInterface<JDatePicker_OnDateChangedListener> _di_JDatePicker_OnDateChangedListener;
class DELPHICLASS TJDatePicker_OnDateChangedListener;
__interface DELPHIINTERFACE JEditTextClass;
typedef System::DelphiInterface<JEditTextClass> _di_JEditTextClass;
__interface DELPHIINTERFACE JEditText;
typedef System::DelphiInterface<JEditText> _di_JEditText;
class DELPHICLASS TJEditText;
__interface DELPHIINTERFACE JFrameLayout_LayoutParamsClass;
typedef System::DelphiInterface<JFrameLayout_LayoutParamsClass> _di_JFrameLayout_LayoutParamsClass;
__interface DELPHIINTERFACE JFrameLayout_LayoutParams;
typedef System::DelphiInterface<JFrameLayout_LayoutParams> _di_JFrameLayout_LayoutParams;
class DELPHICLASS TJFrameLayout_LayoutParams;
__interface DELPHIINTERFACE JImageViewClass;
typedef System::DelphiInterface<JImageViewClass> _di_JImageViewClass;
__interface DELPHIINTERFACE JImageView;
typedef System::DelphiInterface<JImageView> _di_JImageView;
class DELPHICLASS TJImageView;
__interface DELPHIINTERFACE JImageView_ScaleTypeClass;
typedef System::DelphiInterface<JImageView_ScaleTypeClass> _di_JImageView_ScaleTypeClass;
__interface DELPHIINTERFACE JImageView_ScaleType;
typedef System::DelphiInterface<JImageView_ScaleType> _di_JImageView_ScaleType;
class DELPHICLASS TJImageView_ScaleType;
__interface DELPHIINTERFACE JLinearLayoutClass;
typedef System::DelphiInterface<JLinearLayoutClass> _di_JLinearLayoutClass;
__interface DELPHIINTERFACE JLinearLayout;
typedef System::DelphiInterface<JLinearLayout> _di_JLinearLayout;
class DELPHICLASS TJLinearLayout;
__interface DELPHIINTERFACE JLinearLayout_LayoutParamsClass;
typedef System::DelphiInterface<JLinearLayout_LayoutParamsClass> _di_JLinearLayout_LayoutParamsClass;
__interface DELPHIINTERFACE JLinearLayout_LayoutParams;
typedef System::DelphiInterface<JLinearLayout_LayoutParams> _di_JLinearLayout_LayoutParams;
class DELPHICLASS TJLinearLayout_LayoutParams;
__interface DELPHIINTERFACE JListAdapterClass;
typedef System::DelphiInterface<JListAdapterClass> _di_JListAdapterClass;
__interface DELPHIINTERFACE JListAdapter;
typedef System::DelphiInterface<JListAdapter> _di_JListAdapter;
class DELPHICLASS TJListAdapter;
__interface DELPHIINTERFACE JListViewClass;
typedef System::DelphiInterface<JListViewClass> _di_JListViewClass;
__interface DELPHIINTERFACE JListView;
typedef System::DelphiInterface<JListView> _di_JListView;
class DELPHICLASS TJListView;
__interface DELPHIINTERFACE JPopupWindowClass;
typedef System::DelphiInterface<JPopupWindowClass> _di_JPopupWindowClass;
__interface DELPHIINTERFACE JPopupWindow;
typedef System::DelphiInterface<JPopupWindow> _di_JPopupWindow;
class DELPHICLASS TJPopupWindow;
__interface DELPHIINTERFACE JPopupWindow_OnDismissListenerClass;
typedef System::DelphiInterface<JPopupWindow_OnDismissListenerClass> _di_JPopupWindow_OnDismissListenerClass;
__interface DELPHIINTERFACE JPopupWindow_OnDismissListener;
typedef System::DelphiInterface<JPopupWindow_OnDismissListener> _di_JPopupWindow_OnDismissListener;
class DELPHICLASS TJPopupWindow_OnDismissListener;
__interface DELPHIINTERFACE JRelativeLayoutClass;
typedef System::DelphiInterface<JRelativeLayoutClass> _di_JRelativeLayoutClass;
__interface DELPHIINTERFACE JRelativeLayout;
typedef System::DelphiInterface<JRelativeLayout> _di_JRelativeLayout;
class DELPHICLASS TJRelativeLayout;
__interface DELPHIINTERFACE JRelativeLayout_LayoutParamsClass;
typedef System::DelphiInterface<JRelativeLayout_LayoutParamsClass> _di_JRelativeLayout_LayoutParamsClass;
__interface DELPHIINTERFACE JRelativeLayout_LayoutParams;
typedef System::DelphiInterface<JRelativeLayout_LayoutParams> _di_JRelativeLayout_LayoutParams;
class DELPHICLASS TJRelativeLayout_LayoutParams;
__interface DELPHIINTERFACE JRemoteViewsClass;
typedef System::DelphiInterface<JRemoteViewsClass> _di_JRemoteViewsClass;
__interface DELPHIINTERFACE JRemoteViews;
typedef System::DelphiInterface<JRemoteViews> _di_JRemoteViews;
class DELPHICLASS TJRemoteViews;
__interface DELPHIINTERFACE JScrollViewClass;
typedef System::DelphiInterface<JScrollViewClass> _di_JScrollViewClass;
__interface DELPHIINTERFACE JScrollView;
typedef System::DelphiInterface<JScrollView> _di_JScrollView;
class DELPHICLASS TJScrollView;
__interface DELPHIINTERFACE JScrollerClass;
typedef System::DelphiInterface<JScrollerClass> _di_JScrollerClass;
__interface DELPHIINTERFACE JScroller;
typedef System::DelphiInterface<JScroller> _di_JScroller;
class DELPHICLASS TJScroller;
__interface DELPHIINTERFACE JSpinnerAdapterClass;
typedef System::DelphiInterface<JSpinnerAdapterClass> _di_JSpinnerAdapterClass;
__interface DELPHIINTERFACE JSpinnerAdapter;
typedef System::DelphiInterface<JSpinnerAdapter> _di_JSpinnerAdapter;
class DELPHICLASS TJSpinnerAdapter;
__interface DELPHIINTERFACE JSwitchClass;
typedef System::DelphiInterface<JSwitchClass> _di_JSwitchClass;
__interface DELPHIINTERFACE JSwitch;
typedef System::DelphiInterface<JSwitch> _di_JSwitch;
class DELPHICLASS TJSwitch;
__interface DELPHIINTERFACE JTextView_BufferTypeClass;
typedef System::DelphiInterface<JTextView_BufferTypeClass> _di_JTextView_BufferTypeClass;
__interface DELPHIINTERFACE JTextView_BufferType;
typedef System::DelphiInterface<JTextView_BufferType> _di_JTextView_BufferType;
class DELPHICLASS TJTextView_BufferType;
__interface DELPHIINTERFACE JTextView_OnEditorActionListenerClass;
typedef System::DelphiInterface<JTextView_OnEditorActionListenerClass> _di_JTextView_OnEditorActionListenerClass;
__interface DELPHIINTERFACE JTextView_OnEditorActionListener;
typedef System::DelphiInterface<JTextView_OnEditorActionListener> _di_JTextView_OnEditorActionListener;
class DELPHICLASS TJTextView_OnEditorActionListener;
__interface DELPHIINTERFACE JTimePickerClass;
typedef System::DelphiInterface<JTimePickerClass> _di_JTimePickerClass;
__interface DELPHIINTERFACE JTimePicker;
typedef System::DelphiInterface<JTimePicker> _di_JTimePicker;
class DELPHICLASS TJTimePicker;
__interface DELPHIINTERFACE JTimePicker_OnTimeChangedListenerClass;
typedef System::DelphiInterface<JTimePicker_OnTimeChangedListenerClass> _di_JTimePicker_OnTimeChangedListenerClass;
__interface DELPHIINTERFACE JTimePicker_OnTimeChangedListener;
typedef System::DelphiInterface<JTimePicker_OnTimeChangedListener> _di_JTimePicker_OnTimeChangedListener;
class DELPHICLASS TJTimePicker_OnTimeChangedListener;
__interface DELPHIINTERFACE JToastClass;
typedef System::DelphiInterface<JToastClass> _di_JToastClass;
__interface DELPHIINTERFACE JToast;
typedef System::DelphiInterface<JToast> _di_JToast;
class DELPHICLASS TJToast;
__interface DELPHIINTERFACE JToolbarClass;
typedef System::DelphiInterface<JToolbarClass> _di_JToolbarClass;
__interface DELPHIINTERFACE JToolbar;
typedef System::DelphiInterface<JToolbar> _di_JToolbar;
class DELPHICLASS TJToolbar;
__interface DELPHIINTERFACE JToolbar_OnMenuItemClickListenerClass;
typedef System::DelphiInterface<JToolbar_OnMenuItemClickListenerClass> _di_JToolbar_OnMenuItemClickListenerClass;
__interface DELPHIINTERFACE JToolbar_OnMenuItemClickListener;
typedef System::DelphiInterface<JToolbar_OnMenuItemClickListener> _di_JToolbar_OnMenuItemClickListener;
class DELPHICLASS TJToolbar_OnMenuItemClickListener;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{6490B102-5823-45D6-A2C4-E7211652D552}") JAdapterViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	virtual int __cdecl _GetINVALID_POSITION() = 0 ;
	virtual __int64 __cdecl _GetINVALID_ROW_ID() = 0 ;
	virtual int __cdecl _GetITEM_VIEW_TYPE_HEADER_OR_FOOTER() = 0 ;
	virtual int __cdecl _GetITEM_VIEW_TYPE_IGNORE() = 0 ;
	HIDESBASE virtual _di_JAdapterView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JAdapterView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JAdapterView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JAdapterView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	__property int INVALID_POSITION = {read=_GetINVALID_POSITION};
	__property __int64 INVALID_ROW_ID = {read=_GetINVALID_ROW_ID};
	__property int ITEM_VIEW_TYPE_HEADER_OR_FOOTER = {read=_GetITEM_VIEW_TYPE_HEADER_OR_FOOTER};
	__property int ITEM_VIEW_TYPE_IGNORE = {read=_GetITEM_VIEW_TYPE_IGNORE};
};

__interface  INTERFACE_UUID("{7A567A58-E436-4C18-94B6-DCE4ECB35FDB}") JAdapterView  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, int index) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, int index, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual _di_JAdapter __cdecl getAdapter() = 0 ;
	virtual int __cdecl getCount() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getEmptyView() = 0 ;
	virtual int __cdecl getFirstVisiblePosition() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getItemAtPosition(int position) = 0 ;
	virtual __int64 __cdecl getItemIdAtPosition(int position) = 0 ;
	virtual int __cdecl getLastVisiblePosition() = 0 ;
	virtual _di_JAdapterView_OnItemClickListener __cdecl getOnItemClickListener() = 0 ;
	virtual _di_JAdapterView_OnItemLongClickListener __cdecl getOnItemLongClickListener() = 0 ;
	virtual _di_JAdapterView_OnItemSelectedListener __cdecl getOnItemSelectedListener() = 0 ;
	virtual int __cdecl getPositionForView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getSelectedItem() = 0 ;
	virtual __int64 __cdecl getSelectedItemId() = 0 ;
	virtual int __cdecl getSelectedItemPosition() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getSelectedView() = 0 ;
	HIDESBASE virtual void __cdecl onProvideAutofillStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure, int flags) = 0 ;
	virtual bool __cdecl performItemClick(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, __int64 id) = 0 ;
	HIDESBASE virtual void __cdecl removeAllViews() = 0 ;
	HIDESBASE virtual void __cdecl removeView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child) = 0 ;
	HIDESBASE virtual void __cdecl removeViewAt(int index) = 0 ;
	virtual void __cdecl setAdapter(_di_JAdapter adapter) = 0 ;
	virtual void __cdecl setEmptyView(Androidapi::Jni::Graphicscontentviewtext::_di_JView emptyView) = 0 ;
	HIDESBASE virtual void __cdecl setFocusable(int focusable) = 0 ;
	HIDESBASE virtual void __cdecl setFocusableInTouchMode(bool focusable) = 0 ;
	HIDESBASE virtual void __cdecl setOnClickListener(Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnClickListener l) = 0 ;
	virtual void __cdecl setOnItemClickListener(_di_JAdapterView_OnItemClickListener listener) = 0 ;
	virtual void __cdecl setOnItemLongClickListener(_di_JAdapterView_OnItemLongClickListener listener) = 0 ;
	virtual void __cdecl setOnItemSelectedListener(_di_JAdapterView_OnItemSelectedListener listener) = 0 ;
	virtual void __cdecl setSelection(int position) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdapterView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterViewClass,_di_JAdapterView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterViewClass,_di_JAdapterView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdapterView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterViewClass,_di_JAdapterView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdapterView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BAC07826-4DE7-4811-BCF8-A4E35AF7F784}") JAbsListViewClass  : public JAdapterViewClass 
{
	virtual int __cdecl _GetCHOICE_MODE_MULTIPLE() = 0 ;
	virtual int __cdecl _GetCHOICE_MODE_MULTIPLE_MODAL() = 0 ;
	virtual int __cdecl _GetCHOICE_MODE_NONE() = 0 ;
	virtual int __cdecl _GetCHOICE_MODE_SINGLE() = 0 ;
	virtual int __cdecl _GetTRANSCRIPT_MODE_ALWAYS_SCROLL() = 0 ;
	virtual int __cdecl _GetTRANSCRIPT_MODE_DISABLED() = 0 ;
	virtual int __cdecl _GetTRANSCRIPT_MODE_NORMAL() = 0 ;
	HIDESBASE virtual _di_JAbsListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	__property int CHOICE_MODE_MULTIPLE = {read=_GetCHOICE_MODE_MULTIPLE};
	__property int CHOICE_MODE_MULTIPLE_MODAL = {read=_GetCHOICE_MODE_MULTIPLE_MODAL};
	__property int CHOICE_MODE_NONE = {read=_GetCHOICE_MODE_NONE};
	__property int CHOICE_MODE_SINGLE = {read=_GetCHOICE_MODE_SINGLE};
	__property int TRANSCRIPT_MODE_ALWAYS_SCROLL = {read=_GetTRANSCRIPT_MODE_ALWAYS_SCROLL};
	__property int TRANSCRIPT_MODE_DISABLED = {read=_GetTRANSCRIPT_MODE_DISABLED};
	__property int TRANSCRIPT_MODE_NORMAL = {read=_GetTRANSCRIPT_MODE_NORMAL};
};

__interface  INTERFACE_UUID("{F366DE71-7C40-4135-8C83-F7354D97A276}") JAbsListView  : public JAdapterView 
{
	HIDESBASE virtual void __cdecl addTouchables(Androidapi::Jni::Javatypes::_di_JArrayList views) = 0 ;
	virtual void __cdecl afterTextChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable s) = 0 ;
	virtual void __cdecl beforeTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int count, int after) = 0 ;
	virtual bool __cdecl canScrollList(int direction) = 0 ;
	HIDESBASE virtual bool __cdecl checkInputConnectionProxy(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl clearChoices() = 0 ;
	virtual void __cdecl clearTextFilter() = 0 ;
	virtual void __cdecl deferNotifyDataSetChanged() = 0 ;
	HIDESBASE virtual void __cdecl dispatchDrawableHotspotChanged(float x, float y) = 0 ;
	HIDESBASE virtual void __cdecl draw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	virtual void __cdecl fling(int velocityY) = 0 ;
	HIDESBASE virtual _di_JAbsListView_LayoutParams __cdecl generateLayoutParams(Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual int __cdecl getCacheColorHint() = 0 ;
	virtual int __cdecl getCheckedItemCount() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl getCheckedItemIds() = 0 ;
	virtual int __cdecl getCheckedItemPosition() = 0 ;
	virtual Androidapi::Jni::Util::_di_JSparseBooleanArray __cdecl getCheckedItemPositions() = 0 ;
	virtual int __cdecl getChoiceMode() = 0 ;
	HIDESBASE virtual void __cdecl getFocusedRect(Androidapi::Jni::Graphicscontentviewtext::_di_JRect r) = 0 ;
	virtual int __cdecl getListPaddingBottom() = 0 ;
	virtual int __cdecl getListPaddingLeft() = 0 ;
	virtual int __cdecl getListPaddingRight() = 0 ;
	virtual int __cdecl getListPaddingTop() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getSelectedView() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getSelector() = 0 ;
	HIDESBASE virtual int __cdecl getSolidColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTextFilter() = 0 ;
	virtual int __cdecl getTranscriptMode() = 0 ;
	HIDESBASE virtual int __cdecl getVerticalScrollbarWidth() = 0 ;
	virtual bool __cdecl hasTextFilter() = 0 ;
	virtual void __cdecl invalidateViews() = 0 ;
	virtual bool __cdecl isFastScrollAlwaysVisible() = 0 ;
	virtual bool __cdecl isFastScrollEnabled() = 0 ;
	virtual bool __cdecl isItemChecked(int position) = 0 ;
	virtual bool __cdecl isScrollingCacheEnabled() = 0 ;
	virtual bool __cdecl isSmoothScrollbarEnabled() = 0 ;
	virtual bool __cdecl isStackFromBottom() = 0 ;
	virtual bool __cdecl isTextFilterEnabled() = 0 ;
	HIDESBASE virtual void __cdecl jumpDrawablesToCurrentState() = 0 ;
	HIDESBASE virtual void __cdecl onCancelPendingInputEvents() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection __cdecl onCreateInputConnection(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo outAttrs) = 0 ;
	virtual void __cdecl onFilterComplete(int count) = 0 ;
	HIDESBASE virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	virtual void __cdecl onGlobalLayout() = 0 ;
	virtual void __cdecl onInitializeAccessibilityNodeInfoForItem(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityNodeInfo info) = 0 ;
	HIDESBASE virtual bool __cdecl onInterceptHoverEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onInterceptTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onNestedFling(Androidapi::Jni::Graphicscontentviewtext::_di_JView target, float velocityX, float velocityY, bool consumed) = 0 ;
	HIDESBASE virtual void __cdecl onNestedScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int dxConsumed, int dyConsumed, int dxUnconsumed, int dyUnconsumed) = 0 ;
	HIDESBASE virtual void __cdecl onNestedScrollAccepted(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int axes) = 0 ;
	virtual bool __cdecl onRemoteAdapterConnected() = 0 ;
	virtual void __cdecl onRemoteAdapterDisconnected() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPointerIcon __cdecl onResolvePointerIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, int pointerIndex) = 0 ;
	virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JParcelable state) = 0 ;
	HIDESBASE virtual void __cdecl onRtlPropertiesChanged(int layoutDirection) = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable __cdecl onSaveInstanceState() = 0 ;
	HIDESBASE virtual bool __cdecl onStartNestedScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int nestedScrollAxes) = 0 ;
	virtual void __cdecl onTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int before, int count) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual void __cdecl onTouchModeChanged(bool isInTouchMode) = 0 ;
	HIDESBASE virtual void __cdecl onWindowFocusChanged(bool hasWindowFocus) = 0 ;
	HIDESBASE virtual bool __cdecl performItemClick(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, __int64 id) = 0 ;
	virtual int __cdecl pointToPosition(int x, int y) = 0 ;
	virtual __int64 __cdecl pointToRowId(int x, int y) = 0 ;
	virtual void __cdecl reclaimViews(Androidapi::Jni::Javatypes::_di_JList views) = 0 ;
	HIDESBASE virtual void __cdecl requestDisallowInterceptTouchEvent(bool disallowIntercept) = 0 ;
	HIDESBASE virtual void __cdecl requestLayout() = 0 ;
	virtual void __cdecl scrollListBy(int y) = 0 ;
	HIDESBASE virtual void __cdecl setAdapter(_di_JListAdapter adapter) = 0 ;
	virtual void __cdecl setCacheColorHint(int color) = 0 ;
	virtual void __cdecl setChoiceMode(int choiceMode) = 0 ;
	virtual void __cdecl setDrawSelectorOnTop(bool onTop) = 0 ;
	virtual void __cdecl setFastScrollAlwaysVisible(bool alwaysShow) = 0 ;
	virtual void __cdecl setFastScrollEnabled(bool enabled) = 0 ;
	virtual void __cdecl setFastScrollStyle(int styleResId) = 0 ;
	virtual void __cdecl setFilterText(Androidapi::Jni::Javatypes::_di_JString filterText) = 0 ;
	virtual void __cdecl setFriction(float friction) = 0 ;
	virtual void __cdecl setItemChecked(int position, bool value) = 0 ;
	virtual void __cdecl setMultiChoiceModeListener(_di_JAbsListView_MultiChoiceModeListener listener) = 0 ;
	virtual void __cdecl setOnScrollListener(_di_JAbsListView_OnScrollListener l) = 0 ;
	HIDESBASE virtual void __cdecl setOverScrollMode(int mode) = 0 ;
	virtual void __cdecl setRecyclerListener(_di_JAbsListView_RecyclerListener listener) = 0 ;
	virtual void __cdecl setRemoteViewsAdapter(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl setScrollBarStyle(int style) = 0 ;
	HIDESBASE virtual void __cdecl setScrollIndicators(Androidapi::Jni::Graphicscontentviewtext::_di_JView up, Androidapi::Jni::Graphicscontentviewtext::_di_JView down) = 0 ;
	virtual void __cdecl setScrollingCacheEnabled(bool enabled) = 0 ;
	virtual void __cdecl setSelectionFromTop(int position, int y) = 0 ;
	virtual void __cdecl setSelector(int resID) = 0 /* overload */;
	virtual void __cdecl setSelector(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable sel) = 0 /* overload */;
	virtual void __cdecl setSmoothScrollbarEnabled(bool enabled) = 0 ;
	virtual void __cdecl setStackFromBottom(bool stackFromBottom) = 0 ;
	virtual void __cdecl setTextFilterEnabled(bool textFilterEnabled) = 0 ;
	virtual void __cdecl setTranscriptMode(int mode) = 0 ;
	virtual void __cdecl setVelocityScale(float scale) = 0 ;
	HIDESBASE virtual void __cdecl setVerticalScrollbarPosition(int position) = 0 ;
	HIDESBASE virtual bool __cdecl showContextMenu() = 0 /* overload */;
	HIDESBASE virtual bool __cdecl showContextMenu(float x, float y) = 0 /* overload */;
	HIDESBASE virtual bool __cdecl showContextMenuForChild(Androidapi::Jni::Graphicscontentviewtext::_di_JView originalView) = 0 /* overload */;
	HIDESBASE virtual bool __cdecl showContextMenuForChild(Androidapi::Jni::Graphicscontentviewtext::_di_JView originalView, float x, float y) = 0 /* overload */;
	virtual void __cdecl smoothScrollBy(int distance, int duration) = 0 ;
	virtual void __cdecl smoothScrollToPosition(int position) = 0 /* overload */;
	virtual void __cdecl smoothScrollToPosition(int position, int boundPosition) = 0 /* overload */;
	virtual void __cdecl smoothScrollToPositionFromTop(int position, int offset, int duration) = 0 /* overload */;
	virtual void __cdecl smoothScrollToPositionFromTop(int position, int offset) = 0 /* overload */;
	virtual bool __cdecl verifyDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable dr) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsListView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListViewClass,_di_JAbsListView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListViewClass,_di_JAbsListView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsListView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListViewClass,_di_JAbsListView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsListView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BA119D83-F4CC-4B61-B09E-949DDD5F3E2C}") JAbsListView_LayoutParamsClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_LayoutParamsClass 
{
	HIDESBASE virtual _di_JAbsListView_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView_LayoutParams __cdecl init(int w, int h) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView_LayoutParams __cdecl init(int w, int h, int viewType) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsListView_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams source) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{0257889C-E50D-40DF-8A0E-1CABF3504F80}") JAbsListView_LayoutParams  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_LayoutParams 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsListView_LayoutParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_LayoutParamsClass,_di_JAbsListView_LayoutParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_LayoutParamsClass,_di_JAbsListView_LayoutParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsListView_LayoutParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_LayoutParamsClass,_di_JAbsListView_LayoutParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsListView_LayoutParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8BB552DD-2198-4EE3-954D-7AED2EA26652}") JAbsListView_MultiChoiceModeListenerClass  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_CallbackClass 
{
	
};

__interface  INTERFACE_UUID("{33997ECE-97BD-47EF-BCAD-E9175C1E4DED}") JAbsListView_MultiChoiceModeListener  : public Androidapi::Jni::Graphicscontentviewtext::JActionMode_Callback 
{
	virtual void __cdecl onItemCheckedStateChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode mode, int position, __int64 id, bool checked) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsListView_MultiChoiceModeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_MultiChoiceModeListenerClass,_di_JAbsListView_MultiChoiceModeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_MultiChoiceModeListenerClass,_di_JAbsListView_MultiChoiceModeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsListView_MultiChoiceModeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_MultiChoiceModeListenerClass,_di_JAbsListView_MultiChoiceModeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsListView_MultiChoiceModeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{479243DC-B7C6-4219-A4EA-4DB71A796E0D}") JAbsListView_OnScrollListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetSCROLL_STATE_FLING() = 0 ;
	virtual int __cdecl _GetSCROLL_STATE_IDLE() = 0 ;
	virtual int __cdecl _GetSCROLL_STATE_TOUCH_SCROLL() = 0 ;
	__property int SCROLL_STATE_FLING = {read=_GetSCROLL_STATE_FLING};
	__property int SCROLL_STATE_IDLE = {read=_GetSCROLL_STATE_IDLE};
	__property int SCROLL_STATE_TOUCH_SCROLL = {read=_GetSCROLL_STATE_TOUCH_SCROLL};
};

__interface  INTERFACE_UUID("{9B3AA66F-2D52-4E66-BF3B-4664B89919F7}") JAbsListView_OnScrollListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onScroll(_di_JAbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) = 0 ;
	virtual void __cdecl onScrollStateChanged(_di_JAbsListView view, int scrollState) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsListView_OnScrollListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_OnScrollListenerClass,_di_JAbsListView_OnScrollListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_OnScrollListenerClass,_di_JAbsListView_OnScrollListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsListView_OnScrollListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_OnScrollListenerClass,_di_JAbsListView_OnScrollListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsListView_OnScrollListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{06DBD286-C7E2-43B3-B493-7DA33E6C15BC}") JAbsListView_RecyclerListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{FD43448A-4F16-42C9-BA44-62CB7DC68E6C}") JAbsListView_RecyclerListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onMovedToScrapHeap(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsListView_RecyclerListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_RecyclerListenerClass,_di_JAbsListView_RecyclerListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_RecyclerListenerClass,_di_JAbsListView_RecyclerListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsListView_RecyclerListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsListView_RecyclerListenerClass,_di_JAbsListView_RecyclerListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsListView_RecyclerListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FD88C087-3EAF-4ABA-A323-5C0788D7B04F}") JAbsoluteLayoutClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JAbsoluteLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsoluteLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsoluteLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JAbsoluteLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{0880FBEB-72E8-4BFB-922D-A773808F1999}") JAbsoluteLayout  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams __cdecl generateLayoutParams(Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAbsoluteLayout : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsoluteLayoutClass,_di_JAbsoluteLayout>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsoluteLayoutClass,_di_JAbsoluteLayout> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAbsoluteLayout() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAbsoluteLayoutClass,_di_JAbsoluteLayout>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAbsoluteLayout() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3958FE3D-7A07-4294-B0AD-318CFF53495F}") JAdapterClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetIGNORE_ITEM_VIEW_TYPE() = 0 ;
	virtual int __cdecl _GetNO_SELECTION() = 0 ;
	__property int IGNORE_ITEM_VIEW_TYPE = {read=_GetIGNORE_ITEM_VIEW_TYPE};
	__property int NO_SELECTION = {read=_GetNO_SELECTION};
};

__interface  INTERFACE_UUID("{0D24EAC8-AFC6-4494-B3D7-B7A70C11B7A2}") JAdapter  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JCharSequence>* __cdecl getAutofillOptions() = 0 ;
	virtual int __cdecl getCount() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getItem(int position) = 0 ;
	virtual __int64 __cdecl getItemId(int position) = 0 ;
	virtual int __cdecl getItemViewType(int position) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getView(int position, Androidapi::Jni::Graphicscontentviewtext::_di_JView convertView, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup parent) = 0 ;
	virtual int __cdecl getViewTypeCount() = 0 ;
	virtual bool __cdecl hasStableIds() = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual void __cdecl registerDataSetObserver(Androidapi::Jni::Graphicscontentviewtext::_di_JDataSetObserver observer) = 0 ;
	virtual void __cdecl unregisterDataSetObserver(Androidapi::Jni::Graphicscontentviewtext::_di_JDataSetObserver observer) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterClass,_di_JAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterClass,_di_JAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterClass,_di_JAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{927C4193-A697-4855-B9DB-F8E7238E505B}") JAdapterView_OnItemClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C961007F-9268-49A1-A7D2-FF18F99CB04F}") JAdapterView_OnItemClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onItemClick(_di_JAdapterView parent, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, __int64 id) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdapterView_OnItemClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemClickListenerClass,_di_JAdapterView_OnItemClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemClickListenerClass,_di_JAdapterView_OnItemClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdapterView_OnItemClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemClickListenerClass,_di_JAdapterView_OnItemClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdapterView_OnItemClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{56FC07F2-9B26-4321-BBA7-87B90FE02F20}") JAdapterView_OnItemLongClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{64F90302-CAC6-499D-85CB-B8159D130BE7}") JAdapterView_OnItemLongClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onItemLongClick(_di_JAdapterView parent, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, __int64 id) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdapterView_OnItemLongClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemLongClickListenerClass,_di_JAdapterView_OnItemLongClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemLongClickListenerClass,_di_JAdapterView_OnItemLongClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdapterView_OnItemLongClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemLongClickListenerClass,_di_JAdapterView_OnItemLongClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdapterView_OnItemLongClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8CC3E8E8-40EF-49D6-990B-985B599D11E1}") JAdapterView_OnItemSelectedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{81BE7775-99A9-4BF0-B1D4-920851584468}") JAdapterView_OnItemSelectedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onItemSelected(_di_JAdapterView parent, Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, __int64 id) = 0 ;
	virtual void __cdecl onNothingSelected(_di_JAdapterView parent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAdapterView_OnItemSelectedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemSelectedListenerClass,_di_JAdapterView_OnItemSelectedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemSelectedListenerClass,_di_JAdapterView_OnItemSelectedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAdapterView_OnItemSelectedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAdapterView_OnItemSelectedListenerClass,_di_JAdapterView_OnItemSelectedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAdapterView_OnItemSelectedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EF2DDA32-D53B-4127-8BDB-D0080A04ABE7}") JBaseAdapterClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JBaseAdapter __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{97D5EC81-ED8E-4BC8-8176-8918C46D6D61}") JBaseAdapter  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl areAllItemsEnabled() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getDropDownView(int position, Androidapi::Jni::Graphicscontentviewtext::_di_JView convertView, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup parent) = 0 ;
	virtual int __cdecl getItemViewType(int position) = 0 ;
	virtual int __cdecl getViewTypeCount() = 0 ;
	virtual bool __cdecl hasStableIds() = 0 ;
	virtual bool __cdecl isEmpty() = 0 ;
	virtual bool __cdecl isEnabled(int position) = 0 ;
	virtual void __cdecl notifyDataSetChanged() = 0 ;
	virtual void __cdecl notifyDataSetInvalidated() = 0 ;
	virtual void __cdecl registerDataSetObserver(Androidapi::Jni::Graphicscontentviewtext::_di_JDataSetObserver observer) = 0 ;
	virtual void __cdecl unregisterDataSetObserver(Androidapi::Jni::Graphicscontentviewtext::_di_JDataSetObserver observer) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJBaseAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseAdapterClass,_di_JBaseAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseAdapterClass,_di_JBaseAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJBaseAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JBaseAdapterClass,_di_JBaseAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJBaseAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF2B8D3E-17E8-4F9A-AEC2-B2E39AB20CDE}") JTextViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewClass 
{
	virtual int __cdecl _GetAUTO_SIZE_TEXT_TYPE_NONE() = 0 ;
	virtual int __cdecl _GetAUTO_SIZE_TEXT_TYPE_UNIFORM() = 0 ;
	HIDESBASE virtual _di_JTextView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JTextView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JTextView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JTextView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	virtual int __cdecl getTextColor(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JTypedArray attrs, int def) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getTextColors(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JTypedArray attrs) = 0 /* overload */;
	__property int AUTO_SIZE_TEXT_TYPE_NONE = {read=_GetAUTO_SIZE_TEXT_TYPE_NONE};
	__property int AUTO_SIZE_TEXT_TYPE_UNIFORM = {read=_GetAUTO_SIZE_TEXT_TYPE_UNIFORM};
};

__interface  INTERFACE_UUID("{45436351-10E4-41C0-ADB2-099CB38BA534}") JTextView  : public Androidapi::Jni::Graphicscontentviewtext::JView 
{
	HIDESBASE virtual void __cdecl addExtraDataToAccessibilityNodeInfo(Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityNodeInfo info, Androidapi::Jni::Javatypes::_di_JString extraDataKey, Androidapi::Jni::Os::_di_JBundle arguments) = 0 ;
	virtual void __cdecl addTextChangedListener(Androidapi::Jni::Graphicscontentviewtext::_di_JTextWatcher watcher) = 0 ;
	virtual void __cdecl append(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual void __cdecl append(Androidapi::Jni::Javatypes::_di_JCharSequence text, int start, int end_) = 0 /* overload */;
	HIDESBASE virtual void __cdecl autofill(Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue value) = 0 ;
	virtual void __cdecl beginBatchEdit() = 0 ;
	virtual bool __cdecl bringPointIntoView(int offset) = 0 ;
	HIDESBASE virtual void __cdecl cancelLongPress() = 0 ;
	virtual void __cdecl clearComposingText() = 0 ;
	HIDESBASE virtual void __cdecl computeScroll() = 0 ;
	virtual void __cdecl debug(int depth) = 0 ;
	virtual bool __cdecl didTouchFocusSelect() = 0 ;
	HIDESBASE virtual void __cdecl drawableHotspotChanged(float x, float y) = 0 ;
	virtual void __cdecl endBatchEdit() = 0 ;
	virtual bool __cdecl extractText(Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedTextRequest request, Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedText outText) = 0 ;
	HIDESBASE virtual void __cdecl findViewsWithText(Androidapi::Jni::Javatypes::_di_JArrayList outViews, Androidapi::Jni::Javatypes::_di_JCharSequence searched, int flags) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual int __cdecl getAutoLinkMask() = 0 ;
	virtual int __cdecl getAutoSizeMaxTextSize() = 0 ;
	virtual int __cdecl getAutoSizeMinTextSize() = 0 ;
	virtual int __cdecl getAutoSizeStepGranularity() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl getAutoSizeTextAvailableSizes() = 0 ;
	virtual int __cdecl getAutoSizeTextType() = 0 ;
	HIDESBASE virtual int __cdecl getAutofillType() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue __cdecl getAutofillValue() = 0 ;
	HIDESBASE virtual int __cdecl getBaseline() = 0 ;
	virtual int __cdecl getBreakStrategy() = 0 ;
	virtual int __cdecl getCompoundDrawablePadding() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getCompoundDrawableTintList() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode __cdecl getCompoundDrawableTintMode() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable>* __cdecl getCompoundDrawables() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable>* __cdecl getCompoundDrawablesRelative() = 0 ;
	virtual int __cdecl getCompoundPaddingBottom() = 0 ;
	virtual int __cdecl getCompoundPaddingEnd() = 0 ;
	virtual int __cdecl getCompoundPaddingLeft() = 0 ;
	virtual int __cdecl getCompoundPaddingRight() = 0 ;
	virtual int __cdecl getCompoundPaddingStart() = 0 ;
	virtual int __cdecl getCompoundPaddingTop() = 0 ;
	virtual int __cdecl getCurrentHintTextColor() = 0 ;
	virtual int __cdecl getCurrentTextColor() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback __cdecl getCustomInsertionActionModeCallback() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback __cdecl getCustomSelectionActionModeCallback() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JEditable __cdecl getEditableText() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTextUtils_TruncateAt __cdecl getEllipsize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getError() = 0 ;
	virtual int __cdecl getExtendedPaddingBottom() = 0 ;
	virtual int __cdecl getExtendedPaddingTop() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JInputFilter>* __cdecl getFilters() = 0 ;
	HIDESBASE virtual void __cdecl getFocusedRect(Androidapi::Jni::Graphicscontentviewtext::_di_JRect r) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFontFeatureSettings() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFontVariationSettings() = 0 ;
	virtual bool __cdecl getFreezesText() = 0 ;
	virtual int __cdecl getGravity() = 0 ;
	virtual int __cdecl getHighlightColor() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getHint() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getHintTextColors() = 0 ;
	virtual int __cdecl getHyphenationFrequency() = 0 ;
	virtual int __cdecl getImeActionId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getImeActionLabel() = 0 ;
	virtual Androidapi::Jni::Os::_di_JLocaleList __cdecl getImeHintLocales() = 0 ;
	virtual int __cdecl getImeOptions() = 0 ;
	virtual bool __cdecl getIncludeFontPadding() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getInputExtras(bool create) = 0 ;
	virtual int __cdecl getInputType() = 0 ;
	virtual int __cdecl getJustificationMode() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JKeyListener __cdecl getKeyListener() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JLayout __cdecl getLayout() = 0 ;
	virtual float __cdecl getLetterSpacing() = 0 ;
	virtual int __cdecl getLineBounds(int line, Androidapi::Jni::Graphicscontentviewtext::_di_JRect bounds) = 0 ;
	virtual int __cdecl getLineCount() = 0 ;
	virtual int __cdecl getLineHeight() = 0 ;
	virtual float __cdecl getLineSpacingExtra() = 0 ;
	virtual float __cdecl getLineSpacingMultiplier() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getLinkTextColors() = 0 ;
	virtual bool __cdecl getLinksClickable() = 0 ;
	virtual int __cdecl getMarqueeRepeatLimit() = 0 ;
	virtual int __cdecl getMaxEms() = 0 ;
	virtual int __cdecl getMaxHeight() = 0 ;
	virtual int __cdecl getMaxLines() = 0 ;
	virtual int __cdecl getMaxWidth() = 0 ;
	virtual int __cdecl getMinEms() = 0 ;
	virtual int __cdecl getMinHeight() = 0 ;
	virtual int __cdecl getMinLines() = 0 ;
	virtual int __cdecl getMinWidth() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JMovementMethod __cdecl getMovementMethod() = 0 ;
	virtual int __cdecl getOffsetForPosition(float x, float y) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTextPaint __cdecl getPaint() = 0 ;
	virtual int __cdecl getPaintFlags() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPrivateImeOptions() = 0 ;
	virtual int __cdecl getSelectionEnd() = 0 ;
	virtual int __cdecl getSelectionStart() = 0 ;
	virtual int __cdecl getShadowColor() = 0 ;
	virtual float __cdecl getShadowDx() = 0 ;
	virtual float __cdecl getShadowDy() = 0 ;
	virtual float __cdecl getShadowRadius() = 0 ;
	virtual bool __cdecl getShowSoftInputOnFocus() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getText() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTextClassifier __cdecl getTextClassifier() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getTextColors() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JLocale __cdecl getTextLocale() = 0 ;
	virtual Androidapi::Jni::Os::_di_JLocaleList __cdecl getTextLocales() = 0 ;
	virtual float __cdecl getTextScaleX() = 0 ;
	virtual float __cdecl getTextSize() = 0 ;
	virtual int __cdecl getTotalPaddingBottom() = 0 ;
	virtual int __cdecl getTotalPaddingEnd() = 0 ;
	virtual int __cdecl getTotalPaddingLeft() = 0 ;
	virtual int __cdecl getTotalPaddingRight() = 0 ;
	virtual int __cdecl getTotalPaddingStart() = 0 ;
	virtual int __cdecl getTotalPaddingTop() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTransformationMethod __cdecl getTransformationMethod() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTypeface __cdecl getTypeface() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JURLSpan>* __cdecl getUrls() = 0 ;
	HIDESBASE virtual bool __cdecl hasOverlappingRendering() = 0 ;
	virtual bool __cdecl hasSelection() = 0 ;
	HIDESBASE virtual void __cdecl invalidateDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 ;
	virtual bool __cdecl isCursorVisible() = 0 ;
	virtual bool __cdecl isInputMethodTarget() = 0 ;
	virtual bool __cdecl isSuggestionsEnabled() = 0 ;
	virtual bool __cdecl isTextSelectable() = 0 ;
	HIDESBASE virtual void __cdecl jumpDrawablesToCurrentState() = 0 ;
	virtual int __cdecl length() = 0 ;
	virtual bool __cdecl moveCursorToVisibleOffset() = 0 ;
	virtual void __cdecl onBeginBatchEdit() = 0 ;
	HIDESBASE virtual bool __cdecl onCheckIsTextEditor() = 0 ;
	virtual void __cdecl onCommitCompletion(Androidapi::Jni::Graphicscontentviewtext::_di_JCompletionInfo text) = 0 ;
	virtual void __cdecl onCommitCorrection(Androidapi::Jni::Graphicscontentviewtext::_di_JCorrectionInfo info) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JInputConnection __cdecl onCreateInputConnection(Androidapi::Jni::Graphicscontentviewtext::_di_JEditorInfo outAttrs) = 0 ;
	HIDESBASE virtual bool __cdecl onDragEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JDragEvent event) = 0 ;
	virtual void __cdecl onEditorAction(int actionCode) = 0 ;
	virtual void __cdecl onEndBatchEdit() = 0 ;
	HIDESBASE virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyMultiple(int keyCode, int repeatCount, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyPreIme(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyShortcut(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl onPreDraw() = 0 ;
	virtual bool __cdecl onPrivateIMECommand(Androidapi::Jni::Javatypes::_di_JString action, Androidapi::Jni::Os::_di_JBundle data) = 0 ;
	HIDESBASE virtual void __cdecl onProvideAutofillStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure, int flags) = 0 ;
	HIDESBASE virtual void __cdecl onProvideStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPointerIcon __cdecl onResolvePointerIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, int pointerIndex) = 0 ;
	virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JParcelable state) = 0 ;
	HIDESBASE virtual void __cdecl onRtlPropertiesChanged(int layoutDirection) = 0 ;
	virtual Androidapi::Jni::Os::_di_JParcelable __cdecl onSaveInstanceState() = 0 ;
	HIDESBASE virtual void __cdecl onScreenStateChanged(int screenState) = 0 ;
	virtual bool __cdecl onTextContextMenuItem(int id) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onTrackballEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual void __cdecl onWindowFocusChanged(bool hasWindowFocus) = 0 ;
	HIDESBASE virtual bool __cdecl performLongClick() = 0 ;
	virtual void __cdecl removeTextChangedListener(Androidapi::Jni::Graphicscontentviewtext::_di_JTextWatcher watcher) = 0 ;
	virtual void __cdecl setAllCaps(bool allCaps) = 0 ;
	virtual void __cdecl setAutoLinkMask(int mask) = 0 ;
	virtual void __cdecl setAutoSizeTextTypeUniformWithConfiguration(int autoSizeMinTextSize, int autoSizeMaxTextSize, int autoSizeStepGranularity, int unit_) = 0 ;
	virtual void __cdecl setAutoSizeTextTypeUniformWithPresetSizes(Androidapi::Jnibridge::TJavaArray__1<int>* presetSizes, int unit_) = 0 ;
	virtual void __cdecl setAutoSizeTextTypeWithDefaults(int autoSizeTextType) = 0 ;
	virtual void __cdecl setBreakStrategy(int breakStrategy) = 0 ;
	virtual void __cdecl setCompoundDrawablePadding(int pad) = 0 ;
	virtual void __cdecl setCompoundDrawableTintList(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList tint) = 0 ;
	virtual void __cdecl setCompoundDrawableTintMode(Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode tintMode) = 0 ;
	virtual void __cdecl setCompoundDrawables(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable left, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable top, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable right, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable bottom) = 0 ;
	virtual void __cdecl setCompoundDrawablesRelative(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable start, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable top, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable end_, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable bottom) = 0 ;
	virtual void __cdecl setCompoundDrawablesRelativeWithIntrinsicBounds(int start, int top, int end_, int bottom) = 0 /* overload */;
	virtual void __cdecl setCompoundDrawablesRelativeWithIntrinsicBounds(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable start, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable top, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable end_, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable bottom) = 0 /* overload */;
	virtual void __cdecl setCompoundDrawablesWithIntrinsicBounds(int left, int top, int right, int bottom) = 0 /* overload */;
	virtual void __cdecl setCompoundDrawablesWithIntrinsicBounds(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable left, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable top, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable right, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable bottom) = 0 /* overload */;
	virtual void __cdecl setCursorVisible(bool visible) = 0 ;
	virtual void __cdecl setCustomInsertionActionModeCallback(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback actionModeCallback) = 0 ;
	virtual void __cdecl setCustomSelectionActionModeCallback(Androidapi::Jni::Graphicscontentviewtext::_di_JActionMode_Callback actionModeCallback) = 0 ;
	virtual void __cdecl setEditableFactory(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable_Factory factory) = 0 ;
	virtual void __cdecl setElegantTextHeight(bool elegant) = 0 ;
	virtual void __cdecl setEllipsize(Androidapi::Jni::Graphicscontentviewtext::_di_JTextUtils_TruncateAt where) = 0 ;
	virtual void __cdecl setEms(int ems) = 0 ;
	HIDESBASE virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setError(Androidapi::Jni::Javatypes::_di_JCharSequence error) = 0 /* overload */;
	virtual void __cdecl setError(Androidapi::Jni::Javatypes::_di_JCharSequence error, Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual void __cdecl setExtractedText(Androidapi::Jni::Graphicscontentviewtext::_di_JExtractedText text) = 0 ;
	virtual void __cdecl setFilters(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JInputFilter>* filters) = 0 ;
	virtual void __cdecl setFontFeatureSettings(Androidapi::Jni::Javatypes::_di_JString fontFeatureSettings) = 0 ;
	virtual bool __cdecl setFontVariationSettings(Androidapi::Jni::Javatypes::_di_JString fontVariationSettings) = 0 ;
	virtual void __cdecl setFreezesText(bool freezesText) = 0 ;
	virtual void __cdecl setGravity(int gravity) = 0 ;
	virtual void __cdecl setHeight(int pixels) = 0 ;
	virtual void __cdecl setHighlightColor(int color) = 0 ;
	virtual void __cdecl setHint(Androidapi::Jni::Javatypes::_di_JCharSequence hint) = 0 /* overload */;
	virtual void __cdecl setHint(int resid) = 0 /* overload */;
	virtual void __cdecl setHintTextColor(int color) = 0 /* overload */;
	virtual void __cdecl setHintTextColor(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList colors) = 0 /* overload */;
	virtual void __cdecl setHorizontallyScrolling(bool whether) = 0 ;
	virtual void __cdecl setHyphenationFrequency(int hyphenationFrequency) = 0 ;
	virtual void __cdecl setImeActionLabel(Androidapi::Jni::Javatypes::_di_JCharSequence label_, int actionId) = 0 ;
	virtual void __cdecl setImeHintLocales(Androidapi::Jni::Os::_di_JLocaleList hintLocales) = 0 ;
	virtual void __cdecl setImeOptions(int imeOptions) = 0 ;
	virtual void __cdecl setIncludeFontPadding(bool includepad) = 0 ;
	virtual void __cdecl setInputExtras(int xmlResId) = 0 ;
	virtual void __cdecl setInputType(int type_) = 0 ;
	virtual void __cdecl setJustificationMode(int justificationMode) = 0 ;
	virtual void __cdecl setKeyListener(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyListener input) = 0 ;
	virtual void __cdecl setLetterSpacing(float letterSpacing) = 0 ;
	virtual void __cdecl setLineSpacing(float add, float mult) = 0 ;
	virtual void __cdecl setLines(int lines) = 0 ;
	virtual void __cdecl setLinkTextColor(int color) = 0 /* overload */;
	virtual void __cdecl setLinkTextColor(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList colors) = 0 /* overload */;
	virtual void __cdecl setLinksClickable(bool whether) = 0 ;
	virtual void __cdecl setMarqueeRepeatLimit(int marqueeLimit) = 0 ;
	virtual void __cdecl setMaxEms(int maxEms) = 0 ;
	virtual void __cdecl setMaxHeight(int maxPixels) = 0 ;
	virtual void __cdecl setMaxLines(int maxLines) = 0 ;
	virtual void __cdecl setMaxWidth(int maxPixels) = 0 ;
	virtual void __cdecl setMinEms(int minEms) = 0 ;
	virtual void __cdecl setMinHeight(int minPixels) = 0 ;
	virtual void __cdecl setMinLines(int minLines) = 0 ;
	virtual void __cdecl setMinWidth(int minPixels) = 0 ;
	virtual void __cdecl setMovementMethod(Androidapi::Jni::Graphicscontentviewtext::_di_JMovementMethod movement) = 0 ;
	virtual void __cdecl setOnEditorActionListener(_di_JTextView_OnEditorActionListener l) = 0 ;
	HIDESBASE virtual void __cdecl setPadding(int left, int top, int right, int bottom) = 0 ;
	HIDESBASE virtual void __cdecl setPaddingRelative(int start, int top, int end_, int bottom) = 0 ;
	virtual void __cdecl setPaintFlags(int flags) = 0 ;
	virtual void __cdecl setPrivateImeOptions(Androidapi::Jni::Javatypes::_di_JString type_) = 0 ;
	virtual void __cdecl setRawInputType(int type_) = 0 ;
	virtual void __cdecl setScroller(_di_JScroller s) = 0 ;
	virtual void __cdecl setSelectAllOnFocus(bool selectAllOnFocus) = 0 ;
	HIDESBASE virtual void __cdecl setSelected(bool selected) = 0 ;
	virtual void __cdecl setShadowLayer(float radius, float dx, float dy, int color) = 0 ;
	virtual void __cdecl setShowSoftInputOnFocus(bool show) = 0 ;
	virtual void __cdecl setSingleLine() = 0 /* overload */;
	virtual void __cdecl setSingleLine(bool singleLine) = 0 /* overload */;
	virtual void __cdecl setSpannableFactory(Androidapi::Jni::Graphicscontentviewtext::_di_JSpannable_Factory factory) = 0 ;
	virtual void __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual void __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence text, _di_JTextView_BufferType type_) = 0 /* overload */;
	virtual void __cdecl setText(Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* text, int start, int len) = 0 /* overload */;
	virtual void __cdecl setText(int resid) = 0 /* overload */;
	virtual void __cdecl setText(int resid, _di_JTextView_BufferType type_) = 0 /* overload */;
	virtual void __cdecl setTextAppearance(int resId) = 0 /* overload */;
	virtual void __cdecl setTextAppearance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int resId) = 0 /* overload */;
	virtual void __cdecl setTextClassifier(Androidapi::Jni::Graphicscontentviewtext::_di_JTextClassifier textClassifier) = 0 ;
	virtual void __cdecl setTextColor(int color) = 0 /* overload */;
	virtual void __cdecl setTextColor(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList colors) = 0 /* overload */;
	virtual void __cdecl setTextIsSelectable(bool selectable) = 0 ;
	virtual void __cdecl setTextKeepState(Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 /* overload */;
	virtual void __cdecl setTextKeepState(Androidapi::Jni::Javatypes::_di_JCharSequence text, _di_JTextView_BufferType type_) = 0 /* overload */;
	virtual void __cdecl setTextLocale(Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 ;
	virtual void __cdecl setTextLocales(Androidapi::Jni::Os::_di_JLocaleList locales) = 0 ;
	virtual void __cdecl setTextScaleX(float size) = 0 ;
	virtual void __cdecl setTextSize(float size) = 0 /* overload */;
	virtual void __cdecl setTextSize(int unit_, float size) = 0 /* overload */;
	virtual void __cdecl setTransformationMethod(Androidapi::Jni::Graphicscontentviewtext::_di_JTransformationMethod method) = 0 ;
	virtual void __cdecl setTypeface(Androidapi::Jni::Graphicscontentviewtext::_di_JTypeface tf, int style) = 0 /* overload */;
	virtual void __cdecl setTypeface(Androidapi::Jni::Graphicscontentviewtext::_di_JTypeface tf) = 0 /* overload */;
	virtual void __cdecl setWidth(int pixels) = 0 ;
	HIDESBASE virtual bool __cdecl showContextMenu() = 0 /* overload */;
	HIDESBASE virtual bool __cdecl showContextMenu(float x, float y) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextViewClass,_di_JTextView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextViewClass,_di_JTextView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextViewClass,_di_JTextView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{84EB5039-0F0A-420F-8AAA-1454DE4BC213}") JButtonClass  : public JTextViewClass 
{
	HIDESBASE virtual _di_JButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{72BF0D65-7D16-4B9D-B6E7-5CAF786278CC}") JButton  : public JTextView 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPointerIcon __cdecl onResolvePointerIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, int pointerIndex) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJButton : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtonClass,_di_JButton>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtonClass,_di_JButton> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJButton() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JButtonClass,_di_JButton>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJButton() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6E65B2D2-EEA5-40FA-9F02-D104EC2EABCC}") JFrameLayoutClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JFrameLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{94E79213-4DDA-45B3-B896-22E5AA59C3D3}") JFrameLayout  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl generateLayoutParams(Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual bool __cdecl getConsiderGoneChildrenWhenMeasuring() = 0 ;
	virtual bool __cdecl getMeasureAllChildren() = 0 ;
	HIDESBASE virtual void __cdecl setForegroundGravity(int foregroundGravity) = 0 ;
	virtual void __cdecl setMeasureAllChildren(bool measureAll) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFrameLayout : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayoutClass,_di_JFrameLayout>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayoutClass,_di_JFrameLayout> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFrameLayout() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayoutClass,_di_JFrameLayout>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFrameLayout() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{296A6CD9-C5FB-4267-8E0A-FE5E3D63984F}") JCalendarViewClass  : public JFrameLayoutClass 
{
	HIDESBASE virtual _di_JCalendarView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JCalendarView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JCalendarView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JCalendarView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{EC25F4BA-2D6E-4641-9C00-CEBFE6C66BA8}") JCalendarView  : public JFrameLayout 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual __int64 __cdecl getDate() = 0 ;
	virtual int __cdecl getDateTextAppearance() = 0 ;
	virtual int __cdecl getFirstDayOfWeek() = 0 ;
	virtual int __cdecl getFocusedMonthDateColor() = 0 ;
	virtual __int64 __cdecl getMaxDate() = 0 ;
	virtual __int64 __cdecl getMinDate() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getSelectedDateVerticalBar() = 0 ;
	virtual int __cdecl getSelectedWeekBackgroundColor() = 0 ;
	virtual bool __cdecl getShowWeekNumber() = 0 ;
	virtual int __cdecl getShownWeekCount() = 0 ;
	virtual int __cdecl getUnfocusedMonthDateColor() = 0 ;
	virtual int __cdecl getWeekDayTextAppearance() = 0 ;
	virtual int __cdecl getWeekNumberColor() = 0 ;
	virtual int __cdecl getWeekSeparatorLineColor() = 0 ;
	virtual void __cdecl setDate(__int64 date) = 0 /* overload */;
	virtual void __cdecl setDate(__int64 date, bool animate, bool center) = 0 /* overload */;
	virtual void __cdecl setDateTextAppearance(int resourceId) = 0 ;
	virtual void __cdecl setFirstDayOfWeek(int firstDayOfWeek) = 0 ;
	virtual void __cdecl setFocusedMonthDateColor(int color) = 0 ;
	virtual void __cdecl setMaxDate(__int64 maxDate) = 0 ;
	virtual void __cdecl setMinDate(__int64 minDate) = 0 ;
	virtual void __cdecl setOnDateChangeListener(_di_JCalendarView_OnDateChangeListener listener) = 0 ;
	virtual void __cdecl setSelectedDateVerticalBar(int resourceId) = 0 /* overload */;
	virtual void __cdecl setSelectedDateVerticalBar(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 /* overload */;
	virtual void __cdecl setSelectedWeekBackgroundColor(int color) = 0 ;
	virtual void __cdecl setShowWeekNumber(bool showWeekNumber) = 0 ;
	virtual void __cdecl setShownWeekCount(int count) = 0 ;
	virtual void __cdecl setUnfocusedMonthDateColor(int color) = 0 ;
	virtual void __cdecl setWeekDayTextAppearance(int resourceId) = 0 ;
	virtual void __cdecl setWeekNumberColor(int color) = 0 ;
	virtual void __cdecl setWeekSeparatorLineColor(int color) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCalendarView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarViewClass,_di_JCalendarView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarViewClass,_di_JCalendarView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCalendarView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarViewClass,_di_JCalendarView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCalendarView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1A59348E-9069-4AC0-993A-0621FE1AF5DE}") JCalendarView_OnDateChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8BFCE3F3-F4AF-4758-A036-7C63196D41A4}") JCalendarView_OnDateChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onSelectedDayChange(_di_JCalendarView view, int year, int month, int dayOfMonth) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCalendarView_OnDateChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarView_OnDateChangeListenerClass,_di_JCalendarView_OnDateChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarView_OnDateChangeListenerClass,_di_JCalendarView_OnDateChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCalendarView_OnDateChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCalendarView_OnDateChangeListenerClass,_di_JCalendarView_OnDateChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCalendarView_OnDateChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A00ADD78-B9E3-4FE6-8480-89B52EEA6942}") JCompoundButtonClass  : public JButtonClass 
{
	HIDESBASE virtual _di_JCompoundButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JCompoundButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JCompoundButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JCompoundButton __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{365F9429-E6D3-4BE4-B7A5-F5B27AB3861F}") JCompoundButton  : public JButton 
{
	HIDESBASE virtual void __cdecl drawableHotspotChanged(float x, float y) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getButtonDrawable() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getButtonTintList() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode __cdecl getButtonTintMode() = 0 ;
	HIDESBASE virtual int __cdecl getCompoundPaddingLeft() = 0 ;
	HIDESBASE virtual int __cdecl getCompoundPaddingRight() = 0 ;
	virtual bool __cdecl isChecked() = 0 ;
	HIDESBASE virtual void __cdecl jumpDrawablesToCurrentState() = 0 ;
	HIDESBASE virtual void __cdecl onRestoreInstanceState(Androidapi::Jni::Os::_di_JParcelable state) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelable __cdecl onSaveInstanceState() = 0 ;
	HIDESBASE virtual bool __cdecl performClick() = 0 ;
	virtual void __cdecl setButtonDrawable(int resId) = 0 /* overload */;
	virtual void __cdecl setButtonDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 /* overload */;
	virtual void __cdecl setButtonTintList(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList tint) = 0 ;
	virtual void __cdecl setButtonTintMode(Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode tintMode) = 0 ;
	virtual void __cdecl setChecked(bool checked) = 0 ;
	virtual void __cdecl setOnCheckedChangeListener(_di_JCompoundButton_OnCheckedChangeListener listener) = 0 ;
	virtual void __cdecl toggle() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCompoundButton : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButtonClass,_di_JCompoundButton>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButtonClass,_di_JCompoundButton> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCompoundButton() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButtonClass,_di_JCompoundButton>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCompoundButton() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{06626864-A73D-44E0-B6FA-FFD166116BC0}") JCompoundButton_OnCheckedChangeListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{1B3374AF-2381-42F4-AE22-2CEB920B0C76}") JCompoundButton_OnCheckedChangeListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCheckedChanged(_di_JCompoundButton buttonView, bool isChecked) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCompoundButton_OnCheckedChangeListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButton_OnCheckedChangeListenerClass,_di_JCompoundButton_OnCheckedChangeListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButton_OnCheckedChangeListenerClass,_di_JCompoundButton_OnCheckedChangeListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCompoundButton_OnCheckedChangeListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCompoundButton_OnCheckedChangeListenerClass,_di_JCompoundButton_OnCheckedChangeListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCompoundButton_OnCheckedChangeListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1896B41D-1252-4F3F-BDE6-0D510F6DF7E1}") JDatePickerClass  : public JFrameLayoutClass 
{
	HIDESBASE virtual _di_JDatePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JDatePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JDatePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JDatePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{C7B0DF58-E364-4312-A6AC-15B036CEE969}") JDatePicker  : public JFrameLayout 
{
	HIDESBASE virtual void __cdecl autofill(Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue value) = 0 ;
	HIDESBASE virtual void __cdecl dispatchProvideAutofillStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure, int flags) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual int __cdecl getAutofillType() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue __cdecl getAutofillValue() = 0 ;
	virtual _di_JCalendarView __cdecl getCalendarView() = 0 ;
	virtual bool __cdecl getCalendarViewShown() = 0 ;
	virtual int __cdecl getDayOfMonth() = 0 ;
	virtual int __cdecl getFirstDayOfWeek() = 0 ;
	virtual __int64 __cdecl getMaxDate() = 0 ;
	virtual __int64 __cdecl getMinDate() = 0 ;
	virtual int __cdecl getMonth() = 0 ;
	virtual bool __cdecl getSpinnersShown() = 0 ;
	virtual int __cdecl getYear() = 0 ;
	virtual void __cdecl init(int year, int monthOfYear, int dayOfMonth, _di_JDatePicker_OnDateChangedListener onDateChangedListener) = 0 /* overload */;
	HIDESBASE virtual bool __cdecl isEnabled() = 0 ;
	virtual void __cdecl setCalendarViewShown(bool shown) = 0 ;
	HIDESBASE virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setFirstDayOfWeek(int firstDayOfWeek) = 0 ;
	virtual void __cdecl setMaxDate(__int64 maxDate) = 0 ;
	virtual void __cdecl setMinDate(__int64 minDate) = 0 ;
	virtual void __cdecl setOnDateChangedListener(_di_JDatePicker_OnDateChangedListener onDateChangedListener) = 0 ;
	virtual void __cdecl setSpinnersShown(bool shown) = 0 ;
	virtual void __cdecl updateDate(int year, int month, int dayOfMonth) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePickerClass,_di_JDatePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePickerClass,_di_JDatePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePickerClass,_di_JDatePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1D607822-DB13-4D3A-987A-1142465633A3}") JDatePicker_OnDateChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{33E320F2-69E9-4349-8B66-FA8C424FFB03}") JDatePicker_OnDateChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDateChanged(_di_JDatePicker view, int year, int monthOfYear, int dayOfMonth) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatePicker_OnDateChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePicker_OnDateChangedListenerClass,_di_JDatePicker_OnDateChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePicker_OnDateChangedListenerClass,_di_JDatePicker_OnDateChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatePicker_OnDateChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatePicker_OnDateChangedListenerClass,_di_JDatePicker_OnDateChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatePicker_OnDateChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A1E1255C-8FC9-449A-A886-57ABA315C3E3}") JEditTextClass  : public JTextViewClass 
{
	HIDESBASE virtual _di_JEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JEditText __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{53E7BC41-9ED8-4863-B9A3-B8D23DA1794F}") JEditText  : public JTextView 
{
	virtual void __cdecl extendSelection(int index) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual bool __cdecl getFreezesText() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JEditable __cdecl getText() = 0 ;
	virtual void __cdecl selectAll() = 0 ;
	HIDESBASE virtual void __cdecl setEllipsize(Androidapi::Jni::Graphicscontentviewtext::_di_JTextUtils_TruncateAt ellipsis) = 0 ;
	virtual void __cdecl setSelection(int start, int stop) = 0 /* overload */;
	virtual void __cdecl setSelection(int index) = 0 /* overload */;
	HIDESBASE virtual void __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence text, _di_JTextView_BufferType type_) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJEditText : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEditTextClass,_di_JEditText>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEditTextClass,_di_JEditText> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJEditText() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JEditTextClass,_di_JEditText>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJEditText() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F5F1E63E-8329-4F5C-8096-D369E2650637}") JFrameLayout_LayoutParamsClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParamsClass 
{
	virtual int __cdecl _GetUNSPECIFIED_GRAVITY() = 0 ;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(int width, int height, int gravity) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_MarginLayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JFrameLayout_LayoutParams __cdecl init(_di_JFrameLayout_LayoutParams source) = 0 /* overload */;
	__property int UNSPECIFIED_GRAVITY = {read=_GetUNSPECIFIED_GRAVITY};
};

__interface  INTERFACE_UUID("{01468B94-1F5E-4E57-990C-909B89476072}") JFrameLayout_LayoutParams  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParams 
{
	virtual int __cdecl _Getgravity() = 0 ;
	virtual void __cdecl _Setgravity(int Value) = 0 ;
	__property int gravity = {read=_Getgravity, write=_Setgravity};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFrameLayout_LayoutParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayout_LayoutParamsClass,_di_JFrameLayout_LayoutParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayout_LayoutParamsClass,_di_JFrameLayout_LayoutParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFrameLayout_LayoutParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFrameLayout_LayoutParamsClass,_di_JFrameLayout_LayoutParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFrameLayout_LayoutParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0BBBCB19-E4B1-4147-99A8-9DA0AEEEA7AD}") JImageViewClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewClass 
{
	HIDESBASE virtual _di_JImageView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JImageView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JImageView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JImageView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{21CA0CF7-F857-4E53-9E2B-A12903F4216E}") JImageView  : public Androidapi::Jni::Graphicscontentviewtext::JView 
{
	virtual void __cdecl clearColorFilter() = 0 ;
	HIDESBASE virtual void __cdecl drawableHotspotChanged(float x, float y) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual bool __cdecl getAdjustViewBounds() = 0 ;
	HIDESBASE virtual int __cdecl getBaseline() = 0 ;
	virtual bool __cdecl getBaselineAlignBottom() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorFilter __cdecl getColorFilter() = 0 ;
	virtual bool __cdecl getCropToPadding() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getDrawable() = 0 ;
	virtual int __cdecl getImageAlpha() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JMatrix __cdecl getImageMatrix() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getImageTintList() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode __cdecl getImageTintMode() = 0 ;
	virtual int __cdecl getMaxHeight() = 0 ;
	virtual int __cdecl getMaxWidth() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl getScaleType() = 0 ;
	HIDESBASE virtual bool __cdecl hasOverlappingRendering() = 0 ;
	HIDESBASE virtual void __cdecl invalidateDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable dr) = 0 ;
	HIDESBASE virtual bool __cdecl isOpaque() = 0 ;
	HIDESBASE virtual void __cdecl jumpDrawablesToCurrentState() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl onCreateDrawableState(int extraSpace) = 0 ;
	HIDESBASE virtual void __cdecl onRtlPropertiesChanged(int layoutDirection) = 0 ;
	HIDESBASE virtual void __cdecl onVisibilityAggregated(bool isVisible) = 0 ;
	virtual void __cdecl setAdjustViewBounds(bool adjustViewBounds) = 0 ;
	HIDESBASE virtual void __cdecl setAlpha(int alpha) = 0 ;
	virtual void __cdecl setBaseline(int baseline) = 0 ;
	virtual void __cdecl setBaselineAlignBottom(bool aligned) = 0 ;
	virtual void __cdecl setColorFilter(int color, Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode mode) = 0 /* overload */;
	virtual void __cdecl setColorFilter(int color) = 0 /* overload */;
	virtual void __cdecl setColorFilter(Androidapi::Jni::Graphicscontentviewtext::_di_JColorFilter cf) = 0 /* overload */;
	virtual void __cdecl setCropToPadding(bool cropToPadding) = 0 ;
	virtual void __cdecl setImageAlpha(int alpha) = 0 ;
	virtual void __cdecl setImageBitmap(Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bm) = 0 ;
	virtual void __cdecl setImageDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 ;
	virtual void __cdecl setImageIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JIcon icon) = 0 ;
	virtual void __cdecl setImageLevel(int level) = 0 ;
	virtual void __cdecl setImageMatrix(Androidapi::Jni::Graphicscontentviewtext::_di_JMatrix matrix) = 0 ;
	virtual void __cdecl setImageResource(int resId) = 0 ;
	virtual void __cdecl setImageState(Androidapi::Jnibridge::TJavaArray__1<int>* state, bool merge) = 0 ;
	virtual void __cdecl setImageTintList(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList tint) = 0 ;
	virtual void __cdecl setImageTintMode(Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode tintMode) = 0 ;
	virtual void __cdecl setImageURI(Androidapi::Jni::Net::_di_Jnet_Uri uri) = 0 ;
	virtual void __cdecl setMaxHeight(int maxHeight) = 0 ;
	virtual void __cdecl setMaxWidth(int maxWidth) = 0 ;
	virtual void __cdecl setScaleType(_di_JImageView_ScaleType scaleType) = 0 ;
	HIDESBASE virtual void __cdecl setSelected(bool selected) = 0 ;
	HIDESBASE virtual void __cdecl setVisibility(int visibility) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJImageView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageViewClass,_di_JImageView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageViewClass,_di_JImageView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJImageView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageViewClass,_di_JImageView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJImageView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{37CB0769-42AF-482A-BC66-8B9D10398D26}") JImageView_ScaleTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JImageView_ScaleType __cdecl _GetCENTER() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetCENTER_CROP() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetCENTER_INSIDE() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetFIT_CENTER() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetFIT_END() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetFIT_START() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetFIT_XY() = 0 ;
	virtual _di_JImageView_ScaleType __cdecl _GetMATRIX() = 0 ;
	HIDESBASE virtual _di_JImageView_ScaleType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JImageView_ScaleType>* __cdecl values() = 0 ;
	__property _di_JImageView_ScaleType CENTER = {read=_GetCENTER};
	__property _di_JImageView_ScaleType CENTER_CROP = {read=_GetCENTER_CROP};
	__property _di_JImageView_ScaleType CENTER_INSIDE = {read=_GetCENTER_INSIDE};
	__property _di_JImageView_ScaleType FIT_CENTER = {read=_GetFIT_CENTER};
	__property _di_JImageView_ScaleType FIT_END = {read=_GetFIT_END};
	__property _di_JImageView_ScaleType FIT_START = {read=_GetFIT_START};
	__property _di_JImageView_ScaleType FIT_XY = {read=_GetFIT_XY};
	__property _di_JImageView_ScaleType MATRIX = {read=_GetMATRIX};
};

__interface  INTERFACE_UUID("{A1D4F79C-D43B-4158-B200-826C032F62A1}") JImageView_ScaleType  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJImageView_ScaleType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageView_ScaleTypeClass,_di_JImageView_ScaleType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageView_ScaleTypeClass,_di_JImageView_ScaleType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJImageView_ScaleType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JImageView_ScaleTypeClass,_di_JImageView_ScaleType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJImageView_ScaleType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EAEAF7E9-98CA-403B-A2E4-2AA56B0A3E1F}") JLinearLayoutClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	virtual int __cdecl _GetHORIZONTAL() = 0 ;
	virtual int __cdecl _GetSHOW_DIVIDER_BEGINNING() = 0 ;
	virtual int __cdecl _GetSHOW_DIVIDER_END() = 0 ;
	virtual int __cdecl _GetSHOW_DIVIDER_MIDDLE() = 0 ;
	virtual int __cdecl _GetSHOW_DIVIDER_NONE() = 0 ;
	virtual int __cdecl _GetVERTICAL() = 0 ;
	HIDESBASE virtual _di_JLinearLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	__property int HORIZONTAL = {read=_GetHORIZONTAL};
	__property int SHOW_DIVIDER_BEGINNING = {read=_GetSHOW_DIVIDER_BEGINNING};
	__property int SHOW_DIVIDER_END = {read=_GetSHOW_DIVIDER_END};
	__property int SHOW_DIVIDER_MIDDLE = {read=_GetSHOW_DIVIDER_MIDDLE};
	__property int SHOW_DIVIDER_NONE = {read=_GetSHOW_DIVIDER_NONE};
	__property int VERTICAL = {read=_GetVERTICAL};
};

__interface  INTERFACE_UUID("{903D0B13-CCC1-4012-B4A8-C24B6013F07F}") JLinearLayout  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl generateLayoutParams(Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual int __cdecl getBaseline() = 0 ;
	virtual int __cdecl getBaselineAlignedChildIndex() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getDividerDrawable() = 0 ;
	virtual int __cdecl getDividerPadding() = 0 ;
	virtual int __cdecl getGravity() = 0 ;
	virtual int __cdecl getOrientation() = 0 ;
	virtual int __cdecl getShowDividers() = 0 ;
	virtual float __cdecl getWeightSum() = 0 ;
	virtual bool __cdecl isBaselineAligned() = 0 ;
	virtual bool __cdecl isMeasureWithLargestChildEnabled() = 0 ;
	HIDESBASE virtual void __cdecl onRtlPropertiesChanged(int layoutDirection) = 0 ;
	virtual void __cdecl setBaselineAligned(bool baselineAligned) = 0 ;
	virtual void __cdecl setBaselineAlignedChildIndex(int i) = 0 ;
	virtual void __cdecl setDividerDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable divider) = 0 ;
	virtual void __cdecl setDividerPadding(int padding) = 0 ;
	virtual void __cdecl setGravity(int gravity) = 0 ;
	virtual void __cdecl setHorizontalGravity(int horizontalGravity) = 0 ;
	virtual void __cdecl setMeasureWithLargestChildEnabled(bool enabled) = 0 ;
	virtual void __cdecl setOrientation(int orientation) = 0 ;
	virtual void __cdecl setShowDividers(int showDividers) = 0 ;
	virtual void __cdecl setVerticalGravity(int verticalGravity) = 0 ;
	virtual void __cdecl setWeightSum(float weightSum) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLinearLayout : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayoutClass,_di_JLinearLayout>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayoutClass,_di_JLinearLayout> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLinearLayout() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayoutClass,_di_JLinearLayout>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLinearLayout() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F97E1053-9B59-4F9E-AB20-FFAE01213E75}") JLinearLayout_LayoutParamsClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParamsClass 
{
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(int width, int height, float weight) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams p) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_MarginLayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JLinearLayout_LayoutParams __cdecl init(_di_JLinearLayout_LayoutParams source) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D53D211C-BCB8-4B84-9F82-BBCAC65549F7}") JLinearLayout_LayoutParams  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParams 
{
	virtual int __cdecl _Getgravity() = 0 ;
	virtual void __cdecl _Setgravity(int Value) = 0 ;
	virtual float __cdecl _Getweight() = 0 ;
	virtual void __cdecl _Setweight(float Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl debug(Androidapi::Jni::Javatypes::_di_JString output) = 0 ;
	__property int gravity = {read=_Getgravity, write=_Setgravity};
	__property float weight = {read=_Getweight, write=_Setweight};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJLinearLayout_LayoutParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayout_LayoutParamsClass,_di_JLinearLayout_LayoutParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayout_LayoutParamsClass,_di_JLinearLayout_LayoutParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJLinearLayout_LayoutParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JLinearLayout_LayoutParamsClass,_di_JLinearLayout_LayoutParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJLinearLayout_LayoutParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C631AA3D-E166-4F53-8B50-A801AD94FB9C}") JListAdapterClass  : public JAdapterClass 
{
	
};

__interface  INTERFACE_UUID("{F7DEDFB9-6976-4AFF-9264-02AEC6317A7B}") JListAdapter  : public JAdapter 
{
	virtual bool __cdecl areAllItemsEnabled() = 0 ;
	virtual bool __cdecl isEnabled(int position) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJListAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListAdapterClass,_di_JListAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListAdapterClass,_di_JListAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJListAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListAdapterClass,_di_JListAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJListAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{64E52E74-CA76-451C-83EA-2A6C996C3E42}") JListViewClass  : public JAbsListViewClass 
{
	HIDESBASE virtual _di_JListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JListView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{2F533089-9B07-456B-9CCD-E37633BC3E9B}") JListView  : public JAbsListView 
{
	virtual void __cdecl addFooterView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Javatypes::_di_JObject data, bool isSelectable) = 0 /* overload */;
	virtual void __cdecl addFooterView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 /* overload */;
	virtual void __cdecl addHeaderView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Javatypes::_di_JObject data, bool isSelectable) = 0 /* overload */;
	virtual void __cdecl addHeaderView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 /* overload */;
	virtual bool __cdecl areFooterDividersEnabled() = 0 ;
	virtual bool __cdecl areHeaderDividersEnabled() = 0 ;
	HIDESBASE virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual _di_JListAdapter __cdecl getAdapter() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<__int64>* __cdecl getCheckItemIds() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getDivider() = 0 ;
	virtual int __cdecl getDividerHeight() = 0 ;
	virtual int __cdecl getFooterViewsCount() = 0 ;
	virtual int __cdecl getHeaderViewsCount() = 0 ;
	virtual bool __cdecl getItemsCanFocus() = 0 ;
	virtual int __cdecl getMaxScrollAmount() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getOverscrollFooter() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getOverscrollHeader() = 0 ;
	HIDESBASE virtual bool __cdecl isOpaque() = 0 ;
	HIDESBASE virtual void __cdecl onInitializeAccessibilityNodeInfoForItem(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, int position, Androidapi::Jni::Graphicscontentviewtext::_di_JAccessibilityNodeInfo info) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyDown(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyMultiple(int keyCode, int repeatCount, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onKeyUp(int keyCode, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual bool __cdecl removeFooterView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 ;
	virtual bool __cdecl removeHeaderView(Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 ;
	HIDESBASE virtual bool __cdecl requestChildRectangleOnScreen(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JRect rect, bool immediate) = 0 ;
	HIDESBASE virtual void __cdecl setAdapter(_di_JListAdapter adapter) = 0 ;
	HIDESBASE virtual void __cdecl setCacheColorHint(int color) = 0 ;
	virtual void __cdecl setDivider(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable divider) = 0 ;
	virtual void __cdecl setDividerHeight(int height) = 0 ;
	virtual void __cdecl setFooterDividersEnabled(bool footerDividersEnabled) = 0 ;
	virtual void __cdecl setHeaderDividersEnabled(bool headerDividersEnabled) = 0 ;
	virtual void __cdecl setItemsCanFocus(bool itemsCanFocus) = 0 ;
	virtual void __cdecl setOverscrollFooter(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable footer) = 0 ;
	virtual void __cdecl setOverscrollHeader(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable header) = 0 ;
	HIDESBASE virtual void __cdecl setRemoteViewsAdapter(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	HIDESBASE virtual void __cdecl setSelection(int position) = 0 ;
	virtual void __cdecl setSelectionAfterHeaderView() = 0 ;
	virtual void __cdecl smoothScrollByOffset(int offset) = 0 ;
	HIDESBASE virtual void __cdecl smoothScrollToPosition(int position) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJListView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListViewClass,_di_JListView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListViewClass,_di_JListView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJListView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JListViewClass,_di_JListView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJListView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D703BEFF-3652-475F-A780-B2B2C9F43D66}") JPopupWindowClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetINPUT_METHOD_FROM_FOCUSABLE() = 0 ;
	virtual int __cdecl _GetINPUT_METHOD_NEEDED() = 0 ;
	virtual int __cdecl _GetINPUT_METHOD_NOT_NEEDED() = 0 ;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JView contentView) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JView contentView, int width, int height) = 0 /* overload */;
	HIDESBASE virtual _di_JPopupWindow __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JView contentView, int width, int height, bool focusable) = 0 /* overload */;
	__property int INPUT_METHOD_FROM_FOCUSABLE = {read=_GetINPUT_METHOD_FROM_FOCUSABLE};
	__property int INPUT_METHOD_NEEDED = {read=_GetINPUT_METHOD_NEEDED};
	__property int INPUT_METHOD_NOT_NEEDED = {read=_GetINPUT_METHOD_NOT_NEEDED};
};

__interface  INTERFACE_UUID("{5D44B452-2E94-47F4-9610-F25833488A46}") JPopupWindow  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl dismiss() = 0 ;
	virtual int __cdecl getAnimationStyle() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getBackground() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getContentView() = 0 ;
	virtual float __cdecl getElevation() = 0 ;
	virtual int __cdecl getHeight() = 0 ;
	virtual int __cdecl getInputMethodMode() = 0 ;
	virtual int __cdecl getMaxAvailableHeight(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor) = 0 /* overload */;
	virtual int __cdecl getMaxAvailableHeight(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int yOffset) = 0 /* overload */;
	virtual int __cdecl getMaxAvailableHeight(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int yOffset, bool ignoreBottomDecorations) = 0 /* overload */;
	virtual bool __cdecl getOverlapAnchor() = 0 ;
	virtual int __cdecl getSoftInputMode() = 0 ;
	virtual int __cdecl getWidth() = 0 ;
	virtual int __cdecl getWindowLayoutType() = 0 ;
	virtual bool __cdecl isAboveAnchor() = 0 ;
	virtual bool __cdecl isAttachedInDecor() = 0 ;
	virtual bool __cdecl isClippingEnabled() = 0 ;
	virtual bool __cdecl isFocusable() = 0 ;
	virtual bool __cdecl isOutsideTouchable() = 0 ;
	virtual bool __cdecl isShowing() = 0 ;
	virtual bool __cdecl isSplitTouchEnabled() = 0 ;
	virtual bool __cdecl isTouchable() = 0 ;
	virtual void __cdecl setAnimationStyle(int animationStyle) = 0 ;
	virtual void __cdecl setAttachedInDecor(bool enabled) = 0 ;
	virtual void __cdecl setBackgroundDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable background) = 0 ;
	virtual void __cdecl setClippingEnabled(bool enabled) = 0 ;
	virtual void __cdecl setContentView(Androidapi::Jni::Graphicscontentviewtext::_di_JView contentView) = 0 ;
	virtual void __cdecl setElevation(float elevation) = 0 ;
	virtual void __cdecl setFocusable(bool focusable) = 0 ;
	virtual void __cdecl setHeight(int height) = 0 ;
	virtual void __cdecl setIgnoreCheekPress() = 0 ;
	virtual void __cdecl setInputMethodMode(int mode) = 0 ;
	virtual void __cdecl setOnDismissListener(_di_JPopupWindow_OnDismissListener onDismissListener) = 0 ;
	virtual void __cdecl setOutsideTouchable(bool touchable) = 0 ;
	virtual void __cdecl setOverlapAnchor(bool overlapAnchor) = 0 ;
	virtual void __cdecl setSoftInputMode(int mode) = 0 ;
	virtual void __cdecl setSplitTouchEnabled(bool enabled) = 0 ;
	virtual void __cdecl setTouchInterceptor(Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnTouchListener l) = 0 ;
	virtual void __cdecl setTouchable(bool touchable) = 0 ;
	virtual void __cdecl setWidth(int width) = 0 ;
	virtual void __cdecl setWindowLayoutMode(int widthSpec, int heightSpec) = 0 ;
	virtual void __cdecl setWindowLayoutType(int layoutType) = 0 ;
	virtual void __cdecl showAsDropDown(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor) = 0 /* overload */;
	virtual void __cdecl showAsDropDown(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int xoff, int yoff) = 0 /* overload */;
	virtual void __cdecl showAsDropDown(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int xoff, int yoff, int gravity) = 0 /* overload */;
	virtual void __cdecl showAtLocation(Androidapi::Jni::Graphicscontentviewtext::_di_JView parent, int gravity, int x, int y) = 0 ;
	virtual void __cdecl update() = 0 /* overload */;
	virtual void __cdecl update(int width, int height) = 0 /* overload */;
	virtual void __cdecl update(int x, int y, int width, int height) = 0 /* overload */;
	virtual void __cdecl update(int x, int y, int width, int height, bool force) = 0 /* overload */;
	virtual void __cdecl update(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int width, int height) = 0 /* overload */;
	virtual void __cdecl update(Androidapi::Jni::Graphicscontentviewtext::_di_JView anchor, int xoff, int yoff, int width, int height) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPopupWindow : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindowClass,_di_JPopupWindow>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindowClass,_di_JPopupWindow> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPopupWindow() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindowClass,_di_JPopupWindow>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPopupWindow() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0D8EC9E0-1E9D-4218-B811-4D795CBDEF2D}") JPopupWindow_OnDismissListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C4613C55-80EE-41CB-A235-6C002B229AED}") JPopupWindow_OnDismissListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDismiss() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPopupWindow_OnDismissListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindow_OnDismissListenerClass,_di_JPopupWindow_OnDismissListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindow_OnDismissListenerClass,_di_JPopupWindow_OnDismissListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPopupWindow_OnDismissListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPopupWindow_OnDismissListenerClass,_di_JPopupWindow_OnDismissListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPopupWindow_OnDismissListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8D562318-EFE5-4CAE-AFAA-23E36D81BA54}") JRelativeLayoutClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	virtual int __cdecl _GetABOVE() = 0 ;
	virtual int __cdecl _GetALIGN_BASELINE() = 0 ;
	virtual int __cdecl _GetALIGN_BOTTOM() = 0 ;
	virtual int __cdecl _GetALIGN_END() = 0 ;
	virtual int __cdecl _GetALIGN_LEFT() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_BOTTOM() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_END() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_LEFT() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_RIGHT() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_START() = 0 ;
	virtual int __cdecl _GetALIGN_PARENT_TOP() = 0 ;
	virtual int __cdecl _GetALIGN_RIGHT() = 0 ;
	virtual int __cdecl _GetALIGN_START() = 0 ;
	virtual int __cdecl _GetALIGN_TOP() = 0 ;
	virtual int __cdecl _GetBELOW() = 0 ;
	virtual int __cdecl _GetCENTER_HORIZONTAL() = 0 ;
	virtual int __cdecl _GetCENTER_IN_PARENT() = 0 ;
	virtual int __cdecl _GetCENTER_VERTICAL() = 0 ;
	virtual int __cdecl _GetEND_OF() = 0 ;
	virtual int __cdecl _GetLEFT_OF() = 0 ;
	virtual int __cdecl _GetRIGHT_OF() = 0 ;
	virtual int __cdecl _GetSTART_OF() = 0 ;
	virtual int __cdecl _GetTRUE() = 0 ;
	HIDESBASE virtual _di_JRelativeLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
	__property int ABOVE = {read=_GetABOVE};
	__property int ALIGN_BASELINE = {read=_GetALIGN_BASELINE};
	__property int ALIGN_BOTTOM = {read=_GetALIGN_BOTTOM};
	__property int ALIGN_END = {read=_GetALIGN_END};
	__property int ALIGN_LEFT = {read=_GetALIGN_LEFT};
	__property int ALIGN_PARENT_BOTTOM = {read=_GetALIGN_PARENT_BOTTOM};
	__property int ALIGN_PARENT_END = {read=_GetALIGN_PARENT_END};
	__property int ALIGN_PARENT_LEFT = {read=_GetALIGN_PARENT_LEFT};
	__property int ALIGN_PARENT_RIGHT = {read=_GetALIGN_PARENT_RIGHT};
	__property int ALIGN_PARENT_START = {read=_GetALIGN_PARENT_START};
	__property int ALIGN_PARENT_TOP = {read=_GetALIGN_PARENT_TOP};
	__property int ALIGN_RIGHT = {read=_GetALIGN_RIGHT};
	__property int ALIGN_START = {read=_GetALIGN_START};
	__property int ALIGN_TOP = {read=_GetALIGN_TOP};
	__property int BELOW = {read=_GetBELOW};
	__property int CENTER_HORIZONTAL = {read=_GetCENTER_HORIZONTAL};
	__property int CENTER_IN_PARENT = {read=_GetCENTER_IN_PARENT};
	__property int CENTER_VERTICAL = {read=_GetCENTER_VERTICAL};
	__property int END_OF = {read=_GetEND_OF};
	__property int LEFT_OF = {read=_GetLEFT_OF};
	__property int RIGHT_OF = {read=_GetRIGHT_OF};
	__property int START_OF = {read=_GetSTART_OF};
	__property int TRUE = {read=_GetTRUE};
};

__interface  INTERFACE_UUID("{6EBCD918-E863-4925-8C9F-5854948F05C2}") JRelativeLayout  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl generateLayoutParams(Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual int __cdecl getBaseline() = 0 ;
	virtual int __cdecl getGravity() = 0 ;
	HIDESBASE virtual void __cdecl requestLayout() = 0 ;
	virtual void __cdecl setGravity(int gravity) = 0 ;
	virtual void __cdecl setHorizontalGravity(int horizontalGravity) = 0 ;
	virtual void __cdecl setIgnoreGravity(int viewId) = 0 ;
	virtual void __cdecl setVerticalGravity(int verticalGravity) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRelativeLayout : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayoutClass,_di_JRelativeLayout>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayoutClass,_di_JRelativeLayout> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRelativeLayout() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayoutClass,_di_JRelativeLayout>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRelativeLayout() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{869D1064-F0BF-4BBC-AB67-F3354AE7D63C}") JRelativeLayout_LayoutParamsClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParamsClass 
{
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl init(int w, int h) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_MarginLayoutParams source) = 0 /* overload */;
	HIDESBASE virtual _di_JRelativeLayout_LayoutParams __cdecl init(_di_JRelativeLayout_LayoutParams source) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{FF04C65D-4845-4AA6-B259-B32A28442D8C}") JRelativeLayout_LayoutParams  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup_MarginLayoutParams 
{
	virtual bool __cdecl _GetalignWithParent() = 0 ;
	virtual void __cdecl _SetalignWithParent(bool Value) = 0 ;
	virtual void __cdecl addRule(int verb) = 0 /* overload */;
	virtual void __cdecl addRule(int verb, int subject) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl debug(Androidapi::Jni::Javatypes::_di_JString output) = 0 ;
	virtual int __cdecl getRule(int verb) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl getRules() = 0 ;
	virtual void __cdecl removeRule(int verb) = 0 ;
	HIDESBASE virtual void __cdecl resolveLayoutDirection(int layoutDirection) = 0 ;
	__property bool alignWithParent = {read=_GetalignWithParent, write=_SetalignWithParent};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRelativeLayout_LayoutParams : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayout_LayoutParamsClass,_di_JRelativeLayout_LayoutParams>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayout_LayoutParamsClass,_di_JRelativeLayout_LayoutParams> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRelativeLayout_LayoutParams() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRelativeLayout_LayoutParamsClass,_di_JRelativeLayout_LayoutParams>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRelativeLayout_LayoutParams() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5C019581-AE7F-440F-A66D-AAA4F5DBE9C2}") JRemoteViewsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JRemoteViews __cdecl init(Androidapi::Jni::Javatypes::_di_JString packageName, int layoutId) = 0 /* overload */;
	HIDESBASE virtual _di_JRemoteViews __cdecl init(_di_JRemoteViews landscape, _di_JRemoteViews portrait) = 0 /* overload */;
	HIDESBASE virtual _di_JRemoteViews __cdecl init(Androidapi::Jni::Os::_di_JParcel parcel) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{C4C8FF03-5E94-4821-9401-A3DCA8A1119A}") JRemoteViews  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addView(int viewId, _di_JRemoteViews nestedView) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl apply(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup parent) = 0 ;
	virtual _di_JRemoteViews __cdecl clone() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getLayoutId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPackage() = 0 ;
	virtual bool __cdecl onLoadClass(Androidapi::Jni::Javatypes::_di_Jlang_Class clazz) = 0 ;
	virtual void __cdecl reapply(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JView v) = 0 ;
	virtual void __cdecl removeAllViews(int viewId) = 0 ;
	virtual void __cdecl setAccessibilityTraversalAfter(int viewId, int nextId) = 0 ;
	virtual void __cdecl setAccessibilityTraversalBefore(int viewId, int nextId) = 0 ;
	virtual void __cdecl setBitmap(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap value) = 0 ;
	virtual void __cdecl setBoolean(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, bool value) = 0 ;
	virtual void __cdecl setBundle(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Os::_di_JBundle value) = 0 ;
	virtual void __cdecl setByte(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, System::Byte value) = 0 ;
	virtual void __cdecl setChar(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, System::WideChar value) = 0 ;
	virtual void __cdecl setCharSequence(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Javatypes::_di_JCharSequence value) = 0 ;
	virtual void __cdecl setChronometer(int viewId, __int64 base, Androidapi::Jni::Javatypes::_di_JString format, bool started) = 0 ;
	virtual void __cdecl setChronometerCountDown(int viewId, bool isCountDown) = 0 ;
	virtual void __cdecl setContentDescription(int viewId, Androidapi::Jni::Javatypes::_di_JCharSequence contentDescription) = 0 ;
	virtual void __cdecl setDisplayedChild(int viewId, int childIndex) = 0 ;
	virtual void __cdecl setDouble(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, double value) = 0 ;
	virtual void __cdecl setEmptyView(int viewId, int emptyViewId) = 0 ;
	virtual void __cdecl setFloat(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, float value) = 0 ;
	virtual void __cdecl setIcon(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Graphicscontentviewtext::_di_JIcon value) = 0 ;
	virtual void __cdecl setImageViewBitmap(int viewId, Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap bitmap) = 0 ;
	virtual void __cdecl setImageViewIcon(int viewId, Androidapi::Jni::Graphicscontentviewtext::_di_JIcon icon) = 0 ;
	virtual void __cdecl setImageViewResource(int viewId, int srcId) = 0 ;
	virtual void __cdecl setImageViewUri(int viewId, Androidapi::Jni::Net::_di_Jnet_Uri uri) = 0 ;
	virtual void __cdecl setInt(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, int value) = 0 ;
	virtual void __cdecl setIntent(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent value) = 0 ;
	virtual void __cdecl setLabelFor(int viewId, int labeledId) = 0 ;
	virtual void __cdecl setLong(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, __int64 value) = 0 ;
	virtual void __cdecl setOnClickFillInIntent(int viewId, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent fillInIntent) = 0 ;
	virtual void __cdecl setProgressBar(int viewId, int max, int progress, bool indeterminate) = 0 ;
	virtual void __cdecl setRelativeScrollPosition(int viewId, int offset) = 0 ;
	virtual void __cdecl setRemoteAdapter(int appWidgetId, int viewId, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual void __cdecl setRemoteAdapter(int viewId, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 /* overload */;
	virtual void __cdecl setScrollPosition(int viewId, int position) = 0 ;
	virtual void __cdecl setShort(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, short value) = 0 ;
	virtual void __cdecl setString(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setTextColor(int viewId, int color) = 0 ;
	virtual void __cdecl setTextViewCompoundDrawables(int viewId, int left, int top, int right, int bottom) = 0 ;
	virtual void __cdecl setTextViewCompoundDrawablesRelative(int viewId, int start, int top, int end_, int bottom) = 0 ;
	virtual void __cdecl setTextViewText(int viewId, Androidapi::Jni::Javatypes::_di_JCharSequence text) = 0 ;
	virtual void __cdecl setTextViewTextSize(int viewId, int units, float size) = 0 ;
	virtual void __cdecl setUri(int viewId, Androidapi::Jni::Javatypes::_di_JString methodName, Androidapi::Jni::Net::_di_Jnet_Uri value) = 0 ;
	virtual void __cdecl setViewPadding(int viewId, int left, int top, int right, int bottom) = 0 ;
	virtual void __cdecl setViewVisibility(int viewId, int visibility) = 0 ;
	virtual void __cdecl showNext(int viewId) = 0 ;
	virtual void __cdecl showPrevious(int viewId) = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJRemoteViews : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteViewsClass,_di_JRemoteViews>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteViewsClass,_di_JRemoteViews> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJRemoteViews() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JRemoteViewsClass,_di_JRemoteViews>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJRemoteViews() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ECF090FA-E2FD-4EBD-8703-621FCE93BBF3}") JScrollViewClass  : public JFrameLayoutClass 
{
	HIDESBASE virtual _di_JScrollView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JScrollView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JScrollView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JScrollView __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{583976EE-6287-4A78-8B75-27D2799348D0}") JScrollView  : public JFrameLayout 
{
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, int index) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	HIDESBASE virtual void __cdecl addView(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, int index, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup_LayoutParams params) = 0 /* overload */;
	virtual bool __cdecl arrowScroll(int direction) = 0 ;
	HIDESBASE virtual void __cdecl computeScroll() = 0 ;
	HIDESBASE virtual bool __cdecl dispatchKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	HIDESBASE virtual void __cdecl draw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas canvas) = 0 ;
	virtual bool __cdecl executeKeyEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
	virtual void __cdecl fling(int velocityY) = 0 ;
	virtual bool __cdecl fullScroll(int direction) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	virtual int __cdecl getMaxScrollAmount() = 0 ;
	virtual bool __cdecl isFillViewport() = 0 ;
	virtual bool __cdecl isSmoothScrollingEnabled() = 0 ;
	HIDESBASE virtual bool __cdecl onGenericMotionEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event) = 0 ;
	HIDESBASE virtual bool __cdecl onInterceptTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	HIDESBASE virtual bool __cdecl onNestedFling(Androidapi::Jni::Graphicscontentviewtext::_di_JView target, float velocityX, float velocityY, bool consumed) = 0 ;
	HIDESBASE virtual void __cdecl onNestedScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int dxConsumed, int dyConsumed, int dxUnconsumed, int dyUnconsumed) = 0 ;
	HIDESBASE virtual void __cdecl onNestedScrollAccepted(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int axes) = 0 ;
	HIDESBASE virtual bool __cdecl onStartNestedScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JView target, int nestedScrollAxes) = 0 ;
	HIDESBASE virtual void __cdecl onStopNestedScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JView target) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual bool __cdecl pageScroll(int direction) = 0 ;
	HIDESBASE virtual void __cdecl requestChildFocus(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JView focused) = 0 ;
	HIDESBASE virtual bool __cdecl requestChildRectangleOnScreen(Androidapi::Jni::Graphicscontentviewtext::_di_JView child, Androidapi::Jni::Graphicscontentviewtext::_di_JRect rectangle, bool immediate) = 0 ;
	HIDESBASE virtual void __cdecl requestDisallowInterceptTouchEvent(bool disallowIntercept) = 0 ;
	HIDESBASE virtual void __cdecl requestLayout() = 0 ;
	HIDESBASE virtual void __cdecl scrollTo(int x, int y) = 0 ;
	virtual void __cdecl setFillViewport(bool fillViewport) = 0 ;
	HIDESBASE virtual void __cdecl setOverScrollMode(int mode) = 0 ;
	virtual void __cdecl setSmoothScrollingEnabled(bool smoothScrollingEnabled) = 0 ;
	HIDESBASE virtual bool __cdecl shouldDelayChildPressedState() = 0 ;
	virtual void __cdecl smoothScrollBy(int dx, int dy) = 0 ;
	virtual void __cdecl smoothScrollTo(int x, int y) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScrollView : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollViewClass,_di_JScrollView>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollViewClass,_di_JScrollView> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScrollView() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollViewClass,_di_JScrollView>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScrollView() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B6534774-81A9-4C48-BB64-97570118163B}") JScrollerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JScroller __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{35B1FBEE-2281-4808-B971-93DBCCA5E7F2}") JScroller  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl abortAnimation() = 0 ;
	virtual bool __cdecl computeScrollOffset() = 0 ;
	virtual void __cdecl extendDuration(int extend) = 0 ;
	virtual void __cdecl fling(int startX, int startY, int velocityX, int velocityY, int minX, int maxX, int minY, int maxY) = 0 ;
	virtual void __cdecl forceFinished(bool finished) = 0 ;
	virtual float __cdecl getCurrVelocity() = 0 ;
	virtual int __cdecl getCurrX() = 0 ;
	virtual int __cdecl getCurrY() = 0 ;
	virtual int __cdecl getDuration() = 0 ;
	virtual int __cdecl getFinalX() = 0 ;
	virtual int __cdecl getFinalY() = 0 ;
	virtual int __cdecl getStartX() = 0 ;
	virtual int __cdecl getStartY() = 0 ;
	virtual bool __cdecl isFinished() = 0 ;
	virtual void __cdecl setFinalX(int newX) = 0 ;
	virtual void __cdecl setFinalY(int newY) = 0 ;
	virtual void __cdecl setFriction(float friction) = 0 ;
	virtual void __cdecl startScroll(int startX, int startY, int dx, int dy) = 0 /* overload */;
	virtual void __cdecl startScroll(int startX, int startY, int dx, int dy, int duration) = 0 /* overload */;
	virtual int __cdecl timePassed() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJScroller : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollerClass,_di_JScroller>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollerClass,_di_JScroller> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJScroller() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JScrollerClass,_di_JScroller>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJScroller() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{691169DF-C0EF-4E6C-8E72-E7128AE1841B}") JSpinnerAdapterClass  : public JAdapterClass 
{
	
};

__interface  INTERFACE_UUID("{68A77466-E8F0-443D-88C6-FB41DB5AB915}") JSpinnerAdapter  : public JAdapter 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getDropDownView(int position, Androidapi::Jni::Graphicscontentviewtext::_di_JView convertView, Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup parent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSpinnerAdapter : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpinnerAdapterClass,_di_JSpinnerAdapter>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpinnerAdapterClass,_di_JSpinnerAdapter> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSpinnerAdapter() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSpinnerAdapterClass,_di_JSpinnerAdapter>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSpinnerAdapter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C0D46D4E-5384-466B-94CC-0E3D668331F8}") JSwitchClass  : public JCompoundButtonClass 
{
	HIDESBASE virtual _di_JSwitch __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JSwitch __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JSwitch __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JSwitch __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{0BF56A5E-7BE7-42C3-BA4E-4A22C96F42C6}") JSwitch  : public JCompoundButton 
{
	HIDESBASE virtual void __cdecl draw(Androidapi::Jni::Graphicscontentviewtext::_di_JCanvas c) = 0 ;
	HIDESBASE virtual void __cdecl drawableHotspotChanged(float x, float y) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual int __cdecl getCompoundPaddingLeft() = 0 ;
	HIDESBASE virtual int __cdecl getCompoundPaddingRight() = 0 ;
	virtual bool __cdecl getShowText() = 0 ;
	virtual bool __cdecl getSplitTrack() = 0 ;
	virtual int __cdecl getSwitchMinWidth() = 0 ;
	virtual int __cdecl getSwitchPadding() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTextOff() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTextOn() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getThumbDrawable() = 0 ;
	virtual int __cdecl getThumbTextPadding() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getThumbTintList() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode __cdecl getThumbTintMode() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getTrackDrawable() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList __cdecl getTrackTintList() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode __cdecl getTrackTintMode() = 0 ;
	HIDESBASE virtual void __cdecl jumpDrawablesToCurrentState() = 0 ;
	virtual void __cdecl onMeasure(int widthMeasureSpec, int heightMeasureSpec) = 0 ;
	HIDESBASE virtual void __cdecl onProvideStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	HIDESBASE virtual void __cdecl setChecked(bool checked) = 0 ;
	virtual void __cdecl setShowText(bool showText) = 0 ;
	virtual void __cdecl setSplitTrack(bool splitTrack) = 0 ;
	virtual void __cdecl setSwitchMinWidth(int pixels) = 0 ;
	virtual void __cdecl setSwitchPadding(int pixels) = 0 ;
	virtual void __cdecl setSwitchTextAppearance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int resid) = 0 ;
	virtual void __cdecl setSwitchTypeface(Androidapi::Jni::Graphicscontentviewtext::_di_JTypeface tf, int style) = 0 /* overload */;
	virtual void __cdecl setSwitchTypeface(Androidapi::Jni::Graphicscontentviewtext::_di_JTypeface tf) = 0 /* overload */;
	virtual void __cdecl setTextOff(Androidapi::Jni::Javatypes::_di_JCharSequence textOff) = 0 ;
	virtual void __cdecl setTextOn(Androidapi::Jni::Javatypes::_di_JCharSequence textOn) = 0 ;
	virtual void __cdecl setThumbDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable thumb) = 0 ;
	virtual void __cdecl setThumbResource(int resId) = 0 ;
	virtual void __cdecl setThumbTextPadding(int pixels) = 0 ;
	virtual void __cdecl setThumbTintList(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList tint) = 0 ;
	virtual void __cdecl setThumbTintMode(Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode tintMode) = 0 ;
	virtual void __cdecl setTrackDrawable(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable track) = 0 ;
	virtual void __cdecl setTrackResource(int resId) = 0 ;
	virtual void __cdecl setTrackTintList(Androidapi::Jni::Graphicscontentviewtext::_di_JColorStateList tint) = 0 ;
	virtual void __cdecl setTrackTintMode(Androidapi::Jni::Graphicscontentviewtext::_di_JPorterDuff_Mode tintMode) = 0 ;
	HIDESBASE virtual void __cdecl toggle() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSwitch : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSwitchClass,_di_JSwitch>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSwitchClass,_di_JSwitch> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSwitch() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSwitchClass,_di_JSwitch>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSwitch() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7275F65A-D22F-4DB7-8B68-C7607AFCB6DC}") JTextView_BufferTypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JTextView_BufferType __cdecl _GetEDITABLE() = 0 ;
	virtual _di_JTextView_BufferType __cdecl _GetNORMAL() = 0 ;
	virtual _di_JTextView_BufferType __cdecl _GetSPANNABLE() = 0 ;
	HIDESBASE virtual _di_JTextView_BufferType __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JTextView_BufferType>* __cdecl values() = 0 ;
	__property _di_JTextView_BufferType EDITABLE = {read=_GetEDITABLE};
	__property _di_JTextView_BufferType NORMAL = {read=_GetNORMAL};
	__property _di_JTextView_BufferType SPANNABLE = {read=_GetSPANNABLE};
};

__interface  INTERFACE_UUID("{059F9BC3-E477-4961-B36D-8BEB7170D0F5}") JTextView_BufferType  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextView_BufferType : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_BufferTypeClass,_di_JTextView_BufferType>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_BufferTypeClass,_di_JTextView_BufferType> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextView_BufferType() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_BufferTypeClass,_di_JTextView_BufferType>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextView_BufferType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F1975C99-6495-441B-AE06-1BF3187DCCC8}") JTextView_OnEditorActionListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{6E2FAEE9-92A5-4592-B040-72632B17DA08}") JTextView_OnEditorActionListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onEditorAction(_di_JTextView v, int actionId, Androidapi::Jni::Graphicscontentviewtext::_di_JKeyEvent event) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTextView_OnEditorActionListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_OnEditorActionListenerClass,_di_JTextView_OnEditorActionListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_OnEditorActionListenerClass,_di_JTextView_OnEditorActionListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTextView_OnEditorActionListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTextView_OnEditorActionListenerClass,_di_JTextView_OnEditorActionListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTextView_OnEditorActionListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3061352E-39CC-4614-BF94-C3856A4ECA05}") JTimePickerClass  : public JFrameLayoutClass 
{
	HIDESBASE virtual _di_JTimePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JTimePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JTimePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JTimePicker __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{BC21C49B-9018-4962-93F6-7D8FC5E254F5}") JTimePicker  : public JFrameLayout 
{
	HIDESBASE virtual void __cdecl autofill(Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue value) = 0 ;
	HIDESBASE virtual void __cdecl dispatchProvideAutofillStructure(Androidapi::Jni::Graphicscontentviewtext::_di_JViewStructure structure, int flags) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getAccessibilityClassName() = 0 ;
	HIDESBASE virtual int __cdecl getAutofillType() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAutofillValue __cdecl getAutofillValue() = 0 ;
	HIDESBASE virtual int __cdecl getBaseline() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInteger __cdecl getCurrentHour() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInteger __cdecl getCurrentMinute() = 0 ;
	virtual int __cdecl getHour() = 0 ;
	virtual int __cdecl getMinute() = 0 ;
	virtual bool __cdecl is24HourView() = 0 ;
	HIDESBASE virtual bool __cdecl isEnabled() = 0 ;
	virtual void __cdecl setCurrentHour(Androidapi::Jni::Javatypes::_di_JInteger currentHour) = 0 ;
	virtual void __cdecl setCurrentMinute(Androidapi::Jni::Javatypes::_di_JInteger currentMinute) = 0 ;
	HIDESBASE virtual void __cdecl setEnabled(bool enabled) = 0 ;
	virtual void __cdecl setHour(int hour) = 0 ;
	virtual void __cdecl setIs24HourView(Androidapi::Jni::Javatypes::_di_JBoolean is24HourView) = 0 ;
	virtual void __cdecl setMinute(int minute) = 0 ;
	virtual void __cdecl setOnTimeChangedListener(_di_JTimePicker_OnTimeChangedListener onTimeChangedListener) = 0 ;
	virtual bool __cdecl validateInput() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTimePicker : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePickerClass,_di_JTimePicker>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePickerClass,_di_JTimePicker> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTimePicker() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePickerClass,_di_JTimePicker>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTimePicker() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{72F8448B-20CE-4BE8-9B35-B4F2C0677091}") JTimePicker_OnTimeChangedListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{201D381C-01E8-4104-BE53-7DD32EB514C7}") JTimePicker_OnTimeChangedListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onTimeChanged(_di_JTimePicker view, int hourOfDay, int minute) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTimePicker_OnTimeChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePicker_OnTimeChangedListenerClass,_di_JTimePicker_OnTimeChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePicker_OnTimeChangedListenerClass,_di_JTimePicker_OnTimeChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTimePicker_OnTimeChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTimePicker_OnTimeChangedListenerClass,_di_JTimePicker_OnTimeChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTimePicker_OnTimeChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D06A7EAF-EE60-4F55-A3EA-E7B0B37EC7CB}") JToastClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetLENGTH_LONG() = 0 ;
	virtual int __cdecl _GetLENGTH_SHORT() = 0 ;
	HIDESBASE virtual _di_JToast __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual _di_JToast __cdecl makeText(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JCharSequence text, int duration) = 0 /* overload */;
	virtual _di_JToast __cdecl makeText(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int resId, int duration) = 0 /* overload */;
	__property int LENGTH_LONG = {read=_GetLENGTH_LONG};
	__property int LENGTH_SHORT = {read=_GetLENGTH_SHORT};
};

__interface  INTERFACE_UUID("{410DDA5F-7D4B-415E-8BE4-F545D331176C}") JToast  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl cancel() = 0 ;
	virtual int __cdecl getDuration() = 0 ;
	virtual int __cdecl getGravity() = 0 ;
	virtual float __cdecl getHorizontalMargin() = 0 ;
	virtual float __cdecl getVerticalMargin() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __cdecl getView() = 0 ;
	virtual int __cdecl getXOffset() = 0 ;
	virtual int __cdecl getYOffset() = 0 ;
	virtual void __cdecl setDuration(int duration) = 0 ;
	virtual void __cdecl setGravity(int gravity, int xOffset, int yOffset) = 0 ;
	virtual void __cdecl setMargin(float horizontalMargin, float verticalMargin) = 0 ;
	virtual void __cdecl setText(int resId) = 0 /* overload */;
	virtual void __cdecl setText(Androidapi::Jni::Javatypes::_di_JCharSequence s) = 0 /* overload */;
	virtual void __cdecl setView(Androidapi::Jni::Graphicscontentviewtext::_di_JView view) = 0 ;
	virtual void __cdecl show() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJToast : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJToast() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToastClass,_di_JToast>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJToast() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1CB20DE3-2F6E-42CC-8FC8-BB5E27FFF510}") JToolbarClass  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroupClass 
{
	HIDESBASE virtual _di_JToolbar __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 /* overload */;
	HIDESBASE virtual _di_JToolbar __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs) = 0 /* overload */;
	HIDESBASE virtual _di_JToolbar __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr) = 0 /* overload */;
	HIDESBASE virtual _di_JToolbar __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Util::_di_JAttributeSet attrs, int defStyleAttr, int defStyleRes) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D338BDF9-DC9C-4325-A04D-642A6D7F4FBC}") JToolbar  : public Androidapi::Jni::Graphicscontentviewtext::JViewGroup 
{
	virtual void __cdecl collapseActionView() = 0 ;
	virtual void __cdecl dismissPopupMenus() = 0 ;
	virtual int __cdecl getContentInsetEnd() = 0 ;
	virtual int __cdecl getContentInsetEndWithActions() = 0 ;
	virtual int __cdecl getContentInsetLeft() = 0 ;
	virtual int __cdecl getContentInsetRight() = 0 ;
	virtual int __cdecl getContentInsetStart() = 0 ;
	virtual int __cdecl getContentInsetStartWithNavigation() = 0 ;
	virtual int __cdecl getCurrentContentInsetEnd() = 0 ;
	virtual int __cdecl getCurrentContentInsetLeft() = 0 ;
	virtual int __cdecl getCurrentContentInsetRight() = 0 ;
	virtual int __cdecl getCurrentContentInsetStart() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getLogo() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getLogoDescription() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JMenu __cdecl getMenu() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getNavigationContentDescription() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getNavigationIcon() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable __cdecl getOverflowIcon() = 0 ;
	virtual int __cdecl getPopupTheme() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getSubtitle() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getTitle() = 0 ;
	virtual int __cdecl getTitleMarginBottom() = 0 ;
	virtual int __cdecl getTitleMarginEnd() = 0 ;
	virtual int __cdecl getTitleMarginStart() = 0 ;
	virtual int __cdecl getTitleMarginTop() = 0 ;
	virtual bool __cdecl hasExpandedActionView() = 0 ;
	virtual bool __cdecl hideOverflowMenu() = 0 ;
	virtual void __cdecl inflateMenu(int resId) = 0 ;
	virtual bool __cdecl isOverflowMenuShowing() = 0 ;
	HIDESBASE virtual void __cdecl onRtlPropertiesChanged(int layoutDirection) = 0 ;
	HIDESBASE virtual bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent ev) = 0 ;
	virtual void __cdecl setContentInsetEndWithActions(int insetEndWithActions) = 0 ;
	virtual void __cdecl setContentInsetStartWithNavigation(int insetStartWithNavigation) = 0 ;
	virtual void __cdecl setContentInsetsAbsolute(int contentInsetLeft, int contentInsetRight) = 0 ;
	virtual void __cdecl setContentInsetsRelative(int contentInsetStart, int contentInsetEnd) = 0 ;
	virtual void __cdecl setLogo(int resId) = 0 /* overload */;
	virtual void __cdecl setLogo(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable drawable) = 0 /* overload */;
	virtual void __cdecl setLogoDescription(int resId) = 0 /* overload */;
	virtual void __cdecl setLogoDescription(Androidapi::Jni::Javatypes::_di_JCharSequence description) = 0 /* overload */;
	virtual void __cdecl setNavigationContentDescription(int resId) = 0 /* overload */;
	virtual void __cdecl setNavigationContentDescription(Androidapi::Jni::Javatypes::_di_JCharSequence description) = 0 /* overload */;
	virtual void __cdecl setNavigationIcon(int resId) = 0 /* overload */;
	virtual void __cdecl setNavigationIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 /* overload */;
	virtual void __cdecl setNavigationOnClickListener(Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnClickListener listener) = 0 ;
	virtual void __cdecl setOnMenuItemClickListener(_di_JToolbar_OnMenuItemClickListener listener) = 0 ;
	virtual void __cdecl setOverflowIcon(Androidapi::Jni::Graphicscontentviewtext::_di_JDrawable icon) = 0 ;
	virtual void __cdecl setPopupTheme(int resId) = 0 ;
	virtual void __cdecl setSubtitle(int resId) = 0 /* overload */;
	virtual void __cdecl setSubtitle(Androidapi::Jni::Javatypes::_di_JCharSequence subtitle) = 0 /* overload */;
	virtual void __cdecl setSubtitleTextAppearance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int resId) = 0 ;
	virtual void __cdecl setSubtitleTextColor(int color) = 0 ;
	virtual void __cdecl setTitle(int resId) = 0 /* overload */;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 /* overload */;
	virtual void __cdecl setTitleMargin(int start, int top, int end_, int bottom) = 0 ;
	virtual void __cdecl setTitleMarginBottom(int margin) = 0 ;
	virtual void __cdecl setTitleMarginEnd(int margin) = 0 ;
	virtual void __cdecl setTitleMarginStart(int margin) = 0 ;
	virtual void __cdecl setTitleMarginTop(int margin) = 0 ;
	virtual void __cdecl setTitleTextAppearance(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, int resId) = 0 ;
	virtual void __cdecl setTitleTextColor(int color) = 0 ;
	virtual bool __cdecl showOverflowMenu() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJToolbar : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbarClass,_di_JToolbar>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbarClass,_di_JToolbar> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJToolbar() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbarClass,_di_JToolbar>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJToolbar() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{906D5CB5-5B59-455F-82B3-023A7610849F}") JToolbar_OnMenuItemClickListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B997AA5D-5096-46A3-9194-5196C1A74673}") JToolbar_OnMenuItemClickListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl onMenuItemClick(Androidapi::Jni::Graphicscontentviewtext::_di_JMenuItem item) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJToolbar_OnMenuItemClickListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbar_OnMenuItemClickListenerClass,_di_JToolbar_OnMenuItemClickListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbar_OnMenuItemClickListenerClass,_di_JToolbar_OnMenuItemClickListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJToolbar_OnMenuItemClickListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JToolbar_OnMenuItemClickListenerClass,_di_JToolbar_OnMenuItemClickListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJToolbar_OnMenuItemClickListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Widget */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_WIDGET)
using namespace Androidapi::Jni::Widget;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_WidgetHPP
