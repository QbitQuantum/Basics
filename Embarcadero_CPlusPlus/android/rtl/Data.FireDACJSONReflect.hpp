// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.FireDACJSONReflect.pas' rev: 34.00 (Android)

#ifndef Data_FiredacjsonreflectHPP
#define Data_FiredacjsonreflectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.Client.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Firedacjsonreflect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDJSONInterceptor;
class DELPHICLASS TFDJSONDataSetsBase;
class DELPHICLASS TFDJSONDataSets;
class DELPHICLASS TFDJSONDeltas;
__interface DELPHIINTERFACE IFDJSONDataSetsWriter;
typedef System::DelphiInterface<IFDJSONDataSetsWriter> _di_IFDJSONDataSetsWriter;
__interface DELPHIINTERFACE IFDJSONDeltasWriter;
typedef System::DelphiInterface<IFDJSONDeltasWriter> _di_IFDJSONDeltasWriter;
__interface DELPHIINTERFACE IFDJSONDataSetsReader;
typedef System::DelphiInterface<IFDJSONDataSetsReader> _di_IFDJSONDataSetsReader;
__interface DELPHIINTERFACE IFDJSONDeltasReader;
typedef System::DelphiInterface<IFDJSONDeltasReader> _di_IFDJSONDeltasReader;
__interface DELPHIINTERFACE IFDJSONDeltasApplyUpdates;
typedef System::DelphiInterface<IFDJSONDeltasApplyUpdates> _di_IFDJSONDeltasApplyUpdates;
__interface DELPHIINTERFACE IFDJSONDeltasApplyUpdatesMax;
typedef System::DelphiInterface<IFDJSONDeltasApplyUpdatesMax> _di_IFDJSONDeltasApplyUpdatesMax;
class DELPHICLASS TFDJSONDataSetsWriterBase;
class DELPHICLASS TFDJSONDataSetsReaderBase;
class DELPHICLASS TFDJSONDataSetsWriter;
class DELPHICLASS TFDJSONDataSetsReader;
class DELPHICLASS TFDJSONDeltasWriter;
class DELPHICLASS TFDJSONDeltasReader;
class DELPHICLASS TFDJSONDeltasApplyUpdates;
class DELPHICLASS TFDJSONDeltasApplyUpdatesMax;
class DELPHICLASS TFDJSONErrors;
class DELPHICLASS EFDDataListError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONInterceptor : public Data::Dbxjsonreflect::TJSONInterceptor
{
	typedef Data::Dbxjsonreflect::TJSONInterceptor inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> TItemPair;
	
	typedef System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* TItemList;
	
	
private:
	System::Generics::Collections::TObjectList__1<System::TObject*>* FFreeObjects;
	
public:
	static bool __fastcall ItemListToJSONObject(System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* const AList, System::Json::TJSONObject* const AJSONObject);
	static bool __fastcall DataSetsToJSONObject(TFDJSONDataSetsBase* const ADataSets, System::Json::TJSONObject* const AJSONObject);
	static bool __fastcall JSONObjectToItemList(System::Json::TJSONObject* const AJSONObject, System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* const AList);
	static bool __fastcall JSONObjectToDataSets(System::Json::TJSONObject* const AJSONObject, TFDJSONDataSetsBase* const ADataSets);
	__fastcall virtual ~TFDJSONInterceptor();
	virtual System::TObject* __fastcall TypeObjectConverter(System::TObject* AData);
	virtual System::TObject* __fastcall TypeObjectReverter(System::TObject* AData);
public:
	/* TObject.Create */ inline __fastcall TFDJSONInterceptor() : Data::Dbxjsonreflect::TJSONInterceptor() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSetsBase : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TItemList;
	class PASCALIMPLEMENTATION TItemList : public System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >
	{
		typedef System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> > inherited;
		
	public:
		/* {System_Generics_Collections}TList<System_Generics_Collections_TPair<System_string,FireDAC_Comp_Client_TFDAdaptedDataSet>>.Create */ inline __fastcall TItemList()/* overload */ : System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >() { }
		/* {System_Generics_Collections}TList<System_Generics_Collections_TPair<System_string,FireDAC_Comp_Client_TFDAdaptedDataSet>>.Create */ inline __fastcall TItemList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> > > AComparer)/* overload */ : System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >(AComparer) { }
		/* {System_Generics_Collections}TList<System_Generics_Collections_TPair<System_string,FireDAC_Comp_Client_TFDAdaptedDataSet>>.Create */ inline __fastcall TItemList(System::Generics::Collections::TEnumerable__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* const Collection)/* overload */ : System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >(Collection) { }
		/* {System_Generics_Collections}TList<System_Generics_Collections_TPair<System_string,FireDAC_Comp_Client_TFDAdaptedDataSet>>.Destroy */ inline __fastcall virtual ~TItemList() { }
		
	};
	
	
	
private:
	TItemList* FDataSets;
	bool FOwnsDataSets;
	
public:
	__fastcall TFDJSONDataSetsBase();
	__fastcall virtual ~TFDJSONDataSetsBase();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSets : /*[[sealed]]*/ public TFDJSONDataSetsBase
{
	typedef TFDJSONDataSetsBase inherited;
	
public:
	/* TFDJSONDataSetsBase.Create */ inline __fastcall TFDJSONDataSets() : TFDJSONDataSetsBase() { }
	/* TFDJSONDataSetsBase.Destroy */ inline __fastcall virtual ~TFDJSONDataSets() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDeltas : /*[[sealed]]*/ public TFDJSONDataSetsBase
{
	typedef TFDJSONDataSetsBase inherited;
	
public:
	/* TFDJSONDataSetsBase.Create */ inline __fastcall TFDJSONDeltas() : TFDJSONDataSetsBase() { }
	/* TFDJSONDataSetsBase.Destroy */ inline __fastcall virtual ~TFDJSONDeltas() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1DD9F6B1-D841-4475-98B6-5AA985D05DFC}") IFDJSONDataSetsWriter  : public System::IInterface 
{
	virtual void __fastcall Add(const System::UnicodeString AName, Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet) = 0 /* overload */;
	virtual void __fastcall Add(Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet) = 0 /* overload */;
	virtual TFDJSONDataSets* __fastcall GetDataSetList() = 0 ;
	__property TFDJSONDataSets* DataSetList = {read=GetDataSetList};
};

__interface  INTERFACE_UUID("{2C9646B0-DCFC-43A3-838D-1E9592095D71}") IFDJSONDeltasWriter  : public System::IInterface 
{
	virtual void __fastcall Add(const System::UnicodeString AName, Firedac::Comp::Client::TFDMemTable* const AFDMemTable) = 0 /* overload */;
	virtual void __fastcall Add(Firedac::Comp::Client::TFDMemTable* const AFDMemTable) = 0 /* overload */;
	virtual TFDJSONDeltas* __fastcall GetDeltaList() = 0 ;
	__property TFDJSONDeltas* DeltaList = {read=GetDeltaList};
};

__interface  INTERFACE_UUID("{00C69185-9E6C-4FEA-A8F8-2344972B4C68}") IFDJSONDataSetsReader  : public System::IInterface 
{
	virtual TFDJSONDataSets* __fastcall GetDataSetList() = 0 ;
	__property TFDJSONDataSets* DataSetList = {read=GetDataSetList};
	virtual int __fastcall GetCount() = 0 ;
	virtual Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetValue(int I) = 0 ;
	virtual Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetValueByName(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetKey(int I) = 0 ;
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall GetItem(int I) = 0 ;
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall ExtractItem(int I) = 0 ;
	__property int Count = {read=GetCount};
	__property Firedac::Comp::Client::TFDAdaptedDataSet* Values[int I] = {read=GetValue};
	__property System::UnicodeString Keys[int I] = {read=GetKey};
	__property System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> Items[int I] = {read=GetItem};
	__property Firedac::Comp::Client::TFDAdaptedDataSet* ValueByName[const System::UnicodeString AName] = {read=GetValueByName};
};

__interface  INTERFACE_UUID("{45073B83-F37A-40C9-9749-56C96F7B7EEA}") IFDJSONDeltasReader  : public System::IInterface 
{
	virtual TFDJSONDeltas* __fastcall GetDeltaList() = 0 ;
	__property TFDJSONDeltas* DeltaList = {read=GetDeltaList};
	virtual int __fastcall GetCount() = 0 ;
	virtual Firedac::Comp::Client::TFDMemTable* __fastcall GetValue(int I) = 0 ;
	virtual Firedac::Comp::Client::TFDMemTable* __fastcall GetValueByName(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetKey(int I) = 0 ;
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall GetItem(int I) = 0 ;
	virtual System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall ExtractItem(int I) = 0 ;
	__property int Count = {read=GetCount};
	__property Firedac::Comp::Client::TFDMemTable* Values[int I] = {read=GetValue};
	__property System::UnicodeString Keys[int I] = {read=GetKey};
	__property System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> Items[int I] = {read=GetItem};
	__property Firedac::Comp::Client::TFDMemTable* ValueByName[const System::UnicodeString AName] = {read=GetValueByName};
};

__interface  INTERFACE_UUID("{58213D3C-BFE8-4BE3-8197-4236FFC215C8}") IFDJSONDeltasApplyUpdates  : public IFDJSONDeltasReader 
{
	virtual int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter) = 0 /* overload */;
	virtual TFDJSONErrors* __fastcall GetErrors() = 0 ;
	__property TFDJSONErrors* Errors = {read=GetErrors};
};

__interface  INTERFACE_UUID("{58213D3C-BFE8-4BE3-8197-4236FFC215C8}") IFDJSONDeltasApplyUpdatesMax  : public IFDJSONDeltasReader 
{
	virtual int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff) = 0 /* overload */;
	virtual int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff) = 0 /* overload */;
	virtual TFDJSONErrors* __fastcall GetErrors() = 0 ;
	__property TFDJSONErrors* Errors = {read=GetErrors};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSetsWriterBase : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
protected:
	virtual __classmethod void __fastcall CreateList(TFDJSONDataSetsBase* const ADataList) = 0 ;
	__classmethod System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* __fastcall GetPairList(TFDJSONDataSetsBase* const AList);
	template<typename T> __classmethod void __fastcall ListAddT(TFDJSONDataSetsBase* const ADataList, const System::UnicodeString AName, const T ADataSet)/* overload */;
	template<typename T> __classmethod void __fastcall ListAddT(TFDJSONDataSetsBase* const ADataList, const T ADataSet)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TFDJSONDataSetsWriterBase() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDataSetsWriterBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSetsReaderBase : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	__classmethod System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> >* __fastcall GetPairList(TFDJSONDataSetsBase* const AList);
	
protected:
	__classmethod int __fastcall GetListCountT(TFDJSONDataSetsBase* const ADataList);
	template<typename T> __classmethod T __fastcall GetListValueT(TFDJSONDataSetsBase* const ADataList, int I);
	template<typename T> __classmethod T __fastcall GetListValueByNameT(TFDJSONDataSetsBase* const ADataList, const System::UnicodeString AName);
	template<typename T> __classmethod System::UnicodeString __fastcall GetListKeyT(TFDJSONDataSetsBase* const ADataList, int I);
	template<typename T> __classmethod System::Generics::Collections::TPair__2<System::UnicodeString,T> __fastcall GetListItemT(TFDJSONDataSetsBase* const ADataList, int I);
	template<typename T> __classmethod System::Generics::Collections::TPair__2<System::UnicodeString,T> __fastcall ExtractListItemT(TFDJSONDataSetsBase* const ADataList, int I);
public:
	/* TObject.Create */ inline __fastcall TFDJSONDataSetsReaderBase() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDataSetsReaderBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSetsWriter : public TFDJSONDataSetsWriterBase
{
	typedef TFDJSONDataSetsWriterBase inherited;
	
private:
	TFDJSONDataSets* FDataSetList;
	
protected:
	__classmethod virtual void __fastcall CreateList(TFDJSONDataSetsBase* const ADataList);
	TFDJSONDataSetsBase* __fastcall GetList();
	void __fastcall Add(const System::UnicodeString AName, Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet)/* overload */;
	void __fastcall Add(Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet)/* overload */;
	TFDJSONDataSets* __fastcall GetDataSetList();
	
public:
	__classmethod void __fastcall ListAdd(TFDJSONDataSets* const ADataList, const System::UnicodeString AName, Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet)/* overload */;
	__classmethod void __fastcall ListAdd(TFDJSONDataSets* const ADataList, Firedac::Comp::Client::TFDAdaptedDataSet* const ADataSet)/* overload */;
	__fastcall TFDJSONDataSetsWriter(TFDJSONDataSets* const ADataSetList);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDataSetsWriter() { }
	
private:
	void *__IFDJSONDataSetsWriter;	// IFDJSONDataSetsWriter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1DD9F6B1-D841-4475-98B6-5AA985D05DFC}
	operator _di_IFDJSONDataSetsWriter()
	{
		_di_IFDJSONDataSetsWriter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDataSetsWriter*(void) { return (IFDJSONDataSetsWriter*)&__IFDJSONDataSetsWriter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDataSetsReader : public TFDJSONDataSetsReaderBase
{
	typedef TFDJSONDataSetsReaderBase inherited;
	
	
private:
	TFDJSONDataSets* FDataSetList;
	
protected:
	static _di_IFDJSONDataSetsReader __fastcall GetListReader(TFDJSONDataSets* const ADataList);
	int __fastcall GetCount();
	Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetValue(int I);
	Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetValueByName(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetKey(int I);
	System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall GetItem(int I);
	System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall ExtractItem(int I)/* overload */;
	TFDJSONDataSets* __fastcall GetDataSetList();
	
public:
	static int __fastcall GetListCount(TFDJSONDataSets* const ADataList);
	static Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetListValue(TFDJSONDataSets* const ADataList, int I);
	static Firedac::Comp::Client::TFDAdaptedDataSet* __fastcall GetListValueByName(TFDJSONDataSets* const ADataList, const System::UnicodeString AName);
	static System::UnicodeString __fastcall GetListKey(TFDJSONDataSets* const ADataList, int I);
	static System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall GetListItem(TFDJSONDataSets* const ADataList, int I);
	static System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDAdaptedDataSet*> __fastcall ExtractListItem(TFDJSONDataSets* const ADataList, int I);
	__fastcall virtual TFDJSONDataSetsReader(TFDJSONDataSets* const ADataSetList);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDataSetsReader() { }
	
private:
	void *__IFDJSONDataSetsReader;	// IFDJSONDataSetsReader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00C69185-9E6C-4FEA-A8F8-2344972B4C68}
	operator _di_IFDJSONDataSetsReader()
	{
		_di_IFDJSONDataSetsReader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDataSetsReader*(void) { return (IFDJSONDataSetsReader*)&__IFDJSONDataSetsReader; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDeltasWriter : public TFDJSONDataSetsWriterBase
{
	typedef TFDJSONDataSetsWriterBase inherited;
	
private:
	TFDJSONDeltas* FDeltaList;
	
protected:
	__classmethod virtual void __fastcall CreateList(TFDJSONDataSetsBase* const ADataList);
	Firedac::Comp::Client::TFDMemTable* __fastcall CreateDelta(Firedac::Comp::Client::TFDMemTable* const AFDMemTable);
	void __fastcall Add(const System::UnicodeString AName, Firedac::Comp::Client::TFDMemTable* const AFDMemTable)/* overload */;
	void __fastcall Add(Firedac::Comp::Client::TFDMemTable* const AFDMemTable)/* overload */;
	TFDJSONDeltas* __fastcall GetDeltaList();
	
public:
	static void __fastcall ListAdd(TFDJSONDeltas* const ADeltaList, const System::UnicodeString AName, Firedac::Comp::Client::TFDMemTable* const AFDMemTable)/* overload */;
	static void __fastcall ListAdd(TFDJSONDeltas* const ADeltaList, Firedac::Comp::Client::TFDMemTable* const AFDMemTable)/* overload */;
	__fastcall virtual TFDJSONDeltasWriter(TFDJSONDeltas* const ADeltaList);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDeltasWriter() { }
	
private:
	void *__IFDJSONDeltasWriter;	// IFDJSONDeltasWriter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2C9646B0-DCFC-43A3-838D-1E9592095D71}
	operator _di_IFDJSONDeltasWriter()
	{
		_di_IFDJSONDeltasWriter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDeltasWriter*(void) { return (IFDJSONDeltasWriter*)&__IFDJSONDeltasWriter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDeltasReader : public TFDJSONDataSetsReaderBase
{
	typedef TFDJSONDataSetsReaderBase inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> TItemPair;
	
	
private:
	TFDJSONDeltas* FDeltaList;
	
protected:
	TFDJSONDeltas* __fastcall GetDeltaList();
	int __fastcall GetCount();
	Firedac::Comp::Client::TFDMemTable* __fastcall GetValue(int I);
	Firedac::Comp::Client::TFDMemTable* __fastcall GetValueByName(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetKey(int I);
	System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall GetItem(int I);
	System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall ExtractItem(int I);
	
public:
	static int __fastcall GetListCount(TFDJSONDeltas* const ADataList);
	static Firedac::Comp::Client::TFDMemTable* __fastcall GetListValue(TFDJSONDeltas* const ADataList, int I);
	static Firedac::Comp::Client::TFDMemTable* __fastcall GetListValueByName(TFDJSONDeltas* const ADataList, const System::UnicodeString AName);
	static System::UnicodeString __fastcall GetListKey(TFDJSONDeltas* const ADataList, int I);
	static System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall GetListItem(TFDJSONDeltas* const ADataList, int I);
	static System::Generics::Collections::TPair__2<System::UnicodeString,Firedac::Comp::Client::TFDMemTable*> __fastcall ExtractListItem(TFDJSONDeltas* const ADataList, int I);
	__fastcall virtual TFDJSONDeltasReader(TFDJSONDeltas* const ADeltaList);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDJSONDeltasReader() { }
	
private:
	void *__IFDJSONDeltasReader;	// IFDJSONDeltasReader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {45073B83-F37A-40C9-9749-56C96F7B7EEA}
	operator _di_IFDJSONDeltasReader()
	{
		_di_IFDJSONDeltasReader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDeltasReader*(void) { return (IFDJSONDeltasReader*)&__IFDJSONDeltasReader; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDeltasApplyUpdates : public TFDJSONDeltasReader
{
	typedef TFDJSONDeltasReader inherited;
	
private:
	TFDJSONErrors* FErrors;
	
protected:
	__classmethod int __fastcall ApplyUpdates(Firedac::Comp::Client::TFDMemTable* const ADelta, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, TFDJSONErrors* const AErrors)/* overload */;
	__classmethod int __fastcall ApplyUpdates(Firedac::Comp::Client::TFDMemTable* const ADelta, Firedac::Comp::Client::TFDCustomCommand* const ACommand, TFDJSONErrors* const AErrors)/* overload */;
	int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand)/* overload */;
	int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand)/* overload */;
	int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter)/* overload */;
	int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter)/* overload */;
	TFDJSONErrors* __fastcall GetErrors();
	
public:
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	__fastcall virtual TFDJSONDeltasApplyUpdates(TFDJSONDeltas* const ADeltaList);
	__fastcall virtual ~TFDJSONDeltasApplyUpdates();
private:
	void *__IFDJSONDeltasApplyUpdates;	// IFDJSONDeltasApplyUpdates 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {58213D3C-BFE8-4BE3-8197-4236FFC215C8}
	operator _di_IFDJSONDeltasApplyUpdates()
	{
		_di_IFDJSONDeltasApplyUpdates intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDeltasApplyUpdates*(void) { return (IFDJSONDeltasApplyUpdates*)&__IFDJSONDeltasApplyUpdates; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONDeltasApplyUpdatesMax : public TFDJSONDeltasReader
{
	typedef TFDJSONDeltasReader inherited;
	
private:
	TFDJSONErrors* FErrors;
	
protected:
	__classmethod int __fastcall ApplyUpdates(Firedac::Comp::Client::TFDMemTable* const ADelta, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors, TFDJSONErrors* const AErrors)/* overload */;
	__classmethod int __fastcall ApplyUpdates(Firedac::Comp::Client::TFDMemTable* const ADelta, Firedac::Comp::Client::TFDCustomCommand* const ACommand, int AMaxErrors, TFDJSONErrors* const AErrors)/* overload */;
	int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff)/* overload */;
	int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff)/* overload */;
	int __fastcall ApplyUpdates(const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff)/* overload */;
	int __fastcall ApplyUpdates(const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff)/* overload */;
	TFDJSONErrors* __fastcall GetErrors();
	
public:
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const System::UnicodeString AKey, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const int Index, Firedac::Comp::Client::TFDCustomCommand* const ASelectCommand, int AMaxErrors = 0xffffffff, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const System::UnicodeString AKey, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	static int __fastcall ListApplyUpdates(TFDJSONDeltas* const ADeltaList, const int Index, Firedac::Comp::Client::TFDTableAdapter* const AAdapter, int AMaxErrors = 0xffffffff, TFDJSONErrors* const AErrors = (TFDJSONErrors*)(0x0))/* overload */;
	__fastcall virtual TFDJSONDeltasApplyUpdatesMax(TFDJSONDeltas* const ADeltaList);
	__fastcall virtual ~TFDJSONDeltasApplyUpdatesMax();
private:
	void *__IFDJSONDeltasApplyUpdatesMax;	// IFDJSONDeltasApplyUpdatesMax 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {58213D3C-BFE8-4BE3-8197-4236FFC215C8}
	operator _di_IFDJSONDeltasApplyUpdatesMax()
	{
		_di_IFDJSONDeltasApplyUpdatesMax intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IFDJSONDeltasApplyUpdatesMax*(void) { return (IFDJSONDeltasApplyUpdatesMax*)&__IFDJSONDeltasApplyUpdatesMax; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDJSONErrors : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStrings* FErrors;
	int __fastcall GetCount();
	
public:
	__fastcall TFDJSONErrors();
	__fastcall virtual ~TFDJSONErrors();
	virtual void __fastcall DoBeforeApplyUpdates(Firedac::Comp::Client::TFDMemTable* ASender);
	virtual void __fastcall DoAfterApplyUpdates(Firedac::Comp::Client::TFDMemTable* ASender);
	virtual void __fastcall UpdateError(Data::Db::TDataSet* ASender, Firedac::Stan::Error::EFDException* AException, Firedac::Dats::TFDDatSRow* ARow, Firedac::Stan::Option::TFDUpdateRequest ARequest, Firedac::Stan::Intf::TFDErrorAction &AAction);
	void __fastcall Clear();
	__property System::Classes::TStrings* Strings = {read=FErrors};
	__property int Count = {read=GetCount, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EFDDataListError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EFDDataListError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EFDDataListError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EFDDataListError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EFDDataListError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EFDDataListError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EFDDataListError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EFDDataListError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EFDDataListError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EFDDataListError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EFDDataListError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EFDDataListError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EFDDataListError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EFDDataListError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Firedacjsonreflect */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_FIREDACJSONREFLECT)
using namespace Data::Firedacjsonreflect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_FiredacjsonreflectHPP
