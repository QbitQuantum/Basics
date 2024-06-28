// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.DAE.Schema.GLES.pas' rev: 34.00 (Windows)

#ifndef Fmx_Dae_Schema_GlesHPP
#define Fmx_Dae_Schema_GlesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Xml.XMLDoc.hpp>
#include <Xml.XMLIntf.hpp>
#include <FMX.DAE.Schema.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Dae
{
namespace Schema
{
namespace Gles
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TXMLProfile_gles2_type;
class DELPHICLASS TXMLProfile_gles2_type_newparamList;
class DELPHICLASS TXMLProfile_gles2_type_technique;
class DELPHICLASS TXMLProfile_gles2_type_techniqueList;
class DELPHICLASS TXMLGles2_pass_type;
class DELPHICLASS TXMLGles2_pass_typeList;
class DELPHICLASS TXMLGles2_pass_type_states;
class DELPHICLASS TXMLFx_include_type;
class DELPHICLASS TXMLFx_include_typeList;
class DELPHICLASS TXMLFx_code_type;
class DELPHICLASS TXMLFx_code_typeList;
class DELPHICLASS TXMLGles2_newparam_type;
class DELPHICLASS TXMLProfile_gles2_type_newparam;
class DELPHICLASS TXMLFx_annotate_type;
class DELPHICLASS TXMLFx_annotate_typeList;
class DELPHICLASS TXMLFx_newparam_type;
class DELPHICLASS TXMLFx_newparam_typeList;
class DELPHICLASS TXMLFx_sampler_type;
class DELPHICLASS TXMLFx_sampler1D_type;
class DELPHICLASS TXMLFx_sampler2D_type;
class DELPHICLASS TXMLFx_sampler3D_type;
class DELPHICLASS TXMLFx_samplerCUBE_type;
class DELPHICLASS TXMLFx_samplerRECT_type;
class DELPHICLASS TXMLFx_samplerDEPTH_type;
class DELPHICLASS TXMLUsertype;
class DELPHICLASS TXMLUsertype_setparam;
class DELPHICLASS TXMLArray_;
class DELPHICLASS TXMLBlend_color;
class DELPHICLASS TXMLBlend_equation;
class DELPHICLASS TXMLBlend_equation_separate;
class DELPHICLASS TXMLBlend_equation_separate_rgb;
class DELPHICLASS TXMLBlend_equation_separate_alpha;
class DELPHICLASS TXMLBlend_func;
class DELPHICLASS TXMLBlend_func_src;
class DELPHICLASS TXMLBlend_func_dest;
class DELPHICLASS TXMLBlend_func_separate;
class DELPHICLASS TXMLBlend_func_separate_src_rgb;
class DELPHICLASS TXMLBlend_func_separate_dest_rgb;
class DELPHICLASS TXMLBlend_func_separate_src_alpha;
class DELPHICLASS TXMLBlend_func_separate_dest_alpha;
class DELPHICLASS TXMLColor_mask;
class DELPHICLASS TXMLCull_face;
class DELPHICLASS TXMLDepth_func;
class DELPHICLASS TXMLDepth_mask;
class DELPHICLASS TXMLDepth_range;
class DELPHICLASS TXMLFront_face;
class DELPHICLASS TXMLLine_width;
class DELPHICLASS TXMLPolygon_offset;
class DELPHICLASS TXMLPoint_size;
class DELPHICLASS TXMLSample_coverage;
class DELPHICLASS TXMLSample_coverage_value;
class DELPHICLASS TXMLSample_coverage_invert;
class DELPHICLASS TXMLScissor;
class DELPHICLASS TXMLStencil_func;
class DELPHICLASS TXMLStencil_func_func;
class DELPHICLASS TXMLStencil_func_ref;
class DELPHICLASS TXMLStencil_func_mask;
class DELPHICLASS TXMLStencil_func_separate;
class DELPHICLASS TXMLStencil_func_separate_front;
class DELPHICLASS TXMLStencil_func_separate_back;
class DELPHICLASS TXMLStencil_func_separate_ref;
class DELPHICLASS TXMLStencil_func_separate_mask;
class DELPHICLASS TXMLStencil_mask;
class DELPHICLASS TXMLStencil_mask_separate;
class DELPHICLASS TXMLStencil_mask_separate_face;
class DELPHICLASS TXMLStencil_mask_separate_mask;
class DELPHICLASS TXMLStencil_op;
class DELPHICLASS TXMLStencil_op_fail;
class DELPHICLASS TXMLStencil_op_zfail;
class DELPHICLASS TXMLStencil_op_zpass;
class DELPHICLASS TXMLStencil_op_separate;
class DELPHICLASS TXMLStencil_op_separate_face;
class DELPHICLASS TXMLStencil_op_separate_fail;
class DELPHICLASS TXMLStencil_op_separate_zfail;
class DELPHICLASS TXMLStencil_op_separate_zpass;
class DELPHICLASS TXMLBlend_enable;
class DELPHICLASS TXMLCull_face_enable;
class DELPHICLASS TXMLDepth_test_enable;
class DELPHICLASS TXMLDither_enable;
class DELPHICLASS TXMLPolygon_offset_fill_enable;
class DELPHICLASS TXMLPoint_size_enable;
class DELPHICLASS TXMLSample_alpha_to_coverage_enable;
class DELPHICLASS TXMLSample_coverage_enable;
class DELPHICLASS TXMLScissor_test_enable;
class DELPHICLASS TXMLStencil_test_enable;
class DELPHICLASS TXMLGles2_program_type;
class DELPHICLASS TXMLGles2_shader_type;
class DELPHICLASS TXMLGles2_shader_typeList;
class DELPHICLASS TXMLFx_sources_type;
class DELPHICLASS TXMLFx_sources_type_import;
class DELPHICLASS TXMLFx_sources_type_importList;
class DELPHICLASS TXMLGles2_shader_type_sources;
class DELPHICLASS TXMLFx_target_type;
class DELPHICLASS TXMLFx_target_typeList;
class DELPHICLASS TXMLFx_target_type_binary;
class DELPHICLASS TXMLFx_target_type_binary_hex;
class DELPHICLASS TXMLGles2_program_type_bind_attribute;
class DELPHICLASS TXMLGles2_program_type_bind_attributeList;
class DELPHICLASS TXMLGles2_program_type_bind_uniform;
class DELPHICLASS TXMLGles2_program_type_bind_uniformList;
class DELPHICLASS TXMLGles2_program_type_bind_uniform_param;
class DELPHICLASS TXMLGles2_pass_type_evaluate;
class DELPHICLASS TXMLFx_rendertarget_type;
class DELPHICLASS TXMLFx_rendertarget_type_param;
class DELPHICLASS TXMLFx_colortarget_type;
class DELPHICLASS TXMLFx_colortarget_typeList;
class DELPHICLASS TXMLFx_depthtarget_type;
class DELPHICLASS TXMLFx_depthtarget_typeList;
class DELPHICLASS TXMLFx_stenciltarget_type;
class DELPHICLASS TXMLFx_stenciltarget_typeList;
class DELPHICLASS TXMLFx_clearcolor_type;
class DELPHICLASS TXMLFx_clearcolor_typeList;
class DELPHICLASS TXMLFx_clearstencil_type;
class DELPHICLASS TXMLFx_clearstencil_typeList;
class DELPHICLASS TXMLFx_cleardepth_type;
class DELPHICLASS TXMLFx_cleardepth_typeList;
class DELPHICLASS TXMLProfile_glsl_type;
class DELPHICLASS TXMLGlsl_newparam_type;
class DELPHICLASS TXMLGlsl_newparam_typeList;
class DELPHICLASS TXMLGlsl_array_type;
class DELPHICLASS TXMLProfile_glsl_type_technique;
class DELPHICLASS TXMLProfile_glsl_type_techniqueList;
class DELPHICLASS TXMLProfile_glsl_type_technique_pass;
class DELPHICLASS TXMLProfile_glsl_type_technique_passList;
class DELPHICLASS TXMLProfile_glsl_type_technique_pass_states;
class DELPHICLASS TXMLString_List;
class DELPHICLASS TXMLGlsl_program_type;
class DELPHICLASS TXMLGlsl_shader_type;
class DELPHICLASS TXMLGlsl_shader_typeList;
class DELPHICLASS TXMLGlsl_program_type_bind_attribute;
class DELPHICLASS TXMLGlsl_program_type_bind_attributeList;
class DELPHICLASS TXMLGlsl_program_type_bind_uniform;
class DELPHICLASS TXMLGlsl_program_type_bind_uniformList;
class DELPHICLASS TXMLGlsl_program_type_bind_uniform_param;
class DELPHICLASS TXMLProfile_glsl_type_technique_pass_evaluate;
class DELPHICLASS TXMLAlpha_func;
class DELPHICLASS TXMLAlpha_func_func;
class DELPHICLASS TXMLAlpha_func_value;
class DELPHICLASS TXMLColor_material;
class DELPHICLASS TXMLColor_material_face;
class DELPHICLASS TXMLColor_material_mode;
class DELPHICLASS TXMLFog_mode;
class DELPHICLASS TXMLFog_coord_src;
class DELPHICLASS TXMLLight_model_color_control;
class DELPHICLASS TXMLLogic_op;
class DELPHICLASS TXMLPolygon_mode;
class DELPHICLASS TXMLPolygon_mode_face;
class DELPHICLASS TXMLPolygon_mode_mode;
class DELPHICLASS TXMLShade_model;
class DELPHICLASS TXMLLight_enable;
class DELPHICLASS TXMLLight_ambient;
class DELPHICLASS TXMLLight_diffuse;
class DELPHICLASS TXMLLight_specular;
class DELPHICLASS TXMLLight_position;
class DELPHICLASS TXMLLight_constant_attenuation;
class DELPHICLASS TXMLLight_linear_attenuation;
class DELPHICLASS TXMLLight_quadratic_attenuation;
class DELPHICLASS TXMLLight_spot_cutoff;
class DELPHICLASS TXMLLight_spot_direction;
class DELPHICLASS TXMLLight_spot_exponent;
class DELPHICLASS TXMLTexture1D;
class DELPHICLASS TXMLTexture2D;
class DELPHICLASS TXMLTexture3D;
class DELPHICLASS TXMLTextureCUBE;
class DELPHICLASS TXMLTextureRECT;
class DELPHICLASS TXMLTextureDEPTH;
class DELPHICLASS TXMLTexture1D_enable;
class DELPHICLASS TXMLTexture2D_enable;
class DELPHICLASS TXMLTexture3D_enable;
class DELPHICLASS TXMLTextureCUBE_enable;
class DELPHICLASS TXMLTextureRECT_enable;
class DELPHICLASS TXMLTextureDEPTH_enable;
class DELPHICLASS TXMLTexture_env_color;
class DELPHICLASS TXMLTexture_env_mode;
class DELPHICLASS TXMLClip_plane;
class DELPHICLASS TXMLClip_plane_enable;
class DELPHICLASS TXMLDepth_bounds;
class DELPHICLASS TXMLFog_density;
class DELPHICLASS TXMLFog_start;
class DELPHICLASS TXMLFog_end;
class DELPHICLASS TXMLFog_color;
class DELPHICLASS TXMLLight_model_ambient;
class DELPHICLASS TXMLLighting_enable;
class DELPHICLASS TXMLLine_stipple;
class DELPHICLASS TXMLMaterial_ambient;
class DELPHICLASS TXMLMaterial_diffuse;
class DELPHICLASS TXMLMaterial_emission;
class DELPHICLASS TXMLMaterial_shininess;
class DELPHICLASS TXMLMaterial_specular;
class DELPHICLASS TXMLModel_view_matrix;
class DELPHICLASS TXMLPoint_distance_attenuation;
class DELPHICLASS TXMLPoint_fade_threshold_size;
class DELPHICLASS TXMLPoint_size_min;
class DELPHICLASS TXMLPoint_size_max;
class DELPHICLASS TXMLProjection_matrix;
class DELPHICLASS TXMLAlpha_test_enable;
class DELPHICLASS TXMLColor_logic_op_enable;
class DELPHICLASS TXMLColor_material_enable;
class DELPHICLASS TXMLDepth_bounds_enable;
class DELPHICLASS TXMLDepth_clamp_enable;
class DELPHICLASS TXMLFog_enable;
class DELPHICLASS TXMLLight_model_local_viewer_enable;
class DELPHICLASS TXMLLight_model_two_side_enable;
class DELPHICLASS TXMLLine_smooth_enable;
class DELPHICLASS TXMLLine_stipple_enable;
class DELPHICLASS TXMLLogic_op_enable;
class DELPHICLASS TXMLMultisample_enable;
class DELPHICLASS TXMLNormalize_enable;
class DELPHICLASS TXMLPoint_smooth_enable;
class DELPHICLASS TXMLPolygon_offset_line_enable;
class DELPHICLASS TXMLPolygon_offset_point_enable;
class DELPHICLASS TXMLPolygon_smooth_enable;
class DELPHICLASS TXMLPolygon_stipple_enable;
class DELPHICLASS TXMLRescale_normal_enable;
class DELPHICLASS TXMLSample_alpha_to_one_enable;
class DELPHICLASS TXMLFx_common_newparam_type;
class DELPHICLASS TXMLFx_common_newparam_typeList;
class DELPHICLASS TXMLProfile_cg_type;
class DELPHICLASS TXMLCg_newparam_type;
class DELPHICLASS TXMLCg_newparam_typeList;
class DELPHICLASS TXMLCg_array_type;
class DELPHICLASS TXMLCg_user_type;
class DELPHICLASS TXMLCg_setparam_type;
class DELPHICLASS TXMLProfile_cg_type_technique;
class DELPHICLASS TXMLProfile_cg_type_techniqueList;
class DELPHICLASS TXMLCg_pass_type;
class DELPHICLASS TXMLCg_pass_typeList;
class DELPHICLASS TXMLCg_pass_type_states;
class DELPHICLASS TXMLCg_pass_type_program;
class DELPHICLASS TXMLCg_pass_type_program_shader;
class DELPHICLASS TXMLCg_pass_type_program_shader_sources;
class DELPHICLASS TXMLCg_pass_type_program_shader_bind_uniform;
class DELPHICLASS TXMLCg_pass_type_program_shader_bind_uniformList;
class DELPHICLASS TXMLCg_pass_type_program_shader_bind_uniform_param;
class DELPHICLASS TXMLCg_pass_type_evaluate;
class DELPHICLASS TXMLProfile_gles_type;
class DELPHICLASS TXMLGles_newparam_type;
class DELPHICLASS TXMLGles_newparam_typeList;
class DELPHICLASS TXMLGles_sampler_type;
class DELPHICLASS TXMLGles_sampler_type_texcoord;
class DELPHICLASS TXMLProfile_gles_type_technique;
class DELPHICLASS TXMLProfile_gles_type_techniqueList;
class DELPHICLASS TXMLProfile_gles_type_technique_pass;
class DELPHICLASS TXMLProfile_gles_type_technique_passList;
class DELPHICLASS TXMLProfile_gles_type_technique_pass_states;
class DELPHICLASS TXMLTexture_pipeline;
class DELPHICLASS TXMLGles_texture_pipeline_type;
class DELPHICLASS TXMLGles_texcombiner_command_type;
class DELPHICLASS TXMLGles_texcombiner_command_typeList;
class DELPHICLASS TXMLGles_texture_constant_type;
class DELPHICLASS TXMLGles_texcombiner_command_rgb_type;
class DELPHICLASS TXMLGles_texcombiner_argument_rgb_type;
class DELPHICLASS TXMLGles_texcombiner_command_alpha_type;
class DELPHICLASS TXMLGles_texcombiner_argument_alpha_type;
class DELPHICLASS TXMLGles_texenv_command_type;
class DELPHICLASS TXMLGles_texenv_command_typeList;
class DELPHICLASS TXMLProfile_gles_type_technique_pass_evaluate;
class DELPHICLASS TXMLProfile_common_type;
class DELPHICLASS TXMLProfile_bridge_type;
class DELPHICLASS TXMLProfile_common_type_technique;
class DELPHICLASS TXMLProfile_common_type_technique_constant;
class DELPHICLASS TXMLFx_common_color_or_texture_type;
class DELPHICLASS TXMLFx_common_color_or_texture_type_color;
class DELPHICLASS TXMLFx_common_color_or_texture_type_param;
class DELPHICLASS TXMLFx_common_color_or_texture_type_texture;
class DELPHICLASS TXMLFx_common_float_or_param_type;
class DELPHICLASS TXMLFx_common_float_or_param_type_float;
class DELPHICLASS TXMLFx_common_float_or_param_type_param;
class DELPHICLASS TXMLFx_common_transparent_type;
class DELPHICLASS TXMLProfile_common_type_technique_lambert;
class DELPHICLASS TXMLProfile_common_type_technique_phong;
class DELPHICLASS TXMLProfile_common_type_technique_blinn;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TXMLProfile_gles2_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList FInclude;
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList FCode;
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparamList FNewparam;
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_techniqueList FTechnique;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Language();
	System::UnicodeString __fastcall Get_Platforms();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList __fastcall Get_Include();
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList __fastcall Get_Code();
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparamList __fastcall Get_Newparam();
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_techniqueList __fastcall Get_Technique();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Language(System::UnicodeString Value);
	void __fastcall Set_Platforms(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles2_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles2_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles2_type() { }
	
private:
	void *__IXMLProfile_gles2_type;	// Fmx::Dae::Schema::IXMLProfile_gles2_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F2CA96D7-0563-45D4-82FA-28072215AD1F}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles2_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles2_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles2_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles2_type*)&__IXMLProfile_gles2_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles2_type_newparamList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparam __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparam __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparam __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles2_type_newparamList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles2_type_newparamList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles2_type_newparamList() { }
	
private:
	void *__IXMLProfile_gles2_type_newparamList;	// Fmx::Dae::Schema::IXMLProfile_gles2_type_newparamList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {15B5BFB0-79F9-46A5-98F1-749C6477D1F1}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparamList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparamList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles2_type_newparamList*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles2_type_newparamList*)&__IXMLProfile_gles2_type_newparamList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles2_type_technique : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLGles2_pass_typeList FPass;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLGles2_pass_typeList __fastcall Get_Pass();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles2_type_technique(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles2_type_technique(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles2_type_technique() { }
	
private:
	void *__IXMLProfile_gles2_type_technique;	// Fmx::Dae::Schema::IXMLProfile_gles2_type_technique 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2EB162F7-F0CE-4887-B51E-3EE7E5392DFE}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_technique()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_technique intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles2_type_technique*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles2_type_technique*)&__IXMLProfile_gles2_type_technique; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles2_type_techniqueList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_technique __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_technique __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_technique __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles2_type_techniqueList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles2_type_techniqueList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles2_type_techniqueList() { }
	
private:
	void *__IXMLProfile_gles2_type_techniqueList;	// Fmx::Dae::Schema::IXMLProfile_gles2_type_techniqueList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ED2DFC28-0CDC-4AEE-8245-81DCD15CA371}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_techniqueList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_techniqueList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles2_type_techniqueList*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles2_type_techniqueList*)&__IXMLProfile_gles2_type_techniqueList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_pass_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLGles2_pass_type_states __fastcall Get_States();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type __fastcall Get_Program_();
	Fmx::Dae::Schema::_di_IXMLGles2_pass_type_evaluate __fastcall Get_Evaluate();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_pass_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_pass_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_pass_type() { }
	
private:
	void *__IXMLGles2_pass_type;	// Fmx::Dae::Schema::IXMLGles2_pass_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8C2BA657-1E5B-4E86-95C2-66486137DA2E}
	operator Fmx::Dae::Schema::_di_IXMLGles2_pass_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_pass_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_pass_type*(void) { return (Fmx::Dae::Schema::IXMLGles2_pass_type*)&__IXMLGles2_pass_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_pass_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles2_pass_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles2_pass_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles2_pass_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_pass_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_pass_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_pass_typeList() { }
	
private:
	void *__IXMLGles2_pass_typeList;	// Fmx::Dae::Schema::IXMLGles2_pass_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B841D5EE-E8AF-479F-A35C-479D7ED83501}
	operator Fmx::Dae::Schema::_di_IXMLGles2_pass_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_pass_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_pass_typeList*(void) { return (Fmx::Dae::Schema::IXMLGles2_pass_typeList*)&__IXMLGles2_pass_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_pass_type_states : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLBlend_color __fastcall Get_Blend_color();
	Fmx::Dae::Schema::_di_IXMLBlend_equation __fastcall Get_Blend_equation();
	Fmx::Dae::Schema::_di_IXMLBlend_equation_separate __fastcall Get_Blend_equation_separate();
	Fmx::Dae::Schema::_di_IXMLBlend_func __fastcall Get_Blend_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate __fastcall Get_Blend_func_separate();
	Fmx::Dae::Schema::_di_IXMLColor_mask __fastcall Get_Color_mask();
	Fmx::Dae::Schema::_di_IXMLCull_face __fastcall Get_Cull_face();
	Fmx::Dae::Schema::_di_IXMLDepth_func __fastcall Get_Depth_func();
	Fmx::Dae::Schema::_di_IXMLDepth_mask __fastcall Get_Depth_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_range __fastcall Get_Depth_range();
	Fmx::Dae::Schema::_di_IXMLFront_face __fastcall Get_Front_face();
	Fmx::Dae::Schema::_di_IXMLLine_width __fastcall Get_Line_width();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset __fastcall Get_Polygon_offset();
	Fmx::Dae::Schema::_di_IXMLPoint_size __fastcall Get_Point_size();
	Fmx::Dae::Schema::_di_IXMLSample_coverage __fastcall Get_Sample_coverage();
	Fmx::Dae::Schema::_di_IXMLScissor __fastcall Get_Scissor();
	Fmx::Dae::Schema::_di_IXMLStencil_func __fastcall Get_Stencil_func();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate __fastcall Get_Stencil_func_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_mask __fastcall Get_Stencil_mask();
	Fmx::Dae::Schema::_di_IXMLStencil_mask_separate __fastcall Get_Stencil_mask_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_op __fastcall Get_Stencil_op();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate __fastcall Get_Stencil_op_separate();
	Fmx::Dae::Schema::_di_IXMLBlend_enable __fastcall Get_Blend_enable();
	Fmx::Dae::Schema::_di_IXMLCull_face_enable __fastcall Get_Cull_face_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_test_enable __fastcall Get_Depth_test_enable();
	Fmx::Dae::Schema::_di_IXMLDither_enable __fastcall Get_Dither_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable __fastcall Get_Polygon_offset_fill_enable();
	Fmx::Dae::Schema::_di_IXMLPoint_size_enable __fastcall Get_Point_size_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable __fastcall Get_Sample_alpha_to_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLSample_coverage_enable __fastcall Get_Sample_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLScissor_test_enable __fastcall Get_Scissor_test_enable();
	Fmx::Dae::Schema::_di_IXMLStencil_test_enable __fastcall Get_Stencil_test_enable();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_pass_type_states(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_pass_type_states(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_pass_type_states() { }
	
private:
	void *__IXMLGles2_pass_type_states;	// Fmx::Dae::Schema::IXMLGles2_pass_type_states 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {018F1334-9908-4A38-8475-C6E50AE9FCC0}
	operator Fmx::Dae::Schema::_di_IXMLGles2_pass_type_states()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_pass_type_states intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_pass_type_states*(void) { return (Fmx::Dae::Schema::IXMLGles2_pass_type_states*)&__IXMLGles2_pass_type_states; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_include_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	System::UnicodeString __fastcall Get_Url();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Url(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_include_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_include_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_include_type() { }
	
private:
	void *__IXMLFx_include_type;	// Fmx::Dae::Schema::IXMLFx_include_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4DFB402E-EB80-462B-A01C-BF576D63A852}
	operator Fmx::Dae::Schema::_di_IXMLFx_include_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_include_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_include_type*(void) { return (Fmx::Dae::Schema::IXMLFx_include_type*)&__IXMLFx_include_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_include_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_include_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_include_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_include_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_include_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_include_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_include_typeList() { }
	
private:
	void *__IXMLFx_include_typeList;	// Fmx::Dae::Schema::IXMLFx_include_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B8378A46-0AE4-43B8-8BD3-FDBB43905472}
	operator Fmx::Dae::Schema::_di_IXMLFx_include_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_include_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_include_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_include_typeList*)&__IXMLFx_include_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_code_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	void __fastcall Set_Sid(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_code_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_code_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_code_type() { }
	
private:
	void *__IXMLFx_code_type;	// Fmx::Dae::Schema::IXMLFx_code_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6C258B65-487D-441E-86D7-0A3667A9597E}
	operator Fmx::Dae::Schema::_di_IXMLFx_code_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_code_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_code_type*(void) { return (Fmx::Dae::Schema::IXMLFx_code_type*)&__IXMLFx_code_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_code_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_code_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_code_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_code_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_code_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_code_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_code_typeList() { }
	
private:
	void *__IXMLFx_code_typeList;	// Fmx::Dae::Schema::IXMLFx_code_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8E3E971E-AE0B-4465-9A9B-A42BBB104891}
	operator Fmx::Dae::Schema::_di_IXMLFx_code_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_code_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_code_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_code_typeList*)&__IXMLFx_code_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	System::UnicodeString __fastcall Get_Semantic();
	System::UnicodeString __fastcall Get_Modifier();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bvec2();
	System::UnicodeString __fastcall Get_Bvec3();
	System::UnicodeString __fastcall Get_Bvec4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Vec2();
	System::UnicodeString __fastcall Get_Vec3();
	System::UnicodeString __fastcall Get_Vec4();
	System::UnicodeString __fastcall Get_Mat2();
	System::UnicodeString __fastcall Get_Mat3();
	System::UnicodeString __fastcall Get_Mat4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Ivec2();
	System::UnicodeString __fastcall Get_Ivec3();
	System::UnicodeString __fastcall Get_Ivec4();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	Fmx::Dae::Schema::_di_IXMLUsertype __fastcall Get_Usertype();
	Fmx::Dae::Schema::_di_IXMLArray_ __fastcall Get_Array_();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Modifier(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bvec2(System::UnicodeString Value);
	void __fastcall Set_Bvec3(System::UnicodeString Value);
	void __fastcall Set_Bvec4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Vec2(System::UnicodeString Value);
	void __fastcall Set_Vec3(System::UnicodeString Value);
	void __fastcall Set_Vec4(System::UnicodeString Value);
	void __fastcall Set_Mat2(System::UnicodeString Value);
	void __fastcall Set_Mat3(System::UnicodeString Value);
	void __fastcall Set_Mat4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Ivec2(System::UnicodeString Value);
	void __fastcall Set_Ivec3(System::UnicodeString Value);
	void __fastcall Set_Ivec4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_newparam_type() { }
	
private:
	void *__IXMLGles2_newparam_type;	// Fmx::Dae::Schema::IXMLGles2_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F2E5674E-EFA1-4FB4-96E4-21173AE56B95}
	operator Fmx::Dae::Schema::_di_IXMLGles2_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLGles2_newparam_type*)&__IXMLGles2_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles2_type_newparam : public TXMLGles2_newparam_type
{
	typedef TXMLGles2_newparam_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles2_type_newparam(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLGles2_newparam_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles2_type_newparam(Xml::Xmldoc::TXMLNode* HostNode) : TXMLGles2_newparam_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles2_type_newparam() { }
	
private:
	void *__IXMLProfile_gles2_type_newparam;	// Fmx::Dae::Schema::IXMLProfile_gles2_type_newparam 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D614A322-1853-45FB-8525-1B9A2B3BF0BE}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparam()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles2_type_newparam intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles2_type_newparam*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles2_type_newparam*)&__IXMLProfile_gles2_type_newparam; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_annotate_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Name();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float4x4();
	System::UnicodeString __fastcall Get_String_();
	void __fastcall Set_Name(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_String_(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_annotate_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_annotate_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_annotate_type() { }
	
private:
	void *__IXMLFx_annotate_type;	// Fmx::Dae::Schema::IXMLFx_annotate_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C0E534A3-F941-499B-A9DC-794519CA4431}
	operator Fmx::Dae::Schema::_di_IXMLFx_annotate_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_annotate_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_annotate_type*(void) { return (Fmx::Dae::Schema::IXMLFx_annotate_type*)&__IXMLFx_annotate_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_annotate_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_annotate_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_annotate_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_annotate_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_annotate_typeList() { }
	
private:
	void *__IXMLFx_annotate_typeList;	// Fmx::Dae::Schema::IXMLFx_annotate_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1FE321B4-FE0D-4B88-BDCA-8F28E169772F}
	operator Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_annotate_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_annotate_typeList*)&__IXMLFx_annotate_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	System::UnicodeString __fastcall Get_Semantic();
	System::UnicodeString __fastcall Get_Modifier();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_Enum();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Modifier(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_newparam_type() { }
	
private:
	void *__IXMLFx_newparam_type;	// Fmx::Dae::Schema::IXMLFx_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6AB5EED5-7318-4C45-9E10-6FB44609226A}
	operator Fmx::Dae::Schema::_di_IXMLFx_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLFx_newparam_type*)&__IXMLFx_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_newparam_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_newparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_newparam_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_newparam_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_newparam_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_newparam_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_newparam_typeList() { }
	
private:
	void *__IXMLFx_newparam_typeList;	// Fmx::Dae::Schema::IXMLFx_newparam_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {901883AF-47EB-45FB-9925-82736EAB7391}
	operator Fmx::Dae::Schema::_di_IXMLFx_newparam_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_newparam_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_newparam_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_newparam_typeList*)&__IXMLFx_newparam_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sampler_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	Fmx::Dae::Schema::_di_IXMLInstance_image_type __fastcall Get_Instance_image();
	System::UnicodeString __fastcall Get_Wrap_s();
	System::UnicodeString __fastcall Get_Wrap_t();
	System::UnicodeString __fastcall Get_Wrap_p();
	System::UnicodeString __fastcall Get_Minfilter();
	System::UnicodeString __fastcall Get_Magfilter();
	System::UnicodeString __fastcall Get_Mipfilter();
	System::UnicodeString __fastcall Get_Border_color();
	System::Byte __fastcall Get_Mip_max_level();
	System::Byte __fastcall Get_Mip_min_level();
	float __fastcall Get_Mip_bias();
	unsigned __fastcall Get_Max_anisotropy();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Wrap_s(System::UnicodeString Value);
	void __fastcall Set_Wrap_t(System::UnicodeString Value);
	void __fastcall Set_Wrap_p(System::UnicodeString Value);
	void __fastcall Set_Minfilter(System::UnicodeString Value);
	void __fastcall Set_Magfilter(System::UnicodeString Value);
	void __fastcall Set_Mipfilter(System::UnicodeString Value);
	void __fastcall Set_Border_color(System::UnicodeString Value);
	void __fastcall Set_Mip_max_level(System::Byte Value);
	void __fastcall Set_Mip_min_level(System::Byte Value);
	void __fastcall Set_Mip_bias(float Value);
	void __fastcall Set_Max_anisotropy(unsigned Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sampler_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sampler_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sampler_type() { }
	
private:
	void *__IXMLFx_sampler_type;	// Fmx::Dae::Schema::IXMLFx_sampler_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A419CA5C-F775-4567-AF24-F4931061DE8B}
	operator Fmx::Dae::Schema::_di_IXMLFx_sampler_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sampler_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sampler_type*(void) { return (Fmx::Dae::Schema::IXMLFx_sampler_type*)&__IXMLFx_sampler_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sampler1D_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sampler1D_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sampler1D_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sampler1D_type() { }
	
private:
	void *__IXMLFx_sampler1D_type;	// Fmx::Dae::Schema::IXMLFx_sampler1D_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59FC363E-6863-4003-9C59-2F12E20B23A6}
	operator Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sampler1D_type*(void) { return (Fmx::Dae::Schema::IXMLFx_sampler1D_type*)&__IXMLFx_sampler1D_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sampler2D_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sampler2D_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sampler2D_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sampler2D_type() { }
	
private:
	void *__IXMLFx_sampler2D_type;	// Fmx::Dae::Schema::IXMLFx_sampler2D_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {728A290B-EEE0-44A3-BDEF-DA10AEE9AB06}
	operator Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sampler2D_type*(void) { return (Fmx::Dae::Schema::IXMLFx_sampler2D_type*)&__IXMLFx_sampler2D_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sampler3D_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sampler3D_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sampler3D_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sampler3D_type() { }
	
private:
	void *__IXMLFx_sampler3D_type;	// Fmx::Dae::Schema::IXMLFx_sampler3D_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AB2E9F42-AA0F-4007-8D4B-B80935774D2C}
	operator Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sampler3D_type*(void) { return (Fmx::Dae::Schema::IXMLFx_sampler3D_type*)&__IXMLFx_sampler3D_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_samplerCUBE_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_samplerCUBE_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_samplerCUBE_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_samplerCUBE_type() { }
	
private:
	void *__IXMLFx_samplerCUBE_type;	// Fmx::Dae::Schema::IXMLFx_samplerCUBE_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D6050EDD-66EF-47B9-B829-40EDA11E3F6A}
	operator Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_samplerCUBE_type*(void) { return (Fmx::Dae::Schema::IXMLFx_samplerCUBE_type*)&__IXMLFx_samplerCUBE_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_samplerRECT_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_samplerRECT_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_samplerRECT_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_samplerRECT_type() { }
	
private:
	void *__IXMLFx_samplerRECT_type;	// Fmx::Dae::Schema::IXMLFx_samplerRECT_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ADF41962-E3E9-42AE-BA09-EE99943B5113}
	operator Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_samplerRECT_type*(void) { return (Fmx::Dae::Schema::IXMLFx_samplerRECT_type*)&__IXMLFx_samplerRECT_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_samplerDEPTH_type : public TXMLFx_sampler_type
{
	typedef TXMLFx_sampler_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_samplerDEPTH_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sampler_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_samplerDEPTH_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sampler_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_samplerDEPTH_type() { }
	
private:
	void *__IXMLFx_samplerDEPTH_type;	// Fmx::Dae::Schema::IXMLFx_samplerDEPTH_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A94FED81-7F9D-477B-B128-EC02427EDDC0}
	operator Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_samplerDEPTH_type*(void) { return (Fmx::Dae::Schema::IXMLFx_samplerDEPTH_type*)&__IXMLFx_samplerDEPTH_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLUsertype : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	System::UnicodeString __fastcall Get_Typename();
	Fmx::Dae::Schema::_di_IXMLUsertype_setparam __fastcall Get_Setparam(int Index);
	void __fastcall Set_Typename(System::UnicodeString Value);
	Fmx::Dae::Schema::_di_IXMLUsertype_setparam __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLUsertype_setparam __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLUsertype(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLUsertype(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLUsertype() { }
	
private:
	void *__IXMLUsertype;	// Fmx::Dae::Schema::IXMLUsertype 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A2AFABAD-5ECE-4604-BDFA-81D3F6B93A79}
	operator Fmx::Dae::Schema::_di_IXMLUsertype()
	{
		Fmx::Dae::Schema::_di_IXMLUsertype intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLUsertype*(void) { return (Fmx::Dae::Schema::IXMLUsertype*)&__IXMLUsertype; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLUsertype_setparam : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bvec2();
	System::UnicodeString __fastcall Get_Bvec3();
	System::UnicodeString __fastcall Get_Bvec4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Vec2();
	System::UnicodeString __fastcall Get_Vec3();
	System::UnicodeString __fastcall Get_Vec4();
	System::UnicodeString __fastcall Get_Mat2();
	System::UnicodeString __fastcall Get_Mat3();
	System::UnicodeString __fastcall Get_Mat4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Ivec2();
	System::UnicodeString __fastcall Get_Ivec3();
	System::UnicodeString __fastcall Get_Ivec4();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	Fmx::Dae::Schema::_di_IXMLUsertype __fastcall Get_Usertype();
	Fmx::Dae::Schema::_di_IXMLArray_ __fastcall Get_Array_();
	void __fastcall Set_Ref(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bvec2(System::UnicodeString Value);
	void __fastcall Set_Bvec3(System::UnicodeString Value);
	void __fastcall Set_Bvec4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Vec2(System::UnicodeString Value);
	void __fastcall Set_Vec3(System::UnicodeString Value);
	void __fastcall Set_Vec4(System::UnicodeString Value);
	void __fastcall Set_Mat2(System::UnicodeString Value);
	void __fastcall Set_Mat3(System::UnicodeString Value);
	void __fastcall Set_Mat4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Ivec2(System::UnicodeString Value);
	void __fastcall Set_Ivec3(System::UnicodeString Value);
	void __fastcall Set_Ivec4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLUsertype_setparam(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLUsertype_setparam(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLUsertype_setparam() { }
	
private:
	void *__IXMLUsertype_setparam;	// Fmx::Dae::Schema::IXMLUsertype_setparam 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CA023DFF-33FB-4433-89AA-F31947E67626}
	operator Fmx::Dae::Schema::_di_IXMLUsertype_setparam()
	{
		Fmx::Dae::Schema::_di_IXMLUsertype_setparam intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLUsertype_setparam*(void) { return (Fmx::Dae::Schema::IXMLUsertype_setparam*)&__IXMLUsertype_setparam; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLArray_ : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Length();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bvec2();
	System::UnicodeString __fastcall Get_Bvec3();
	System::UnicodeString __fastcall Get_Bvec4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Vec2();
	System::UnicodeString __fastcall Get_Vec3();
	System::UnicodeString __fastcall Get_Vec4();
	System::UnicodeString __fastcall Get_Mat2();
	System::UnicodeString __fastcall Get_Mat3();
	System::UnicodeString __fastcall Get_Mat4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Ivec2();
	System::UnicodeString __fastcall Get_Ivec3();
	System::UnicodeString __fastcall Get_Ivec4();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	Fmx::Dae::Schema::_di_IXMLUsertype __fastcall Get_Usertype();
	Fmx::Dae::Schema::_di_IXMLArray_ __fastcall Get_Array_();
	void __fastcall Set_Length(unsigned Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bvec2(System::UnicodeString Value);
	void __fastcall Set_Bvec3(System::UnicodeString Value);
	void __fastcall Set_Bvec4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Vec2(System::UnicodeString Value);
	void __fastcall Set_Vec3(System::UnicodeString Value);
	void __fastcall Set_Vec4(System::UnicodeString Value);
	void __fastcall Set_Mat2(System::UnicodeString Value);
	void __fastcall Set_Mat3(System::UnicodeString Value);
	void __fastcall Set_Mat4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Ivec2(System::UnicodeString Value);
	void __fastcall Set_Ivec3(System::UnicodeString Value);
	void __fastcall Set_Ivec4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLArray_(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLArray_(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLArray_() { }
	
private:
	void *__IXMLArray_;	// Fmx::Dae::Schema::IXMLArray_ 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {19C8E30C-07BF-4FA6-AC1A-6245FFC7A1EC}
	operator Fmx::Dae::Schema::_di_IXMLArray_()
	{
		Fmx::Dae::Schema::_di_IXMLArray_ intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLArray_*(void) { return (Fmx::Dae::Schema::IXMLArray_*)&__IXMLArray_; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_color : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_color(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_color(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_color() { }
	
private:
	void *__IXMLBlend_color;	// Fmx::Dae::Schema::IXMLBlend_color 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {674FE4E7-799C-4B28-A7BD-646419E85724}
	operator Fmx::Dae::Schema::_di_IXMLBlend_color()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_color intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_color*(void) { return (Fmx::Dae::Schema::IXMLBlend_color*)&__IXMLBlend_color; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_equation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_equation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_equation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_equation() { }
	
private:
	void *__IXMLBlend_equation;	// Fmx::Dae::Schema::IXMLBlend_equation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BD7C00A6-9116-4242-9EC2-2FC65C76F4C7}
	operator Fmx::Dae::Schema::_di_IXMLBlend_equation()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_equation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_equation*(void) { return (Fmx::Dae::Schema::IXMLBlend_equation*)&__IXMLBlend_equation; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_equation_separate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_rgb __fastcall Get_Rgb();
	Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_alpha __fastcall Get_Alpha();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_equation_separate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_equation_separate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_equation_separate() { }
	
private:
	void *__IXMLBlend_equation_separate;	// Fmx::Dae::Schema::IXMLBlend_equation_separate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5A4BC664-20A6-40D2-9CA0-40AE21FF86C9}
	operator Fmx::Dae::Schema::_di_IXMLBlend_equation_separate()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_equation_separate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_equation_separate*(void) { return (Fmx::Dae::Schema::IXMLBlend_equation_separate*)&__IXMLBlend_equation_separate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_equation_separate_rgb : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_equation_separate_rgb(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_equation_separate_rgb(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_equation_separate_rgb() { }
	
private:
	void *__IXMLBlend_equation_separate_rgb;	// Fmx::Dae::Schema::IXMLBlend_equation_separate_rgb 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AE255DEC-76FD-4250-9A1A-B0A3038547B3}
	operator Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_rgb()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_rgb intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_equation_separate_rgb*(void) { return (Fmx::Dae::Schema::IXMLBlend_equation_separate_rgb*)&__IXMLBlend_equation_separate_rgb; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_equation_separate_alpha : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_equation_separate_alpha(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_equation_separate_alpha(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_equation_separate_alpha() { }
	
private:
	void *__IXMLBlend_equation_separate_alpha;	// Fmx::Dae::Schema::IXMLBlend_equation_separate_alpha 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E7847259-7977-485B-9D3A-CF3803A68A4C}
	operator Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_alpha()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_equation_separate_alpha intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_equation_separate_alpha*(void) { return (Fmx::Dae::Schema::IXMLBlend_equation_separate_alpha*)&__IXMLBlend_equation_separate_alpha; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLBlend_func_src __fastcall Get_Src();
	Fmx::Dae::Schema::_di_IXMLBlend_func_dest __fastcall Get_Dest();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func() { }
	
private:
	void *__IXMLBlend_func;	// Fmx::Dae::Schema::IXMLBlend_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7188855C-155C-4CDA-8880-ADC69EDF4E84}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func*(void) { return (Fmx::Dae::Schema::IXMLBlend_func*)&__IXMLBlend_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_src : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_src(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_src(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_src() { }
	
private:
	void *__IXMLBlend_func_src;	// Fmx::Dae::Schema::IXMLBlend_func_src 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5FADDFFC-3B16-44F4-BE19-3A7822150685}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_src()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_src intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_src*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_src*)&__IXMLBlend_func_src; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_dest : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_dest(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_dest(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_dest() { }
	
private:
	void *__IXMLBlend_func_dest;	// Fmx::Dae::Schema::IXMLBlend_func_dest 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3881BF94-3FCB-48C9-9B49-F28016997716}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_dest()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_dest intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_dest*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_dest*)&__IXMLBlend_func_dest; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_separate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_rgb __fastcall Get_Src_rgb();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_rgb __fastcall Get_Dest_rgb();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_alpha __fastcall Get_Src_alpha();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_alpha __fastcall Get_Dest_alpha();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_separate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_separate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_separate() { }
	
private:
	void *__IXMLBlend_func_separate;	// Fmx::Dae::Schema::IXMLBlend_func_separate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F05DB67D-7665-4D68-871E-C74050D49BFF}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_separate()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_separate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_separate*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_separate*)&__IXMLBlend_func_separate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_separate_src_rgb : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_separate_src_rgb(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_separate_src_rgb(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_separate_src_rgb() { }
	
private:
	void *__IXMLBlend_func_separate_src_rgb;	// Fmx::Dae::Schema::IXMLBlend_func_separate_src_rgb 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C0354622-870F-4B08-8CB2-AE6870682A24}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_rgb()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_rgb intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_separate_src_rgb*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_separate_src_rgb*)&__IXMLBlend_func_separate_src_rgb; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_separate_dest_rgb : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_separate_dest_rgb(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_separate_dest_rgb(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_separate_dest_rgb() { }
	
private:
	void *__IXMLBlend_func_separate_dest_rgb;	// Fmx::Dae::Schema::IXMLBlend_func_separate_dest_rgb 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AA37E7AE-9EC6-4E71-A319-86EEDBF34EE4}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_rgb()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_rgb intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_separate_dest_rgb*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_separate_dest_rgb*)&__IXMLBlend_func_separate_dest_rgb; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_separate_src_alpha : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_separate_src_alpha(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_separate_src_alpha(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_separate_src_alpha() { }
	
private:
	void *__IXMLBlend_func_separate_src_alpha;	// Fmx::Dae::Schema::IXMLBlend_func_separate_src_alpha 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E17F33C2-79DE-49D2-8D78-C1CC460FFFB2}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_alpha()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_separate_src_alpha intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_separate_src_alpha*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_separate_src_alpha*)&__IXMLBlend_func_separate_src_alpha; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_func_separate_dest_alpha : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_func_separate_dest_alpha(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_func_separate_dest_alpha(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_func_separate_dest_alpha() { }
	
private:
	void *__IXMLBlend_func_separate_dest_alpha;	// Fmx::Dae::Schema::IXMLBlend_func_separate_dest_alpha 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {57432EAD-49FA-4242-A21B-6C7ABB09077B}
	operator Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_alpha()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_func_separate_dest_alpha intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_func_separate_dest_alpha*(void) { return (Fmx::Dae::Schema::IXMLBlend_func_separate_dest_alpha*)&__IXMLBlend_func_separate_dest_alpha; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_mask() { }
	
private:
	void *__IXMLColor_mask;	// Fmx::Dae::Schema::IXMLColor_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6BF5C117-2DD2-4221-81B9-B24CAA82E459}
	operator Fmx::Dae::Schema::_di_IXMLColor_mask()
	{
		Fmx::Dae::Schema::_di_IXMLColor_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_mask*(void) { return (Fmx::Dae::Schema::IXMLColor_mask*)&__IXMLColor_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCull_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCull_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCull_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCull_face() { }
	
private:
	void *__IXMLCull_face;	// Fmx::Dae::Schema::IXMLCull_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {25319C70-EE05-490E-AEA9-B17A40230615}
	operator Fmx::Dae::Schema::_di_IXMLCull_face()
	{
		Fmx::Dae::Schema::_di_IXMLCull_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCull_face*(void) { return (Fmx::Dae::Schema::IXMLCull_face*)&__IXMLCull_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_func() { }
	
private:
	void *__IXMLDepth_func;	// Fmx::Dae::Schema::IXMLDepth_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5321E23F-F8A3-4385-B361-25FEABAC3D5E}
	operator Fmx::Dae::Schema::_di_IXMLDepth_func()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_func*(void) { return (Fmx::Dae::Schema::IXMLDepth_func*)&__IXMLDepth_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_mask() { }
	
private:
	void *__IXMLDepth_mask;	// Fmx::Dae::Schema::IXMLDepth_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7572901B-850B-4C20-8F37-86D622B236CC}
	operator Fmx::Dae::Schema::_di_IXMLDepth_mask()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_mask*(void) { return (Fmx::Dae::Schema::IXMLDepth_mask*)&__IXMLDepth_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_range : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_range(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_range(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_range() { }
	
private:
	void *__IXMLDepth_range;	// Fmx::Dae::Schema::IXMLDepth_range 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EBABAF4D-B9EB-488D-BB6C-E3A1B93EF208}
	operator Fmx::Dae::Schema::_di_IXMLDepth_range()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_range intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_range*(void) { return (Fmx::Dae::Schema::IXMLDepth_range*)&__IXMLDepth_range; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFront_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFront_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFront_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFront_face() { }
	
private:
	void *__IXMLFront_face;	// Fmx::Dae::Schema::IXMLFront_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AC24AF4F-5937-4018-AF03-E875D132C320}
	operator Fmx::Dae::Schema::_di_IXMLFront_face()
	{
		Fmx::Dae::Schema::_di_IXMLFront_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFront_face*(void) { return (Fmx::Dae::Schema::IXMLFront_face*)&__IXMLFront_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLine_width : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLine_width(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLine_width(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLine_width() { }
	
private:
	void *__IXMLLine_width;	// Fmx::Dae::Schema::IXMLLine_width 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2F556C8B-AA5B-4ECE-B98B-ABE3F1F9995F}
	operator Fmx::Dae::Schema::_di_IXMLLine_width()
	{
		Fmx::Dae::Schema::_di_IXMLLine_width intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLine_width*(void) { return (Fmx::Dae::Schema::IXMLLine_width*)&__IXMLLine_width; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_offset : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_offset(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_offset(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_offset() { }
	
private:
	void *__IXMLPolygon_offset;	// Fmx::Dae::Schema::IXMLPolygon_offset 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {25D5856C-3E19-4245-8D25-15CB30DA7EC5}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_offset()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_offset intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_offset*(void) { return (Fmx::Dae::Schema::IXMLPolygon_offset*)&__IXMLPolygon_offset; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_size : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_size(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_size(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_size() { }
	
private:
	void *__IXMLPoint_size;	// Fmx::Dae::Schema::IXMLPoint_size 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0C955864-C21E-4F3C-AFA9-32DC3EDD6E5F}
	operator Fmx::Dae::Schema::_di_IXMLPoint_size()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_size intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_size*(void) { return (Fmx::Dae::Schema::IXMLPoint_size*)&__IXMLPoint_size; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_coverage : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLSample_coverage_value __fastcall Get_Value();
	Fmx::Dae::Schema::_di_IXMLSample_coverage_invert __fastcall Get_Invert();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_coverage(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_coverage(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_coverage() { }
	
private:
	void *__IXMLSample_coverage;	// Fmx::Dae::Schema::IXMLSample_coverage 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAB96057-AC6F-4699-897A-E409B425CF1B}
	operator Fmx::Dae::Schema::_di_IXMLSample_coverage()
	{
		Fmx::Dae::Schema::_di_IXMLSample_coverage intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_coverage*(void) { return (Fmx::Dae::Schema::IXMLSample_coverage*)&__IXMLSample_coverage; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_coverage_value : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	float __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(float Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_coverage_value(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_coverage_value(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_coverage_value() { }
	
private:
	void *__IXMLSample_coverage_value;	// Fmx::Dae::Schema::IXMLSample_coverage_value 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {88CFA444-15EE-4271-B429-BF68B970848D}
	operator Fmx::Dae::Schema::_di_IXMLSample_coverage_value()
	{
		Fmx::Dae::Schema::_di_IXMLSample_coverage_value intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_coverage_value*(void) { return (Fmx::Dae::Schema::IXMLSample_coverage_value*)&__IXMLSample_coverage_value; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_coverage_invert : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_coverage_invert(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_coverage_invert(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_coverage_invert() { }
	
private:
	void *__IXMLSample_coverage_invert;	// Fmx::Dae::Schema::IXMLSample_coverage_invert 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F794CAD4-6CAA-4620-88AC-C82FE3566D38}
	operator Fmx::Dae::Schema::_di_IXMLSample_coverage_invert()
	{
		Fmx::Dae::Schema::_di_IXMLSample_coverage_invert intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_coverage_invert*(void) { return (Fmx::Dae::Schema::IXMLSample_coverage_invert*)&__IXMLSample_coverage_invert; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLScissor : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLScissor(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLScissor(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLScissor() { }
	
private:
	void *__IXMLScissor;	// Fmx::Dae::Schema::IXMLScissor 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D1A26B41-5860-435A-97C4-2352B7F9DB7A}
	operator Fmx::Dae::Schema::_di_IXMLScissor()
	{
		Fmx::Dae::Schema::_di_IXMLScissor intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLScissor*(void) { return (Fmx::Dae::Schema::IXMLScissor*)&__IXMLScissor; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLStencil_func_func __fastcall Get_Func();
	Fmx::Dae::Schema::_di_IXMLStencil_func_ref __fastcall Get_Ref();
	Fmx::Dae::Schema::_di_IXMLStencil_func_mask __fastcall Get_Mask();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func() { }
	
private:
	void *__IXMLStencil_func;	// Fmx::Dae::Schema::IXMLStencil_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79ADDFEC-E0AB-40F9-A012-C1EC5ED67F7F}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func*(void) { return (Fmx::Dae::Schema::IXMLStencil_func*)&__IXMLStencil_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_func() { }
	
private:
	void *__IXMLStencil_func_func;	// Fmx::Dae::Schema::IXMLStencil_func_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CBC16CC5-FBB7-438F-AE48-7567A24AB250}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_func()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_func*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_func*)&__IXMLStencil_func_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_ref : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::Byte __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::Byte Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_ref(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_ref(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_ref() { }
	
private:
	void *__IXMLStencil_func_ref;	// Fmx::Dae::Schema::IXMLStencil_func_ref 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ED86FCBD-49BB-4492-932A-118AA5A36BB4}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_ref()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_ref intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_ref*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_ref*)&__IXMLStencil_func_ref; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::Byte __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::Byte Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_mask() { }
	
private:
	void *__IXMLStencil_func_mask;	// Fmx::Dae::Schema::IXMLStencil_func_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B5985806-F39C-4BB0-AA1C-3D42B70C2A63}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_mask()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_mask*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_mask*)&__IXMLStencil_func_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_separate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate_front __fastcall Get_Front();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate_back __fastcall Get_Back();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate_ref __fastcall Get_Ref();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate_mask __fastcall Get_Mask();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_separate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_separate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_separate() { }
	
private:
	void *__IXMLStencil_func_separate;	// Fmx::Dae::Schema::IXMLStencil_func_separate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EB6DDFB2-64BB-4569-B2B2-9738CE3D8D53}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_separate()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_separate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_separate*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_separate*)&__IXMLStencil_func_separate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_separate_front : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_separate_front(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_separate_front(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_separate_front() { }
	
private:
	void *__IXMLStencil_func_separate_front;	// Fmx::Dae::Schema::IXMLStencil_func_separate_front 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FF344AB8-0E08-4808-ABB0-9C2981B6C384}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_separate_front()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_separate_front intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_separate_front*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_separate_front*)&__IXMLStencil_func_separate_front; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_separate_back : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_separate_back(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_separate_back(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_separate_back() { }
	
private:
	void *__IXMLStencil_func_separate_back;	// Fmx::Dae::Schema::IXMLStencil_func_separate_back 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8ADD3F55-E415-41C5-9C94-2403738B40F9}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_separate_back()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_separate_back intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_separate_back*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_separate_back*)&__IXMLStencil_func_separate_back; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_separate_ref : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::Byte __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::Byte Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_separate_ref(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_separate_ref(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_separate_ref() { }
	
private:
	void *__IXMLStencil_func_separate_ref;	// Fmx::Dae::Schema::IXMLStencil_func_separate_ref 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E8CCFDB6-2355-4ED8-A129-98417F72625D}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_separate_ref()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_separate_ref intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_separate_ref*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_separate_ref*)&__IXMLStencil_func_separate_ref; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_func_separate_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::Byte __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::Byte Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_func_separate_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_func_separate_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_func_separate_mask() { }
	
private:
	void *__IXMLStencil_func_separate_mask;	// Fmx::Dae::Schema::IXMLStencil_func_separate_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0688B708-0463-45C0-BC12-C827504D6503}
	operator Fmx::Dae::Schema::_di_IXMLStencil_func_separate_mask()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_func_separate_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_func_separate_mask*(void) { return (Fmx::Dae::Schema::IXMLStencil_func_separate_mask*)&__IXMLStencil_func_separate_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	__int64 __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(__int64 Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_mask() { }
	
private:
	void *__IXMLStencil_mask;	// Fmx::Dae::Schema::IXMLStencil_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C1E13E5E-C6DF-420B-907C-91E61F575497}
	operator Fmx::Dae::Schema::_di_IXMLStencil_mask()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_mask*(void) { return (Fmx::Dae::Schema::IXMLStencil_mask*)&__IXMLStencil_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_mask_separate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_face __fastcall Get_Face();
	Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_mask __fastcall Get_Mask();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_mask_separate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_mask_separate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_mask_separate() { }
	
private:
	void *__IXMLStencil_mask_separate;	// Fmx::Dae::Schema::IXMLStencil_mask_separate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B134FD2F-970A-46D3-BF3C-1F36C2C7936B}
	operator Fmx::Dae::Schema::_di_IXMLStencil_mask_separate()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_mask_separate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_mask_separate*(void) { return (Fmx::Dae::Schema::IXMLStencil_mask_separate*)&__IXMLStencil_mask_separate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_mask_separate_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_mask_separate_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_mask_separate_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_mask_separate_face() { }
	
private:
	void *__IXMLStencil_mask_separate_face;	// Fmx::Dae::Schema::IXMLStencil_mask_separate_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {146F9E9D-6F81-48CE-A0F3-E2F879F43830}
	operator Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_face()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_mask_separate_face*(void) { return (Fmx::Dae::Schema::IXMLStencil_mask_separate_face*)&__IXMLStencil_mask_separate_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_mask_separate_mask : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::Byte __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::Byte Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_mask_separate_mask(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_mask_separate_mask(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_mask_separate_mask() { }
	
private:
	void *__IXMLStencil_mask_separate_mask;	// Fmx::Dae::Schema::IXMLStencil_mask_separate_mask 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B2AAAD47-8B8B-421D-B896-578E8AB9BFF4}
	operator Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_mask()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_mask_separate_mask intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_mask_separate_mask*(void) { return (Fmx::Dae::Schema::IXMLStencil_mask_separate_mask*)&__IXMLStencil_mask_separate_mask; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLStencil_op_fail __fastcall Get_Fail();
	Fmx::Dae::Schema::_di_IXMLStencil_op_zfail __fastcall Get_Zfail();
	Fmx::Dae::Schema::_di_IXMLStencil_op_zpass __fastcall Get_Zpass();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op() { }
	
private:
	void *__IXMLStencil_op;	// Fmx::Dae::Schema::IXMLStencil_op 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AF263F0F-66F3-4648-9FE7-07650C6305A4}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op*(void) { return (Fmx::Dae::Schema::IXMLStencil_op*)&__IXMLStencil_op; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_fail : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_fail(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_fail(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_fail() { }
	
private:
	void *__IXMLStencil_op_fail;	// Fmx::Dae::Schema::IXMLStencil_op_fail 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {597AA7FE-B802-4E1A-BD41-ACE92E82CA34}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_fail()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_fail intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_fail*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_fail*)&__IXMLStencil_op_fail; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_zfail : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_zfail(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_zfail(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_zfail() { }
	
private:
	void *__IXMLStencil_op_zfail;	// Fmx::Dae::Schema::IXMLStencil_op_zfail 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4BB9396F-26F9-4C8A-87B8-8C1341716D7F}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_zfail()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_zfail intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_zfail*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_zfail*)&__IXMLStencil_op_zfail; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_zpass : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_zpass(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_zpass(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_zpass() { }
	
private:
	void *__IXMLStencil_op_zpass;	// Fmx::Dae::Schema::IXMLStencil_op_zpass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D6290D32-6174-43A2-9F6B-5140AE29BCF5}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_zpass()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_zpass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_zpass*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_zpass*)&__IXMLStencil_op_zpass; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_separate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate_face __fastcall Get_Face();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate_fail __fastcall Get_Fail();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zfail __fastcall Get_Zfail();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zpass __fastcall Get_Zpass();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_separate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_separate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_separate() { }
	
private:
	void *__IXMLStencil_op_separate;	// Fmx::Dae::Schema::IXMLStencil_op_separate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {18D75A04-A719-4891-8045-B5DCBB1928FD}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_separate()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_separate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_separate*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_separate*)&__IXMLStencil_op_separate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_separate_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_separate_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_separate_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_separate_face() { }
	
private:
	void *__IXMLStencil_op_separate_face;	// Fmx::Dae::Schema::IXMLStencil_op_separate_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {02BABEEE-2E86-4106-9C7D-83DEA90DAD82}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_separate_face()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_separate_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_separate_face*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_separate_face*)&__IXMLStencil_op_separate_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_separate_fail : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_separate_fail(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_separate_fail(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_separate_fail() { }
	
private:
	void *__IXMLStencil_op_separate_fail;	// Fmx::Dae::Schema::IXMLStencil_op_separate_fail 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4EBA1286-A9F2-4E2E-ACE5-BC88901FE40D}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_separate_fail()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_separate_fail intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_separate_fail*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_separate_fail*)&__IXMLStencil_op_separate_fail; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_separate_zfail : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_separate_zfail(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_separate_zfail(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_separate_zfail() { }
	
private:
	void *__IXMLStencil_op_separate_zfail;	// Fmx::Dae::Schema::IXMLStencil_op_separate_zfail 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A45BDA96-A576-4005-BBA4-A5E482A5C553}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zfail()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zfail intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_separate_zfail*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_separate_zfail*)&__IXMLStencil_op_separate_zfail; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_op_separate_zpass : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_op_separate_zpass(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_op_separate_zpass(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_op_separate_zpass() { }
	
private:
	void *__IXMLStencil_op_separate_zpass;	// Fmx::Dae::Schema::IXMLStencil_op_separate_zpass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ACECFE79-597E-46C9-BB9F-6ACFE07917F4}
	operator Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zpass()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_op_separate_zpass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_op_separate_zpass*(void) { return (Fmx::Dae::Schema::IXMLStencil_op_separate_zpass*)&__IXMLStencil_op_separate_zpass; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLBlend_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLBlend_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLBlend_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLBlend_enable() { }
	
private:
	void *__IXMLBlend_enable;	// Fmx::Dae::Schema::IXMLBlend_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3822FB2D-ED32-4180-9B8F-68936FF66AA5}
	operator Fmx::Dae::Schema::_di_IXMLBlend_enable()
	{
		Fmx::Dae::Schema::_di_IXMLBlend_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLBlend_enable*(void) { return (Fmx::Dae::Schema::IXMLBlend_enable*)&__IXMLBlend_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCull_face_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCull_face_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCull_face_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCull_face_enable() { }
	
private:
	void *__IXMLCull_face_enable;	// Fmx::Dae::Schema::IXMLCull_face_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A492A91D-F805-41D4-BCAA-615421C0AC37}
	operator Fmx::Dae::Schema::_di_IXMLCull_face_enable()
	{
		Fmx::Dae::Schema::_di_IXMLCull_face_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCull_face_enable*(void) { return (Fmx::Dae::Schema::IXMLCull_face_enable*)&__IXMLCull_face_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_test_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_test_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_test_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_test_enable() { }
	
private:
	void *__IXMLDepth_test_enable;	// Fmx::Dae::Schema::IXMLDepth_test_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BEF236CB-5C43-4155-9F6D-3DA3BA97E244}
	operator Fmx::Dae::Schema::_di_IXMLDepth_test_enable()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_test_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_test_enable*(void) { return (Fmx::Dae::Schema::IXMLDepth_test_enable*)&__IXMLDepth_test_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDither_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDither_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDither_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDither_enable() { }
	
private:
	void *__IXMLDither_enable;	// Fmx::Dae::Schema::IXMLDither_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ACCA94AF-54AB-41E3-BE56-80188F40EA6D}
	operator Fmx::Dae::Schema::_di_IXMLDither_enable()
	{
		Fmx::Dae::Schema::_di_IXMLDither_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDither_enable*(void) { return (Fmx::Dae::Schema::IXMLDither_enable*)&__IXMLDither_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_offset_fill_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_offset_fill_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_offset_fill_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_offset_fill_enable() { }
	
private:
	void *__IXMLPolygon_offset_fill_enable;	// Fmx::Dae::Schema::IXMLPolygon_offset_fill_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1F026664-1564-45B4-8224-BF1B61409E89}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_offset_fill_enable*(void) { return (Fmx::Dae::Schema::IXMLPolygon_offset_fill_enable*)&__IXMLPolygon_offset_fill_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_size_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_size_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_size_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_size_enable() { }
	
private:
	void *__IXMLPoint_size_enable;	// Fmx::Dae::Schema::IXMLPoint_size_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A5BDC689-6D49-4EF5-9C22-B2BCDAC95D86}
	operator Fmx::Dae::Schema::_di_IXMLPoint_size_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_size_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_size_enable*(void) { return (Fmx::Dae::Schema::IXMLPoint_size_enable*)&__IXMLPoint_size_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_alpha_to_coverage_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_alpha_to_coverage_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_alpha_to_coverage_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_alpha_to_coverage_enable() { }
	
private:
	void *__IXMLSample_alpha_to_coverage_enable;	// Fmx::Dae::Schema::IXMLSample_alpha_to_coverage_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {24678D0C-1987-4A66-8463-3F386C36F96F}
	operator Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable()
	{
		Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_alpha_to_coverage_enable*(void) { return (Fmx::Dae::Schema::IXMLSample_alpha_to_coverage_enable*)&__IXMLSample_alpha_to_coverage_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_coverage_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_coverage_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_coverage_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_coverage_enable() { }
	
private:
	void *__IXMLSample_coverage_enable;	// Fmx::Dae::Schema::IXMLSample_coverage_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DF624553-E239-49B3-AB18-29C12483B479}
	operator Fmx::Dae::Schema::_di_IXMLSample_coverage_enable()
	{
		Fmx::Dae::Schema::_di_IXMLSample_coverage_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_coverage_enable*(void) { return (Fmx::Dae::Schema::IXMLSample_coverage_enable*)&__IXMLSample_coverage_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLScissor_test_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLScissor_test_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLScissor_test_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLScissor_test_enable() { }
	
private:
	void *__IXMLScissor_test_enable;	// Fmx::Dae::Schema::IXMLScissor_test_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A2DF04FF-15E7-45B8-8959-043253337021}
	operator Fmx::Dae::Schema::_di_IXMLScissor_test_enable()
	{
		Fmx::Dae::Schema::_di_IXMLScissor_test_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLScissor_test_enable*(void) { return (Fmx::Dae::Schema::IXMLScissor_test_enable*)&__IXMLScissor_test_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLStencil_test_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLStencil_test_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLStencil_test_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLStencil_test_enable() { }
	
private:
	void *__IXMLStencil_test_enable;	// Fmx::Dae::Schema::IXMLStencil_test_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ACB936E1-E401-4D12-9949-45E9F90A2592}
	operator Fmx::Dae::Schema::_di_IXMLStencil_test_enable()
	{
		Fmx::Dae::Schema::_di_IXMLStencil_test_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLStencil_test_enable*(void) { return (Fmx::Dae::Schema::IXMLStencil_test_enable*)&__IXMLStencil_test_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLGles2_shader_typeList FShader;
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList FLinker;
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attributeList FBind_attribute;
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniformList FBind_uniform;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles2_shader_typeList __fastcall Get_Shader();
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList __fastcall Get_Linker();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attributeList __fastcall Get_Bind_attribute();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniformList __fastcall Get_Bind_uniform();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type() { }
	
private:
	void *__IXMLGles2_program_type;	// Fmx::Dae::Schema::IXMLGles2_program_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2682C4AA-97DA-4579-94EF-8EABFAAC4906}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type*)&__IXMLGles2_program_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_shader_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList FCompiler;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Stage();
	Fmx::Dae::Schema::_di_IXMLGles2_shader_type_sources __fastcall Get_Sources();
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList __fastcall Get_Compiler();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Stage(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_shader_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_shader_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_shader_type() { }
	
private:
	void *__IXMLGles2_shader_type;	// Fmx::Dae::Schema::IXMLGles2_shader_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {37424980-2744-4AC0-9979-78EA2D6024BB}
	operator Fmx::Dae::Schema::_di_IXMLGles2_shader_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_shader_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_shader_type*(void) { return (Fmx::Dae::Schema::IXMLGles2_shader_type*)&__IXMLGles2_shader_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_shader_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles2_shader_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles2_shader_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles2_shader_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_shader_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_shader_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_shader_typeList() { }
	
private:
	void *__IXMLGles2_shader_typeList;	// Fmx::Dae::Schema::IXMLGles2_shader_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5698DA63-5909-4C0E-95D9-E060443198E7}
	operator Fmx::Dae::Schema::_di_IXMLGles2_shader_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_shader_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_shader_typeList*(void) { return (Fmx::Dae::Schema::IXMLGles2_shader_typeList*)&__IXMLGles2_shader_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sources_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLString_List FInline_;
	Fmx::Dae::Schema::_di_IXMLFx_sources_type_importList FImport;
	
protected:
	Fmx::Dae::Schema::_di_IXMLString_List __fastcall Get_Inline_();
	Fmx::Dae::Schema::_di_IXMLFx_sources_type_importList __fastcall Get_Import();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sources_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sources_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sources_type() { }
	
private:
	void *__IXMLFx_sources_type;	// Fmx::Dae::Schema::IXMLFx_sources_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {643C47E3-734D-44F9-B209-4E25D6A8DDE9}
	operator Fmx::Dae::Schema::_di_IXMLFx_sources_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sources_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sources_type*(void) { return (Fmx::Dae::Schema::IXMLFx_sources_type*)&__IXMLFx_sources_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sources_type_import : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sources_type_import(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sources_type_import(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sources_type_import() { }
	
private:
	void *__IXMLFx_sources_type_import;	// Fmx::Dae::Schema::IXMLFx_sources_type_import 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C7713A1B-ADEE-4263-849E-78EF245E1037}
	operator Fmx::Dae::Schema::_di_IXMLFx_sources_type_import()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sources_type_import intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sources_type_import*(void) { return (Fmx::Dae::Schema::IXMLFx_sources_type_import*)&__IXMLFx_sources_type_import; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_sources_type_importList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_sources_type_import __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_sources_type_import __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_sources_type_import __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_sources_type_importList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_sources_type_importList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_sources_type_importList() { }
	
private:
	void *__IXMLFx_sources_type_importList;	// Fmx::Dae::Schema::IXMLFx_sources_type_importList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C4C78965-04AF-4885-A77F-A46E462A1451}
	operator Fmx::Dae::Schema::_di_IXMLFx_sources_type_importList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_sources_type_importList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_sources_type_importList*(void) { return (Fmx::Dae::Schema::IXMLFx_sources_type_importList*)&__IXMLFx_sources_type_importList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_shader_type_sources : public TXMLFx_sources_type
{
	typedef TXMLFx_sources_type inherited;
	
protected:
	System::UnicodeString __fastcall Get_Entry();
	void __fastcall Set_Entry(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_shader_type_sources(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sources_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_shader_type_sources(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sources_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_shader_type_sources() { }
	
private:
	void *__IXMLGles2_shader_type_sources;	// Fmx::Dae::Schema::IXMLGles2_shader_type_sources 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F1BF3168-E706-4CF7-899B-8FDBAFFF5DCD}
	operator Fmx::Dae::Schema::_di_IXMLGles2_shader_type_sources()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_shader_type_sources intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_shader_type_sources*(void) { return (Fmx::Dae::Schema::IXMLGles2_shader_type_sources*)&__IXMLGles2_shader_type_sources; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_target_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Platform();
	System::UnicodeString __fastcall Get_Target();
	System::UnicodeString __fastcall Get_Options();
	Fmx::Dae::Schema::_di_IXMLFx_target_type_binary __fastcall Get_Binary();
	void __fastcall Set_Platform(System::UnicodeString Value);
	void __fastcall Set_Target(System::UnicodeString Value);
	void __fastcall Set_Options(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_target_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_target_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_target_type() { }
	
private:
	void *__IXMLFx_target_type;	// Fmx::Dae::Schema::IXMLFx_target_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {39B95CD5-F210-4142-99C0-4E252B1D29BA}
	operator Fmx::Dae::Schema::_di_IXMLFx_target_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_target_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_target_type*(void) { return (Fmx::Dae::Schema::IXMLFx_target_type*)&__IXMLFx_target_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_target_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_target_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_target_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_target_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_target_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_target_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_target_typeList() { }
	
private:
	void *__IXMLFx_target_typeList;	// Fmx::Dae::Schema::IXMLFx_target_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EFA3EBA8-3E18-4F89-A301-1ED936C785A0}
	operator Fmx::Dae::Schema::_di_IXMLFx_target_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_target_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_target_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_target_typeList*)&__IXMLFx_target_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_target_type_binary : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	Fmx::Dae::Schema::_di_IXMLFx_target_type_binary_hex __fastcall Get_Hex();
	void __fastcall Set_Ref(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_target_type_binary(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_target_type_binary(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_target_type_binary() { }
	
private:
	void *__IXMLFx_target_type_binary;	// Fmx::Dae::Schema::IXMLFx_target_type_binary 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {87A86695-B3D5-4C84-B288-ABC831776809}
	operator Fmx::Dae::Schema::_di_IXMLFx_target_type_binary()
	{
		Fmx::Dae::Schema::_di_IXMLFx_target_type_binary intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_target_type_binary*(void) { return (Fmx::Dae::Schema::IXMLFx_target_type_binary*)&__IXMLFx_target_type_binary; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_target_type_binary_hex : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Format();
	void __fastcall Set_Format(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_target_type_binary_hex(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_target_type_binary_hex(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_target_type_binary_hex() { }
	
private:
	void *__IXMLFx_target_type_binary_hex;	// Fmx::Dae::Schema::IXMLFx_target_type_binary_hex 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7B2221C6-8CE6-46EC-B634-051180BA345C}
	operator Fmx::Dae::Schema::_di_IXMLFx_target_type_binary_hex()
	{
		Fmx::Dae::Schema::_di_IXMLFx_target_type_binary_hex intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_target_type_binary_hex*(void) { return (Fmx::Dae::Schema::IXMLFx_target_type_binary_hex*)&__IXMLFx_target_type_binary_hex; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type_bind_attribute : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Symbol();
	System::UnicodeString __fastcall Get_Semantic();
	void __fastcall Set_Symbol(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type_bind_attribute(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type_bind_attribute(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type_bind_attribute() { }
	
private:
	void *__IXMLGles2_program_type_bind_attribute;	// Fmx::Dae::Schema::IXMLGles2_program_type_bind_attribute 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {596F0298-5C68-45D6-A582-994B6E24F083}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attribute()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attribute intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type_bind_attribute*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type_bind_attribute*)&__IXMLGles2_program_type_bind_attribute; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type_bind_attributeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attribute __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attribute __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attribute __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type_bind_attributeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type_bind_attributeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type_bind_attributeList() { }
	
private:
	void *__IXMLGles2_program_type_bind_attributeList;	// Fmx::Dae::Schema::IXMLGles2_program_type_bind_attributeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {284365A5-F8EB-41CF-8715-25FBF74974C6}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attributeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_attributeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type_bind_attributeList*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type_bind_attributeList*)&__IXMLGles2_program_type_bind_attributeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type_bind_uniform : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Symbol();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform_param __fastcall Get_Param();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bvec2();
	System::UnicodeString __fastcall Get_Bvec3();
	System::UnicodeString __fastcall Get_Bvec4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Vec2();
	System::UnicodeString __fastcall Get_Vec3();
	System::UnicodeString __fastcall Get_Vec4();
	System::UnicodeString __fastcall Get_Mat2();
	System::UnicodeString __fastcall Get_Mat3();
	System::UnicodeString __fastcall Get_Mat4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Ivec2();
	System::UnicodeString __fastcall Get_Ivec3();
	System::UnicodeString __fastcall Get_Ivec4();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	Fmx::Dae::Schema::_di_IXMLUsertype __fastcall Get_Usertype();
	Fmx::Dae::Schema::_di_IXMLArray_ __fastcall Get_Array_();
	void __fastcall Set_Symbol(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bvec2(System::UnicodeString Value);
	void __fastcall Set_Bvec3(System::UnicodeString Value);
	void __fastcall Set_Bvec4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Vec2(System::UnicodeString Value);
	void __fastcall Set_Vec3(System::UnicodeString Value);
	void __fastcall Set_Vec4(System::UnicodeString Value);
	void __fastcall Set_Mat2(System::UnicodeString Value);
	void __fastcall Set_Mat3(System::UnicodeString Value);
	void __fastcall Set_Mat4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Ivec2(System::UnicodeString Value);
	void __fastcall Set_Ivec3(System::UnicodeString Value);
	void __fastcall Set_Ivec4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type_bind_uniform(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type_bind_uniform(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type_bind_uniform() { }
	
private:
	void *__IXMLGles2_program_type_bind_uniform;	// Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {47E30718-9CB7-464C-B412-50DC1F7CA759}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform*)&__IXMLGles2_program_type_bind_uniform; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type_bind_uniformList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type_bind_uniformList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type_bind_uniformList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type_bind_uniformList() { }
	
private:
	void *__IXMLGles2_program_type_bind_uniformList;	// Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniformList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2AE2D982-6084-4CF8-9BA6-08B54CF70FD6}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniformList()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniformList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniformList*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniformList*)&__IXMLGles2_program_type_bind_uniformList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_program_type_bind_uniform_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_program_type_bind_uniform_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_program_type_bind_uniform_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_program_type_bind_uniform_param() { }
	
private:
	void *__IXMLGles2_program_type_bind_uniform_param;	// Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D1A44A50-661B-4009-892E-4B2F32FF011D}
	operator Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform_param()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_program_type_bind_uniform_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform_param*(void) { return (Fmx::Dae::Schema::IXMLGles2_program_type_bind_uniform_param*)&__IXMLGles2_program_type_bind_uniform_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles2_pass_type_evaluate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList FColor_target;
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList FDepth_target;
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList FStencil_target;
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList FColor_clear;
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList FStencil_clear;
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList FDepth_clear;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList __fastcall Get_Color_target();
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList __fastcall Get_Depth_target();
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList __fastcall Get_Stencil_target();
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList __fastcall Get_Color_clear();
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList __fastcall Get_Stencil_clear();
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList __fastcall Get_Depth_clear();
	System::UnicodeString __fastcall Get_Draw();
	void __fastcall Set_Draw(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles2_pass_type_evaluate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles2_pass_type_evaluate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles2_pass_type_evaluate() { }
	
private:
	void *__IXMLGles2_pass_type_evaluate;	// Fmx::Dae::Schema::IXMLGles2_pass_type_evaluate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {78044BDB-3BF1-4358-8F59-C7F1B9BF1D20}
	operator Fmx::Dae::Schema::_di_IXMLGles2_pass_type_evaluate()
	{
		Fmx::Dae::Schema::_di_IXMLGles2_pass_type_evaluate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles2_pass_type_evaluate*(void) { return (Fmx::Dae::Schema::IXMLGles2_pass_type_evaluate*)&__IXMLGles2_pass_type_evaluate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_rendertarget_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	unsigned __fastcall Get_Mip();
	System::UnicodeString __fastcall Get_Face();
	unsigned __fastcall Get_Slice();
	Fmx::Dae::Schema::_di_IXMLFx_rendertarget_type_param __fastcall Get_Param();
	Fmx::Dae::Schema::_di_IXMLInstance_image_type __fastcall Get_Instance_image();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Mip(unsigned Value);
	void __fastcall Set_Face(System::UnicodeString Value);
	void __fastcall Set_Slice(unsigned Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_rendertarget_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_rendertarget_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_rendertarget_type() { }
	
private:
	void *__IXMLFx_rendertarget_type;	// Fmx::Dae::Schema::IXMLFx_rendertarget_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {80CF4B9E-890F-4F5B-94B8-65F64560ECCE}
	operator Fmx::Dae::Schema::_di_IXMLFx_rendertarget_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_rendertarget_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_rendertarget_type*(void) { return (Fmx::Dae::Schema::IXMLFx_rendertarget_type*)&__IXMLFx_rendertarget_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_rendertarget_type_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_rendertarget_type_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_rendertarget_type_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_rendertarget_type_param() { }
	
private:
	void *__IXMLFx_rendertarget_type_param;	// Fmx::Dae::Schema::IXMLFx_rendertarget_type_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1DE12E72-0868-477F-A47B-DA8212966A37}
	operator Fmx::Dae::Schema::_di_IXMLFx_rendertarget_type_param()
	{
		Fmx::Dae::Schema::_di_IXMLFx_rendertarget_type_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_rendertarget_type_param*(void) { return (Fmx::Dae::Schema::IXMLFx_rendertarget_type_param*)&__IXMLFx_rendertarget_type_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_colortarget_type : public TXMLFx_rendertarget_type
{
	typedef TXMLFx_rendertarget_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_colortarget_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_rendertarget_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_colortarget_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_rendertarget_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_colortarget_type() { }
	
private:
	void *__IXMLFx_colortarget_type;	// Fmx::Dae::Schema::IXMLFx_colortarget_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5FE06DB2-E584-4BF9-8FFF-0D2284771375}
	operator Fmx::Dae::Schema::_di_IXMLFx_colortarget_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_colortarget_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_colortarget_type*(void) { return (Fmx::Dae::Schema::IXMLFx_colortarget_type*)&__IXMLFx_colortarget_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_colortarget_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_colortarget_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_colortarget_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_colortarget_typeList() { }
	
private:
	void *__IXMLFx_colortarget_typeList;	// Fmx::Dae::Schema::IXMLFx_colortarget_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C35D0FC9-25D9-4E8B-99AA-A42ED8478DA0}
	operator Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_colortarget_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_colortarget_typeList*)&__IXMLFx_colortarget_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_depthtarget_type : public TXMLFx_rendertarget_type
{
	typedef TXMLFx_rendertarget_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_depthtarget_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_rendertarget_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_depthtarget_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_rendertarget_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_depthtarget_type() { }
	
private:
	void *__IXMLFx_depthtarget_type;	// Fmx::Dae::Schema::IXMLFx_depthtarget_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BA5FA307-15AC-407C-A14C-30BCF72EA826}
	operator Fmx::Dae::Schema::_di_IXMLFx_depthtarget_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_depthtarget_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_depthtarget_type*(void) { return (Fmx::Dae::Schema::IXMLFx_depthtarget_type*)&__IXMLFx_depthtarget_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_depthtarget_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_depthtarget_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_depthtarget_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_depthtarget_typeList() { }
	
private:
	void *__IXMLFx_depthtarget_typeList;	// Fmx::Dae::Schema::IXMLFx_depthtarget_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {32DEDD42-8B5D-45C2-89DC-530529A6B323}
	operator Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_depthtarget_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_depthtarget_typeList*)&__IXMLFx_depthtarget_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_stenciltarget_type : public TXMLFx_rendertarget_type
{
	typedef TXMLFx_rendertarget_type inherited;
	
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_stenciltarget_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_rendertarget_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_stenciltarget_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_rendertarget_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_stenciltarget_type() { }
	
private:
	void *__IXMLFx_stenciltarget_type;	// Fmx::Dae::Schema::IXMLFx_stenciltarget_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {93C1803E-38FA-47D6-B33A-48BD7BB9F9E7}
	operator Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_stenciltarget_type*(void) { return (Fmx::Dae::Schema::IXMLFx_stenciltarget_type*)&__IXMLFx_stenciltarget_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_stenciltarget_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_stenciltarget_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_stenciltarget_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_stenciltarget_typeList() { }
	
private:
	void *__IXMLFx_stenciltarget_typeList;	// Fmx::Dae::Schema::IXMLFx_stenciltarget_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D09D1DA0-6639-49D9-B04F-D9060B38DFE8}
	operator Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_stenciltarget_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_stenciltarget_typeList*)&__IXMLFx_stenciltarget_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_clearcolor_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_clearcolor_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_clearcolor_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_clearcolor_type() { }
	
private:
	void *__IXMLFx_clearcolor_type;	// Fmx::Dae::Schema::IXMLFx_clearcolor_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8167DF22-D71D-40FA-AD62-3870E29CA088}
	operator Fmx::Dae::Schema::_di_IXMLFx_clearcolor_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_clearcolor_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_clearcolor_type*(void) { return (Fmx::Dae::Schema::IXMLFx_clearcolor_type*)&__IXMLFx_clearcolor_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_clearcolor_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_clearcolor_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_clearcolor_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_clearcolor_typeList() { }
	
private:
	void *__IXMLFx_clearcolor_typeList;	// Fmx::Dae::Schema::IXMLFx_clearcolor_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {30155194-3B14-4D46-B938-C4754675CCD8}
	operator Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_clearcolor_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_clearcolor_typeList*)&__IXMLFx_clearcolor_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_clearstencil_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_clearstencil_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_clearstencil_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_clearstencil_type() { }
	
private:
	void *__IXMLFx_clearstencil_type;	// Fmx::Dae::Schema::IXMLFx_clearstencil_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F35721F7-5B4C-4035-BB1E-D32A6C063EC6}
	operator Fmx::Dae::Schema::_di_IXMLFx_clearstencil_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_clearstencil_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_clearstencil_type*(void) { return (Fmx::Dae::Schema::IXMLFx_clearstencil_type*)&__IXMLFx_clearstencil_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_clearstencil_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_clearstencil_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_clearstencil_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_clearstencil_typeList() { }
	
private:
	void *__IXMLFx_clearstencil_typeList;	// Fmx::Dae::Schema::IXMLFx_clearstencil_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0C9379AC-17F3-4545-A066-956117243B3A}
	operator Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_clearstencil_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_clearstencil_typeList*)&__IXMLFx_clearstencil_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_cleardepth_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_cleardepth_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_cleardepth_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_cleardepth_type() { }
	
private:
	void *__IXMLFx_cleardepth_type;	// Fmx::Dae::Schema::IXMLFx_cleardepth_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {93B790F8-EFD3-4CD5-A17F-BCE11B5AB6CC}
	operator Fmx::Dae::Schema::_di_IXMLFx_cleardepth_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_cleardepth_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_cleardepth_type*(void) { return (Fmx::Dae::Schema::IXMLFx_cleardepth_type*)&__IXMLFx_cleardepth_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_cleardepth_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_cleardepth_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_cleardepth_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_cleardepth_typeList() { }
	
private:
	void *__IXMLFx_cleardepth_typeList;	// Fmx::Dae::Schema::IXMLFx_cleardepth_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {63114096-FD8B-4AF5-AC7B-A9935B91DFF9}
	operator Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_cleardepth_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_cleardepth_typeList*)&__IXMLFx_cleardepth_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList FCode;
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList FInclude;
	Fmx::Dae::Schema::_di_IXMLGlsl_newparam_typeList FNewparam;
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_techniqueList FTechnique;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Platform();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList __fastcall Get_Code();
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList __fastcall Get_Include();
	Fmx::Dae::Schema::_di_IXMLGlsl_newparam_typeList __fastcall Get_Newparam();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_techniqueList __fastcall Get_Technique();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Platform(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type() { }
	
private:
	void *__IXMLProfile_glsl_type;	// Fmx::Dae::Schema::IXMLProfile_glsl_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E82913B9-2C3A-4FF0-B63B-F2EDBF733A9A}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type*)&__IXMLProfile_glsl_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	System::UnicodeString __fastcall Get_Semantic();
	System::UnicodeString __fastcall Get_Modifier();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLGlsl_array_type __fastcall Get_Array_();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Modifier(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_newparam_type() { }
	
private:
	void *__IXMLGlsl_newparam_type;	// Fmx::Dae::Schema::IXMLGlsl_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A6D71C07-335B-4142-9E31-E75A24FA3B66}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLGlsl_newparam_type*)&__IXMLGlsl_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_newparam_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGlsl_newparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGlsl_newparam_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGlsl_newparam_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_newparam_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_newparam_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_newparam_typeList() { }
	
private:
	void *__IXMLGlsl_newparam_typeList;	// Fmx::Dae::Schema::IXMLGlsl_newparam_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FA39269A-59A3-4D82-A262-22F174382B5C}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_newparam_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_newparam_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_newparam_typeList*(void) { return (Fmx::Dae::Schema::IXMLGlsl_newparam_typeList*)&__IXMLGlsl_newparam_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_array_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Length();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLGlsl_array_type __fastcall Get_Array_();
	void __fastcall Set_Length(unsigned Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_array_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_array_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_array_type() { }
	
private:
	void *__IXMLGlsl_array_type;	// Fmx::Dae::Schema::IXMLGlsl_array_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {017ECB21-1E6E-46C3-9556-B33BD9D5D85B}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_array_type()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_array_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_array_type*(void) { return (Fmx::Dae::Schema::IXMLGlsl_array_type*)&__IXMLGlsl_array_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_technique : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_passList FPass;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_passList __fastcall Get_Pass();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_technique(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_technique(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_technique() { }
	
private:
	void *__IXMLProfile_glsl_type_technique;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_technique 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7C7A049B-E0D6-48F6-89FA-56EA5AB50732}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_technique*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_technique*)&__IXMLProfile_glsl_type_technique; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_techniqueList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_techniqueList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_techniqueList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_techniqueList() { }
	
private:
	void *__IXMLProfile_glsl_type_techniqueList;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_techniqueList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EEBA4612-061E-483C-86D3-6376D84BF311}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_techniqueList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_techniqueList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_techniqueList*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_techniqueList*)&__IXMLProfile_glsl_type_techniqueList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_technique_pass : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_states __fastcall Get_States();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type __fastcall Get_Program_();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_evaluate __fastcall Get_Evaluate();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_technique_pass(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_technique_pass(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_technique_pass() { }
	
private:
	void *__IXMLProfile_glsl_type_technique_pass;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {858F9322-2370-4333-BAFC-0AE434EEAAD6}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass*)&__IXMLProfile_glsl_type_technique_pass; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_technique_passList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_technique_passList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_technique_passList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_technique_passList() { }
	
private:
	void *__IXMLProfile_glsl_type_technique_passList;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_passList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C2FDFD20-8C7A-4776-BA98-A5DB352A5BDC}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_passList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_passList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_passList*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_passList*)&__IXMLProfile_glsl_type_technique_passList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_technique_pass_states : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLAlpha_func __fastcall Get_Alpha_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func __fastcall Get_Blend_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate __fastcall Get_Blend_func_separate();
	Fmx::Dae::Schema::_di_IXMLBlend_equation __fastcall Get_Blend_equation();
	Fmx::Dae::Schema::_di_IXMLBlend_equation_separate __fastcall Get_Blend_equation_separate();
	Fmx::Dae::Schema::_di_IXMLColor_material __fastcall Get_Color_material();
	Fmx::Dae::Schema::_di_IXMLCull_face __fastcall Get_Cull_face();
	Fmx::Dae::Schema::_di_IXMLDepth_func __fastcall Get_Depth_func();
	Fmx::Dae::Schema::_di_IXMLFog_mode __fastcall Get_Fog_mode();
	Fmx::Dae::Schema::_di_IXMLFog_coord_src __fastcall Get_Fog_coord_src();
	Fmx::Dae::Schema::_di_IXMLFront_face __fastcall Get_Front_face();
	Fmx::Dae::Schema::_di_IXMLLight_model_color_control __fastcall Get_Light_model_color_control();
	Fmx::Dae::Schema::_di_IXMLLogic_op __fastcall Get_Logic_op();
	Fmx::Dae::Schema::_di_IXMLPolygon_mode __fastcall Get_Polygon_mode();
	Fmx::Dae::Schema::_di_IXMLShade_model __fastcall Get_Shade_model();
	Fmx::Dae::Schema::_di_IXMLStencil_func __fastcall Get_Stencil_func();
	Fmx::Dae::Schema::_di_IXMLStencil_op __fastcall Get_Stencil_op();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate __fastcall Get_Stencil_func_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate __fastcall Get_Stencil_op_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_mask_separate __fastcall Get_Stencil_mask_separate();
	Fmx::Dae::Schema::_di_IXMLLight_enable __fastcall Get_Light_enable();
	Fmx::Dae::Schema::_di_IXMLLight_ambient __fastcall Get_Light_ambient();
	Fmx::Dae::Schema::_di_IXMLLight_diffuse __fastcall Get_Light_diffuse();
	Fmx::Dae::Schema::_di_IXMLLight_specular __fastcall Get_Light_specular();
	Fmx::Dae::Schema::_di_IXMLLight_position __fastcall Get_Light_position();
	Fmx::Dae::Schema::_di_IXMLLight_constant_attenuation __fastcall Get_Light_constant_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_linear_attenuation __fastcall Get_Light_linear_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_quadratic_attenuation __fastcall Get_Light_quadratic_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_spot_cutoff __fastcall Get_Light_spot_cutoff();
	Fmx::Dae::Schema::_di_IXMLLight_spot_direction __fastcall Get_Light_spot_direction();
	Fmx::Dae::Schema::_di_IXMLLight_spot_exponent __fastcall Get_Light_spot_exponent();
	Fmx::Dae::Schema::_di_IXMLTexture1D __fastcall Get_Texture1D();
	Fmx::Dae::Schema::_di_IXMLTexture2D __fastcall Get_Texture2D();
	Fmx::Dae::Schema::_di_IXMLTexture3D __fastcall Get_Texture3D();
	Fmx::Dae::Schema::_di_IXMLTextureCUBE __fastcall Get_TextureCUBE();
	Fmx::Dae::Schema::_di_IXMLTextureRECT __fastcall Get_TextureRECT();
	Fmx::Dae::Schema::_di_IXMLTextureDEPTH __fastcall Get_TextureDEPTH();
	Fmx::Dae::Schema::_di_IXMLTexture1D_enable __fastcall Get_Texture1D_enable();
	Fmx::Dae::Schema::_di_IXMLTexture2D_enable __fastcall Get_Texture2D_enable();
	Fmx::Dae::Schema::_di_IXMLTexture3D_enable __fastcall Get_Texture3D_enable();
	Fmx::Dae::Schema::_di_IXMLTextureCUBE_enable __fastcall Get_TextureCUBE_enable();
	Fmx::Dae::Schema::_di_IXMLTextureRECT_enable __fastcall Get_TextureRECT_enable();
	Fmx::Dae::Schema::_di_IXMLTextureDEPTH_enable __fastcall Get_TextureDEPTH_enable();
	Fmx::Dae::Schema::_di_IXMLTexture_env_color __fastcall Get_Texture_env_color();
	Fmx::Dae::Schema::_di_IXMLTexture_env_mode __fastcall Get_Texture_env_mode();
	Fmx::Dae::Schema::_di_IXMLClip_plane __fastcall Get_Clip_plane();
	Fmx::Dae::Schema::_di_IXMLClip_plane_enable __fastcall Get_Clip_plane_enable();
	Fmx::Dae::Schema::_di_IXMLBlend_color __fastcall Get_Blend_color();
	Fmx::Dae::Schema::_di_IXMLColor_mask __fastcall Get_Color_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_bounds __fastcall Get_Depth_bounds();
	Fmx::Dae::Schema::_di_IXMLDepth_mask __fastcall Get_Depth_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_range __fastcall Get_Depth_range();
	Fmx::Dae::Schema::_di_IXMLFog_density __fastcall Get_Fog_density();
	Fmx::Dae::Schema::_di_IXMLFog_start __fastcall Get_Fog_start();
	Fmx::Dae::Schema::_di_IXMLFog_end __fastcall Get_Fog_end();
	Fmx::Dae::Schema::_di_IXMLFog_color __fastcall Get_Fog_color();
	Fmx::Dae::Schema::_di_IXMLLight_model_ambient __fastcall Get_Light_model_ambient();
	Fmx::Dae::Schema::_di_IXMLLighting_enable __fastcall Get_Lighting_enable();
	Fmx::Dae::Schema::_di_IXMLLine_stipple __fastcall Get_Line_stipple();
	Fmx::Dae::Schema::_di_IXMLLine_width __fastcall Get_Line_width();
	Fmx::Dae::Schema::_di_IXMLMaterial_ambient __fastcall Get_Material_ambient();
	Fmx::Dae::Schema::_di_IXMLMaterial_diffuse __fastcall Get_Material_diffuse();
	Fmx::Dae::Schema::_di_IXMLMaterial_emission __fastcall Get_Material_emission();
	Fmx::Dae::Schema::_di_IXMLMaterial_shininess __fastcall Get_Material_shininess();
	Fmx::Dae::Schema::_di_IXMLMaterial_specular __fastcall Get_Material_specular();
	Fmx::Dae::Schema::_di_IXMLModel_view_matrix __fastcall Get_Model_view_matrix();
	Fmx::Dae::Schema::_di_IXMLPoint_distance_attenuation __fastcall Get_Point_distance_attenuation();
	Fmx::Dae::Schema::_di_IXMLPoint_fade_threshold_size __fastcall Get_Point_fade_threshold_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size __fastcall Get_Point_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size_min __fastcall Get_Point_size_min();
	Fmx::Dae::Schema::_di_IXMLPoint_size_max __fastcall Get_Point_size_max();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset __fastcall Get_Polygon_offset();
	Fmx::Dae::Schema::_di_IXMLProjection_matrix __fastcall Get_Projection_matrix();
	Fmx::Dae::Schema::_di_IXMLScissor __fastcall Get_Scissor();
	Fmx::Dae::Schema::_di_IXMLStencil_mask __fastcall Get_Stencil_mask();
	Fmx::Dae::Schema::_di_IXMLAlpha_test_enable __fastcall Get_Alpha_test_enable();
	Fmx::Dae::Schema::_di_IXMLBlend_enable __fastcall Get_Blend_enable();
	Fmx::Dae::Schema::_di_IXMLColor_logic_op_enable __fastcall Get_Color_logic_op_enable();
	Fmx::Dae::Schema::_di_IXMLColor_material_enable __fastcall Get_Color_material_enable();
	Fmx::Dae::Schema::_di_IXMLCull_face_enable __fastcall Get_Cull_face_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_bounds_enable __fastcall Get_Depth_bounds_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_clamp_enable __fastcall Get_Depth_clamp_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_test_enable __fastcall Get_Depth_test_enable();
	Fmx::Dae::Schema::_di_IXMLDither_enable __fastcall Get_Dither_enable();
	Fmx::Dae::Schema::_di_IXMLFog_enable __fastcall Get_Fog_enable();
	Fmx::Dae::Schema::_di_IXMLLight_model_local_viewer_enable __fastcall Get_Light_model_local_viewer_enable();
	Fmx::Dae::Schema::_di_IXMLLight_model_two_side_enable __fastcall Get_Light_model_two_side_enable();
	Fmx::Dae::Schema::_di_IXMLLine_smooth_enable __fastcall Get_Line_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLLine_stipple_enable __fastcall Get_Line_stipple_enable();
	Fmx::Dae::Schema::_di_IXMLLogic_op_enable __fastcall Get_Logic_op_enable();
	Fmx::Dae::Schema::_di_IXMLMultisample_enable __fastcall Get_Multisample_enable();
	Fmx::Dae::Schema::_di_IXMLNormalize_enable __fastcall Get_Normalize_enable();
	Fmx::Dae::Schema::_di_IXMLPoint_smooth_enable __fastcall Get_Point_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable __fastcall Get_Polygon_offset_fill_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_line_enable __fastcall Get_Polygon_offset_line_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_point_enable __fastcall Get_Polygon_offset_point_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_smooth_enable __fastcall Get_Polygon_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_stipple_enable __fastcall Get_Polygon_stipple_enable();
	Fmx::Dae::Schema::_di_IXMLRescale_normal_enable __fastcall Get_Rescale_normal_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable __fastcall Get_Sample_alpha_to_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_one_enable __fastcall Get_Sample_alpha_to_one_enable();
	Fmx::Dae::Schema::_di_IXMLSample_coverage_enable __fastcall Get_Sample_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLScissor_test_enable __fastcall Get_Scissor_test_enable();
	Fmx::Dae::Schema::_di_IXMLStencil_test_enable __fastcall Get_Stencil_test_enable();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_technique_pass_states(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_technique_pass_states(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_technique_pass_states() { }
	
private:
	void *__IXMLProfile_glsl_type_technique_pass_states;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_states 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {425898BE-E198-4983-AEF2-E3FCEEBF2945}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_states()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_states intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_states*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_states*)&__IXMLProfile_glsl_type_technique_pass_states; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLString_List : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Xml::Xmlintf::_di_IXMLNode __fastcall Add(const System::UnicodeString Value);
	Xml::Xmlintf::_di_IXMLNode __fastcall Insert(const int Index, const System::UnicodeString Value);
	System::UnicodeString __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLString_List(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLString_List(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLString_List() { }
	
private:
	void *__IXMLString_List;	// Fmx::Dae::Schema::IXMLString_List 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D4C163D2-215B-4CDD-BB6C-3FC09451359C}
	operator Fmx::Dae::Schema::_di_IXMLString_List()
	{
		Fmx::Dae::Schema::_di_IXMLString_List intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLString_List*(void) { return (Fmx::Dae::Schema::IXMLString_List*)&__IXMLString_List; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLGlsl_shader_typeList FShader;
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attributeList FBind_attribute;
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniformList FBind_uniform;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGlsl_shader_typeList __fastcall Get_Shader();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attributeList __fastcall Get_Bind_attribute();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniformList __fastcall Get_Bind_uniform();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type() { }
	
private:
	void *__IXMLGlsl_program_type;	// Fmx::Dae::Schema::IXMLGlsl_program_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D7E168BB-4ED6-433F-A32F-BB2445094A2A}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type*)&__IXMLGlsl_program_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_shader_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Stage();
	Fmx::Dae::Schema::_di_IXMLFx_sources_type __fastcall Get_Sources();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Stage(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_shader_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_shader_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_shader_type() { }
	
private:
	void *__IXMLGlsl_shader_type;	// Fmx::Dae::Schema::IXMLGlsl_shader_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {51452731-B6C2-443E-8896-A2A6421522BB}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_shader_type()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_shader_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_shader_type*(void) { return (Fmx::Dae::Schema::IXMLGlsl_shader_type*)&__IXMLGlsl_shader_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_shader_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGlsl_shader_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGlsl_shader_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGlsl_shader_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_shader_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_shader_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_shader_typeList() { }
	
private:
	void *__IXMLGlsl_shader_typeList;	// Fmx::Dae::Schema::IXMLGlsl_shader_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AC9CFA59-3EE9-4EEF-ADD8-21A37E2DC54E}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_shader_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_shader_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_shader_typeList*(void) { return (Fmx::Dae::Schema::IXMLGlsl_shader_typeList*)&__IXMLGlsl_shader_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type_bind_attribute : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Symbol();
	System::UnicodeString __fastcall Get_Semantic();
	void __fastcall Set_Symbol(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type_bind_attribute(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type_bind_attribute(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type_bind_attribute() { }
	
private:
	void *__IXMLGlsl_program_type_bind_attribute;	// Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attribute 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9F82BA01-CACF-4704-9F95-AC54F980704D}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attribute()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attribute intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attribute*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attribute*)&__IXMLGlsl_program_type_bind_attribute; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type_bind_attributeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attribute __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attribute __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attribute __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type_bind_attributeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type_bind_attributeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type_bind_attributeList() { }
	
private:
	void *__IXMLGlsl_program_type_bind_attributeList;	// Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attributeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AE4DBB61-3748-488E-A457-311C3F512780}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attributeList()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_attributeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attributeList*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type_bind_attributeList*)&__IXMLGlsl_program_type_bind_attributeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type_bind_uniform : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Symbol();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform_param __fastcall Get_Param();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLGlsl_array_type __fastcall Get_Array_();
	void __fastcall Set_Symbol(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type_bind_uniform(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type_bind_uniform(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type_bind_uniform() { }
	
private:
	void *__IXMLGlsl_program_type_bind_uniform;	// Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6B4EFB46-1411-4566-9335-FDD2C9D6757E}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform*)&__IXMLGlsl_program_type_bind_uniform; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type_bind_uniformList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type_bind_uniformList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type_bind_uniformList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type_bind_uniformList() { }
	
private:
	void *__IXMLGlsl_program_type_bind_uniformList;	// Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniformList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {14EEEEE4-2FF0-48CD-B7BC-6438026A6E60}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniformList()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniformList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniformList*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniformList*)&__IXMLGlsl_program_type_bind_uniformList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGlsl_program_type_bind_uniform_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGlsl_program_type_bind_uniform_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGlsl_program_type_bind_uniform_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGlsl_program_type_bind_uniform_param() { }
	
private:
	void *__IXMLGlsl_program_type_bind_uniform_param;	// Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D88A1514-4663-4EA6-AB8C-BB5B6BA700C4}
	operator Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform_param()
	{
		Fmx::Dae::Schema::_di_IXMLGlsl_program_type_bind_uniform_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform_param*(void) { return (Fmx::Dae::Schema::IXMLGlsl_program_type_bind_uniform_param*)&__IXMLGlsl_program_type_bind_uniform_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_glsl_type_technique_pass_evaluate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList FColor_target;
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList FDepth_target;
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList FStencil_target;
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList FColor_clear;
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList FDepth_clear;
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList FStencil_clear;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList __fastcall Get_Color_target();
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList __fastcall Get_Depth_target();
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList __fastcall Get_Stencil_target();
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList __fastcall Get_Color_clear();
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList __fastcall Get_Depth_clear();
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList __fastcall Get_Stencil_clear();
	System::UnicodeString __fastcall Get_Draw();
	void __fastcall Set_Draw(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_glsl_type_technique_pass_evaluate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_glsl_type_technique_pass_evaluate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_glsl_type_technique_pass_evaluate() { }
	
private:
	void *__IXMLProfile_glsl_type_technique_pass_evaluate;	// Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_evaluate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2606BC23-1DE4-4361-B9AE-DA132C5A5458}
	operator Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_evaluate()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_glsl_type_technique_pass_evaluate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_evaluate*(void) { return (Fmx::Dae::Schema::IXMLProfile_glsl_type_technique_pass_evaluate*)&__IXMLProfile_glsl_type_technique_pass_evaluate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLAlpha_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLAlpha_func_func __fastcall Get_Func();
	Fmx::Dae::Schema::_di_IXMLAlpha_func_value __fastcall Get_Value();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAlpha_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAlpha_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAlpha_func() { }
	
private:
	void *__IXMLAlpha_func;	// Fmx::Dae::Schema::IXMLAlpha_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5E80FDE7-A37C-4DCF-8439-FA7983FDE1E5}
	operator Fmx::Dae::Schema::_di_IXMLAlpha_func()
	{
		Fmx::Dae::Schema::_di_IXMLAlpha_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLAlpha_func*(void) { return (Fmx::Dae::Schema::IXMLAlpha_func*)&__IXMLAlpha_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLAlpha_func_func : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAlpha_func_func(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAlpha_func_func(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAlpha_func_func() { }
	
private:
	void *__IXMLAlpha_func_func;	// Fmx::Dae::Schema::IXMLAlpha_func_func 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B04312A2-DCC1-4FCA-AC5A-A2AFD766978E}
	operator Fmx::Dae::Schema::_di_IXMLAlpha_func_func()
	{
		Fmx::Dae::Schema::_di_IXMLAlpha_func_func intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLAlpha_func_func*(void) { return (Fmx::Dae::Schema::IXMLAlpha_func_func*)&__IXMLAlpha_func_func; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLAlpha_func_value : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	float __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(float Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAlpha_func_value(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAlpha_func_value(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAlpha_func_value() { }
	
private:
	void *__IXMLAlpha_func_value;	// Fmx::Dae::Schema::IXMLAlpha_func_value 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {22973CFF-E5A8-4F6B-B21D-A50E0B031C52}
	operator Fmx::Dae::Schema::_di_IXMLAlpha_func_value()
	{
		Fmx::Dae::Schema::_di_IXMLAlpha_func_value intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLAlpha_func_value*(void) { return (Fmx::Dae::Schema::IXMLAlpha_func_value*)&__IXMLAlpha_func_value; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_material : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLColor_material_face __fastcall Get_Face();
	Fmx::Dae::Schema::_di_IXMLColor_material_mode __fastcall Get_Mode();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_material(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_material(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_material() { }
	
private:
	void *__IXMLColor_material;	// Fmx::Dae::Schema::IXMLColor_material 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BC7C74A5-B64C-4C87-9161-2B969B56EB5A}
	operator Fmx::Dae::Schema::_di_IXMLColor_material()
	{
		Fmx::Dae::Schema::_di_IXMLColor_material intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_material*(void) { return (Fmx::Dae::Schema::IXMLColor_material*)&__IXMLColor_material; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_material_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_material_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_material_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_material_face() { }
	
private:
	void *__IXMLColor_material_face;	// Fmx::Dae::Schema::IXMLColor_material_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2F07B6A0-7315-453D-919D-944CE7981DDF}
	operator Fmx::Dae::Schema::_di_IXMLColor_material_face()
	{
		Fmx::Dae::Schema::_di_IXMLColor_material_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_material_face*(void) { return (Fmx::Dae::Schema::IXMLColor_material_face*)&__IXMLColor_material_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_material_mode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_material_mode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_material_mode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_material_mode() { }
	
private:
	void *__IXMLColor_material_mode;	// Fmx::Dae::Schema::IXMLColor_material_mode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F67CF692-4DF8-4F4E-B352-FDDDA78A1204}
	operator Fmx::Dae::Schema::_di_IXMLColor_material_mode()
	{
		Fmx::Dae::Schema::_di_IXMLColor_material_mode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_material_mode*(void) { return (Fmx::Dae::Schema::IXMLColor_material_mode*)&__IXMLColor_material_mode; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_mode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_mode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_mode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_mode() { }
	
private:
	void *__IXMLFog_mode;	// Fmx::Dae::Schema::IXMLFog_mode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {06EBD9BD-164B-497E-8FB9-EB6989FCB31D}
	operator Fmx::Dae::Schema::_di_IXMLFog_mode()
	{
		Fmx::Dae::Schema::_di_IXMLFog_mode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_mode*(void) { return (Fmx::Dae::Schema::IXMLFog_mode*)&__IXMLFog_mode; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_coord_src : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_coord_src(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_coord_src(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_coord_src() { }
	
private:
	void *__IXMLFog_coord_src;	// Fmx::Dae::Schema::IXMLFog_coord_src 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {185CDC9D-76D5-4481-B48A-A4CB8BD3214F}
	operator Fmx::Dae::Schema::_di_IXMLFog_coord_src()
	{
		Fmx::Dae::Schema::_di_IXMLFog_coord_src intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_coord_src*(void) { return (Fmx::Dae::Schema::IXMLFog_coord_src*)&__IXMLFog_coord_src; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_model_color_control : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_model_color_control(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_model_color_control(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_model_color_control() { }
	
private:
	void *__IXMLLight_model_color_control;	// Fmx::Dae::Schema::IXMLLight_model_color_control 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D7518D67-8186-41EA-ACCD-80AFBF633F62}
	operator Fmx::Dae::Schema::_di_IXMLLight_model_color_control()
	{
		Fmx::Dae::Schema::_di_IXMLLight_model_color_control intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_model_color_control*(void) { return (Fmx::Dae::Schema::IXMLLight_model_color_control*)&__IXMLLight_model_color_control; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLogic_op : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLogic_op(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLogic_op(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLogic_op() { }
	
private:
	void *__IXMLLogic_op;	// Fmx::Dae::Schema::IXMLLogic_op 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {10134A2D-6BA7-48E0-BA28-2F6D374B2789}
	operator Fmx::Dae::Schema::_di_IXMLLogic_op()
	{
		Fmx::Dae::Schema::_di_IXMLLogic_op intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLogic_op*(void) { return (Fmx::Dae::Schema::IXMLLogic_op*)&__IXMLLogic_op; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_mode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLPolygon_mode_face __fastcall Get_Face();
	Fmx::Dae::Schema::_di_IXMLPolygon_mode_mode __fastcall Get_Mode();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_mode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_mode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_mode() { }
	
private:
	void *__IXMLPolygon_mode;	// Fmx::Dae::Schema::IXMLPolygon_mode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79F16467-42FD-4B2E-9832-AC2FC9C86C85}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_mode()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_mode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_mode*(void) { return (Fmx::Dae::Schema::IXMLPolygon_mode*)&__IXMLPolygon_mode; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_mode_face : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_mode_face(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_mode_face(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_mode_face() { }
	
private:
	void *__IXMLPolygon_mode_face;	// Fmx::Dae::Schema::IXMLPolygon_mode_face 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B2D6DD4F-09D2-481D-9B92-7FA6D68FB0AE}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_mode_face()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_mode_face intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_mode_face*(void) { return (Fmx::Dae::Schema::IXMLPolygon_mode_face*)&__IXMLPolygon_mode_face; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_mode_mode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_mode_mode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_mode_mode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_mode_mode() { }
	
private:
	void *__IXMLPolygon_mode_mode;	// Fmx::Dae::Schema::IXMLPolygon_mode_mode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5C67DCF5-7F56-4035-A954-B3A8C32D5081}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_mode_mode()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_mode_mode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_mode_mode*(void) { return (Fmx::Dae::Schema::IXMLPolygon_mode_mode*)&__IXMLPolygon_mode_mode; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLShade_model : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLShade_model(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLShade_model(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLShade_model() { }
	
private:
	void *__IXMLShade_model;	// Fmx::Dae::Schema::IXMLShade_model 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {98537992-CD6C-4FAE-A7F1-FD0935C022E3}
	operator Fmx::Dae::Schema::_di_IXMLShade_model()
	{
		Fmx::Dae::Schema::_di_IXMLShade_model intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLShade_model*(void) { return (Fmx::Dae::Schema::IXMLShade_model*)&__IXMLShade_model; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_enable() { }
	
private:
	void *__IXMLLight_enable;	// Fmx::Dae::Schema::IXMLLight_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9B3F70F5-AFF2-49DF-9B0D-070C837B6C78}
	operator Fmx::Dae::Schema::_di_IXMLLight_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLight_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_enable*(void) { return (Fmx::Dae::Schema::IXMLLight_enable*)&__IXMLLight_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_ambient : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_ambient(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_ambient(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_ambient() { }
	
private:
	void *__IXMLLight_ambient;	// Fmx::Dae::Schema::IXMLLight_ambient 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A17ADB8B-9588-4636-B210-DBDC2660CC24}
	operator Fmx::Dae::Schema::_di_IXMLLight_ambient()
	{
		Fmx::Dae::Schema::_di_IXMLLight_ambient intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_ambient*(void) { return (Fmx::Dae::Schema::IXMLLight_ambient*)&__IXMLLight_ambient; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_diffuse : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_diffuse(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_diffuse(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_diffuse() { }
	
private:
	void *__IXMLLight_diffuse;	// Fmx::Dae::Schema::IXMLLight_diffuse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A69CAB39-A9D2-4BBF-A6BD-BE9CA02D2EC8}
	operator Fmx::Dae::Schema::_di_IXMLLight_diffuse()
	{
		Fmx::Dae::Schema::_di_IXMLLight_diffuse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_diffuse*(void) { return (Fmx::Dae::Schema::IXMLLight_diffuse*)&__IXMLLight_diffuse; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_specular : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_specular(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_specular(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_specular() { }
	
private:
	void *__IXMLLight_specular;	// Fmx::Dae::Schema::IXMLLight_specular 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5B3A6785-C73B-4D8A-8ACE-766DA4E715FE}
	operator Fmx::Dae::Schema::_di_IXMLLight_specular()
	{
		Fmx::Dae::Schema::_di_IXMLLight_specular intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_specular*(void) { return (Fmx::Dae::Schema::IXMLLight_specular*)&__IXMLLight_specular; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_position : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_position(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_position(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_position() { }
	
private:
	void *__IXMLLight_position;	// Fmx::Dae::Schema::IXMLLight_position 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {244739E7-1D14-40E1-BBDD-22D9CB6B7C52}
	operator Fmx::Dae::Schema::_di_IXMLLight_position()
	{
		Fmx::Dae::Schema::_di_IXMLLight_position intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_position*(void) { return (Fmx::Dae::Schema::IXMLLight_position*)&__IXMLLight_position; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_constant_attenuation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_constant_attenuation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_constant_attenuation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_constant_attenuation() { }
	
private:
	void *__IXMLLight_constant_attenuation;	// Fmx::Dae::Schema::IXMLLight_constant_attenuation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B4F72777-C282-4480-B4E0-5388B6AFEC9F}
	operator Fmx::Dae::Schema::_di_IXMLLight_constant_attenuation()
	{
		Fmx::Dae::Schema::_di_IXMLLight_constant_attenuation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_constant_attenuation*(void) { return (Fmx::Dae::Schema::IXMLLight_constant_attenuation*)&__IXMLLight_constant_attenuation; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_linear_attenuation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_linear_attenuation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_linear_attenuation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_linear_attenuation() { }
	
private:
	void *__IXMLLight_linear_attenuation;	// Fmx::Dae::Schema::IXMLLight_linear_attenuation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6FDB0175-DE28-4103-8344-3228BCF0D6AC}
	operator Fmx::Dae::Schema::_di_IXMLLight_linear_attenuation()
	{
		Fmx::Dae::Schema::_di_IXMLLight_linear_attenuation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_linear_attenuation*(void) { return (Fmx::Dae::Schema::IXMLLight_linear_attenuation*)&__IXMLLight_linear_attenuation; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_quadratic_attenuation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_quadratic_attenuation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_quadratic_attenuation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_quadratic_attenuation() { }
	
private:
	void *__IXMLLight_quadratic_attenuation;	// Fmx::Dae::Schema::IXMLLight_quadratic_attenuation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {636D9352-FCEA-4F85-A103-B14CB7048D9F}
	operator Fmx::Dae::Schema::_di_IXMLLight_quadratic_attenuation()
	{
		Fmx::Dae::Schema::_di_IXMLLight_quadratic_attenuation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_quadratic_attenuation*(void) { return (Fmx::Dae::Schema::IXMLLight_quadratic_attenuation*)&__IXMLLight_quadratic_attenuation; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_spot_cutoff : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_spot_cutoff(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_spot_cutoff(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_spot_cutoff() { }
	
private:
	void *__IXMLLight_spot_cutoff;	// Fmx::Dae::Schema::IXMLLight_spot_cutoff 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D7E09A6B-5073-48CC-8854-328211342072}
	operator Fmx::Dae::Schema::_di_IXMLLight_spot_cutoff()
	{
		Fmx::Dae::Schema::_di_IXMLLight_spot_cutoff intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_spot_cutoff*(void) { return (Fmx::Dae::Schema::IXMLLight_spot_cutoff*)&__IXMLLight_spot_cutoff; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_spot_direction : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_spot_direction(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_spot_direction(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_spot_direction() { }
	
private:
	void *__IXMLLight_spot_direction;	// Fmx::Dae::Schema::IXMLLight_spot_direction 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {61A8B857-E354-4A71-A42C-7BDA181725EE}
	operator Fmx::Dae::Schema::_di_IXMLLight_spot_direction()
	{
		Fmx::Dae::Schema::_di_IXMLLight_spot_direction intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_spot_direction*(void) { return (Fmx::Dae::Schema::IXMLLight_spot_direction*)&__IXMLLight_spot_direction; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_spot_exponent : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_spot_exponent(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_spot_exponent(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_spot_exponent() { }
	
private:
	void *__IXMLLight_spot_exponent;	// Fmx::Dae::Schema::IXMLLight_spot_exponent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B73B38AE-66AD-446A-A2D3-83832E3F2F21}
	operator Fmx::Dae::Schema::_di_IXMLLight_spot_exponent()
	{
		Fmx::Dae::Schema::_di_IXMLLight_spot_exponent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_spot_exponent*(void) { return (Fmx::Dae::Schema::IXMLLight_spot_exponent*)&__IXMLLight_spot_exponent; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture1D : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture1D(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture1D(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture1D() { }
	
private:
	void *__IXMLTexture1D;	// Fmx::Dae::Schema::IXMLTexture1D 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1863E56A-A78C-40B9-AE8A-79FFE79630CB}
	operator Fmx::Dae::Schema::_di_IXMLTexture1D()
	{
		Fmx::Dae::Schema::_di_IXMLTexture1D intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture1D*(void) { return (Fmx::Dae::Schema::IXMLTexture1D*)&__IXMLTexture1D; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture2D : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture2D(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture2D(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture2D() { }
	
private:
	void *__IXMLTexture2D;	// Fmx::Dae::Schema::IXMLTexture2D 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8699390F-477D-4423-ABD3-60F953BA6749}
	operator Fmx::Dae::Schema::_di_IXMLTexture2D()
	{
		Fmx::Dae::Schema::_di_IXMLTexture2D intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture2D*(void) { return (Fmx::Dae::Schema::IXMLTexture2D*)&__IXMLTexture2D; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture3D : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture3D(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture3D(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture3D() { }
	
private:
	void *__IXMLTexture3D;	// Fmx::Dae::Schema::IXMLTexture3D 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D58AC6C6-9734-4319-82ED-97CD8873CFC6}
	operator Fmx::Dae::Schema::_di_IXMLTexture3D()
	{
		Fmx::Dae::Schema::_di_IXMLTexture3D intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture3D*(void) { return (Fmx::Dae::Schema::IXMLTexture3D*)&__IXMLTexture3D; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureCUBE : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureCUBE(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureCUBE(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureCUBE() { }
	
private:
	void *__IXMLTextureCUBE;	// Fmx::Dae::Schema::IXMLTextureCUBE 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CAE87EF8-0F7A-4587-9A22-DF5919314CE0}
	operator Fmx::Dae::Schema::_di_IXMLTextureCUBE()
	{
		Fmx::Dae::Schema::_di_IXMLTextureCUBE intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureCUBE*(void) { return (Fmx::Dae::Schema::IXMLTextureCUBE*)&__IXMLTextureCUBE; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureRECT : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureRECT(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureRECT(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureRECT() { }
	
private:
	void *__IXMLTextureRECT;	// Fmx::Dae::Schema::IXMLTextureRECT 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DA9552E7-C88F-4598-AFC1-363946A1C2EE}
	operator Fmx::Dae::Schema::_di_IXMLTextureRECT()
	{
		Fmx::Dae::Schema::_di_IXMLTextureRECT intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureRECT*(void) { return (Fmx::Dae::Schema::IXMLTextureRECT*)&__IXMLTextureRECT; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureDEPTH : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Index();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Index(unsigned Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureDEPTH(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureDEPTH(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureDEPTH() { }
	
private:
	void *__IXMLTextureDEPTH;	// Fmx::Dae::Schema::IXMLTextureDEPTH 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0FB934A7-76F0-4E58-8A6A-DD3C10261FA1}
	operator Fmx::Dae::Schema::_di_IXMLTextureDEPTH()
	{
		Fmx::Dae::Schema::_di_IXMLTextureDEPTH intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureDEPTH*(void) { return (Fmx::Dae::Schema::IXMLTextureDEPTH*)&__IXMLTextureDEPTH; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture1D_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture1D_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture1D_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture1D_enable() { }
	
private:
	void *__IXMLTexture1D_enable;	// Fmx::Dae::Schema::IXMLTexture1D_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7510804E-A7D8-4498-A2FA-1F77408D3F08}
	operator Fmx::Dae::Schema::_di_IXMLTexture1D_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTexture1D_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture1D_enable*(void) { return (Fmx::Dae::Schema::IXMLTexture1D_enable*)&__IXMLTexture1D_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture2D_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture2D_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture2D_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture2D_enable() { }
	
private:
	void *__IXMLTexture2D_enable;	// Fmx::Dae::Schema::IXMLTexture2D_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8F82795D-5F39-4FB8-976B-44CC36BDA980}
	operator Fmx::Dae::Schema::_di_IXMLTexture2D_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTexture2D_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture2D_enable*(void) { return (Fmx::Dae::Schema::IXMLTexture2D_enable*)&__IXMLTexture2D_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture3D_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture3D_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture3D_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture3D_enable() { }
	
private:
	void *__IXMLTexture3D_enable;	// Fmx::Dae::Schema::IXMLTexture3D_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {771CF6FD-C8E2-481E-98D8-273843ECE0F2}
	operator Fmx::Dae::Schema::_di_IXMLTexture3D_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTexture3D_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture3D_enable*(void) { return (Fmx::Dae::Schema::IXMLTexture3D_enable*)&__IXMLTexture3D_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureCUBE_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureCUBE_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureCUBE_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureCUBE_enable() { }
	
private:
	void *__IXMLTextureCUBE_enable;	// Fmx::Dae::Schema::IXMLTextureCUBE_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A8F3FDCC-61FC-4230-B47E-3BA585CD4AB9}
	operator Fmx::Dae::Schema::_di_IXMLTextureCUBE_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTextureCUBE_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureCUBE_enable*(void) { return (Fmx::Dae::Schema::IXMLTextureCUBE_enable*)&__IXMLTextureCUBE_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureRECT_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureRECT_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureRECT_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureRECT_enable() { }
	
private:
	void *__IXMLTextureRECT_enable;	// Fmx::Dae::Schema::IXMLTextureRECT_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8B21AF3B-5CB4-4725-B496-B501E5A24139}
	operator Fmx::Dae::Schema::_di_IXMLTextureRECT_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTextureRECT_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureRECT_enable*(void) { return (Fmx::Dae::Schema::IXMLTextureRECT_enable*)&__IXMLTextureRECT_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTextureDEPTH_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTextureDEPTH_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTextureDEPTH_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTextureDEPTH_enable() { }
	
private:
	void *__IXMLTextureDEPTH_enable;	// Fmx::Dae::Schema::IXMLTextureDEPTH_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {76B39D55-B0DC-40CB-A357-D902DC54F922}
	operator Fmx::Dae::Schema::_di_IXMLTextureDEPTH_enable()
	{
		Fmx::Dae::Schema::_di_IXMLTextureDEPTH_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTextureDEPTH_enable*(void) { return (Fmx::Dae::Schema::IXMLTextureDEPTH_enable*)&__IXMLTextureDEPTH_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture_env_color : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture_env_color(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture_env_color(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture_env_color() { }
	
private:
	void *__IXMLTexture_env_color;	// Fmx::Dae::Schema::IXMLTexture_env_color 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9A2B7E85-0E70-45B6-A629-C1158436F192}
	operator Fmx::Dae::Schema::_di_IXMLTexture_env_color()
	{
		Fmx::Dae::Schema::_di_IXMLTexture_env_color intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture_env_color*(void) { return (Fmx::Dae::Schema::IXMLTexture_env_color*)&__IXMLTexture_env_color; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture_env_mode : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture_env_mode(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture_env_mode(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture_env_mode() { }
	
private:
	void *__IXMLTexture_env_mode;	// Fmx::Dae::Schema::IXMLTexture_env_mode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F47D11E6-6094-4D4E-B542-C66BF3E54E7E}
	operator Fmx::Dae::Schema::_di_IXMLTexture_env_mode()
	{
		Fmx::Dae::Schema::_di_IXMLTexture_env_mode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture_env_mode*(void) { return (Fmx::Dae::Schema::IXMLTexture_env_mode*)&__IXMLTexture_env_mode; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLClip_plane : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLClip_plane(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLClip_plane(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLClip_plane() { }
	
private:
	void *__IXMLClip_plane;	// Fmx::Dae::Schema::IXMLClip_plane 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {23696286-5B1A-4FB7-ACF6-4E5A0F64FB56}
	operator Fmx::Dae::Schema::_di_IXMLClip_plane()
	{
		Fmx::Dae::Schema::_di_IXMLClip_plane intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLClip_plane*(void) { return (Fmx::Dae::Schema::IXMLClip_plane*)&__IXMLClip_plane; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLClip_plane_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	unsigned __fastcall Get_Index();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
	void __fastcall Set_Index(unsigned Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLClip_plane_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLClip_plane_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLClip_plane_enable() { }
	
private:
	void *__IXMLClip_plane_enable;	// Fmx::Dae::Schema::IXMLClip_plane_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1DA1DFD3-7761-42CE-8155-781155881996}
	operator Fmx::Dae::Schema::_di_IXMLClip_plane_enable()
	{
		Fmx::Dae::Schema::_di_IXMLClip_plane_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLClip_plane_enable*(void) { return (Fmx::Dae::Schema::IXMLClip_plane_enable*)&__IXMLClip_plane_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_bounds : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_bounds(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_bounds(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_bounds() { }
	
private:
	void *__IXMLDepth_bounds;	// Fmx::Dae::Schema::IXMLDepth_bounds 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1E0E8779-4FE4-4942-A401-62228F1E0C57}
	operator Fmx::Dae::Schema::_di_IXMLDepth_bounds()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_bounds intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_bounds*(void) { return (Fmx::Dae::Schema::IXMLDepth_bounds*)&__IXMLDepth_bounds; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_density : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_density(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_density(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_density() { }
	
private:
	void *__IXMLFog_density;	// Fmx::Dae::Schema::IXMLFog_density 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FDF22EDE-BBC2-43EA-8310-13B65E3AC00E}
	operator Fmx::Dae::Schema::_di_IXMLFog_density()
	{
		Fmx::Dae::Schema::_di_IXMLFog_density intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_density*(void) { return (Fmx::Dae::Schema::IXMLFog_density*)&__IXMLFog_density; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_start : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_start(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_start(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_start() { }
	
private:
	void *__IXMLFog_start;	// Fmx::Dae::Schema::IXMLFog_start 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FF716319-DD72-412D-A924-95CE3294839B}
	operator Fmx::Dae::Schema::_di_IXMLFog_start()
	{
		Fmx::Dae::Schema::_di_IXMLFog_start intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_start*(void) { return (Fmx::Dae::Schema::IXMLFog_start*)&__IXMLFog_start; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_end : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_end(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_end(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_end() { }
	
private:
	void *__IXMLFog_end;	// Fmx::Dae::Schema::IXMLFog_end 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {898A2C36-06FC-4F55-B037-E6DBF737D017}
	operator Fmx::Dae::Schema::_di_IXMLFog_end()
	{
		Fmx::Dae::Schema::_di_IXMLFog_end intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_end*(void) { return (Fmx::Dae::Schema::IXMLFog_end*)&__IXMLFog_end; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_color : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_color(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_color(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_color() { }
	
private:
	void *__IXMLFog_color;	// Fmx::Dae::Schema::IXMLFog_color 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {57557404-E167-47E9-A5D0-B91E107D7D73}
	operator Fmx::Dae::Schema::_di_IXMLFog_color()
	{
		Fmx::Dae::Schema::_di_IXMLFog_color intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_color*(void) { return (Fmx::Dae::Schema::IXMLFog_color*)&__IXMLFog_color; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_model_ambient : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_model_ambient(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_model_ambient(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_model_ambient() { }
	
private:
	void *__IXMLLight_model_ambient;	// Fmx::Dae::Schema::IXMLLight_model_ambient 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7AAEE8D1-103F-44F4-B287-DD073C0850D7}
	operator Fmx::Dae::Schema::_di_IXMLLight_model_ambient()
	{
		Fmx::Dae::Schema::_di_IXMLLight_model_ambient intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_model_ambient*(void) { return (Fmx::Dae::Schema::IXMLLight_model_ambient*)&__IXMLLight_model_ambient; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLighting_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLighting_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLighting_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLighting_enable() { }
	
private:
	void *__IXMLLighting_enable;	// Fmx::Dae::Schema::IXMLLighting_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A2ACC9A6-0A7F-490A-B1C2-95E092CF98D1}
	operator Fmx::Dae::Schema::_di_IXMLLighting_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLighting_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLighting_enable*(void) { return (Fmx::Dae::Schema::IXMLLighting_enable*)&__IXMLLighting_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLine_stipple : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLine_stipple(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLine_stipple(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLine_stipple() { }
	
private:
	void *__IXMLLine_stipple;	// Fmx::Dae::Schema::IXMLLine_stipple 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C71B95FC-3AC2-4F65-824C-55671593FB89}
	operator Fmx::Dae::Schema::_di_IXMLLine_stipple()
	{
		Fmx::Dae::Schema::_di_IXMLLine_stipple intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLine_stipple*(void) { return (Fmx::Dae::Schema::IXMLLine_stipple*)&__IXMLLine_stipple; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMaterial_ambient : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMaterial_ambient(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMaterial_ambient(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMaterial_ambient() { }
	
private:
	void *__IXMLMaterial_ambient;	// Fmx::Dae::Schema::IXMLMaterial_ambient 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {579ACCFA-10CF-4916-B72D-51A3A54C9DA8}
	operator Fmx::Dae::Schema::_di_IXMLMaterial_ambient()
	{
		Fmx::Dae::Schema::_di_IXMLMaterial_ambient intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMaterial_ambient*(void) { return (Fmx::Dae::Schema::IXMLMaterial_ambient*)&__IXMLMaterial_ambient; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMaterial_diffuse : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMaterial_diffuse(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMaterial_diffuse(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMaterial_diffuse() { }
	
private:
	void *__IXMLMaterial_diffuse;	// Fmx::Dae::Schema::IXMLMaterial_diffuse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59AF41C9-D7E2-472C-9542-FF911E89F265}
	operator Fmx::Dae::Schema::_di_IXMLMaterial_diffuse()
	{
		Fmx::Dae::Schema::_di_IXMLMaterial_diffuse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMaterial_diffuse*(void) { return (Fmx::Dae::Schema::IXMLMaterial_diffuse*)&__IXMLMaterial_diffuse; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMaterial_emission : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMaterial_emission(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMaterial_emission(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMaterial_emission() { }
	
private:
	void *__IXMLMaterial_emission;	// Fmx::Dae::Schema::IXMLMaterial_emission 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A06C9C32-3DE4-49F1-AE45-446FA78A293E}
	operator Fmx::Dae::Schema::_di_IXMLMaterial_emission()
	{
		Fmx::Dae::Schema::_di_IXMLMaterial_emission intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMaterial_emission*(void) { return (Fmx::Dae::Schema::IXMLMaterial_emission*)&__IXMLMaterial_emission; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMaterial_shininess : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMaterial_shininess(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMaterial_shininess(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMaterial_shininess() { }
	
private:
	void *__IXMLMaterial_shininess;	// Fmx::Dae::Schema::IXMLMaterial_shininess 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1C458950-15D2-4CCA-9715-8076826C61FC}
	operator Fmx::Dae::Schema::_di_IXMLMaterial_shininess()
	{
		Fmx::Dae::Schema::_di_IXMLMaterial_shininess intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMaterial_shininess*(void) { return (Fmx::Dae::Schema::IXMLMaterial_shininess*)&__IXMLMaterial_shininess; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMaterial_specular : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMaterial_specular(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMaterial_specular(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMaterial_specular() { }
	
private:
	void *__IXMLMaterial_specular;	// Fmx::Dae::Schema::IXMLMaterial_specular 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8910CF75-29A7-4BC2-A8AB-B7F40AC467CB}
	operator Fmx::Dae::Schema::_di_IXMLMaterial_specular()
	{
		Fmx::Dae::Schema::_di_IXMLMaterial_specular intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMaterial_specular*(void) { return (Fmx::Dae::Schema::IXMLMaterial_specular*)&__IXMLMaterial_specular; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLModel_view_matrix : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLModel_view_matrix(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLModel_view_matrix(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLModel_view_matrix() { }
	
private:
	void *__IXMLModel_view_matrix;	// Fmx::Dae::Schema::IXMLModel_view_matrix 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A8D9233B-9332-4F52-80C4-BD7876978FCF}
	operator Fmx::Dae::Schema::_di_IXMLModel_view_matrix()
	{
		Fmx::Dae::Schema::_di_IXMLModel_view_matrix intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLModel_view_matrix*(void) { return (Fmx::Dae::Schema::IXMLModel_view_matrix*)&__IXMLModel_view_matrix; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_distance_attenuation : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_distance_attenuation(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_distance_attenuation(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_distance_attenuation() { }
	
private:
	void *__IXMLPoint_distance_attenuation;	// Fmx::Dae::Schema::IXMLPoint_distance_attenuation 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BE1A8B54-8C53-44A5-9EE5-1824BCF99000}
	operator Fmx::Dae::Schema::_di_IXMLPoint_distance_attenuation()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_distance_attenuation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_distance_attenuation*(void) { return (Fmx::Dae::Schema::IXMLPoint_distance_attenuation*)&__IXMLPoint_distance_attenuation; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_fade_threshold_size : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_fade_threshold_size(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_fade_threshold_size(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_fade_threshold_size() { }
	
private:
	void *__IXMLPoint_fade_threshold_size;	// Fmx::Dae::Schema::IXMLPoint_fade_threshold_size 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1F6C7D83-A090-4967-9040-AF9E5D707289}
	operator Fmx::Dae::Schema::_di_IXMLPoint_fade_threshold_size()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_fade_threshold_size intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_fade_threshold_size*(void) { return (Fmx::Dae::Schema::IXMLPoint_fade_threshold_size*)&__IXMLPoint_fade_threshold_size; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_size_min : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_size_min(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_size_min(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_size_min() { }
	
private:
	void *__IXMLPoint_size_min;	// Fmx::Dae::Schema::IXMLPoint_size_min 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E352D128-11EF-4CD7-8E3E-2762DD9494D3}
	operator Fmx::Dae::Schema::_di_IXMLPoint_size_min()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_size_min intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_size_min*(void) { return (Fmx::Dae::Schema::IXMLPoint_size_min*)&__IXMLPoint_size_min; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_size_max : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	double __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(double Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_size_max(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_size_max(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_size_max() { }
	
private:
	void *__IXMLPoint_size_max;	// Fmx::Dae::Schema::IXMLPoint_size_max 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {72B75059-D89A-4292-A9F9-EC5321D33093}
	operator Fmx::Dae::Schema::_di_IXMLPoint_size_max()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_size_max intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_size_max*(void) { return (Fmx::Dae::Schema::IXMLPoint_size_max*)&__IXMLPoint_size_max; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProjection_matrix : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProjection_matrix(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProjection_matrix(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProjection_matrix() { }
	
private:
	void *__IXMLProjection_matrix;	// Fmx::Dae::Schema::IXMLProjection_matrix 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1EB56546-D9B6-4321-BD6B-A48E54A24BB9}
	operator Fmx::Dae::Schema::_di_IXMLProjection_matrix()
	{
		Fmx::Dae::Schema::_di_IXMLProjection_matrix intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProjection_matrix*(void) { return (Fmx::Dae::Schema::IXMLProjection_matrix*)&__IXMLProjection_matrix; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLAlpha_test_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLAlpha_test_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLAlpha_test_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLAlpha_test_enable() { }
	
private:
	void *__IXMLAlpha_test_enable;	// Fmx::Dae::Schema::IXMLAlpha_test_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7553D2CB-AB43-4D1A-8EA7-226A95EE07BB}
	operator Fmx::Dae::Schema::_di_IXMLAlpha_test_enable()
	{
		Fmx::Dae::Schema::_di_IXMLAlpha_test_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLAlpha_test_enable*(void) { return (Fmx::Dae::Schema::IXMLAlpha_test_enable*)&__IXMLAlpha_test_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_logic_op_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_logic_op_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_logic_op_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_logic_op_enable() { }
	
private:
	void *__IXMLColor_logic_op_enable;	// Fmx::Dae::Schema::IXMLColor_logic_op_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {113B6ACC-B48D-46E4-9DF7-F074D74965D8}
	operator Fmx::Dae::Schema::_di_IXMLColor_logic_op_enable()
	{
		Fmx::Dae::Schema::_di_IXMLColor_logic_op_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_logic_op_enable*(void) { return (Fmx::Dae::Schema::IXMLColor_logic_op_enable*)&__IXMLColor_logic_op_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLColor_material_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLColor_material_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLColor_material_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLColor_material_enable() { }
	
private:
	void *__IXMLColor_material_enable;	// Fmx::Dae::Schema::IXMLColor_material_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E66A6C37-B8DC-41B1-BD1F-CEF43DA43D93}
	operator Fmx::Dae::Schema::_di_IXMLColor_material_enable()
	{
		Fmx::Dae::Schema::_di_IXMLColor_material_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLColor_material_enable*(void) { return (Fmx::Dae::Schema::IXMLColor_material_enable*)&__IXMLColor_material_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_bounds_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_bounds_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_bounds_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_bounds_enable() { }
	
private:
	void *__IXMLDepth_bounds_enable;	// Fmx::Dae::Schema::IXMLDepth_bounds_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {01648435-2804-494A-9E8C-B6B66FF825A5}
	operator Fmx::Dae::Schema::_di_IXMLDepth_bounds_enable()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_bounds_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_bounds_enable*(void) { return (Fmx::Dae::Schema::IXMLDepth_bounds_enable*)&__IXMLDepth_bounds_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLDepth_clamp_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLDepth_clamp_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLDepth_clamp_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLDepth_clamp_enable() { }
	
private:
	void *__IXMLDepth_clamp_enable;	// Fmx::Dae::Schema::IXMLDepth_clamp_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {35B3ED93-A29D-4BFD-A257-0F6CE6DEA402}
	operator Fmx::Dae::Schema::_di_IXMLDepth_clamp_enable()
	{
		Fmx::Dae::Schema::_di_IXMLDepth_clamp_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLDepth_clamp_enable*(void) { return (Fmx::Dae::Schema::IXMLDepth_clamp_enable*)&__IXMLDepth_clamp_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFog_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFog_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFog_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFog_enable() { }
	
private:
	void *__IXMLFog_enable;	// Fmx::Dae::Schema::IXMLFog_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7E8DA0C9-1D00-47E8-A469-2CBEC3F783A0}
	operator Fmx::Dae::Schema::_di_IXMLFog_enable()
	{
		Fmx::Dae::Schema::_di_IXMLFog_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFog_enable*(void) { return (Fmx::Dae::Schema::IXMLFog_enable*)&__IXMLFog_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_model_local_viewer_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_model_local_viewer_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_model_local_viewer_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_model_local_viewer_enable() { }
	
private:
	void *__IXMLLight_model_local_viewer_enable;	// Fmx::Dae::Schema::IXMLLight_model_local_viewer_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CCEBEFD4-037F-4E4B-A0E5-9A266B3F6969}
	operator Fmx::Dae::Schema::_di_IXMLLight_model_local_viewer_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLight_model_local_viewer_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_model_local_viewer_enable*(void) { return (Fmx::Dae::Schema::IXMLLight_model_local_viewer_enable*)&__IXMLLight_model_local_viewer_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLight_model_two_side_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLight_model_two_side_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLight_model_two_side_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLight_model_two_side_enable() { }
	
private:
	void *__IXMLLight_model_two_side_enable;	// Fmx::Dae::Schema::IXMLLight_model_two_side_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CC0F4456-0AF5-43EA-943D-D537458A6589}
	operator Fmx::Dae::Schema::_di_IXMLLight_model_two_side_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLight_model_two_side_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLight_model_two_side_enable*(void) { return (Fmx::Dae::Schema::IXMLLight_model_two_side_enable*)&__IXMLLight_model_two_side_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLine_smooth_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLine_smooth_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLine_smooth_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLine_smooth_enable() { }
	
private:
	void *__IXMLLine_smooth_enable;	// Fmx::Dae::Schema::IXMLLine_smooth_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {94DA41B0-F029-4FAE-8894-665F06FF0622}
	operator Fmx::Dae::Schema::_di_IXMLLine_smooth_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLine_smooth_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLine_smooth_enable*(void) { return (Fmx::Dae::Schema::IXMLLine_smooth_enable*)&__IXMLLine_smooth_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLine_stipple_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLine_stipple_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLine_stipple_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLine_stipple_enable() { }
	
private:
	void *__IXMLLine_stipple_enable;	// Fmx::Dae::Schema::IXMLLine_stipple_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FA03F5F8-B664-4DC5-9E03-E7C0C599FDC0}
	operator Fmx::Dae::Schema::_di_IXMLLine_stipple_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLine_stipple_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLine_stipple_enable*(void) { return (Fmx::Dae::Schema::IXMLLine_stipple_enable*)&__IXMLLine_stipple_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLLogic_op_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLLogic_op_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLLogic_op_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLLogic_op_enable() { }
	
private:
	void *__IXMLLogic_op_enable;	// Fmx::Dae::Schema::IXMLLogic_op_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CDAAFF36-C730-4EF4-B183-314A5A596746}
	operator Fmx::Dae::Schema::_di_IXMLLogic_op_enable()
	{
		Fmx::Dae::Schema::_di_IXMLLogic_op_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLLogic_op_enable*(void) { return (Fmx::Dae::Schema::IXMLLogic_op_enable*)&__IXMLLogic_op_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLMultisample_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLMultisample_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLMultisample_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLMultisample_enable() { }
	
private:
	void *__IXMLMultisample_enable;	// Fmx::Dae::Schema::IXMLMultisample_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CCF0CA01-3BF2-422B-953E-7E135C695E2F}
	operator Fmx::Dae::Schema::_di_IXMLMultisample_enable()
	{
		Fmx::Dae::Schema::_di_IXMLMultisample_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLMultisample_enable*(void) { return (Fmx::Dae::Schema::IXMLMultisample_enable*)&__IXMLMultisample_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLNormalize_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLNormalize_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLNormalize_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLNormalize_enable() { }
	
private:
	void *__IXMLNormalize_enable;	// Fmx::Dae::Schema::IXMLNormalize_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C6E01C09-5A55-4E29-B346-81837C98DFD9}
	operator Fmx::Dae::Schema::_di_IXMLNormalize_enable()
	{
		Fmx::Dae::Schema::_di_IXMLNormalize_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLNormalize_enable*(void) { return (Fmx::Dae::Schema::IXMLNormalize_enable*)&__IXMLNormalize_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPoint_smooth_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPoint_smooth_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPoint_smooth_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPoint_smooth_enable() { }
	
private:
	void *__IXMLPoint_smooth_enable;	// Fmx::Dae::Schema::IXMLPoint_smooth_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {05BDB1A5-095A-4F0E-B7FD-A2DE5309E674}
	operator Fmx::Dae::Schema::_di_IXMLPoint_smooth_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPoint_smooth_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPoint_smooth_enable*(void) { return (Fmx::Dae::Schema::IXMLPoint_smooth_enable*)&__IXMLPoint_smooth_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_offset_line_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_offset_line_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_offset_line_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_offset_line_enable() { }
	
private:
	void *__IXMLPolygon_offset_line_enable;	// Fmx::Dae::Schema::IXMLPolygon_offset_line_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7BB4F48B-DDBD-44E8-87D9-C07D43A338D8}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_offset_line_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_offset_line_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_offset_line_enable*(void) { return (Fmx::Dae::Schema::IXMLPolygon_offset_line_enable*)&__IXMLPolygon_offset_line_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_offset_point_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_offset_point_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_offset_point_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_offset_point_enable() { }
	
private:
	void *__IXMLPolygon_offset_point_enable;	// Fmx::Dae::Schema::IXMLPolygon_offset_point_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C5D32DEA-1B80-45A2-A8B6-21B7203E0917}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_offset_point_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_offset_point_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_offset_point_enable*(void) { return (Fmx::Dae::Schema::IXMLPolygon_offset_point_enable*)&__IXMLPolygon_offset_point_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_smooth_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_smooth_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_smooth_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_smooth_enable() { }
	
private:
	void *__IXMLPolygon_smooth_enable;	// Fmx::Dae::Schema::IXMLPolygon_smooth_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {414AB649-FD9D-4E68-B688-3F65D217EA7C}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_smooth_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_smooth_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_smooth_enable*(void) { return (Fmx::Dae::Schema::IXMLPolygon_smooth_enable*)&__IXMLPolygon_smooth_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLPolygon_stipple_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLPolygon_stipple_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLPolygon_stipple_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLPolygon_stipple_enable() { }
	
private:
	void *__IXMLPolygon_stipple_enable;	// Fmx::Dae::Schema::IXMLPolygon_stipple_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C2FC82BC-B4E8-48B0-8EAD-0D5E4D40151A}
	operator Fmx::Dae::Schema::_di_IXMLPolygon_stipple_enable()
	{
		Fmx::Dae::Schema::_di_IXMLPolygon_stipple_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLPolygon_stipple_enable*(void) { return (Fmx::Dae::Schema::IXMLPolygon_stipple_enable*)&__IXMLPolygon_stipple_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLRescale_normal_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLRescale_normal_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLRescale_normal_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLRescale_normal_enable() { }
	
private:
	void *__IXMLRescale_normal_enable;	// Fmx::Dae::Schema::IXMLRescale_normal_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3909791C-64A5-490E-B7CA-2F073A85D15C}
	operator Fmx::Dae::Schema::_di_IXMLRescale_normal_enable()
	{
		Fmx::Dae::Schema::_di_IXMLRescale_normal_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLRescale_normal_enable*(void) { return (Fmx::Dae::Schema::IXMLRescale_normal_enable*)&__IXMLRescale_normal_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLSample_alpha_to_one_enable : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	bool __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(bool Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLSample_alpha_to_one_enable(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLSample_alpha_to_one_enable(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLSample_alpha_to_one_enable() { }
	
private:
	void *__IXMLSample_alpha_to_one_enable;	// Fmx::Dae::Schema::IXMLSample_alpha_to_one_enable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {391B0BF4-8ABE-4446-ABEB-C36AA2E3C7C1}
	operator Fmx::Dae::Schema::_di_IXMLSample_alpha_to_one_enable()
	{
		Fmx::Dae::Schema::_di_IXMLSample_alpha_to_one_enable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLSample_alpha_to_one_enable*(void) { return (Fmx::Dae::Schema::IXMLSample_alpha_to_one_enable*)&__IXMLSample_alpha_to_one_enable; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	System::UnicodeString __fastcall Get_Semantic();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_newparam_type() { }
	
private:
	void *__IXMLFx_common_newparam_type;	// Fmx::Dae::Schema::IXMLFx_common_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C08A7A26-FA6B-4602-9CA5-913D5A27FC32}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLFx_common_newparam_type*)&__IXMLFx_common_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_newparam_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_newparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLFx_common_newparam_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLFx_common_newparam_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_newparam_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_newparam_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_newparam_typeList() { }
	
private:
	void *__IXMLFx_common_newparam_typeList;	// Fmx::Dae::Schema::IXMLFx_common_newparam_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FECE62AC-EA3E-4438-B9CE-7B4E5EC15B8A}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_newparam_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_newparam_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_newparam_typeList*(void) { return (Fmx::Dae::Schema::IXMLFx_common_newparam_typeList*)&__IXMLFx_common_newparam_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_cg_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList FCode;
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList FInclude;
	Fmx::Dae::Schema::_di_IXMLCg_newparam_typeList FNewparam;
	Fmx::Dae::Schema::_di_IXMLProfile_cg_type_techniqueList FTechnique;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Platform();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_code_typeList __fastcall Get_Code();
	Fmx::Dae::Schema::_di_IXMLFx_include_typeList __fastcall Get_Include();
	Fmx::Dae::Schema::_di_IXMLCg_newparam_typeList __fastcall Get_Newparam();
	Fmx::Dae::Schema::_di_IXMLProfile_cg_type_techniqueList __fastcall Get_Technique();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Platform(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_cg_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_cg_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_cg_type() { }
	
private:
	void *__IXMLProfile_cg_type;	// Fmx::Dae::Schema::IXMLProfile_cg_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {72471E87-0B39-43F1-9435-47744AEDC77D}
	operator Fmx::Dae::Schema::_di_IXMLProfile_cg_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_cg_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_cg_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_cg_type*)&__IXMLProfile_cg_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	System::UnicodeString __fastcall Get_Semantic();
	System::UnicodeString __fastcall Get_Modifier();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	System::UnicodeString __fastcall Get_Bool2x1();
	System::UnicodeString __fastcall Get_Bool2x2();
	System::UnicodeString __fastcall Get_Bool2x3();
	System::UnicodeString __fastcall Get_Bool2x4();
	System::UnicodeString __fastcall Get_Bool3x1();
	System::UnicodeString __fastcall Get_Bool3x2();
	System::UnicodeString __fastcall Get_Bool3x3();
	System::UnicodeString __fastcall Get_Bool3x4();
	System::UnicodeString __fastcall Get_Bool4x1();
	System::UnicodeString __fastcall Get_Bool4x2();
	System::UnicodeString __fastcall Get_Bool4x3();
	System::UnicodeString __fastcall Get_Bool4x4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	System::UnicodeString __fastcall Get_Int2x1();
	System::UnicodeString __fastcall Get_Int2x2();
	System::UnicodeString __fastcall Get_Int2x3();
	System::UnicodeString __fastcall Get_Int2x4();
	System::UnicodeString __fastcall Get_Int3x1();
	System::UnicodeString __fastcall Get_Int3x2();
	System::UnicodeString __fastcall Get_Int3x3();
	System::UnicodeString __fastcall Get_Int3x4();
	System::UnicodeString __fastcall Get_Int4x1();
	System::UnicodeString __fastcall Get_Int4x2();
	System::UnicodeString __fastcall Get_Int4x3();
	System::UnicodeString __fastcall Get_Int4x4();
	double __fastcall Get_Half();
	System::UnicodeString __fastcall Get_Half2();
	System::UnicodeString __fastcall Get_Half3();
	System::UnicodeString __fastcall Get_Half4();
	System::UnicodeString __fastcall Get_Half2x1();
	System::UnicodeString __fastcall Get_Half2x2();
	System::UnicodeString __fastcall Get_Half2x3();
	System::UnicodeString __fastcall Get_Half2x4();
	System::UnicodeString __fastcall Get_Half3x1();
	System::UnicodeString __fastcall Get_Half3x2();
	System::UnicodeString __fastcall Get_Half3x3();
	System::UnicodeString __fastcall Get_Half3x4();
	System::UnicodeString __fastcall Get_Half4x1();
	System::UnicodeString __fastcall Get_Half4x2();
	System::UnicodeString __fastcall Get_Half4x3();
	System::UnicodeString __fastcall Get_Half4x4();
	double __fastcall Get_Fixed();
	System::UnicodeString __fastcall Get_Fixed2();
	System::UnicodeString __fastcall Get_Fixed3();
	System::UnicodeString __fastcall Get_Fixed4();
	System::UnicodeString __fastcall Get_Fixed2x1();
	System::UnicodeString __fastcall Get_Fixed2x2();
	System::UnicodeString __fastcall Get_Fixed2x3();
	System::UnicodeString __fastcall Get_Fixed2x4();
	System::UnicodeString __fastcall Get_Fixed3x1();
	System::UnicodeString __fastcall Get_Fixed3x2();
	System::UnicodeString __fastcall Get_Fixed3x3();
	System::UnicodeString __fastcall Get_Fixed3x4();
	System::UnicodeString __fastcall Get_Fixed4x1();
	System::UnicodeString __fastcall Get_Fixed4x2();
	System::UnicodeString __fastcall Get_Fixed4x3();
	System::UnicodeString __fastcall Get_Fixed4x4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_String_();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLCg_array_type __fastcall Get_Array_();
	Fmx::Dae::Schema::_di_IXMLCg_user_type __fastcall Get_Usertype();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Modifier(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Bool2x1(System::UnicodeString Value);
	void __fastcall Set_Bool2x2(System::UnicodeString Value);
	void __fastcall Set_Bool2x3(System::UnicodeString Value);
	void __fastcall Set_Bool2x4(System::UnicodeString Value);
	void __fastcall Set_Bool3x1(System::UnicodeString Value);
	void __fastcall Set_Bool3x2(System::UnicodeString Value);
	void __fastcall Set_Bool3x3(System::UnicodeString Value);
	void __fastcall Set_Bool3x4(System::UnicodeString Value);
	void __fastcall Set_Bool4x1(System::UnicodeString Value);
	void __fastcall Set_Bool4x2(System::UnicodeString Value);
	void __fastcall Set_Bool4x3(System::UnicodeString Value);
	void __fastcall Set_Bool4x4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Int2x1(System::UnicodeString Value);
	void __fastcall Set_Int2x2(System::UnicodeString Value);
	void __fastcall Set_Int2x3(System::UnicodeString Value);
	void __fastcall Set_Int2x4(System::UnicodeString Value);
	void __fastcall Set_Int3x1(System::UnicodeString Value);
	void __fastcall Set_Int3x2(System::UnicodeString Value);
	void __fastcall Set_Int3x3(System::UnicodeString Value);
	void __fastcall Set_Int3x4(System::UnicodeString Value);
	void __fastcall Set_Int4x1(System::UnicodeString Value);
	void __fastcall Set_Int4x2(System::UnicodeString Value);
	void __fastcall Set_Int4x3(System::UnicodeString Value);
	void __fastcall Set_Int4x4(System::UnicodeString Value);
	void __fastcall Set_Half(double Value);
	void __fastcall Set_Half2(System::UnicodeString Value);
	void __fastcall Set_Half3(System::UnicodeString Value);
	void __fastcall Set_Half4(System::UnicodeString Value);
	void __fastcall Set_Half2x1(System::UnicodeString Value);
	void __fastcall Set_Half2x2(System::UnicodeString Value);
	void __fastcall Set_Half2x3(System::UnicodeString Value);
	void __fastcall Set_Half2x4(System::UnicodeString Value);
	void __fastcall Set_Half3x1(System::UnicodeString Value);
	void __fastcall Set_Half3x2(System::UnicodeString Value);
	void __fastcall Set_Half3x3(System::UnicodeString Value);
	void __fastcall Set_Half3x4(System::UnicodeString Value);
	void __fastcall Set_Half4x1(System::UnicodeString Value);
	void __fastcall Set_Half4x2(System::UnicodeString Value);
	void __fastcall Set_Half4x3(System::UnicodeString Value);
	void __fastcall Set_Half4x4(System::UnicodeString Value);
	void __fastcall Set_Fixed(double Value);
	void __fastcall Set_Fixed2(System::UnicodeString Value);
	void __fastcall Set_Fixed3(System::UnicodeString Value);
	void __fastcall Set_Fixed4(System::UnicodeString Value);
	void __fastcall Set_Fixed2x1(System::UnicodeString Value);
	void __fastcall Set_Fixed2x2(System::UnicodeString Value);
	void __fastcall Set_Fixed2x3(System::UnicodeString Value);
	void __fastcall Set_Fixed2x4(System::UnicodeString Value);
	void __fastcall Set_Fixed3x1(System::UnicodeString Value);
	void __fastcall Set_Fixed3x2(System::UnicodeString Value);
	void __fastcall Set_Fixed3x3(System::UnicodeString Value);
	void __fastcall Set_Fixed3x4(System::UnicodeString Value);
	void __fastcall Set_Fixed4x1(System::UnicodeString Value);
	void __fastcall Set_Fixed4x2(System::UnicodeString Value);
	void __fastcall Set_Fixed4x3(System::UnicodeString Value);
	void __fastcall Set_Fixed4x4(System::UnicodeString Value);
	void __fastcall Set_String_(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_newparam_type() { }
	
private:
	void *__IXMLCg_newparam_type;	// Fmx::Dae::Schema::IXMLCg_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7FFBBBF-B1D5-4BF2-9673-D846B10AC83A}
	operator Fmx::Dae::Schema::_di_IXMLCg_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLCg_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLCg_newparam_type*)&__IXMLCg_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_newparam_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLCg_newparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLCg_newparam_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLCg_newparam_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_newparam_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_newparam_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_newparam_typeList() { }
	
private:
	void *__IXMLCg_newparam_typeList;	// Fmx::Dae::Schema::IXMLCg_newparam_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {291DE285-B968-4BC2-8F93-1684386D0551}
	operator Fmx::Dae::Schema::_di_IXMLCg_newparam_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLCg_newparam_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_newparam_typeList*(void) { return (Fmx::Dae::Schema::IXMLCg_newparam_typeList*)&__IXMLCg_newparam_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_array_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	unsigned __fastcall Get_Length();
	bool __fastcall Get_Resizable();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	System::UnicodeString __fastcall Get_Bool2x1();
	System::UnicodeString __fastcall Get_Bool2x2();
	System::UnicodeString __fastcall Get_Bool2x3();
	System::UnicodeString __fastcall Get_Bool2x4();
	System::UnicodeString __fastcall Get_Bool3x1();
	System::UnicodeString __fastcall Get_Bool3x2();
	System::UnicodeString __fastcall Get_Bool3x3();
	System::UnicodeString __fastcall Get_Bool3x4();
	System::UnicodeString __fastcall Get_Bool4x1();
	System::UnicodeString __fastcall Get_Bool4x2();
	System::UnicodeString __fastcall Get_Bool4x3();
	System::UnicodeString __fastcall Get_Bool4x4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	System::UnicodeString __fastcall Get_Int2x1();
	System::UnicodeString __fastcall Get_Int2x2();
	System::UnicodeString __fastcall Get_Int2x3();
	System::UnicodeString __fastcall Get_Int2x4();
	System::UnicodeString __fastcall Get_Int3x1();
	System::UnicodeString __fastcall Get_Int3x2();
	System::UnicodeString __fastcall Get_Int3x3();
	System::UnicodeString __fastcall Get_Int3x4();
	System::UnicodeString __fastcall Get_Int4x1();
	System::UnicodeString __fastcall Get_Int4x2();
	System::UnicodeString __fastcall Get_Int4x3();
	System::UnicodeString __fastcall Get_Int4x4();
	double __fastcall Get_Half();
	System::UnicodeString __fastcall Get_Half2();
	System::UnicodeString __fastcall Get_Half3();
	System::UnicodeString __fastcall Get_Half4();
	System::UnicodeString __fastcall Get_Half2x1();
	System::UnicodeString __fastcall Get_Half2x2();
	System::UnicodeString __fastcall Get_Half2x3();
	System::UnicodeString __fastcall Get_Half2x4();
	System::UnicodeString __fastcall Get_Half3x1();
	System::UnicodeString __fastcall Get_Half3x2();
	System::UnicodeString __fastcall Get_Half3x3();
	System::UnicodeString __fastcall Get_Half3x4();
	System::UnicodeString __fastcall Get_Half4x1();
	System::UnicodeString __fastcall Get_Half4x2();
	System::UnicodeString __fastcall Get_Half4x3();
	System::UnicodeString __fastcall Get_Half4x4();
	double __fastcall Get_Fixed();
	System::UnicodeString __fastcall Get_Fixed2();
	System::UnicodeString __fastcall Get_Fixed3();
	System::UnicodeString __fastcall Get_Fixed4();
	System::UnicodeString __fastcall Get_Fixed2x1();
	System::UnicodeString __fastcall Get_Fixed2x2();
	System::UnicodeString __fastcall Get_Fixed2x3();
	System::UnicodeString __fastcall Get_Fixed2x4();
	System::UnicodeString __fastcall Get_Fixed3x1();
	System::UnicodeString __fastcall Get_Fixed3x2();
	System::UnicodeString __fastcall Get_Fixed3x3();
	System::UnicodeString __fastcall Get_Fixed3x4();
	System::UnicodeString __fastcall Get_Fixed4x1();
	System::UnicodeString __fastcall Get_Fixed4x2();
	System::UnicodeString __fastcall Get_Fixed4x3();
	System::UnicodeString __fastcall Get_Fixed4x4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_String_();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLCg_array_type __fastcall Get_Array_();
	Fmx::Dae::Schema::_di_IXMLCg_user_type __fastcall Get_Usertype();
	void __fastcall Set_Length(unsigned Value);
	void __fastcall Set_Resizable(bool Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Bool2x1(System::UnicodeString Value);
	void __fastcall Set_Bool2x2(System::UnicodeString Value);
	void __fastcall Set_Bool2x3(System::UnicodeString Value);
	void __fastcall Set_Bool2x4(System::UnicodeString Value);
	void __fastcall Set_Bool3x1(System::UnicodeString Value);
	void __fastcall Set_Bool3x2(System::UnicodeString Value);
	void __fastcall Set_Bool3x3(System::UnicodeString Value);
	void __fastcall Set_Bool3x4(System::UnicodeString Value);
	void __fastcall Set_Bool4x1(System::UnicodeString Value);
	void __fastcall Set_Bool4x2(System::UnicodeString Value);
	void __fastcall Set_Bool4x3(System::UnicodeString Value);
	void __fastcall Set_Bool4x4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Int2x1(System::UnicodeString Value);
	void __fastcall Set_Int2x2(System::UnicodeString Value);
	void __fastcall Set_Int2x3(System::UnicodeString Value);
	void __fastcall Set_Int2x4(System::UnicodeString Value);
	void __fastcall Set_Int3x1(System::UnicodeString Value);
	void __fastcall Set_Int3x2(System::UnicodeString Value);
	void __fastcall Set_Int3x3(System::UnicodeString Value);
	void __fastcall Set_Int3x4(System::UnicodeString Value);
	void __fastcall Set_Int4x1(System::UnicodeString Value);
	void __fastcall Set_Int4x2(System::UnicodeString Value);
	void __fastcall Set_Int4x3(System::UnicodeString Value);
	void __fastcall Set_Int4x4(System::UnicodeString Value);
	void __fastcall Set_Half(double Value);
	void __fastcall Set_Half2(System::UnicodeString Value);
	void __fastcall Set_Half3(System::UnicodeString Value);
	void __fastcall Set_Half4(System::UnicodeString Value);
	void __fastcall Set_Half2x1(System::UnicodeString Value);
	void __fastcall Set_Half2x2(System::UnicodeString Value);
	void __fastcall Set_Half2x3(System::UnicodeString Value);
	void __fastcall Set_Half2x4(System::UnicodeString Value);
	void __fastcall Set_Half3x1(System::UnicodeString Value);
	void __fastcall Set_Half3x2(System::UnicodeString Value);
	void __fastcall Set_Half3x3(System::UnicodeString Value);
	void __fastcall Set_Half3x4(System::UnicodeString Value);
	void __fastcall Set_Half4x1(System::UnicodeString Value);
	void __fastcall Set_Half4x2(System::UnicodeString Value);
	void __fastcall Set_Half4x3(System::UnicodeString Value);
	void __fastcall Set_Half4x4(System::UnicodeString Value);
	void __fastcall Set_Fixed(double Value);
	void __fastcall Set_Fixed2(System::UnicodeString Value);
	void __fastcall Set_Fixed3(System::UnicodeString Value);
	void __fastcall Set_Fixed4(System::UnicodeString Value);
	void __fastcall Set_Fixed2x1(System::UnicodeString Value);
	void __fastcall Set_Fixed2x2(System::UnicodeString Value);
	void __fastcall Set_Fixed2x3(System::UnicodeString Value);
	void __fastcall Set_Fixed2x4(System::UnicodeString Value);
	void __fastcall Set_Fixed3x1(System::UnicodeString Value);
	void __fastcall Set_Fixed3x2(System::UnicodeString Value);
	void __fastcall Set_Fixed3x3(System::UnicodeString Value);
	void __fastcall Set_Fixed3x4(System::UnicodeString Value);
	void __fastcall Set_Fixed4x1(System::UnicodeString Value);
	void __fastcall Set_Fixed4x2(System::UnicodeString Value);
	void __fastcall Set_Fixed4x3(System::UnicodeString Value);
	void __fastcall Set_Fixed4x4(System::UnicodeString Value);
	void __fastcall Set_String_(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_array_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_array_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_array_type() { }
	
private:
	void *__IXMLCg_array_type;	// Fmx::Dae::Schema::IXMLCg_array_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {722C7EE0-6D1E-4526-8C2C-AE01A2AE4409}
	operator Fmx::Dae::Schema::_di_IXMLCg_array_type()
	{
		Fmx::Dae::Schema::_di_IXMLCg_array_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_array_type*(void) { return (Fmx::Dae::Schema::IXMLCg_array_type*)&__IXMLCg_array_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_user_type : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	System::UnicodeString __fastcall Get_Typename();
	System::UnicodeString __fastcall Get_Source();
	Fmx::Dae::Schema::_di_IXMLCg_setparam_type __fastcall Get_Setparam(int Index);
	void __fastcall Set_Typename(System::UnicodeString Value);
	void __fastcall Set_Source(System::UnicodeString Value);
	Fmx::Dae::Schema::_di_IXMLCg_setparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLCg_setparam_type __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_user_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_user_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_user_type() { }
	
private:
	void *__IXMLCg_user_type;	// Fmx::Dae::Schema::IXMLCg_user_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CDEA4C31-C2D5-4BB6-AF5D-F43A97E1D0E3}
	operator Fmx::Dae::Schema::_di_IXMLCg_user_type()
	{
		Fmx::Dae::Schema::_di_IXMLCg_user_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_user_type*(void) { return (Fmx::Dae::Schema::IXMLCg_user_type*)&__IXMLCg_user_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_setparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	System::UnicodeString __fastcall Get_Bool2x1();
	System::UnicodeString __fastcall Get_Bool2x2();
	System::UnicodeString __fastcall Get_Bool2x3();
	System::UnicodeString __fastcall Get_Bool2x4();
	System::UnicodeString __fastcall Get_Bool3x1();
	System::UnicodeString __fastcall Get_Bool3x2();
	System::UnicodeString __fastcall Get_Bool3x3();
	System::UnicodeString __fastcall Get_Bool3x4();
	System::UnicodeString __fastcall Get_Bool4x1();
	System::UnicodeString __fastcall Get_Bool4x2();
	System::UnicodeString __fastcall Get_Bool4x3();
	System::UnicodeString __fastcall Get_Bool4x4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	System::UnicodeString __fastcall Get_Int2x1();
	System::UnicodeString __fastcall Get_Int2x2();
	System::UnicodeString __fastcall Get_Int2x3();
	System::UnicodeString __fastcall Get_Int2x4();
	System::UnicodeString __fastcall Get_Int3x1();
	System::UnicodeString __fastcall Get_Int3x2();
	System::UnicodeString __fastcall Get_Int3x3();
	System::UnicodeString __fastcall Get_Int3x4();
	System::UnicodeString __fastcall Get_Int4x1();
	System::UnicodeString __fastcall Get_Int4x2();
	System::UnicodeString __fastcall Get_Int4x3();
	System::UnicodeString __fastcall Get_Int4x4();
	double __fastcall Get_Half();
	System::UnicodeString __fastcall Get_Half2();
	System::UnicodeString __fastcall Get_Half3();
	System::UnicodeString __fastcall Get_Half4();
	System::UnicodeString __fastcall Get_Half2x1();
	System::UnicodeString __fastcall Get_Half2x2();
	System::UnicodeString __fastcall Get_Half2x3();
	System::UnicodeString __fastcall Get_Half2x4();
	System::UnicodeString __fastcall Get_Half3x1();
	System::UnicodeString __fastcall Get_Half3x2();
	System::UnicodeString __fastcall Get_Half3x3();
	System::UnicodeString __fastcall Get_Half3x4();
	System::UnicodeString __fastcall Get_Half4x1();
	System::UnicodeString __fastcall Get_Half4x2();
	System::UnicodeString __fastcall Get_Half4x3();
	System::UnicodeString __fastcall Get_Half4x4();
	double __fastcall Get_Fixed();
	System::UnicodeString __fastcall Get_Fixed2();
	System::UnicodeString __fastcall Get_Fixed3();
	System::UnicodeString __fastcall Get_Fixed4();
	System::UnicodeString __fastcall Get_Fixed2x1();
	System::UnicodeString __fastcall Get_Fixed2x2();
	System::UnicodeString __fastcall Get_Fixed2x3();
	System::UnicodeString __fastcall Get_Fixed2x4();
	System::UnicodeString __fastcall Get_Fixed3x1();
	System::UnicodeString __fastcall Get_Fixed3x2();
	System::UnicodeString __fastcall Get_Fixed3x3();
	System::UnicodeString __fastcall Get_Fixed3x4();
	System::UnicodeString __fastcall Get_Fixed4x1();
	System::UnicodeString __fastcall Get_Fixed4x2();
	System::UnicodeString __fastcall Get_Fixed4x3();
	System::UnicodeString __fastcall Get_Fixed4x4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_String_();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLCg_array_type __fastcall Get_Array_();
	Fmx::Dae::Schema::_di_IXMLCg_user_type __fastcall Get_Usertype();
	void __fastcall Set_Ref(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Bool2x1(System::UnicodeString Value);
	void __fastcall Set_Bool2x2(System::UnicodeString Value);
	void __fastcall Set_Bool2x3(System::UnicodeString Value);
	void __fastcall Set_Bool2x4(System::UnicodeString Value);
	void __fastcall Set_Bool3x1(System::UnicodeString Value);
	void __fastcall Set_Bool3x2(System::UnicodeString Value);
	void __fastcall Set_Bool3x3(System::UnicodeString Value);
	void __fastcall Set_Bool3x4(System::UnicodeString Value);
	void __fastcall Set_Bool4x1(System::UnicodeString Value);
	void __fastcall Set_Bool4x2(System::UnicodeString Value);
	void __fastcall Set_Bool4x3(System::UnicodeString Value);
	void __fastcall Set_Bool4x4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Int2x1(System::UnicodeString Value);
	void __fastcall Set_Int2x2(System::UnicodeString Value);
	void __fastcall Set_Int2x3(System::UnicodeString Value);
	void __fastcall Set_Int2x4(System::UnicodeString Value);
	void __fastcall Set_Int3x1(System::UnicodeString Value);
	void __fastcall Set_Int3x2(System::UnicodeString Value);
	void __fastcall Set_Int3x3(System::UnicodeString Value);
	void __fastcall Set_Int3x4(System::UnicodeString Value);
	void __fastcall Set_Int4x1(System::UnicodeString Value);
	void __fastcall Set_Int4x2(System::UnicodeString Value);
	void __fastcall Set_Int4x3(System::UnicodeString Value);
	void __fastcall Set_Int4x4(System::UnicodeString Value);
	void __fastcall Set_Half(double Value);
	void __fastcall Set_Half2(System::UnicodeString Value);
	void __fastcall Set_Half3(System::UnicodeString Value);
	void __fastcall Set_Half4(System::UnicodeString Value);
	void __fastcall Set_Half2x1(System::UnicodeString Value);
	void __fastcall Set_Half2x2(System::UnicodeString Value);
	void __fastcall Set_Half2x3(System::UnicodeString Value);
	void __fastcall Set_Half2x4(System::UnicodeString Value);
	void __fastcall Set_Half3x1(System::UnicodeString Value);
	void __fastcall Set_Half3x2(System::UnicodeString Value);
	void __fastcall Set_Half3x3(System::UnicodeString Value);
	void __fastcall Set_Half3x4(System::UnicodeString Value);
	void __fastcall Set_Half4x1(System::UnicodeString Value);
	void __fastcall Set_Half4x2(System::UnicodeString Value);
	void __fastcall Set_Half4x3(System::UnicodeString Value);
	void __fastcall Set_Half4x4(System::UnicodeString Value);
	void __fastcall Set_Fixed(double Value);
	void __fastcall Set_Fixed2(System::UnicodeString Value);
	void __fastcall Set_Fixed3(System::UnicodeString Value);
	void __fastcall Set_Fixed4(System::UnicodeString Value);
	void __fastcall Set_Fixed2x1(System::UnicodeString Value);
	void __fastcall Set_Fixed2x2(System::UnicodeString Value);
	void __fastcall Set_Fixed2x3(System::UnicodeString Value);
	void __fastcall Set_Fixed2x4(System::UnicodeString Value);
	void __fastcall Set_Fixed3x1(System::UnicodeString Value);
	void __fastcall Set_Fixed3x2(System::UnicodeString Value);
	void __fastcall Set_Fixed3x3(System::UnicodeString Value);
	void __fastcall Set_Fixed3x4(System::UnicodeString Value);
	void __fastcall Set_Fixed4x1(System::UnicodeString Value);
	void __fastcall Set_Fixed4x2(System::UnicodeString Value);
	void __fastcall Set_Fixed4x3(System::UnicodeString Value);
	void __fastcall Set_Fixed4x4(System::UnicodeString Value);
	void __fastcall Set_String_(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_setparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_setparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_setparam_type() { }
	
private:
	void *__IXMLCg_setparam_type;	// Fmx::Dae::Schema::IXMLCg_setparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4EC7104E-4FD9-4CEB-81C1-C6A936A5DA3A}
	operator Fmx::Dae::Schema::_di_IXMLCg_setparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLCg_setparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_setparam_type*(void) { return (Fmx::Dae::Schema::IXMLCg_setparam_type*)&__IXMLCg_setparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_cg_type_technique : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLCg_pass_typeList FPass;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLCg_pass_typeList __fastcall Get_Pass();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_cg_type_technique(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_cg_type_technique(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_cg_type_technique() { }
	
private:
	void *__IXMLProfile_cg_type_technique;	// Fmx::Dae::Schema::IXMLProfile_cg_type_technique 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AF7CD944-FE24-419E-BDAF-CBF66B887FDF}
	operator Fmx::Dae::Schema::_di_IXMLProfile_cg_type_technique()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_cg_type_technique intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_cg_type_technique*(void) { return (Fmx::Dae::Schema::IXMLProfile_cg_type_technique*)&__IXMLProfile_cg_type_technique; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_cg_type_techniqueList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_cg_type_technique __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_cg_type_technique __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_cg_type_technique __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_cg_type_techniqueList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_cg_type_techniqueList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_cg_type_techniqueList() { }
	
private:
	void *__IXMLProfile_cg_type_techniqueList;	// Fmx::Dae::Schema::IXMLProfile_cg_type_techniqueList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B33EF92E-9251-4C2B-80CF-A5EDEA8732B2}
	operator Fmx::Dae::Schema::_di_IXMLProfile_cg_type_techniqueList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_cg_type_techniqueList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_cg_type_techniqueList*(void) { return (Fmx::Dae::Schema::IXMLProfile_cg_type_techniqueList*)&__IXMLProfile_cg_type_techniqueList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_states __fastcall Get_States();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program __fastcall Get_Program_();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_evaluate __fastcall Get_Evaluate();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type() { }
	
private:
	void *__IXMLCg_pass_type;	// Fmx::Dae::Schema::IXMLCg_pass_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5E68643B-711D-47F9-8663-138359C848BE}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type*)&__IXMLCg_pass_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLCg_pass_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLCg_pass_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_typeList() { }
	
private:
	void *__IXMLCg_pass_typeList;	// Fmx::Dae::Schema::IXMLCg_pass_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2061889B-8C77-4273-BC7D-468BC52F4FA5}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_typeList*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_typeList*)&__IXMLCg_pass_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_states : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLAlpha_func __fastcall Get_Alpha_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func __fastcall Get_Blend_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func_separate __fastcall Get_Blend_func_separate();
	Fmx::Dae::Schema::_di_IXMLBlend_equation __fastcall Get_Blend_equation();
	Fmx::Dae::Schema::_di_IXMLBlend_equation_separate __fastcall Get_Blend_equation_separate();
	Fmx::Dae::Schema::_di_IXMLColor_material __fastcall Get_Color_material();
	Fmx::Dae::Schema::_di_IXMLCull_face __fastcall Get_Cull_face();
	Fmx::Dae::Schema::_di_IXMLDepth_func __fastcall Get_Depth_func();
	Fmx::Dae::Schema::_di_IXMLFog_mode __fastcall Get_Fog_mode();
	Fmx::Dae::Schema::_di_IXMLFog_coord_src __fastcall Get_Fog_coord_src();
	Fmx::Dae::Schema::_di_IXMLFront_face __fastcall Get_Front_face();
	Fmx::Dae::Schema::_di_IXMLLight_model_color_control __fastcall Get_Light_model_color_control();
	Fmx::Dae::Schema::_di_IXMLLogic_op __fastcall Get_Logic_op();
	Fmx::Dae::Schema::_di_IXMLPolygon_mode __fastcall Get_Polygon_mode();
	Fmx::Dae::Schema::_di_IXMLShade_model __fastcall Get_Shade_model();
	Fmx::Dae::Schema::_di_IXMLStencil_func __fastcall Get_Stencil_func();
	Fmx::Dae::Schema::_di_IXMLStencil_op __fastcall Get_Stencil_op();
	Fmx::Dae::Schema::_di_IXMLStencil_func_separate __fastcall Get_Stencil_func_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_op_separate __fastcall Get_Stencil_op_separate();
	Fmx::Dae::Schema::_di_IXMLStencil_mask_separate __fastcall Get_Stencil_mask_separate();
	Fmx::Dae::Schema::_di_IXMLLight_enable __fastcall Get_Light_enable();
	Fmx::Dae::Schema::_di_IXMLLight_ambient __fastcall Get_Light_ambient();
	Fmx::Dae::Schema::_di_IXMLLight_diffuse __fastcall Get_Light_diffuse();
	Fmx::Dae::Schema::_di_IXMLLight_specular __fastcall Get_Light_specular();
	Fmx::Dae::Schema::_di_IXMLLight_position __fastcall Get_Light_position();
	Fmx::Dae::Schema::_di_IXMLLight_constant_attenuation __fastcall Get_Light_constant_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_linear_attenuation __fastcall Get_Light_linear_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_quadratic_attenuation __fastcall Get_Light_quadratic_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_spot_cutoff __fastcall Get_Light_spot_cutoff();
	Fmx::Dae::Schema::_di_IXMLLight_spot_direction __fastcall Get_Light_spot_direction();
	Fmx::Dae::Schema::_di_IXMLLight_spot_exponent __fastcall Get_Light_spot_exponent();
	Fmx::Dae::Schema::_di_IXMLTexture1D __fastcall Get_Texture1D();
	Fmx::Dae::Schema::_di_IXMLTexture2D __fastcall Get_Texture2D();
	Fmx::Dae::Schema::_di_IXMLTexture3D __fastcall Get_Texture3D();
	Fmx::Dae::Schema::_di_IXMLTextureCUBE __fastcall Get_TextureCUBE();
	Fmx::Dae::Schema::_di_IXMLTextureRECT __fastcall Get_TextureRECT();
	Fmx::Dae::Schema::_di_IXMLTextureDEPTH __fastcall Get_TextureDEPTH();
	Fmx::Dae::Schema::_di_IXMLTexture1D_enable __fastcall Get_Texture1D_enable();
	Fmx::Dae::Schema::_di_IXMLTexture2D_enable __fastcall Get_Texture2D_enable();
	Fmx::Dae::Schema::_di_IXMLTexture3D_enable __fastcall Get_Texture3D_enable();
	Fmx::Dae::Schema::_di_IXMLTextureCUBE_enable __fastcall Get_TextureCUBE_enable();
	Fmx::Dae::Schema::_di_IXMLTextureRECT_enable __fastcall Get_TextureRECT_enable();
	Fmx::Dae::Schema::_di_IXMLTextureDEPTH_enable __fastcall Get_TextureDEPTH_enable();
	Fmx::Dae::Schema::_di_IXMLTexture_env_color __fastcall Get_Texture_env_color();
	Fmx::Dae::Schema::_di_IXMLTexture_env_mode __fastcall Get_Texture_env_mode();
	Fmx::Dae::Schema::_di_IXMLClip_plane __fastcall Get_Clip_plane();
	Fmx::Dae::Schema::_di_IXMLClip_plane_enable __fastcall Get_Clip_plane_enable();
	Fmx::Dae::Schema::_di_IXMLBlend_color __fastcall Get_Blend_color();
	Fmx::Dae::Schema::_di_IXMLColor_mask __fastcall Get_Color_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_bounds __fastcall Get_Depth_bounds();
	Fmx::Dae::Schema::_di_IXMLDepth_mask __fastcall Get_Depth_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_range __fastcall Get_Depth_range();
	Fmx::Dae::Schema::_di_IXMLFog_density __fastcall Get_Fog_density();
	Fmx::Dae::Schema::_di_IXMLFog_start __fastcall Get_Fog_start();
	Fmx::Dae::Schema::_di_IXMLFog_end __fastcall Get_Fog_end();
	Fmx::Dae::Schema::_di_IXMLFog_color __fastcall Get_Fog_color();
	Fmx::Dae::Schema::_di_IXMLLight_model_ambient __fastcall Get_Light_model_ambient();
	Fmx::Dae::Schema::_di_IXMLLighting_enable __fastcall Get_Lighting_enable();
	Fmx::Dae::Schema::_di_IXMLLine_stipple __fastcall Get_Line_stipple();
	Fmx::Dae::Schema::_di_IXMLLine_width __fastcall Get_Line_width();
	Fmx::Dae::Schema::_di_IXMLMaterial_ambient __fastcall Get_Material_ambient();
	Fmx::Dae::Schema::_di_IXMLMaterial_diffuse __fastcall Get_Material_diffuse();
	Fmx::Dae::Schema::_di_IXMLMaterial_emission __fastcall Get_Material_emission();
	Fmx::Dae::Schema::_di_IXMLMaterial_shininess __fastcall Get_Material_shininess();
	Fmx::Dae::Schema::_di_IXMLMaterial_specular __fastcall Get_Material_specular();
	Fmx::Dae::Schema::_di_IXMLModel_view_matrix __fastcall Get_Model_view_matrix();
	Fmx::Dae::Schema::_di_IXMLPoint_distance_attenuation __fastcall Get_Point_distance_attenuation();
	Fmx::Dae::Schema::_di_IXMLPoint_fade_threshold_size __fastcall Get_Point_fade_threshold_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size __fastcall Get_Point_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size_min __fastcall Get_Point_size_min();
	Fmx::Dae::Schema::_di_IXMLPoint_size_max __fastcall Get_Point_size_max();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset __fastcall Get_Polygon_offset();
	Fmx::Dae::Schema::_di_IXMLProjection_matrix __fastcall Get_Projection_matrix();
	Fmx::Dae::Schema::_di_IXMLScissor __fastcall Get_Scissor();
	Fmx::Dae::Schema::_di_IXMLStencil_mask __fastcall Get_Stencil_mask();
	Fmx::Dae::Schema::_di_IXMLAlpha_test_enable __fastcall Get_Alpha_test_enable();
	Fmx::Dae::Schema::_di_IXMLBlend_enable __fastcall Get_Blend_enable();
	Fmx::Dae::Schema::_di_IXMLColor_logic_op_enable __fastcall Get_Color_logic_op_enable();
	Fmx::Dae::Schema::_di_IXMLColor_material_enable __fastcall Get_Color_material_enable();
	Fmx::Dae::Schema::_di_IXMLCull_face_enable __fastcall Get_Cull_face_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_bounds_enable __fastcall Get_Depth_bounds_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_clamp_enable __fastcall Get_Depth_clamp_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_test_enable __fastcall Get_Depth_test_enable();
	Fmx::Dae::Schema::_di_IXMLDither_enable __fastcall Get_Dither_enable();
	Fmx::Dae::Schema::_di_IXMLFog_enable __fastcall Get_Fog_enable();
	Fmx::Dae::Schema::_di_IXMLLight_model_local_viewer_enable __fastcall Get_Light_model_local_viewer_enable();
	Fmx::Dae::Schema::_di_IXMLLight_model_two_side_enable __fastcall Get_Light_model_two_side_enable();
	Fmx::Dae::Schema::_di_IXMLLine_smooth_enable __fastcall Get_Line_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLLine_stipple_enable __fastcall Get_Line_stipple_enable();
	Fmx::Dae::Schema::_di_IXMLLogic_op_enable __fastcall Get_Logic_op_enable();
	Fmx::Dae::Schema::_di_IXMLMultisample_enable __fastcall Get_Multisample_enable();
	Fmx::Dae::Schema::_di_IXMLNormalize_enable __fastcall Get_Normalize_enable();
	Fmx::Dae::Schema::_di_IXMLPoint_smooth_enable __fastcall Get_Point_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable __fastcall Get_Polygon_offset_fill_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_line_enable __fastcall Get_Polygon_offset_line_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_point_enable __fastcall Get_Polygon_offset_point_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_smooth_enable __fastcall Get_Polygon_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_stipple_enable __fastcall Get_Polygon_stipple_enable();
	Fmx::Dae::Schema::_di_IXMLRescale_normal_enable __fastcall Get_Rescale_normal_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable __fastcall Get_Sample_alpha_to_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_one_enable __fastcall Get_Sample_alpha_to_one_enable();
	Fmx::Dae::Schema::_di_IXMLSample_coverage_enable __fastcall Get_Sample_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLScissor_test_enable __fastcall Get_Scissor_test_enable();
	Fmx::Dae::Schema::_di_IXMLStencil_test_enable __fastcall Get_Stencil_test_enable();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_states(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_states(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_states() { }
	
private:
	void *__IXMLCg_pass_type_states;	// Fmx::Dae::Schema::IXMLCg_pass_type_states 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DCE713C8-FF4D-46EC-9B29-13AE6BD28018}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_states()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_states intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_states*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_states*)&__IXMLCg_pass_type_states; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader __fastcall Get_Shader(int Index);
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program() { }
	
private:
	void *__IXMLCg_pass_type_program;	// Fmx::Dae::Schema::IXMLCg_pass_type_program 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C08A8BFF-44BD-419B-A001-644E85549108}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program*)&__IXMLCg_pass_type_program; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program_shader : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList FCompiler;
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniformList FBind_uniform;
	
protected:
	System::UnicodeString __fastcall Get_Stage();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_sources __fastcall Get_Sources();
	Fmx::Dae::Schema::_di_IXMLFx_target_typeList __fastcall Get_Compiler();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniformList __fastcall Get_Bind_uniform();
	void __fastcall Set_Stage(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program_shader(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program_shader(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program_shader() { }
	
private:
	void *__IXMLCg_pass_type_program_shader;	// Fmx::Dae::Schema::IXMLCg_pass_type_program_shader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9DDEDC41-B263-4641-A554-3CF553B1AD14}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program_shader*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program_shader*)&__IXMLCg_pass_type_program_shader; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program_shader_sources : public TXMLFx_sources_type
{
	typedef TXMLFx_sources_type inherited;
	
protected:
	System::UnicodeString __fastcall Get_Entry();
	void __fastcall Set_Entry(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program_shader_sources(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_sources_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program_shader_sources(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_sources_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program_shader_sources() { }
	
private:
	void *__IXMLCg_pass_type_program_shader_sources;	// Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_sources 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D6EE468B-743C-4FA0-90D8-D5B7D47282E4}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_sources()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_sources intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_sources*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_sources*)&__IXMLCg_pass_type_program_shader_sources; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program_shader_bind_uniform : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Symbol();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform_param __fastcall Get_Param();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	System::UnicodeString __fastcall Get_Bool2x1();
	System::UnicodeString __fastcall Get_Bool2x2();
	System::UnicodeString __fastcall Get_Bool2x3();
	System::UnicodeString __fastcall Get_Bool2x4();
	System::UnicodeString __fastcall Get_Bool3x1();
	System::UnicodeString __fastcall Get_Bool3x2();
	System::UnicodeString __fastcall Get_Bool3x3();
	System::UnicodeString __fastcall Get_Bool3x4();
	System::UnicodeString __fastcall Get_Bool4x1();
	System::UnicodeString __fastcall Get_Bool4x2();
	System::UnicodeString __fastcall Get_Bool4x3();
	System::UnicodeString __fastcall Get_Bool4x4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	System::UnicodeString __fastcall Get_Int2x1();
	System::UnicodeString __fastcall Get_Int2x2();
	System::UnicodeString __fastcall Get_Int2x3();
	System::UnicodeString __fastcall Get_Int2x4();
	System::UnicodeString __fastcall Get_Int3x1();
	System::UnicodeString __fastcall Get_Int3x2();
	System::UnicodeString __fastcall Get_Int3x3();
	System::UnicodeString __fastcall Get_Int3x4();
	System::UnicodeString __fastcall Get_Int4x1();
	System::UnicodeString __fastcall Get_Int4x2();
	System::UnicodeString __fastcall Get_Int4x3();
	System::UnicodeString __fastcall Get_Int4x4();
	double __fastcall Get_Half();
	System::UnicodeString __fastcall Get_Half2();
	System::UnicodeString __fastcall Get_Half3();
	System::UnicodeString __fastcall Get_Half4();
	System::UnicodeString __fastcall Get_Half2x1();
	System::UnicodeString __fastcall Get_Half2x2();
	System::UnicodeString __fastcall Get_Half2x3();
	System::UnicodeString __fastcall Get_Half2x4();
	System::UnicodeString __fastcall Get_Half3x1();
	System::UnicodeString __fastcall Get_Half3x2();
	System::UnicodeString __fastcall Get_Half3x3();
	System::UnicodeString __fastcall Get_Half3x4();
	System::UnicodeString __fastcall Get_Half4x1();
	System::UnicodeString __fastcall Get_Half4x2();
	System::UnicodeString __fastcall Get_Half4x3();
	System::UnicodeString __fastcall Get_Half4x4();
	double __fastcall Get_Fixed();
	System::UnicodeString __fastcall Get_Fixed2();
	System::UnicodeString __fastcall Get_Fixed3();
	System::UnicodeString __fastcall Get_Fixed4();
	System::UnicodeString __fastcall Get_Fixed2x1();
	System::UnicodeString __fastcall Get_Fixed2x2();
	System::UnicodeString __fastcall Get_Fixed2x3();
	System::UnicodeString __fastcall Get_Fixed2x4();
	System::UnicodeString __fastcall Get_Fixed3x1();
	System::UnicodeString __fastcall Get_Fixed3x2();
	System::UnicodeString __fastcall Get_Fixed3x3();
	System::UnicodeString __fastcall Get_Fixed3x4();
	System::UnicodeString __fastcall Get_Fixed4x1();
	System::UnicodeString __fastcall Get_Fixed4x2();
	System::UnicodeString __fastcall Get_Fixed4x3();
	System::UnicodeString __fastcall Get_Fixed4x4();
	Fmx::Dae::Schema::_di_IXMLFx_sampler1D_type __fastcall Get_Sampler1D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler2D_type __fastcall Get_Sampler2D();
	Fmx::Dae::Schema::_di_IXMLFx_sampler3D_type __fastcall Get_Sampler3D();
	Fmx::Dae::Schema::_di_IXMLFx_samplerRECT_type __fastcall Get_SamplerRECT();
	Fmx::Dae::Schema::_di_IXMLFx_samplerCUBE_type __fastcall Get_SamplerCUBE();
	Fmx::Dae::Schema::_di_IXMLFx_samplerDEPTH_type __fastcall Get_SamplerDEPTH();
	System::UnicodeString __fastcall Get_String_();
	System::UnicodeString __fastcall Get_Enum();
	Fmx::Dae::Schema::_di_IXMLCg_array_type __fastcall Get_Array_();
	Fmx::Dae::Schema::_di_IXMLCg_user_type __fastcall Get_Usertype();
	void __fastcall Set_Symbol(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Bool2x1(System::UnicodeString Value);
	void __fastcall Set_Bool2x2(System::UnicodeString Value);
	void __fastcall Set_Bool2x3(System::UnicodeString Value);
	void __fastcall Set_Bool2x4(System::UnicodeString Value);
	void __fastcall Set_Bool3x1(System::UnicodeString Value);
	void __fastcall Set_Bool3x2(System::UnicodeString Value);
	void __fastcall Set_Bool3x3(System::UnicodeString Value);
	void __fastcall Set_Bool3x4(System::UnicodeString Value);
	void __fastcall Set_Bool4x1(System::UnicodeString Value);
	void __fastcall Set_Bool4x2(System::UnicodeString Value);
	void __fastcall Set_Bool4x3(System::UnicodeString Value);
	void __fastcall Set_Bool4x4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Int2x1(System::UnicodeString Value);
	void __fastcall Set_Int2x2(System::UnicodeString Value);
	void __fastcall Set_Int2x3(System::UnicodeString Value);
	void __fastcall Set_Int2x4(System::UnicodeString Value);
	void __fastcall Set_Int3x1(System::UnicodeString Value);
	void __fastcall Set_Int3x2(System::UnicodeString Value);
	void __fastcall Set_Int3x3(System::UnicodeString Value);
	void __fastcall Set_Int3x4(System::UnicodeString Value);
	void __fastcall Set_Int4x1(System::UnicodeString Value);
	void __fastcall Set_Int4x2(System::UnicodeString Value);
	void __fastcall Set_Int4x3(System::UnicodeString Value);
	void __fastcall Set_Int4x4(System::UnicodeString Value);
	void __fastcall Set_Half(double Value);
	void __fastcall Set_Half2(System::UnicodeString Value);
	void __fastcall Set_Half3(System::UnicodeString Value);
	void __fastcall Set_Half4(System::UnicodeString Value);
	void __fastcall Set_Half2x1(System::UnicodeString Value);
	void __fastcall Set_Half2x2(System::UnicodeString Value);
	void __fastcall Set_Half2x3(System::UnicodeString Value);
	void __fastcall Set_Half2x4(System::UnicodeString Value);
	void __fastcall Set_Half3x1(System::UnicodeString Value);
	void __fastcall Set_Half3x2(System::UnicodeString Value);
	void __fastcall Set_Half3x3(System::UnicodeString Value);
	void __fastcall Set_Half3x4(System::UnicodeString Value);
	void __fastcall Set_Half4x1(System::UnicodeString Value);
	void __fastcall Set_Half4x2(System::UnicodeString Value);
	void __fastcall Set_Half4x3(System::UnicodeString Value);
	void __fastcall Set_Half4x4(System::UnicodeString Value);
	void __fastcall Set_Fixed(double Value);
	void __fastcall Set_Fixed2(System::UnicodeString Value);
	void __fastcall Set_Fixed3(System::UnicodeString Value);
	void __fastcall Set_Fixed4(System::UnicodeString Value);
	void __fastcall Set_Fixed2x1(System::UnicodeString Value);
	void __fastcall Set_Fixed2x2(System::UnicodeString Value);
	void __fastcall Set_Fixed2x3(System::UnicodeString Value);
	void __fastcall Set_Fixed2x4(System::UnicodeString Value);
	void __fastcall Set_Fixed3x1(System::UnicodeString Value);
	void __fastcall Set_Fixed3x2(System::UnicodeString Value);
	void __fastcall Set_Fixed3x3(System::UnicodeString Value);
	void __fastcall Set_Fixed3x4(System::UnicodeString Value);
	void __fastcall Set_Fixed4x1(System::UnicodeString Value);
	void __fastcall Set_Fixed4x2(System::UnicodeString Value);
	void __fastcall Set_Fixed4x3(System::UnicodeString Value);
	void __fastcall Set_Fixed4x4(System::UnicodeString Value);
	void __fastcall Set_String_(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniform(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniform(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program_shader_bind_uniform() { }
	
private:
	void *__IXMLCg_pass_type_program_shader_bind_uniform;	// Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {555C0AEE-9DAD-436B-AA4B-7C3C1D2B2856}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform*)&__IXMLCg_pass_type_program_shader_bind_uniform; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program_shader_bind_uniformList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniformList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniformList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program_shader_bind_uniformList() { }
	
private:
	void *__IXMLCg_pass_type_program_shader_bind_uniformList;	// Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniformList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B77F4022-1452-49B9-B2A5-47311E38FDF8}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniformList()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniformList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniformList*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniformList*)&__IXMLCg_pass_type_program_shader_bind_uniformList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_program_shader_bind_uniform_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniform_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_program_shader_bind_uniform_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_program_shader_bind_uniform_param() { }
	
private:
	void *__IXMLCg_pass_type_program_shader_bind_uniform_param;	// Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6E5C3D86-8F9F-4102-AC04-A51541BC0338}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform_param()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_program_shader_bind_uniform_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform_param*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_program_shader_bind_uniform_param*)&__IXMLCg_pass_type_program_shader_bind_uniform_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLCg_pass_type_evaluate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList FColor_target;
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList FDepth_target;
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList FStencil_target;
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList FColor_clear;
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList FDepth_clear;
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList FStencil_clear;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList __fastcall Get_Color_target();
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList __fastcall Get_Depth_target();
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList __fastcall Get_Stencil_target();
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList __fastcall Get_Color_clear();
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList __fastcall Get_Depth_clear();
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList __fastcall Get_Stencil_clear();
	System::UnicodeString __fastcall Get_Draw();
	void __fastcall Set_Draw(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLCg_pass_type_evaluate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLCg_pass_type_evaluate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLCg_pass_type_evaluate() { }
	
private:
	void *__IXMLCg_pass_type_evaluate;	// Fmx::Dae::Schema::IXMLCg_pass_type_evaluate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E522CBBF-6FF3-4E31-BEB8-1DED9FEFBD2E}
	operator Fmx::Dae::Schema::_di_IXMLCg_pass_type_evaluate()
	{
		Fmx::Dae::Schema::_di_IXMLCg_pass_type_evaluate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLCg_pass_type_evaluate*(void) { return (Fmx::Dae::Schema::IXMLCg_pass_type_evaluate*)&__IXMLCg_pass_type_evaluate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLGles_newparam_typeList FNewparam;
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_techniqueList FTechnique;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Platform();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLGles_newparam_typeList __fastcall Get_Newparam();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_techniqueList __fastcall Get_Technique();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Platform(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type() { }
	
private:
	void *__IXMLProfile_gles_type;	// Fmx::Dae::Schema::IXMLProfile_gles_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C32571D7-6D03-4B83-A308-22F1C9D88408}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type*)&__IXMLProfile_gles_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_newparam_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	System::UnicodeString __fastcall Get_Semantic();
	System::UnicodeString __fastcall Get_Modifier();
	bool __fastcall Get_Bool();
	System::UnicodeString __fastcall Get_Bool2();
	System::UnicodeString __fastcall Get_Bool3();
	System::UnicodeString __fastcall Get_Bool4();
	__int64 __fastcall Get_Int();
	System::UnicodeString __fastcall Get_Int2();
	System::UnicodeString __fastcall Get_Int3();
	System::UnicodeString __fastcall Get_Int4();
	double __fastcall Get_Float();
	System::UnicodeString __fastcall Get_Float2();
	System::UnicodeString __fastcall Get_Float3();
	System::UnicodeString __fastcall Get_Float4();
	double __fastcall Get_Float1x1();
	System::UnicodeString __fastcall Get_Float1x2();
	System::UnicodeString __fastcall Get_Float1x3();
	System::UnicodeString __fastcall Get_Float1x4();
	System::UnicodeString __fastcall Get_Float2x1();
	System::UnicodeString __fastcall Get_Float2x2();
	System::UnicodeString __fastcall Get_Float2x3();
	System::UnicodeString __fastcall Get_Float2x4();
	System::UnicodeString __fastcall Get_Float3x1();
	System::UnicodeString __fastcall Get_Float3x2();
	System::UnicodeString __fastcall Get_Float3x3();
	System::UnicodeString __fastcall Get_Float3x4();
	System::UnicodeString __fastcall Get_Float4x1();
	System::UnicodeString __fastcall Get_Float4x2();
	System::UnicodeString __fastcall Get_Float4x3();
	System::UnicodeString __fastcall Get_Float4x4();
	Fmx::Dae::Schema::_di_IXMLGles_sampler_type __fastcall Get_Sampler2D();
	System::UnicodeString __fastcall Get_Enum();
	void __fastcall Set_Sid(System::UnicodeString Value);
	void __fastcall Set_Semantic(System::UnicodeString Value);
	void __fastcall Set_Modifier(System::UnicodeString Value);
	void __fastcall Set_Bool(bool Value);
	void __fastcall Set_Bool2(System::UnicodeString Value);
	void __fastcall Set_Bool3(System::UnicodeString Value);
	void __fastcall Set_Bool4(System::UnicodeString Value);
	void __fastcall Set_Int(__int64 Value);
	void __fastcall Set_Int2(System::UnicodeString Value);
	void __fastcall Set_Int3(System::UnicodeString Value);
	void __fastcall Set_Int4(System::UnicodeString Value);
	void __fastcall Set_Float(double Value);
	void __fastcall Set_Float2(System::UnicodeString Value);
	void __fastcall Set_Float3(System::UnicodeString Value);
	void __fastcall Set_Float4(System::UnicodeString Value);
	void __fastcall Set_Float1x1(double Value);
	void __fastcall Set_Float1x2(System::UnicodeString Value);
	void __fastcall Set_Float1x3(System::UnicodeString Value);
	void __fastcall Set_Float1x4(System::UnicodeString Value);
	void __fastcall Set_Float2x1(System::UnicodeString Value);
	void __fastcall Set_Float2x2(System::UnicodeString Value);
	void __fastcall Set_Float2x3(System::UnicodeString Value);
	void __fastcall Set_Float2x4(System::UnicodeString Value);
	void __fastcall Set_Float3x1(System::UnicodeString Value);
	void __fastcall Set_Float3x2(System::UnicodeString Value);
	void __fastcall Set_Float3x3(System::UnicodeString Value);
	void __fastcall Set_Float3x4(System::UnicodeString Value);
	void __fastcall Set_Float4x1(System::UnicodeString Value);
	void __fastcall Set_Float4x2(System::UnicodeString Value);
	void __fastcall Set_Float4x3(System::UnicodeString Value);
	void __fastcall Set_Float4x4(System::UnicodeString Value);
	void __fastcall Set_Enum(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_newparam_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_newparam_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_newparam_type() { }
	
private:
	void *__IXMLGles_newparam_type;	// Fmx::Dae::Schema::IXMLGles_newparam_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9F7C246F-0D7A-497A-821D-2D9AA168E3EB}
	operator Fmx::Dae::Schema::_di_IXMLGles_newparam_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_newparam_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_newparam_type*(void) { return (Fmx::Dae::Schema::IXMLGles_newparam_type*)&__IXMLGles_newparam_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_newparam_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles_newparam_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles_newparam_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles_newparam_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_newparam_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_newparam_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_newparam_typeList() { }
	
private:
	void *__IXMLGles_newparam_typeList;	// Fmx::Dae::Schema::IXMLGles_newparam_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B4E15F98-8CF2-486D-A624-4A23945AF6E7}
	operator Fmx::Dae::Schema::_di_IXMLGles_newparam_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles_newparam_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_newparam_typeList*(void) { return (Fmx::Dae::Schema::IXMLGles_newparam_typeList*)&__IXMLGles_newparam_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_sampler_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	Fmx::Dae::Schema::_di_IXMLInstance_image_type __fastcall Get_Instance_image();
	Fmx::Dae::Schema::_di_IXMLGles_sampler_type_texcoord __fastcall Get_Texcoord();
	System::UnicodeString __fastcall Get_Wrap_s();
	System::UnicodeString __fastcall Get_Wrap_t();
	System::UnicodeString __fastcall Get_Minfilter();
	System::UnicodeString __fastcall Get_Magfilter();
	System::UnicodeString __fastcall Get_Mipfilter();
	System::Byte __fastcall Get_Mip_max_level();
	float __fastcall Get_Mip_bias();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Wrap_s(System::UnicodeString Value);
	void __fastcall Set_Wrap_t(System::UnicodeString Value);
	void __fastcall Set_Minfilter(System::UnicodeString Value);
	void __fastcall Set_Magfilter(System::UnicodeString Value);
	void __fastcall Set_Mipfilter(System::UnicodeString Value);
	void __fastcall Set_Mip_max_level(System::Byte Value);
	void __fastcall Set_Mip_bias(float Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_sampler_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_sampler_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_sampler_type() { }
	
private:
	void *__IXMLGles_sampler_type;	// Fmx::Dae::Schema::IXMLGles_sampler_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F321AD3C-9BD5-4BC1-91F1-7932647368DB}
	operator Fmx::Dae::Schema::_di_IXMLGles_sampler_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_sampler_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_sampler_type*(void) { return (Fmx::Dae::Schema::IXMLGles_sampler_type*)&__IXMLGles_sampler_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_sampler_type_texcoord : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Semantic();
	void __fastcall Set_Semantic(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_sampler_type_texcoord(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_sampler_type_texcoord(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_sampler_type_texcoord() { }
	
private:
	void *__IXMLGles_sampler_type_texcoord;	// Fmx::Dae::Schema::IXMLGles_sampler_type_texcoord 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4325C6B0-9CA7-4B31-8B00-0A2DDEA9E0B8}
	operator Fmx::Dae::Schema::_di_IXMLGles_sampler_type_texcoord()
	{
		Fmx::Dae::Schema::_di_IXMLGles_sampler_type_texcoord intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_sampler_type_texcoord*(void) { return (Fmx::Dae::Schema::IXMLGles_sampler_type_texcoord*)&__IXMLGles_sampler_type_texcoord; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_technique : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_passList FPass;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_passList __fastcall Get_Pass();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_technique(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_technique(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_technique() { }
	
private:
	void *__IXMLProfile_gles_type_technique;	// Fmx::Dae::Schema::IXMLProfile_gles_type_technique 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FF211325-BDDA-41F1-A1FE-73F5D6DB5430}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_technique*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_technique*)&__IXMLProfile_gles_type_technique; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_techniqueList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_techniqueList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_techniqueList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_techniqueList() { }
	
private:
	void *__IXMLProfile_gles_type_techniqueList;	// Fmx::Dae::Schema::IXMLProfile_gles_type_techniqueList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1822A2B6-BD9F-40F6-B9B4-6AC0624A7F6F}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_techniqueList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_techniqueList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_techniqueList*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_techniqueList*)&__IXMLProfile_gles_type_techniqueList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_technique_pass : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList FAnnotate;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLFx_annotate_typeList __fastcall Get_Annotate();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_states __fastcall Get_States();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_evaluate __fastcall Get_Evaluate();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_technique_pass(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_technique_pass(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_technique_pass() { }
	
private:
	void *__IXMLProfile_gles_type_technique_pass;	// Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {69DC8F82-73FE-4152-9790-634F5ECB562E}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass*)&__IXMLProfile_gles_type_technique_pass; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_technique_passList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_technique_passList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_technique_passList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_technique_passList() { }
	
private:
	void *__IXMLProfile_gles_type_technique_passList;	// Fmx::Dae::Schema::IXMLProfile_gles_type_technique_passList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {18C47783-A687-457E-808C-1486D26ED40B}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_passList()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_passList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_technique_passList*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_technique_passList*)&__IXMLProfile_gles_type_technique_passList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_technique_pass_states : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLAlpha_func __fastcall Get_Alpha_func();
	Fmx::Dae::Schema::_di_IXMLBlend_func __fastcall Get_Blend_func();
	Fmx::Dae::Schema::_di_IXMLClip_plane __fastcall Get_Clip_plane();
	Fmx::Dae::Schema::_di_IXMLColor_mask __fastcall Get_Color_mask();
	Fmx::Dae::Schema::_di_IXMLCull_face __fastcall Get_Cull_face();
	Fmx::Dae::Schema::_di_IXMLDepth_func __fastcall Get_Depth_func();
	Fmx::Dae::Schema::_di_IXMLDepth_mask __fastcall Get_Depth_mask();
	Fmx::Dae::Schema::_di_IXMLDepth_range __fastcall Get_Depth_range();
	Fmx::Dae::Schema::_di_IXMLFog_color __fastcall Get_Fog_color();
	Fmx::Dae::Schema::_di_IXMLFog_density __fastcall Get_Fog_density();
	Fmx::Dae::Schema::_di_IXMLFog_mode __fastcall Get_Fog_mode();
	Fmx::Dae::Schema::_di_IXMLFog_start __fastcall Get_Fog_start();
	Fmx::Dae::Schema::_di_IXMLFog_end __fastcall Get_Fog_end();
	Fmx::Dae::Schema::_di_IXMLFront_face __fastcall Get_Front_face();
	Fmx::Dae::Schema::_di_IXMLLogic_op __fastcall Get_Logic_op();
	Fmx::Dae::Schema::_di_IXMLLight_ambient __fastcall Get_Light_ambient();
	Fmx::Dae::Schema::_di_IXMLLight_diffuse __fastcall Get_Light_diffuse();
	Fmx::Dae::Schema::_di_IXMLLight_specular __fastcall Get_Light_specular();
	Fmx::Dae::Schema::_di_IXMLLight_position __fastcall Get_Light_position();
	Fmx::Dae::Schema::_di_IXMLLight_constant_attenuation __fastcall Get_Light_constant_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_linear_attenuation __fastcall Get_Light_linear_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_quadratic_attenuation __fastcall Get_Light_quadratic_attenuation();
	Fmx::Dae::Schema::_di_IXMLLight_spot_cutoff __fastcall Get_Light_spot_cutoff();
	Fmx::Dae::Schema::_di_IXMLLight_spot_direction __fastcall Get_Light_spot_direction();
	Fmx::Dae::Schema::_di_IXMLLight_spot_exponent __fastcall Get_Light_spot_exponent();
	Fmx::Dae::Schema::_di_IXMLLight_model_ambient __fastcall Get_Light_model_ambient();
	Fmx::Dae::Schema::_di_IXMLLine_width __fastcall Get_Line_width();
	Fmx::Dae::Schema::_di_IXMLMaterial_ambient __fastcall Get_Material_ambient();
	Fmx::Dae::Schema::_di_IXMLMaterial_diffuse __fastcall Get_Material_diffuse();
	Fmx::Dae::Schema::_di_IXMLMaterial_emission __fastcall Get_Material_emission();
	Fmx::Dae::Schema::_di_IXMLMaterial_shininess __fastcall Get_Material_shininess();
	Fmx::Dae::Schema::_di_IXMLMaterial_specular __fastcall Get_Material_specular();
	Fmx::Dae::Schema::_di_IXMLModel_view_matrix __fastcall Get_Model_view_matrix();
	Fmx::Dae::Schema::_di_IXMLPoint_distance_attenuation __fastcall Get_Point_distance_attenuation();
	Fmx::Dae::Schema::_di_IXMLPoint_fade_threshold_size __fastcall Get_Point_fade_threshold_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size __fastcall Get_Point_size();
	Fmx::Dae::Schema::_di_IXMLPoint_size_min __fastcall Get_Point_size_min();
	Fmx::Dae::Schema::_di_IXMLPoint_size_max __fastcall Get_Point_size_max();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset __fastcall Get_Polygon_offset();
	Fmx::Dae::Schema::_di_IXMLProjection_matrix __fastcall Get_Projection_matrix();
	Fmx::Dae::Schema::_di_IXMLScissor __fastcall Get_Scissor();
	Fmx::Dae::Schema::_di_IXMLShade_model __fastcall Get_Shade_model();
	Fmx::Dae::Schema::_di_IXMLStencil_func __fastcall Get_Stencil_func();
	Fmx::Dae::Schema::_di_IXMLStencil_mask __fastcall Get_Stencil_mask();
	Fmx::Dae::Schema::_di_IXMLStencil_op __fastcall Get_Stencil_op();
	Fmx::Dae::Schema::_di_IXMLTexture_pipeline __fastcall Get_Texture_pipeline();
	Fmx::Dae::Schema::_di_IXMLAlpha_test_enable __fastcall Get_Alpha_test_enable();
	Fmx::Dae::Schema::_di_IXMLBlend_enable __fastcall Get_Blend_enable();
	Fmx::Dae::Schema::_di_IXMLClip_plane_enable __fastcall Get_Clip_plane_enable();
	Fmx::Dae::Schema::_di_IXMLColor_logic_op_enable __fastcall Get_Color_logic_op_enable();
	Fmx::Dae::Schema::_di_IXMLColor_material_enable __fastcall Get_Color_material_enable();
	Fmx::Dae::Schema::_di_IXMLCull_face_enable __fastcall Get_Cull_face_enable();
	Fmx::Dae::Schema::_di_IXMLDepth_test_enable __fastcall Get_Depth_test_enable();
	Fmx::Dae::Schema::_di_IXMLDither_enable __fastcall Get_Dither_enable();
	Fmx::Dae::Schema::_di_IXMLFog_enable __fastcall Get_Fog_enable();
	Fmx::Dae::Schema::_di_IXMLLight_enable __fastcall Get_Light_enable();
	Fmx::Dae::Schema::_di_IXMLLighting_enable __fastcall Get_Lighting_enable();
	Fmx::Dae::Schema::_di_IXMLLight_model_two_side_enable __fastcall Get_Light_model_two_side_enable();
	Fmx::Dae::Schema::_di_IXMLLine_smooth_enable __fastcall Get_Line_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLMultisample_enable __fastcall Get_Multisample_enable();
	Fmx::Dae::Schema::_di_IXMLNormalize_enable __fastcall Get_Normalize_enable();
	Fmx::Dae::Schema::_di_IXMLPoint_smooth_enable __fastcall Get_Point_smooth_enable();
	Fmx::Dae::Schema::_di_IXMLPolygon_offset_fill_enable __fastcall Get_Polygon_offset_fill_enable();
	Fmx::Dae::Schema::_di_IXMLRescale_normal_enable __fastcall Get_Rescale_normal_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_coverage_enable __fastcall Get_Sample_alpha_to_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLSample_alpha_to_one_enable __fastcall Get_Sample_alpha_to_one_enable();
	Fmx::Dae::Schema::_di_IXMLSample_coverage_enable __fastcall Get_Sample_coverage_enable();
	Fmx::Dae::Schema::_di_IXMLScissor_test_enable __fastcall Get_Scissor_test_enable();
	Fmx::Dae::Schema::_di_IXMLStencil_test_enable __fastcall Get_Stencil_test_enable();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_technique_pass_states(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_technique_pass_states(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_technique_pass_states() { }
	
private:
	void *__IXMLProfile_gles_type_technique_pass_states;	// Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_states 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0A7CA7F3-21C2-449A-95B7-1003DB15FE10}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_states()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_states intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_states*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_states*)&__IXMLProfile_gles_type_technique_pass_states; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLTexture_pipeline : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles_texture_pipeline_type __fastcall Get_Value();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLTexture_pipeline(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLTexture_pipeline(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLTexture_pipeline() { }
	
private:
	void *__IXMLTexture_pipeline;	// Fmx::Dae::Schema::IXMLTexture_pipeline 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {08099160-26F3-4E1D-996D-0081D8C4A1E8}
	operator Fmx::Dae::Schema::_di_IXMLTexture_pipeline()
	{
		Fmx::Dae::Schema::_di_IXMLTexture_pipeline intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLTexture_pipeline*(void) { return (Fmx::Dae::Schema::IXMLTexture_pipeline*)&__IXMLTexture_pipeline; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texture_pipeline_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_typeList FTexcombiner;
	Fmx::Dae::Schema::_di_IXMLGles_texenv_command_typeList FTexenv;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_typeList __fastcall Get_Texcombiner();
	Fmx::Dae::Schema::_di_IXMLGles_texenv_command_typeList __fastcall Get_Texenv();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texture_pipeline_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texture_pipeline_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texture_pipeline_type() { }
	
private:
	void *__IXMLGles_texture_pipeline_type;	// Fmx::Dae::Schema::IXMLGles_texture_pipeline_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3A51F91F-E089-4C66-B12C-C68FBCE62924}
	operator Fmx::Dae::Schema::_di_IXMLGles_texture_pipeline_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texture_pipeline_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texture_pipeline_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texture_pipeline_type*)&__IXMLGles_texture_pipeline_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_command_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles_texture_constant_type __fastcall Get_Constant();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_rgb_type __fastcall Get_RGB();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_alpha_type __fastcall Get_Alpha();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_command_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_command_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_command_type() { }
	
private:
	void *__IXMLGles_texcombiner_command_type;	// Fmx::Dae::Schema::IXMLGles_texcombiner_command_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79416F43-9AA9-46A1-8B9D-D74661CE071C}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_command_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_command_type*)&__IXMLGles_texcombiner_command_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_command_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_command_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_command_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_command_typeList() { }
	
private:
	void *__IXMLGles_texcombiner_command_typeList;	// Fmx::Dae::Schema::IXMLGles_texcombiner_command_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E2C998D7-2C42-4E41-B881-04F8A3915AA6}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_command_typeList*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_command_typeList*)&__IXMLGles_texcombiner_command_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texture_constant_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Value();
	System::UnicodeString __fastcall Get_Param();
	void __fastcall Set_Value(System::UnicodeString Value);
	void __fastcall Set_Param(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texture_constant_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texture_constant_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texture_constant_type() { }
	
private:
	void *__IXMLGles_texture_constant_type;	// Fmx::Dae::Schema::IXMLGles_texture_constant_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {975A18BC-10D2-4588-AAA3-6AFA3F0ACF6A}
	operator Fmx::Dae::Schema::_di_IXMLGles_texture_constant_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texture_constant_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texture_constant_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texture_constant_type*)&__IXMLGles_texture_constant_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_command_rgb_type : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	System::UnicodeString __fastcall Get_Operator_();
	float __fastcall Get_Scale();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_rgb_type __fastcall Get_Argument(int Index);
	void __fastcall Set_Operator_(System::UnicodeString Value);
	void __fastcall Set_Scale(float Value);
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_rgb_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_rgb_type __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_command_rgb_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_command_rgb_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_command_rgb_type() { }
	
private:
	void *__IXMLGles_texcombiner_command_rgb_type;	// Fmx::Dae::Schema::IXMLGles_texcombiner_command_rgb_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0BFCFC20-E47B-42A9-9174-C8860E132D58}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_rgb_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_rgb_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_command_rgb_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_command_rgb_type*)&__IXMLGles_texcombiner_command_rgb_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_argument_rgb_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Source();
	System::UnicodeString __fastcall Get_Operand();
	System::UnicodeString __fastcall Get_Sampler();
	void __fastcall Set_Source(System::UnicodeString Value);
	void __fastcall Set_Operand(System::UnicodeString Value);
	void __fastcall Set_Sampler(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_argument_rgb_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_argument_rgb_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_argument_rgb_type() { }
	
private:
	void *__IXMLGles_texcombiner_argument_rgb_type;	// Fmx::Dae::Schema::IXMLGles_texcombiner_argument_rgb_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ED7800A7-9A3F-4282-AAAE-1E4FDDE73A4C}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_rgb_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_rgb_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_argument_rgb_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_argument_rgb_type*)&__IXMLGles_texcombiner_argument_rgb_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_command_alpha_type : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	System::UnicodeString __fastcall Get_Operator_();
	float __fastcall Get_Scale();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_alpha_type __fastcall Get_Argument(int Index);
	void __fastcall Set_Operator_(System::UnicodeString Value);
	void __fastcall Set_Scale(float Value);
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_alpha_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_alpha_type __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_command_alpha_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_command_alpha_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_command_alpha_type() { }
	
private:
	void *__IXMLGles_texcombiner_command_alpha_type;	// Fmx::Dae::Schema::IXMLGles_texcombiner_command_alpha_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C1D4C2AF-B501-4148-80A1-8DFF326616C9}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_alpha_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_command_alpha_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_command_alpha_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_command_alpha_type*)&__IXMLGles_texcombiner_command_alpha_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texcombiner_argument_alpha_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Source();
	System::UnicodeString __fastcall Get_Operand();
	System::UnicodeString __fastcall Get_Sampler();
	void __fastcall Set_Source(System::UnicodeString Value);
	void __fastcall Set_Operand(System::UnicodeString Value);
	void __fastcall Set_Sampler(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texcombiner_argument_alpha_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texcombiner_argument_alpha_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texcombiner_argument_alpha_type() { }
	
private:
	void *__IXMLGles_texcombiner_argument_alpha_type;	// Fmx::Dae::Schema::IXMLGles_texcombiner_argument_alpha_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DCFBE34C-6143-4FA1-BD81-B08166353F54}
	operator Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_alpha_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texcombiner_argument_alpha_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texcombiner_argument_alpha_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texcombiner_argument_alpha_type*)&__IXMLGles_texcombiner_argument_alpha_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texenv_command_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Operator_();
	System::UnicodeString __fastcall Get_Sampler();
	Fmx::Dae::Schema::_di_IXMLGles_texture_constant_type __fastcall Get_Constant();
	void __fastcall Set_Operator_(System::UnicodeString Value);
	void __fastcall Set_Sampler(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texenv_command_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texenv_command_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texenv_command_type() { }
	
private:
	void *__IXMLGles_texenv_command_type;	// Fmx::Dae::Schema::IXMLGles_texenv_command_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E83C2ECA-AFEB-42F0-B932-D802E9D64CAB}
	operator Fmx::Dae::Schema::_di_IXMLGles_texenv_command_type()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texenv_command_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texenv_command_type*(void) { return (Fmx::Dae::Schema::IXMLGles_texenv_command_type*)&__IXMLGles_texenv_command_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLGles_texenv_command_typeList : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLGles_texenv_command_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLGles_texenv_command_type __fastcall Insert(const int Index);
	Fmx::Dae::Schema::_di_IXMLGles_texenv_command_type __fastcall Get_Item(int Index);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLGles_texenv_command_typeList(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLGles_texenv_command_typeList(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLGles_texenv_command_typeList() { }
	
private:
	void *__IXMLGles_texenv_command_typeList;	// Fmx::Dae::Schema::IXMLGles_texenv_command_typeList 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ABA87D0A-FE26-47B2-99A2-BE93D5CEB9C6}
	operator Fmx::Dae::Schema::_di_IXMLGles_texenv_command_typeList()
	{
		Fmx::Dae::Schema::_di_IXMLGles_texenv_command_typeList intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLGles_texenv_command_typeList*(void) { return (Fmx::Dae::Schema::IXMLGles_texenv_command_typeList*)&__IXMLGles_texenv_command_typeList; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_gles_type_technique_pass_evaluate : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList FColor_target;
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList FDepth_target;
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList FStencil_target;
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList FColor_clear;
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList FDepth_clear;
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList FStencil_clear;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_colortarget_typeList __fastcall Get_Color_target();
	Fmx::Dae::Schema::_di_IXMLFx_depthtarget_typeList __fastcall Get_Depth_target();
	Fmx::Dae::Schema::_di_IXMLFx_stenciltarget_typeList __fastcall Get_Stencil_target();
	Fmx::Dae::Schema::_di_IXMLFx_clearcolor_typeList __fastcall Get_Color_clear();
	Fmx::Dae::Schema::_di_IXMLFx_cleardepth_typeList __fastcall Get_Depth_clear();
	Fmx::Dae::Schema::_di_IXMLFx_clearstencil_typeList __fastcall Get_Stencil_clear();
	System::UnicodeString __fastcall Get_Draw();
	void __fastcall Set_Draw(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_gles_type_technique_pass_evaluate(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_gles_type_technique_pass_evaluate(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_gles_type_technique_pass_evaluate() { }
	
private:
	void *__IXMLProfile_gles_type_technique_pass_evaluate;	// Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_evaluate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {6966DD0E-0953-4812-A4ED-CFE36C6A5D66}
	operator Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_evaluate()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_gles_type_technique_pass_evaluate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_evaluate*(void) { return (Fmx::Dae::Schema::IXMLProfile_gles_type_technique_pass_evaluate*)&__IXMLProfile_gles_type_technique_pass_evaluate; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLFx_common_newparam_typeList FNewparam;
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLFx_common_newparam_typeList __fastcall Get_Newparam();
	Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique __fastcall Get_Technique();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type() { }
	
private:
	void *__IXMLProfile_common_type;	// Fmx::Dae::Schema::IXMLProfile_common_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2242424B-7AAA-4778-B3A6-02239BEB2D99}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type*)&__IXMLProfile_common_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_bridge_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Platform();
	System::UnicodeString __fastcall Get_Url();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Platform(System::UnicodeString Value);
	void __fastcall Set_Url(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_bridge_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_bridge_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_bridge_type() { }
	
private:
	void *__IXMLProfile_bridge_type;	// Fmx::Dae::Schema::IXMLProfile_bridge_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DBE604A7-74EA-4337-B791-D42631E8DEF7}
	operator Fmx::Dae::Schema::_di_IXMLProfile_bridge_type()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_bridge_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_bridge_type*(void) { return (Fmx::Dae::Schema::IXMLProfile_bridge_type*)&__IXMLProfile_bridge_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type_technique : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
private:
	Fmx::Dae::Schema::_di_IXMLExtra_typeList FExtra;
	
protected:
	System::UnicodeString __fastcall Get_Id();
	System::UnicodeString __fastcall Get_Sid();
	Fmx::Dae::Schema::_di_IXMLAsset_type __fastcall Get_Asset();
	Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_constant __fastcall Get_Constant();
	Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_lambert __fastcall Get_Lambert();
	Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_phong __fastcall Get_Phong();
	Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_blinn __fastcall Get_Blinn();
	Fmx::Dae::Schema::_di_IXMLExtra_typeList __fastcall Get_Extra();
	void __fastcall Set_Id(System::UnicodeString Value);
	void __fastcall Set_Sid(System::UnicodeString Value);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type_technique(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type_technique(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type_technique() { }
	
private:
	void *__IXMLProfile_common_type_technique;	// Fmx::Dae::Schema::IXMLProfile_common_type_technique 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4FA1C85F-A117-466E-8250-BBB7F035F13A}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type_technique*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type_technique*)&__IXMLProfile_common_type_technique; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type_technique_constant : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Emission();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Reflective();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Reflectivity();
	Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type __fastcall Get_Transparent();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Transparency();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Index_of_refraction();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type_technique_constant(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type_technique_constant(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type_technique_constant() { }
	
private:
	void *__IXMLProfile_common_type_technique_constant;	// Fmx::Dae::Schema::IXMLProfile_common_type_technique_constant 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8F522F83-08C5-47F7-9C78-ADA3EF3EB275}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_constant()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_constant intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type_technique_constant*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type_technique_constant*)&__IXMLProfile_common_type_technique_constant; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_color_or_texture_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_color __fastcall Get_Color();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_param __fastcall Get_Param();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_texture __fastcall Get_Texture();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_color_or_texture_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_color_or_texture_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_color_or_texture_type() { }
	
private:
	void *__IXMLFx_common_color_or_texture_type;	// Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C40FE403-00E5-406B-A382-D967FADB3DAD}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type*(void) { return (Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type*)&__IXMLFx_common_color_or_texture_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_color_or_texture_type_color : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	void __fastcall Set_Sid(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_color_or_texture_type_color(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_color_or_texture_type_color(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_color_or_texture_type_color() { }
	
private:
	void *__IXMLFx_common_color_or_texture_type_color;	// Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_color 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9554CB96-FC8D-4224-9621-A446E050E8AE}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_color()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_color intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_color*(void) { return (Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_color*)&__IXMLFx_common_color_or_texture_type_color; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_color_or_texture_type_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_color_or_texture_type_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_color_or_texture_type_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_color_or_texture_type_param() { }
	
private:
	void *__IXMLFx_common_color_or_texture_type_param;	// Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {333C946F-AC6B-46BA-B27E-B6AE93CFC5BA}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_param()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_param*(void) { return (Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_param*)&__IXMLFx_common_color_or_texture_type_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_color_or_texture_type_texture : public Xml::Xmldoc::TXMLNodeCollection
{
	typedef Xml::Xmldoc::TXMLNodeCollection inherited;
	
protected:
	System::UnicodeString __fastcall Get_Texture();
	System::UnicodeString __fastcall Get_Texcoord();
	Fmx::Dae::Schema::_di_IXMLExtra_type __fastcall Get_Extra(int Index);
	void __fastcall Set_Texture(System::UnicodeString Value);
	void __fastcall Set_Texcoord(System::UnicodeString Value);
	Fmx::Dae::Schema::_di_IXMLExtra_type __fastcall Add();
	Fmx::Dae::Schema::_di_IXMLExtra_type __fastcall Insert(const int Index);
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_color_or_texture_type_texture(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNodeCollection(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_color_or_texture_type_texture(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNodeCollection(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_color_or_texture_type_texture() { }
	
private:
	void *__IXMLFx_common_color_or_texture_type_texture;	// Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_texture 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DB13C7F4-37C9-46D9-866D-5CC72BA6DE3B}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_texture()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type_texture intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_texture*(void) { return (Fmx::Dae::Schema::IXMLFx_common_color_or_texture_type_texture*)&__IXMLFx_common_color_or_texture_type_texture; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_float_or_param_type : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_float __fastcall Get_Float();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_param __fastcall Get_Param();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_float_or_param_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_float_or_param_type(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_float_or_param_type() { }
	
private:
	void *__IXMLFx_common_float_or_param_type;	// Fmx::Dae::Schema::IXMLFx_common_float_or_param_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {70E2493E-F5F5-4F8E-AEB2-C3B43C2C44B1}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_float_or_param_type*(void) { return (Fmx::Dae::Schema::IXMLFx_common_float_or_param_type*)&__IXMLFx_common_float_or_param_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_float_or_param_type_float : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Sid();
	void __fastcall Set_Sid(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_float_or_param_type_float(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_float_or_param_type_float(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_float_or_param_type_float() { }
	
private:
	void *__IXMLFx_common_float_or_param_type_float;	// Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_float 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ECA688F3-6B14-44B2-BACD-B0183CB3F7DE}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_float()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_float intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_float*(void) { return (Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_float*)&__IXMLFx_common_float_or_param_type_float; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_float_or_param_type_param : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	System::UnicodeString __fastcall Get_Ref();
	void __fastcall Set_Ref(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_float_or_param_type_param(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_float_or_param_type_param(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_float_or_param_type_param() { }
	
private:
	void *__IXMLFx_common_float_or_param_type_param;	// Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_param 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B8CB5106-54FC-4CE3-B8C7-67BBE6DFF9F0}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_param()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type_param intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_param*(void) { return (Fmx::Dae::Schema::IXMLFx_common_float_or_param_type_param*)&__IXMLFx_common_float_or_param_type_param; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLFx_common_transparent_type : public TXMLFx_common_color_or_texture_type
{
	typedef TXMLFx_common_color_or_texture_type inherited;
	
protected:
	System::UnicodeString __fastcall Get_Opaque();
	void __fastcall Set_Opaque(System::UnicodeString Value);
public:
	/* TXMLNode.Create */ inline __fastcall TXMLFx_common_transparent_type(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : TXMLFx_common_color_or_texture_type(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLFx_common_transparent_type(Xml::Xmldoc::TXMLNode* HostNode) : TXMLFx_common_color_or_texture_type(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLFx_common_transparent_type() { }
	
private:
	void *__IXMLFx_common_transparent_type;	// Fmx::Dae::Schema::IXMLFx_common_transparent_type 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B7465527-0308-40AE-BC4D-B77F75B17BB8}
	operator Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type()
	{
		Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLFx_common_transparent_type*(void) { return (Fmx::Dae::Schema::IXMLFx_common_transparent_type*)&__IXMLFx_common_transparent_type; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type_technique_lambert : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Emission();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Ambient();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Diffuse();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Reflective();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Reflectivity();
	Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type __fastcall Get_Transparent();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Transparency();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Index_of_refraction();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type_technique_lambert(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type_technique_lambert(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type_technique_lambert() { }
	
private:
	void *__IXMLProfile_common_type_technique_lambert;	// Fmx::Dae::Schema::IXMLProfile_common_type_technique_lambert 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {9461AE13-6E61-4C35-BD89-52825BFB537A}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_lambert()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_lambert intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type_technique_lambert*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type_technique_lambert*)&__IXMLProfile_common_type_technique_lambert; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type_technique_phong : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Emission();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Ambient();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Diffuse();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Specular();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Shininess();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Reflective();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Reflectivity();
	Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type __fastcall Get_Transparent();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Transparency();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Index_of_refraction();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type_technique_phong(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type_technique_phong(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type_technique_phong() { }
	
private:
	void *__IXMLProfile_common_type_technique_phong;	// Fmx::Dae::Schema::IXMLProfile_common_type_technique_phong 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EEA7018E-B636-4FFF-9F2E-FA291F017023}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_phong()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_phong intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type_technique_phong*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type_technique_phong*)&__IXMLProfile_common_type_technique_phong; }
	#endif
	
};


class PASCALIMPLEMENTATION TXMLProfile_common_type_technique_blinn : public Xml::Xmldoc::TXMLNode
{
	typedef Xml::Xmldoc::TXMLNode inherited;
	
protected:
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Emission();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Ambient();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Diffuse();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Specular();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Shininess();
	Fmx::Dae::Schema::_di_IXMLFx_common_color_or_texture_type __fastcall Get_Reflective();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Reflectivity();
	Fmx::Dae::Schema::_di_IXMLFx_common_transparent_type __fastcall Get_Transparent();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Transparency();
	Fmx::Dae::Schema::_di_IXMLFx_common_float_or_param_type __fastcall Get_Index_of_refraction();
	
public:
	virtual void __fastcall AfterConstruction();
public:
	/* TXMLNode.Create */ inline __fastcall TXMLProfile_common_type_technique_blinn(const Xml::Xmldom::_di_IDOMNode ADOMNode, Xml::Xmldoc::TXMLNode* const AParentNode, Xml::Xmldoc::TXMLDocument* const OwnerDoc) : Xml::Xmldoc::TXMLNode(ADOMNode, AParentNode, OwnerDoc) { }
	/* TXMLNode.CreateHosted */ inline __fastcall TXMLProfile_common_type_technique_blinn(Xml::Xmldoc::TXMLNode* HostNode) : Xml::Xmldoc::TXMLNode(HostNode) { }
	/* TXMLNode.Destroy */ inline __fastcall virtual ~TXMLProfile_common_type_technique_blinn() { }
	
private:
	void *__IXMLProfile_common_type_technique_blinn;	// Fmx::Dae::Schema::IXMLProfile_common_type_technique_blinn 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {32F3AC65-019D-4655-9ADF-30C0CA3B0946}
	operator Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_blinn()
	{
		Fmx::Dae::Schema::_di_IXMLProfile_common_type_technique_blinn intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Dae::Schema::IXMLProfile_common_type_technique_blinn*(void) { return (Fmx::Dae::Schema::IXMLProfile_common_type_technique_blinn*)&__IXMLProfile_common_type_technique_blinn; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Gles */
}	/* namespace Schema */
}	/* namespace Dae */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_SCHEMA_GLES)
using namespace Fmx::Dae::Schema::Gles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE_SCHEMA)
using namespace Fmx::Dae::Schema;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_DAE)
using namespace Fmx::Dae;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Dae_Schema_GlesHPP
