void
_mesa_Lightfv( GLenum light, GLenum pname, const GLfloat *params )
{
   GET_CURRENT_CONTEXT(ctx);
   GLint i = (GLint) (light - GL_LIGHT0);
   struct gl_light *l = &ctx->Light.Light[i];

   if (i < 0 || i >= (GLint) ctx->Const.MaxLights) {
      _mesa_error( ctx, GL_INVALID_ENUM, "glLight" );
      return;
   }

   switch (pname) {
   case GL_AMBIENT:
      if (TEST_EQ_4V(l->Ambient, params))
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      COPY_4V( l->Ambient, params );
      break;
   case GL_DIFFUSE:
      if (TEST_EQ_4V(l->Diffuse, params))
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      COPY_4V( l->Diffuse, params );
      break;
   case GL_SPECULAR:
      if (TEST_EQ_4V(l->Specular, params))
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      COPY_4V( l->Specular, params );
      break;
   case GL_POSITION: {
      GLfloat tmp[4];
      /* transform position by ModelView matrix */
      TRANSFORM_POINT( tmp, ctx->ModelView.m, params );
      if (TEST_EQ_4V(l->EyePosition, tmp))
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      COPY_4V(l->EyePosition, tmp);
      if (l->EyePosition[3] != 0.0F)
	 l->_Flags |= LIGHT_POSITIONAL;
      else
	 l->_Flags &= ~LIGHT_POSITIONAL;
      break;
   }
   case GL_SPOT_DIRECTION: {
      GLfloat tmp[4];
      /* transform direction by inverse modelview */
      if (ctx->ModelView.flags & MAT_DIRTY_INVERSE) {
	 _math_matrix_analyse( &ctx->ModelView );
      }
      TRANSFORM_NORMAL( tmp, params, ctx->ModelView.inv );
      if (TEST_EQ_3V(l->EyeDirection, tmp))
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      COPY_3V(l->EyeDirection, tmp);
      break;
   }
   case GL_SPOT_EXPONENT:
      if (params[0]<0.0 || params[0]>128.0) {
	 _mesa_error( ctx, GL_INVALID_VALUE, "glLight" );
	 return;
      }
      if (l->SpotExponent == params[0])
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      l->SpotExponent = params[0];
      _mesa_invalidate_spot_exp_table( l );
      break;
   case GL_SPOT_CUTOFF:
      if ((params[0]<0.0 || params[0]>90.0) && params[0]!=180.0) {
	 _mesa_error( ctx, GL_INVALID_VALUE, "glLight" );
	 return;
      }
      if (l->SpotCutoff == params[0])
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      l->SpotCutoff = params[0];
      l->_CosCutoff = (GLfloat) cos(params[0]*DEG2RAD);
      if (l->_CosCutoff < 0)
	 l->_CosCutoff = 0;
      if (l->SpotCutoff != 180.0F)
	 l->_Flags |= LIGHT_SPOT;
      else
	 l->_Flags &= ~LIGHT_SPOT;
      break;
   case GL_CONSTANT_ATTENUATION:
      if (params[0]<0.0) {
	 _mesa_error( ctx, GL_INVALID_VALUE, "glLight" );
	 return;
      }
      if (l->ConstantAttenuation == params[0])
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      l->ConstantAttenuation = params[0];
      break;
   case GL_LINEAR_ATTENUATION:
      if (params[0]<0.0) {
	 _mesa_error( ctx, GL_INVALID_VALUE, "glLight" );
	 return;
      }
      if (l->LinearAttenuation == params[0])
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      l->LinearAttenuation = params[0];
      break;
   case GL_QUADRATIC_ATTENUATION:
      if (params[0]<0.0) {
	 _mesa_error( ctx, GL_INVALID_VALUE, "glLight" );
	 return;
      }
      if (l->QuadraticAttenuation == params[0])
	 return;
      FLUSH_VERTICES(ctx, _NEW_LIGHT);
      l->QuadraticAttenuation = params[0];
      break;
   default:
      _mesa_error( ctx, GL_INVALID_ENUM, "glLight" );
      return;
   }

   if (ctx->Driver.Lightfv)
      ctx->Driver.Lightfv( ctx, light, pname, params );
}