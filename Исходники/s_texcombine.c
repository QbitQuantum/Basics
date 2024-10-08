/**
 * Do texture application for:
 *  GL_EXT_texture_env_combine
 *  GL_ARB_texture_env_combine
 *  GL_EXT_texture_env_dot3
 *  GL_ARB_texture_env_dot3
 *  GL_ATI_texture_env_combine3
 *  GL_NV_texture_env_combine4
 *  conventional GL texture env modes
 *
 * \param ctx          rendering context
 * \param unit         the texture combiner unit
 * \param n            number of fragments to process (span width)
 * \param primary_rgba incoming fragment color array
 * \param texelBuffer  pointer to texel colors for all texture units
 * 
 * \param rgba         incoming/result fragment colors
 */
static void
texture_combine( GLcontext *ctx, GLuint unit, GLuint n,
                 const float4_array primary_rgba,
                 const GLfloat *texelBuffer,
                 GLchan (*rgbaChan)[4] )
{
   SWcontext *swrast = SWRAST_CONTEXT(ctx);
   const struct gl_texture_unit *textureUnit = &(ctx->Texture.Unit[unit]);
   const struct gl_tex_env_combine_state *combine = textureUnit->_CurrentCombine;
   float4_array argRGB[MAX_COMBINER_TERMS];
   float4_array argA[MAX_COMBINER_TERMS];
   const GLfloat scaleRGB = (GLfloat) (1 << combine->ScaleShiftRGB);
   const GLfloat scaleA = (GLfloat) (1 << combine->ScaleShiftA);
   const GLuint numArgsRGB = combine->_NumArgsRGB;
   const GLuint numArgsA = combine->_NumArgsA;
   GLfloat ccolor[MAX_COMBINER_TERMS][MAX_WIDTH][4]; /* temp color buffers */
   GLfloat rgba[MAX_WIDTH][4];
   GLuint i, term;

   for (i = 0; i < n; i++) {
      rgba[i][RCOMP] = CHAN_TO_FLOAT(rgbaChan[i][RCOMP]);
      rgba[i][GCOMP] = CHAN_TO_FLOAT(rgbaChan[i][GCOMP]);
      rgba[i][BCOMP] = CHAN_TO_FLOAT(rgbaChan[i][BCOMP]);
      rgba[i][ACOMP] = CHAN_TO_FLOAT(rgbaChan[i][ACOMP]);
   }

   /*
   printf("modeRGB 0x%x  modeA 0x%x  srcRGB1 0x%x  srcA1 0x%x  srcRGB2 0x%x  srcA2 0x%x\n",
          combine->ModeRGB,
          combine->ModeA,
          combine->SourceRGB[0],
          combine->SourceA[0],
          combine->SourceRGB[1],
          combine->SourceA[1]);
   */

   /*
    * Do operand setup for up to 4 operands.  Loop over the terms.
    */
   for (term = 0; term < numArgsRGB; term++) {
      const GLenum srcRGB = combine->SourceRGB[term];
      const GLenum operandRGB = combine->OperandRGB[term];

      switch (srcRGB) {
         case GL_TEXTURE:
            argRGB[term] = get_texel_array(swrast, unit);
            break;
         case GL_PRIMARY_COLOR:
            argRGB[term] = primary_rgba;
            break;
         case GL_PREVIOUS:
            argRGB[term] = rgba;
            break;
         case GL_CONSTANT:
            {
               float4_array c = ccolor[term];
               GLfloat red   = textureUnit->EnvColor[0];
               GLfloat green = textureUnit->EnvColor[1];
               GLfloat blue  = textureUnit->EnvColor[2];
               GLfloat alpha = textureUnit->EnvColor[3];
               for (i = 0; i < n; i++) {
                  ASSIGN_4V(c[i], red, green, blue, alpha);
               }
               argRGB[term] = ccolor[term];
            }
            break;
	 /* GL_ATI_texture_env_combine3 allows GL_ZERO & GL_ONE as sources.
	  */
	 case GL_ZERO:
            {
               float4_array c = ccolor[term];
               for (i = 0; i < n; i++) {
                  ASSIGN_4V(c[i], 0.0F, 0.0F, 0.0F, 0.0F);
               }
               argRGB[term] = ccolor[term];
            }
            break;
	 case GL_ONE:
            {
               float4_array c = ccolor[term];
               for (i = 0; i < n; i++) {
                  ASSIGN_4V(c[i], 1.0F, 1.0F, 1.0F, 1.0F);
               }
               argRGB[term] = ccolor[term];
            }
            break;
         default:
            /* ARB_texture_env_crossbar source */
            {
               const GLuint srcUnit = srcRGB - GL_TEXTURE0;
               ASSERT(srcUnit < ctx->Const.MaxTextureUnits);
               if (!ctx->Texture.Unit[srcUnit]._ReallyEnabled)
                  return;
               argRGB[term] = get_texel_array(swrast, srcUnit);
            }
      }

      if (operandRGB != GL_SRC_COLOR) {
         float4_array src = argRGB[term];
         float4_array dst = ccolor[term];

         /* point to new arg[term] storage */
         argRGB[term] = ccolor[term];

         switch (operandRGB) {
         case GL_ONE_MINUS_SRC_COLOR:
            for (i = 0; i < n; i++) {
               dst[i][RCOMP] = 1.0F - src[i][RCOMP];
               dst[i][GCOMP] = 1.0F - src[i][GCOMP];
               dst[i][BCOMP] = 1.0F - src[i][BCOMP];
            }
            break;
         case GL_SRC_ALPHA:
            for (i = 0; i < n; i++) {
               dst[i][RCOMP] =
               dst[i][GCOMP] =
               dst[i][BCOMP] = src[i][ACOMP];
            }
            break;
         case GL_ONE_MINUS_SRC_ALPHA:
            for (i = 0; i < n; i++) {
               dst[i][RCOMP] =
               dst[i][GCOMP] =
               dst[i][BCOMP] = 1.0F - src[i][ACOMP];
            }
            break;
         default:
            _mesa_problem(ctx, "Bad operandRGB");
         }
      }
   }

   /*
    * Set up the argA[term] pointers
    */
   for (term = 0; term < numArgsA; term++) {
      const GLenum srcA = combine->SourceA[term];
      const GLenum operandA = combine->OperandA[term];

      switch (srcA) {
         case GL_TEXTURE:
            argA[term] = get_texel_array(swrast, unit);
            break;
         case GL_PRIMARY_COLOR:
            argA[term] = primary_rgba;
            break;
         case GL_PREVIOUS:
            argA[term] = rgba;
            break;
         case GL_CONSTANT:
            {
               float4_array c = ccolor[term];
               GLfloat alpha = textureUnit->EnvColor[3];
               for (i = 0; i < n; i++)
                  c[i][ACOMP] = alpha;
               argA[term] = ccolor[term];
            }
            break;
	 /* GL_ATI_texture_env_combine3 allows GL_ZERO & GL_ONE as sources.
	  */
	 case GL_ZERO:
            {
               float4_array c = ccolor[term];
               for (i = 0; i < n; i++)
                  c[i][ACOMP] = 0.0F;
               argA[term] = ccolor[term];
            }
            break;
	 case GL_ONE:
            {
               float4_array c = ccolor[term];
               for (i = 0; i < n; i++)
                  c[i][ACOMP] = 1.0F;
               argA[term] = ccolor[term];
            }
            break;
         default:
            /* ARB_texture_env_crossbar source */
            {
               const GLuint srcUnit = srcA - GL_TEXTURE0;
               ASSERT(srcUnit < ctx->Const.MaxTextureUnits);
               if (!ctx->Texture.Unit[srcUnit]._ReallyEnabled)
                  return;
               argA[term] = get_texel_array(swrast, srcUnit);
            }
      }

      if (operandA == GL_ONE_MINUS_SRC_ALPHA) {
         float4_array src = argA[term];
         float4_array dst = ccolor[term];
         argA[term] = ccolor[term];
         for (i = 0; i < n; i++) {
            dst[i][ACOMP] = 1.0F - src[i][ACOMP];
         }
      }
   }

   /* RGB channel combine */
   {
      float4_array arg0 = argRGB[0];
      float4_array arg1 = argRGB[1];
      float4_array arg2 = argRGB[2];
      float4_array arg3 = argRGB[3];

      switch (combine->ModeRGB) {
      case GL_REPLACE:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = arg0[i][RCOMP] * scaleRGB;
            rgba[i][GCOMP] = arg0[i][GCOMP] * scaleRGB;
            rgba[i][BCOMP] = arg0[i][BCOMP] * scaleRGB;
         }
         break;
      case GL_MODULATE:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = arg0[i][RCOMP] * arg1[i][RCOMP] * scaleRGB;
            rgba[i][GCOMP] = arg0[i][GCOMP] * arg1[i][GCOMP] * scaleRGB;
            rgba[i][BCOMP] = arg0[i][BCOMP] * arg1[i][BCOMP] * scaleRGB;
         }
         break;
      case GL_ADD:
         if (textureUnit->EnvMode == GL_COMBINE4_NV) {
            /* (a * b) + (c * d) */
            for (i = 0; i < n; i++) {
               rgba[i][RCOMP] = (arg0[i][RCOMP] * arg1[i][RCOMP] +
                                 arg2[i][RCOMP] * arg3[i][RCOMP]) * scaleRGB;
               rgba[i][GCOMP] = (arg0[i][GCOMP] * arg1[i][GCOMP] +
                                 arg2[i][GCOMP] * arg3[i][GCOMP]) * scaleRGB;
               rgba[i][BCOMP] = (arg0[i][BCOMP] * arg1[i][BCOMP] +
                                 arg2[i][BCOMP] * arg3[i][BCOMP]) * scaleRGB;
            }
         }
         else {
            /* 2-term addition */
            for (i = 0; i < n; i++) {
               rgba[i][RCOMP] = (arg0[i][RCOMP] + arg1[i][RCOMP]) * scaleRGB;
               rgba[i][GCOMP] = (arg0[i][GCOMP] + arg1[i][GCOMP]) * scaleRGB;
               rgba[i][BCOMP] = (arg0[i][BCOMP] + arg1[i][BCOMP]) * scaleRGB;
            }
         }
         break;
      case GL_ADD_SIGNED:
         if (textureUnit->EnvMode == GL_COMBINE4_NV) {
            /* (a * b) + (c * d) - 0.5 */
            for (i = 0; i < n; i++) {
               rgba[i][RCOMP] = (arg0[i][RCOMP] * arg1[i][RCOMP] +
                                 arg2[i][RCOMP] * arg3[i][RCOMP] - 0.5) * scaleRGB;
               rgba[i][GCOMP] = (arg0[i][GCOMP] * arg1[i][GCOMP] +
                                 arg2[i][GCOMP] * arg3[i][GCOMP] - 0.5) * scaleRGB;
               rgba[i][BCOMP] = (arg0[i][BCOMP] * arg1[i][BCOMP] +
                                 arg2[i][BCOMP] * arg3[i][BCOMP] - 0.5) * scaleRGB;
            }
         }
         else {
            for (i = 0; i < n; i++) {
               rgba[i][RCOMP] = (arg0[i][RCOMP] + arg1[i][RCOMP] - 0.5) * scaleRGB;
               rgba[i][GCOMP] = (arg0[i][GCOMP] + arg1[i][GCOMP] - 0.5) * scaleRGB;
               rgba[i][BCOMP] = (arg0[i][BCOMP] + arg1[i][BCOMP] - 0.5) * scaleRGB;
            }
         }
         break;
      case GL_INTERPOLATE:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = (arg0[i][RCOMP] * arg2[i][RCOMP] +
                          arg1[i][RCOMP] * (1.0F - arg2[i][RCOMP])) * scaleRGB;
            rgba[i][GCOMP] = (arg0[i][GCOMP] * arg2[i][GCOMP] +
                          arg1[i][GCOMP] * (1.0F - arg2[i][GCOMP])) * scaleRGB;
            rgba[i][BCOMP] = (arg0[i][BCOMP] * arg2[i][BCOMP] +
                          arg1[i][BCOMP] * (1.0F - arg2[i][BCOMP])) * scaleRGB;
         }
         break;
      case GL_SUBTRACT:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = (arg0[i][RCOMP] - arg1[i][RCOMP]) * scaleRGB;
            rgba[i][GCOMP] = (arg0[i][GCOMP] - arg1[i][GCOMP]) * scaleRGB;
            rgba[i][BCOMP] = (arg0[i][BCOMP] - arg1[i][BCOMP]) * scaleRGB;
         }
         break;
      case GL_DOT3_RGB_EXT:
      case GL_DOT3_RGBA_EXT:
         /* Do not scale the result by 1 2 or 4 */
         for (i = 0; i < n; i++) {
            GLfloat dot = ((arg0[i][RCOMP] - 0.5F) * (arg1[i][RCOMP] - 0.5F) +
                           (arg0[i][GCOMP] - 0.5F) * (arg1[i][GCOMP] - 0.5F) +
                           (arg0[i][BCOMP] - 0.5F) * (arg1[i][BCOMP] - 0.5F))
               * 4.0F;
            dot = CLAMP(dot, 0.0F, 1.0F);
            rgba[i][RCOMP] = rgba[i][GCOMP] = rgba[i][BCOMP] = dot;
         }
         break;
      case GL_DOT3_RGB:
      case GL_DOT3_RGBA:
         /* DO scale the result by 1 2 or 4 */
         for (i = 0; i < n; i++) {
            GLfloat dot = ((arg0[i][RCOMP] - 0.5F) * (arg1[i][RCOMP] - 0.5F) +
                           (arg0[i][GCOMP] - 0.5F) * (arg1[i][GCOMP] - 0.5F) +
                           (arg0[i][BCOMP] - 0.5F) * (arg1[i][BCOMP] - 0.5F))
               * 4.0F * scaleRGB;
            dot = CLAMP(dot, 0.0, 1.0F);
            rgba[i][RCOMP] = rgba[i][GCOMP] = rgba[i][BCOMP] = dot;
         }
         break;
      case GL_MODULATE_ADD_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = ((arg0[i][RCOMP] * arg2[i][RCOMP]) +
                              arg1[i][RCOMP]) * scaleRGB;
            rgba[i][GCOMP] = ((arg0[i][GCOMP] * arg2[i][GCOMP]) +
                              arg1[i][GCOMP]) * scaleRGB;
            rgba[i][BCOMP] = ((arg0[i][BCOMP] * arg2[i][BCOMP]) +
                              arg1[i][BCOMP]) * scaleRGB;
	 }
         break;
      case GL_MODULATE_SIGNED_ADD_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = ((arg0[i][RCOMP] * arg2[i][RCOMP]) +
                              arg1[i][RCOMP] - 0.5) * scaleRGB;
            rgba[i][GCOMP] = ((arg0[i][GCOMP] * arg2[i][GCOMP]) +
                              arg1[i][GCOMP] - 0.5) * scaleRGB;
            rgba[i][BCOMP] = ((arg0[i][BCOMP] * arg2[i][BCOMP]) +
                              arg1[i][BCOMP] - 0.5) * scaleRGB;
	 }
         break;
      case GL_MODULATE_SUBTRACT_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][RCOMP] = ((arg0[i][RCOMP] * arg2[i][RCOMP]) -
                              arg1[i][RCOMP]) * scaleRGB;
            rgba[i][GCOMP] = ((arg0[i][GCOMP] * arg2[i][GCOMP]) -
                              arg1[i][GCOMP]) * scaleRGB;
            rgba[i][BCOMP] = ((arg0[i][BCOMP] * arg2[i][BCOMP]) -
                              arg1[i][BCOMP]) * scaleRGB;
	 }
         break;
      case GL_BUMP_ENVMAP_ATI:
         /* this produces a fixed rgba color, and the coord calc is done elsewhere */
         for (i = 0; i < n; i++) {
            /* rgba result is 0,0,0,1 */
            rgba[i][RCOMP] = 0.0;
            rgba[i][GCOMP] = 0.0;
            rgba[i][BCOMP] = 0.0;
            rgba[i][ACOMP] = 1.0;
	 }
         return; /* no alpha processing */
      default:
         _mesa_problem(ctx, "invalid combine mode");
      }
   }

   /* Alpha channel combine */
   {
      float4_array arg0 = argA[0];
      float4_array arg1 = argA[1];
      float4_array arg2 = argA[2];
      float4_array arg3 = argA[3];

      switch (combine->ModeA) {
      case GL_REPLACE:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = arg0[i][ACOMP] * scaleA;
         }
         break;
      case GL_MODULATE:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = arg0[i][ACOMP] * arg1[i][ACOMP] * scaleA;
         }
         break;
      case GL_ADD:
         if (textureUnit->EnvMode == GL_COMBINE4_NV) {
            /* (a * b) + (c * d) */
            for (i = 0; i < n; i++) {
               rgba[i][ACOMP] = (arg0[i][ACOMP] * arg1[i][ACOMP] +
                                 arg2[i][ACOMP] * arg3[i][ACOMP]) * scaleA;
            }
         }
         else {
            /* two-term add */
            for (i = 0; i < n; i++) {
               rgba[i][ACOMP] = (arg0[i][ACOMP] + arg1[i][ACOMP]) * scaleA;
            }
         }
         break;
      case GL_ADD_SIGNED:
         if (textureUnit->EnvMode == GL_COMBINE4_NV) {
            /* (a * b) + (c * d) - 0.5 */
            for (i = 0; i < n; i++) {
               rgba[i][ACOMP] = (arg0[i][ACOMP] * arg1[i][ACOMP] +
                                 arg2[i][ACOMP] * arg3[i][ACOMP] -
                                 0.5) * scaleA;
            }
         }
         else {
            /* a + b - 0.5 */
            for (i = 0; i < n; i++) {
               rgba[i][ACOMP] = (arg0[i][ACOMP] + arg1[i][ACOMP] - 0.5F) * scaleA;
            }
         }
         break;
      case GL_INTERPOLATE:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = (arg0[i][ACOMP] * arg2[i][ACOMP] +
                              arg1[i][ACOMP] * (1.0F - arg2[i][ACOMP]))
               * scaleA;
         }
         break;
      case GL_SUBTRACT:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = (arg0[i][ACOMP] - arg1[i][ACOMP]) * scaleA;
         }
         break;
      case GL_MODULATE_ADD_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = ((arg0[i][ACOMP] * arg2[i][ACOMP])
                              + arg1[i][ACOMP]) * scaleA;
         }
         break;
      case GL_MODULATE_SIGNED_ADD_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = ((arg0[i][ACOMP] * arg2[i][ACOMP]) +
                              arg1[i][ACOMP] - 0.5F) * scaleA;
         }
         break;
      case GL_MODULATE_SUBTRACT_ATI:
         for (i = 0; i < n; i++) {
            rgba[i][ACOMP] = ((arg0[i][ACOMP] * arg2[i][ACOMP])
                              - arg1[i][ACOMP]) * scaleA;
         }
         break;
      default:
         _mesa_problem(ctx, "invalid combine mode");
      }
   }

   /* Fix the alpha component for GL_DOT3_RGBA_EXT/ARB combining.
    * This is kind of a kludge.  It would have been better if the spec
    * were written such that the GL_COMBINE_ALPHA value could be set to
    * GL_DOT3.
    */
   if (combine->ModeRGB == GL_DOT3_RGBA_EXT ||
       combine->ModeRGB == GL_DOT3_RGBA) {
      for (i = 0; i < n; i++) {
	 rgba[i][ACOMP] = rgba[i][RCOMP];
      }
   }

   for (i = 0; i < n; i++) {
      UNCLAMPED_FLOAT_TO_CHAN(rgbaChan[i][RCOMP], rgba[i][RCOMP]);
      UNCLAMPED_FLOAT_TO_CHAN(rgbaChan[i][GCOMP], rgba[i][GCOMP]);
      UNCLAMPED_FLOAT_TO_CHAN(rgbaChan[i][BCOMP], rgba[i][BCOMP]);
      UNCLAMPED_FLOAT_TO_CHAN(rgbaChan[i][ACOMP], rgba[i][ACOMP]);
   }
}