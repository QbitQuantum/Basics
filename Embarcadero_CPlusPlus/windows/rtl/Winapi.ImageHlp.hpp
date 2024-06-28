// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ImageHlp.pas' rev: 34.00 (Windows)

#ifndef Winapi_ImagehlpHPP
#define Winapi_ImagehlpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <imagehlp.h>

namespace Winapi
{
namespace Imagehlp
{
//-- forward type declarations -----------------------------------------------
struct _IMAGE_DEBUG_INFORMATION;
struct _tagADDRESS;
struct _KDHELP;
struct _tagSTACKFRAME;
struct _IMAGEHLP_SYMBOL;
struct _IMAGEHLP_MODULE;
struct _IMAGEHLP_DEFERRED_SYMBOL_LOAD;
struct _IMAGEHLP_DUPLICATE_SYMBOL;
//-- type declarations -------------------------------------------------------
typedef _IMAGEHLP_STATUS_REASON TImagehlpStatusReason;

typedef PIMAGEHLP_STATUS_ROUTINE TImagehlpStatusRoutine;

typedef _LOADED_IMAGE *PloadedImage;

typedef _LOADED_IMAGE LoadedImage;

typedef _LOADED_IMAGE TLoadedImage;

struct DECLSPEC_DRECORD _IMAGE_DEBUG_INFORMATION
{
public:
#ifndef _WIN64
	_SINGLE_LIST_ENTRY List;
#else /* _WIN64 */
	_SLIST_ENTRY List;
#endif /* _WIN64 */
	unsigned Size;
	void *MappedBase;
	System::Word Machine;
	System::Word Characteristics;
	unsigned CheckSum;
	unsigned ImageBase;
	unsigned SizeOfImage;
	unsigned NumberOfSections;
	_IMAGE_SECTION_HEADER *Sections;
	unsigned ExportedNamesSize;
	char *ExportedNames;
	unsigned NumberOfFunctionTableEntries;
	_IMAGE_FUNCTION_ENTRY *FunctionTableEntries;
	unsigned LowestFunctionStartingAddress;
	unsigned HighestFunctionEndingAddress;
	unsigned NumberOfFpoTableEntries;
	_FPO_DATA *FpoTableEntries;
	unsigned SizeOfCoffSymbols;
	_IMAGE_COFF_SYMBOLS_HEADER *CoffSymbols;
	unsigned SizeOfCodeViewSymbols;
	void *CodeViewSymbols;
	char *ImageFilePath;
	char *ImageFileName;
	char *DebugFilePath;
	unsigned TimeDateStamp;
	System::LongBool RomImage;
	_IMAGE_DEBUG_DIRECTORY *DebugDirectory;
	unsigned NumberOfDebugDirectories;
	System::StaticArray<unsigned, 3> Reserved;
};


typedef ADDRESS_MODE TAddressMode;

struct DECLSPEC_DRECORD _tagADDRESS
{
public:
	NativeUInt Offset;
	System::Word Segment;
	ADDRESS_MODE Mode;
};


struct DECLSPEC_DRECORD _KDHELP
{
public:
	NativeUInt Thread;
	unsigned ThCallbackStack;
#ifdef _WIN64
	unsigned ThCallbackBStore;
#endif /* _WIN64 */
	unsigned NextCallback;
	unsigned FramePointer;
	NativeUInt KiCallUserMode;
	NativeUInt KeUserCallbackDispatcher;
	NativeUInt SystemRangeStart;
#ifndef _WIN64
	unsigned ThCallbackBStore;
#endif /* not _WIN64 */
	NativeUInt KiUserExceptionDispatcher;
	NativeUInt StackBase;
	NativeUInt StackLimit;
	System::StaticArray<NativeUInt, 5> Reserved;
};


struct DECLSPEC_DRECORD _tagSTACKFRAME
{
public:
	_tagADDRESS AddrPC;
	_tagADDRESS AddrReturn;
	_tagADDRESS AddrFrame;
	_tagADDRESS AddrStack;
#ifdef _WIN64
	_tagADDRESS AddrBStore;
#endif /* _WIN64 */
	void *FuncTableEntry;
	System::StaticArray<NativeUInt, 4> Params;
	System::LongBool _Far;
	System::LongBool _Virtual;
	System::StaticArray<NativeUInt, 3> Reserved;
	_KDHELP KdHelp;
#ifndef _WIN64
	_tagADDRESS AddrBStore;
#endif /* not _WIN64 */
};


typedef PREAD_PROCESS_MEMORY_ROUTINE TReadProcessMemoryRoutine;

typedef PFUNCTION_TABLE_ACCESS_ROUTINE TFunctionTableAccessRoutine;

typedef PGET_MODULE_BASE_ROUTINE TGetModuleBaseRoutine;

typedef PTRANSLATE_ADDRESS_ROUTINE TTranslateAddressRoutine;

typedef API_VERSION *PApiVersion;

typedef API_VERSION TApiVersion;

typedef PSYM_ENUMMODULES_CALLBACK TSymEnummodulesCallback;

typedef PSYM_ENUMSYMBOLS_CALLBACK TSymEnumsymbolsCallback;

typedef PENUMLOADED_MODULES_CALLBACK TEnumloadedModulesCallback;

typedef PSYMBOL_REGISTERED_CALLBACK TSymbolRegisteredCallback;

typedef SYM_TYPE TSymType;

struct DECLSPEC_DRECORD _IMAGEHLP_SYMBOL
{
public:
	unsigned SizeOfStruct;
	NativeUInt Address;
	unsigned Size;
	unsigned Flags;
	unsigned MaxNameLength;
	System::StaticArray<char, 1> Name;
};


struct DECLSPEC_DRECORD _IMAGEHLP_MODULE
{
public:
	unsigned SizeOfStruct;
	NativeUInt BaseOfImage;
	unsigned ImageSize;
	unsigned TimeDateStamp;
	unsigned CheckSum;
	unsigned NumSyms;
	SYM_TYPE SymType;
	System::StaticArray<char, 32> ModuleName;
	System::StaticArray<char, 256> ImageName;
	System::StaticArray<char, 256> LoadedImageName;
#ifdef _WIN64
	System::StaticArray<char, 256> LoadedPdbName;
	unsigned CVSig;
	System::StaticArray<char, 780> CVData;
	unsigned PdbSig;
	GUID PdbSig70;
	unsigned PdbAge;
	System::LongBool PdbUnmatched;
	System::LongBool DbgUnmatched;
	System::LongBool LineNumbers;
	System::LongBool GlobalSymbols;
	System::LongBool TypeInfo;
	System::LongBool SourceIndexed;
	System::LongBool Publics;
#endif /* _WIN64 */
};


struct DECLSPEC_DRECORD _IMAGEHLP_DEFERRED_SYMBOL_LOAD
{
public:
	unsigned SizeOfStruct;
	NativeUInt BaseOfImage;
	unsigned CheckSum;
	unsigned TimeDateStamp;
	System::StaticArray<char, 260> FileName;
	System::LongBool Reparse;
	NativeUInt hFile;
#ifdef _WIN64
	unsigned Flags;
#endif /* _WIN64 */
};


struct DECLSPEC_DRECORD _IMAGEHLP_DUPLICATE_SYMBOL
{
public:
	unsigned SizeOfStruct;
	unsigned NumberOfDups;
	_IMAGEHLP_SYMBOL *Symbol;
	unsigned SelectedSymbol;
};


typedef void * TDigestHandle;

typedef DIGEST_FUNCTION TDigestFunction;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Imagehlp */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_IMAGEHLP)
using namespace Winapi::Imagehlp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_ImagehlpHPP
