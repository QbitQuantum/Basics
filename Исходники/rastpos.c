/**
 * glRasterPos transformation.  Typically called via ctx->Driver.RasterPos().
 *
 * \param vObj  vertex position in object space
 */
void
_mesa_RasterPos(struct gl_context *ctx, const GLfloat vObj[4])
{
   if (_mesa_arb_vertex_program_enabled(ctx)) {
      /* XXX implement this */
      _mesa_problem(ctx, "Vertex programs not implemented for glRasterPos");
      return;
   }
   else {
      GLfloat eye[4], clip[4], ndc[3], d;
      GLfloat *norm, eyenorm[3];
      GLfloat *objnorm = ctx->Current.Attrib[VERT_ATTRIB_NORMAL];
      float scale[3], translate[3];

      /* apply modelview matrix:  eye = MV * obj */
      TRANSFORM_POINT( eye, ctx->ModelviewMatrixStack.Top->m, vObj );
      /* apply projection matrix:  clip = Proj * eye */
      TRANSFORM_POINT( clip, ctx->ProjectionMatrixStack.Top->m, eye );

      /* clip to view volume. */
      if (!ctx->Transform.DepthClamp) {
         if (viewclip_point_z(clip) == 0) {
            ctx->Current.RasterPosValid = GL_FALSE;
            return;
         }
      }
      if (!ctx->Transform.RasterPositionUnclipped) {
         if (viewclip_point_xy(clip) == 0) {
            ctx->Current.RasterPosValid = GL_FALSE;
            return;
         }
      }

      /* clip to user clipping planes */
      if (ctx->Transform.ClipPlanesEnabled && !userclip_point(ctx, clip)) {
         ctx->Current.RasterPosValid = GL_FALSE;
         return;
      }

      /* ndc = clip / W */
      d = (clip[3] == 0.0F) ? 1.0F : 1.0F / clip[3];
      ndc[0] = clip[0] * d;
      ndc[1] = clip[1] * d;
      ndc[2] = clip[2] * d;
      /* wincoord = viewport_mapping(ndc) */
      _mesa_get_viewport_xform(ctx, 0, scale, translate);
      ctx->Current.RasterPos[0] = ndc[0] * scale[0] + translate[0];
      ctx->Current.RasterPos[1] = ndc[1] * scale[1] + translate[1];
      ctx->Current.RasterPos[2] = ndc[2] * scale[2] + translate[2];
      ctx->Current.RasterPos[3] = clip[3];

      if (ctx->Transform.DepthClamp) {
	 ctx->Current.RasterPos[3] = CLAMP(ctx->Current.RasterPos[3],
					   ctx->ViewportArray[0].Near,
					   ctx->ViewportArray[0].Far);
      }

      /* compute raster distance */
      if (ctx->Fog.FogCoordinateSource == GL_FOG_COORDINATE_EXT)
         ctx->Current.RasterDistance = ctx->Current.Attrib[VERT_ATTRIB_FOG][0];
      else
         ctx->Current.RasterDistance =
                        sqrtf( eye[0]*eye[0] + eye[1]*eye[1] + eye[2]*eye[2] );

      /* compute transformed normal vector (for lighting or texgen) */
      if (ctx->_NeedEyeCoords) {
         const GLfloat *inv = ctx->ModelviewMatrixStack.Top->inv;
         TRANSFORM_NORMAL( eyenorm, objnorm, inv );
         norm = eyenorm;
      }
      else {
         norm = objnorm;
      }

      /* update raster color */
      if (ctx->Light.Enabled) {
         /* lighting */
         shade_rastpos( ctx, vObj, norm,
                        ctx->Current.RasterColor,
                        ctx->Current.RasterSecondaryColor );
      }
      else {
         /* use current color */
	 COPY_4FV(ctx->Current.RasterColor,
		  ctx->Current.Attrib[VERT_ATTRIB_COLOR0]);
	 COPY_4FV(ctx->Current.RasterSecondaryColor,
		  ctx->Current.Attrib[VERT_ATTRIB_COLOR1]);
      }

      /* texture coords */
      {
         GLuint u;
         for (u = 0; u < ctx->Const.MaxTextureCoordUnits; u++) {
            GLfloat tc[4];
            COPY_4V(tc, ctx->Current.Attrib[VERT_ATTRIB_TEX0 + u]);
            if (ctx->Texture.Unit[u].TexGenEnabled) {
               compute_texgen(ctx, vObj, eye, norm, u, tc);
            }
            TRANSFORM_POINT(ctx->Current.RasterTexCoords[u],
                            ctx->TextureMatrixStack[u].Top->m, tc);
         }
      }

      ctx->Current.RasterPosValid = GL_TRUE;
   }

   if (ctx->RenderMode == GL_SELECT) {
      _mesa_update_hitflag( ctx, ctx->Current.RasterPos[2] );
   }
}