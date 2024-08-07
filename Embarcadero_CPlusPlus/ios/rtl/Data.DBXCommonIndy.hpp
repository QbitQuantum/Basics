﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXCommonIndy.pas' rev: 34.00 (iOS)

#ifndef Data_DbxcommonindyHPP
#define Data_DbxcommonindyHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <Data.DBXCommon.hpp>
#include <IPPeerAPI.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxcommonindy
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TX500PrincipalIndy;
class DELPHICLASS TX509CertificateIndy;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TX500PrincipalIndy : public Data::Dbxcommon::TX500Principal
{
	typedef Data::Dbxcommon::TX500Principal inherited;
	
protected:
	Ippeerapi::_di_IIPX509Name FIdX509Name;
	bool FInstanceOwner;
	
public:
	__fastcall virtual TX500PrincipalIndy(Ippeerapi::_di_IIPX509Name idX509Name, bool instanceOwner);
	__fastcall virtual ~TX500PrincipalIndy();
	virtual System::UnicodeString __fastcall GetName();
	virtual long __fastcall GetEncoded();
};


class PASCALIMPLEMENTATION TX509CertificateIndy : public Data::Dbxcommon::TX509Certificate
{
	typedef Data::Dbxcommon::TX509Certificate inherited;
	
protected:
	Ippeerapi::_di_IIPX509 FIdX509;
	TX500PrincipalIndy* FSubjectPrincipal;
	TX500PrincipalIndy* FIssuerPrincipal;
	bool FInstanceOwner;
	
public:
	__fastcall virtual TX509CertificateIndy(System::UnicodeString CertFile)/* overload */;
	__fastcall virtual TX509CertificateIndy(System::UnicodeString CertFile, const System::UnicodeString AIPImplementationID)/* overload */;
	__fastcall virtual TX509CertificateIndy(System::UnicodeString CertFile, const System::UnicodeString AIPImplementationID, const System::UnicodeString certpassword)/* overload */;
	__fastcall virtual TX509CertificateIndy(Ippeerapi::_di_IIPX509 idX509, bool instanceOwner)/* overload */;
	__fastcall virtual ~TX509CertificateIndy();
	virtual System::TArray__1<System::Byte> __fastcall GetEncoded()/* overload */;
	virtual Data::Dbxcommon::TPublicKey* __fastcall GetPublicKey()/* overload */;
	virtual bool __fastcall Verify(Data::Dbxcommon::TPublicKey* key)/* overload */;
	virtual void __fastcall CheckValidity()/* overload */;
	virtual void __fastcall CheckValidity(System::TDateTime ADate)/* overload */;
	virtual System::TDateTime __fastcall GetNotAfter();
	virtual System::TDateTime __fastcall GetNotBefore();
	virtual int __fastcall GetBasicConstraints();
	virtual System::UnicodeString __fastcall GetSerialNumber();
	virtual long __fastcall GetVersion();
	virtual System::UnicodeString __fastcall GetSigAlgName();
	virtual System::UnicodeString __fastcall GetSignature();
	virtual Data::Dbxcommon::TX500Principal* __fastcall GetIssuerX500Principal();
	virtual Data::Dbxcommon::TX500Principal* __fastcall GetSubjectX500Principal();
	int __fastcall GetFileType(System::UnicodeString CertFile);
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxcommonindy */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXCOMMONINDY)
using namespace Data::Dbxcommonindy;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxcommonindyHPP
