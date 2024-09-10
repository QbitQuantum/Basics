static void
llvm_pipeline_generic( struct draw_pt_middle_end *middle,
                       const struct draw_fetch_info *fetch_info,
                       const struct draw_prim_info *in_prim_info )
{
   struct llvm_middle_end *fpme = (struct llvm_middle_end *)middle;
   struct draw_context *draw = fpme->draw;
   struct draw_geometry_shader *gshader = draw->gs.geometry_shader;
   struct draw_prim_info gs_prim_info;
   struct draw_vertex_info llvm_vert_info;
   struct draw_vertex_info gs_vert_info;
   struct draw_vertex_info *vert_info;
   struct draw_prim_info ia_prim_info;
   struct draw_vertex_info ia_vert_info;
   const struct draw_prim_info *prim_info = in_prim_info;
   boolean free_prim_info = FALSE;
   unsigned opt = fpme->opt;
   unsigned clipped = 0;

   llvm_vert_info.count = fetch_info->count;
   llvm_vert_info.vertex_size = fpme->vertex_size;
   llvm_vert_info.stride = fpme->vertex_size;
   llvm_vert_info.verts =
      (struct vertex_header *)MALLOC(fpme->vertex_size *
                                     align(fetch_info->count,  lp_native_vector_width / 32));
   if (!llvm_vert_info.verts) {
      assert(0);
      return;
   }

   if (draw->collect_statistics) {
      draw->statistics.ia_vertices += fetch_info->count;
      draw->statistics.ia_primitives +=
         u_decomposed_prims_for_vertices(prim_info->prim, prim_info->count);
      draw->statistics.vs_invocations += fetch_info->count;
   }

   if (fetch_info->linear)
      clipped = fpme->current_variant->jit_func( &fpme->llvm->jit_context,
                                       llvm_vert_info.verts,
                                       (const char **)draw->pt.user.vbuffer,
                                       fetch_info->start,
                                       fetch_info->count,
                                       fpme->vertex_size,
                                       draw->pt.vertex_buffer,
                                       draw->instance_id);
   else
      clipped = fpme->current_variant->jit_func_elts( &fpme->llvm->jit_context,
                                            llvm_vert_info.verts,
                                            (const char **)draw->pt.user.vbuffer,
                                            fetch_info->elts,
                                            fetch_info->count,
                                            fpme->vertex_size,
                                            draw->pt.vertex_buffer,
                                            draw->instance_id);

   /* Finished with fetch and vs:
    */
   fetch_info = NULL;
   vert_info = &llvm_vert_info;


   if ((opt & PT_SHADE) && gshader) {
      struct draw_vertex_shader *vshader = draw->vs.vertex_shader;
      draw_geometry_shader_run(gshader,
                               draw->pt.user.gs_constants,
                               draw->pt.user.gs_constants_size,
                               vert_info,
                               prim_info,
                               &vshader->info,
                               &gs_vert_info,
                               &gs_prim_info);

      FREE(vert_info->verts);
      vert_info = &gs_vert_info;
      prim_info = &gs_prim_info;
   } else {
      if (draw_prim_assembler_is_required(draw, prim_info, vert_info)) {
         draw_prim_assembler_run(draw, prim_info, vert_info,
                                 &ia_prim_info, &ia_vert_info);

         if (ia_vert_info.count) {
            FREE(vert_info->verts);
            vert_info = &ia_vert_info;
            prim_info = &ia_prim_info;
            free_prim_info = TRUE;
         }
      }
   }

   /* stream output needs to be done before clipping */
   draw_pt_so_emit( fpme->so_emit, vert_info, prim_info );

   /*
    * if there's no position, need to stop now, or the latter stages
    * will try to access non-existent position output.
    */
   if (draw_current_shader_position_output(draw) != -1) {
      if ((opt & PT_SHADE) && gshader) {
         clipped = draw_pt_post_vs_run( fpme->post_vs, vert_info );
      }
      if (clipped) {
         opt |= PT_PIPELINE;
      }

      /* Do we need to run the pipeline? Now will come here if clipped
       */
      if (opt & PT_PIPELINE) {
         pipeline( fpme, vert_info, prim_info );
      }
      else {
         emit( fpme->emit, vert_info, prim_info );
      }
   }
   FREE(vert_info->verts);
   if (free_prim_info) {
      FREE(prim_info->primitive_lengths);
   }
}