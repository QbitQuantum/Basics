// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Wbem.pas' rev: 34.00 (Windows)

#ifndef Winapi_WbemHPP
#define Winapi_WbemHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------

#include "wbemidl.h"

DECLARE_DINTERFACE_TYPE(IWbemClassObject);
DECLARE_DINTERFACE_TYPE(IWbemObjectAccess);
DECLARE_DINTERFACE_TYPE(IWbemQualifierSet);
DECLARE_DINTERFACE_TYPE(IWbemServices);
DECLARE_DINTERFACE_TYPE(IWbemLocator);
DECLARE_DINTERFACE_TYPE(IWbemObjectSink);
DECLARE_DINTERFACE_TYPE(IEnumWbemClassObject);
DECLARE_DINTERFACE_TYPE(IWbemCallResult);
DECLARE_DINTERFACE_TYPE(IWbemContext);
DECLARE_DINTERFACE_TYPE(IUnsecuredApartment);
DECLARE_DINTERFACE_TYPE(IWbemUnsecuredApartment);
DECLARE_DINTERFACE_TYPE(IWbemStatusCodeText);
DECLARE_DINTERFACE_TYPE(IWbemBackupRestore);
DECLARE_DINTERFACE_TYPE(IWbemBackupRestoreEx);
DECLARE_DINTERFACE_TYPE(IWbemRefresher);
DECLARE_DINTERFACE_TYPE(IWbemHiPerfEnum);
DECLARE_DINTERFACE_TYPE(IWbemConfigureRefresher);
DECLARE_DINTERFACE_TYPE(IWbemShutdown);
DECLARE_DINTERFACE_TYPE(IWbemObjectTextSrc);
DECLARE_DINTERFACE_TYPE(IMofCompiler);
DECLARE_DINTERFACE_TYPE(IWbemPropertyProvider);
DECLARE_DINTERFACE_TYPE(IWbemUnboundObjectSink);
DECLARE_DINTERFACE_TYPE(IWbemEventProvider);
DECLARE_DINTERFACE_TYPE(IWbemEventProviderQuerySink);
DECLARE_DINTERFACE_TYPE(IWbemEventProviderSecurity);
DECLARE_DINTERFACE_TYPE(IWbemEventConsumerProvider);
DECLARE_DINTERFACE_TYPE(IWbemProviderInitSink);
DECLARE_DINTERFACE_TYPE(IWbemProviderInit);
DECLARE_DINTERFACE_TYPE(IWbemHiPerfProvider);
DECLARE_DINTERFACE_TYPE(IWbemDecoupledRegistrar);
DECLARE_DINTERFACE_TYPE(IWbemProviderIdentity);
DECLARE_DINTERFACE_TYPE(IWbemDecoupledBasicEventProvider);
DECLARE_DINTERFACE_TYPE(IWbemEventSink);
DECLARE_DINTERFACE_TYPE(IWbemTransport);
DECLARE_DINTERFACE_TYPE(IWbemLevel1Login);
DECLARE_DINTERFACE_TYPE(IWbemConnectorLogin);
DECLARE_DINTERFACE_TYPE(IWbemAddressResolution);
DECLARE_DINTERFACE_TYPE(IWbemClientTransport);
DECLARE_DINTERFACE_TYPE(IWbemClientConnectionTransport);
DECLARE_DINTERFACE_TYPE(IWbemConstructClassObject);

namespace Winapi
{
namespace Wbem
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef int *PCIMTYPE;

typedef WBEM_COMPILE_STATUS_INFO tag_CompileStatusInfo;

typedef WBEM_COMPILE_STATUS_INFO TWbemCompileStatusInfo;

typedef WBEM_COMPILE_STATUS_INFO *PWbemCompileStatusInfo;

typedef System::PByte WBEM_128BITS;

//-- var, const, procedure ---------------------------------------------------
#define SID_IWbemClassObject L"{dc12a681-737f-11cf-884d-00aa004b2e24}"
#define SID_IWbemObjectAccess L"{49353c9a-516b-11d1-aea6-00c04fb68820}"
#define SID_IWbemQualifierSet L"{dc12a680-737f-11cf-884d-00aa004b2e24}"
#define SID_IWbemServices L"{9556dc99-828c-11cf-a37e-00aa003240c7}"
#define SID_IWbemLocator L"{dc12a687-737f-11cf-884d-00aa004b2e24}"
#define SID_IWbemObjectSink L"{7c857801-7381-11cf-884d-00aa004b2e24}"
#define SID_IEnumWbemClassObject L"{027947e1-d731-11ce-a357-000000000001}"
#define SID_IWbemCallResult L"{44aca675-e8fc-11d0-a07c-00c04fb68820}"
#define SID_IWbemContext L"{44aca674-e8fc-11d0-a07c-00c04fb68820}"
#define SID_IUnsecuredApartment L"{1cfaba8c-1523-11d1-ad79-00c04fd8fdff}"
#define SID_IWbemUnsecuredApartment L"{31739d04-3471-4cf4-9a7c-57a44ae71956}"
#define SID_IWbemStatusCodeText L"{eb87e1bc-3233-11d2-aec9-00c04fb68820}"
#define SID_IWbemBackupRestore L"{C49E32C7-BC8B-11d2-85D4-00105A1F8304}"
#define SID_IWbemBackupRestoreEx L"{A359DEC5-E813-4834-8A2A-BA7F1D777D76}"
#define SID_IWbemRefresher L"{49353c99-516b-11d1-aea6-00c04fb68820}"
#define SID_IWbemHiPerfEnum L"{2705C288-79AE-11d2-B348-00105A1F8177}"
#define SID_IWbemConfigureRefresher L"{49353c92-516b-11d1-aea6-00c04fb68820}"
#define SID_IWbemShutdown L"{b7b31df9-d515-11d3-a11c-00105a1f515a}"
#define SID_IWbemObjectTextSrc L"{bfbf883a-cad7-11d3-a11b-00105a1f515a}"
#define SID_IMofCompiler L"{6daf974e-2e37-11d2-aec9-00c04fb68820}"
#define SID_IWbemPropertyProvider L"{CE61E841-65BC-11d0-B6BD-00AA003240C7}"
#define SID_IWbemUnboundObjectSink L"{e246107b-b06e-11d0-ad61-00c04fd8fdff}"
#define SID_IWbemEventProvider L"{e245105b-b06e-11d0-ad61-00c04fd8fdff}"
#define SID_IWbemEventProviderQuerySink L"{580acaf8-fa1c-11d0-ad72-00c04fd8fdff}"
#define SID_IWbemEventProviderSecurity L"{631f7d96-d993-11d2-b339-00105a1f4aaf}"
#define SID_IWbemEventConsumerProvider L"{e246107a-b06e-11d0-ad61-00c04fd8fdff}"
#define SID_IWbemProviderInitSink L"{1be41571-91dd-11d1-aeb2-00c04fb68820}"
#define SID_IWbemProviderInit L"{1be41572-91dd-11d1-aeb2-00c04fb68820}"
#define SID_IWbemHiPerfProvider L"{49353c93-516b-11d1-aea6-00c04fb68820}"
#define SID_IWbemDecoupledRegistrar L"{1005cbcf-e64f-4646-bcd3-3a089d8a84b4}"
#define SID_IWbemProviderIdentity L"{631f7d97-d993-11d2-b339-00105a1f4aaf}"
#define SID_IWbemDecoupledBasicEventProvider L"{86336d20-ca11-4786-9ef1-bc8a946b42fc}"
#define SID_IWbemEventSink L"{3ae0080a-7e3a-4366-bf89-0feedc931659}"
#define SID_IWbemTransport L"{553fe584-2156-11d0-b6ae-00aa003240c7}"
#define SID_IWbemLevel1Login L"{F309AD18-D86A-11d0-A075-00C04FB68820}"
#define SID_IWbemConnectorLogin L"{d8ec9cb1-b135-4f10-8b1b-c7188bb0d186}"
#define SID_IWbemAddressResolution L"{F7CE2E12-8C90-11d1-9E7B-00C04FC324A8}"
#define SID_IWbemClientTransport L"{F7CE2E11-8C90-11d1-9E7B-00C04FC324A8}"
#define SID_IWbemClientConnectionTransport L"{a889c72a-fcc1-4a9e-af61-ed071333fb5b}"
#define SID_IWbemConstructClassObject L"{9ef76194-70d5-11d1-ad90-00c04fd8fdff}"
}	/* namespace Wbem */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WBEM)
using namespace Winapi::Wbem;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_WbemHPP
