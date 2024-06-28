// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXEncryption.pas' rev: 34.00 (Windows)

#ifndef Data_DbxencryptionHPP
#define Data_DbxencryptionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxencryption
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPC1Cypher;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPC1Cypher : /*[[sealed]]*/ public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Byte TEMPXORVeri;
	
public:
	__fastcall TPC1Cypher()/* overload */;
	__fastcall TPC1Cypher(const System::UnicodeString Key)/* overload */;
	System::Byte __fastcall Cypher(const System::Byte C);
	System::Byte __fastcall Decypher(const System::Byte C);
	bool __fastcall SetEncryptionKey(const System::UnicodeString Key);
	void __fastcall Reset();
	
protected:
	System::UnicodeString __fastcall GetEncryptionKey();
	
private:
	bool __fastcall Init();
	int __fastcall Assemble();
	int __fastcall Code(const int I);
	int FSi;
	int FX1a2;
	Data::Dbxplatform::TDBXInt32s FX1a0;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FCle;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FCle;
#endif /* _WIN64 */
	System::UnicodeString FCypherKey;
	
public:
	__property System::UnicodeString EncryptionKey = {read=GetEncryptionKey};
	
private:
	static const System::Int8 Keylen = System::Int8(0x10);
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TPC1Cypher() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxencryption */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXENCRYPTION)
using namespace Data::Dbxencryption;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxencryptionHPP
