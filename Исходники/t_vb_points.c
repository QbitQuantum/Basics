/**
 * Compute point size for each vertex from the vertex eye-space Z
 * coordinate and the point size attenuation factors.
 * Only done when point size attenuation is enabled and vertex program is
 * disabled.
 */
static GLboolean
run_point_stage(struct gl_context *ctx, struct tnl_pipeline_stage *stage)
{
   if (ctx->Point._Attenuated) {
      struct point_stage_data *store = POINT_STAGE_DATA(stage);
      struct vertex_buffer *VB = &TNL_CONTEXT(ctx)->vb;
      const GLfloat *eyeCoord = (GLfloat *) VB->EyePtr->data + 2;
      const GLint eyeCoordStride = VB->EyePtr->stride / sizeof(GLfloat);
      const GLfloat p0 = ctx->Point.Params[0];
      const GLfloat p1 = ctx->Point.Params[1];
      const GLfloat p2 = ctx->Point.Params[2];
      const GLfloat pointSize = ctx->Point.Size;
      GLfloat (*size)[4] = store->PointSize.data;
      GLuint i;

      for (i = 0; i < VB->Count; i++) {
         const GLfloat dist = FABSF(*eyeCoord);
         const GLfloat q = p0 + dist * (p1 + dist * p2);
         const GLfloat atten = (q != 0.0F) ? SQRTF(1.0F / q) : 1.0F;
         size[i][0] = pointSize * atten; /* clamping done in rasterization */
         eyeCoord += eyeCoordStride;
      }

      VB->AttribPtr[_TNL_ATTRIB_POINTSIZE] = &store->PointSize;
   }

   return GL_TRUE;
}