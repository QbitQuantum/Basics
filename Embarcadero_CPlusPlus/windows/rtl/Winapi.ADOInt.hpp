// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ADOInt.pas' rev: 34.00 (Windows)

#ifndef Winapi_AdointHPP
#define Winapi_AdointHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Adoint
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE _Connection;
typedef System::DelphiInterface<_Connection> _di__Connection;
__interface DELPHIINTERFACE _Record;
typedef System::DelphiInterface<_Record> _di__Record;
__interface DELPHIINTERFACE _Stream;
typedef System::DelphiInterface<_Stream> _di__Stream;
__interface DELPHIINTERFACE _Command;
typedef System::DelphiInterface<_Command> _di__Command;
__interface DELPHIINTERFACE _Recordset;
typedef System::DelphiInterface<_Recordset> _di__Recordset;
__interface DELPHIINTERFACE _Parameter;
typedef System::DelphiInterface<_Parameter> _di__Parameter;
__interface DELPHIINTERFACE IDataspace;
typedef System::DelphiInterface<IDataspace> _di_IDataspace;
__interface DELPHIINTERFACE _Collection;
typedef System::DelphiInterface<_Collection> _di__Collection;
__dispinterface _CollectionDisp;
typedef System::DelphiInterface<_CollectionDisp> _di__CollectionDisp;
__interface DELPHIINTERFACE _DynaCollection;
typedef System::DelphiInterface<_DynaCollection> _di__DynaCollection;
__dispinterface _DynaCollectionDisp;
typedef System::DelphiInterface<_DynaCollectionDisp> _di__DynaCollectionDisp;
__interface DELPHIINTERFACE _ADO;
typedef System::DelphiInterface<_ADO> _di__ADO;
__dispinterface _ADODisp;
typedef System::DelphiInterface<_ADODisp> _di__ADODisp;
__interface DELPHIINTERFACE Properties;
typedef System::DelphiInterface<Properties> _di_Properties;
__dispinterface PropertiesDisp;
typedef System::DelphiInterface<PropertiesDisp> _di_PropertiesDisp;
__interface DELPHIINTERFACE Property_;
typedef System::DelphiInterface<Property_> _di_Property_;
__dispinterface Property_Disp;
typedef System::DelphiInterface<Property_Disp> _di_Property_Disp;
__interface DELPHIINTERFACE Error;
typedef System::DelphiInterface<Error> _di_Error;
__dispinterface ErrorDisp;
typedef System::DelphiInterface<ErrorDisp> _di_ErrorDisp;
__interface DELPHIINTERFACE Errors;
typedef System::DelphiInterface<Errors> _di_Errors;
__dispinterface ErrorsDisp;
typedef System::DelphiInterface<ErrorsDisp> _di_ErrorsDisp;
__interface DELPHIINTERFACE Command15;
typedef System::DelphiInterface<Command15> _di_Command15;
__dispinterface Command15Disp;
typedef System::DelphiInterface<Command15Disp> _di_Command15Disp;
__interface DELPHIINTERFACE Connection15;
typedef System::DelphiInterface<Connection15> _di_Connection15;
__dispinterface Connection15Disp;
typedef System::DelphiInterface<Connection15Disp> _di_Connection15Disp;
__dispinterface _ConnectionDisp;
typedef System::DelphiInterface<_ConnectionDisp> _di__ConnectionDisp;
__interface DELPHIINTERFACE Recordset15;
typedef System::DelphiInterface<Recordset15> _di_Recordset15;
__dispinterface Recordset15Disp;
typedef System::DelphiInterface<Recordset15Disp> _di_Recordset15Disp;
__interface DELPHIINTERFACE Recordset20;
typedef System::DelphiInterface<Recordset20> _di_Recordset20;
__dispinterface Recordset20Disp;
typedef System::DelphiInterface<Recordset20Disp> _di_Recordset20Disp;
__interface DELPHIINTERFACE Recordset21;
typedef System::DelphiInterface<Recordset21> _di_Recordset21;
__dispinterface Recordset21Disp;
typedef System::DelphiInterface<Recordset21Disp> _di_Recordset21Disp;
__dispinterface _RecordsetDisp;
typedef System::DelphiInterface<_RecordsetDisp> _di__RecordsetDisp;
__interface DELPHIINTERFACE Fields15;
typedef System::DelphiInterface<Fields15> _di_Fields15;
__dispinterface Fields15Disp;
typedef System::DelphiInterface<Fields15Disp> _di_Fields15Disp;
__interface DELPHIINTERFACE Fields20;
typedef System::DelphiInterface<Fields20> _di_Fields20;
__dispinterface Fields20Disp;
typedef System::DelphiInterface<Fields20Disp> _di_Fields20Disp;
__interface DELPHIINTERFACE Fields;
typedef System::DelphiInterface<Fields> _di_Fields;
__dispinterface FieldsDisp;
typedef System::DelphiInterface<FieldsDisp> _di_FieldsDisp;
__interface DELPHIINTERFACE Field20;
typedef System::DelphiInterface<Field20> _di_Field20;
__dispinterface Field20Disp;
typedef System::DelphiInterface<Field20Disp> _di_Field20Disp;
__interface DELPHIINTERFACE Field;
typedef System::DelphiInterface<Field> _di_Field;
__dispinterface FieldDisp;
typedef System::DelphiInterface<FieldDisp> _di_FieldDisp;
__dispinterface _ParameterDisp;
typedef System::DelphiInterface<_ParameterDisp> _di__ParameterDisp;
__interface DELPHIINTERFACE Parameters;
typedef System::DelphiInterface<Parameters> _di_Parameters;
__dispinterface ParametersDisp;
typedef System::DelphiInterface<ParametersDisp> _di_ParametersDisp;
__interface DELPHIINTERFACE Command25;
typedef System::DelphiInterface<Command25> _di_Command25;
__dispinterface Command25Disp;
typedef System::DelphiInterface<Command25Disp> _di_Command25Disp;
__dispinterface _CommandDisp;
typedef System::DelphiInterface<_CommandDisp> _di__CommandDisp;
__interface DELPHIINTERFACE ConnectionEventsVt;
typedef System::DelphiInterface<ConnectionEventsVt> _di_ConnectionEventsVt;
__interface DELPHIINTERFACE RecordsetEventsVt;
typedef System::DelphiInterface<RecordsetEventsVt> _di_RecordsetEventsVt;
__dispinterface ConnectionEvents;
typedef System::DelphiInterface<ConnectionEvents> _di_ConnectionEvents;
__dispinterface RecordsetEvents;
typedef System::DelphiInterface<RecordsetEvents> _di_RecordsetEvents;
__interface DELPHIINTERFACE ADOConnectionConstruction15;
typedef System::DelphiInterface<ADOConnectionConstruction15> _di_ADOConnectionConstruction15;
__interface DELPHIINTERFACE ADOConnectionConstruction;
typedef System::DelphiInterface<ADOConnectionConstruction> _di_ADOConnectionConstruction;
__dispinterface _RecordDisp;
typedef System::DelphiInterface<_RecordDisp> _di__RecordDisp;
__dispinterface _StreamDisp;
typedef System::DelphiInterface<_StreamDisp> _di__StreamDisp;
__interface DELPHIINTERFACE ADORecordConstruction;
typedef System::DelphiInterface<ADORecordConstruction> _di_ADORecordConstruction;
__interface DELPHIINTERFACE ADOStreamConstruction;
typedef System::DelphiInterface<ADOStreamConstruction> _di_ADOStreamConstruction;
__interface DELPHIINTERFACE ADOCommandConstruction;
typedef System::DelphiInterface<ADOCommandConstruction> _di_ADOCommandConstruction;
__interface DELPHIINTERFACE ADORecordsetConstruction;
typedef System::DelphiInterface<ADORecordsetConstruction> _di_ADORecordsetConstruction;
__interface DELPHIINTERFACE Field15;
typedef System::DelphiInterface<Field15> _di_Field15;
__dispinterface Field15Disp;
typedef System::DelphiInterface<Field15Disp> _di_Field15Disp;
__dispinterface IDataspaceDisp;
typedef System::DelphiInterface<IDataspaceDisp> _di_IDataspaceDisp;
class DELPHICLASS CoConnection;
class DELPHICLASS CoRecord_;
class DELPHICLASS CoStream;
class DELPHICLASS CoCommand;
class DELPHICLASS CoRecordset;
class DELPHICLASS CoParameter;
//-- type declarations -------------------------------------------------------
typedef _di__Connection Connection;

typedef _di__Record Record_;

typedef _di__Stream Stream;

typedef _di__Command Command;

typedef _di__Recordset Recordset;

typedef _di__Parameter Parameter;

typedef _di_IDataspace DataSpace;

typedef System::OleVariant *POleVariant1;

__interface  INTERFACE_UUID("{00000512-0000-0010-8000-00AA006D2EA4}") _Collection  : public IDispatch 
{
	virtual HRESULT __safecall Get_Count(int &__Get_Count_result) = 0 ;
	virtual HRESULT __safecall _NewEnum(System::_di_IInterface &___NewEnum_result) = 0 ;
	virtual HRESULT __safecall Refresh() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Count() { int __r; HRESULT __hr = Get_Count(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Count = {read=_scw_Get_Count};
};

__dispinterface  INTERFACE_UUID("{00000512-0000-0010-8000-00AA006D2EA4}") _CollectionDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000513-0000-0010-8000-00AA006D2EA4}") _DynaCollection  : public _Collection 
{
	virtual HRESULT __safecall Append(const _di_IDispatch Object_) = 0 ;
	virtual HRESULT __safecall Delete(System::OleVariant Index) = 0 ;
};

__dispinterface  INTERFACE_UUID("{00000513-0000-0010-8000-00AA006D2EA4}") _DynaCollectionDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000534-0000-0010-8000-00AA006D2EA4}") _ADO  : public IDispatch 
{
	virtual HRESULT __safecall Get_Properties(_di_Properties &__Get_Properties_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Properties _scw_Get_Properties() { _di_Properties __r; HRESULT __hr = Get_Properties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Properties Properties = {read=_scw_Get_Properties};
};

__dispinterface  INTERFACE_UUID("{00000534-0000-0010-8000-00AA006D2EA4}") _ADODisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000504-0000-0010-8000-00AA006D2EA4}") Properties  : public _Collection 
{
	
public:
	_di_Property_ operator[](System::OleVariant Index) { return this->Item[Index]; }
	virtual HRESULT __safecall Get_Item(System::OleVariant Index, _di_Property_ &__Get_Item_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Property_ _scw_Get_Item(System::OleVariant Index) { _di_Property_ __r; HRESULT __hr = Get_Item(Index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Property_ Item[System::OleVariant Index] = {read=_scw_Get_Item/*, default*/};
};

__dispinterface  INTERFACE_UUID("{00000504-0000-0010-8000-00AA006D2EA4}") PropertiesDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000503-0000-0010-8000-00AA006D2EA4}") Property_  : public IDispatch 
{
	virtual HRESULT __safecall Get_Value(System::OleVariant &__Get_Value_result) = 0 ;
	virtual HRESULT __safecall Set_Value(System::OleVariant pval) = 0 ;
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_Type_(Winapi::Activex::TOleEnum &__Get_Type__result) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int &__Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int plAttributes) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Value() { System::OleVariant __r; HRESULT __hr = Get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Value = {read=_scw_Get_Value, write=Set_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Type_() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Type_ = {read=_scw_Get_Type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes() { int __r; HRESULT __hr = Get_Attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Attributes = {read=_scw_Get_Attributes, write=Set_Attributes};
};

__dispinterface  INTERFACE_UUID("{00000503-0000-0010-8000-00AA006D2EA4}") Property_Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000500-0000-0010-8000-00AA006D2EA4}") Error  : public IDispatch 
{
	virtual HRESULT __safecall Get_Number(int &__Get_Number_result) = 0 ;
	virtual HRESULT __safecall Get_Source(System::WideString &__Get_Source_result) = 0 ;
	virtual HRESULT __safecall Get_Description(System::WideString &__Get_Description_result) = 0 ;
	virtual HRESULT __safecall Get_HelpFile(System::WideString &__Get_HelpFile_result) = 0 ;
	virtual HRESULT __safecall Get_HelpContext(int &__Get_HelpContext_result) = 0 ;
	virtual HRESULT __safecall Get_SQLState(System::WideString &__Get_SQLState_result) = 0 ;
	virtual HRESULT __safecall Get_NativeError(int &__Get_NativeError_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Number() { int __r; HRESULT __hr = Get_Number(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Number = {read=_scw_Get_Number};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Source() { System::WideString __r; HRESULT __hr = Get_Source(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Source = {read=_scw_Get_Source};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Description() { System::WideString __r; HRESULT __hr = Get_Description(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Description = {read=_scw_Get_Description};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_HelpFile() { System::WideString __r; HRESULT __hr = Get_HelpFile(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString HelpFile = {read=_scw_Get_HelpFile};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_HelpContext() { int __r; HRESULT __hr = Get_HelpContext(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int HelpContext = {read=_scw_Get_HelpContext};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_SQLState() { System::WideString __r; HRESULT __hr = Get_SQLState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString SQLState = {read=_scw_Get_SQLState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_NativeError() { int __r; HRESULT __hr = Get_NativeError(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int NativeError = {read=_scw_Get_NativeError};
};

__dispinterface  INTERFACE_UUID("{00000500-0000-0010-8000-00AA006D2EA4}") ErrorDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000501-0000-0010-8000-00AA006D2EA4}") Errors  : public _Collection 
{
	
public:
	_di_Error operator[](System::OleVariant Index) { return this->Item[Index]; }
	virtual HRESULT __safecall Get_Item(System::OleVariant Index, _di_Error &__Get_Item_result) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Error _scw_Get_Item(System::OleVariant Index) { _di_Error __r; HRESULT __hr = Get_Item(Index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Error Item[System::OleVariant Index] = {read=_scw_Get_Item/*, default*/};
};

__dispinterface  INTERFACE_UUID("{00000501-0000-0010-8000-00AA006D2EA4}") ErrorsDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000508-0000-0010-8000-00AA006D2EA4}") Command15  : public _ADO 
{
	virtual HRESULT __safecall Get_ActiveConnection(_di__Connection &__Get_ActiveConnection_result) = 0 ;
	virtual HRESULT __safecall Set_ActiveConnection(const _di__Connection ppvObject) = 0 ;
	virtual HRESULT __safecall _Set_ActiveConnection(System::OleVariant ppvObject) = 0 ;
	virtual HRESULT __safecall Get_CommandText(System::WideString &__Get_CommandText_result) = 0 ;
	virtual HRESULT __safecall Set_CommandText(const System::WideString pbstr) = 0 ;
	virtual HRESULT __safecall Get_CommandTimeout(int &__Get_CommandTimeout_result) = 0 ;
	virtual HRESULT __safecall Set_CommandTimeout(int pl) = 0 ;
	virtual HRESULT __safecall Get_Prepared(System::WordBool &__Get_Prepared_result) = 0 ;
	virtual HRESULT __safecall Set_Prepared(System::WordBool pfPrepared) = 0 ;
	virtual HRESULT __safecall Execute(/* out */ System::OleVariant &RecordsAffected, const System::OleVariant &Parameters, int Options, _di__Recordset &__Execute_result) = 0 ;
	virtual HRESULT __safecall CreateParameter(const System::WideString Name, Winapi::Activex::TOleEnum Type_, Winapi::Activex::TOleEnum Direction, NativeInt Size, System::OleVariant Value, _di__Parameter &__CreateParameter_result) = 0 ;
	virtual HRESULT __safecall Get_Parameters(_di_Parameters &__Get_Parameters_result) = 0 ;
	virtual HRESULT __safecall Set_CommandType(Winapi::Activex::TOleEnum plCmdType) = 0 ;
	virtual HRESULT __safecall Get_CommandType(Winapi::Activex::TOleEnum &__Get_CommandType_result) = 0 ;
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Set_Name(const System::WideString pbstrName) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_CommandText() { System::WideString __r; HRESULT __hr = Get_CommandText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString CommandText = {read=_scw_Get_CommandText, write=Set_CommandText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CommandTimeout() { int __r; HRESULT __hr = Get_CommandTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int CommandTimeout = {read=_scw_Get_CommandTimeout, write=Set_CommandTimeout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_Prepared() { System::WordBool __r; HRESULT __hr = Get_Prepared(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool Prepared = {read=_scw_Get_Prepared, write=Set_Prepared};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Parameters _scw_Get_Parameters() { _di_Parameters __r; HRESULT __hr = Get_Parameters(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Parameters Parameters = {read=_scw_Get_Parameters};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_CommandType() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_CommandType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum CommandType = {read=_scw_Get_CommandType, write=Set_CommandType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name, write=Set_Name};
};

__dispinterface  INTERFACE_UUID("{00000508-0000-0010-8000-00AA006D2EA4}") Command15Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000515-0000-0010-8000-00AA006D2EA4}") Connection15  : public _ADO 
{
	virtual HRESULT __safecall Get_ConnectionString(System::WideString &__Get_ConnectionString_result) = 0 ;
	virtual HRESULT __safecall Set_ConnectionString(const System::WideString pbstr) = 0 ;
	virtual HRESULT __safecall Get_CommandTimeout(int &__Get_CommandTimeout_result) = 0 ;
	virtual HRESULT __safecall Set_CommandTimeout(int plTimeout) = 0 ;
	virtual HRESULT __safecall Get_ConnectionTimeout(int &__Get_ConnectionTimeout_result) = 0 ;
	virtual HRESULT __safecall Set_ConnectionTimeout(int plTimeout) = 0 ;
	virtual HRESULT __safecall Get_Version(System::WideString &__Get_Version_result) = 0 ;
	virtual HRESULT __safecall Close() = 0 ;
	virtual HRESULT __safecall Execute(const System::WideString CommandText, /* out */ System::OleVariant &RecordsAffected, int Options, _di__Recordset &__Execute_result) = 0 ;
	virtual HRESULT __safecall BeginTrans(int &__BeginTrans_result) = 0 ;
	virtual HRESULT __safecall CommitTrans() = 0 ;
	virtual HRESULT __safecall RollbackTrans() = 0 ;
	virtual HRESULT __safecall Open(const System::WideString ConnectionString, const System::WideString UserID, const System::WideString Password, int Options) = 0 ;
	virtual HRESULT __safecall Get_Errors(_di_Errors &__Get_Errors_result) = 0 ;
	virtual HRESULT __safecall Get_DefaultDatabase(System::WideString &__Get_DefaultDatabase_result) = 0 ;
	virtual HRESULT __safecall Set_DefaultDatabase(const System::WideString pbstr) = 0 ;
	virtual HRESULT __safecall Get_IsolationLevel(Winapi::Activex::TOleEnum &__Get_IsolationLevel_result) = 0 ;
	virtual HRESULT __safecall Set_IsolationLevel(Winapi::Activex::TOleEnum Level) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int &__Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int plAttr) = 0 ;
	virtual HRESULT __safecall Get_CursorLocation(Winapi::Activex::TOleEnum &__Get_CursorLocation_result) = 0 ;
	virtual HRESULT __safecall Set_CursorLocation(Winapi::Activex::TOleEnum plCursorLoc) = 0 ;
	virtual HRESULT __safecall Get_Mode(Winapi::Activex::TOleEnum &__Get_Mode_result) = 0 ;
	virtual HRESULT __safecall Set_Mode(Winapi::Activex::TOleEnum plMode) = 0 ;
	virtual HRESULT __safecall Get_Provider(System::WideString &__Get_Provider_result) = 0 ;
	virtual HRESULT __safecall Set_Provider(const System::WideString pbstr) = 0 ;
	virtual HRESULT __safecall Get_State(int &__Get_State_result) = 0 ;
	virtual HRESULT __safecall OpenSchema(Winapi::Activex::TOleEnum Schema, System::OleVariant Restrictions, System::OleVariant SchemaID, _di__Recordset &__OpenSchema_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_ConnectionString() { System::WideString __r; HRESULT __hr = Get_ConnectionString(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString ConnectionString = {read=_scw_Get_ConnectionString, write=Set_ConnectionString};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CommandTimeout() { int __r; HRESULT __hr = Get_CommandTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int CommandTimeout = {read=_scw_Get_CommandTimeout, write=Set_CommandTimeout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_ConnectionTimeout() { int __r; HRESULT __hr = Get_ConnectionTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ConnectionTimeout = {read=_scw_Get_ConnectionTimeout, write=Set_ConnectionTimeout};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Version() { System::WideString __r; HRESULT __hr = Get_Version(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Version = {read=_scw_Get_Version};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Errors _scw_Get_Errors() { _di_Errors __r; HRESULT __hr = Get_Errors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Errors Errors = {read=_scw_Get_Errors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_DefaultDatabase() { System::WideString __r; HRESULT __hr = Get_DefaultDatabase(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString DefaultDatabase = {read=_scw_Get_DefaultDatabase, write=Set_DefaultDatabase};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_IsolationLevel() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_IsolationLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum IsolationLevel = {read=_scw_Get_IsolationLevel, write=Set_IsolationLevel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes() { int __r; HRESULT __hr = Get_Attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Attributes = {read=_scw_Get_Attributes, write=Set_Attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_CursorLocation() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_CursorLocation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum CursorLocation = {read=_scw_Get_CursorLocation, write=Set_CursorLocation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Mode() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Mode = {read=_scw_Get_Mode, write=Set_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Provider() { System::WideString __r; HRESULT __hr = Get_Provider(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Provider = {read=_scw_Get_Provider, write=Set_Provider};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_State() { int __r; HRESULT __hr = Get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int State = {read=_scw_Get_State};
};

__dispinterface  INTERFACE_UUID("{00000515-0000-0010-8000-00AA006D2EA4}") Connection15Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000550-0000-0010-8000-00AA006D2EA4}") _Connection  : public Connection15 
{
	virtual HRESULT __safecall Cancel() = 0 ;
};

__dispinterface  INTERFACE_UUID("{00000550-0000-0010-8000-00AA006D2EA4}") _ConnectionDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000050E-0000-0010-8000-00AA006D2EA4}") Recordset15  : public _ADO 
{
	virtual HRESULT __safecall Get_AbsolutePosition(NativeUInt &__Get_AbsolutePosition_result) = 0 ;
	virtual HRESULT __safecall Set_AbsolutePosition(NativeUInt pl) = 0 ;
	virtual HRESULT __safecall _Set_ActiveConnection(const _di_IDispatch pvar) = 0 ;
	virtual HRESULT __safecall Set_ActiveConnection(System::OleVariant pvar) = 0 ;
	virtual HRESULT __safecall Get_ActiveConnection(System::OleVariant &__Get_ActiveConnection_result) = 0 ;
	virtual HRESULT __safecall Get_BOF(System::WordBool &__Get_BOF_result) = 0 ;
	virtual HRESULT __safecall Get_Bookmark(System::OleVariant &__Get_Bookmark_result) = 0 ;
	virtual HRESULT __safecall Set_Bookmark(System::OleVariant pvBookmark) = 0 ;
	virtual HRESULT __safecall Get_CacheSize(int &__Get_CacheSize_result) = 0 ;
	virtual HRESULT __safecall Set_CacheSize(int pl) = 0 ;
	virtual HRESULT __safecall Get_CursorType(Winapi::Activex::TOleEnum &__Get_CursorType_result) = 0 ;
	virtual HRESULT __safecall Set_CursorType(Winapi::Activex::TOleEnum plCursorType) = 0 ;
	virtual HRESULT __safecall Get_EOF(System::WordBool &__Get_EOF_result) = 0 ;
	virtual HRESULT __safecall Get_Fields(_di_Fields &__Get_Fields_result) = 0 ;
	virtual HRESULT __safecall Get_LockType(Winapi::Activex::TOleEnum &__Get_LockType_result) = 0 ;
	virtual HRESULT __safecall Set_LockType(Winapi::Activex::TOleEnum plLockType) = 0 ;
	virtual HRESULT __safecall Get_MaxRecords(NativeInt &__Get_MaxRecords_result) = 0 ;
	virtual HRESULT __safecall Set_MaxRecords(NativeInt plMaxRecords) = 0 ;
	virtual HRESULT __safecall Get_RecordCount(NativeInt &__Get_RecordCount_result) = 0 ;
	virtual HRESULT __safecall _Set_Source(const _di_IDispatch pvSource) = 0 ;
	virtual HRESULT __safecall Set_Source(const System::WideString pvSource) = 0 ;
	virtual HRESULT __safecall Get_Source(System::OleVariant &__Get_Source_result) = 0 ;
	virtual HRESULT __safecall AddNew(System::OleVariant FieldList, System::OleVariant Values) = 0 ;
	virtual HRESULT __safecall CancelUpdate() = 0 ;
	virtual HRESULT __safecall Close() = 0 ;
	virtual HRESULT __safecall Delete(Winapi::Activex::TOleEnum AffectRecords) = 0 ;
	virtual HRESULT __safecall GetRows(int Rows, System::OleVariant Start, System::OleVariant Fields, System::OleVariant &__GetRows_result) = 0 ;
	virtual HRESULT __safecall Move(NativeInt NumRecords, System::OleVariant Start) = 0 ;
	virtual HRESULT __safecall MoveNext() = 0 ;
	virtual HRESULT __safecall MovePrevious() = 0 ;
	virtual HRESULT __safecall MoveFirst() = 0 ;
	virtual HRESULT __safecall MoveLast() = 0 ;
	virtual HRESULT __safecall Open(System::OleVariant Source, System::OleVariant ActiveConnection, Winapi::Activex::TOleEnum CursorType, Winapi::Activex::TOleEnum LockType, int Options) = 0 ;
	virtual HRESULT __safecall Requery(int Options) = 0 ;
	virtual HRESULT __safecall _xResync(Winapi::Activex::TOleEnum AffectRecords) = 0 ;
	virtual HRESULT __safecall Update(System::OleVariant Fields, System::OleVariant Values) = 0 ;
	virtual HRESULT __safecall Get_AbsolutePage(NativeUInt &__Get_AbsolutePage_result) = 0 ;
	virtual HRESULT __safecall Set_AbsolutePage(NativeUInt pl) = 0 ;
	virtual HRESULT __safecall Get_EditMode(Winapi::Activex::TOleEnum &__Get_EditMode_result) = 0 ;
	virtual HRESULT __safecall Get_Filter(System::OleVariant &__Get_Filter_result) = 0 ;
	virtual HRESULT __safecall Set_Filter(System::OleVariant Criteria) = 0 ;
	virtual HRESULT __safecall Get_PageCount(NativeInt &__Get_PageCount_result) = 0 ;
	virtual HRESULT __safecall Get_PageSize(int &__Get_PageSize_result) = 0 ;
	virtual HRESULT __safecall Set_PageSize(int pl) = 0 ;
	virtual HRESULT __safecall Get_Sort(System::WideString &__Get_Sort_result) = 0 ;
	virtual HRESULT __safecall Set_Sort(const System::WideString Criteria) = 0 ;
	virtual HRESULT __safecall Get_Status(int &__Get_Status_result) = 0 ;
	virtual HRESULT __safecall Get_State(int &__Get_State_result) = 0 ;
	virtual HRESULT __safecall _xClone(_di__Recordset &___xClone_result) = 0 ;
	virtual HRESULT __safecall UpdateBatch(Winapi::Activex::TOleEnum AffectRecords) = 0 ;
	virtual HRESULT __safecall CancelBatch(Winapi::Activex::TOleEnum AffectRecords) = 0 ;
	virtual HRESULT __safecall Get_CursorLocation(Winapi::Activex::TOleEnum &__Get_CursorLocation_result) = 0 ;
	virtual HRESULT __safecall Set_CursorLocation(Winapi::Activex::TOleEnum plCursorLoc) = 0 ;
	virtual HRESULT __safecall NextRecordset(/* out */ System::OleVariant &RecordsAffected, _di__Recordset &__NextRecordset_result) = 0 ;
	virtual HRESULT __safecall Supports(Winapi::Activex::TOleEnum CursorOptions, System::WordBool &__Supports_result) = 0 ;
	virtual HRESULT __safecall Get_Collect(System::OleVariant Index, System::OleVariant &__Get_Collect_result) = 0 ;
	virtual HRESULT __safecall Set_Collect(System::OleVariant Index, System::OleVariant pvar) = 0 ;
	virtual HRESULT __safecall Get_MarshalOptions(Winapi::Activex::TOleEnum &__Get_MarshalOptions_result) = 0 ;
	virtual HRESULT __safecall Set_MarshalOptions(Winapi::Activex::TOleEnum peMarshal) = 0 ;
	virtual HRESULT __safecall Find(const System::WideString Criteria, NativeInt SkipRecords, Winapi::Activex::TOleEnum SearchDirection, System::OleVariant Start) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeUInt _scw_Get_AbsolutePosition() { NativeUInt __r; HRESULT __hr = Get_AbsolutePosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeUInt AbsolutePosition = {read=_scw_Get_AbsolutePosition, write=Set_AbsolutePosition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_BOF() { System::WordBool __r; HRESULT __hr = Get_BOF(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool BOF = {read=_scw_Get_BOF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Bookmark() { System::OleVariant __r; HRESULT __hr = Get_Bookmark(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Bookmark = {read=_scw_Get_Bookmark, write=Set_Bookmark};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_CacheSize() { int __r; HRESULT __hr = Get_CacheSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int CacheSize = {read=_scw_Get_CacheSize, write=Set_CacheSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_CursorType() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_CursorType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum CursorType = {read=_scw_Get_CursorType, write=Set_CursorType};
	System::WordBool _scw_Get_EOF() { System::WordBool __r; HRESULT __hr = Get_EOF(__r); System::CheckSafecallResult(__hr); return __r; }
	__property System::WordBool Eof = {read=_scw_Get_EOF};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fields _scw_Get_Fields() { _di_Fields __r; HRESULT __hr = Get_Fields(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fields Fields = {read=_scw_Get_Fields};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_LockType() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_LockType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum LockType = {read=_scw_Get_LockType, write=Set_LockType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_MaxRecords() { NativeInt __r; HRESULT __hr = Get_MaxRecords(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt MaxRecords = {read=_scw_Get_MaxRecords, write=Set_MaxRecords};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_RecordCount() { NativeInt __r; HRESULT __hr = Get_RecordCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt RecordCount = {read=_scw_Get_RecordCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeUInt _scw_Get_AbsolutePage() { NativeUInt __r; HRESULT __hr = Get_AbsolutePage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeUInt AbsolutePage = {read=_scw_Get_AbsolutePage, write=Set_AbsolutePage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_EditMode() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_EditMode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum EditMode = {read=_scw_Get_EditMode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Filter() { System::OleVariant __r; HRESULT __hr = Get_Filter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Filter = {read=_scw_Get_Filter, write=Set_Filter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_PageCount() { NativeInt __r; HRESULT __hr = Get_PageCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt PageCount = {read=_scw_Get_PageCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_PageSize() { int __r; HRESULT __hr = Get_PageSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int PageSize = {read=_scw_Get_PageSize, write=Set_PageSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Sort() { System::WideString __r; HRESULT __hr = Get_Sort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Sort = {read=_scw_Get_Sort, write=Set_Sort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Status() { int __r; HRESULT __hr = Get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_Get_Status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_State() { int __r; HRESULT __hr = Get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_CursorLocation() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_CursorLocation(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum CursorLocation = {read=_scw_Get_CursorLocation, write=Set_CursorLocation};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Collect(System::OleVariant Index) { System::OleVariant __r; HRESULT __hr = Get_Collect(Index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Collect[System::OleVariant Index] = {read=_scw_Get_Collect, write=Set_Collect};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_MarshalOptions() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_MarshalOptions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum MarshalOptions = {read=_scw_Get_MarshalOptions, write=Set_MarshalOptions};
};

__dispinterface  INTERFACE_UUID("{0000050E-0000-0010-8000-00AA006D2EA4}") Recordset15Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000054F-0000-0010-8000-00AA006D2EA4}") Recordset20  : public Recordset15 
{
	virtual HRESULT __safecall Cancel() = 0 ;
	virtual HRESULT __safecall Get_DataSource(System::_di_IInterface &__Get_DataSource_result) = 0 ;
	virtual HRESULT __safecall _Set_DataSource(const System::_di_IInterface ppunkDataSource) = 0 ;
	virtual HRESULT __safecall _xSave(const System::WideString FileName, Winapi::Activex::TOleEnum PersistFormat) = 0 ;
	virtual HRESULT __safecall Get_ActiveCommand(_di_IDispatch &__Get_ActiveCommand_result) = 0 ;
	virtual HRESULT __safecall Set_StayInSync(System::WordBool pbStayInSync) = 0 ;
	virtual HRESULT __safecall Get_StayInSync(System::WordBool &__Get_StayInSync_result) = 0 ;
	virtual HRESULT __safecall GetString(Winapi::Activex::TOleEnum StringFormat, int NumRows, const System::WideString ColumnDelimeter, const System::WideString RowDelimeter, const System::WideString NullExpr, System::WideString &__GetString_result) = 0 ;
	virtual HRESULT __safecall Get_DataMember(System::WideString &__Get_DataMember_result) = 0 ;
	virtual HRESULT __safecall Set_DataMember(const System::WideString pbstrDataMember) = 0 ;
	virtual HRESULT __safecall CompareBookmarks(System::OleVariant Bookmark1, System::OleVariant Bookmark2, Winapi::Activex::TOleEnum &__CompareBookmarks_result) = 0 ;
	virtual HRESULT __safecall Clone(Winapi::Activex::TOleEnum LockType, _di__Recordset &__Clone_result) = 0 ;
	virtual HRESULT __safecall Resync(Winapi::Activex::TOleEnum AffectRecords, Winapi::Activex::TOleEnum ResyncValues) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get_DataSource() { System::_di_IInterface __r; HRESULT __hr = Get_DataSource(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface DataSource = {read=_scw_Get_DataSource, write=_Set_DataSource};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IDispatch _scw_Get_ActiveCommand() { _di_IDispatch __r; HRESULT __hr = Get_ActiveCommand(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IDispatch ActiveCommand = {read=_scw_Get_ActiveCommand};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_StayInSync() { System::WordBool __r; HRESULT __hr = Get_StayInSync(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool StayInSync = {read=_scw_Get_StayInSync, write=Set_StayInSync};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_DataMember() { System::WideString __r; HRESULT __hr = Get_DataMember(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString DataMember = {read=_scw_Get_DataMember, write=Set_DataMember};
};

__dispinterface  INTERFACE_UUID("{0000054F-0000-0010-8000-00AA006D2EA4}") Recordset20Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000555-0000-0010-8000-00AA006D2EA4}") Recordset21  : public Recordset20 
{
	virtual HRESULT __safecall Seek(System::OleVariant KeyValues, Winapi::Activex::TOleEnum SeekOption) = 0 ;
	virtual HRESULT __safecall Set_Index(const System::WideString pbstrIndex) = 0 ;
	virtual HRESULT __safecall Get_Index(System::WideString &__Get_Index_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Index() { System::WideString __r; HRESULT __hr = Get_Index(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Index = {read=_scw_Get_Index, write=Set_Index};
};

__dispinterface  INTERFACE_UUID("{00000555-0000-0010-8000-00AA006D2EA4}") Recordset21Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000556-0000-0010-8000-00AA006D2EA4}") _Recordset  : public Recordset21 
{
	virtual HRESULT __safecall Save(System::OleVariant Destination, Winapi::Activex::TOleEnum PersistFormat) = 0 ;
};

__dispinterface  INTERFACE_UUID("{00000556-0000-0010-8000-00AA006D2EA4}") _RecordsetDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000506-0000-0010-8000-00AA006D2EA4}") Fields15  : public _Collection 
{
	
public:
	_di_Field operator[](System::OleVariant Index) { return this->Item[Index]; }
	virtual HRESULT __safecall Get_Item(System::OleVariant Index, _di_Field &__Get_Item_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Field _scw_Get_Item(System::OleVariant Index) { _di_Field __r; HRESULT __hr = Get_Item(Index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Field Item[System::OleVariant Index] = {read=_scw_Get_Item/*, default*/};
};

__dispinterface  INTERFACE_UUID("{00000506-0000-0010-8000-00AA006D2EA4}") Fields15Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000054D-0000-0010-8000-00AA006D2EA4}") Fields20  : public Fields15 
{
	virtual HRESULT __safecall _Append(const System::WideString Name, Winapi::Activex::TOleEnum Type_, NativeInt DefinedSize, Winapi::Activex::TOleEnum Attrib) = 0 ;
	virtual HRESULT __safecall Delete(System::OleVariant Index) = 0 ;
};

__dispinterface  INTERFACE_UUID("{0000054D-0000-0010-8000-00AA006D2EA4}") Fields20Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000564-0000-0010-8000-00AA006D2EA4}") Fields  : public Fields20 
{
	virtual HRESULT __safecall Append(const System::WideString Name, Winapi::Activex::TOleEnum Type_, NativeInt DefinedSize, Winapi::Activex::TOleEnum Attrib, System::OleVariant FieldValue) = 0 ;
	virtual HRESULT __safecall Update() = 0 ;
	virtual HRESULT __safecall Resync(Winapi::Activex::TOleEnum ResyncValues) = 0 ;
	virtual HRESULT __safecall CancelUpdate() = 0 ;
};

__dispinterface  INTERFACE_UUID("{00000564-0000-0010-8000-00AA006D2EA4}") FieldsDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000054C-0000-0010-8000-00AA006D2EA4}") Field20  : public _ADO 
{
	virtual HRESULT __safecall Get_ActualSize(NativeInt &__Get_ActualSize_result) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int &__Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Get_DefinedSize(NativeInt &__Get_DefinedSize_result) = 0 ;
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_Type_(Winapi::Activex::TOleEnum &__Get_Type__result) = 0 ;
	virtual HRESULT __safecall Get_Value(System::OleVariant &__Get_Value_result) = 0 ;
	virtual HRESULT __safecall Set_Value(System::OleVariant pvar) = 0 ;
	virtual HRESULT __safecall Get_Precision(System::Byte &__Get_Precision_result) = 0 ;
	virtual HRESULT __safecall Get_NumericScale(System::Byte &__Get_NumericScale_result) = 0 ;
	virtual HRESULT __safecall AppendChunk(System::OleVariant Data) = 0 ;
	virtual HRESULT __safecall GetChunk(int Length, System::OleVariant &__GetChunk_result) = 0 ;
	virtual HRESULT __safecall Get_OriginalValue(System::OleVariant &__Get_OriginalValue_result) = 0 ;
	virtual HRESULT __safecall Get_UnderlyingValue(System::OleVariant &__Get_UnderlyingValue_result) = 0 ;
	virtual HRESULT __safecall Get_DataFormat(System::_di_IInterface &__Get_DataFormat_result) = 0 ;
	virtual HRESULT __safecall _Set_DataFormat(const System::_di_IInterface ppiDF) = 0 ;
	virtual HRESULT __safecall Set_Precision(System::Byte pbPrecision) = 0 ;
	virtual HRESULT __safecall Set_NumericScale(System::Byte pbNumericScale) = 0 ;
	virtual HRESULT __safecall Set_Type_(Winapi::Activex::TOleEnum pDataType) = 0 ;
	virtual HRESULT __safecall Set_DefinedSize(NativeInt pl) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int pl) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_ActualSize() { NativeInt __r; HRESULT __hr = Get_ActualSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt ActualSize = {read=_scw_Get_ActualSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes() { int __r; HRESULT __hr = Get_Attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Attributes = {read=_scw_Get_Attributes, write=Set_Attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_DefinedSize() { NativeInt __r; HRESULT __hr = Get_DefinedSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt DefinedSize = {read=_scw_Get_DefinedSize, write=Set_DefinedSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Type_() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Type_ = {read=_scw_Get_Type_, write=Set_Type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Value() { System::OleVariant __r; HRESULT __hr = Get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Value = {read=_scw_Get_Value, write=Set_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_Precision() { System::Byte __r; HRESULT __hr = Get_Precision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Precision = {read=_scw_Get_Precision, write=Set_Precision};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_NumericScale() { System::Byte __r; HRESULT __hr = Get_NumericScale(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte NumericScale = {read=_scw_Get_NumericScale, write=Set_NumericScale};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_OriginalValue() { System::OleVariant __r; HRESULT __hr = Get_OriginalValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant OriginalValue = {read=_scw_Get_OriginalValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_UnderlyingValue() { System::OleVariant __r; HRESULT __hr = Get_UnderlyingValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant UnderlyingValue = {read=_scw_Get_UnderlyingValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get_DataFormat() { System::_di_IInterface __r; HRESULT __hr = Get_DataFormat(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface DataFormat = {read=_scw_Get_DataFormat, write=_Set_DataFormat};
};

__dispinterface  INTERFACE_UUID("{0000054C-0000-0010-8000-00AA006D2EA4}") Field20Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000569-0000-0010-8000-00AA006D2EA4}") Field  : public Field20 
{
	virtual HRESULT __safecall Get_Status(int &__Get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Status() { int __r; HRESULT __hr = Get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_Get_Status};
};

__dispinterface  INTERFACE_UUID("{00000569-0000-0010-8000-00AA006D2EA4}") FieldDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000050C-0000-0010-8000-00AA006D2EA4}") _Parameter  : public _ADO 
{
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Set_Name(const System::WideString pbstr) = 0 ;
	virtual HRESULT __safecall Get_Value(System::OleVariant &__Get_Value_result) = 0 ;
	virtual HRESULT __safecall Set_Value(System::OleVariant pvar) = 0 ;
	virtual HRESULT __safecall Get_Type_(Winapi::Activex::TOleEnum &__Get_Type__result) = 0 ;
	virtual HRESULT __safecall Set_Type_(Winapi::Activex::TOleEnum psDataType) = 0 ;
	virtual HRESULT __safecall Set_Direction(Winapi::Activex::TOleEnum plParmDirection) = 0 ;
	virtual HRESULT __safecall Get_Direction(Winapi::Activex::TOleEnum &__Get_Direction_result) = 0 ;
	virtual HRESULT __safecall Set_Precision(System::Byte pbPrecision) = 0 ;
	virtual HRESULT __safecall Get_Precision(System::Byte &__Get_Precision_result) = 0 ;
	virtual HRESULT __safecall Set_NumericScale(System::Byte pbScale) = 0 ;
	virtual HRESULT __safecall Get_NumericScale(System::Byte &__Get_NumericScale_result) = 0 ;
	virtual HRESULT __safecall Set_Size(NativeInt pl) = 0 ;
	virtual HRESULT __safecall Get_Size(NativeInt &__Get_Size_result) = 0 ;
	virtual HRESULT __safecall AppendChunk(System::OleVariant Val) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int &__Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Set_Attributes(int plParmAttribs) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name, write=Set_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Value() { System::OleVariant __r; HRESULT __hr = Get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Value = {read=_scw_Get_Value, write=Set_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Type_() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Type_ = {read=_scw_Get_Type_, write=Set_Type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Direction() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Direction(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Direction = {read=_scw_Get_Direction, write=Set_Direction};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_Precision() { System::Byte __r; HRESULT __hr = Get_Precision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Precision = {read=_scw_Get_Precision, write=Set_Precision};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_NumericScale() { System::Byte __r; HRESULT __hr = Get_NumericScale(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte NumericScale = {read=_scw_Get_NumericScale, write=Set_NumericScale};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_Size() { NativeInt __r; HRESULT __hr = Get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt Size = {read=_scw_Get_Size, write=Set_Size};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes() { int __r; HRESULT __hr = Get_Attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Attributes = {read=_scw_Get_Attributes, write=Set_Attributes};
};

__dispinterface  INTERFACE_UUID("{0000050C-0000-0010-8000-00AA006D2EA4}") _ParameterDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000050D-0000-0010-8000-00AA006D2EA4}") Parameters  : public _DynaCollection 
{
	
public:
	_di__Parameter operator[](System::OleVariant Index) { return this->Item[Index]; }
	virtual HRESULT __safecall Get_Item(System::OleVariant Index, _di__Parameter &__Get_Item_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di__Parameter _scw_Get_Item(System::OleVariant Index) { _di__Parameter __r; HRESULT __hr = Get_Item(Index, __r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di__Parameter Item[System::OleVariant Index] = {read=_scw_Get_Item/*, default*/};
};

__dispinterface  INTERFACE_UUID("{0000050D-0000-0010-8000-00AA006D2EA4}") ParametersDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{0000054E-0000-0010-8000-00AA006D2EA4}") Command25  : public Command15 
{
	virtual HRESULT __safecall Get_State(int &__Get_State_result) = 0 ;
	virtual HRESULT __safecall Cancel() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_State() { int __r; HRESULT __hr = Get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int State = {read=_scw_Get_State};
};

__dispinterface  INTERFACE_UUID("{0000054E-0000-0010-8000-00AA006D2EA4}") Command25Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{B08400BD-F9D1-4D02-B856-71D5DBA123E9}") _Command  : public Command25 
{
	virtual HRESULT __safecall _Set_CommandStream(const System::_di_IInterface pvStream) = 0 ;
	virtual HRESULT __safecall Get_CommandStream(System::OleVariant &__Get_CommandStream_result) = 0 ;
	virtual HRESULT __safecall Set_Dialect(const System::WideString pbstrDialect) = 0 ;
	virtual HRESULT __safecall Get_Dialect(System::WideString &__Get_Dialect_result) = 0 ;
	virtual HRESULT __safecall Set_NamedParameters(System::WordBool pfNamedParameters) = 0 ;
	virtual HRESULT __safecall Get_NamedParameters(System::WordBool &__Get_NamedParameters_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Dialect() { System::WideString __r; HRESULT __hr = Get_Dialect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Dialect = {read=_scw_Get_Dialect, write=Set_Dialect};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_NamedParameters() { System::WordBool __r; HRESULT __hr = Get_NamedParameters(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool NamedParameters = {read=_scw_Get_NamedParameters, write=Set_NamedParameters};
};

__dispinterface  INTERFACE_UUID("{B08400BD-F9D1-4D02-B856-71D5DBA123E9}") _CommandDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000402-0000-0010-8000-00AA006D2EA4}") ConnectionEventsVt  : public System::IInterface 
{
	virtual HRESULT __safecall InfoMessage(const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall BeginTransComplete(int TransactionLevel, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall CommitTransComplete(const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall RollbackTransComplete(const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall WillExecute(System::WideString &Source, Winapi::Activex::TOleEnum &CursorType, Winapi::Activex::TOleEnum &LockType, int &Options, Winapi::Activex::TOleEnum &adStatus, const _di__Command pCommand, const _di__Recordset pRecordset, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall ExecuteComplete(int RecordsAffected, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Command pCommand, const _di__Recordset pRecordset, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall WillConnect(System::WideString &ConnectionString, System::WideString &UserID, System::WideString &Password, int &Options, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall ConnectComplete(const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
	virtual HRESULT __safecall Disconnect(Winapi::Activex::TOleEnum &adStatus, const _di__Connection pConnection) = 0 ;
};

__interface  INTERFACE_UUID("{00000403-0000-0010-8000-00AA006D2EA4}") RecordsetEventsVt  : public System::IInterface 
{
	virtual HRESULT __safecall WillChangeField(int cFields, System::OleVariant Fields, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall FieldChangeComplete(int cFields, System::OleVariant Fields, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall WillChangeRecord(Winapi::Activex::TOleEnum adReason, int cRecords, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall RecordChangeComplete(Winapi::Activex::TOleEnum adReason, int cRecords, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall WillChangeRecordset(Winapi::Activex::TOleEnum adReason, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall RecordsetChangeComplete(Winapi::Activex::TOleEnum adReason, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall WillMove(Winapi::Activex::TOleEnum adReason, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall MoveComplete(Winapi::Activex::TOleEnum adReason, const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall EndOfRecordset(System::WordBool &fMoreData, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall FetchProgress(int Progress, int MaxProgress, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
	virtual HRESULT __safecall FetchComplete(const _di_Error pError, Winapi::Activex::TOleEnum &adStatus, const _di__Recordset pRecordset) = 0 ;
};

__dispinterface  INTERFACE_UUID("{00000400-0000-0010-8000-00AA006D2EA4}") ConnectionEvents  : public IDispatch 
{
	
};

__dispinterface  INTERFACE_UUID("{00000266-0000-0010-8000-00AA006D2EA4}") RecordsetEvents  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000516-0000-0010-8000-00AA006D2EA4}") ADOConnectionConstruction15  : public System::IInterface 
{
	virtual HRESULT __safecall Get_DSO(System::_di_IInterface &__Get_DSO_result) = 0 ;
	virtual HRESULT __safecall Get_Session(System::_di_IInterface &__Get_Session_result) = 0 ;
	virtual HRESULT __safecall WrapDSOandSession(const System::_di_IInterface pDSO, const System::_di_IInterface pSession) = 0 ;
};

__interface  INTERFACE_UUID("{00000551-0000-0010-8000-00AA006D2EA4}") ADOConnectionConstruction  : public ADOConnectionConstruction15 
{
	
};

__interface  INTERFACE_UUID("{00000562-0000-0010-8000-00AA006D2EA4}") _Record  : public _ADO 
{
	virtual HRESULT __safecall Get_ActiveConnection(System::OleVariant &__Get_ActiveConnection_result) = 0 ;
	virtual HRESULT __safecall Set_ActiveConnection(const System::WideString pvar) = 0 ;
	virtual HRESULT __safecall _Set_ActiveConnection(const _di__Connection pvar) = 0 ;
	virtual HRESULT __safecall Get_State(Winapi::Activex::TOleEnum &__Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_Source(System::OleVariant &__Get_Source_result) = 0 ;
	virtual HRESULT __safecall Set_Source(const System::WideString pvar) = 0 ;
	virtual HRESULT __safecall _Set_Source(const _di_IDispatch pvar) = 0 ;
	virtual HRESULT __safecall Get_Mode(Winapi::Activex::TOleEnum &__Get_Mode_result) = 0 ;
	virtual HRESULT __safecall Set_Mode(Winapi::Activex::TOleEnum pMode) = 0 ;
	virtual HRESULT __safecall Get_ParentURL(System::WideString &__Get_ParentURL_result) = 0 ;
	virtual HRESULT __safecall MoveRecord(const System::WideString Source, const System::WideString Destination, const System::WideString UserName, const System::WideString Password, Winapi::Activex::TOleEnum Options, System::WordBool Async, System::WideString &__MoveRecord_result) = 0 ;
	virtual HRESULT __safecall CopyRecord(const System::WideString Source, const System::WideString Destination, const System::WideString UserName, const System::WideString Password, Winapi::Activex::TOleEnum Options, System::WordBool Async, System::WideString &__CopyRecord_result) = 0 ;
	virtual HRESULT __safecall DeleteRecord(const System::WideString Source, System::WordBool Async) = 0 ;
	virtual HRESULT __safecall Open(System::OleVariant Source, System::OleVariant ActiveConnection, Winapi::Activex::TOleEnum Mode, Winapi::Activex::TOleEnum CreateOptions, Winapi::Activex::TOleEnum Options, const System::WideString UserName, const System::WideString Password) = 0 ;
	virtual HRESULT __safecall Close() = 0 ;
	virtual HRESULT __safecall Get_Fields(_di_Fields &__Get_Fields_result) = 0 ;
	virtual HRESULT __safecall Get_RecordType(Winapi::Activex::TOleEnum &__Get_RecordType_result) = 0 ;
	virtual HRESULT __safecall GetChildren(_di__Recordset &__GetChildren_result) = 0 ;
	virtual HRESULT __safecall Cancel() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_State() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Mode() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Mode = {read=_scw_Get_Mode, write=Set_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_ParentURL() { System::WideString __r; HRESULT __hr = Get_ParentURL(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString ParentURL = {read=_scw_Get_ParentURL};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Fields _scw_Get_Fields() { _di_Fields __r; HRESULT __hr = Get_Fields(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Fields Fields = {read=_scw_Get_Fields};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_RecordType() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_RecordType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum RecordType = {read=_scw_Get_RecordType};
};

__dispinterface  INTERFACE_UUID("{00000562-0000-0010-8000-00AA006D2EA4}") _RecordDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000565-0000-0010-8000-00AA006D2EA4}") _Stream  : public IDispatch 
{
	virtual HRESULT __safecall Get_Size(NativeInt &__Get_Size_result) = 0 ;
	virtual HRESULT __safecall Get_EOS(System::WordBool &__Get_EOS_result) = 0 ;
	virtual HRESULT __safecall Get_Position(NativeInt &__Get_Position_result) = 0 ;
	virtual HRESULT __safecall Set_Position(NativeInt pPos) = 0 ;
	virtual HRESULT __safecall Get_Type_(Winapi::Activex::TOleEnum &__Get_Type__result) = 0 ;
	virtual HRESULT __safecall Set_Type_(Winapi::Activex::TOleEnum ptype) = 0 ;
	virtual HRESULT __safecall Get_LineSeparator(Winapi::Activex::TOleEnum &__Get_LineSeparator_result) = 0 ;
	virtual HRESULT __safecall Set_LineSeparator(Winapi::Activex::TOleEnum pLS) = 0 ;
	virtual HRESULT __safecall Get_State(Winapi::Activex::TOleEnum &__Get_State_result) = 0 ;
	virtual HRESULT __safecall Get_Mode(Winapi::Activex::TOleEnum &__Get_Mode_result) = 0 ;
	virtual HRESULT __safecall Set_Mode(Winapi::Activex::TOleEnum pMode) = 0 ;
	virtual HRESULT __safecall Get_Charset(System::WideString &__Get_Charset_result) = 0 ;
	virtual HRESULT __safecall Set_Charset(const System::WideString pbstrCharset) = 0 ;
	virtual HRESULT __safecall Read(int NumBytes, System::OleVariant &__Read_result) = 0 ;
	virtual HRESULT __safecall Open(System::OleVariant Source, Winapi::Activex::TOleEnum Mode, Winapi::Activex::TOleEnum Options, const System::WideString UserName, const System::WideString Password) = 0 ;
	virtual HRESULT __safecall Close() = 0 ;
	virtual HRESULT __safecall SkipLine() = 0 ;
	virtual HRESULT __safecall Write(System::OleVariant Buffer) = 0 ;
	virtual HRESULT __safecall SetEOS() = 0 ;
	virtual HRESULT __safecall CopyTo(const _di__Stream DestStream, NativeInt CharNumber) = 0 ;
	virtual HRESULT __safecall Flush() = 0 ;
	virtual HRESULT __safecall SaveToFile(const System::WideString FileName, Winapi::Activex::TOleEnum Options) = 0 ;
	virtual HRESULT __safecall LoadFromFile(const System::WideString FileName) = 0 ;
	virtual HRESULT __safecall ReadText(int NumChars, System::WideString &__ReadText_result) = 0 ;
	virtual HRESULT __safecall WriteText(const System::WideString Data, Winapi::Activex::TOleEnum Options) = 0 ;
	virtual HRESULT __safecall Cancel() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_Size() { NativeInt __r; HRESULT __hr = Get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt Size = {read=_scw_Get_Size};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WordBool _scw_Get_EOS() { System::WordBool __r; HRESULT __hr = Get_EOS(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WordBool EOS = {read=_scw_Get_EOS};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_Position() { NativeInt __r; HRESULT __hr = Get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt Position = {read=_scw_Get_Position, write=Set_Position};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Type_() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Type_ = {read=_scw_Get_Type_, write=Set_Type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_LineSeparator() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_LineSeparator(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum LineSeparator = {read=_scw_Get_LineSeparator, write=Set_LineSeparator};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_State() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum State = {read=_scw_Get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Mode() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Mode = {read=_scw_Get_Mode, write=Set_Mode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Charset() { System::WideString __r; HRESULT __hr = Get_Charset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Charset = {read=_scw_Get_Charset, write=Set_Charset};
};

__dispinterface  INTERFACE_UUID("{00000565-0000-0010-8000-00AA006D2EA4}") _StreamDisp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{00000567-0000-0010-8000-00AA006D2EA4}") ADORecordConstruction  : public IDispatch 
{
	virtual HRESULT __stdcall Get_Row(/* out */ System::_di_IInterface &ppRow) = 0 ;
	virtual HRESULT __stdcall Set_Row(const System::_di_IInterface ppRow) = 0 ;
	virtual HRESULT __stdcall Set_ParentRow(const System::_di_IInterface Param1) = 0 ;
};

__interface  INTERFACE_UUID("{00000568-0000-0010-8000-00AA006D2EA4}") ADOStreamConstruction  : public IDispatch 
{
	virtual HRESULT __stdcall Get_Stream(/* out */ System::_di_IInterface &ppStm) = 0 ;
	virtual HRESULT __stdcall Set_Stream(const System::_di_IInterface ppStm) = 0 ;
};

__interface  INTERFACE_UUID("{00000517-0000-0010-8000-00AA006D2EA4}") ADOCommandConstruction  : public System::IInterface 
{
	virtual HRESULT __safecall Get_OLEDBCommand(System::_di_IInterface &__Get_OLEDBCommand_result) = 0 ;
	virtual HRESULT __safecall Set_OLEDBCommand(const System::_di_IInterface ppOLEDBCommand) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get_OLEDBCommand() { System::_di_IInterface __r; HRESULT __hr = Get_OLEDBCommand(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface OLEDBCommand = {read=_scw_Get_OLEDBCommand, write=Set_OLEDBCommand};
};

__interface  INTERFACE_UUID("{00000283-0000-0010-8000-00AA006D2EA4}") ADORecordsetConstruction  : public IDispatch 
{
	virtual HRESULT __safecall Get_Rowset(System::_di_IInterface &__Get_Rowset_result) = 0 ;
	virtual HRESULT __safecall Set_Rowset(const System::_di_IInterface ppRowset) = 0 ;
	virtual HRESULT __safecall Get_Chapter(NativeInt &__Get_Chapter_result) = 0 ;
	virtual HRESULT __safecall Set_Chapter(NativeInt plChapter) = 0 ;
	virtual HRESULT __safecall Get_RowPosition(System::_di_IInterface &__Get_RowPosition_result) = 0 ;
	virtual HRESULT __safecall Set_RowPosition(const System::_di_IInterface ppRowPos) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get_Rowset() { System::_di_IInterface __r; HRESULT __hr = Get_Rowset(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface Rowset = {read=_scw_Get_Rowset, write=Set_Rowset};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_Chapter() { NativeInt __r; HRESULT __hr = Get_Chapter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt Chapter = {read=_scw_Get_Chapter, write=Set_Chapter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::_di_IInterface _scw_Get_RowPosition() { System::_di_IInterface __r; HRESULT __hr = Get_RowPosition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::_di_IInterface RowPosition = {read=_scw_Get_RowPosition, write=Set_RowPosition};
};

__interface  INTERFACE_UUID("{00000505-0000-0010-8000-00AA006D2EA4}") Field15  : public _ADO 
{
	virtual HRESULT __safecall Get_ActualSize(NativeInt &__Get_ActualSize_result) = 0 ;
	virtual HRESULT __safecall Get_Attributes(int &__Get_Attributes_result) = 0 ;
	virtual HRESULT __safecall Get_DefinedSize(NativeInt &__Get_DefinedSize_result) = 0 ;
	virtual HRESULT __safecall Get_Name(System::WideString &__Get_Name_result) = 0 ;
	virtual HRESULT __safecall Get_Type_(Winapi::Activex::TOleEnum &__Get_Type__result) = 0 ;
	virtual HRESULT __safecall Get_Value(System::OleVariant &__Get_Value_result) = 0 ;
	virtual HRESULT __safecall Set_Value(System::OleVariant pvar) = 0 ;
	virtual HRESULT __safecall Get_Precision(System::Byte &__Get_Precision_result) = 0 ;
	virtual HRESULT __safecall Get_NumericScale(System::Byte &__Get_NumericScale_result) = 0 ;
	virtual HRESULT __safecall AppendChunk(System::OleVariant Data) = 0 ;
	virtual HRESULT __safecall GetChunk(int Length, System::OleVariant &__GetChunk_result) = 0 ;
	virtual HRESULT __safecall Get_OriginalValue(System::OleVariant &__Get_OriginalValue_result) = 0 ;
	virtual HRESULT __safecall Get_UnderlyingValue(System::OleVariant &__Get_UnderlyingValue_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_ActualSize() { NativeInt __r; HRESULT __hr = Get_ActualSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt ActualSize = {read=_scw_Get_ActualSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_Attributes() { int __r; HRESULT __hr = Get_Attributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Attributes = {read=_scw_Get_Attributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline NativeInt _scw_Get_DefinedSize() { NativeInt __r; HRESULT __hr = Get_DefinedSize(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property NativeInt DefinedSize = {read=_scw_Get_DefinedSize};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::WideString _scw_Get_Name() { System::WideString __r; HRESULT __hr = Get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::WideString Name = {read=_scw_Get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Activex::TOleEnum _scw_Get_Type_() { Winapi::Activex::TOleEnum __r; HRESULT __hr = Get_Type_(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Activex::TOleEnum Type_ = {read=_scw_Get_Type_};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_Value() { System::OleVariant __r; HRESULT __hr = Get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant Value = {read=_scw_Get_Value, write=Set_Value};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_Precision() { System::Byte __r; HRESULT __hr = Get_Precision(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte Precision = {read=_scw_Get_Precision};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Byte _scw_Get_NumericScale() { System::Byte __r; HRESULT __hr = Get_NumericScale(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Byte NumericScale = {read=_scw_Get_NumericScale};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_OriginalValue() { System::OleVariant __r; HRESULT __hr = Get_OriginalValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant OriginalValue = {read=_scw_Get_OriginalValue};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::OleVariant _scw_Get_UnderlyingValue() { System::OleVariant __r; HRESULT __hr = Get_UnderlyingValue(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::OleVariant UnderlyingValue = {read=_scw_Get_UnderlyingValue};
};

__dispinterface  INTERFACE_UUID("{00000505-0000-0010-8000-00AA006D2EA4}") Field15Disp  : public IDispatch 
{
	
};

__interface  INTERFACE_UUID("{BD96C556-65A3-11D0-983A-00C04FC29E34}") IDataspace  : public IDispatch 
{
	virtual HRESULT __safecall CreateObject(const System::WideString bstrProgid, const System::WideString bstrConnection, System::OleVariant &__CreateObject_result) = 0 ;
	virtual HRESULT __safecall Get_InternetTimeout(int &__Get_InternetTimeout_result) = 0 ;
	virtual HRESULT __safecall Set_InternetTimeout(int plInetTimeout) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_Get_InternetTimeout() { int __r; HRESULT __hr = Get_InternetTimeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InternetTimeout = {read=_scw_Get_InternetTimeout, write=Set_InternetTimeout};
};

__dispinterface  INTERFACE_UUID("{BD96C556-65A3-11D0-983A-00C04FC29E34}") IDataspaceDisp  : public IDispatch 
{
	
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoConnection : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Connection __fastcall Create();
	__classmethod _di__Connection __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoConnection() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoConnection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoRecord_ : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Record __fastcall Create();
	__classmethod _di__Record __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoRecord_() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoRecord_() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoStream : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Stream __fastcall Create();
	__classmethod _di__Stream __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoStream() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoStream() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoCommand : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Command __fastcall Create();
	__classmethod _di__Command __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoCommand() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoCommand() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoRecordset : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Recordset __fastcall Create();
	__classmethod _di__Recordset __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoRecordset() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoRecordset() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION CoParameter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod _di__Parameter __fastcall Create();
	__classmethod _di__Parameter __fastcall CreateRemote(const System::UnicodeString MachineName);
public:
	/* TObject.Create */ inline __fastcall CoParameter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~CoParameter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 ADODBMajorVersion = System::Int8(0x2);
static const System::Int8 ADODBMinorVersion = System::Int8(0x8);
extern DELPHI_PACKAGE GUID LIBID_ADODB;
extern DELPHI_PACKAGE GUID IID__Collection;
extern DELPHI_PACKAGE GUID IID__DynaCollection;
extern DELPHI_PACKAGE GUID IID__ADO;
extern DELPHI_PACKAGE GUID IID_Properties;
extern DELPHI_PACKAGE GUID IID_Property_;
extern DELPHI_PACKAGE GUID IID_Error;
extern DELPHI_PACKAGE GUID IID_Errors;
extern DELPHI_PACKAGE GUID IID_Command15;
extern DELPHI_PACKAGE GUID IID_Connection15;
extern DELPHI_PACKAGE GUID IID__Connection;
extern DELPHI_PACKAGE GUID IID_Recordset15;
extern DELPHI_PACKAGE GUID IID_Recordset20;
extern DELPHI_PACKAGE GUID IID_Recordset21;
extern DELPHI_PACKAGE GUID IID__Recordset;
extern DELPHI_PACKAGE GUID IID_Fields15;
extern DELPHI_PACKAGE GUID IID_Fields20;
extern DELPHI_PACKAGE GUID IID_Fields;
extern DELPHI_PACKAGE GUID IID_Field20;
extern DELPHI_PACKAGE GUID IID_Field;
extern DELPHI_PACKAGE GUID IID__Parameter;
extern DELPHI_PACKAGE GUID IID_Parameters;
extern DELPHI_PACKAGE GUID IID_Command25;
extern DELPHI_PACKAGE GUID IID__Command;
extern DELPHI_PACKAGE GUID IID_ConnectionEventsVt;
extern DELPHI_PACKAGE GUID IID_RecordsetEventsVt;
extern DELPHI_PACKAGE GUID DIID_ConnectionEvents;
extern DELPHI_PACKAGE GUID DIID_RecordsetEvents;
extern DELPHI_PACKAGE GUID IID_ADOConnectionConstruction15;
extern DELPHI_PACKAGE GUID IID_ADOConnectionConstruction;
extern DELPHI_PACKAGE GUID CLASS_Connection;
extern DELPHI_PACKAGE GUID IID__Record;
extern DELPHI_PACKAGE GUID CLASS_Record_;
extern DELPHI_PACKAGE GUID IID__Stream;
extern DELPHI_PACKAGE GUID CLASS_Stream;
extern DELPHI_PACKAGE GUID IID_ADORecordConstruction;
extern DELPHI_PACKAGE GUID IID_ADOStreamConstruction;
extern DELPHI_PACKAGE GUID IID_ADOCommandConstruction;
extern DELPHI_PACKAGE GUID CLASS_Command;
extern DELPHI_PACKAGE GUID CLASS_Recordset;
extern DELPHI_PACKAGE GUID IID_ADORecordsetConstruction;
extern DELPHI_PACKAGE GUID IID_Field15;
extern DELPHI_PACKAGE GUID CLASS_Parameter;
extern DELPHI_PACKAGE GUID CLASS_DataSpace;
extern DELPHI_PACKAGE GUID CLASS_DataFactory;
extern DELPHI_PACKAGE GUID IID_IDataspace;
#define CT_USERID L"USER ID="
#define CT_PROVIDER L"PROVIDER="
#define CT_FILENAME L"FILE NAME="
}	/* namespace Adoint */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_ADOINT)
using namespace Winapi::Adoint;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_AdointHPP
