// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxSocketChannelNative.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsocketchannelnativeHPP
#define Data_DbxsocketchannelnativeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <System.SysUtils.hpp>
#include <Data.DBXTransport.hpp>
#include <IPPeerAPI.hpp>
#include <Data.DBXOpenSSL.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxsocketchannelnative
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSocketChannel;
class DELPHICLASS TDBXIdTCPLayer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSocketChannel : public Data::Dbxtransport::TDbxChannel
{
	typedef Data::Dbxtransport::TDbxChannel inherited;
	
private:
	Data::Dbxcommon::TDBXCommunicationLayer* FCommLayer;
	
protected:
	virtual Data::Dbxtransport::TDBXChannelInfo* __fastcall GetChannelInfo();
	
public:
	__fastcall TDBXSocketChannel()/* overload */;
	__fastcall TDBXSocketChannel(const int id)/* overload */;
	__fastcall virtual ~TDBXSocketChannel();
	virtual void __fastcall Open();
	virtual void __fastcall Close();
	void __fastcall Terminate();
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDBXIdTCPLayer : public Data::Dbxcommon::TDBXCommunicationLayer
{
	typedef Data::Dbxcommon::TDBXCommunicationLayer inherited;
	
private:
	Ippeerapi::_di_IIPTCPClient FIdSocket;
	bool FConnected;
	System::UnicodeString FIPImplementationID;
	
protected:
#ifndef _WIN64
	int __fastcall ReadData(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	int __fastcall ReadData(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	virtual Ippeerapi::_di_IIPTCPClient __fastcall CreateClientSocket();
	
public:
	__fastcall virtual TDBXIdTCPLayer();
	__fastcall virtual ~TDBXIdTCPLayer();
	virtual void __fastcall Open(Data::Dbxcommon::TDBXProperties* const DBXProperties);
	virtual void __fastcall Close();
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	virtual void __fastcall Terminate();
	virtual System::UnicodeString __fastcall Info();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsocketchannelnative */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSOCKETCHANNELNATIVE)
using namespace Data::Dbxsocketchannelnative;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsocketchannelnativeHPP
