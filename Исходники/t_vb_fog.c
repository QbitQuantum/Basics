static GLboolean
run_fog_stage(struct gl_context *ctx, struct tnl_pipeline_stage *stage)
{
   TNLcontext *tnl = TNL_CONTEXT(ctx);
   struct vertex_buffer *VB = &tnl->vb;
   struct fog_stage_data *store = FOG_STAGE_DATA(stage);
   GLvector4f *input;


   if (!ctx->Fog.Enabled)
      return GL_TRUE;

   if (ctx->Fog.FogCoordinateSource == GL_FRAGMENT_DEPTH_EXT && !ctx->VertexProgram._Current) {
      GLuint i;
      GLfloat *coord;
      /* Fog is computed from vertex or fragment Z values */
      /* source = VB->AttribPtr[_TNL_ATTRIB_POS] or VB->EyePtr coords */
      /* dest = VB->AttribPtr[_TNL_ATTRIB_FOG] = fog stage private storage */
      VB->AttribPtr[_TNL_ATTRIB_FOG] = &store->fogcoord;

      if (!ctx->_NeedEyeCoords) {
         /* compute fog coords from object coords */
	 const GLfloat *m = ctx->ModelviewMatrixStack.Top->m;
	 GLfloat plane[4];

	 /* Use this to store calculated eye z values:
	  */
	 input = &store->fogcoord;

	 plane[0] = m[2];
	 plane[1] = m[6];
	 plane[2] = m[10];
	 plane[3] = m[14];
	 /* Full eye coords weren't required, just calculate the
	  * eye Z values.
	  */
	 _mesa_dotprod_tab[VB->AttribPtr[_TNL_ATTRIB_POS]->size]
	    ( (GLfloat *) input->data,
	      4 * sizeof(GLfloat),
	      VB->AttribPtr[_TNL_ATTRIB_POS], plane );

	 input->count = VB->AttribPtr[_TNL_ATTRIB_POS]->count;

	 /* make sure coords are really positive
	    NOTE should avoid going through array twice */
	 coord = input->start;
	 for (i = 0; i < input->count; i++) {
	    *coord = FABSF(*coord);
	    STRIDE_F(coord, input->stride);
	 }
      }
      else {
         /* fog coordinates = eye Z coordinates - need to copy for ABS */
	 input = &store->fogcoord;

	 if (VB->EyePtr->size < 2)
	    _mesa_vector4f_clean_elem( VB->EyePtr, VB->Count, 2 );

	 input->stride = 4 * sizeof(GLfloat);
	 input->count = VB->EyePtr->count;
	 coord = VB->EyePtr->start;
	 for (i = 0 ; i < VB->EyePtr->count; i++) {
	    input->data[i][0] = FABSF(coord[2]);
	    STRIDE_F(coord, VB->EyePtr->stride);
	 }
      }
   }
   else {
      /* use glFogCoord() coordinates */
      input = VB->AttribPtr[_TNL_ATTRIB_FOG];  /* source data */

      /* input->count may be one if glFogCoord was only called once
       * before glBegin.  But we need to compute fog for all vertices.
       */
      input->count = VB->AttribPtr[_TNL_ATTRIB_POS]->count;

      VB->AttribPtr[_TNL_ATTRIB_FOG] = &store->fogcoord;  /* dest data */
   }

   if (tnl->_DoVertexFog) {
      /* compute blend factors from fog coordinates */
      compute_fog_blend_factors( ctx, VB->AttribPtr[_TNL_ATTRIB_FOG], input );
   }
   else {
      /* results = incoming fog coords (compute fog per-fragment later) */
      VB->AttribPtr[_TNL_ATTRIB_FOG] = input;
   }

   return GL_TRUE;
}