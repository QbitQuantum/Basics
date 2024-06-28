// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Management.pas' rev: 34.00 (Windows)

#ifndef Winapi_ManagementHPP
#define Winapi_ManagementHPP

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
#include <Winapi.ApplicationModel.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Foundation.hpp>
#include <Winapi.Storage.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Management
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE Deployment_IPackageVolume;
typedef System::DelphiInterface<Deployment_IPackageVolume> _di_Deployment_IPackageVolume;
__interface DELPHIINTERFACE Deployment_IDeploymentResult;
typedef System::DelphiInterface<Deployment_IDeploymentResult> _di_Deployment_IDeploymentResult;
__interface DELPHIINTERFACE Deployment_IPackageUserInformation;
typedef System::DelphiInterface<Deployment_IPackageUserInformation> _di_Deployment_IPackageUserInformation;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base> _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
typedef System::DelphiInterface<AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress> _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base> _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
typedef System::DelphiInterface<AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress> _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Base;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Base> _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Base;
__interface DELPHIINTERFACE IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
typedef System::DelphiInterface<IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress> _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;
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
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Boolean;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Boolean> _di_AsyncOperationCompletedHandler_1__Boolean;
__interface DELPHIINTERFACE IAsyncOperation_1__Boolean;
typedef System::DelphiInterface<IAsyncOperation_1__Boolean> _di_IAsyncOperation_1__Boolean;
__interface DELPHIINTERFACE IIterator_1__Deployment_IPackageUserInformation_Base;
typedef System::DelphiInterface<IIterator_1__Deployment_IPackageUserInformation_Base> _di_IIterator_1__Deployment_IPackageUserInformation_Base;
__interface DELPHIINTERFACE IIterator_1__Deployment_IPackageUserInformation;
typedef System::DelphiInterface<IIterator_1__Deployment_IPackageUserInformation> _di_IIterator_1__Deployment_IPackageUserInformation;
__interface DELPHIINTERFACE IIterable_1__Deployment_IPackageUserInformation_Base;
typedef System::DelphiInterface<IIterable_1__Deployment_IPackageUserInformation_Base> _di_IIterable_1__Deployment_IPackageUserInformation_Base;
__interface DELPHIINTERFACE IIterable_1__Deployment_IPackageUserInformation;
typedef System::DelphiInterface<IIterable_1__Deployment_IPackageUserInformation> _di_IIterable_1__Deployment_IPackageUserInformation;
__interface DELPHIINTERFACE Deployment_IPackageManager;
typedef System::DelphiInterface<Deployment_IPackageManager> _di_Deployment_IPackageManager;
__interface DELPHIINTERFACE IIterator_1__HSTRING;
typedef System::DelphiInterface<IIterator_1__HSTRING> _di_IIterator_1__HSTRING;
__interface DELPHIINTERFACE IIterable_1__HSTRING;
typedef System::DelphiInterface<IIterable_1__HSTRING> _di_IIterable_1__HSTRING;
__interface DELPHIINTERFACE Deployment_IPackageManager2;
typedef System::DelphiInterface<Deployment_IPackageManager2> _di_Deployment_IPackageManager2;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Deployment_IPackageVolume_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Deployment_IPackageVolume_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Deployment_IPackageVolume> _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE IAsyncOperation_1__Deployment_IPackageVolume_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Deployment_IPackageVolume_Base> _di_IAsyncOperation_1__Deployment_IPackageVolume_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<IAsyncOperation_1__Deployment_IPackageVolume> _di_IAsyncOperation_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE IIterator_1__Deployment_IPackageVolume_Base;
typedef System::DelphiInterface<IIterator_1__Deployment_IPackageVolume_Base> _di_IIterator_1__Deployment_IPackageVolume_Base;
__interface DELPHIINTERFACE IIterator_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<IIterator_1__Deployment_IPackageVolume> _di_IIterator_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE IIterable_1__Deployment_IPackageVolume_Base;
typedef System::DelphiInterface<IIterable_1__Deployment_IPackageVolume_Base> _di_IIterable_1__Deployment_IPackageVolume_Base;
__interface DELPHIINTERFACE IIterable_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<IIterable_1__Deployment_IPackageVolume> _di_IIterable_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE Deployment_IPackageManager3;
typedef System::DelphiInterface<Deployment_IPackageManager3> _di_Deployment_IPackageManager3;
__interface DELPHIINTERFACE IVectorView_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<IVectorView_1__Deployment_IPackageVolume> _di_IVectorView_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume> _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume_Base> _di_IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume> _di_IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume;
__interface DELPHIINTERFACE Deployment_IPackageManager4;
typedef System::DelphiInterface<Deployment_IPackageManager4> _di_Deployment_IPackageManager4;
__interface DELPHIINTERFACE Deployment_IPackageManagerDebugSettings;
typedef System::DelphiInterface<Deployment_IPackageManagerDebugSettings> _di_Deployment_IPackageManagerDebugSettings;
__interface DELPHIINTERFACE Deployment_IPackageManager5;
typedef System::DelphiInterface<Deployment_IPackageManager5> _di_Deployment_IPackageManager5;
__interface DELPHIINTERFACE Deployment_IPackageManager6;
typedef System::DelphiInterface<Deployment_IPackageManager6> _di_Deployment_IPackageManager6;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UInt64_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UInt64_Delegate_Base> _di_AsyncOperationCompletedHandler_1__UInt64_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UInt64;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UInt64> _di_AsyncOperationCompletedHandler_1__UInt64;
__interface DELPHIINTERFACE IAsyncOperation_1__UInt64_Base;
typedef System::DelphiInterface<IAsyncOperation_1__UInt64_Base> _di_IAsyncOperation_1__UInt64_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__UInt64;
typedef System::DelphiInterface<IAsyncOperation_1__UInt64> _di_IAsyncOperation_1__UInt64;
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
__interface DELPHIINTERFACE TypedEventHandler_2__IApplicationData__IInspectable;
typedef System::DelphiInterface<TypedEventHandler_2__IApplicationData__IInspectable> _di_TypedEventHandler_2__IApplicationData__IInspectable;
__interface DELPHIINTERFACE IVectorView_1__HSTRING;
typedef System::DelphiInterface<IVectorView_1__HSTRING> _di_IVectorView_1__HSTRING;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IInspectable;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IInspectable> _di_AsyncOperationCompletedHandler_1__IInspectable;
__interface DELPHIINTERFACE IAsyncOperation_1__IInspectable;
typedef System::DelphiInterface<IAsyncOperation_1__IInspectable> _di_IAsyncOperation_1__IInspectable;
__interface DELPHIINTERFACE Deployment_Preview_IInstalledClassicAppInfo;
typedef System::DelphiInterface<Deployment_Preview_IInstalledClassicAppInfo> _di_Deployment_Preview_IInstalledClassicAppInfo;
__interface DELPHIINTERFACE Deployment_Preview_IClassicAppManagerStatics;
typedef System::DelphiInterface<Deployment_Preview_IClassicAppManagerStatics> _di_Deployment_Preview_IClassicAppManagerStatics;
class DELPHICLASS TDeployment_PackageManager;
class DELPHICLASS TDeployment_Preview_ClassicAppManager;
//-- type declarations -------------------------------------------------------
typedef _di_Deployment_IPackageVolume *PDeployment_IPackageVolume;

typedef _di_Deployment_IDeploymentResult *PDeployment_IDeploymentResult;

typedef _di_Deployment_IPackageUserInformation *PDeployment_IPackageUserInformation;

typedef _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress *PAsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress *PAsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;

typedef _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress *PIAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress;

typedef _di_AsyncOperationProgressHandler_2__IBuffer__Cardinal *PAsyncOperationProgressHandler_2__IBuffer__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__IBuffer__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__IBuffer__Cardinal *PIAsyncOperationWithProgress_2__IBuffer__Cardinal;

typedef _di_AsyncOperationProgressHandler_2__Cardinal__Cardinal *PAsyncOperationProgressHandler_2__Cardinal__Cardinal;

typedef _di_AsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal *PAsyncOperationWithProgressCompletedHandler_2__Cardinal__Cardinal;

typedef _di_IAsyncOperationWithProgress_2__Cardinal__Cardinal *PIAsyncOperationWithProgress_2__Cardinal__Cardinal;

typedef _di_AsyncOperationCompletedHandler_1__Boolean *PAsyncOperationCompletedHandler_1__Boolean;

typedef _di_IAsyncOperation_1__Boolean *PIAsyncOperation_1__Boolean;

typedef _di_IIterator_1__Deployment_IPackageUserInformation *PIIterator_1__Deployment_IPackageUserInformation;

typedef _di_IIterable_1__Deployment_IPackageUserInformation *PIIterable_1__Deployment_IPackageUserInformation;

typedef _di_Deployment_IPackageManager *PDeployment_IPackageManager;

typedef _di_IIterator_1__HSTRING *PIIterator_1__HSTRING;

typedef _di_IIterable_1__HSTRING *PIIterable_1__HSTRING;

typedef _di_Deployment_IPackageManager2 *PDeployment_IPackageManager2;

typedef _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume *PAsyncOperationCompletedHandler_1__Deployment_IPackageVolume;

typedef _di_IAsyncOperation_1__Deployment_IPackageVolume *PIAsyncOperation_1__Deployment_IPackageVolume;

typedef _di_IIterator_1__Deployment_IPackageVolume *PIIterator_1__Deployment_IPackageVolume;

typedef _di_IIterable_1__Deployment_IPackageVolume *PIIterable_1__Deployment_IPackageVolume;

typedef _di_Deployment_IPackageManager3 *PDeployment_IPackageManager3;

typedef _di_IVectorView_1__Deployment_IPackageVolume *PIVectorView_1__Deployment_IPackageVolume;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume *PAsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume;

typedef _di_IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume *PIAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume;

typedef _di_Deployment_IPackageManager4 *PDeployment_IPackageManager4;

typedef _di_Deployment_IPackageManagerDebugSettings *PDeployment_IPackageManagerDebugSettings;

typedef _di_Deployment_IPackageManager5 *PDeployment_IPackageManager5;

typedef _di_Deployment_IPackageManager6 *PDeployment_IPackageManager6;

typedef _di_AsyncOperationCompletedHandler_1__UInt64 *PAsyncOperationCompletedHandler_1__UInt64;

typedef _di_IAsyncOperation_1__UInt64 *PIAsyncOperation_1__UInt64;

typedef _di_IKeyValuePair_2__HSTRING__IInspectable *PIKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterator_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterator_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IIterable_1__IKeyValuePair_2__HSTRING__IInspectable *PIIterable_1__IKeyValuePair_2__HSTRING__IInspectable;

typedef _di_IMapView_2__HSTRING__IInspectable *PIMapView_2__HSTRING__IInspectable;

typedef _di_IMap_2__HSTRING__IInspectable *PIMap_2__HSTRING__IInspectable;

typedef _di_IMapChangedEventArgs_1__HSTRING *PIMapChangedEventArgs_1__HSTRING;

typedef _di_MapChangedEventHandler_2__HSTRING__IInspectable *PMapChangedEventHandler_2__HSTRING__IInspectable;

typedef _di_IObservableMap_2__HSTRING__IInspectable *PIObservableMap_2__HSTRING__IInspectable;

typedef _di_TypedEventHandler_2__IApplicationData__IInspectable *PTypedEventHandler_2__IApplicationData__IInspectable;

typedef _di_IVectorView_1__HSTRING *PIVectorView_1__HSTRING;

typedef _di_AsyncOperationCompletedHandler_1__IInspectable *PAsyncOperationCompletedHandler_1__IInspectable;

typedef _di_IAsyncOperation_1__IInspectable *PIAsyncOperation_1__IInspectable;

typedef _di_Deployment_Preview_IInstalledClassicAppInfo *PDeployment_Preview_IInstalledClassicAppInfo;

typedef _di_Deployment_Preview_IClassicAppManagerStatics *PDeployment_Preview_IClassicAppManagerStatics;

__interface  INTERFACE_UUID("{CF2672C3-1A40-4450-9739-2ACE2E898853}") Deployment_IPackageVolume  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IsOffline(bool &__get_IsOffline_result) = 0 ;
	virtual HRESULT __safecall get_IsSystemVolume(bool &__get_IsSystemVolume_result) = 0 ;
	virtual HRESULT __safecall get_MountPoint(HSTRING &__get_MountPoint_result) = 0 ;
	virtual HRESULT __safecall get_Name(HSTRING &__get_Name_result) = 0 ;
	virtual HRESULT __safecall get_PackageStorePath(HSTRING &__get_PackageStorePath_result) = 0 ;
	virtual HRESULT __safecall get_SupportsHardLinks(bool &__get_SupportsHardLinks_result) = 0 ;
	virtual HRESULT __safecall FindPackages(Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackages(HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackages(HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(Winapi::Commontypes::Deployment_PackageTypes packageTypes, HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(Winapi::Commontypes::Deployment_PackageTypes packageTypes, HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackage(HSTRING packageFullName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackage_result) = 0 ;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, Winapi::Commontypes::Deployment_PackageTypes packageTypes, HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, Winapi::Commontypes::Deployment_PackageTypes packageTypes, HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackageForUser(HSTRING userSecurityId, HSTRING packageFullName, Winapi::Applicationmodel::_di_IVector_1__IPackage &__FindPackageForUser_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsOffline() { bool __r; HRESULT __hr = get_IsOffline(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsOffline = {read=_scw_get_IsOffline};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsSystemVolume() { bool __r; HRESULT __hr = get_IsSystemVolume(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsSystemVolume = {read=_scw_get_IsSystemVolume};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_MountPoint() { HSTRING __r; HRESULT __hr = get_MountPoint(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING MountPoint = {read=_scw_get_MountPoint};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Name() { HSTRING __r; HRESULT __hr = get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Name = {read=_scw_get_Name};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_PackageStorePath() { HSTRING __r; HRESULT __hr = get_PackageStorePath(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING PackageStorePath = {read=_scw_get_PackageStorePath};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_SupportsHardLinks() { bool __r; HRESULT __hr = get_SupportsHardLinks(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool SupportsHardLinks = {read=_scw_get_SupportsHardLinks};
};

__interface  INTERFACE_UUID("{2563B9AE-B77D-4C1F-8A7B-20E6AD515EF3}") Deployment_IDeploymentResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_ErrorText(HSTRING &__get_ErrorText_result) = 0 ;
	virtual HRESULT __safecall get_ActivityId(GUID &__get_ActivityId_result) = 0 ;
	virtual HRESULT __safecall get_ExtendedErrorCode(HRESULT &__get_ExtendedErrorCode_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline GUID _scw_get_ActivityId() { GUID __r; HRESULT __hr = get_ActivityId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property GUID ActivityId = {read=_scw_get_ActivityId};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_ErrorText() { HSTRING __r; HRESULT __hr = get_ErrorText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING ErrorText = {read=_scw_get_ErrorText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HRESULT _scw_get_ExtendedErrorCode() { HRESULT __r; HRESULT __hr = get_ExtendedErrorCode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HRESULT ExtendedErrorCode = {read=_scw_get_ExtendedErrorCode};
};

__interface  INTERFACE_UUID("{F6383423-FA09-4CBC-9055-15CA275E2E7E}") Deployment_IPackageUserInformation  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_UserSecurityId(HSTRING &__get_UserSecurityId_result) = 0 ;
	virtual HRESULT __safecall get_InstallState(Winapi::Commontypes::Deployment_PackageInstallState &__get_InstallState_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Deployment_PackageInstallState _scw_get_InstallState() { Winapi::Commontypes::Deployment_PackageInstallState __r; HRESULT __hr = get_InstallState(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Deployment_PackageInstallState InstallState = {read=_scw_get_InstallState};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UserSecurityId() { HSTRING __r; HRESULT __hr = get_UserSecurityId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UserSecurityId = {read=_scw_get_UserSecurityId};
};

__interface  INTERFACE_UUID("{F1B926D1-1796-597A-9BEA-6C6449D03EEF}") AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{861AC421-B865-5686-86C4-4917F24750BB}") AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress  : public AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress asyncInfo, Winapi::Commontypes::Deployment_DeploymentProgress progressInfo) = 0 ;
};

__interface  INTERFACE_UUID("{6E1C7129-61E0-5D88-9FD4-F3CE65A05719}") AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{2ABB4ED1-2F62-5ED0-8D86-755BEEBBB430}") AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress  : public AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{5A97AAB7-B6EA-55AC-A5DC-D5B164D94E94}") IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{7AF23842-29E8-5C37-BB0B-6561C00ADB92}") IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress  : public IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress_Base 
{
	virtual HRESULT __safecall put_Progress(_di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress handler) = 0 ;
	virtual HRESULT __safecall get_Progress(_di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__get_Progress_result) = 0 ;
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_Deployment_IDeploymentResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress _scw_get_Progress() { _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress __r; HRESULT __hr = get_Progress(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationProgressHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress Progress = {read=_scw_get_Progress, write=put_Progress};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress _scw_get_Completed() { _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationWithProgressCompletedHandler_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress Completed = {read=_scw_get_Completed, write=put_Completed};
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

__interface  INTERFACE_UUID("{75660566-AE43-5858-ADA6-D57DDAE90277}") IIterator_1__Deployment_IPackageUserInformation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{BA4EB7C5-E98F-56CE-965B-8E26E0FF88DC}") IIterator_1__Deployment_IPackageUserInformation  : public IIterator_1__Deployment_IPackageUserInformation_Base 
{
	virtual HRESULT __safecall get_Current(_di_Deployment_IPackageUserInformation &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PDeployment_IPackageUserInformation items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Deployment_IPackageUserInformation _scw_get_Current() { _di_Deployment_IPackageUserInformation __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Deployment_IPackageUserInformation Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{341348B9-52C8-5B57-9E91-F19F2A05B188}") IIterable_1__Deployment_IPackageUserInformation_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{1CD8D83B-9210-50C2-A324-5A8E16954951}") IIterable_1__Deployment_IPackageUserInformation  : public IIterable_1__Deployment_IPackageUserInformation_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Deployment_IPackageUserInformation &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9A7D4B65-5E8F-4FC7-A2E5-7F6925CB8B53}") Deployment_IPackageManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AddPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__AddPackageAsync_result) = 0 ;
	virtual HRESULT __safecall UpdatePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__UpdatePackageAsync_result) = 0 ;
	virtual HRESULT __safecall RemovePackageAsync(HSTRING packageFullName, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RemovePackageAsync_result) = 0 ;
	virtual HRESULT __safecall StagePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StagePackageAsync_result) = 0 ;
	virtual HRESULT __safecall RegisterPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass manifestUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RegisterPackageAsync_result) = 0 ;
	virtual HRESULT __safecall FindPackages(Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackages(HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, HSTRING packageName, HSTRING packagePublisher, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindUsers(HSTRING packageFullName, _di_IIterable_1__Deployment_IPackageUserInformation &__FindUsers_result) = 0 ;
	virtual HRESULT __safecall SetPackageState(HSTRING packageFullName, Winapi::Commontypes::Deployment_PackageState packageState) = 0 ;
	virtual HRESULT __safecall FindPackage(HSTRING packageFullName, Winapi::Commontypes::_di_IPackage &__FindPackage_result) = 0 ;
	virtual HRESULT __safecall CleanupPackageForUserAsync(HSTRING packageName, HSTRING userSecurityId, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__CleanupPackageForUserAsync_result) = 0 ;
	virtual HRESULT __safecall FindPackages(HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackages_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUser(HSTRING userSecurityId, HSTRING packageFamilyName, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUser_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackageForUser(HSTRING userSecurityId, HSTRING packageFullName, Winapi::Commontypes::_di_IPackage &__FindPackageForUser_result) = 0 ;
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

__interface  INTERFACE_UUID("{F7AAD08D-0840-46F2-B5D8-CAD47693A095}") Deployment_IPackageManager2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall RemovePackageAsync(HSTRING packageFullName, Winapi::Commontypes::Deployment_RemovalOptions removalOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RemovePackageAsync_result) = 0 ;
	virtual HRESULT __safecall StagePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StagePackageAsync_result) = 0 ;
	virtual HRESULT __safecall RegisterPackageByFullNameAsync(HSTRING mainPackageFullName, _di_IIterable_1__HSTRING dependencyPackageFullNames, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RegisterPackageByFullNameAsync_result) = 0 ;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(HSTRING packageName, HSTRING packagePublisher, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, HSTRING packageName, HSTRING packagePublisher, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesWithPackageTypes(HSTRING packageFamilyName, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall FindPackagesForUserWithPackageTypes(HSTRING userSecurityId, HSTRING packageFamilyName, Winapi::Commontypes::Deployment_PackageTypes packageTypes, Winapi::Applicationmodel::_di_IIterable_1__IPackage &__FindPackagesForUserWithPackageTypes_result) = 0 /* overload */;
	virtual HRESULT __safecall StageUserDataAsync(HSTRING packageFullName, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StageUserDataAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{35FEE361-6CEA-5E5C-8EDA-34B3F22DF4E7}") AsyncOperationCompletedHandler_1__Deployment_IPackageVolume_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{6FE7A673-8668-57D3-B7F0-4B020D7ACA77}") AsyncOperationCompletedHandler_1__Deployment_IPackageVolume  : public AsyncOperationCompletedHandler_1__Deployment_IPackageVolume_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Deployment_IPackageVolume asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{0315EDB6-DC58-51CC-A519-44901AD2CF15}") IAsyncOperation_1__Deployment_IPackageVolume_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{EEED3F8D-7911-534D-99E8-F5C0D3968F23}") IAsyncOperation_1__Deployment_IPackageVolume  : public IAsyncOperation_1__Deployment_IPackageVolume_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_Deployment_IPackageVolume &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Deployment_IPackageVolume Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{A8D5B736-4E68-5EF1-9F07-F06837988C73}") IIterator_1__Deployment_IPackageVolume_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6502657F-39D1-51CB-8EFC-A5C8E5249C0F}") IIterator_1__Deployment_IPackageVolume  : public IIterator_1__Deployment_IPackageVolume_Base 
{
	virtual HRESULT __safecall get_Current(_di_Deployment_IPackageVolume &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PDeployment_IPackageVolume items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Deployment_IPackageVolume _scw_get_Current() { _di_Deployment_IPackageVolume __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Deployment_IPackageVolume Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{A6199162-B163-56A1-9980-DB0C3F4E9284}") IIterable_1__Deployment_IPackageVolume_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{FF5F02E2-4F72-50FC-B792-22550539B8A0}") IIterable_1__Deployment_IPackageVolume  : public IIterable_1__Deployment_IPackageVolume_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Deployment_IPackageVolume &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{DAAD9948-36F1-41A7-9188-BC263E0DCB72}") Deployment_IPackageManager3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AddPackageVolumeAsync(HSTRING packageStorePath, _di_IAsyncOperation_1__Deployment_IPackageVolume &__AddPackageVolumeAsync_result) = 0 ;
	virtual HRESULT __safecall AddPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__AddPackageAsync_result) = 0 ;
	virtual HRESULT __safecall ClearPackageStatus(HSTRING packageFullName, Winapi::Commontypes::Deployment_PackageStatus status) = 0 ;
	virtual HRESULT __safecall RegisterPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass manifestUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume appDataVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RegisterPackageAsync_result) = 0 ;
	virtual HRESULT __safecall FindPackageVolume(HSTRING volumeName, _di_Deployment_IPackageVolume &__FindPackageVolume_result) = 0 ;
	virtual HRESULT __safecall FindPackageVolumes(_di_IIterable_1__Deployment_IPackageVolume &__FindPackageVolumes_result) = 0 ;
	virtual HRESULT __safecall GetDefaultPackageVolume(_di_Deployment_IPackageVolume &__GetDefaultPackageVolume_result) = 0 ;
	virtual HRESULT __safecall MovePackageToVolumeAsync(HSTRING packageFullName, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__MovePackageToVolumeAsync_result) = 0 ;
	virtual HRESULT __safecall RemovePackageVolumeAsync(_di_Deployment_IPackageVolume volume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RemovePackageVolumeAsync_result) = 0 ;
	virtual HRESULT __safecall SetDefaultPackageVolume(_di_Deployment_IPackageVolume volume) = 0 ;
	virtual HRESULT __safecall SetPackageStatus(HSTRING packageFullName, Winapi::Commontypes::Deployment_PackageStatus status) = 0 ;
	virtual HRESULT __safecall SetPackageVolumeOfflineAsync(_di_Deployment_IPackageVolume packageVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__SetPackageVolumeOfflineAsync_result) = 0 ;
	virtual HRESULT __safecall SetPackageVolumeOnlineAsync(_di_Deployment_IPackageVolume packageVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__SetPackageVolumeOnlineAsync_result) = 0 ;
	virtual HRESULT __safecall StagePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StagePackageAsync_result) = 0 ;
	virtual HRESULT __safecall StageUserDataAsync(HSTRING packageFullName, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StageUserDataAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{3A73E178-6A1B-565F-9E4D-5FA259CA687E}") IVectorView_1__Deployment_IPackageVolume  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Deployment_IPackageVolume &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Deployment_IPackageVolume value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PDeployment_IPackageVolume items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{721241C2-0B83-594A-9B61-CE7F1492C415}") AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F20E797E-09FA-5BAA-B39F-599C139664E1}") AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume  : public AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{1E357E07-D337-5C07-AE06-900C1B9A77C1}") IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{6FD8C3AE-E9B7-5052-A4F6-0481394B4685}") IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume  : public IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__Deployment_IPackageVolume &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__Deployment_IPackageVolume Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{3C719963-BAB6-46BF-8FF7-DA4719230AE6}") Deployment_IPackageManager4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetPackageVolumesAsync(_di_IAsyncOperation_1__IVectorView_1__Deployment_IPackageVolume &__GetPackageVolumesAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{1A611683-A988-4FCF-8F0F-CE175898E8EB}") Deployment_IPackageManagerDebugSettings  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetContentGroupStateAsync(Winapi::Commontypes::_di_IPackage package, HSTRING contentGroupName, Winapi::Commontypes::PackageContentGroupState state, Winapi::Commontypes::_di_IAsyncAction &__SetContentGroupStateAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall SetContentGroupStateAsync(Winapi::Commontypes::_di_IPackage package, HSTRING contentGroupName, Winapi::Commontypes::PackageContentGroupState state, double completionPercentage, Winapi::Commontypes::_di_IAsyncAction &__SetContentGroupStateAsync_result) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{711F3117-1AFD-4313-978C-9BB6E1B864A7}") Deployment_IPackageManager5  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AddPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass externalPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__AddPackageAsync_result) = 0 ;
	virtual HRESULT __safecall StagePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass externalPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StagePackageAsync_result) = 0 ;
	virtual HRESULT __safecall RegisterPackageByFamilyNameAsync(HSTRING mainPackageFamilyName, _di_IIterable_1__HSTRING dependencyPackageFamilyNames, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume appDataVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RegisterPackageByFamilyNameAsync_result) = 0 ;
	virtual HRESULT __safecall get_DebugSettings(_di_Deployment_IPackageManagerDebugSettings &__get_DebugSettings_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Deployment_IPackageManagerDebugSettings _scw_get_DebugSettings() { _di_Deployment_IPackageManagerDebugSettings __r; HRESULT __hr = get_DebugSettings(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Deployment_IPackageManagerDebugSettings DebugSettings = {read=_scw_get_DebugSettings};
};

__interface  INTERFACE_UUID("{0847E909-53CD-4E4F-832E-57D180F6E447}") Deployment_IPackageManager6  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall ProvisionPackageForAllUsersAsync(HSTRING packageFamilyName, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__ProvisionPackageForAllUsersAsync_result) = 0 ;
	virtual HRESULT __safecall AddPackageByAppInstallerFileAsync(Winapi::Commontypes::_di_IUriRuntimeClass appInstallerFileUri, Winapi::Commontypes::Deployment_AddPackageByAppInstallerOptions options, _di_Deployment_IPackageVolume targetVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__AddPackageByAppInstallerFileAsync_result) = 0 ;
	virtual HRESULT __safecall RequestAddPackageByAppInstallerFileAsync(Winapi::Commontypes::_di_IUriRuntimeClass appInstallerFileUri, Winapi::Commontypes::Deployment_AddPackageByAppInstallerOptions options, _di_Deployment_IPackageVolume targetVolume, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RequestAddPackageByAppInstallerFileAsync_result) = 0 ;
	virtual HRESULT __safecall AddPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions options, _di_Deployment_IPackageVolume targetVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass packageUrisToInstall, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass relatedPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__AddPackageAsync_result) = 0 ;
	virtual HRESULT __safecall StagePackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions options, _di_Deployment_IPackageVolume targetVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass packageUrisToInstall, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass relatedPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__StagePackageAsync_result) = 0 ;
	virtual HRESULT __safecall RequestAddPackageAsync(Winapi::Commontypes::_di_IUriRuntimeClass packageUri, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass dependencyPackageUris, Winapi::Commontypes::Deployment_DeploymentOptions deploymentOptions, _di_Deployment_IPackageVolume targetVolume, _di_IIterable_1__HSTRING optionalPackageFamilyNames, Winapi::Foundation::_di_IIterable_1__IUriRuntimeClass relatedPackageUris, _di_IAsyncOperationWithProgress_2__Deployment_IDeploymentResult__Deployment_DeploymentProgress &__RequestAddPackageAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{EE8AEB02-FB00-51FA-8F57-32583EA241F9}") AsyncOperationCompletedHandler_1__UInt64_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{EE8AEB02-FB00-51FA-8F57-32583EA241F9}") AsyncOperationCompletedHandler_1__UInt64  : public AsyncOperationCompletedHandler_1__UInt64_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__UInt64 asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2A70D630-0767-5F0A-A1C2-DEB08126E26E}") IAsyncOperation_1__UInt64_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2A70D630-0767-5F0A-A1C2-DEB08126E26E}") IAsyncOperation_1__UInt64  : public IAsyncOperation_1__UInt64_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__UInt64 handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__UInt64 &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(unsigned __int64 &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__UInt64 _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__UInt64 __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__UInt64 Completed = {read=_scw_get_Completed, write=put_Completed};
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

__interface  INTERFACE_UUID("{4E72D889-3D9A-5E3B-AA8A-3B37D17226DC}") TypedEventHandler_2__IApplicationData__IInspectable  : public System::IInterface 
{
	virtual HRESULT __safecall Invoke(Winapi::Storage::_di_IApplicationData sender, Winapi::Winrt::_di_IInspectable args) = 0 ;
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

__interface  INTERFACE_UUID("{0A7D3DA3-65D0-4086-80D6-0610D760207D}") Deployment_Preview_IInstalledClassicAppInfo  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall get_DisplayVersion(HSTRING &__get_DisplayVersion_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayVersion() { HSTRING __r; HRESULT __hr = get_DisplayVersion(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayVersion = {read=_scw_get_DisplayVersion};
};

__interface  INTERFACE_UUID("{E2FAD668-882C-4F33-B035-0DF7B90D67E6}") Deployment_Preview_IClassicAppManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall FindInstalledApp(HSTRING appUninstallKey, _di_Deployment_Preview_IInstalledClassicAppInfo &__FindInstalledApp_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDeployment_PackageManager : public System::Win::Winrt::TWinRTGenericImportI__1<_di_Deployment_IPackageManager>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_Deployment_IPackageManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TDeployment_PackageManager() : System::Win::Winrt::TWinRTGenericImportI__1<_di_Deployment_IPackageManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDeployment_PackageManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDeployment_Preview_ClassicAppManager : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Deployment_Preview_IClassicAppManagerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Deployment_Preview_IClassicAppManagerStatics> inherited;
	
public:
	static _di_Deployment_Preview_IInstalledClassicAppInfo __fastcall FindInstalledApp(HSTRING appUninstallKey);
public:
	/* TObject.Create */ inline __fastcall TDeployment_Preview_ClassicAppManager() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Deployment_Preview_IClassicAppManagerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDeployment_Preview_ClassicAppManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Management */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_ManagementHPP
