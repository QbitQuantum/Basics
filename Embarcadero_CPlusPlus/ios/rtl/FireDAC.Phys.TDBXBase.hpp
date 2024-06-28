// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.TDBXBase.pas' rev: 34.00 (iOS)

#ifndef Firedac_Phys_TdbxbaseHPP
#define Firedac_Phys_TdbxbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBCommonTypes.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Tdbxbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ETDBXNativeException;
class DELPHICLASS TFDPhysTDBXBaseDriverLink;
class DELPHICLASS TFDPhysTDBXLib;
class DELPHICLASS TFDPhysTDBXDriverBase;
class DELPHICLASS TFDPhysTDBXConnectionBase;
class DELPHICLASS TFDPhysTDBXTransaction;
class DELPHICLASS TFDPhysTDBXCommand;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION ETDBXNativeException : public Firedac::Stan::Error::EFDDBEngineException
{
	typedef Firedac::Stan::Error::EFDDBEngineException inherited;
	
public:
	__fastcall ETDBXNativeException(Data::Dbxcommon::TDBXError* ADBXError, const System::UnicodeString ADriverName)/* overload */;
public:
	/* EFDDBEngineException.Create */ inline __fastcall virtual ETDBXNativeException()/* overload */ : Firedac::Stan::Error::EFDDBEngineException() { }
	/* EFDDBEngineException.Create */ inline __fastcall ETDBXNativeException(int AADCode, const System::UnicodeString AMessage)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(AADCode, AMessage) { }
	/* EFDDBEngineException.Destroy */ inline __fastcall virtual ~ETDBXNativeException() { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall ETDBXNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETDBXNativeException(NativeUInt Ident)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETDBXNativeException(System::PResStringRec ResStringRec)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETDBXNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETDBXNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETDBXNativeException(const System::UnicodeString Msg, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETDBXNativeException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Firedac::Stan::Error::EFDDBEngineException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETDBXNativeException(NativeUInt Ident, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETDBXNativeException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETDBXNativeException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETDBXNativeException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Firedac::Stan::Error::EFDDBEngineException(Ident, Args, Args_High, AHelpContext) { }
	
};


class PASCALIMPLEMENTATION TFDPhysTDBXBaseDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysTDBXBaseDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysTDBXBaseDriverLink() { }
	
};


class PASCALIMPLEMENTATION TFDPhysTDBXLib : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TObject* FOwningObj;
	System::Syncobjs::TCriticalSection* FLock;
	TFDPhysTDBXConnectionBase* FCurrentConnection;
	__classmethod System::UnicodeString __fastcall GetRegistryFile(const System::UnicodeString Setting, const System::UnicodeString Default);
	void __fastcall DoError(Data::Dbxcommon::TDBXError* ADBXError);
	
public:
	__fastcall TFDPhysTDBXLib(System::TObject* AOwningObj);
	__fastcall virtual ~TFDPhysTDBXLib();
	__property System::TObject* OwningObj = {read=FOwningObj};
};


class PASCALIMPLEMENTATION TFDPhysTDBXDriverBase : public Firedac::Phys::TFDPhysDriver
{
	typedef Firedac::Phys::TFDPhysDriver inherited;
	
private:
	System::UnicodeString FCfgFile;
	TFDPhysTDBXLib* FLib;
	
protected:
	virtual void __fastcall InternalLoad();
	virtual void __fastcall InternalUnload();
	virtual void * __fastcall GetCliObj();
	virtual Firedac::Dats::TFDDatSTable* __fastcall GetConnParams(System::Classes::TStrings* AKeys, Firedac::Dats::TFDDatSTable* AParams);
	
public:
	__fastcall virtual TFDPhysTDBXDriverBase(Firedac::Phys::TFDPhysManager* AManager, const Firedac::Stan::Intf::_di_IFDStanDefinition ADriverDef);
	__fastcall virtual ~TFDPhysTDBXDriverBase();
	__property System::UnicodeString CfgFile = {read=FCfgFile};
	__property TFDPhysTDBXLib* Lib = {read=FLib};
};


class PASCALIMPLEMENTATION TFDPhysTDBXConnectionBase : public Firedac::Phys::TFDPhysConnection
{
	typedef Firedac::Phys::TFDPhysConnection inherited;
	
private:
	Data::Dbxcommon::TDBXConnection* FDbxConnection;
	Firedac::Stan::Intf::TFDRDBMSKind FRdbmsKind;
	TFDPhysTDBXCommand* FCurrentCommand;
	bool FDBX4;
	Firedac::Stan::Util::TFDEncoder* FEncoder;
	Data::Dbcommontypes::CBRType __fastcall DoTrace(const Data::Dbxcommon::TDBXTraceInfo &TraceInfo);
	void __fastcall GetConnInterfaces();
	void __fastcall SetConnParams();
	void __fastcall DoError(Data::Dbxcommon::TDBXError* ADBXError);
	bool __fastcall GetIsDS();
	TFDPhysTDBXDriverBase* __fastcall GetTDBXDriver();
	
protected:
	System::UnicodeString FDriverName;
	virtual void __fastcall InternalConnect();
	virtual void __fastcall InternalDisconnect();
	virtual Firedac::Phys::TFDPhysCommand* __fastcall InternalCreateCommand();
	virtual Firedac::Phys::TFDPhysTransaction* __fastcall InternalCreateTransaction();
	virtual void __fastcall InternalTracingChanged();
	virtual void __fastcall InternalExecuteDirect(const System::UnicodeString ASQL, Firedac::Phys::TFDPhysTransaction* ATransaction);
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual int __fastcall GetItemCount();
	virtual void * __fastcall GetCliObj();
	virtual void * __fastcall InternalGetCliHandle();
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKindFromAlias();
	System::UnicodeString __fastcall GetKeywords();
	virtual void __fastcall CheckDBXDriver();
	virtual void __fastcall BuildDBXConnParams(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef, Data::Dbxcommon::TDBXProperties* AConnProps);
	
public:
	__fastcall virtual TFDPhysTDBXConnectionBase(Firedac::Phys::TFDPhysDriver* ADriverObj, Firedac::Phys::TFDPhysConnectionHost* AConnHost);
	__fastcall virtual ~TFDPhysTDBXConnectionBase();
	__property Data::Dbxcommon::TDBXConnection* DbxConnection = {read=FDbxConnection};
	__property System::UnicodeString DriverName = {read=FDriverName};
	__property bool IsDS = {read=GetIsDS, nodefault};
	__property TFDPhysTDBXDriverBase* TDBXDriver = {read=GetTDBXDriver};
};


class PASCALIMPLEMENTATION TFDPhysTDBXTransaction : public Firedac::Phys::TFDPhysTransaction
{
	typedef Firedac::Phys::TFDPhysTransaction inherited;
	
private:
	Firedac::Stan::Intf::TFDStringList* FTransactions;
	int __fastcall GetIsolationLevel();
	TFDPhysTDBXConnectionBase* __fastcall GetTDBXConn();
	
protected:
	virtual void __fastcall InternalStartTransaction(unsigned long AID);
	virtual void __fastcall InternalCommit(unsigned long AID);
	virtual void __fastcall InternalRollback(unsigned long AID);
	
public:
	__fastcall virtual TFDPhysTDBXTransaction(Firedac::Phys::TFDPhysConnection* AConnection);
	__fastcall virtual ~TFDPhysTDBXTransaction();
	__property TFDPhysTDBXConnectionBase* TDBXConn = {read=GetTDBXConn};
};


class PASCALIMPLEMENTATION TFDPhysTDBXCommand : public Firedac::Phys::TFDPhysCommand
{
	typedef Firedac::Phys::TFDPhysCommand inherited;
	
	
private:
	typedef System::DynamicArray<System::Word> _TFDPhysTDBXCommand__1;
	
	
private:
	Data::Dbxcommon::TDBXCommand* FDBXCommand;
	Data::Dbxcommon::TDBXReader* FDBXReader;
	System::Classes::TList* FReadersList;
	System::Word FColumnIndex;
	_TFDPhysTDBXCommand__1 FParamChildPos;
	bool FMetaForPackage;
	void __fastcall FetchRow(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow);
	void __fastcall GetParamValues(Firedac::Stan::Param::TFDParams* AParams, bool AGetDataSets);
	void __fastcall SetParamValues(Firedac::Stan::Param::TFDParams* AParams, int AValueIndex);
	void __fastcall CalcUnits(Firedac::Stan::Param::TFDParams* const AParams, const int AIndex, System::Word *AChildPos, const int AChildPos_High, int &ASubItems);
	void __fastcall OpenMetaInfo();
	bool __fastcall FetchMetaRow(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, int ARowIndex);
	void __fastcall Dbx2ADColInfo(int ADbxType, int ADbxSubType, int ADbxPrec, short ADbxScale, Firedac::Stan::Intf::TFDDataType &AType, Firedac::Stan::Intf::TFDDataAttributes &AAtrs, unsigned long &ALen, int &APrec, int &AScale);
	TFDPhysTDBXConnectionBase* __fastcall GetTDBXConn();
	void __fastcall AddCursor(Data::Dbxcommon::TDBXReader* AReader);
	void __fastcall DeleteCursor(Data::Dbxcommon::TDBXReader* AReader);
	
protected:
	virtual void __fastcall InternalClose();
	virtual void __fastcall InternalExecute(int ATimes, int AOffset, __int64 &ACount);
	virtual unsigned long __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned long ARowsetSize);
	virtual bool __fastcall InternalOpen(__int64 &ACount);
	virtual bool __fastcall InternalNextRecordSet();
	virtual void __fastcall InternalPrepare();
	virtual bool __fastcall InternalColInfoStart(Firedac::Phys::TFDPhysDataTableInfo &ATabInfo);
	virtual bool __fastcall InternalColInfoGet(Firedac::Phys::TFDPhysDataColumnInfo &AColInfo);
	virtual void __fastcall InternalUnprepare();
	virtual void * __fastcall GetCliObj();
	
public:
	__fastcall TFDPhysTDBXCommand(Firedac::Phys::TFDPhysConnection* AConnectionObj);
	__fastcall virtual ~TFDPhysTDBXCommand();
	__property TFDPhysTDBXConnectionBase* TDBXConn = {read=GetTDBXConn};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Tdbxbase */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_TDBXBASE)
using namespace Firedac::Phys::Tdbxbase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_TdbxbaseHPP
