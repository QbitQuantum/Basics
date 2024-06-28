// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.StructuredQuery.pas' rev: 34.00 (Windows)

#ifndef Winapi_StructuredqueryHPP
#define Winapi_StructuredqueryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.StructuredQueryCondition.hpp>
#include <Winapi.ObjectArray.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <structuredquery.h>
DECLARE_DINTERFACE_TYPE(ISchemaLocalizerSupport);
DECLARE_DINTERFACE_TYPE(IQueryParser);
DECLARE_DINTERFACE_TYPE(IConditionFactory);
DECLARE_DINTERFACE_TYPE(IQuerySolution);
DECLARE_DINTERFACE_TYPE(IConditionFactory2);
DECLARE_DINTERFACE_TYPE(IConditionGenerator);
DECLARE_DINTERFACE_TYPE(IInterval);
DECLARE_DINTERFACE_TYPE(IMetaData);
DECLARE_DINTERFACE_TYPE(IEntity);
DECLARE_DINTERFACE_TYPE(IRelationship);
DECLARE_DINTERFACE_TYPE(INamedEntity);
DECLARE_DINTERFACE_TYPE(ISchemaProvider);
DECLARE_DINTERFACE_TYPE(ITokenCollection);
DECLARE_DINTERFACE_TYPE(INamedEntityCollector);
DECLARE_DINTERFACE_TYPE(ISchemaLocalizerSupport);
DECLARE_DINTERFACE_TYPE(IQueryParserManager);

namespace Winapi
{
namespace Structuredquery
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef STRUCTURED_QUERY_SYNTAX TStructuredQuerySyntax;

typedef STRUCTURED_QUERY_SINGLE_OPTION TStructuredQuerySingleOption;

typedef STRUCTURED_QUERY_MULTIOPTION TStructuredQueryMultiOption;

typedef STRUCTURED_QUERY_PARSE_ERROR TStructuredQueryParseError;

typedef STRUCTURED_QUERY_RESOLVE_OPTION TStructuredQueryResolveOption;

typedef INTERVAL_LIMIT_KIND TIntervalLimitKind;

typedef QUERY_PARSER_MANAGER_OPTION TQueryParserManagerOption;

typedef CONDITION_CREATION_OPTIONS TConditionCreationOptions;

typedef NAMED_ENTITY_CERTAINTY TNamedEntityCertainty;

//-- var, const, procedure ---------------------------------------------------
#define SID_IQueryParser L"{2EBDEE67-3505-43f8-9946-EA44ABC8E5B0}"
#define SID_IConditionFactory L"{A5EFE073-B16F-474f-9F3E-9F8B497A3E08}"
#define SID_IQuerySolution L"{D6EBC66B-8921-4193-AFDD-A1789FB7FF57}"
#define SID_IConditionFactory2 L"{71D222E1-432F-429e-8C13-B6DAFDE5077A}"
#define SID_IConditionGenerator L"{92D2CC58-4386-45a3-B98C-7E0CE64A4117}"
#define SID_IInterval L"{6BF0A714-3C18-430b-8B5D-83B1C234D3DB}"
#define SID_IMetaData L"{780102B0-C43B-4876-BC7B-5E9BA5C88794}"
#define SID_IEntity L"{24264891-E80B-4fd3-B7CE-4FF2FAE8931F}"
#define SID_IRelationship L"{2769280B-5108-498c-9C7F-A51239B63147}"
#define SID_INamedEntity L"{ABDBD0B1-7D54-49fb-AB5C-BFF4130004CD}"
#define SID_ISchemaProvider L"{8CF89BCB-394C-49b2-AE28-A59DD4ED7F68}"
#define SID_ITokenCollection L"{22D8B4F2-F577-4adb-A335-C2AE88416FAB}"
#define SID_INamedEntityCollector L"{AF2440F6-8AFC-47d0-9A7F-396A0ACFB43D}"
#define SID_ISchemaLocalizerSupport L"{CA3FDCA2-BFBE-4eed-90D7-0CAEF0A1BDA1}"
#define SID_IQueryParserManager L"{A879E3C4-AF77-44fb-8F37-EBD1487CF920}"
}	/* namespace Structuredquery */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_STRUCTUREDQUERY)
using namespace Winapi::Structuredquery;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_StructuredqueryHPP
