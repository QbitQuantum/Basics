// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXFile.pas' rev: 34.00 (Windows)

#ifndef Winapi_DxfileHPP
#define Winapi_DxfileHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "dxfile.h"
#include "rmxfguid.h"
#include "rmxftmpl.h"
typedef System::DelphiInterface<IDirectXFile> _di_IDirectXFile;
typedef System::DelphiInterface<IDirectXFileEnumObject> _di_IDirectXFileEnumObject;
typedef System::DelphiInterface<IDirectXFileSaveObject> _di_IDirectXFileSaveObject;
typedef System::DelphiInterface<IDirectXFileObject> _di_IDirectXFileObject;
typedef System::DelphiInterface<IDirectXFileData> _di_IDirectXFileData;
typedef System::DelphiInterface<IDirectXFileDataReference> _di_IDirectXFileDataReference;
typedef System::DelphiInterface<IDirectXFileBinary> _di_IDirectXFileBinary;

namespace Winapi
{
namespace Dxfile
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned TDXFileFormat;

typedef unsigned TDXFileLoadOptions;

typedef _DXFILELOADRESOURCE *PDXFileLoadResource;

typedef _DXFILELOADRESOURCE TDXFileLoadResource;

typedef _DXFILELOADMEMORY *PDXFileLoadMemory;

typedef _DXFILELOADMEMORY TDXFileLoadMemory;

//-- var, const, procedure ---------------------------------------------------
static const int MAKE_DDHRESULT_D = int(-2005532672);
}	/* namespace Dxfile */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXFILE)
using namespace Winapi::Dxfile;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DxfileHPP
