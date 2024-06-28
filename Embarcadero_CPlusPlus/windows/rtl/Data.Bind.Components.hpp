// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.Components.pas' rev: 34.00 (Windows)

#ifndef Data_Bind_ComponentsHPP
#define Data_Bind_ComponentsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.Bind.Components"

namespace Data
{
namespace Bind
{
namespace Components
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBasicBindComponent;
class DELPHICLASS TContainedBindComponent;
__interface DELPHIINTERFACE IBindMemberChange;
typedef System::DelphiInterface<IBindMemberChange> _di_IBindMemberChange;
class DELPHICLASS TCommonBindComponent;
__interface DELPHIINTERFACE IDependencyList;
typedef System::DelphiInterface<IDependencyList> _di_IDependencyList;
class DELPHICLASS TCustomBindingsList;
class DELPHICLASS TBindingsListEnumerator;
class DELPHICLASS TDependencyList;
class DELPHICLASS TDependency;
class DELPHICLASS TBindingsList;
class DELPHICLASS TActivatedContainedBindComponent;
class DELPHICLASS TExpressionsBindComponent;
__interface DELPHIINTERFACE IBindActivate;
typedef System::DelphiInterface<IBindActivate> _di_IBindActivate;
class DELPHICLASS TBaseBindExpression;
class DELPHICLASS TCustomBindExpression;
class DELPHICLASS TBindExpression;
class DELPHICLASS TCustomBindExprItems;
class DELPHICLASS TBindExprItems;
__interface DELPHIINTERFACE IBindNavigator;
typedef System::DelphiInterface<IBindNavigator> _di_IBindNavigator;
__interface DELPHIINTERFACE IScopeRecordEnumerator;
typedef System::DelphiInterface<IScopeRecordEnumerator> _di_IScopeRecordEnumerator;
__interface DELPHIINTERFACE IScopeRecordControlUpdator;
typedef System::DelphiInterface<IScopeRecordControlUpdator> _di_IScopeRecordControlUpdator;
__interface DELPHIINTERFACE TValueCallback;
typedef System::DelphiInterface<TValueCallback> _di_TValueCallback;
__interface DELPHIINTERFACE IScopeRecordEnumeratorEvalShortcut;
typedef System::DelphiInterface<IScopeRecordEnumeratorEvalShortcut> _di_IScopeRecordEnumeratorEvalShortcut;
__interface DELPHIINTERFACE IScopeRecordEnumeratorCount;
typedef System::DelphiInterface<IScopeRecordEnumeratorCount> _di_IScopeRecordEnumeratorCount;
__interface DELPHIINTERFACE IScopeRecordEnumeratorStatus;
typedef System::DelphiInterface<IScopeRecordEnumeratorStatus> _di_IScopeRecordEnumeratorStatus;
__interface DELPHIINTERFACE IScopeRecordEnumerable;
typedef System::DelphiInterface<IScopeRecordEnumerable> _di_IScopeRecordEnumerable;
__interface DELPHIINTERFACE IScopeRecordEnumerableBuffered;
typedef System::DelphiInterface<IScopeRecordEnumerableBuffered> _di_IScopeRecordEnumerableBuffered;
__interface DELPHIINTERFACE IScopeCurrentRecord;
typedef System::DelphiInterface<IScopeCurrentRecord> _di_IScopeCurrentRecord;
__interface DELPHIINTERFACE IScopeGetRecord;
typedef System::DelphiInterface<IScopeGetRecord> _di_IScopeGetRecord;
__interface DELPHIINTERFACE IScopeLookup;
typedef System::DelphiInterface<IScopeLookup> _di_IScopeLookup;
__interface DELPHIINTERFACE IScopeLocate;
typedef System::DelphiInterface<IScopeLocate> _di_IScopeLocate;
__interface DELPHIINTERFACE IScopeNavigatorUpdates;
typedef System::DelphiInterface<IScopeNavigatorUpdates> _di_IScopeNavigatorUpdates;
__interface DELPHIINTERFACE IScopeBuffer;
typedef System::DelphiInterface<IScopeBuffer> _di_IScopeBuffer;
__interface DELPHIINTERFACE IBindLink;
typedef System::DelphiInterface<IBindLink> _di_IBindLink;
__interface DELPHIINTERFACE IBindPosition;
typedef System::DelphiInterface<IBindPosition> _di_IBindPosition;
__interface DELPHIINTERFACE IBindTrack;
typedef System::DelphiInterface<IBindTrack> _di_IBindTrack;
__interface DELPHIINTERFACE IBindControlValue;
typedef System::DelphiInterface<IBindControlValue> _di_IBindControlValue;
__interface DELPHIINTERFACE IBindListUpdate;
typedef System::DelphiInterface<IBindListUpdate> _di_IBindListUpdate;
__interface DELPHIINTERFACE IBindListRefresh;
typedef System::DelphiInterface<IBindListRefresh> _di_IBindListRefresh;
__interface DELPHIINTERFACE IBindListRefreshing;
typedef System::DelphiInterface<IBindListRefreshing> _di_IBindListRefreshing;
__interface DELPHIINTERFACE IBindLayoutChanged;
typedef System::DelphiInterface<IBindLayoutChanged> _di_IBindLayoutChanged;
__interface DELPHIINTERFACE TFormatCallback;
typedef System::DelphiInterface<TFormatCallback> _di_TFormatCallback;
__interface DELPHIINTERFACE TQueryBreakCallback;
typedef System::DelphiInterface<TQueryBreakCallback> _di_TQueryBreakCallback;
__interface DELPHIINTERFACE IBindCheckBoxEditor;
typedef System::DelphiInterface<IBindCheckBoxEditor> _di_IBindCheckBoxEditor;
__interface DELPHIINTERFACE IBindDateTimeEditEditor;
typedef System::DelphiInterface<IBindDateTimeEditEditor> _di_IBindDateTimeEditEditor;
__interface DELPHIINTERFACE IBindTimeEditEditor;
typedef System::DelphiInterface<IBindTimeEditEditor> _di_IBindTimeEditEditor;
__interface DELPHIINTERFACE IBindFillControlMembers;
typedef System::DelphiInterface<IBindFillControlMembers> _di_IBindFillControlMembers;
__interface DELPHIINTERFACE IBindListEditorCommon;
typedef System::DelphiInterface<IBindListEditorCommon> _di_IBindListEditorCommon;
__interface DELPHIINTERFACE IBindListGroupEditor;
typedef System::DelphiInterface<IBindListGroupEditor> _di_IBindListGroupEditor;
__interface DELPHIINTERFACE IBindListSynchEditor;
typedef System::DelphiInterface<IBindListSynchEditor> _di_IBindListSynchEditor;
__interface DELPHIINTERFACE IBindListItemIndexEditor;
typedef System::DelphiInterface<IBindListItemIndexEditor> _di_IBindListItemIndexEditor;
__interface DELPHIINTERFACE IBindListEditorItem;
typedef System::DelphiInterface<IBindListEditorItem> _di_IBindListEditorItem;
__interface DELPHIINTERFACE IBindListEditor;
typedef System::DelphiInterface<IBindListEditor> _di_IBindListEditor;
__interface DELPHIINTERFACE IBindListEditorEvalShortcut;
typedef System::DelphiInterface<IBindListEditorEvalShortcut> _di_IBindListEditorEvalShortcut;
__interface DELPHIINTERFACE IBindListLookupEditor;
typedef System::DelphiInterface<IBindListLookupEditor> _di_IBindListLookupEditor;
__interface DELPHIINTERFACE TBindGridOnCallbackEvaluateFormat;
typedef System::DelphiInterface<TBindGridOnCallbackEvaluateFormat> _di_TBindGridOnCallbackEvaluateFormat;
__interface DELPHIINTERFACE IBindListVirtualEditor;
typedef System::DelphiInterface<IBindListVirtualEditor> _di_IBindListVirtualEditor;
__interface DELPHIINTERFACE IBindListRecordVirtualEditor;
typedef System::DelphiInterface<IBindListRecordVirtualEditor> _di_IBindListRecordVirtualEditor;
__interface DELPHIINTERFACE IBindListVirtualEditorScope;
typedef System::DelphiInterface<IBindListVirtualEditorScope> _di_IBindListVirtualEditorScope;
__interface DELPHIINTERFACE IBindGridEditor;
typedef System::DelphiInterface<IBindGridEditor> _di_IBindGridEditor;
__interface DELPHIINTERFACE IBindLinkColumns;
typedef System::DelphiInterface<IBindLinkColumns> _di_IBindLinkColumns;
class DELPHICLASS TCustomBindPosition;
class DELPHICLASS TBindPosition;
class DELPHICLASS TCustomBindControlValue;
class DELPHICLASS TBindControlValue;
class DELPHICLASS TCustomBindList;
class DELPHICLASS TBindList;
class DELPHICLASS TCustomBindListLookup;
class DELPHICLASS TCustomBindListLink;
class DELPHICLASS TBindListLink;
class DELPHICLASS TCustomBindLink;
class DELPHICLASS TBindLink;
template<typename T> class DELPHICLASS TCollectionEnumerator__1;
class DELPHICLASS TFillBreakGroupItem;
class DELPHICLASS TFillBreakGroups;
class DELPHICLASS TEvalEnumeratorToEditor;
class DELPHICLASS TEvalEnumerator;
class DELPHICLASS TCustomBindGridList;
class DELPHICLASS TBindGridList;
class DELPHICLASS TCustomBindGridListLookup;
class DELPHICLASS TCustomBindGridListLink;
class DELPHICLASS TCustomBindGridLink;
class DELPHICLASS TBindGridLink;
class DELPHICLASS TColumnFormatExpressionItem;
class DELPHICLASS TColumnLinkExpressionItem;
class DELPHICLASS TColumnFormatExpressions;
class DELPHICLASS TColumnLinkExpressions;
class DELPHICLASS TExpressionItem;
class DELPHICLASS TExpressionItemDir;
class DELPHICLASS TBindCompExpressionCollection;
class DELPHICLASS TExpressions;
class DELPHICLASS TExpressionsDir;
class DELPHICLASS TExpressionDirEnumerator;
class DELPHICLASS TBindComponentDelegate;
class DELPHICLASS TLinkControlDelegate;
class DELPHICLASS TLinkControlToFieldDelegate;
class DELPHICLASS TCustomLinkControlToField;
class DELPHICLASS TLinkControlToField;
class DELPHICLASS TFormatExpressionItem;
__interface DELPHIINTERFACE IControlEditorName;
typedef System::DelphiInterface<IControlEditorName> _di_IControlEditorName;
class DELPHICLASS TFormatExpressions;
class DELPHICLASS TCustomLinkFillControlToField;
class DELPHICLASS TLinkFillControlToField;
class DELPHICLASS TCustomLinkListControlToField;
class DELPHICLASS TLinkListControlToField;
class DELPHICLASS TLinkPropertyToFieldDelegate;
class DELPHICLASS TCustomLinkPropertyToField;
class DELPHICLASS TLinkPropertyToField;
class DELPHICLASS TCustomLinkControlToProperty;
class DELPHICLASS TLinkControlToProperty;
class DELPHICLASS TCustomLinkFillControlToProperty;
class DELPHICLASS TLinkFillControlToProperty;
class DELPHICLASS TBindArtifactItem;
class DELPHICLASS TScopeMappingItem;
class DELPHICLASS TScopeMappingsEnumerator;
class DELPHICLASS TScopeMappings;
class DELPHICLASS TBindArtifacts;
class DELPHICLASS TMethods;
class DELPHICLASS TOutputConverters;
__interface DELPHIINTERFACE IScopeComponent;
typedef System::DelphiInterface<IScopeComponent> _di_IScopeComponent;
__interface DELPHIINTERFACE IScopeExpressions;
typedef System::DelphiInterface<IScopeExpressions> _di_IScopeExpressions;
__interface DELPHIINTERFACE IScopeLocks;
typedef System::DelphiInterface<IScopeLocks> _di_IScopeLocks;
__interface DELPHIINTERFACE IScopeEditLink;
typedef System::DelphiInterface<IScopeEditLink> _di_IScopeEditLink;
__interface DELPHIINTERFACE IScopeActive;
typedef System::DelphiInterface<IScopeActive> _di_IScopeActive;
__interface DELPHIINTERFACE IScopeState;
typedef System::DelphiInterface<IScopeState> _di_IScopeState;
__interface DELPHIINTERFACE IScopeEditor;
typedef System::DelphiInterface<IScopeEditor> _di_IScopeEditor;
__interface DELPHIINTERFACE IScopeNavigator;
typedef System::DelphiInterface<IScopeNavigator> _di_IScopeNavigator;
__interface DELPHIINTERFACE IScopeMemberNames;
typedef System::DelphiInterface<IScopeMemberNames> _di_IScopeMemberNames;
__interface DELPHIINTERFACE IScopeUnidirectional;
typedef System::DelphiInterface<IScopeUnidirectional> _di_IScopeUnidirectional;
__interface DELPHIINTERFACE IScopeMemberScripting;
typedef System::DelphiInterface<IScopeMemberScripting> _di_IScopeMemberScripting;
class DELPHICLASS TBaseBindScopeComponent;
class DELPHICLASS TBaseLinkingBindSource;
class DELPHICLASS TCustomBindScope;
class DELPHICLASS TBindScope;
class DELPHICLASS TBindEventListT;
class DELPHICLASS TBindEventList;
template<typename T> class DELPHICLASS TBindEventList1__1;
__interface DELPHIINTERFACE IBindCompFactoryContext;
typedef System::DelphiInterface<IBindCompFactoryContext> _di_IBindCompFactoryContext;
__interface DELPHIINTERFACE IBindCompFactoryExecuteContext;
typedef System::DelphiInterface<IBindCompFactoryExecuteContext> _di_IBindCompFactoryExecuteContext;
__interface DELPHIINTERFACE IBindCompFactory;
typedef System::DelphiInterface<IBindCompFactory> _di_IBindCompFactory;
struct TBindCompDesignExpressionCollection;
struct TBindCompDesignExpression;
__interface DELPHIINTERFACE IBindCompDesigner;
typedef System::DelphiInterface<IBindCompDesigner> _di_IBindCompDesigner;
class DELPHICLASS TBindEditorFactory;
class DELPHICLASS EBindCompError;
class DELPHICLASS TControlObserver;
struct TControlObserverHelper /* Helper for class 'TControlObserver*' */;
class DELPHICLASS TEvalShortcutEnumeratorToEditor;
class DELPHICLASS TEvalShortcutEnumerator;
class DELPHICLASS TEvalShortcutFactory;
class DELPHICLASS TEvalShortcutFactories;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBasicBindComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	/* TComponent.Create */ inline __fastcall virtual TBasicBindComponent(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TBasicBindComponent() { }
	
};


class PASCALIMPLEMENTATION TContainedBindComponent : public TBasicBindComponent
{
	typedef TBasicBindComponent inherited;
	
private:
	TCustomBindingsList* FBindingsList;
	System::UnicodeString FCategory;
	void __fastcall SetBindingsList(TCustomBindingsList* const Value);
	void __fastcall SetCategory(const System::UnicodeString Value);
	int __fastcall GetIndex();
	void __fastcall SetIndex(int Value);
	
protected:
	virtual TCustomBindingsList* __fastcall GetBindingsList();
	virtual void __fastcall ReadState(System::Classes::TReader* Reader);
	virtual System::Classes::TComponent* __fastcall GetControlComponent() = 0 ;
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value) = 0 ;
	void __fastcall CheckControlComponent();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual bool __fastcall Designing();
	virtual bool __fastcall Loading();
	
public:
	__fastcall virtual TContainedBindComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TContainedBindComponent();
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
	DYNAMIC System::Classes::TComponent* __fastcall GetParentComponent();
	DYNAMIC bool __fastcall HasParent();
	DYNAMIC void __fastcall SetParentComponent(System::Classes::TComponent* AParent);
	__property TCustomBindingsList* BindingsList = {read=GetBindingsList, write=SetBindingsList};
	__property int Index = {read=GetIndex, write=SetIndex, stored=false, nodefault};
	__property System::Classes::TComponent* ControlComponent = {read=GetControlComponent, write=SetControlComponent};
	__property System::UnicodeString DisplayName = {read=GetDisplayName};
	
__published:
	__property System::UnicodeString Category = {read=FCategory, write=SetCategory};
};


enum DECLSPEC_DENUM TBindCompExpressionType : unsigned char { exprUnspecified, exprPosSource, exprPosControl, exprFill, exprParse, exprFormat, exprClear, exprFormatColumn, exprOther1, exprOther2, exprOther3, exprFormatControl };

typedef void __fastcall (__closure *TBindCompEvalErrorEvent)(System::TObject* Sender, System::Sysutils::Exception* AException);

typedef void __fastcall (__closure *TBindCompAssigningValueEvent)(System::TObject* Sender, const System::Bindings::Outputs::TBindingAssignValueRec &AssignValueRec, System::Rtti::TValue &Value, bool &Handled);

typedef void __fastcall (__closure *TBindCompAssignedValueEvent)(System::TObject* Sender, const System::Bindings::Outputs::TBindingAssignValueRec &AssignValueRec, const System::Rtti::TValue &Value);

__interface  INTERFACE_UUID("{C1A876BA-6128-477A-B7AB-60458993F366}") IBindMemberChange  : public System::IInterface 
{
	virtual void __fastcall MemberRenamed(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString APrevMemberName) = 0 ;
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName) = 0 ;
	virtual void __fastcall MemberRemoved(System::Classes::TComponent* AComponent, const System::UnicodeString AMemberName) = 0 ;
};

class PASCALIMPLEMENTATION TCommonBindComponent : public TContainedBindComponent
{
	typedef TContainedBindComponent inherited;
	
private:
	System::Classes::TComponent* FSourceComponent;
	TBindCompAssigningValueEvent FOnAssigningValue;
	TBindCompAssignedValueEvent FOnAssignedValue;
	TBindCompEvalErrorEvent FOnEvalError;
	System::Bindings::Outputs::TBindingLocationUpdatedEvent FOnLocationUpdated;
	System::Classes::TComponent* FControlComponent;
	System::UnicodeString FSourceMemberName;
	
private:
	System::Classes::TNotifyEvent FOnActivating;
	System::Classes::TNotifyEvent FOnActivated;
	
protected:
	virtual void __fastcall MemberRenamed(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString APrevMemberName);
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall MemberRemoved(System::Classes::TComponent* AComponent, const System::UnicodeString AMemberName);
	virtual System::Classes::TComponent* __fastcall GetSourceComponent();
	virtual void __fastcall SetSourceComponent(System::Classes::TComponent* const Value);
	virtual void __fastcall SetSourceMemberName(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetSourceMemberName();
	virtual void __fastcall DoOnAssigningValue(const System::Bindings::Outputs::TBindingAssignValueRec &AssignValueRec, System::Rtti::TValue &Value, bool &Handled);
	virtual void __fastcall DoOnLocationUpdated(System::Bindings::Evalprotocol::_di_ILocation AOldLocation, System::Bindings::Evalprotocol::_di_ILocation ANewLocation);
	virtual void __fastcall DoOnAssignedValue(const System::Bindings::Outputs::TBindingAssignValueRec &AssignValueRec, const System::Rtti::TValue &Value);
	virtual void __fastcall DoOnEvalError(System::Sysutils::Exception* AException);
	virtual void __fastcall DoOnActivating();
	virtual void __fastcall DoOnActivated();
	virtual void __fastcall DoOnDeactivating();
	virtual void __fastcall DoOnDeactivated();
#ifndef _WIN64
	System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes();
	System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes();
#else /* _WIN64 */
	System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes();
	System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes();
#endif /* _WIN64 */
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	virtual System::Classes::TComponent* __fastcall GetControlComponent();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall UpdateExpressions();
	void __fastcall FreeExpressionObjects(System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* AList);
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetComponentScope(System::Classes::TComponent* AComponent, const System::UnicodeString AMemberName = System::UnicodeString());
#ifndef _WIN64
	System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetComponentScopes(System::Classes::TComponent* AComponent, const System::UnicodeString AMemberName = System::UnicodeString())/* overload */;
	System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetComponentScopes(System::Bindings::Evalprotocol::_di_IScope AComponentScope)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetComponentScopes(System::Classes::TComponent* AComponent, const System::UnicodeString AMemberName = System::UnicodeString())/* overload */;
	System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetComponentScopes(System::Bindings::Evalprotocol::_di_IScope AComponentScope)/* overload */;
#endif /* _WIN64 */
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetMethodsScope();
	System::Bindings::Outputs::_di_IValueRefConverter __fastcall GetOutputConverter();
	virtual bool __fastcall GetUseEvalShortcuts();
	virtual void __fastcall UpdateSourceChanging();
	virtual void __fastcall UpdateSourceChanged();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall UpdateControlChanged();
	virtual void __fastcall UpdateSourceMemberChanging();
	virtual void __fastcall UpdateSourceMemberChanged();
	void __fastcall EvaluateControlExpression(System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback)/* overload */;
	void __fastcall EvaluateSourceExpression(System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::UnicodeString AEnumExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback)/* overload */;
	virtual void __fastcall SetOnActivated(const System::Classes::TNotifyEvent Value);
	virtual void __fastcall SetOnActivating(const System::Classes::TNotifyEvent Value);
	virtual void __fastcall SetOnAssignedValue(const TBindCompAssignedValueEvent Value);
	virtual void __fastcall SetOnAssigningValue(const TBindCompAssigningValueEvent Value);
	virtual void __fastcall SetOnEvalError(const TBindCompEvalErrorEvent Value);
	virtual void __fastcall SetOnLocationUpdated(const System::Bindings::Outputs::TBindingLocationUpdatedEvent Value);
	
public:
	__fastcall virtual TCommonBindComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCommonBindComponent();
	virtual void __fastcall EvaluateControlExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0))/* overload */;
	virtual void __fastcall EvaluateSourceExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0))/* overload */;
	virtual void __fastcall ExecuteAssignToControlExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0))/* overload */;
	virtual void __fastcall ExecuteAssignToSourceExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0));
	__property System::Classes::TComponent* SourceComponent = {read=GetSourceComponent, write=SetSourceComponent};
	__property System::UnicodeString SourceMemberName = {read=GetSourceMemberName, write=SetSourceMemberName};
	__property System::Classes::TComponent* ControlComponent = {read=GetControlComponent, write=SetControlComponent};
	__property TBindCompAssigningValueEvent OnAssigningValue = {read=FOnAssigningValue, write=SetOnAssigningValue};
	__property TBindCompAssignedValueEvent OnAssignedValue = {read=FOnAssignedValue, write=SetOnAssignedValue};
	__property TBindCompEvalErrorEvent OnEvalError = {read=FOnEvalError, write=SetOnEvalError};
	__property System::Bindings::Outputs::TBindingLocationUpdatedEvent OnLocationUpdated = {read=FOnLocationUpdated, write=SetOnLocationUpdated};
	__property System::Classes::TNotifyEvent OnActivating = {read=FOnActivating, write=SetOnActivating};
	__property System::Classes::TNotifyEvent OnActivated = {read=FOnActivated, write=SetOnActivated};
private:
	void *__IBindMemberChange;	// IBindMemberChange 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C1A876BA-6128-477A-B7AB-60458993F366}
	operator _di_IBindMemberChange()
	{
		_di_IBindMemberChange intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindMemberChange*(void) { return (IBindMemberChange*)&__IBindMemberChange; }
	#endif
	
};


#ifndef _WIN64
typedef System::TMetaClass* TContainedBindCompClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TContainedBindCompClass);
#endif /* _WIN64 */

__interface  INTERFACE_UUID("{E79E5862-E1F2-4493-A642-5859A9D765D8}") IDependencyList  : public System::IInterface 
{
	virtual TDependency* __fastcall Add(TDependency* ADependency) = 0 ;
	virtual void __fastcall Remove(TDependency* ADependency) = 0 ;
	virtual void __fastcall Notify(System::TObject* ASender, System::Classes::TComponent* const AComponent, const System::UnicodeString AValue) = 0 /* overload */;
	virtual void __fastcall Notify(System::TObject* ASender, const System::Bindings::Evalprotocol::_di_ILocation ALocation, const System::UnicodeString AExpr) = 0 /* overload */;
	virtual void __fastcall Link(System::Classes::TComponent* AComponent, const System::Bindings::Evalprotocol::_di_ILocation ALocation) = 0 ;
	virtual System::Classes::TComponent* __fastcall GetLink(const System::Bindings::Evalprotocol::_di_ILocation ALocation) = 0 ;
	virtual void __fastcall ClearLink(const System::Bindings::Evalprotocol::_di_ILocation ALocation) = 0 ;
};

class PASCALIMPLEMENTATION TCustomBindingsList : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	TContainedBindComponent* operator[](int Index) { return this->BindComps[Index]; }
	
private:
	System::Generics::Collections::TList__1<TContainedBindComponent*>* FBindComps;
	TMethods* FMethods;
	bool FUseAppManager;
	System::Bindings::Manager::TBindingManager* FBindingsManager;
	TOutputConverters* FOutputConverters;
	System::Bindings::Outputs::_di_IValueRefConverter FOutputConverter;
	System::Bindings::Evalprotocol::_di_IScope FMethodsScope;
	_di_IDependencyList FDependencyList;
	bool FPromptDeleteUnused;
	TContainedBindComponent* __fastcall GetBindComp(int Index);
	int __fastcall GetBindCompCount();
	void __fastcall SetBindComp(int Index, TContainedBindComponent* const Value);
	void __fastcall SetMethods(TMethods* const Value);
	void __fastcall SetOutputConverters(TOutputConverters* const Value);
	void __fastcall SetUseAppManager(bool Value);
	bool __fastcall GetUseAppManager();
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetOutputConverterNames();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetOutputConverterNames();
#endif /* _WIN64 */
	
protected:
	void __fastcall AddBindComp(TContainedBindComponent* ABindComp);
	void __fastcall RemoveBindComp(TContainedBindComponent* ABindComp);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TCustomBindingsList(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindingsList();
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetMethodsScope();
	System::Bindings::Outputs::_di_IValueRefConverter __fastcall GetOutputConverter();
	void __fastcall Notify(System::TObject* const AObject, const System::UnicodeString AProperty);
	DYNAMIC void __fastcall GetChildren(System::Classes::TGetChildProc Proc, System::Classes::TComponent* Root);
	__property TMethods* Methods = {read=FMethods, write=SetMethods};
	__property TOutputConverters* OutputConverters = {read=FOutputConverters, write=SetOutputConverters};
	HIDESBASE TBindingsListEnumerator* __fastcall GetEnumerator();
	__property TContainedBindComponent* BindComps[int Index] = {read=GetBindComp, write=SetBindComp/*, default*/};
	__property int BindCompCount = {read=GetBindCompCount, nodefault};
	__property bool UseAppManager = {read=GetUseAppManager, write=SetUseAppManager, default=1};
	__property bool PromptDeleteUnused = {read=FPromptDeleteUnused, write=FPromptDeleteUnused, default=1};
	__property _di_IDependencyList DependencyList = {read=FDependencyList};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindingsListEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	TCustomBindingsList* FBindCompList;
	
public:
	__fastcall TBindingsListEnumerator(TCustomBindingsList* ABindCompList);
	TContainedBindComponent* __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TContainedBindComponent* Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingsListEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDependencyList : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::Classes::TComponent*,System::Generics::Collections::TList__1<System::UnicodeString>*>* FNotified;
	TCustomBindingsList* FBindingsList;
	System::Generics::Collections::TList__1<TDependency*>* FList;
	System::Generics::Collections::TDictionary__2<System::Bindings::Evalprotocol::_di_ILocation,System::Classes::TComponent*>* FLocationDict;
	
public:
	__fastcall TDependencyList(TCustomBindingsList* ABindCompList);
	__fastcall virtual ~TDependencyList();
	TDependency* __fastcall Add(TDependency* ADependency);
	void __fastcall Remove(TDependency* ADependency);
	void __fastcall Link(System::Classes::TComponent* AComponent, const System::Bindings::Evalprotocol::_di_ILocation ALocation);
	System::Classes::TComponent* __fastcall GetLink(const System::Bindings::Evalprotocol::_di_ILocation ALocation);
	void __fastcall ClearLink(const System::Bindings::Evalprotocol::_di_ILocation ALocation);
	void __fastcall Notify(System::TObject* ASender, const System::Bindings::Evalprotocol::_di_ILocation ALocation, const System::UnicodeString AExpr)/* overload */;
	void __fastcall Notify(System::TObject* ASender, System::Classes::TComponent* const AComponent, const System::UnicodeString AValue)/* overload */;
private:
	void *__IDependencyList;	// IDependencyList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E79E5862-E1F2-4493-A642-5859A9D765D8}
	operator _di_IDependencyList()
	{
		_di_IDependencyList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDependencyList*(void) { return (IDependencyList*)&__IDependencyList; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDependency : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TObject* FOwner;
	System::Classes::TComponent* FComponent;
	System::UnicodeString FMember;
	System::UnicodeString FExpr;
	
public:
	__fastcall TDependency(System::TObject* AOwner, System::Classes::TComponent* AComponent, const System::UnicodeString AMember, const System::UnicodeString AExpr);
	virtual void __fastcall NotifyDependent();
	__property System::TObject* Owner = {read=FOwner};
	__property System::Classes::TComponent* Component = {read=FComponent};
	__property System::UnicodeString Member = {read=FMember};
	__property System::UnicodeString Expr = {read=FExpr};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDependency() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TBindingsList : public TCustomBindingsList
{
	typedef TCustomBindingsList inherited;
	
__published:
	__property Methods;
	__property OutputConverters;
	__property UseAppManager = {default=1};
	__property PromptDeleteUnused = {default=1};
public:
	/* TCustomBindingsList.Create */ inline __fastcall virtual TBindingsList(System::Classes::TComponent* AOwner) : TCustomBindingsList(AOwner) { }
	/* TCustomBindingsList.Destroy */ inline __fastcall virtual ~TBindingsList() { }
	
};


class PASCALIMPLEMENTATION TActivatedContainedBindComponent : public TCommonBindComponent
{
	typedef TCommonBindComponent inherited;
	
private:
	bool FAutoActivate;
	void __fastcall AddScopeExpressions();
	void __fastcall RemoveScopeExpressions();
	
private:
	void __fastcall AutoActivateOnPropertyChange();
	
protected:
	virtual void __fastcall LoadActivate();
	virtual void __fastcall BindActivate(bool Value);
	bool __fastcall ActivateFromSource();
	virtual void __fastcall UpdateEnableChanging();
	virtual void __fastcall UpdateEnableChanged();
	virtual void __fastcall SetActive(bool AValue) = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual bool __fastcall GetAutoActivate();
	virtual void __fastcall SetAutoActivate(bool AValue);
	virtual bool __fastcall CanActivate();
	virtual void __fastcall ApplyComponents();
	virtual void __fastcall UpdateSourceChanging();
	virtual void __fastcall UpdateSourceMemberChanged();
	virtual void __fastcall UpdateSourceChanged();
	virtual void __fastcall UpdateControlChanged();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall UpdateSourceMemberChanging();
	
public:
	__fastcall virtual TActivatedContainedBindComponent(System::Classes::TComponent* AOwner);
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
public:
	/* TCommonBindComponent.Destroy */ inline __fastcall virtual ~TActivatedContainedBindComponent() { }
	
};


class PASCALIMPLEMENTATION TExpressionsBindComponent : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
private:
	System::Generics::Collections::TList__1<TDependency*>* FDependencies;
	System::Generics::Collections::TList__1<System::Bindings::Evalprotocol::_di_ILocation>* FDependencyLinks;
	TExpressions* FParseExpressions;
	TExpressions* FFormatExpressions;
	TExpressions* FClearExpressions;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FParseExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FFormatExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FClearExpressionObjects;
	
protected:
	virtual TExpressions* __fastcall GetClearExpressions();
	virtual TExpressions* __fastcall GetFormatExpressions();
	virtual TExpressions* __fastcall GetParseExpressions();
	virtual void __fastcall SetParseExpressions(TExpressions* const Value);
	virtual void __fastcall SetFormatExpressions(TExpressions* const Value);
	virtual void __fastcall SetClearExpressions(TExpressions* const Value);
	void __fastcall AddDependency(System::Bindings::Expression::TBindingExpression* ABindingExpression, System::DelphiInterface<System::Sysutils::TProc__1<TExpressionsBindComponent*> > ANotifyProc, System::Classes::TComponent* ASourceComponent, System::UnicodeString ASourceMemberName, System::UnicodeString AExpression, System::Classes::TComponent* AOutputComponent);
	void __fastcall CleanDependencies();
	virtual void __fastcall FreeExpressionsObjects();
	void __fastcall NotifyDependentOutputs(System::Bindings::Expression::TBindingExpression* ABindingExpression);
	virtual void __fastcall DoOnAssignedValue(const System::Bindings::Outputs::TBindingAssignValueRec &AssignValueRec, const System::Rtti::TValue &Value);
	virtual void __fastcall DoOnLocationUpdated(System::Bindings::Evalprotocol::_di_ILocation AOldLocation, System::Bindings::Evalprotocol::_di_ILocation ANewLocation);
	
public:
	__fastcall virtual TExpressionsBindComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TExpressionsBindComponent();
	__property TExpressions* FormatExpressions = {read=GetFormatExpressions, write=SetFormatExpressions};
	__property TExpressions* ParseExpressions = {read=GetParseExpressions, write=SetParseExpressions};
	__property TExpressions* ClearExpressions = {read=GetClearExpressions, write=SetClearExpressions};
};


__interface  INTERFACE_UUID("{79856F26-5E66-4A24-B4DE-A7DBBE6356AD}") IBindActivate  : public System::IInterface 
{
	virtual void __fastcall SetActive(bool AValue) = 0 ;
};

class PASCALIMPLEMENTATION TBaseBindExpression : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
private:
	bool FDeferActive;
	bool FActive;
	bool FManaged;
	bool FNotifyOutputs;
	void __fastcall SetManaged(const bool Value);
	void __fastcall SetNotifyOutputs(const bool Value);
	
protected:
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetActive();
	virtual void __fastcall EvaluateFormat();
	virtual void __fastcall EvaluateClear();
	virtual void __fastcall SetActive(bool Value);
	
public:
	__fastcall virtual TBaseBindExpression(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseBindExpression();
	__property bool Managed = {read=FManaged, write=SetManaged, default=1};
	__property bool NotifyOutputs = {read=FNotifyOutputs, write=SetNotifyOutputs, nodefault};
private:
	void *__IBindActivate;	// IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	
};


enum DECLSPEC_DENUM TExpressionDirection : unsigned char { dirSourceToControl, dirControlToSource, dirBidirectional };

class PASCALIMPLEMENTATION TCustomBindExpression : public TBaseBindExpression
{
	typedef TBaseBindExpression inherited;
	
private:
	System::UnicodeString FSourceExpression;
	System::Bindings::Expression::TBindingExpression* FExpressionObject;
	System::Bindings::Expression::TBindingExpression* FReverseExpressionObject;
	System::UnicodeString FControlExpression;
	TExpressionDirection FDirection;
	void __fastcall SetSourceExpression(const System::UnicodeString Value);
	void __fastcall SetControlExpression(const System::UnicodeString Value);
	
protected:
	void __fastcall EvaluateWithoutNotify();
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall FreeExpressionsObjects();
	virtual bool __fastcall CanActivate();
	
public:
	__fastcall virtual TCustomBindExpression(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindExpression();
	__property System::UnicodeString ControlExpression = {read=FControlExpression, write=SetControlExpression};
	__property TExpressionDirection Direction = {read=FDirection, write=FDirection, nodefault};
	virtual void __fastcall EvaluateFormat();
	void __fastcall Evaluate();
	void __fastcall Recompile();
	__property System::UnicodeString SourceExpression = {read=FSourceExpression, write=SetSourceExpression};
};


class PASCALIMPLEMENTATION TBindExpression : public TCustomBindExpression
{
	typedef TCustomBindExpression inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property SourceMemberName = {default=0};
	__property SourceExpression = {default=0};
	__property ControlExpression = {default=0};
	__property AutoActivate = {default=1};
	__property Managed = {default=1};
	__property NotifyOutputs;
	__property Direction;
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindExpression.Create */ inline __fastcall virtual TBindExpression(System::Classes::TComponent* AOwner) : TCustomBindExpression(AOwner) { }
	/* TCustomBindExpression.Destroy */ inline __fastcall virtual ~TBindExpression() { }
	
};


class PASCALIMPLEMENTATION TCustomBindExprItems : public TBaseBindExpression
{
	typedef TBaseBindExpression inherited;
	
private:
	TExpressionsDir* FFormatExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FFormatExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FReverseFormatExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FClearExpressionObjects;
	TExpressionsDir* FClearExpressions;
	void __fastcall SetFormatExpressions(TExpressionsDir* Value);
	void __fastcall SetClearExpressions(TExpressionsDir* const Value);
	void __fastcall EvaluateWithoutNotify();
	
protected:
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall FreeExpressionsObjects();
	virtual bool __fastcall CanActivate();
	
public:
	__fastcall virtual TCustomBindExprItems(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindExprItems();
	virtual void __fastcall EvaluateFormat();
	virtual void __fastcall EvaluateClear();
	void __fastcall Recompile();
	__property TExpressionsDir* FormatExpressions = {read=FFormatExpressions, write=SetFormatExpressions};
	__property TExpressionsDir* ClearExpressions = {read=FClearExpressions, write=SetClearExpressions};
};


class PASCALIMPLEMENTATION TBindExprItems : public TCustomBindExprItems
{
	typedef TCustomBindExprItems inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property SourceMemberName = {default=0};
	__property FormatExpressions;
	__property ClearExpressions;
	__property AutoActivate = {default=1};
	__property Managed = {default=1};
	__property NotifyOutputs;
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindExprItems.Create */ inline __fastcall virtual TBindExprItems(System::Classes::TComponent* AOwner) : TCustomBindExprItems(AOwner) { }
	/* TCustomBindExprItems.Destroy */ inline __fastcall virtual ~TBindExprItems() { }
	
};


__interface  INTERFACE_UUID("{50307CDD-63CD-4538-A211-D605C3811A0B}") IBindNavigator  : public System::IInterface 
{
	virtual TBaseLinkingBindSource* __fastcall GetDataSource() = 0 ;
	virtual void __fastcall SetDataSource(TBaseLinkingBindSource* AScope) = 0 ;
	__property TBaseLinkingBindSource* DataSource = {read=GetDataSource, write=SetDataSource};
};

__interface  INTERFACE_UUID("{6C93BB29-D210-43E9-9850-0C22EDD0F9B2}") IScopeRecordEnumerator  : public System::IInterface 
{
	virtual void __fastcall First() = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrent() = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetMemberCurrent(const System::UnicodeString AMemberName) = 0 ;
	virtual bool __fastcall MoveNext() = 0 ;
	__property System::Bindings::Evalprotocol::_di_IScope Current = {read=GetCurrent};
};

__interface  INTERFACE_UUID("{E961A08B-7FC3-4FE2-819C-79F3D0A230BE}") IScopeRecordControlUpdator  : public System::IInterface 
{
	virtual void __fastcall UpdateControlComponent(System::Classes::TComponent* AControl) = 0 ;
};

enum DECLSPEC_DENUM TScopeMemberType : unsigned char { mtUnknown, mtText, mtInteger, mtFloat, mtBitmap, mtMemo, mtBoolean, mtBCD, mtUInteger, mtDateTime, mtCurrency, mtObject, mtVariant, mtDate, mtTime, mtChar, mtTValue };

__interface TValueCallback  : public System::IInterface 
{
	virtual void __fastcall Invoke(const System::Rtti::TValue &AValue, TScopeMemberType AType) = 0 ;
};

__interface  INTERFACE_UUID("{64768DD1-CD80-434E-A5C1-D5990E0E04F9}") IScopeRecordEnumeratorEvalShortcut  : public System::IInterface 
{
	virtual void __fastcall GetMemberValue(const System::UnicodeString AMemberName, const TScopeMemberType AType, const _di_TValueCallback ACallback) = 0 /* overload */;
	virtual bool __fastcall GetMemberValue(const System::UnicodeString AMemberName, const TScopeMemberType *ATypes, const int ATypes_High, /* out */ System::Rtti::TValue &AValue) = 0 /* overload */;
	virtual bool __fastcall CanGetMemberValue(const System::UnicodeString AMemberName, TScopeMemberType AType) = 0 ;
};

__interface  INTERFACE_UUID("{46FAE534-6F58-4850-AF66-14DF7B8AEC0C}") IScopeRecordEnumeratorCount  : public System::IInterface 
{
	virtual int __fastcall GetRecordCount() = 0 ;
	__property int RecordCount = {read=GetRecordCount};
};

__interface  INTERFACE_UUID("{755F088B-F673-45BD-A74D-ECBBDB38ACBA}") IScopeRecordEnumeratorStatus  : public System::IInterface 
{
	virtual bool __fastcall GetMultiRecordChange() = 0 ;
	__property bool MultiRecordChange = {read=GetMultiRecordChange};
};

__interface  INTERFACE_UUID("{34A6773D-A71B-4870-9C60-409A798206FA}") IScopeRecordEnumerable  : public System::IInterface 
{
	virtual _di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, int ABufferCount = 0xffffffff) = 0 ;
};

__interface  INTERFACE_UUID("{DC2115E9-F163-43E2-A713-52A8455EF8FD}") IScopeRecordEnumerableBuffered  : public System::IInterface 
{
	virtual _di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, bool ABuffered) = 0 ;
};

__interface  INTERFACE_UUID("{5ADA44B4-4E81-401B-9784-3B51D29A5149}") IScopeCurrentRecord  : public System::IInterface 
{
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetCurrentRecord(const System::UnicodeString AMemberName) = 0 ;
};

__interface  INTERFACE_UUID("{D33C242C-310D-4BE7-9908-C3CAC3C856B6}") IScopeGetRecord  : public System::IInterface 
{
	virtual void __fastcall GetRecord(int ARow, const System::UnicodeString AMemberName, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IScope> > ACallback) = 0 ;
};

__interface  INTERFACE_UUID("{95C4149E-E1AD-4D21-A8DF-A84A33B6D2D9}") IScopeLookup  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall Lookup(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues, const System::UnicodeString ResultFields) = 0 ;
	virtual void __fastcall GetLookupMemberNames(System::Classes::TStrings* AList) = 0 ;
};

__interface  INTERFACE_UUID("{CBC0B2CC-0011-4569-B17E-1B5B62BE59CF}") IScopeLocate  : public System::IInterface 
{
	virtual bool __fastcall Locate(const System::UnicodeString KeyFields, const System::Rtti::TValue &KeyValues) = 0 ;
};

__interface  INTERFACE_UUID("{3E48BABC-3939-4326-AD02-B1DF377746C6}") IScopeNavigatorUpdates  : public System::IInterface 
{
	virtual void __fastcall ApplyUpdates() = 0 ;
	virtual bool __fastcall GetCanApplyUpdates() = 0 ;
	virtual bool __fastcall GetCanCancelUpdates() = 0 ;
	virtual void __fastcall CancelUpdates() = 0 ;
	__property bool CanApplyUpdates = {read=GetCanApplyUpdates};
	__property bool CanCancelUpdates = {read=GetCanCancelUpdates};
};

__interface  INTERFACE_UUID("{43D47EB0-14F2-47D0-89F5-6CB516F36BF3}") IScopeBuffer  : public System::IInterface 
{
	virtual bool __fastcall GetBufferCount(/* out */ int &ACount) = 0 ;
};

__interface  INTERFACE_UUID("{4E952D1B-0D23-41C4-8DF0-D24C4C325D5C}") IBindLink  : public System::IInterface 
{
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual bool __fastcall GetUpdating() = 0 ;
	__property bool Updating = {read=GetUpdating};
	virtual void __fastcall SetIsReadOnly(bool Value) = 0 ;
	virtual bool __fastcall IsRequired() = 0 ;
	virtual bool __fastcall IsValidChar(System::WideChar AKey) = 0 ;
	virtual bool __fastcall GetCanModify() = 0 ;
	virtual bool __fastcall GetIsModified() = 0 ;
	virtual void __fastcall SetModified() = 0 ;
	virtual bool __fastcall Edit() = 0 ;
	virtual bool __fastcall GetIsEditing() = 0 ;
	virtual void __fastcall Reset() = 0 ;
	virtual void __fastcall UpdateRecord() = 0 ;
	virtual void __fastcall EvaluateParse(const System::UnicodeString AMemberName) = 0 ;
	virtual void __fastcall EvaluateFormat(const System::UnicodeString AMemberName) = 0 ;
	virtual void __fastcall EvaluateClear(const System::UnicodeString AMemberName) = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(bool AValue) = 0 ;
	virtual System::Classes::TComponent* __fastcall GetBindComp() = 0 ;
	virtual System::UnicodeString __fastcall GetSourceMemberName() = 0 ;
	__property bool Active = {read=GetActive, write=SetActive};
	__property System::Classes::TComponent* BindComp = {read=GetBindComp};
	__property System::UnicodeString SourceMemberName = {read=GetSourceMemberName};
	__property bool IsModified = {read=GetIsModified};
	__property bool CanModify = {read=GetCanModify};
	__property bool IsEditing = {read=GetIsEditing};
	virtual void __fastcall ClearEditingLink() = 0 ;
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink() = 0 ;
};

__interface  INTERFACE_UUID("{6E9EB32B-4982-4D4D-9510-A0ADFB1BDCC8}") IBindPosition  : public System::IInterface 
{
	virtual System::Classes::TComponent* __fastcall GetBindComp() = 0 ;
	virtual void __fastcall PosChanged() = 0 ;
	virtual void __fastcall PosChanging() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual System::UnicodeString __fastcall GetSourceMemberName() = 0 ;
	virtual void __fastcall EvaluatePosControl() = 0 ;
	virtual void __fastcall EvaluatePosClear() = 0 ;
	virtual void __fastcall SetActive(bool AValue) = 0 ;
	__property System::Classes::TComponent* BindComp = {read=GetBindComp};
	__property bool Active = {read=GetActive, write=SetActive};
	__property System::UnicodeString SourceMemberName = {read=GetSourceMemberName};
};

__interface  INTERFACE_UUID("{7EE337E7-C25E-4900-90C3-DA2EE9F33954}") IBindTrack  : public System::IInterface 
{
	virtual bool __fastcall GetTrack() = 0 ;
	virtual void __fastcall SetTrack(const bool Value) = 0 ;
	__property bool Track = {read=GetTrack, write=SetTrack};
};

__interface  INTERFACE_UUID("{ABDF3DA4-7A87-44F3-9589-1610207529F7}") IBindControlValue  : public System::IInterface 
{
	virtual void __fastcall ValueChanged() = 0 ;
	virtual bool __fastcall GetUpdating() = 0 ;
	__property bool Updating = {read=GetUpdating};
};

__interface  INTERFACE_UUID("{01EED9E9-F0BD-4752-A6BA-F79EF46ABE55}") IBindListUpdate  : public System::IInterface 
{
	virtual System::Classes::TComponent* __fastcall GetBindComp() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall UpdateList() = 0 ;
	__property System::Classes::TComponent* BindComp = {read=GetBindComp};
	__property bool Active = {read=GetActive};
};

__interface  INTERFACE_UUID("{89D41A89-AA65-4177-A3D3-373E1430EF35}") IBindListRefresh  : public System::IInterface 
{
	virtual void __fastcall RefreshList() = 0 ;
	virtual bool __fastcall RefreshNeeded() = 0 ;
};

__interface  INTERFACE_UUID("{1B1D65B7-EB88-4D81-A1B4-D706DCE4C05C}") IBindListRefreshing  : public System::IInterface 
{
	virtual System::Classes::TNotifyEvent __fastcall GetListRefreshing() = 0 ;
	virtual void __fastcall SetListRefreshing(System::Classes::TNotifyEvent AEvent) = 0 ;
	__property System::Classes::TNotifyEvent OnListRefreshing = {read=GetListRefreshing, write=SetListRefreshing};
};

__interface  INTERFACE_UUID("{6913B4FE-45C1-4844-9C9F-A2F59309C9FC}") IBindLayoutChanged  : public System::IInterface 
{
	virtual void __fastcall LayoutChanged() = 0 ;
};

__interface TFormatCallback  : public System::IInterface 
{
	virtual void __fastcall Invoke(const System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::Bindings::Evalprotocol::_di_IScope AControlScope) = 0 ;
};

__interface TQueryBreakCallback  : public System::IInterface 
{
	virtual bool __fastcall Invoke(const System::Bindings::Evalprotocol::_di_IScope ASourceScope) = 0 ;
};

enum DECLSPEC_DENUM TBindCheckBoxState : unsigned char { cbUnchecked, cbChecked, cbGrayed };

__interface  INTERFACE_UUID("{907EB30C-3C04-400C-88FD-3E9FD5EAE761}") IBindCheckBoxEditor  : public System::IInterface 
{
	virtual TBindCheckBoxState __fastcall GetState() = 0 ;
	virtual void __fastcall SetState(TBindCheckBoxState Value) = 0 ;
	virtual bool __fastcall GetAllowGrayed() = 0 ;
	virtual void __fastcall SetAllowGrayed(bool Value) = 0 ;
	__property bool AllowGrayed = {read=GetAllowGrayed, write=SetAllowGrayed};
	__property TBindCheckBoxState State = {read=GetState, write=SetState};
};

__interface  INTERFACE_UUID("{B94877B1-5DCB-420F-A9E4-D3401C05AF25}") IBindDateTimeEditEditor  : public System::IInterface 
{
	virtual bool __fastcall GetIsEmpty() = 0 ;
	virtual void __fastcall SetIsEmpty(bool Value) = 0 ;
	virtual System::TDateTime __fastcall GetDateTime() = 0 ;
	virtual void __fastcall SetDateTime(System::TDateTime ADateTime) = 0 ;
	__property bool IsEmpty = {read=GetIsEmpty, write=SetIsEmpty};
	__property System::TDateTime SelectedDateTime = {read=GetDateTime, write=SetDateTime};
};

__interface  INTERFACE_UUID("{21F446F9-5C99-47F2-8029-5D7BD0A40563}") IBindTimeEditEditor  : public System::IInterface 
{
	virtual bool __fastcall GetIsEmpty() = 0 ;
	virtual void __fastcall SetIsEmpty(bool Value) = 0 ;
	virtual System::TTime __fastcall GetTime() = 0 ;
	virtual void __fastcall SetTime(System::TTime ATime) = 0 ;
	__property bool IsEmpty = {read=GetIsEmpty, write=SetIsEmpty};
	__property System::TTime SelectedTime = {read=GetTime, write=SetTime};
};

__interface  INTERFACE_UUID("{85AD494A-E7ED-402A-90FF-4F9B485B209C}") IBindFillControlMembers  : public System::IInterface 
{
	virtual void __fastcall GetItemMemberNames(System::Classes::TStrings* ANames) = 0 ;
	virtual System::UnicodeString __fastcall GetItemMemberNameExpression(const System::UnicodeString AName) = 0 ;
	virtual void __fastcall GetHeaderMemberNames(System::Classes::TStrings* ANames) = 0 ;
	virtual System::UnicodeString __fastcall GetHeaderMemberNameExpression(const System::UnicodeString AName) = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentHeaderItem() = 0 ;
};

__interface  INTERFACE_UUID("{87465AA0-608E-4CA4-BE36-B808B3895486}") IBindListEditorCommon  : public System::IInterface 
{
	virtual void __fastcall BeginUpdate() = 0 ;
	virtual void __fastcall EndUpdate() = 0 ;
	virtual int __fastcall GetRowCount() = 0 ;
	virtual void __fastcall ClearList() = 0 ;
	virtual System::TObject* __fastcall GetSelectedItem() = 0 ;
	virtual System::UnicodeString __fastcall GetSelectedText() = 0 ;
	virtual System::Rtti::TValue __fastcall GetSelectedValue() = 0 ;
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase) = 0 ;
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase) = 0 ;
	__property System::UnicodeString SelectedText = {read=GetSelectedText};
	__property System::Rtti::TValue SelectedValue = {read=GetSelectedValue};
	__property System::TObject* SelectedItem = {read=GetSelectedItem};
	__property int RowCount = {read=GetRowCount};
};

__interface  INTERFACE_UUID("{788EB4F3-AA8F-42EA-AD73-B5A5B1D90A49}") IBindListGroupEditor  : public System::IInterface 
{
	virtual void __fastcall FillGroupList(_di_IScopeRecordEnumerator ARecordEnumerator, _di_TFormatCallback AFormatProc, _di_TFormatCallback AFormatHeaderProc, _di_TQueryBreakCallback AQueryBreakCallback) = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddHeader() = 0 ;
};

__interface  INTERFACE_UUID("{B6F0F4F3-EDF7-44F6-A466-32F439B9E3EA}") IBindListSynchEditor  : public System::IInterface 
{
	virtual int __fastcall GetSynchIndex() = 0 ;
	virtual void __fastcall SetSynchIndex(int AIndex) = 0 ;
	virtual void __fastcall ApplyFilter() = 0 ;
	__property int SynchIndex = {read=GetSynchIndex, write=SetSynchIndex};
};

__interface  INTERFACE_UUID("{A3EBD46C-A2F7-45A2-87FA-8E1CCE9C7601}") IBindListItemIndexEditor  : public System::IInterface 
{
	virtual int __fastcall GetItemIndex() = 0 ;
	virtual void __fastcall SetItemIndex(int AIndex) = 0 ;
	__property int ItemIndex = {read=GetItemIndex, write=SetItemIndex};
};

__interface  INTERFACE_UUID("{6FBB6044-F568-4996-BAA2-CD71F7D1A83E}") IBindListEditorItem  : public System::IInterface 
{
	virtual System::TObject* __fastcall CurrentObject() = 0 ;
	virtual int __fastcall CurrentIndex() = 0 ;
};

__interface  INTERFACE_UUID("{C0D3125F-F9E8-4EAE-98CB-AC16D0E7B075}") IBindListEditor  : public IBindListEditorCommon 
{
	HIDESBASE virtual System::Rtti::TValue __fastcall GetSelectedValue() = 0 ;
	virtual void __fastcall SetSelectedValue(const System::Rtti::TValue &AValue) = 0 ;
	virtual void __fastcall SetSelectedText(const System::UnicodeString AValue) = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall AddItem(bool Select = false) = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall InsertItem(bool Select = false) = 0 ;
	virtual bool __fastcall CanInsertItem() = 0 ;
	virtual void __fastcall DeleteToEnd() = 0 ;
	virtual bool __fastcall UpdateNeeded(_di_IScopeRecordEnumerator ARecordEnumerator) = 0 ;
	virtual bool __fastcall RefreshNeeded(_di_IScopeRecordEnumerator ARecordEnumerator) = 0 ;
	virtual void __fastcall UpdateList(_di_IScopeRecordEnumerator ARecordEnumerator, _di_TFormatCallback AFormatProc) = 0 ;
	virtual void __fastcall FillList(_di_IScopeRecordEnumerator ARecordEnumerator, _di_TFormatCallback AFormatProc) = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall CurrentItem() = 0 ;
	virtual bool __fastcall MoveNext() = 0 ;
	virtual void __fastcall SetExpectedRowCount(int ARowCount) = 0 ;
	__property System::UnicodeString SelectedText = {read=GetSelectedText, write=SetSelectedText};
	__property System::Rtti::TValue SelectedValue = {read=GetSelectedValue, write=SetSelectedValue};
};

__interface  INTERFACE_UUID("{B3E7381A-559C-479B-B867-92FDACFDFD34}") IBindListEditorEvalShortcut  : public System::IInterface 
{
	virtual void __fastcall SetCurrentValue(const System::UnicodeString AMemberName, const System::Rtti::TValue &AValue, TScopeMemberType AType) = 0 ;
	virtual bool __fastcall CanSetCurrentValue(const System::UnicodeString AMemberName, /* out */ TScopeMemberType &AType) = 0 ;
};

__interface  INTERFACE_UUID("{A70B5726-FF2F-4E6E-A99C-72C73FCF0168}") IBindListLookupEditor  : public IBindListEditor 
{
	virtual bool __fastcall GetUseLookups() = 0 ;
	virtual void __fastcall SetUseLookups(bool AUseLookups) = 0 ;
	virtual System::Rtti::TValue __fastcall GetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope) = 0 ;
	virtual void __fastcall SetLookupValue(const System::Bindings::Evalprotocol::_di_IScope AScope, const System::Rtti::TValue &AValue) = 0 ;
	virtual System::Rtti::TValue __fastcall GetSelectedLookupValue() = 0 ;
	virtual void __fastcall SetSelectedLookupValue(const System::Rtti::TValue &AValue) = 0 ;
	__property System::Rtti::TValue LookupValue[const System::Bindings::Evalprotocol::_di_IScope AScope] = {read=GetLookupValue, write=SetLookupValue};
	__property System::Rtti::TValue SelectedLookupValue = {read=GetSelectedLookupValue, write=SetSelectedLookupValue};
	__property bool UseLookups = {read=GetUseLookups, write=SetUseLookups};
};

__interface TBindGridOnCallbackEvaluateFormat  : public System::IInterface 
{
	virtual void __fastcall Invoke(int Col, int Row, System::Bindings::Evalprotocol::_di_IScope AEditorScope) = 0 ;
};

__interface  INTERFACE_UUID("{826B10CB-AD17-4D60-830C-7912B6ED6712}") IBindListVirtualEditor  : public IBindListEditorCommon 
{
	virtual void __fastcall SetRowCount(int ARowCount) = 0 ;
	virtual void __fastcall SetOnCallbackEvaluateFormat(_di_TBindGridOnCallbackEvaluateFormat OnCallbackEvaluateFormat) = 0 ;
	virtual void __fastcall UpdateCell(int Col) = 0 ;
};

__interface  INTERFACE_UUID("{3DE056BC-0DC9-40B0-AB32-2B4FE7AFDCF5}") IBindListRecordVirtualEditor  : public System::IInterface 
{
	virtual void __fastcall BeforeRecordUpdate() = 0 ;
	virtual void __fastcall AfterRecordUpdate() = 0 ;
};

__interface  INTERFACE_UUID("{E4E25A70-9D29-4B46-BB7B-E3A07DC676B0}") IBindListVirtualEditorScope  : public System::IInterface 
{
	virtual bool __fastcall CanCache() = 0 ;
};

__interface  INTERFACE_UUID("{FDE1D9BA-4277-4549-945F-ABFC5E61A56D}") IBindGridEditor  : public System::IInterface 
{
	virtual void __fastcall GetColumnNames(System::Classes::TStrings* AList) = 0 ;
	virtual void __fastcall GetColumnIndices(System::Classes::TStrings* AList) = 0 ;
};

__interface  INTERFACE_UUID("{F0FAEC32-EC29-45C1-9490-1DC9CD169DD4}") IBindLinkColumns  : public IBindLink 
{
	virtual System::UnicodeString __fastcall GetEditColumnName() = 0 ;
	virtual int __fastcall GetEditColumnIndex() = 0 ;
	virtual void __fastcall SetEditColumn(const System::UnicodeString AName, int AIndex) = 0 ;
	__property System::UnicodeString EditColumnName = {read=GetEditColumnName};
	__property int EditColumnIndex = {read=GetEditColumnIndex};
};

class PASCALIMPLEMENTATION TCustomBindPosition : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
private:
	System::Classes::_di_IPositionLinkObserver FPositionObserver;
	void __fastcall SetPosControlExpressions(TExpressions* const Value);
	void __fastcall SetPosSourceExpressions(TExpressions* const Value);
	void __fastcall SetPosClearExpressions(TExpressions* const Value);
	TExpressions* FPosControlExpressions;
	TExpressions* FPosSourceExpressions;
	TExpressions* FPosClearExpressions;
	bool FDeferActive;
	bool FActive;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosSourceExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosClearExpressionObjects;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	
protected:
	virtual void __fastcall CheckEditingLink();
	virtual void __fastcall ClearEditingLink();
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall Loaded();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	virtual bool __fastcall CanActivate();
	System::Classes::TComponent* __fastcall GetBindComp();
	void __fastcall PosChanged();
	void __fastcall PosChanging();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	void __fastcall EvaluatePosControl();
	void __fastcall EvaluatePosSource();
	void __fastcall EvaluatePosClear();
	
public:
	__property TExpressions* PosSourceExpressions = {read=FPosSourceExpressions, write=SetPosSourceExpressions};
	__property TExpressions* PosControlExpressions = {read=FPosControlExpressions, write=SetPosControlExpressions};
	__property TExpressions* PosClearExpressions = {read=FPosClearExpressions, write=SetPosClearExpressions};
	__fastcall virtual TCustomBindPosition(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindPosition();
private:
	void *__IBindActivate;	// IBindActivate 
	void *__IBindPosition;	// IBindPosition 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6E9EB32B-4982-4D4D-9510-A0ADFB1BDCC8}
	operator _di_IBindPosition()
	{
		_di_IBindPosition intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindPosition*(void) { return (IBindPosition*)&__IBindPosition; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindPosition : public TCustomBindPosition
{
	typedef TCustomBindPosition inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property SourceMemberName = {default=0};
	__property PosSourceExpressions;
	__property PosControlExpressions;
	__property PosClearExpressions;
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindPosition.Create */ inline __fastcall virtual TBindPosition(System::Classes::TComponent* AOwner) : TCustomBindPosition(AOwner) { }
	/* TCustomBindPosition.Destroy */ inline __fastcall virtual ~TBindPosition() { }
	
};


class PASCALIMPLEMENTATION TCustomBindControlValue : public TExpressionsBindComponent
{
	typedef TExpressionsBindComponent inherited;
	
private:
	bool FTrack;
	System::Classes::_di_IControlValueObserver FControlValueObserver;
	int FUpdateCounter;
	bool FDeferActive;
	bool FActive;
	void __fastcall SetTrack(const bool Value);
	bool __fastcall GetTrack();
	void __fastcall UpdateTrack();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall GetUpdating();
	void __fastcall EvaluateParse();
	void __fastcall EvaluateClear();
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	virtual void __fastcall CheckEditingLink();
	virtual void __fastcall ClearEditingLink();
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall Loaded();
	void __fastcall ValueChanged();
	void __fastcall EvaluateFormat();
	
public:
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
	__property bool Track = {read=GetTrack, write=SetTrack, nodefault};
	__fastcall virtual TCustomBindControlValue(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindControlValue();
private:
	void *__IBindTrack;	// IBindTrack 
	void *__IBindControlValue;	// IBindControlValue 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EE337E7-C25E-4900-90C3-DA2EE9F33954}
	operator _di_IBindTrack()
	{
		_di_IBindTrack intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindTrack*(void) { return (IBindTrack*)&__IBindTrack; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ABDF3DA4-7A87-44F3-9589-1610207529F7}
	operator _di_IBindControlValue()
	{
		_di_IBindControlValue intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindControlValue*(void) { return (IBindControlValue*)&__IBindControlValue; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindControlValue : public TCustomBindControlValue
{
	typedef TCustomBindControlValue inherited;
	
__published:
	__property Track;
	__property ControlComponent;
	__property SourceComponent;
	__property SourceMemberName = {default=0};
	__property FormatExpressions;
	__property ParseExpressions;
	__property ClearExpressions;
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindControlValue.Create */ inline __fastcall virtual TBindControlValue(System::Classes::TComponent* AOwner) : TCustomBindControlValue(AOwner) { }
	/* TCustomBindControlValue.Destroy */ inline __fastcall virtual ~TBindControlValue() { }
	
};


enum DECLSPEC_DENUM TFillItemMode : unsigned char { fmFill, fmInsert, fmAdd, fmUpdate };

typedef void __fastcall (__closure *TFillListItemEvent)(System::TObject* Sender, const _di_IBindListEditorItem AEditor);

class PASCALIMPLEMENTATION TCustomBindList : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
private:
	_di_IBindListEditorCommon FBindListEditor;
	int FDeprecatedBufferCount;
	TExpressions* FFormatExpressions;
	TExpressions* FFormatControlExpressions;
	TExpressions* FClearControlExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FFormatControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FClearControlExpressionObjects;
	bool FDeferActive;
	bool FActive;
	bool FAutoFill;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	System::UnicodeString FEditor;
	TFillListItemEvent FOnFilledListItem;
	TFillListItemEvent FOnFillingListItem;
	System::Classes::TNotifyEvent FOnFillingList;
	System::Classes::TNotifyEvent FOnFilledList;
	void __fastcall SetAutoFill(const bool Value);
	void __fastcall SetFormatExpressions(TExpressions* const Value);
	void __fastcall EvaluateExpressionItem(TExpressionItem* AItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, System::Bindings::Evalprotocol::_di_IScope AEnumScope)/* overload */;
	void __fastcall EvaluateExpressions(System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression)/* overload */;
	_di_IBindListEditorCommon __fastcall GetBindListEditor();
	void __fastcall SetClearControlExpressions(TExpressions* const Value);
	void __fastcall SetFormatControlExpressions(TExpressions* const Value);
	void __fastcall EvaluateClearControl();
	void __fastcall EvaluateFormatControl();
	void __fastcall SetEditor(const System::UnicodeString Value);
	void __fastcall SetBindListEditor(const _di_IBindListEditorCommon AEditor);
	
protected:
	virtual bool __fastcall IsLinked();
	void __fastcall DoFilledListItem(const _di_IBindListEditor AEditor);
	void __fastcall DoFillingListItem(const _di_IBindListEditor AEditor);
	void __fastcall DoFilledList();
	void __fastcall DoFillingList();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall FillListItem(const _di_IBindListEditor AEditor, const System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::Bindings::Evalprotocol::_di_IScope AEditorScope, TFillItemMode AMode);
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetActive();
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall SetActive(bool Value);
	virtual bool __fastcall TryGetBindListEditor(/* out */ _di_IBindListEditorCommon &AEditor);
	__property _di_IBindListEditorCommon BindListEditor = {read=FBindListEditor, write=SetBindListEditor};
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__property TExpressions* FormatExpressions = {read=FFormatExpressions, write=SetFormatExpressions};
	__property TExpressions* FormatControlExpressions = {read=FFormatControlExpressions, write=SetFormatControlExpressions};
	__property TExpressions* ClearControlExpressions = {read=FClearControlExpressions, write=SetClearControlExpressions};
	__fastcall virtual TCustomBindList(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindList();
	void __fastcall ClearList();
	void __fastcall FillList();
	bool __fastcall CanInsert();
	bool __fastcall CanUpdate();
	void __fastcall InsertItem(bool Select = true);
	void __fastcall UpdateItem();
	void __fastcall AddItem(bool Select = true);
	virtual void __fastcall ExecuteAssignToSourceExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType);
	virtual void __fastcall ExecuteAssignToControlExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	virtual void __fastcall EvaluateControlExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	virtual void __fastcall EvaluateSourceExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	void __fastcall ResetList();
	__property int BufferCount = {read=FDeprecatedBufferCount, write=FDeprecatedBufferCount, default=-1};
	__property bool AutoFill = {read=FAutoFill, write=SetAutoFill, default=1};
	__property System::UnicodeString Editor = {read=FEditor, write=SetEditor};
	__property TFillListItemEvent OnFillingListItem = {read=FOnFillingListItem, write=FOnFillingListItem};
	__property TFillListItemEvent OnFilledListItem = {read=FOnFilledListItem, write=FOnFilledListItem};
	__property System::Classes::TNotifyEvent OnFillingList = {read=FOnFillingList, write=FOnFillingList};
	__property System::Classes::TNotifyEvent OnFilledList = {read=FOnFilledList, write=FOnFilledList};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  EvaluateControlExpression(System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback){ TCommonBindComponent::EvaluateControlExpression(AEditorScope, AEditorExpression, ACallback); }
	inline void __fastcall  EvaluateSourceExpression(System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::UnicodeString AEnumExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback){ TCommonBindComponent::EvaluateSourceExpression(ASourceScope, AEnumExpression, ACallback); }
	
private:
	void *__IBindActivate;	// IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindList : public TCustomBindList
{
	typedef TCustomBindList inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property SourceMemberName = {default=0};
	__property FormatExpressions;
	__property FormatControlExpressions;
	__property ClearControlExpressions;
	__property AutoFill = {default=1};
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property Editor = {default=0};
public:
	/* TCustomBindList.Create */ inline __fastcall virtual TBindList(System::Classes::TComponent* AOwner) : TCustomBindList(AOwner) { }
	/* TCustomBindList.Destroy */ inline __fastcall virtual ~TBindList() { }
	
};


class PASCALIMPLEMENTATION TCustomBindListLookup : public TCustomBindList
{
	typedef TCustomBindList inherited;
	
private:
	System::UnicodeString FLookupValueSourceExpression;
	System::UnicodeString FLookupValueSourceMemberName;
	void __fastcall SetLookupValueSourceMemberName(const System::UnicodeString Value);
	void __fastcall SetLookupValueSourceExpression(const System::UnicodeString Value);
	void __fastcall CheckLookupList();
	
protected:
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall FillListItem(const _di_IBindListEditor AEditor, const System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::Bindings::Evalprotocol::_di_IScope AEditorScope, TFillItemMode AMode);
	virtual bool __fastcall TryGetBindListEditor(/* out */ _di_IBindListEditorCommon &AEditor);
	
public:
	System::Rtti::TValue __fastcall GetSelectedValue();
	__property System::UnicodeString LookupValueSourceExpression = {read=FLookupValueSourceExpression, write=SetLookupValueSourceExpression};
	__property System::UnicodeString LookupValueSourceMemberName = {read=FLookupValueSourceMemberName, write=SetLookupValueSourceMemberName};
public:
	/* TCustomBindList.Create */ inline __fastcall virtual TCustomBindListLookup(System::Classes::TComponent* AOwner) : TCustomBindList(AOwner) { }
	/* TCustomBindList.Destroy */ inline __fastcall virtual ~TCustomBindListLookup() { }
	
};


class PASCALIMPLEMENTATION TCustomBindListLink : public TCustomBindList
{
	typedef TCustomBindList inherited;
	
private:
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FParseExpressionObjects;
	TExpressions* FParseExpressions;
	TExpressions* FPosSourceExpressions;
	TExpressions* FPosControlExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosSourceExpressionObjects;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	TControlObserver* FControlObserver;
	int FUpdateCounter;
	int FDeprecatedBufferCount;
	int FLockPosControl;
	void __fastcall SetPosControlExpressions(TExpressions* const Value);
	void __fastcall SetPosSourceExpressions(TExpressions* const Value);
	void __fastcall SetParseExpressions(TExpressions* const Value);
	void __fastcall FillRecord(const System::Bindings::Evalprotocol::_di_IScope ASourceScope, const System::Bindings::Evalprotocol::_di_IScope AEditorScope);
	void __fastcall ClearModified();
	bool __fastcall RequiresControlHandler();
	void __fastcall CheckEditingLink();
	
protected:
	virtual bool __fastcall IsLinked();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall UpdateExpressions();
	System::Classes::TComponent* __fastcall GetBindComp();
	void __fastcall PosChanged();
	void __fastcall PosChanging();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	void __fastcall EvaluatePosControl();
	void __fastcall EvaluatePosSource();
	void __fastcall EvaluatePosClear();
	bool __fastcall GetUpdating();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsRequired();
	void __fastcall SetIsReadOnly(bool Value);
	bool __fastcall IsValidChar(System::WideChar AKey);
	bool __fastcall GetCanModify();
	void __fastcall SetModified();
	bool __fastcall GetIsModified();
	bool __fastcall Edit();
	bool __fastcall GetIsEditing();
	void __fastcall Reset();
	void __fastcall UpdateRecord();
	void __fastcall EvaluateParse(const System::UnicodeString AMemberName);
	void __fastcall EvaluateFormat(const System::UnicodeString AMemberName);
	void __fastcall EvaluateClear(const System::UnicodeString AMemberName);
	virtual void __fastcall ClearEditingLink();
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
	void __fastcall UpdateList();
	
public:
	__fastcall virtual TCustomBindListLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindListLink();
	HIDESBASE void __fastcall ResetList();
	virtual void __fastcall ExecuteAssignToSourceExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType);
	__property System::Classes::TComponent* ControlComponent = {read=GetControlComponent, write=SetControlComponent};
	__property TExpressions* PosSourceExpressions = {read=FPosSourceExpressions, write=SetPosSourceExpressions};
	__property TExpressions* PosControlExpressions = {read=FPosControlExpressions, write=SetPosControlExpressions};
	__property TExpressions* ParseExpressions = {read=FParseExpressions, write=SetParseExpressions};
private:
	void *__IBindListUpdate;	// IBindListUpdate 
	void *__IBindLink;	// IBindLink 
	void *__IBindPosition;	// IBindPosition 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {01EED9E9-F0BD-4752-A6BA-F79EF46ABE55}
	operator _di_IBindListUpdate()
	{
		_di_IBindListUpdate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindListUpdate*(void) { return (IBindListUpdate*)&__IBindListUpdate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4E952D1B-0D23-41C4-8DF0-D24C4C325D5C}
	operator _di_IBindLink()
	{
		_di_IBindLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindLink*(void) { return (IBindLink*)&__IBindLink; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6E9EB32B-4982-4D4D-9510-A0ADFB1BDCC8}
	operator _di_IBindPosition()
	{
		_di_IBindPosition intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindPosition*(void) { return (IBindPosition*)&__IBindPosition; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindListLink : public TCustomBindListLink
{
	typedef TCustomBindListLink inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property FormatExpressions;
	__property ParseExpressions;
	__property PosControlExpressions;
	__property PosSourceExpressions;
	__property FormatControlExpressions;
	__property ClearControlExpressions;
	__property SourceMemberName = {default=0};
	__property AutoFill = {default=1};
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property Editor = {default=0};
public:
	/* TCustomBindListLink.Create */ inline __fastcall virtual TBindListLink(System::Classes::TComponent* AOwner) : TCustomBindListLink(AOwner) { }
	/* TCustomBindListLink.Destroy */ inline __fastcall virtual ~TBindListLink() { }
	
};


class PASCALIMPLEMENTATION TCustomBindLink : public TExpressionsBindComponent
{
	typedef TExpressionsBindComponent inherited;
	
private:
	int FUpdateCounter;
	TControlObserver* FControlObserver;
	bool FDeferActive;
	bool FActive;
	bool FTrack;
	void __fastcall SetTrack(const bool Value);
	bool __fastcall GetTrack();
	void __fastcall UpdateTrack();
	
protected:
#ifndef _WIN64
	HIDESBASE virtual System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes();
#else /* _WIN64 */
	HIDESBASE virtual System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes();
#endif /* _WIN64 */
	virtual void __fastcall UpdateExpressions();
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall CheckEditingLink();
	virtual void __fastcall ClearEditingLink();
	virtual void __fastcall UpdateControlChanging();
	bool __fastcall GetUpdating();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsRequired();
	void __fastcall SetIsReadOnly(bool Value);
	bool __fastcall IsValidChar(System::WideChar AKey);
	bool __fastcall GetCanModify();
	void __fastcall ClearModified();
	void __fastcall SetModified();
	bool __fastcall GetIsModified();
	bool __fastcall Edit();
	bool __fastcall GetIsEditing();
	void __fastcall Reset();
	void __fastcall UpdateRecord();
	virtual bool __fastcall GetActive();
	System::Classes::TComponent* __fastcall GetBindComp();
	void __fastcall EvaluateParse(const System::UnicodeString AMemberName);
	void __fastcall EvaluateFormat(const System::UnicodeString AMemberName);
	void __fastcall EvaluateClear(const System::UnicodeString AMemberName);
	virtual void __fastcall SetActive(bool Value);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
	
public:
	__fastcall virtual TCustomBindLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindLink();
	virtual void __fastcall Loaded();
	System::Bindings::Evalprotocol::_di_IValue __fastcall EvaluateControl();
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property bool Track = {read=GetTrack, write=SetTrack, nodefault};
private:
	void *__IBindTrack;	// IBindTrack 
	void *__IBindActivate;	// IBindActivate 
	void *__IBindLink;	// IBindLink 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7EE337E7-C25E-4900-90C3-DA2EE9F33954}
	operator _di_IBindTrack()
	{
		_di_IBindTrack intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindTrack*(void) { return (IBindTrack*)&__IBindTrack; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4E952D1B-0D23-41C4-8DF0-D24C4C325D5C}
	operator _di_IBindLink()
	{
		_di_IBindLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindLink*(void) { return (IBindLink*)&__IBindLink; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindLink : public TCustomBindLink
{
	typedef TCustomBindLink inherited;
	
protected:
	virtual bool __fastcall CanActivate();
	
__published:
	__property SourceMemberName = {default=0};
	__property ControlComponent;
	__property SourceComponent;
	__property ParseExpressions;
	__property FormatExpressions;
	__property ClearExpressions;
	__property AutoActivate = {default=1};
	__property Track;
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindLink.Create */ inline __fastcall virtual TBindLink(System::Classes::TComponent* AOwner) : TCustomBindLink(AOwner) { }
	/* TCustomBindLink.Destroy */ inline __fastcall virtual ~TBindLink() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TCollectionEnumerator__1 : public System::Generics::Collections::TEnumerator__1<T>
{
	typedef System::Generics::Collections::TEnumerator__1<T> inherited;
	
private:
	System::Classes::TCollectionEnumerator* FCollectionEnumerator;
	
public:
	__fastcall TCollectionEnumerator__1(System::Classes::TCollection* ACollection);
	__fastcall virtual ~TCollectionEnumerator__1();
	virtual T __fastcall DoGetCurrent();
	virtual bool __fastcall DoMoveNext();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFillBreakGroupItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FDisplayText;
	System::UnicodeString FMinValue;
	System::UnicodeString FMaxValue;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
__published:
	__property System::UnicodeString DisplayText = {read=FDisplayText, write=FDisplayText};
	__property System::UnicodeString MinValue = {read=FMinValue, write=FMinValue};
	__property System::UnicodeString MaxValue = {read=FMaxValue, write=FMaxValue};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TFillBreakGroupItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TFillBreakGroupItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFillBreakGroups : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
	
__published:
	typedef TCollectionEnumerator__1<TFillBreakGroupItem*>* TEnumerator;
	
	
public:
	TFillBreakGroupItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TFillBreakGroupItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TFillBreakGroupItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	
public:
	HIDESBASE TCollectionEnumerator__1<TFillBreakGroupItem*>* __fastcall GetEnumerator();
	TFillBreakGroupItem* __fastcall AddItem();
	TFillBreakGroupItem* __fastcall FindItem(const System::Rtti::TValue &AValue);
	__property TFillBreakGroupItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TFillBreakGroups(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFillBreakGroups() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TEvalEnumeratorToEditor : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (__closure *TOnEvalErrorEvent)(System::Sysutils::Exception* AException);
	
	
private:
	bool FUseEvalShortcuts;
	System::Bindings::Expression::TBindingExpression* FBindingExpression;
	bool FHaveEvalShortcut;
	TEvalShortcutEnumeratorToEditor* FEvalShortcut;
	_di_IScopeRecordEnumerator FSource;
	System::UnicodeString FSourceMemberName;
	_di_IBindListEditor FEditor;
	System::UnicodeString FEditorMemberName;
	bool FCustom;
	TOnEvalErrorEvent FOnEvalError;
	void __fastcall Evaluate()/* overload */;
	void __fastcall CheckEvalShortcut();
	
public:
	__fastcall TEvalEnumeratorToEditor(bool AUseEvalShortcuts, const _di_IScopeRecordEnumerator ASource, const System::UnicodeString ASourceMemberName, const _di_IBindListEditor AEditor, const System::UnicodeString AEditorMemberName, bool ACustom, const TOnEvalErrorEvent AOnEvalError, System::Bindings::Expression::TBindingExpression* const ABindingExpression);
	__fastcall virtual ~TEvalEnumeratorToEditor();
	__property _di_IScopeRecordEnumerator Source = {read=FSource};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName};
	__property _di_IBindListEditor Editor = {read=FEditor};
	__property System::UnicodeString EditorMemberName = {read=FEditorMemberName};
	__property bool UseEvalShortcuts = {read=FUseEvalShortcuts, nodefault};
	__property System::Bindings::Expression::TBindingExpression* Expression = {read=FBindingExpression};
	__property TOnEvalErrorEvent OnEvalError = {read=FOnEvalError};
	__property bool Custom = {read=FCustom, nodefault};
};


class PASCALIMPLEMENTATION TEvalEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (__closure *TOnEvalErrorEvent)(System::Sysutils::Exception* AException);
	
	
private:
	bool FUseEvalShortcuts;
	System::Bindings::Expression::TBindingExpression* FBindingExpression;
	bool FHaveEvalShortcut;
	TEvalShortcutEnumerator* FEvalShortcut;
	_di_IScopeRecordEnumerator FSource;
	System::UnicodeString FSourceMemberName;
	bool FCustom;
	TOnEvalErrorEvent FOnEvalError;
	bool __fastcall Evaluate(const TScopeMemberType *ATypes, const int ATypes_High, /* out */ System::Rtti::TValue &AValue)/* overload */;
	void __fastcall CheckEvalShortcut();
	
public:
	__fastcall TEvalEnumerator(bool AUseEvalShortcuts, const _di_IScopeRecordEnumerator ASource, const System::UnicodeString ASourceMemberName, bool ACustom, const TOnEvalErrorEvent AOnEvalError, System::Bindings::Expression::TBindingExpression* const ABindingExpression);
	__fastcall virtual ~TEvalEnumerator();
	__property _di_IScopeRecordEnumerator Source = {read=FSource};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName};
	__property bool UseEvalShortcuts = {read=FUseEvalShortcuts, nodefault};
	__property System::Bindings::Expression::TBindingExpression* Expression = {read=FBindingExpression};
	__property TOnEvalErrorEvent OnEvalError = {read=FOnEvalError};
	__property bool Custom = {read=FCustom, nodefault};
};


class PASCALIMPLEMENTATION TCustomBindGridList : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
	
public:
#ifndef _WIN64
	typedef System::DynamicArray<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> TArrayListCellExpression;
#else /* _WIN64 */
	typedef System::TArray__1<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> TArrayListCellExpression;
#endif /* _WIN64 */
	
	
private:
	TExpressions* FFormatControlExpressions;
	TExpressions* FClearControlExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FFormatControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FClearControlExpressionObjects;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	bool FActive;
	int FDeprecatedBufferCount;
	_di_IBindListEditorCommon FBindListEditor;
	System::UnicodeString FListItemStyle;
	TColumnFormatExpressions* FColumnExpressions;
	bool FDeferActive;
	bool FAutoFill;
	System::UnicodeString FBreakExpression;
	System::UnicodeString FBreakMemberName;
	bool FBreakCustom;
	TFillBreakGroups* FBreakGroups;
	bool FDisableBreakGroups;
	TFillListItemEvent FOnFillingRecord;
	TFillListItemEvent FOnFilledRecord;
	System::Classes::TNotifyEvent FOnFilledRecords;
	System::Classes::TNotifyEvent FOnFillingRecords;
	void __fastcall SetColumnExpressions(TColumnFormatExpressions* const Value);
#ifndef _WIN64
	HIDESBASE System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes(TColumnFormatExpressionItem* AColumnExpressionItem);
	HIDESBASE System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(TColumnFormatExpressionItem* AColumnExpressionItem);
#else /* _WIN64 */
	HIDESBASE System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes(TColumnFormatExpressionItem* AColumnExpressionItem);
	HIDESBASE System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(TColumnFormatExpressionItem* AColumnExpressionItem);
#endif /* _WIN64 */
	_di_IBindListEditorCommon __fastcall GetBindListEditor();
	_di_IScopeRecordEnumerator __fastcall GetScopeRecordEnumerator();
	void __fastcall EvaluateExpressionItem(TColumnFormatExpressionItem* AColumnExpressionItem, TExpressionItem* AItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, System::Bindings::Evalprotocol::_di_IScope AEnumScope);
	void __fastcall EvaluateExpressions(TColumnFormatExpressionItem* AColumnExpressionItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression)/* overload */;
	HIDESBASE void __fastcall EvaluateSourceExpression(System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback)/* overload */;
	void __fastcall SetFormatControlExpressions(TExpressions* const Value);
	void __fastcall SetClearControlExpressions(TExpressions* const Value);
	void __fastcall FormatColumns();
	void __fastcall EvaluateClearControl();
	void __fastcall EvaluateFormatControl();
#ifndef _WIN64
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__1<System::DynamicArray<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> > > ACallback)/* overload */;
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__4<System::DynamicArray<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*>,System::DynamicArray<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*>,TEvalEnumerator*,System::TObject*> > ACallback)/* overload */;
#else /* _WIN64 */
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__1<System::TArray__1<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> > > ACallback)/* overload */;
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__4<System::TArray__1<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*>,System::TArray__1<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*>,TEvalEnumerator*,System::TObject*> > ACallback)/* overload */;
#endif /* _WIN64 */
	void __fastcall SetListItemStyle(const System::UnicodeString Value);
	void __fastcall SetAutoFill(const bool Value);
	void __fastcall SetBreakGroups(TFillBreakGroups* const Value);
	void __fastcall FillRecord2(const _di_IBindListEditor AEditor);
	void __fastcall SetBindListEditor(const _di_IBindListEditorCommon Value);
	
protected:
	virtual bool __fastcall IsLinked();
	virtual void __fastcall DoFilledRecord(const _di_IBindListEditor AEditor);
	virtual void __fastcall DoFillingRecord(const _di_IBindListEditor AEditor);
	virtual void __fastcall DoFilledRecords();
	virtual void __fastcall DoFillingRecords();
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall FillRecords(const _di_IBindListEditor AEditor);
	virtual void __fastcall FillRecord(const _di_IBindListEditor AEditor, System::Sysutils::_di_TProc AEvaluate);
	virtual void __fastcall FillHeaderRecord(const _di_IBindListEditor AEditor, System::Sysutils::_di_TProc AEvaluate);
	virtual bool __fastcall TryGetBindListEditor(/* out */ _di_IBindListEditorCommon &AEditor);
	virtual void __fastcall UpdateControlChanged();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall UpdateExpressions();
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	virtual void __fastcall UpdateControlChanging();
	__property _di_IBindListEditorCommon BindListEditor = {read=FBindListEditor, write=SetBindListEditor};
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__property TColumnFormatExpressions* ColumnExpressions = {read=FColumnExpressions, write=SetColumnExpressions};
	__fastcall virtual TCustomBindGridList(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindGridList();
	void __fastcall InsertItem(bool Select);
	bool __fastcall CanInsert();
	bool __fastcall CanUpdate();
	void __fastcall UpdateItem();
	void __fastcall AddItem(bool Select = true);
	virtual void __fastcall ClearList();
	virtual void __fastcall FillList();
	virtual void __fastcall ResetList();
	HIDESBASE void __fastcall EvaluateControlExpression(TColumnFormatExpressionItem* AColumnExpressionItem, const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	HIDESBASE void __fastcall ExecuteAssignToControlExpression(TColumnFormatExpressionItem* AColumnExpressionItem, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	HIDESBASE void __fastcall EvaluateSourceExpression(TColumnFormatExpressionItem* AColumnExpressionItem, const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	HIDESBASE virtual void __fastcall ExecuteAssignToSourceExpression(TColumnFormatExpressionItem* AColumnExpressionItem, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType);
	__property bool AutoFill = {read=FAutoFill, write=SetAutoFill, default=1};
	__property int BufferCount = {read=FDeprecatedBufferCount, write=FDeprecatedBufferCount, default=-1};
	__property TExpressions* FormatControlExpressions = {read=FFormatControlExpressions, write=SetFormatControlExpressions};
	__property TExpressions* ClearControlExpressions = {read=FClearControlExpressions, write=SetClearControlExpressions};
	__property System::UnicodeString ListItemStyle = {read=FListItemStyle, write=SetListItemStyle};
	__property System::UnicodeString BreakExpression = {read=FBreakExpression, write=FBreakExpression};
	__property System::UnicodeString BreakMemberName = {read=FBreakMemberName, write=FBreakMemberName};
	__property TFillBreakGroups* BreakGroups = {read=FBreakGroups, write=SetBreakGroups};
	__property bool DisableBreakGroups = {read=FDisableBreakGroups, write=FDisableBreakGroups, nodefault};
	__property TFillListItemEvent OnFillingRecord = {read=FOnFillingRecord, write=FOnFillingRecord};
	__property TFillListItemEvent OnFilledRecord = {read=FOnFilledRecord, write=FOnFilledRecord};
	__property System::Classes::TNotifyEvent OnFillingRecords = {read=FOnFillingRecords, write=FOnFillingRecords};
	__property System::Classes::TNotifyEvent OnFilledRecords = {read=FOnFilledRecords, write=FOnFilledRecords};
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  EvaluateSourceExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::EvaluateSourceExpression(AExpression, ACallback, AType); }
	
protected:
	inline void __fastcall  EvaluateControlExpression(System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback){ TCommonBindComponent::EvaluateControlExpression(AEditorScope, AEditorExpression, ACallback); }
	
public:
	inline void __fastcall  EvaluateControlExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::EvaluateControlExpression(AExpression, ACallback, AType); }
	inline void __fastcall  ExecuteAssignToControlExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::ExecuteAssignToControlExpression(AControlExpression, ASourceExpression, ACallback, AType); }
	
private:
	void *__IBindActivate;	// IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindGridList : public TCustomBindGridList
{
	typedef TCustomBindGridList inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property ColumnExpressions;
	__property FormatControlExpressions;
	__property ClearControlExpressions;
	__property AutoFill = {default=1};
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property ListItemStyle = {default=0};
	__property BreakExpression = {default=0};
	__property BreakMemberName = {default=0};
	__property BreakGroups;
public:
	/* TCustomBindGridList.Create */ inline __fastcall virtual TBindGridList(System::Classes::TComponent* AOwner) : TCustomBindGridList(AOwner) { }
	/* TCustomBindGridList.Destroy */ inline __fastcall virtual ~TBindGridList() { }
	
};


class PASCALIMPLEMENTATION TCustomBindGridListLookup : public TCustomBindGridList
{
	typedef TCustomBindGridList inherited;
	
private:
	_di_IBindListLookupEditor FLookupEditor;
	System::Bindings::Expression::TBindingExpression* FLookupExpression;
	System::UnicodeString FLookupValueSourceExpression;
	System::UnicodeString FLookupValueSourceMemberName;
	void __fastcall SetLookupValueSourceMemberName(const System::UnicodeString Value);
	void __fastcall SetLookupValueSourceExpression(const System::UnicodeString Value);
	void __fastcall CheckLookupList();
	
protected:
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall FillRecord(const _di_IBindListEditor AEditor, System::Sysutils::_di_TProc AEvaluate);
	virtual void __fastcall FillRecords(const _di_IBindListEditor AEditor);
	virtual bool __fastcall TryGetBindListEditor(/* out */ _di_IBindListEditorCommon &AEditor);
	
public:
	System::Rtti::TValue __fastcall GetSelectedValue();
	__property System::UnicodeString LookupValueSourceExpression = {read=FLookupValueSourceExpression, write=SetLookupValueSourceExpression};
	__property System::UnicodeString LookupValueSourceMemberName = {read=FLookupValueSourceMemberName, write=SetLookupValueSourceMemberName};
public:
	/* TCustomBindGridList.Create */ inline __fastcall virtual TCustomBindGridListLookup(System::Classes::TComponent* AOwner) : TCustomBindGridList(AOwner) { }
	/* TCustomBindGridList.Destroy */ inline __fastcall virtual ~TCustomBindGridListLookup() { }
	
};


class PASCALIMPLEMENTATION TCustomBindGridListLink : public TCustomBindGridList
{
	typedef TCustomBindGridList inherited;
	
private:
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FParseExpressionObjects;
	TExpressions* FParseExpressions;
	TExpressions* FPosSourceExpressions;
	TExpressions* FPosControlExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosSourceExpressionObjects;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	TControlObserver* FControlObserver;
	int FUpdateCounter;
	int FDeprecatedBufferCount;
	int FLockPosControl;
	void __fastcall SetPosControlExpressions(TExpressions* const Value);
	void __fastcall SetPosSourceExpressions(TExpressions* const Value);
	void __fastcall SetParseExpressions(TExpressions* const Value);
	void __fastcall ClearModified();
	bool __fastcall RequiresControlHandler();
	void __fastcall CheckEditingLink();
	
protected:
	virtual bool __fastcall IsLinked();
	virtual void __fastcall UpdateControlChanging();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall UpdateExpressions();
	System::Classes::TComponent* __fastcall GetBindComp();
	void __fastcall PosChanged();
	void __fastcall PosChanging();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	void __fastcall EvaluatePosControl();
	void __fastcall EvaluatePosSource();
	void __fastcall EvaluatePosClear();
	bool __fastcall GetUpdating();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsRequired();
	void __fastcall SetIsReadOnly(bool Value);
	bool __fastcall IsValidChar(System::WideChar AKey);
	bool __fastcall GetCanModify();
	void __fastcall SetModified();
	bool __fastcall GetIsModified();
	bool __fastcall Edit();
	bool __fastcall GetIsEditing();
	void __fastcall Reset();
	void __fastcall UpdateRecord();
	void __fastcall EvaluateParse(const System::UnicodeString AMemberName);
	void __fastcall EvaluateFormat(const System::UnicodeString AMemberName);
	void __fastcall EvaluateClear(const System::UnicodeString AMemberName);
	virtual void __fastcall ClearEditingLink();
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
	void __fastcall UpdateList();
	
public:
	__fastcall virtual TCustomBindGridListLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindGridListLink();
	virtual void __fastcall ResetList();
	__property System::Classes::TComponent* ControlComponent = {read=GetControlComponent, write=SetControlComponent};
	__property TExpressions* PosSourceExpressions = {read=FPosSourceExpressions, write=SetPosSourceExpressions};
	__property TExpressions* PosControlExpressions = {read=FPosControlExpressions, write=SetPosControlExpressions};
	__property TExpressions* ParseExpressions = {read=FParseExpressions, write=SetParseExpressions};
private:
	void *__IBindListUpdate;	// IBindListUpdate 
	void *__IBindLink;	// IBindLink 
	void *__IBindPosition;	// IBindPosition 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {01EED9E9-F0BD-4752-A6BA-F79EF46ABE55}
	operator _di_IBindListUpdate()
	{
		_di_IBindListUpdate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindListUpdate*(void) { return (IBindListUpdate*)&__IBindListUpdate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4E952D1B-0D23-41C4-8DF0-D24C4C325D5C}
	operator _di_IBindLink()
	{
		_di_IBindLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindLink*(void) { return (IBindLink*)&__IBindLink; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6E9EB32B-4982-4D4D-9510-A0ADFB1BDCC8}
	operator _di_IBindPosition()
	{
		_di_IBindPosition intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindPosition*(void) { return (IBindPosition*)&__IBindPosition; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomBindGridLink : public TActivatedContainedBindComponent
{
	typedef TActivatedContainedBindComponent inherited;
	
	
private:
	_di_IBindListEditorCommon FBindListEditor;
	TControlObserver* FControlObserver;
	int FUpdateCounter;
	TExpressions* FPosSourceExpressions;
	TExpressions* FPosControlExpressions;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FPosSourceExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FFormatControlExpressionObjects;
	System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FClearControlExpressionObjects;
	System::Bindings::Expression::TBindingExpression* FControlExpressionObject;
	TExpressions* FFormatControlExpressions;
	TExpressions* FClearControlExpressions;
	int FLockPosControl;
	TFillListItemEvent FOnFillingRecord;
	TFillListItemEvent FOnFilledRecord;
	void __fastcall SetColumnExpressions(TColumnLinkExpressions* const Value);
#ifndef _WIN64
	HIDESBASE System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes(TColumnLinkExpressionItem* AColumnExpressionItem);
	HIDESBASE System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(TColumnLinkExpressionItem* AColumnExpressionItem);
#else /* _WIN64 */
	HIDESBASE System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetControlScopes(TColumnLinkExpressionItem* AColumnExpressionItem);
	HIDESBASE System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(TColumnLinkExpressionItem* AColumnExpressionItem);
#endif /* _WIN64 */
	_di_IBindListEditorCommon __fastcall GetBindListEditor();
	_di_IScopeRecordEnumerator __fastcall GetScopeRecordEnumerator();
	void __fastcall EvaluateExpressionItem(TColumnLinkExpressionItem* AColumnExpressionItem, TExpressionItem* AItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, System::Bindings::Evalprotocol::_di_IScope AEnumScope);
	void __fastcall EvaluateExpressions(TColumnLinkExpressionItem* AColumnExpressionItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression)/* overload */;
	HIDESBASE void __fastcall EvaluateSourceExpression(System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback)/* overload */;
	System::Bindings::Evalprotocol::_di_IScope __fastcall GetScopeCurrentRecord(TColumnLinkExpressionItem* AColumnExpressionItem);
	void __fastcall SetPosControlExpressions(TExpressions* const Value);
	void __fastcall SetPosSourceExpressions(TExpressions* const Value);
	TColumnLinkExpressionItem* __fastcall FindColumnExpressionItem(int AIndex, System::UnicodeString AName);
	void __fastcall SetClearControlExpressions(TExpressions* const Value);
	void __fastcall SetFormatControlExpressions(TExpressions* const Value);
	void __fastcall EvaluateClearControl();
	void __fastcall EvaluateFormatControl();
	void __fastcall FormatColumns();
	void __fastcall UpdateRow(_di_IBindListVirtualEditor AEditor);
	void __fastcall EvaluateFormatCallback(int ACol, int ARow, System::Bindings::Evalprotocol::_di_IScope AEditorScope, bool ACanCacheExpressions);
#ifndef _WIN64
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__1<System::DynamicArray<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> > > ACallback);
#else /* _WIN64 */
	void __fastcall GetBindingExpressions(const _di_IScopeRecordEnumerator AEnumerator, const _di_IBindListEditor AEditor, System::DelphiInterface<System::Sysutils::TProc__1<System::TArray__1<System::Generics::Collections::TList__1<TEvalEnumeratorToEditor*>*> > > ACallback);
#endif /* _WIN64 */
	System::Bindings::Expression::TBindingExpression* __fastcall CreateUnmanagedExpression(TColumnLinkExpressionItem* AColumnExpressionItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::Bindings::Evalprotocol::_di_IScope AEnumScope, const System::UnicodeString AEnumExpression);
	System::Bindings::Expression::TBindingExpression* __fastcall CreateUnmanagedExpressionItem(TColumnLinkExpressionItem* AColumnExpressionItem, TExpressionItem* AItem, System::Bindings::Evalprotocol::_di_IScope AEditorScope, System::Bindings::Evalprotocol::_di_IScope AEnumScope);
	void __fastcall SetBindListEditor(const _di_IBindListEditorCommon Value);
	System::Generics::Collections::TDictionary__2<int,System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>*>* FUnmanagedColumnExpressions;
	int FDeprecatedBufferCount;
	TColumnLinkExpressions* FColumnExpressions;
	System::UnicodeString FEditColumnName;
	int FEditColumnIndex;
	System::TVarRec FEditColumnCurrent;
	bool FDeferActive;
	bool FActive;
	bool FAutoFill;
	void __fastcall SetAutoFill(const bool Value);
	System::UnicodeString __fastcall UpdateColumnCurrent();
	
protected:
	virtual bool __fastcall IsLinked();
	bool __fastcall TryGetBindListEditor(/* out */ _di_IBindListEditorCommon &AEditor);
	virtual void __fastcall DoFillingRecord(const _di_IBindListEditor AEditor);
	virtual void __fastcall DoFilledRecord(const _di_IBindListEditor AEditor);
	virtual void __fastcall FillRecord(const _di_IBindListEditor AEditor, System::Sysutils::_di_TProc AEvaluate);
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall UpdateControlChanging();
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall CheckEditingLink();
	virtual void __fastcall ClearEditingLink();
	virtual void __fastcall FreeExpressionsObjects();
	virtual void __fastcall UpdateExpressions();
	System::Classes::TComponent* __fastcall GetBindComp();
	void __fastcall PosChanged();
	void __fastcall PosChanging();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	void __fastcall EvaluatePosControl();
	void __fastcall EvaluatePosSource();
	void __fastcall EvaluatePosClear();
	bool __fastcall GetUpdating();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	bool __fastcall IsRequired();
	void __fastcall SetIsReadOnly(bool Value);
	bool __fastcall IsValidChar(System::WideChar AKey);
	bool __fastcall GetCanModify();
	void __fastcall SetModified();
	void __fastcall ClearModified();
	bool __fastcall GetIsModified();
	bool __fastcall Edit();
	bool __fastcall GetIsEditing();
	void __fastcall Reset();
	void __fastcall UpdateRecord();
	void __fastcall EvaluateParse(const System::UnicodeString AMemberName);
	void __fastcall EvaluateFormat(const System::UnicodeString AMemberName);
	void __fastcall EvaluateClear(const System::UnicodeString AMemberName);
	System::Classes::_di_IEditFormatLink __fastcall GetFormatLink();
	System::UnicodeString __fastcall GetEditColumnName();
	int __fastcall GetEditColumnIndex();
	void __fastcall SetEditColumn(const System::UnicodeString AName, int AIndex);
	void __fastcall UpdateList();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	__property _di_IBindListEditorCommon BindListEditor = {read=FBindListEditor, write=SetBindListEditor};
	
public:
	__fastcall virtual TCustomBindGridLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindGridLink();
	virtual void __fastcall Loaded();
	virtual void __fastcall ClearGrid();
	virtual void __fastcall FillGrid();
	virtual void __fastcall ResetGrid();
	void __fastcall ResetColumns();
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* AControl);
	HIDESBASE void __fastcall EvaluateControlExpression(TColumnLinkExpressionItem* AColumnExpressionItem, const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	HIDESBASE void __fastcall ExecuteAssignToControlExpression(TColumnLinkExpressionItem* AColumnExpressionItem, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	HIDESBASE void __fastcall EvaluateSourceExpression(TColumnLinkExpressionItem* AColumnExpressionItem, const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType)/* overload */;
	void __fastcall ExecuteAssignItemToSourceExpression(TColumnLinkExpressionItem* AColumnExpressionItem, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType);
	__property TColumnLinkExpressions* ColumnExpressions = {read=FColumnExpressions, write=SetColumnExpressions};
	__property bool AutoFill = {read=FAutoFill, write=SetAutoFill, default=1};
	__property TExpressions* PosSourceExpressions = {read=FPosSourceExpressions, write=SetPosSourceExpressions};
	__property TExpressions* PosControlExpressions = {read=FPosControlExpressions, write=SetPosControlExpressions};
	__property TExpressions* FormatControlExpressions = {read=FFormatControlExpressions, write=SetFormatControlExpressions};
	__property TExpressions* ClearControlExpressions = {read=FClearControlExpressions, write=SetClearControlExpressions};
	__property int BufferCount = {read=FDeprecatedBufferCount, write=FDeprecatedBufferCount, default=-1};
	__property TFillListItemEvent OnFillingRecord = {read=FOnFillingRecord, write=FOnFillingRecord};
	__property TFillListItemEvent OnFilledRecord = {read=FOnFilledRecord, write=FOnFilledRecord};
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  EvaluateSourceExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::EvaluateSourceExpression(AExpression, ACallback, AType); }
	
protected:
	inline void __fastcall  EvaluateControlExpression(System::Bindings::Evalprotocol::_di_IScope AEditorScope, const System::UnicodeString AEditorExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback){ TCommonBindComponent::EvaluateControlExpression(AEditorScope, AEditorExpression, ACallback); }
	
public:
	inline void __fastcall  EvaluateControlExpression(const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::EvaluateControlExpression(AExpression, ACallback, AType); }
	inline void __fastcall  ExecuteAssignToControlExpression(const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback, TBindCompExpressionType AType = (TBindCompExpressionType)(0x0)){ TCommonBindComponent::ExecuteAssignToControlExpression(AControlExpression, ASourceExpression, ACallback, AType); }
	
private:
	void *__IBindActivate;	// IBindActivate 
	void *__IBindListUpdate;	// IBindListUpdate 
	void *__IBindLinkColumns;	// IBindLinkColumns 
	void *__IBindLink;	// IBindLink 
	void *__IBindPosition;	// IBindPosition 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {01EED9E9-F0BD-4752-A6BA-F79EF46ABE55}
	operator _di_IBindListUpdate()
	{
		_di_IBindListUpdate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindListUpdate*(void) { return (IBindListUpdate*)&__IBindListUpdate; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F0FAEC32-EC29-45C1-9490-1DC9CD169DD4}
	operator _di_IBindLinkColumns()
	{
		_di_IBindLinkColumns intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindLinkColumns*(void) { return (IBindLinkColumns*)&__IBindLinkColumns; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4E952D1B-0D23-41C4-8DF0-D24C4C325D5C}
	operator _di_IBindLink()
	{
		_di_IBindLink intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindLink*(void) { return (IBindLink*)&__IBindLink; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6E9EB32B-4982-4D4D-9510-A0ADFB1BDCC8}
	operator _di_IBindPosition()
	{
		_di_IBindPosition intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindPosition*(void) { return (IBindPosition*)&__IBindPosition; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindGridLink : public TCustomBindGridLink
{
	typedef TCustomBindGridLink inherited;
	
__published:
	__property ControlComponent;
	__property SourceComponent;
	__property ColumnExpressions;
	__property PosControlExpressions;
	__property PosSourceExpressions;
	__property FormatControlExpressions;
	__property ClearControlExpressions;
	__property AutoFill = {default=1};
	__property AutoActivate = {default=1};
	__property OnAssigningValue;
	__property OnAssignedValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
public:
	/* TCustomBindGridLink.Create */ inline __fastcall virtual TBindGridLink(System::Classes::TComponent* AOwner) : TCustomBindGridLink(AOwner) { }
	/* TCustomBindGridLink.Destroy */ inline __fastcall virtual ~TBindGridLink() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TColumnFormatExpressionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FColumnName;
	int FColumnIndex;
	TExpressions* FFormatCellExpressions;
	TExpressions* FFormatColumnExpressions;
	System::UnicodeString FSourceMemberName;
	System::UnicodeString FControlMemberName;
	TExpressions* FFormatCellHeaderExpressions;
	TColumnFormatExpressions* __fastcall GetColumnExpressions();
	System::UnicodeString __fastcall GetName();
	void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall SetFormatCellExpressions(TExpressions* const Value);
	void __fastcall SetFormatColumnExpressions(TExpressions* const Value);
	int __fastcall GetColumnIndex();
	void __fastcall SetColumnIndex(int Value);
	void __fastcall SetFormatCellHeaderExpressions(TExpressions* const Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TColumnFormatExpressionItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TColumnFormatExpressionItem();
	__property TColumnFormatExpressions* ColumnExpressions = {read=GetColumnExpressions};
	
__published:
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString ColumnName = {read=FColumnName, write=FColumnName};
	__property int ColumnIndex = {read=GetColumnIndex, write=SetColumnIndex, nodefault};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName, write=FSourceMemberName};
	__property System::UnicodeString ControlMemberName = {read=FControlMemberName, write=FControlMemberName};
	__property TExpressions* FormatCellExpressions = {read=FFormatCellExpressions, write=SetFormatCellExpressions};
	__property TExpressions* FormatCellHeaderExpressions = {read=FFormatCellHeaderExpressions, write=SetFormatCellHeaderExpressions};
	__property TExpressions* FormatColumnExpressions = {read=FFormatColumnExpressions, write=SetFormatColumnExpressions};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TColumnLinkExpressionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FName;
	System::UnicodeString FColumnName;
	int FColumnIndex;
	TExpressions* FFormatCellExpressions;
	TExpressions* FFormatColumnExpressions;
	TExpressions* FParseCellExpressions;
	System::UnicodeString FSourceMemberName;
	System::UnicodeString FControlMemberName;
	TColumnLinkExpressions* __fastcall GetColumnExpressions();
	System::UnicodeString __fastcall GetName();
	void __fastcall SetName(const System::UnicodeString Value);
	void __fastcall SetFormatCellExpressions(TExpressions* const Value);
	void __fastcall SetParseExpressions(TExpressions* const Value);
	int __fastcall GetColumnIndex();
	void __fastcall SetColumnIndex(int Value);
	void __fastcall SetFormatColumnExpressions(TExpressions* const Value);
	void __fastcall SetSourceMemberName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__fastcall virtual TColumnLinkExpressionItem(System::Classes::TCollection* Collection);
	__fastcall virtual ~TColumnLinkExpressionItem();
	__property TColumnLinkExpressions* ColumnExpressions = {read=GetColumnExpressions};
	
__published:
	__property System::UnicodeString Name = {read=GetName, write=SetName};
	__property System::UnicodeString ColumnName = {read=FColumnName, write=FColumnName};
	__property int ColumnIndex = {read=GetColumnIndex, write=SetColumnIndex, nodefault};
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName, write=SetSourceMemberName};
	__property System::UnicodeString ControlMemberName = {read=FControlMemberName, write=FControlMemberName};
	__property TExpressions* ParseCellExpressions = {read=FParseCellExpressions, write=SetParseExpressions};
	__property TExpressions* FormatCellExpressions = {read=FFormatCellExpressions, write=SetFormatCellExpressions};
	__property TExpressions* FormatColumnExpressions = {read=FFormatColumnExpressions, write=SetFormatColumnExpressions};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TColumnFormatExpressions : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
	
__published:
	typedef TCollectionEnumerator__1<TColumnFormatExpressionItem*>* TEnumerator;
	
	
public:
	TColumnFormatExpressionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FModified;
	HIDESBASE TColumnFormatExpressionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TColumnFormatExpressionItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	__property bool Modified = {read=FModified, nodefault};
	
public:
	HIDESBASE TCollectionEnumerator__1<TColumnFormatExpressionItem*>* __fastcall GetEnumerator();
	TColumnFormatExpressionItem* __fastcall AddExpression();
	__property TColumnFormatExpressionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TColumnFormatExpressions(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TColumnFormatExpressions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TColumnLinkExpressions : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
	
__published:
	typedef TCollectionEnumerator__1<TColumnLinkExpressionItem*>* TEnumerator;
	
	
public:
	TColumnLinkExpressionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FModified;
	HIDESBASE TColumnLinkExpressionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TColumnLinkExpressionItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	__property bool Modified = {read=FModified, nodefault};
	
public:
	HIDESBASE TCollectionEnumerator__1<TColumnLinkExpressionItem*>* __fastcall GetEnumerator();
	TColumnLinkExpressionItem* __fastcall AddExpression();
	__property TColumnLinkExpressionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TColumnLinkExpressions(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TColumnLinkExpressions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TExpressionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FControlExpression;
	System::UnicodeString FSourceExpression;
	bool FCustom;
	TExpressions* __fastcall GetExpressions();
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__property TExpressions* Expressions = {read=GetExpressions};
	__property bool Custom = {read=FCustom, write=FCustom, nodefault};
	
__published:
	__property System::UnicodeString ControlExpression = {read=FControlExpression, write=FControlExpression};
	__property System::UnicodeString SourceExpression = {read=FSourceExpression, write=FSourceExpression};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TExpressionItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TExpressionItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TExpressionItemDir : public TExpressionItem
{
	typedef TExpressionItem inherited;
	
private:
	TExpressionDirection FDirection;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
__published:
	__property TExpressionDirection Direction = {read=FDirection, write=FDirection, default=0};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TExpressionItemDir(System::Classes::TCollection* Collection) : TExpressionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TExpressionItemDir() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindCompExpressionCollection : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	/* TOwnedCollection.Create */ inline __fastcall TBindCompExpressionCollection(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TBindCompExpressionCollection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TExpressions : public TBindCompExpressionCollection
{
	typedef TBindCompExpressionCollection inherited;
	
	
__published:
	typedef TCollectionEnumerator__1<TExpressionItem*>* TEnumerator;
	
	
public:
	TExpressionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TExpressionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TExpressionItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	
public:
	HIDESBASE TCollectionEnumerator__1<TExpressionItem*>* __fastcall GetEnumerator();
	TExpressionItem* __fastcall AddExpression();
	__property TExpressionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TExpressions(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : TBindCompExpressionCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TExpressions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TExpressionsDir : public TBindCompExpressionCollection
{
	typedef TBindCompExpressionCollection inherited;
	
public:
	TExpressionItemDir* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TExpressionItemDir* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TExpressionItemDir* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	
public:
	HIDESBASE TExpressionDirEnumerator* __fastcall GetEnumerator();
	TExpressionItemDir* __fastcall AddExpression();
	__property TExpressionItemDir* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TExpressionsDir(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : TBindCompExpressionCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TExpressionsDir() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TExpressionDirEnumerator : public System::Classes::TCollectionEnumerator
{
	typedef System::Classes::TCollectionEnumerator inherited;
	
public:
	HIDESBASE TExpressionItemDir* __fastcall GetCurrent();
	__property TExpressionItemDir* Current = {read=GetCurrent};
public:
	/* TCollectionEnumerator.Create */ inline __fastcall TExpressionDirEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TExpressionDirEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TBindComponentDelegate : public TContainedBindComponent
{
	typedef TContainedBindComponent inherited;
	
private:
	TBindCompAssigningValueEvent __fastcall GetOnAssigningValue();
	TBindCompEvalErrorEvent __fastcall GetOnEvalError();
	void __fastcall SetOnAssigningValue(const TBindCompAssigningValueEvent Value);
	void __fastcall SetOnEvalError(const TBindCompEvalErrorEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnActivated();
	System::Classes::TNotifyEvent __fastcall GetOnActivating();
	void __fastcall SetOnActivated(const System::Classes::TNotifyEvent Value);
	void __fastcall SetOnActivating(const System::Classes::TNotifyEvent Value);
	TBindCompAssignedValueEvent __fastcall GetOnAssignedValue();
	void __fastcall SetOnAssignedValue(const TBindCompAssignedValueEvent Value);
	
protected:
	virtual void __fastcall Reactivate() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender) = 0 ;
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender) = 0 ;
	virtual void __fastcall Activated(System::Classes::TComponent* Sender);
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender) = 0 ;
	virtual bool __fastcall RequiresControlHandler() = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#else /* _WIN64 */
	virtual System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#endif /* _WIN64 */
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual bool __fastcall GetUseEvalShortcuts();
	
public:
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates() = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates() = 0 ;
#endif /* _WIN64 */
	__property TBindCompAssigningValueEvent OnAssigningValue = {read=GetOnAssigningValue, write=SetOnAssigningValue};
	__property TBindCompAssignedValueEvent OnAssignedValue = {read=GetOnAssignedValue, write=SetOnAssignedValue};
	__property TBindCompEvalErrorEvent OnEvalError = {read=GetOnEvalError, write=SetOnEvalError};
	__property System::Classes::TNotifyEvent OnActivating = {read=GetOnActivating, write=SetOnActivating};
	__property System::Classes::TNotifyEvent OnActivated = {read=GetOnActivated, write=SetOnActivated};
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TBindComponentDelegate(System::Classes::TComponent* AOwner) : TContainedBindComponent(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TBindComponentDelegate() { }
	
};


class PASCALIMPLEMENTATION TLinkControlDelegate : public TBindComponentDelegate
{
	typedef TBindComponentDelegate inherited;
	
protected:
	virtual System::Classes::TComponent* __fastcall GetControlComponent();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	virtual System::UnicodeString __fastcall GetControlComponentMemberName();
	virtual void __fastcall SetActive(bool AValue);
	virtual void __fastcall BindActivate(bool AValue);
	
public:
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TLinkControlDelegate(System::Classes::TComponent* AOwner) : TBindComponentDelegate(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TLinkControlDelegate() { }
	
private:
	void *__IBindActivate;	// IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	
};


class PASCALIMPLEMENTATION TLinkControlToFieldDelegate : public TLinkControlDelegate
{
	typedef TLinkControlDelegate inherited;
	
protected:
	void __fastcall SetDataSource(TBaseLinkingBindSource* const Value);
	TBaseLinkingBindSource* __fastcall GetDataSource();
	void __fastcall SetSourceMember(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSourceMember();
	virtual bool __fastcall GetDisplaysMultipleSourceMembers();
	
public:
	__property TBaseLinkingBindSource* DataSource = {read=GetDataSource, write=SetDataSource};
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TLinkControlToFieldDelegate(System::Classes::TComponent* AOwner) : TLinkControlDelegate(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TLinkControlToFieldDelegate() { }
	
};


enum DECLSPEC_DENUM TLinkControlToFieldDirection : unsigned char { linkBidirectional, linkDataToControl, linkControlToData };

class PASCALIMPLEMENTATION TCustomLinkControlToField : public TLinkControlToFieldDelegate
{
	typedef TLinkControlToFieldDelegate inherited;
	
private:
	TLinkControlToFieldDirection FDirection;
	TBasicBindComponent* FLookupMemberChange;
	TExpressionsBindComponent* FBinding;
	System::UnicodeString FCustomFormat;
	System::UnicodeString FCustomParse;
	System::UnicodeString FLookupValueFieldName;
	TBaseLinkingBindSource* FLookupDataSource;
	System::UnicodeString FLookupKeyFieldName;
	bool FUseEvalShortcuts;
	bool __fastcall GetAutoActivate();
	void __fastcall SetDirection(const TLinkControlToFieldDirection Value);
	bool __fastcall GetTrack();
	void __fastcall SetTrack(const bool Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	void __fastcall SetCustomParse(const System::UnicodeString Value);
	void __fastcall SetLookupDataSource(TBaseLinkingBindSource* const Value);
	void __fastcall SetLookupKeyFieldName(const System::UnicodeString Value);
	void __fastcall SetLookupValueFieldName(const System::UnicodeString Value);
	bool __fastcall UsingLookup();
	TLinkControlToFieldDirection __fastcall GetDirection();
	void __fastcall SetUseEvalShortcuts(const bool Value);
	
protected:
	virtual void __fastcall Reactivate();
	virtual bool __fastcall AllowBidirectional();
	virtual bool __fastcall CheckAllowBidirectional();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
#ifndef _WIN64
	virtual System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#else /* _WIN64 */
	virtual System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#endif /* _WIN64 */
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual void __fastcall SetAutoActivate(const bool Value);
	virtual System::UnicodeString __fastcall GetControlExpression();
	virtual void __fastcall SetActive(bool Value);
	virtual bool __fastcall GetActive();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetUseEvalShortcuts();
	
public:
	__fastcall virtual TCustomLinkControlToField(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkControlToField();
	virtual void __fastcall ClearExpressionProperties();
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	__property TExpressionsBindComponent* Binding = {read=FBinding};
	__property System::UnicodeString FieldName = {read=GetSourceMember, write=SetSourceMember};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property TLinkControlToFieldDirection Direction = {read=GetDirection, write=SetDirection, default=0};
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property System::Classes::TComponent* Control = {read=GetControlComponent, write=SetControlComponent};
	__property System::UnicodeString ControlMemberName = {read=GetControlComponentMemberName};
	__property bool Track = {read=GetTrack, write=SetTrack, nodefault};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
	__property System::UnicodeString CustomParse = {read=FCustomParse, write=SetCustomParse};
	__property TBaseLinkingBindSource* LookupDataSource = {read=FLookupDataSource, write=SetLookupDataSource};
	__property System::UnicodeString LookupKeyFieldName = {read=FLookupKeyFieldName, write=SetLookupKeyFieldName};
	__property System::UnicodeString LookupValueFieldName = {read=FLookupValueFieldName, write=SetLookupValueFieldName};
	__property bool UseEvalShortcuts = {read=GetUseEvalShortcuts, write=SetUseEvalShortcuts, default=1};
};


class PASCALIMPLEMENTATION TLinkControlToField : public TCustomLinkControlToField
{
	typedef TCustomLinkControlToField inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property Control;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property Direction = {default=0};
	__property Track;
	__property CustomFormat = {default=0};
	__property CustomParse = {default=0};
	__property LookupDataSource;
	__property LookupKeyFieldName = {default=0};
	__property LookupValueFieldName = {default=0};
	__property UseEvalShortcuts = {default=1};
public:
	/* TCustomLinkControlToField.Create */ inline __fastcall virtual TLinkControlToField(System::Classes::TComponent* AOwner) : TCustomLinkControlToField(AOwner) { }
	/* TCustomLinkControlToField.Destroy */ inline __fastcall virtual ~TLinkControlToField() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFormatExpressionItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FSourceMemberName;
	System::UnicodeString FControlMemberName;
	System::UnicodeString FCustomFormat;
	void __fastcall SetControlMemberName(const System::UnicodeString Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	void __fastcall SetSourceMemberName(const System::UnicodeString Value);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TFormatExpressionItem(System::Classes::TCollection* Collection, const System::UnicodeString AControlMemberName, const System::UnicodeString ASourceMemberName, const System::UnicodeString ACustomFormat);
	
__published:
	__property System::UnicodeString SourceMemberName = {read=FSourceMemberName, write=SetSourceMemberName};
	__property System::UnicodeString ControlMemberName = {read=FControlMemberName, write=SetControlMemberName};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TFormatExpressionItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{54BA961D-A606-469E-98BE-0F39E97E98B6}") IControlEditorName  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetControlEditorName(const GUID &AGuid) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFormatExpressions : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
	
__published:
	typedef TCollectionEnumerator__1<TFormatExpressionItem*>* TEnumerator;
	
	
public:
	TFormatExpressionItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	System::DelphiInterface<System::Sysutils::TProc__1<System::Classes::TCollectionItem*> > FOnUpdate;
	HIDESBASE TFormatExpressionItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TFormatExpressionItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	virtual void __fastcall Update(System::Classes::TCollectionItem* AItem);
	
public:
	__fastcall TFormatExpressions(System::Classes::TPersistent* AOwner);
	HIDESBASE TCollectionEnumerator__1<TFormatExpressionItem*>* __fastcall GetEnumerator();
	TFormatExpressionItem* __fastcall AddExpression();
	void __fastcall SourceMemberRenaming(const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	__property TFormatExpressionItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
	__property System::DelphiInterface<System::Sysutils::TProc__1<System::Classes::TCollectionItem*> > OnUpdate = {read=FOnUpdate, write=FOnUpdate};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFormatExpressions() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomLinkFillControlToField : public TCustomLinkControlToField
{
	typedef TCustomLinkControlToField inherited;
	
private:
	TCustomBindGridListLookup* FBindList;
	System::UnicodeString FFillDisplayCustomFormat;
	System::UnicodeString FFillValueCustomFormat;
	TFormatExpressions* FFillExpressions;
	bool FDeprecatedAutoBufferCount;
	TFormatExpressions* FFillHeaderExpressions;
	System::UnicodeString FFillBreakFieldName;
	System::UnicodeString FFillBreakCustomFormat;
	System::UnicodeString FFillHeaderFieldName;
	System::UnicodeString FFillHeaderCustomFormat;
	bool __fastcall GetAutoFill();
	int __fastcall GetBufferCount();
	TBaseLinkingBindSource* __fastcall GetFillDataSource();
	System::UnicodeString __fastcall GetFillDisplayFieldName();
	System::UnicodeString __fastcall GetFillValueFieldName();
	void __fastcall SetAutoFill(const bool Value);
	void __fastcall SetBufferCount(const int Value);
	void __fastcall SetFillDataSource(TBaseLinkingBindSource* const Value);
	void __fastcall SetFillDisplayFieldName(const System::UnicodeString Value);
	void __fastcall SetFillValueFieldName(const System::UnicodeString Value);
	void __fastcall SetFillDisplayCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillValueCustomFormat(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetListItemStyle();
	void __fastcall SetListItemStyle(const System::UnicodeString Value);
	void __fastcall SetFillExpressions(TFormatExpressions* const Value);
	void __fastcall SetFillHeaderExpressions(TFormatExpressions* const Value);
	void __fastcall FillExpressionsUpdate(System::Classes::TCollectionItem* AItem);
	void __fastcall OnListRefreshing(System::TObject* Sender);
	void __fastcall SetFillBreakCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillBreakFieldName(const System::UnicodeString Value);
	void __fastcall SetFillHeaderCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillHeaderFieldName(const System::UnicodeString Value);
	TFillBreakGroups* __fastcall GetFillBreakGroups();
	void __fastcall SetFillBreakGroups(TFillBreakGroups* const Value);
	TFillListItemEvent __fastcall GetOnFilledListItem();
	TFillListItemEvent __fastcall GetOnFillingListItem();
	void __fastcall SetOnFilledListItem(const TFillListItemEvent Value);
	void __fastcall SetOnFillingListItem(const TFillListItemEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnFilledList();
	System::Classes::TNotifyEvent __fastcall GetOnFillingList();
	void __fastcall SetOnFilledList(const System::Classes::TNotifyEvent Value);
	void __fastcall SetOnFillingList(const System::Classes::TNotifyEvent Value);
	
protected:
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual System::UnicodeString __fastcall GetControlComponentMemberName();
	virtual void __fastcall Activated(System::Classes::TComponent* Sender);
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender)/* overload */;
	virtual void __fastcall SetAutoActivate(const bool Value);
	virtual System::UnicodeString __fastcall GetControlExpression();
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall Loaded();
	virtual void __fastcall SetActive(bool Value);
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const AValue);
	System::UnicodeString __fastcall GetControlEditorName(const GUID &AGuid);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TCustomLinkFillControlToField(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkFillControlToField();
	virtual void __fastcall ClearExpressionProperties();
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	bool __fastcall UsingLookupProperties();
	__property TCustomBindGridListLookup* BindList = {read=FBindList};
	__property TBaseLinkingBindSource* FillDataSource = {read=GetFillDataSource, write=SetFillDataSource};
	__property System::UnicodeString FillValueFieldName = {read=GetFillValueFieldName, write=SetFillValueFieldName};
	__property System::UnicodeString FillDisplayFieldName = {read=GetFillDisplayFieldName, write=SetFillDisplayFieldName};
	__property System::UnicodeString FillDisplayCustomFormat = {read=FFillDisplayCustomFormat, write=SetFillDisplayCustomFormat};
	__property System::UnicodeString FillValueCustomFormat = {read=FFillValueCustomFormat, write=SetFillValueCustomFormat};
	__property bool AutoFill = {read=GetAutoFill, write=SetAutoFill, nodefault};
	__property int BufferCount = {read=GetBufferCount, write=SetBufferCount, nodefault};
	__property System::UnicodeString ListItemStyle = {read=GetListItemStyle, write=SetListItemStyle};
	__property TFormatExpressions* FillExpressions = {read=FFillExpressions, write=SetFillExpressions};
	__property bool AutoBufferCount = {read=FDeprecatedAutoBufferCount, write=FDeprecatedAutoBufferCount, nodefault};
	__property TFormatExpressions* FillHeaderExpressions = {read=FFillHeaderExpressions, write=SetFillHeaderExpressions};
	__property System::UnicodeString FillBreakFieldName = {read=FFillBreakFieldName, write=SetFillBreakFieldName};
	__property System::UnicodeString FillBreakCustomFormat = {read=FFillBreakCustomFormat, write=SetFillBreakCustomFormat};
	__property System::UnicodeString FillHeaderFieldName = {read=FFillHeaderFieldName, write=SetFillHeaderFieldName};
	__property System::UnicodeString FillHeaderCustomFormat = {read=FFillHeaderCustomFormat, write=SetFillHeaderCustomFormat};
	__property TFillBreakGroups* FillBreakGroups = {read=GetFillBreakGroups, write=SetFillBreakGroups};
	__property TFillListItemEvent OnFillingListItem = {read=GetOnFillingListItem, write=SetOnFillingListItem};
	__property TFillListItemEvent OnFilledListItem = {read=GetOnFilledListItem, write=SetOnFilledListItem};
	__property System::Classes::TNotifyEvent OnFillingList = {read=GetOnFillingList, write=SetOnFillingList};
	__property System::Classes::TNotifyEvent OnFilledList = {read=GetOnFilledList, write=SetOnFilledList};
private:
	void *__IControlEditorName;	// IControlEditorName 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {54BA961D-A606-469E-98BE-0F39E97E98B6}
	operator _di_IControlEditorName()
	{
		_di_IControlEditorName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IControlEditorName*(void) { return (IControlEditorName*)&__IControlEditorName; }
	#endif
	
};


class PASCALIMPLEMENTATION TLinkFillControlToField : public TCustomLinkFillControlToField
{
	typedef TCustomLinkFillControlToField inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property Control;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property Direction = {default=0};
	__property Track;
	__property CustomParse = {default=0};
	__property CustomFormat = {default=0};
	__property FillDataSource;
	__property FillValueFieldName = {default=0};
	__property FillDisplayFieldName = {default=0};
	__property FillDisplayCustomFormat = {default=0};
	__property FillValueCustomFormat = {default=0};
	__property AutoFill;
	__property ListItemStyle = {default=0};
	__property FillExpressions;
	__property FillHeaderExpressions;
	__property FillBreakFieldName = {default=0};
	__property FillBreakCustomFormat = {default=0};
	__property FillHeaderFieldName = {default=0};
	__property FillHeaderCustomFormat = {default=0};
	__property FillBreakGroups;
	__property OnFillingListItem;
	__property OnFilledListItem;
	__property OnFillingList;
	__property OnFilledList;
	__property UseEvalShortcuts = {default=1};
public:
	/* TCustomLinkFillControlToField.Create */ inline __fastcall virtual TLinkFillControlToField(System::Classes::TComponent* AOwner) : TCustomLinkFillControlToField(AOwner) { }
	/* TCustomLinkFillControlToField.Destroy */ inline __fastcall virtual ~TLinkFillControlToField() { }
	
};


class PASCALIMPLEMENTATION TCustomLinkListControlToField : public TLinkControlToFieldDelegate
{
	typedef TLinkControlToFieldDelegate inherited;
	
private:
	TLinkControlToFieldDirection FDirection;
	TCustomBindGridListLink* FBindListLink;
	System::UnicodeString FCustomFormat;
	TFormatExpressions* FFillExpressions;
	TFormatExpressions* FFillHeaderExpressions;
	System::UnicodeString FFillBreakFieldName;
	System::UnicodeString FFillBreakCustomFormat;
	System::UnicodeString FFillHeaderFieldName;
	System::UnicodeString FFillHeaderCustomFormat;
	System::UnicodeString FCustomParse;
	bool FDeprecatedAutoBufferCount;
	bool FUseEvalShortcuts;
	bool __fastcall GetAutoActivate();
	void __fastcall SetAutoActivate(const bool Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	void __fastcall SetCustomParse(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetListItemStyle();
	void __fastcall SetFillExpressions(TFormatExpressions* const Value);
	void __fastcall SetFillHeaderExpressions(TFormatExpressions* const Value);
	void __fastcall SetListItemStyle(const System::UnicodeString Value);
	void __fastcall FillExpressionsUpdate(System::Classes::TCollectionItem* AItem);
	int __fastcall GetBufferCount();
	void __fastcall SetBufferCount(const int Value);
	void __fastcall OnListRefreshing(System::TObject* Sender);
	void __fastcall SetFillBreakCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillBreakFieldName(const System::UnicodeString Value);
	void __fastcall SetFillHeaderCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillHeaderFieldName(const System::UnicodeString Value);
	TFillBreakGroups* __fastcall GetFillBreakGroups();
	void __fastcall SetFillBreakGroups(TFillBreakGroups* const Value);
	TFillListItemEvent __fastcall GetOnFilledListItem();
	TFillListItemEvent __fastcall GetOnFillingListItem();
	void __fastcall SetOnFilledListItem(const TFillListItemEvent Value);
	void __fastcall SetOnFillingListItem(const TFillListItemEvent Value);
	System::Classes::TNotifyEvent __fastcall GetOnFilledList();
	System::Classes::TNotifyEvent __fastcall GetOnFillingList();
	void __fastcall SetOnFilledList(const System::Classes::TNotifyEvent Value);
	void __fastcall SetOnFillingList(const System::Classes::TNotifyEvent Value);
	void __fastcall SetUseEvalShortcuts(const bool Value);
	
protected:
	virtual void __fastcall Reactivate();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	virtual System::UnicodeString __fastcall GetControlComponentMemberName();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetDisplaysMultipleSourceMembers();
	System::UnicodeString __fastcall GetControlEditorName(const GUID &AGuid);
	void __fastcall SetFieldName(const System::UnicodeString AName);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual bool __fastcall GetUseEvalShortcuts();
	
public:
	__fastcall virtual TCustomLinkListControlToField(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkListControlToField();
	virtual void __fastcall ClearExpressionProperties();
	void __fastcall FillList();
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	__property TCustomBindGridListLink* BindLink = {read=FBindListLink};
	__property System::UnicodeString FieldName = {read=GetSourceMember, write=SetFieldName};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property TLinkControlToFieldDirection Direction = {read=FDirection, write=FDirection, default=0};
	__property int BufferCount = {read=GetBufferCount, write=SetBufferCount, default=-1};
	__property bool AutoBufferCount = {read=FDeprecatedAutoBufferCount, write=FDeprecatedAutoBufferCount, nodefault};
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property System::Classes::TComponent* Control = {read=GetControlComponent, write=SetControlComponent};
	__property System::UnicodeString ControlMemberName = {read=GetControlComponentMemberName};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
	__property System::UnicodeString CustomParse = {read=FCustomParse, write=SetCustomParse};
	__property TFormatExpressions* FillExpressions = {read=FFillExpressions, write=SetFillExpressions};
	__property System::UnicodeString ListItemStyle = {read=GetListItemStyle, write=SetListItemStyle};
	__property TFormatExpressions* FillHeaderExpressions = {read=FFillHeaderExpressions, write=SetFillHeaderExpressions};
	__property System::UnicodeString FillBreakFieldName = {read=FFillBreakFieldName, write=SetFillBreakFieldName};
	__property System::UnicodeString FillBreakCustomFormat = {read=FFillBreakCustomFormat, write=SetFillBreakCustomFormat};
	__property System::UnicodeString FillHeaderFieldName = {read=FFillHeaderFieldName, write=SetFillHeaderFieldName};
	__property System::UnicodeString FillHeaderCustomFormat = {read=FFillHeaderCustomFormat, write=SetFillHeaderCustomFormat};
	__property TFillBreakGroups* FillBreakGroups = {read=GetFillBreakGroups, write=SetFillBreakGroups};
	__property TFillListItemEvent OnFillingListItem = {read=GetOnFillingListItem, write=SetOnFillingListItem};
	__property TFillListItemEvent OnFilledListItem = {read=GetOnFilledListItem, write=SetOnFilledListItem};
	__property System::Classes::TNotifyEvent OnFillingList = {read=GetOnFillingList, write=SetOnFillingList};
	__property System::Classes::TNotifyEvent OnFilledList = {read=GetOnFilledList, write=SetOnFilledList};
	__property bool UseEvalShortcuts = {read=GetUseEvalShortcuts, write=SetUseEvalShortcuts, default=1};
private:
	void *__IControlEditorName;	// IControlEditorName 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {54BA961D-A606-469E-98BE-0F39E97E98B6}
	operator _di_IControlEditorName()
	{
		_di_IControlEditorName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IControlEditorName*(void) { return (IControlEditorName*)&__IControlEditorName; }
	#endif
	
};


class PASCALIMPLEMENTATION TLinkListControlToField : public TCustomLinkListControlToField
{
	typedef TCustomLinkListControlToField inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property Control;
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property CustomFormat = {default=0};
	__property FillExpressions;
	__property ListItemStyle = {default=0};
	__property FillHeaderExpressions;
	__property FillBreakFieldName = {default=0};
	__property FillBreakCustomFormat = {default=0};
	__property FillHeaderFieldName = {default=0};
	__property FillHeaderCustomFormat = {default=0};
	__property FillBreakGroups;
	__property OnFillingListItem;
	__property OnFilledListItem;
	__property OnFillingList;
	__property OnFilledList;
public:
	/* TCustomLinkListControlToField.Create */ inline __fastcall virtual TLinkListControlToField(System::Classes::TComponent* AOwner) : TCustomLinkListControlToField(AOwner) { }
	/* TCustomLinkListControlToField.Destroy */ inline __fastcall virtual ~TLinkListControlToField() { }
	
};


class PASCALIMPLEMENTATION TLinkPropertyToFieldDelegate : public TBindComponentDelegate
{
	typedef TBindComponentDelegate inherited;
	
private:
	System::UnicodeString FComponentProperty;
	
protected:
	void __fastcall SetDataSource(TBaseLinkingBindSource* const Value);
	TBaseLinkingBindSource* __fastcall GetDataSource();
	void __fastcall SetSourceMember(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSourceMember();
	virtual System::Classes::TComponent* __fastcall GetControlComponent();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	void __fastcall SetComponentProperty(const System::UnicodeString Value);
	virtual void __fastcall SetActive(bool AValue);
	virtual void __fastcall BindActivate(bool AValue);
	
public:
	__property TBaseLinkingBindSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property System::Classes::TComponent* Component = {read=GetControlComponent, write=SetControlComponent};
	__property System::UnicodeString ComponentProperty = {read=FComponentProperty, write=SetComponentProperty};
	__property System::UnicodeString FieldName = {read=GetSourceMember, write=SetSourceMember};
public:
	/* TContainedBindComponent.Create */ inline __fastcall virtual TLinkPropertyToFieldDelegate(System::Classes::TComponent* AOwner) : TBindComponentDelegate(AOwner) { }
	/* TContainedBindComponent.Destroy */ inline __fastcall virtual ~TLinkPropertyToFieldDelegate() { }
	
private:
	void *__IBindActivate;	// IBindActivate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79856F26-5E66-4A24-B4DE-A7DBBE6356AD}
	operator _di_IBindActivate()
	{
		_di_IBindActivate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IBindActivate*(void) { return (IBindActivate*)&__IBindActivate; }
	#endif
	
};


class PASCALIMPLEMENTATION TCustomLinkPropertyToField : public TLinkPropertyToFieldDelegate
{
	typedef TLinkPropertyToFieldDelegate inherited;
	
private:
	TBasicBindComponent* FLookupMemberChange;
	TCustomBindLink* FBindLink;
	System::UnicodeString FCustomFormat;
	System::UnicodeString FLookupValueFieldName;
	TBaseLinkingBindSource* FLookupDataSource;
	System::UnicodeString FLookupKeyFieldName;
	bool __fastcall GetAutoActivate();
	void __fastcall SetAutoActivate(const bool Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	void __fastcall SetLookupDataSource(TBaseLinkingBindSource* const Value);
	void __fastcall SetLookupKeyFieldName(const System::UnicodeString Value);
	void __fastcall SetLookupValueFieldName(const System::UnicodeString Value);
	bool __fastcall UsingLookup();
	
protected:
	virtual void __fastcall Reactivate();
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(bool Value);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
#ifndef _WIN64
	virtual System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::DynamicArray<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#else /* _WIN64 */
	virtual System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> __fastcall GetSourceScopes(System::Classes::TComponent* Sender, System::TArray__1<System::Bindings::Evalprotocol::_di_IScope> AScopes);
#endif /* _WIN64 */
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	
public:
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall Loaded();
	__fastcall virtual TCustomLinkPropertyToField(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkPropertyToField();
	__property TCustomBindLink* BindLink = {read=FBindLink};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property TBaseLinkingBindSource* LookupDataSource = {read=FLookupDataSource, write=SetLookupDataSource};
	__property System::UnicodeString LookupKeyFieldName = {read=FLookupKeyFieldName, write=SetLookupKeyFieldName};
	__property System::UnicodeString LookupValueFieldName = {read=FLookupValueFieldName, write=SetLookupValueFieldName};
};


class PASCALIMPLEMENTATION TLinkPropertyToField : public TCustomLinkPropertyToField
{
	typedef TCustomLinkPropertyToField inherited;
	
__published:
	__property DataSource;
	__property FieldName = {default=0};
	__property Component;
	__property CustomFormat = {default=0};
	__property ComponentProperty = {default=0};
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property LookupDataSource;
	__property LookupKeyFieldName = {default=0};
	__property LookupValueFieldName = {default=0};
public:
	/* TCustomLinkPropertyToField.Create */ inline __fastcall virtual TLinkPropertyToField(System::Classes::TComponent* AOwner) : TCustomLinkPropertyToField(AOwner) { }
	/* TCustomLinkPropertyToField.Destroy */ inline __fastcall virtual ~TLinkPropertyToField() { }
	
};


class PASCALIMPLEMENTATION TCustomLinkControlToProperty : public TLinkControlDelegate
{
	typedef TLinkControlDelegate inherited;
	
private:
	TCustomBindControlValue* FBindLink;
	TDependency* FDependency;
	System::UnicodeString FComponentProperty;
	System::UnicodeString FCustomFormat;
	System::UnicodeString FCustomParse;
	bool FInitializeControlValue;
	bool __fastcall GetAutoActivate();
	void __fastcall SetComponentProperty(const System::UnicodeString Value);
	void __fastcall SetCustomFormat(const System::UnicodeString Value);
	bool __fastcall GetTrack();
	void __fastcall SetTrack(const bool Value);
	void __fastcall SetCustomParse(const System::UnicodeString Value);
	void __fastcall SetInitializeControlValue(const bool Value);
	
protected:
	virtual void __fastcall Reactivate();
	virtual void __fastcall SetAutoActivate(const bool Value);
	virtual bool __fastcall GetActive();
	virtual System::UnicodeString __fastcall GetControlExpression();
	virtual void __fastcall SetActive(bool Value);
	void __fastcall SetSourceComponent(System::Classes::TComponent* const Value);
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const Value);
	System::Classes::TComponent* __fastcall GetSourceComponent();
	
public:
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual bool __fastcall RequiresControlHandler();
	virtual void __fastcall Loaded();
	virtual void __fastcall ClearExpressionProperties();
	__fastcall virtual TCustomLinkControlToProperty(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkControlToProperty();
	__property TCustomBindControlValue* BindControlValue = {read=FBindLink};
	__property bool AutoActivate = {read=GetAutoActivate, write=SetAutoActivate, default=1};
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property System::Classes::TComponent* Control = {read=GetControlComponent, write=SetControlComponent};
	__property System::Classes::TComponent* Component = {read=GetSourceComponent, write=SetSourceComponent};
	__property System::UnicodeString ComponentProperty = {read=FComponentProperty, write=SetComponentProperty};
	__property System::UnicodeString ControlMemberName = {read=GetControlComponentMemberName};
	__property System::UnicodeString CustomFormat = {read=FCustomFormat, write=SetCustomFormat};
	__property System::UnicodeString CustomParse = {read=FCustomParse, write=SetCustomParse};
	__property bool InitializeControlValue = {read=FInitializeControlValue, write=SetInitializeControlValue, default=1};
	__property bool Track = {read=GetTrack, write=SetTrack, nodefault};
};


class PASCALIMPLEMENTATION TLinkControlToProperty : public TCustomLinkControlToProperty
{
	typedef TCustomLinkControlToProperty inherited;
	
__published:
	__property Control;
	__property Track;
	__property Component;
	__property ComponentProperty = {default=0};
	__property AutoActivate = {default=1};
	__property CustomFormat = {default=0};
	__property CustomParse = {default=0};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property InitializeControlValue = {default=1};
public:
	/* TCustomLinkControlToProperty.Create */ inline __fastcall virtual TLinkControlToProperty(System::Classes::TComponent* AOwner) : TCustomLinkControlToProperty(AOwner) { }
	/* TCustomLinkControlToProperty.Destroy */ inline __fastcall virtual ~TLinkControlToProperty() { }
	
};


class PASCALIMPLEMENTATION TCustomLinkFillControlToProperty : public TCustomLinkControlToProperty
{
	typedef TCustomLinkControlToProperty inherited;
	
private:
	TCustomBindGridListLookup* FBindList;
	System::UnicodeString FFillDisplayCustomFormat;
	System::UnicodeString FFillValueCustomFormat;
	TFormatExpressions* FFillExpressions;
	TFormatExpressions* FFillHeaderExpressions;
	System::UnicodeString FFillBreakFieldName;
	System::UnicodeString FFillBreakCustomFormat;
	System::UnicodeString FFillHeaderFieldName;
	System::UnicodeString FFillHeaderCustomFormat;
	bool FDeprecatedAutoBufferCount;
	bool __fastcall GetAutoFill();
	int __fastcall GetBufferCount();
	TBaseLinkingBindSource* __fastcall GetFillDataSource();
	System::UnicodeString __fastcall GetFillDisplayFieldName();
	System::UnicodeString __fastcall GetFillValueFieldName();
	void __fastcall SetAutoFill(const bool Value);
	void __fastcall SetBufferCount(const int Value);
	void __fastcall SetFillDataSourceName(TBaseLinkingBindSource* const Value);
	void __fastcall SetFillDisplayFieldName(const System::UnicodeString Value);
	void __fastcall SetFillValueFieldName(const System::UnicodeString Value);
	void __fastcall SetFillDisplayCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillValueCustomFormat(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetListItemStyle();
	void __fastcall SetListItemStyle(const System::UnicodeString Value);
	void __fastcall SetFillExpressions(TFormatExpressions* const Value);
	void __fastcall SetFillHeaderExpressions(TFormatExpressions* const Value);
	void __fastcall FillExpressionsUpdate(System::Classes::TCollectionItem* AItem);
	void __fastcall OnListRefreshing(System::TObject* Sender);
	void __fastcall SetFillBreakCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillBreakFieldName(const System::UnicodeString Value);
	void __fastcall SetFillHeaderCustomFormat(const System::UnicodeString Value);
	void __fastcall SetFillHeaderFieldName(const System::UnicodeString Value);
	TFillBreakGroups* __fastcall GetFillBreakGroups();
	void __fastcall SetFillBreakGroups(TFillBreakGroups* const Value);
	
protected:
	virtual void __fastcall MemberRenaming(System::Classes::TComponent* Sender, System::Classes::TComponent* AComponent, const System::UnicodeString ACurMemberName, const System::UnicodeString ANewMemberName);
	virtual System::UnicodeString __fastcall GetControlComponentMemberName();
	virtual void __fastcall Activated(System::Classes::TComponent* Sender);
	virtual void __fastcall SetAutoActivate(const bool Value);
	virtual System::UnicodeString __fastcall GetControlExpression();
	virtual void __fastcall SetActive(bool Value);
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetControlComponent(System::Classes::TComponent* const AValue);
	System::UnicodeString __fastcall GetControlEditorName(const GUID &AGuid);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TCustomLinkFillControlToProperty(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomLinkFillControlToProperty();
	virtual void __fastcall ClearExpressionProperties();
#ifndef _WIN64
	virtual System::DynamicArray<TCommonBindComponent*> __fastcall GetDelegates();
#else /* _WIN64 */
	virtual System::TArray__1<TCommonBindComponent*> __fastcall GetDelegates();
#endif /* _WIN64 */
	virtual bool __fastcall CanSetControlComponent(System::Classes::TComponent* Value);
	bool __fastcall UsingLookupProperties();
	virtual bool __fastcall CanActivate(System::Classes::TComponent* Sender);
	virtual void __fastcall Loaded();
	virtual void __fastcall ClearGeneratedExpressions(System::Classes::TComponent* Sender);
	virtual void __fastcall GenerateExpressions(System::Classes::TComponent* Sender);
	__property TCustomBindGridListLookup* BindList = {read=FBindList};
	__property TBaseLinkingBindSource* FillDataSource = {read=GetFillDataSource, write=SetFillDataSourceName};
	__property System::UnicodeString FillValueFieldName = {read=GetFillValueFieldName, write=SetFillValueFieldName};
	__property System::UnicodeString FillDisplayFieldName = {read=GetFillDisplayFieldName, write=SetFillDisplayFieldName};
	__property System::UnicodeString FillDisplayCustomFormat = {read=FFillDisplayCustomFormat, write=SetFillDisplayCustomFormat};
	__property System::UnicodeString FillValueCustomFormat = {read=FFillValueCustomFormat, write=SetFillValueCustomFormat};
	__property bool AutoFill = {read=GetAutoFill, write=SetAutoFill, nodefault};
	__property int BufferCount = {read=GetBufferCount, write=SetBufferCount, nodefault};
	__property System::UnicodeString ListItemStyle = {read=GetListItemStyle, write=SetListItemStyle};
	__property TFormatExpressions* FillExpressions = {read=FFillExpressions, write=SetFillExpressions};
	__property bool AutoBufferCount = {read=FDeprecatedAutoBufferCount, write=FDeprecatedAutoBufferCount, nodefault};
	__property TFormatExpressions* FillHeaderExpressions = {read=FFillHeaderExpressions, write=SetFillHeaderExpressions};
	__property System::UnicodeString FillBreakFieldName = {read=FFillBreakFieldName, write=SetFillBreakFieldName};
	__property System::UnicodeString FillBreakCustomFormat = {read=FFillBreakCustomFormat, write=SetFillBreakCustomFormat};
	__property System::UnicodeString FillHeaderFieldName = {read=FFillHeaderFieldName, write=SetFillHeaderFieldName};
	__property System::UnicodeString FillHeaderCustomFormat = {read=FFillHeaderCustomFormat, write=SetFillHeaderCustomFormat};
	__property TFillBreakGroups* FillBreakGroups = {read=GetFillBreakGroups, write=SetFillBreakGroups};
private:
	void *__IControlEditorName;	// IControlEditorName 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {54BA961D-A606-469E-98BE-0F39E97E98B6}
	operator _di_IControlEditorName()
	{
		_di_IControlEditorName intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IControlEditorName*(void) { return (IControlEditorName*)&__IControlEditorName; }
	#endif
	
};


class PASCALIMPLEMENTATION TLinkFillControlToProperty : public TCustomLinkFillControlToProperty
{
	typedef TCustomLinkFillControlToProperty inherited;
	
__published:
	__property Track;
	__property Control;
	__property Component;
	__property ComponentProperty = {default=0};
	__property AutoActivate = {default=1};
	__property OnAssignedValue;
	__property OnAssigningValue;
	__property OnEvalError;
	__property OnActivating;
	__property OnActivated;
	__property FillDataSource;
	__property FillValueFieldName = {default=0};
	__property FillDisplayFieldName = {default=0};
	__property FillDisplayCustomFormat = {default=0};
	__property FillValueCustomFormat = {default=0};
	__property CustomParse = {default=0};
	__property CustomFormat = {default=0};
	__property AutoFill;
	__property ListItemStyle = {default=0};
	__property FillExpressions;
	__property InitializeControlValue = {default=1};
	__property FillHeaderExpressions;
	__property FillBreakFieldName = {default=0};
	__property FillBreakCustomFormat = {default=0};
	__property FillHeaderFieldName = {default=0};
	__property FillHeaderCustomFormat = {default=0};
	__property FillBreakGroups;
public:
	/* TCustomLinkFillControlToProperty.Create */ inline __fastcall virtual TLinkFillControlToProperty(System::Classes::TComponent* AOwner) : TCustomLinkFillControlToProperty(AOwner) { }
	/* TCustomLinkFillControlToProperty.Destroy */ inline __fastcall virtual ~TLinkFillControlToProperty() { }
	
};


enum DECLSPEC_DENUM TBindArtifactState : unsigned char { eaInclude, eaExclude };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindArtifactItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FID;
	TBindArtifactState FState;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
__published:
	__property System::UnicodeString ID = {read=FID, write=FID};
	__property TBindArtifactState State = {read=FState, write=FState, nodefault};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TBindArtifactItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TBindArtifactItem() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TScopeMappingItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::UnicodeString FAlias;
	System::Classes::TComponent* FValComponent;
	System::Rtti::TValue FValValue;
	System::TObject* FValObject;
	System::Classes::TNotifyEvent FValNotifyEvent;
	System::Variant FValVariant;
	TScopeMappings* __fastcall GetScopeMappings();
	void __fastcall SetValObject(System::TObject* const Value);
	void __fastcall SetValNotifyEvent(const System::Classes::TNotifyEvent Value);
	void __fastcall SetValComponent(System::Classes::TComponent* const Value);
	void __fastcall SetValVariant(const System::Variant &Value);
	void __fastcall ClearValue();
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual System::UnicodeString __fastcall GetDisplayName();
	
public:
	__property TScopeMappings* ScopeMappings = {read=GetScopeMappings};
	__property System::TObject* ValObject = {read=FValObject, write=SetValObject};
	
__published:
	__property System::UnicodeString Name = {read=FAlias, write=FAlias};
	__property System::Classes::TComponent* ValComponent = {read=FValComponent, write=SetValComponent};
	__property System::Variant ValVariant = {read=FValVariant, write=SetValVariant};
	__property System::Classes::TNotifyEvent ValNotifyEvent = {read=FValNotifyEvent, write=SetValNotifyEvent};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TScopeMappingItem(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TScopeMappingItem() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScopeMappingsEnumerator : public System::Classes::TCollectionEnumerator
{
	typedef System::Classes::TCollectionEnumerator inherited;
	
public:
	HIDESBASE TScopeMappingItem* __fastcall GetCurrent();
	__property TScopeMappingItem* Current = {read=GetCurrent};
public:
	/* TCollectionEnumerator.Create */ inline __fastcall TScopeMappingsEnumerator(System::Classes::TCollection* ACollection) : System::Classes::TCollectionEnumerator(ACollection) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TScopeMappingsEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScopeMappings : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TScopeMappingItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	HIDESBASE TScopeMappingItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TScopeMappingItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	
public:
	HIDESBASE TScopeMappingsEnumerator* __fastcall GetEnumerator();
	TScopeMappingItem* __fastcall AddExpression();
	__property TScopeMappingItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TOwnedCollection.Create */ inline __fastcall TScopeMappings(System::Classes::TPersistent* AOwner, System::Classes::TCollectionItemClass ItemClass) : System::Classes::TOwnedCollection(AOwner, ItemClass) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TScopeMappings() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindArtifacts : public System::Classes::TOwnedCollection
{
	typedef System::Classes::TOwnedCollection inherited;
	
public:
	TBindArtifactItem* operator[](int Index) { return this->Items[Index]; }
	
private:
	bool FModified;
	HIDESBASE TBindArtifactItem* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TBindArtifactItem* const Value);
	
protected:
	DYNAMIC int __fastcall GetAttrCount();
	DYNAMIC System::UnicodeString __fastcall GetAttr(int Index);
	DYNAMIC System::UnicodeString __fastcall GetItemAttr(int Index, int ItemIndex);
	__property bool Modified = {read=FModified, nodefault};
	
public:
	__fastcall TBindArtifacts(System::Classes::TPersistent* AOwner);
	__property TBindArtifactItem* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TBindArtifacts() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMethods : public TBindArtifacts
{
	typedef TBindArtifacts inherited;
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
public:
	/* TBindArtifacts.Create */ inline __fastcall TMethods(System::Classes::TPersistent* AOwner) : TBindArtifacts(AOwner) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOutputConverters : public TBindArtifacts
{
	typedef TBindArtifacts inherited;
	
protected:
	virtual void __fastcall Update(System::Classes::TCollectionItem* Item);
public:
	/* TBindArtifacts.Create */ inline __fastcall TOutputConverters(System::Classes::TPersistent* AOwner) : TBindArtifacts(AOwner) { }
	
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TOutputConverters() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{84C633CB-6A4B-407A-A8E4-D175923D8E61}") IScopeComponent  : public System::IInterface 
{
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetScope() = 0 ;
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetMemberScope(const System::UnicodeString AMemberName) = 0 ;
	virtual System::TObject* __fastcall GetScopeObject() = 0 ;
};

__interface  INTERFACE_UUID("{EE75B066-3C8B-4102-9864-383447BFA6F2}") IScopeExpressions  : public System::IInterface 
{
	virtual void __fastcall AddExpression(TBasicBindComponent* AExpression) = 0 ;
	virtual void __fastcall RemoveExpression(TBasicBindComponent* AExpression) = 0 ;
};

__interface  INTERFACE_UUID("{174B9736-9D6B-46B6-9DD5-FE8A1B713C62}") IScopeLocks  : public System::IInterface 
{
	virtual void __fastcall PosLockEnter() = 0 ;
	virtual void __fastcall PosLockLeave() = 0 ;
	virtual bool __fastcall GetPosLock() = 0 ;
	__property bool PosLock = {read=GetPosLock};
};

__interface  INTERFACE_UUID("{86C2783F-082F-4D78-98A3-CC3540D72A0D}") IScopeEditLink  : public System::IInterface 
{
	virtual void __fastcall SetField(TBasicBindComponent* ABindComp, const System::UnicodeString FieldName) = 0 ;
	virtual bool __fastcall Edit(TBasicBindComponent* ABindComp) = 0 ;
	virtual bool __fastcall GetIsEditing(TBasicBindComponent* ABindComp) = 0 ;
	virtual void __fastcall SetModified(TBasicBindComponent* ABindComp) = 0 ;
	virtual bool __fastcall GetIsModified(TBasicBindComponent* ABindComp) = 0 ;
	virtual bool __fastcall GetCanModify(TBasicBindComponent* ABindComp) = 0 ;
	virtual void __fastcall UpdateRecord(TBasicBindComponent* ABindComp) = 0 ;
	virtual void __fastcall Reset(TBasicBindComponent* ABindComp) = 0 ;
	virtual void __fastcall SetReadOnly(TBasicBindComponent* ABindComp, const bool Value) = 0 ;
	virtual void __fastcall ClearModified(TBasicBindComponent* ABindComp) = 0 ;
	virtual void __fastcall PosChanging(TBasicBindComponent* ABindComp) = 0 ;
};

typedef void __fastcall (__closure *TNotifyDistanceEvent)(System::TObject* Sender, int Distance);

__interface  INTERFACE_UUID("{56387EF7-0E9C-4049-AD67-37D0CA60F0D9}") IScopeActive  : public System::IInterface 
{
	virtual bool __fastcall GetActive() = 0 ;
	__property bool Active = {read=GetActive};
};

__interface  INTERFACE_UUID("{2B1E1B3F-EBD5-46F0-A611-E5512D49BCFD}") IScopeState  : public IScopeActive 
{
	virtual bool __fastcall GetCanModify() = 0 ;
	virtual bool __fastcall GetCanDelete() = 0 ;
	virtual bool __fastcall GetCanInsert() = 0 ;
	virtual bool __fastcall GetEditing() = 0 ;
	virtual bool __fastcall GetCanRefresh() = 0 ;
	virtual void __fastcall AddActiveChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall RemoveActiveChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall AddEditingChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall RemoveEditingChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall AddDataSetChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall RemoveDataSetChanged(System::Classes::TNotifyEvent LNotify) = 0 ;
	virtual void __fastcall AddDataSetScrolled(TNotifyDistanceEvent LNotify) = 0 ;
	virtual void __fastcall RemoveDataSetScrolled(TNotifyDistanceEvent LNotify) = 0 ;
	__property bool Editing = {read=GetEditing};
	__property bool CanModify = {read=GetCanModify};
	__property bool CanInsert = {read=GetCanInsert};
	__property bool CanDelete = {read=GetCanDelete};
	__property bool CanRefresh = {read=GetCanRefresh};
};

__interface  INTERFACE_UUID("{F2A94E16-2181-4943-8BDC-3D0CA7FDE336}") IScopeEditor  : public System::IInterface 
{
	virtual void __fastcall Insert() = 0 ;
	virtual void __fastcall Delete() = 0 ;
	virtual void __fastcall Cancel() = 0 ;
	virtual void __fastcall Post() = 0 ;
	virtual void __fastcall Edit() = 0 ;
	virtual void __fastcall Refresh() = 0 ;
	virtual bool __fastcall IsValidChar(const System::UnicodeString AFieldName, const System::WideChar AChar) = 0 ;
	virtual bool __fastcall IsRequired(const System::UnicodeString AFieldName) = 0 ;
	virtual System::Classes::_di_IEditFormatLink __fastcall GetFormatLink(const System::UnicodeString AFieldName) = 0 ;
};

__interface  INTERFACE_UUID("{C71852CF-888A-42C6-9A15-B704E11229D8}") IScopeNavigator  : public System::IInterface 
{
	virtual bool __fastcall GetBOF() = 0 ;
	virtual bool __fastcall GetEOF() = 0 ;
	virtual bool __fastcall GetSelected() = 0 ;
	virtual void __fastcall Next() = 0 ;
	virtual void __fastcall Prior() = 0 ;
	virtual void __fastcall First() = 0 ;
	virtual void __fastcall Last() = 0 ;
	__property bool Eof = {read=GetEOF};
	__property bool BOF = {read=GetBOF};
	__property bool Selected = {read=GetSelected};
};

__interface  INTERFACE_UUID("{E6D8BFA3-0453-436B-8434-D10623724644}") IScopeMemberNames  : public System::IInterface 
{
	virtual void __fastcall GetMemberNames(System::Classes::TStrings* AList) = 0 ;
};

__interface  INTERFACE_UUID("{4B7BCC08-0278-4CC4-ADF3-7376F2A0A8CC}") IScopeUnidirectional  : public System::IInterface 
{
	virtual bool __fastcall GetIsUnidirectional() = 0 ;
	__property bool IsUnidirection = {read=GetIsUnidirectional};
};

typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::Classes::TPersistent*> TPersistentPair;

typedef System::Set<TScopeMemberType, TScopeMemberType::mtUnknown, TScopeMemberType::mtTValue> TScopeMemberTypes;

__interface  INTERFACE_UUID("{3B273E26-19DA-4591-99AF-6748B71ABD3A}") IScopeMemberScripting  : public System::IInterface 
{
	virtual bool __fastcall GetMemberGetter(const System::UnicodeString AMemberName, System::UnicodeString &AGetter) = 0 ;
	virtual bool __fastcall GetMemberSetter(const System::UnicodeString AMemberName, System::UnicodeString &ASetter) = 0 ;
	virtual bool __fastcall GetMemberType(const System::UnicodeString AMemberName, TScopeMemberType &AType) = 0 ;
	virtual bool __fastcall GetPositionGetter(System::UnicodeString &AGetter, int &ABase) = 0 ;
	virtual bool __fastcall GetPositionSetter(System::UnicodeString &ASetter, int &ABase) = 0 ;
};

class PASCALIMPLEMENTATION TBaseBindScopeComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Generics::Collections::TList__1<TBasicBindComponent*>* FExpressions;
	int FPosLock;
	TScopeMappings* FScopeMappings;
	
protected:
	virtual void __fastcall SetScopeMappings(TScopeMappings* const Value);
	System::Bindings::Evalprotocol::_di_IScope __fastcall AddScopeMappings(System::Bindings::Evalprotocol::_di_IScope AScope);
	virtual System::TObject* __fastcall GetMember(const System::UnicodeString AMemberName);
	virtual System::TObject* __fastcall GetValue();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetScope();
	virtual System::Bindings::Evalprotocol::_di_IScope __fastcall GetMemberScope(const System::UnicodeString AMemberName);
	System::TObject* __fastcall GetScopeObject();
	void __fastcall PosLockEnter();
	void __fastcall PosLockLeave();
	bool __fastcall GetPosLock();
	virtual void __fastcall AddExpression(TBasicBindComponent* AExpression);
	virtual void __fastcall RemoveExpression(TBasicBindComponent* AExpression);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall ActivateExpressions(bool AValue);
	__property System::Generics::Collections::TList__1<TBasicBindComponent*>* Expressions = {read=FExpressions};
	__property TScopeMappings* ScopeMappings = {read=FScopeMappings, write=SetScopeMappings};
	
public:
	__fastcall virtual TBaseBindScopeComponent(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBaseBindScopeComponent();
private:
	void *__IScopeLocks;	// IScopeLocks 
	void *__IScopeExpressions;	// IScopeExpressions 
	void *__IScopeComponent;	// IScopeComponent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {174B9736-9D6B-46B6-9DD5-FE8A1B713C62}
	operator _di_IScopeLocks()
	{
		_di_IScopeLocks intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeLocks*(void) { return (IScopeLocks*)&__IScopeLocks; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EE75B066-3C8B-4102-9864-383447BFA6F2}
	operator _di_IScopeExpressions()
	{
		_di_IScopeExpressions intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeExpressions*(void) { return (IScopeExpressions*)&__IScopeExpressions; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {84C633CB-6A4B-407A-A8E4-D175923D8E61}
	operator _di_IScopeComponent()
	{
		_di_IScopeComponent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeComponent*(void) { return (IScopeComponent*)&__IScopeComponent; }
	#endif
	
};


class PASCALIMPLEMENTATION TBaseLinkingBindSource : public TBaseBindScopeComponent
{
	typedef TBaseBindScopeComponent inherited;
	
public:
	/* TBaseBindScopeComponent.Create */ inline __fastcall virtual TBaseLinkingBindSource(System::Classes::TComponent* AOwner) : TBaseBindScopeComponent(AOwner) { }
	/* TBaseBindScopeComponent.Destroy */ inline __fastcall virtual ~TBaseLinkingBindSource() { }
	
};


class PASCALIMPLEMENTATION TCustomBindScope : public TBaseBindScopeComponent
{
	typedef TBaseBindScopeComponent inherited;
	
private:
	System::Classes::TComponent* FComponent;
	bool FActive;
	bool FAutoActivate;
	bool FDeferActive;
	System::TObject* FDataObject;
	void __fastcall SetComponent(System::Classes::TComponent* const Value);
	void __fastcall SetDataObject(System::TObject* const Value);
	void __fastcall SetAutoActivate(const bool Value);
	bool __fastcall CanActivate();
	void __fastcall UpdateDataChanged();
	void __fastcall UpdateDataChanging();
	
protected:
	virtual System::TObject* __fastcall GetValue();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	bool __fastcall GetActive();
	void __fastcall SetActive(bool Value);
	virtual void __fastcall Loaded();
	HIDESBASE _di_IScopeRecordEnumerator __fastcall GetEnumerator(const System::UnicodeString AMemberName, int ABufferCount);
	
public:
	__fastcall virtual TCustomBindScope(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindScope();
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property System::Classes::TComponent* Component = {read=FComponent, write=SetComponent};
	__property System::TObject* DataObject = {read=FDataObject, write=SetDataObject};
	__property bool AutoActivate = {read=FAutoActivate, write=SetAutoActivate, default=1};
private:
	void *__IScopeRecordEnumerable;	// IScopeRecordEnumerable 
	void *__IScopeActive;	// IScopeActive 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {34A6773D-A71B-4870-9C60-409A798206FA}
	operator _di_IScopeRecordEnumerable()
	{
		_di_IScopeRecordEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeRecordEnumerable*(void) { return (IScopeRecordEnumerable*)&__IScopeRecordEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {56387EF7-0E9C-4049-AD67-37D0CA60F0D9}
	operator _di_IScopeActive()
	{
		_di_IScopeActive intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeActive*(void) { return (IScopeActive*)&__IScopeActive; }
	#endif
	
};


class PASCALIMPLEMENTATION TBindScope : public TCustomBindScope
{
	typedef TCustomBindScope inherited;
	
__published:
	__property Component;
	__property AutoActivate = {default=1};
	__property ScopeMappings;
public:
	/* TCustomBindScope.Create */ inline __fastcall virtual TBindScope(System::Classes::TComponent* AOwner) : TCustomBindScope(AOwner) { }
	/* TCustomBindScope.Destroy */ inline __fastcall virtual ~TBindScope() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEventListT : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	System::Generics::Collections::TList__1<System::Classes::TNotifyEvent>* FList;
	void __fastcall InternalAdd(System::Classes::TNotifyEvent AEvent);
	void __fastcall InternalRemove(System::Classes::TNotifyEvent AEvent);
	
public:
	__fastcall TBindEventListT();
	__fastcall virtual ~TBindEventListT();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEventList : public TBindEventListT
{
	typedef TBindEventListT inherited;
	
public:
	void __fastcall Add(System::Classes::TNotifyEvent AEvent);
	void __fastcall Remove(System::Classes::TNotifyEvent AEvent);
	void __fastcall Send(System::TObject* Sender);
public:
	/* TBindEventListT.Create */ inline __fastcall TBindEventList() : TBindEventListT() { }
	/* TBindEventListT.Destroy */ inline __fastcall virtual ~TBindEventList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

/* [Template Alias] */
#if defined(__clang__)
template<typename T> using TBindNotifyEvent1__1 = void __fastcall (__closure *)(System::TObject* Sender, T P);
#endif

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TBindEventList1__1 : public TBindEventListT
{
	typedef TBindEventListT inherited;
	
public:
#ifndef _WIN64
	typedef void __fastcall (__closure *_dt_Data_Bind_Components_1)(System::TObject* Sender, T P);
	void __fastcall Add(_dt_Data_Bind_Components_1 AEvent);
	typedef void __fastcall (__closure *_dt_Data_Bind_Components_2)(System::TObject* Sender, T P);
	void __fastcall Remove(_dt_Data_Bind_Components_2 AEvent);
#else /* _WIN64 */
	void __fastcall Add(TBindNotifyEvent1__1<T> AEvent);
	void __fastcall Remove(TBindNotifyEvent1__1<T> AEvent);
#endif /* _WIN64 */
	void __fastcall Send(System::TObject* Sender, const T P);
public:
	/* TBindEventListT.Create */ inline __fastcall TBindEventList1__1() : TBindEventListT() { }
	/* TBindEventListT.Destroy */ inline __fastcall virtual ~TBindEventList1__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void * TEnumBindCompProcInfo;

typedef void __fastcall (__closure *TEnumBindCompProc)(const System::UnicodeString Category, TContainedBindCompClass BindCompClass, void * Info);

__interface  INTERFACE_UUID("{E0FB570F-2EF0-44C7-BD19-F4F8ACAE2294}") IBindCompFactoryContext  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall GetDesigner() = 0 ;
	virtual System::Classes::TComponent* __fastcall GetControlComponent() = 0 ;
	virtual System::Classes::TComponent* __fastcall GetOwner() = 0 ;
	virtual TCustomBindingsList* __fastcall GetBindingsList() = 0 ;
	__property TCustomBindingsList* BindingsList = {read=GetBindingsList};
	__property System::Classes::TComponent* Owner = {read=GetOwner};
	__property System::Classes::TComponent* ControlComponent = {read=GetControlComponent};
	__property System::_di_IInterface Designer = {read=GetDesigner};
};

__interface  INTERFACE_UUID("{E0FB570F-2EF0-44C7-BD19-F4F8ACAE2294}") IBindCompFactoryExecuteContext  : public IBindCompFactoryContext 
{
	virtual System::UnicodeString __fastcall UniqueName(const System::UnicodeString ABaseName) = 0 ;
	virtual void __fastcall BindCompCreated(System::Classes::TComponent* AComponent) = 0 ;
};

__interface  INTERFACE_UUID("{C9E39805-4ED9-4C60-B903-4D3F9E8F0671}") IBindCompFactory  : public System::IInterface 
{
	virtual bool __fastcall Enabled(_di_IBindCompFactoryContext AContext) = 0 ;
	virtual System::UnicodeString __fastcall GetCommandText(_di_IBindCompFactoryContext AContext) = 0 ;
	virtual void __fastcall Execute(_di_IBindCompFactoryExecuteContext AContext) = 0 ;
};

enum DECLSPEC_DENUM TBindCompDesignerCollectionType : unsigned char { colExpressions, colCollections };

enum DECLSPEC_DENUM TBindCompDesignerExpressionType : unsigned char { exprControlToSource, exprSourceToControl, exprBidirectional };

typedef System::Set<TBindCompDesignerExpressionType, TBindCompDesignerExpressionType::exprControlToSource, TBindCompDesignerExpressionType::exprBidirectional> TBindCompDesignerExpressionTypes;

struct DECLSPEC_DRECORD TBindCompDesignExpressionCollection
{
private:
	System::UnicodeString FName;
	System::Classes::TCollection* FCollection;
	System::Classes::TCollectionItem* FParentCollectionItem;
	TBindCompDesignerCollectionType FCollectionType;
	
public:
	__fastcall TBindCompDesignExpressionCollection(const System::UnicodeString AName, System::Classes::TCollection* ACollection, System::Classes::TCollectionItem* AParentCollectionItem, TBindCompDesignerCollectionType ACollectionType);
	__property System::UnicodeString Name = {read=FName};
	__property System::Classes::TCollection* Collection = {read=FCollection};
	__property System::Classes::TCollectionItem* ParentCollectionItem = {read=FParentCollectionItem};
	__property TBindCompDesignerCollectionType CollectionType = {read=FCollectionType};
	TBindCompDesignExpressionCollection() {}
};


struct DECLSPEC_DRECORD TBindCompDesignExpression
{
	
public:
	__interface DELPHIINTERFACE TExecuteDesignExpression;
	typedef System::DelphiInterface<TExecuteDesignExpression> _di_TExecuteDesignExpression;
	__interface TExecuteDesignExpression  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const System::UnicodeString AName, const System::UnicodeString AExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback) = 0 ;
	};
	
	__interface DELPHIINTERFACE TExecuteDesignExpression2;
	typedef System::DelphiInterface<TExecuteDesignExpression2> _di_TExecuteDesignExpression2;
	__interface TExecuteDesignExpression2  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const System::UnicodeString AName, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceExpression, System::DelphiInterface<System::Sysutils::TProc__1<System::Bindings::Evalprotocol::_di_IValue> > ACallback) = 0 ;
	};
	
	__interface DELPHIINTERFACE TSaveDesignExpression;
	typedef System::DelphiInterface<TSaveDesignExpression> _di_TSaveDesignExpression;
	__interface TSaveDesignExpression  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const System::UnicodeString AName, const System::UnicodeString AExpression) = 0 ;
	};
	
	
private:
	System::UnicodeString FName;
	System::UnicodeString FControlScope;
	System::UnicodeString FControlExpression;
	System::UnicodeString FSourceScope;
	System::UnicodeString FSourceExpression;
	_di_TExecuteDesignExpression FExecuteControlProc;
	_di_TExecuteDesignExpression FExecuteSourceProc;
	_di_TExecuteDesignExpression2 FExecuteAssignToSourceProc;
	_di_TExecuteDesignExpression2 FExecuteAssignToControlProc;
	_di_TSaveDesignExpression FSaveControlProc;
	_di_TSaveDesignExpression FSaveSourceProc;
	System::Classes::TCollectionItem* FCollectionItem;
	System::UnicodeString FCollectionName;
	System::Classes::TCollectionItem* FParentCollectionItem;
	TBindCompDesignerExpressionType FExpressionType;
	
public:
	__fastcall TBindCompDesignExpression(const System::UnicodeString AName, const System::UnicodeString AControlScope, const System::UnicodeString AControlExpression, const System::UnicodeString ASourceScope, const System::UnicodeString ASourceExpression, _di_TExecuteDesignExpression2 AExecuteAssignToControl, _di_TExecuteDesignExpression2 AExecuteAssignToSource, _di_TExecuteDesignExpression AExecuteControl, _di_TExecuteDesignExpression AExecuteSource, _di_TSaveDesignExpression ASaveControl, _di_TSaveDesignExpression ASaveSource, System::Classes::TCollectionItem* ACollectionItem, const System::UnicodeString ACollectionName, System::Classes::TCollectionItem* AParentCollectionItem, TBindCompDesignerExpressionType AExpressionType);
	__property System::UnicodeString Name = {read=FName};
	__property System::UnicodeString ControlScope = {read=FControlScope};
	__property System::UnicodeString ControlExpression = {read=FControlExpression};
	__property System::UnicodeString SourceScope = {read=FSourceScope};
	__property System::UnicodeString SourceExpression = {read=FSourceExpression};
	__property _di_TExecuteDesignExpression2 ExecuteAssignToControlProc = {read=FExecuteAssignToControlProc};
	__property _di_TExecuteDesignExpression2 ExecuteAssignToSourceProc = {read=FExecuteAssignToSourceProc};
	__property _di_TExecuteDesignExpression ExecuteSourceProc = {read=FExecuteSourceProc};
	__property _di_TExecuteDesignExpression ExecuteControlProc = {read=FExecuteControlProc};
	__property _di_TSaveDesignExpression SaveSourceProc = {read=FSaveSourceProc};
	__property _di_TSaveDesignExpression SaveControlProc = {read=FSaveControlProc};
	__property System::Classes::TCollectionItem* CollectionItem = {read=FCollectionItem};
	__property System::UnicodeString CollectionName = {read=FCollectionName};
	__property System::Classes::TCollectionItem* ParentCollectionItem = {read=FParentCollectionItem};
	__property TBindCompDesignerExpressionType ExpressionType = {read=FExpressionType};
	TBindCompDesignExpression() {}
};


enum DECLSPEC_DENUM TBindCompDesignerBindsType : unsigned char { biBindsComponent, biBindsComponentProperty, biBindsOther };

typedef System::Set<TBindCompDesignerBindsType, TBindCompDesignerBindsType::biBindsComponent, TBindCompDesignerBindsType::biBindsOther> TBindCompDesignerBindsTypes;

__interface  INTERFACE_UUID("{45B5E422-5908-4C9E-8073-361A7954F209}") IBindCompDesigner  : public System::IInterface 
{
	virtual bool __fastcall CanBindComponent(TContainedBindCompClass ADataBindingClass, System::Classes::TComponent* AComponent, System::_di_IInterface ADesigner) = 0 ;
	virtual bool __fastcall BindsComponent(TContainedBindComponent* ABindComp, System::Classes::TComponent* AComponent) = 0 ;
	virtual bool __fastcall BindsComponentPropertyName(TContainedBindComponent* ABindComp, const System::UnicodeString APropertyName) = 0 ;
	virtual System::UnicodeString __fastcall GetDescription(TContainedBindComponent* ABindComp) = 0 ;
	virtual bool __fastcall IsReadOnly(TContainedBindComponent* ABindComp, const TBindCompDesignExpression &AExpression) = 0 /* overload */;
	virtual bool __fastcall IsReadOnly(TContainedBindComponent* ABindComp, System::Classes::TCollectionItem* AItem) = 0 /* overload */;
	virtual bool __fastcall IsReadOnly(TContainedBindComponent* ABindComp, System::Classes::TCollection* ACollection) = 0 /* overload */;
#ifndef _WIN64
	virtual System::DynamicArray<TBindCompDesignExpression> __fastcall GetExpressions(TContainedBindComponent* ABindComp, /* out */ TBindCompDesignerExpressionTypes &ATypes) = 0 ;
	virtual System::DynamicArray<TBindCompDesignExpressionCollection> __fastcall GetExpressionCollections(TContainedBindComponent* ABindComp) = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<TBindCompDesignExpression> __fastcall GetExpressions(TContainedBindComponent* ABindComp, /* out */ TBindCompDesignerExpressionTypes &ATypes) = 0 ;
	virtual System::TArray__1<TBindCompDesignExpressionCollection> __fastcall GetExpressionCollections(TContainedBindComponent* ABindComp) = 0 ;
#endif /* _WIN64 */
};

typedef void __fastcall (__closure *TEnumBindCompFactoryProc)(_di_IBindCompFactory BindCompFactory, void * Info);

enum DECLSPEC_DENUM TBoundComponentOption : unsigned char { dbcoptAddDataBindingsProperty, dbcoptApplyToDescendents };

typedef System::Set<TBoundComponentOption, TBoundComponentOption::dbcoptAddDataBindingsProperty, TBoundComponentOption::dbcoptApplyToDescendents> TBoundComponentOptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindEditorFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TBindEditorFactory();
	virtual bool __fastcall Supports(const GUID &AIntf, System::TObject* AObject) = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::UnicodeString> __fastcall GetNames();
#else /* _WIN64 */
	virtual System::TArray__1<System::UnicodeString> __fastcall GetNames();
#endif /* _WIN64 */
	virtual bool __fastcall HasNamedEditor(const System::UnicodeString AName);
	virtual System::_di_IInterface __fastcall CreateEditor(const GUID &AIntf, System::TObject* AObject) = 0 ;
	virtual System::_di_IInterface __fastcall CreateNamedEditor(const GUID &AIntf, const System::UnicodeString AName, System::TObject* AObject);
	virtual bool __fastcall ReleaseEditor(const System::_di_IInterface AEditor);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBindEditorFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindCompError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindCompError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindCompError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindCompError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindCompError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindCompError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindCompError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindCompError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindCompError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindCompError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindCompError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindCompError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindCompError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindCompError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef EBindCompError TBindCompException;

#ifndef _WIN64
typedef System::TMetaClass* TBindEditorFactoryClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TBindEditorFactoryClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TControlObserver : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TComponent* FComponent;
	System::Generics::Collections::TDictionary__2<int,System::Classes::_di_IObserver>* FDictionary;
	bool __fastcall AddObserver(const int ID, System::DelphiInterface<System::Sysutils::TFunc__1<System::Classes::_di_IObserver> > AFunc);
	void __fastcall RemoveObserver(const int ID);
	void __fastcall SetComponent(System::Classes::TComponent* const Value);
	void __fastcall RemoveObservers();
	
public:
	static const int IDEditLinkObserver = int(1);
	
	static const int IDEditGridLinkObserver = int(2);
	
	static const int IDPositionLinkObserver = int(3);
	
	static const int IDControlValueObserver = int(4);
	
	
private:
	System::Classes::_di_IEditGridLinkObserver __fastcall GetEditGridLink();
	System::Classes::_di_IPositionLinkObserver __fastcall GetPositionLinkObserver();
	System::Classes::_di_IControlValueObserver __fastcall GetControlValueObserver();
	System::Classes::_di_IEditLinkObserver __fastcall GetEditLink();
	
public:
	__fastcall TControlObserver();
	bool __fastcall EnsureObserving(const int ID, System::DelphiInterface<System::Sysutils::TFunc__1<System::Classes::_di_IObserver> > AFunc);
	bool __fastcall IsObserving(const int ID);
	System::Classes::_di_IObserver __fastcall GetObserver(const int ID);
	bool __fastcall TrySetActive(bool AValue);
	__fastcall virtual ~TControlObserver();
	void __fastcall Clear();
	__property System::Classes::TComponent* Component = {read=FComponent, write=SetComponent};
	__property System::Classes::_di_IEditGridLinkObserver EditGridLinkObserver = {read=GetEditGridLink};
	__property System::Classes::_di_IPositionLinkObserver PositionLinkObserver = {read=GetPositionLinkObserver};
	__property System::Classes::_di_IEditLinkObserver EditLinkObserver = {read=GetEditLink};
	__property System::Classes::_di_IControlValueObserver ControlValueObserver = {read=GetControlValueObserver};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TObservableMemberOption : unsigned char { moTrack };

typedef System::Set<TObservableMemberOption, TObservableMemberOption::moTrack, TObservableMemberOption::moTrack> TObservableMemberOptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEvalShortcutEnumeratorToEditor : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual void __fastcall Evaluate(TEvalEnumeratorToEditor* const AExpression) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TEvalShortcutEnumeratorToEditor() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEvalShortcutEnumeratorToEditor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEvalShortcutEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	virtual bool __fastcall Evaluate(TEvalEnumerator* const AExpression, const TScopeMemberType *ATypes, const int ATypes_High, /* out */ System::Rtti::TValue &AValue) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TEvalShortcutEnumerator() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEvalShortcutEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEvalShortcutFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual bool __fastcall Supports(TEvalEnumeratorToEditor* const AExpression, /* out */ TEvalShortcutEnumeratorToEditor* &AEvalShortcut) = 0 /* overload */;
	bool __fastcall Supports(TEvalEnumeratorToEditor* const AExpression)/* overload */;
	virtual bool __fastcall Supports(TEvalEnumerator* const AExpression, /* out */ TEvalShortcutEnumerator* &AEvalShortcut) = 0 /* overload */;
	bool __fastcall Supports(TEvalEnumerator* const AExpression)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TEvalShortcutFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TEvalShortcutFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEvalShortcutFactories : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TEvalShortcutFactories* FInstance;
	System::Generics::Collections::TList__1<TEvalShortcutFactory*>* FList;
	
public:
	__fastcall TEvalShortcutFactories();
	__fastcall virtual ~TEvalShortcutFactories();
	bool __fastcall Supports(TEvalEnumeratorToEditor* const AExpression, /* out */ TEvalShortcutEnumeratorToEditor* &AEvalShortcut)/* overload */;
	bool __fastcall Supports(TEvalEnumeratorToEditor* const AExpression)/* overload */;
	bool __fastcall Supports(TEvalEnumerator* const AExpression, /* out */ TEvalShortcutEnumerator* &AEvalShortcut)/* overload */;
	bool __fastcall Supports(TEvalEnumerator* const AExpression)/* overload */;
	void __fastcall Register(TEvalShortcutFactory* const AFactory);
	void __fastcall Unregister(TEvalShortcutFactory* &AFactory);
	/* static */ __property TEvalShortcutFactories* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall (*RegisterBindCompProc)(const System::UnicodeString CategoryName, TContainedBindCompClass const *AClasses, const int AClasses_High);
extern DELPHI_PACKAGE void __fastcall (*UnRegisterBindCompProc)(TContainedBindCompClass const *AClasses, const int AClasses_High);
extern DELPHI_PACKAGE void __fastcall (*EnumRegisteredBindCompsProc)(TEnumBindCompProc Proc, void * Info);
extern DELPHI_PACKAGE TContainedBindComponent* __fastcall (*CreateBindCompProc)(System::Classes::TComponent* AOwner, TContainedBindCompClass BindCompClass);
extern DELPHI_PACKAGE void __fastcall (*RegisterBindCompFactoryProc)(_di_IBindCompFactory AFactory);
extern DELPHI_PACKAGE void __fastcall (*EnumRegisteredBindCompFactoriesProc)(TEnumBindCompFactoryProc Proc, void * Info);
extern DELPHI_PACKAGE void __fastcall (*RegisterBindCompDesignerProc)(TContainedBindCompClass AClass, _di_IBindCompDesigner ADesigner);
extern DELPHI_PACKAGE _di_IBindCompDesigner __fastcall (*GetBindCompDesignerProc)(TContainedBindCompClass AClass);
extern DELPHI_PACKAGE void __fastcall (*RegisterBoundComponentsProc)(System::Classes::TComponentClass const *AClasses, const int AClasses_High, TBoundComponentOptions AFlags);
extern DELPHI_PACKAGE TBoundComponentOptions __fastcall (*GetBoundComponentOptionsProc)(System::Classes::TComponentClass AClass);
extern DELPHI_PACKAGE _di_IScopeRecordEnumerator __fastcall GetScopeRecordEnumerator(System::Classes::TComponent* const ASourceComponent, bool ABuffered)/* overload */;
extern DELPHI_PACKAGE bool __fastcall GetListItemValueExpression(System::Classes::TComponent* AComponent, /* out */ System::UnicodeString &AExpression, /* out */ System::UnicodeString &AHeaderExpression)/* overload */;
extern DELPHI_PACKAGE bool __fastcall GetListItemValueExpression(System::Classes::TComponent* AComponent, /* out */ System::UnicodeString &AExpression)/* overload */;
extern DELPHI_PACKAGE bool __fastcall GetControlValuePropertyName(System::Classes::TComponent* AComponent, /* out */ System::UnicodeString &APropertyName, /* out */ bool &AWritable)/* overload */;
extern DELPHI_PACKAGE bool __fastcall GetControlValuePropertyOptions(System::Classes::TComponent* AComponent, /* out */ TObservableMemberOptions &AOptions)/* overload */;
#ifndef _WIN64
extern DELPHI_PACKAGE System::DynamicArray<System::Classes::TComponentClass> __fastcall GetControlValueClasses(const System::UnicodeString AFrameworkExt, bool FWritableOnly);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::TArray__1<System::Classes::TComponentClass> __fastcall GetControlValueClasses(const System::UnicodeString AFrameworkExt, bool FWritableOnly);
#endif /* _WIN64 */
extern DELPHI_PACKAGE bool __fastcall GetControlValuePropertyName(System::Classes::TComponent* AComponent, /* out */ System::UnicodeString &APropertyName)/* overload */;
extern DELPHI_PACKAGE System::_di_IInterface __fastcall GetBindEditor(System::TObject* AComponent, const GUID &AGuid, const System::UnicodeString AName = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall ReleaseBindEditor(const System::_di_IInterface AEditor);
#ifndef _WIN64
extern DELPHI_PACKAGE System::DynamicArray<System::UnicodeString> __fastcall GetBindEditorNames(System::TObject* AComponent, const GUID &AGuid);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::TArray__1<System::UnicodeString> __fastcall GetBindEditorNames(System::TObject* AComponent, const GUID &AGuid);
#endif /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall RegisterBindComponents(const System::UnicodeString CategoryName, TContainedBindCompClass const *AClasses, const int AClasses_High);
extern DELPHI_PACKAGE void __fastcall UnRegisterBindComponents(TContainedBindCompClass const *AClasses, const int AClasses_High);
extern DELPHI_PACKAGE void __fastcall EnumRegisteredBindComponents(TEnumBindCompProc Proc, void * Info);
extern DELPHI_PACKAGE TContainedBindComponent* __fastcall CreateBindComponent(System::Classes::TComponent* AOwner, TContainedBindCompClass ABindCompClass);
extern DELPHI_PACKAGE void __fastcall RegisterBindCompFactory(_di_IBindCompFactory AFactory);
extern DELPHI_PACKAGE void __fastcall EnumRegisteredBindCompFactories(TEnumBindCompFactoryProc Proc, void * Info);
extern DELPHI_PACKAGE void __fastcall RegisterBindCompDesigner(TContainedBindCompClass AClass, _di_IBindCompDesigner ADesigner);
extern DELPHI_PACKAGE _di_IBindCompDesigner __fastcall GetBindCompDesigner(TContainedBindCompClass AClass);
extern DELPHI_PACKAGE void __fastcall RegisterBoundComponents(System::Classes::TComponentClass const *AClasses, const int AClasses_High, TBoundComponentOptions AFlags);
extern DELPHI_PACKAGE TBoundComponentOptions __fastcall GetBoundComponentOptions(const System::Classes::TComponentClass AClass);
extern DELPHI_PACKAGE void __fastcall RegisterBindEditorFactory(TBindEditorFactoryClass *AFactories, const int AFactories_High);
extern DELPHI_PACKAGE void __fastcall UnregisterBindEditorFactory(TBindEditorFactoryClass *AFactories, const int AFactories_High);
#ifndef _WIN64
extern DELPHI_PACKAGE void __fastcall RegisterObservableMember(System::DynamicArray<System::TClass> AClasses, const System::UnicodeString APropertyName, const System::UnicodeString AFrameworkExt)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterObservableMemberOptions(System::DynamicArray<System::TClass> AClasses, TObservableMemberOptions AOptions)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterValuePropertyName(System::DynamicArray<System::TClass> AClasses, const System::UnicodeString APropertyName, const System::UnicodeString AFrameWorkExt)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterValuePropertyName(System::DynamicArray<System::TClass> AClasses)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterObservableMember(System::DynamicArray<System::TClass> AClasses)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterObservableMemberOptions(System::DynamicArray<System::TClass> AClasses);
extern DELPHI_PACKAGE void __fastcall RegisterListItemValueExpression(System::DynamicArray<System::TClass> AClasses, const System::UnicodeString AExpression, const System::UnicodeString AHeaderExpression = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE void __fastcall UnregisterListItemValueExpression(System::DynamicArray<System::TClass> AClasses)/* overload */;
#else /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall RegisterObservableMember(System::TArray__1<System::TClass> AClasses, const System::UnicodeString APropertyName, const System::UnicodeString AFrameworkExt)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterObservableMemberOptions(System::TArray__1<System::TClass> AClasses, TObservableMemberOptions AOptions)/* overload */;
extern DELPHI_PACKAGE void __fastcall RegisterValuePropertyName(System::TArray__1<System::TClass> AClasses, const System::UnicodeString APropertyName, const System::UnicodeString AFrameWorkExt)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterValuePropertyName(System::TArray__1<System::TClass> AClasses)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterObservableMember(System::TArray__1<System::TClass> AClasses)/* overload */;
extern DELPHI_PACKAGE void __fastcall UnRegisterObservableMemberOptions(System::TArray__1<System::TClass> AClasses);
extern DELPHI_PACKAGE void __fastcall RegisterListItemValueExpression(System::TArray__1<System::TClass> AClasses, const System::UnicodeString AExpression, const System::UnicodeString AHeaderExpression = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE void __fastcall UnregisterListItemValueExpression(System::TArray__1<System::TClass> AClasses)/* overload */;
#endif /* _WIN64 */
extern DELPHI_PACKAGE bool __fastcall IsUnidirectionalDataSource(System::Classes::TComponent* ADataSource);
extern DELPHI_PACKAGE void __fastcall CheckUnidirectionalDataSource(System::Classes::TComponent* ADataSource, TContainedBindComponent* ABindComponent);
}	/* namespace Components */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_COMPONENTS)
using namespace Data::Bind::Components;
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
#endif	// Data_Bind_ComponentsHPP
