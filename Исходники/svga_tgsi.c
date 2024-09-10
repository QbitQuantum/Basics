static boolean svga_shader_expand( struct svga_shader_emitter *emit )
{
   char *new_buf;
   unsigned newsize = emit->size * 2;

   if(emit->buf != err_buf)
      new_buf = REALLOC(emit->buf, emit->size, newsize);
   else
      new_buf = NULL;

   if (new_buf == NULL) {
      emit->ptr = err_buf;
      emit->buf = err_buf;
      emit->size = sizeof(err_buf);
      return FALSE;
   }

   emit->size = newsize;
   emit->ptr = new_buf + (emit->ptr - emit->buf);
   emit->buf = new_buf;
   return TRUE;
}   