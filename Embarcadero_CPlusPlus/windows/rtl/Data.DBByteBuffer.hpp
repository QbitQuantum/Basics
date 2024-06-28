// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBByteBuffer.pas' rev: 34.00 (Windows)

#ifndef Data_DbbytebufferHPP
#define Data_DbbytebufferHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbbytebuffer
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBByteBuffer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBByteBuffer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Byte> FBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FBuffer;
#endif /* _WIN64 */
	int FOffset;
	int FUsed;
	void __fastcall CheckSpace(int SpaceNeeded);
	
public:
	__fastcall TDBByteBuffer()/* overload */;
#ifndef _WIN64
	__fastcall TDBByteBuffer(System::DynamicArray<System::Byte> Buffer)/* overload */;
#else /* _WIN64 */
	__fastcall TDBByteBuffer(System::TArray__1<System::Byte> Buffer)/* overload */;
#endif /* _WIN64 */
	__fastcall TDBByteBuffer(int Capacity)/* overload */;
	__fastcall virtual ~TDBByteBuffer();
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall GetBytes();
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall GetBytes();
#endif /* _WIN64 */
	void __fastcall SetString(System::UnicodeString Value);
#ifndef _WIN64
	void __fastcall SetBytes(System::DynamicArray<System::Byte> Value);
#else /* _WIN64 */
	void __fastcall SetBytes(System::TArray__1<System::Byte> Value);
#endif /* _WIN64 */
	void __fastcall Append(System::UnicodeString Value)/* overload */;
#ifndef _WIN64
	void __fastcall Append(System::DynamicArray<System::Byte> Value)/* overload */;
#else /* _WIN64 */
	void __fastcall Append(System::TArray__1<System::Byte> Value)/* overload */;
#endif /* _WIN64 */
	void __fastcall Append(System::WideChar * Value, int Count)/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbbytebuffer */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBBYTEBUFFER)
using namespace Data::Dbbytebuffer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbbytebufferHPP
