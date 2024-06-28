// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MSSQLCli.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_MssqlcliHPP
#define Firedac_Phys_MssqlcliHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Phys
{
namespace Mssqlcli
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
#ifndef __x86_64__
typedef NativeUInt __stdcall (*TMSSQLOpenSqlFilestream)(System::WideChar * FilestreamPath, unsigned DesiredAccess, unsigned OpenOptions, System::PByte FilestreamTransactionContext, unsigned FilestreamTransactionContextLength, System::PInt64 AllocationSize);
#else /* __x86_64__ */
typedef NativeUInt __stdcall (*TMSSQLOpenSqlFilestream)(System::WideChar * FilestreamPath, unsigned long DesiredAccess, unsigned long OpenOptions, System::PByte FilestreamTransactionContext, unsigned __int64 FilestreamTransactionContextLength, System::PInt64 AllocationSize);
#endif /* __x86_64__ */

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 SQL_FILESTREAM_READ = System::Int8(0x0);
static const System::Int8 SQL_FILESTREAM_WRITE = System::Int8(0x1);
static const System::Int8 SQL_FILESTREAM_READWRITE = System::Int8(0x2);
static const System::Int8 SQL_FILESTREAM_OPEN_NONE = System::Int8(0x0);
static const System::Int8 SQL_FILESTREAM_OPEN_FLAG_ASYNC = System::Int8(0x1);
static const System::Int8 SQL_FILESTREAM_OPEN_FLAG_NO_BUFFERING = System::Int8(0x2);
static const System::Int8 SQL_FILESTREAM_OPEN_FLAG_NO_WRITE_THROUGH = System::Int8(0x4);
static const System::Int8 SQL_FILESTREAM_OPEN_FLAG_SEQUENTIAL_SCAN = System::Int8(0x8);
static const System::Int8 SQL_FILESTREAM_OPEN_FLAG_RANDOM_ACCESS = System::Int8(0x10);
}	/* namespace Mssqlcli */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MSSQLCLI)
using namespace Firedac::Phys::Mssqlcli;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_MssqlcliHPP
