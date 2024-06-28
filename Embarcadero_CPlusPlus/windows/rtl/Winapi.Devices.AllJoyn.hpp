// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Devices.AllJoyn.pas' rev: 34.00 (Windows)

#ifndef Winapi_Devices_AlljoynHPP
#define Winapi_Devices_AlljoynHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.SystemRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Security.Cryptography.hpp>
#include <Winapi.Security.Credentials.hpp>
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.Globalization.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Devices
{
namespace Alljoyn
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IAllJoynStatusStatics;
typedef System::DelphiInterface<IAllJoynStatusStatics> _di_IAllJoynStatusStatics;
__interface DELPHIINTERFACE IAllJoynAboutData;
typedef System::DelphiInterface<IAllJoynAboutData> _di_IAllJoynAboutData;
__interface DELPHIINTERFACE IAllJoynBusAttachmentStateChangedEventArgs;
typedef System::DelphiInterface<IAllJoynBusAttachmentStateChangedEventArgs> _di_IAllJoynBusAttachmentStateChangedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs;
__interface DELPHIINTERFACE IIterator_1__AllJoynAuthenticationMechanism_Base;
typedef System::DelphiInterface<IIterator_1__AllJoynAuthenticationMechanism_Base> _di_IIterator_1__AllJoynAuthenticationMechanism_Base;
__interface DELPHIINTERFACE IIterator_1__AllJoynAuthenticationMechanism;
typedef System::DelphiInterface<IIterator_1__AllJoynAuthenticationMechanism> _di_IIterator_1__AllJoynAuthenticationMechanism;
__interface DELPHIINTERFACE IIterable_1__AllJoynAuthenticationMechanism_Base;
typedef System::DelphiInterface<IIterable_1__AllJoynAuthenticationMechanism_Base> _di_IIterable_1__AllJoynAuthenticationMechanism_Base;
__interface DELPHIINTERFACE IIterable_1__AllJoynAuthenticationMechanism;
typedef System::DelphiInterface<IIterable_1__AllJoynAuthenticationMechanism> _di_IIterable_1__AllJoynAuthenticationMechanism;
__interface DELPHIINTERFACE IVectorView_1__AllJoynAuthenticationMechanism;
typedef System::DelphiInterface<IVectorView_1__AllJoynAuthenticationMechanism> _di_IVectorView_1__AllJoynAuthenticationMechanism;
__interface DELPHIINTERFACE IVector_1__AllJoynAuthenticationMechanism;
typedef System::DelphiInterface<IVector_1__AllJoynAuthenticationMechanism> _di_IVector_1__AllJoynAuthenticationMechanism;
__interface DELPHIINTERFACE IAllJoynCredentials;
typedef System::DelphiInterface<IAllJoynCredentials> _di_IAllJoynCredentials;
__interface DELPHIINTERFACE IAllJoynCredentialsRequestedEventArgs;
typedef System::DelphiInterface<IAllJoynCredentialsRequestedEventArgs> _di_IAllJoynCredentialsRequestedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs;
__interface DELPHIINTERFACE IAllJoynCredentialsVerificationRequestedEventArgs;
typedef System::DelphiInterface<IAllJoynCredentialsVerificationRequestedEventArgs> _di_IAllJoynCredentialsVerificationRequestedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs;
__interface DELPHIINTERFACE IAllJoynAuthenticationCompleteEventArgs;
typedef System::DelphiInterface<IAllJoynAuthenticationCompleteEventArgs> _di_IAllJoynAuthenticationCompleteEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs;
__interface DELPHIINTERFACE IAllJoynBusAttachment;
typedef System::DelphiInterface<IAllJoynBusAttachment> _di_IAllJoynBusAttachment;
__interface DELPHIINTERFACE IAllJoynAboutDataView;
typedef System::DelphiInterface<IAllJoynAboutDataView> _di_IAllJoynAboutDataView;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynAboutDataView_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynAboutDataView_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynAboutDataView;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynAboutDataView> _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynAboutDataView_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynAboutDataView_Base> _di_IAsyncOperation_1__IAllJoynAboutDataView_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynAboutDataView;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynAboutDataView> _di_IAsyncOperation_1__IAllJoynAboutDataView;
__interface DELPHIINTERFACE IAllJoynServiceInfo;
typedef System::DelphiInterface<IAllJoynServiceInfo> _di_IAllJoynServiceInfo;
__interface DELPHIINTERFACE IAllJoynAcceptSessionJoinerEventArgs;
typedef System::DelphiInterface<IAllJoynAcceptSessionJoinerEventArgs> _di_IAllJoynAcceptSessionJoinerEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs;
__interface DELPHIINTERFACE IAllJoynSessionMemberAddedEventArgs;
typedef System::DelphiInterface<IAllJoynSessionMemberAddedEventArgs> _di_IAllJoynSessionMemberAddedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs;
__interface DELPHIINTERFACE IAllJoynSessionMemberRemovedEventArgs;
typedef System::DelphiInterface<IAllJoynSessionMemberRemovedEventArgs> _di_IAllJoynSessionMemberRemovedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs;
__interface DELPHIINTERFACE IAllJoynSessionLostEventArgs;
typedef System::DelphiInterface<IAllJoynSessionLostEventArgs> _di_IAllJoynSessionLostEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs> _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs;
__interface DELPHIINTERFACE IAllJoynSession;
typedef System::DelphiInterface<IAllJoynSession> _di_IAllJoynSession;
__interface DELPHIINTERFACE IAllJoynSessionJoinedEventArgs;
typedef System::DelphiInterface<IAllJoynSessionJoinedEventArgs> _di_IAllJoynSessionJoinedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs> _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs;
__interface DELPHIINTERFACE IAllJoynBusAttachment2;
typedef System::DelphiInterface<IAllJoynBusAttachment2> _di_IAllJoynBusAttachment2;
__interface DELPHIINTERFACE IAllJoynBusAttachmentStatics;
typedef System::DelphiInterface<IAllJoynBusAttachmentStatics> _di_IAllJoynBusAttachmentStatics;
__interface DELPHIINTERFACE IAllJoynBusAttachmentFactory;
typedef System::DelphiInterface<IAllJoynBusAttachmentFactory> _di_IAllJoynBusAttachmentFactory;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynSession_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynSession_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IAllJoynSession_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynSession;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynSession> _di_AsyncOperationCompletedHandler_1__IAllJoynSession;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynSession_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynSession_Base> _di_IAsyncOperation_1__IAllJoynSession_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynSession;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynSession> _di_IAsyncOperation_1__IAllJoynSession;
__interface DELPHIINTERFACE IAllJoynSessionStatics;
typedef System::DelphiInterface<IAllJoynSessionStatics> _di_IAllJoynSessionStatics;
__interface DELPHIINTERFACE IAllJoynBusObjectStoppedEventArgs;
typedef System::DelphiInterface<IAllJoynBusObjectStoppedEventArgs> _di_IAllJoynBusObjectStoppedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs_Delegate_Base> _di_TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs> _di_TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs;
__interface DELPHIINTERFACE IAllJoynBusObject;
typedef System::DelphiInterface<IAllJoynBusObject> _di_IAllJoynBusObject;
__interface DELPHIINTERFACE IAllJoynProducer;
typedef System::DelphiInterface<IAllJoynProducer> _di_IAllJoynProducer;
__interface DELPHIINTERFACE IAllJoynBusObjectFactory;
typedef System::DelphiInterface<IAllJoynBusObjectFactory> _di_IAllJoynBusObjectFactory;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynServiceInfo_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynServiceInfo_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IAllJoynServiceInfo;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IAllJoynServiceInfo> _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynServiceInfo_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynServiceInfo_Base> _di_IAsyncOperation_1__IAllJoynServiceInfo_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IAllJoynServiceInfo;
typedef System::DelphiInterface<IAsyncOperation_1__IAllJoynServiceInfo> _di_IAsyncOperation_1__IAllJoynServiceInfo;
__interface DELPHIINTERFACE IAllJoynServiceInfoStatics;
typedef System::DelphiInterface<IAllJoynServiceInfoStatics> _di_IAllJoynServiceInfoStatics;
__interface DELPHIINTERFACE IAllJoynServiceInfoFactory;
typedef System::DelphiInterface<IAllJoynServiceInfoFactory> _di_IAllJoynServiceInfoFactory;
__interface DELPHIINTERFACE IAllJoynAboutDataViewStatics;
typedef System::DelphiInterface<IAllJoynAboutDataViewStatics> _di_IAllJoynAboutDataViewStatics;
__interface DELPHIINTERFACE IAllJoynAcceptSessionJoiner;
typedef System::DelphiInterface<IAllJoynAcceptSessionJoiner> _di_IAllJoynAcceptSessionJoiner;
__interface DELPHIINTERFACE IAllJoynAcceptSessionJoinerEventArgsFactory;
typedef System::DelphiInterface<IAllJoynAcceptSessionJoinerEventArgsFactory> _di_IAllJoynAcceptSessionJoinerEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynSessionMemberAddedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynSessionMemberAddedEventArgsFactory> _di_IAllJoynSessionMemberAddedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynSessionMemberRemovedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynSessionMemberRemovedEventArgsFactory> _di_IAllJoynSessionMemberRemovedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynSessionJoinedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynSessionJoinedEventArgsFactory> _di_IAllJoynSessionJoinedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynSessionLostEventArgsFactory;
typedef System::DelphiInterface<IAllJoynSessionLostEventArgsFactory> _di_IAllJoynSessionLostEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynProducerStoppedEventArgs;
typedef System::DelphiInterface<IAllJoynProducerStoppedEventArgs> _di_IAllJoynProducerStoppedEventArgs;
__interface DELPHIINTERFACE IAllJoynProducerStoppedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynProducerStoppedEventArgsFactory> _di_IAllJoynProducerStoppedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynBusObjectStoppedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynBusObjectStoppedEventArgsFactory> _di_IAllJoynBusObjectStoppedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynWatcherStoppedEventArgs;
typedef System::DelphiInterface<IAllJoynWatcherStoppedEventArgs> _di_IAllJoynWatcherStoppedEventArgs;
__interface DELPHIINTERFACE IAllJoynWatcherStoppedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynWatcherStoppedEventArgsFactory> _di_IAllJoynWatcherStoppedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynServiceInfoRemovedEventArgs;
typedef System::DelphiInterface<IAllJoynServiceInfoRemovedEventArgs> _di_IAllJoynServiceInfoRemovedEventArgs;
__interface DELPHIINTERFACE IAllJoynServiceInfoRemovedEventArgsFactory;
typedef System::DelphiInterface<IAllJoynServiceInfoRemovedEventArgsFactory> _di_IAllJoynServiceInfoRemovedEventArgsFactory;
__interface DELPHIINTERFACE IAllJoynMessageInfo;
typedef System::DelphiInterface<IAllJoynMessageInfo> _di_IAllJoynMessageInfo;
__interface DELPHIINTERFACE IAllJoynMessageInfoFactory;
typedef System::DelphiInterface<IAllJoynMessageInfoFactory> _di_IAllJoynMessageInfoFactory;
class DELPHICLASS TAllJoynStatus;
class DELPHICLASS TAllJoynBusAttachment;
class DELPHICLASS TAllJoynServiceInfo;
class DELPHICLASS TAllJoynAboutDataView;
class DELPHICLASS TAllJoynAcceptSessionJoinerEventArgs;
class DELPHICLASS TAllJoynSessionJoinedEventArgs;
class DELPHICLASS TAllJoynSession;
class DELPHICLASS TAllJoynSessionMemberAddedEventArgs;
class DELPHICLASS TAllJoynSessionMemberRemovedEventArgs;
class DELPHICLASS TAllJoynSessionLostEventArgs;
class DELPHICLASS TAllJoynBusObject;
class DELPHICLASS TAllJoynBusObjectStoppedEventArgs;
class DELPHICLASS TAllJoynProducerStoppedEventArgs;
class DELPHICLASS TAllJoynWatcherStoppedEventArgs;
class DELPHICLASS TAllJoynServiceInfoRemovedEventArgs;
class DELPHICLASS TAllJoynMessageInfo;
//-- type declarations -------------------------------------------------------
typedef _di_IAllJoynStatusStatics *PIAllJoynStatusStatics;

typedef _di_IAllJoynAboutData *PIAllJoynAboutData;

typedef _di_IAllJoynBusAttachmentStateChangedEventArgs *PIAllJoynBusAttachmentStateChangedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs;

typedef _di_IIterator_1__AllJoynAuthenticationMechanism *PIIterator_1__AllJoynAuthenticationMechanism;

typedef _di_IIterable_1__AllJoynAuthenticationMechanism *PIIterable_1__AllJoynAuthenticationMechanism;

typedef _di_IVectorView_1__AllJoynAuthenticationMechanism *PIVectorView_1__AllJoynAuthenticationMechanism;

typedef _di_IVector_1__AllJoynAuthenticationMechanism *PIVector_1__AllJoynAuthenticationMechanism;

typedef _di_IAllJoynCredentials *PIAllJoynCredentials;

typedef _di_IAllJoynCredentialsRequestedEventArgs *PIAllJoynCredentialsRequestedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs;

typedef _di_IAllJoynCredentialsVerificationRequestedEventArgs *PIAllJoynCredentialsVerificationRequestedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs;

typedef _di_IAllJoynAuthenticationCompleteEventArgs *PIAllJoynAuthenticationCompleteEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs;

typedef _di_IAllJoynBusAttachment *PIAllJoynBusAttachment;

typedef _di_IAllJoynAboutDataView *PIAllJoynAboutDataView;

typedef _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView *PAsyncOperationCompletedHandler_1__IAllJoynAboutDataView;

typedef _di_IAsyncOperation_1__IAllJoynAboutDataView *PIAsyncOperation_1__IAllJoynAboutDataView;

typedef _di_IAllJoynServiceInfo *PIAllJoynServiceInfo;

typedef _di_IAllJoynAcceptSessionJoinerEventArgs *PIAllJoynAcceptSessionJoinerEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs;

typedef _di_IAllJoynSessionMemberAddedEventArgs *PIAllJoynSessionMemberAddedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs *PTypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs;

typedef _di_IAllJoynSessionMemberRemovedEventArgs *PIAllJoynSessionMemberRemovedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs *PTypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs;

typedef _di_IAllJoynSessionLostEventArgs *PIAllJoynSessionLostEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs *PTypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs;

typedef _di_IAllJoynSession *PIAllJoynSession;

typedef _di_IAllJoynSessionJoinedEventArgs *PIAllJoynSessionJoinedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs *PTypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs;

typedef _di_IAllJoynBusAttachment2 *PIAllJoynBusAttachment2;

typedef _di_IAllJoynBusAttachmentStatics *PIAllJoynBusAttachmentStatics;

typedef _di_IAllJoynBusAttachmentFactory *PIAllJoynBusAttachmentFactory;

typedef _di_AsyncOperationCompletedHandler_1__IAllJoynSession *PAsyncOperationCompletedHandler_1__IAllJoynSession;

typedef _di_IAsyncOperation_1__IAllJoynSession *PIAsyncOperation_1__IAllJoynSession;

typedef _di_IAllJoynSessionStatics *PIAllJoynSessionStatics;

typedef _di_IAllJoynBusObjectStoppedEventArgs *PIAllJoynBusObjectStoppedEventArgs;

typedef _di_TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs *PTypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs;

typedef _di_IAllJoynBusObject *PIAllJoynBusObject;

typedef _di_IAllJoynProducer *PIAllJoynProducer;

typedef _di_IAllJoynBusObjectFactory *PIAllJoynBusObjectFactory;

typedef _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo *PAsyncOperationCompletedHandler_1__IAllJoynServiceInfo;

typedef _di_IAsyncOperation_1__IAllJoynServiceInfo *PIAsyncOperation_1__IAllJoynServiceInfo;

typedef _di_IAllJoynServiceInfoStatics *PIAllJoynServiceInfoStatics;

typedef _di_IAllJoynServiceInfoFactory *PIAllJoynServiceInfoFactory;

typedef _di_IAllJoynAboutDataViewStatics *PIAllJoynAboutDataViewStatics;

typedef _di_IAllJoynAcceptSessionJoiner *PIAllJoynAcceptSessionJoiner;

typedef _di_IAllJoynAcceptSessionJoinerEventArgsFactory *PIAllJoynAcceptSessionJoinerEventArgsFactory;

typedef _di_IAllJoynSessionMemberAddedEventArgsFactory *PIAllJoynSessionMemberAddedEventArgsFactory;

typedef _di_IAllJoynSessionMemberRemovedEventArgsFactory *PIAllJoynSessionMemberRemovedEventArgsFactory;

typedef _di_IAllJoynSessionJoinedEventArgsFactory *PIAllJoynSessionJoinedEventArgsFactory;

typedef _di_IAllJoynSessionLostEventArgsFactory *PIAllJoynSessionLostEventArgsFactory;

typedef _di_IAllJoynProducerStoppedEventArgs *PIAllJoynProducerStoppedEventArgs;

typedef _di_IAllJoynProducerStoppedEventArgsFactory *PIAllJoynProducerStoppedEventArgsFactory;

typedef _di_IAllJoynBusObjectStoppedEventArgsFactory *PIAllJoynBusObjectStoppedEventArgsFactory;

typedef _di_IAllJoynWatcherStoppedEventArgs *PIAllJoynWatcherStoppedEventArgs;

typedef _di_IAllJoynWatcherStoppedEventArgsFactory *PIAllJoynWatcherStoppedEventArgsFactory;

typedef _di_IAllJoynServiceInfoRemovedEventArgs *PIAllJoynServiceInfoRemovedEventArgs;

typedef _di_IAllJoynServiceInfoRemovedEventArgsFactory *PIAllJoynServiceInfoRemovedEventArgsFactory;

typedef _di_IAllJoynMessageInfo *PIAllJoynMessageInfo;

typedef _di_IAllJoynMessageInfoFactory *PIAllJoynMessageInfoFactory;

__interface  INTERFACE_UUID("{D0B7A17E-0D29-4DA9-8AC6-54C554BEDBC5}") IAllJoynStatusStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Ok(int &__get_Ok_result) = 0 ;
	virtual HRESULT __safecall get_Fail(int &__get_Fail_result) = 0 ;
	virtual HRESULT __safecall get_OperationTimedOut(int &__get_OperationTimedOut_result) = 0 ;
	virtual HRESULT __safecall get_OtherEndClosed(int &__get_OtherEndClosed_result) = 0 ;
	virtual HRESULT __safecall get_ConnectionRefused(int &__get_ConnectionRefused_result) = 0 ;
	virtual HRESULT __safecall get_AuthenticationFailed(int &__get_AuthenticationFailed_result) = 0 ;
	virtual HRESULT __safecall get_AuthenticationRejectedByUser(int &__get_AuthenticationRejectedByUser_result) = 0 ;
	virtual HRESULT __safecall get_SslConnectFailed(int &__get_SslConnectFailed_result) = 0 ;
	virtual HRESULT __safecall get_SslIdentityVerificationFailed(int &__get_SslIdentityVerificationFailed_result) = 0 ;
	virtual HRESULT __safecall get_InsufficientSecurity(int &__get_InsufficientSecurity_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument1(int &__get_InvalidArgument1_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument2(int &__get_InvalidArgument2_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument3(int &__get_InvalidArgument3_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument4(int &__get_InvalidArgument4_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument5(int &__get_InvalidArgument5_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument6(int &__get_InvalidArgument6_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument7(int &__get_InvalidArgument7_result) = 0 ;
	virtual HRESULT __safecall get_InvalidArgument8(int &__get_InvalidArgument8_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_AuthenticationFailed() { int __r; HRESULT __hr = get_AuthenticationFailed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int AuthenticationFailed = {read=_scw_get_AuthenticationFailed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_AuthenticationRejectedByUser() { int __r; HRESULT __hr = get_AuthenticationRejectedByUser(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int AuthenticationRejectedByUser = {read=_scw_get_AuthenticationRejectedByUser};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_ConnectionRefused() { int __r; HRESULT __hr = get_ConnectionRefused(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int ConnectionRefused = {read=_scw_get_ConnectionRefused};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Fail() { int __r; HRESULT __hr = get_Fail(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Fail = {read=_scw_get_Fail};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InsufficientSecurity() { int __r; HRESULT __hr = get_InsufficientSecurity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InsufficientSecurity = {read=_scw_get_InsufficientSecurity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument1() { int __r; HRESULT __hr = get_InvalidArgument1(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument1 = {read=_scw_get_InvalidArgument1};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument2() { int __r; HRESULT __hr = get_InvalidArgument2(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument2 = {read=_scw_get_InvalidArgument2};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument3() { int __r; HRESULT __hr = get_InvalidArgument3(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument3 = {read=_scw_get_InvalidArgument3};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument4() { int __r; HRESULT __hr = get_InvalidArgument4(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument4 = {read=_scw_get_InvalidArgument4};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument5() { int __r; HRESULT __hr = get_InvalidArgument5(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument5 = {read=_scw_get_InvalidArgument5};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument6() { int __r; HRESULT __hr = get_InvalidArgument6(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument6 = {read=_scw_get_InvalidArgument6};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument7() { int __r; HRESULT __hr = get_InvalidArgument7(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument7 = {read=_scw_get_InvalidArgument7};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_InvalidArgument8() { int __r; HRESULT __hr = get_InvalidArgument8(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int InvalidArgument8 = {read=_scw_get_InvalidArgument8};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Ok() { int __r; HRESULT __hr = get_Ok(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Ok = {read=_scw_get_Ok};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_OperationTimedOut() { int __r; HRESULT __hr = get_OperationTimedOut(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int OperationTimedOut = {read=_scw_get_OperationTimedOut};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_OtherEndClosed() { int __r; HRESULT __hr = get_OtherEndClosed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int OtherEndClosed = {read=_scw_get_OtherEndClosed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_SslConnectFailed() { int __r; HRESULT __hr = get_SslConnectFailed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int SslConnectFailed = {read=_scw_get_SslConnectFailed};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_SslIdentityVerificationFailed() { int __r; HRESULT __hr = get_SslIdentityVerificationFailed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int SslIdentityVerificationFailed = {read=_scw_get_SslIdentityVerificationFailed};
};

__interface  INTERFACE_UUID("{E5A9BF00-1FA2-4839-93EF-F9DF404890F7}") IAllJoynAboutData  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsEnabled(bool &__get_IsEnabled_result) = 0 ;
	virtual HRESULT __safecall put_IsEnabled(bool value) = 0 ;
	virtual HRESULT __safecall get_DefaultAppName(HSTRING &__get_DefaultAppName_result) = 0 ;
	virtual HRESULT __safecall put_DefaultAppName(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_AppNames(Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING &__get_AppNames_result) = 0 ;
	virtual HRESULT __safecall get_DateOfManufacture(Winapi::Commontypes::_di_IReference_1__DateTime &__get_DateOfManufacture_result) = 0 ;
	virtual HRESULT __safecall put_DateOfManufacture(Winapi::Commontypes::_di_IReference_1__DateTime value) = 0 ;
	virtual HRESULT __safecall get_DefaultDescription(HSTRING &__get_DefaultDescription_result) = 0 ;
	virtual HRESULT __safecall put_DefaultDescription(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Descriptions(Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING &__get_Descriptions_result) = 0 ;
	virtual HRESULT __safecall get_DefaultManufacturer(HSTRING &__get_DefaultManufacturer_result) = 0 ;
	virtual HRESULT __safecall put_DefaultManufacturer(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Manufacturers(Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING &__get_Manufacturers_result) = 0 ;
	virtual HRESULT __safecall get_ModelNumber(HSTRING &__get_ModelNumber_result) = 0 ;
	virtual HRESULT __safecall put_ModelNumber(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_SoftwareVersion(HSTRING &__get_SoftwareVersion_result) = 0 ;
	virtual HRESULT __safecall put_SoftwareVersion(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_SupportUrl(Winapi::Commontypes::_di_IUriRuntimeClass &__get_SupportUrl_result) = 0 ;
	virtual HRESULT __safecall put_SupportUrl(Winapi::Commontypes::_di_IUriRuntimeClass value) = 0 ;
	virtual HRESULT __safecall get_AppId(GUID &__get_AppId_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_AppId(GUID value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_AppId(const GUID &value) = 0 ;
#endif /* _WIN64 */
	#pragma option push -w-inl
	/* safecall wrapper */ inline GUID _scw_get_AppId() { GUID __r; HRESULT __hr = get_AppId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property GUID AppId = {read=_scw_get_AppId, write=put_AppId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING _scw_get_AppNames() { Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING __r; HRESULT __hr = get_AppNames(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING AppNames = {read=_scw_get_AppNames};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_DateOfManufacture() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_DateOfManufacture(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime DateOfManufacture = {read=_scw_get_DateOfManufacture, write=put_DateOfManufacture};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DefaultAppName() { HSTRING __r; HRESULT __hr = get_DefaultAppName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DefaultAppName = {read=_scw_get_DefaultAppName, write=put_DefaultAppName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DefaultDescription() { HSTRING __r; HRESULT __hr = get_DefaultDescription(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DefaultDescription = {read=_scw_get_DefaultDescription, write=put_DefaultDescription};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DefaultManufacturer() { HSTRING __r; HRESULT __hr = get_DefaultManufacturer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DefaultManufacturer = {read=_scw_get_DefaultManufacturer, write=put_DefaultManufacturer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING _scw_get_Descriptions() { Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING __r; HRESULT __hr = get_Descriptions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING Descriptions = {read=_scw_get_Descriptions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsEnabled() { bool __r; HRESULT __hr = get_IsEnabled(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsEnabled = {read=_scw_get_IsEnabled, write=put_IsEnabled};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING _scw_get_Manufacturers() { Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING __r; HRESULT __hr = get_Manufacturers(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IMap_2__HSTRING__HSTRING Manufacturers = {read=_scw_get_Manufacturers};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ModelNumber() { HSTRING __r; HRESULT __hr = get_ModelNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ModelNumber = {read=_scw_get_ModelNumber, write=put_ModelNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SoftwareVersion() { HSTRING __r; HRESULT __hr = get_SoftwareVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SoftwareVersion = {read=_scw_get_SoftwareVersion, write=put_SoftwareVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_SupportUrl() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_SupportUrl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass SupportUrl = {read=_scw_get_SupportUrl, write=put_SupportUrl};
};

__interface  INTERFACE_UUID("{D82E75F4-C02A-41EC-A8D5-EAB1558953AA}") IAllJoynBusAttachmentStateChangedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_State(Winapi::Commontypes::AllJoynBusAttachmentState &__get_State_result) = 0 ;
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynBusAttachmentState _scw_get_State() { Winapi::Commontypes::AllJoynBusAttachmentState __r; HRESULT __hr = get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynBusAttachmentState State = {read=_scw_get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{82A8561D-3693-5C90-8CF2-58DE83D80243}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{29DC3D05-5B86-5A84-8420-640DC74209A6}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynBusAttachmentStateChangedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{0FBC36D2-F46E-5A4D-AA10-4C806B4945D6}") IIterator_1__AllJoynAuthenticationMechanism_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{752850B9-5ED2-5655-8DE2-262EFC26CF39}") IIterator_1__AllJoynAuthenticationMechanism  : public IIterator_1__AllJoynAuthenticationMechanism_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::AllJoynAuthenticationMechanism &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PAllJoynAuthenticationMechanism items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynAuthenticationMechanism _scw_get_Current() { Winapi::Commontypes::AllJoynAuthenticationMechanism __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynAuthenticationMechanism Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{D307C7AF-4106-5D1C-B06C-5EB593D9BE34}") IIterable_1__AllJoynAuthenticationMechanism_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1B6614A1-8FC5-567D-9157-410A9E0ECBC5}") IIterable_1__AllJoynAuthenticationMechanism  : public IIterable_1__AllJoynAuthenticationMechanism_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__AllJoynAuthenticationMechanism &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86D0B56E-CB4E-58F0-B9A2-1528619DCD26}") IVectorView_1__AllJoynAuthenticationMechanism  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::AllJoynAuthenticationMechanism &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::AllJoynAuthenticationMechanism value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PAllJoynAuthenticationMechanism items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A4739064-B54E-55D4-8012-317E2B6A807B}") IVector_1__AllJoynAuthenticationMechanism  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, Winapi::Commontypes::AllJoynAuthenticationMechanism &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__AllJoynAuthenticationMechanism &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(Winapi::Commontypes::AllJoynAuthenticationMechanism value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, Winapi::Commontypes::AllJoynAuthenticationMechanism value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, Winapi::Commontypes::AllJoynAuthenticationMechanism value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(Winapi::Commontypes::AllJoynAuthenticationMechanism value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Commontypes::PAllJoynAuthenticationMechanism items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, Winapi::Commontypes::PAllJoynAuthenticationMechanism items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{824650F2-A190-40B1-ABAB-349EC244DFAA}") IAllJoynCredentials  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AuthenticationMechanism(Winapi::Commontypes::AllJoynAuthenticationMechanism &__get_AuthenticationMechanism_result) = 0 ;
	virtual HRESULT __safecall get_Certificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_Certificate_result) = 0 ;
	virtual HRESULT __safecall put_Certificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate value) = 0 ;
	virtual HRESULT __safecall get_PasswordCredential(Winapi::Security::Credentials::_di_IPasswordCredential &__get_PasswordCredential_result) = 0 ;
	virtual HRESULT __safecall put_PasswordCredential(Winapi::Security::Credentials::_di_IPasswordCredential value) = 0 ;
	virtual HRESULT __safecall get_Timeout(Winapi::Commontypes::TimeSpan &__get_Timeout_result) = 0 ;
	virtual HRESULT __safecall put_Timeout(Winapi::Commontypes::TimeSpan value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynAuthenticationMechanism _scw_get_AuthenticationMechanism() { Winapi::Commontypes::AllJoynAuthenticationMechanism __r; HRESULT __hr = get_AuthenticationMechanism(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynAuthenticationMechanism AuthenticationMechanism = {read=_scw_get_AuthenticationMechanism};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_Certificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_Certificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate Certificate = {read=_scw_get_Certificate, write=put_Certificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IPasswordCredential _scw_get_PasswordCredential() { Winapi::Security::Credentials::_di_IPasswordCredential __r; HRESULT __hr = get_PasswordCredential(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IPasswordCredential PasswordCredential = {read=_scw_get_PasswordCredential, write=put_PasswordCredential};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::TimeSpan _scw_get_Timeout() { Winapi::Commontypes::TimeSpan __r; HRESULT __hr = get_Timeout(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::TimeSpan Timeout = {read=_scw_get_Timeout, write=put_Timeout};
};

__interface  INTERFACE_UUID("{6A87E34E-B069-4B80-9E1A-41BC837C65D2}") IAllJoynCredentialsRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AttemptCount(System::Word &__get_AttemptCount_result) = 0 ;
	virtual HRESULT __safecall get_Credentials(_di_IAllJoynCredentials &__get_Credentials_result) = 0 ;
	virtual HRESULT __safecall get_PeerUniqueName(HSTRING &__get_PeerUniqueName_result) = 0 ;
	virtual HRESULT __safecall get_RequestedUserName(HSTRING &__get_RequestedUserName_result) = 0 ;
	virtual HRESULT __safecall GetDeferral(Winapi::Commontypes::_di_IDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_AttemptCount() { System::Word __r; HRESULT __hr = get_AttemptCount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word AttemptCount = {read=_scw_get_AttemptCount};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAllJoynCredentials _scw_get_Credentials() { _di_IAllJoynCredentials __r; HRESULT __hr = get_Credentials(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAllJoynCredentials Credentials = {read=_scw_get_Credentials};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PeerUniqueName() { HSTRING __r; HRESULT __hr = get_PeerUniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PeerUniqueName = {read=_scw_get_PeerUniqueName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RequestedUserName() { HSTRING __r; HRESULT __hr = get_RequestedUserName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RequestedUserName = {read=_scw_get_RequestedUserName};
};

__interface  INTERFACE_UUID("{AB2196E7-4B41-53BD-95B1-B80CAD824795}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E7DD83C2-EA54-565E-9FAA-4BEE17B6871B}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynCredentialsRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{800A7612-B805-44AF-A2E1-792AB655A2D0}") IAllJoynCredentialsVerificationRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AuthenticationMechanism(Winapi::Commontypes::AllJoynAuthenticationMechanism &__get_AuthenticationMechanism_result) = 0 ;
	virtual HRESULT __safecall get_PeerUniqueName(HSTRING &__get_PeerUniqueName_result) = 0 ;
	virtual HRESULT __safecall get_PeerCertificate(Winapi::Security::Cryptography::_di_Certificates_ICertificate &__get_PeerCertificate_result) = 0 ;
	virtual HRESULT __safecall get_PeerCertificateErrorSeverity(Winapi::Commontypes::SocketSslErrorSeverity &__get_PeerCertificateErrorSeverity_result) = 0 ;
	virtual HRESULT __safecall get_PeerCertificateErrors(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult &__get_PeerCertificateErrors_result) = 0 ;
	virtual HRESULT __safecall get_PeerIntermediateCertificates(Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate &__get_PeerIntermediateCertificates_result) = 0 ;
	virtual HRESULT __safecall Accept() = 0 ;
	virtual HRESULT __safecall GetDeferral(Winapi::Commontypes::_di_IDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynAuthenticationMechanism _scw_get_AuthenticationMechanism() { Winapi::Commontypes::AllJoynAuthenticationMechanism __r; HRESULT __hr = get_AuthenticationMechanism(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynAuthenticationMechanism AuthenticationMechanism = {read=_scw_get_AuthenticationMechanism};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_Certificates_ICertificate _scw_get_PeerCertificate() { Winapi::Security::Cryptography::_di_Certificates_ICertificate __r; HRESULT __hr = get_PeerCertificate(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_Certificates_ICertificate PeerCertificate = {read=_scw_get_PeerCertificate};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::SocketSslErrorSeverity _scw_get_PeerCertificateErrorSeverity() { Winapi::Commontypes::SocketSslErrorSeverity __r; HRESULT __hr = get_PeerCertificateErrorSeverity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::SocketSslErrorSeverity PeerCertificateErrorSeverity = {read=_scw_get_PeerCertificateErrorSeverity};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult _scw_get_PeerCertificateErrors() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult __r; HRESULT __hr = get_PeerCertificateErrors(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ChainValidationResult PeerCertificateErrors = {read=_scw_get_PeerCertificateErrors};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate _scw_get_PeerIntermediateCertificates() { Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate __r; HRESULT __hr = get_PeerIntermediateCertificates(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Cryptography::_di_IVectorView_1__Certificates_ICertificate PeerIntermediateCertificates = {read=_scw_get_PeerIntermediateCertificates};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PeerUniqueName() { HSTRING __r; HRESULT __hr = get_PeerUniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PeerUniqueName = {read=_scw_get_PeerUniqueName};
};

__interface  INTERFACE_UUID("{7EF99C96-51B1-5670-A41F-AE404F2FF53F}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4AD61AAB-D8D2-5DE7-B9C8-F595115E267F}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynCredentialsVerificationRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{97B4701C-15DC-4B53-B6A4-7D134300D7BF}") IAllJoynAuthenticationCompleteEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AuthenticationMechanism(Winapi::Commontypes::AllJoynAuthenticationMechanism &__get_AuthenticationMechanism_result) = 0 ;
	virtual HRESULT __safecall get_PeerUniqueName(HSTRING &__get_PeerUniqueName_result) = 0 ;
	virtual HRESULT __safecall get_Succeeded(bool &__get_Succeeded_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynAuthenticationMechanism _scw_get_AuthenticationMechanism() { Winapi::Commontypes::AllJoynAuthenticationMechanism __r; HRESULT __hr = get_AuthenticationMechanism(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynAuthenticationMechanism AuthenticationMechanism = {read=_scw_get_AuthenticationMechanism};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PeerUniqueName() { HSTRING __r; HRESULT __hr = get_PeerUniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PeerUniqueName = {read=_scw_get_PeerUniqueName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_Succeeded() { bool __r; HRESULT __hr = get_Succeeded(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool Succeeded = {read=_scw_get_Succeeded};
};

__interface  INTERFACE_UUID("{E4FD18B4-4CDE-508E-8084-63E7283262C5}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{67D215E8-9E69-5A88-815C-2098F6761202}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynAuthenticationCompleteEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{F309F153-1EED-42C3-A20E-436D41FE62F6}") IAllJoynBusAttachment  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AboutData(_di_IAllJoynAboutData &__get_AboutData_result) = 0 ;
	virtual HRESULT __safecall get_ConnectionSpecification(HSTRING &__get_ConnectionSpecification_result) = 0 ;
	virtual HRESULT __safecall get_State(Winapi::Commontypes::AllJoynBusAttachmentState &__get_State_result) = 0 ;
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	virtual HRESULT __safecall PingAsync(HSTRING uniqueName, Winapi::Applicationmodel::_di_IAsyncOperation_1__Integer &__PingAsync_result) = 0 ;
	virtual HRESULT __safecall Connect() = 0 ;
	virtual HRESULT __safecall Disconnect() = 0 ;
	virtual HRESULT __safecall add_StateChanged(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynBusAttachmentStateChangedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_StateChanged_result) = 0 ;
	virtual HRESULT __safecall remove_StateChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall get_AuthenticationMechanisms(_di_IVector_1__AllJoynAuthenticationMechanism &__get_AuthenticationMechanisms_result) = 0 ;
	virtual HRESULT __safecall add_CredentialsRequested(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_CredentialsRequested_result) = 0 ;
	virtual HRESULT __safecall remove_CredentialsRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_CredentialsVerificationRequested(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynCredentialsVerificationRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_CredentialsVerificationRequested_result) = 0 ;
	virtual HRESULT __safecall remove_CredentialsVerificationRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_AuthenticationComplete(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAuthenticationCompleteEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_AuthenticationComplete_result) = 0 ;
	virtual HRESULT __safecall remove_AuthenticationComplete(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAllJoynAboutData _scw_get_AboutData() { _di_IAllJoynAboutData __r; HRESULT __hr = get_AboutData(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAllJoynAboutData AboutData = {read=_scw_get_AboutData};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__AllJoynAuthenticationMechanism _scw_get_AuthenticationMechanisms() { _di_IVector_1__AllJoynAuthenticationMechanism __r; HRESULT __hr = get_AuthenticationMechanisms(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__AllJoynAuthenticationMechanism AuthenticationMechanisms = {read=_scw_get_AuthenticationMechanisms};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ConnectionSpecification() { HSTRING __r; HRESULT __hr = get_ConnectionSpecification(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ConnectionSpecification = {read=_scw_get_ConnectionSpecification};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynBusAttachmentState _scw_get_State() { Winapi::Commontypes::AllJoynBusAttachmentState __r; HRESULT __hr = get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynBusAttachmentState State = {read=_scw_get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{6823111F-6212-4934-9C48-E19CA4984288}") IAllJoynAboutDataView  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	virtual HRESULT __safecall get_Properties(Winapi::Applicationmodel::_di_IMapView_2__HSTRING__IInspectable &__get_Properties_result) = 0 ;
	virtual HRESULT __safecall get_AJSoftwareVersion(HSTRING &__get_AJSoftwareVersion_result) = 0 ;
	virtual HRESULT __safecall get_AppId(GUID &__get_AppId_result) = 0 ;
	virtual HRESULT __safecall get_DateOfManufacture(Winapi::Commontypes::_di_IReference_1__DateTime &__get_DateOfManufacture_result) = 0 ;
	virtual HRESULT __safecall get_DefaultLanguage(Winapi::Globalization::_di_ILanguage &__get_DefaultLanguage_result) = 0 ;
	virtual HRESULT __safecall get_DeviceId(HSTRING &__get_DeviceId_result) = 0 ;
	virtual HRESULT __safecall get_HardwareVersion(HSTRING &__get_HardwareVersion_result) = 0 ;
	virtual HRESULT __safecall get_ModelNumber(HSTRING &__get_ModelNumber_result) = 0 ;
	virtual HRESULT __safecall get_SoftwareVersion(HSTRING &__get_SoftwareVersion_result) = 0 ;
	virtual HRESULT __safecall get_SupportedLanguages(Winapi::Globalization::_di_IVectorView_1__ILanguage &__get_SupportedLanguages_result) = 0 ;
	virtual HRESULT __safecall get_SupportUrl(Winapi::Commontypes::_di_IUriRuntimeClass &__get_SupportUrl_result) = 0 ;
	virtual HRESULT __safecall get_AppName(HSTRING &__get_AppName_result) = 0 ;
	virtual HRESULT __safecall get_Description(HSTRING &__get_Description_result) = 0 ;
	virtual HRESULT __safecall get_DeviceName(HSTRING &__get_DeviceName_result) = 0 ;
	virtual HRESULT __safecall get_Manufacturer(HSTRING &__get_Manufacturer_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AJSoftwareVersion() { HSTRING __r; HRESULT __hr = get_AJSoftwareVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AJSoftwareVersion = {read=_scw_get_AJSoftwareVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline GUID _scw_get_AppId() { GUID __r; HRESULT __hr = get_AppId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property GUID AppId = {read=_scw_get_AppId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_AppName() { HSTRING __r; HRESULT __hr = get_AppName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING AppName = {read=_scw_get_AppName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_DateOfManufacture() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_DateOfManufacture(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime DateOfManufacture = {read=_scw_get_DateOfManufacture};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Globalization::_di_ILanguage _scw_get_DefaultLanguage() { Winapi::Globalization::_di_ILanguage __r; HRESULT __hr = get_DefaultLanguage(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Globalization::_di_ILanguage DefaultLanguage = {read=_scw_get_DefaultLanguage};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Description() { HSTRING __r; HRESULT __hr = get_Description(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Description = {read=_scw_get_Description};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceId() { HSTRING __r; HRESULT __hr = get_DeviceId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceId = {read=_scw_get_DeviceId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DeviceName() { HSTRING __r; HRESULT __hr = get_DeviceName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DeviceName = {read=_scw_get_DeviceName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HardwareVersion() { HSTRING __r; HRESULT __hr = get_HardwareVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HardwareVersion = {read=_scw_get_HardwareVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Manufacturer() { HSTRING __r; HRESULT __hr = get_Manufacturer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Manufacturer = {read=_scw_get_Manufacturer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ModelNumber() { HSTRING __r; HRESULT __hr = get_ModelNumber(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ModelNumber = {read=_scw_get_ModelNumber};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Applicationmodel::_di_IMapView_2__HSTRING__IInspectable _scw_get_Properties() { Winapi::Applicationmodel::_di_IMapView_2__HSTRING__IInspectable __r; HRESULT __hr = get_Properties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Applicationmodel::_di_IMapView_2__HSTRING__IInspectable Properties = {read=_scw_get_Properties};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SoftwareVersion() { HSTRING __r; HRESULT __hr = get_SoftwareVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SoftwareVersion = {read=_scw_get_SoftwareVersion};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_SupportUrl() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_SupportUrl(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass SupportUrl = {read=_scw_get_SupportUrl};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Globalization::_di_IVectorView_1__ILanguage _scw_get_SupportedLanguages() { Winapi::Globalization::_di_IVectorView_1__ILanguage __r; HRESULT __hr = get_SupportedLanguages(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Globalization::_di_IVectorView_1__ILanguage SupportedLanguages = {read=_scw_get_SupportedLanguages};
};

__interface  INTERFACE_UUID("{BA2DA2F5-F9B0-5C66-8FC9-7D437A67F28A}") AsyncOperationCompletedHandler_1__IAllJoynAboutDataView_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F8256533-24D4-517F-8837-AFB1442A90AB}") AsyncOperationCompletedHandler_1__IAllJoynAboutDataView  : public AsyncOperationCompletedHandler_1__IAllJoynAboutDataView_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IAllJoynAboutDataView asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{3757414E-F54B-51C4-8F2F-E0477559B2AD}") IAsyncOperation_1__IAllJoynAboutDataView_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{AA3E95CB-D128-5A0F-8E68-05ABB381FBEC}") IAsyncOperation_1__IAllJoynAboutDataView  : public IAsyncOperation_1__IAllJoynAboutDataView_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IAllJoynAboutDataView &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IAllJoynAboutDataView Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{4CBE8209-B93E-4182-999B-DDD000F9C575}") IAllJoynServiceInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	virtual HRESULT __safecall get_ObjectPath(HSTRING &__get_ObjectPath_result) = 0 ;
	virtual HRESULT __safecall get_SessionPort(System::Word &__get_SessionPort_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ObjectPath() { HSTRING __r; HRESULT __hr = get_ObjectPath(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ObjectPath = {read=_scw_get_ObjectPath};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_SessionPort() { System::Word __r; HRESULT __hr = get_SessionPort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word SessionPort = {read=_scw_get_SessionPort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{4EFB5365-3E8A-4257-8F10-539CE0D56C0F}") IAllJoynAcceptSessionJoinerEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	virtual HRESULT __safecall get_SessionPort(System::Word &__get_SessionPort_result) = 0 ;
	virtual HRESULT __safecall get_TrafficType(Winapi::Commontypes::AllJoynTrafficType &__get_TrafficType_result) = 0 ;
	virtual HRESULT __safecall get_SamePhysicalNode(bool &__get_SamePhysicalNode_result) = 0 ;
	virtual HRESULT __safecall get_SameNetwork(bool &__get_SameNetwork_result) = 0 ;
	virtual HRESULT __safecall Accept() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SameNetwork() { bool __r; HRESULT __hr = get_SameNetwork(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SameNetwork = {read=_scw_get_SameNetwork};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SamePhysicalNode() { bool __r; HRESULT __hr = get_SamePhysicalNode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SamePhysicalNode = {read=_scw_get_SamePhysicalNode};
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Word _scw_get_SessionPort() { System::Word __r; HRESULT __hr = get_SessionPort(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Word SessionPort = {read=_scw_get_SessionPort};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynTrafficType _scw_get_TrafficType() { Winapi::Commontypes::AllJoynTrafficType __r; HRESULT __hr = get_TrafficType(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynTrafficType TrafficType = {read=_scw_get_TrafficType};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{DD224D96-F45C-5E3D-8860-8596D0E474F0}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F41E75C7-5B92-52CC-AFEE-54CF2AE4A301}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynAcceptSessionJoinerEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{49A2798A-0DD1-46C1-9CD6-27190E503A5E}") IAllJoynSessionMemberAddedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{330BAA61-1C24-5FAA-AF3C-4D69AD2F1E31}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{4635741C-8ACC-5D6C-A0EF-1D2048BF3E61}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs  : public TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynSession sender, _di_IAllJoynSessionMemberAddedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{409A219F-AA4A-4893-B430-BAA1B63C6219}") IAllJoynSessionMemberRemovedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{2969ED7C-DB6C-58AA-9F6D-89E7FE089FC1}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{44FE5812-1C70-5379-BCA1-4D01BA4F5FAC}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs  : public TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynSession sender, _di_IAllJoynSessionMemberRemovedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{E766A48A-8BB8-4954-AE67-D2FA43D1F96B}") IAllJoynSessionLostEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Reason(Winapi::Commontypes::AllJoynSessionLostReason &__get_Reason_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::AllJoynSessionLostReason _scw_get_Reason() { Winapi::Commontypes::AllJoynSessionLostReason __r; HRESULT __hr = get_Reason(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::AllJoynSessionLostReason Reason = {read=_scw_get_Reason};
};

__interface  INTERFACE_UUID("{DFFC2B25-5AE2-52F1-BBC4-363CEFEDA03F}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{BEB06AF4-7AF5-5A3C-B032-00FC56F09D6D}") TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs  : public TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynSession sender, _di_IAllJoynSessionLostEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{E8D11B0C-C0D4-406C-88A9-A93EFA85D4B1}") IAllJoynSession  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(int &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	virtual HRESULT __safecall RemoveMemberAsync(HSTRING uniqueName, Winapi::Applicationmodel::_di_IAsyncOperation_1__Integer &__RemoveMemberAsync_result) = 0 ;
	virtual HRESULT __safecall add_MemberAdded(_di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberAddedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_MemberAdded_result) = 0 ;
	virtual HRESULT __safecall remove_MemberAdded(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_MemberRemoved(_di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionMemberRemovedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_MemberRemoved_result) = 0 ;
	virtual HRESULT __safecall remove_MemberRemoved(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_Lost(_di_TypedEventHandler_2__IAllJoynSession__IAllJoynSessionLostEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Lost_result) = 0 ;
	virtual HRESULT __safecall remove_Lost(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Id() { int __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{9E9F5BD0-B5D7-47C5-8DAB-B040CC192871}") IAllJoynSessionJoinedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Session(_di_IAllJoynSession &__get_Session_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAllJoynSession _scw_get_Session() { _di_IAllJoynSession __r; HRESULT __hr = get_Session(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAllJoynSession Session = {read=_scw_get_Session};
};

__interface  INTERFACE_UUID("{56BB8D26-39B6-53FA-8013-3781AA27A0BC}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{3BF101A7-25DA-56ED-B70D-CC1AC581A6CB}") TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs  : public TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusAttachment sender, _di_IAllJoynSessionJoinedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{3474CB1E-2368-43B2-B43E-6A3AC1278D98}") IAllJoynBusAttachment2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAboutDataAsync(_di_IAllJoynServiceInfo serviceInfo, _di_IAsyncOperation_1__IAllJoynAboutDataView &__GetAboutDataAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetAboutDataAsync(_di_IAllJoynServiceInfo serviceInfo, Winapi::Globalization::_di_ILanguage language, _di_IAsyncOperation_1__IAllJoynAboutDataView &__GetAboutDataAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall add_AcceptSessionJoinerRequested(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynAcceptSessionJoinerEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_AcceptSessionJoinerRequested_result) = 0 ;
	virtual HRESULT __safecall remove_AcceptSessionJoinerRequested(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	virtual HRESULT __safecall add_SessionJoined(_di_TypedEventHandler_2__IAllJoynBusAttachment__IAllJoynSessionJoinedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_SessionJoined_result) = 0 ;
	virtual HRESULT __safecall remove_SessionJoined(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{839D4D3D-1051-40D7-872A-8D0141115B1F}") IAllJoynBusAttachmentStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDefault(_di_IAllJoynBusAttachment &__GetDefault_result) = 0 ;
	virtual HRESULT __safecall GetWatcher(Winapi::Globalization::_di_IIterable_1__HSTRING requiredInterfaces, Winapi::Commontypes::_di_IDeviceWatcher &__GetWatcher_result) = 0 ;
};

__interface  INTERFACE_UUID("{642EF1A4-AD85-4DDF-90AE-604452B22288}") IAllJoynBusAttachmentFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING connectionSpecification, _di_IAllJoynBusAttachment &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{52490F64-C98F-5019-8361-B2A3E1679F27}") AsyncOperationCompletedHandler_1__IAllJoynSession_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{78CDCB8A-D7F3-5F4E-9768-B2D7C5C438B0}") AsyncOperationCompletedHandler_1__IAllJoynSession  : public AsyncOperationCompletedHandler_1__IAllJoynSession_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IAllJoynSession asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{74AE55F8-3D63-5472-913D-74E9A1125DD3}") IAsyncOperation_1__IAllJoynSession_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D17BD492-54E8-5B50-BB5C-512E616919D9}") IAsyncOperation_1__IAllJoynSession  : public IAsyncOperation_1__IAllJoynSession_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynSession handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynSession &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IAllJoynSession &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IAllJoynSession _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IAllJoynSession __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IAllJoynSession Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9E05D604-A06C-46D4-B46C-0B0B54105B44}") IAllJoynSessionStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetFromServiceInfoAsync(_di_IAllJoynServiceInfo serviceInfo, _di_IAsyncOperation_1__IAllJoynSession &__GetFromServiceInfoAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetFromServiceInfoAsync(_di_IAllJoynServiceInfo serviceInfo, _di_IAllJoynBusAttachment busAttachment, _di_IAsyncOperation_1__IAllJoynSession &__GetFromServiceInfoAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{DE102115-EF8E-4D42-B93B-A2AE74519766}") IAllJoynBusObjectStoppedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{9871592F-823D-5630-BE72-CA8F17846B71}") TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B9DF8852-3946-5AA4-AA38-4740B35089FE}") TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs  : public TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAllJoynBusObject sender, _di_IAllJoynBusObjectStoppedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{E8FD825E-F73A-490C-8804-04E026643047}") IAllJoynBusObject  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Start() = 0 ;
	virtual HRESULT __safecall Stop() = 0 ;
	virtual HRESULT __safecall AddProducer(_di_IAllJoynProducer producer) = 0 ;
	virtual HRESULT __safecall get_BusAttachment(_di_IAllJoynBusAttachment &__get_BusAttachment_result) = 0 ;
	virtual HRESULT __safecall get_Session(_di_IAllJoynSession &__get_Session_result) = 0 ;
	virtual HRESULT __safecall add_Stopped(_di_TypedEventHandler_2__IAllJoynBusObject__IAllJoynBusObjectStoppedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_Stopped_result) = 0 ;
	virtual HRESULT __safecall remove_Stopped(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAllJoynBusAttachment _scw_get_BusAttachment() { _di_IAllJoynBusAttachment __r; HRESULT __hr = get_BusAttachment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAllJoynBusAttachment BusAttachment = {read=_scw_get_BusAttachment};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IAllJoynSession _scw_get_Session() { _di_IAllJoynSession __r; HRESULT __hr = get_Session(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IAllJoynSession Session = {read=_scw_get_Session};
};

__interface  INTERFACE_UUID("{9D084679-469B-495A-A710-AC50F123069F}") IAllJoynProducer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetBusObject(_di_IAllJoynBusObject busObject) = 0 ;
};

__interface  INTERFACE_UUID("{2C2F9F0B-8E02-4F9C-AC27-EA6DAD5D3B50}") IAllJoynBusObjectFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING objectPath, _di_IAllJoynBusObject &__Create_result) = 0 ;
	virtual HRESULT __safecall CreateWithBusAttachment(HSTRING objectPath, _di_IAllJoynBusAttachment busAttachment, _di_IAllJoynBusObject &__CreateWithBusAttachment_result) = 0 ;
};

__interface  INTERFACE_UUID("{FFB22299-A9C9-5C2A-ACE3-0CD0A6DD1039}") AsyncOperationCompletedHandler_1__IAllJoynServiceInfo_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{83FD2C55-C8BD-5D40-A679-E12D36FE5A26}") AsyncOperationCompletedHandler_1__IAllJoynServiceInfo  : public AsyncOperationCompletedHandler_1__IAllJoynServiceInfo_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IAllJoynServiceInfo asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B9CE48C1-16CC-5E46-91D5-E5CD06F8026E}") IAsyncOperation_1__IAllJoynServiceInfo_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{96E9C54F-A203-54A5-8970-F1B0EA9D674A}") IAsyncOperation_1__IAllJoynServiceInfo  : public IAsyncOperation_1__IAllJoynServiceInfo_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IAllJoynServiceInfo &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IAllJoynServiceInfo Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{5678570A-603A-49FC-B750-0EF13609213C}") IAllJoynServiceInfoStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FromIdAsync(HSTRING deviceId, _di_IAsyncOperation_1__IAllJoynServiceInfo &__FromIdAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{7581DABD-FE03-4F4B-94A4-F02FDCBD11B8}") IAllJoynServiceInfoFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING uniqueName, HSTRING objectPath, System::Word sessionPort, _di_IAllJoynServiceInfo &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{57EDB688-0C5E-416E-88B5-39B32D25C47D}") IAllJoynAboutDataViewStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetDataBySessionPortAsync(HSTRING uniqueName, _di_IAllJoynBusAttachment busAttachment, System::Word sessionPort, _di_IAsyncOperation_1__IAllJoynAboutDataView &__GetDataBySessionPortAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall GetDataBySessionPortAsync(HSTRING uniqueName, _di_IAllJoynBusAttachment busAttachment, System::Word sessionPort, Winapi::Globalization::_di_ILanguage language, _di_IAsyncOperation_1__IAllJoynAboutDataView &__GetDataBySessionPortAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{4DA817D2-CD1D-4023-A7C4-16DEF89C28DF}") IAllJoynAcceptSessionJoiner  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Accept() = 0 ;
};

__interface  INTERFACE_UUID("{B4435BC0-6145-429E-84DB-D5BFE772B14F}") IAllJoynAcceptSessionJoinerEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING uniqueName, System::Word sessionPort, Winapi::Commontypes::AllJoynTrafficType trafficType, System::Byte proximity, _di_IAllJoynAcceptSessionJoiner acceptSessionJoiner, _di_IAllJoynAcceptSessionJoinerEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{341DE352-1D33-40A1-A1D3-E5777020E1F1}") IAllJoynSessionMemberAddedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING uniqueName, _di_IAllJoynSessionMemberAddedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{C4D355E8-42B8-4B67-B757-D0CFCAD59280}") IAllJoynSessionMemberRemovedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING uniqueName, _di_IAllJoynSessionMemberRemovedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{6824D689-D6CB-4D9E-A09E-35806870B17F}") IAllJoynSessionJoinedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(_di_IAllJoynSession session, _di_IAllJoynSessionJoinedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{13BBFD32-D2F4-49C9-980E-2805E13586B1}") IAllJoynSessionLostEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(Winapi::Commontypes::AllJoynSessionLostReason reason, _di_IAllJoynSessionLostEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{51309770-4937-492D-8080-236439987CEB}") IAllJoynProducerStoppedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{56529961-B219-4D6E-9F78-FA3F99FA8FE5}") IAllJoynProducerStoppedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(int status, _di_IAllJoynProducerStoppedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{6B22FD48-D0A3-4255-953A-4772B4028073}") IAllJoynBusObjectStoppedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(int status, _di_IAllJoynBusObjectStoppedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{C9FCA03B-701D-4AA8-97DD-A2BB0A8F5FA3}") IAllJoynWatcherStoppedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(int &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_Status() { int __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{878FA5A8-2D50-47E1-904A-20BF0D48C782}") IAllJoynWatcherStoppedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(int status, _di_IAllJoynWatcherStoppedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{3057A95F-1D3F-41F3-8969-E32792627396}") IAllJoynServiceInfoRemovedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UniqueName(HSTRING &__get_UniqueName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UniqueName() { HSTRING __r; HRESULT __hr = get_UniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UniqueName = {read=_scw_get_UniqueName};
};

__interface  INTERFACE_UUID("{0DBF8627-9AFF-4955-9227-6953BAF41569}") IAllJoynServiceInfoRemovedEventArgsFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING uniqueName, _di_IAllJoynServiceInfoRemovedEventArgs &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{FF2B0127-2C12-4859-AA3A-C74461EE814C}") IAllJoynMessageInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_SenderUniqueName(HSTRING &__get_SenderUniqueName_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_SenderUniqueName() { HSTRING __r; HRESULT __hr = get_SenderUniqueName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING SenderUniqueName = {read=_scw_get_SenderUniqueName};
};

__interface  INTERFACE_UUID("{34664C2A-8289-43D4-B4A8-3F4DE359F043}") IAllJoynMessageInfoFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(HSTRING senderUniqueName, _di_IAllJoynMessageInfo &__Create_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynStatus : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynStatusStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynStatusStatics> inherited;
	
public:
	static int __fastcall get_Ok();
	static int __fastcall get_Fail();
	static int __fastcall get_OperationTimedOut();
	static int __fastcall get_OtherEndClosed();
	static int __fastcall get_ConnectionRefused();
	static int __fastcall get_AuthenticationFailed();
	static int __fastcall get_AuthenticationRejectedByUser();
	static int __fastcall get_SslConnectFailed();
	static int __fastcall get_SslIdentityVerificationFailed();
	static int __fastcall get_InsufficientSecurity();
	static int __fastcall get_InvalidArgument1();
	static int __fastcall get_InvalidArgument2();
	static int __fastcall get_InvalidArgument3();
	static int __fastcall get_InvalidArgument4();
	static int __fastcall get_InvalidArgument5();
	static int __fastcall get_InvalidArgument6();
	static int __fastcall get_InvalidArgument7();
	static int __fastcall get_InvalidArgument8();
	/* static */ __property int AuthenticationFailed = {read=get_AuthenticationFailed, nodefault};
	/* static */ __property int AuthenticationRejectedByUser = {read=get_AuthenticationRejectedByUser, nodefault};
	/* static */ __property int ConnectionRefused = {read=get_ConnectionRefused, nodefault};
	/* static */ __property int Fail = {read=get_Fail, nodefault};
	/* static */ __property int InsufficientSecurity = {read=get_InsufficientSecurity, nodefault};
	/* static */ __property int InvalidArgument1 = {read=get_InvalidArgument1, nodefault};
	/* static */ __property int InvalidArgument2 = {read=get_InvalidArgument2, nodefault};
	/* static */ __property int InvalidArgument3 = {read=get_InvalidArgument3, nodefault};
	/* static */ __property int InvalidArgument4 = {read=get_InvalidArgument4, nodefault};
	/* static */ __property int InvalidArgument5 = {read=get_InvalidArgument5, nodefault};
	/* static */ __property int InvalidArgument6 = {read=get_InvalidArgument6, nodefault};
	/* static */ __property int InvalidArgument7 = {read=get_InvalidArgument7, nodefault};
	/* static */ __property int InvalidArgument8 = {read=get_InvalidArgument8, nodefault};
	/* static */ __property int Ok = {read=get_Ok, nodefault};
	/* static */ __property int OperationTimedOut = {read=get_OperationTimedOut, nodefault};
	/* static */ __property int OtherEndClosed = {read=get_OtherEndClosed, nodefault};
	/* static */ __property int SslConnectFailed = {read=get_SslConnectFailed, nodefault};
	/* static */ __property int SslIdentityVerificationFailed = {read=get_SslIdentityVerificationFailed, nodefault};
public:
	/* TObject.Create */ inline __fastcall TAllJoynStatus() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynStatusStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynStatus() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynBusAttachment : public System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IAllJoynBusAttachmentFactory,_di_IAllJoynBusAttachmentStatics,_di_IAllJoynBusAttachment>
{
	typedef System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IAllJoynBusAttachmentFactory,_di_IAllJoynBusAttachmentStatics,_di_IAllJoynBusAttachment> inherited;
	
public:
	static _di_IAllJoynBusAttachment __fastcall GetDefault();
	static Winapi::Commontypes::_di_IDeviceWatcher __fastcall GetWatcher(Winapi::Globalization::_di_IIterable_1__HSTRING requiredInterfaces);
	static _di_IAllJoynBusAttachment __fastcall Create(HSTRING connectionSpecification)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TAllJoynBusAttachment() : System::Win::Winrt::TWinRTGenericImportFSI__3<_di_IAllJoynBusAttachmentFactory,_di_IAllJoynBusAttachmentStatics,_di_IAllJoynBusAttachment>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynBusAttachment() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynServiceInfo : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_IAllJoynServiceInfoFactory,_di_IAllJoynServiceInfoStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_IAllJoynServiceInfoFactory,_di_IAllJoynServiceInfoStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IAllJoynServiceInfo __fastcall FromIdAsync(HSTRING deviceId);
	static _di_IAllJoynServiceInfo __fastcall Create(HSTRING uniqueName, HSTRING objectPath, System::Word sessionPort);
public:
	/* TObject.Create */ inline __fastcall TAllJoynServiceInfo() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_IAllJoynServiceInfoFactory,_di_IAllJoynServiceInfoStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynServiceInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynAboutDataView : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynAboutDataViewStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynAboutDataViewStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IAllJoynAboutDataView __fastcall GetDataBySessionPortAsync(HSTRING uniqueName, _di_IAllJoynBusAttachment busAttachment, System::Word sessionPort)/* overload */;
	static _di_IAsyncOperation_1__IAllJoynAboutDataView __fastcall GetDataBySessionPortAsync(HSTRING uniqueName, _di_IAllJoynBusAttachment busAttachment, System::Word sessionPort, Winapi::Globalization::_di_ILanguage language)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TAllJoynAboutDataView() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynAboutDataViewStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynAboutDataView() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynAcceptSessionJoinerEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynAcceptSessionJoinerEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynAcceptSessionJoinerEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynAcceptSessionJoinerEventArgs __fastcall Create(HSTRING uniqueName, System::Word sessionPort, Winapi::Commontypes::AllJoynTrafficType trafficType, System::Byte proximity, _di_IAllJoynAcceptSessionJoiner acceptSessionJoiner);
public:
	/* TObject.Create */ inline __fastcall TAllJoynAcceptSessionJoinerEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynAcceptSessionJoinerEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynAcceptSessionJoinerEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynSessionJoinedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionJoinedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionJoinedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynSessionJoinedEventArgs __fastcall Create(_di_IAllJoynSession session);
public:
	/* TObject.Create */ inline __fastcall TAllJoynSessionJoinedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionJoinedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynSessionJoinedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynSession : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynSessionStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynSessionStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__IAllJoynSession __fastcall GetFromServiceInfoAsync(_di_IAllJoynServiceInfo serviceInfo)/* overload */;
	static _di_IAsyncOperation_1__IAllJoynSession __fastcall GetFromServiceInfoAsync(_di_IAllJoynServiceInfo serviceInfo, _di_IAllJoynBusAttachment busAttachment)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TAllJoynSession() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IAllJoynSessionStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynSession() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynSessionMemberAddedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberAddedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberAddedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynSessionMemberAddedEventArgs __fastcall Create(HSTRING uniqueName);
public:
	/* TObject.Create */ inline __fastcall TAllJoynSessionMemberAddedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberAddedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynSessionMemberAddedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynSessionMemberRemovedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberRemovedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberRemovedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynSessionMemberRemovedEventArgs __fastcall Create(HSTRING uniqueName);
public:
	/* TObject.Create */ inline __fastcall TAllJoynSessionMemberRemovedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionMemberRemovedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynSessionMemberRemovedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynSessionLostEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionLostEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionLostEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynSessionLostEventArgs __fastcall Create(Winapi::Commontypes::AllJoynSessionLostReason reason);
public:
	/* TObject.Create */ inline __fastcall TAllJoynSessionLostEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynSessionLostEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynSessionLostEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynBusObject : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_IAllJoynBusObjectFactory,_di_IAllJoynBusObject>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_IAllJoynBusObjectFactory,_di_IAllJoynBusObject> inherited;
	
public:
	static _di_IAllJoynBusObject __fastcall Create(HSTRING objectPath)/* overload */;
	static _di_IAllJoynBusObject __fastcall CreateWithBusAttachment(HSTRING objectPath, _di_IAllJoynBusAttachment busAttachment);
public:
	/* TObject.Create */ inline __fastcall TAllJoynBusObject() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_IAllJoynBusObjectFactory,_di_IAllJoynBusObject>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynBusObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynBusObjectStoppedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynBusObjectStoppedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynBusObjectStoppedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynBusObjectStoppedEventArgs __fastcall Create(int status);
public:
	/* TObject.Create */ inline __fastcall TAllJoynBusObjectStoppedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynBusObjectStoppedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynBusObjectStoppedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynProducerStoppedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynProducerStoppedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynProducerStoppedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynProducerStoppedEventArgs __fastcall Create(int status);
public:
	/* TObject.Create */ inline __fastcall TAllJoynProducerStoppedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynProducerStoppedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynProducerStoppedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynWatcherStoppedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynWatcherStoppedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynWatcherStoppedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynWatcherStoppedEventArgs __fastcall Create(int status);
public:
	/* TObject.Create */ inline __fastcall TAllJoynWatcherStoppedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynWatcherStoppedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynWatcherStoppedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynServiceInfoRemovedEventArgs : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynServiceInfoRemovedEventArgsFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynServiceInfoRemovedEventArgsFactory> inherited;
	
public:
	static _di_IAllJoynServiceInfoRemovedEventArgs __fastcall Create(HSTRING uniqueName);
public:
	/* TObject.Create */ inline __fastcall TAllJoynServiceInfoRemovedEventArgs() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynServiceInfoRemovedEventArgsFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynServiceInfoRemovedEventArgs() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAllJoynMessageInfo : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynMessageInfoFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynMessageInfoFactory> inherited;
	
public:
	static _di_IAllJoynMessageInfo __fastcall Create(HSTRING senderUniqueName);
public:
	/* TObject.Create */ inline __fastcall TAllJoynMessageInfo() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IAllJoynMessageInfoFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAllJoynMessageInfo() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Alljoyn */
}	/* namespace Devices */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Devices_AlljoynHPP
