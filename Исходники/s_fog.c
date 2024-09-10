/**
 * As above, but color index mode.
 */
void
_swrast_fog_ci_span( const GLcontext *ctx, SWspan *span )
{
   const SWcontext *swrast = SWRAST_CONTEXT(ctx);
   const GLuint haveW = (span->interpMask & SPAN_W);
   const GLuint fogIndex = (GLuint) ctx->Fog.Index;
   GLuint *index = span->array->index;

   ASSERT(swrast->_FogEnabled);
   ASSERT(span->arrayMask & SPAN_INDEX);
   ASSERT((span->interpMask | span->arrayMask) & SPAN_FOG);

   /* we need to compute fog blend factors */
   if (swrast->_PreferPixelFog) {
      /* The span's fog values are fog coordinates, now compute blend factors
       * and blend the fragment colors with the fog color.
       */
      switch (ctx->Fog.Mode) {
      case GL_LINEAR:
         {
            const GLfloat fogEnd = ctx->Fog.End;
            const GLfloat fogScale = (ctx->Fog.Start == ctx->Fog.End)
               ? 1.0F : 1.0F / (ctx->Fog.End - ctx->Fog.Start);
            const GLfloat fogStep = span->attrStepX[FRAG_ATTRIB_FOGC][0];
            GLfloat fogCoord = span->attrStart[FRAG_ATTRIB_FOGC][0];
            const GLfloat wStep = haveW ? span->attrStepX[FRAG_ATTRIB_WPOS][3] : 0.0F;
            GLfloat w = haveW ? span->attrStart[FRAG_ATTRIB_WPOS][3] : 1.0F;
            GLuint i;
            for (i = 0; i < span->end; i++) {
               GLfloat f = (fogEnd - fogCoord / w) * fogScale;
               f = CLAMP(f, 0.0F, 1.0F);
               index[i] = (GLuint) ((GLfloat) index[i] + (1.0F - f) * fogIndex);
               fogCoord += fogStep;
               w += wStep;
            }
         }
         break;
      case GL_EXP:
         {
            const GLfloat density = -ctx->Fog.Density;
            const GLfloat fogStep = span->attrStepX[FRAG_ATTRIB_FOGC][0];
            GLfloat fogCoord = span->attrStart[FRAG_ATTRIB_FOGC][0];
            const GLfloat wStep = haveW ? span->attrStepX[FRAG_ATTRIB_WPOS][3] : 0.0F;
            GLfloat w = haveW ? span->attrStart[FRAG_ATTRIB_WPOS][3] : 1.0F;
            GLuint i;
            for (i = 0; i < span->end; i++) {
               GLfloat f = EXPF(density * fogCoord / w);
               f = CLAMP(f, 0.0F, 1.0F);
               index[i] = (GLuint) ((GLfloat) index[i] + (1.0F - f) * fogIndex);
               fogCoord += fogStep;
               w += wStep;
            }
         }
         break;
      case GL_EXP2:
         {
            const GLfloat negDensitySquared = -ctx->Fog.Density * ctx->Fog.Density;
            const GLfloat fogStep = span->attrStepX[FRAG_ATTRIB_FOGC][0];
            GLfloat fogCoord = span->attrStart[FRAG_ATTRIB_FOGC][0];
            const GLfloat wStep = haveW ? span->attrStepX[FRAG_ATTRIB_WPOS][3] : 0.0F;
            GLfloat w = haveW ? span->attrStart[FRAG_ATTRIB_WPOS][3] : 1.0F;
            GLuint i;
            for (i = 0; i < span->end; i++) {
               const GLfloat coord = fogCoord / w;
               GLfloat tmp = negDensitySquared * coord * coord;
               GLfloat f;
#if defined(__alpha__) || defined(__alpha)
               /* XXX this underflow check may be needed for other systems*/
               if (tmp < FLT_MIN_10_EXP)
                  tmp = FLT_MIN_10_EXP;
#endif
               f = EXPF(tmp);
               f = CLAMP(f, 0.0F, 1.0F);
               index[i] = (GLuint) ((GLfloat) index[i] + (1.0F - f) * fogIndex);
               fogCoord += fogStep;
               w += wStep;
            }
         }
         break;
      default:
         _mesa_problem(ctx, "Bad fog mode in _swrast_fog_ci_span");
         return;
      }
   }
   else if (span->arrayMask & SPAN_FOG) {
      /* The span's fog array values are blend factors.
       * They were previously computed per-vertex.
       */
      GLuint i;
      for (i = 0; i < span->end; i++) {
         const GLfloat f = span->array->attribs[FRAG_ATTRIB_FOGC][i][0];
         index[i] = (GLuint) ((GLfloat) index[i] + (1.0F - f) * fogIndex);
      }
   }
   else {
      /* The span's fog start/step values are blend factors.
       * They were previously computed per-vertex.
       */
      const GLfloat fogStep = span->attrStepX[FRAG_ATTRIB_FOGC][0];
      GLfloat fog = span->attrStart[FRAG_ATTRIB_FOGC][0];
      const GLfloat wStep = haveW ? span->attrStepX[FRAG_ATTRIB_WPOS][3] : 0.0F;
      GLfloat w = haveW ? span->attrStart[FRAG_ATTRIB_WPOS][3] : 1.0F;
      GLuint i;
      ASSERT(span->interpMask & SPAN_FOG);
      for (i = 0; i < span->end; i++) {
         const GLfloat f = fog / w;
         index[i] = (GLuint) ((GLfloat) index[i] + (1.0F - f) * fogIndex);
         fog += fogStep;
         w += wStep;
      }
   }
}