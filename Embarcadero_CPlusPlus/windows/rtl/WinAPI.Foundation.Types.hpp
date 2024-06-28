// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Foundation.Types.pas' rev: 34.00 (Windows)

#ifndef Winapi_Foundation_TypesHPP
#define Winapi_Foundation_TypesHPP

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
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Foundation
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD FoundationContract
{
};


struct DECLSPEC_DRECORD UniversalApiContract
{
};


struct Numerics_Vector2;
struct Numerics_Vector4;
struct Numerics_Matrix3x2;
//-- type declarations -------------------------------------------------------
using Winapi::Commontypes::AsyncStatus;

typedef Winapi::Commontypes::EventRegistrationToken EventRegistrationToken;

enum class DECLSPEC_DENUM Metadata_GCPressureAmount : unsigned int { Low, Medium, High };

typedef Metadata_GCPressureAmount *PMetadata_GCPressureAmount;

enum class DECLSPEC_DENUM PropertyType : unsigned int { Empty, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Single, Double, Char16, Boolean, String, Inspectable, DateTime, TimeSpan, Guid, Point, Size, Rect, OtherType, UInt8Array = 1025, Int16Array, UInt16Array, Int32Array, UInt32Array, Int64Array, UInt64Array, SingleArray, DoubleArray, Char16Array, BooleanArray, StringArray, InspectableArray, DateTimeArray, TimeSpanArray, GuidArray, PointArray, SizeArray, RectArray, OtherTypeArray };

typedef PropertyType *PPropertyType;

enum class DECLSPEC_DENUM Metadata_Platform : unsigned int { Windows, WindowsPhone };

typedef Metadata_Platform *PMetadata_Platform;

enum class DECLSPEC_DENUM Metadata_AttributeTargets: int { All = -1, Delegate = 1, Enum, Event = 4, Field = 8, Interface = 16, Method = 64, Parameter = 128, Property = 256, RuntimeClass = 512, Struct = 1024, InterfaceImpl = 2048, ApiContract = 8192 };

typedef Metadata_AttributeTargets *PMetadata_AttributeTargets;

enum class DECLSPEC_DENUM Metadata_FeatureStage : unsigned int { AlwaysDisabled, DisabledByDefault, EnabledByDefault, AlwaysEnabled };

typedef Metadata_FeatureStage *PMetadata_FeatureStage;

enum class DECLSPEC_DENUM Metadata_CompositionType : unsigned int { Protected = 0x1, Public };

typedef Metadata_CompositionType *PMetadata_CompositionType;

enum class DECLSPEC_DENUM Metadata_ThreadingModel : unsigned int { STA = 1, MTA, Both, InvalidThreading = 0 };

typedef Metadata_ThreadingModel *PMetadata_ThreadingModel;

enum class DECLSPEC_DENUM Metadata_MarshalingType : unsigned int { None = 1, Agile, Standard, InvalidMarshaling = 0 };

typedef Metadata_MarshalingType *PMetadata_MarshalingType;

enum class DECLSPEC_DENUM Metadata_DeprecationType : unsigned int { Deprecate, Remove };

typedef Metadata_DeprecationType *PMetadata_DeprecationType;

enum class DECLSPEC_DENUM Diagnostics_CausalityTraceLevel : unsigned int { Required, Important, Verbose };

typedef Diagnostics_CausalityTraceLevel *PDiagnostics_CausalityTraceLevel;

enum class DECLSPEC_DENUM Diagnostics_CausalitySource : unsigned int { Application, Library, System };

typedef Diagnostics_CausalitySource *PDiagnostics_CausalitySource;

enum class DECLSPEC_DENUM Diagnostics_CausalityRelation : unsigned int { AssignDelegate, Join, Choice, Cancel, Error };

typedef Diagnostics_CausalityRelation *PDiagnostics_CausalityRelation;

enum class DECLSPEC_DENUM Diagnostics_CausalitySynchronousWork : unsigned int { CompletionNotification, ProgressNotification, Execution };

typedef Diagnostics_CausalitySynchronousWork *PDiagnostics_CausalitySynchronousWork;

enum class DECLSPEC_DENUM Diagnostics_ErrorOptions : unsigned int { None, SuppressExceptions, ForceExceptions, UseSetErrorInfo = 0x4, SuppressSetErrorInfo = 0x8 };

typedef Diagnostics_ErrorOptions *PDiagnostics_ErrorOptions;

enum class DECLSPEC_DENUM Diagnostics_LoggingLevel : unsigned int { Verbose, Information, Warning, Error, Critical };

typedef Diagnostics_LoggingLevel *PDiagnostics_LoggingLevel;

enum class DECLSPEC_DENUM Diagnostics_LoggingOpcode : unsigned int { Info, Start, Stop, Reply = 6, Resume, Suspend, Send };

typedef Diagnostics_LoggingOpcode *PDiagnostics_LoggingOpcode;

enum class DECLSPEC_DENUM Diagnostics_LoggingFieldFormat : unsigned int { Default, Hidden, String, Boolean, Hexadecimal, ProcessId, ThreadId, Port, Ipv4Address, Ipv6Address, SocketAddress, Xml, Json, Win32Error, NTStatus, HResult, FileTime, Signed, Unsigned };

typedef Diagnostics_LoggingFieldFormat *PDiagnostics_LoggingFieldFormat;

typedef FoundationContract *PFoundationContract;

typedef UniversalApiContract *PUniversalApiContract;

struct DECLSPEC_DRECORD Numerics_Vector2
{
public:
	float X;
	float Y;
};


typedef Numerics_Vector2 *PNumerics_Vector2;

struct DECLSPEC_DRECORD Numerics_Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};


typedef Numerics_Vector4 *PNumerics_Vector4;

struct DECLSPEC_DRECORD Numerics_Matrix3x2
{
public:
	float M11;
	float M12;
	float M21;
	float M22;
	float M31;
	float M32;
};


typedef Numerics_Matrix3x2 *PNumerics_Matrix3x2;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Types */
}	/* namespace Foundation */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Foundation_TypesHPP
