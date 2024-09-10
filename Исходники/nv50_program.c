bool
nv50_program_upload_code(struct nv50_context *nv50, struct nv50_program *prog)
{
   struct nouveau_heap *heap;
   int ret;
   uint32_t size = align(prog->code_size, 0x40);
   uint8_t prog_type;

   switch (prog->type) {
   case PIPE_SHADER_VERTEX:   heap = nv50->screen->vp_code_heap; break;
   case PIPE_SHADER_GEOMETRY: heap = nv50->screen->gp_code_heap; break;
   case PIPE_SHADER_FRAGMENT: heap = nv50->screen->fp_code_heap; break;
   case PIPE_SHADER_COMPUTE:  heap = nv50->screen->fp_code_heap; break;
   default:
      assert(!"invalid program type");
      return false;
   }

   ret = nouveau_heap_alloc(heap, size, prog, &prog->mem);
   if (ret) {
      /* Out of space: evict everything to compactify the code segment, hoping
       * the working set is much smaller and drifts slowly. Improve me !
       */
      while (heap->next) {
         struct nv50_program *evict = heap->next->priv;
         if (evict)
            nouveau_heap_free(&evict->mem);
      }
      debug_printf("WARNING: out of code space, evicting all shaders.\n");
      ret = nouveau_heap_alloc(heap, size, prog, &prog->mem);
      if (ret) {
         NOUVEAU_ERR("shader too large (0x%x) to fit in code space ?\n", size);
         return false;
      }
   }

   if (prog->type == PIPE_SHADER_COMPUTE) {
      /* CP code must be uploaded in FP code segment. */
      prog_type = 1;
   } else {
      prog->code_base = prog->mem->start;
      prog_type = prog->type;
   }

   ret = nv50_tls_realloc(nv50->screen, prog->tls_space);
   if (ret < 0) {
      nouveau_heap_free(&prog->mem);
      return false;
   }
   if (ret > 0)
      nv50->state.new_tls_space = true;

   if (prog->fixups)
      nv50_ir_relocate_code(prog->fixups, prog->code, prog->code_base, 0, 0);
   if (prog->interps)
      nv50_ir_change_interp(prog->interps, prog->code,
                            prog->fp.force_persample_interp,
                            false /* flatshade */);

   nv50_sifc_linear_u8(&nv50->base, nv50->screen->code,
                       (prog_type << NV50_CODE_BO_SIZE_LOG2) + prog->code_base,
                       NOUVEAU_BO_VRAM, prog->code_size, prog->code);

   BEGIN_NV04(nv50->base.pushbuf, NV50_3D(CODE_CB_FLUSH), 1);
   PUSH_DATA (nv50->base.pushbuf, 0);

   return true;
}