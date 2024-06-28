// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.MidConst.pas' rev: 34.00 (iOS)

#ifndef Datasnap_MidconstHPP
#define Datasnap_MidconstHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Midconst
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#define MIDAS_CatDesc u"Borland DataSnap Application Servers"
extern DELPHI_PACKAGE GUID CATID_MIDASAppServer;
#define MIDASInterceptor_CatDesc u"Borland DataSnap Application Servers"
extern DELPHI_PACKAGE GUID CATID_MIDASInterceptor;
#define SCatImplBaseKey u"%s\\Implemented Categories"
#define SCatImplKey u"%s\\Implemented Categories\\%s"
#define MIDAS_DLL u"MIDAS.DLL"
#define SClsid u"CLSID\\"
#define SPooled u"Pooled"
#define SMaxObjects u"MaxObjects"
#define STimeout u"Timeout"
#define SSingleton u"Singleton"
#define SSockets u"Sockets"
#define SWeb u"Web"
static constexpr System::WideChar SFlagOn = (System::WideChar)(0x31);
static constexpr System::WideChar SFlagOff = (System::WideChar)(0x30);
static constexpr System::Int8 MINDATAPACKETSIZE = System::Int8(0x8);
#define SMidasLib u"libmidas.dylib"
extern DELPHI_PACKAGE System::ResourceString _SProviderNotExported;
#define Datasnap_Midconst_SProviderNotExported System::LoadResourceString(&Datasnap::Midconst::_SProviderNotExported)
extern DELPHI_PACKAGE System::ResourceString _SNoDataProvider;
#define Datasnap_Midconst_SNoDataProvider System::LoadResourceString(&Datasnap::Midconst::_SNoDataProvider)
extern DELPHI_PACKAGE System::ResourceString _SInvalidDataPacket;
#define Datasnap_Midconst_SInvalidDataPacket System::LoadResourceString(&Datasnap::Midconst::_SInvalidDataPacket)
extern DELPHI_PACKAGE System::ResourceString _SRefreshError;
#define Datasnap_Midconst_SRefreshError System::LoadResourceString(&Datasnap::Midconst::_SRefreshError)
extern DELPHI_PACKAGE System::ResourceString _SProviderInvalid;
#define Datasnap_Midconst_SProviderInvalid System::LoadResourceString(&Datasnap::Midconst::_SProviderInvalid)
extern DELPHI_PACKAGE System::ResourceString _SServerNameBlank;
#define Datasnap_Midconst_SServerNameBlank System::LoadResourceString(&Datasnap::Midconst::_SServerNameBlank)
extern DELPHI_PACKAGE System::ResourceString _SRepositoryIdBlank;
#define Datasnap_Midconst_SRepositoryIdBlank System::LoadResourceString(&Datasnap::Midconst::_SRepositoryIdBlank)
extern DELPHI_PACKAGE System::ResourceString _SAggsGroupingLevel;
#define Datasnap_Midconst_SAggsGroupingLevel System::LoadResourceString(&Datasnap::Midconst::_SAggsGroupingLevel)
extern DELPHI_PACKAGE System::ResourceString _SAggsNoSuchLevel;
#define Datasnap_Midconst_SAggsNoSuchLevel System::LoadResourceString(&Datasnap::Midconst::_SAggsNoSuchLevel)
extern DELPHI_PACKAGE System::ResourceString _SNoCircularReference;
#define Datasnap_Midconst_SNoCircularReference System::LoadResourceString(&Datasnap::Midconst::_SNoCircularReference)
extern DELPHI_PACKAGE System::ResourceString _SErrorLoadingMidas;
#define Datasnap_Midconst_SErrorLoadingMidas System::LoadResourceString(&Datasnap::Midconst::_SErrorLoadingMidas)
extern DELPHI_PACKAGE System::ResourceString _SCannotCreateDataSet;
#define Datasnap_Midconst_SCannotCreateDataSet System::LoadResourceString(&Datasnap::Midconst::_SCannotCreateDataSet)
extern DELPHI_PACKAGE System::ResourceString _SInvalidClone;
#define Datasnap_Midconst_SInvalidClone System::LoadResourceString(&Datasnap::Midconst::_SInvalidClone)
extern DELPHI_PACKAGE System::ResourceString _SCDSDlgOpenCaption;
#define Datasnap_Midconst_SCDSDlgOpenCaption System::LoadResourceString(&Datasnap::Midconst::_SCDSDlgOpenCaption)
extern DELPHI_PACKAGE System::ResourceString _SNoConnectToBroker;
#define Datasnap_Midconst_SNoConnectToBroker System::LoadResourceString(&Datasnap::Midconst::_SNoConnectToBroker)
extern DELPHI_PACKAGE System::ResourceString _SSocketReadError;
#define Datasnap_Midconst_SSocketReadError System::LoadResourceString(&Datasnap::Midconst::_SSocketReadError)
extern DELPHI_PACKAGE System::ResourceString _SInvalidProviderName;
#define Datasnap_Midconst_SInvalidProviderName System::LoadResourceString(&Datasnap::Midconst::_SInvalidProviderName)
extern DELPHI_PACKAGE System::ResourceString _SBadVariantType;
#define Datasnap_Midconst_SBadVariantType System::LoadResourceString(&Datasnap::Midconst::_SBadVariantType)
extern DELPHI_PACKAGE System::ResourceString _SInvalidAction;
#define Datasnap_Midconst_SInvalidAction System::LoadResourceString(&Datasnap::Midconst::_SInvalidAction)
extern DELPHI_PACKAGE System::ResourceString _SNoParentConnection;
#define Datasnap_Midconst_SNoParentConnection System::LoadResourceString(&Datasnap::Midconst::_SNoParentConnection)
extern DELPHI_PACKAGE System::ResourceString _SBlankChildName;
#define Datasnap_Midconst_SBlankChildName System::LoadResourceString(&Datasnap::Midconst::_SBlankChildName)
extern DELPHI_PACKAGE System::ResourceString _SInvalidResponse;
#define Datasnap_Midconst_SInvalidResponse System::LoadResourceString(&Datasnap::Midconst::_SInvalidResponse)
extern DELPHI_PACKAGE System::ResourceString _SRecordNotFound;
#define Datasnap_Midconst_SRecordNotFound System::LoadResourceString(&Datasnap::Midconst::_SRecordNotFound)
extern DELPHI_PACKAGE System::ResourceString _STooManyRecordsModified;
#define Datasnap_Midconst_STooManyRecordsModified System::LoadResourceString(&Datasnap::Midconst::_STooManyRecordsModified)
extern DELPHI_PACKAGE System::ResourceString _SInvalidOptParamType;
#define Datasnap_Midconst_SInvalidOptParamType System::LoadResourceString(&Datasnap::Midconst::_SInvalidOptParamType)
extern DELPHI_PACKAGE System::ResourceString _SMissingDataSet;
#define Datasnap_Midconst_SMissingDataSet System::LoadResourceString(&Datasnap::Midconst::_SMissingDataSet)
extern DELPHI_PACKAGE System::ResourceString _SConstraintFailed;
#define Datasnap_Midconst_SConstraintFailed System::LoadResourceString(&Datasnap::Midconst::_SConstraintFailed)
extern DELPHI_PACKAGE System::ResourceString _SField;
#define Datasnap_Midconst_SField System::LoadResourceString(&Datasnap::Midconst::_SField)
extern DELPHI_PACKAGE System::ResourceString _SReadOnlyProvider;
#define Datasnap_Midconst_SReadOnlyProvider System::LoadResourceString(&Datasnap::Midconst::_SReadOnlyProvider)
extern DELPHI_PACKAGE System::ResourceString _SNoKeySpecified;
#define Datasnap_Midconst_SNoKeySpecified System::LoadResourceString(&Datasnap::Midconst::_SNoKeySpecified)
extern DELPHI_PACKAGE System::ResourceString _SNoDataSets;
#define Datasnap_Midconst_SNoDataSets System::LoadResourceString(&Datasnap::Midconst::_SNoDataSets)
extern DELPHI_PACKAGE System::ResourceString _SRecConstFail;
#define Datasnap_Midconst_SRecConstFail System::LoadResourceString(&Datasnap::Midconst::_SRecConstFail)
extern DELPHI_PACKAGE System::ResourceString _SFieldConstFail;
#define Datasnap_Midconst_SFieldConstFail System::LoadResourceString(&Datasnap::Midconst::_SFieldConstFail)
extern DELPHI_PACKAGE System::ResourceString _SDefExprFail;
#define Datasnap_Midconst_SDefExprFail System::LoadResourceString(&Datasnap::Midconst::_SDefExprFail)
extern DELPHI_PACKAGE System::ResourceString _SArrayElementError;
#define Datasnap_Midconst_SArrayElementError System::LoadResourceString(&Datasnap::Midconst::_SArrayElementError)
extern DELPHI_PACKAGE System::ResourceString _SNoTableName;
#define Datasnap_Midconst_SNoTableName System::LoadResourceString(&Datasnap::Midconst::_SNoTableName)
extern DELPHI_PACKAGE System::ResourceString _SNoEditsAllowed;
#define Datasnap_Midconst_SNoEditsAllowed System::LoadResourceString(&Datasnap::Midconst::_SNoEditsAllowed)
extern DELPHI_PACKAGE System::ResourceString _SNoDeletesAllowed;
#define Datasnap_Midconst_SNoDeletesAllowed System::LoadResourceString(&Datasnap::Midconst::_SNoDeletesAllowed)
extern DELPHI_PACKAGE System::ResourceString _SNoInsertsAllowed;
#define Datasnap_Midconst_SNoInsertsAllowed System::LoadResourceString(&Datasnap::Midconst::_SNoInsertsAllowed)
extern DELPHI_PACKAGE System::ResourceString _SCannotChangeCommandText;
#define Datasnap_Midconst_SCannotChangeCommandText System::LoadResourceString(&Datasnap::Midconst::_SCannotChangeCommandText)
extern DELPHI_PACKAGE System::ResourceString _SAggregatesActive;
#define Datasnap_Midconst_SAggregatesActive System::LoadResourceString(&Datasnap::Midconst::_SAggregatesActive)
extern DELPHI_PACKAGE System::ResourceString _SNoServers;
#define Datasnap_Midconst_SNoServers System::LoadResourceString(&Datasnap::Midconst::_SNoServers)
extern DELPHI_PACKAGE System::ResourceString _SInvalidRegistration;
#define Datasnap_Midconst_SInvalidRegistration System::LoadResourceString(&Datasnap::Midconst::_SInvalidRegistration)
extern DELPHI_PACKAGE System::ResourceString _SConnectionMissing;
#define Datasnap_Midconst_SConnectionMissing System::LoadResourceString(&Datasnap::Midconst::_SConnectionMissing)
extern DELPHI_PACKAGE System::ResourceString _SNoCircularConnection;
#define Datasnap_Midconst_SNoCircularConnection System::LoadResourceString(&Datasnap::Midconst::_SNoCircularConnection)
extern DELPHI_PACKAGE System::ResourceString _SReturnError;
#define Datasnap_Midconst_SReturnError System::LoadResourceString(&Datasnap::Midconst::_SReturnError)
extern DELPHI_PACKAGE System::ResourceString _SNoWinSock2;
#define Datasnap_Midconst_SNoWinSock2 System::LoadResourceString(&Datasnap::Midconst::_SNoWinSock2)
extern DELPHI_PACKAGE System::ResourceString _SURLRequired;
#define Datasnap_Midconst_SURLRequired System::LoadResourceString(&Datasnap::Midconst::_SURLRequired)
extern DELPHI_PACKAGE System::ResourceString _SDefaultURL;
#define Datasnap_Midconst_SDefaultURL System::LoadResourceString(&Datasnap::Midconst::_SDefaultURL)
extern DELPHI_PACKAGE System::ResourceString _SInvalidURL;
#define Datasnap_Midconst_SInvalidURL System::LoadResourceString(&Datasnap::Midconst::_SInvalidURL)
extern DELPHI_PACKAGE System::ResourceString _SServerIsBusy;
#define Datasnap_Midconst_SServerIsBusy System::LoadResourceString(&Datasnap::Midconst::_SServerIsBusy)
extern DELPHI_PACKAGE System::ResourceString _SObjectNotAvailable;
#define Datasnap_Midconst_SObjectNotAvailable System::LoadResourceString(&Datasnap::Midconst::_SObjectNotAvailable)
extern DELPHI_PACKAGE System::ResourceString _SMasterNotOpen;
#define Datasnap_Midconst_SMasterNotOpen System::LoadResourceString(&Datasnap::Midconst::_SMasterNotOpen)
extern DELPHI_PACKAGE System::ResourceString _SClassNotAvailable;
#define Datasnap_Midconst_SClassNotAvailable System::LoadResourceString(&Datasnap::Midconst::_SClassNotAvailable)
extern DELPHI_PACKAGE System::ResourceString _SOutOfMemory;
#define Datasnap_Midconst_SOutOfMemory System::LoadResourceString(&Datasnap::Midconst::_SOutOfMemory)
extern DELPHI_PACKAGE System::ResourceString _SInvalidArg;
#define Datasnap_Midconst_SInvalidArg System::LoadResourceString(&Datasnap::Midconst::_SInvalidArg)
extern DELPHI_PACKAGE System::ResourceString _SUnableToLoadICU;
#define Datasnap_Midconst_SUnableToLoadICU System::LoadResourceString(&Datasnap::Midconst::_SUnableToLoadICU)
extern DELPHI_PACKAGE System::ResourceString _SNotFound;
#define Datasnap_Midconst_SNotFound System::LoadResourceString(&Datasnap::Midconst::_SNotFound)
}	/* namespace Midconst */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_MIDCONST)
using namespace Datasnap::Midconst;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_MidconstHPP
