// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.pas' rev: 34.00 (Android)

#ifndef Firedac_PhysHPP
#define Firedac_PhysHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.SyncObjs.hpp>
#include <Data.DB.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.Stan.Param.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Stan.Error.hpp>
#include <FireDAC.Stan.Factory.hpp>
#include <FireDAC.DatS.hpp>
#include <FireDAC.Phys.Intf.hpp>
#include <FireDAC.Phys.SQLGenerator.hpp>
#include <FireDAC.UI.Intf.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Phys
{
  _INIT_UNIT(Firedac_Phys);
}	/* namespace Phys */
}	/* namespace Firedac */

namespace Firedac
{
namespace Phys
{
//-- forward type declarations -----------------------------------------------
struct TFDPhysCliHandles;
class DELPHICLASS TFDPhysManager;
class DELPHICLASS TFDPhysDriver;
class DELPHICLASS TFDPhysDriverLink;
class DELPHICLASS TFDPhysDriverService;
class DELPHICLASS TFDPhysConnectionHost;
class DELPHICLASS TFDPhysConnection;
class DELPHICLASS TFDPhysTransaction;
class DELPHICLASS TFDPhysEventThread;
class DELPHICLASS TFDPhysEventMessage;
class DELPHICLASS TFDPhysEventStartMessage;
class DELPHICLASS TFDPhysEventStopMessage;
class DELPHICLASS TFDPhysEventAlerter;
struct TFDPhysDataTableInfo;
struct TFDPhysDataColumnInfo;
class DELPHICLASS TFDPhysCommand;
//-- type declarations -------------------------------------------------------
_DECLARE_METACLASS(System::TMetaClass, TFDPhysDriverClass);

_DECLARE_METACLASS(System::TMetaClass, TFDPhysConnectionClass);

struct DECLSPEC_DRECORD TFDPhysCliHandles
{
public:
	void *FDriverCliHandles;
#ifndef __aarch64__
	unsigned FTxSerialID;
#else /* __aarch64__ */
	unsigned long FTxSerialID;
#endif /* __aarch64__ */
	System::StaticArray<System::WideChar, 11> FDriverID;
};


typedef TFDPhysCliHandles *PFDPhysCliHandles;

enum DECLSPEC_DENUM TFDPhysFindObjMode : unsigned int { fomNone, fomMBActive, fomMBNotInactive, fomIfActive };

enum DECLSPEC_DENUM Firedac_Phys__1 : unsigned int { rfInRecovery, rfEmergencyClose };

typedef System::Set<Firedac_Phys__1, Firedac_Phys__1::rfInRecovery, Firedac_Phys__1::rfEmergencyClose> TFDPhysRecoveryFlags;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysManager : public Firedac::Stan::Factory::TFDObject
{
	typedef Firedac::Stan::Factory::TFDObject inherited;
	
private:
	System::Syncobjs::TCriticalSection* FLock;
	Firedac::Stan::Intf::_di_IFDStanDefinitions FDriverDefs;
	Firedac::Stan::Intf::TFDStringList* FDriverIDs;
	Firedac::Stan::Intf::TFDStringList* FRDBMSNames;
	System::Classes::TList* FDriverClasses;
	System::Classes::TList* FDriverList;
	System::Classes::TList* FDriverLinkList;
	Firedac::Phys::Intf::TFDPhysManagerState FState;
	Firedac::Stan::Intf::_di_IFDStanConnectionDefs FConnectionDefs;
	bool FUpdateDriverIDs;
	void __fastcall CheckActive();
	void __fastcall CheckActiveOrStoping();
	void __fastcall CleanupDrivers();
	void __fastcall CleanupManager();
	TFDPhysDriverClass __fastcall FindDriverClass(const System::UnicodeString ADriverID);
	TFDPhysDriver* __fastcall DriverByID(const System::UnicodeString ADriverID, TFDPhysFindObjMode AMode, bool ARequired);
	void __fastcall InternalClose(bool ATerminate, bool AWaitForClose);
	void __fastcall Shutdown();
	void __fastcall ErrorDriverNotReg(const System::UnicodeString ADriverID, const System::UnicodeString ABaseDriverID);
	void __fastcall UpdateDriverIDs();
	void __fastcall CheckUpdateDriverIDs();
	
protected:
	Firedac::Stan::Option::_di_IFDStanOptions FOptions;
	HIDESBASE int __stdcall _Release();
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID IID, /* out */ void *Obj);
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	__property Firedac::Stan::Option::_di_IFDStanOptions Options = {read=FOptions};
	void __fastcall CreateDriver(const System::UnicodeString ADriverID, /* out */ Firedac::Phys::Intf::_di_IFDPhysDriver &ADrv, bool AIntfRequired = true);
	void __fastcall CreateConnection(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef, /* out */ Firedac::Phys::Intf::_di_IFDPhysConnection &AConn, bool AIntfRequired = true)/* overload */;
	void __fastcall CreateConnection(const System::UnicodeString AConDefName, /* out */ Firedac::Phys::Intf::_di_IFDPhysConnection &AConn, bool AIntfRequired = true)/* overload */;
	void __fastcall CreateMetadata(/* out */ Firedac::Phys::Intf::_di_IFDPhysManagerMetadata &AMeta);
	void __fastcall CreateDefaultConnectionMetadata(/* out */ Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata &AConMeta);
	void __fastcall Open();
	void __fastcall Close(bool AWait = false);
	void __fastcall CloseConnectionDef(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	void __fastcall RefreshMetadataCache();
	System::UnicodeString __fastcall DriverIDFromSharedCliHandle(void * ASharedCliHandle);
	void __fastcall RegisterRDBMSKind(Firedac::Stan::Intf::TFDRDBMSKind AKind, const System::UnicodeString AName);
	void __fastcall RegisterDriverClass(System::TClass ADriverClass);
	void __fastcall UnregisterDriverClass(System::TClass ADriverClass);
	Firedac::Stan::Intf::_di_IFDStanDefinitions __fastcall GetDriverDefs();
	Firedac::Stan::Intf::_di_IFDStanConnectionDefs __fastcall GetConnectionDefs();
	Firedac::Stan::Option::_di_IFDStanOptions __fastcall GetOptions();
	Firedac::Phys::Intf::TFDPhysManagerState __fastcall GetState();
	int __fastcall GetDriverCount();
	System::UnicodeString __fastcall GetDriverID(int AIndex);
	System::UnicodeString __fastcall GetBaseDriverID(int AIndex)/* overload */;
	System::UnicodeString __fastcall GetBaseDriverID(const System::UnicodeString ADriverID)/* overload */;
	System::TClass __fastcall GetBaseDriverClass(const System::UnicodeString ADriverID);
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind(const System::UnicodeString ADriverID);
	System::UnicodeString __fastcall GetRDBMSName(Firedac::Stan::Intf::TFDRDBMSKind AKind);
	void __fastcall GetRDBMSNames(System::Classes::TStrings* ANames);
	void __fastcall CreateDriverMetadata(const System::UnicodeString ADriverID, /* out */ Firedac::Phys::Intf::_di_IFDPhysDriverMetadata &AMeta);
	
public:
	virtual void __fastcall Initialize();
	__fastcall virtual ~TFDPhysManager();
	TFDPhysDriverLink* __fastcall FindDriverLink(const System::UnicodeString ADriverID);
public:
	/* TFDObject.Create */ inline __fastcall virtual TFDPhysManager() : Firedac::Stan::Factory::TFDObject() { }
	
private:
	void *__IFDPhysManagerMetadata;	// Firedac::Phys::Intf::IFDPhysManagerMetadata 
	void *__IFDPhysManager;	// Firedac::Phys::Intf::IFDPhysManager 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2100}
	operator Firedac::Phys::Intf::_di_IFDPhysManagerMetadata()
	{
		Firedac::Phys::Intf::_di_IFDPhysManagerMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysManagerMetadata*(void) { return (Firedac::Phys::Intf::IFDPhysManagerMetadata*)&__IFDPhysManagerMetadata; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2101}
	operator Firedac::Phys::Intf::_di_IFDPhysManager()
	{
		Firedac::Phys::Intf::_di_IFDPhysManager intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysManager*(void) { return (Firedac::Phys::Intf::IFDPhysManager*)&__IFDPhysManager; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2018}
	operator Firedac::Stan::Option::_di_IFDStanOptions() { return Options; }
	#else
	operator Firedac::Stan::Option::IFDStanOptions*(void) { return (Firedac::Stan::Option::IFDStanOptions*)Options; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IFDPhysManagerMetadata; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysDriver : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Syncobjs::TCriticalSection* FLock;
	System::UnicodeString FDriverID;
	Firedac::Stan::Intf::_di_IFDStanDefinition FParams;
	Firedac::Phys::Intf::TFDPhysDriverState FState;
	TFDPhysManager* FManager;
	System::Classes::TList* FConnHostList;
	System::Classes::TList* FConnectionList;
	Firedac::Stan::Util::TFDLog* FMessages;
	int FUsageCount;
	void __fastcall Stop();
	void __fastcall Shutdown();
	TFDPhysConnectionHost* __fastcall FindConnectionHost(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	
protected:
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	System::UnicodeString __fastcall GetDriverID();
	System::UnicodeString __fastcall GetBaseDrvID();
	Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetDbKind();
	virtual void * __fastcall GetCliObj();
	System::Classes::TStrings* __fastcall GetMessages();
	void __fastcall Load();
	void __fastcall Unload();
	void __fastcall Employ();
	void __fastcall Vacate();
	void __fastcall CreateConnection(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef, /* out */ Firedac::Phys::Intf::_di_IFDPhysConnection &AConn);
	void __fastcall CloseConnectionDef(const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	void __fastcall CreateMetadata(/* out */ Firedac::Phys::Intf::_di_IFDPhysDriverMetadata &ADrvMeta);
	void __fastcall CreateConnectionWizard(/* out */ Firedac::Phys::Intf::_di_IFDPhysDriverConnectionWizard &AWizard);
	int __fastcall GetConnectionCount();
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnections(int AIndex);
	Firedac::Phys::Intf::TFDPhysDriverState __fastcall GetState();
	virtual Firedac::Dats::TFDDatSTable* __fastcall GetConnParams(System::Classes::TStrings* AKeys, Firedac::Dats::TFDDatSTable* AParams);
	System::UnicodeString __fastcall GetBaseDrvDesc();
	__classmethod virtual System::UnicodeString __fastcall GetBaseDriverID();
	__classmethod virtual System::UnicodeString __fastcall GetBaseDriverDesc();
	__classmethod virtual Firedac::Stan::Intf::TFDRDBMSKind __fastcall GetRDBMSKind();
	__classmethod virtual Firedac::Stan::Intf::TFDConnectionDefParamsClass __fastcall GetConnectionDefParamsClass();
	virtual void __fastcall InternalLoad() = 0 ;
	virtual void __fastcall InternalUnload() = 0 ;
	virtual TFDPhysConnection* __fastcall InternalCreateConnection(TFDPhysConnectionHost* AConnHost) = 0 ;
	void __fastcall GetVendorParams(/* out */ System::UnicodeString &AHome, /* out */ System::UnicodeString &ALib);
	
public:
	__fastcall virtual TFDPhysDriver(TFDPhysManager* AManager, const Firedac::Stan::Intf::_di_IFDStanDefinition ADriverDef);
	__fastcall virtual ~TFDPhysDriver();
	__property System::UnicodeString DriverID = {read=FDriverID};
	__property System::UnicodeString BaseDriverID = {read=GetBaseDrvID};
	__property Firedac::Stan::Intf::TFDRDBMSKind RDBMSKind = {read=GetDbKind, nodefault};
	__property Firedac::Phys::Intf::TFDPhysDriverState State = {read=FState, nodefault};
	__property TFDPhysManager* Manager = {read=FManager};
	__property Firedac::Stan::Intf::_di_IFDStanDefinition Params = {read=FParams};
	__property Firedac::Stan::Util::TFDLog* Messages = {read=FMessages};
private:
	void *__IFDPhysDriverMetadata;	// Firedac::Phys::Intf::IFDPhysDriverMetadata 
	void *__IFDPhysDriver;	// Firedac::Phys::Intf::IFDPhysDriver 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2102}
	operator Firedac::Phys::Intf::_di_IFDPhysDriverMetadata()
	{
		Firedac::Phys::Intf::_di_IFDPhysDriverMetadata intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysDriverMetadata*(void) { return (Firedac::Phys::Intf::IFDPhysDriverMetadata*)&__IFDPhysDriverMetadata; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2103}
	operator Firedac::Phys::Intf::_di_IFDPhysDriver()
	{
		Firedac::Phys::Intf::_di_IFDPhysDriver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysDriver*(void) { return (Firedac::Phys::Intf::IFDPhysDriver*)&__IFDPhysDriver; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysDriverLink : public Firedac::Stan::Intf::TFDComponent
{
	typedef Firedac::Stan::Intf::TFDComponent inherited;
	
private:
	System::UnicodeString FDriverID;
	System::UnicodeString FVendorHome;
	System::UnicodeString FVendorLib;
	System::Classes::TNotifyEvent FOnDriverDestroying;
	System::Classes::TNotifyEvent FOnDriverCreated;
	System::Classes::TList* FServiceList;
	void __fastcall SetDriverID(const System::UnicodeString AValue);
	Firedac::Phys::Intf::_di_IFDPhysDriver __fastcall GetDriverIntf();
	Firedac::Phys::Intf::TFDPhysDriverState __fastcall GetDriverState();
	TFDPhysDriverService* __fastcall GetServices(int AIndex);
	int __fastcall GetServicesCount();
	void __fastcall SetupDef(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	void __fastcall SetUpdateDriverIDs();
	
protected:
	virtual System::UnicodeString __fastcall GetActualDriverID();
	virtual System::UnicodeString __fastcall GetBaseDriverID();
	virtual bool __fastcall IsConfigured();
	virtual void __fastcall ApplyTo(const Firedac::Stan::Intf::_di_IFDStanDefinition AParams);
	virtual void __fastcall DoDriverCreated();
	virtual void __fastcall DoDriverDestroying();
	
public:
	__fastcall virtual TFDPhysDriverLink(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDPhysDriverLink();
	void __fastcall Release();
	__property Firedac::Phys::Intf::TFDPhysDriverState DriverState = {read=GetDriverState, nodefault};
	__property Firedac::Phys::Intf::_di_IFDPhysDriver DriverIntf = {read=GetDriverIntf};
	__property System::UnicodeString ActualDriverID = {read=GetActualDriverID};
	__property int ServicesCount = {read=GetServicesCount, nodefault};
	__property TFDPhysDriverService* Services[int AIndex] = {read=GetServices};
	
__published:
	__property System::UnicodeString BaseDriverID = {read=GetBaseDriverID};
	__property System::UnicodeString DriverID = {read=FDriverID, write=SetDriverID};
	__property System::UnicodeString VendorHome = {read=FVendorHome, write=FVendorHome};
	__property System::UnicodeString VendorLib = {read=FVendorLib, write=FVendorLib};
	__property System::Classes::TNotifyEvent OnDriverCreated = {read=FOnDriverCreated, write=FOnDriverCreated};
	__property System::Classes::TNotifyEvent OnDriverDestroying = {read=FOnDriverDestroying, write=FOnDriverDestroying};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TFDPhysServiceProgressEvent)(TFDPhysDriverService* ASender, const System::UnicodeString AMessage);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysDriverService : public Firedac::Stan::Intf::TFDComponent
{
	typedef Firedac::Stan::Intf::TFDComponent inherited;
	
private:
	TFDPhysDriverLink* FDriverLink;
	bool FActive;
	Firedac::Stan::Error::TFDErrorEvent FOnError;
	bool FStreamingActive;
	System::Classes::TNotifyEvent FBeforeExecute;
	System::Classes::TNotifyEvent FAfterExecute;
	void __fastcall SetActive(const bool AValue);
	void __fastcall SetDriverLink(TFDPhysDriverLink* const AValue);
	System::TObject* __fastcall GetCliObj();
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Loaded();
	virtual bool __fastcall GetActualActive();
	virtual void __fastcall CheckActive(bool AAutoActivate, bool ANeedActivation);
	virtual void __fastcall InternalUninstall();
	virtual void __fastcall InternalInstall();
	virtual void __fastcall InternalExecute();
	virtual void __fastcall DoBeforeExecute();
	virtual void __fastcall DoAfterExecute();
	void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	__property TFDPhysDriverLink* DriverLink = {read=FDriverLink, write=SetDriverLink};
	__property bool ActualActive = {read=GetActualActive, nodefault};
	__property bool Active = {read=FActive, write=SetActive, default=0};
	void __fastcall Execute();
	
public:
	__fastcall virtual ~TFDPhysDriverService();
	__property System::TObject* CliObj = {read=GetCliObj};
	
__published:
	__property Firedac::Stan::Error::TFDErrorEvent OnError = {read=FOnError, write=FOnError};
	__property System::Classes::TNotifyEvent BeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property System::Classes::TNotifyEvent AfterExecute = {read=FAfterExecute, write=FAfterExecute};
public:
	/* TComponent.Create */ inline __fastcall virtual TFDPhysDriverService(System::Classes::TComponent* AOwner) : Firedac::Stan::Intf::TFDComponent(AOwner) { }
	
private:
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysConnectionHost : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TFDPhysDriver* FDriverObj;
	Firedac::Stan::Intf::_di_IFDStanConnectionDef FConnectionDef;
	int FConnectionCount;
	Firedac::Stan::Intf::_di_IFDStanObjectFactory FPool;
#ifndef __aarch64__
	unsigned FPassCode;
#else /* __aarch64__ */
	unsigned long FPassCode;
#endif /* __aarch64__ */
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	bool FInitialTracing;
	void __fastcall AddMoniClient();
	void __fastcall Employ();
	void __fastcall Vacate();
	
protected:
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	System::Classes::TComponentName __fastcall GetObjectKindName();
	void __fastcall CreateObject(/* out */ Firedac::Stan::Intf::_di_IFDStanObject &AObject);
	
public:
	__fastcall TFDPhysConnectionHost(TFDPhysDriver* ADriver, const Firedac::Stan::Intf::_di_IFDStanConnectionDef AConnectionDef);
	__fastcall virtual ~TFDPhysConnectionHost();
	void __fastcall CreateConnection(/* out */ Firedac::Phys::Intf::_di_IFDPhysConnection &AConn);
	__property Firedac::Stan::Intf::_di_IFDStanConnectionDef ConnectionDef = {read=FConnectionDef};
private:
	void *__IFDStanObjectHost;	// Firedac::Stan::Intf::IFDStanObjectHost 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2002}
	operator Firedac::Stan::Intf::_di_IFDStanObjectHost()
	{
		Firedac::Stan::Intf::_di_IFDStanObjectHost intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObjectHost*(void) { return (Firedac::Stan::Intf::IFDStanObjectHost*)&__IFDStanObjectHost; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IFDStanObjectHost; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TFDPhysConnection : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Firedac::Phys::Intf::_di_IFDPhysDriver FDriver;
	TFDPhysDriver* FDriverObj;
	TFDPhysConnectionHost* FConnHost;
	System::Syncobjs::TCriticalSection* FLock;
	Firedac::Stan::Intf::_di_IFDStanErrorHandler FErrorHandler;
	Firedac::Phys::Intf::_di_IFDPhysConnectionRecoveryHandler FRecoveryHandler;
	System::TObject* FMetadata;
	Firedac::Ui::Intf::_di_IFDGUIxLoginDialog FLogin;
	bool FLoginPrompt;
	int FPreparedCommands;
	Firedac::Stan::Intf::_di_IFDStanConnectionDef FInternalConnectionDef;
	bool FPoolManaged;
	Firedac::Stan::Intf::TFDMoniAdapterHelper* FMoniAdapterHelper;
	TFDPhysCliHandles *FSharedHandle;
	Firedac::Phys::Intf::_di_IFDPhysTransaction FTransaction;
	TFDPhysTransaction* FTransactionObj;
	TFDPhysRecoveryFlags FRecoveryFlags;
	TFDPhysCliHandles FCliHandles;
	void __fastcall UpdateMonitor();
	void __fastcall CheckInactive();
	void __fastcall CheckActive(bool ADisconnectingAllowed = false);
	void __fastcall IncPrepared(TFDPhysCommand* ACommand);
	void __fastcall DecPrepared();
	void __fastcall ConnectBase();
	void __fastcall DoConnect();
	void __fastcall DoLogin();
	void __fastcall CheckTransaction();
	void __fastcall AllocTransactionHandles();
	void __fastcall ReleaseTransactionHandles();
	void __fastcall DisconnectTransactions();
	void __fastcall DisconnectCommands();
	System::UnicodeString __fastcall GetDriverID();
	void __fastcall DisconnectEvents();
	void __fastcall RecoverConnection(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, bool AOnLogin);
	
public:
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	
protected:
	Firedac::Stan::Option::_di_IFDStanOptions FOptions;
	Firedac::Stan::Intf::_di_IFDMoniClient FMonitor;
	bool FTracing;
#ifndef __aarch64__
	unsigned __fastcall GetHandle();
#else /* __aarch64__ */
	unsigned long __fastcall GetHandle();
#endif /* __aarch64__ */
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual Firedac::Stan::Intf::TFDMoniAdapterItemKinds __fastcall GetSupportItems();
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	__property Firedac::Stan::Option::_di_IFDStanOptions Options = {read=FOptions};
	void __fastcall GetParentOptions(Firedac::Stan::Option::_di_IFDStanOptions &AOpts);
	void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	Firedac::Phys::Intf::_di_IFDPhysDriver __fastcall GetDriver();
	Firedac::Phys::Intf::TFDPhysConnectionState __fastcall GetState();
	Firedac::Stan::Option::_di_IFDStanOptions __fastcall GetOptions();
	int __fastcall GetCommandCount();
	Firedac::Phys::Intf::_di_IFDPhysCommand __fastcall GetCommands(int AIndex);
	Firedac::Stan::Intf::_di_IFDStanErrorHandler __fastcall GetErrorHandler();
	Firedac::Phys::Intf::_di_IFDPhysConnectionRecoveryHandler __fastcall GetRecoveryHandler();
	Firedac::Ui::Intf::_di_IFDGUIxLoginDialog __fastcall GetLogin();
	bool __fastcall GetLoginPrompt();
	Firedac::Stan::Intf::_di_IFDStanConnectionDef __fastcall GetConnectionDef();
	virtual Firedac::Stan::Error::EFDDBEngineException* __fastcall GetMessages();
	virtual void * __fastcall GetCliObj();
	void * __fastcall GetCliHandle();
	void * __fastcall GetSharedCliHandle();
	Firedac::Phys::Intf::_di_IFDPhysTransaction __fastcall GetTransaction();
	int __fastcall GetTransactionCount();
	Firedac::Phys::Intf::_di_IFDPhysTransaction __fastcall GetTransactions(int AIndex);
	System::UnicodeString __fastcall GetCurrentCatalog();
	System::UnicodeString __fastcall GetCurrentSchema();
	int __fastcall GetEventCount();
	Firedac::Phys::Intf::_di_IFDPhysEventAlerter __fastcall GetEvents(int AIndex);
	void __fastcall SetOptions(const Firedac::Stan::Option::_di_IFDStanOptions AValue);
	void __fastcall SetErrorHandler(const Firedac::Stan::Intf::_di_IFDStanErrorHandler AValue);
	void __fastcall SetRecoveryHandler(const Firedac::Phys::Intf::_di_IFDPhysConnectionRecoveryHandler AValue);
	void __fastcall SetLogin(const Firedac::Ui::Intf::_di_IFDGUIxLoginDialog AValue);
	void __fastcall SetLoginPrompt(const bool AValue);
	void __fastcall SetSharedCliHandle(void * AValue);
	void __fastcall SetTransaction(const Firedac::Phys::Intf::_di_IFDPhysTransaction AValue);
	void __fastcall SetCurrentCatalog(const System::UnicodeString AValue);
	void __fastcall SetCurrentSchema(const System::UnicodeString AValue);
	void __fastcall CreateMetadata(/* out */ Firedac::Phys::Intf::_di_IFDPhysConnectionMetadata &AConnMeta);
	void __fastcall CreateCommandGenerator(/* out */ Firedac::Phys::Intf::_di_IFDPhysCommandGenerator &AGen, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	void __fastcall CreateCommand(/* out */ Firedac::Phys::Intf::_di_IFDPhysCommand &ACmd);
	void __fastcall CreateMetaInfoCommand(/* out */ Firedac::Phys::Intf::_di_IFDPhysMetaInfoCommand &AMetaCmd);
	void __fastcall CreateTransaction(/* out */ Firedac::Phys::Intf::_di_IFDPhysTransaction &ATx);
	void __fastcall CreateEvent(const System::UnicodeString AEventKind, /* out */ Firedac::Phys::Intf::_di_IFDPhysEventAlerter &AEvent);
	void __fastcall Open();
	void __fastcall Close();
	void __fastcall ForceDisconnect();
	bool __fastcall Ping();
	void __fastcall ChangePassword(const System::UnicodeString ANewPassword);
	virtual System::Variant __fastcall GetLastAutoGenValue(const System::UnicodeString AName = System::UnicodeString());
	void __fastcall SaveLastAutoGenValue(const System::Variant &AValue);
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall Clone();
	virtual void __fastcall AnalyzeSession(System::Classes::TStrings* AMessages);
	void __fastcall TracingChanged();
	bool __fastcall GetTracing();
	void __fastcall SetTracing(bool AValue);
	Firedac::Stan::Intf::_di_IFDMoniClient __fastcall GetMonitor();
	void __fastcall TraceList(System::Classes::TStrings* AList, const System::UnicodeString AName);
	void __fastcall TraceConnInfo(Firedac::Stan::Intf::TFDMoniAdapterItemKind AKind, const System::UnicodeString AName);
	virtual void __fastcall InternalConnect() = 0 ;
	virtual void __fastcall InternalSetMeta();
	virtual void __fastcall InternalDisconnect() = 0 ;
	virtual void __fastcall InternalPing();
	virtual System::TObject* __fastcall InternalCreateMetadata() = 0 ;
	virtual TFDPhysTransaction* __fastcall InternalCreateTransaction() = 0 ;
	virtual TFDPhysEventAlerter* __fastcall InternalCreateEvent(const System::UnicodeString AEventKind);
	virtual TFDPhysCommand* __fastcall InternalCreateCommand() = 0 ;
	virtual TFDPhysCommand* __fastcall InternalCreateMetaInfoCommand();
	virtual Firedac::Phys::Sqlgenerator::TFDPhysCommandGenerator* __fastcall InternalCreateCommandGenerator(const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand) = 0 ;
	virtual void __fastcall InternalChangePassword(const System::UnicodeString AUserName, const System::UnicodeString AOldPassword, const System::UnicodeString ANewPassword);
	virtual void __fastcall InternalTracingChanged();
	virtual void __fastcall InternalOverrideNameByCommand(Firedac::Phys::Intf::TFDPhysParsedName &AParsedName, const Firedac::Phys::Intf::_di_IFDPhysCommand ACommand);
	virtual void __fastcall InternalExecuteDirect(const System::UnicodeString ASQL, TFDPhysTransaction* ATransaction) = 0 ;
	virtual System::UnicodeString __fastcall InternalGetCurrentCatalog();
	virtual System::UnicodeString __fastcall InternalGetCurrentSchema();
	virtual void * __fastcall InternalGetCliHandle();
	virtual void * __fastcall InternalGetSharedCliHandle();
	virtual void __fastcall InternalAnalyzeSession(System::Classes::TStrings* AMessages);
	Firedac::Phys::Intf::TFDPhysConnectionState FState;
	System::Classes::TList* FCommandList;
	System::Classes::TList* FTransactionList;
	System::Classes::TList* FEventList;
	System::UnicodeString FDefaultSchema;
	System::UnicodeString FDefaultCatalog;
	System::UnicodeString FCurrentCatalog;
	System::UnicodeString FCurrentSchema;
	Firedac::Phys::Intf::TFDPhysNameParts FAvoidImplicitMeta;
	Firedac::Phys::Intf::TFDPhysNameParts FRemoveDefaultMeta;
	System::Variant FLastAutoGenValue;
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	
public:
	__fastcall virtual TFDPhysConnection(TFDPhysDriver* ADriverObj, TFDPhysConnectionHost* AConnHost);
	__fastcall virtual ~TFDPhysConnection();
	void __fastcall Lock();
	void __fastcall Unlock();
	__property TFDPhysDriver* DriverObj = {read=FDriverObj};
	__property TFDPhysTransaction* TransactionObj = {read=FTransactionObj};
	__property Firedac::Stan::Intf::_di_IFDStanConnectionDef ConnectionDef = {read=GetConnectionDef};
	__property void * CliObj = {read=GetCliObj};
	__property System::UnicodeString DefaultSchema = {read=FDefaultSchema};
	__property System::UnicodeString DefaultCatalog = {read=FDefaultCatalog};
	__property Firedac::Phys::Intf::TFDPhysNameParts AvoidImplicitMeta = {read=FAvoidImplicitMeta, nodefault};
	__property Firedac::Phys::Intf::TFDPhysNameParts RemoveDefaultMeta = {read=FRemoveDefaultMeta, nodefault};
	__property System::UnicodeString DriverID = {read=GetDriverID};
private:
	void *__IFDPhysConnection;	// Firedac::Phys::Intf::IFDPhysConnection 
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	void *__IFDMoniAdapter;	// Firedac::Stan::Intf::IFDMoniAdapter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2105}
	operator Firedac::Phys::Intf::_di_IFDPhysConnection()
	{
		Firedac::Phys::Intf::_di_IFDPhysConnection intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysConnection*(void) { return (Firedac::Phys::Intf::IFDPhysConnection*)&__IFDPhysConnection; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2018}
	operator Firedac::Stan::Option::_di_IFDStanOptions() { return Options; }
	#else
	operator Firedac::Stan::Option::IFDStanOptions*(void) { return (Firedac::Stan::Option::IFDStanOptions*)Options; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2006}
	operator Firedac::Stan::Intf::_di_IFDMoniAdapter()
	{
		Firedac::Stan::Intf::_di_IFDMoniAdapter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniAdapter*(void) { return (Firedac::Stan::Intf::IFDMoniAdapter*)&__IFDMoniAdapter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IFDPhysConnection; }
	#endif
	
};


enum DECLSPEC_DENUM TFDPhysTxNotification : unsigned int { cpBeforeCmdPrepare, cpAfterCmdPrepareSuccess, cpAfterCmdPrepareFailure, cpAfterCmdUnprepare, cpBeforeCmdExecute, cpAfterCmdExecuteSuccess, cpAfterCmdExecuteFailure };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysTransaction : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Firedac::Phys::Intf::_di_IFDPhysConnection FConnection;
	TFDPhysConnection* FConnectionObj;
	Firedac::Stan::Option::TFDTxOptions* FOptions;
	Firedac::Stan::Option::TFDTxOptions* FExternalOptions;
	Firedac::Stan::Intf::TFDStringList* FSavepoints;
#ifndef __aarch64__
	unsigned FSerialID;
#else /* __aarch64__ */
	unsigned long FSerialID;
#endif /* __aarch64__ */
	Firedac::Stan::Intf::TFDMoniAdapterHelper* FMoniAdapterHelper;
	bool FRetaining;
	System::Classes::TList* FCommandList;
	Firedac::Phys::Intf::TFDPhysTransactionState FState;
	System::Classes::TInterfaceList* FStateHandlerList;
	bool FPrevAutoStop;
	bool FExplicitActive;
	int FLockAutoStopCount;
	int FNotifyCount;
	bool FSharedActive;
	void __fastcall UpdateMonitor();
	bool __fastcall GetCLIAutoCommit();
	System::UnicodeString __fastcall GetDriverID();
	void __fastcall TxOperation(Firedac::Phys::Intf::TFDPhysTransactionState AOperation, bool ABefore);
	
protected:
#ifndef __aarch64__
	unsigned __fastcall GetHandle();
#else /* __aarch64__ */
	unsigned long __fastcall GetHandle();
#endif /* __aarch64__ */
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual Firedac::Stan::Intf::TFDMoniAdapterItemKinds __fastcall GetSupportItems();
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	Firedac::Stan::Option::TFDTxOptions* __fastcall GetOptions();
	bool __fastcall GetActive();
#ifndef __aarch64__
	unsigned __fastcall GetTopSerialID();
	unsigned __fastcall GetSerialID();
	unsigned __fastcall GetNestingLevel();
#else /* __aarch64__ */
	unsigned long __fastcall GetTopSerialID();
	unsigned long __fastcall GetSerialID();
	unsigned long __fastcall GetNestingLevel();
#endif /* __aarch64__ */
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnection();
	virtual void * __fastcall GetCliObj();
	Firedac::Phys::Intf::TFDPhysTransactionState __fastcall GetState();
	void __fastcall SetOptions(Firedac::Stan::Option::TFDTxOptions* const AValue);
#ifndef __aarch64__
	unsigned __fastcall StartTransaction();
#else /* __aarch64__ */
	unsigned long __fastcall StartTransaction();
#endif /* __aarch64__ */
	void __fastcall Commit();
	void __fastcall CommitRetaining();
	void __fastcall Rollback();
	void __fastcall RollbackRetaining();
	void __fastcall LockAutoStop();
	void __fastcall UnlockAutoStop(bool ASuccess, bool AAllowStop);
	void __fastcall AddStateHandler(const Firedac::Phys::Intf::_di_IFDPhysTransactionStateHandler AHandler);
	void __fastcall RemoveStateHandler(const Firedac::Phys::Intf::_di_IFDPhysTransactionStateHandler AHandler);
	void __fastcall Disconnect();
#ifndef __aarch64__
	unsigned FIDAutoCommit;
	virtual void __fastcall InternalStartTransaction(unsigned AID) = 0 ;
	virtual void __fastcall InternalCommit(unsigned AID) = 0 ;
	virtual void __fastcall InternalRollback(unsigned AID) = 0 ;
#else /* __aarch64__ */
	unsigned long FIDAutoCommit;
	virtual void __fastcall InternalStartTransaction(unsigned long AID) = 0 ;
	virtual void __fastcall InternalCommit(unsigned long AID) = 0 ;
	virtual void __fastcall InternalRollback(unsigned long AID) = 0 ;
#endif /* __aarch64__ */
	virtual void __fastcall InternalSetSavepoint(const System::UnicodeString AName);
	virtual void __fastcall InternalRollbackToSavepoint(const System::UnicodeString AName);
	virtual void __fastcall InternalCommitSavepoint(const System::UnicodeString AName);
	virtual void __fastcall InternalChanged();
	virtual void __fastcall InternalAllocHandle();
	virtual void __fastcall InternalReleaseHandle();
	virtual void __fastcall InternalSelect();
	virtual void __fastcall InternalUnSelect();
	virtual void __fastcall InternalNotify(TFDPhysTxNotification ANotification, TFDPhysCommand* ACommandObj);
	virtual void __fastcall InternalCheckState(TFDPhysCommand* ACommandObj, bool ASuccess);
	void __fastcall Update();
	void __fastcall DisconnectCommands(Firedac::Phys::Intf::TFDPhysDisconnectFilter AFilter, Firedac::Phys::Intf::TFDPhysDisconnectMode AMode);
	void __fastcall Stop(bool ASuccess);
	void __fastcall CheckStoping(bool AAllowUnprepare, bool AForce, bool ASuccess);
	void __fastcall Notify(TFDPhysTxNotification ANotification, TFDPhysCommand* ACommandObj);
	void __fastcall TransactionFinished();
	void __fastcall TransactionStarted();
	void __fastcall ReleaseHandleBase();
	
public:
	__fastcall virtual TFDPhysTransaction(TFDPhysConnection* AConnection);
	__fastcall virtual ~TFDPhysTransaction();
	__property TFDPhysConnection* ConnectionObj = {read=FConnectionObj};
	__property bool Retaining = {read=FRetaining, nodefault};
	__property bool CLIAutoCommit = {read=GetCLIAutoCommit, nodefault};
	__property System::UnicodeString DriverID = {read=GetDriverID};
private:
	void *__IFDPhysTransaction;	// Firedac::Phys::Intf::IFDPhysTransaction 
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	void *__IFDMoniAdapter;	// Firedac::Stan::Intf::IFDMoniAdapter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2113}
	operator Firedac::Phys::Intf::_di_IFDPhysTransaction()
	{
		Firedac::Phys::Intf::_di_IFDPhysTransaction intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysTransaction*(void) { return (Firedac::Phys::Intf::IFDPhysTransaction*)&__IFDPhysTransaction; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2006}
	operator Firedac::Stan::Intf::_di_IFDMoniAdapter()
	{
		Firedac::Stan::Intf::_di_IFDMoniAdapter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniAdapter*(void) { return (Firedac::Stan::Intf::IFDMoniAdapter*)&__IFDMoniAdapter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysEventThread : public Firedac::Stan::Util::TFDThread
{
	typedef Firedac::Stan::Util::TFDThread inherited;
	
private:
	TFDPhysEventAlerter* FAlerter;
	
protected:
	virtual void __fastcall DoTimeout();
	__classmethod virtual Firedac::Stan::Util::TFDThreadMsgClass __fastcall GetStartMsgClass();
	__classmethod virtual Firedac::Stan::Util::TFDThreadMsgClass __fastcall GetStopMsgClass();
	
public:
	__fastcall TFDPhysEventThread(TFDPhysEventAlerter* AAlerter);
public:
	/* TFDThread.Destroy */ inline __fastcall virtual ~TFDPhysEventThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysEventMessage : public Firedac::Stan::Util::TFDThreadMsgBase
{
	typedef Firedac::Stan::Util::TFDThreadMsgBase inherited;
	
private:
	TFDPhysEventThread* FMsgThread;
	void __fastcall BasePerform();
	
protected:
	__classmethod virtual bool __fastcall ThreadOwned();
	
public:
	virtual bool __fastcall Perform(Firedac::Stan::Util::TFDThread* AThread);
public:
	/* TFDThreadMsgBase.Create */ inline __fastcall virtual TFDPhysEventMessage()/* overload */ : Firedac::Stan::Util::TFDThreadMsgBase() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysEventMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysEventStartMessage : public Firedac::Stan::Util::TFDThreadStartMsg
{
	typedef Firedac::Stan::Util::TFDThreadStartMsg inherited;
	
public:
	virtual bool __fastcall Perform(Firedac::Stan::Util::TFDThread* AThread);
public:
	/* TFDThreadMsgBase.Create */ inline __fastcall virtual TFDPhysEventStartMessage()/* overload */ : Firedac::Stan::Util::TFDThreadStartMsg() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysEventStartMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysEventStopMessage : public Firedac::Stan::Util::TFDThreadStopMsg
{
	typedef Firedac::Stan::Util::TFDThreadStopMsg inherited;
	
public:
	virtual bool __fastcall Perform(Firedac::Stan::Util::TFDThread* AThread);
public:
	/* TFDThreadMsgBase.Create */ inline __fastcall virtual TFDPhysEventStopMessage()/* overload */ : Firedac::Stan::Util::TFDThreadStopMsg() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFDPhysEventStopMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysEventAlerter : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Firedac::Phys::Intf::_di_IFDPhysConnection FConnection;
	TFDPhysConnection* FConnectionObj;
	System::UnicodeString FKind;
	Firedac::Phys::Intf::TFDPhysEventAlerterState FState;
	Firedac::Stan::Intf::TFDStringList* FNames;
	System::UnicodeString FSubscriptionName;
	Firedac::Phys::Intf::_di_IFDPhysEventHandler FHandler;
	Firedac::Stan::Option::TFDEventAlerterOptions* FOptions;
	Firedac::Stan::Option::TFDEventAlerterOptions* FExternalOptions;
	Firedac::Stan::Intf::TFDMoniAdapterHelper* FMoniAdapterHelper;
	System::UnicodeString __fastcall GetDriverID();
	void __fastcall DoNamesChanging(System::TObject* ASender);
	void __fastcall DoTimeout();
	void __fastcall MarkChangeHandlers(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler, bool AModified);
	bool __fastcall AreChangeHandlersModified();
	void __fastcall UpdateMonitor();
	
protected:
	Firedac::Stan::Util::TFDThread* FMsgThread;
	System::Classes::TInterfaceList* FChangeHandlers;
	Firedac::Stan::Intf::TFDStringList* FChangeHandlerNames;
	bool __fastcall IsRunning();
	void __fastcall SetupCommand(const Firedac::Phys::Intf::_di_IFDPhysCommand ACmd);
#ifndef __aarch64__
	unsigned __fastcall GetHandle();
#else /* __aarch64__ */
	unsigned long __fastcall GetHandle();
#endif /* __aarch64__ */
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual Firedac::Stan::Intf::TFDMoniAdapterItemKinds __fastcall GetSupportItems();
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnection();
	Firedac::Phys::Intf::TFDPhysEventAlerterState __fastcall GetState();
	System::UnicodeString __fastcall GetKind();
	Firedac::Stan::Option::TFDEventAlerterOptions* __fastcall GetOptions();
	System::Classes::TStrings* __fastcall GetNames();
	System::UnicodeString __fastcall GetSubscriptionName();
	Firedac::Phys::Intf::_di_IFDPhysEventHandler __fastcall GetHandler();
	void __fastcall SetOptions(Firedac::Stan::Option::TFDEventAlerterOptions* const AValue);
	void __fastcall SetNames(System::Classes::TStrings* const AValue);
	void __fastcall SetSubscriptionName(const System::UnicodeString AValue);
	void __fastcall SetHandler(const Firedac::Phys::Intf::_di_IFDPhysEventHandler AValue);
	void __fastcall Register();
	void __fastcall Unregister();
	void __fastcall Signal(const System::UnicodeString AEvent, const System::Variant &AArgument);
	void __fastcall Refresh(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler, bool AForce);
	void __fastcall AddChangeHandler(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler);
	void __fastcall RemoveChangeHandler(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler);
	void __fastcall AbortJob();
	virtual void __fastcall InternalAllocHandle();
	virtual void __fastcall InternalReleaseHandle();
	virtual void __fastcall InternalHandle(TFDPhysEventMessage* AEventMessage) = 0 ;
	virtual void __fastcall InternalAbortJob();
	virtual void __fastcall InternalRegister();
	virtual void __fastcall InternalUnregister();
	virtual void __fastcall InternalSignal(const System::UnicodeString AEvent, const System::Variant &AArgument) = 0 ;
	virtual void __fastcall InternalRefresh(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler);
	virtual void __fastcall InternalHandleEvent(const System::UnicodeString AEventName, const System::Variant &AArgument);
	virtual void __fastcall InternalHandleTimeout(bool &AContinue);
	virtual void __fastcall InternalChangeHandlerModified(const Firedac::Phys::Intf::_di_IFDPhysChangeHandler AHandler, const System::UnicodeString AEventName, System::Classes::TOperation AOperation);
	
public:
	__fastcall virtual TFDPhysEventAlerter(TFDPhysConnection* AConnection, const System::UnicodeString AKind);
	__fastcall virtual ~TFDPhysEventAlerter();
	__property TFDPhysConnection* ConnectionObj = {read=FConnectionObj};
	__property System::UnicodeString DriverID = {read=GetDriverID};
private:
	void *__IFDPhysEventAlerter;	// Firedac::Phys::Intf::IFDPhysEventAlerter 
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	void *__IFDMoniAdapter;	// Firedac::Stan::Intf::IFDMoniAdapter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2117}
	operator Firedac::Phys::Intf::_di_IFDPhysEventAlerter()
	{
		Firedac::Phys::Intf::_di_IFDPhysEventAlerter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysEventAlerter*(void) { return (Firedac::Phys::Intf::IFDPhysEventAlerter*)&__IFDPhysEventAlerter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2006}
	operator Firedac::Stan::Intf::_di_IFDMoniAdapter()
	{
		Firedac::Stan::Intf::_di_IFDMoniAdapter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniAdapter*(void) { return (Firedac::Stan::Intf::IFDMoniAdapter*)&__IFDMoniAdapter; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

struct DECLSPEC_DRECORD TFDPhysDataTableInfo
{
public:
	System::UnicodeString FSourceName;
	int FSourceID;
	System::UnicodeString FOriginName;
	int FArraySize;
};


struct DECLSPEC_DRECORD TFDPhysDataColumnInfo
{
public:
	int FParentTableSourceID;
	int FTableSourceID;
	System::UnicodeString FSourceName;
	int FSourceID;
	System::UnicodeString FSourceTypeName;
	Firedac::Stan::Intf::TFDDataType FSourceType;
	Firedac::Phys::Intf::TFDPhysParsedName FOriginTabName;
	System::UnicodeString FOriginColName;
	Firedac::Stan::Intf::TFDDataType FType;
#ifndef __aarch64__
	unsigned FLen;
#else /* __aarch64__ */
	unsigned long FLen;
#endif /* __aarch64__ */
	int FPrec;
	int FScale;
	Firedac::Stan::Intf::TFDDataAttributes FAttrs;
	Firedac::Stan::Intf::TFDDataOptions FForceAddOpts;
	Firedac::Stan::Intf::TFDDataOptions FForceRemOpts;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysCommand : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FBaseObjectName;
	System::UnicodeString FSchemaName;
	System::UnicodeString FCatalogName;
	System::UnicodeString FCommandText;
	Firedac::Phys::Intf::TFDPhysCommandKind FCommandKind;
	bool FFixedCommandKind;
	Firedac::Stan::Param::TFDMacros* FMacros;
	Firedac::Stan::Param::TFDParams* FParams;
	Firedac::Phys::Intf::TFDPhysObjectScopes FObjectScopes;
	Firedac::Phys::Intf::TFDPhysTableKinds FTableKinds;
	System::UnicodeString FWildcard;
	Firedac::Stan::Intf::_di_IFDStanAsyncExecutor FExecutor;
	Firedac::Phys::Intf::TFDPhysCommandState FState;
	NativeUInt FThreadID;
	System::UnicodeString FSourceObjectName;
	System::UnicodeString FSourceRecordSetName;
	int FRecordSetIndex;
	System::Word FOverload;
	bool FEof;
	bool FFirstFetch;
	bool FNextRecordSet;
	Firedac::Stan::Intf::_di_IFDStanErrorHandler FErrorHandler;
	int FExecuteCount;
	Firedac::Phys::Intf::_di_IFDPhysCommandStateHandler FStateHandler;
#ifndef __aarch64__
	int FRowsAffected;
#else /* __aarch64__ */
	__int64 FRowsAffected;
#endif /* __aarch64__ */
	bool FRowsAffectedReal;
	Firedac::Stan::Intf::TFDErrorAction FErrorAction;
	Firedac::Phys::Intf::_di_IFDPhysMappingHandler FMappingHandler;
	Firedac::Stan::Intf::TFDMoniAdapterHelper* FMoniAdapterHelper;
	Firedac::Phys::Intf::TFDPhysLimitOptions FLimitOptions;
	void __fastcall UpdateMonitor();
	void __fastcall CheckState(Firedac::Phys::Intf::TFDPhysCommandState ARequiredState);
	Firedac::Dats::TFDDatSTable* __fastcall DoDefineDataTable(Firedac::Dats::TFDDatSManager* ADatSManager, Firedac::Dats::TFDDatSTable* ATable, int ARootID, const System::UnicodeString ARootName, Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode AMetaInfoMergeMode);
	void __fastcall PreprocessCommand(bool ACreateParams, bool ACreateMacros, bool AExpandParams, bool AExpandMacros, bool AExpandEscapes, bool AParseSQL);
	bool __fastcall CheckMetaAvailability();
	void __fastcall OpenBase();
	void __fastcall FetchBase(Firedac::Dats::TFDDatSTable* ATable, bool AAll);
	void __fastcall ExecuteBase(int ATimes, int AOffset);
	void __fastcall BeginDefine();
	System::Classes::TPersistent* __fastcall GetParamsOwner();
	System::UnicodeString __fastcall GetDriverID();
	void __fastcall CheckPreprocessCommand(bool ACreateParams);
	void __fastcall ExecuteTask(const Firedac::Stan::Intf::_di_IFDStanAsyncOperation AOperation, const Firedac::Stan::Intf::_di_IFDStanAsyncHandler AHandler, bool ABlocked);
	
protected:
	Firedac::Stan::Option::_di_IFDStanOptions FOptions;
	System::Classes::TComponentName __fastcall GetName();
	Firedac::Stan::Intf::_di_IFDStanObject __fastcall GetParent();
	void __fastcall BeforeReuse();
	void __fastcall AfterReuse();
	void __fastcall SetOwner(System::TObject* const AOwner, const System::Classes::TComponentName ARole);
	void __fastcall HandleException(const Firedac::Stan::Intf::_di_IFDStanObject AInitiator, System::Sysutils::Exception* &AException);
	__property Firedac::Stan::Option::_di_IFDStanOptions Options = {read=FOptions};
	void __fastcall GetParentOptions(Firedac::Stan::Option::_di_IFDStanOptions &AOpts);
#ifndef __aarch64__
	unsigned __fastcall GetHandle();
#else /* __aarch64__ */
	unsigned long __fastcall GetHandle();
#endif /* __aarch64__ */
	virtual int __fastcall GetItemCount();
	virtual void __fastcall GetItem(int AIndex, /* out */ System::UnicodeString &AName, /* out */ System::Variant &AValue, /* out */ Firedac::Stan::Intf::TFDMoniAdapterItemKind &AKind);
	virtual Firedac::Stan::Intf::TFDMoniAdapterItemKinds __fastcall GetSupportItems();
	System::UnicodeString __fastcall GetSchemaName();
	System::UnicodeString __fastcall GetCatalogName();
	System::UnicodeString __fastcall GetBaseObjectName();
	Firedac::Phys::Intf::_di_IFDPhysConnection __fastcall GetConnection();
	Firedac::Stan::Option::_di_IFDStanOptions __fastcall GetOptions();
	Firedac::Phys::Intf::TFDPhysCommandState __fastcall GetState();
	System::UnicodeString __fastcall GetCommandText();
	Firedac::Phys::Intf::TFDPhysCommandKind __fastcall GetCommandKind();
	Firedac::Stan::Param::TFDParams* __fastcall GetParams();
	System::Word __fastcall GetOverload();
	bool __fastcall GetNextRecordSet();
	Firedac::Stan::Intf::_di_IFDStanErrorHandler __fastcall GetErrorHandler();
	System::UnicodeString __fastcall GetSourceObjectName();
	System::UnicodeString __fastcall GetSourceRecordSetName();
	Firedac::Stan::Param::TFDMacros* __fastcall GetMacros();
#ifndef __aarch64__
	int __fastcall GetRowsAffected();
#else /* __aarch64__ */
	__int64 __fastcall GetRowsAffected();
#endif /* __aarch64__ */
	bool __fastcall GetRowsAffectedReal();
	Firedac::Stan::Intf::TFDErrorAction __fastcall GetErrorAction();
	Firedac::Phys::Intf::_di_IFDPhysMappingHandler __fastcall GetMappingHandler();
	int __fastcall GetSQLOrderByPos();
	virtual void * __fastcall GetCliObj();
	Firedac::Phys::Intf::_di_IFDPhysTransaction __fastcall GetTransaction();
	System::UnicodeString __fastcall GetSQLText();
	Firedac::Phys::Intf::_di_IFDPhysCommandStateHandler __fastcall GetStateHandler();
	void __fastcall SetSchemaName(const System::UnicodeString AValue);
	void __fastcall SetCatalogName(const System::UnicodeString AValue);
	void __fastcall SetBaseObjectName(const System::UnicodeString AValue);
	void __fastcall SetOptions(const Firedac::Stan::Option::_di_IFDStanOptions AValue);
	void __fastcall SetCommandText(const System::UnicodeString AValue);
	void __fastcall SetCommandKind(const Firedac::Phys::Intf::TFDPhysCommandKind AValue);
	void __fastcall SetSourceObjectName(const System::UnicodeString AValue);
	void __fastcall SetSourceRecordSetName(const System::UnicodeString AValue);
	void __fastcall SetNextRecordSet(const bool AValue);
	void __fastcall SetErrorHandler(const Firedac::Stan::Intf::_di_IFDStanErrorHandler AValue);
	void __fastcall SetOverload(const System::Word AValue);
	void __fastcall SetMappingHandler(const Firedac::Phys::Intf::_di_IFDPhysMappingHandler AValue);
	void __fastcall SetState(const Firedac::Phys::Intf::TFDPhysCommandState AValue);
	void __fastcall SetTransaction(const Firedac::Phys::Intf::_di_IFDPhysTransaction AValue);
	void __fastcall SetStateHandler(const Firedac::Phys::Intf::_di_IFDPhysCommandStateHandler AValue);
	void __fastcall SetMacros(Firedac::Stan::Param::TFDMacros* AValue);
	void __fastcall SetParams(Firedac::Stan::Param::TFDParams* AValue);
	void __fastcall AbortJob(const bool AWait = false);
	Firedac::Dats::TFDDatSTable* __fastcall Define(Firedac::Dats::TFDDatSManager* ADatSManager, Firedac::Dats::TFDDatSTable* ATable = (Firedac::Dats::TFDDatSTable*)(0x0), Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode AMetaInfoMergeMode = (Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode)(0x0))/* overload */;
	Firedac::Dats::TFDDatSTable* __fastcall Define(Firedac::Dats::TFDDatSTable* ATable, Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode AMetaInfoMergeMode = (Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode)(0x0))/* overload */;
	void __fastcall Execute(int ATimes = 0x0, int AOffset = 0x0, bool ABlocked = false);
	void __fastcall Fetch(Firedac::Dats::TFDDatSTable* ATable, bool AAll = true, bool ABlocked = false)/* overload */;
	void __fastcall Fetch(Firedac::Dats::TFDDatSManager* ADatSManager, Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode AMetaInfoMergeMode = (Firedac::Phys::Intf::TFDPhysMetaInfoMergeMode)(0x0))/* overload */;
	void __fastcall CloseStreams();
	void __fastcall Preprocess();
	void __fastcall Prepare(const System::UnicodeString ACommandText = System::UnicodeString(), bool ACreateParams = true);
	void __fastcall Unprepare();
	void __fastcall Open(bool ABlocked = false);
	void __fastcall Close();
	void __fastcall CloseAll();
	void __fastcall Disconnect();
	void __fastcall CheckAsyncProgress();
	Firedac::Phys::Intf::TFDPhysMetaInfoKind __fastcall GetMetaInfoKind();
	void __fastcall SetMetaInfoKind(Firedac::Phys::Intf::TFDPhysMetaInfoKind AValue);
	Firedac::Phys::Intf::TFDPhysTableKinds __fastcall GetTableKinds();
	void __fastcall SetTableKinds(Firedac::Phys::Intf::TFDPhysTableKinds AValue);
	System::UnicodeString __fastcall GetWildcard();
	void __fastcall SetWildcard(const System::UnicodeString AValue);
	Firedac::Phys::Intf::TFDPhysObjectScopes __fastcall GetObjectScopes();
	void __fastcall SetObjectScopes(Firedac::Phys::Intf::TFDPhysObjectScopes AValue);
	TFDPhysConnection* FConnectionObj;
	Firedac::Phys::Intf::_di_IFDPhysConnection FConnection;
	TFDPhysTransaction* FTransactionObj;
	Firedac::Phys::Intf::_di_IFDPhysTransaction FTransaction;
	System::UnicodeString FDbCommandText;
	Firedac::Phys::Intf::TFDPhysMetaInfoKind FMetaInfoKind;
	Firedac::Stan::Util::TFDBuffer* FBuffer;
	int FSQLValuesPos;
	int FSQLValuesPosEnd;
	int FSQLOrderByPos;
	int FSQLLimitSkip;
	int FSQLLimitRows;
	int FRecordsFetched;
	System::UnicodeString __fastcall GetTraceCommandText(const System::UnicodeString ACmd = System::UnicodeString());
	void __fastcall Trace(Firedac::Stan::Intf::TFDMoniEventKind AKind, Firedac::Stan::Intf::TFDMoniEventStep AStep, const System::UnicodeString AMsg, const System::TVarRec *AArgs, const int AArgs_High);
	bool __fastcall EnterTrace(TFDPhysConnection* AConnObj);
	bool __fastcall ExitTrace(TFDPhysConnection* AConnObj, bool &AUpdateMonitor);
	bool __fastcall CheckFetchColumn(Firedac::Stan::Intf::TFDDataType ADataType, Firedac::Stan::Intf::TFDDataAttributes AAttributes)/* overload */;
	void __fastcall CheckParamMatching(Firedac::Stan::Param::TFDParam* AParam, Data::Db::TFieldType ADataType, Data::Db::TParamType AParamType, int APrec);
	void __fastcall CreateCommandGenerator(/* out */ Firedac::Phys::Intf::_di_IFDPhysCommandGenerator &AGen);
	bool __fastcall OpenBlocked();
	void __fastcall GenerateStoredProcParams(const Firedac::Phys::Intf::TFDPhysParsedName &AName);
	void __fastcall GenerateStoredProcCall(const Firedac::Phys::Intf::TFDPhysParsedName &AName, Firedac::Phys::Intf::TFDPhysCommandKind ASPUsage);
	void __fastcall GetSelectMetaInfoParams(/* out */ Firedac::Phys::Intf::TFDPhysParsedName &AName);
	void __fastcall GenerateSelectMetaInfo(const Firedac::Phys::Intf::TFDPhysParsedName &AName);
	void __fastcall GenerateLimitSelect();
	void __fastcall GenerateParamMarkers();
	void __fastcall ParTypeMapError(Firedac::Stan::Param::TFDParam* AParam);
	void __fastcall ParTypeUnknownError(Firedac::Stan::Param::TFDParam* AParam);
	void __fastcall ParDefChangedError(Data::Db::TFieldType ADataType, Firedac::Stan::Param::TFDParam* AParam);
	void __fastcall ParSetChangedError(int AExpected, int AActual);
	void __fastcall UnsupParamObjError(Firedac::Stan::Param::TFDParam* AParam);
	void __fastcall CheckMetaInfoParams(const Firedac::Phys::Intf::TFDPhysParsedName &AName);
#ifndef __aarch64__
	void __fastcall CheckExact(bool AUseRecsMax, int ATimes, int AOffset, int AValue, bool AFetch);
#else /* __aarch64__ */
	void __fastcall CheckExact(bool AUseRecsMax, int ATimes, int AOffset, __int64 AValue, bool AFetch);
#endif /* __aarch64__ */
	void __fastcall CheckArrayDMLWithIntStr(bool AHasIntStreams, int ATimes, int AOffset);
	void __fastcall InitRowsAffected();
#ifndef __aarch64__
	void __fastcall UpdateRowsAffected(int AValue);
#else /* __aarch64__ */
	void __fastcall UpdateRowsAffected(__int64 AValue);
#endif /* __aarch64__ */
	virtual void __fastcall InternalAbort();
	virtual void __fastcall InternalPrepare() = 0 ;
	virtual void __fastcall InternalUnprepare() = 0 ;
#ifndef __aarch64__
	virtual bool __fastcall InternalOpen(int &ACount) = 0 ;
#else /* __aarch64__ */
	virtual bool __fastcall InternalOpen(__int64 &ACount) = 0 ;
#endif /* __aarch64__ */
	virtual bool __fastcall InternalNextRecordSet() = 0 ;
	virtual void __fastcall InternalClose() = 0 ;
#ifndef __aarch64__
	virtual void __fastcall InternalExecute(int ATimes, int AOffset, int &ACount) = 0 ;
#else /* __aarch64__ */
	virtual void __fastcall InternalExecute(int ATimes, int AOffset, __int64 &ACount) = 0 ;
#endif /* __aarch64__ */
	virtual void __fastcall InternalCloseStreams();
	virtual bool __fastcall InternalUseStandardMetadata();
	virtual bool __fastcall InternalColInfoStart(TFDPhysDataTableInfo &ATabInfo) = 0 ;
	virtual bool __fastcall InternalColInfoGet(TFDPhysDataColumnInfo &AColInfo) = 0 ;
#ifndef __aarch64__
	virtual unsigned __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned ARowsetSize) = 0 ;
#else /* __aarch64__ */
	virtual unsigned long __fastcall InternalFetchRowSet(Firedac::Dats::TFDDatSTable* ATable, Firedac::Dats::TFDDatSRow* AParentRow, unsigned long ARowsetSize) = 0 ;
#endif /* __aarch64__ */
	
public:
	__fastcall TFDPhysCommand(TFDPhysConnection* AConnection);
	__fastcall virtual ~TFDPhysCommand();
	__property System::UnicodeString DriverID = {read=GetDriverID};
private:
	void *__IFDPhysMetaInfoCommand;	// Firedac::Phys::Intf::IFDPhysMetaInfoCommand 
	void *__IFDStanErrorHandler;	// Firedac::Stan::Intf::IFDStanErrorHandler 
	void *__IFDStanObject;	// Firedac::Stan::Intf::IFDStanObject 
	void *__IFDMoniAdapter;	// Firedac::Stan::Intf::IFDMoniAdapter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2110}
	operator Firedac::Phys::Intf::_di_IFDPhysMetaInfoCommand()
	{
		Firedac::Phys::Intf::_di_IFDPhysMetaInfoCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysMetaInfoCommand*(void) { return (Firedac::Phys::Intf::IFDPhysMetaInfoCommand*)&__IFDPhysMetaInfoCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2109}
	operator Firedac::Phys::Intf::_di_IFDPhysCommand()
	{
		Firedac::Phys::Intf::_di_IFDPhysCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Phys::Intf::IFDPhysCommand*(void) { return (Firedac::Phys::Intf::IFDPhysCommand*)&__IFDPhysMetaInfoCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2007}
	operator Firedac::Stan::Intf::_di_IFDStanErrorHandler()
	{
		Firedac::Stan::Intf::_di_IFDStanErrorHandler intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanErrorHandler*(void) { return (Firedac::Stan::Intf::IFDStanErrorHandler*)&__IFDStanErrorHandler; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2018}
	operator Firedac::Stan::Option::_di_IFDStanOptions() { return Options; }
	#else
	operator Firedac::Stan::Option::IFDStanOptions*(void) { return (Firedac::Stan::Option::IFDStanOptions*)Options; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2001}
	operator Firedac::Stan::Intf::_di_IFDStanObject()
	{
		Firedac::Stan::Intf::_di_IFDStanObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDStanObject*(void) { return (Firedac::Stan::Intf::IFDStanObject*)&__IFDStanObject; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2006}
	operator Firedac::Stan::Intf::_di_IFDMoniAdapter()
	{
		Firedac::Stan::Intf::_di_IFDMoniAdapter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Stan::Intf::IFDMoniAdapter*(void) { return (Firedac::Stan::Intf::IFDMoniAdapter*)&__IFDMoniAdapter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IFDPhysMetaInfoCommand; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TFDPhysManager* FDPhysManagerObj;
}	/* namespace Phys */
}	/* namespace Firedac */
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
#endif	// Firedac_PhysHPP
