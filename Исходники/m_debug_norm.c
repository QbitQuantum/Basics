static void ref_norm_transform_rescale( const GLmatrix *mat,
					GLfloat scale,
					const GLvector4f *in,
					const GLfloat *lengths,
					GLvector4f *dest )
{
   GLuint i;
   const GLfloat *s = in->start;
   const GLfloat *m = mat->inv;
   GLfloat (*out)[4] = (GLfloat (*)[4]) dest->start;

   (void) lengths;

   for ( i = 0 ; i < in->count ; i++ ) {
      GLfloat t[3];

      TRANSFORM_NORMAL( t, s, m );
      SCALE_SCALAR_3V( out[i], scale, t );

      s = (GLfloat *)((char *)s + in->stride);
   }
}