static void
create_vert_shader(struct vl_compositor *c)
{
   const unsigned max_tokens = 50;

   struct pipe_shader_state vs;
   struct tgsi_token *tokens;
   struct tgsi_header *header;

   struct tgsi_full_declaration decl;
   struct tgsi_full_instruction inst;

   unsigned ti;

   unsigned i;

   assert(c);

   tokens = (struct tgsi_token*)MALLOC(max_tokens * sizeof(struct tgsi_token));
   *(struct tgsi_version*)&tokens[0] = tgsi_build_version();
   header = (struct tgsi_header*)&tokens[1];
   *header = tgsi_build_header();
   *(struct tgsi_processor*)&tokens[2] = tgsi_build_processor(TGSI_PROCESSOR_VERTEX, header);

   ti = 3;

   /*
    * decl i0             ; Vertex pos
    * decl i1             ; Vertex texcoords
    */
   for (i = 0; i < 2; i++) {
      decl = vl_decl_input(i == 0 ? TGSI_SEMANTIC_POSITION : TGSI_SEMANTIC_GENERIC, i, i, i);
      ti += tgsi_build_full_declaration(&decl, &tokens[ti], header, max_tokens - ti);
   }

   /*
    * decl c0             ; Scaling vector to scale vertex pos rect to destination size
    * decl c1             ; Translation vector to move vertex pos rect into position
    * decl c2             ; Scaling vector to scale texcoord rect to source size
    * decl c3             ; Translation vector to move texcoord rect into position
    */
   decl = vl_decl_constants(TGSI_SEMANTIC_GENERIC, 0, 0, 3);
   ti += tgsi_build_full_declaration(&decl, &tokens[ti], header, max_tokens - ti);

   /*
    * decl o0             ; Vertex pos
    * decl o1             ; Vertex texcoords
    */
   for (i = 0; i < 2; i++) {
      decl = vl_decl_output(i == 0 ? TGSI_SEMANTIC_POSITION : TGSI_SEMANTIC_GENERIC, i, i, i);
      ti += tgsi_build_full_declaration(&decl, &tokens[ti], header, max_tokens - ti);
   }

   /* decl t0, t1 */
   decl = vl_decl_temps(0, 1);
   ti += tgsi_build_full_declaration(&decl, &tokens[ti], header, max_tokens - ti);

   /*
    * mad o0, i0, c0, c1  ; Scale and translate unit output rect to destination size and pos
    * mad o1, i1, c2, c3  ; Scale and translate unit texcoord rect to source size and pos
    */
   for (i = 0; i < 2; ++i) {
      inst = vl_inst4(TGSI_OPCODE_MAD, TGSI_FILE_OUTPUT, i, TGSI_FILE_INPUT, i, TGSI_FILE_CONSTANT, i * 2, TGSI_FILE_CONSTANT, i * 2 + 1);
      ti += tgsi_build_full_instruction(&inst, &tokens[ti], header, max_tokens - ti);
   }

   /* end */
   inst = vl_end();
   ti += tgsi_build_full_instruction(&inst, &tokens[ti], header, max_tokens - ti);

   assert(ti <= max_tokens);

   vs.tokens = tokens;
   c->vertex_shader = c->pipe->create_vs_state(c->pipe, &vs);
   FREE(tokens);
}