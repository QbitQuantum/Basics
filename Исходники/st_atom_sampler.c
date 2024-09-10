static void
convert_sampler(struct st_context *st,
                struct pipe_sampler_state *sampler,
                GLuint texUnit)
{
   struct gl_texture_object *texobj;
   struct gl_context *ctx = st->ctx;
   struct gl_sampler_object *msamp;

   texobj = ctx->Texture.Unit[texUnit]._Current;
   if (!texobj) {
      texobj = _mesa_get_fallback_texture(ctx, TEXTURE_2D_INDEX);
   }

   msamp = _mesa_get_samplerobj(ctx, texUnit);

   memset(sampler, 0, sizeof(*sampler));
   sampler->wrap_s = gl_wrap_xlate(msamp->WrapS);
   sampler->wrap_t = gl_wrap_xlate(msamp->WrapT);
   sampler->wrap_r = gl_wrap_xlate(msamp->WrapR);

   sampler->min_img_filter = gl_filter_to_img_filter(msamp->MinFilter);
   sampler->min_mip_filter = gl_filter_to_mip_filter(msamp->MinFilter);
   sampler->mag_img_filter = gl_filter_to_img_filter(msamp->MagFilter);

   if (texobj->Target != GL_TEXTURE_RECTANGLE_ARB)
      sampler->normalized_coords = 1;

   sampler->lod_bias = ctx->Texture.Unit[texUnit].LodBias + msamp->LodBias;

   sampler->min_lod = CLAMP(msamp->MinLod,
                            0.0f,
                            (GLfloat) texobj->MaxLevel - texobj->BaseLevel);
   sampler->max_lod = MIN2((GLfloat) texobj->MaxLevel - texobj->BaseLevel,
                           msamp->MaxLod);
   if (sampler->max_lod < sampler->min_lod) {
      /* The GL spec doesn't seem to specify what to do in this case.
       * Swap the values.
       */
      float tmp = sampler->max_lod;
      sampler->max_lod = sampler->min_lod;
      sampler->min_lod = tmp;
      assert(sampler->min_lod <= sampler->max_lod);
   }

   if (msamp->BorderColor.ui[0] ||
       msamp->BorderColor.ui[1] ||
       msamp->BorderColor.ui[2] ||
       msamp->BorderColor.ui[3]) {
      struct gl_texture_image *teximg;

      teximg = texobj->Image[0][texobj->BaseLevel];

      st_translate_color(msamp->BorderColor.f,
                         teximg ? teximg->_BaseFormat : GL_RGBA,
                         sampler->border_color.f);
   }

   sampler->max_anisotropy = (msamp->MaxAnisotropy == 1.0 ?
                              0 : (GLuint) msamp->MaxAnisotropy);

   /* only care about ARB_shadow, not SGI shadow */
   if (msamp->CompareMode == GL_COMPARE_R_TO_TEXTURE) {
      sampler->compare_mode = PIPE_TEX_COMPARE_R_TO_TEXTURE;
      sampler->compare_func
         = st_compare_func_to_pipe(msamp->CompareFunc);
   }

   sampler->seamless_cube_map =
      ctx->Texture.CubeMapSeamless || msamp->CubeMapSeamless;
}