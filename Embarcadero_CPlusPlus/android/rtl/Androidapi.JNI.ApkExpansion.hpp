// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.ApkExpansion.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_ApkexpansionHPP
#define Androidapi_Jni_ApkexpansionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Net.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Apkexpansion
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAPEZProviderClass;
typedef System::DelphiInterface<JAPEZProviderClass> _di_JAPEZProviderClass;
__interface DELPHIINTERFACE JAPEZProvider;
typedef System::DelphiInterface<JAPEZProvider> _di_JAPEZProvider;
class DELPHICLASS TJAPEZProvider;
__interface DELPHIINTERFACE JAPKExpansionSupportClass;
typedef System::DelphiInterface<JAPKExpansionSupportClass> _di_JAPKExpansionSupportClass;
__interface DELPHIINTERFACE JAPKExpansionSupport;
typedef System::DelphiInterface<JAPKExpansionSupport> _di_JAPKExpansionSupport;
class DELPHICLASS TJAPKExpansionSupport;
__interface DELPHIINTERFACE JZipResourceFileClass;
typedef System::DelphiInterface<JZipResourceFileClass> _di_JZipResourceFileClass;
__interface DELPHIINTERFACE JZipResourceFile;
typedef System::DelphiInterface<JZipResourceFile> _di_JZipResourceFile;
class DELPHICLASS TJZipResourceFile;
__interface DELPHIINTERFACE JZipResourceFile_ZipEntryROClass;
typedef System::DelphiInterface<JZipResourceFile_ZipEntryROClass> _di_JZipResourceFile_ZipEntryROClass;
__interface DELPHIINTERFACE JZipResourceFile_ZipEntryRO;
typedef System::DelphiInterface<JZipResourceFile_ZipEntryRO> _di_JZipResourceFile_ZipEntryRO;
class DELPHICLASS TJZipResourceFile_ZipEntryRO;
__interface DELPHIINTERFACE JApkAlarmReceiverClass;
typedef System::DelphiInterface<JApkAlarmReceiverClass> _di_JApkAlarmReceiverClass;
__interface DELPHIINTERFACE JApkAlarmReceiver;
typedef System::DelphiInterface<JApkAlarmReceiver> _di_JApkAlarmReceiver;
class DELPHICLASS TJApkAlarmReceiver;
__interface DELPHIINTERFACE JApkBaseDownloaderClass;
typedef System::DelphiInterface<JApkBaseDownloaderClass> _di_JApkBaseDownloaderClass;
__interface DELPHIINTERFACE JApkBaseDownloader;
typedef System::DelphiInterface<JApkBaseDownloader> _di_JApkBaseDownloader;
class DELPHICLASS TJApkBaseDownloader;
__interface DELPHIINTERFACE JApkDownloaderClientClass;
typedef System::DelphiInterface<JApkDownloaderClientClass> _di_JApkDownloaderClientClass;
__interface DELPHIINTERFACE JApkDownloaderClient;
typedef System::DelphiInterface<JApkDownloaderClient> _di_JApkDownloaderClient;
class DELPHICLASS TJApkDownloaderClient;
__interface DELPHIINTERFACE JApkDownloaderListenerClass;
typedef System::DelphiInterface<JApkDownloaderListenerClass> _di_JApkDownloaderListenerClass;
__interface DELPHIINTERFACE JApkDownloaderListener;
typedef System::DelphiInterface<JApkDownloaderListener> _di_JApkDownloaderListener;
class DELPHICLASS TJApkDownloaderListener;
__interface DELPHIINTERFACE JCustomIntentServiceClass;
typedef System::DelphiInterface<JCustomIntentServiceClass> _di_JCustomIntentServiceClass;
__interface DELPHIINTERFACE JCustomIntentService;
typedef System::DelphiInterface<JCustomIntentService> _di_JCustomIntentService;
class DELPHICLASS TJCustomIntentService;
__interface DELPHIINTERFACE JDownloaderServiceClass;
typedef System::DelphiInterface<JDownloaderServiceClass> _di_JDownloaderServiceClass;
__interface DELPHIINTERFACE JDownloaderService;
typedef System::DelphiInterface<JDownloaderService> _di_JDownloaderService;
class DELPHICLASS TJDownloaderService;
__interface DELPHIINTERFACE JApkDownloaderServiceClass;
typedef System::DelphiInterface<JApkDownloaderServiceClass> _di_JApkDownloaderServiceClass;
__interface DELPHIINTERFACE JApkDownloaderService;
typedef System::DelphiInterface<JApkDownloaderService> _di_JApkDownloaderService;
class DELPHICLASS TJApkDownloaderService;
__interface DELPHIINTERFACE JApkFileInfoClass;
typedef System::DelphiInterface<JApkFileInfoClass> _di_JApkFileInfoClass;
__interface DELPHIINTERFACE JApkFileInfo;
typedef System::DelphiInterface<JApkFileInfo> _di_JApkFileInfo;
class DELPHICLASS TJApkFileInfo;
__interface DELPHIINTERFACE JApkFilesHelperClass;
typedef System::DelphiInterface<JApkFilesHelperClass> _di_JApkFilesHelperClass;
__interface DELPHIINTERFACE JApkFilesHelper;
typedef System::DelphiInterface<JApkFilesHelper> _di_JApkFilesHelper;
class DELPHICLASS TJApkFilesHelper;
__interface DELPHIINTERFACE JObbClass;
typedef System::DelphiInterface<JObbClass> _di_JObbClass;
__interface DELPHIINTERFACE JObb;
typedef System::DelphiInterface<JObb> _di_JObb;
class DELPHICLASS TJObb;
__interface DELPHIINTERFACE JObb_ObbListenerClass;
typedef System::DelphiInterface<JObb_ObbListenerClass> _di_JObb_ObbListenerClass;
__interface DELPHIINTERFACE JObb_ObbListener;
typedef System::DelphiInterface<JObb_ObbListener> _di_JObb_ObbListener;
class DELPHICLASS TJObb_ObbListener;
__interface DELPHIINTERFACE JDownloaderActivityClass;
typedef System::DelphiInterface<JDownloaderActivityClass> _di_JDownloaderActivityClass;
__interface DELPHIINTERFACE JDownloaderActivity;
typedef System::DelphiInterface<JDownloaderActivity> _di_JDownloaderActivity;
class DELPHICLASS TJDownloaderActivity;
__interface DELPHIINTERFACE JDownloaderActivityConfigClass;
typedef System::DelphiInterface<JDownloaderActivityConfigClass> _di_JDownloaderActivityConfigClass;
__interface DELPHIINTERFACE JDownloaderActivityConfig;
typedef System::DelphiInterface<JDownloaderActivityConfig> _di_JDownloaderActivityConfig;
class DELPHICLASS TJDownloaderActivityConfig;
__interface DELPHIINTERFACE JDownloaderActivityLauncherClass;
typedef System::DelphiInterface<JDownloaderActivityLauncherClass> _di_JDownloaderActivityLauncherClass;
__interface DELPHIINTERFACE JDownloaderActivityLauncher;
typedef System::DelphiInterface<JDownloaderActivityLauncher> _di_JDownloaderActivityLauncher;
class DELPHICLASS TJDownloaderActivityLauncher;
__interface DELPHIINTERFACE JNativeDownloaderLauncherClass;
typedef System::DelphiInterface<JNativeDownloaderLauncherClass> _di_JNativeDownloaderLauncherClass;
__interface DELPHIINTERFACE JNativeDownloaderLauncher;
typedef System::DelphiInterface<JNativeDownloaderLauncher> _di_JNativeDownloaderLauncher;
class DELPHICLASS TJNativeDownloaderLauncher;
__interface DELPHIINTERFACE JConstantsClass;
typedef System::DelphiInterface<JConstantsClass> _di_JConstantsClass;
__interface DELPHIINTERFACE JConstants;
typedef System::DelphiInterface<JConstants> _di_JConstants;
class DELPHICLASS TJConstants;
__interface DELPHIINTERFACE JDownloadProgressInfoClass;
typedef System::DelphiInterface<JDownloadProgressInfoClass> _di_JDownloadProgressInfoClass;
__interface DELPHIINTERFACE JDownloadProgressInfo;
typedef System::DelphiInterface<JDownloadProgressInfo> _di_JDownloadProgressInfo;
class DELPHICLASS TJDownloadProgressInfo;
__interface DELPHIINTERFACE JDownloaderClientMarshallerClass;
typedef System::DelphiInterface<JDownloaderClientMarshallerClass> _di_JDownloaderClientMarshallerClass;
__interface DELPHIINTERFACE JDownloaderClientMarshaller;
typedef System::DelphiInterface<JDownloaderClientMarshaller> _di_JDownloaderClientMarshaller;
class DELPHICLASS TJDownloaderClientMarshaller;
__interface DELPHIINTERFACE JDownloaderServiceMarshallerClass;
typedef System::DelphiInterface<JDownloaderServiceMarshallerClass> _di_JDownloaderServiceMarshallerClass;
__interface DELPHIINTERFACE JDownloaderServiceMarshaller;
typedef System::DelphiInterface<JDownloaderServiceMarshaller> _di_JDownloaderServiceMarshaller;
class DELPHICLASS TJDownloaderServiceMarshaller;
__interface DELPHIINTERFACE JHelpersClass;
typedef System::DelphiInterface<JHelpersClass> _di_JHelpersClass;
__interface DELPHIINTERFACE JHelpers;
typedef System::DelphiInterface<JHelpers> _di_JHelpers;
class DELPHICLASS TJHelpers;
__interface DELPHIINTERFACE JIDownloaderClientClass;
typedef System::DelphiInterface<JIDownloaderClientClass> _di_JIDownloaderClientClass;
__interface DELPHIINTERFACE JIDownloaderClient;
typedef System::DelphiInterface<JIDownloaderClient> _di_JIDownloaderClient;
class DELPHICLASS TJIDownloaderClient;
__interface DELPHIINTERFACE JIDownloaderServiceClass;
typedef System::DelphiInterface<JIDownloaderServiceClass> _di_JIDownloaderServiceClass;
__interface DELPHIINTERFACE JIDownloaderService;
typedef System::DelphiInterface<JIDownloaderService> _di_JIDownloaderService;
class DELPHICLASS TJIDownloaderService;
__interface DELPHIINTERFACE JIStubClass;
typedef System::DelphiInterface<JIStubClass> _di_JIStubClass;
__interface DELPHIINTERFACE JIStub;
typedef System::DelphiInterface<JIStub> _di_JIStub;
class DELPHICLASS TJIStub;
__interface DELPHIINTERFACE JNotificationLabelsClass;
typedef System::DelphiInterface<JNotificationLabelsClass> _di_JNotificationLabelsClass;
__interface DELPHIINTERFACE JNotificationLabels;
typedef System::DelphiInterface<JNotificationLabels> _di_JNotificationLabels;
class DELPHICLASS TJNotificationLabels;
__interface DELPHIINTERFACE JCustomNotificationFactoryClass;
typedef System::DelphiInterface<JCustomNotificationFactoryClass> _di_JCustomNotificationFactoryClass;
__interface DELPHIINTERFACE JCustomNotificationFactory;
typedef System::DelphiInterface<JCustomNotificationFactory> _di_JCustomNotificationFactory;
class DELPHICLASS TJCustomNotificationFactory;
__interface DELPHIINTERFACE JDownloadInfoClass;
typedef System::DelphiInterface<JDownloadInfoClass> _di_JDownloadInfoClass;
__interface DELPHIINTERFACE JDownloadInfo;
typedef System::DelphiInterface<JDownloadInfo> _di_JDownloadInfo;
class DELPHICLASS TJDownloadInfo;
__interface DELPHIINTERFACE JDownloadNotificationClass;
typedef System::DelphiInterface<JDownloadNotificationClass> _di_JDownloadNotificationClass;
__interface DELPHIINTERFACE JDownloadNotification;
typedef System::DelphiInterface<JDownloadNotification> _di_JDownloadNotification;
class DELPHICLASS TJDownloadNotification;
__interface DELPHIINTERFACE JDownloadNotification_ICustomNotificationClass;
typedef System::DelphiInterface<JDownloadNotification_ICustomNotificationClass> _di_JDownloadNotification_ICustomNotificationClass;
__interface DELPHIINTERFACE JDownloadNotification_ICustomNotification;
typedef System::DelphiInterface<JDownloadNotification_ICustomNotification> _di_JDownloadNotification_ICustomNotification;
class DELPHICLASS TJDownloadNotification_ICustomNotification;
__interface DELPHIINTERFACE JDownloadThreadClass;
typedef System::DelphiInterface<JDownloadThreadClass> _di_JDownloadThreadClass;
__interface DELPHIINTERFACE JDownloadThread;
typedef System::DelphiInterface<JDownloadThread> _di_JDownloadThread;
class DELPHICLASS TJDownloadThread;
__interface DELPHIINTERFACE JDownloaderService_GenerateSaveFileErrorClass;
typedef System::DelphiInterface<JDownloaderService_GenerateSaveFileErrorClass> _di_JDownloaderService_GenerateSaveFileErrorClass;
__interface DELPHIINTERFACE JDownloaderService_GenerateSaveFileError;
typedef System::DelphiInterface<JDownloaderService_GenerateSaveFileError> _di_JDownloaderService_GenerateSaveFileError;
class DELPHICLASS TJDownloaderService_GenerateSaveFileError;
__interface DELPHIINTERFACE JDownloadsDBClass;
typedef System::DelphiInterface<JDownloadsDBClass> _di_JDownloadsDBClass;
__interface DELPHIINTERFACE JDownloadsDB;
typedef System::DelphiInterface<JDownloadsDB> _di_JDownloadsDB;
class DELPHICLASS TJDownloadsDB;
__interface DELPHIINTERFACE JDownloadsDB_DownloadColumnsClass;
typedef System::DelphiInterface<JDownloadsDB_DownloadColumnsClass> _di_JDownloadsDB_DownloadColumnsClass;
__interface DELPHIINTERFACE JDownloadsDB_DownloadColumns;
typedef System::DelphiInterface<JDownloadsDB_DownloadColumns> _di_JDownloadsDB_DownloadColumns;
class DELPHICLASS TJDownloadsDB_DownloadColumns;
__interface DELPHIINTERFACE JDownloadsDB_MetadataColumnsClass;
typedef System::DelphiInterface<JDownloadsDB_MetadataColumnsClass> _di_JDownloadsDB_MetadataColumnsClass;
__interface DELPHIINTERFACE JDownloadsDB_MetadataColumns;
typedef System::DelphiInterface<JDownloadsDB_MetadataColumns> _di_JDownloadsDB_MetadataColumns;
class DELPHICLASS TJDownloadsDB_MetadataColumns;
__interface DELPHIINTERFACE JHttpDateTimeClass;
typedef System::DelphiInterface<JHttpDateTimeClass> _di_JHttpDateTimeClass;
__interface DELPHIINTERFACE JHttpDateTime;
typedef System::DelphiInterface<JHttpDateTime> _di_JHttpDateTime;
class DELPHICLASS TJHttpDateTime;
__interface DELPHIINTERFACE JV14CustomNotificationClass;
typedef System::DelphiInterface<JV14CustomNotificationClass> _di_JV14CustomNotificationClass;
__interface DELPHIINTERFACE JV14CustomNotification;
typedef System::DelphiInterface<JV14CustomNotification> _di_JV14CustomNotification;
class DELPHICLASS TJV14CustomNotification;
__interface DELPHIINTERFACE JV3CustomNotificationClass;
typedef System::DelphiInterface<JV3CustomNotificationClass> _di_JV3CustomNotificationClass;
__interface DELPHIINTERFACE JV3CustomNotification;
typedef System::DelphiInterface<JV3CustomNotification> _di_JV3CustomNotification;
class DELPHICLASS TJV3CustomNotification;
struct TDownloadProgressInfo;
struct TApkFileInfo;
class DELPHICLASS TApkExpansion;
class DELPHICLASS TObb;
class DELPHICLASS TNativeDownloader;
class DELPHICLASS TUIThread;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{E26ADD72-3ABD-4FEA-BED4-CC8CC3B16D49}") JAPEZProviderClass  : public Androidapi::Jni::Graphicscontentviewtext::JContentProviderClass 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetALL_FIELDS() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl _GetALL_FIELDS_INT() = 0 ;
	virtual int __cdecl _GetCOMPLEN_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCOMPRESSEDLEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCOMPRESSIONTYPE() = 0 ;
	virtual int __cdecl _GetCOMPTYPE_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCRC32() = 0 ;
	virtual int __cdecl _GetCRC_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFILEID() = 0 ;
	virtual int __cdecl _GetFILEID_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFILENAME() = 0 ;
	virtual int __cdecl _GetFILENAME_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMODIFICATION() = 0 ;
	virtual int __cdecl _GetMOD_IDX() = 0 ;
	virtual int __cdecl _GetUNCOMPLEN_IDX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetUNCOMPRESSEDLEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetZIPFILE() = 0 ;
	virtual int __cdecl _GetZIPFILE_IDX() = 0 ;
	HIDESBASE virtual _di_JAPEZProvider __cdecl init() = 0 ;
	__property Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* ALL_FIELDS = {read=_GetALL_FIELDS};
	__property Androidapi::Jnibridge::TJavaArray__1<int>* ALL_FIELDS_INT = {read=_GetALL_FIELDS_INT};
	__property int COMPLEN_IDX = {read=_GetCOMPLEN_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString COMPRESSEDLEN = {read=_GetCOMPRESSEDLEN};
	__property Androidapi::Jni::Javatypes::_di_JString COMPRESSIONTYPE = {read=_GetCOMPRESSIONTYPE};
	__property int COMPTYPE_IDX = {read=_GetCOMPTYPE_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString CRC32 = {read=_GetCRC32};
	__property int CRC_IDX = {read=_GetCRC_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString FILEID = {read=_GetFILEID};
	__property int FILEID_IDX = {read=_GetFILEID_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString FILENAME = {read=_GetFILENAME};
	__property int FILENAME_IDX = {read=_GetFILENAME_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString MODIFICATION = {read=_GetMODIFICATION};
	__property int MOD_IDX = {read=_GetMOD_IDX};
	__property int UNCOMPLEN_IDX = {read=_GetUNCOMPLEN_IDX};
	__property Androidapi::Jni::Javatypes::_di_JString UNCOMPRESSEDLEN = {read=_GetUNCOMPRESSEDLEN};
	__property Androidapi::Jni::Javatypes::_di_JString ZIPFILE = {read=_GetZIPFILE};
	__property int ZIPFILE_IDX = {read=_GetZIPFILE_IDX};
};

__interface  INTERFACE_UUID("{3B3FD75B-DED0-4A72-B479-FF9B97236122}") JAPEZProvider  : public Androidapi::Jni::Graphicscontentviewtext::JContentProvider 
{
	HIDESBASE virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Graphicscontentviewtext::_di_JContentProviderResult>* __cdecl applyBatch(Androidapi::Jni::Javatypes::_di_JArrayList operations) = 0 ;
	HIDESBASE virtual int __cdecl Delete(Androidapi::Jni::Net::_di_Jnet_Uri arg0, Androidapi::Jni::Javatypes::_di_JString arg1, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* arg2) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAuthority() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getType(Androidapi::Jni::Net::_di_Jnet_Uri uri) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Net::_di_Jnet_Uri __cdecl insert(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues values) = 0 ;
	HIDESBASE virtual bool __cdecl onCreate() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAssetFileDescriptor __cdecl openAssetFile(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JString mode) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelFileDescriptor __cdecl openFile(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Javatypes::_di_JString mode) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Graphicscontentviewtext::_di_JCursor __cdecl query(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* projection, Androidapi::Jni::Javatypes::_di_JString selection, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* selectionArgs, Androidapi::Jni::Javatypes::_di_JString sortOrder) = 0 ;
	HIDESBASE virtual int __cdecl update(Androidapi::Jni::Net::_di_Jnet_Uri uri, Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues values, Androidapi::Jni::Javatypes::_di_JString selection, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* selectionArgs) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAPEZProvider : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPEZProviderClass,_di_JAPEZProvider>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPEZProviderClass,_di_JAPEZProvider> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAPEZProvider() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPEZProviderClass,_di_JAPEZProvider>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAPEZProvider() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B82F8FBA-AE89-402F-A482-D5EA88561B45}") JAPKExpansionSupportClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JAPKExpansionSupport __cdecl init() = 0 ;
	virtual _di_JZipResourceFile __cdecl getAPKExpansionZipFile(Androidapi::Jni::Graphicscontentviewtext::_di_JContext ctx, int mainVersion, int patchVersion) = 0 ;
	virtual _di_JZipResourceFile __cdecl getResourceZipFile(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* expansionFiles) = 0 ;
};

__interface  INTERFACE_UUID("{062184CE-7401-498E-BD7C-1929B9EFC7F2}") JAPKExpansionSupport  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAPKExpansionSupport : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionSupportClass,_di_JAPKExpansionSupport>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionSupportClass,_di_JAPKExpansionSupport> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAPKExpansionSupport() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAPKExpansionSupportClass,_di_JAPKExpansionSupport>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAPKExpansionSupport() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{69F1BD88-F6CC-45B5-8FD2-A34D003C1642}") JZipResourceFileClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JZipResourceFile __cdecl init(Androidapi::Jni::Javatypes::_di_JString zipFileName) = 0 ;
};

__interface  INTERFACE_UUID("{84984AFD-9A67-4A07-9660-921BC4C7B1CF}") JZipResourceFile  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JHashMap __cdecl _GetmZipFiles() = 0 ;
	virtual void __cdecl _SetmZipFiles(Androidapi::Jni::Javatypes::_di_JHashMap Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JZipResourceFile_ZipEntryRO>* __cdecl getAllEntries() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAssetFileDescriptor __cdecl getAssetFileDescriptor(Androidapi::Jni::Javatypes::_di_JString assetPath) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getInputStream(Androidapi::Jni::Javatypes::_di_JString assetPath) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JHashMap mZipFiles = {read=_GetmZipFiles, write=_SetmZipFiles};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJZipResourceFile : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFileClass,_di_JZipResourceFile>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFileClass,_di_JZipResourceFile> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJZipResourceFile() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFileClass,_di_JZipResourceFile>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJZipResourceFile() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{437CD8DF-9215-4B25-A6A1-D41E4948F191}") JZipResourceFile_ZipEntryROClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JZipResourceFile_ZipEntryRO __cdecl init(Androidapi::Jni::Javatypes::_di_JString zipFileName, Androidapi::Jni::Javatypes::_di_JFile file_, Androidapi::Jni::Javatypes::_di_JString fileName) = 0 ;
};

__interface  INTERFACE_UUID("{F0695EE3-93F6-479E-B462-3A927EF83EC2}") JZipResourceFile_ZipEntryRO  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual __int64 __cdecl _GetmCRC32() = 0 ;
	virtual void __cdecl _SetmCRC32(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GetmCompressedLength() = 0 ;
	virtual void __cdecl _SetmCompressedLength(__int64 Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl _GetmFile() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmFileName() = 0 ;
	virtual __int64 __cdecl _GetmLocalHdrOffset() = 0 ;
	virtual void __cdecl _SetmLocalHdrOffset(__int64 Value) = 0 ;
	virtual int __cdecl _GetmMethod() = 0 ;
	virtual void __cdecl _SetmMethod(int Value) = 0 ;
	virtual __int64 __cdecl _GetmOffset() = 0 ;
	virtual void __cdecl _SetmOffset(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GetmUncompressedLength() = 0 ;
	virtual void __cdecl _SetmUncompressedLength(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GetmWhenModified() = 0 ;
	virtual void __cdecl _SetmWhenModified(__int64 Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmZipFileName() = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JAssetFileDescriptor __cdecl getAssetFileDescriptor() = 0 ;
	virtual __int64 __cdecl getOffset() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getZipFile() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getZipFileName() = 0 ;
	virtual bool __cdecl isUncompressed() = 0 ;
	virtual void __cdecl setOffsetFromFile(Androidapi::Jni::Javatypes::_di_JRandomAccessFile f, Androidapi::Jni::Javatypes::_di_JByteBuffer buf) = 0 ;
	__property __int64 mCRC32 = {read=_GetmCRC32, write=_SetmCRC32};
	__property __int64 mCompressedLength = {read=_GetmCompressedLength, write=_SetmCompressedLength};
	__property Androidapi::Jni::Javatypes::_di_JFile mFile = {read=_GetmFile};
	__property Androidapi::Jni::Javatypes::_di_JString mFileName = {read=_GetmFileName};
	__property __int64 mLocalHdrOffset = {read=_GetmLocalHdrOffset, write=_SetmLocalHdrOffset};
	__property int mMethod = {read=_GetmMethod, write=_SetmMethod};
	__property __int64 mOffset = {read=_GetmOffset, write=_SetmOffset};
	__property __int64 mUncompressedLength = {read=_GetmUncompressedLength, write=_SetmUncompressedLength};
	__property __int64 mWhenModified = {read=_GetmWhenModified, write=_SetmWhenModified};
	__property Androidapi::Jni::Javatypes::_di_JString mZipFileName = {read=_GetmZipFileName};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJZipResourceFile_ZipEntryRO : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFile_ZipEntryROClass,_di_JZipResourceFile_ZipEntryRO>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFile_ZipEntryROClass,_di_JZipResourceFile_ZipEntryRO> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJZipResourceFile_ZipEntryRO() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JZipResourceFile_ZipEntryROClass,_di_JZipResourceFile_ZipEntryRO>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJZipResourceFile_ZipEntryRO() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C65FE68B-E670-412D-BC27-63F090AA06B2}") JApkAlarmReceiverClass  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiverClass 
{
	HIDESBASE virtual _di_JApkAlarmReceiver __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{81DBEE4F-5150-4C40-A733-6004BF9A200A}") JApkAlarmReceiver  : public Androidapi::Jni::Graphicscontentviewtext::JBroadcastReceiver 
{
	HIDESBASE virtual void __cdecl onReceive(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkAlarmReceiver : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkAlarmReceiverClass,_di_JApkAlarmReceiver>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkAlarmReceiverClass,_di_JApkAlarmReceiver> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkAlarmReceiver() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkAlarmReceiverClass,_di_JApkAlarmReceiver>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkAlarmReceiver() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5872D446-A340-44F6-A11B-0DC74BC28120}") JApkBaseDownloaderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JApkBaseDownloader __cdecl init(Androidapi::Jni::Javatypes::_di_JString publicKey, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* salt, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* apks) = 0 ;
};

__interface  INTERFACE_UUID("{EE973BF3-2B7A-456A-A600-2A997B6CC81F}") JApkBaseDownloader  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl setNotificationLabels(Androidapi::Jni::Javatypes::_di_JHashMap labels) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkBaseDownloader : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkBaseDownloaderClass,_di_JApkBaseDownloader>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkBaseDownloaderClass,_di_JApkBaseDownloader> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkBaseDownloader() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkBaseDownloaderClass,_di_JApkBaseDownloader>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkBaseDownloader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{16A14F76-6178-4719-8138-47AD32E513F5}") JApkDownloaderClientClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JApkDownloaderClient __cdecl init(Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* xAPKS, _di_JApkDownloaderListener downloaderListener) = 0 ;
};

__interface  INTERFACE_UUID("{2890DE6A-89C6-4AFC-AD89-A27DA56B3DA1}") JApkDownloaderClient  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JIStub __cdecl getDownloaderClientStub() = 0 ;
	virtual _di_JIDownloaderService __cdecl getDownloaderService() = 0 ;
	virtual bool __cdecl launch() = 0 ;
	virtual void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress) = 0 ;
	virtual void __cdecl onDownloadStateChanged(int newState) = 0 ;
	virtual void __cdecl onServiceConnected(Androidapi::Jni::Os::_di_JMessenger m) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkDownloaderClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderClientClass,_di_JApkDownloaderClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderClientClass,_di_JApkDownloaderClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkDownloaderClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderClientClass,_di_JApkDownloaderClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkDownloaderClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ADA57B92-707B-469B-90B7-34D3BD123EB4}") JApkDownloaderListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{782B8878-9306-4A8C-A2FC-093A82144484}") JApkDownloaderListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress) = 0 ;
	virtual void __cdecl onDownloadStateChanged(int newState) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkDownloaderListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderListenerClass,_di_JApkDownloaderListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderListenerClass,_di_JApkDownloaderListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkDownloaderListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderListenerClass,_di_JApkDownloaderListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkDownloaderListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{847A1962-3CB2-4980-B2AF-F1D559D224F7}") JCustomIntentServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	HIDESBASE virtual _di_JCustomIntentService __cdecl init(Androidapi::Jni::Javatypes::_di_JString paramString) = 0 ;
};

__interface  INTERFACE_UUID("{BA491650-C614-4C1C-836A-A8B0BA7DBCF2}") JCustomIntentService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent paramIntent) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	HIDESBASE virtual void __cdecl onStart(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent paramIntent, int startId) = 0 ;
	HIDESBASE virtual int __cdecl onStartCommand(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent paramIntent, int flags, int startId) = 0 ;
	virtual void __cdecl setIntentRedelivery(bool enabled) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCustomIntentService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomIntentServiceClass,_di_JCustomIntentService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomIntentServiceClass,_di_JCustomIntentService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCustomIntentService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomIntentServiceClass,_di_JCustomIntentService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCustomIntentService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2F4F734A-5053-469C-A97C-2BD2AF8D24BF}") JDownloaderServiceClass  : public JCustomIntentServiceClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DOWNLOADS_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DOWNLOAD_COMPLETE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DOWNLOAD_STATUS() = 0 ;
	virtual int __cdecl _GetDOWNLOAD_REQUIRED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_FILE_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_IS_WIFI_REQUIRED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MESSAGE_HANDLER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PACKAGE_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PENDING_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATUS_CURRENT_FILE_SIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATUS_CURRENT_PROGRESS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATUS_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATUS_TOTAL_PROGRESS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATUS_TOTAL_SIZE() = 0 ;
	virtual int __cdecl _GetLVL_CHECK_REQUIRED() = 0 ;
	virtual int __cdecl _GetNETWORK_CANNOT_USE_ROAMING() = 0 ;
	virtual int __cdecl _GetNETWORK_MOBILE() = 0 ;
	virtual int __cdecl _GetNETWORK_NO_CONNECTION() = 0 ;
	virtual int __cdecl _GetNETWORK_OK() = 0 ;
	virtual int __cdecl _GetNETWORK_RECOMMENDED_UNUSABLE_DUE_TO_SIZE() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_DISALLOWED_BY_REQUESTOR() = 0 ;
	virtual int __cdecl _GetNETWORK_UNUSABLE_DUE_TO_SIZE() = 0 ;
	virtual int __cdecl _GetNETWORK_WIFI() = 0 ;
	virtual int __cdecl _GetNO_DOWNLOAD_REQUIRED() = 0 ;
	virtual int __cdecl _GetSTATUS_CANNOT_RESUME() = 0 ;
	virtual int __cdecl _GetSTATUS_FILE_ALREADY_EXISTS_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_FILE_DELIVERED_INCORRECTLY() = 0 ;
	virtual int __cdecl _GetSTATUS_FORBIDDEN() = 0 ;
	virtual int __cdecl _GetSTATUS_PAUSED_BY_APP() = 0 ;
	virtual int __cdecl _GetSTATUS_PENDING() = 0 ;
	virtual int __cdecl _GetSTATUS_QUEUED_FOR_WIFI() = 0 ;
	virtual int __cdecl _GetSTATUS_QUEUED_FOR_WIFI_OR_CELLULAR_PERMISSION() = 0 ;
	virtual int __cdecl _GetSTATUS_RUNNING() = 0 ;
	virtual int __cdecl _GetSTATUS_UNKNOWN_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_WAITING_FOR_NETWORK() = 0 ;
	virtual int __cdecl _GetSTATUS_WAITING_TO_RETRY() = 0 ;
	HIDESBASE virtual _di_JDownloaderService __cdecl init() = 0 ;
	virtual bool __cdecl isStatusClientError(int status) = 0 ;
	virtual bool __cdecl isStatusCompleted(int status) = 0 ;
	virtual bool __cdecl isStatusError(int status) = 0 ;
	virtual bool __cdecl isStatusInformational(int status) = 0 ;
	virtual bool __cdecl isStatusServerError(int status) = 0 ;
	virtual bool __cdecl isStatusSuccess(int status) = 0 ;
	virtual int __cdecl startDownloadServiceIfRequired(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Javatypes::_di_Jlang_Class serviceClass) = 0 /* overload */;
	virtual int __cdecl startDownloadServiceIfRequired(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::App::_di_JPendingIntent pendingIntent, Androidapi::Jni::Javatypes::_di_Jlang_Class serviceClass) = 0 /* overload */;
	virtual int __cdecl startDownloadServiceIfRequired(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::App::_di_JPendingIntent pendingIntent, Androidapi::Jni::Javatypes::_di_JString classPackage, Androidapi::Jni::Javatypes::_di_JString className) = 0 /* overload */;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DOWNLOADS_CHANGED = {read=_GetACTION_DOWNLOADS_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DOWNLOAD_COMPLETE = {read=_GetACTION_DOWNLOAD_COMPLETE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DOWNLOAD_STATUS = {read=_GetACTION_DOWNLOAD_STATUS};
	__property int DOWNLOAD_REQUIRED = {read=_GetDOWNLOAD_REQUIRED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_FILE_NAME = {read=_GetEXTRA_FILE_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_IS_WIFI_REQUIRED = {read=_GetEXTRA_IS_WIFI_REQUIRED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MESSAGE_HANDLER = {read=_GetEXTRA_MESSAGE_HANDLER};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PACKAGE_NAME = {read=_GetEXTRA_PACKAGE_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PENDING_INTENT = {read=_GetEXTRA_PENDING_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATUS_CURRENT_FILE_SIZE = {read=_GetEXTRA_STATUS_CURRENT_FILE_SIZE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATUS_CURRENT_PROGRESS = {read=_GetEXTRA_STATUS_CURRENT_PROGRESS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATUS_STATE = {read=_GetEXTRA_STATUS_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATUS_TOTAL_PROGRESS = {read=_GetEXTRA_STATUS_TOTAL_PROGRESS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATUS_TOTAL_SIZE = {read=_GetEXTRA_STATUS_TOTAL_SIZE};
	__property int LVL_CHECK_REQUIRED = {read=_GetLVL_CHECK_REQUIRED};
	__property int NETWORK_CANNOT_USE_ROAMING = {read=_GetNETWORK_CANNOT_USE_ROAMING};
	__property int NETWORK_MOBILE = {read=_GetNETWORK_MOBILE};
	__property int NETWORK_NO_CONNECTION = {read=_GetNETWORK_NO_CONNECTION};
	__property int NETWORK_OK = {read=_GetNETWORK_OK};
	__property int NETWORK_RECOMMENDED_UNUSABLE_DUE_TO_SIZE = {read=_GetNETWORK_RECOMMENDED_UNUSABLE_DUE_TO_SIZE};
	__property int NETWORK_TYPE_DISALLOWED_BY_REQUESTOR = {read=_GetNETWORK_TYPE_DISALLOWED_BY_REQUESTOR};
	__property int NETWORK_UNUSABLE_DUE_TO_SIZE = {read=_GetNETWORK_UNUSABLE_DUE_TO_SIZE};
	__property int NETWORK_WIFI = {read=_GetNETWORK_WIFI};
	__property int NO_DOWNLOAD_REQUIRED = {read=_GetNO_DOWNLOAD_REQUIRED};
	__property int STATUS_CANNOT_RESUME = {read=_GetSTATUS_CANNOT_RESUME};
	__property int STATUS_FILE_ALREADY_EXISTS_ERROR = {read=_GetSTATUS_FILE_ALREADY_EXISTS_ERROR};
	__property int STATUS_FILE_DELIVERED_INCORRECTLY = {read=_GetSTATUS_FILE_DELIVERED_INCORRECTLY};
	__property int STATUS_FORBIDDEN = {read=_GetSTATUS_FORBIDDEN};
	__property int STATUS_PAUSED_BY_APP = {read=_GetSTATUS_PAUSED_BY_APP};
	__property int STATUS_PENDING = {read=_GetSTATUS_PENDING};
	__property int STATUS_QUEUED_FOR_WIFI = {read=_GetSTATUS_QUEUED_FOR_WIFI};
	__property int STATUS_QUEUED_FOR_WIFI_OR_CELLULAR_PERMISSION = {read=_GetSTATUS_QUEUED_FOR_WIFI_OR_CELLULAR_PERMISSION};
	__property int STATUS_RUNNING = {read=_GetSTATUS_RUNNING};
	__property int STATUS_UNKNOWN_ERROR = {read=_GetSTATUS_UNKNOWN_ERROR};
	__property int STATUS_WAITING_FOR_NETWORK = {read=_GetSTATUS_WAITING_FOR_NETWORK};
	__property int STATUS_WAITING_TO_RETRY = {read=_GetSTATUS_WAITING_TO_RETRY};
};

__interface  INTERFACE_UUID("{2DFE6D5F-4CC2-4712-B66C-A12CBB7116D1}") JDownloaderService  : public JCustomIntentService 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl generateSaveFile(Androidapi::Jni::Javatypes::_di_JString filename, __int64 filesize) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl generateTempSaveFileName(Androidapi::Jni::Javatypes::_di_JString fileName) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAlarmReceiverClassName() = 0 ;
	virtual int __cdecl getControl() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLogMessageForNetworkError(int networkError) = 0 ;
	virtual int __cdecl getNetworkAvailabilityState(_di_JDownloadsDB db) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPublicKey() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getSALT() = 0 ;
	virtual int __cdecl getStatus() = 0 ;
	virtual bool __cdecl handleFileUpdated(_di_JDownloadsDB db, int index, Androidapi::Jni::Javatypes::_di_JString filename, __int64 fileSize) = 0 ;
	virtual bool __cdecl isWiFi() = 0 ;
	virtual void __cdecl notifyUpdateBytes(__int64 totalBytesSoFar) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent paramIntent) = 0 ;
	virtual void __cdecl onClientUpdated(Androidapi::Jni::Os::_di_JMessenger clientMessenger) = 0 ;
	HIDESBASE virtual void __cdecl onCreate() = 0 ;
	HIDESBASE virtual void __cdecl onDestroy() = 0 ;
	virtual void __cdecl requestAbortDownload() = 0 ;
	virtual void __cdecl requestContinueDownload() = 0 ;
	virtual void __cdecl requestDownloadStatus() = 0 ;
	virtual void __cdecl requestPauseDownload() = 0 ;
	virtual void __cdecl setDownloadFlags(int flags) = 0 ;
	virtual void __cdecl updateLVL(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceClass,_di_JDownloaderService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceClass,_di_JDownloaderService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceClass,_di_JDownloaderService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C34557AF-1EA4-4EEF-A3A0-74886F5F57E4}") JApkDownloaderServiceClass  : public JDownloaderServiceClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetBASE64_PUBLIC_KEY() = 0 ;
	virtual void __cdecl _SetBASE64_PUBLIC_KEY(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetSALT() = 0 ;
	virtual void __cdecl _SetSALT(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* __cdecl _GetxAPKS() = 0 ;
	virtual void __cdecl _SetxAPKS(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* Value) = 0 ;
	HIDESBASE virtual _di_JApkDownloaderService __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString BASE64_PUBLIC_KEY = {read=_GetBASE64_PUBLIC_KEY, write=_SetBASE64_PUBLIC_KEY};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* SALT = {read=_GetSALT, write=_SetSALT};
	__property Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* xAPKS = {read=_GetxAPKS, write=_SetxAPKS};
};

__interface  INTERFACE_UUID("{5441EB6E-2512-44F1-A240-45B5B751E161}") JApkDownloaderService  : public JDownloaderService 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAlarmReceiverClassName() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPublicKey() = 0 ;
	HIDESBASE virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getSALT() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkDownloaderService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderServiceClass,_di_JApkDownloaderService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderServiceClass,_di_JApkDownloaderService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkDownloaderService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkDownloaderServiceClass,_di_JApkDownloaderService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkDownloaderService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{639B498E-2CC7-4675-B82B-D96A60BEE247}") JApkFileInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JApkFileInfo __cdecl init(bool isMain, int fileVersion, __int64 fileSize, Androidapi::Jni::Javatypes::_di_JString encriptKey) = 0 ;
};

__interface  INTERFACE_UUID("{57422024-F0E6-43BA-9A35-79F369A7A0A9}") JApkFileInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmEncriptKey() = 0 ;
	virtual __int64 __cdecl _GetmFileSize() = 0 ;
	virtual int __cdecl _GetmFileVersion() = 0 ;
	virtual bool __cdecl _GetmIsMain() = 0 ;
	virtual _di_JObb __cdecl getObb(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString mEncriptKey = {read=_GetmEncriptKey};
	__property __int64 mFileSize = {read=_GetmFileSize};
	__property int mFileVersion = {read=_GetmFileVersion};
	__property bool mIsMain = {read=_GetmIsMain};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkFileInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFileInfoClass,_di_JApkFileInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFileInfoClass,_di_JApkFileInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkFileInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFileInfoClass,_di_JApkFileInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkFileInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF77F727-F74E-4B87-91F8-0E1FDDF42F2C}") JApkFilesHelperClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JApkFilesHelper __cdecl init() = 0 ;
	virtual bool __cdecl areExpansionFilesDelivered(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* xAPKS) = 0 /* overload */;
	virtual bool __cdecl areExpansionFilesDelivered(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* xAPKS, bool deleteFileOnMismatch) = 0 /* overload */;
	virtual bool __cdecl doesExpansionFileExist(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, bool isMain, int fileVersion, __int64 fileSize, bool deleteFileOnMismatch) = 0 ;
	virtual bool __cdecl doesFileExist(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Javatypes::_di_JString fileName, __int64 fileSize, bool deleteFileOnMismatch) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExpansionFileName(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, bool isMain, int fileVersion) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExpansionFilePath(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, bool isMain, int fileVersion) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMountedObbPath(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Javatypes::_di_JString filePath) = 0 ;
};

__interface  INTERFACE_UUID("{6765E9A5-5B12-43CB-B883-F40D37C87F16}") JApkFilesHelper  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJApkFilesHelper : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFilesHelperClass,_di_JApkFilesHelper>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFilesHelperClass,_di_JApkFilesHelper> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJApkFilesHelper() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JApkFilesHelperClass,_di_JApkFilesHelper>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJApkFilesHelper() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{9C53DC45-B0E1-427F-A0F5-0E5C22B9369C}") JObbClass  : public Androidapi::Jni::Os::JOnObbStateChangeListenerClass 
{
	HIDESBASE virtual _di_JObb __cdecl init(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, _di_JApkFileInfo a) = 0 ;
};

__interface  INTERFACE_UUID("{4CBDC758-C2BC-4247-A342-8C23905A5CCF}") JObb  : public Androidapi::Jni::Os::JOnObbStateChangeListener 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMountedObbPath() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPath() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getResourcePath(Androidapi::Jni::Javatypes::_di_JString filePath) = 0 ;
	virtual bool __cdecl isMounted() = 0 ;
	virtual void __cdecl mount() = 0 ;
	HIDESBASE virtual void __cdecl onObbStateChange(Androidapi::Jni::Javatypes::_di_JString path, int state) = 0 ;
	virtual void __cdecl setListener(_di_JObb_ObbListener listener) = 0 ;
	virtual void __cdecl umount(bool force) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJObb : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObbClass,_di_JObb>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObbClass,_di_JObb> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJObb() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObbClass,_di_JObb>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJObb() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C4E05674-A415-484C-84BA-B3F6DCFEA0A1}") JObb_ObbListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{710A8D6A-4E6B-44A7-A552-4BFCE8939BBE}") JObb_ObbListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onObbStateChange(Androidapi::Jni::Javatypes::_di_JString path, int state) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJObb_ObbListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObb_ObbListenerClass,_di_JObb_ObbListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObb_ObbListenerClass,_di_JObb_ObbListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJObb_ObbListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JObb_ObbListenerClass,_di_JObb_ObbListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJObb_ObbListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{23019048-ECDC-412F-9492-7AEEC11FF854}") JDownloaderActivityClass  : public Androidapi::Jni::App::JActivityClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTITLE() = 0 ;
	virtual void __cdecl _SetTITLE(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual bool __cdecl _GetisAlive() = 0 ;
	virtual void __cdecl _SetisAlive(bool Value) = 0 ;
	virtual bool __cdecl _GetmEnabled() = 0 ;
	virtual void __cdecl _SetmEnabled(bool Value) = 0 ;
	HIDESBASE virtual _di_JDownloaderActivity __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString TITLE = {read=_GetTITLE, write=_SetTITLE};
	__property bool isAlive = {read=_GetisAlive, write=_SetisAlive};
	__property bool mEnabled = {read=_GetmEnabled, write=_SetmEnabled};
};

__interface  INTERFACE_UUID("{3ED370EB-155B-4FC5-9C26-0E27F7D52A7F}") JDownloaderActivity  : public Androidapi::Jni::App::JActivity 
{
	HIDESBASE virtual void __cdecl onBackPressed() = 0 ;
	HIDESBASE virtual void __cdecl onCreate(Androidapi::Jni::Os::_di_JBundle savedInstanceState) = 0 ;
	virtual void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress) = 0 ;
	virtual void __cdecl onDownloadStateChanged(int newState) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderActivity : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityClass,_di_JDownloaderActivity>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityClass,_di_JDownloaderActivity> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderActivity() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityClass,_di_JDownloaderActivity>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderActivity() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{613A6437-5781-4281-8BA0-DCFF254B93D7}") JDownloaderActivityConfigClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getapp_name() = 0 ;
	virtual void __cdecl _Setapp_name(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetrequestCode() = 0 ;
	virtual void __cdecl _SetrequestCode(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_cancel() = 0 ;
	virtual void __cdecl _Settext_button_cancel(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_cancel_verify() = 0 ;
	virtual void __cdecl _Settext_button_cancel_verify(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_pause() = 0 ;
	virtual void __cdecl _Settext_button_pause(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_resume() = 0 ;
	virtual void __cdecl _Settext_button_resume(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_resume_cellular() = 0 ;
	virtual void __cdecl _Settext_button_resume_cellular(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_button_wifi_settings() = 0 ;
	virtual void __cdecl _Settext_button_wifi_settings(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_cancel() = 0 ;
	virtual void __cdecl _Settext_cancel(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_ok() = 0 ;
	virtual void __cdecl _Settext_ok(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_paused_cellular() = 0 ;
	virtual void __cdecl _Settext_paused_cellular(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_paused_cellular_2() = 0 ;
	virtual void __cdecl _Settext_paused_cellular_2(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_validation_complete() = 0 ;
	virtual void __cdecl _Settext_validation_complete(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_validation_failed() = 0 ;
	virtual void __cdecl _Settext_validation_failed(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettext_verifying_download() = 0 ;
	virtual void __cdecl _Settext_verifying_download(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettitle() = 0 ;
	virtual void __cdecl _Settitle(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	HIDESBASE virtual _di_JDownloaderActivityConfig __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString app_name = {read=_Getapp_name, write=_Setapp_name};
	__property Androidapi::Jni::Javatypes::_di_JString requestCode = {read=_GetrequestCode, write=_SetrequestCode};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_cancel = {read=_Gettext_button_cancel, write=_Settext_button_cancel};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_cancel_verify = {read=_Gettext_button_cancel_verify, write=_Settext_button_cancel_verify};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_pause = {read=_Gettext_button_pause, write=_Settext_button_pause};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_resume = {read=_Gettext_button_resume, write=_Settext_button_resume};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_resume_cellular = {read=_Gettext_button_resume_cellular, write=_Settext_button_resume_cellular};
	__property Androidapi::Jni::Javatypes::_di_JString text_button_wifi_settings = {read=_Gettext_button_wifi_settings, write=_Settext_button_wifi_settings};
	__property Androidapi::Jni::Javatypes::_di_JString text_cancel = {read=_Gettext_cancel, write=_Settext_cancel};
	__property Androidapi::Jni::Javatypes::_di_JString text_ok = {read=_Gettext_ok, write=_Settext_ok};
	__property Androidapi::Jni::Javatypes::_di_JString text_paused_cellular = {read=_Gettext_paused_cellular, write=_Settext_paused_cellular};
	__property Androidapi::Jni::Javatypes::_di_JString text_paused_cellular_2 = {read=_Gettext_paused_cellular_2, write=_Settext_paused_cellular_2};
	__property Androidapi::Jni::Javatypes::_di_JString text_validation_complete = {read=_Gettext_validation_complete, write=_Settext_validation_complete};
	__property Androidapi::Jni::Javatypes::_di_JString text_validation_failed = {read=_Gettext_validation_failed, write=_Settext_validation_failed};
	__property Androidapi::Jni::Javatypes::_di_JString text_verifying_download = {read=_Gettext_verifying_download, write=_Settext_verifying_download};
	__property Androidapi::Jni::Javatypes::_di_JString title = {read=_Gettitle, write=_Settitle};
};

__interface  INTERFACE_UUID("{71310121-4259-4779-95DA-425B21F4DF9C}") JDownloaderActivityConfig  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderActivityConfig : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityConfigClass,_di_JDownloaderActivityConfig>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityConfigClass,_di_JDownloaderActivityConfig> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderActivityConfig() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityConfigClass,_di_JDownloaderActivityConfig>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderActivityConfig() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DA7CEE58-DE43-462C-85ED-028F530527D7}") JDownloaderActivityLauncherClass  : public JApkBaseDownloaderClass 
{
	HIDESBASE virtual _di_JDownloaderActivityLauncher __cdecl init(Androidapi::Jni::Javatypes::_di_JString publicKey, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* salt, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* apks) = 0 ;
};

__interface  INTERFACE_UUID("{CD906884-35CF-4556-AD44-63994C47E721}") JDownloaderActivityLauncher  : public JApkBaseDownloader 
{
	virtual bool __cdecl launch(Androidapi::Jni::App::_di_JActivity activity, int requestCode) = 0 ;
	virtual void __cdecl setActivityEnabled(bool enable) = 0 ;
	virtual void __cdecl setDownloaderLabels(Androidapi::Jni::Javatypes::_di_JHashMap labels) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderActivityLauncher : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityLauncherClass,_di_JDownloaderActivityLauncher>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityLauncherClass,_di_JDownloaderActivityLauncher> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderActivityLauncher() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderActivityLauncherClass,_di_JDownloaderActivityLauncher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderActivityLauncher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{CD90EE03-C9A8-4115-ADCA-97E7B23FB76B}") JNativeDownloaderLauncherClass  : public JApkBaseDownloaderClass 
{
	HIDESBASE virtual _di_JNativeDownloaderLauncher __cdecl init(Androidapi::Jni::Javatypes::_di_JString publicKey, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* salt, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JApkFileInfo>* apks) = 0 ;
};

__interface  INTERFACE_UUID("{4A21AA69-7067-42A4-BA61-37A7A43A23BA}") JNativeDownloaderLauncher  : public JApkBaseDownloader 
{
	virtual void __cdecl connect(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	virtual void __cdecl disconnect(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	virtual _di_JIStub __cdecl getDownloaderClientStup() = 0 ;
	virtual _di_JIDownloaderService __cdecl getDownloaderService() = 0 ;
	virtual bool __cdecl launch(Androidapi::Jni::App::_di_JActivity activity, _di_JApkDownloaderListener listener) = 0 ;
	virtual void __cdecl requestAbortDownload() = 0 ;
	virtual void __cdecl requestContinueDownload() = 0 ;
	virtual void __cdecl requestPauseDownload() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNativeDownloaderLauncher : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeDownloaderLauncherClass,_di_JNativeDownloaderLauncher>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeDownloaderLauncherClass,_di_JNativeDownloaderLauncher> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNativeDownloaderLauncher() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNativeDownloaderLauncherClass,_di_JNativeDownloaderLauncher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNativeDownloaderLauncher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BAD49A84-76B7-441E-840A-75BFA37F76AE}") JConstantsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_HIDE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_LIST() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_OPEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_RETRY() = 0 ;
	virtual __int64 __cdecl _GetACTIVE_THREAD_WATCHDOG() = 0 ;
	virtual int __cdecl _GetBUFFER_SIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDEFAULT_USER_AGENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXP_PATH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFILENAME_SEQUENCE_SEPARATOR() = 0 ;
	virtual bool __cdecl _GetLOGV() = 0 ;
	virtual bool __cdecl _GetLOGVV() = 0 ;
	virtual bool __cdecl _GetLOGX() = 0 ;
	virtual int __cdecl _GetMAX_DOWNLOADS() = 0 ;
	virtual int __cdecl _GetMAX_REDIRECTS() = 0 ;
	virtual int __cdecl _GetMAX_RETRIES() = 0 ;
	virtual int __cdecl _GetMAX_RETRY_AFTER() = 0 ;
	virtual int __cdecl _GetMIN_ARTIFICIAL_ERROR_STATUS() = 0 ;
	virtual int __cdecl _GetMIN_PROGRESS_STEP() = 0 ;
	virtual __int64 __cdecl _GetMIN_PROGRESS_TIME() = 0 ;
	virtual int __cdecl _GetMIN_RETRY_AFTER() = 0 ;
	virtual int __cdecl _GetRETRY_FIRST_DELAY() = 0 ;
	virtual int __cdecl _GetSTATUS_BAD_REQUEST() = 0 ;
	virtual int __cdecl _GetSTATUS_CANCELED() = 0 ;
	virtual int __cdecl _GetSTATUS_CANNOT_RESUME() = 0 ;
	virtual int __cdecl _GetSTATUS_DEVICE_NOT_FOUND_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_FILE_ALREADY_EXISTS_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_FILE_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_HTTP_DATA_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_HTTP_EXCEPTION() = 0 ;
	virtual int __cdecl _GetSTATUS_INSUFFICIENT_SPACE_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_LENGTH_REQUIRED() = 0 ;
	virtual int __cdecl _GetSTATUS_NOT_ACCEPTABLE() = 0 ;
	virtual int __cdecl _GetSTATUS_PRECONDITION_FAILED() = 0 ;
	virtual int __cdecl _GetSTATUS_SUCCESS() = 0 ;
	virtual int __cdecl _GetSTATUS_TOO_MANY_REDIRECTS() = 0 ;
	virtual int __cdecl _GetSTATUS_UNHANDLED_HTTP_CODE() = 0 ;
	virtual int __cdecl _GetSTATUS_UNHANDLED_REDIRECT() = 0 ;
	virtual int __cdecl _GetSTATUS_UNKNOWN_ERROR() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTAG() = 0 ;
	virtual __int64 __cdecl _GetWATCHDOG_WAKE_TIMER() = 0 ;
	HIDESBASE virtual _di_JConstants __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_HIDE = {read=_GetACTION_HIDE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_LIST = {read=_GetACTION_LIST};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_OPEN = {read=_GetACTION_OPEN};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_RETRY = {read=_GetACTION_RETRY};
	__property __int64 ACTIVE_THREAD_WATCHDOG = {read=_GetACTIVE_THREAD_WATCHDOG};
	__property int BUFFER_SIZE = {read=_GetBUFFER_SIZE};
	__property Androidapi::Jni::Javatypes::_di_JString DEFAULT_USER_AGENT = {read=_GetDEFAULT_USER_AGENT};
	__property Androidapi::Jni::Javatypes::_di_JString EXP_PATH = {read=_GetEXP_PATH};
	__property Androidapi::Jni::Javatypes::_di_JString FILENAME_SEQUENCE_SEPARATOR = {read=_GetFILENAME_SEQUENCE_SEPARATOR};
	__property bool LOGV = {read=_GetLOGV};
	__property bool LOGVV = {read=_GetLOGVV};
	__property bool LOGX = {read=_GetLOGX};
	__property int MAX_DOWNLOADS = {read=_GetMAX_DOWNLOADS};
	__property int MAX_REDIRECTS = {read=_GetMAX_REDIRECTS};
	__property int MAX_RETRIES = {read=_GetMAX_RETRIES};
	__property int MAX_RETRY_AFTER = {read=_GetMAX_RETRY_AFTER};
	__property int MIN_ARTIFICIAL_ERROR_STATUS = {read=_GetMIN_ARTIFICIAL_ERROR_STATUS};
	__property int MIN_PROGRESS_STEP = {read=_GetMIN_PROGRESS_STEP};
	__property __int64 MIN_PROGRESS_TIME = {read=_GetMIN_PROGRESS_TIME};
	__property int MIN_RETRY_AFTER = {read=_GetMIN_RETRY_AFTER};
	__property int RETRY_FIRST_DELAY = {read=_GetRETRY_FIRST_DELAY};
	__property int STATUS_BAD_REQUEST = {read=_GetSTATUS_BAD_REQUEST};
	__property int STATUS_CANCELED = {read=_GetSTATUS_CANCELED};
	__property int STATUS_CANNOT_RESUME = {read=_GetSTATUS_CANNOT_RESUME};
	__property int STATUS_DEVICE_NOT_FOUND_ERROR = {read=_GetSTATUS_DEVICE_NOT_FOUND_ERROR};
	__property int STATUS_FILE_ALREADY_EXISTS_ERROR = {read=_GetSTATUS_FILE_ALREADY_EXISTS_ERROR};
	__property int STATUS_FILE_ERROR = {read=_GetSTATUS_FILE_ERROR};
	__property int STATUS_HTTP_DATA_ERROR = {read=_GetSTATUS_HTTP_DATA_ERROR};
	__property int STATUS_HTTP_EXCEPTION = {read=_GetSTATUS_HTTP_EXCEPTION};
	__property int STATUS_INSUFFICIENT_SPACE_ERROR = {read=_GetSTATUS_INSUFFICIENT_SPACE_ERROR};
	__property int STATUS_LENGTH_REQUIRED = {read=_GetSTATUS_LENGTH_REQUIRED};
	__property int STATUS_NOT_ACCEPTABLE = {read=_GetSTATUS_NOT_ACCEPTABLE};
	__property int STATUS_PRECONDITION_FAILED = {read=_GetSTATUS_PRECONDITION_FAILED};
	__property int STATUS_SUCCESS = {read=_GetSTATUS_SUCCESS};
	__property int STATUS_TOO_MANY_REDIRECTS = {read=_GetSTATUS_TOO_MANY_REDIRECTS};
	__property int STATUS_UNHANDLED_HTTP_CODE = {read=_GetSTATUS_UNHANDLED_HTTP_CODE};
	__property int STATUS_UNHANDLED_REDIRECT = {read=_GetSTATUS_UNHANDLED_REDIRECT};
	__property int STATUS_UNKNOWN_ERROR = {read=_GetSTATUS_UNKNOWN_ERROR};
	__property Androidapi::Jni::Javatypes::_di_JString TAG = {read=_GetTAG};
	__property __int64 WATCHDOG_WAKE_TIMER = {read=_GetWATCHDOG_WAKE_TIMER};
};

__interface  INTERFACE_UUID("{A453331C-B467-49F3-813F-42088D599D91}") JConstants  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJConstants : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConstantsClass,_di_JConstants>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConstantsClass,_di_JConstants> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJConstants() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JConstantsClass,_di_JConstants>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJConstants() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{881ECB1E-C9CC-4787-9B0D-F57D90261FFD}") JDownloadProgressInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JDownloadProgressInfo __cdecl init(Androidapi::Jni::Os::_di_JParcel p) = 0 /* overload */;
	HIDESBASE virtual _di_JDownloadProgressInfo __cdecl init(__int64 overallTotal, __int64 overallProgress, __int64 timeRemaining, float currentSpeed) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{3798A8DB-D57D-4516-ABEC-1442E421C3A3}") JDownloadProgressInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual float __cdecl _GetmCurrentSpeed() = 0 ;
	virtual void __cdecl _SetmCurrentSpeed(float Value) = 0 ;
	virtual __int64 __cdecl _GetmOverallProgress() = 0 ;
	virtual void __cdecl _SetmOverallProgress(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GetmOverallTotal() = 0 ;
	virtual void __cdecl _SetmOverallTotal(__int64 Value) = 0 ;
	virtual __int64 __cdecl _GetmTimeRemaining() = 0 ;
	virtual void __cdecl _SetmTimeRemaining(__int64 Value) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel p, int i) = 0 ;
	__property float mCurrentSpeed = {read=_GetmCurrentSpeed, write=_SetmCurrentSpeed};
	__property __int64 mOverallProgress = {read=_GetmOverallProgress, write=_SetmOverallProgress};
	__property __int64 mOverallTotal = {read=_GetmOverallTotal, write=_SetmOverallTotal};
	__property __int64 mTimeRemaining = {read=_GetmTimeRemaining, write=_SetmTimeRemaining};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadProgressInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadProgressInfoClass,_di_JDownloadProgressInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadProgressInfoClass,_di_JDownloadProgressInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadProgressInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadProgressInfoClass,_di_JDownloadProgressInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadProgressInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{75A82EEA-6851-420D-94F6-FD0ECA9F2DE5}") JDownloaderClientMarshallerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetDOWNLOAD_REQUIRED() = 0 ;
	virtual int __cdecl _GetLVL_CHECK_REQUIRED() = 0 ;
	virtual int __cdecl _GetMSG_ONDOWNLOADPROGRESS() = 0 ;
	virtual int __cdecl _GetMSG_ONDOWNLOADSTATE_CHANGED() = 0 ;
	virtual int __cdecl _GetMSG_ONSERVICECONNECTED() = 0 ;
	virtual int __cdecl _GetNO_DOWNLOAD_REQUIRED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPARAM_MESSENGER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPARAM_NEW_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPARAM_PROGRESS() = 0 ;
	HIDESBASE virtual _di_JDownloaderClientMarshaller __cdecl init() = 0 ;
	virtual _di_JIDownloaderClient __cdecl CreateProxy(Androidapi::Jni::Os::_di_JMessenger msg) = 0 ;
	virtual _di_JIStub __cdecl CreateStub(_di_JIDownloaderClient itf, Androidapi::Jni::Javatypes::_di_Jlang_Class downloaderService) = 0 ;
	virtual int __cdecl startDownloadServiceIfRequired(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::App::_di_JPendingIntent notificationClient, Androidapi::Jni::Javatypes::_di_Jlang_Class serviceClass) = 0 /* overload */;
	virtual int __cdecl startDownloadServiceIfRequired(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent notificationClient, Androidapi::Jni::Javatypes::_di_Jlang_Class serviceClass) = 0 /* overload */;
	__property int DOWNLOAD_REQUIRED = {read=_GetDOWNLOAD_REQUIRED};
	__property int LVL_CHECK_REQUIRED = {read=_GetLVL_CHECK_REQUIRED};
	__property int MSG_ONDOWNLOADPROGRESS = {read=_GetMSG_ONDOWNLOADPROGRESS};
	__property int MSG_ONDOWNLOADSTATE_CHANGED = {read=_GetMSG_ONDOWNLOADSTATE_CHANGED};
	__property int MSG_ONSERVICECONNECTED = {read=_GetMSG_ONSERVICECONNECTED};
	__property int NO_DOWNLOAD_REQUIRED = {read=_GetNO_DOWNLOAD_REQUIRED};
	__property Androidapi::Jni::Javatypes::_di_JString PARAM_MESSENGER = {read=_GetPARAM_MESSENGER};
	__property Androidapi::Jni::Javatypes::_di_JString PARAM_NEW_STATE = {read=_GetPARAM_NEW_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString PARAM_PROGRESS = {read=_GetPARAM_PROGRESS};
};

__interface  INTERFACE_UUID("{86C0E465-3E15-47C3-8021-19E7D3E46A16}") JDownloaderClientMarshaller  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderClientMarshaller : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderClientMarshallerClass,_di_JDownloaderClientMarshaller>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderClientMarshallerClass,_di_JDownloaderClientMarshaller> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderClientMarshaller() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderClientMarshallerClass,_di_JDownloaderClientMarshaller>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderClientMarshaller() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C0AA10E1-4A1A-40AA-A7B5-E700C2F8179F}") JDownloaderServiceMarshallerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetMSG_REQUEST_ABORT_DOWNLOAD() = 0 ;
	virtual int __cdecl _GetMSG_REQUEST_CLIENT_UPDATE() = 0 ;
	virtual int __cdecl _GetMSG_REQUEST_CONTINUE_DOWNLOAD() = 0 ;
	virtual int __cdecl _GetMSG_REQUEST_DOWNLOAD_STATE() = 0 ;
	virtual int __cdecl _GetMSG_REQUEST_PAUSE_DOWNLOAD() = 0 ;
	virtual int __cdecl _GetMSG_SET_DOWNLOAD_FLAGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPARAMS_FLAGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPARAM_MESSENGER() = 0 ;
	HIDESBASE virtual _di_JDownloaderServiceMarshaller __cdecl init() = 0 ;
	virtual _di_JIDownloaderService __cdecl CreateProxy(Androidapi::Jni::Os::_di_JMessenger msg) = 0 ;
	virtual _di_JIStub __cdecl CreateStub(_di_JIDownloaderService itf) = 0 ;
	__property int MSG_REQUEST_ABORT_DOWNLOAD = {read=_GetMSG_REQUEST_ABORT_DOWNLOAD};
	__property int MSG_REQUEST_CLIENT_UPDATE = {read=_GetMSG_REQUEST_CLIENT_UPDATE};
	__property int MSG_REQUEST_CONTINUE_DOWNLOAD = {read=_GetMSG_REQUEST_CONTINUE_DOWNLOAD};
	__property int MSG_REQUEST_DOWNLOAD_STATE = {read=_GetMSG_REQUEST_DOWNLOAD_STATE};
	__property int MSG_REQUEST_PAUSE_DOWNLOAD = {read=_GetMSG_REQUEST_PAUSE_DOWNLOAD};
	__property int MSG_SET_DOWNLOAD_FLAGS = {read=_GetMSG_SET_DOWNLOAD_FLAGS};
	__property Androidapi::Jni::Javatypes::_di_JString PARAMS_FLAGS = {read=_GetPARAMS_FLAGS};
	__property Androidapi::Jni::Javatypes::_di_JString PARAM_MESSENGER = {read=_GetPARAM_MESSENGER};
};

__interface  INTERFACE_UUID("{8F9F546F-191C-4489-8222-7E979F78F41A}") JDownloaderServiceMarshaller  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderServiceMarshaller : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceMarshallerClass,_di_JDownloaderServiceMarshaller>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceMarshallerClass,_di_JDownloaderServiceMarshaller> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderServiceMarshaller() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderServiceMarshallerClass,_di_JDownloaderServiceMarshaller>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderServiceMarshaller() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A1509108-FA42-4AE4-A17B-29DCB2DABCE0}") JHelpersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JRandom __cdecl _GetsRandom() = 0 ;
	virtual void __cdecl _SetsRandom(Androidapi::Jni::Javatypes::_di_JRandom Value) = 0 ;
	virtual bool __cdecl doesFileExist(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Javatypes::_di_JString fileName, __int64 fileSize, bool deleteFileOnMismatch) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl generateSaveFileName(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, Androidapi::Jni::Javatypes::_di_JString fileName) = 0 ;
	virtual __int64 __cdecl getAvailableBytes(Androidapi::Jni::Javatypes::_di_JFile root) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDownloadProgressPercent(__int64 overallProgress, __int64 overallTotal) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDownloadProgressString(__int64 overallProgress, __int64 overallTotal) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDownloadProgressStringNotification(__int64 overallProgress, __int64 overallTotal) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDownloaderStringResourceIDFromState(int state) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getExpansionAPKFileName(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c, bool mainFile, int versionCode) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JFile __cdecl getFilesystemRoot(Androidapi::Jni::Javatypes::_di_JString path) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSaveFilePath(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSpeedString(float bytesPerMillisecond) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getTimeRemaining(__int64 durationInMilliseconds) = 0 ;
	virtual bool __cdecl isExternalMediaMounted() = 0 ;
	virtual bool __cdecl isFilenameValid(Androidapi::Jni::Javatypes::_di_JString filename) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JRandom sRandom = {read=_GetsRandom, write=_SetsRandom};
};

__interface  INTERFACE_UUID("{0024D8E0-E52D-47C1-95D5-414438B5AAFD}") JHelpers  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHelpers : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHelpersClass,_di_JHelpers>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHelpersClass,_di_JHelpers> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHelpers() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHelpersClass,_di_JHelpers>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHelpers() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8159CCD5-7CC0-4895-AD28-8FFFA4662F17}") JIDownloaderClientClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetSTATE_COMPLETED() = 0 ;
	virtual int __cdecl _GetSTATE_CONNECTING() = 0 ;
	virtual int __cdecl _GetSTATE_DOWNLOADING() = 0 ;
	virtual int __cdecl _GetSTATE_FAILED() = 0 ;
	virtual int __cdecl _GetSTATE_FAILED_CANCELED() = 0 ;
	virtual int __cdecl _GetSTATE_FAILED_FETCHING_URL() = 0 ;
	virtual int __cdecl _GetSTATE_FAILED_SDCARD_FULL() = 0 ;
	virtual int __cdecl _GetSTATE_FAILED_UNLICENSED() = 0 ;
	virtual int __cdecl _GetSTATE_FETCHING_URL() = 0 ;
	virtual int __cdecl _GetSTATE_IDLE() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_BY_REQUEST() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_NEED_CELLULAR_PERMISSION() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_NEED_WIFI() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_NETWORK_SETUP_FAILURE() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_NETWORK_UNAVAILABLE() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_ROAMING() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_SDCARD_UNAVAILABLE() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_WIFI_DISABLED() = 0 ;
	virtual int __cdecl _GetSTATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION() = 0 ;
	__property int STATE_COMPLETED = {read=_GetSTATE_COMPLETED};
	__property int STATE_CONNECTING = {read=_GetSTATE_CONNECTING};
	__property int STATE_DOWNLOADING = {read=_GetSTATE_DOWNLOADING};
	__property int STATE_FAILED = {read=_GetSTATE_FAILED};
	__property int STATE_FAILED_CANCELED = {read=_GetSTATE_FAILED_CANCELED};
	__property int STATE_FAILED_FETCHING_URL = {read=_GetSTATE_FAILED_FETCHING_URL};
	__property int STATE_FAILED_SDCARD_FULL = {read=_GetSTATE_FAILED_SDCARD_FULL};
	__property int STATE_FAILED_UNLICENSED = {read=_GetSTATE_FAILED_UNLICENSED};
	__property int STATE_FETCHING_URL = {read=_GetSTATE_FETCHING_URL};
	__property int STATE_IDLE = {read=_GetSTATE_IDLE};
	__property int STATE_PAUSED_BY_REQUEST = {read=_GetSTATE_PAUSED_BY_REQUEST};
	__property int STATE_PAUSED_NEED_CELLULAR_PERMISSION = {read=_GetSTATE_PAUSED_NEED_CELLULAR_PERMISSION};
	__property int STATE_PAUSED_NEED_WIFI = {read=_GetSTATE_PAUSED_NEED_WIFI};
	__property int STATE_PAUSED_NETWORK_SETUP_FAILURE = {read=_GetSTATE_PAUSED_NETWORK_SETUP_FAILURE};
	__property int STATE_PAUSED_NETWORK_UNAVAILABLE = {read=_GetSTATE_PAUSED_NETWORK_UNAVAILABLE};
	__property int STATE_PAUSED_ROAMING = {read=_GetSTATE_PAUSED_ROAMING};
	__property int STATE_PAUSED_SDCARD_UNAVAILABLE = {read=_GetSTATE_PAUSED_SDCARD_UNAVAILABLE};
	__property int STATE_PAUSED_WIFI_DISABLED = {read=_GetSTATE_PAUSED_WIFI_DISABLED};
	__property int STATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION = {read=_GetSTATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION};
};

__interface  INTERFACE_UUID("{E35F3579-F34C-48D4-8657-37970D83E7B1}") JIDownloaderClient  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress) = 0 ;
	virtual void __cdecl onDownloadStateChanged(int newState) = 0 ;
	virtual void __cdecl onServiceConnected(Androidapi::Jni::Os::_di_JMessenger m) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIDownloaderClient : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderClientClass,_di_JIDownloaderClient>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderClientClass,_di_JIDownloaderClient> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIDownloaderClient() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderClientClass,_di_JIDownloaderClient>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIDownloaderClient() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{41544B3F-F012-4833-8764-661EDF6F52C3}") JIDownloaderServiceClass  : public Androidapi::Jnibridge::IJavaClass 
{
	virtual int __cdecl _GetFLAGS_DOWNLOAD_OVER_CELLULAR() = 0 ;
	__property int FLAGS_DOWNLOAD_OVER_CELLULAR = {read=_GetFLAGS_DOWNLOAD_OVER_CELLULAR};
};

__interface  INTERFACE_UUID("{0D21EF00-EF7F-47D7-971C-4A9D263AA7FC}") JIDownloaderService  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onClientUpdated(Androidapi::Jni::Os::_di_JMessenger clientMessenger) = 0 ;
	virtual void __cdecl requestAbortDownload() = 0 ;
	virtual void __cdecl requestContinueDownload() = 0 ;
	virtual void __cdecl requestDownloadStatus() = 0 ;
	virtual void __cdecl requestPauseDownload() = 0 ;
	virtual void __cdecl setDownloadFlags(int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIDownloaderService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderServiceClass,_di_JIDownloaderService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderServiceClass,_di_JIDownloaderService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIDownloaderService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIDownloaderServiceClass,_di_JIDownloaderService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIDownloaderService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7DE9F188-261B-4291-8D56-CEFDA3A45919}") JIStubClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B84B97DB-7E4D-410E-A35B-2FC426E3BB0E}") JIStub  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl connect(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	virtual void __cdecl disconnect(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
	virtual Androidapi::Jni::Os::_di_JMessenger __cdecl getMessenger() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIStub : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIStubClass,_di_JIStub>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIStubClass,_di_JIStub> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIStub() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIStubClass,_di_JIStub>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIStub() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4A8A2C31-B5DB-41B5-A3B4-4BDF61B5D2EF}") JNotificationLabelsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getkilobytes_per_second() = 0 ;
	virtual void __cdecl _Setkilobytes_per_second(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getnotification_download_complete() = 0 ;
	virtual void __cdecl _Setnotification_download_complete(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getnotification_download_failed() = 0 ;
	virtual void __cdecl _Setnotification_download_failed(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_completed() = 0 ;
	virtual void __cdecl _Setstate_completed(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_connecting() = 0 ;
	virtual void __cdecl _Setstate_connecting(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_downloading() = 0 ;
	virtual void __cdecl _Setstate_downloading(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_failed() = 0 ;
	virtual void __cdecl _Setstate_failed(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_failed_cancelled() = 0 ;
	virtual void __cdecl _Setstate_failed_cancelled(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_failed_fetching_url() = 0 ;
	virtual void __cdecl _Setstate_failed_fetching_url(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_failed_sdcard_full() = 0 ;
	virtual void __cdecl _Setstate_failed_sdcard_full(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_failed_unlicensed() = 0 ;
	virtual void __cdecl _Setstate_failed_unlicensed(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_fetching_url() = 0 ;
	virtual void __cdecl _Setstate_fetching_url(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_idle() = 0 ;
	virtual void __cdecl _Setstate_idle(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_by_request() = 0 ;
	virtual void __cdecl _Setstate_paused_by_request(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_network_setup_failure() = 0 ;
	virtual void __cdecl _Setstate_paused_network_setup_failure(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_network_unavailable() = 0 ;
	virtual void __cdecl _Setstate_paused_network_unavailable(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_roaming() = 0 ;
	virtual void __cdecl _Setstate_paused_roaming(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_sdcard_unavailable() = 0 ;
	virtual void __cdecl _Setstate_paused_sdcard_unavailable(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_wifi_disabled() = 0 ;
	virtual void __cdecl _Setstate_paused_wifi_disabled(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_paused_wifi_unavailable() = 0 ;
	virtual void __cdecl _Setstate_paused_wifi_unavailable(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getstate_unknown() = 0 ;
	virtual void __cdecl _Setstate_unknown(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettime_remaining() = 0 ;
	virtual void __cdecl _Settime_remaining(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettime_remaining_notification() = 0 ;
	virtual void __cdecl _Settime_remaining_notification(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	HIDESBASE virtual _di_JNotificationLabels __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString kilobytes_per_second = {read=_Getkilobytes_per_second, write=_Setkilobytes_per_second};
	__property Androidapi::Jni::Javatypes::_di_JString notification_download_complete = {read=_Getnotification_download_complete, write=_Setnotification_download_complete};
	__property Androidapi::Jni::Javatypes::_di_JString notification_download_failed = {read=_Getnotification_download_failed, write=_Setnotification_download_failed};
	__property Androidapi::Jni::Javatypes::_di_JString state_completed = {read=_Getstate_completed, write=_Setstate_completed};
	__property Androidapi::Jni::Javatypes::_di_JString state_connecting = {read=_Getstate_connecting, write=_Setstate_connecting};
	__property Androidapi::Jni::Javatypes::_di_JString state_downloading = {read=_Getstate_downloading, write=_Setstate_downloading};
	__property Androidapi::Jni::Javatypes::_di_JString state_failed = {read=_Getstate_failed, write=_Setstate_failed};
	__property Androidapi::Jni::Javatypes::_di_JString state_failed_cancelled = {read=_Getstate_failed_cancelled, write=_Setstate_failed_cancelled};
	__property Androidapi::Jni::Javatypes::_di_JString state_failed_fetching_url = {read=_Getstate_failed_fetching_url, write=_Setstate_failed_fetching_url};
	__property Androidapi::Jni::Javatypes::_di_JString state_failed_sdcard_full = {read=_Getstate_failed_sdcard_full, write=_Setstate_failed_sdcard_full};
	__property Androidapi::Jni::Javatypes::_di_JString state_failed_unlicensed = {read=_Getstate_failed_unlicensed, write=_Setstate_failed_unlicensed};
	__property Androidapi::Jni::Javatypes::_di_JString state_fetching_url = {read=_Getstate_fetching_url, write=_Setstate_fetching_url};
	__property Androidapi::Jni::Javatypes::_di_JString state_idle = {read=_Getstate_idle, write=_Setstate_idle};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_by_request = {read=_Getstate_paused_by_request, write=_Setstate_paused_by_request};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_network_setup_failure = {read=_Getstate_paused_network_setup_failure, write=_Setstate_paused_network_setup_failure};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_network_unavailable = {read=_Getstate_paused_network_unavailable, write=_Setstate_paused_network_unavailable};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_roaming = {read=_Getstate_paused_roaming, write=_Setstate_paused_roaming};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_sdcard_unavailable = {read=_Getstate_paused_sdcard_unavailable, write=_Setstate_paused_sdcard_unavailable};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_wifi_disabled = {read=_Getstate_paused_wifi_disabled, write=_Setstate_paused_wifi_disabled};
	__property Androidapi::Jni::Javatypes::_di_JString state_paused_wifi_unavailable = {read=_Getstate_paused_wifi_unavailable, write=_Setstate_paused_wifi_unavailable};
	__property Androidapi::Jni::Javatypes::_di_JString state_unknown = {read=_Getstate_unknown, write=_Setstate_unknown};
	__property Androidapi::Jni::Javatypes::_di_JString time_remaining = {read=_Gettime_remaining, write=_Settime_remaining};
	__property Androidapi::Jni::Javatypes::_di_JString time_remaining_notification = {read=_Gettime_remaining_notification, write=_Settime_remaining_notification};
};

__interface  INTERFACE_UUID("{C15E6974-1B42-4F31-83B9-385D6936F367}") JNotificationLabels  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNotificationLabels : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationLabelsClass,_di_JNotificationLabels>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationLabelsClass,_di_JNotificationLabels> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNotificationLabels() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNotificationLabelsClass,_di_JNotificationLabels>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNotificationLabels() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7F8598EB-108D-49B1-8A24-1DCAC828734C}") JCustomNotificationFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCustomNotificationFactory __cdecl init() = 0 ;
	virtual _di_JDownloadNotification_ICustomNotification __cdecl createCustomNotification() = 0 ;
};

__interface  INTERFACE_UUID("{FC2DE5B2-6F5C-424E-A8A3-47071E65B729}") JCustomNotificationFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCustomNotificationFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomNotificationFactoryClass,_di_JCustomNotificationFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomNotificationFactoryClass,_di_JCustomNotificationFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCustomNotificationFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomNotificationFactoryClass,_di_JCustomNotificationFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCustomNotificationFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F3074D64-CC05-491E-BBD6-4222F2AE918D}") JDownloadInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDownloadInfo __cdecl init(int index, Androidapi::Jni::Javatypes::_di_JString fileName, Androidapi::Jni::Javatypes::_di_JString pkg) = 0 ;
};

__interface  INTERFACE_UUID("{BE027323-52FF-4D36-8793-F04E2FF47E1E}") JDownloadInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetmControl() = 0 ;
	virtual void __cdecl _SetmControl(int Value) = 0 ;
	virtual __int64 __cdecl _GetmCurrentBytes() = 0 ;
	virtual void __cdecl _SetmCurrentBytes(__int64 Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmETag() = 0 ;
	virtual void __cdecl _SetmETag(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmFileName() = 0 ;
	virtual int __cdecl _GetmFuzz() = 0 ;
	virtual void __cdecl _SetmFuzz(int Value) = 0 ;
	virtual int __cdecl _GetmIndex() = 0 ;
	virtual __int64 __cdecl _GetmLastMod() = 0 ;
	virtual void __cdecl _SetmLastMod(__int64 Value) = 0 ;
	virtual int __cdecl _GetmNumFailed() = 0 ;
	virtual void __cdecl _SetmNumFailed(int Value) = 0 ;
	virtual int __cdecl _GetmRedirectCount() = 0 ;
	virtual void __cdecl _SetmRedirectCount(int Value) = 0 ;
	virtual int __cdecl _GetmRetryAfter() = 0 ;
	virtual void __cdecl _SetmRetryAfter(int Value) = 0 ;
	virtual int __cdecl _GetmStatus() = 0 ;
	virtual void __cdecl _SetmStatus(int Value) = 0 ;
	virtual __int64 __cdecl _GetmTotalBytes() = 0 ;
	virtual void __cdecl _SetmTotalBytes(__int64 Value) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetmUri() = 0 ;
	virtual void __cdecl _SetmUri(Androidapi::Jni::Javatypes::_di_JString Value) = 0 ;
	virtual void __cdecl logVerboseInfo() = 0 ;
	virtual void __cdecl resetDownload() = 0 ;
	virtual __int64 __cdecl restartTime(__int64 now) = 0 ;
	__property int mControl = {read=_GetmControl, write=_SetmControl};
	__property __int64 mCurrentBytes = {read=_GetmCurrentBytes, write=_SetmCurrentBytes};
	__property Androidapi::Jni::Javatypes::_di_JString mETag = {read=_GetmETag, write=_SetmETag};
	__property Androidapi::Jni::Javatypes::_di_JString mFileName = {read=_GetmFileName};
	__property int mFuzz = {read=_GetmFuzz, write=_SetmFuzz};
	__property int mIndex = {read=_GetmIndex};
	__property __int64 mLastMod = {read=_GetmLastMod, write=_SetmLastMod};
	__property int mNumFailed = {read=_GetmNumFailed, write=_SetmNumFailed};
	__property int mRedirectCount = {read=_GetmRedirectCount, write=_SetmRedirectCount};
	__property int mRetryAfter = {read=_GetmRetryAfter, write=_SetmRetryAfter};
	__property int mStatus = {read=_GetmStatus, write=_SetmStatus};
	__property __int64 mTotalBytes = {read=_GetmTotalBytes, write=_SetmTotalBytes};
	__property Androidapi::Jni::Javatypes::_di_JString mUri = {read=_GetmUri, write=_SetmUri};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadInfoClass,_di_JDownloadInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadInfoClass,_di_JDownloadInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadInfoClass,_di_JDownloadInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{92E75B92-17A5-49AA-8C2B-0866FD212482}") JDownloadNotificationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{637B8622-9735-48D9-99DD-ECE406B60F73}") JDownloadNotification  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::App::_di_JPendingIntent __cdecl getClientIntent() = 0 ;
	virtual void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress) = 0 ;
	virtual void __cdecl onDownloadStateChanged(int newState) = 0 ;
	virtual void __cdecl onServiceConnected(Androidapi::Jni::Os::_di_JMessenger m) = 0 ;
	virtual void __cdecl resendState() = 0 ;
	virtual void __cdecl setClientIntent(Androidapi::Jni::App::_di_JPendingIntent mClientIntent) = 0 ;
	virtual void __cdecl setMessenger(Androidapi::Jni::Os::_di_JMessenger msg) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadNotification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotificationClass,_di_JDownloadNotification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotificationClass,_di_JDownloadNotification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadNotification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotificationClass,_di_JDownloadNotification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8158EF16-A61B-4085-9B67-7A7BD35D139B}") JDownloadNotification_ICustomNotificationClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{56E88756-E5A1-47EF-8506-84EB871A0EE8}") JDownloadNotification_ICustomNotification  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl setCurrentBytes(__int64 currentBytes) = 0 ;
	virtual void __cdecl setIcon(int iconResource) = 0 ;
	virtual void __cdecl setPendingIntent(Androidapi::Jni::App::_di_JPendingIntent mContentIntent) = 0 ;
	virtual void __cdecl setTicker(Androidapi::Jni::Javatypes::_di_JCharSequence ticker) = 0 ;
	virtual void __cdecl setTimeRemaining(__int64 timeRemaining) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 ;
	virtual void __cdecl setTotalBytes(__int64 totalBytes) = 0 ;
	virtual Androidapi::Jni::App::_di_JNotification __cdecl updateNotification(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadNotification_ICustomNotification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotification_ICustomNotificationClass,_di_JDownloadNotification_ICustomNotification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotification_ICustomNotificationClass,_di_JDownloadNotification_ICustomNotification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadNotification_ICustomNotification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadNotification_ICustomNotificationClass,_di_JDownloadNotification_ICustomNotification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadNotification_ICustomNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1BDE2D91-16DD-4B28-A84A-7D73A434B5AA}") JDownloadThreadClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDownloadThread __cdecl init(_di_JDownloadInfo info, _di_JDownloaderService service, _di_JDownloadNotification notification) = 0 ;
};

__interface  INTERFACE_UUID("{4F1F71DC-33F8-4F2D-B528-ED3397ABE958}") JDownloadThread  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getPreferredHttpHost(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString url) = 0 ;
	virtual void __cdecl run() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadThread : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadThreadClass,_di_JDownloadThread>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadThreadClass,_di_JDownloadThread> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadThread() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadThreadClass,_di_JDownloadThread>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadThread() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AD77F5D6-1F2A-4BAE-B67F-C7637A7B3CFD}") JDownloaderService_GenerateSaveFileErrorClass  : public Androidapi::Jni::Javatypes::JExceptionClass 
{
	HIDESBASE virtual _di_JDownloaderService_GenerateSaveFileError __cdecl init(int status, Androidapi::Jni::Javatypes::_di_JString message) = 0 ;
};

__interface  INTERFACE_UUID("{329A95DC-A15B-4B76-B251-145B96A34D64}") JDownloaderService_GenerateSaveFileError  : public Androidapi::Jni::Javatypes::JException 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloaderService_GenerateSaveFileError : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderService_GenerateSaveFileErrorClass,_di_JDownloaderService_GenerateSaveFileError>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderService_GenerateSaveFileErrorClass,_di_JDownloaderService_GenerateSaveFileError> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloaderService_GenerateSaveFileError() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloaderService_GenerateSaveFileErrorClass,_di_JDownloaderService_GenerateSaveFileError>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloaderService_GenerateSaveFileError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6A0BA0DE-13E4-48F2-B4CB-730B6BB30451}") JDownloadsDBClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLOG_TAG() = 0 ;
	virtual _di_JDownloadsDB __cdecl getDB(Androidapi::Jni::Graphicscontentviewtext::_di_JContext paramContext) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString LOG_TAG = {read=_GetLOG_TAG};
};

__interface  INTERFACE_UUID("{47CC25B2-3ADA-4611-83ED-E834E01C3C1D}") JDownloadsDB  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl close() = 0 ;
	virtual _di_JDownloadInfo __cdecl getDownloadInfoFromCursor(Androidapi::Jni::Graphicscontentviewtext::_di_JCursor cur) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JDownloadInfo>* __cdecl getDownloads() = 0 ;
	virtual int __cdecl getFlags() = 0 ;
	virtual __int64 __cdecl getIDByIndex(int index) = 0 ;
	virtual __int64 __cdecl getIDForDownloadInfo(_di_JDownloadInfo di) = 0 ;
	virtual int __cdecl getLastCheckedVersionCode() = 0 ;
	virtual bool __cdecl isDownloadRequired() = 0 ;
	virtual void __cdecl setDownloadInfoFromCursor(_di_JDownloadInfo di, Androidapi::Jni::Graphicscontentviewtext::_di_JCursor cur) = 0 ;
	virtual bool __cdecl updateDownload(_di_JDownloadInfo di) = 0 /* overload */;
	virtual bool __cdecl updateDownload(_di_JDownloadInfo di, Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues cv) = 0 /* overload */;
	virtual void __cdecl updateDownloadCurrentBytes(_di_JDownloadInfo di) = 0 ;
	virtual bool __cdecl updateFlags(int flags) = 0 ;
	virtual bool __cdecl updateFromDb(_di_JDownloadInfo di) = 0 ;
	virtual bool __cdecl updateMetadata(Androidapi::Jni::Graphicscontentviewtext::_di_JContentValues cv) = 0 /* overload */;
	virtual bool __cdecl updateMetadata(int apkVersion, int downloadStatus) = 0 /* overload */;
	virtual bool __cdecl updateStatus(int status) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadsDB : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDBClass,_di_JDownloadsDB>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDBClass,_di_JDownloadsDB> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadsDB() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDBClass,_di_JDownloadsDB>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadsDB() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{309FB969-9E60-4FEE-9083-5708B1FEB032}") JDownloadsDB_DownloadColumnsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCONTROL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetCURRENTBYTES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetETAG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFILENAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetINDEX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLASTMOD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetNUM_FAILED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetREDIRECT_COUNT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetRETRY_AFTER() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectBiArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetSCHEMA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSTATUS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTABLE_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTOTALBYTES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetURI() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Get_ID() = 0 ;
	HIDESBASE virtual _di_JDownloadsDB_DownloadColumns __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString CONTROL = {read=_GetCONTROL};
	__property Androidapi::Jni::Javatypes::_di_JString CURRENTBYTES = {read=_GetCURRENTBYTES};
	__property Androidapi::Jni::Javatypes::_di_JString ETAG = {read=_GetETAG};
	__property Androidapi::Jni::Javatypes::_di_JString FILENAME = {read=_GetFILENAME};
	__property Androidapi::Jni::Javatypes::_di_JString INDEX = {read=_GetINDEX};
	__property Androidapi::Jni::Javatypes::_di_JString LASTMOD = {read=_GetLASTMOD};
	__property Androidapi::Jni::Javatypes::_di_JString NUM_FAILED = {read=_GetNUM_FAILED};
	__property Androidapi::Jni::Javatypes::_di_JString REDIRECT_COUNT = {read=_GetREDIRECT_COUNT};
	__property Androidapi::Jni::Javatypes::_di_JString RETRY_AFTER = {read=_GetRETRY_AFTER};
	__property Androidapi::Jnibridge::TJavaObjectBiArray__1<Androidapi::Jni::Javatypes::_di_JString>* SCHEMA = {read=_GetSCHEMA};
	__property Androidapi::Jni::Javatypes::_di_JString STATUS = {read=_GetSTATUS};
	__property Androidapi::Jni::Javatypes::_di_JString TABLE_NAME = {read=_GetTABLE_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString TOTALBYTES = {read=_GetTOTALBYTES};
	__property Androidapi::Jni::Javatypes::_di_JString URI = {read=_GetURI};
	__property Androidapi::Jni::Javatypes::_di_JString _ID = {read=_Get_ID};
};

__interface  INTERFACE_UUID("{70F2EEAB-F288-4E3C-A81F-86DAAB2E3810}") JDownloadsDB_DownloadColumns  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadsDB_DownloadColumns : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_DownloadColumnsClass,_di_JDownloadsDB_DownloadColumns>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_DownloadColumnsClass,_di_JDownloadsDB_DownloadColumns> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadsDB_DownloadColumns() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_DownloadColumnsClass,_di_JDownloadsDB_DownloadColumns>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadsDB_DownloadColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8DFD2602-E83D-44A1-AA48-1AC95679C976}") JDownloadsDB_MetadataColumnsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAPKVERSION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetDOWNLOAD_STATUS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetFLAGS() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectBiArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl _GetSCHEMA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetTABLE_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Get_ID() = 0 ;
	HIDESBASE virtual _di_JDownloadsDB_MetadataColumns __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString APKVERSION = {read=_GetAPKVERSION};
	__property Androidapi::Jni::Javatypes::_di_JString DOWNLOAD_STATUS = {read=_GetDOWNLOAD_STATUS};
	__property Androidapi::Jni::Javatypes::_di_JString FLAGS = {read=_GetFLAGS};
	__property Androidapi::Jnibridge::TJavaObjectBiArray__1<Androidapi::Jni::Javatypes::_di_JString>* SCHEMA = {read=_GetSCHEMA};
	__property Androidapi::Jni::Javatypes::_di_JString TABLE_NAME = {read=_GetTABLE_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString _ID = {read=_Get_ID};
};

__interface  INTERFACE_UUID("{96D3961A-9DEF-4421-9BA9-0927F877356F}") JDownloadsDB_MetadataColumns  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDownloadsDB_MetadataColumns : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_MetadataColumnsClass,_di_JDownloadsDB_MetadataColumns>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_MetadataColumnsClass,_di_JDownloadsDB_MetadataColumns> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDownloadsDB_MetadataColumns() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDownloadsDB_MetadataColumnsClass,_di_JDownloadsDB_MetadataColumns>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDownloadsDB_MetadataColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E5F4C13B-B479-41BB-AB05-9D6E1881D102}") JHttpDateTimeClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JHttpDateTime __cdecl init() = 0 ;
	virtual __int64 __cdecl parse(Androidapi::Jni::Javatypes::_di_JString timeString) = 0 ;
};

__interface  INTERFACE_UUID("{686B6AD2-8C07-48F0-AE6F-12278C24A12E}") JHttpDateTime  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHttpDateTime : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpDateTimeClass,_di_JHttpDateTime>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpDateTimeClass,_di_JHttpDateTime> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHttpDateTime() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpDateTimeClass,_di_JHttpDateTime>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHttpDateTime() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D16E2048-BF59-443A-A0D7-446AB9F09FE9}") JV14CustomNotificationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JV14CustomNotification __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{EB90C5CB-A513-4FF8-9327-E7FF28DF2AEC}") JV14CustomNotification  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl setCurrentBytes(__int64 currentBytes) = 0 ;
	virtual void __cdecl setIcon(int icon) = 0 ;
	virtual void __cdecl setPendingIntent(Androidapi::Jni::App::_di_JPendingIntent contentIntent) = 0 ;
	virtual void __cdecl setTicker(Androidapi::Jni::Javatypes::_di_JCharSequence ticker) = 0 ;
	virtual void __cdecl setTimeRemaining(__int64 timeRemaining) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 ;
	virtual void __cdecl setTotalBytes(__int64 totalBytes) = 0 ;
	virtual Androidapi::Jni::App::_di_JNotification __cdecl updateNotification(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJV14CustomNotification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV14CustomNotificationClass,_di_JV14CustomNotification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV14CustomNotificationClass,_di_JV14CustomNotification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJV14CustomNotification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV14CustomNotificationClass,_di_JV14CustomNotification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJV14CustomNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4E619072-0DB1-4DBD-A7D8-F8DA4BC36366}") JV3CustomNotificationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JV3CustomNotification __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{AF9A3534-5317-46CD-A1E2-03D78E324E8E}") JV3CustomNotification  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl setCurrentBytes(__int64 currentBytes) = 0 ;
	virtual void __cdecl setIcon(int icon) = 0 ;
	virtual void __cdecl setPendingIntent(Androidapi::Jni::App::_di_JPendingIntent contentIntent) = 0 ;
	virtual void __cdecl setTicker(Androidapi::Jni::Javatypes::_di_JCharSequence ticker) = 0 ;
	virtual void __cdecl setTimeRemaining(__int64 timeRemaining) = 0 ;
	virtual void __cdecl setTitle(Androidapi::Jni::Javatypes::_di_JCharSequence title) = 0 ;
	virtual void __cdecl setTotalBytes(__int64 totalBytes) = 0 ;
	virtual Androidapi::Jni::App::_di_JNotification __cdecl updateNotification(Androidapi::Jni::Graphicscontentviewtext::_di_JContext c) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJV3CustomNotification : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV3CustomNotificationClass,_di_JV3CustomNotification>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV3CustomNotificationClass,_di_JV3CustomNotification> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJV3CustomNotification() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JV3CustomNotificationClass,_di_JV3CustomNotification>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJV3CustomNotification() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TDownloadStateKind : unsigned char { STATE_IDLE = 1, STATE_FETCHING_URL, STATE_CONNECTING, STATE_DOWNLOADING, STATE_COMPLETED, STATE_PAUSED_NETWORK_UNAVAILABLE, STATE_PAUSED_BY_REQUEST, STATE_PAUSED_WIFI_DISABLED_NEED_CELLULAR_PERMISSION, STATE_PAUSED_NEED_CELLULAR_PERMISSION, STATE_PAUSED_WIFI_DISABLED, STATE_PAUSED_NEED_WIFI, STATE_PAUSED_ROAMING, STATE_PAUSED_NETWORK_SETUP_FAILURE, STATE_PAUSED_SDCARD_UNAVAILABLE, STATE_FAILED_UNLICENSED, STATE_FAILED_FETCHING_URL, STATE_FAILED_SDCARD_FULL, STATE_FAILED_CANCELED, STATE_FAILED };

enum DECLSPEC_DENUM TObbStateKind : unsigned char { ERROR_INTERNAL = 20, ERROR_COULD_NOT_MOUNT, ERROR_COULD_NOT_UNMOUNT, ERROR_NOT_MOUNTED, ERROR_ALREADY_MOUNTED, ERROR_PERMISSION_DENIED, MOUNTED = 1, UNMOUNTED };

struct DECLSPEC_DRECORD TDownloadProgressInfo
{
public:
	__int64 OverallTotal;
	__int64 OverallProgress;
	__int64 TimeRemaining;
	float CurrentSpeed;
};


struct DECLSPEC_DRECORD TApkFileInfo
{
public:
	bool IsMainFile;
	int FileVersion;
	__int64 FileSize;
	System::UnicodeString EncriptKey;
	TObb* __fastcall GetObb();
	_di_JApkFileInfo __fastcall ToJApkFileInfo();
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TApkExpansion : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod bool __fastcall AreFilesDelivered(const TApkFileInfo &MainFile)/* overload */;
	__classmethod bool __fastcall AreFilesDelivered(const TApkFileInfo &MainFile, const TApkFileInfo &PatchFile)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TApkExpansion() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TApkExpansion() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnObbStateChangeCallback)(TObb* Obb, const TObbStateKind State);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TObb : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	_di_JObb FObb;
	TOnObbStateChangeCallback FOnStateChange;
	
public:
	__fastcall TObb(const TApkFileInfo &ApkFile)/* overload */;
	HIDESBASE System::UnicodeString __fastcall GetName();
	System::UnicodeString __fastcall GetPath();
	System::UnicodeString __fastcall GetMountedPath();
	System::UnicodeString __fastcall GetResourcePath(System::UnicodeString filePath);
	bool __fastcall IsMounted();
	void __fastcall Mount(TOnObbStateChangeCallback Callback);
	void __cdecl onObbStateChange(Androidapi::Jni::Javatypes::_di_JString path, int state);
	void __fastcall Unmount(TOnObbStateChangeCallback Callback, bool Force);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TObb() { }
	
private:
	void *__JObb_ObbListener;	// JObb_ObbListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {710A8D6A-4E6B-44A7-A552-4BFCE8939BBE}
	operator _di_JObb_ObbListener()
	{
		_di_JObb_ObbListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator JObb_ObbListener*(void) { return (JObb_ObbListener*)&__JObb_ObbListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnDownloadStateChange)(TDownloadStateKind NewState);

typedef void __fastcall (__closure *TOnDownloadProgress)(const TDownloadProgressInfo &DownloadInfo);

class PASCALIMPLEMENTATION TNativeDownloader : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	_di_JNativeDownloaderLauncher FDownloader;
	TOnDownloadStateChange FStateChangeCallback;
	TOnDownloadProgress FDownloadProgressCallback;
	TApkFileInfo FMainFile;
	TApkFileInfo FPatchFile;
	
public:
	__fastcall TNativeDownloader(System::UnicodeString PublicKey, System::Byte *Salt, const int Salt_High, const TApkFileInfo &MainFile)/* overload */;
	__fastcall TNativeDownloader(System::UnicodeString PublicKey, System::Byte *Salt, const int Salt_High, const TApkFileInfo &MainFile, const TApkFileInfo &PatchFile)/* overload */;
	void __fastcall ClearCallbacks();
	void __fastcall DoLaunch();
	bool __fastcall Launch(TOnDownloadStateChange StateChangeCallback, TOnDownloadProgress DownloadProgressCallback);
	void __fastcall requestAbortDownload();
	void __fastcall requestContinueDownload();
	void __fastcall requestPauseDownload();
	void __cdecl onDownloadProgress(_di_JDownloadProgressInfo progress);
	void __cdecl onDownloadStateChanged(int newState);
	void __fastcall onStart();
	void __fastcall onStop();
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TNativeDownloader() { }
	
private:
	void *__JApkDownloaderListener;	// JApkDownloaderListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {782B8878-9306-4A8C-A2FC-093A82144484}
	operator _di_JApkDownloaderListener()
	{
		_di_JApkDownloaderListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator JApkDownloaderListener*(void) { return (JApkDownloaderListener*)&__JApkDownloaderListener; }
	#endif
	
};


typedef void __fastcall (__closure *TRunMethod)(void);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TUIThread : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TRunMethod FRunMethod;
	
public:
	__fastcall TUIThread(TRunMethod RunMethod)/* overload */;
	void __cdecl run();
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TUIThread() { }
	
private:
	void *__JRunnable;	// Androidapi::Jni::Javatypes::JRunnable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BC131B27-7A72-4CAF-BB8E-170B8359B22E}
	operator Androidapi::Jni::Javatypes::_di_JRunnable()
	{
		Androidapi::Jni::Javatypes::_di_JRunnable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Javatypes::JRunnable*(void) { return (Androidapi::Jni::Javatypes::JRunnable*)&__JRunnable; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Apkexpansion */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_APKEXPANSION)
using namespace Androidapi::Jni::Apkexpansion;
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
#endif	// Androidapi_Jni_ApkexpansionHPP
