// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdDNSServer.pas' rev: 34.00 (Windows)

#ifndef IddnsserverHPP
#define IddnsserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdContainers.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdSocketHandle.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdGlobal.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdContext.hpp>
#include <IdUDPBase.hpp>
#include <IdResourceStrings.hpp>
#include <IdExceptionCore.hpp>
#include <IdDNSResolver.hpp>
#include <IdUDPServer.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdStackConsts.hpp>
#include <IdThread.hpp>
#include <IdDNSCommon.hpp>
#include <System.Contnrs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iddnsserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdDomainExpireCheckThread;
class DELPHICLASS TIdDomainNameServerMapping;
class DELPHICLASS TIdDNSMap;
class DELPHICLASS TIdMWayTreeNode;
class DELPHICLASS TIdDNTreeNode;
class DELPHICLASS TIdDNS_TCPServer;
class DELPHICLASS TIdDNS_ProcessThread;
class DELPHICLASS TIdDNS_UDPServer;
class DELPHICLASS TIdDNSServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdDomainExpireCheckThread : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	unsigned FInterval;
	System::TObject* FSender;
	System::Classes::TNotifyEvent FTimerEvent;
	bool FBusy;
	System::UnicodeString FDomain;
	System::UnicodeString FHost;
	virtual void __fastcall Run();
	void __fastcall TimerEvent();
public:
	/* TIdThread.Create */ inline __fastcall virtual TIdDomainExpireCheckThread(bool ACreateSuspended, bool ALoop, const System::UnicodeString AName) : Idthread::TIdThread(ACreateSuspended, ALoop, AName) { }
	/* TIdThread.Destroy */ inline __fastcall virtual ~TIdDomainExpireCheckThread() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdDomainNameServerMapping : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FHost;
	System::UnicodeString FDomainName;
	bool FBusy;
	unsigned FInterval;
	TIdDNSMap* FList;
	void __fastcall SetHost(const System::UnicodeString Value);
	void __fastcall SetInterval(const unsigned Value);
	
protected:
	TIdDomainExpireCheckThread* CheckScheduler;
	__property unsigned Interval = {read=FInterval, write=SetInterval, nodefault};
	__property TIdDNSMap* List = {read=FList, write=FList};
	
public:
	__fastcall TIdDomainNameServerMapping(TIdDNSMap* AList);
	__fastcall virtual ~TIdDomainNameServerMapping();
	void __fastcall SyncAndUpdate(System::TObject* Sender);
	__property System::UnicodeString Host = {read=FHost, write=SetHost};
	__property System::UnicodeString DomainName = {read=FDomainName, write=FDomainName};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdDNSMap : public Idcontainers::TIdObjectList
{
	typedef Idcontainers::TIdObjectList inherited;
	
public:
	TIdDomainNameServerMapping* operator[](int Index) { return this->Items[Index]; }
	
private:
	TIdDNS_UDPServer* FServer;
	HIDESBASE TIdDomainNameServerMapping* __fastcall GetItem(int Index);
	HIDESBASE void __fastcall SetItem(int Index, TIdDomainNameServerMapping* const Value);
	void __fastcall SetServer(TIdDNS_UDPServer* const Value);
	
public:
	__fastcall TIdDNSMap(TIdDNS_UDPServer* Server);
	__fastcall virtual ~TIdDNSMap();
	__property TIdDNS_UDPServer* Server = {read=FServer, write=SetServer};
	__property TIdDomainNameServerMapping* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TIdMWayTreeNodeClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TIdMWayTreeNodeClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdMWayTreeNode : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Idcontainers::TIdObjectList* SubTree;
	TIdMWayTreeNodeClass FFundmentalClass;
	TIdMWayTreeNode* __fastcall GetTreeNode(int Index);
	void __fastcall SetFundmentalClass(const TIdMWayTreeNodeClass Value);
	void __fastcall SetTreeNode(int Index, TIdMWayTreeNode* const Value);
	
public:
	__fastcall virtual TIdMWayTreeNode(TIdMWayTreeNodeClass NodeClass);
	__fastcall virtual ~TIdMWayTreeNode();
	__property TIdMWayTreeNodeClass FundmentalClass = {read=FFundmentalClass, write=SetFundmentalClass};
	__property TIdMWayTreeNode* Children[int Index] = {read=GetTreeNode, write=SetTreeNode};
	TIdMWayTreeNode* __fastcall AddChild();
	TIdMWayTreeNode* __fastcall InsertChild(int Index);
	void __fastcall RemoveChild(int Index);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TIdDNTreeNode : public TIdMWayTreeNode
{
	typedef TIdMWayTreeNode inherited;
	
private:
	System::UnicodeString FCLabel;
	Iddnscommon::TIdTextModeRRs* FRRs;
	System::Classes::TStrings* FChildIndex;
	TIdDNTreeNode* FParentNode;
	bool FAutoSortChild;
	void __fastcall SetCLabel(const System::UnicodeString Value);
	void __fastcall SetRRs(Iddnscommon::TIdTextModeRRs* const Value);
	TIdDNTreeNode* __fastcall GetNode(int Index);
	void __fastcall SetNode(int Index, TIdDNTreeNode* const Value);
	void __fastcall SetChildIndex(System::Classes::TStrings* const Value);
	System::UnicodeString __fastcall GetFullName();
	System::UnicodeString __fastcall ConvertToDNString();
	Idglobal::TIdBytes __fastcall DumpAllBinaryData(int &RecordCount);
	
public:
	__property TIdDNTreeNode* ParentNode = {read=FParentNode, write=FParentNode};
	__property System::UnicodeString CLabel = {read=FCLabel, write=SetCLabel};
	__property Iddnscommon::TIdTextModeRRs* RRs = {read=FRRs, write=SetRRs};
	__property TIdDNTreeNode* Children[int Index] = {read=GetNode, write=SetNode};
	__property System::Classes::TStrings* ChildIndex = {read=FChildIndex, write=SetChildIndex};
	__property bool AutoSortChild = {read=FAutoSortChild, write=FAutoSortChild, nodefault};
	__property System::UnicodeString FullName = {read=GetFullName};
	__fastcall TIdDNTreeNode(TIdDNTreeNode* AParentNode);
	__fastcall virtual ~TIdDNTreeNode();
	HIDESBASE TIdDNTreeNode* __fastcall AddChild();
	HIDESBASE TIdDNTreeNode* __fastcall InsertChild(int Index);
	HIDESBASE void __fastcall RemoveChild(int Index);
	void __fastcall SortChildren();
	void __fastcall Clear();
	void __fastcall SaveToFile(System::UnicodeString Filename);
	int __fastcall IndexByLabel(System::UnicodeString CLabel);
	int __fastcall IndexByNode(TIdDNTreeNode* ANode);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TIdDNS_TCPServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	System::Classes::TStrings* FAccessList;
	bool FAccessControl;
	virtual void __fastcall DoConnect(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	void __fastcall SetAccessList(System::Classes::TStrings* const Value);
	
public:
	__fastcall virtual ~TIdDNS_TCPServer();
	
__published:
	__property System::Classes::TStrings* AccessList = {read=FAccessList, write=SetAccessList};
	__property bool AccessControl = {read=FAccessControl, write=FAccessControl, nodefault};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDNS_TCPServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDNS_TCPServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


class PASCALIMPLEMENTATION TIdDNS_ProcessThread : public Idthread::TIdThread
{
	typedef Idthread::TIdThread inherited;
	
protected:
	Idsockethandle::TIdSocketHandle* FMyBinding;
	Idsockethandle::TIdSocketHandle* FMainBinding;
	System::Classes::TStream* FMyData;
	Idglobal::TIdBytes FData;
	TIdDNS_UDPServer* FServer;
	void __fastcall SetMyBinding(Idsockethandle::TIdSocketHandle* const Value);
	void __fastcall SetMyData(System::Classes::TStream* const Value);
	void __fastcall SetServer(TIdDNS_UDPServer* const Value);
	void __fastcall ComposeErrorResult(Idglobal::TIdBytes &VFinal, Iddnscommon::TDNSHeader* OriginalHeader, Idglobal::TIdBytes OriginalQuestion, int ErrorStatus);
	Idglobal::TIdBytes __fastcall CombineAnswer(Iddnscommon::TDNSHeader* Header, const Idglobal::TIdBytes EQuery, const Idglobal::TIdBytes Answer);
	void __fastcall InternalSearch(Iddnscommon::TDNSHeader* Header, System::UnicodeString QName, System::Word QType, Idglobal::TIdBytes &Answer, bool IfMainQuestion, bool IsSearchCache = false, bool IsAdditional = false, bool IsWildCard = false, System::UnicodeString WildCardOrgName = System::UnicodeString());
	void __fastcall ExternalSearch(Iddnsresolver::TIdDNSResolver* ADNSResolver, Iddnscommon::TDNSHeader* Header, Idglobal::TIdBytes Question, Idglobal::TIdBytes &Answer);
	System::UnicodeString __fastcall CompleteQuery(Iddnscommon::TDNSHeader* DNSHeader, System::UnicodeString Question, Idglobal::TIdBytes OriginalQuestion, Idglobal::TIdBytes &Answer, System::Word QType, System::Word QClass, Iddnsresolver::TIdDNSResolver* DNSResolver);
	void __fastcall SaveToCache(Idglobal::TIdBytes ResourceRecord, System::UnicodeString QueryName, System::Word OriginalQType);
	TIdDNTreeNode* __fastcall SearchTree(TIdDNTreeNode* Root, System::UnicodeString QName, System::Word QType);
	virtual void __fastcall Run();
	void __fastcall QueryDomain();
	void __fastcall SendData();
	
public:
	__property Idsockethandle::TIdSocketHandle* MyBinding = {read=FMyBinding, write=SetMyBinding};
	__property System::Classes::TStream* MyData = {read=FMyData, write=SetMyData};
	__property TIdDNS_UDPServer* Server = {read=FServer, write=SetServer};
	__fastcall TIdDNS_ProcessThread(bool ACreateSuspended, Idglobal::TIdBytes Data, Idsockethandle::TIdSocketHandle* MainBinding, Idsockethandle::TIdSocketHandle* Binding, TIdDNS_UDPServer* Server)/* overload */;
	__fastcall virtual ~TIdDNS_ProcessThread();
};


typedef void __fastcall (__closure *TIdDNSBeforeQueryEvent)(Idsockethandle::TIdSocketHandle* ABinding, Iddnscommon::TDNSHeader* ADNSHeader, Idglobal::TIdBytes &ADNSQuery);

typedef void __fastcall (__closure *TIdDNSAfterQueryEvent)(Idsockethandle::TIdSocketHandle* ABinding, Iddnscommon::TDNSHeader* ADNSHeader, Idglobal::TIdBytes &QueryResult, System::UnicodeString &ResultCode, Idglobal::TIdBytes Query);

typedef void __fastcall (__closure *TIdDNSAfterCacheSaved)(TIdDNTreeNode* CacheRoot);

class PASCALIMPLEMENTATION TIdDNS_UDPServer : public Idudpserver::TIdUDPServer
{
	typedef Idudpserver::TIdUDPServer inherited;
	
private:
	bool FBusy;
	
protected:
	bool FAutoUpdateZoneInfo;
	System::Classes::TStrings* FZoneMasterFiles;
	System::Classes::TStrings* FRootDNS_NET;
	bool FCacheUnknowZone;
	TIdDNTreeNode* FCached_Tree;
	TIdDNTreeNode* FHanded_Tree;
	System::Classes::TStrings* FHanded_DomainList;
	bool FAutoLoadMasterFile;
	TIdDNSAfterQueryEvent FOnAfterQuery;
	TIdDNSBeforeQueryEvent FOnBeforeQuery;
	Idglobal::TIdCriticalSection* FCS;
	TIdDNSAfterQueryEvent FOnAfterSendBack;
	TIdDNSAfterCacheSaved FOnAfterCacheSaved;
	Idglobal::TIdCriticalSection* FGlobalCS;
	System::UnicodeString FDNSVersion;
	bool FofferDNSVersion;
	DYNAMIC void __fastcall DoBeforeQuery(Idsockethandle::TIdSocketHandle* ABinding, Iddnscommon::TDNSHeader* ADNSHeader, Idglobal::TIdBytes &ADNSQuery);
	DYNAMIC void __fastcall DoAfterQuery(Idsockethandle::TIdSocketHandle* ABinding, Iddnscommon::TDNSHeader* ADNSHeader, Idglobal::TIdBytes &QueryResult, System::UnicodeString &ResultCode, Idglobal::TIdBytes Query);
	DYNAMIC void __fastcall DoAfterSendBack(Idsockethandle::TIdSocketHandle* ABinding, Iddnscommon::TDNSHeader* ADNSHeader, Idglobal::TIdBytes &QueryResult, System::UnicodeString &ResultCode, Idglobal::TIdBytes Query);
	DYNAMIC void __fastcall DoAfterCacheSaved(TIdDNTreeNode* CacheRoot);
	void __fastcall SetZoneMasterFiles(System::Classes::TStrings* const Value);
	void __fastcall SetRootDNS_NET(System::Classes::TStrings* const Value);
	void __fastcall SetHanded_DomainList(System::Classes::TStrings* const Value);
	void __fastcall InternalSearch(Iddnscommon::TDNSHeader* Header, System::UnicodeString QName, System::Word QType, Idglobal::TIdBytes &Answer, bool IfMainQuestion, bool IsSearchCache = false, bool IsAdditional = false, bool IsWildCard = false, System::UnicodeString WildCardOrgName = System::UnicodeString());
	void __fastcall ExternalSearch(Iddnsresolver::TIdDNSResolver* ADNSResolver, Iddnscommon::TDNSHeader* Header, Idglobal::TIdBytes Question, Idglobal::TIdBytes &Answer);
	void __fastcall SaveToCache(Idglobal::TIdBytes ResourceRecord, System::UnicodeString QueryName, System::Word OriginalQType);
	virtual void __fastcall InitComponent();
	__property bool AutoUpdateZoneInfo = {read=FAutoUpdateZoneInfo, write=FAutoUpdateZoneInfo, nodefault};
	__property Idglobal::TIdCriticalSection* CS = {read=FCS};
	virtual void __fastcall DoUDPRead(Idudpserver::TIdUDPListenerThread* AThread, const Idglobal::TIdBytes AData, Idsockethandle::TIdSocketHandle* ABinding);
	
public:
	__fastcall virtual ~TIdDNS_UDPServer();
	System::UnicodeString __fastcall AXFR(Iddnscommon::TDNSHeader* Header, System::UnicodeString Question, Idglobal::TIdBytes &Answer);
	System::UnicodeString __fastcall CompleteQuery _DEPRECATED_ATTRIBUTE0 (Iddnscommon::TDNSHeader* DNSHeader, System::UnicodeString Question, Idglobal::TIdBytes OriginalQuestion, Idglobal::TIdBytes &Answer, System::Word QType, System::Word QClass, Iddnsresolver::TIdDNSResolver* DNSResolver);
	bool __fastcall LoadZoneFromMasterFile(System::UnicodeString MasterFileName);
	bool __fastcall LoadZoneStrings(System::Classes::TStrings* FileStrings, System::UnicodeString Filename, TIdDNTreeNode* TreeRoot);
	TIdDNTreeNode* __fastcall SearchTree(TIdDNTreeNode* Root, System::UnicodeString QName, System::Word QType);
	void __fastcall UpdateTree(TIdDNTreeNode* TreeRoot, Iddnscommon::TIdTextModeResourceRecord* RR)/* overload */;
	System::UnicodeString __fastcall FindNodeFullName(TIdDNTreeNode* Root, System::UnicodeString QName, System::Word QType);
	TIdDNTreeNode* __fastcall FindHandedNodeByName(System::UnicodeString QName, System::Word QType);
	void __fastcall UpdateTree(TIdDNTreeNode* TreeRoot, Iddnsresolver::TResultRecord* RR)/* overload */;
	__property System::Classes::TStrings* RootDNS_NET = {read=FRootDNS_NET, write=SetRootDNS_NET};
	__property TIdDNTreeNode* Cached_Tree = {read=FCached_Tree};
	__property TIdDNTreeNode* Handed_Tree = {read=FHanded_Tree};
	__property bool Busy = {read=FBusy, nodefault};
	__property Idglobal::TIdCriticalSection* GlobalCS = {read=FGlobalCS};
	
__published:
	__property DefaultPort = {default=53};
	__property bool AutoLoadMasterFile = {read=FAutoLoadMasterFile, write=FAutoLoadMasterFile, default=0};
	__property System::Classes::TStrings* ZoneMasterFiles = {read=FZoneMasterFiles, write=SetZoneMasterFiles};
	__property bool CacheUnknowZone = {read=FCacheUnknowZone, write=FCacheUnknowZone, default=0};
	__property System::Classes::TStrings* Handed_DomainList = {read=FHanded_DomainList, write=SetHanded_DomainList};
	__property System::UnicodeString DNSVersion = {read=FDNSVersion, write=FDNSVersion};
	__property bool offerDNSVersion = {read=FofferDNSVersion, write=FofferDNSVersion, nodefault};
	__property TIdDNSBeforeQueryEvent OnBeforeQuery = {read=FOnBeforeQuery, write=FOnBeforeQuery};
	__property TIdDNSAfterQueryEvent OnAfterQuery = {read=FOnAfterQuery, write=FOnAfterQuery};
	__property TIdDNSAfterQueryEvent OnAfterSendBack = {read=FOnAfterSendBack, write=FOnAfterSendBack};
	__property TIdDNSAfterCacheSaved OnAfterCacheSaved = {read=FOnAfterCacheSaved, write=FOnAfterCacheSaved};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDNS_UDPServer(System::Classes::TComponent* AOwner)/* overload */ : Idudpserver::TIdUDPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDNS_UDPServer()/* overload */ : Idudpserver::TIdUDPServer() { }
	
};


class PASCALIMPLEMENTATION TIdDNSServer : public Idcomponent::TIdComponent
{
	typedef Idcomponent::TIdComponent inherited;
	
protected:
	bool FActive;
	bool FTCPACLActive;
	Iddnscommon::TDNSServerTypes FServerType;
	TIdDNS_TCPServer* FTCPTunnel;
	TIdDNS_UDPServer* FUDPTunnel;
	System::Classes::TStrings* FAccessList;
	Idsockethandle::TIdSocketHandles* FBindings;
	void __fastcall SetAccessList(System::Classes::TStrings* const Value);
	void __fastcall SetActive(const bool Value);
	void __fastcall SetTCPACLActive(const bool Value);
	void __fastcall SetBindings(Idsockethandle::TIdSocketHandles* const Value);
	void __fastcall TimeToUpdateNodeData(System::TObject* Sender);
	virtual void __fastcall InitComponent();
	
public:
	TIdDNSMap* BackupDNSMap;
	__fastcall virtual ~TIdDNSServer();
	void __fastcall CheckIfExpire(System::TObject* Sender);
	
__published:
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property System::Classes::TStrings* AccessList = {read=FAccessList, write=SetAccessList};
	__property Idsockethandle::TIdSocketHandles* Bindings = {read=FBindings, write=SetBindings};
	__property bool TCPACLActive = {read=FTCPACLActive, write=SetTCPACLActive, nodefault};
	__property Iddnscommon::TDNSServerTypes ServerType = {read=FServerType, write=FServerType, nodefault};
	__property TIdDNS_TCPServer* TCPTunnel = {read=FTCPTunnel, write=FTCPTunnel};
	__property TIdDNS_UDPServer* UDPTunnel = {read=FUDPTunnel, write=FUDPTunnel};
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdDNSServer(System::Classes::TComponent* AOwner)/* overload */ : Idcomponent::TIdComponent(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdDNSServer()/* overload */ : Idcomponent::TIdComponent() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Iddnsserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDDNSSERVER)
using namespace Iddnsserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IddnsserverHPP
