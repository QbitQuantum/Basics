// ************************************************************************ //
// WARNING                                                                    
// -------                                                                    
// The types declared in this file were generated from data read from a       
// Type Library. If this type library is explicitly or indirectly (via        
// another type library referring to this type library) re-imported, or the   
// 'Refresh' command of the Type Library Editor activated while editing the   
// Type Library, the contents of this file will be regenerated and all        
// manual modifications will be lost.                                         
// ************************************************************************ //

// $Rev: 48729 $
// File generated on 30/04/2012 12:01:57 from Type Library described below.

// ************************************************************************  //
// Type Lib: 2000\MSO9.dll (1)
// LIBID: {2DF8D04C-5BFA-101B-BDE5-00AA0044DE52}
// LCID: 0
// Helpfile: c:\tests\tlibimp\vbaoff9.chm 
// HelpString: Microsoft Office 9.0 Object Library
// DepndLst: 
//   (1) v2.0 stdole, (C:\Windows\SysWOW64\stdole2.tlb)
// SYS_KIND: SYS_WIN32
// Cmdline:
//   tlibimp  -C+ -Fe_2K -CE_2K_SRVR -Ha- -Hr+ -HpsOffice2K -Yp+ -D.\cpp2k -Cv-  -Hs- -Ha- 2000\MSO9.dll
// ************************************************************************ //
#ifndef   Office_2K_SRVRH
#define   Office_2K_SRVRH

#pragma option push -b -a4 -w-inl -w-8118

#if !defined(__UTILCLS_H)
#include <utilcls.h>
#endif
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0700)
//
// The code generated by the TLIBIMP utility or the Import|TypeLibrary 
// and Import|ActiveX feature of C++Builder rely on specific versions of
// the header file UTILCLS.H found in the INCLUDE\VCL directory. If an 
// older version of the file is detected, you probably need an update/patch.
//
#error "This file requires a newer version of the header UTILCLS.H" \
       "You need to apply an update/patch to your copy of C++Builder"
#endif
#include <olectl.h>
#include <ocidl.h>
#if !defined(_NO_VCL)
#include <System.Win.StdVCL.hpp>
#endif  //   _NO_VCL
#include <ocxproxy.h>

#include "Office_2K.h"
namespace Office_2k
{

// *********************************************************************//
// HelpString: Microsoft Office 9.0 Object Library
// Version:    2.1
// *********************************************************************//

// SKIPPING COCLASS: CommandBars          - Configured to skip Servers
// SKIPPING COCLASS: CommandBarComboBox   - Configured to skip Servers
// SKIPPING COCLASS: CommandBarButton     - Configured to skip Servers
};     // namespace Office_2k

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Office_2k;
#endif

#pragma option pop

#endif // Office_2K_SRVRH
