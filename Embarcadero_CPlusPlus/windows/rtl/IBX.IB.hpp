// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IB.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbHPP
#define Ibx_IbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBExternals.hpp>
#include <Data.DB.hpp>
#include <IBX.IBXConst.hpp>
#include <IBX.IBIntf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ib
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIBError;
class DELPHICLASS EIBInterBaseError;
class DELPHICLASS EIBInterBaseRoleError;
class DELPHICLASS EIBClientError;
class DELPHICLASS EIBPlanError;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TTraceFlag : unsigned char { tfQPrepare, tfQExecute, tfQFetch, tfError, tfStmt, tfConnect, tfTransact, tfBlob, tfService, tfMisc };

typedef System::Set<TTraceFlag, TTraceFlag::tfQPrepare, TTraceFlag::tfMisc> TTraceFlags;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIBError : public Data::Db::EDatabaseError
{
	typedef Data::Db::EDatabaseError inherited;
	
private:
	int FSQLCode;
	int FIBErrorCode;
	
public:
	__fastcall EIBError(int ASQLCode, System::UnicodeString Msg)/* overload */;
	__fastcall EIBError(int ASQLCode, int AIBErrorCode, System::UnicodeString Msg)/* overload */;
	__property int SQLCode = {read=FSQLCode, nodefault};
	__property int IBErrorCode = {read=FIBErrorCode, nodefault};
public:
	/* Exception.CreateFmt */ inline __fastcall EIBError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Data::Db::EDatabaseError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBError(NativeUInt Ident)/* overload */ : Data::Db::EDatabaseError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBError(System::PResStringRec ResStringRec)/* overload */ : Data::Db::EDatabaseError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBError(const System::UnicodeString Msg, int AHelpContext) : Data::Db::EDatabaseError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Data::Db::EDatabaseError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBError(NativeUInt Ident, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Db::EDatabaseError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIBInterBaseError : public EIBError
{
	typedef EIBError inherited;
	
public:
	/* EIBError.Create */ inline __fastcall EIBInterBaseError(int ASQLCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, Msg) { }
	/* EIBError.Create */ inline __fastcall EIBInterBaseError(int ASQLCode, int AIBErrorCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, AIBErrorCode, Msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBInterBaseError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBInterBaseError(NativeUInt Ident)/* overload */ : EIBError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBInterBaseError(System::PResStringRec ResStringRec)/* overload */ : EIBError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInterBaseError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInterBaseError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBInterBaseError(const System::UnicodeString Msg, int AHelpContext) : EIBError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBInterBaseError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInterBaseError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInterBaseError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInterBaseError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInterBaseError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBInterBaseError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIBInterBaseRoleError : public EIBError
{
	typedef EIBError inherited;
	
public:
	/* EIBError.Create */ inline __fastcall EIBInterBaseRoleError(int ASQLCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, Msg) { }
	/* EIBError.Create */ inline __fastcall EIBInterBaseRoleError(int ASQLCode, int AIBErrorCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, AIBErrorCode, Msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBInterBaseRoleError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBInterBaseRoleError(NativeUInt Ident)/* overload */ : EIBError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBInterBaseRoleError(System::PResStringRec ResStringRec)/* overload */ : EIBError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInterBaseRoleError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBInterBaseRoleError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBInterBaseRoleError(const System::UnicodeString Msg, int AHelpContext) : EIBError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBInterBaseRoleError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInterBaseRoleError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBInterBaseRoleError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInterBaseRoleError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBInterBaseRoleError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBInterBaseRoleError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIBClientError : public EIBError
{
	typedef EIBError inherited;
	
public:
	/* EIBError.Create */ inline __fastcall EIBClientError(int ASQLCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, Msg) { }
	/* EIBError.Create */ inline __fastcall EIBClientError(int ASQLCode, int AIBErrorCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, AIBErrorCode, Msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBClientError(NativeUInt Ident)/* overload */ : EIBError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBClientError(System::PResStringRec ResStringRec)/* overload */ : EIBError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBClientError(const System::UnicodeString Msg, int AHelpContext) : EIBError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBClientError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBClientError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBClientError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBClientError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBClientError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBClientError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIBPlanError : public EIBError
{
	typedef EIBError inherited;
	
public:
	/* EIBError.Create */ inline __fastcall EIBPlanError(int ASQLCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, Msg) { }
	/* EIBError.Create */ inline __fastcall EIBPlanError(int ASQLCode, int AIBErrorCode, System::UnicodeString Msg)/* overload */ : EIBError(ASQLCode, AIBErrorCode, Msg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIBPlanError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIBError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIBPlanError(NativeUInt Ident)/* overload */ : EIBError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIBPlanError(System::PResStringRec ResStringRec)/* overload */ : EIBError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBPlanError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIBPlanError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIBError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIBPlanError(const System::UnicodeString Msg, int AHelpContext) : EIBError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIBPlanError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIBError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBPlanError(NativeUInt Ident, int AHelpContext)/* overload */ : EIBError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIBPlanError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIBError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBPlanError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIBPlanError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIBError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIBPlanError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TIBDataBaseErrorMessage : unsigned char { ShowSQLCode, ShowIBMessage, ShowSQLMessage };

typedef System::Set<TIBDataBaseErrorMessage, TIBDataBaseErrorMessage::ShowSQLCode, TIBDataBaseErrorMessage::ShowSQLMessage> TIBDataBaseErrorMessages;

enum DECLSPEC_DENUM TIBClientError : unsigned char { ibxeUnknownError, ibxeInterBaseMissing, ibxeInterBaseInstallMissing, ibxeIB60feature, ibxeNotSupported, ibxeNotPermitted, ibxeFileAccessError, ibxeConnectionTimeout, ibxeCannotSetDatabase, ibxeCannotSetTransaction, ibxeOperationCancelled, ibxeDPBConstantNotSupported, ibxeDPBConstantUnknown, ibxeTPBConstantNotSupported, ibxeTPBConstantUnknown, ibxeDatabaseClosed, ibxeDatabaseOpen, ibxeDatabaseNameMissing, ibxeNotInTransaction, ibxeInTransaction, ibxeTimeoutNegative, ibxeNoDatabasesInTransaction, ibxeUpdateWrongDB, ibxeUpdateWrongTR, ibxeDatabaseNotAssigned, ibxeTransactionNotAssigned, ibxeXSQLDAIndexOutOfRange, ibxeXSQLDANameDoesNotExist, ibxeEOF, ibxeBOF, ibxeInvalidStatementHandle, ibxeSQLOpen, 
	ibxeSQLClosed, ibxeDatasetOpen, ibxeDatasetClosed, ibxeUnknownSQLDataType, ibxeInvalidColumnIndex, ibxeInvalidParamColumnIndex, ibxeInvalidDataConversion, ibxeColumnIsNotNullable, ibxeBlobCannotBeRead, ibxeBlobCannotBeWritten, ibxeEmptyQuery, ibxeCannotOpenNonSQLSelect, ibxeNoFieldAccess, ibxeFieldReadOnly, ibxeFieldNotFound, ibxeNotEditing, ibxeCannotInsert, ibxeCannotPost, ibxeCannotUpdate, ibxeCannotDelete, ibxeCannotRefresh, ibxeBufferNotSet, ibxeCircularReference, ibxeSQLParseError, ibxeUserAbort, ibxeDataSetUniDirectional, ibxeCannotCreateSharedResource, ibxeWindowsAPIError, ibxeColumnListsDontMatch, ibxeColumnTypesDontMatch, ibxeCantEndSharedTransaction, ibxeFieldUnsupportedType, ibxeCircularDataLink, ibxeEmptySQLStatement, ibxeIsASelectStatement, 
	ibxeRequiredParamNotSet, ibxeNoStoredProcName, ibxeIsAExecuteProcedure, ibxeUpdateFailed, ibxeNotCachedUpdates, ibxeNotLiveRequest, ibxeNoProvider, ibxeNoRecordsAffected, ibxeNoTableName, ibxeCannotCreatePrimaryIndex, ibxeCannotDropSystemIndex, ibxeTableNameMismatch, ibxeIndexFieldMissing, ibxeInvalidCancellation, ibxeInvalidEvent, ibxeMaximumEvents, ibxeNoEventsRegistered, ibxeInvalidQueueing, ibxeInvalidRegistration, ibxeInvalidBatchMove, ibxeSQLDialectInvalid, ibxeSPBConstantNotSupported, ibxeSPBConstantUnknown, ibxeServiceActive, ibxeServiceInActive, ibxeServerNameMissing, ibxeQueryParamsError, ibxeStartParamsError, ibxeOutputParsingError, ibxeUseSpecificProcedures, ibxeSQLMonitorAlreadyPresent, ibxeCantPrintValue, ibxeEOFReached, ibxeEOFInComment, 
	ibxeEOFInString, ibxeParamNameExpected, ibxeSuccess, ibxeDelphiException, ibxeNoOptionsSet, ibxeNoDestinationDirectory, ibxeNosourceDirectory, ibxeNoUninstallFile, ibxeOptionNeedsClient, ibxeOptionNeedsServer, ibxeInvalidOption, ibxeInvalidOnErrorResult, ibxeInvalidOnStatusResult, ibxeDPBConstantUnknownEx, ibxeTPBConstantUnknownEx, ibxeUnknownPlan, ibxeFieldSizeMismatch, ibxeEventAlreadyRegistered, ibxeStringTooLarge, ibxeIB65feature, ibxeIB70Feature, ibxeIBUnknownServerType, ibxeInvalidLibraryType, ibxeInvalidODSVersion };

typedef System::StaticArray<NativeInt, 20> TStatusVector;

typedef TStatusVector *PStatusVector;

typedef System::StaticArray<System::UnicodeString, 125> Ibx_Ib__6;

//-- var, const, procedure ---------------------------------------------------
#define IBPalette1 L"InterBase"
#define IBPalette2 L"InterBase Admin"
static const System::Word IBLocalBufferLength = System::Word(0x200);
static const System::Word IBBigLocalBufferLength = System::Word(0x400);
static const System::Word IBHugeLocalBufferLength = System::Word(0x5000);
extern DELPHI_PACKAGE Ibx_Ib__6 IBErrorMessages;
extern DELPHI_PACKAGE System::Sysutils::TSimpleRWSync* IBCS;
extern DELPHI_PACKAGE void __fastcall IBAlloc(void *P, NativeInt OldSize, NativeInt NewSize)/* overload */;
extern DELPHI_PACKAGE void __fastcall IBAlloc(System::PByte &p, NativeInt OldSize, NativeInt NewSize)/* overload */;
extern DELPHI_PACKAGE void __fastcall IBError(TIBClientError ErrMess, const System::TVarRec *Args, const int Args_High);
extern DELPHI_PACKAGE void __fastcall IBDataBaseError(Ibx::Ibintf::_di_IGDSLibrary FGDSLibrary);
extern DELPHI_PACKAGE Ibx::Ibexternals::PISC_STATUS __fastcall StatusVector(void);
extern DELPHI_PACKAGE PStatusVector __fastcall StatusVectorArray(void);
extern DELPHI_PACKAGE bool __fastcall CheckStatusVector(NativeInt *ErrorCodes, const int ErrorCodes_High);
extern DELPHI_PACKAGE System::UnicodeString __fastcall StatusVectorAsText(void);
extern DELPHI_PACKAGE void __fastcall SetIBDataBaseErrorMessages(TIBDataBaseErrorMessages Value);
extern DELPHI_PACKAGE TIBDataBaseErrorMessages __fastcall GetIBDataBaseErrorMessages(void);
}	/* namespace Ib */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IB)
using namespace Ibx::Ib;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbHPP
