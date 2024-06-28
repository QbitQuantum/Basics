// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.PhoneDialer.Actions.pas' rev: 34.00 (Windows)

#ifndef Fmx_Phonedialer_ActionsHPP
#define Fmx_Phonedialer_ActionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Actions.hpp>
#include <FMX.Types.hpp>
#include <FMX.PhoneDialer.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.StdActns.hpp>
#include <FMX.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Phonedialer
{
namespace Actions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPhoneCallAction;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPhoneCallAction : public Fmx::Stdactns::TSysCommonAction
{
	typedef Fmx::Stdactns::TSysCommonAction inherited;
	
private:
	Fmx::Phonedialer::_di_IFMXPhoneDialerService FPhoneDialerService;
	System::UnicodeString FTelephoneNumber;
	
protected:
	virtual bool __fastcall IsSupportedInterface();
	
public:
	__fastcall virtual TPhoneCallAction(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TPhoneCallAction();
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property System::UnicodeString TelephoneNumber = {read=FTelephoneNumber, write=FTelephoneNumber};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Actions */
}	/* namespace Phonedialer */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PHONEDIALER_ACTIONS)
using namespace Fmx::Phonedialer::Actions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PHONEDIALER)
using namespace Fmx::Phonedialer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Phonedialer_ActionsHPP
