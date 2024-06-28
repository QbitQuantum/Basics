// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTP.pas' rev: 34.00 (iOS)

#ifndef IdftpHPP
#define IdftpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdGlobal.hpp>
#include <IdCustomTransparentProxy.hpp>
#include <IdExceptionCore.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdFTPCommon.hpp>
#include <IdFTPList.hpp>
#include <IdFTPListParseBase.hpp>
#include <IdException.hpp>
#include <IdIOHandler.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdReplyFTP.hpp>
#include <IdBaseComponent.hpp>
#include <IdReplyRFC.hpp>
#include <IdReply.hpp>
#include <IdSocketHandle.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPClient.hpp>
#include <IdThreadSafe.hpp>
#include <IdZLibCompressorBase.hpp>
#include <IdComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdFTPClientIdentifier;
class DELPHICLASS TIdFtpProxySettings;
class DELPHICLASS TIdFTPTZInfo;
class DELPHICLASS TIdFTPKeepAlive;
class DELPHICLASS TIdFTP;
class DELPHICLASS EIdFTPException;
class DELPHICLASS EIdFTPFileAlreadyExists;
class DELPHICLASS EIdFTPMustUseExtWithIPv6;
class DELPHICLASS EIdFTPMustUseExtWithNATFastTrack;
class DELPHICLASS EIdFTPPassiveMustBeTrueWithNATFT;
class DELPHICLASS EIdFTPServerSentInvalidPort;
class DELPHICLASS EIdFTPSiteToSiteTransfer;
class DELPHICLASS EIdFTPSToSNATFastTrack;
class DELPHICLASS EIdFTPSToSNoDataProtection;
class DELPHICLASS EIdFTPSToSIPProtoMustBeSame;
class DELPHICLASS EIdFTPSToSBothMostSupportSSCN;
class DELPHICLASS EIdFTPSToSTransModesMustBeSame;
class DELPHICLASS EIdFTPOnCustomFTPProxyRequired;
class DELPHICLASS EIdFTPConnAssuranceFailure;
class DELPHICLASS EIdFTPWrongIOHandler;
class DELPHICLASS EIdFTPUploadFileNameCanNotBeEmpty;
class DELPHICLASS EIdFTPDataPortProtection;
class DELPHICLASS EIdFTPNoDataPortProtectionAfterCCC;
class DELPHICLASS EIdFTPNoDataPortProtectionWOEncryption;
class DELPHICLASS EIdFTPNoCCCWOEncryption;
class DELPHICLASS EIdFTPAUTHException;
class DELPHICLASS EIdFTPNoAUTHWOSSL;
class DELPHICLASS EIdFTPCanNotSetAUTHCon;
class DELPHICLASS EIdFTPMissingCompressor;
class DELPHICLASS EIdFTPCompressorNotReady;
class DELPHICLASS EIdFTPUnsupportedTransferMode;
class DELPHICLASS EIdFTPUnsupportedTransferType;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdFtpProxyType : unsigned char { fpcmNone, fpcmUserSite, fpcmSite, fpcmOpen, fpcmUserPass, fpcmTransparent, fpcmUserHostFireWallID, fpcmNovellBorder, fpcmHttpProxyWithFtp, fpcmCustomProxy };

enum DECLSPEC_DENUM TAuthCmd : unsigned char { tAuto, tAuthTLS, tAuthSSL, tAuthTLSC, tAuthTLSP };

typedef void __fastcall (__closure *TIdCreateFTPList)(System::TObject* ASender, Idftplist::TIdFTPListItems* &VFTPList);

typedef System::Classes::TNotifyEvent TOnAfterClientLogin;

typedef void __fastcall (__closure *TIdFtpAfterGet)(System::TObject* ASender, System::Classes::TStream* AStream);

typedef void __fastcall (__closure *TIdOnDataChannelCreate)(System::TObject* ASender, Idtcpconnection::TIdTCPConnection* ADataChannel);

typedef void __fastcall (__closure *TIdOnDataChannelDestroy)(System::TObject* ASender, Idtcpconnection::TIdTCPConnection* ADataChannel);

typedef void __fastcall (__closure *TIdNeedAccountEvent)(System::TObject* ASender, System::UnicodeString &VAcct);

typedef void __fastcall (__closure *TIdFTPBannerEvent)(System::TObject* ASender, const System::UnicodeString AMsg);

class PASCALIMPLEMENTATION TIdFTPClientIdentifier : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	System::UnicodeString FClientName;
	System::UnicodeString FClientVersion;
	System::UnicodeString FPlatformDescription;
	void __fastcall SetClientName(const System::UnicodeString AValue);
	void __fastcall SetClientVersion(const System::UnicodeString AValue);
	void __fastcall SetPlatformDescription(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetClntOutput();
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	__property System::UnicodeString ClntOutput = {read=GetClntOutput};
	
__published:
	__property System::UnicodeString ClientName = {read=FClientName, write=SetClientName};
	__property System::UnicodeString ClientVersion = {read=FClientVersion, write=SetClientVersion};
	__property System::UnicodeString PlatformDescription = {read=FPlatformDescription, write=SetPlatformDescription};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdFTPClientIdentifier() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdFTPClientIdentifier() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TIdFtpProxySettings : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	System::UnicodeString FHost;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	TIdFtpProxyType FProxyType;
	System::Word FPort;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property TIdFtpProxyType ProxyType = {read=FProxyType, write=FProxyType, nodefault};
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::Word Port = {read=FPort, write=FPort, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdFtpProxySettings() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdFtpProxySettings() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TIdFTPTZInfo : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	System::TDateTime FGMTOffset;
	bool FGMTOffsetAvailable;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property System::TDateTime GMTOffset = {read=FGMTOffset, write=FGMTOffset};
	__property bool GMTOffsetAvailable = {read=FGMTOffsetAvailable, write=FGMTOffsetAvailable, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdFTPTZInfo() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdFTPTZInfo() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TIdFTPKeepAlive : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	bool FUseKeepAlive;
	int FIdleTimeMS;
	int FIntervalMS;
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	
__published:
	__property bool UseKeepAlive = {read=FUseKeepAlive, write=FUseKeepAlive, nodefault};
	__property int IdleTimeMS = {read=FIdleTimeMS, write=FIdleTimeMS, nodefault};
	__property int IntervalMS = {read=FIntervalMS, write=FIntervalMS, nodefault};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TIdFTPKeepAlive() { }
	
public:
	/* TObject.Create */ inline __fastcall TIdFTPKeepAlive() : System::Classes::TPersistent() { }
	
};


class PASCALIMPLEMENTATION TIdFTP : public Idexplicittlsclientserverbase::TIdExplicitTLSClient
{
	typedef Idexplicittlsclientserverbase::TIdExplicitTLSClient inherited;
	
protected:
	bool FAutoLogin;
	bool FAutoIssueFEAT;
	Idftpcommon::TIdFTPTransferMode FCurrentTransferMode;
	TIdFTPClientIdentifier* FClientInfo;
	bool FDataSettingsSent;
	bool FUsingSFTP;
	bool FUsingCCC;
	bool FUseHOST;
	System::UnicodeString FServerHOST;
	bool FCanUseMLS;
	bool FUsingExtDataPort;
	bool FUsingNATFastTrack;
	bool FCanResume;
	System::Classes::TStrings* FListResult;
	Idreplyftp::TIdReplyFTP* FLoginMsg;
	bool FPassive;
	bool FPassiveUseControlHost;
	Idftpcommon::TIdFTPDataPortSecurity FDataPortProtection;
	TAuthCmd FAUTHCmd;
	System::Word FDataPort;
	System::Word FDataPortMin;
	System::Word FDataPortMax;
	Idglobal::_di_IIdTextEncoding FDefStringEncoding;
	System::UnicodeString FExternalIP;
	bool FResumeTested;
	System::UnicodeString FServerDesc;
	System::UnicodeString FSystemDesc;
	Idftpcommon::TIdFTPTransferType FTransferType;
	int FTransferTimeout;
	int FListenTimeout;
	Idtcpconnection::TIdTCPConnection* FDataChannel;
	Idftplist::TIdFTPListItems* FDirectoryListing;
	System::UnicodeString FDirFormat;
	Idftplistparsebase::TIdFTPListParseClass FListParserClass;
	System::Classes::TNotifyEvent FOnAfterClientLogin;
	TIdCreateFTPList FOnCreateFTPList;
	System::Classes::TNotifyEvent FOnBeforeGet;
	TIdFtpAfterGet FOnBeforePut;
	TIdFtpAfterGet FOnAfterGet;
	System::Classes::TNotifyEvent FOnAfterPut;
	TIdNeedAccountEvent FOnNeedAccount;
	System::Classes::TNotifyEvent FOnCustomFTPProxy;
	TIdOnDataChannelCreate FOnDataChannelCreate;
	TIdOnDataChannelDestroy FOnDataChannelDestroy;
	TIdFtpProxySettings* FProxySettings;
	bool FUseExtensionDataPort;
	bool FTryNATFastTrack;
	bool FUseMLIS;
	System::Classes::TStrings* FLangsSupported;
	bool FUseCCC;
	bool FSSCNOn;
	bool FIsCompressionSupported;
	TIdFTPBannerEvent FOnBannerBeforeLogin;
	TIdFTPBannerEvent FOnBannerAfterLogin;
	TIdFTPBannerEvent FOnBannerWarning;
	TIdFTPTZInfo* FTZInfo;
	Idzlibcompressorbase::TIdZLibCompressorBase* FCompressor;
	int FZLibCompressionLevel;
	int FZLibWindowBits;
	int FZLibMemLevel;
	int FZLibStratagy;
	System::Classes::TNotifyEvent FOnRetrievedDir;
	System::Classes::TNotifyEvent FOnDirParseStart;
	System::Classes::TNotifyEvent FOnDirParseEnd;
	Idthreadsafe::TIdThreadSafeBoolean* FAbortFlag;
	System::UnicodeString FAccount;
	TIdFTPKeepAlive* FNATKeepAlive;
	void __fastcall DoOnDataChannelCreate();
	void __fastcall DoOnDataChannelDestroy();
	void __fastcall DoOnRetrievedDir();
	void __fastcall DoOnDirParseStart();
	void __fastcall DoOnDirParseEnd();
	void __fastcall FinalizeDataOperation();
	void __fastcall SetTZInfo(TIdFTPTZInfo* const Value);
	bool __fastcall IsSiteZONESupported();
	int __fastcall IndexOfFeatLine(const System::UnicodeString AFeatLine);
	void __fastcall ClearSSCN();
	bool __fastcall SetSSCNToOn();
	void __fastcall SendInternalPassive(const System::UnicodeString ACmd, System::UnicodeString &VIP, System::Word &VPort);
	void __fastcall SendCPassive(System::UnicodeString &VIP, System::Word &VPort);
	System::UnicodeString __fastcall FindAuthCmd();
	virtual Idreply::TIdReplyClass __fastcall GetReplyClass();
	void __fastcall ParseFTPList();
	void __fastcall SetPassive(const bool AValue);
	void __fastcall SetTryNATFastTrack(const bool AValue);
	void __fastcall DoTryNATFastTrack();
	void __fastcall SetUseExtensionDataPort(const bool AValue);
	virtual void __fastcall SetIPVersion(const Idglobal::TIdIPVersion AValue);
	virtual void __fastcall SetIOHandler(Idiohandler::TIdIOHandler* AValue);
	virtual bool __fastcall GetSupportsTLS();
	void __fastcall ConstructDirListing();
	void __fastcall DoAfterLogin();
	void __fastcall DoFTPList();
	void __fastcall DoCustomFTPProxy();
	void __fastcall DoOnBannerAfterLogin(System::Classes::TStrings* AText);
	void __fastcall DoOnBannerBeforeLogin(System::Classes::TStrings* AText);
	void __fastcall DoOnBannerWarning(System::Classes::TStrings* AText);
	void __fastcall SendPBSZ();
	void __fastcall SendPROT();
	void __fastcall SendDataSettings();
	Idftplist::TIdFTPListItems* __fastcall GetDirectoryListing();
	void __fastcall InitDataChannel();
	void __fastcall SendPret(const System::UnicodeString ACommand);
	void __fastcall InternalGet(const System::UnicodeString ACommand, System::Classes::TStream* ADest, bool AResume = false);
	void __fastcall InternalPut(const System::UnicodeString ACommand, System::Classes::TStream* ASource, bool AFromBeginning = true, bool AResume = false);
	void __fastcall SendPassive(System::UnicodeString &VIP, System::Word &VPort);
	void __fastcall SendPort(Idsockethandle::TIdSocketHandle* AHandle)/* overload */;
	void __fastcall SendPort(const System::UnicodeString AIP, const System::Word APort)/* overload */;
	void __fastcall ParseEPSV(const System::UnicodeString AReply, System::UnicodeString &VIP, System::Word &VPort);
	void __fastcall SendEPort(Idsockethandle::TIdSocketHandle* AHandle)/* overload */;
	void __fastcall SendEPort(const System::UnicodeString AIP, const System::Word APort, const Idglobal::TIdIPVersion AIPVersion)/* overload */;
	void __fastcall SendEPassive(System::UnicodeString &VIP, System::Word &VPort);
	short __fastcall SendHost();
	void __fastcall SetProxySettings(TIdFtpProxySettings* const Value);
	void __fastcall SetClientInfo(TIdFTPClientIdentifier* const AValue);
	void __fastcall SetCompressor(Idzlibcompressorbase::TIdZLibCompressorBase* AValue);
	void __fastcall SendTransferType(Idftpcommon::TIdFTPTransferType AValue);
	void __fastcall SetTransferType(Idftpcommon::TIdFTPTransferType AValue);
	virtual void __fastcall DoBeforeGet();
	virtual void __fastcall DoBeforePut(System::Classes::TStream* AStream);
	virtual void __fastcall DoAfterGet(System::Classes::TStream* AStream);
	virtual void __fastcall DoAfterPut();
	__classmethod void __fastcall FXPSetTransferPorts(TIdFTP* AFromSite, TIdFTP* AToSite, const bool ATargetUsesPasv);
	__classmethod void __fastcall FXPSendFile(TIdFTP* AFromSite, TIdFTP* AToSite, const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile);
	__classmethod bool __fastcall InternalEncryptedTLSFXP(TIdFTP* AFromSite, TIdFTP* AToSite, const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile, const bool ATargetUsesPasv);
	__classmethod bool __fastcall InternalUnencryptedFXP(TIdFTP* AFromSite, TIdFTP* AToSite, const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile, const bool ATargetUsesPasv);
	__classmethod bool __fastcall ValidateInternalIsTLSFXP(TIdFTP* AFromSite, TIdFTP* AToSite, const bool ATargetUsesPasv);
	virtual void __fastcall InitComponent();
	virtual void __fastcall SetUseTLS(Idexplicittlsclientserverbase::TIdUseTLS AValue);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetDataPortProtection(Idftpcommon::TIdFTPDataPortSecurity AValue);
	void __fastcall SetAUTHCmd(const TAuthCmd AValue);
	void __fastcall SetDefStringEncoding(Idglobal::_di_IIdTextEncoding AValue);
	void __fastcall SetUseCCC(const bool AValue);
	void __fastcall SetNATKeepAlive(TIdFTPKeepAlive* AValue);
	void __fastcall IssueFEAT();
	bool __fastcall IsOldServU();
	bool __fastcall IsBPFTP();
	bool __fastcall IsTitan();
	bool __fastcall IsWSFTP();
	bool __fastcall IsIIS();
	bool __fastcall CheckAccount();
	bool __fastcall IsAccountNeeded();
	bool __fastcall GetSupportsVerification();
	
public:
	__fastcall TIdFTP(System::Classes::TComponent* AOwner)/* overload */;
	virtual void __fastcall GetInternalResponse(Idglobal::_di_IIdTextEncoding AEncoding = Idglobal::_di_IIdTextEncoding());
	virtual short __fastcall CheckResponse(const short AResponse, const short *AAllowedResponses, const int AAllowedResponses_High)/* overload */;
	bool __fastcall IsExtSupported(const System::UnicodeString ACmd);
	void __fastcall ExtractFeatFacts(const System::UnicodeString ACmd, System::Classes::TStrings* AResults);
	System::UnicodeString __fastcall GetLoginPassword()/* overload */;
	System::UnicodeString __fastcall GetLoginPassword(const System::UnicodeString APrompt)/* overload */;
	virtual void __fastcall Abort();
	void __fastcall Allocate(int AAllocateBytes);
	void __fastcall ChangeDir(const System::UnicodeString ADirName);
	void __fastcall ChangeDirUp();
	virtual void __fastcall Connect()/* overload */;
	__fastcall virtual ~TIdFTP();
	void __fastcall Delete(const System::UnicodeString AFilename);
	void __fastcall FileStructure(Idftpcommon::TIdFTPDataStructure AStructure);
	void __fastcall Get(const System::UnicodeString ASourceFile, System::Classes::TStream* ADest, bool AResume = false)/* overload */;
	void __fastcall Get(const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile, const bool ACanOverwrite = false, bool AResume = false)/* overload */;
	void __fastcall Help(System::Classes::TStrings* AHelpContents, System::UnicodeString ACommand = System::UnicodeString());
	virtual void __fastcall KillDataChannel();
	void __fastcall List()/* overload */;
	void __fastcall List(const System::UnicodeString ASpecifier, bool ADetails = true)/* overload */;
	void __fastcall List(System::Classes::TStrings* ADest, const System::UnicodeString ASpecifier = System::UnicodeString(), bool ADetails = true)/* overload */;
	void __fastcall ExtListDir(System::Classes::TStrings* ADest = (System::Classes::TStrings*)(0x0), const System::UnicodeString ADirectory = System::UnicodeString());
	void __fastcall ExtListItem(System::Classes::TStrings* ADest, Idftplist::TIdFTPListItems* AFList, const System::UnicodeString AItem = System::UnicodeString())/* overload */;
	void __fastcall ExtListItem(System::Classes::TStrings* ADest, const System::UnicodeString AItem = System::UnicodeString())/* overload */;
	void __fastcall ExtListItem(Idftplist::TIdFTPListItems* AFList, const System::UnicodeString AItem = System::UnicodeString())/* overload */;
	System::TDateTime __fastcall FileDate(const System::UnicodeString AFileName, const bool AsGMT = false);
	void __fastcall Login();
	void __fastcall MakeDir(const System::UnicodeString ADirName);
	void __fastcall Noop();
	void __fastcall SetCmdOpt(const System::UnicodeString ACMD, const System::UnicodeString AOptions);
	void __fastcall Put(System::Classes::TStream* const ASource, const System::UnicodeString ADestFile, const bool AAppend = false, const __int64 AStartPos = (__int64)(-1LL))/* overload */;
	void __fastcall Put(const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile = System::UnicodeString(), const bool AAppend = false, const __int64 AStartPos = (__int64)(-1LL))/* overload */;
	void __fastcall StoreUnique(System::Classes::TStream* const ASource, const __int64 AStartPos = (__int64)(-1LL))/* overload */;
	void __fastcall StoreUnique(const System::UnicodeString ASourceFile, const __int64 AStartPos = (__int64)(-1LL))/* overload */;
	void __fastcall SiteToSiteUpload(TIdFTP* const AToSite, const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile = System::UnicodeString());
	void __fastcall SiteToSiteDownload(TIdFTP* const AFromSite, const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile = System::UnicodeString());
	virtual void __fastcall DisconnectNotifyPeer();
	void __fastcall Quit _DEPRECATED_ATTRIBUTE0 ();
	short __fastcall Quote(const System::UnicodeString ACommand);
	void __fastcall RemoveDir(const System::UnicodeString ADirName);
	void __fastcall Rename(const System::UnicodeString ASourceFile, const System::UnicodeString ADestFile);
	bool __fastcall ResumeSupported();
	System::UnicodeString __fastcall RetrieveCurrentDir();
	void __fastcall Site(const System::UnicodeString ACommand);
	__int64 __fastcall Size(const System::UnicodeString AFileName);
	void __fastcall Status(System::Classes::TStrings* AStatusList);
	void __fastcall StructureMount(System::UnicodeString APath);
	void __fastcall TransferMode(Idftpcommon::TIdFTPTransferMode ATransferMode);
	void __fastcall ReInitialize(unsigned ADelay = (unsigned)(0xa));
	void __fastcall SetLang(const System::UnicodeString ALangTag);
	__int64 __fastcall CRC(const System::UnicodeString AFIleName, const __int64 AStartPoint = (__int64)(0LL), const __int64 AEndPoint = (__int64)(0LL));
	bool __fastcall VerifyFile(System::Classes::TStream* ALocalFile, const System::UnicodeString ARemoteFile, const __int64 AStartPoint = (__int64)(0LL), const __int64 AByteCount = (__int64)(0LL))/* overload */;
	bool __fastcall VerifyFile(const System::UnicodeString ALocalFile, const System::UnicodeString ARemoteFile, const __int64 AStartPoint = (__int64)(0LL), const __int64 AByteCount = (__int64)(0LL))/* overload */;
	void __fastcall CombineFiles(const System::UnicodeString ATargetFile, System::Classes::TStrings* AFileParts);
	void __fastcall SetModTime(const System::UnicodeString AFileName, const System::TDateTime ALocalTime);
	void __fastcall SetModTimeGMT(const System::UnicodeString AFileName, const System::TDateTime AGMTTime);
	bool __fastcall IsServerMDTZAndListTForm();
	__property bool IsCompressionSupported = {read=FIsCompressionSupported, nodefault};
	__property bool SupportsVerification = {read=GetSupportsVerification, nodefault};
	__property bool CanResume = {read=ResumeSupported, nodefault};
	__property bool CanUseMLS = {read=FCanUseMLS, nodefault};
	__property Idftplist::TIdFTPListItems* DirectoryListing = {read=GetDirectoryListing};
	__property System::UnicodeString DirFormat = {read=FDirFormat};
	__property System::Classes::TStrings* LangsSupported = {read=FLangsSupported};
	__property Idftplistparsebase::TIdFTPListParseClass ListParserClass = {read=FListParserClass, write=FListParserClass};
	__property Idreplyftp::TIdReplyFTP* LoginMsg = {read=FLoginMsg};
	__property System::Classes::TStrings* ListResult = {read=FListResult};
	__property System::UnicodeString SystemDesc = {read=FSystemDesc};
	__property TIdFTPTZInfo* TZInfo = {read=FTZInfo, write=SetTZInfo};
	__property bool UsingExtDataPort = {read=FUsingExtDataPort, nodefault};
	__property bool UsingNATFastTrack = {read=FUsingNATFastTrack, nodefault};
	__property bool UsingSFTP = {read=FUsingSFTP, nodefault};
	__property Idftpcommon::TIdFTPTransferMode CurrentTransferMode = {read=FCurrentTransferMode, write=TransferMode, nodefault};
	__property Idglobal::_di_IIdTextEncoding DefStringEncoding = {read=FDefStringEncoding, write=SetDefStringEncoding};
	
__published:
	__property IPVersion = {default=0};
	__property bool AutoIssueFEAT = {read=FAutoIssueFEAT, write=FAutoIssueFEAT, default=1};
	__property bool AutoLogin = {read=FAutoLogin, write=FAutoLogin, default=1};
	__property Idzlibcompressorbase::TIdZLibCompressorBase* Compressor = {read=FCompressor, write=SetCompressor};
	__property Host = {default=0};
	__property bool UseCCC = {read=FUseCCC, write=SetUseCCC, default=0};
	__property bool Passive = {read=FPassive, write=SetPassive, default=0};
	__property bool PassiveUseControlHost = {read=FPassiveUseControlHost, write=FPassiveUseControlHost, default=0};
	__property Idftpcommon::TIdFTPDataPortSecurity DataPortProtection = {read=FDataPortProtection, write=SetDataPortProtection, default=0};
	__property TAuthCmd AUTHCmd = {read=FAUTHCmd, write=SetAUTHCmd, default=0};
	__property ConnectTimeout;
	__property System::Word DataPort = {read=FDataPort, write=FDataPort, default=0};
	__property System::Word DataPortMin = {read=FDataPortMin, write=FDataPortMin, default=0};
	__property System::Word DataPortMax = {read=FDataPortMax, write=FDataPortMax, default=0};
	__property System::UnicodeString ExternalIP = {read=FExternalIP, write=FExternalIP};
	__property Password = {default=0};
	__property Idftpcommon::TIdFTPTransferType TransferType = {read=FTransferType, write=SetTransferType, default=0};
	__property int TransferTimeout = {read=FTransferTimeout, write=FTransferTimeout, default=0};
	__property int ListenTimeout = {read=FListenTimeout, write=FListenTimeout, default=10000};
	__property Username = {default=0};
	__property Port = {default=21};
	__property bool UseExtensionDataPort = {read=FUseExtensionDataPort, write=SetUseExtensionDataPort, default=0};
	__property bool UseMLIS = {read=FUseMLIS, write=FUseMLIS, default=1};
	__property bool TryNATFastTrack = {read=FTryNATFastTrack, write=SetTryNATFastTrack, default=0};
	__property TIdFTPKeepAlive* NATKeepAlive = {read=FNATKeepAlive, write=SetNATKeepAlive};
	__property TIdFtpProxySettings* ProxySettings = {read=FProxySettings, write=SetProxySettings};
	__property System::UnicodeString Account = {read=FAccount, write=FAccount};
	__property TIdFTPClientIdentifier* ClientInfo = {read=FClientInfo, write=SetClientInfo};
	__property bool UseHOST = {read=FUseHOST, write=FUseHOST, default=1};
	__property System::UnicodeString ServerHOST = {read=FServerHOST, write=FServerHOST};
	__property UseTLS = {default=0};
	__property OnTLSNotAvailable;
	__property TIdFTPBannerEvent OnBannerBeforeLogin = {read=FOnBannerBeforeLogin, write=FOnBannerBeforeLogin};
	__property TIdFTPBannerEvent OnBannerAfterLogin = {read=FOnBannerAfterLogin, write=FOnBannerAfterLogin};
	__property TIdFTPBannerEvent OnBannerWarning = {read=FOnBannerWarning, write=FOnBannerWarning};
	__property System::Classes::TNotifyEvent OnBeforeGet = {read=FOnBeforeGet, write=FOnBeforeGet};
	__property TIdFtpAfterGet OnBeforePut = {read=FOnBeforePut, write=FOnBeforePut};
	__property System::Classes::TNotifyEvent OnAfterClientLogin = {read=FOnAfterClientLogin, write=FOnAfterClientLogin};
	__property TIdCreateFTPList OnCreateFTPList = {read=FOnCreateFTPList, write=FOnCreateFTPList};
	__property TIdFtpAfterGet OnAfterGet = {read=FOnAfterGet, write=FOnAfterGet};
	__property System::Classes::TNotifyEvent OnAfterPut = {read=FOnAfterPut, write=FOnAfterPut};
	__property TIdNeedAccountEvent OnNeedAccount = {read=FOnNeedAccount, write=FOnNeedAccount};
	__property System::Classes::TNotifyEvent OnCustomFTPProxy = {read=FOnCustomFTPProxy, write=FOnCustomFTPProxy};
	__property TIdOnDataChannelCreate OnDataChannelCreate = {read=FOnDataChannelCreate, write=FOnDataChannelCreate};
	__property TIdOnDataChannelDestroy OnDataChannelDestroy = {read=FOnDataChannelDestroy, write=FOnDataChannelDestroy};
	__property System::Classes::TNotifyEvent OnRetrievedDir = {read=FOnRetrievedDir, write=FOnRetrievedDir};
	__property System::Classes::TNotifyEvent OnDirParseStart = {read=FOnDirParseStart, write=FOnDirParseStart};
	__property System::Classes::TNotifyEvent OnDirParseEnd = {read=FOnDirParseEnd, write=FOnDirParseEnd};
	__property ReadTimeout = {default=60000};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdFTP()/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  CheckResponse(const System::UnicodeString AResponse, const System::UnicodeString AAllowedResponse){ return Idtcpconnection::TIdTCPConnection::CheckResponse(AResponse, AAllowedResponse); }
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	
};


class PASCALIMPLEMENTATION EIdFTPException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPException() { }
	
};


class PASCALIMPLEMENTATION EIdFTPFileAlreadyExists : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPFileAlreadyExists(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPFileAlreadyExists(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPFileAlreadyExists(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPFileAlreadyExists(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPFileAlreadyExists(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPFileAlreadyExists(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPFileAlreadyExists(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPFileAlreadyExists(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPFileAlreadyExists(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPFileAlreadyExists(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPFileAlreadyExists(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPFileAlreadyExists(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPFileAlreadyExists() { }
	
};


class PASCALIMPLEMENTATION EIdFTPMustUseExtWithIPv6 : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPMustUseExtWithIPv6(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPMustUseExtWithIPv6(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMustUseExtWithIPv6(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMustUseExtWithIPv6(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMustUseExtWithIPv6(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMustUseExtWithIPv6(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMustUseExtWithIPv6(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPMustUseExtWithIPv6() { }
	
};


class PASCALIMPLEMENTATION EIdFTPMustUseExtWithNATFastTrack : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPMustUseExtWithNATFastTrack(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMustUseExtWithNATFastTrack(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPMustUseExtWithNATFastTrack() { }
	
};


class PASCALIMPLEMENTATION EIdFTPPassiveMustBeTrueWithNATFT : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPPassiveMustBeTrueWithNATFT(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPPassiveMustBeTrueWithNATFT(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPPassiveMustBeTrueWithNATFT() { }
	
};


class PASCALIMPLEMENTATION EIdFTPServerSentInvalidPort : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPServerSentInvalidPort(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPServerSentInvalidPort(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerSentInvalidPort(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPServerSentInvalidPort(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerSentInvalidPort(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPServerSentInvalidPort(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPServerSentInvalidPort(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPServerSentInvalidPort(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerSentInvalidPort(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPServerSentInvalidPort(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerSentInvalidPort(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPServerSentInvalidPort(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPServerSentInvalidPort() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSiteToSiteTransfer : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSiteToSiteTransfer(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSiteToSiteTransfer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSiteToSiteTransfer(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSiteToSiteTransfer(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSiteToSiteTransfer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSiteToSiteTransfer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSiteToSiteTransfer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSiteToSiteTransfer() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSToSNATFastTrack : public EIdFTPSiteToSiteTransfer
{
	typedef EIdFTPSiteToSiteTransfer inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSToSNATFastTrack(const System::UnicodeString AMsg)/* overload */ : EIdFTPSiteToSiteTransfer(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSToSNATFastTrack(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSNATFastTrack(NativeUInt Ident)/* overload */ : EIdFTPSiteToSiteTransfer(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSNATFastTrack(System::PResStringRec ResStringRec)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSNATFastTrack(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSNATFastTrack(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSToSNATFastTrack(const System::UnicodeString Msg, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSToSNATFastTrack(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSNATFastTrack(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSNATFastTrack(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSNATFastTrack(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSNATFastTrack(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSToSNATFastTrack() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSToSNoDataProtection : public EIdFTPSiteToSiteTransfer
{
	typedef EIdFTPSiteToSiteTransfer inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSToSNoDataProtection(const System::UnicodeString AMsg)/* overload */ : EIdFTPSiteToSiteTransfer(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSToSNoDataProtection(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSNoDataProtection(NativeUInt Ident)/* overload */ : EIdFTPSiteToSiteTransfer(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSNoDataProtection(System::PResStringRec ResStringRec)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSNoDataProtection(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSNoDataProtection(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSToSNoDataProtection(const System::UnicodeString Msg, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSToSNoDataProtection(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSNoDataProtection(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSNoDataProtection(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSNoDataProtection(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSNoDataProtection(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSToSNoDataProtection() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSToSIPProtoMustBeSame : public EIdFTPSiteToSiteTransfer
{
	typedef EIdFTPSiteToSiteTransfer inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSToSIPProtoMustBeSame(const System::UnicodeString AMsg)/* overload */ : EIdFTPSiteToSiteTransfer(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(NativeUInt Ident)/* overload */ : EIdFTPSiteToSiteTransfer(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(System::PResStringRec ResStringRec)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(const System::UnicodeString Msg, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSIPProtoMustBeSame(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSToSIPProtoMustBeSame() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSToSBothMostSupportSSCN : public EIdFTPSiteToSiteTransfer
{
	typedef EIdFTPSiteToSiteTransfer inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSToSBothMostSupportSSCN(const System::UnicodeString AMsg)/* overload */ : EIdFTPSiteToSiteTransfer(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(NativeUInt Ident)/* overload */ : EIdFTPSiteToSiteTransfer(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(System::PResStringRec ResStringRec)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(const System::UnicodeString Msg, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSBothMostSupportSSCN(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSToSBothMostSupportSSCN() { }
	
};


class PASCALIMPLEMENTATION EIdFTPSToSTransModesMustBeSame : public EIdFTPSiteToSiteTransfer
{
	typedef EIdFTPSiteToSiteTransfer inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPSToSTransModesMustBeSame(const System::UnicodeString AMsg)/* overload */ : EIdFTPSiteToSiteTransfer(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPSToSTransModesMustBeSame(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSTransModesMustBeSame(NativeUInt Ident)/* overload */ : EIdFTPSiteToSiteTransfer(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPSToSTransModesMustBeSame(System::PResStringRec ResStringRec)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSTransModesMustBeSame(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPSToSTransModesMustBeSame(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(const System::UnicodeString Msg, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPSiteToSiteTransfer(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPSToSTransModesMustBeSame(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPSiteToSiteTransfer(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPSToSTransModesMustBeSame() { }
	
};


class PASCALIMPLEMENTATION EIdFTPOnCustomFTPProxyRequired : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPOnCustomFTPProxyRequired(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPOnCustomFTPProxyRequired(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPOnCustomFTPProxyRequired() { }
	
};


class PASCALIMPLEMENTATION EIdFTPConnAssuranceFailure : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPConnAssuranceFailure(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPConnAssuranceFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPConnAssuranceFailure(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPConnAssuranceFailure(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPConnAssuranceFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPConnAssuranceFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPConnAssuranceFailure(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPConnAssuranceFailure(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPConnAssuranceFailure(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPConnAssuranceFailure(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPConnAssuranceFailure(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPConnAssuranceFailure(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPConnAssuranceFailure() { }
	
};


class PASCALIMPLEMENTATION EIdFTPWrongIOHandler : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPWrongIOHandler(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPWrongIOHandler(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPWrongIOHandler(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPWrongIOHandler(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPWrongIOHandler(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPWrongIOHandler(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPWrongIOHandler(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPWrongIOHandler(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPWrongIOHandler(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPWrongIOHandler(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPWrongIOHandler(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPWrongIOHandler(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPWrongIOHandler() { }
	
};


class PASCALIMPLEMENTATION EIdFTPUploadFileNameCanNotBeEmpty : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPUploadFileNameCanNotBeEmpty(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUploadFileNameCanNotBeEmpty(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPUploadFileNameCanNotBeEmpty() { }
	
};


class PASCALIMPLEMENTATION EIdFTPDataPortProtection : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPDataPortProtection(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPDataPortProtection(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPDataPortProtection(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPDataPortProtection(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPDataPortProtection(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPDataPortProtection(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPDataPortProtection(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPDataPortProtection(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPDataPortProtection(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPDataPortProtection(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPDataPortProtection(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPDataPortProtection(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPDataPortProtection() { }
	
};


class PASCALIMPLEMENTATION EIdFTPNoDataPortProtectionAfterCCC : public EIdFTPDataPortProtection
{
	typedef EIdFTPDataPortProtection inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPNoDataPortProtectionAfterCCC(const System::UnicodeString AMsg)/* overload */ : EIdFTPDataPortProtection(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPDataPortProtection(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(NativeUInt Ident)/* overload */ : EIdFTPDataPortProtection(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(System::PResStringRec ResStringRec)/* overload */ : EIdFTPDataPortProtection(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPDataPortProtection(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPDataPortProtection(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(const System::UnicodeString Msg, int AHelpContext) : EIdFTPDataPortProtection(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPDataPortProtection(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionAfterCCC(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPNoDataPortProtectionAfterCCC() { }
	
};


class PASCALIMPLEMENTATION EIdFTPNoDataPortProtectionWOEncryption : public EIdFTPDataPortProtection
{
	typedef EIdFTPDataPortProtection inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPNoDataPortProtectionWOEncryption(const System::UnicodeString AMsg)/* overload */ : EIdFTPDataPortProtection(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPDataPortProtection(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(NativeUInt Ident)/* overload */ : EIdFTPDataPortProtection(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(System::PResStringRec ResStringRec)/* overload */ : EIdFTPDataPortProtection(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPDataPortProtection(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPDataPortProtection(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(const System::UnicodeString Msg, int AHelpContext) : EIdFTPDataPortProtection(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPDataPortProtection(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoDataPortProtectionWOEncryption(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPDataPortProtection(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPNoDataPortProtectionWOEncryption() { }
	
};


class PASCALIMPLEMENTATION EIdFTPNoCCCWOEncryption : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPNoCCCWOEncryption(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPNoCCCWOEncryption(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoCCCWOEncryption(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoCCCWOEncryption(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoCCCWOEncryption(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoCCCWOEncryption(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoCCCWOEncryption(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPNoCCCWOEncryption() { }
	
};


class PASCALIMPLEMENTATION EIdFTPAUTHException : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPAUTHException(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPAUTHException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPAUTHException(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPAUTHException(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPAUTHException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPAUTHException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPAUTHException(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPAUTHException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPAUTHException(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPAUTHException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPAUTHException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPAUTHException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPAUTHException() { }
	
};


class PASCALIMPLEMENTATION EIdFTPNoAUTHWOSSL : public EIdFTPAUTHException
{
	typedef EIdFTPAUTHException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPNoAUTHWOSSL(const System::UnicodeString AMsg)/* overload */ : EIdFTPAUTHException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPNoAUTHWOSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPAUTHException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoAUTHWOSSL(NativeUInt Ident)/* overload */ : EIdFTPAUTHException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPNoAUTHWOSSL(System::PResStringRec ResStringRec)/* overload */ : EIdFTPAUTHException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoAUTHWOSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPAUTHException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPNoAUTHWOSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPAUTHException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(const System::UnicodeString Msg, int AHelpContext) : EIdFTPAUTHException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPAUTHException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPAUTHException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPAUTHException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPAUTHException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPNoAUTHWOSSL(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPAUTHException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPNoAUTHWOSSL() { }
	
};


class PASCALIMPLEMENTATION EIdFTPCanNotSetAUTHCon : public EIdFTPAUTHException
{
	typedef EIdFTPAUTHException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPCanNotSetAUTHCon(const System::UnicodeString AMsg)/* overload */ : EIdFTPAUTHException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPCanNotSetAUTHCon(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPAUTHException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCanNotSetAUTHCon(NativeUInt Ident)/* overload */ : EIdFTPAUTHException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCanNotSetAUTHCon(System::PResStringRec ResStringRec)/* overload */ : EIdFTPAUTHException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCanNotSetAUTHCon(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPAUTHException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCanNotSetAUTHCon(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPAUTHException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(const System::UnicodeString Msg, int AHelpContext) : EIdFTPAUTHException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPAUTHException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPAUTHException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPAUTHException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPAUTHException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCanNotSetAUTHCon(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPAUTHException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPCanNotSetAUTHCon() { }
	
};


class PASCALIMPLEMENTATION EIdFTPMissingCompressor : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPMissingCompressor(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPMissingCompressor(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMissingCompressor(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPMissingCompressor(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMissingCompressor(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPMissingCompressor(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPMissingCompressor(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPMissingCompressor(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMissingCompressor(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPMissingCompressor(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMissingCompressor(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPMissingCompressor(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPMissingCompressor() { }
	
};


class PASCALIMPLEMENTATION EIdFTPCompressorNotReady : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPCompressorNotReady(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPCompressorNotReady(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCompressorNotReady(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPCompressorNotReady(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCompressorNotReady(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPCompressorNotReady(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPCompressorNotReady(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPCompressorNotReady(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCompressorNotReady(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPCompressorNotReady(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCompressorNotReady(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPCompressorNotReady(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPCompressorNotReady() { }
	
};


class PASCALIMPLEMENTATION EIdFTPUnsupportedTransferMode : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPUnsupportedTransferMode(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPUnsupportedTransferMode(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUnsupportedTransferMode(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUnsupportedTransferMode(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUnsupportedTransferMode(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUnsupportedTransferMode(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferMode(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPUnsupportedTransferMode() { }
	
};


class PASCALIMPLEMENTATION EIdFTPUnsupportedTransferType : public EIdFTPException
{
	typedef EIdFTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdFTPUnsupportedTransferType(const System::UnicodeString AMsg)/* overload */ : EIdFTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdFTPUnsupportedTransferType(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdFTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUnsupportedTransferType(NativeUInt Ident)/* overload */ : EIdFTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdFTPUnsupportedTransferType(System::PResStringRec ResStringRec)/* overload */ : EIdFTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUnsupportedTransferType(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdFTPUnsupportedTransferType(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdFTPUnsupportedTransferType(const System::UnicodeString Msg, int AHelpContext) : EIdFTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferType(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdFTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUnsupportedTransferType(NativeUInt Ident, int AHelpContext)/* overload */ : EIdFTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdFTPUnsupportedTransferType(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferType(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdFTPUnsupportedTransferType(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdFTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdFTPUnsupportedTransferType() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const Idftpcommon::TIdFTPTransferType Id_TIdFTP_TransferType = (Idftpcommon::TIdFTPTransferType)(0);
static constexpr bool Id_TIdFTP_Passive = false;
static constexpr bool Id_TIdFTP_UseNATFastTrack = false;
static constexpr System::WideChar Id_TIdFTP_HostPortDelimiter = (System::WideChar)(0x3a);
static constexpr bool Id_TIdFTP_DataConAssurance = false;
static const Idftpcommon::TIdFTPDataPortSecurity Id_TIdFTP_DataPortProtection = (Idftpcommon::TIdFTPDataPortSecurity)(0);
static constexpr bool DEF_Id_TIdFTP_Implicit = false;
static constexpr bool DEF_Id_FTP_UseExtendedDataPort = false;
static constexpr bool DEF_Id_TIdFTP_UseExtendedData = false;
static constexpr bool DEF_Id_TIdFTP_UseMIS = true;
static constexpr bool DEF_Id_FTP_UseCCC = false;
static const TAuthCmd DEF_Id_FTP_AUTH_CMD = (TAuthCmd)(0);
static constexpr System::Word DEF_Id_FTP_ListenTimeout = System::Word(0x2710);
static constexpr System::Word DEF_Id_FTP_READTIMEOUT = System::Word(0xea60);
static constexpr bool DEF_Id_FTP_UseHOST = true;
static constexpr bool DEF_Id_FTP_PassiveUseControlHost = false;
static constexpr bool DEF_Id_FTP_AutoIssueFEAT = true;
static constexpr bool DEF_Id_FTP_AutoLogin = true;
}	/* namespace Idftp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTP)
using namespace Idftp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftpHPP
