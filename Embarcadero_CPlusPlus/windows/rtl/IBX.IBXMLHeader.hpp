// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBXMLHeader.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbxmlheaderHPP
#define Ibx_IbxmlheaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IBX.IBExternals.hpp>
#include <IBX.IBHeader.hpp>
#include <IBX.IBSQL.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibxmlheader
{
//-- forward type declarations -----------------------------------------------
struct TVary;
struct Tib_xmlda;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TVary
{
public:
	short vary_length;
	System::WideChar vary_string;
};


typedef TVary *PVary;

struct DECLSPEC_DRECORD Tib_xmlda
{
public:
	System::Byte *xmlda_file_name;
	System::Byte *xmlda_header_tag;
	System::Byte *xmlda_database_tag;
	System::Byte *xmlda_table_tag;
	System::Byte *xmlda_row_tag;
	System::file *xmlda_file_ptr;
	System::PByte *xmlda_temo_buffer;
	NativeInt xmlda_fetch_stata;
	unsigned xmlda_flags;
	unsigned xmlda_more_data;
	unsigned xmlda_temp_size;
	short xmlda_status;
	short xmlda_more;
	System::Word xmlda_version;
	System::Word xmlda_array_size;
	unsigned xmlda_reserved;
};


typedef Tib_xmlda *PIB_XMLDA;

typedef int __stdcall (*Tisc_dsql_xml_fetch)(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);

typedef int __stdcall (*Tisc_dsql_xml_fetch_all)(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);

typedef int __stdcall (*Tisc_dsql_xml_buffer_fetch)(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::PByte buffer, int buffer_size, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 XMLDA_ATTRIBUTE_FLAG = System::Int8(0x1);
static const System::Int8 XMLDA_DISPLAY_NULL_FLAG = System::Int8(0x2);
static const System::Int8 XMLDA_NO_HEADER_FLAG = System::Int8(0x4);
static const System::Int8 MAXCHARSET_LENGTH = System::Int8(0x20);
static const System::Int8 SHORT_LEN = System::Int8(0x7);
static const System::Int8 LONG_LEN = System::Int8(0xc);
static const System::Int8 INT64_LEN = System::Int8(0x15);
static const System::Int8 QUAD_LEN = System::Int8(0x13);
static const System::Int8 FLOAT_LEN = System::Int8(0xe);
static const System::Int8 DOUBLE_LEN = System::Int8(0x17);
static const System::Int8 DATE_LEN = System::Int8(0xb);
static const System::Int8 DATETIME_LEN = System::Int8(0x19);
static const System::Int8 TIME_ONLY_LEN = System::Int8(0xd);
static const System::Int8 DATE_ONLY_LEN = System::Int8(0xb);
static const System::Int8 UNKNOWN_LEN = System::Int8(0x14);
static const System::Int8 ERR_NOT_ENOUGH_MEMORY = System::Int8(-1);
static const System::Int8 ERR_BUFFERSIZE_NOT_ENOUGH = System::Int8(-2);
extern DELPHI_PACKAGE Tisc_dsql_xml_fetch isc_dsql_xml_fetch;
extern DELPHI_PACKAGE Tisc_dsql_xml_fetch_all isc_dsql_xml_fetch_all;
extern DELPHI_PACKAGE Tisc_dsql_xml_buffer_fetch isc_dsql_xml_buffer_fetch;
extern DELPHI_PACKAGE int __stdcall isc_dsql_xml_fetch_stub(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);
extern DELPHI_PACKAGE int __stdcall isc_dsql_xml_fetch_all_stub(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);
extern DELPHI_PACKAGE int __stdcall isc_dsql_xml_buffer_fetch_stub(Ibx::Ibexternals::PISC_STATUS status, Ibx::Ibheader::PISC_STMT_HANDLE stmt, System::PByte buffer, int buffer_size, System::Word da_version, Ibx::Ibheader::PXSQLDA sqlda, PIB_XMLDA ib_xmlda);
}	/* namespace Ibxmlheader */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBXMLHEADER)
using namespace Ibx::Ibxmlheader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbxmlheaderHPP
