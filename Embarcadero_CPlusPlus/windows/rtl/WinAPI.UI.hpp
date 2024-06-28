// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.pas' rev: 34.00 (Windows)

#ifndef Winapi_UiHPP
#define Winapi_UiHPP

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
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Foundation.hpp>
#include <Winapi.Security.Credentials.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IReference_1__Color;
typedef System::DelphiInterface<IReference_1__Color> _di_IReference_1__Color;
__interface DELPHIINTERFACE Shell_IAdaptiveCard;
typedef System::DelphiInterface<Shell_IAdaptiveCard> _di_Shell_IAdaptiveCard;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__IInspectable> _di_IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__IInspectable> _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__IInspectable> _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IMapView_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IMapView_2__HSTRING__IInspectable> _di_IMapView_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IMap_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IMap_2__HSTRING__IInspectable> _di_IMap_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IMapChangedEventArgs_1__HSTRING;
typedef System::DelphiInterface<IMapChangedEventArgs_1__HSTRING> _di_IMapChangedEventArgs_1__HSTRING;
__interface DELPHIINTERFACE MapChangedEventHandler_2__HSTRING__IInspectable;
typedef System::DelphiInterface<MapChangedEventHandler_2__HSTRING__IInspectable> _di_MapChangedEventHandler_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE IObservableMap_2__HSTRING__IInspectable;
typedef System::DelphiInterface<IObservableMap_2__HSTRING__IInspectable> _di_IObservableMap_2__HSTRING__IInspectable;
__interface DELPHIINTERFACE Popups_UICommandInvokedHandler;
typedef System::DelphiInterface<Popups_UICommandInvokedHandler> _di_Popups_UICommandInvokedHandler;
__interface DELPHIINTERFACE Popups_IUICommand;
typedef System::DelphiInterface<Popups_IUICommand> _di_Popups_IUICommand;
__interface DELPHIINTERFACE IIterator_1__Popups_IUICommand_Base;
typedef System::DelphiInterface<IIterator_1__Popups_IUICommand_Base> _di_IIterator_1__Popups_IUICommand_Base;
__interface DELPHIINTERFACE IIterator_1__Popups_IUICommand;
typedef System::DelphiInterface<IIterator_1__Popups_IUICommand> _di_IIterator_1__Popups_IUICommand;
__interface DELPHIINTERFACE IIterable_1__Popups_IUICommand_Base;
typedef System::DelphiInterface<IIterable_1__Popups_IUICommand_Base> _di_IIterable_1__Popups_IUICommand_Base;
__interface DELPHIINTERFACE IIterable_1__Popups_IUICommand;
typedef System::DelphiInterface<IIterable_1__Popups_IUICommand> _di_IIterable_1__Popups_IUICommand;
__interface DELPHIINTERFACE IVectorView_1__Popups_IUICommand;
typedef System::DelphiInterface<IVectorView_1__Popups_IUICommand> _di_IVectorView_1__Popups_IUICommand;
__interface DELPHIINTERFACE IVector_1__Popups_IUICommand;
typedef System::DelphiInterface<IVector_1__Popups_IUICommand> _di_IVector_1__Popups_IUICommand;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Popups_IUICommand_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Popups_IUICommand_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Popups_IUICommand_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Popups_IUICommand;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Popups_IUICommand> _di_AsyncOperationCompletedHandler_1__Popups_IUICommand;
__interface DELPHIINTERFACE IAsyncOperation_1__Popups_IUICommand_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Popups_IUICommand_Base> _di_IAsyncOperation_1__Popups_IUICommand_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Popups_IUICommand;
typedef System::DelphiInterface<IAsyncOperation_1__Popups_IUICommand> _di_IAsyncOperation_1__Popups_IUICommand;
__interface DELPHIINTERFACE ApplicationSettings_ISettingsCommandFactory;
typedef System::DelphiInterface<ApplicationSettings_ISettingsCommandFactory> _di_ApplicationSettings_ISettingsCommandFactory;
__interface DELPHIINTERFACE ApplicationSettings_ISettingsCommandStatics;
typedef System::DelphiInterface<ApplicationSettings_ISettingsCommandStatics> _di_ApplicationSettings_ISettingsCommandStatics;
__interface DELPHIINTERFACE ApplicationSettings_IWebAccountProviderCommand;
typedef System::DelphiInterface<ApplicationSettings_IWebAccountProviderCommand> _di_ApplicationSettings_IWebAccountProviderCommand;
__interface DELPHIINTERFACE ApplicationSettings_WebAccountProviderCommandInvokedHandler;
typedef System::DelphiInterface<ApplicationSettings_WebAccountProviderCommandInvokedHandler> _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler;
__interface DELPHIINTERFACE ApplicationSettings_IWebAccountProviderCommandFactory;
typedef System::DelphiInterface<ApplicationSettings_IWebAccountProviderCommandFactory> _di_ApplicationSettings_IWebAccountProviderCommandFactory;
__interface DELPHIINTERFACE ApplicationSettings_IWebAccountCommand;
typedef System::DelphiInterface<ApplicationSettings_IWebAccountCommand> _di_ApplicationSettings_IWebAccountCommand;
__interface DELPHIINTERFACE ApplicationSettings_IWebAccountInvokedArgs;
typedef System::DelphiInterface<ApplicationSettings_IWebAccountInvokedArgs> _di_ApplicationSettings_IWebAccountInvokedArgs;
__interface DELPHIINTERFACE ApplicationSettings_WebAccountCommandInvokedHandler;
typedef System::DelphiInterface<ApplicationSettings_WebAccountCommandInvokedHandler> _di_ApplicationSettings_WebAccountCommandInvokedHandler;
__interface DELPHIINTERFACE ApplicationSettings_IWebAccountCommandFactory;
typedef System::DelphiInterface<ApplicationSettings_IWebAccountCommandFactory> _di_ApplicationSettings_IWebAccountCommandFactory;
__interface DELPHIINTERFACE ApplicationSettings_ICredentialCommand;
typedef System::DelphiInterface<ApplicationSettings_ICredentialCommand> _di_ApplicationSettings_ICredentialCommand;
__interface DELPHIINTERFACE ApplicationSettings_CredentialCommandCredentialDeletedHandler;
typedef System::DelphiInterface<ApplicationSettings_CredentialCommandCredentialDeletedHandler> _di_ApplicationSettings_CredentialCommandCredentialDeletedHandler;
__interface DELPHIINTERFACE ApplicationSettings_IAccountsSettingsPaneEventDeferral;
typedef System::DelphiInterface<ApplicationSettings_IAccountsSettingsPaneEventDeferral> _di_ApplicationSettings_IAccountsSettingsPaneEventDeferral;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_IWebAccountProviderCommand_Base;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_IWebAccountProviderCommand_Base> _di_IIterator_1__ApplicationSettings_IWebAccountProviderCommand_Base;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_IWebAccountProviderCommand;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_IWebAccountProviderCommand> _di_IIterator_1__ApplicationSettings_IWebAccountProviderCommand;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_IWebAccountProviderCommand_Base;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_IWebAccountProviderCommand_Base> _di_IIterable_1__ApplicationSettings_IWebAccountProviderCommand_Base;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_IWebAccountProviderCommand;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_IWebAccountProviderCommand> _di_IIterable_1__ApplicationSettings_IWebAccountProviderCommand;
__interface DELPHIINTERFACE IVectorView_1__ApplicationSettings_IWebAccountProviderCommand;
typedef System::DelphiInterface<IVectorView_1__ApplicationSettings_IWebAccountProviderCommand> _di_IVectorView_1__ApplicationSettings_IWebAccountProviderCommand;
__interface DELPHIINTERFACE IVector_1__ApplicationSettings_IWebAccountProviderCommand;
typedef System::DelphiInterface<IVector_1__ApplicationSettings_IWebAccountProviderCommand> _di_IVector_1__ApplicationSettings_IWebAccountProviderCommand;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_IWebAccountCommand_Base;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_IWebAccountCommand_Base> _di_IIterator_1__ApplicationSettings_IWebAccountCommand_Base;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_IWebAccountCommand;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_IWebAccountCommand> _di_IIterator_1__ApplicationSettings_IWebAccountCommand;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_IWebAccountCommand_Base;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_IWebAccountCommand_Base> _di_IIterable_1__ApplicationSettings_IWebAccountCommand_Base;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_IWebAccountCommand;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_IWebAccountCommand> _di_IIterable_1__ApplicationSettings_IWebAccountCommand;
__interface DELPHIINTERFACE IVectorView_1__ApplicationSettings_IWebAccountCommand;
typedef System::DelphiInterface<IVectorView_1__ApplicationSettings_IWebAccountCommand> _di_IVectorView_1__ApplicationSettings_IWebAccountCommand;
__interface DELPHIINTERFACE IVector_1__ApplicationSettings_IWebAccountCommand;
typedef System::DelphiInterface<IVector_1__ApplicationSettings_IWebAccountCommand> _di_IVector_1__ApplicationSettings_IWebAccountCommand;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_ICredentialCommand_Base;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_ICredentialCommand_Base> _di_IIterator_1__ApplicationSettings_ICredentialCommand_Base;
__interface DELPHIINTERFACE IIterator_1__ApplicationSettings_ICredentialCommand;
typedef System::DelphiInterface<IIterator_1__ApplicationSettings_ICredentialCommand> _di_IIterator_1__ApplicationSettings_ICredentialCommand;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_ICredentialCommand_Base;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_ICredentialCommand_Base> _di_IIterable_1__ApplicationSettings_ICredentialCommand_Base;
__interface DELPHIINTERFACE IIterable_1__ApplicationSettings_ICredentialCommand;
typedef System::DelphiInterface<IIterable_1__ApplicationSettings_ICredentialCommand> _di_IIterable_1__ApplicationSettings_ICredentialCommand;
__interface DELPHIINTERFACE IVectorView_1__ApplicationSettings_ICredentialCommand;
typedef System::DelphiInterface<IVectorView_1__ApplicationSettings_ICredentialCommand> _di_IVectorView_1__ApplicationSettings_ICredentialCommand;
__interface DELPHIINTERFACE IVector_1__ApplicationSettings_ICredentialCommand;
typedef System::DelphiInterface<IVector_1__ApplicationSettings_ICredentialCommand> _di_IVector_1__ApplicationSettings_ICredentialCommand;
__interface DELPHIINTERFACE ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;
typedef System::DelphiInterface<ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs> _di_ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs_Delegate_Base> _di_TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs> _di_TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;
__interface DELPHIINTERFACE ApplicationSettings_IAccountsSettingsPane;
typedef System::DelphiInterface<ApplicationSettings_IAccountsSettingsPane> _di_ApplicationSettings_IAccountsSettingsPane;
__interface DELPHIINTERFACE ApplicationSettings_IAccountsSettingsPaneStatics;
typedef System::DelphiInterface<ApplicationSettings_IAccountsSettingsPaneStatics> _di_ApplicationSettings_IAccountsSettingsPaneStatics;
__interface DELPHIINTERFACE ApplicationSettings_IAccountsSettingsPaneStatics2;
typedef System::DelphiInterface<ApplicationSettings_IAccountsSettingsPaneStatics2> _di_ApplicationSettings_IAccountsSettingsPaneStatics2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Boolean;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Boolean> _di_AsyncOperationCompletedHandler_1__Boolean;
__interface DELPHIINTERFACE IAsyncOperation_1__Boolean;
typedef System::DelphiInterface<IAsyncOperation_1__Boolean> _di_IAsyncOperation_1__Boolean;
__interface DELPHIINTERFACE EventHandler_1__IInspectable;
typedef System::DelphiInterface<EventHandler_1__IInspectable> _di_EventHandler_1__IInspectable;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__IBuffer__Cardinal> _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal> _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__IBuffer__Cardinal;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__IBuffer__Cardinal> _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__Cardinal__Cardinal;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__Cardinal__Cardinal> _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal> _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__Cardinal__Cardinal;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__Cardinal__Cardinal> _di_IAsyncOperationWithProgress_2__Cardinal__Cardinal;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IInspectable;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IInspectable> _di_AsyncOperationCompletedHandler_1__IInspectable;
__interface DELPHIINTERFACE IAsyncOperation_1__IInspectable;
typedef System::DelphiInterface<IAsyncOperation_1__IInspectable> _di_IAsyncOperation_1__IInspectable;
__interface DELPHIINTERFACE IIterator_1__HSTRING;
typedef System::DelphiInterface<IIterator_1__HSTRING> _di_IIterator_1__HSTRING;
__interface DELPHIINTERFACE IIterable_1__HSTRING;
typedef System::DelphiInterface<IIterable_1__HSTRING> _di_IIterable_1__HSTRING;
__interface DELPHIINTERFACE IVectorView_1__HSTRING;
typedef System::DelphiInterface<IVectorView_1__HSTRING> _di_IVectorView_1__HSTRING;
__interface DELPHIINTERFACE IReference_1__Single;
typedef System::DelphiInterface<IReference_1__Single> _di_IReference_1__Single;
__interface DELPHIINTERFACE IKeyValuePair_2__HSTRING__HSTRING;
typedef System::DelphiInterface<IKeyValuePair_2__HSTRING__HSTRING> _di_IKeyValuePair_2__HSTRING__HSTRING;
__interface DELPHIINTERFACE IIterator_1__IKeyValuePair_2__HSTRING__HSTRING;
typedef System::DelphiInterface<IIterator_1__IKeyValuePair_2__HSTRING__HSTRING> _di_IIterator_1__IKeyValuePair_2__HSTRING__HSTRING;
__interface DELPHIINTERFACE IIterable_1__IKeyValuePair_2__HSTRING__HSTRING;
typedef System::DelphiInterface<IIterable_1__IKeyValuePair_2__HSTRING__HSTRING> _di_IIterable_1__IKeyValuePair_2__HSTRING__HSTRING;
__interface DELPHIINTERFACE IMapView_2__HSTRING__HSTRING;
typedef System::DelphiInterface<IMapView_2__HSTRING__HSTRING> _di_IMapView_2__HSTRING__HSTRING;
__interface DELPHIINTERFACE IMap_2__HSTRING__HSTRING;
typedef System::DelphiInterface<IMap_2__HSTRING__HSTRING> _di_IMap_2__HSTRING__HSTRING;
__interface DELPHIINTERFACE TypedEventHandler_2__IDispatcherQueueTimer__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__IDispatcherQueueTimer__IInspectable> _di_TypedEventHandler_2__IDispatcherQueueTimer__IInspectable;
__interface DELPHIINTERFACE TypedEventHandler_2__IDispatcherQueue__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__IDispatcherQueue__IInspectable> _di_TypedEventHandler_2__IDispatcherQueue__IInspectable;
__interface DELPHIINTERFACE TypedEventHandler_2__ICoreWindow__IInspectable_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__ICoreWindow__IInspectable_Delegate_Base> _di_TypedEventHandler_2__ICoreWindow__IInspectable_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__ICoreWindow__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__ICoreWindow__IInspectable> _di_TypedEventHandler_2__ICoreWindow__IInspectable;
__interface DELPHIINTERFACE TypedEventHandler_2__Activation_ISplashScreen__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__Activation_ISplashScreen__IInspectable> _di_TypedEventHandler_2__Activation_ISplashScreen__IInspectable;
__interface DELPHIINTERFACE IIterator_1__Cardinal;
typedef System::DelphiInterface<IIterator_1__Cardinal> _di_IIterator_1__Cardinal;
__interface DELPHIINTERFACE IIterable_1__Cardinal;
typedef System::DelphiInterface<IIterable_1__Cardinal> _di_IIterable_1__Cardinal;
__interface DELPHIINTERFACE IVectorView_1__Cardinal;
typedef System::DelphiInterface<IVectorView_1__Cardinal> _di_IVectorView_1__Cardinal;
__interface DELPHIINTERFACE TypedEventHandler_2__IToastNotification__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__IToastNotification__IInspectable> _di_TypedEventHandler_2__IToastNotification__IInspectable;
class DELPHICLASS TApplicationSettings_SettingsCommand;
class DELPHICLASS TApplicationSettings_WebAccountProviderCommand;
class DELPHICLASS TApplicationSettings_WebAccountCommand;
class DELPHICLASS TApplicationSettings_AccountsSettingsPane;
//-- type declarations -------------------------------------------------------
typedef _di_IReference_1__Color *PIReference_1__Color;

typedef _di_Shell_IAdaptiveCard *PShell_IAdaptiveCard;

typedef _di_IKeyValuePair_2__HSTRING__IInspectable *PIKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterator_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterable_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IMapView_2__HSTRING__IInspectable *PIMapView_2__HSTRING__IInspectable;

typedef _di_IMap_2__HSTRING__IInspectable *PIMap_2__HSTRING__IInspectable;

typedef _di_IMapChangedEventArgs_1__HSTRING *PIMapChangedEventArgs_1__HSTRING;

typedef _di_MapChangedEventHandler_2__HSTRING__IInspectable *PMapChangedEventHandler_2__HSTRING__IInspectable;

typedef _di_IObservableMap_2__HSTRING__IInspectable *PIObservableMap_2__HSTRING__IInspectable;

typedef _di_Popups_UICommandInvokedHandler *PPopups_UICommandInvokedHandler;

typedef _di_Popups_IUICommand *PPopups_IUICommand;

typedef _di_IIterator_1__Popups_IUICommand *PIIterator_1__Popups_IUICommand;

typedef _di_IIterable_1__Popups_IUICommand *PIIterable_1__Popups_IUICommand;

typedef _di_IVectorView_1__Popups_IUICommand *PIVectorView_1__Popups_IUICommand;

typedef _di_IVector_1__Popups_IUICommand *PIVector_1__Popups_IUICommand;

typedef _di_AsyncOperationCompletedHandler_1__Popups_IUICommand *PAsyncOperationCompletedHandler_1__Popups_IUICommand;

typedef _di_IAsyncOperation_1__Popups_IUICommand *PIAsyncOperation_1__Popups_IUICommand;

typedef _di_ApplicationSettings_ISettingsCommandFactory *PApplicationSettings_ISettingsCommandFactory;

typedef _di_ApplicationSettings_ISettingsCommandStatics *PApplicationSettings_ISettingsCommandStatics;

typedef _di_ApplicationSettings_IWebAccountProviderCommand *PApplicationSettings_IWebAccountProviderCommand;

typedef _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler *PApplicationSettings_WebAccountProviderCommandInvokedHandler;

typedef _di_ApplicationSettings_IWebAccountProviderCommandFactory *PApplicationSettings_IWebAccountProviderCommandFactory;

typedef _di_ApplicationSettings_IWebAccountCommand *PApplicationSettings_IWebAccountCommand;

typedef _di_ApplicationSettings_IWebAccountInvokedArgs *PApplicationSettings_IWebAccountInvokedArgs;

typedef _di_ApplicationSettings_WebAccountCommandInvokedHandler *PApplicationSettings_WebAccountCommandInvokedHandler;

typedef _di_ApplicationSettings_IWebAccountCommandFactory *PApplicationSettings_IWebAccountCommandFactory;

typedef _di_ApplicationSettings_ICredentialCommand *PApplicationSettings_ICredentialCommand;

typedef _di_ApplicationSettings_CredentialCommandCredentialDeletedHandler *PApplicationSettings_CredentialCommandCredentialDeletedHandler;

typedef _di_ApplicationSettings_IAccountsSettingsPaneEventDeferral *PApplicationSettings_IAccountsSettingsPaneEventDeferral;

typedef _di_IIterator_1__ApplicationSettings_IWebAccountProviderCommand *PIIterator_1__ApplicationSettings_IWebAccountProviderCommand;

typedef _di_IIterable_1__ApplicationSettings_IWebAccountProviderCommand *PIIterable_1__ApplicationSettings_IWebAccountProviderCommand;

typedef _di_IVectorView_1__ApplicationSettings_IWebAccountProviderCommand *PIVectorView_1__ApplicationSettings_IWebAccountProviderCommand;

typedef _di_IVector_1__ApplicationSettings_IWebAccountProviderCommand *PIVector_1__ApplicationSettings_IWebAccountProviderCommand;

typedef _di_IIterator_1__ApplicationSettings_IWebAccountCommand *PIIterator_1__ApplicationSettings_IWebAccountCommand;

typedef _di_IIterable_1__ApplicationSettings_IWebAccountCommand *PIIterable_1__ApplicationSettings_IWebAccountCommand;

typedef _di_IVectorView_1__ApplicationSettings_IWebAccountCommand *PIVectorView_1__ApplicationSettings_IWebAccountCommand;

typedef _di_IVector_1__ApplicationSettings_IWebAccountCommand *PIVector_1__ApplicationSettings_IWebAccountCommand;

typedef _di_IIterator_1__ApplicationSettings_ICredentialCommand *PIIterator_1__ApplicationSettings_ICredentialCommand;

typedef _di_IIterable_1__ApplicationSettings_ICredentialCommand *PIIterable_1__ApplicationSettings_ICredentialCommand;

typedef _di_IVectorView_1__ApplicationSettings_ICredentialCommand *PIVectorView_1__ApplicationSettings_ICredentialCommand;

typedef _di_IVector_1__ApplicationSettings_ICredentialCommand *PIVector_1__ApplicationSettings_ICredentialCommand;

typedef _di_ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs *PApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;

typedef _di_TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs *PTypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs;

typedef _di_ApplicationSettings_IAccountsSettingsPane *PApplicationSettings_IAccountsSettingsPane;

typedef _di_ApplicationSettings_IAccountsSettingsPaneStatics *PApplicationSettings_IAccountsSettingsPaneStatics;

typedef _di_ApplicationSettings_IAccountsSettingsPaneStatics2 *PApplicationSettings_IAccountsSettingsPaneStatics2;

typedef _di_AsyncOperationCompletedHandler_1__Boolean *PAsyncOperationCompletedHandler_1__Boolean;

typedef _di_IAsyncOperation_1__Boolean *PIAsyncOperation_1__Boolean;

typedef _di_EventHandler_1__IInspectable *PEventHandler_1__IInspectable;

typedef _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal *PAsyncOperationProgressHandler_2__IBuffer__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal *PIAsyncOperationWithProgress_2__IBuffer__Cardinal;

typedef _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal *PAsyncOperationProgressHandler_2__Cardinal__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__Cardinal__Cardinal *PIAsyncOperationWithProgress_2__Cardinal__Cardinal;

typedef _di_AsyncOperationCompletedHandler_1__IInspectable *PAsyncOperationCompletedHandler_1__IInspectable;

typedef _di_IAsyncOperation_1__IInspectable *PIAsyncOperation_1__IInspectable;

typedef _di_IIterator_1__HSTRING *PIIterator_1__HSTRING;

typedef _di_IIterable_1__HSTRING *PIIterable_1__HSTRING;

typedef _di_IVectorView_1__HSTRING *PIVectorView_1__HSTRING;

typedef _di_IReference_1__Single *PIReference_1__Single;

typedef _di_IKeyValuePair_2__HSTRING__HSTRING *PIKeyValuePair_2__HSTRING__HSTRING;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__HSTRING *PIIterator_1__IKeyValuePair_2__HSTRING__HSTRING;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__HSTRING *PIIterable_1__IKeyValuePair_2__HSTRING__HSTRING;

typedef _di_IMapView_2__HSTRING__HSTRING *PIMapView_2__HSTRING__HSTRING;

typedef _di_IMap_2__HSTRING__HSTRING *PIMap_2__HSTRING__HSTRING;

typedef _di_TypedEventHandler_2__IDispatcherQueueTimer__IInspectable *PTypedEventHandler_2__IDispatcherQueueTimer__IInspectable;

typedef _di_TypedEventHandler_2__IDispatcherQueue__IInspectable *PTypedEventHandler_2__IDispatcherQueue__IInspectable;

typedef _di_TypedEventHandler_2__ICoreWindow__IInspectable *PTypedEventHandler_2__ICoreWindow__IInspectable;

typedef _di_TypedEventHandler_2__Activation_ISplashScreen__IInspectable *PTypedEventHandler_2__Activation_ISplashScreen__IInspectable;

typedef _di_IIterator_1__Cardinal *PIIterator_1__Cardinal;

typedef _di_IIterable_1__Cardinal *PIIterable_1__Cardinal;

typedef _di_IVectorView_1__Cardinal *PIVectorView_1__Cardinal;

typedef _di_TypedEventHandler_2__IToastNotification__IInspectable *PTypedEventHandler_2__IToastNotification__IInspectable;

__interface  INTERFACE_UUID("{455ACF7B-8F11-5BB9-93BE-7A214CD5A134}") IReference_1__Color  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(Winapi::Commontypes::Color &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_Value() { Winapi::Commontypes::Color __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{72D0568C-A274-41CD-82A8-989D40B9B05E}") Shell_IAdaptiveCard  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ToJson(HSTRING &__ToJson_result) = 0 ;
};

__interface  INTERFACE_UUID("{09335560-6C6B-5A26-9348-97B781132B20}") IKeyValuePair_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(Winapi::Winrt::_di_IInspectable &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Value() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{5DB5FA32-707C-5849-A06B-91C8EB9D10E8}") IIterator_1__IKeyValuePair_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__IInspectable &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__IInspectable items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__IInspectable _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__IInspectable __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__IInspectable Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{FE2F3D47-5D47-5499-8374-430C7CDA0204}") IIterable_1__IKeyValuePair_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{BB78502A-F79D-54FA-92C9-90C5039FDF7E}") IMapView_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, Winapi::Winrt::_di_IInspectable &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall Split(/* out */ _di_IMapView_2__HSTRING__IInspectable &first, /* out */ _di_IMapView_2__HSTRING__IInspectable &second) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{1B0D3570-0877-5EC2-8A2C-3B9539506ACA}") IMap_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, Winapi::Winrt::_di_IInspectable &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IMapView_2__HSTRING__IInspectable &__GetView_result) = 0 ;
	virtual HRESULT __safecall Insert(HSTRING key, Winapi::Winrt::_di_IInspectable value, bool &__Insert_result) = 0 ;
	virtual HRESULT __safecall Remove(HSTRING key) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{60141EFB-F2F9-5377-96FD-F8C60D9558B5}") IMapChangedEventArgs_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CollectionChange(Winapi::Commontypes::CollectionChange &__get_CollectionChange_result) = 0 ;
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::CollectionChange _scw_get_CollectionChange() { Winapi::Commontypes::CollectionChange __r; HRESULT __hr = get_CollectionChange(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::CollectionChange CollectionChange = {read=_scw_get_CollectionChange};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
};

__interface  INTERFACE_UUID("{24F981E5-DDCA-538D-AADA-A59906084CF1}") MapChangedEventHandler_2__HSTRING__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IObservableMap_2__HSTRING__IInspectable sender, _di_IMapChangedEventArgs_1__HSTRING event) = 0 ;
};

__interface  INTERFACE_UUID("{236AAC9D-FB12-5C4D-A41C-9E445FB4D7EC}") IObservableMap_2__HSTRING__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_MapChanged(_di_MapChangedEventHandler_2__HSTRING__IInspectable vhnd, Winapi::Commontypes::EventRegistrationToken &__add_MapChanged_result) = 0 ;
	virtual HRESULT __safecall remove_MapChanged(Winapi::Commontypes::EventRegistrationToken token) = 0 ;
};

__interface  INTERFACE_UUID("{DAF77A4F-C27A-4298-9AC6-2922C45E7DA6}") Popups_UICommandInvokedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_Popups_IUICommand command) = 0 ;
};

__interface  INTERFACE_UUID("{4FF93A75-4145-47FF-AC7F-DFF1C1FA5B0F}") Popups_IUICommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Label(HSTRING &__get_Label_result) = 0 ;
	virtual HRESULT __safecall put_Label(HSTRING value) = 0 ;
	virtual HRESULT __safecall get_Invoked(_di_Popups_UICommandInvokedHandler &__get_Invoked_result) = 0 ;
	virtual HRESULT __safecall put_Invoked(_di_Popups_UICommandInvokedHandler value) = 0 ;
	virtual HRESULT __safecall get_Id(Winapi::Winrt::_di_IInspectable &__get_Id_result) = 0 ;
	virtual HRESULT __safecall put_Id(Winapi::Winrt::_di_IInspectable value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Winrt::_di_IInspectable _scw_get_Id() { Winapi::Winrt::_di_IInspectable __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Winrt::_di_IInspectable Id = {read=_scw_get_Id, write=put_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Popups_UICommandInvokedHandler _scw_get_Invoked() { _di_Popups_UICommandInvokedHandler __r; HRESULT __hr = get_Invoked(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Popups_UICommandInvokedHandler Invoked = {read=_scw_get_Invoked, write=put_Invoked};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Label() { HSTRING __r; HRESULT __hr = get_Label(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Label = {read=_scw_get_Label, write=put_Label};
};

__interface  INTERFACE_UUID("{2F071C24-4A58-5A00-A294-C7162E98C2A0}") IIterator_1__Popups_IUICommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{F45DB3D3-7299-57CE-A73E-297CF0AF3083}") IIterator_1__Popups_IUICommand  : public IIterator_1__Popups_IUICommand_Base 
{
	virtual HRESULT __safecall get_Current(_di_Popups_IUICommand &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PPopups_IUICommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Popups_IUICommand _scw_get_Current() { _di_Popups_IUICommand __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Popups_IUICommand Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{6308E7E8-CB85-5339-A3E9-9A7500D19C68}") IIterable_1__Popups_IUICommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E63DE42B-53C3-5E07-90D3-98172D545412}") IIterable_1__Popups_IUICommand  : public IIterable_1__Popups_IUICommand_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Popups_IUICommand &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{ED1165E6-F377-5B00-8172-93C1BD04DEB4}") IVectorView_1__Popups_IUICommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Popups_IUICommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Popups_IUICommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PPopups_IUICommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{105139A1-DCB8-5F65-97EF-CB1BF0B75F9D}") IVector_1__Popups_IUICommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Popups_IUICommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__Popups_IUICommand &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Popups_IUICommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_Popups_IUICommand value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_Popups_IUICommand value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_Popups_IUICommand value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PPopups_IUICommand items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PPopups_IUICommand items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{DD33FD5B-A24D-5A44-91FE-DD6441770103}") AsyncOperationCompletedHandler_1__Popups_IUICommand_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{DD33FD5B-A24D-5A44-91FE-DD6441770103}") AsyncOperationCompletedHandler_1__Popups_IUICommand  : public AsyncOperationCompletedHandler_1__Popups_IUICommand_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Popups_IUICommand asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B8770535-6A4B-52B1-B578-F3CDC5007A1F}") IAsyncOperation_1__Popups_IUICommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B8770535-6A4B-52B1-B578-F3CDC5007A1F}") IAsyncOperation_1__Popups_IUICommand  : public IAsyncOperation_1__Popups_IUICommand_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Popups_IUICommand handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Popups_IUICommand &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_Popups_IUICommand &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Popups_IUICommand _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Popups_IUICommand __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Popups_IUICommand Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{68E15B33-1C83-433A-AA5A-CEEEA5BD4764}") ApplicationSettings_ISettingsCommandFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateSettingsCommand(Winapi::Winrt::_di_IInspectable settingsCommandId, HSTRING label, _di_Popups_UICommandInvokedHandler handler, _di_Popups_IUICommand &__CreateSettingsCommand_result) = 0 ;
};

__interface  INTERFACE_UUID("{749AE954-2F69-4B17-8ABA-D05CE5778E46}") ApplicationSettings_ISettingsCommandStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AccountsCommand(_di_Popups_IUICommand &__get_AccountsCommand_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Popups_IUICommand _scw_get_AccountsCommand() { _di_Popups_IUICommand __r; HRESULT __hr = get_AccountsCommand(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Popups_IUICommand AccountsCommand = {read=_scw_get_AccountsCommand};
};

__interface  INTERFACE_UUID("{D69BDD9A-A0A6-4E9B-88DC-C71E757A3501}") ApplicationSettings_IWebAccountProviderCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_WebAccountProvider(Winapi::Security::Credentials::_di_IWebAccountProvider &__get_WebAccountProvider_result) = 0 ;
	virtual HRESULT __safecall get_Invoked(_di_ApplicationSettings_WebAccountProviderCommandInvokedHandler &__get_Invoked_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler _scw_get_Invoked() { _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler __r; HRESULT __hr = get_Invoked(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler Invoked = {read=_scw_get_Invoked};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IWebAccountProvider _scw_get_WebAccountProvider() { Winapi::Security::Credentials::_di_IWebAccountProvider __r; HRESULT __hr = get_WebAccountProvider(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IWebAccountProvider WebAccountProvider = {read=_scw_get_WebAccountProvider};
};

__interface  INTERFACE_UUID("{B7DE5527-4C8F-42DD-84DA-5EC493ABDB9A}") ApplicationSettings_WebAccountProviderCommandInvokedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ApplicationSettings_IWebAccountProviderCommand command) = 0 ;
};

__interface  INTERFACE_UUID("{D5658A1B-B176-4776-8469-A9D3FF0B3F59}") ApplicationSettings_IWebAccountProviderCommandFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWebAccountProviderCommand(Winapi::Security::Credentials::_di_IWebAccountProvider webAccountProvider, _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler invoked, _di_ApplicationSettings_IWebAccountProviderCommand &__CreateWebAccountProviderCommand_result) = 0 ;
};

__interface  INTERFACE_UUID("{CAA39398-9CFA-4246-B0C4-A913A3896541}") ApplicationSettings_IWebAccountCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_WebAccount(Winapi::Security::Credentials::_di_IWebAccount &__get_WebAccount_result) = 0 ;
	virtual HRESULT __safecall get_Invoked(_di_ApplicationSettings_WebAccountCommandInvokedHandler &__get_Invoked_result) = 0 ;
	virtual HRESULT __safecall get_Actions(Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions &__get_Actions_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions _scw_get_Actions() { Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions __r; HRESULT __hr = get_Actions(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions Actions = {read=_scw_get_Actions};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_WebAccountCommandInvokedHandler _scw_get_Invoked() { _di_ApplicationSettings_WebAccountCommandInvokedHandler __r; HRESULT __hr = get_Invoked(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_WebAccountCommandInvokedHandler Invoked = {read=_scw_get_Invoked};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IWebAccount _scw_get_WebAccount() { Winapi::Security::Credentials::_di_IWebAccount __r; HRESULT __hr = get_WebAccount(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IWebAccount WebAccount = {read=_scw_get_WebAccount};
};

__interface  INTERFACE_UUID("{E7ABCC40-A1D8-4C5D-9A7F-1D34B2F90AD2}") ApplicationSettings_IWebAccountInvokedArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Action(Winapi::Commontypes::ApplicationSettings_WebAccountAction &__get_Action_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::ApplicationSettings_WebAccountAction _scw_get_Action() { Winapi::Commontypes::ApplicationSettings_WebAccountAction __r; HRESULT __hr = get_Action(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::ApplicationSettings_WebAccountAction Action = {read=_scw_get_Action};
};

__interface  INTERFACE_UUID("{1EE6E459-1705-4A9A-B599-A0C3D6921973}") ApplicationSettings_WebAccountCommandInvokedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ApplicationSettings_IWebAccountCommand command, _di_ApplicationSettings_IWebAccountInvokedArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{BFA6CDFF-2F2D-42F5-81DE-1D56BAFC496D}") ApplicationSettings_IWebAccountCommandFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWebAccountCommand(Winapi::Security::Credentials::_di_IWebAccount webAccount, _di_ApplicationSettings_WebAccountCommandInvokedHandler invoked, Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions actions, _di_ApplicationSettings_IWebAccountCommand &__CreateWebAccountCommand_result) = 0 ;
};

__interface  INTERFACE_UUID("{A5F665E6-6143-4A7A-A971-B017BA978CE2}") ApplicationSettings_ICredentialCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PasswordCredential(Winapi::Security::Credentials::_di_IPasswordCredential &__get_PasswordCredential_result) = 0 ;
	virtual HRESULT __safecall get_CredentialDeleted(_di_ApplicationSettings_CredentialCommandCredentialDeletedHandler &__get_CredentialDeleted_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_CredentialCommandCredentialDeletedHandler _scw_get_CredentialDeleted() { _di_ApplicationSettings_CredentialCommandCredentialDeletedHandler __r; HRESULT __hr = get_CredentialDeleted(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_CredentialCommandCredentialDeletedHandler CredentialDeleted = {read=_scw_get_CredentialDeleted};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Security::Credentials::_di_IPasswordCredential _scw_get_PasswordCredential() { Winapi::Security::Credentials::_di_IPasswordCredential __r; HRESULT __hr = get_PasswordCredential(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Security::Credentials::_di_IPasswordCredential PasswordCredential = {read=_scw_get_PasswordCredential};
};

__interface  INTERFACE_UUID("{61C0E185-0977-4678-B4E2-98727AFBEED9}") ApplicationSettings_CredentialCommandCredentialDeletedHandler  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_ApplicationSettings_ICredentialCommand command) = 0 ;
};

__interface  INTERFACE_UUID("{CBF25D3F-E5BA-40EF-93DA-65E096E5FB04}") ApplicationSettings_IAccountsSettingsPaneEventDeferral  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Complete() = 0 ;
};

__interface  INTERFACE_UUID("{82D7CD74-8E33-5F06-92FC-915138AACBDE}") IIterator_1__ApplicationSettings_IWebAccountProviderCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{0589F3D7-4C7B-5DCF-8B69-521E998840E3}") IIterator_1__ApplicationSettings_IWebAccountProviderCommand  : public IIterator_1__ApplicationSettings_IWebAccountProviderCommand_Base 
{
	virtual HRESULT __safecall get_Current(_di_ApplicationSettings_IWebAccountProviderCommand &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PApplicationSettings_IWebAccountProviderCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_IWebAccountProviderCommand _scw_get_Current() { _di_ApplicationSettings_IWebAccountProviderCommand __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_IWebAccountProviderCommand Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{15165367-2E93-59A6-B5C7-16D3B58FD2E7}") IIterable_1__ApplicationSettings_IWebAccountProviderCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5D3ADB92-B711-52EB-9CEE-0EF716E42707}") IIterable_1__ApplicationSettings_IWebAccountProviderCommand  : public IIterable_1__ApplicationSettings_IWebAccountProviderCommand_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ApplicationSettings_IWebAccountProviderCommand &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{6D1C614A-F7CB-5051-8AF9-79B46848FE39}") IVectorView_1__ApplicationSettings_IWebAccountProviderCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_IWebAccountProviderCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_IWebAccountProviderCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_IWebAccountProviderCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{5E4F3A00-0619-55EB-BDC5-B5AC43E5E153}") IVector_1__ApplicationSettings_IWebAccountProviderCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_IWebAccountProviderCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ApplicationSettings_IWebAccountProviderCommand &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_IWebAccountProviderCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_ApplicationSettings_IWebAccountProviderCommand value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_ApplicationSettings_IWebAccountProviderCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_ApplicationSettings_IWebAccountProviderCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_IWebAccountProviderCommand items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PApplicationSettings_IWebAccountProviderCommand items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{8CBB62B6-BD9C-5486-9D14-9CC4627B32D4}") IIterator_1__ApplicationSettings_IWebAccountCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E620D41D-D00D-54D0-B860-4A421577D0B1}") IIterator_1__ApplicationSettings_IWebAccountCommand  : public IIterator_1__ApplicationSettings_IWebAccountCommand_Base 
{
	virtual HRESULT __safecall get_Current(_di_ApplicationSettings_IWebAccountCommand &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PApplicationSettings_IWebAccountCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_IWebAccountCommand _scw_get_Current() { _di_ApplicationSettings_IWebAccountCommand __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_IWebAccountCommand Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{BD0D999C-B2BA-51B2-BCC0-D4A5CD821555}") IIterable_1__ApplicationSettings_IWebAccountCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{3629C358-6F4E-58FD-80EE-0E5F1F4082E8}") IIterable_1__ApplicationSettings_IWebAccountCommand  : public IIterable_1__ApplicationSettings_IWebAccountCommand_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ApplicationSettings_IWebAccountCommand &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{B927432C-66BF-5A20-ADFE-25DB09CA2B30}") IVectorView_1__ApplicationSettings_IWebAccountCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_IWebAccountCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_IWebAccountCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_IWebAccountCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{58120E09-4156-5FAB-B9BB-8909C18470EE}") IVector_1__ApplicationSettings_IWebAccountCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_IWebAccountCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ApplicationSettings_IWebAccountCommand &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_IWebAccountCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_ApplicationSettings_IWebAccountCommand value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_ApplicationSettings_IWebAccountCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_ApplicationSettings_IWebAccountCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_IWebAccountCommand items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PApplicationSettings_IWebAccountCommand items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{9F1177F1-85BB-5CD0-9B08-A0B47A764C75}") IIterator_1__ApplicationSettings_ICredentialCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B8A25360-140B-5563-8918-58B6E53E057A}") IIterator_1__ApplicationSettings_ICredentialCommand  : public IIterator_1__ApplicationSettings_ICredentialCommand_Base 
{
	virtual HRESULT __safecall get_Current(_di_ApplicationSettings_ICredentialCommand &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PApplicationSettings_ICredentialCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_ApplicationSettings_ICredentialCommand _scw_get_Current() { _di_ApplicationSettings_ICredentialCommand __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_ApplicationSettings_ICredentialCommand Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{883ED18D-4DBB-58F2-8FD2-E4B018509553}") IIterable_1__ApplicationSettings_ICredentialCommand_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E36B7DB3-5D4F-501A-AAD3-062A4D8927A5}") IIterable_1__ApplicationSettings_ICredentialCommand  : public IIterable_1__ApplicationSettings_ICredentialCommand_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__ApplicationSettings_ICredentialCommand &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{CFE85330-C245-5639-B839-4E548E5E6B17}") IVectorView_1__ApplicationSettings_ICredentialCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_ICredentialCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_ICredentialCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_ICredentialCommand items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{458D5549-557E-5756-B5CA-13209BA7D91E}") IVector_1__ApplicationSettings_ICredentialCommand  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_ApplicationSettings_ICredentialCommand &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__ApplicationSettings_ICredentialCommand &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_ApplicationSettings_ICredentialCommand value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_ApplicationSettings_ICredentialCommand value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_ApplicationSettings_ICredentialCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_ApplicationSettings_ICredentialCommand value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PApplicationSettings_ICredentialCommand items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PApplicationSettings_ICredentialCommand items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{3B68C099-DB19-45D0-9ABF-95D3773C9330}") ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_WebAccountProviderCommands(_di_IVector_1__ApplicationSettings_IWebAccountProviderCommand &__get_WebAccountProviderCommands_result) = 0 ;
	virtual HRESULT __safecall get_WebAccountCommands(_di_IVector_1__ApplicationSettings_IWebAccountCommand &__get_WebAccountCommands_result) = 0 ;
	virtual HRESULT __safecall get_CredentialCommands(_di_IVector_1__ApplicationSettings_ICredentialCommand &__get_CredentialCommands_result) = 0 ;
	virtual HRESULT __safecall get_Commands(_di_IVector_1__Popups_IUICommand &__get_Commands_result) = 0 ;
	virtual HRESULT __safecall get_HeaderText(HSTRING &__get_HeaderText_result) = 0 ;
	virtual HRESULT __safecall put_HeaderText(HSTRING value) = 0 ;
	virtual HRESULT __safecall GetDeferral(_di_ApplicationSettings_IAccountsSettingsPaneEventDeferral &__GetDeferral_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__Popups_IUICommand _scw_get_Commands() { _di_IVector_1__Popups_IUICommand __r; HRESULT __hr = get_Commands(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__Popups_IUICommand Commands = {read=_scw_get_Commands};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__ApplicationSettings_ICredentialCommand _scw_get_CredentialCommands() { _di_IVector_1__ApplicationSettings_ICredentialCommand __r; HRESULT __hr = get_CredentialCommands(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__ApplicationSettings_ICredentialCommand CredentialCommands = {read=_scw_get_CredentialCommands};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_HeaderText() { HSTRING __r; HRESULT __hr = get_HeaderText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING HeaderText = {read=_scw_get_HeaderText, write=put_HeaderText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__ApplicationSettings_IWebAccountCommand _scw_get_WebAccountCommands() { _di_IVector_1__ApplicationSettings_IWebAccountCommand __r; HRESULT __hr = get_WebAccountCommands(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__ApplicationSettings_IWebAccountCommand WebAccountCommands = {read=_scw_get_WebAccountCommands};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__ApplicationSettings_IWebAccountProviderCommand _scw_get_WebAccountProviderCommands() { _di_IVector_1__ApplicationSettings_IWebAccountProviderCommand __r; HRESULT __hr = get_WebAccountProviderCommands(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__ApplicationSettings_IWebAccountProviderCommand WebAccountProviderCommands = {read=_scw_get_WebAccountProviderCommands};
};

__interface  INTERFACE_UUID("{69B8847E-7D72-5A15-BC1C-4CA39C93B162}") TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F355D7FC-61F8-5271-A250-80C756A1DE3A}") TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs  : public TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_ApplicationSettings_IAccountsSettingsPane sender, _di_ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{81EA942C-4F09-4406-A538-838D9B14B7E6}") ApplicationSettings_IAccountsSettingsPane  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_AccountCommandsRequested(_di_TypedEventHandler_2__ApplicationSettings_IAccountsSettingsPane__ApplicationSettings_IAccountsSettingsPaneCommandsRequestedEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_AccountCommandsRequested_result) = 0 ;
	virtual HRESULT __safecall remove_AccountCommandsRequested(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
};

__interface  INTERFACE_UUID("{561F8B60-B0EC-4150-A8DC-208EE44B068A}") ApplicationSettings_IAccountsSettingsPaneStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetForCurrentView(_di_ApplicationSettings_IAccountsSettingsPane &__GetForCurrentView_result) = 0 ;
	virtual HRESULT __safecall Show() = 0 ;
};

__interface  INTERFACE_UUID("{D21DF7C2-CE0D-484F-B8E8-E823C215765E}") ApplicationSettings_IAccountsSettingsPaneStatics2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ShowManageAccountsAsync(Winapi::Commontypes::_di_IAsyncAction &__ShowManageAccountsAsync_result) = 0 ;
	virtual HRESULT __safecall ShowAddAccountAsync(Winapi::Commontypes::_di_IAsyncAction &__ShowAddAccountAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{C1D3D1A2-AE17-5A5F-B5A2-BDCC8844889A}") AsyncOperationCompletedHandler_1__Boolean  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Boolean asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{CDB5EFB3-5788-509D-9BE1-71CCB8A3362A}") IAsyncOperation_1__Boolean  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Boolean handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Boolean &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(bool &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Boolean _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Boolean __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Boolean Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{C50898F6-C536-5F47-8583-8B2C2438A13B}") EventHandler_1__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Winrt::_di_IInspectable sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{BF666554-7605-5D9A-B14E-18D8C8472AFE}") AsyncOperationProgressHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, unsigned progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{06386A7A-E009-5B0B-AB68-A8E48B516647}") AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__IBuffer__Cardinal asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{D26B2819-897F-5C7D-84D6-56D796561431}") IAsyncOperationWithProgress_2__IBuffer__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__IBuffer__Cardinal &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IBuffer &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{EA0FE405-D432-5AC7-9EF8-5A65E1F97D7E}") AsyncOperationProgressHandler_2__Cardinal__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Cardinal__Cardinal asyncInfo, unsigned progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{1E466DC5-840F-54F9-B877-5E3A9F4B6C74}") AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Cardinal__Cardinal asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{ECCB574A-C684-5572-A679-6B0842CFB57F}") IAsyncOperationWithProgress_2__Cardinal__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__Cardinal__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__Cardinal__Cardinal &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(unsigned &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{3F08262E-A2E1-5134-9297-E9211F481A2D}") AsyncOperationCompletedHandler_1__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IInspectable asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{ABF53C57-EE50-5342-B52A-26E3B8CC024F}") IAsyncOperation_1__IInspectable  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IInspectable handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IInspectable &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Winrt::_di_IInspectable &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IInspectable _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IInspectable __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IInspectable Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{8C304EBB-6615-50A4-8829-879ECD443236}") IIterator_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(HSTRING &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Current() { HSTRING __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E2FCC7C1-3BFC-5A0B-B2B0-72E769D1CB7E}") IIterable_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__HSTRING &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2F13C006-A03A-5F69-B090-75A43E33423E}") IVectorView_1__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, HSTRING &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(HSTRING value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, Winapi::Winrt::PHSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{719CC2BA-3E76-5DEF-9F1A-38D85A145EA8}") IReference_1__Single  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Value(float &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Value() { float __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{60310303-49C5-52E6-ABC6-A9B36ECCC716}") IKeyValuePair_2__HSTRING__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Key(HSTRING &__get_Key_result) = 0 ;
	virtual HRESULT __safecall get_Value(HSTRING &__get_Value_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Key() { HSTRING __r; HRESULT __hr = get_Key(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Key = {read=_scw_get_Key};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Value() { HSTRING __r; HRESULT __hr = get_Value(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Value = {read=_scw_get_Value};
};

__interface  INTERFACE_UUID("{05EB86F1-7140-5517-B88D-CBAEBE57E6B1}") IIterator_1__IKeyValuePair_2__HSTRING__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(_di_IKeyValuePair_2__HSTRING__HSTRING &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIKeyValuePair_2__HSTRING__HSTRING items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyValuePair_2__HSTRING__HSTRING _scw_get_Current() { _di_IKeyValuePair_2__HSTRING__HSTRING __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyValuePair_2__HSTRING__HSTRING Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E9BDAAF0-CBF6-5C72-BE90-29CBF3A1319B}") IIterable_1__IKeyValuePair_2__HSTRING__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IKeyValuePair_2__HSTRING__HSTRING &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{AC7F26F2-FEB7-5B2A-8AC4-345BC62CAEDE}") IMapView_2__HSTRING__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, HSTRING &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall Split(/* out */ _di_IMapView_2__HSTRING__HSTRING &first, /* out */ _di_IMapView_2__HSTRING__HSTRING &second) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{F6D1F700-49C2-52AE-8154-826F9908773C}") IMap_2__HSTRING__HSTRING  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Lookup(HSTRING key, HSTRING &__Lookup_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall HasKey(HSTRING key, bool &__HasKey_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IMapView_2__HSTRING__HSTRING &__GetView_result) = 0 ;
	virtual HRESULT __safecall Insert(HSTRING key, HSTRING value, bool &__Insert_result) = 0 ;
	virtual HRESULT __safecall Remove(HSTRING key) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{8A13AE56-7643-5F25-A347-5C9F548273DC}") TypedEventHandler_2__IDispatcherQueueTimer__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IDispatcherQueueTimer sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{1ECC7D76-D5F1-5514-8DA3-343E7A82F842}") TypedEventHandler_2__IDispatcherQueue__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IDispatcherQueue sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{6368AE3D-52D4-5290-B936-717A9ACF5BEA}") TypedEventHandler_2__ICoreWindow__IInspectable_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B36B7AF8-9A47-5035-B15C-4B124BDFC849}") TypedEventHandler_2__ICoreWindow__IInspectable  : public TypedEventHandler_2__ICoreWindow__IInspectable_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_ICoreWindow sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{359B8887-2FA6-5405-A4AF-642C9FDACC93}") TypedEventHandler_2__Activation_ISplashScreen__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_Activation_ISplashScreen sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

__interface  INTERFACE_UUID("{F06A2739-9443-5EF0-B284-DC5AFF3E7D10}") IIterator_1__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Current(unsigned &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, System::PCardinal items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Current() { unsigned __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{421D4B91-B13B-5F37-AE54-B5249BD80539}") IIterable_1__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Cardinal &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{E5CE1A07-8D33-5007-BA64-7D2508CCF85C}") IVectorView_1__Cardinal  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, unsigned &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(unsigned value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, System::PCardinal items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{93621AAC-6E87-5F7A-AA83-927B2D905518}") TypedEventHandler_2__IToastNotification__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Commontypes::_di_IToastNotification sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TApplicationSettings_SettingsCommand : public System::Win::Winrt::TWinRTGenericImportFS__2<_di_ApplicationSettings_ISettingsCommandFactory,_di_ApplicationSettings_ISettingsCommandStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportFS__2<_di_ApplicationSettings_ISettingsCommandFactory,_di_ApplicationSettings_ISettingsCommandStatics> inherited;
	
public:
	static _di_Popups_IUICommand __fastcall get_AccountsCommand();
	/* static */ __property _di_Popups_IUICommand AccountsCommand = {read=get_AccountsCommand};
	static _di_Popups_IUICommand __fastcall CreateSettingsCommand(Winapi::Winrt::_di_IInspectable settingsCommandId, HSTRING label, _di_Popups_UICommandInvokedHandler handler);
public:
	/* TObject.Create */ inline __fastcall TApplicationSettings_SettingsCommand() : System::Win::Winrt::TWinRTGenericImportFS__2<_di_ApplicationSettings_ISettingsCommandFactory,_di_ApplicationSettings_ISettingsCommandStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TApplicationSettings_SettingsCommand() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TApplicationSettings_WebAccountProviderCommand : public System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountProviderCommandFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountProviderCommandFactory> inherited;
	
public:
	static _di_ApplicationSettings_IWebAccountProviderCommand __fastcall CreateWebAccountProviderCommand(Winapi::Security::Credentials::_di_IWebAccountProvider webAccountProvider, _di_ApplicationSettings_WebAccountProviderCommandInvokedHandler invoked);
public:
	/* TObject.Create */ inline __fastcall TApplicationSettings_WebAccountProviderCommand() : System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountProviderCommandFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TApplicationSettings_WebAccountProviderCommand() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TApplicationSettings_WebAccountCommand : public System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountCommandFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountCommandFactory> inherited;
	
public:
	static _di_ApplicationSettings_IWebAccountCommand __fastcall CreateWebAccountCommand(Winapi::Security::Credentials::_di_IWebAccount webAccount, _di_ApplicationSettings_WebAccountCommandInvokedHandler invoked, Winapi::Commontypes::ApplicationSettings_SupportedWebAccountActions actions);
public:
	/* TObject.Create */ inline __fastcall TApplicationSettings_WebAccountCommand() : System::Win::Winrt::TWinRTGenericImportF__1<_di_ApplicationSettings_IWebAccountCommandFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TApplicationSettings_WebAccountCommand() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TApplicationSettings_AccountsSettingsPane : public System::Win::Winrt::TWinRTGenericImportS2__2<_di_ApplicationSettings_IAccountsSettingsPaneStatics,_di_ApplicationSettings_IAccountsSettingsPaneStatics2>
{
	typedef System::Win::Winrt::TWinRTGenericImportS2__2<_di_ApplicationSettings_IAccountsSettingsPaneStatics,_di_ApplicationSettings_IAccountsSettingsPaneStatics2> inherited;
	
public:
	static _di_ApplicationSettings_IAccountsSettingsPane __fastcall GetForCurrentView();
	static void __fastcall Show();
	static Winapi::Commontypes::_di_IAsyncAction __fastcall ShowManageAccountsAsync();
	static Winapi::Commontypes::_di_IAsyncAction __fastcall ShowAddAccountAsync();
public:
	/* TObject.Create */ inline __fastcall TApplicationSettings_AccountsSettingsPane() : System::Win::Winrt::TWinRTGenericImportS2__2<_di_ApplicationSettings_IAccountsSettingsPaneStatics,_di_ApplicationSettings_IAccountsSettingsPaneStatics2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TApplicationSettings_AccountsSettingsPane() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_UiHPP
