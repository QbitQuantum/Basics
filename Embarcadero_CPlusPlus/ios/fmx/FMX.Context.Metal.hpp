// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.Metal.pas' rev: 34.00 (iOS)

#ifndef Fmx_Context_MetalHPP
#define Fmx_Context_MetalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Math.Vectors.hpp>
#include <System.Generics.Collections.hpp>
#include <Macapi.Metal.hpp>
#include <Macapi.MetalKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.QuartzCore.hpp>
#include <FMX.Platform.iOS.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Graphics.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Metal
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomContextMetal;
struct TPipelineStateConfiguration;
struct TDepthStencilStateConfiguration;
struct TSamplerStateConfiguration;
class DELPHICLASS TContextMetal;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomContextMetal : public Fmx::Types3d::TContext3D
{
	typedef Fmx::Types3d::TContext3D inherited;
	
private:
	static int FMaxTextureSize;
	static Macapi::Metal::_di_MTLDevice FSharedDevice;
	__classmethod void __fastcall InitMaxTextureSize();
	
protected:
	static Macapi::Metal::_di_MTLDevice __fastcall GetSharedDevice();
	__classmethod virtual void __fastcall CreateSharedDevice();
	__classmethod virtual void __fastcall DestroySharedDevice();
	
public:
	/* static */ __property Macapi::Metal::_di_MTLDevice SharedDevice = {read=GetSharedDevice};
	__classmethod virtual Fmx::Types::TPixelFormat __fastcall PixelFormat();
	__classmethod virtual int __fastcall MaxTextureSize();
	__classmethod virtual bool __fastcall Valid();
	__classmethod virtual int __fastcall MaxLightCount();
	__classmethod virtual bool __fastcall IsMetalSupported();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomContextMetal(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	/* TContext3D.CreateFromTexture */ inline __fastcall virtual TCustomContextMetal(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(ATexture, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomContextMetal() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomContextMetal() : Fmx::Types3d::TContext3D() { }
	
};


struct DECLSPEC_DRECORD TPipelineStateConfiguration
{
public:
	unsigned long ColorWriteMask;
	int SampleCount;
	bool BlendingEnabled;
	NativeUInt VertexShaderHandle;
	NativeUInt PixelShaderHandle;
	System::StaticArray<Fmx::Types3d::TVertexElement, 16> VertexDeclaration;
	void __fastcall Reset();
};


struct DECLSPEC_DRECORD TDepthStencilStateConfiguration
{
public:
	unsigned long DepthCompareFunction;
	bool DepthWriteEnabled;
	bool StencilEnabled;
	unsigned long StencilFailureOperation;
	unsigned long DepthFailureOperation;
	unsigned long DepthStencilPassOperation;
	unsigned long StencilCompareFunction;
	unsigned long StencilMask;
	void __fastcall Reset();
};


struct DECLSPEC_DRECORD TSamplerStateConfiguration
{
public:
	unsigned long MinFilter;
	unsigned long MagFilter;
	unsigned long MipFilter;
	void __fastcall Reset();
};


class PASCALIMPLEMENTATION TContextMetal : public TCustomContextMetal
{
	typedef TCustomContextMetal inherited;
	
private:
	static int FShaderHandleGenerator;
	static System::Generics::Collections::TDictionary__2<TPipelineStateConfiguration,Macapi::Metal::_di_MTLRenderPipelineState>* FPipelineStates;
	static System::Generics::Collections::TDictionary__2<TDepthStencilStateConfiguration,Macapi::Metal::_di_MTLDepthStencilState>* FDepthStencilStates;
	static System::Generics::Collections::TDictionary__2<TSamplerStateConfiguration,Macapi::Metal::_di_MTLSamplerState>* FSamplerStates;
	TPipelineStateConfiguration FPipelineStateConfiguration;
	TDepthStencilStateConfiguration FDepthStencilStateConfiguration;
	Macapi::Metal::_di_MTLCommandQueue FCommandQueue;
	Macapi::Metal::_di_MTLCommandBuffer FCommandBuffer;
	Macapi::Metal::_di_MTLRenderPassDescriptor FRenderPassDescriptor;
	Macapi::Metal::_di_MTLRenderCommandEncoder FRenderCommandEncoder;
	Macapi::Metalkit::_di_CAMetalDrawable FCurrentDrawable;
	Macapi::Metal::_di_MTLTexture FOnScreenTexture;
	unsigned long FStencilReferenceValue;
	unsigned long FSampleCount;
	__classmethod Macapi::Metal::_di_MTLRenderPipelineState __fastcall GetPipelineState(const TPipelineStateConfiguration &AConfiguration);
	__classmethod Macapi::Metal::_di_MTLRenderPipelineState __fastcall CreatePipelineState(const TPipelineStateConfiguration &AConfiguration);
	__classmethod Macapi::Metal::_di_MTLDepthStencilState __fastcall GetDepthStencilState(const TDepthStencilStateConfiguration &AConfiguration);
	__classmethod Macapi::Metal::_di_MTLDepthStencilState __fastcall CreateDepthStencilState(const TDepthStencilStateConfiguration &AConfiguration);
	__classmethod Macapi::Metal::_di_MTLSamplerState __fastcall GetSamplerState(const TSamplerStateConfiguration &AConfiguration);
	__classmethod Macapi::Metal::_di_MTLSamplerState __fastcall CreateSamplerState(const TSamplerStateConfiguration &AConfiguration);
	void __fastcall CreateRenderPassDescriptor();
	void __fastcall DestroyRenderPassDescriptor();
	void __fastcall CreateRenderCommandEncoder();
	Macapi::Metalkit::_di_CAMetalDrawable __fastcall GetCurrentDrawable();
	
protected:
	Macapi::Metal::_di_MTLTexture FDepthStencilBufferTexture;
	Macapi::Metal::_di_MTLTexture FMultisampleBufferTexture;
	virtual void __fastcall DoResize();
	virtual void __fastcall DoCreateBuffer();
	virtual void __fastcall DoFreeBuffer();
	virtual void __fastcall DoCopyToBitmap(Fmx::Graphics::TBitmap* const Dest, const System::Types::TRect &ARect);
	virtual void __fastcall DoCopyToBits(const void * Bits, const int Pitch, const System::Types::TRect &ARect);
	virtual bool __fastcall DoBeginScene();
	virtual void __fastcall DoEndScene();
	virtual void __fastcall DoClear(const Fmx::Types3d::TClearTargets ATarget, const System::Uitypes::TAlphaColor AColor, const float ADepth, const unsigned AStencil);
	__classmethod void __fastcall CreateSharedStates();
	__classmethod void __fastcall DestroySharedStates();
	virtual void __fastcall DoSetContextState(Fmx::Types3d::TContextState AState);
	virtual void __fastcall DoSetStencilOp(const Fmx::Types3d::TStencilOp Fail, const Fmx::Types3d::TStencilOp ZFail, const Fmx::Types3d::TStencilOp ZPass);
	virtual void __fastcall DoSetStencilFunc(const Fmx::Types3d::TStencilFunc Func, unsigned Ref, unsigned Mask);
	virtual void __fastcall DoSetScissorRect(const System::Types::TRect &ScissorRect);
	virtual void __fastcall DoDrawPrimitivesBatch(const Fmx::Types3d::TPrimitivesKind AKind, const void * Vertices, const void * Indices, const Fmx::Types3d::TVertexDeclaration VertexDeclaration, const int VertexSize, const int VertexCount, const int IndexSize, const int IndexCount);
	__classmethod virtual void __fastcall DoInitializeTexture(Fmx::Types3d::TTexture* const Texture);
	__classmethod virtual void __fastcall DoFinalizeTexture(Fmx::Types3d::TTexture* const Texture);
	__classmethod virtual void __fastcall DoUpdateTexture(Fmx::Types3d::TTexture* const Texture, const void * Bits, const int Pitch);
	__classmethod virtual Fmx::Types3d::TTexture* __fastcall DoBitmapToTexture(Fmx::Graphics::TBitmap* const Bitmap);
	__classmethod virtual void __fastcall DoInitializeShader(Fmx::Types3d::TContextShader* const Shader);
	__classmethod virtual void __fastcall DoFinalizeShader(Fmx::Types3d::TContextShader* const Shader);
	virtual void __fastcall DoSetShaders(Fmx::Types3d::TContextShader* const VertexShader, Fmx::Types3d::TContextShader* const PixelShader);
	virtual void __fastcall DoSetShaderVariable(const System::UnicodeString Name, const System::Math::Vectors::TVector3D *Data, const int Data_High)/* overload */;
	virtual void __fastcall DoSetShaderVariable(const System::UnicodeString Name, Fmx::Types3d::TTexture* const Texture)/* overload */;
	virtual void __fastcall DoSetShaderVariable(const System::UnicodeString Name, const System::Math::Vectors::TMatrix3D &Matrix)/* overload */;
	__fastcall virtual TContextMetal(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil);
	__fastcall virtual TContextMetal(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil);
	virtual void __fastcall InitContext();
	
public:
	__fastcall virtual ~TContextMetal();
public:
	/* TObject.Create */ inline __fastcall TContextMetal() : TCustomContextMetal() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall MultisampleTypeToNumber(const Fmx::Types3d::TMultisample AMultisample);
extern DELPHI_PACKAGE int __fastcall GetSupportedMultisample(const int ADesiredMultisample);
extern DELPHI_PACKAGE unsigned long __fastcall PixelFormatToMTLPixelFormat(const Fmx::Types::TPixelFormat ASource);
extern DELPHI_PACKAGE void __fastcall RegisterContextClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterContextClasses(void);
}	/* namespace Metal */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_METAL)
using namespace Fmx::Context::Metal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT)
using namespace Fmx::Context;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Context_MetalHPP
