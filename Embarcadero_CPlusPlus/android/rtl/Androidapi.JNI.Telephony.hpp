// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Telephony.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_TelephonyHPP
#define Androidapi_Jni_TelephonyHPP

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
namespace Telephony
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JCarrierConfigManagerClass;
typedef System::DelphiInterface<JCarrierConfigManagerClass> _di_JCarrierConfigManagerClass;
__interface DELPHIINTERFACE JCarrierConfigManager;
typedef System::DelphiInterface<JCarrierConfigManager> _di_JCarrierConfigManager;
class DELPHICLASS TJCarrierConfigManager;
__interface DELPHIINTERFACE JCellIdentityCdmaClass;
typedef System::DelphiInterface<JCellIdentityCdmaClass> _di_JCellIdentityCdmaClass;
__interface DELPHIINTERFACE JCellIdentityCdma;
typedef System::DelphiInterface<JCellIdentityCdma> _di_JCellIdentityCdma;
class DELPHICLASS TJCellIdentityCdma;
__interface DELPHIINTERFACE JCellIdentityGsmClass;
typedef System::DelphiInterface<JCellIdentityGsmClass> _di_JCellIdentityGsmClass;
__interface DELPHIINTERFACE JCellIdentityGsm;
typedef System::DelphiInterface<JCellIdentityGsm> _di_JCellIdentityGsm;
class DELPHICLASS TJCellIdentityGsm;
__interface DELPHIINTERFACE JCellIdentityLteClass;
typedef System::DelphiInterface<JCellIdentityLteClass> _di_JCellIdentityLteClass;
__interface DELPHIINTERFACE JCellIdentityLte;
typedef System::DelphiInterface<JCellIdentityLte> _di_JCellIdentityLte;
class DELPHICLASS TJCellIdentityLte;
__interface DELPHIINTERFACE JCellIdentityWcdmaClass;
typedef System::DelphiInterface<JCellIdentityWcdmaClass> _di_JCellIdentityWcdmaClass;
__interface DELPHIINTERFACE JCellIdentityWcdma;
typedef System::DelphiInterface<JCellIdentityWcdma> _di_JCellIdentityWcdma;
class DELPHICLASS TJCellIdentityWcdma;
__interface DELPHIINTERFACE JCellInfoClass;
typedef System::DelphiInterface<JCellInfoClass> _di_JCellInfoClass;
__interface DELPHIINTERFACE JCellInfo;
typedef System::DelphiInterface<JCellInfo> _di_JCellInfo;
class DELPHICLASS TJCellInfo;
__interface DELPHIINTERFACE JCellInfoCdmaClass;
typedef System::DelphiInterface<JCellInfoCdmaClass> _di_JCellInfoCdmaClass;
__interface DELPHIINTERFACE JCellInfoCdma;
typedef System::DelphiInterface<JCellInfoCdma> _di_JCellInfoCdma;
class DELPHICLASS TJCellInfoCdma;
__interface DELPHIINTERFACE JCellInfoGsmClass;
typedef System::DelphiInterface<JCellInfoGsmClass> _di_JCellInfoGsmClass;
__interface DELPHIINTERFACE JCellInfoGsm;
typedef System::DelphiInterface<JCellInfoGsm> _di_JCellInfoGsm;
class DELPHICLASS TJCellInfoGsm;
__interface DELPHIINTERFACE JCellInfoLteClass;
typedef System::DelphiInterface<JCellInfoLteClass> _di_JCellInfoLteClass;
__interface DELPHIINTERFACE JCellInfoLte;
typedef System::DelphiInterface<JCellInfoLte> _di_JCellInfoLte;
class DELPHICLASS TJCellInfoLte;
__interface DELPHIINTERFACE JCellInfoWcdmaClass;
typedef System::DelphiInterface<JCellInfoWcdmaClass> _di_JCellInfoWcdmaClass;
__interface DELPHIINTERFACE JCellInfoWcdma;
typedef System::DelphiInterface<JCellInfoWcdma> _di_JCellInfoWcdma;
class DELPHICLASS TJCellInfoWcdma;
__interface DELPHIINTERFACE JCellLocationClass;
typedef System::DelphiInterface<JCellLocationClass> _di_JCellLocationClass;
__interface DELPHIINTERFACE JCellLocation;
typedef System::DelphiInterface<JCellLocation> _di_JCellLocation;
class DELPHICLASS TJCellLocation;
__interface DELPHIINTERFACE JCellSignalStrengthClass;
typedef System::DelphiInterface<JCellSignalStrengthClass> _di_JCellSignalStrengthClass;
__interface DELPHIINTERFACE JCellSignalStrength;
typedef System::DelphiInterface<JCellSignalStrength> _di_JCellSignalStrength;
class DELPHICLASS TJCellSignalStrength;
__interface DELPHIINTERFACE JCellSignalStrengthCdmaClass;
typedef System::DelphiInterface<JCellSignalStrengthCdmaClass> _di_JCellSignalStrengthCdmaClass;
__interface DELPHIINTERFACE JCellSignalStrengthCdma;
typedef System::DelphiInterface<JCellSignalStrengthCdma> _di_JCellSignalStrengthCdma;
class DELPHICLASS TJCellSignalStrengthCdma;
__interface DELPHIINTERFACE JCellSignalStrengthGsmClass;
typedef System::DelphiInterface<JCellSignalStrengthGsmClass> _di_JCellSignalStrengthGsmClass;
__interface DELPHIINTERFACE JCellSignalStrengthGsm;
typedef System::DelphiInterface<JCellSignalStrengthGsm> _di_JCellSignalStrengthGsm;
class DELPHICLASS TJCellSignalStrengthGsm;
__interface DELPHIINTERFACE JCellSignalStrengthLteClass;
typedef System::DelphiInterface<JCellSignalStrengthLteClass> _di_JCellSignalStrengthLteClass;
__interface DELPHIINTERFACE JCellSignalStrengthLte;
typedef System::DelphiInterface<JCellSignalStrengthLte> _di_JCellSignalStrengthLte;
class DELPHICLASS TJCellSignalStrengthLte;
__interface DELPHIINTERFACE JCellSignalStrengthWcdmaClass;
typedef System::DelphiInterface<JCellSignalStrengthWcdmaClass> _di_JCellSignalStrengthWcdmaClass;
__interface DELPHIINTERFACE JCellSignalStrengthWcdma;
typedef System::DelphiInterface<JCellSignalStrengthWcdma> _di_JCellSignalStrengthWcdma;
class DELPHICLASS TJCellSignalStrengthWcdma;
__interface DELPHIINTERFACE JPhoneStateListenerClass;
typedef System::DelphiInterface<JPhoneStateListenerClass> _di_JPhoneStateListenerClass;
__interface DELPHIINTERFACE JPhoneStateListener;
typedef System::DelphiInterface<JPhoneStateListener> _di_JPhoneStateListener;
class DELPHICLASS TJPhoneStateListener;
__interface DELPHIINTERFACE JCustomPhoneStateListenerClass;
typedef System::DelphiInterface<JCustomPhoneStateListenerClass> _di_JCustomPhoneStateListenerClass;
__interface DELPHIINTERFACE JCustomPhoneStateListener;
typedef System::DelphiInterface<JCustomPhoneStateListener> _di_JCustomPhoneStateListener;
class DELPHICLASS TJCustomPhoneStateListener;
__interface DELPHIINTERFACE JICustomPhoneStateListenerClass;
typedef System::DelphiInterface<JICustomPhoneStateListenerClass> _di_JICustomPhoneStateListenerClass;
__interface DELPHIINTERFACE JICustomPhoneStateListener;
typedef System::DelphiInterface<JICustomPhoneStateListener> _di_JICustomPhoneStateListener;
class DELPHICLASS TJICustomPhoneStateListener;
__interface DELPHIINTERFACE JIccOpenLogicalChannelResponseClass;
typedef System::DelphiInterface<JIccOpenLogicalChannelResponseClass> _di_JIccOpenLogicalChannelResponseClass;
__interface DELPHIINTERFACE JIccOpenLogicalChannelResponse;
typedef System::DelphiInterface<JIccOpenLogicalChannelResponse> _di_JIccOpenLogicalChannelResponse;
class DELPHICLASS TJIccOpenLogicalChannelResponse;
__interface DELPHIINTERFACE JNeighboringCellInfoClass;
typedef System::DelphiInterface<JNeighboringCellInfoClass> _di_JNeighboringCellInfoClass;
__interface DELPHIINTERFACE JNeighboringCellInfo;
typedef System::DelphiInterface<JNeighboringCellInfo> _di_JNeighboringCellInfo;
class DELPHICLASS TJNeighboringCellInfo;
__interface DELPHIINTERFACE JPhoneNumberFormattingTextWatcherClass;
typedef System::DelphiInterface<JPhoneNumberFormattingTextWatcherClass> _di_JPhoneNumberFormattingTextWatcherClass;
__interface DELPHIINTERFACE JPhoneNumberFormattingTextWatcher;
typedef System::DelphiInterface<JPhoneNumberFormattingTextWatcher> _di_JPhoneNumberFormattingTextWatcher;
class DELPHICLASS TJPhoneNumberFormattingTextWatcher;
__interface DELPHIINTERFACE JPhoneNumberUtilsClass;
typedef System::DelphiInterface<JPhoneNumberUtilsClass> _di_JPhoneNumberUtilsClass;
__interface DELPHIINTERFACE JPhoneNumberUtils;
typedef System::DelphiInterface<JPhoneNumberUtils> _di_JPhoneNumberUtils;
class DELPHICLASS TJPhoneNumberUtils;
__interface DELPHIINTERFACE JServiceStateClass;
typedef System::DelphiInterface<JServiceStateClass> _di_JServiceStateClass;
__interface DELPHIINTERFACE JServiceState;
typedef System::DelphiInterface<JServiceState> _di_JServiceState;
class DELPHICLASS TJServiceState;
__interface DELPHIINTERFACE JSignalStrengthClass;
typedef System::DelphiInterface<JSignalStrengthClass> _di_JSignalStrengthClass;
__interface DELPHIINTERFACE JSignalStrength;
typedef System::DelphiInterface<JSignalStrength> _di_JSignalStrength;
class DELPHICLASS TJSignalStrength;
__interface DELPHIINTERFACE JSmsManagerClass;
typedef System::DelphiInterface<JSmsManagerClass> _di_JSmsManagerClass;
__interface DELPHIINTERFACE JSmsManager;
typedef System::DelphiInterface<JSmsManager> _di_JSmsManager;
class DELPHICLASS TJSmsManager;
__interface DELPHIINTERFACE JSmsMessageClass;
typedef System::DelphiInterface<JSmsMessageClass> _di_JSmsMessageClass;
__interface DELPHIINTERFACE JSmsMessage;
typedef System::DelphiInterface<JSmsMessage> _di_JSmsMessage;
class DELPHICLASS TJSmsMessage;
__interface DELPHIINTERFACE JSmsMessage_MessageClassClass;
typedef System::DelphiInterface<JSmsMessage_MessageClassClass> _di_JSmsMessage_MessageClassClass;
__interface DELPHIINTERFACE JSmsMessage_MessageClass;
typedef System::DelphiInterface<JSmsMessage_MessageClass> _di_JSmsMessage_MessageClass;
class DELPHICLASS TJSmsMessage_MessageClass;
__interface DELPHIINTERFACE JSmsMessage_SubmitPduClass;
typedef System::DelphiInterface<JSmsMessage_SubmitPduClass> _di_JSmsMessage_SubmitPduClass;
__interface DELPHIINTERFACE JSmsMessage_SubmitPdu;
typedef System::DelphiInterface<JSmsMessage_SubmitPdu> _di_JSmsMessage_SubmitPdu;
class DELPHICLASS TJSmsMessage_SubmitPdu;
__interface DELPHIINTERFACE JSubscriptionInfoClass;
typedef System::DelphiInterface<JSubscriptionInfoClass> _di_JSubscriptionInfoClass;
__interface DELPHIINTERFACE JSubscriptionInfo;
typedef System::DelphiInterface<JSubscriptionInfo> _di_JSubscriptionInfo;
class DELPHICLASS TJSubscriptionInfo;
__interface DELPHIINTERFACE JSubscriptionManagerClass;
typedef System::DelphiInterface<JSubscriptionManagerClass> _di_JSubscriptionManagerClass;
__interface DELPHIINTERFACE JSubscriptionManager;
typedef System::DelphiInterface<JSubscriptionManager> _di_JSubscriptionManager;
class DELPHICLASS TJSubscriptionManager;
__interface DELPHIINTERFACE JSubscriptionManager_OnSubscriptionsChangedListenerClass;
typedef System::DelphiInterface<JSubscriptionManager_OnSubscriptionsChangedListenerClass> _di_JSubscriptionManager_OnSubscriptionsChangedListenerClass;
__interface DELPHIINTERFACE JSubscriptionManager_OnSubscriptionsChangedListener;
typedef System::DelphiInterface<JSubscriptionManager_OnSubscriptionsChangedListener> _di_JSubscriptionManager_OnSubscriptionsChangedListener;
class DELPHICLASS TJSubscriptionManager_OnSubscriptionsChangedListener;
__interface DELPHIINTERFACE JTelephonyManagerClass;
typedef System::DelphiInterface<JTelephonyManagerClass> _di_JTelephonyManagerClass;
__interface DELPHIINTERFACE JTelephonyManager;
typedef System::DelphiInterface<JTelephonyManager> _di_JTelephonyManager;
class DELPHICLASS TJTelephonyManager;
__interface DELPHIINTERFACE JTelephonyManager_UssdResponseCallbackClass;
typedef System::DelphiInterface<JTelephonyManager_UssdResponseCallbackClass> _di_JTelephonyManager_UssdResponseCallbackClass;
__interface DELPHIINTERFACE JTelephonyManager_UssdResponseCallback;
typedef System::DelphiInterface<JTelephonyManager_UssdResponseCallback> _di_JTelephonyManager_UssdResponseCallback;
class DELPHICLASS TJTelephonyManager_UssdResponseCallback;
__interface DELPHIINTERFACE JVisualVoicemailServiceClass;
typedef System::DelphiInterface<JVisualVoicemailServiceClass> _di_JVisualVoicemailServiceClass;
__interface DELPHIINTERFACE JVisualVoicemailService;
typedef System::DelphiInterface<JVisualVoicemailService> _di_JVisualVoicemailService;
class DELPHICLASS TJVisualVoicemailService;
__interface DELPHIINTERFACE JVisualVoicemailService_VisualVoicemailTaskClass;
typedef System::DelphiInterface<JVisualVoicemailService_VisualVoicemailTaskClass> _di_JVisualVoicemailService_VisualVoicemailTaskClass;
__interface DELPHIINTERFACE JVisualVoicemailService_VisualVoicemailTask;
typedef System::DelphiInterface<JVisualVoicemailService_VisualVoicemailTask> _di_JVisualVoicemailService_VisualVoicemailTask;
class DELPHICLASS TJVisualVoicemailService_VisualVoicemailTask;
__interface DELPHIINTERFACE JVisualVoicemailSmsClass;
typedef System::DelphiInterface<JVisualVoicemailSmsClass> _di_JVisualVoicemailSmsClass;
__interface DELPHIINTERFACE JVisualVoicemailSms;
typedef System::DelphiInterface<JVisualVoicemailSms> _di_JVisualVoicemailSms;
class DELPHICLASS TJVisualVoicemailSms;
__interface DELPHIINTERFACE JVisualVoicemailSmsFilterSettingsClass;
typedef System::DelphiInterface<JVisualVoicemailSmsFilterSettingsClass> _di_JVisualVoicemailSmsFilterSettingsClass;
__interface DELPHIINTERFACE JVisualVoicemailSmsFilterSettings;
typedef System::DelphiInterface<JVisualVoicemailSmsFilterSettings> _di_JVisualVoicemailSmsFilterSettings;
class DELPHICLASS TJVisualVoicemailSmsFilterSettings;
__interface DELPHIINTERFACE JVisualVoicemailSmsFilterSettings_BuilderClass;
typedef System::DelphiInterface<JVisualVoicemailSmsFilterSettings_BuilderClass> _di_JVisualVoicemailSmsFilterSettings_BuilderClass;
__interface DELPHIINTERFACE JVisualVoicemailSmsFilterSettings_Builder;
typedef System::DelphiInterface<JVisualVoicemailSmsFilterSettings_Builder> _di_JVisualVoicemailSmsFilterSettings_Builder;
class DELPHICLASS TJVisualVoicemailSmsFilterSettings_Builder;
__interface DELPHIINTERFACE JCdmaCellLocationClass;
typedef System::DelphiInterface<JCdmaCellLocationClass> _di_JCdmaCellLocationClass;
__interface DELPHIINTERFACE JCdmaCellLocation;
typedef System::DelphiInterface<JCdmaCellLocation> _di_JCdmaCellLocation;
class DELPHICLASS TJCdmaCellLocation;
__interface DELPHIINTERFACE JGsmCellLocationClass;
typedef System::DelphiInterface<JGsmCellLocationClass> _di_JGsmCellLocationClass;
__interface DELPHIINTERFACE JGsmCellLocation;
typedef System::DelphiInterface<JGsmCellLocation> _di_JGsmCellLocation;
class DELPHICLASS TJGsmCellLocation;
__interface DELPHIINTERFACE Jgsm_SmsManagerClass;
typedef System::DelphiInterface<Jgsm_SmsManagerClass> _di_Jgsm_SmsManagerClass;
__interface DELPHIINTERFACE Jgsm_SmsManager;
typedef System::DelphiInterface<Jgsm_SmsManager> _di_Jgsm_SmsManager;
class DELPHICLASS TJgsm_SmsManager;
__interface DELPHIINTERFACE Jgsm_SmsMessageClass;
typedef System::DelphiInterface<Jgsm_SmsMessageClass> _di_Jgsm_SmsMessageClass;
__interface DELPHIINTERFACE Jgsm_SmsMessage;
typedef System::DelphiInterface<Jgsm_SmsMessage> _di_Jgsm_SmsMessage;
class DELPHICLASS TJgsm_SmsMessage;
__interface DELPHIINTERFACE Jgsm_SmsMessage_MessageClassClass;
typedef System::DelphiInterface<Jgsm_SmsMessage_MessageClassClass> _di_Jgsm_SmsMessage_MessageClassClass;
__interface DELPHIINTERFACE Jgsm_SmsMessage_MessageClass;
typedef System::DelphiInterface<Jgsm_SmsMessage_MessageClass> _di_Jgsm_SmsMessage_MessageClass;
class DELPHICLASS TJgsm_SmsMessage_MessageClass;
__interface DELPHIINTERFACE Jgsm_SmsMessage_SubmitPduClass;
typedef System::DelphiInterface<Jgsm_SmsMessage_SubmitPduClass> _di_Jgsm_SmsMessage_SubmitPduClass;
__interface DELPHIINTERFACE Jgsm_SmsMessage_SubmitPdu;
typedef System::DelphiInterface<Jgsm_SmsMessage_SubmitPdu> _di_Jgsm_SmsMessage_SubmitPdu;
class DELPHICLASS TJgsm_SmsMessage_SubmitPdu;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{8164A855-B878-453D-BE18-688B0A72A983}") JCarrierConfigManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CARRIER_CONFIG_CHANGED() = 0 ;
	virtual int __cdecl _GetDATA_CYCLE_THRESHOLD_DISABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ADDITIONAL_CALL_SETTING_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_ADDING_APNS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_ADD_CALL_DURING_VIDEO_CALL_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_EMERGENCY_NUMBERS_IN_CALL_LOG_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_EMERGENCY_VIDEO_CALLS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_LOCAL_DTMF_TONES_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_MERGE_WIFI_CALLS_WHEN_VOWIFI_OFF_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALLOW_NON_EMERGENCY_CALLS_IN_ECM_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ALWAYS_SHOW_EMERGENCY_ALERT_ONOFF_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_APN_EXPAND_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_AUTO_RETRY_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CALL_FORWARDING_BLOCKS_WHILE_ROAMING_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_ALLOW_TURNOFF_IMS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_DATA_CALL_PERMANENT_FAILURE_STRINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_FORCE_DISABLE_ETWS_CMAS_TEST_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_IMS_GBA_REQUIRED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_INSTANT_LETTERING_AVAILABLE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_INSTANT_LETTERING_ENCODING_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_INSTANT_LETTERING_ESCAPED_CHARS_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_INSTANT_LETTERING_INVALID_CHARS_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_INSTANT_LETTERING_LENGTH_LIMIT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_SETTINGS_ENABLE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_USE_IMS_FIRST_FOR_EMERGENCY_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VOLTE_AVAILABLE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VOLTE_PROVISIONED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VOLTE_PROVISIONING_REQUIRED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VOLTE_TTY_SUPPORTED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VT_AVAILABLE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VVM_PACKAGE_NAME_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_VVM_PACKAGE_NAME_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_WFC_IMS_AVAILABLE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CARRIER_WFC_SUPPORTS_WIFI_ONLY_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CDMA_3WAYCALL_FLASH_DELAY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CDMA_DTMF_TONE_DELAY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CDMA_NONROAMING_NETWORKS_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CDMA_ROAMING_NETWORKS_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CI_ACTION_ON_SYS_UPDATE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_VAL_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CI_ACTION_ON_SYS_UPDATE_INTENT_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CONFIG_IMS_PACKAGE_OVERRIDE_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CSP_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DATA_LIMIT_THRESHOLD_BYTES_LONG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DATA_WARNING_THRESHOLD_BYTES_LONG() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DEFAULT_SIM_CALL_MANAGER_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DEFAULT_VM_NUMBER_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DIAL_STRING_REPLACE_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DISABLE_CDMA_ACTIVATION_CODE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DROP_VIDEO_CALL_WHEN_ANSWERING_AUDIO_CALL_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DTMF_TYPE_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_DURATION_BLOCKING_DISABLED_AFTER_EMERGENCY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_EDITABLE_ENHANCED_4G_LTE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_EDITABLE_VOICEMAIL_NUMBER_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ENABLE_DIALER_KEY_VIBRATION_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_FORCE_HOME_NETWORK_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_GSM_DTMF_TONE_DELAY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_GSM_NONROAMING_NETWORKS_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_GSM_ROAMING_NETWORKS_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HAS_IN_CALL_NOISE_SUPPRESSION_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HIDE_CARRIER_NETWORK_SETTINGS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HIDE_ENHANCED_4G_LTE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HIDE_IMS_APN_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HIDE_PREFERRED_NETWORK_TYPE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_HIDE_SIM_LOCK_SETTINGS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_IGNORE_SIM_NETWORK_LOCKED_EVENTS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_IMS_CONFERENCE_SIZE_LIMIT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_IMS_DTMF_TONE_DELAY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_IS_IMS_CONFERENCE_SIZE_ENFORCED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MDN_IS_ADDITIONAL_VOICEMAIL_NUMBER_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_ALIAS_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_ALIAS_MAX_CHARS_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_ALIAS_MIN_CHARS_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_ALLOW_ATTACH_AUDIO_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_APPEND_TRANSACTION_ID_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_EMAIL_GATEWAY_NUMBER_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_GROUP_MMS_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_HTTP_PARAMS_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_HTTP_SOCKET_TIMEOUT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MAX_IMAGE_HEIGHT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MAX_IMAGE_WIDTH_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MAX_MESSAGE_SIZE_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MESSAGE_TEXT_MAX_SIZE_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MMS_DELIVERY_REPORT_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MMS_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MMS_READ_REPORT_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_MULTIPART_SMS_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_NAI_SUFFIX_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_NOTIFY_WAP_MMSC_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_RECIPIENT_LIMIT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SHOW_CELL_BROADCAST_APP_LINKS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SMS_DELIVERY_REPORT_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SMS_TO_MMS_TEXT_THRESHOLD_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SUBJECT_MAX_LENGTH_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SUPPORT_HTTP_CHARSET_HEADER_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_SUPPORT_MMS_CONTENT_DISPOSITION_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_UA_PROF_TAG_NAME_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_UA_PROF_URL_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MMS_USER_AGENT_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_MONTHLY_DATA_CYCLE_DAY_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ONLY_SINGLE_DC_ALLOWED_INT_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_OPERATOR_SELECTION_EXPAND_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PREFER_2G_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_RCS_CONFIG_SERVER_URL_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_REQUIRE_ENTITLEMENT_CHECKS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_RESTART_RADIO_ON_PDP_FAIL_REGULAR_DEACTIVATION_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SHOW_APN_SETTING_CDMA_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SHOW_CDMA_CHOICES_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SHOW_ICCID_IN_SIM_STATUS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SHOW_ONSCREEN_DIAL_BUTTON_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SIMPLIFIED_NETWORK_SETTINGS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SIM_NETWORK_UNLOCK_ALLOW_DISMISS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SMS_REQUIRES_DESTINATION_NUMBER_CONVERSION_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SUPPORT_3GPP_CALL_FORWARDING_WHILE_ROAMING_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SUPPORT_CONFERENCE_CALL_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SUPPORT_PAUSE_IMS_VIDEO_CALLS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_SUPPORT_SWAP_AFTER_MERGE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_TREAT_DOWNGRADED_VIDEO_CALLS_AS_VIDEO_CALLS_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_USE_HFA_FOR_PROVISIONING_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_USE_OTASP_FOR_PROVISIONING_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_USE_RCS_PRESENCE_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VOICEMAIL_NOTIFICATION_PERSISTENT_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VOICE_PRIVACY_DISABLE_UI_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VOLTE_REPLACEMENT_RAT_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_CELLULAR_DATA_REQUIRED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_CLIENT_PREFIX_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_DESTINATION_NUMBER_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_DISABLED_CAPABILITIES_STRING_ARRAY() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_LEGACY_MODE_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_PORT_NUMBER_INT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_PREFETCH_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_SSL_ENABLED_BOOL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_VVM_TYPE_STRING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_WORLD_PHONE_BOOL() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CARRIER_CONFIG_CHANGED = {read=_GetACTION_CARRIER_CONFIG_CHANGED};
	__property int DATA_CYCLE_THRESHOLD_DISABLED = {read=_GetDATA_CYCLE_THRESHOLD_DISABLED};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ADDITIONAL_CALL_SETTING_BOOL = {read=_GetKEY_ADDITIONAL_CALL_SETTING_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_ADDING_APNS_BOOL = {read=_GetKEY_ALLOW_ADDING_APNS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_ADD_CALL_DURING_VIDEO_CALL_BOOL = {read=_GetKEY_ALLOW_ADD_CALL_DURING_VIDEO_CALL_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_EMERGENCY_NUMBERS_IN_CALL_LOG_BOOL = {read=_GetKEY_ALLOW_EMERGENCY_NUMBERS_IN_CALL_LOG_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_EMERGENCY_VIDEO_CALLS_BOOL = {read=_GetKEY_ALLOW_EMERGENCY_VIDEO_CALLS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_LOCAL_DTMF_TONES_BOOL = {read=_GetKEY_ALLOW_LOCAL_DTMF_TONES_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_MERGE_WIFI_CALLS_WHEN_VOWIFI_OFF_BOOL = {read=_GetKEY_ALLOW_MERGE_WIFI_CALLS_WHEN_VOWIFI_OFF_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALLOW_NON_EMERGENCY_CALLS_IN_ECM_BOOL = {read=_GetKEY_ALLOW_NON_EMERGENCY_CALLS_IN_ECM_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ALWAYS_SHOW_EMERGENCY_ALERT_ONOFF_BOOL = {read=_GetKEY_ALWAYS_SHOW_EMERGENCY_ALERT_ONOFF_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_APN_EXPAND_BOOL = {read=_GetKEY_APN_EXPAND_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_AUTO_RETRY_ENABLED_BOOL = {read=_GetKEY_AUTO_RETRY_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CALL_FORWARDING_BLOCKS_WHILE_ROAMING_STRING_ARRAY = {read=_GetKEY_CALL_FORWARDING_BLOCKS_WHILE_ROAMING_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_ALLOW_TURNOFF_IMS_BOOL = {read=_GetKEY_CARRIER_ALLOW_TURNOFF_IMS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_DATA_CALL_PERMANENT_FAILURE_STRINGS = {read=_GetKEY_CARRIER_DATA_CALL_PERMANENT_FAILURE_STRINGS};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_FORCE_DISABLE_ETWS_CMAS_TEST_BOOL = {read=_GetKEY_CARRIER_FORCE_DISABLE_ETWS_CMAS_TEST_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_IMS_GBA_REQUIRED_BOOL = {read=_GetKEY_CARRIER_IMS_GBA_REQUIRED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_INSTANT_LETTERING_AVAILABLE_BOOL = {read=_GetKEY_CARRIER_INSTANT_LETTERING_AVAILABLE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_INSTANT_LETTERING_ENCODING_STRING = {read=_GetKEY_CARRIER_INSTANT_LETTERING_ENCODING_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_INSTANT_LETTERING_ESCAPED_CHARS_STRING = {read=_GetKEY_CARRIER_INSTANT_LETTERING_ESCAPED_CHARS_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_INSTANT_LETTERING_INVALID_CHARS_STRING = {read=_GetKEY_CARRIER_INSTANT_LETTERING_INVALID_CHARS_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_INSTANT_LETTERING_LENGTH_LIMIT_INT = {read=_GetKEY_CARRIER_INSTANT_LETTERING_LENGTH_LIMIT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_SETTINGS_ENABLE_BOOL = {read=_GetKEY_CARRIER_SETTINGS_ENABLE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_USE_IMS_FIRST_FOR_EMERGENCY_BOOL = {read=_GetKEY_CARRIER_USE_IMS_FIRST_FOR_EMERGENCY_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VOLTE_AVAILABLE_BOOL = {read=_GetKEY_CARRIER_VOLTE_AVAILABLE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VOLTE_PROVISIONED_BOOL = {read=_GetKEY_CARRIER_VOLTE_PROVISIONED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VOLTE_PROVISIONING_REQUIRED_BOOL = {read=_GetKEY_CARRIER_VOLTE_PROVISIONING_REQUIRED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VOLTE_TTY_SUPPORTED_BOOL = {read=_GetKEY_CARRIER_VOLTE_TTY_SUPPORTED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VT_AVAILABLE_BOOL = {read=_GetKEY_CARRIER_VT_AVAILABLE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VVM_PACKAGE_NAME_STRING = {read=_GetKEY_CARRIER_VVM_PACKAGE_NAME_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_VVM_PACKAGE_NAME_STRING_ARRAY = {read=_GetKEY_CARRIER_VVM_PACKAGE_NAME_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_WFC_IMS_AVAILABLE_BOOL = {read=_GetKEY_CARRIER_WFC_IMS_AVAILABLE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CARRIER_WFC_SUPPORTS_WIFI_ONLY_BOOL = {read=_GetKEY_CARRIER_WFC_SUPPORTS_WIFI_ONLY_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CDMA_3WAYCALL_FLASH_DELAY_INT = {read=_GetKEY_CDMA_3WAYCALL_FLASH_DELAY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CDMA_DTMF_TONE_DELAY_INT = {read=_GetKEY_CDMA_DTMF_TONE_DELAY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CDMA_NONROAMING_NETWORKS_STRING_ARRAY = {read=_GetKEY_CDMA_NONROAMING_NETWORKS_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CDMA_ROAMING_NETWORKS_STRING_ARRAY = {read=_GetKEY_CDMA_ROAMING_NETWORKS_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CI_ACTION_ON_SYS_UPDATE_BOOL = {read=_GetKEY_CI_ACTION_ON_SYS_UPDATE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_STRING = {read=_GetKEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_VAL_STRING = {read=_GetKEY_CI_ACTION_ON_SYS_UPDATE_EXTRA_VAL_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CI_ACTION_ON_SYS_UPDATE_INTENT_STRING = {read=_GetKEY_CI_ACTION_ON_SYS_UPDATE_INTENT_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CONFIG_IMS_PACKAGE_OVERRIDE_STRING = {read=_GetKEY_CONFIG_IMS_PACKAGE_OVERRIDE_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CSP_ENABLED_BOOL = {read=_GetKEY_CSP_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DATA_LIMIT_THRESHOLD_BYTES_LONG = {read=_GetKEY_DATA_LIMIT_THRESHOLD_BYTES_LONG};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DATA_WARNING_THRESHOLD_BYTES_LONG = {read=_GetKEY_DATA_WARNING_THRESHOLD_BYTES_LONG};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DEFAULT_SIM_CALL_MANAGER_STRING = {read=_GetKEY_DEFAULT_SIM_CALL_MANAGER_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DEFAULT_VM_NUMBER_STRING = {read=_GetKEY_DEFAULT_VM_NUMBER_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DIAL_STRING_REPLACE_STRING_ARRAY = {read=_GetKEY_DIAL_STRING_REPLACE_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DISABLE_CDMA_ACTIVATION_CODE_BOOL = {read=_GetKEY_DISABLE_CDMA_ACTIVATION_CODE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DROP_VIDEO_CALL_WHEN_ANSWERING_AUDIO_CALL_BOOL = {read=_GetKEY_DROP_VIDEO_CALL_WHEN_ANSWERING_AUDIO_CALL_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DTMF_TYPE_ENABLED_BOOL = {read=_GetKEY_DTMF_TYPE_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_DURATION_BLOCKING_DISABLED_AFTER_EMERGENCY_INT = {read=_GetKEY_DURATION_BLOCKING_DISABLED_AFTER_EMERGENCY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_EDITABLE_ENHANCED_4G_LTE_BOOL = {read=_GetKEY_EDITABLE_ENHANCED_4G_LTE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_EDITABLE_VOICEMAIL_NUMBER_BOOL = {read=_GetKEY_EDITABLE_VOICEMAIL_NUMBER_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ENABLE_DIALER_KEY_VIBRATION_BOOL = {read=_GetKEY_ENABLE_DIALER_KEY_VIBRATION_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_FORCE_HOME_NETWORK_BOOL = {read=_GetKEY_FORCE_HOME_NETWORK_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_GSM_DTMF_TONE_DELAY_INT = {read=_GetKEY_GSM_DTMF_TONE_DELAY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_GSM_NONROAMING_NETWORKS_STRING_ARRAY = {read=_GetKEY_GSM_NONROAMING_NETWORKS_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_GSM_ROAMING_NETWORKS_STRING_ARRAY = {read=_GetKEY_GSM_ROAMING_NETWORKS_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HAS_IN_CALL_NOISE_SUPPRESSION_BOOL = {read=_GetKEY_HAS_IN_CALL_NOISE_SUPPRESSION_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HIDE_CARRIER_NETWORK_SETTINGS_BOOL = {read=_GetKEY_HIDE_CARRIER_NETWORK_SETTINGS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HIDE_ENHANCED_4G_LTE_BOOL = {read=_GetKEY_HIDE_ENHANCED_4G_LTE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HIDE_IMS_APN_BOOL = {read=_GetKEY_HIDE_IMS_APN_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HIDE_PREFERRED_NETWORK_TYPE_BOOL = {read=_GetKEY_HIDE_PREFERRED_NETWORK_TYPE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_HIDE_SIM_LOCK_SETTINGS_BOOL = {read=_GetKEY_HIDE_SIM_LOCK_SETTINGS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_IGNORE_SIM_NETWORK_LOCKED_EVENTS_BOOL = {read=_GetKEY_IGNORE_SIM_NETWORK_LOCKED_EVENTS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_IMS_CONFERENCE_SIZE_LIMIT_INT = {read=_GetKEY_IMS_CONFERENCE_SIZE_LIMIT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_IMS_DTMF_TONE_DELAY_INT = {read=_GetKEY_IMS_DTMF_TONE_DELAY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_IS_IMS_CONFERENCE_SIZE_ENFORCED_BOOL = {read=_GetKEY_IS_IMS_CONFERENCE_SIZE_ENFORCED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MDN_IS_ADDITIONAL_VOICEMAIL_NUMBER_BOOL = {read=_GetKEY_MDN_IS_ADDITIONAL_VOICEMAIL_NUMBER_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_ALIAS_ENABLED_BOOL = {read=_GetKEY_MMS_ALIAS_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_ALIAS_MAX_CHARS_INT = {read=_GetKEY_MMS_ALIAS_MAX_CHARS_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_ALIAS_MIN_CHARS_INT = {read=_GetKEY_MMS_ALIAS_MIN_CHARS_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_ALLOW_ATTACH_AUDIO_BOOL = {read=_GetKEY_MMS_ALLOW_ATTACH_AUDIO_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_APPEND_TRANSACTION_ID_BOOL = {read=_GetKEY_MMS_APPEND_TRANSACTION_ID_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_EMAIL_GATEWAY_NUMBER_STRING = {read=_GetKEY_MMS_EMAIL_GATEWAY_NUMBER_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_GROUP_MMS_ENABLED_BOOL = {read=_GetKEY_MMS_GROUP_MMS_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_HTTP_PARAMS_STRING = {read=_GetKEY_MMS_HTTP_PARAMS_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_HTTP_SOCKET_TIMEOUT_INT = {read=_GetKEY_MMS_HTTP_SOCKET_TIMEOUT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MAX_IMAGE_HEIGHT_INT = {read=_GetKEY_MMS_MAX_IMAGE_HEIGHT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MAX_IMAGE_WIDTH_INT = {read=_GetKEY_MMS_MAX_IMAGE_WIDTH_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MAX_MESSAGE_SIZE_INT = {read=_GetKEY_MMS_MAX_MESSAGE_SIZE_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MESSAGE_TEXT_MAX_SIZE_INT = {read=_GetKEY_MMS_MESSAGE_TEXT_MAX_SIZE_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MMS_DELIVERY_REPORT_ENABLED_BOOL = {read=_GetKEY_MMS_MMS_DELIVERY_REPORT_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MMS_ENABLED_BOOL = {read=_GetKEY_MMS_MMS_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MMS_READ_REPORT_ENABLED_BOOL = {read=_GetKEY_MMS_MMS_READ_REPORT_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_MULTIPART_SMS_ENABLED_BOOL = {read=_GetKEY_MMS_MULTIPART_SMS_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_NAI_SUFFIX_STRING = {read=_GetKEY_MMS_NAI_SUFFIX_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_NOTIFY_WAP_MMSC_ENABLED_BOOL = {read=_GetKEY_MMS_NOTIFY_WAP_MMSC_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_RECIPIENT_LIMIT_INT = {read=_GetKEY_MMS_RECIPIENT_LIMIT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES_BOOL = {read=_GetKEY_MMS_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SHOW_CELL_BROADCAST_APP_LINKS_BOOL = {read=_GetKEY_MMS_SHOW_CELL_BROADCAST_APP_LINKS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SMS_DELIVERY_REPORT_ENABLED_BOOL = {read=_GetKEY_MMS_SMS_DELIVERY_REPORT_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD_INT = {read=_GetKEY_MMS_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SMS_TO_MMS_TEXT_THRESHOLD_INT = {read=_GetKEY_MMS_SMS_TO_MMS_TEXT_THRESHOLD_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SUBJECT_MAX_LENGTH_INT = {read=_GetKEY_MMS_SUBJECT_MAX_LENGTH_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SUPPORT_HTTP_CHARSET_HEADER_BOOL = {read=_GetKEY_MMS_SUPPORT_HTTP_CHARSET_HEADER_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_SUPPORT_MMS_CONTENT_DISPOSITION_BOOL = {read=_GetKEY_MMS_SUPPORT_MMS_CONTENT_DISPOSITION_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_UA_PROF_TAG_NAME_STRING = {read=_GetKEY_MMS_UA_PROF_TAG_NAME_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_UA_PROF_URL_STRING = {read=_GetKEY_MMS_UA_PROF_URL_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MMS_USER_AGENT_STRING = {read=_GetKEY_MMS_USER_AGENT_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_MONTHLY_DATA_CYCLE_DAY_INT = {read=_GetKEY_MONTHLY_DATA_CYCLE_DAY_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ONLY_SINGLE_DC_ALLOWED_INT_ARRAY = {read=_GetKEY_ONLY_SINGLE_DC_ALLOWED_INT_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_OPERATOR_SELECTION_EXPAND_BOOL = {read=_GetKEY_OPERATOR_SELECTION_EXPAND_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PREFER_2G_BOOL = {read=_GetKEY_PREFER_2G_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_RCS_CONFIG_SERVER_URL_STRING = {read=_GetKEY_RCS_CONFIG_SERVER_URL_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_REQUIRE_ENTITLEMENT_CHECKS_BOOL = {read=_GetKEY_REQUIRE_ENTITLEMENT_CHECKS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_RESTART_RADIO_ON_PDP_FAIL_REGULAR_DEACTIVATION_BOOL = {read=_GetKEY_RESTART_RADIO_ON_PDP_FAIL_REGULAR_DEACTIVATION_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SHOW_APN_SETTING_CDMA_BOOL = {read=_GetKEY_SHOW_APN_SETTING_CDMA_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SHOW_CDMA_CHOICES_BOOL = {read=_GetKEY_SHOW_CDMA_CHOICES_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SHOW_ICCID_IN_SIM_STATUS_BOOL = {read=_GetKEY_SHOW_ICCID_IN_SIM_STATUS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SHOW_ONSCREEN_DIAL_BUTTON_BOOL = {read=_GetKEY_SHOW_ONSCREEN_DIAL_BUTTON_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SIMPLIFIED_NETWORK_SETTINGS_BOOL = {read=_GetKEY_SIMPLIFIED_NETWORK_SETTINGS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SIM_NETWORK_UNLOCK_ALLOW_DISMISS_BOOL = {read=_GetKEY_SIM_NETWORK_UNLOCK_ALLOW_DISMISS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SMS_REQUIRES_DESTINATION_NUMBER_CONVERSION_BOOL = {read=_GetKEY_SMS_REQUIRES_DESTINATION_NUMBER_CONVERSION_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SUPPORT_3GPP_CALL_FORWARDING_WHILE_ROAMING_BOOL = {read=_GetKEY_SUPPORT_3GPP_CALL_FORWARDING_WHILE_ROAMING_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SUPPORT_CONFERENCE_CALL_BOOL = {read=_GetKEY_SUPPORT_CONFERENCE_CALL_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SUPPORT_PAUSE_IMS_VIDEO_CALLS_BOOL = {read=_GetKEY_SUPPORT_PAUSE_IMS_VIDEO_CALLS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_SUPPORT_SWAP_AFTER_MERGE_BOOL = {read=_GetKEY_SUPPORT_SWAP_AFTER_MERGE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_TREAT_DOWNGRADED_VIDEO_CALLS_AS_VIDEO_CALLS_BOOL = {read=_GetKEY_TREAT_DOWNGRADED_VIDEO_CALLS_AS_VIDEO_CALLS_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_USE_HFA_FOR_PROVISIONING_BOOL = {read=_GetKEY_USE_HFA_FOR_PROVISIONING_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_USE_OTASP_FOR_PROVISIONING_BOOL = {read=_GetKEY_USE_OTASP_FOR_PROVISIONING_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_USE_RCS_PRESENCE_BOOL = {read=_GetKEY_USE_RCS_PRESENCE_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VOICEMAIL_NOTIFICATION_PERSISTENT_BOOL = {read=_GetKEY_VOICEMAIL_NOTIFICATION_PERSISTENT_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VOICE_PRIVACY_DISABLE_UI_BOOL = {read=_GetKEY_VOICE_PRIVACY_DISABLE_UI_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VOLTE_REPLACEMENT_RAT_INT = {read=_GetKEY_VOLTE_REPLACEMENT_RAT_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_CELLULAR_DATA_REQUIRED_BOOL = {read=_GetKEY_VVM_CELLULAR_DATA_REQUIRED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_CLIENT_PREFIX_STRING = {read=_GetKEY_VVM_CLIENT_PREFIX_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_DESTINATION_NUMBER_STRING = {read=_GetKEY_VVM_DESTINATION_NUMBER_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_DISABLED_CAPABILITIES_STRING_ARRAY = {read=_GetKEY_VVM_DISABLED_CAPABILITIES_STRING_ARRAY};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_LEGACY_MODE_ENABLED_BOOL = {read=_GetKEY_VVM_LEGACY_MODE_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_PORT_NUMBER_INT = {read=_GetKEY_VVM_PORT_NUMBER_INT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_PREFETCH_BOOL = {read=_GetKEY_VVM_PREFETCH_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_SSL_ENABLED_BOOL = {read=_GetKEY_VVM_SSL_ENABLED_BOOL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_VVM_TYPE_STRING = {read=_GetKEY_VVM_TYPE_STRING};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_WORLD_PHONE_BOOL = {read=_GetKEY_WORLD_PHONE_BOOL};
};

__interface  INTERFACE_UUID("{11F40FA1-334D-4683-9D44-7A888F2661B8}") JCarrierConfigManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Os::_di_JPersistableBundle __cdecl getConfig() = 0 ;
	virtual Androidapi::Jni::Os::_di_JPersistableBundle __cdecl getConfigForSubId(int subId) = 0 ;
	virtual void __cdecl notifyConfigChangedForSubId(int subId) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCarrierConfigManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCarrierConfigManagerClass,_di_JCarrierConfigManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCarrierConfigManagerClass,_di_JCarrierConfigManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCarrierConfigManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCarrierConfigManagerClass,_di_JCarrierConfigManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCarrierConfigManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{47D53089-08D3-430B-8D56-2B54959C6F8A}") JCellIdentityCdmaClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{D2456865-988D-40AE-B4B3-42471181056E}") JCellIdentityCdma  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual int __cdecl getBasestationId() = 0 ;
	virtual int __cdecl getLatitude() = 0 ;
	virtual int __cdecl getLongitude() = 0 ;
	virtual int __cdecl getNetworkId() = 0 ;
	virtual int __cdecl getSystemId() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellIdentityCdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityCdmaClass,_di_JCellIdentityCdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityCdmaClass,_di_JCellIdentityCdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellIdentityCdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityCdmaClass,_di_JCellIdentityCdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellIdentityCdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F238DC50-40FA-4093-BDA2-2839208E79CE}") JCellIdentityGsmClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{9DD941A0-7403-4CD9-B000-22D4E7500A6D}") JCellIdentityGsm  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual int __cdecl getArfcn() = 0 ;
	virtual int __cdecl getBsic() = 0 ;
	virtual int __cdecl getCid() = 0 ;
	virtual int __cdecl getLac() = 0 ;
	virtual int __cdecl getMcc() = 0 ;
	virtual int __cdecl getMnc() = 0 ;
	virtual int __cdecl getPsc() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellIdentityGsm : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityGsmClass,_di_JCellIdentityGsm>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityGsmClass,_di_JCellIdentityGsm> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellIdentityGsm() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityGsmClass,_di_JCellIdentityGsm>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellIdentityGsm() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3F1A9F22-BF62-4D7C-ABA7-ECECF9725F68}") JCellIdentityLteClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{A1796A99-CC9C-47E8-97EA-E7AF5B27A5BE}") JCellIdentityLte  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual int __cdecl getCi() = 0 ;
	virtual int __cdecl getEarfcn() = 0 ;
	virtual int __cdecl getMcc() = 0 ;
	virtual int __cdecl getMnc() = 0 ;
	virtual int __cdecl getPci() = 0 ;
	virtual int __cdecl getTac() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellIdentityLte : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityLteClass,_di_JCellIdentityLte>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityLteClass,_di_JCellIdentityLte> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellIdentityLte() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityLteClass,_di_JCellIdentityLte>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellIdentityLte() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F9C9B6D7-9DB2-4E50-8B47-7CC9F5EC7ED6}") JCellIdentityWcdmaClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{1B622051-779D-4813-9CA6-992ABA3535D0}") JCellIdentityWcdma  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual int __cdecl getCid() = 0 ;
	virtual int __cdecl getLac() = 0 ;
	virtual int __cdecl getMcc() = 0 ;
	virtual int __cdecl getMnc() = 0 ;
	virtual int __cdecl getPsc() = 0 ;
	virtual int __cdecl getUarfcn() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellIdentityWcdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityWcdmaClass,_di_JCellIdentityWcdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityWcdmaClass,_di_JCellIdentityWcdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellIdentityWcdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellIdentityWcdmaClass,_di_JCellIdentityWcdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellIdentityWcdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D5A9AC63-0BEA-45CB-A8E3-6DCBA1B9FD89}") JCellInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{726F121A-E75C-4A37-B6CB-9DA886794FDF}") JCellInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual __int64 __cdecl getTimeStamp() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isRegistered() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoClass,_di_JCellInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoClass,_di_JCellInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoClass,_di_JCellInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{553A50F7-6149-45ED-9077-17F3A93B024A}") JCellInfoCdmaClass  : public JCellInfoClass 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
};

__interface  INTERFACE_UUID("{AF6F61BE-45A9-46D4-A45F-D1B71A4F7152}") JCellInfoCdma  : public JCellInfo 
{
	HIDESBASE virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual _di_JCellIdentityCdma __cdecl getCellIdentity() = 0 ;
	virtual _di_JCellSignalStrengthCdma __cdecl getCellSignalStrength() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellInfoCdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoCdmaClass,_di_JCellInfoCdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoCdmaClass,_di_JCellInfoCdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellInfoCdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoCdmaClass,_di_JCellInfoCdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellInfoCdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EF7AB5EA-EE8E-42F6-8652-E50E630E46B4}") JCellInfoGsmClass  : public JCellInfoClass 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
};

__interface  INTERFACE_UUID("{0E1045BB-B110-4AC7-803F-1BECCD8F9C3C}") JCellInfoGsm  : public JCellInfo 
{
	HIDESBASE virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual _di_JCellIdentityGsm __cdecl getCellIdentity() = 0 ;
	virtual _di_JCellSignalStrengthGsm __cdecl getCellSignalStrength() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellInfoGsm : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoGsmClass,_di_JCellInfoGsm>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoGsmClass,_di_JCellInfoGsm> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellInfoGsm() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoGsmClass,_di_JCellInfoGsm>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellInfoGsm() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ED725D53-684B-4A2F-814F-9A9650AAF0F4}") JCellInfoLteClass  : public JCellInfoClass 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
};

__interface  INTERFACE_UUID("{8C7BB823-B037-49B8-8FBA-8C8AFE1F5177}") JCellInfoLte  : public JCellInfo 
{
	HIDESBASE virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual _di_JCellIdentityLte __cdecl getCellIdentity() = 0 ;
	virtual _di_JCellSignalStrengthLte __cdecl getCellSignalStrength() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellInfoLte : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoLteClass,_di_JCellInfoLte>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoLteClass,_di_JCellInfoLte> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellInfoLte() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoLteClass,_di_JCellInfoLte>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellInfoLte() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D77AEE44-3759-4C79-8D70-4E323C80C5FC}") JCellInfoWcdmaClass  : public JCellInfoClass 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
};

__interface  INTERFACE_UUID("{6B66E6E1-BF02-48EA-9B98-5D891AA80788}") JCellInfoWcdma  : public JCellInfo 
{
	HIDESBASE virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject other) = 0 ;
	virtual _di_JCellIdentityWcdma __cdecl getCellIdentity() = 0 ;
	virtual _di_JCellSignalStrengthWcdma __cdecl getCellSignalStrength() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	HIDESBASE virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellInfoWcdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoWcdmaClass,_di_JCellInfoWcdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoWcdmaClass,_di_JCellInfoWcdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellInfoWcdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellInfoWcdmaClass,_di_JCellInfoWcdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellInfoWcdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{048C4A3E-4C00-40E1-A471-364959ED7986}") JCellLocationClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCellLocation __cdecl init() = 0 ;
	virtual _di_JCellLocation __cdecl getEmpty() = 0 ;
	virtual void __cdecl requestLocationUpdate() = 0 ;
};

__interface  INTERFACE_UUID("{769C920D-0E68-4A1D-ABA3-42894B5742C8}") JCellLocation  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellLocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellLocationClass,_di_JCellLocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellLocationClass,_di_JCellLocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellLocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellLocationClass,_di_JCellLocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellLocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2E408E0B-E6EF-450A-BE16-FE6258E458B9}") JCellSignalStrengthClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetSIGNAL_STRENGTH_GOOD() = 0 ;
	virtual int __cdecl _GetSIGNAL_STRENGTH_GREAT() = 0 ;
	virtual int __cdecl _GetSIGNAL_STRENGTH_MODERATE() = 0 ;
	virtual int __cdecl _GetSIGNAL_STRENGTH_NONE_OR_UNKNOWN() = 0 ;
	virtual int __cdecl _GetSIGNAL_STRENGTH_POOR() = 0 ;
	__property int SIGNAL_STRENGTH_GOOD = {read=_GetSIGNAL_STRENGTH_GOOD};
	__property int SIGNAL_STRENGTH_GREAT = {read=_GetSIGNAL_STRENGTH_GREAT};
	__property int SIGNAL_STRENGTH_MODERATE = {read=_GetSIGNAL_STRENGTH_MODERATE};
	__property int SIGNAL_STRENGTH_NONE_OR_UNKNOWN = {read=_GetSIGNAL_STRENGTH_NONE_OR_UNKNOWN};
	__property int SIGNAL_STRENGTH_POOR = {read=_GetSIGNAL_STRENGTH_POOR};
};

__interface  INTERFACE_UUID("{E28FDB30-AFA1-40FC-98B8-C2267E1532E0}") JCellSignalStrength  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual int __cdecl getAsuLevel() = 0 ;
	virtual int __cdecl getDbm() = 0 ;
	virtual int __cdecl getLevel() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellSignalStrength : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthClass,_di_JCellSignalStrength>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthClass,_di_JCellSignalStrength> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellSignalStrength() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthClass,_di_JCellSignalStrength>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellSignalStrength() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{01B4BDE1-698E-4773-B65E-89BEC2EB3074}") JCellSignalStrengthCdmaClass  : public JCellSignalStrengthClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{06C07B11-232F-40E1-9072-885B7D40F92D}") JCellSignalStrengthCdma  : public JCellSignalStrength 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl getAsuLevel() = 0 ;
	virtual int __cdecl getCdmaDbm() = 0 ;
	virtual int __cdecl getCdmaEcio() = 0 ;
	virtual int __cdecl getCdmaLevel() = 0 ;
	HIDESBASE virtual int __cdecl getDbm() = 0 ;
	virtual int __cdecl getEvdoDbm() = 0 ;
	virtual int __cdecl getEvdoEcio() = 0 ;
	virtual int __cdecl getEvdoLevel() = 0 ;
	virtual int __cdecl getEvdoSnr() = 0 ;
	HIDESBASE virtual int __cdecl getLevel() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellSignalStrengthCdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthCdmaClass,_di_JCellSignalStrengthCdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthCdmaClass,_di_JCellSignalStrengthCdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellSignalStrengthCdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthCdmaClass,_di_JCellSignalStrengthCdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellSignalStrengthCdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BC14D3AE-FBE8-4778-9922-2DC549FAA3A3}") JCellSignalStrengthGsmClass  : public JCellSignalStrengthClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{17546ED7-86F4-4A5F-A432-9D0477B4F29C}") JCellSignalStrengthGsm  : public JCellSignalStrength 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl getAsuLevel() = 0 ;
	HIDESBASE virtual int __cdecl getDbm() = 0 ;
	HIDESBASE virtual int __cdecl getLevel() = 0 ;
	virtual int __cdecl getTimingAdvance() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellSignalStrengthGsm : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthGsmClass,_di_JCellSignalStrengthGsm>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthGsmClass,_di_JCellSignalStrengthGsm> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellSignalStrengthGsm() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthGsmClass,_di_JCellSignalStrengthGsm>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellSignalStrengthGsm() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B2AEC25C-986C-49A8-85F0-5CF96A9E0856}") JCellSignalStrengthLteClass  : public JCellSignalStrengthClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{C0E93090-5675-481F-8BB4-5642161E3393}") JCellSignalStrengthLte  : public JCellSignalStrength 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl getAsuLevel() = 0 ;
	virtual int __cdecl getCqi() = 0 ;
	HIDESBASE virtual int __cdecl getDbm() = 0 ;
	HIDESBASE virtual int __cdecl getLevel() = 0 ;
	virtual int __cdecl getRsrp() = 0 ;
	virtual int __cdecl getRsrq() = 0 ;
	virtual int __cdecl getRssnr() = 0 ;
	virtual int __cdecl getTimingAdvance() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellSignalStrengthLte : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthLteClass,_di_JCellSignalStrengthLte>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthLteClass,_di_JCellSignalStrengthLte> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellSignalStrengthLte() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthLteClass,_di_JCellSignalStrengthLte>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellSignalStrengthLte() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2DEBF0C2-DE83-4B07-98A8-BF6CE9070ADF}") JCellSignalStrengthWcdmaClass  : public JCellSignalStrengthClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{09E2490B-D681-44B3-8C18-F4543582F1A3}") JCellSignalStrengthWcdma  : public JCellSignalStrength 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl getAsuLevel() = 0 ;
	HIDESBASE virtual int __cdecl getDbm() = 0 ;
	HIDESBASE virtual int __cdecl getLevel() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCellSignalStrengthWcdma : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthWcdmaClass,_di_JCellSignalStrengthWcdma>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthWcdmaClass,_di_JCellSignalStrengthWcdma> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCellSignalStrengthWcdma() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCellSignalStrengthWcdmaClass,_di_JCellSignalStrengthWcdma>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCellSignalStrengthWcdma() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{897EC9F9-957F-4942-859D-50BCED64009B}") JPhoneStateListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetLISTEN_CALL_FORWARDING_INDICATOR() = 0 ;
	virtual int __cdecl _GetLISTEN_CALL_STATE() = 0 ;
	virtual int __cdecl _GetLISTEN_CELL_INFO() = 0 ;
	virtual int __cdecl _GetLISTEN_CELL_LOCATION() = 0 ;
	virtual int __cdecl _GetLISTEN_DATA_ACTIVITY() = 0 ;
	virtual int __cdecl _GetLISTEN_DATA_CONNECTION_STATE() = 0 ;
	virtual int __cdecl _GetLISTEN_MESSAGE_WAITING_INDICATOR() = 0 ;
	virtual int __cdecl _GetLISTEN_NONE() = 0 ;
	virtual int __cdecl _GetLISTEN_SERVICE_STATE() = 0 ;
	virtual int __cdecl _GetLISTEN_SIGNAL_STRENGTH() = 0 ;
	virtual int __cdecl _GetLISTEN_SIGNAL_STRENGTHS() = 0 ;
	HIDESBASE virtual _di_JPhoneStateListener __cdecl init() = 0 ;
	__property int LISTEN_CALL_FORWARDING_INDICATOR = {read=_GetLISTEN_CALL_FORWARDING_INDICATOR};
	__property int LISTEN_CALL_STATE = {read=_GetLISTEN_CALL_STATE};
	__property int LISTEN_CELL_INFO = {read=_GetLISTEN_CELL_INFO};
	__property int LISTEN_CELL_LOCATION = {read=_GetLISTEN_CELL_LOCATION};
	__property int LISTEN_DATA_ACTIVITY = {read=_GetLISTEN_DATA_ACTIVITY};
	__property int LISTEN_DATA_CONNECTION_STATE = {read=_GetLISTEN_DATA_CONNECTION_STATE};
	__property int LISTEN_MESSAGE_WAITING_INDICATOR = {read=_GetLISTEN_MESSAGE_WAITING_INDICATOR};
	__property int LISTEN_NONE = {read=_GetLISTEN_NONE};
	__property int LISTEN_SERVICE_STATE = {read=_GetLISTEN_SERVICE_STATE};
	__property int LISTEN_SIGNAL_STRENGTH = {read=_GetLISTEN_SIGNAL_STRENGTH};
	__property int LISTEN_SIGNAL_STRENGTHS = {read=_GetLISTEN_SIGNAL_STRENGTHS};
};

__interface  INTERFACE_UUID("{50CE10E1-C584-4145-BC72-65BFA48BB281}") JPhoneStateListener  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onCallForwardingIndicatorChanged(bool cfi) = 0 ;
	virtual void __cdecl onCallStateChanged(int state, Androidapi::Jni::Javatypes::_di_JString incomingNumber) = 0 ;
	virtual void __cdecl onCellInfoChanged(Androidapi::Jni::Javatypes::_di_JList cellInfo) = 0 ;
	virtual void __cdecl onCellLocationChanged(_di_JCellLocation location) = 0 ;
	virtual void __cdecl onDataActivity(int direction) = 0 ;
	virtual void __cdecl onDataConnectionStateChanged(int state) = 0 /* overload */;
	virtual void __cdecl onDataConnectionStateChanged(int state, int networkType) = 0 /* overload */;
	virtual void __cdecl onMessageWaitingIndicatorChanged(bool mwi) = 0 ;
	virtual void __cdecl onServiceStateChanged(_di_JServiceState serviceState) = 0 ;
	virtual void __cdecl onSignalStrengthChanged(int asu) = 0 ;
	virtual void __cdecl onSignalStrengthsChanged(_di_JSignalStrength signalStrength) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPhoneStateListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneStateListenerClass,_di_JPhoneStateListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneStateListenerClass,_di_JPhoneStateListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPhoneStateListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneStateListenerClass,_di_JPhoneStateListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPhoneStateListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{94FF7ECE-DF9C-41E3-B9E7-9E44DC0127BB}") JCustomPhoneStateListenerClass  : public JPhoneStateListenerClass 
{
	HIDESBASE virtual _di_JCustomPhoneStateListener __cdecl init(_di_JICustomPhoneStateListener listener) = 0 ;
};

__interface  INTERFACE_UUID("{753BA66D-E86F-4345-89FC-7BC79F6B5C5A}") JCustomPhoneStateListener  : public JPhoneStateListener 
{
	HIDESBASE virtual void __cdecl onCallForwardingIndicatorChanged(bool cfi) = 0 ;
	HIDESBASE virtual void __cdecl onCallStateChanged(int state, Androidapi::Jni::Javatypes::_di_JString incomingNumber) = 0 ;
	HIDESBASE virtual void __cdecl onCellInfoChanged(Androidapi::Jni::Javatypes::_di_JList cellInfo) = 0 ;
	HIDESBASE virtual void __cdecl onCellLocationChanged(_di_JCellLocation location) = 0 ;
	HIDESBASE virtual void __cdecl onDataActivity(int direction) = 0 ;
	HIDESBASE virtual void __cdecl onDataConnectionStateChanged(int state) = 0 /* overload */;
	HIDESBASE virtual void __cdecl onDataConnectionStateChanged(int state, int networkType) = 0 /* overload */;
	HIDESBASE virtual void __cdecl onMessageWaitingIndicatorChanged(bool mwi) = 0 ;
	HIDESBASE virtual void __cdecl onServiceStateChanged(_di_JServiceState serviceState) = 0 ;
	HIDESBASE virtual void __cdecl onSignalStrengthChanged(int asu) = 0 ;
	HIDESBASE virtual void __cdecl onSignalStrengthsChanged(_di_JSignalStrength signalStrength) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCustomPhoneStateListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomPhoneStateListenerClass,_di_JCustomPhoneStateListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomPhoneStateListenerClass,_di_JCustomPhoneStateListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCustomPhoneStateListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCustomPhoneStateListenerClass,_di_JCustomPhoneStateListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCustomPhoneStateListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2B3FDA31-7A12-4ADC-B81C-B7E9D37ADD09}") JICustomPhoneStateListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{C8ABB706-0034-43DA-B768-F095F9ABE215}") JICustomPhoneStateListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onCallForwardingIndicatorChanged(bool cfi) = 0 ;
	virtual void __cdecl onCallStateChanged(int state, Androidapi::Jni::Javatypes::_di_JString incomingNumber) = 0 ;
	virtual void __cdecl onCellInfoChanged(Androidapi::Jni::Javatypes::_di_JList cellInfo) = 0 ;
	virtual void __cdecl onCellLocationChanged(_di_JCellLocation location) = 0 ;
	virtual void __cdecl onDataActivity(int direction) = 0 ;
	virtual void __cdecl onDataConnectionStateChanged(int state) = 0 /* overload */;
	virtual void __cdecl onDataConnectionStateChanged(int state, int networkType) = 0 /* overload */;
	virtual void __cdecl onMessageWaitingIndicatorChanged(bool mwi) = 0 ;
	virtual void __cdecl onServiceStateChanged(_di_JServiceState serviceState) = 0 ;
	virtual void __cdecl onSignalStrengthChanged(int asu) = 0 ;
	virtual void __cdecl onSignalStrengthsChanged(_di_JSignalStrength signalStrength) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJICustomPhoneStateListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JICustomPhoneStateListenerClass,_di_JICustomPhoneStateListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JICustomPhoneStateListenerClass,_di_JICustomPhoneStateListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJICustomPhoneStateListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JICustomPhoneStateListenerClass,_di_JICustomPhoneStateListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJICustomPhoneStateListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BADEDECF-3EFB-4912-9478-37C4ADCDC8A3}") JIccOpenLogicalChannelResponseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetINVALID_CHANNEL() = 0 ;
	virtual int __cdecl _GetSTATUS_MISSING_RESOURCE() = 0 ;
	virtual int __cdecl _GetSTATUS_NO_ERROR() = 0 ;
	virtual int __cdecl _GetSTATUS_NO_SUCH_ELEMENT() = 0 ;
	virtual int __cdecl _GetSTATUS_UNKNOWN_ERROR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int INVALID_CHANNEL = {read=_GetINVALID_CHANNEL};
	__property int STATUS_MISSING_RESOURCE = {read=_GetSTATUS_MISSING_RESOURCE};
	__property int STATUS_NO_ERROR = {read=_GetSTATUS_NO_ERROR};
	__property int STATUS_NO_SUCH_ELEMENT = {read=_GetSTATUS_NO_SUCH_ELEMENT};
	__property int STATUS_UNKNOWN_ERROR = {read=_GetSTATUS_UNKNOWN_ERROR};
};

__interface  INTERFACE_UUID("{75F3CEEA-52CC-4693-8E6A-264831D23AC9}") JIccOpenLogicalChannelResponse  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getChannel() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getSelectResponse() = 0 ;
	virtual int __cdecl getStatus() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJIccOpenLogicalChannelResponse : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIccOpenLogicalChannelResponseClass,_di_JIccOpenLogicalChannelResponse>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIccOpenLogicalChannelResponseClass,_di_JIccOpenLogicalChannelResponse> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJIccOpenLogicalChannelResponse() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JIccOpenLogicalChannelResponseClass,_di_JIccOpenLogicalChannelResponse>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJIccOpenLogicalChannelResponse() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EB3E8F37-13C7-4E29-9015-FE80FD8BD4A7}") JNeighboringCellInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetUNKNOWN_CID() = 0 ;
	virtual int __cdecl _GetUNKNOWN_RSSI() = 0 ;
	HIDESBASE virtual _di_JNeighboringCellInfo __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JNeighboringCellInfo __cdecl init(int rssi, int cid) = 0 /* overload */;
	HIDESBASE virtual _di_JNeighboringCellInfo __cdecl init(int rssi, Androidapi::Jni::Javatypes::_di_JString location, int radioType) = 0 /* overload */;
	HIDESBASE virtual _di_JNeighboringCellInfo __cdecl init(Androidapi::Jni::Os::_di_JParcel in_) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int UNKNOWN_CID = {read=_GetUNKNOWN_CID};
	__property int UNKNOWN_RSSI = {read=_GetUNKNOWN_RSSI};
};

__interface  INTERFACE_UUID("{8BF5BF7B-3E55-4C97-A2A5-11C1D079EF73}") JNeighboringCellInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual int __cdecl getCid() = 0 ;
	virtual int __cdecl getLac() = 0 ;
	virtual int __cdecl getNetworkType() = 0 ;
	virtual int __cdecl getPsc() = 0 ;
	virtual int __cdecl getRssi() = 0 ;
	virtual void __cdecl setCid(int cid) = 0 ;
	virtual void __cdecl setRssi(int rssi) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNeighboringCellInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNeighboringCellInfoClass,_di_JNeighboringCellInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNeighboringCellInfoClass,_di_JNeighboringCellInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNeighboringCellInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNeighboringCellInfoClass,_di_JNeighboringCellInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNeighboringCellInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{41B14776-2EE7-4DE2-8E4E-C1E936C866C1}") JPhoneNumberFormattingTextWatcherClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JPhoneNumberFormattingTextWatcher __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JPhoneNumberFormattingTextWatcher __cdecl init(Androidapi::Jni::Javatypes::_di_JString countryCode) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{891E6B45-DD52-484F-8E52-5F5272FC56DC}") JPhoneNumberFormattingTextWatcher  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl afterTextChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable s) = 0 ;
	virtual void __cdecl beforeTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int count, int after) = 0 ;
	virtual void __cdecl onTextChanged(Androidapi::Jni::Javatypes::_di_JCharSequence s, int start, int before, int count) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPhoneNumberFormattingTextWatcher : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberFormattingTextWatcherClass,_di_JPhoneNumberFormattingTextWatcher>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberFormattingTextWatcherClass,_di_JPhoneNumberFormattingTextWatcher> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPhoneNumberFormattingTextWatcher() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberFormattingTextWatcherClass,_di_JPhoneNumberFormattingTextWatcher>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPhoneNumberFormattingTextWatcher() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B641F06B-F83E-4853-BAA9-1939B5B5C231}") JPhoneNumberUtilsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetFORMAT_JAPAN() = 0 ;
	virtual int __cdecl _GetFORMAT_NANP() = 0 ;
	virtual int __cdecl _GetFORMAT_UNKNOWN() = 0 ;
	virtual System::WideChar __cdecl _GetPAUSE() = 0 ;
	virtual int __cdecl _GetTOA_International() = 0 ;
	virtual int __cdecl _GetTOA_Unknown() = 0 ;
	virtual System::WideChar __cdecl _GetWAIT() = 0 ;
	virtual System::WideChar __cdecl _GetWILD() = 0 ;
	HIDESBASE virtual _di_JPhoneNumberUtils __cdecl init() = 0 ;
	virtual void __cdecl addTtsSpan(Androidapi::Jni::Graphicscontentviewtext::_di_JSpannable s, int start, int endExclusive) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl calledPartyBCDFragmentToString(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* bytes, int offset, int length) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl calledPartyBCDToString(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* bytes, int offset, int length) = 0 ;
	virtual bool __cdecl compare(Androidapi::Jni::Javatypes::_di_JString a, Androidapi::Jni::Javatypes::_di_JString b) = 0 /* overload */;
	virtual bool __cdecl compare(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString a, Androidapi::Jni::Javatypes::_di_JString b) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl convertKeypadLettersToDigits(Androidapi::Jni::Javatypes::_di_JString input) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JTtsSpan __cdecl createTtsSpan(Androidapi::Jni::Javatypes::_di_JString phoneNumberString) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl createTtsSpannable(Androidapi::Jni::Javatypes::_di_JCharSequence phoneNumber) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl extractNetworkPortion(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl extractPostDialPortion(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual void __cdecl formatJapaneseNumber(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable text) = 0 ;
	virtual void __cdecl formatNanpNumber(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable text) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl formatNumber(Androidapi::Jni::Javatypes::_di_JString source) = 0 /* overload */;
	virtual void __cdecl formatNumber(Androidapi::Jni::Graphicscontentviewtext::_di_JEditable text, int defaultFormattingType) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl formatNumber(Androidapi::Jni::Javatypes::_di_JString phoneNumber, Androidapi::Jni::Javatypes::_di_JString defaultCountryIso) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl formatNumber(Androidapi::Jni::Javatypes::_di_JString phoneNumber, Androidapi::Jni::Javatypes::_di_JString phoneNumberE164, Androidapi::Jni::Javatypes::_di_JString defaultCountryIso) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl formatNumberToE164(Androidapi::Jni::Javatypes::_di_JString phoneNumber, Androidapi::Jni::Javatypes::_di_JString defaultCountryIso) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl formatNumberToRFC3966(Androidapi::Jni::Javatypes::_di_JString phoneNumber, Androidapi::Jni::Javatypes::_di_JString defaultCountryIso) = 0 ;
	virtual int __cdecl getFormatTypeForLocale(Androidapi::Jni::Javatypes::_di_JLocale locale) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNumberFromIntent(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent, Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getStrippedReversed(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual bool __cdecl is12Key(System::WideChar c) = 0 ;
	virtual bool __cdecl isDialable(System::WideChar c) = 0 ;
	virtual bool __cdecl isEmergencyNumber(Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual bool __cdecl isGlobalPhoneNumber(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual bool __cdecl isISODigit(System::WideChar c) = 0 ;
	virtual bool __cdecl isLocalEmergencyNumber(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual bool __cdecl isNonSeparator(System::WideChar c) = 0 ;
	virtual bool __cdecl isReallyDialable(System::WideChar c) = 0 ;
	virtual bool __cdecl isStartsPostDial(System::WideChar c) = 0 ;
	virtual bool __cdecl isVoiceMailNumber(Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual bool __cdecl isWellFormedSmsAddress(Androidapi::Jni::Javatypes::_di_JString address) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl networkPortionToCalledPartyBCD(Androidapi::Jni::Javatypes::_di_JString s) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl networkPortionToCalledPartyBCDWithLength(Androidapi::Jni::Javatypes::_di_JString s) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl normalizeNumber(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl numberToCalledPartyBCD(Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl replaceUnicodeDigits(Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl stringFromStringAndTOA(Androidapi::Jni::Javatypes::_di_JString s, int TOA) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl stripSeparators(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toCallerIDMinMatch(Androidapi::Jni::Javatypes::_di_JString phoneNumber) = 0 ;
	virtual int __cdecl toaFromString(Androidapi::Jni::Javatypes::_di_JString s) = 0 ;
	__property int FORMAT_JAPAN = {read=_GetFORMAT_JAPAN};
	__property int FORMAT_NANP = {read=_GetFORMAT_NANP};
	__property int FORMAT_UNKNOWN = {read=_GetFORMAT_UNKNOWN};
	__property System::WideChar PAUSE = {read=_GetPAUSE};
	__property int TOA_International = {read=_GetTOA_International};
	__property int TOA_Unknown = {read=_GetTOA_Unknown};
	__property System::WideChar WAIT = {read=_GetWAIT};
	__property System::WideChar WILD = {read=_GetWILD};
};

__interface  INTERFACE_UUID("{8217405F-564B-4CA0-AF0A-3FEEE87A0444}") JPhoneNumberUtils  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJPhoneNumberUtils : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberUtilsClass,_di_JPhoneNumberUtils>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberUtilsClass,_di_JPhoneNumberUtils> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJPhoneNumberUtils() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JPhoneNumberUtilsClass,_di_JPhoneNumberUtils>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJPhoneNumberUtils() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5E369BCE-8950-478C-88C1-1612B0C7999C}") JServiceStateClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetSTATE_EMERGENCY_ONLY() = 0 ;
	virtual int __cdecl _GetSTATE_IN_SERVICE() = 0 ;
	virtual int __cdecl _GetSTATE_OUT_OF_SERVICE() = 0 ;
	virtual int __cdecl _GetSTATE_POWER_OFF() = 0 ;
	HIDESBASE virtual _di_JServiceState __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JServiceState __cdecl init(_di_JServiceState s) = 0 /* overload */;
	HIDESBASE virtual _di_JServiceState __cdecl init(Androidapi::Jni::Os::_di_JParcel in_) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int STATE_EMERGENCY_ONLY = {read=_GetSTATE_EMERGENCY_ONLY};
	__property int STATE_IN_SERVICE = {read=_GetSTATE_IN_SERVICE};
	__property int STATE_OUT_OF_SERVICE = {read=_GetSTATE_OUT_OF_SERVICE};
	__property int STATE_POWER_OFF = {read=_GetSTATE_POWER_OFF};
};

__interface  INTERFACE_UUID("{981444BD-E25C-4943-97AE-C21D85913DEF}") JServiceState  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual bool __cdecl getIsManualSelection() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOperatorAlphaLong() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOperatorAlphaShort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOperatorNumeric() = 0 ;
	virtual bool __cdecl getRoaming() = 0 ;
	virtual int __cdecl getState() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setIsManualSelection(bool isManual) = 0 ;
	virtual void __cdecl setOperatorName(Androidapi::Jni::Javatypes::_di_JString longName, Androidapi::Jni::Javatypes::_di_JString shortName, Androidapi::Jni::Javatypes::_di_JString numeric) = 0 ;
	virtual void __cdecl setRoaming(bool roaming) = 0 ;
	virtual void __cdecl setState(int state) = 0 ;
	virtual void __cdecl setStateOff() = 0 ;
	virtual void __cdecl setStateOutOfService() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServiceState : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceStateClass,_di_JServiceState>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceStateClass,_di_JServiceState> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServiceState() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServiceStateClass,_di_JServiceState>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServiceState() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C579E9F5-9291-4F6F-B4BE-8C8522EE8C5E}") JSignalStrengthClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1260215B-42EC-4F73-8FFB-168FABD93E9A}") JSignalStrength  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual int __cdecl getCdmaDbm() = 0 ;
	virtual int __cdecl getCdmaEcio() = 0 ;
	virtual int __cdecl getEvdoDbm() = 0 ;
	virtual int __cdecl getEvdoEcio() = 0 ;
	virtual int __cdecl getEvdoSnr() = 0 ;
	virtual int __cdecl getGsmBitErrorRate() = 0 ;
	virtual int __cdecl getGsmSignalStrength() = 0 ;
	virtual int __cdecl getLevel() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isGsm() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel out_, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSignalStrength : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSignalStrengthClass,_di_JSignalStrength>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSignalStrengthClass,_di_JSignalStrength> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSignalStrength() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSignalStrengthClass,_di_JSignalStrength>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSignalStrength() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{5FD2ABA7-01A0-4AA1-BDE6-B125CD6A6752}") JSmsManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MMS_DATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_MMS_HTTP_STATUS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_ALIAS_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_ALIAS_MAX_CHARS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_ALIAS_MIN_CHARS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_ALLOW_ATTACH_AUDIO() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_APPEND_TRANSACTION_ID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_EMAIL_GATEWAY_NUMBER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_GROUP_MMS_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_HTTP_PARAMS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_HTTP_SOCKET_TIMEOUT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MAX_IMAGE_HEIGHT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MAX_IMAGE_WIDTH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MAX_MESSAGE_SIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MESSAGE_TEXT_MAX_SIZE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MMS_DELIVERY_REPORT_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MMS_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MMS_READ_REPORT_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_MULTIPART_SMS_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_NAI_SUFFIX() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_NOTIFY_WAP_MMSC_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_RECIPIENT_LIMIT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SHOW_CELL_BROADCAST_APP_LINKS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SMS_DELIVERY_REPORT_ENABLED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SMS_TO_MMS_TEXT_THRESHOLD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SUBJECT_MAX_LENGTH() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SUPPORT_HTTP_CHARSET_HEADER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_SUPPORT_MMS_CONTENT_DISPOSITION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_UA_PROF_TAG_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_UA_PROF_URL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMMS_CONFIG_USER_AGENT() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_CONFIGURATION_ERROR() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_HTTP_FAILURE() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_INVALID_APN() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_IO_ERROR() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_NO_DATA_NETWORK() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_RETRY() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_UNABLE_CONNECT_MMS() = 0 ;
	virtual int __cdecl _GetMMS_ERROR_UNSPECIFIED() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_GENERIC_FAILURE() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_NO_SERVICE() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_NULL_PDU() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_RADIO_OFF() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_ICC_FREE() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_ICC_READ() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_ICC_SENT() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_ICC_UNREAD() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_ICC_UNSENT() = 0 ;
	virtual _di_JSmsManager __cdecl getDefault() = 0 ;
	virtual int __cdecl getDefaultSmsSubscriptionId() = 0 ;
	virtual _di_JSmsManager __cdecl getSmsManagerForSubscriptionId(int subId) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MMS_DATA = {read=_GetEXTRA_MMS_DATA};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_MMS_HTTP_STATUS = {read=_GetEXTRA_MMS_HTTP_STATUS};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_ALIAS_ENABLED = {read=_GetMMS_CONFIG_ALIAS_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_ALIAS_MAX_CHARS = {read=_GetMMS_CONFIG_ALIAS_MAX_CHARS};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_ALIAS_MIN_CHARS = {read=_GetMMS_CONFIG_ALIAS_MIN_CHARS};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_ALLOW_ATTACH_AUDIO = {read=_GetMMS_CONFIG_ALLOW_ATTACH_AUDIO};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_APPEND_TRANSACTION_ID = {read=_GetMMS_CONFIG_APPEND_TRANSACTION_ID};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_EMAIL_GATEWAY_NUMBER = {read=_GetMMS_CONFIG_EMAIL_GATEWAY_NUMBER};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_GROUP_MMS_ENABLED = {read=_GetMMS_CONFIG_GROUP_MMS_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_HTTP_PARAMS = {read=_GetMMS_CONFIG_HTTP_PARAMS};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_HTTP_SOCKET_TIMEOUT = {read=_GetMMS_CONFIG_HTTP_SOCKET_TIMEOUT};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MAX_IMAGE_HEIGHT = {read=_GetMMS_CONFIG_MAX_IMAGE_HEIGHT};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MAX_IMAGE_WIDTH = {read=_GetMMS_CONFIG_MAX_IMAGE_WIDTH};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MAX_MESSAGE_SIZE = {read=_GetMMS_CONFIG_MAX_MESSAGE_SIZE};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MESSAGE_TEXT_MAX_SIZE = {read=_GetMMS_CONFIG_MESSAGE_TEXT_MAX_SIZE};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MMS_DELIVERY_REPORT_ENABLED = {read=_GetMMS_CONFIG_MMS_DELIVERY_REPORT_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MMS_ENABLED = {read=_GetMMS_CONFIG_MMS_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MMS_READ_REPORT_ENABLED = {read=_GetMMS_CONFIG_MMS_READ_REPORT_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_MULTIPART_SMS_ENABLED = {read=_GetMMS_CONFIG_MULTIPART_SMS_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_NAI_SUFFIX = {read=_GetMMS_CONFIG_NAI_SUFFIX};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_NOTIFY_WAP_MMSC_ENABLED = {read=_GetMMS_CONFIG_NOTIFY_WAP_MMSC_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_RECIPIENT_LIMIT = {read=_GetMMS_CONFIG_RECIPIENT_LIMIT};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES = {read=_GetMMS_CONFIG_SEND_MULTIPART_SMS_AS_SEPARATE_MESSAGES};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SHOW_CELL_BROADCAST_APP_LINKS = {read=_GetMMS_CONFIG_SHOW_CELL_BROADCAST_APP_LINKS};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SMS_DELIVERY_REPORT_ENABLED = {read=_GetMMS_CONFIG_SMS_DELIVERY_REPORT_ENABLED};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD = {read=_GetMMS_CONFIG_SMS_TO_MMS_TEXT_LENGTH_THRESHOLD};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SMS_TO_MMS_TEXT_THRESHOLD = {read=_GetMMS_CONFIG_SMS_TO_MMS_TEXT_THRESHOLD};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SUBJECT_MAX_LENGTH = {read=_GetMMS_CONFIG_SUBJECT_MAX_LENGTH};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SUPPORT_HTTP_CHARSET_HEADER = {read=_GetMMS_CONFIG_SUPPORT_HTTP_CHARSET_HEADER};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_SUPPORT_MMS_CONTENT_DISPOSITION = {read=_GetMMS_CONFIG_SUPPORT_MMS_CONTENT_DISPOSITION};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_UA_PROF_TAG_NAME = {read=_GetMMS_CONFIG_UA_PROF_TAG_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_UA_PROF_URL = {read=_GetMMS_CONFIG_UA_PROF_URL};
	__property Androidapi::Jni::Javatypes::_di_JString MMS_CONFIG_USER_AGENT = {read=_GetMMS_CONFIG_USER_AGENT};
	__property int MMS_ERROR_CONFIGURATION_ERROR = {read=_GetMMS_ERROR_CONFIGURATION_ERROR};
	__property int MMS_ERROR_HTTP_FAILURE = {read=_GetMMS_ERROR_HTTP_FAILURE};
	__property int MMS_ERROR_INVALID_APN = {read=_GetMMS_ERROR_INVALID_APN};
	__property int MMS_ERROR_IO_ERROR = {read=_GetMMS_ERROR_IO_ERROR};
	__property int MMS_ERROR_NO_DATA_NETWORK = {read=_GetMMS_ERROR_NO_DATA_NETWORK};
	__property int MMS_ERROR_RETRY = {read=_GetMMS_ERROR_RETRY};
	__property int MMS_ERROR_UNABLE_CONNECT_MMS = {read=_GetMMS_ERROR_UNABLE_CONNECT_MMS};
	__property int MMS_ERROR_UNSPECIFIED = {read=_GetMMS_ERROR_UNSPECIFIED};
	__property int RESULT_ERROR_GENERIC_FAILURE = {read=_GetRESULT_ERROR_GENERIC_FAILURE};
	__property int RESULT_ERROR_NO_SERVICE = {read=_GetRESULT_ERROR_NO_SERVICE};
	__property int RESULT_ERROR_NULL_PDU = {read=_GetRESULT_ERROR_NULL_PDU};
	__property int RESULT_ERROR_RADIO_OFF = {read=_GetRESULT_ERROR_RADIO_OFF};
	__property int STATUS_ON_ICC_FREE = {read=_GetSTATUS_ON_ICC_FREE};
	__property int STATUS_ON_ICC_READ = {read=_GetSTATUS_ON_ICC_READ};
	__property int STATUS_ON_ICC_SENT = {read=_GetSTATUS_ON_ICC_SENT};
	__property int STATUS_ON_ICC_UNREAD = {read=_GetSTATUS_ON_ICC_UNREAD};
	__property int STATUS_ON_ICC_UNSENT = {read=_GetSTATUS_ON_ICC_UNSENT};
};

__interface  INTERFACE_UUID("{8C75DE6B-0BC5-4B5B-9B70-E714A01033E0}") JSmsManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl createAppSpecificSmsToken(Androidapi::Jni::App::_di_JPendingIntent intent) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl divideMessage(Androidapi::Jni::Javatypes::_di_JString text) = 0 ;
	virtual void __cdecl downloadMultimediaMessage(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Javatypes::_di_JString locationUrl, Androidapi::Jni::Net::_di_Jnet_Uri contentUri, Androidapi::Jni::Os::_di_JBundle configOverrides, Androidapi::Jni::App::_di_JPendingIntent downloadedIntent) = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getCarrierConfigValues() = 0 ;
	virtual int __cdecl getSubscriptionId() = 0 ;
	virtual void __cdecl injectSmsPdu(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* pdu, Androidapi::Jni::Javatypes::_di_JString format, Androidapi::Jni::App::_di_JPendingIntent receivedIntent) = 0 ;
	virtual void __cdecl sendDataMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, short destinationPort, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, Androidapi::Jni::App::_di_JPendingIntent sentIntent, Androidapi::Jni::App::_di_JPendingIntent deliveryIntent) = 0 ;
	virtual void __cdecl sendMultimediaMessage(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context, Androidapi::Jni::Net::_di_Jnet_Uri contentUri, Androidapi::Jni::Javatypes::_di_JString locationUrl, Androidapi::Jni::Os::_di_JBundle configOverrides, Androidapi::Jni::App::_di_JPendingIntent sentIntent) = 0 ;
	virtual void __cdecl sendMultipartTextMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JArrayList parts, Androidapi::Jni::Javatypes::_di_JArrayList sentIntents, Androidapi::Jni::Javatypes::_di_JArrayList deliveryIntents) = 0 ;
	virtual void __cdecl sendTextMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::App::_di_JPendingIntent sentIntent, Androidapi::Jni::App::_di_JPendingIntent deliveryIntent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSmsManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsManagerClass,_di_JSmsManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsManagerClass,_di_JSmsManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSmsManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsManagerClass,_di_JSmsManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSmsManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{227C1E7B-3064-474A-8930-D244309E7D27}") JSmsMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetENCODING_16BIT() = 0 ;
	virtual int __cdecl _GetENCODING_7BIT() = 0 ;
	virtual int __cdecl _GetENCODING_8BIT() = 0 ;
	virtual int __cdecl _GetENCODING_UNKNOWN() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_BYTES() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_BYTES_WITH_HEADER() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_SEPTETS() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_SEPTETS_WITH_HEADER() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl calculateLength(Androidapi::Jni::Javatypes::_di_JCharSequence msgBody, bool use7bitOnly) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl calculateLength(Androidapi::Jni::Javatypes::_di_JString messageBody, bool use7bitOnly) = 0 /* overload */;
	virtual _di_JSmsMessage __cdecl createFromPdu(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* pdu) = 0 /* overload */;
	virtual _di_JSmsMessage __cdecl createFromPdu(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* pdu, Androidapi::Jni::Javatypes::_di_JString format) = 0 /* overload */;
	virtual _di_JSmsMessage_SubmitPdu __cdecl getSubmitPdu(Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString message, bool statusReportRequested) = 0 /* overload */;
	virtual _di_JSmsMessage_SubmitPdu __cdecl getSubmitPdu(Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString destinationAddress, short destinationPort, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, bool statusReportRequested) = 0 /* overload */;
	virtual int __cdecl getTPLayerLengthForPDU(Androidapi::Jni::Javatypes::_di_JString pdu) = 0 ;
	__property int ENCODING_16BIT = {read=_GetENCODING_16BIT};
	__property int ENCODING_7BIT = {read=_GetENCODING_7BIT};
	__property int ENCODING_8BIT = {read=_GetENCODING_8BIT};
	__property int ENCODING_UNKNOWN = {read=_GetENCODING_UNKNOWN};
	__property int MAX_USER_DATA_BYTES = {read=_GetMAX_USER_DATA_BYTES};
	__property int MAX_USER_DATA_BYTES_WITH_HEADER = {read=_GetMAX_USER_DATA_BYTES_WITH_HEADER};
	__property int MAX_USER_DATA_SEPTETS = {read=_GetMAX_USER_DATA_SEPTETS};
	__property int MAX_USER_DATA_SEPTETS_WITH_HEADER = {read=_GetMAX_USER_DATA_SEPTETS_WITH_HEADER};
};

__interface  INTERFACE_UUID("{012AA641-B8DD-4F6A-9056-98498FB0B05C}") JSmsMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDisplayMessageBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDisplayOriginatingAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEmailBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEmailFrom() = 0 ;
	virtual int __cdecl getIndexOnIcc() = 0 ;
	virtual int __cdecl getIndexOnSim() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMessageBody() = 0 ;
	virtual _di_JSmsMessage_MessageClass __cdecl getMessageClass() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOriginatingAddress() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getPdu() = 0 ;
	virtual int __cdecl getProtocolIdentifier() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPseudoSubject() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getServiceCenterAddress() = 0 ;
	virtual int __cdecl getStatus() = 0 ;
	virtual int __cdecl getStatusOnIcc() = 0 ;
	virtual int __cdecl getStatusOnSim() = 0 ;
	virtual __int64 __cdecl getTimestampMillis() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getUserData() = 0 ;
	virtual bool __cdecl isCphsMwiMessage() = 0 ;
	virtual bool __cdecl isEmail() = 0 ;
	virtual bool __cdecl isMWIClearMessage() = 0 ;
	virtual bool __cdecl isMWISetMessage() = 0 ;
	virtual bool __cdecl isMwiDontStore() = 0 ;
	virtual bool __cdecl isReplace() = 0 ;
	virtual bool __cdecl isReplyPathPresent() = 0 ;
	virtual bool __cdecl isStatusReportMessage() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSmsMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessageClass,_di_JSmsMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessageClass,_di_JSmsMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSmsMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessageClass,_di_JSmsMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSmsMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{02240F3E-83D9-4ED3-9C44-6F739AD319F1}") JSmsMessage_MessageClassClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JSmsMessage_MessageClass __cdecl _GetCLASS_0() = 0 ;
	virtual _di_JSmsMessage_MessageClass __cdecl _GetCLASS_1() = 0 ;
	virtual _di_JSmsMessage_MessageClass __cdecl _GetCLASS_2() = 0 ;
	virtual _di_JSmsMessage_MessageClass __cdecl _GetCLASS_3() = 0 ;
	virtual _di_JSmsMessage_MessageClass __cdecl _GetUNKNOWN() = 0 ;
	HIDESBASE virtual _di_JSmsMessage_MessageClass __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JSmsMessage_MessageClass>* __cdecl values() = 0 ;
	__property _di_JSmsMessage_MessageClass CLASS_0 = {read=_GetCLASS_0};
	__property _di_JSmsMessage_MessageClass CLASS_1 = {read=_GetCLASS_1};
	__property _di_JSmsMessage_MessageClass CLASS_2 = {read=_GetCLASS_2};
	__property _di_JSmsMessage_MessageClass CLASS_3 = {read=_GetCLASS_3};
	__property _di_JSmsMessage_MessageClass UNKNOWN = {read=_GetUNKNOWN};
};

__interface  INTERFACE_UUID("{A7AA6F95-590D-48F9-9EAD-7DEF27FB0AD3}") JSmsMessage_MessageClass  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSmsMessage_MessageClass : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_MessageClassClass,_di_JSmsMessage_MessageClass>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_MessageClassClass,_di_JSmsMessage_MessageClass> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSmsMessage_MessageClass() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_MessageClassClass,_di_JSmsMessage_MessageClass>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSmsMessage_MessageClass() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3B92B0B3-1E7C-418F-B5DD-222AD433A5AC}") JSmsMessage_SubmitPduClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D69C5B7B-6E92-4599-A3ED-EBB174FEDB68}") JSmsMessage_SubmitPdu  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetencodedMessage() = 0 ;
	virtual void __cdecl _SetencodedMessage(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetencodedScAddress() = 0 ;
	virtual void __cdecl _SetencodedScAddress(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* Value) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* encodedMessage = {read=_GetencodedMessage, write=_SetencodedMessage};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* encodedScAddress = {read=_GetencodedScAddress, write=_SetencodedScAddress};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSmsMessage_SubmitPdu : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_SubmitPduClass,_di_JSmsMessage_SubmitPdu>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_SubmitPduClass,_di_JSmsMessage_SubmitPdu> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSmsMessage_SubmitPdu() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSmsMessage_SubmitPduClass,_di_JSmsMessage_SubmitPdu>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSmsMessage_SubmitPdu() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1ECF5C35-07D4-477C-96B9-6F00EC3944B6}") JSubscriptionInfoClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{2B00AA07-B712-4597-8FA6-05EBB3B1C58E}") JSubscriptionInfo  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap __cdecl createIconBitmap(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getCarrierName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCountryIso() = 0 ;
	virtual int __cdecl getDataRoaming() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCharSequence __cdecl getDisplayName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getIccId() = 0 ;
	virtual int __cdecl getIconTint() = 0 ;
	virtual int __cdecl getMcc() = 0 ;
	virtual int __cdecl getMnc() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNumber() = 0 ;
	virtual int __cdecl getSimSlotIndex() = 0 ;
	virtual int __cdecl getSubscriptionId() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSubscriptionInfo : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionInfoClass,_di_JSubscriptionInfo>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionInfoClass,_di_JSubscriptionInfo> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSubscriptionInfo() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionInfoClass,_di_JSubscriptionInfo>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSubscriptionInfo() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{119324F9-C6B0-4E89-94F1-0EAB9CA0287E}") JSubscriptionManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DEFAULT_SMS_SUBSCRIPTION_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_DEFAULT_SUBSCRIPTION_CHANGED() = 0 ;
	virtual int __cdecl _GetDATA_ROAMING_DISABLE() = 0 ;
	virtual int __cdecl _GetDATA_ROAMING_ENABLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_SUBSCRIPTION_INDEX() = 0 ;
	virtual int __cdecl _GetINVALID_SUBSCRIPTION_ID() = 0 ;
	virtual _di_JSubscriptionManager __cdecl from(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual int __cdecl getDefaultDataSubscriptionId() = 0 ;
	virtual int __cdecl getDefaultSmsSubscriptionId() = 0 ;
	virtual int __cdecl getDefaultSubscriptionId() = 0 ;
	virtual int __cdecl getDefaultVoiceSubscriptionId() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DEFAULT_SMS_SUBSCRIPTION_CHANGED = {read=_GetACTION_DEFAULT_SMS_SUBSCRIPTION_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_DEFAULT_SUBSCRIPTION_CHANGED = {read=_GetACTION_DEFAULT_SUBSCRIPTION_CHANGED};
	__property int DATA_ROAMING_DISABLE = {read=_GetDATA_ROAMING_DISABLE};
	__property int DATA_ROAMING_ENABLE = {read=_GetDATA_ROAMING_ENABLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_SUBSCRIPTION_INDEX = {read=_GetEXTRA_SUBSCRIPTION_INDEX};
	__property int INVALID_SUBSCRIPTION_ID = {read=_GetINVALID_SUBSCRIPTION_ID};
};

__interface  INTERFACE_UUID("{0029EBE7-5EF6-4C05-A608-8BB19F2FB263}") JSubscriptionManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addOnSubscriptionsChangedListener(_di_JSubscriptionManager_OnSubscriptionsChangedListener listener) = 0 ;
	virtual _di_JSubscriptionInfo __cdecl getActiveSubscriptionInfo(int subId) = 0 ;
	virtual int __cdecl getActiveSubscriptionInfoCount() = 0 ;
	virtual int __cdecl getActiveSubscriptionInfoCountMax() = 0 ;
	virtual _di_JSubscriptionInfo __cdecl getActiveSubscriptionInfoForSimSlotIndex(int slotIndex) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getActiveSubscriptionInfoList() = 0 ;
	virtual bool __cdecl isNetworkRoaming(int subId) = 0 ;
	virtual void __cdecl removeOnSubscriptionsChangedListener(_di_JSubscriptionManager_OnSubscriptionsChangedListener listener) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSubscriptionManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManagerClass,_di_JSubscriptionManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManagerClass,_di_JSubscriptionManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSubscriptionManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManagerClass,_di_JSubscriptionManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSubscriptionManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F2559847-2FB4-4AE0-90CB-7FF3B0D44875}") JSubscriptionManager_OnSubscriptionsChangedListenerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSubscriptionManager_OnSubscriptionsChangedListener __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{36F98257-7442-4AB5-8854-928260DC45BF}") JSubscriptionManager_OnSubscriptionsChangedListener  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onSubscriptionsChanged() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSubscriptionManager_OnSubscriptionsChangedListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManager_OnSubscriptionsChangedListenerClass,_di_JSubscriptionManager_OnSubscriptionsChangedListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManager_OnSubscriptionsChangedListenerClass,_di_JSubscriptionManager_OnSubscriptionsChangedListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSubscriptionManager_OnSubscriptionsChangedListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSubscriptionManager_OnSubscriptionsChangedListenerClass,_di_JSubscriptionManager_OnSubscriptionsChangedListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSubscriptionManager_OnSubscriptionsChangedListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{543679F3-38DC-4FCA-ADCD-648A27B9B5DD}") JTelephonyManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_CONFIGURE_VOICEMAIL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_PHONE_STATE_CHANGED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_RESPOND_VIA_MESSAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_SHOW_VOICEMAIL_NOTIFICATION() = 0 ;
	virtual int __cdecl _GetAPPTYPE_CSIM() = 0 ;
	virtual int __cdecl _GetAPPTYPE_ISIM() = 0 ;
	virtual int __cdecl _GetAPPTYPE_RUIM() = 0 ;
	virtual int __cdecl _GetAPPTYPE_SIM() = 0 ;
	virtual int __cdecl _GetAPPTYPE_USIM() = 0 ;
	virtual int __cdecl _GetAUTHTYPE_EAP_AKA() = 0 ;
	virtual int __cdecl _GetAUTHTYPE_EAP_SIM() = 0 ;
	virtual int __cdecl _GetCALL_STATE_IDLE() = 0 ;
	virtual int __cdecl _GetCALL_STATE_OFFHOOK() = 0 ;
	virtual int __cdecl _GetCALL_STATE_RINGING() = 0 ;
	virtual int __cdecl _GetDATA_ACTIVITY_DORMANT() = 0 ;
	virtual int __cdecl _GetDATA_ACTIVITY_IN() = 0 ;
	virtual int __cdecl _GetDATA_ACTIVITY_INOUT() = 0 ;
	virtual int __cdecl _GetDATA_ACTIVITY_NONE() = 0 ;
	virtual int __cdecl _GetDATA_ACTIVITY_OUT() = 0 ;
	virtual int __cdecl _GetDATA_CONNECTED() = 0 ;
	virtual int __cdecl _GetDATA_CONNECTING() = 0 ;
	virtual int __cdecl _GetDATA_DISCONNECTED() = 0 ;
	virtual int __cdecl _GetDATA_SUSPENDED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_CALL_VOICEMAIL_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_HIDE_PUBLIC_SETTINGS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_INCOMING_NUMBER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_LAUNCH_VOICEMAIL_SETTINGS_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_NOTIFICATION_COUNT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_PHONE_ACCOUNT_HANDLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE_IDLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE_OFFHOOK() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_STATE_RINGING() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetEXTRA_VOICEMAIL_NUMBER() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetMETADATA_HIDE_VOICEMAIL_SETTINGS_MENU() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_1xRTT() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_CDMA() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_EDGE() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_EHRPD() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_EVDO_0() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_EVDO_A() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_EVDO_B() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_GPRS() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_GSM() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_HSDPA() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_HSPA() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_HSPAP() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_HSUPA() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_IDEN() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_IWLAN() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_LTE() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_TD_SCDMA() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_UMTS() = 0 ;
	virtual int __cdecl _GetNETWORK_TYPE_UNKNOWN() = 0 ;
	virtual int __cdecl _GetPHONE_TYPE_CDMA() = 0 ;
	virtual int __cdecl _GetPHONE_TYPE_GSM() = 0 ;
	virtual int __cdecl _GetPHONE_TYPE_NONE() = 0 ;
	virtual int __cdecl _GetPHONE_TYPE_SIP() = 0 ;
	virtual int __cdecl _GetSIM_STATE_ABSENT() = 0 ;
	virtual int __cdecl _GetSIM_STATE_CARD_IO_ERROR() = 0 ;
	virtual int __cdecl _GetSIM_STATE_CARD_RESTRICTED() = 0 ;
	virtual int __cdecl _GetSIM_STATE_NETWORK_LOCKED() = 0 ;
	virtual int __cdecl _GetSIM_STATE_NOT_READY() = 0 ;
	virtual int __cdecl _GetSIM_STATE_PERM_DISABLED() = 0 ;
	virtual int __cdecl _GetSIM_STATE_PIN_REQUIRED() = 0 ;
	virtual int __cdecl _GetSIM_STATE_PUK_REQUIRED() = 0 ;
	virtual int __cdecl _GetSIM_STATE_READY() = 0 ;
	virtual int __cdecl _GetSIM_STATE_UNKNOWN() = 0 ;
	virtual int __cdecl _GetUSSD_ERROR_SERVICE_UNAVAIL() = 0 ;
	virtual int __cdecl _GetUSSD_RETURN_FAILURE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVVM_TYPE_CVVM() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetVVM_TYPE_OMTP() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_CONFIGURE_VOICEMAIL = {read=_GetACTION_CONFIGURE_VOICEMAIL};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_PHONE_STATE_CHANGED = {read=_GetACTION_PHONE_STATE_CHANGED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_RESPOND_VIA_MESSAGE = {read=_GetACTION_RESPOND_VIA_MESSAGE};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_SHOW_VOICEMAIL_NOTIFICATION = {read=_GetACTION_SHOW_VOICEMAIL_NOTIFICATION};
	__property int APPTYPE_CSIM = {read=_GetAPPTYPE_CSIM};
	__property int APPTYPE_ISIM = {read=_GetAPPTYPE_ISIM};
	__property int APPTYPE_RUIM = {read=_GetAPPTYPE_RUIM};
	__property int APPTYPE_SIM = {read=_GetAPPTYPE_SIM};
	__property int APPTYPE_USIM = {read=_GetAPPTYPE_USIM};
	__property int AUTHTYPE_EAP_AKA = {read=_GetAUTHTYPE_EAP_AKA};
	__property int AUTHTYPE_EAP_SIM = {read=_GetAUTHTYPE_EAP_SIM};
	__property int CALL_STATE_IDLE = {read=_GetCALL_STATE_IDLE};
	__property int CALL_STATE_OFFHOOK = {read=_GetCALL_STATE_OFFHOOK};
	__property int CALL_STATE_RINGING = {read=_GetCALL_STATE_RINGING};
	__property int DATA_ACTIVITY_DORMANT = {read=_GetDATA_ACTIVITY_DORMANT};
	__property int DATA_ACTIVITY_IN = {read=_GetDATA_ACTIVITY_IN};
	__property int DATA_ACTIVITY_INOUT = {read=_GetDATA_ACTIVITY_INOUT};
	__property int DATA_ACTIVITY_NONE = {read=_GetDATA_ACTIVITY_NONE};
	__property int DATA_ACTIVITY_OUT = {read=_GetDATA_ACTIVITY_OUT};
	__property int DATA_CONNECTED = {read=_GetDATA_CONNECTED};
	__property int DATA_CONNECTING = {read=_GetDATA_CONNECTING};
	__property int DATA_DISCONNECTED = {read=_GetDATA_DISCONNECTED};
	__property int DATA_SUSPENDED = {read=_GetDATA_SUSPENDED};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_CALL_VOICEMAIL_INTENT = {read=_GetEXTRA_CALL_VOICEMAIL_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_HIDE_PUBLIC_SETTINGS = {read=_GetEXTRA_HIDE_PUBLIC_SETTINGS};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_INCOMING_NUMBER = {read=_GetEXTRA_INCOMING_NUMBER};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_LAUNCH_VOICEMAIL_SETTINGS_INTENT = {read=_GetEXTRA_LAUNCH_VOICEMAIL_SETTINGS_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_NOTIFICATION_COUNT = {read=_GetEXTRA_NOTIFICATION_COUNT};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_PHONE_ACCOUNT_HANDLE = {read=_GetEXTRA_PHONE_ACCOUNT_HANDLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE = {read=_GetEXTRA_STATE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE_IDLE = {read=_GetEXTRA_STATE_IDLE};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE_OFFHOOK = {read=_GetEXTRA_STATE_OFFHOOK};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_STATE_RINGING = {read=_GetEXTRA_STATE_RINGING};
	__property Androidapi::Jni::Javatypes::_di_JString EXTRA_VOICEMAIL_NUMBER = {read=_GetEXTRA_VOICEMAIL_NUMBER};
	__property Androidapi::Jni::Javatypes::_di_JString METADATA_HIDE_VOICEMAIL_SETTINGS_MENU = {read=_GetMETADATA_HIDE_VOICEMAIL_SETTINGS_MENU};
	__property int NETWORK_TYPE_1xRTT = {read=_GetNETWORK_TYPE_1xRTT};
	__property int NETWORK_TYPE_CDMA = {read=_GetNETWORK_TYPE_CDMA};
	__property int NETWORK_TYPE_EDGE = {read=_GetNETWORK_TYPE_EDGE};
	__property int NETWORK_TYPE_EHRPD = {read=_GetNETWORK_TYPE_EHRPD};
	__property int NETWORK_TYPE_EVDO_0 = {read=_GetNETWORK_TYPE_EVDO_0};
	__property int NETWORK_TYPE_EVDO_A = {read=_GetNETWORK_TYPE_EVDO_A};
	__property int NETWORK_TYPE_EVDO_B = {read=_GetNETWORK_TYPE_EVDO_B};
	__property int NETWORK_TYPE_GPRS = {read=_GetNETWORK_TYPE_GPRS};
	__property int NETWORK_TYPE_GSM = {read=_GetNETWORK_TYPE_GSM};
	__property int NETWORK_TYPE_HSDPA = {read=_GetNETWORK_TYPE_HSDPA};
	__property int NETWORK_TYPE_HSPA = {read=_GetNETWORK_TYPE_HSPA};
	__property int NETWORK_TYPE_HSPAP = {read=_GetNETWORK_TYPE_HSPAP};
	__property int NETWORK_TYPE_HSUPA = {read=_GetNETWORK_TYPE_HSUPA};
	__property int NETWORK_TYPE_IDEN = {read=_GetNETWORK_TYPE_IDEN};
	__property int NETWORK_TYPE_IWLAN = {read=_GetNETWORK_TYPE_IWLAN};
	__property int NETWORK_TYPE_LTE = {read=_GetNETWORK_TYPE_LTE};
	__property int NETWORK_TYPE_TD_SCDMA = {read=_GetNETWORK_TYPE_TD_SCDMA};
	__property int NETWORK_TYPE_UMTS = {read=_GetNETWORK_TYPE_UMTS};
	__property int NETWORK_TYPE_UNKNOWN = {read=_GetNETWORK_TYPE_UNKNOWN};
	__property int PHONE_TYPE_CDMA = {read=_GetPHONE_TYPE_CDMA};
	__property int PHONE_TYPE_GSM = {read=_GetPHONE_TYPE_GSM};
	__property int PHONE_TYPE_NONE = {read=_GetPHONE_TYPE_NONE};
	__property int PHONE_TYPE_SIP = {read=_GetPHONE_TYPE_SIP};
	__property int SIM_STATE_ABSENT = {read=_GetSIM_STATE_ABSENT};
	__property int SIM_STATE_CARD_IO_ERROR = {read=_GetSIM_STATE_CARD_IO_ERROR};
	__property int SIM_STATE_CARD_RESTRICTED = {read=_GetSIM_STATE_CARD_RESTRICTED};
	__property int SIM_STATE_NETWORK_LOCKED = {read=_GetSIM_STATE_NETWORK_LOCKED};
	__property int SIM_STATE_NOT_READY = {read=_GetSIM_STATE_NOT_READY};
	__property int SIM_STATE_PERM_DISABLED = {read=_GetSIM_STATE_PERM_DISABLED};
	__property int SIM_STATE_PIN_REQUIRED = {read=_GetSIM_STATE_PIN_REQUIRED};
	__property int SIM_STATE_PUK_REQUIRED = {read=_GetSIM_STATE_PUK_REQUIRED};
	__property int SIM_STATE_READY = {read=_GetSIM_STATE_READY};
	__property int SIM_STATE_UNKNOWN = {read=_GetSIM_STATE_UNKNOWN};
	__property int USSD_ERROR_SERVICE_UNAVAIL = {read=_GetUSSD_ERROR_SERVICE_UNAVAIL};
	__property int USSD_RETURN_FAILURE = {read=_GetUSSD_RETURN_FAILURE};
	__property Androidapi::Jni::Javatypes::_di_JString VVM_TYPE_CVVM = {read=_GetVVM_TYPE_CVVM};
	__property Androidapi::Jni::Javatypes::_di_JString VVM_TYPE_OMTP = {read=_GetVVM_TYPE_OMTP};
};

__interface  INTERFACE_UUID("{7725226B-9F82-4BFA-B1DE-3960703BB92C}") JTelephonyManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual bool __cdecl canChangeDtmfToneLength() = 0 ;
	virtual _di_JTelephonyManager __cdecl createForSubscriptionId(int subId) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getAllCellInfo() = 0 ;
	virtual int __cdecl getCallState() = 0 ;
	virtual Androidapi::Jni::Os::_di_JPersistableBundle __cdecl getCarrierConfig() = 0 ;
	virtual _di_JCellLocation __cdecl getCellLocation() = 0 ;
	virtual int __cdecl getDataActivity() = 0 ;
	virtual int __cdecl getDataNetworkType() = 0 ;
	virtual int __cdecl getDataState() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceId() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceId(int slotIndex) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDeviceSoftwareVersion() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getForbiddenPlmns() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getGroupIdLevel1() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getIccAuthentication(int appType, int authType, Androidapi::Jni::Javatypes::_di_JString data) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getImei() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getImei(int slotIndex) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getLine1Number() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMeid() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMeid(int slotIndex) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMmsUAProfUrl() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMmsUserAgent() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getNeighboringCellInfo() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNetworkCountryIso() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNetworkOperator() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNetworkOperatorName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getNetworkSpecifier() = 0 ;
	virtual int __cdecl getNetworkType() = 0 ;
	virtual int __cdecl getPhoneCount() = 0 ;
	virtual int __cdecl getPhoneType() = 0 ;
	virtual _di_JServiceState __cdecl getServiceState() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSimCountryIso() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSimOperator() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSimOperatorName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSimSerialNumber() = 0 ;
	virtual int __cdecl getSimState() = 0 /* overload */;
	virtual int __cdecl getSimState(int slotIndex) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSubscriberId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getVisualVoicemailPackageName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getVoiceMailAlphaTag() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getVoiceMailNumber() = 0 ;
	virtual int __cdecl getVoiceNetworkType() = 0 ;
	virtual bool __cdecl hasCarrierPrivileges() = 0 ;
	virtual bool __cdecl hasIccCard() = 0 ;
	virtual bool __cdecl iccCloseLogicalChannel(int channel) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl iccExchangeSimIO(int fileID, int command, int p1, int p2, int p3, Androidapi::Jni::Javatypes::_di_JString filePath) = 0 ;
	virtual _di_JIccOpenLogicalChannelResponse __cdecl iccOpenLogicalChannel(Androidapi::Jni::Javatypes::_di_JString AID) = 0 /* overload */;
	virtual _di_JIccOpenLogicalChannelResponse __cdecl iccOpenLogicalChannel(Androidapi::Jni::Javatypes::_di_JString AID, int p2) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl iccTransmitApduBasicChannel(int cla, int instruction, int p1, int p2, int p3, Androidapi::Jni::Javatypes::_di_JString data) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl iccTransmitApduLogicalChannel(int channel, int cla, int instruction, int p1, int p2, int p3, Androidapi::Jni::Javatypes::_di_JString data) = 0 ;
	virtual bool __cdecl isConcurrentVoiceAndDataSupported() = 0 ;
	virtual bool __cdecl isDataEnabled() = 0 ;
	virtual bool __cdecl isHearingAidCompatibilitySupported() = 0 ;
	virtual bool __cdecl isNetworkRoaming() = 0 ;
	virtual bool __cdecl isSmsCapable() = 0 ;
	virtual bool __cdecl isTtyModeSupported() = 0 ;
	virtual bool __cdecl isVoiceCapable() = 0 ;
	virtual bool __cdecl isWorldPhone() = 0 ;
	virtual void __cdecl listen(_di_JPhoneStateListener listener, int events) = 0 ;
	virtual void __cdecl sendDialerSpecialCode(Androidapi::Jni::Javatypes::_di_JString inputCode) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl sendEnvelopeWithStatus(Androidapi::Jni::Javatypes::_di_JString content) = 0 ;
	virtual void __cdecl sendUssdRequest(Androidapi::Jni::Javatypes::_di_JString ussdRequest, _di_JTelephonyManager_UssdResponseCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual void __cdecl sendVisualVoicemailSms(Androidapi::Jni::Javatypes::_di_JString number, int port, Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::App::_di_JPendingIntent sentIntent) = 0 ;
	virtual void __cdecl setDataEnabled(bool enable) = 0 ;
	virtual bool __cdecl setLine1NumberForDisplay(Androidapi::Jni::Javatypes::_di_JString alphaTag, Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
	virtual bool __cdecl setOperatorBrandOverride(Androidapi::Jni::Javatypes::_di_JString brand) = 0 ;
	virtual bool __cdecl setPreferredNetworkTypeToGlobal() = 0 ;
	virtual void __cdecl setVisualVoicemailSmsFilterSettings(_di_JVisualVoicemailSmsFilterSettings settings) = 0 ;
	virtual bool __cdecl setVoiceMailNumber(Androidapi::Jni::Javatypes::_di_JString alphaTag, Androidapi::Jni::Javatypes::_di_JString number) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTelephonyManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManagerClass,_di_JTelephonyManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManagerClass,_di_JTelephonyManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTelephonyManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManagerClass,_di_JTelephonyManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTelephonyManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{124673C6-2EEC-49C3-A608-8EE16F820123}") JTelephonyManager_UssdResponseCallbackClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JTelephonyManager_UssdResponseCallback __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{A99C7F8A-EDD5-4F21-97D8-87E118578E0F}") JTelephonyManager_UssdResponseCallback  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl onReceiveUssdResponse(_di_JTelephonyManager telephonyManager, Androidapi::Jni::Javatypes::_di_JString request, Androidapi::Jni::Javatypes::_di_JCharSequence response) = 0 ;
	virtual void __cdecl onReceiveUssdResponseFailed(_di_JTelephonyManager telephonyManager, Androidapi::Jni::Javatypes::_di_JString request, int failureCode) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTelephonyManager_UssdResponseCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManager_UssdResponseCallbackClass,_di_JTelephonyManager_UssdResponseCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManager_UssdResponseCallbackClass,_di_JTelephonyManager_UssdResponseCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTelephonyManager_UssdResponseCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTelephonyManager_UssdResponseCallbackClass,_di_JTelephonyManager_UssdResponseCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTelephonyManager_UssdResponseCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{336F6B7D-63A9-467A-A696-619D200ABF52}") JVisualVoicemailServiceClass  : public Androidapi::Jni::App::JServiceClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetSERVICE_INTERFACE() = 0 ;
	HIDESBASE virtual _di_JVisualVoicemailService __cdecl init() = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString SERVICE_INTERFACE = {read=_GetSERVICE_INTERFACE};
};

__interface  INTERFACE_UUID("{2CD44619-916D-4E14-967B-16C73431A524}") JVisualVoicemailService  : public Androidapi::Jni::App::JService 
{
	HIDESBASE virtual Androidapi::Jni::Os::_di_JIBinder __cdecl onBind(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent intent) = 0 ;
	virtual void __cdecl onSmsReceived(_di_JVisualVoicemailService_VisualVoicemailTask task, _di_JVisualVoicemailSms sms) = 0 ;
	virtual void __cdecl onStopped(_di_JVisualVoicemailService_VisualVoicemailTask task) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisualVoicemailService : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailServiceClass,_di_JVisualVoicemailService>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailServiceClass,_di_JVisualVoicemailService> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisualVoicemailService() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailServiceClass,_di_JVisualVoicemailService>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisualVoicemailService() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8F06F81C-DF44-47FD-BE24-65C536CB21FC}") JVisualVoicemailService_VisualVoicemailTaskClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3AAC9A1A-C72E-43FF-9649-94D4CEC01B75}") JVisualVoicemailService_VisualVoicemailTask  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual void __cdecl finish() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisualVoicemailService_VisualVoicemailTask : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailService_VisualVoicemailTaskClass,_di_JVisualVoicemailService_VisualVoicemailTask>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailService_VisualVoicemailTaskClass,_di_JVisualVoicemailService_VisualVoicemailTask> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisualVoicemailService_VisualVoicemailTask() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailService_VisualVoicemailTaskClass,_di_JVisualVoicemailService_VisualVoicemailTask>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisualVoicemailService_VisualVoicemailTask() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8AA434EB-5FFB-4F0A-8A7B-E8F5B7101340}") JVisualVoicemailSmsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{34969245-D8EF-4020-BF72-4B0DDF47B946}") JVisualVoicemailSms  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl describeContents() = 0 ;
	virtual Androidapi::Jni::Os::_di_JBundle __cdecl getFields() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMessageBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPrefix() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisualVoicemailSms : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsClass,_di_JVisualVoicemailSms>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsClass,_di_JVisualVoicemailSms> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisualVoicemailSms() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsClass,_di_JVisualVoicemailSms>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisualVoicemailSms() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80EE86AD-EBCF-4B1C-8332-D5B6DA81DCAB}") JVisualVoicemailSmsFilterSettingsClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	virtual int __cdecl _GetDESTINATION_PORT_ANY() = 0 ;
	virtual int __cdecl _GetDESTINATION_PORT_DATA_SMS() = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
	__property int DESTINATION_PORT_ANY = {read=_GetDESTINATION_PORT_ANY};
	__property int DESTINATION_PORT_DATA_SMS = {read=_GetDESTINATION_PORT_DATA_SMS};
};

__interface  INTERFACE_UUID("{344C0FC0-663A-43D9-BFE7-6838E4FA08C1}") JVisualVoicemailSmsFilterSettings  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetclientPrefix() = 0 ;
	virtual int __cdecl _GetdestinationPort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl _GetoriginatingNumbers() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString clientPrefix = {read=_GetclientPrefix};
	__property int destinationPort = {read=_GetdestinationPort};
	__property Androidapi::Jni::Javatypes::_di_JList originatingNumbers = {read=_GetoriginatingNumbers};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisualVoicemailSmsFilterSettings : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettingsClass,_di_JVisualVoicemailSmsFilterSettings>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettingsClass,_di_JVisualVoicemailSmsFilterSettings> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisualVoicemailSmsFilterSettings() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettingsClass,_di_JVisualVoicemailSmsFilterSettings>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisualVoicemailSmsFilterSettings() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{08F69835-A7CE-47E7-8483-C65CEA9217DB}") JVisualVoicemailSmsFilterSettings_BuilderClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JVisualVoicemailSmsFilterSettings_Builder __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{7BD5DA71-F4FF-4F9B-AFC2-BA8FCF5DAD8A}") JVisualVoicemailSmsFilterSettings_Builder  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JVisualVoicemailSmsFilterSettings __cdecl build() = 0 ;
	virtual _di_JVisualVoicemailSmsFilterSettings_Builder __cdecl setClientPrefix(Androidapi::Jni::Javatypes::_di_JString clientPrefix) = 0 ;
	virtual _di_JVisualVoicemailSmsFilterSettings_Builder __cdecl setDestinationPort(int destinationPort) = 0 ;
	virtual _di_JVisualVoicemailSmsFilterSettings_Builder __cdecl setOriginatingNumbers(Androidapi::Jni::Javatypes::_di_JList originatingNumbers) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJVisualVoicemailSmsFilterSettings_Builder : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettings_BuilderClass,_di_JVisualVoicemailSmsFilterSettings_Builder>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettings_BuilderClass,_di_JVisualVoicemailSmsFilterSettings_Builder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJVisualVoicemailSmsFilterSettings_Builder() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JVisualVoicemailSmsFilterSettings_BuilderClass,_di_JVisualVoicemailSmsFilterSettings_Builder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJVisualVoicemailSmsFilterSettings_Builder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0287239E-831E-4687-B06D-87243B3FC994}") JCdmaCellLocationClass  : public JCellLocationClass 
{
	HIDESBASE virtual _di_JCdmaCellLocation __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JCdmaCellLocation __cdecl init(Androidapi::Jni::Os::_di_JBundle bundle) = 0 /* overload */;
	virtual double __cdecl convertQuartSecToDecDegrees(int quartSec) = 0 ;
};

__interface  INTERFACE_UUID("{30F5155B-56EB-4449-A3B2-90BFE8F170EB}") JCdmaCellLocation  : public JCellLocation 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual void __cdecl fillInNotifierBundle(Androidapi::Jni::Os::_di_JBundle bundleToFill) = 0 ;
	virtual int __cdecl getBaseStationId() = 0 ;
	virtual int __cdecl getBaseStationLatitude() = 0 ;
	virtual int __cdecl getBaseStationLongitude() = 0 ;
	virtual int __cdecl getNetworkId() = 0 ;
	virtual int __cdecl getSystemId() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setCellLocationData(int baseStationId, int baseStationLatitude, int baseStationLongitude) = 0 /* overload */;
	virtual void __cdecl setCellLocationData(int baseStationId, int baseStationLatitude, int baseStationLongitude, int systemId, int networkId) = 0 /* overload */;
	virtual void __cdecl setStateInvalid() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCdmaCellLocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCdmaCellLocationClass,_di_JCdmaCellLocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCdmaCellLocationClass,_di_JCdmaCellLocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCdmaCellLocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCdmaCellLocationClass,_di_JCdmaCellLocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCdmaCellLocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{31FDA1F7-0041-4FF2-91D2-F15D974EAC2C}") JGsmCellLocationClass  : public JCellLocationClass 
{
	HIDESBASE virtual _di_JGsmCellLocation __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JGsmCellLocation __cdecl init(Androidapi::Jni::Os::_di_JBundle bundle) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{D09EE10D-C54B-40AB-AE80-461A6AC0DB66}") JGsmCellLocation  : public JCellLocation 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	virtual void __cdecl fillInNotifierBundle(Androidapi::Jni::Os::_di_JBundle m) = 0 ;
	virtual int __cdecl getCid() = 0 ;
	virtual int __cdecl getLac() = 0 ;
	virtual int __cdecl getPsc() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual void __cdecl setLacAndCid(int lac, int cid) = 0 ;
	virtual void __cdecl setStateInvalid() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJGsmCellLocation : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGsmCellLocationClass,_di_JGsmCellLocation>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGsmCellLocationClass,_di_JGsmCellLocation> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJGsmCellLocation() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JGsmCellLocationClass,_di_JGsmCellLocation>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJGsmCellLocation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{17F8CCF3-8CA3-4E7C-86AA-CD21CF9AE9C5}") Jgsm_SmsManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetRESULT_ERROR_GENERIC_FAILURE() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_NO_SERVICE() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_NULL_PDU() = 0 ;
	virtual int __cdecl _GetRESULT_ERROR_RADIO_OFF() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_SIM_FREE() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_SIM_READ() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_SIM_SENT() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_SIM_UNREAD() = 0 ;
	virtual int __cdecl _GetSTATUS_ON_SIM_UNSENT() = 0 ;
	virtual _di_Jgsm_SmsManager __cdecl getDefault() = 0 ;
	__property int RESULT_ERROR_GENERIC_FAILURE = {read=_GetRESULT_ERROR_GENERIC_FAILURE};
	__property int RESULT_ERROR_NO_SERVICE = {read=_GetRESULT_ERROR_NO_SERVICE};
	__property int RESULT_ERROR_NULL_PDU = {read=_GetRESULT_ERROR_NULL_PDU};
	__property int RESULT_ERROR_RADIO_OFF = {read=_GetRESULT_ERROR_RADIO_OFF};
	__property int STATUS_ON_SIM_FREE = {read=_GetSTATUS_ON_SIM_FREE};
	__property int STATUS_ON_SIM_READ = {read=_GetSTATUS_ON_SIM_READ};
	__property int STATUS_ON_SIM_SENT = {read=_GetSTATUS_ON_SIM_SENT};
	__property int STATUS_ON_SIM_UNREAD = {read=_GetSTATUS_ON_SIM_UNREAD};
	__property int STATUS_ON_SIM_UNSENT = {read=_GetSTATUS_ON_SIM_UNSENT};
};

__interface  INTERFACE_UUID("{0E3A70E1-7A4B-4480-896E-62E41FBF913E}") Jgsm_SmsManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JArrayList __cdecl divideMessage(Androidapi::Jni::Javatypes::_di_JString text) = 0 ;
	virtual void __cdecl sendDataMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, short destinationPort, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, Androidapi::Jni::App::_di_JPendingIntent sentIntent, Androidapi::Jni::App::_di_JPendingIntent deliveryIntent) = 0 ;
	virtual void __cdecl sendMultipartTextMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JArrayList parts, Androidapi::Jni::Javatypes::_di_JArrayList sentIntents, Androidapi::Jni::Javatypes::_di_JArrayList deliveryIntents) = 0 ;
	virtual void __cdecl sendTextMessage(Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString text, Androidapi::Jni::App::_di_JPendingIntent sentIntent, Androidapi::Jni::App::_di_JPendingIntent deliveryIntent) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJgsm_SmsManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsManagerClass,_di_Jgsm_SmsManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsManagerClass,_di_Jgsm_SmsManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJgsm_SmsManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsManagerClass,_di_Jgsm_SmsManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJgsm_SmsManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F5132C01-2558-4829-8125-7EACA7B45F08}") Jgsm_SmsMessageClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual int __cdecl _GetENCODING_16BIT() = 0 ;
	virtual int __cdecl _GetENCODING_7BIT() = 0 ;
	virtual int __cdecl _GetENCODING_8BIT() = 0 ;
	virtual int __cdecl _GetENCODING_UNKNOWN() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_BYTES() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_SEPTETS() = 0 ;
	virtual int __cdecl _GetMAX_USER_DATA_SEPTETS_WITH_HEADER() = 0 ;
	HIDESBASE virtual _di_Jgsm_SmsMessage __cdecl init() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl calculateLength(Androidapi::Jni::Javatypes::_di_JCharSequence messageBody, bool use7bitOnly) = 0 /* overload */;
	virtual Androidapi::Jnibridge::TJavaArray__1<int>* __cdecl calculateLength(Androidapi::Jni::Javatypes::_di_JString messageBody, bool use7bitOnly) = 0 /* overload */;
	virtual _di_Jgsm_SmsMessage __cdecl createFromPdu(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* pdu) = 0 ;
	virtual _di_Jgsm_SmsMessage_SubmitPdu __cdecl getSubmitPdu(Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString destinationAddress, Androidapi::Jni::Javatypes::_di_JString message, bool statusReportRequested) = 0 /* overload */;
	virtual _di_Jgsm_SmsMessage_SubmitPdu __cdecl getSubmitPdu(Androidapi::Jni::Javatypes::_di_JString scAddress, Androidapi::Jni::Javatypes::_di_JString destinationAddress, short destinationPort, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* data, bool statusReportRequested) = 0 /* overload */;
	virtual int __cdecl getTPLayerLengthForPDU(Androidapi::Jni::Javatypes::_di_JString pdu) = 0 ;
	__property int ENCODING_16BIT = {read=_GetENCODING_16BIT};
	__property int ENCODING_7BIT = {read=_GetENCODING_7BIT};
	__property int ENCODING_8BIT = {read=_GetENCODING_8BIT};
	__property int ENCODING_UNKNOWN = {read=_GetENCODING_UNKNOWN};
	__property int MAX_USER_DATA_BYTES = {read=_GetMAX_USER_DATA_BYTES};
	__property int MAX_USER_DATA_SEPTETS = {read=_GetMAX_USER_DATA_SEPTETS};
	__property int MAX_USER_DATA_SEPTETS_WITH_HEADER = {read=_GetMAX_USER_DATA_SEPTETS_WITH_HEADER};
};

__interface  INTERFACE_UUID("{71AD7E64-87CA-4EC5-BB5B-91DCB9A3F8D5}") Jgsm_SmsMessage  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDisplayMessageBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDisplayOriginatingAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEmailBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEmailFrom() = 0 ;
	virtual int __cdecl getIndexOnSim() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getMessageBody() = 0 ;
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl getMessageClass() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getOriginatingAddress() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getPdu() = 0 ;
	virtual int __cdecl getProtocolIdentifier() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPseudoSubject() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getServiceCenterAddress() = 0 ;
	virtual int __cdecl getStatus() = 0 ;
	virtual int __cdecl getStatusOnSim() = 0 ;
	virtual __int64 __cdecl getTimestampMillis() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getUserData() = 0 ;
	virtual bool __cdecl isCphsMwiMessage() = 0 ;
	virtual bool __cdecl isEmail() = 0 ;
	virtual bool __cdecl isMWIClearMessage() = 0 ;
	virtual bool __cdecl isMWISetMessage() = 0 ;
	virtual bool __cdecl isMwiDontStore() = 0 ;
	virtual bool __cdecl isReplace() = 0 ;
	virtual bool __cdecl isReplyPathPresent() = 0 ;
	virtual bool __cdecl isStatusReportMessage() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJgsm_SmsMessage : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessageClass,_di_Jgsm_SmsMessage>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessageClass,_di_Jgsm_SmsMessage> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJgsm_SmsMessage() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessageClass,_di_Jgsm_SmsMessage>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJgsm_SmsMessage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39AF35BE-04BA-4BA5-815F-EAF9192F6413}") Jgsm_SmsMessage_MessageClassClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl _GetCLASS_0() = 0 ;
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl _GetCLASS_1() = 0 ;
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl _GetCLASS_2() = 0 ;
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl _GetCLASS_3() = 0 ;
	virtual _di_Jgsm_SmsMessage_MessageClass __cdecl _GetUNKNOWN() = 0 ;
	HIDESBASE virtual _di_Jgsm_SmsMessage_MessageClass __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_Jgsm_SmsMessage_MessageClass>* __cdecl values() = 0 ;
	__property _di_Jgsm_SmsMessage_MessageClass CLASS_0 = {read=_GetCLASS_0};
	__property _di_Jgsm_SmsMessage_MessageClass CLASS_1 = {read=_GetCLASS_1};
	__property _di_Jgsm_SmsMessage_MessageClass CLASS_2 = {read=_GetCLASS_2};
	__property _di_Jgsm_SmsMessage_MessageClass CLASS_3 = {read=_GetCLASS_3};
	__property _di_Jgsm_SmsMessage_MessageClass UNKNOWN = {read=_GetUNKNOWN};
};

__interface  INTERFACE_UUID("{2A8F0F0C-A782-40C9-A015-DEB6470488E3}") Jgsm_SmsMessage_MessageClass  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJgsm_SmsMessage_MessageClass : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_MessageClassClass,_di_Jgsm_SmsMessage_MessageClass>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_MessageClassClass,_di_Jgsm_SmsMessage_MessageClass> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJgsm_SmsMessage_MessageClass() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_MessageClassClass,_di_Jgsm_SmsMessage_MessageClass>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJgsm_SmsMessage_MessageClass() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1F8AD068-26C6-4018-AC53-2568912E18AC}") Jgsm_SmsMessage_SubmitPduClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jgsm_SmsMessage_SubmitPdu __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{F5357F33-764B-4656-9332-78162CB99DEF}") Jgsm_SmsMessage_SubmitPdu  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetencodedMessage() = 0 ;
	virtual void __cdecl _SetencodedMessage(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* Value) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl _GetencodedScAddress() = 0 ;
	virtual void __cdecl _SetencodedScAddress(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* Value) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* encodedMessage = {read=_GetencodedMessage, write=_SetencodedMessage};
	__property Androidapi::Jnibridge::TJavaArray__1<System::Byte>* encodedScAddress = {read=_GetencodedScAddress, write=_SetencodedScAddress};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJgsm_SmsMessage_SubmitPdu : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_SubmitPduClass,_di_Jgsm_SmsMessage_SubmitPdu>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_SubmitPduClass,_di_Jgsm_SmsMessage_SubmitPdu> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJgsm_SmsMessage_SubmitPdu() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jgsm_SmsMessage_SubmitPduClass,_di_Jgsm_SmsMessage_SubmitPdu>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJgsm_SmsMessage_SubmitPdu() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Telephony */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_TELEPHONY)
using namespace Androidapi::Jni::Telephony;
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
#endif	// Androidapi_Jni_TelephonyHPP
