// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.GLES.pas' rev: 34.00 (Android)

#ifndef Fmx_Context_GlesHPP
#define Fmx_Context_GlesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.hpp>
#include <System.Math.Vectors.hpp>
#include <Androidapi.Egl.hpp>
#include <Androidapi.Gles2.hpp>
#include <Androidapi.Gles2ext.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Filter.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Gles
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TShaderProgram;
class DELPHICLASS TExtensions;
class DELPHICLASS TCustomContextOpenGL;
class DELPHICLASS TGlesDiagnostic;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TOpenGlErrorReporting : unsigned char { Strict, SkipWarnings };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TShaderProgram : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	NativeUInt VS;
	NativeUInt PS;
	NativeUInt Prog;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Fmx::Types3d::TContextShaderVariable>* Variables;
	
public:
	__fastcall TShaderProgram();
	__fastcall virtual ~TShaderProgram();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TExtensions : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	bool operator[](const System::UnicodeString Name) { return this->Extension[Name]; }
	
private:
	System::Classes::TStringList* Extensions;
	System::UnicodeString FRenderer;
	void __fastcall FillExtensions();
	bool __fastcall GetExtension(const System::UnicodeString Name);
	
public:
	__property System::UnicodeString Renderer = {read=FRenderer};
	__property bool Extension[const System::UnicodeString Name] = {read=GetExtension/*, default*/};
	__fastcall TExtensions();
	__fastcall virtual ~TExtensions();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomContextOpenGL : public Fmx::Types3d::TContext3D
{
	typedef Fmx::Types3d::TContext3D inherited;
	
private:
	static TExtensions* FExtensions;
	static Fmx::Types3d::TContext3D::TIndexBufferSupport FIndexBufferSupport;
	static int FMaxTextureSize;
	
protected:
	static System::Generics::Collections::TList__1<TShaderProgram*>* FPrograms;
	static TShaderProgram* FCurrentProgram;
	static TExtensions* __fastcall GetExtensions();
	unsigned FRenderBuf;
	unsigned FFrameBuf;
	unsigned FDepthBuf;
	unsigned FStencilBuf;
	bool FSupportMS;
	int FMSValue;
	unsigned FRenderBufMS;
	unsigned FFrameBufMS;
	unsigned FDepthBufMS;
	unsigned FOldFBO;
	System::StaticArray<int, 4> FOldViewport;
	bool FActivity;
	__classmethod int __fastcall BuildShader(int AType, const Fmx::Types3d::TContextShaderCode ACode);
	__classmethod TShaderProgram* __fastcall FindProgram(Fmx::Types3d::TContextShader* const VS, Fmx::Types3d::TContextShader* const PS);
	__classmethod void __fastcall UseProgram(Fmx::Types3d::TContextShader* const VS, Fmx::Types3d::TContextShader* const PS);
	virtual __classmethod Fmx::Types3d::TContextShaderArch __fastcall GetShaderArch() = 0 ;
	__classmethod void __fastcall DestroyPrograms();
	virtual __classmethod void __fastcall CreateSharedContext() = 0 ;
	virtual __classmethod void __fastcall DestroySharedContext() = 0 ;
	virtual void __fastcall DoResize();
	virtual void __fastcall DoFreeBuffer();
	virtual void __fastcall DoCopyToBitmap(Fmx::Graphics::TBitmap* const Dest, const System::Types::TRect &ARect);
	virtual void __fastcall DoCopyToBits(const void * Bits, const int Pitch, const System::Types::TRect &ARect);
	virtual void __fastcall DoClear(const Fmx::Types3d::TClearTargets ATarget, const System::Uitypes::TAlphaColor AColor, const float ADepth, const unsigned AStencil);
	virtual void __fastcall DoSetContextState(Fmx::Types3d::TContextState AState);
	virtual void __fastcall DoSetStencilOp(const Fmx::Types3d::TStencilOp Fail, const Fmx::Types3d::TStencilOp ZFail, const Fmx::Types3d::TStencilOp ZPass);
	virtual void __fastcall DoSetStencilFunc(const Fmx::Types3d::TStencilFunc Func, unsigned Ref, unsigned Mask);
	virtual void __fastcall DoDrawPrimitivesBatch(const Fmx::Types3d::TPrimitivesKind AKind, const void * Vertices, const void * Indices, const Fmx::Types3d::TVertexDeclaration VertexDeclaration, const int VertexSize, const int VertexCount, const int IndexSize, const int IndexCount);
	virtual void __fastcall DoDrawPrimitives(const Fmx::Types3d::TPrimitivesKind AKind, const void * Vertices, const void * Indices, const Fmx::Types3d::TVertexDeclaration VertexDeclaration, const int VertexSize, const int VertexCount, const int IndexSize, const int IndexCount);
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
	__fastcall virtual TCustomContextOpenGL(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil);
	virtual Fmx::Types3d::TContext3D::TIndexBufferSupport __fastcall GetIndexBufferSupport();
	
public:
	__classmethod bool __fastcall GLHasAnyErrors();
	/* static */ __property TExtensions* Extensions = {read=GetExtensions};
	__classmethod virtual Fmx::Types::TPixelFormat __fastcall PixelFormat();
	__classmethod virtual int __fastcall MaxTextureSize();
	__classmethod virtual int __fastcall TextureUnitCount();
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomContextOpenGL(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomContextOpenGL() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomContextOpenGL() : Fmx::Types3d::TContext3D() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TGlesDiagnostic : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TErrorBuffer
	{
	public:
		System::TArray__1<unsigned> Errors;
		int Count;
		void __fastcall AddError(const int AError);
		void __fastcall Clear();
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
private:
	static TErrorBuffer FErrorBuffer;
	
private:
	// __classmethod void __fastcall Create_();
	
private:
	__classmethod void __fastcall CollectErrors();
	__classmethod System::UnicodeString __fastcall GetDescription(const System::TArray__1<unsigned> AErrors);
	
public:
	__classmethod bool __fastcall IsWarning(const int ACode);
	__classmethod System::UnicodeString __fastcall TranslateErrorCode(const unsigned AErrorCode);
	__classmethod System::TArray__1<unsigned> __fastcall GetLastErrors();
	__classmethod void __fastcall RaiseIfHasError(const System::PResStringRec ARes, const System::TVarRec *AArgs, const int AArgs_High)/* overload */;
	
private:
	// __classmethod void __fastcall Destroy_();
public:
	/* TObject.Create */ inline __fastcall TGlesDiagnostic() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TGlesDiagnostic() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 ATTRIB_VERTEX = System::Int8(0x0);
static constexpr System::Int8 ATTRIB_NORMAL = System::Int8(0x1);
static constexpr System::Int8 ATTRIB_COLOR0 = System::Int8(0x2);
static constexpr System::Int8 ATTRIB_COLOR1 = System::Int8(0x3);
static constexpr System::Int8 ATTRIB_COLOR2 = System::Int8(0x4);
static constexpr System::Int8 ATTRIB_COLOR3 = System::Int8(0x5);
static constexpr System::Int8 ATTRIB_TEXCOORD0 = System::Int8(0x6);
static constexpr System::Int8 ATTRIB_TEXCOORD1 = System::Int8(0x7);
static constexpr System::Int8 ATTRIB_TEXCOORD2 = System::Int8(0x8);
static constexpr System::Int8 ATTRIB_TEXCOORD3 = System::Int8(0x9);
extern DELPHI_PACKAGE TOpenGlErrorReporting OpenGlErrorReporting;
extern DELPHI_PACKAGE void __fastcall RaiseContextExceptionFmt(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High);
extern DELPHI_PACKAGE int __fastcall MultisampleTypeToNumber(const Fmx::Types3d::TMultisample Multisample);
}	/* namespace Gles */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_GLES)
using namespace Fmx::Context::Gles;
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
#endif	// Fmx_Context_GlesHPP
