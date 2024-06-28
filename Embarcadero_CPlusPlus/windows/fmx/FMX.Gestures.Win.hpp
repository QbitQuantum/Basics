// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Gestures.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Gestures_WinHPP
#define Fmx_Gestures_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.MsInkAut.hpp>
#include <Winapi.RtsCom.hpp>
#include <Winapi.TpcShrd.hpp>
#include <Winapi.Windows.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Gestures
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformGestureEngine;
class DELPHICLASS TWinTouchGestureEngine;
class DELPHICLASS TWinGestureEngine;
class DELPHICLASS TGestureRecognizer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPlatformGestureEngine : public Fmx::Gestures::TGestureEngine
{
	typedef Fmx::Gestures::TGestureEngine inherited;
	
private:
	System::Classes::TComponent* FControl;
	static Fmx::Gestures::TGestureEngineClass FDefaultEngineClass;
	
public:
	__classmethod virtual Fmx::Gestures::TCustomGestureRecognizer* __fastcall DoGetRecognizer();
	
private:
	// __classmethod void __fastcall Destroy@();
	// __classmethod void __fastcall Create@();
	
private:
	virtual System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* __fastcall GetGestureList() = 0 ;
	
protected:
	__classmethod virtual Fmx::Gestures::TGestureEngine* __fastcall GetGestureEngine(System::Classes::TComponent* const AControl);
	virtual Fmx::Types::TCustomGestureEngine::TGestureEngineFlags __fastcall GetFlags();
	__property System::Classes::TComponent* Control = {read=FControl};
	
public:
	__classmethod void __fastcall CreateEngine(System::Classes::TComponent* AControl);
	__fastcall virtual TPlatformGestureEngine(System::Classes::TComponent* const AControl);
	/* static */ __property Fmx::Gestures::TGestureEngineClass DefaultEngineClass = {read=FDefaultEngineClass, write=FDefaultEngineClass};
	__property System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* GestureList = {read=GetGestureList};
	__fastcall virtual ~TPlatformGestureEngine();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinTouchGestureEngine : /*[[sealed]]*/ public TPlatformGestureEngine
{
	typedef TPlatformGestureEngine inherited;
	
private:
	static bool FSupported;
	static bool FSupportedTested;
	bool FActive;
	System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* FGestureList;
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(const bool Value);
	virtual System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* __fastcall GetGestureList();
	
public:
	__fastcall virtual TWinTouchGestureEngine(System::Classes::TComponent* const AControl);
	__fastcall virtual ~TWinTouchGestureEngine();
	__classmethod bool __fastcall Supported(System::Classes::TComponent* const AControl = (System::Classes::TComponent*)(0x0));
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinGestureEngine : /*[[sealed]]*/ public TPlatformGestureEngine
{
	typedef TPlatformGestureEngine inherited;
	
	
private:
	class DELPHICLASS TRealTimeStylus;
	class PASCALIMPLEMENTATION TRealTimeStylus : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* FGestureList;
		System::Classes::TComponent* FCurrentControl;
		bool FEnabled;
		_di_IGestureRecognizer FGestureRecognizer;
		HWND FHandle;
		_di_IRealTimeStylus FRealTimeStylus;
		System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* FGestures;
		void __fastcall AddStylusAsyncPlugin(const _di_IStylusAsyncPlugin APlugin);
		void __fastcall AddStylusSyncPlugin(const _di_IStylusSyncPlugin APlugin);
		void __fastcall SetEnabled(const bool Value);
		void __fastcall SetHandle(const HWND Value);
		__classmethod int __fastcall StandardGestureMap(const Fmx::Types::TStandardGesture AGesture);
		__classmethod int __fastcall StylusGestureMap(int AGesture);
		__classmethod System::Classes::TComponent* __fastcall GetControlUnderTouch(const System::Types::TPointF &Value);
		
	public:
		HRESULT __stdcall RealTimeStylusEnabled(_di_IRealTimeStylus piRtsSrc, unsigned cTcidCount, unsigned &pTcids);
		HRESULT __stdcall RealTimeStylusDisabled(_di_IRealTimeStylus piRtsSrc, unsigned cTcidCount, unsigned &pTcids);
		HRESULT __stdcall StylusInRange(_di_IRealTimeStylus piRtsSrc, unsigned tcid, unsigned sid);
		HRESULT __stdcall StylusOutOfRange(_di_IRealTimeStylus piRtsSrc, unsigned tcid, unsigned sid);
		HRESULT __stdcall StylusDown(_di_IRealTimeStylus piRtsSrc, const StylusInfo &pStylusInfo, unsigned cPropCountPerPkt, System::PInteger pPacket, System::PInteger &ppInOutPkt);
		HRESULT __stdcall StylusUp(_di_IRealTimeStylus piRtsSrc, const StylusInfo &pStylusInfo, unsigned cPropCountPerPkt, System::PInteger pPacket, System::PInteger &ppInOutPkt);
		HRESULT __stdcall StylusButtonDown(_di_IRealTimeStylus piRtsSrc, unsigned sid, const GUID &pGuidStylusButton, System::Types::TPoint &pStylusPos);
		HRESULT __stdcall StylusButtonUp(_di_IRealTimeStylus piRtsSrc, unsigned sid, const GUID &pGuidStylusButton, System::Types::TPoint &pStylusPos);
		HRESULT __stdcall InAirPackets(_di_IRealTimeStylus piRtsSrc, const StylusInfo &pStylusInfo, unsigned cPktCount, unsigned cPktBuffLength, System::PInteger pPackets, unsigned &pcInOutPkts, System::PInteger &ppInOutPkts);
		HRESULT __stdcall Packets(_di_IRealTimeStylus piRtsSrc, const StylusInfo &pStylusInfo, unsigned cPktCount, unsigned cPktBuffLength, System::PInteger pPackets, unsigned &pcInOutPkts, System::PInteger &ppInOutPkts);
		HRESULT __stdcall CustomStylusDataAdded(_di_IRealTimeStylus piRtsSrc, const GUID &pGuidId, unsigned cbData, System::PByte pbData);
#ifndef _WIN64
		HRESULT __stdcall SystemEvent(_di_IRealTimeStylus piRtsSrc, unsigned tcid, unsigned sid, System::Word event, SYSTEM_EVENT_DATA eventdata);
#else /* _WIN64 */
		HRESULT __stdcall SystemEvent(_di_IRealTimeStylus piRtsSrc, unsigned tcid, unsigned sid, System::Word event, const SYSTEM_EVENT_DATA &eventdata);
#endif /* _WIN64 */
		HRESULT __stdcall TabletAdded(_di_IRealTimeStylus piRtsSrc, _di_IInkTablet piTablet);
		HRESULT __stdcall TabletRemoved(_di_IRealTimeStylus piRtsSrc, int iTabletIndex);
		HRESULT __stdcall Error(_di_IRealTimeStylus piRtsSrc, _di_IStylusPlugin piPlugin, RealTimeStylusDataInterest dataInterest, HRESULT hrErrorCode, NativeInt &lptrKey);
		HRESULT __stdcall UpdateMapping(_di_IRealTimeStylus piRtsSrc);
		HRESULT __stdcall dataInterest(/* out */ RealTimeStylusDataInterest &pDataInterest);
		__fastcall virtual TRealTimeStylus()/* overload */;
		void __fastcall SetInitialPoint(const System::Types::TPointF &Value);
		__fastcall virtual ~TRealTimeStylus();
		bool __fastcall Initialize();
		bool __fastcall EnableStylus(bool Value, bool Silent);
		void __fastcall Uninitialize();
		System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* __fastcall GetGestureList();
		__property bool Enabled = {read=FEnabled, write=SetEnabled, nodefault};
#ifndef _WIN64
		__property HWND Handle = {read=FHandle, write=SetHandle, nodefault};
#else /* _WIN64 */
		__property HWND Handle = {read=FHandle, write=SetHandle};
#endif /* _WIN64 */
private:
		void *__IStylusAsyncPlugin;	// IStylusAsyncPlugin 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {A7CCA85A-31BC-4CD2-AADC-3289A3AF11C8}
		operator _di_IStylusAsyncPlugin()
		{
			_di_IStylusAsyncPlugin intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator IStylusAsyncPlugin*(void) { return (IStylusAsyncPlugin*)&__IStylusAsyncPlugin; }
		#endif
		
	};
	
	
	
private:
	typedef System::DynamicArray<TRealTimeStylus*> _TWinGestureEngine__1;
	
	
private:
	static System::Generics::Collections::TDictionary__2<void *,void *>* FControlEngineList;
	static void __fastcall RegisterEngineInList(System::Classes::TComponent* const AControl, TPlatformGestureEngine* const AEngine);
	static void __fastcall UnregisterEngineFromList(TPlatformGestureEngine* const AEngine);
	static TPlatformGestureEngine* __fastcall GetEngineFromList(System::Classes::TComponent* const AControl);
	static bool FSupported;
	static bool FSupportedTested;
	_TWinGestureEngine__1 FDeferredCleanupList;
	TRealTimeStylus* FStylusGestureEngine;
	
protected:
	virtual bool __fastcall GetActive();
	virtual void __fastcall SetActive(const bool Value);
	virtual void __fastcall SetInitialPoint(const System::Types::TPointF &Value);
	virtual System::Generics::Collections::TList__1<Fmx::Types::TCustomGestureCollectionItem*>* __fastcall GetGestureList();
	
public:
	__fastcall virtual TWinGestureEngine(System::Classes::TComponent* const AControl);
	__fastcall virtual ~TWinGestureEngine();
	__classmethod bool __fastcall Supported();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TGestureRecognizer : public Fmx::Gestures::TCustomGestureRecognizer
{
	typedef Fmx::Gestures::TCustomGestureRecognizer inherited;
	
	
private:
	typedef void __fastcall (__closure *TPreCallback)(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin);
	
	typedef void __fastcall (__closure *TPostCallback)(const double *Percentages, const int Percentages_High, const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, Fmx::Types::TGestureID GestureID);
	
	typedef int __fastcall (__closure *TGestureFunc)(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin, double *Percentages, const int Percentages_High);
	
	
protected:
	TPreCallback FPreCallback;
	TPostCallback FPostCallback;
	
public:
	virtual float __fastcall Match(const System::Types::TPointF *Points, const int Points_High, const System::Types::TPointF *GesturePoints, const int GesturePoints_High, const Fmx::Types::TGestureOptions Options, Fmx::Types::TGestureID GestureID, int Deviation, int ErrorMargin);
public:
	/* TObject.Create */ inline __fastcall TGestureRecognizer() : Fmx::Gestures::TCustomGestureRecognizer() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGestureRecognizer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Gestures */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES_WIN)
using namespace Fmx::Gestures::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GESTURES)
using namespace Fmx::Gestures;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Gestures_WinHPP
