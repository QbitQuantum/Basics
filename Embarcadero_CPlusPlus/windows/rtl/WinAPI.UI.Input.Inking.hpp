// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UI.Input.Inking.pas' rev: 34.00 (Windows)

#ifndef Winapi_Ui_Input_InkingHPP
#define Winapi_Ui_Input_InkingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.Foundation.Types.hpp>
#include <Winapi.Foundation.hpp>
#include <Winapi.Devices.hpp>
#include <Winapi.UI.Composition.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Ui
{
namespace Input
{
namespace Inking
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IIterator_1__IInkStrokeRenderingSegment_Base;
typedef System::DelphiInterface<IIterator_1__IInkStrokeRenderingSegment_Base> _di_IIterator_1__IInkStrokeRenderingSegment_Base;
__interface DELPHIINTERFACE IIterator_1__IInkStrokeRenderingSegment;
typedef System::DelphiInterface<IIterator_1__IInkStrokeRenderingSegment> _di_IIterator_1__IInkStrokeRenderingSegment;
__interface DELPHIINTERFACE IIterable_1__IInkStrokeRenderingSegment_Base;
typedef System::DelphiInterface<IIterable_1__IInkStrokeRenderingSegment_Base> _di_IIterable_1__IInkStrokeRenderingSegment_Base;
__interface DELPHIINTERFACE IIterable_1__IInkStrokeRenderingSegment;
typedef System::DelphiInterface<IIterable_1__IInkStrokeRenderingSegment> _di_IIterable_1__IInkStrokeRenderingSegment;
__interface DELPHIINTERFACE IIterator_1__IInkStroke_Base;
typedef System::DelphiInterface<IIterator_1__IInkStroke_Base> _di_IIterator_1__IInkStroke_Base;
__interface DELPHIINTERFACE IIterator_1__IInkStroke;
typedef System::DelphiInterface<IIterator_1__IInkStroke> _di_IIterator_1__IInkStroke;
__interface DELPHIINTERFACE IIterable_1__IInkStroke_Base;
typedef System::DelphiInterface<IIterable_1__IInkStroke_Base> _di_IIterable_1__IInkStroke_Base;
__interface DELPHIINTERFACE IIterable_1__IInkStroke;
typedef System::DelphiInterface<IIterable_1__IInkStroke> _di_IIterable_1__IInkStroke;
__interface DELPHIINTERFACE IIterator_1__IInkRecognitionResult_Base;
typedef System::DelphiInterface<IIterator_1__IInkRecognitionResult_Base> _di_IIterator_1__IInkRecognitionResult_Base;
__interface DELPHIINTERFACE IIterator_1__IInkRecognitionResult;
typedef System::DelphiInterface<IIterator_1__IInkRecognitionResult> _di_IIterator_1__IInkRecognitionResult;
__interface DELPHIINTERFACE IIterable_1__IInkRecognitionResult_Base;
typedef System::DelphiInterface<IIterable_1__IInkRecognitionResult_Base> _di_IIterable_1__IInkRecognitionResult_Base;
__interface DELPHIINTERFACE IIterable_1__IInkRecognitionResult;
typedef System::DelphiInterface<IIterable_1__IInkRecognitionResult> _di_IIterable_1__IInkRecognitionResult;
__interface DELPHIINTERFACE IInkPresenterStencil;
typedef System::DelphiInterface<IInkPresenterStencil> _di_IInkPresenterStencil;
__interface DELPHIINTERFACE IInkPresenterRuler;
typedef System::DelphiInterface<IInkPresenterRuler> _di_IInkPresenterRuler;
__interface DELPHIINTERFACE IInkPresenterProtractor;
typedef System::DelphiInterface<IInkPresenterProtractor> _di_IInkPresenterProtractor;
__interface DELPHIINTERFACE IIterator_1__Analysis_IInkAnalysisNode_Base;
typedef System::DelphiInterface<IIterator_1__Analysis_IInkAnalysisNode_Base> _di_IIterator_1__Analysis_IInkAnalysisNode_Base;
__interface DELPHIINTERFACE IIterator_1__Analysis_IInkAnalysisNode;
typedef System::DelphiInterface<IIterator_1__Analysis_IInkAnalysisNode> _di_IIterator_1__Analysis_IInkAnalysisNode;
__interface DELPHIINTERFACE IIterable_1__Analysis_IInkAnalysisNode_Base;
typedef System::DelphiInterface<IIterable_1__Analysis_IInkAnalysisNode_Base> _di_IIterable_1__Analysis_IInkAnalysisNode_Base;
__interface DELPHIINTERFACE IIterable_1__Analysis_IInkAnalysisNode;
typedef System::DelphiInterface<IIterable_1__Analysis_IInkAnalysisNode> _di_IIterable_1__Analysis_IInkAnalysisNode;
__interface DELPHIINTERFACE IVectorView_1__Analysis_IInkAnalysisNode;
typedef System::DelphiInterface<IVectorView_1__Analysis_IInkAnalysisNode> _di_IVectorView_1__Analysis_IInkAnalysisNode;
__interface DELPHIINTERFACE Analysis_IInkAnalysisNode;
typedef System::DelphiInterface<Analysis_IInkAnalysisNode> _di_Analysis_IInkAnalysisNode;
__interface DELPHIINTERFACE Analysis_IInkAnalysisRoot;
typedef System::DelphiInterface<Analysis_IInkAnalysisRoot> _di_Analysis_IInkAnalysisRoot;
__interface DELPHIINTERFACE Analysis_IInkAnalysisResult;
typedef System::DelphiInterface<Analysis_IInkAnalysisResult> _di_Analysis_IInkAnalysisResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult> _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult;
__interface DELPHIINTERFACE IAsyncOperation_1__Analysis_IInkAnalysisResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__Analysis_IInkAnalysisResult_Base> _di_IAsyncOperation_1__Analysis_IInkAnalysisResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__Analysis_IInkAnalysisResult;
typedef System::DelphiInterface<IAsyncOperation_1__Analysis_IInkAnalysisResult> _di_IAsyncOperation_1__Analysis_IInkAnalysisResult;
__interface DELPHIINTERFACE Analysis_IInkAnalyzer;
typedef System::DelphiInterface<Analysis_IInkAnalyzer> _di_Analysis_IInkAnalyzer;
__interface DELPHIINTERFACE Analysis_IInkAnalyzerFactory;
typedef System::DelphiInterface<Analysis_IInkAnalyzerFactory> _di_Analysis_IInkAnalyzerFactory;
__interface DELPHIINTERFACE Analysis_IInkAnalysisWritingRegion;
typedef System::DelphiInterface<Analysis_IInkAnalysisWritingRegion> _di_Analysis_IInkAnalysisWritingRegion;
__interface DELPHIINTERFACE Analysis_IInkAnalysisParagraph;
typedef System::DelphiInterface<Analysis_IInkAnalysisParagraph> _di_Analysis_IInkAnalysisParagraph;
__interface DELPHIINTERFACE Analysis_IInkAnalysisListItem;
typedef System::DelphiInterface<Analysis_IInkAnalysisListItem> _di_Analysis_IInkAnalysisListItem;
__interface DELPHIINTERFACE Analysis_IInkAnalysisInkBullet;
typedef System::DelphiInterface<Analysis_IInkAnalysisInkBullet> _di_Analysis_IInkAnalysisInkBullet;
__interface DELPHIINTERFACE Analysis_IInkAnalysisLine;
typedef System::DelphiInterface<Analysis_IInkAnalysisLine> _di_Analysis_IInkAnalysisLine;
__interface DELPHIINTERFACE Analysis_IInkAnalysisInkWord;
typedef System::DelphiInterface<Analysis_IInkAnalysisInkWord> _di_Analysis_IInkAnalysisInkWord;
__interface DELPHIINTERFACE Analysis_IInkAnalysisInkDrawing;
typedef System::DelphiInterface<Analysis_IInkAnalysisInkDrawing> _di_Analysis_IInkAnalysisInkDrawing;
__interface DELPHIINTERFACE IInkPresenter2;
typedef System::DelphiInterface<IInkPresenter2> _di_IInkPresenter2;
__interface DELPHIINTERFACE IInkPresenterRuler2;
typedef System::DelphiInterface<IInkPresenterRuler2> _di_IInkPresenterRuler2;
__interface DELPHIINTERFACE IInkPresenterRulerFactory;
typedef System::DelphiInterface<IInkPresenterRulerFactory> _di_IInkPresenterRulerFactory;
__interface DELPHIINTERFACE IInkPresenterProtractorFactory;
typedef System::DelphiInterface<IInkPresenterProtractorFactory> _di_IInkPresenterProtractorFactory;
__interface DELPHIINTERFACE Core_ICoreInkIndependentInputSourceStatics;
typedef System::DelphiInterface<Core_ICoreInkIndependentInputSourceStatics> _di_Core_ICoreInkIndependentInputSourceStatics;
__interface DELPHIINTERFACE IInkPoint;
typedef System::DelphiInterface<IInkPoint> _di_IInkPoint;
__interface DELPHIINTERFACE IIterator_1__IInkPoint_Base;
typedef System::DelphiInterface<IIterator_1__IInkPoint_Base> _di_IIterator_1__IInkPoint_Base;
__interface DELPHIINTERFACE IIterator_1__IInkPoint;
typedef System::DelphiInterface<IIterator_1__IInkPoint> _di_IIterator_1__IInkPoint;
__interface DELPHIINTERFACE IIterable_1__IInkPoint_Base;
typedef System::DelphiInterface<IIterable_1__IInkPoint_Base> _di_IIterable_1__IInkPoint_Base;
__interface DELPHIINTERFACE IIterable_1__IInkPoint;
typedef System::DelphiInterface<IIterable_1__IInkPoint> _di_IIterable_1__IInkPoint;
__interface DELPHIINTERFACE IVectorView_1__IInkPoint;
typedef System::DelphiInterface<IVectorView_1__IInkPoint> _di_IVectorView_1__IInkPoint;
__interface DELPHIINTERFACE IVector_1__IInkPoint;
typedef System::DelphiInterface<IVector_1__IInkPoint> _di_IVector_1__IInkPoint;
__interface DELPHIINTERFACE Core_ICoreWetStrokeUpdateEventArgs;
typedef System::DelphiInterface<Core_ICoreWetStrokeUpdateEventArgs> _di_Core_ICoreWetStrokeUpdateEventArgs;
__interface DELPHIINTERFACE TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs_Delegate_Base;
typedef System::DelphiInterface<TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs_Delegate_Base> _di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs_Delegate_Base;
__interface DELPHIINTERFACE TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs;
typedef System::DelphiInterface<TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs> _di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs;
__interface DELPHIINTERFACE Core_ICoreWetStrokeUpdateSource;
typedef System::DelphiInterface<Core_ICoreWetStrokeUpdateSource> _di_Core_ICoreWetStrokeUpdateSource;
__interface DELPHIINTERFACE Core_ICoreWetStrokeUpdateSourceStatics;
typedef System::DelphiInterface<Core_ICoreWetStrokeUpdateSourceStatics> _di_Core_ICoreWetStrokeUpdateSourceStatics;
__interface DELPHIINTERFACE Core_ICoreInkPresenterHost;
typedef System::DelphiInterface<Core_ICoreInkPresenterHost> _di_Core_ICoreInkPresenterHost;
__interface DELPHIINTERFACE IInkPoint2;
typedef System::DelphiInterface<IInkPoint2> _di_IInkPoint2;
__interface DELPHIINTERFACE IInkPointFactory;
typedef System::DelphiInterface<IInkPointFactory> _di_IInkPointFactory;
__interface DELPHIINTERFACE IInkPointFactory2;
typedef System::DelphiInterface<IInkPointFactory2> _di_IInkPointFactory2;
__interface DELPHIINTERFACE IInkDrawingAttributes2;
typedef System::DelphiInterface<IInkDrawingAttributes2> _di_IInkDrawingAttributes2;
__interface DELPHIINTERFACE IInkDrawingAttributesPencilProperties;
typedef System::DelphiInterface<IInkDrawingAttributesPencilProperties> _di_IInkDrawingAttributesPencilProperties;
__interface DELPHIINTERFACE IInkDrawingAttributes3;
typedef System::DelphiInterface<IInkDrawingAttributes3> _di_IInkDrawingAttributes3;
__interface DELPHIINTERFACE IInkDrawingAttributes4;
typedef System::DelphiInterface<IInkDrawingAttributes4> _di_IInkDrawingAttributes4;
__interface DELPHIINTERFACE IInkDrawingAttributesStatics;
typedef System::DelphiInterface<IInkDrawingAttributesStatics> _di_IInkDrawingAttributesStatics;
__interface DELPHIINTERFACE IInkStroke2;
typedef System::DelphiInterface<IInkStroke2> _di_IInkStroke2;
__interface DELPHIINTERFACE IInkStroke3;
typedef System::DelphiInterface<IInkStroke3> _di_IInkStroke3;
__interface DELPHIINTERFACE IInkStrokeBuilder;
typedef System::DelphiInterface<IInkStrokeBuilder> _di_IInkStrokeBuilder;
__interface DELPHIINTERFACE IInkStrokeBuilder2;
typedef System::DelphiInterface<IInkStrokeBuilder2> _di_IInkStrokeBuilder2;
__interface DELPHIINTERFACE IInkStrokeBuilder3;
typedef System::DelphiInterface<IInkStrokeBuilder3> _di_IInkStrokeBuilder3;
__interface DELPHIINTERFACE IInkStrokeContainer2;
typedef System::DelphiInterface<IInkStrokeContainer2> _di_IInkStrokeContainer2;
__interface DELPHIINTERFACE IInkStrokeContainer3;
typedef System::DelphiInterface<IInkStrokeContainer3> _di_IInkStrokeContainer3;
__interface DELPHIINTERFACE IInkRecognizer;
typedef System::DelphiInterface<IInkRecognizer> _di_IInkRecognizer;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IInkRecognitionResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IInkRecognitionResult_Base> _di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IInkRecognitionResult;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IInkRecognitionResult> _di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult;
__interface DELPHIINTERFACE IIterator_1__IInkRecognizer_Base;
typedef System::DelphiInterface<IIterator_1__IInkRecognizer_Base> _di_IIterator_1__IInkRecognizer_Base;
__interface DELPHIINTERFACE IIterator_1__IInkRecognizer;
typedef System::DelphiInterface<IIterator_1__IInkRecognizer> _di_IIterator_1__IInkRecognizer;
__interface DELPHIINTERFACE IIterable_1__IInkRecognizer_Base;
typedef System::DelphiInterface<IIterable_1__IInkRecognizer_Base> _di_IIterable_1__IInkRecognizer_Base;
__interface DELPHIINTERFACE IIterable_1__IInkRecognizer;
typedef System::DelphiInterface<IIterable_1__IInkRecognizer> _di_IIterable_1__IInkRecognizer;
__interface DELPHIINTERFACE IVectorView_1__IInkRecognizer;
typedef System::DelphiInterface<IVectorView_1__IInkRecognizer> _di_IVectorView_1__IInkRecognizer;
__interface DELPHIINTERFACE IInkRecognizerContainer;
typedef System::DelphiInterface<IInkRecognizerContainer> _di_IInkRecognizerContainer;
__interface DELPHIINTERFACE IInkManager;
typedef System::DelphiInterface<IInkManager> _di_IInkManager;
__interface DELPHIINTERFACE Core_ICoreIncrementalInkStroke;
typedef System::DelphiInterface<Core_ICoreIncrementalInkStroke> _di_Core_ICoreIncrementalInkStroke;
__interface DELPHIINTERFACE Core_ICoreIncrementalInkStrokeFactory;
typedef System::DelphiInterface<Core_ICoreIncrementalInkStrokeFactory> _di_Core_ICoreIncrementalInkStrokeFactory;
class DELPHICLASS TAnalysis_InkAnalyzer;
class DELPHICLASS TInkPresenterRuler;
class DELPHICLASS TInkPresenterProtractor;
class DELPHICLASS TCore_CoreInkIndependentInputSource;
class DELPHICLASS TCore_CoreWetStrokeUpdateSource;
class DELPHICLASS TCore_CoreInkPresenterHost;
class DELPHICLASS TInkPoint;
class DELPHICLASS TInkDrawingAttributes;
class DELPHICLASS TInkStrokeBuilder;
class DELPHICLASS TInkStrokeContainer;
class DELPHICLASS TInkRecognizerContainer;
class DELPHICLASS TInkManager;
class DELPHICLASS TCore_CoreIncrementalInkStroke;
//-- type declarations -------------------------------------------------------
typedef _di_IIterator_1__IInkStrokeRenderingSegment *PIIterator_1__IInkStrokeRenderingSegment;

typedef _di_IIterable_1__IInkStrokeRenderingSegment *PIIterable_1__IInkStrokeRenderingSegment;

typedef _di_IIterator_1__IInkStroke *PIIterator_1__IInkStroke;

typedef _di_IIterable_1__IInkStroke *PIIterable_1__IInkStroke;

typedef _di_IIterator_1__IInkRecognitionResult *PIIterator_1__IInkRecognitionResult;

typedef _di_IIterable_1__IInkRecognitionResult *PIIterable_1__IInkRecognitionResult;

typedef _di_IInkPresenterStencil *PIInkPresenterStencil;

typedef _di_IInkPresenterRuler *PIInkPresenterRuler;

typedef _di_IInkPresenterProtractor *PIInkPresenterProtractor;

typedef _di_IIterator_1__Analysis_IInkAnalysisNode *PIIterator_1__Analysis_IInkAnalysisNode;

typedef _di_IIterable_1__Analysis_IInkAnalysisNode *PIIterable_1__Analysis_IInkAnalysisNode;

typedef _di_IVectorView_1__Analysis_IInkAnalysisNode *PIVectorView_1__Analysis_IInkAnalysisNode;

typedef _di_Analysis_IInkAnalysisNode *PAnalysis_IInkAnalysisNode;

typedef _di_Analysis_IInkAnalysisRoot *PAnalysis_IInkAnalysisRoot;

typedef _di_Analysis_IInkAnalysisResult *PAnalysis_IInkAnalysisResult;

typedef _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult *PAsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult;

typedef _di_IAsyncOperation_1__Analysis_IInkAnalysisResult *PIAsyncOperation_1__Analysis_IInkAnalysisResult;

typedef _di_Analysis_IInkAnalyzer *PAnalysis_IInkAnalyzer;

typedef _di_Analysis_IInkAnalyzerFactory *PAnalysis_IInkAnalyzerFactory;

typedef _di_Analysis_IInkAnalysisWritingRegion *PAnalysis_IInkAnalysisWritingRegion;

typedef _di_Analysis_IInkAnalysisParagraph *PAnalysis_IInkAnalysisParagraph;

typedef _di_Analysis_IInkAnalysisListItem *PAnalysis_IInkAnalysisListItem;

typedef _di_Analysis_IInkAnalysisInkBullet *PAnalysis_IInkAnalysisInkBullet;

typedef _di_Analysis_IInkAnalysisLine *PAnalysis_IInkAnalysisLine;

typedef _di_Analysis_IInkAnalysisInkWord *PAnalysis_IInkAnalysisInkWord;

typedef _di_Analysis_IInkAnalysisInkDrawing *PAnalysis_IInkAnalysisInkDrawing;

typedef _di_IInkPresenter2 *PIInkPresenter2;

typedef _di_IInkPresenterRuler2 *PIInkPresenterRuler2;

typedef _di_IInkPresenterRulerFactory *PIInkPresenterRulerFactory;

typedef _di_IInkPresenterProtractorFactory *PIInkPresenterProtractorFactory;

typedef _di_Core_ICoreInkIndependentInputSourceStatics *PCore_ICoreInkIndependentInputSourceStatics;

typedef _di_IInkPoint *PIInkPoint;

typedef _di_IIterator_1__IInkPoint *PIIterator_1__IInkPoint;

typedef _di_IIterable_1__IInkPoint *PIIterable_1__IInkPoint;

typedef _di_IVectorView_1__IInkPoint *PIVectorView_1__IInkPoint;

typedef _di_IVector_1__IInkPoint *PIVector_1__IInkPoint;

typedef _di_Core_ICoreWetStrokeUpdateEventArgs *PCore_ICoreWetStrokeUpdateEventArgs;

typedef _di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs *PTypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs;

typedef _di_Core_ICoreWetStrokeUpdateSource *PCore_ICoreWetStrokeUpdateSource;

typedef _di_Core_ICoreWetStrokeUpdateSourceStatics *PCore_ICoreWetStrokeUpdateSourceStatics;

typedef _di_Core_ICoreInkPresenterHost *PCore_ICoreInkPresenterHost;

typedef _di_IInkPoint2 *PIInkPoint2;

typedef _di_IInkPointFactory *PIInkPointFactory;

typedef _di_IInkPointFactory2 *PIInkPointFactory2;

typedef _di_IInkDrawingAttributes2 *PIInkDrawingAttributes2;

typedef _di_IInkDrawingAttributesPencilProperties *PIInkDrawingAttributesPencilProperties;

typedef _di_IInkDrawingAttributes3 *PIInkDrawingAttributes3;

typedef _di_IInkDrawingAttributes4 *PIInkDrawingAttributes4;

typedef _di_IInkDrawingAttributesStatics *PIInkDrawingAttributesStatics;

typedef _di_IInkStroke2 *PIInkStroke2;

typedef _di_IInkStroke3 *PIInkStroke3;

typedef _di_IInkStrokeBuilder *PIInkStrokeBuilder;

typedef _di_IInkStrokeBuilder2 *PIInkStrokeBuilder2;

typedef _di_IInkStrokeBuilder3 *PIInkStrokeBuilder3;

typedef _di_IInkStrokeContainer2 *PIInkStrokeContainer2;

typedef _di_IInkStrokeContainer3 *PIInkStrokeContainer3;

typedef _di_IInkRecognizer *PIInkRecognizer;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult *PAsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult;

typedef _di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult *PIAsyncOperation_1__IVectorView_1__IInkRecognitionResult;

typedef _di_IIterator_1__IInkRecognizer *PIIterator_1__IInkRecognizer;

typedef _di_IIterable_1__IInkRecognizer *PIIterable_1__IInkRecognizer;

typedef _di_IVectorView_1__IInkRecognizer *PIVectorView_1__IInkRecognizer;

typedef _di_IInkRecognizerContainer *PIInkRecognizerContainer;

typedef _di_IInkManager *PIInkManager;

typedef _di_Core_ICoreIncrementalInkStroke *PCore_ICoreIncrementalInkStroke;

typedef _di_Core_ICoreIncrementalInkStrokeFactory *PCore_ICoreIncrementalInkStrokeFactory;

__interface  INTERFACE_UUID("{D7D8C317-6F3F-5192-9210-65A263BAF8D1}") IIterator_1__IInkStrokeRenderingSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4C6160CF-7BA6-560A-B27C-80F5E4F7FDF5}") IIterator_1__IInkStrokeRenderingSegment  : public IIterator_1__IInkStrokeRenderingSegment_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IInkStrokeRenderingSegment &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIInkStrokeRenderingSegment items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkStrokeRenderingSegment _scw_get_Current() { Winapi::Commontypes::_di_IInkStrokeRenderingSegment __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkStrokeRenderingSegment Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{27000F47-2885-5DA9-8923-16A3A58B7A55}") IIterable_1__IInkStrokeRenderingSegment_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{8257ED76-E624-53F9-A263-989CE2165CBD}") IIterable_1__IInkStrokeRenderingSegment  : public IIterable_1__IInkStrokeRenderingSegment_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IInkStrokeRenderingSegment &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{5608D5A9-E7E4-5A0B-941F-B7FED76B35BF}") IIterator_1__IInkStroke_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{290D40AA-369B-5B43-89AB-EB478BF8E02E}") IIterator_1__IInkStroke  : public IIterator_1__IInkStroke_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IInkStroke &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIInkStroke items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkStroke _scw_get_Current() { Winapi::Commontypes::_di_IInkStroke __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkStroke Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{BBC11401-89D0-5305-A3B3-36C887714B9B}") IIterable_1__IInkStroke_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{D85C9152-A2E8-5C08-AD59-D32E7631674F}") IIterable_1__IInkStroke  : public IIterable_1__IInkStroke_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IInkStroke &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{9ABC247F-0223-5F44-8FA1-0D6D691BF9AF}") IIterator_1__IInkRecognitionResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{666B7A6D-1A5C-5075-8320-52A4D5F5727A}") IIterator_1__IInkRecognitionResult  : public IIterator_1__IInkRecognitionResult_Base 
{
	virtual HRESULT __safecall get_Current(Winapi::Commontypes::_di_IInkRecognitionResult &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, Winapi::Commontypes::PIInkRecognitionResult items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkRecognitionResult _scw_get_Current() { Winapi::Commontypes::_di_IInkRecognitionResult __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkRecognitionResult Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{E29B658B-7CC1-561C-9912-001DBCA86651}") IIterable_1__IInkRecognitionResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{146806FB-6B02-587F-9054-0F8C7AFD57BC}") IIterable_1__IInkRecognitionResult  : public IIterable_1__IInkRecognitionResult_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IInkRecognitionResult &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{30D12D6D-3E06-4D02-B116-277FB5D8ADDC}") IInkPresenterStencil  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Kind(Winapi::Commontypes::InkPresenterStencilKind &__get_Kind_result) = 0 ;
	virtual HRESULT __safecall get_IsVisible(bool &__get_IsVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_BackgroundColor(Winapi::Commontypes::Color &__get_BackgroundColor_result) = 0 ;
	virtual HRESULT __safecall put_BackgroundColor(Winapi::Commontypes::Color value) = 0 ;
	virtual HRESULT __safecall get_ForegroundColor(Winapi::Commontypes::Color &__get_ForegroundColor_result) = 0 ;
	virtual HRESULT __safecall put_ForegroundColor(Winapi::Commontypes::Color value) = 0 ;
	virtual HRESULT __safecall get_Transform(Winapi::Foundation::Types::Numerics_Matrix3x2 &__get_Transform_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_Transform(Winapi::Foundation::Types::Numerics_Matrix3x2 value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_Transform(const Winapi::Foundation::Types::Numerics_Matrix3x2 &value) = 0 ;
#endif /* _WIN64 */
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_BackgroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_BackgroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color BackgroundColor = {read=_scw_get_BackgroundColor, write=put_BackgroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_ForegroundColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_ForegroundColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color ForegroundColor = {read=_scw_get_ForegroundColor, write=put_ForegroundColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsVisible() { bool __r; HRESULT __hr = get_IsVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsVisible = {read=_scw_get_IsVisible, write=put_IsVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::InkPresenterStencilKind _scw_get_Kind() { Winapi::Commontypes::InkPresenterStencilKind __r; HRESULT __hr = get_Kind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::InkPresenterStencilKind Kind = {read=_scw_get_Kind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Matrix3x2 _scw_get_Transform() { Winapi::Foundation::Types::Numerics_Matrix3x2 __r; HRESULT __hr = get_Transform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Matrix3x2 Transform = {read=_scw_get_Transform, write=put_Transform};
};

__interface  INTERFACE_UUID("{6CDA7D5A-DEC7-4DD7-877A-2133F183D48A}") IInkPresenterRuler  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Length(double &__get_Length_result) = 0 ;
	virtual HRESULT __safecall put_Length(double value) = 0 ;
	virtual HRESULT __safecall get_Width(double &__get_Width_result) = 0 ;
	virtual HRESULT __safecall put_Width(double value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Length() { double __r; HRESULT __hr = get_Length(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Length = {read=_scw_get_Length, write=put_Length};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Width() { double __r; HRESULT __hr = get_Width(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Width = {read=_scw_get_Width, write=put_Width};
};

__interface  INTERFACE_UUID("{7DE3F2AA-EF6C-4E91-A73B-5B70D56FBD17}") IInkPresenterProtractor  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AreTickMarksVisible(bool &__get_AreTickMarksVisible_result) = 0 ;
	virtual HRESULT __safecall put_AreTickMarksVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_AreRaysVisible(bool &__get_AreRaysVisible_result) = 0 ;
	virtual HRESULT __safecall put_AreRaysVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_IsCenterMarkerVisible(bool &__get_IsCenterMarkerVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsCenterMarkerVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_IsAngleReadoutVisible(bool &__get_IsAngleReadoutVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsAngleReadoutVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_IsResizable(bool &__get_IsResizable_result) = 0 ;
	virtual HRESULT __safecall put_IsResizable(bool value) = 0 ;
	virtual HRESULT __safecall get_Radius(double &__get_Radius_result) = 0 ;
	virtual HRESULT __safecall put_Radius(double value) = 0 ;
	virtual HRESULT __safecall get_AccentColor(Winapi::Commontypes::Color &__get_AccentColor_result) = 0 ;
	virtual HRESULT __safecall put_AccentColor(Winapi::Commontypes::Color value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Color _scw_get_AccentColor() { Winapi::Commontypes::Color __r; HRESULT __hr = get_AccentColor(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Color AccentColor = {read=_scw_get_AccentColor, write=put_AccentColor};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AreRaysVisible() { bool __r; HRESULT __hr = get_AreRaysVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AreRaysVisible = {read=_scw_get_AreRaysVisible, write=put_AreRaysVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AreTickMarksVisible() { bool __r; HRESULT __hr = get_AreTickMarksVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AreTickMarksVisible = {read=_scw_get_AreTickMarksVisible, write=put_AreTickMarksVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsAngleReadoutVisible() { bool __r; HRESULT __hr = get_IsAngleReadoutVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsAngleReadoutVisible = {read=_scw_get_IsAngleReadoutVisible, write=put_IsAngleReadoutVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCenterMarkerVisible() { bool __r; HRESULT __hr = get_IsCenterMarkerVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCenterMarkerVisible = {read=_scw_get_IsCenterMarkerVisible, write=put_IsCenterMarkerVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsResizable() { bool __r; HRESULT __hr = get_IsResizable(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsResizable = {read=_scw_get_IsResizable, write=put_IsResizable};
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Radius() { double __r; HRESULT __hr = get_Radius(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Radius = {read=_scw_get_Radius, write=put_Radius};
};

__interface  INTERFACE_UUID("{AD35ED5C-5F8C-5A68-A6E1-67F209A05EA7}") IIterator_1__Analysis_IInkAnalysisNode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{AD35ED5C-5F8C-5A68-A6E1-67F209A05EA7}") IIterator_1__Analysis_IInkAnalysisNode  : public IIterator_1__Analysis_IInkAnalysisNode_Base 
{
	virtual HRESULT __safecall get_Current(_di_Analysis_IInkAnalysisNode &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PAnalysis_IInkAnalysisNode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Analysis_IInkAnalysisNode _scw_get_Current() { _di_Analysis_IInkAnalysisNode __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Analysis_IInkAnalysisNode Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{784F069E-BADD-5258-BD8F-42CE205CC95A}") IIterable_1__Analysis_IInkAnalysisNode_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{784F069E-BADD-5258-BD8F-42CE205CC95A}") IIterable_1__Analysis_IInkAnalysisNode  : public IIterable_1__Analysis_IInkAnalysisNode_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__Analysis_IInkAnalysisNode &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{2B3FEE11-53B5-55B0-8D71-C40B427DE029}") IVectorView_1__Analysis_IInkAnalysisNode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_Analysis_IInkAnalysisNode &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_Analysis_IInkAnalysisNode value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PAnalysis_IInkAnalysisNode items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{30831F05-5F64-4A2C-BA37-4F4887879574}") Analysis_IInkAnalysisNode  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(unsigned &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_Kind(Winapi::Commontypes::Analysis_InkAnalysisNodeKind &__get_Kind_result) = 0 ;
	virtual HRESULT __safecall get_BoundingRect(System::Types::TRectF &__get_BoundingRect_result) = 0 ;
	virtual HRESULT __safecall get_RotatedBoundingRect(Winapi::Foundation::_di_IVectorView_1__Point &__get_RotatedBoundingRect_result) = 0 ;
	virtual HRESULT __safecall get_Children(_di_IVectorView_1__Analysis_IInkAnalysisNode &__get_Children_result) = 0 ;
	virtual HRESULT __safecall get_Parent(_di_Analysis_IInkAnalysisNode &__get_Parent_result) = 0 ;
	virtual HRESULT __safecall GetStrokeIds(Winapi::Commontypes::_di_IVectorView_1__Cardinal &__GetStrokeIds_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_BoundingRect() { System::Types::TRectF __r; HRESULT __hr = get_BoundingRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF BoundingRect = {read=_scw_get_BoundingRect};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVectorView_1__Analysis_IInkAnalysisNode _scw_get_Children() { _di_IVectorView_1__Analysis_IInkAnalysisNode __r; HRESULT __hr = get_Children(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVectorView_1__Analysis_IInkAnalysisNode Children = {read=_scw_get_Children};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Id() { unsigned __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Analysis_InkAnalysisNodeKind _scw_get_Kind() { Winapi::Commontypes::Analysis_InkAnalysisNodeKind __r; HRESULT __hr = get_Kind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Analysis_InkAnalysisNodeKind Kind = {read=_scw_get_Kind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Analysis_IInkAnalysisNode _scw_get_Parent() { _di_Analysis_IInkAnalysisNode __r; HRESULT __hr = get_Parent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Analysis_IInkAnalysisNode Parent = {read=_scw_get_Parent};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::_di_IVectorView_1__Point _scw_get_RotatedBoundingRect() { Winapi::Foundation::_di_IVectorView_1__Point __r; HRESULT __hr = get_RotatedBoundingRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::_di_IVectorView_1__Point RotatedBoundingRect = {read=_scw_get_RotatedBoundingRect};
};

__interface  INTERFACE_UUID("{3FB6A3C4-2FDE-4061-8502-A90F32545B84}") Analysis_IInkAnalysisRoot  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	virtual HRESULT __safecall FindNodes(Winapi::Commontypes::Analysis_InkAnalysisNodeKind nodeKind, _di_IVectorView_1__Analysis_IInkAnalysisNode &__FindNodes_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{8948BA79-A243-4AA3-A294-1F98BD0FF580}") Analysis_IInkAnalysisResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::Analysis_InkAnalysisStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Analysis_InkAnalysisStatus _scw_get_Status() { Winapi::Commontypes::Analysis_InkAnalysisStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Analysis_InkAnalysisStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{A7EF2666-6FC4-568F-BBF3-19C1036A26BF}") AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{C89B2AB8-C6A2-559E-B5C5-FD5BBC9F7F29}") AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult  : public AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__Analysis_IInkAnalysisResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{2C46D1BD-6DBB-5007-BA85-3D0106BDDF50}") IAsyncOperation_1__Analysis_IInkAnalysisResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{E0B82816-9C19-5B96-8D45-EA09933B5E33}") IAsyncOperation_1__Analysis_IInkAnalysisResult  : public IAsyncOperation_1__Analysis_IInkAnalysisResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_Analysis_IInkAnalysisResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__Analysis_IInkAnalysisResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{F12B8F95-0866-4DC5-8C77-F88614DFE38C}") Analysis_IInkAnalyzer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AnalysisRoot(_di_Analysis_IInkAnalysisRoot &__get_AnalysisRoot_result) = 0 ;
	virtual HRESULT __safecall get_IsAnalyzing(bool &__get_IsAnalyzing_result) = 0 ;
	virtual HRESULT __safecall AddDataForStroke(Winapi::Commontypes::_di_IInkStroke stroke) = 0 ;
	virtual HRESULT __safecall AddDataForStrokes(_di_IIterable_1__IInkStroke strokes) = 0 ;
	virtual HRESULT __safecall ClearDataForAllStrokes() = 0 ;
	virtual HRESULT __safecall RemoveDataForStroke(unsigned strokeId) = 0 ;
	virtual HRESULT __safecall RemoveDataForStrokes(Winapi::Devices::_di_IIterable_1__Cardinal strokeIds) = 0 ;
	virtual HRESULT __safecall ReplaceDataForStroke(Winapi::Commontypes::_di_IInkStroke stroke) = 0 ;
	virtual HRESULT __safecall SetStrokeDataKind(unsigned strokeId, Winapi::Commontypes::Analysis_InkAnalysisStrokeKind strokeKind) = 0 ;
	virtual HRESULT __safecall AnalyzeAsync(_di_IAsyncOperation_1__Analysis_IInkAnalysisResult &__AnalyzeAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_Analysis_IInkAnalysisRoot _scw_get_AnalysisRoot() { _di_Analysis_IInkAnalysisRoot __r; HRESULT __hr = get_AnalysisRoot(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_Analysis_IInkAnalysisRoot AnalysisRoot = {read=_scw_get_AnalysisRoot};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsAnalyzing() { bool __r; HRESULT __hr = get_IsAnalyzing(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsAnalyzing = {read=_scw_get_IsAnalyzing};
};

__interface  INTERFACE_UUID("{29138686-1963-49D8-9589-E14384C769E3}") Analysis_IInkAnalyzerFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateAnalyzer(_di_Analysis_IInkAnalyzer &__CreateAnalyzer_result) = 0 ;
};

__interface  INTERFACE_UUID("{DD6D6231-BD16-4663-B5AE-941D3043EF5B}") Analysis_IInkAnalysisWritingRegion  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{D9AD045C-0CD1-4DD4-A68B-EB1F12B3D727}") Analysis_IInkAnalysisParagraph  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{B4E3C23F-C4C3-4C3A-A1A6-9D85547EE586}") Analysis_IInkAnalysisListItem  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{EE049368-6110-4136-95F9-EE809FC20030}") Analysis_IInkAnalysisInkBullet  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{A06D048D-2B8D-4754-AD5A-D0871193A956}") Analysis_IInkAnalysisLine  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	virtual HRESULT __safecall get_IndentLevel(int &__get_IndentLevel_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline int _scw_get_IndentLevel() { int __r; HRESULT __hr = get_IndentLevel(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property int IndentLevel = {read=_scw_get_IndentLevel};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
};

__interface  INTERFACE_UUID("{4BD228AD-83AF-4034-8F3B-F8687DFFF436}") Analysis_IInkAnalysisInkWord  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_RecognizedText(HSTRING &__get_RecognizedText_result) = 0 ;
	virtual HRESULT __safecall get_TextAlternates(Winapi::Devices::_di_IVectorView_1__HSTRING &__get_TextAlternates_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_RecognizedText() { HSTRING __r; HRESULT __hr = get_RecognizedText(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING RecognizedText = {read=_scw_get_RecognizedText};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Devices::_di_IVectorView_1__HSTRING _scw_get_TextAlternates() { Winapi::Devices::_di_IVectorView_1__HSTRING __r; HRESULT __hr = get_TextAlternates(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Devices::_di_IVectorView_1__HSTRING TextAlternates = {read=_scw_get_TextAlternates};
};

__interface  INTERFACE_UUID("{6A85ED1F-1FE4-4E15-898C-8E112377E021}") Analysis_IInkAnalysisInkDrawing  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DrawingKind(Winapi::Commontypes::Analysis_InkAnalysisDrawingKind &__get_DrawingKind_result) = 0 ;
	virtual HRESULT __safecall get_Center(System::Types::TPointF &__get_Center_result) = 0 ;
	virtual HRESULT __safecall get_Points(Winapi::Foundation::_di_IVectorView_1__Point &__get_Points_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Center() { System::Types::TPointF __r; HRESULT __hr = get_Center(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Center = {read=_scw_get_Center};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Analysis_InkAnalysisDrawingKind _scw_get_DrawingKind() { Winapi::Commontypes::Analysis_InkAnalysisDrawingKind __r; HRESULT __hr = get_DrawingKind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Analysis_InkAnalysisDrawingKind DrawingKind = {read=_scw_get_DrawingKind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::_di_IVectorView_1__Point _scw_get_Points() { Winapi::Foundation::_di_IVectorView_1__Point __r; HRESULT __hr = get_Points(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::_di_IVectorView_1__Point Points = {read=_scw_get_Points};
};

__interface  INTERFACE_UUID("{CF53E612-9A34-11E6-9F33-A24FC0D9649C}") IInkPresenter2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_HighContrastAdjustment(Winapi::Commontypes::InkHighContrastAdjustment &__get_HighContrastAdjustment_result) = 0 ;
	virtual HRESULT __safecall put_HighContrastAdjustment(Winapi::Commontypes::InkHighContrastAdjustment value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::InkHighContrastAdjustment _scw_get_HighContrastAdjustment() { Winapi::Commontypes::InkHighContrastAdjustment __r; HRESULT __hr = get_HighContrastAdjustment(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::InkHighContrastAdjustment HighContrastAdjustment = {read=_scw_get_HighContrastAdjustment, write=put_HighContrastAdjustment};
};

__interface  INTERFACE_UUID("{45130DC1-BC61-44D4-A423-54712AE671C4}") IInkPresenterRuler2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_AreTickMarksVisible(bool &__get_AreTickMarksVisible_result) = 0 ;
	virtual HRESULT __safecall put_AreTickMarksVisible(bool value) = 0 ;
	virtual HRESULT __safecall get_IsCompassVisible(bool &__get_IsCompassVisible_result) = 0 ;
	virtual HRESULT __safecall put_IsCompassVisible(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_AreTickMarksVisible() { bool __r; HRESULT __hr = get_AreTickMarksVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool AreTickMarksVisible = {read=_scw_get_AreTickMarksVisible, write=put_AreTickMarksVisible};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IsCompassVisible() { bool __r; HRESULT __hr = get_IsCompassVisible(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IsCompassVisible = {read=_scw_get_IsCompassVisible, write=put_IsCompassVisible};
};

__interface  INTERFACE_UUID("{34361BEB-9001-4A4B-A690-69DBAF63E501}") IInkPresenterRulerFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter, _di_IInkPresenterRuler &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{320103C9-68FA-47E9-8127-8370711FC46C}") IInkPresenterProtractorFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter, _di_IInkPresenterProtractor &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{73E6011B-80C0-4DFB-9B66-10BA7F3F9C84}") Core_ICoreInkIndependentInputSourceStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter, Winapi::Commontypes::_di_Core_ICoreInkIndependentInputSource &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{9F87272B-858C-46A5-9B41-D195970459FD}") IInkPoint  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Position(System::Types::TPointF &__get_Position_result) = 0 ;
	virtual HRESULT __safecall get_Pressure(float &__get_Pressure_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TPointF _scw_get_Position() { System::Types::TPointF __r; HRESULT __hr = get_Position(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TPointF Position = {read=_scw_get_Position};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_Pressure() { float __r; HRESULT __hr = get_Pressure(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float Pressure = {read=_scw_get_Pressure};
};

__interface  INTERFACE_UUID("{47415452-DB79-567E-84D5-E9912330F944}") IIterator_1__IInkPoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CDD4F975-F1AD-501A-95D1-5CD7053A3DE1}") IIterator_1__IInkPoint  : public IIterator_1__IInkPoint_Base 
{
	virtual HRESULT __safecall get_Current(_di_IInkPoint &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIInkPoint items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IInkPoint _scw_get_Current() { _di_IInkPoint __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IInkPoint Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{0630C0EF-A4E2-5AF6-B2E9-8E042E294E17}") IIterable_1__IInkPoint_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{A9E993DD-3779-5FEF-B8B2-1E40384D55DA}") IIterable_1__IInkPoint  : public IIterable_1__IInkPoint_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IInkPoint &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{86BAE711-F0CD-51F6-B838-CC568D127246}") IVectorView_1__IInkPoint  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IInkPoint &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IInkPoint value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIInkPoint items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{79F75E88-4A97-5865-9F28-583145FA6024}") IVector_1__IInkPoint  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IInkPoint &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall GetView(_di_IVectorView_1__IInkPoint &__GetView_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IInkPoint value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall SetAt(unsigned index, _di_IInkPoint value) = 0 ;
	virtual HRESULT __safecall InsertAt(unsigned index, _di_IInkPoint value) = 0 ;
	virtual HRESULT __safecall RemoveAt(unsigned index) = 0 ;
	virtual HRESULT __safecall Append(_di_IInkPoint value) = 0 ;
	virtual HRESULT __safecall RemoveAtEnd() = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIInkPoint items, unsigned &__GetMany_result) = 0 ;
	virtual HRESULT __safecall ReplaceAll(unsigned itemsSize, PIInkPoint items) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{FB07D14C-3380-457A-A987-991357896C1B}") Core_ICoreWetStrokeUpdateEventArgs  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_NewInkPoints(_di_IVector_1__IInkPoint &__get_NewInkPoints_result) = 0 ;
	virtual HRESULT __safecall get_PointerId(unsigned &__get_PointerId_result) = 0 ;
	virtual HRESULT __safecall get_Disposition(Winapi::Commontypes::Core_CoreWetStrokeDisposition &__get_Disposition_result) = 0 ;
	virtual HRESULT __safecall put_Disposition(Winapi::Commontypes::Core_CoreWetStrokeDisposition value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::Core_CoreWetStrokeDisposition _scw_get_Disposition() { Winapi::Commontypes::Core_CoreWetStrokeDisposition __r; HRESULT __hr = get_Disposition(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::Core_CoreWetStrokeDisposition Disposition = {read=_scw_get_Disposition, write=put_Disposition};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IVector_1__IInkPoint _scw_get_NewInkPoints() { _di_IVector_1__IInkPoint __r; HRESULT __hr = get_NewInkPoints(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IVector_1__IInkPoint NewInkPoints = {read=_scw_get_NewInkPoints};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_PointerId() { unsigned __r; HRESULT __hr = get_PointerId(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned PointerId = {read=_scw_get_PointerId};
};

__interface  INTERFACE_UUID("{67FF75E8-02A4-5254-A965-0B254C7D0788}") TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{0F5956D0-3883-5571-A68B-29E8B79654CC}") TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs  : public TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_Core_ICoreWetStrokeUpdateSource sender, _di_Core_ICoreWetStrokeUpdateEventArgs args) = 0 ;
};

__interface  INTERFACE_UUID("{1F718E22-EE52-4E00-8209-4C3E5B21A3CC}") Core_ICoreWetStrokeUpdateSource  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall add_WetStrokeStarting(_di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_WetStrokeStarting_result) = 0 ;
	virtual HRESULT __safecall remove_WetStrokeStarting(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall add_WetStrokeContinuing(_di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_WetStrokeContinuing_result) = 0 ;
	virtual HRESULT __safecall remove_WetStrokeContinuing(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall add_WetStrokeStopping(_di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_WetStrokeStopping_result) = 0 ;
	virtual HRESULT __safecall remove_WetStrokeStopping(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall add_WetStrokeCompleted(_di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_WetStrokeCompleted_result) = 0 ;
	virtual HRESULT __safecall remove_WetStrokeCompleted(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall add_WetStrokeCanceled(_di_TypedEventHandler_2__Core_ICoreWetStrokeUpdateSource__Core_ICoreWetStrokeUpdateEventArgs handler, Winapi::Commontypes::EventRegistrationToken &__add_WetStrokeCanceled_result) = 0 ;
	virtual HRESULT __safecall remove_WetStrokeCanceled(Winapi::Commontypes::EventRegistrationToken cookie) = 0 ;
	virtual HRESULT __safecall get_InkPresenter(Winapi::Commontypes::_di_IInkPresenter &__get_InkPresenter_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkPresenter _scw_get_InkPresenter() { Winapi::Commontypes::_di_IInkPresenter __r; HRESULT __hr = get_InkPresenter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkPresenter InkPresenter = {read=_scw_get_InkPresenter};
};

__interface  INTERFACE_UUID("{3DAD9CBA-1D3D-46AE-AB9D-8647486C6F90}") Core_ICoreWetStrokeUpdateSourceStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter, _di_Core_ICoreWetStrokeUpdateSource &__Create_result) = 0 ;
};

__interface  INTERFACE_UUID("{396E89E6-7D55-4617-9E58-68C70C9169B9}") Core_ICoreInkPresenterHost  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_InkPresenter(Winapi::Commontypes::_di_IInkPresenter &__get_InkPresenter_result) = 0 ;
	virtual HRESULT __safecall get_RootVisual(Winapi::Ui::Composition::_di_IContainerVisual &__get_RootVisual_result) = 0 ;
	virtual HRESULT __safecall put_RootVisual(Winapi::Ui::Composition::_di_IContainerVisual value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkPresenter _scw_get_InkPresenter() { Winapi::Commontypes::_di_IInkPresenter __r; HRESULT __hr = get_InkPresenter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkPresenter InkPresenter = {read=_scw_get_InkPresenter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Ui::Composition::_di_IContainerVisual _scw_get_RootVisual() { Winapi::Ui::Composition::_di_IContainerVisual __r; HRESULT __hr = get_RootVisual(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Ui::Composition::_di_IContainerVisual RootVisual = {read=_scw_get_RootVisual, write=put_RootVisual};
};

__interface  INTERFACE_UUID("{FBA9C3F7-AE56-4D5C-BD2F-0AC45F5E4AF9}") IInkPoint2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_TiltX(float &__get_TiltX_result) = 0 ;
	virtual HRESULT __safecall get_TiltY(float &__get_TiltY_result) = 0 ;
	virtual HRESULT __safecall get_Timestamp(unsigned __int64 &__get_Timestamp_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_TiltX() { float __r; HRESULT __hr = get_TiltX(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float TiltX = {read=_scw_get_TiltX};
	#pragma option push -w-inl
	/* safecall wrapper */ inline float _scw_get_TiltY() { float __r; HRESULT __hr = get_TiltY(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property float TiltY = {read=_scw_get_TiltY};
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned __int64 _scw_get_Timestamp() { unsigned __int64 __r; HRESULT __hr = get_Timestamp(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned __int64 Timestamp = {read=_scw_get_Timestamp};
};

__interface  INTERFACE_UUID("{29E5D51C-C98F-405D-9F3B-E53E31068D4D}") IInkPointFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateInkPoint(System::Types::TPointF position, float pressure, _di_IInkPoint &__CreateInkPoint_result) = 0 ;
};

__interface  INTERFACE_UUID("{E0145E85-DAFF-45F2-AD69-050D8256A209}") IInkPointFactory2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateInkPointWithTiltAndTimestamp(System::Types::TPointF position, float pressure, float tiltX, float tiltY, unsigned __int64 timestamp, _di_IInkPoint &__CreateInkPointWithTiltAndTimestamp_result) = 0 ;
};

__interface  INTERFACE_UUID("{7CAB6508-8EC4-42FD-A5A5-E4B7D1D5316D}") IInkDrawingAttributes2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PenTipTransform(Winapi::Foundation::Types::Numerics_Matrix3x2 &__get_PenTipTransform_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_PenTipTransform(Winapi::Foundation::Types::Numerics_Matrix3x2 value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_PenTipTransform(const Winapi::Foundation::Types::Numerics_Matrix3x2 &value) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall get_DrawAsHighlighter(bool &__get_DrawAsHighlighter_result) = 0 ;
	virtual HRESULT __safecall put_DrawAsHighlighter(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_DrawAsHighlighter() { bool __r; HRESULT __hr = get_DrawAsHighlighter(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool DrawAsHighlighter = {read=_scw_get_DrawAsHighlighter, write=put_DrawAsHighlighter};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Matrix3x2 _scw_get_PenTipTransform() { Winapi::Foundation::Types::Numerics_Matrix3x2 __r; HRESULT __hr = get_PenTipTransform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Matrix3x2 PenTipTransform = {read=_scw_get_PenTipTransform, write=put_PenTipTransform};
};

__interface  INTERFACE_UUID("{4F2534CB-2D86-41BB-B0E8-E4C2A0253C52}") IInkDrawingAttributesPencilProperties  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Opacity(double &__get_Opacity_result) = 0 ;
	virtual HRESULT __safecall put_Opacity(double value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline double _scw_get_Opacity() { double __r; HRESULT __hr = get_Opacity(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property double Opacity = {read=_scw_get_Opacity, write=put_Opacity};
};

__interface  INTERFACE_UUID("{72020002-7D5B-4690-8AF4-E664CBE2B74F}") IInkDrawingAttributes3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Kind(Winapi::Commontypes::InkDrawingAttributesKind &__get_Kind_result) = 0 ;
	virtual HRESULT __safecall get_PencilProperties(_di_IInkDrawingAttributesPencilProperties &__get_PencilProperties_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::InkDrawingAttributesKind _scw_get_Kind() { Winapi::Commontypes::InkDrawingAttributesKind __r; HRESULT __hr = get_Kind(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::InkDrawingAttributesKind Kind = {read=_scw_get_Kind};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IInkDrawingAttributesPencilProperties _scw_get_PencilProperties() { _di_IInkDrawingAttributesPencilProperties __r; HRESULT __hr = get_PencilProperties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IInkDrawingAttributesPencilProperties PencilProperties = {read=_scw_get_PencilProperties};
};

__interface  INTERFACE_UUID("{EF65DC25-9F19-456D-91A3-BC3A3D91C5FB}") IInkDrawingAttributes4  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_IgnoreTilt(bool &__get_IgnoreTilt_result) = 0 ;
	virtual HRESULT __safecall put_IgnoreTilt(bool value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_IgnoreTilt() { bool __r; HRESULT __hr = get_IgnoreTilt(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool IgnoreTilt = {read=_scw_get_IgnoreTilt, write=put_IgnoreTilt};
};

__interface  INTERFACE_UUID("{F731E03F-1A65-4862-96CB-6E1665E17F6D}") IInkDrawingAttributesStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateForPencil(Winapi::Commontypes::_di_IInkDrawingAttributes &__CreateForPencil_result) = 0 ;
};

__interface  INTERFACE_UUID("{5DB9E4F4-BAFA-4DE1-89D3-201B1ED7D89B}") IInkStroke2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_PointTransform(Winapi::Foundation::Types::Numerics_Matrix3x2 &__get_PointTransform_result) = 0 ;
#ifndef _WIN64
	virtual HRESULT __safecall put_PointTransform(Winapi::Foundation::Types::Numerics_Matrix3x2 value) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall put_PointTransform(const Winapi::Foundation::Types::Numerics_Matrix3x2 &value) = 0 ;
#endif /* _WIN64 */
	virtual HRESULT __safecall GetInkPoints(_di_IVectorView_1__IInkPoint &__GetInkPoints_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Matrix3x2 _scw_get_PointTransform() { Winapi::Foundation::Types::Numerics_Matrix3x2 __r; HRESULT __hr = get_PointTransform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Matrix3x2 PointTransform = {read=_scw_get_PointTransform, write=put_PointTransform};
};

__interface  INTERFACE_UUID("{4A807374-9499-411D-A1C4-68855D03D65F}") IInkStroke3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(unsigned &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_StrokeStartedTime(Winapi::Commontypes::_di_IReference_1__DateTime &__get_StrokeStartedTime_result) = 0 ;
	virtual HRESULT __safecall put_StrokeStartedTime(Winapi::Commontypes::_di_IReference_1__DateTime value) = 0 ;
	virtual HRESULT __safecall get_StrokeDuration(Winapi::Commontypes::_di_IReference_1__TimeSpan &__get_StrokeDuration_result) = 0 ;
	virtual HRESULT __safecall put_StrokeDuration(Winapi::Commontypes::_di_IReference_1__TimeSpan value) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Id() { unsigned __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__TimeSpan _scw_get_StrokeDuration() { Winapi::Commontypes::_di_IReference_1__TimeSpan __r; HRESULT __hr = get_StrokeDuration(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__TimeSpan StrokeDuration = {read=_scw_get_StrokeDuration, write=put_StrokeDuration};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IReference_1__DateTime _scw_get_StrokeStartedTime() { Winapi::Commontypes::_di_IReference_1__DateTime __r; HRESULT __hr = get_StrokeStartedTime(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IReference_1__DateTime StrokeStartedTime = {read=_scw_get_StrokeStartedTime, write=put_StrokeStartedTime};
};

__interface  INTERFACE_UUID("{82BBD1DC-1C63-41DC-9E07-4B4A70CED801}") IInkStrokeBuilder  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall BeginStroke(Winapi::Commontypes::_di_IPointerPoint pointerPoint) = 0 ;
	virtual HRESULT __safecall AppendToStroke(Winapi::Commontypes::_di_IPointerPoint pointerPoint, Winapi::Commontypes::_di_IPointerPoint &__AppendToStroke_result) = 0 ;
	virtual HRESULT __safecall EndStroke(Winapi::Commontypes::_di_IPointerPoint pointerPoint, Winapi::Commontypes::_di_IInkStroke &__EndStroke_result) = 0 ;
	virtual HRESULT __safecall CreateStroke(Winapi::Commontypes::_di_IIterable_1__Point points, Winapi::Commontypes::_di_IInkStroke &__CreateStroke_result) = 0 ;
	virtual HRESULT __safecall SetDefaultDrawingAttributes(Winapi::Commontypes::_di_IInkDrawingAttributes drawingAttributes) = 0 ;
};

__interface  INTERFACE_UUID("{BD82BC27-731F-4CBC-BBBF-6D468044F1E5}") IInkStrokeBuilder2  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall CreateStrokeFromInkPoints(_di_IIterable_1__IInkPoint inkPoints, Winapi::Foundation::Types::Numerics_Matrix3x2 transform, Winapi::Commontypes::_di_IInkStroke &__CreateStrokeFromInkPoints_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall CreateStrokeFromInkPoints(_di_IIterable_1__IInkPoint inkPoints, const Winapi::Foundation::Types::Numerics_Matrix3x2 &transform, Winapi::Commontypes::_di_IInkStroke &__CreateStrokeFromInkPoints_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{B2C71FCD-5472-46B1-A81D-C37A3D169441}") IInkStrokeBuilder3  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall CreateStrokeFromInkPoints(_di_IIterable_1__IInkPoint inkPoints, Winapi::Foundation::Types::Numerics_Matrix3x2 transform, Winapi::Commontypes::_di_IReference_1__DateTime strokeStartedTime, Winapi::Commontypes::_di_IReference_1__TimeSpan strokeDuration, Winapi::Commontypes::_di_IInkStroke &__CreateStrokeFromInkPoints_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall CreateStrokeFromInkPoints(_di_IIterable_1__IInkPoint inkPoints, const Winapi::Foundation::Types::Numerics_Matrix3x2 &transform, Winapi::Commontypes::_di_IReference_1__DateTime strokeStartedTime, Winapi::Commontypes::_di_IReference_1__TimeSpan strokeDuration, Winapi::Commontypes::_di_IInkStroke &__CreateStrokeFromInkPoints_result) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{8901D364-DA36-4BCF-9E5C-D195825995B4}") IInkStrokeContainer2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AddStrokes(_di_IIterable_1__IInkStroke strokes) = 0 ;
	virtual HRESULT __safecall Clear() = 0 ;
};

__interface  INTERFACE_UUID("{3D07BEA5-BAEA-4C82-A719-7B83DA1067D2}") IInkStrokeContainer3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SaveAsync(Winapi::Commontypes::_di_IOutputStream outputStream, Winapi::Commontypes::InkPersistenceFormat inkPersistenceFormat, Winapi::Devices::_di_IAsyncOperationWithProgress_2__Cardinal__Cardinal &__SaveAsync_result) = 0 ;
	virtual HRESULT __safecall GetStrokeById(unsigned id, Winapi::Commontypes::_di_IInkStroke &__GetStrokeById_result) = 0 ;
};

__interface  INTERFACE_UUID("{077CCEA3-904D-442A-B151-AACA3631C43B}") IInkRecognizer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Name(HSTRING &__get_Name_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Name() { HSTRING __r; HRESULT __hr = get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Name = {read=_scw_get_Name};
};

__interface  INTERFACE_UUID("{ECE8567F-8080-5CED-8988-BB0364C803D4}") AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B658F05D-8BA7-5DAC-9253-FF7006750267}") AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult  : public AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B1923F59-D674-5365-B99A-3F1E52268C7F}") IAsyncOperation_1__IVectorView_1__IInkRecognitionResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{13D81DD7-2C81-5ADB-9106-2B3C3E6F8298}") IAsyncOperation_1__IVectorView_1__IInkRecognitionResult  : public IAsyncOperation_1__IVectorView_1__IInkRecognitionResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::_di_IVectorView_1__IInkRecognitionResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IInkRecognitionResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{F8BD3097-5262-5E7A-A19D-13C029D2D7E5}") IIterator_1__IInkRecognizer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{28DFF88B-C687-51E7-B261-11999AA27264}") IIterator_1__IInkRecognizer  : public IIterator_1__IInkRecognizer_Base 
{
	virtual HRESULT __safecall get_Current(_di_IInkRecognizer &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIInkRecognizer items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IInkRecognizer _scw_get_Current() { _di_IInkRecognizer __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IInkRecognizer Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{611B7E84-A803-5071-AAEA-4F2CE0151052}") IIterable_1__IInkRecognizer_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{DAB88C7D-BE83-5950-B0EA-4B7018E046BE}") IIterable_1__IInkRecognizer  : public IIterable_1__IInkRecognizer_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IInkRecognizer &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{C6A52642-FFBD-5410-ABA3-517FF9A91011}") IVectorView_1__IInkRecognizer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IInkRecognizer &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IInkRecognizer value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIInkRecognizer items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{A74D9A31-8047-4698-A912-F82A5085012F}") IInkRecognizerContainer  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall SetDefaultRecognizer(_di_IInkRecognizer recognizer) = 0 ;
	virtual HRESULT __safecall RecognizeAsync(Winapi::Commontypes::_di_IInkStrokeContainer strokeCollection, Winapi::Commontypes::InkRecognitionTarget recognitionTarget, _di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult &__RecognizeAsync_result) = 0 ;
	virtual HRESULT __safecall GetRecognizers(_di_IVectorView_1__IInkRecognizer &__GetRecognizers_result) = 0 ;
};

__interface  INTERFACE_UUID("{4744737D-671B-4163-9C95-4E8D7A035FE1}") IInkManager  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Mode(Winapi::Commontypes::InkManipulationMode &__get_Mode_result) = 0 ;
	virtual HRESULT __safecall put_Mode(Winapi::Commontypes::InkManipulationMode value) = 0 ;
	virtual HRESULT __safecall ProcessPointerDown(Winapi::Commontypes::_di_IPointerPoint pointerPoint) = 0 ;
	virtual HRESULT __safecall ProcessPointerUpdate(Winapi::Commontypes::_di_IPointerPoint pointerPoint, Winapi::Winrt::_di_IInspectable &__ProcessPointerUpdate_result) = 0 ;
	virtual HRESULT __safecall ProcessPointerUp(Winapi::Commontypes::_di_IPointerPoint pointerPoint, System::Types::TRectF &__ProcessPointerUp_result) = 0 ;
	virtual HRESULT __safecall SetDefaultDrawingAttributes(Winapi::Commontypes::_di_IInkDrawingAttributes drawingAttributes) = 0 ;
	virtual HRESULT __safecall RecognizeAsync(Winapi::Commontypes::InkRecognitionTarget recognitionTarget, _di_IAsyncOperation_1__IVectorView_1__IInkRecognitionResult &__RecognizeAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::InkManipulationMode _scw_get_Mode() { Winapi::Commontypes::InkManipulationMode __r; HRESULT __hr = get_Mode(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::InkManipulationMode Mode = {read=_scw_get_Mode, write=put_Mode};
};

__interface  INTERFACE_UUID("{FDA015D3-9D66-4F7D-A57F-CC70B9CFAA76}") Core_ICoreIncrementalInkStroke  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall AppendInkPoints(_di_IIterable_1__IInkPoint inkPoints, System::Types::TRectF &__AppendInkPoints_result) = 0 ;
	virtual HRESULT __safecall CreateInkStroke(Winapi::Commontypes::_di_IInkStroke &__CreateInkStroke_result) = 0 ;
	virtual HRESULT __safecall get_DrawingAttributes(Winapi::Commontypes::_di_IInkDrawingAttributes &__get_DrawingAttributes_result) = 0 ;
	virtual HRESULT __safecall get_PointTransform(Winapi::Foundation::Types::Numerics_Matrix3x2 &__get_PointTransform_result) = 0 ;
	virtual HRESULT __safecall get_BoundingRect(System::Types::TRectF &__get_BoundingRect_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline System::Types::TRectF _scw_get_BoundingRect() { System::Types::TRectF __r; HRESULT __hr = get_BoundingRect(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property System::Types::TRectF BoundingRect = {read=_scw_get_BoundingRect};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IInkDrawingAttributes _scw_get_DrawingAttributes() { Winapi::Commontypes::_di_IInkDrawingAttributes __r; HRESULT __hr = get_DrawingAttributes(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IInkDrawingAttributes DrawingAttributes = {read=_scw_get_DrawingAttributes};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Foundation::Types::Numerics_Matrix3x2 _scw_get_PointTransform() { Winapi::Foundation::Types::Numerics_Matrix3x2 __r; HRESULT __hr = get_PointTransform(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Foundation::Types::Numerics_Matrix3x2 PointTransform = {read=_scw_get_PointTransform};
};

__interface  INTERFACE_UUID("{D7C59F46-8DA8-4F70-9751-E53BB6DF4596}") Core_ICoreIncrementalInkStrokeFactory  : public Winapi::Winrt::IInspectable 
{
#ifndef _WIN64
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkDrawingAttributes drawingAttributes, Winapi::Foundation::Types::Numerics_Matrix3x2 pointTransform, _di_Core_ICoreIncrementalInkStroke &__Create_result) = 0 ;
#else /* _WIN64 */
	virtual HRESULT __safecall Create(Winapi::Commontypes::_di_IInkDrawingAttributes drawingAttributes, const Winapi::Foundation::Types::Numerics_Matrix3x2 &pointTransform, _di_Core_ICoreIncrementalInkStroke &__Create_result) = 0 ;
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAnalysis_InkAnalyzer : public System::Win::Winrt::TWinRTGenericImportI__1<_di_Analysis_IInkAnalyzer>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_Analysis_IInkAnalyzer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TAnalysis_InkAnalyzer() : System::Win::Winrt::TWinRTGenericImportI__1<_di_Analysis_IInkAnalyzer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAnalysis_InkAnalyzer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkPresenterRuler : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterRulerFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterRulerFactory> inherited;
	
public:
	static _di_IInkPresenterRuler __fastcall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter);
public:
	/* TObject.Create */ inline __fastcall TInkPresenterRuler() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterRulerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkPresenterRuler() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkPresenterProtractor : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterProtractorFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterProtractorFactory> inherited;
	
public:
	static _di_IInkPresenterProtractor __fastcall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter);
public:
	/* TObject.Create */ inline __fastcall TInkPresenterProtractor() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IInkPresenterProtractorFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkPresenterProtractor() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_CoreInkIndependentInputSource : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreInkIndependentInputSourceStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreInkIndependentInputSourceStatics> inherited;
	
public:
	static Winapi::Commontypes::_di_Core_ICoreInkIndependentInputSource __fastcall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter);
public:
	/* TObject.Create */ inline __fastcall TCore_CoreInkIndependentInputSource() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreInkIndependentInputSourceStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_CoreInkIndependentInputSource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_CoreWetStrokeUpdateSource : public System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreWetStrokeUpdateSourceStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreWetStrokeUpdateSourceStatics> inherited;
	
public:
	static _di_Core_ICoreWetStrokeUpdateSource __fastcall Create(Winapi::Commontypes::_di_IInkPresenter inkPresenter);
public:
	/* TObject.Create */ inline __fastcall TCore_CoreWetStrokeUpdateSource() : System::Win::Winrt::TWinRTGenericImportS__1<_di_Core_ICoreWetStrokeUpdateSourceStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_CoreWetStrokeUpdateSource() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_CoreInkPresenterHost : public System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_ICoreInkPresenterHost>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_ICoreInkPresenterHost> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TCore_CoreInkPresenterHost() : System::Win::Winrt::TWinRTGenericImportI__1<_di_Core_ICoreInkPresenterHost>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_CoreInkPresenterHost() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkPoint : public System::Win::Winrt::TWinRTGenericImportF2__2<_di_IInkPointFactory,_di_IInkPointFactory2>
{
	typedef System::Win::Winrt::TWinRTGenericImportF2__2<_di_IInkPointFactory,_di_IInkPointFactory2> inherited;
	
public:
	static _di_IInkPoint __fastcall CreateInkPoint(const System::Types::TPointF &position, float pressure);
	static _di_IInkPoint __fastcall CreateInkPointWithTiltAndTimestamp(const System::Types::TPointF &position, float pressure, float tiltX, float tiltY, unsigned __int64 timestamp);
public:
	/* TObject.Create */ inline __fastcall TInkPoint() : System::Win::Winrt::TWinRTGenericImportF2__2<_di_IInkPointFactory,_di_IInkPointFactory2>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkPoint() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkDrawingAttributes : public System::Win::Winrt::TWinRTGenericImportSI__2<_di_IInkDrawingAttributesStatics,Winapi::Commontypes::_di_IInkDrawingAttributes>
{
	typedef System::Win::Winrt::TWinRTGenericImportSI__2<_di_IInkDrawingAttributesStatics,Winapi::Commontypes::_di_IInkDrawingAttributes> inherited;
	
public:
	static Winapi::Commontypes::_di_IInkDrawingAttributes __fastcall CreateForPencil();
public:
	/* TObject.Create */ inline __fastcall TInkDrawingAttributes() : System::Win::Winrt::TWinRTGenericImportSI__2<_di_IInkDrawingAttributesStatics,Winapi::Commontypes::_di_IInkDrawingAttributes>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkDrawingAttributes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkStrokeBuilder : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkStrokeBuilder>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkStrokeBuilder> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TInkStrokeBuilder() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkStrokeBuilder>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkStrokeBuilder() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkStrokeContainer : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IInkStrokeContainer>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IInkStrokeContainer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TInkStrokeContainer() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IInkStrokeContainer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkStrokeContainer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkRecognizerContainer : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkRecognizerContainer>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkRecognizerContainer> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TInkRecognizerContainer() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkRecognizerContainer>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkRecognizerContainer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TInkManager : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkManager>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TInkManager() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IInkManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInkManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCore_CoreIncrementalInkStroke : public System::Win::Winrt::TWinRTGenericImportF__1<_di_Core_ICoreIncrementalInkStrokeFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_Core_ICoreIncrementalInkStrokeFactory> inherited;
	
public:
	static _di_Core_ICoreIncrementalInkStroke __fastcall Create(Winapi::Commontypes::_di_IInkDrawingAttributes drawingAttributes, const Winapi::Foundation::Types::Numerics_Matrix3x2 &pointTransform);
public:
	/* TObject.Create */ inline __fastcall TCore_CoreIncrementalInkStroke() : System::Win::Winrt::TWinRTGenericImportF__1<_di_Core_ICoreIncrementalInkStrokeFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCore_CoreIncrementalInkStroke() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Inking */
}	/* namespace Input */
}	/* namespace Ui */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Ui_Input_InkingHPP
