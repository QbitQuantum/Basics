/**
 * Free all the temporary data in a scene.
 */
void
lp_scene_end_rasterization(struct lp_scene *scene )
{
   int i, j;

   /* Unmap color buffers */
   for (i = 0; i < scene->fb.nr_cbufs; i++) {
      if (scene->cbufs[i].map) {
         struct pipe_surface *cbuf = scene->fb.cbufs[i];
         if (llvmpipe_resource_is_texture(cbuf->texture)) {
            llvmpipe_resource_unmap(cbuf->texture,
                                    cbuf->u.tex.level,
                                    cbuf->u.tex.first_layer);
         }
         scene->cbufs[i].map = NULL;
      }
   }

   /* Unmap z/stencil buffer */
   if (scene->zsbuf.map) {
      struct pipe_surface *zsbuf = scene->fb.zsbuf;
      llvmpipe_resource_unmap(zsbuf->texture,
                              zsbuf->u.tex.level,
                              zsbuf->u.tex.first_layer);
      scene->zsbuf.map = NULL;
   }

   /* Reset all command lists:
    */
   for (i = 0; i < scene->tiles_x; i++) {
      for (j = 0; j < scene->tiles_y; j++) {
         struct cmd_bin *bin = lp_scene_get_bin(scene, i, j);
         bin->head = NULL;
         bin->tail = NULL;
         bin->last_state = NULL;
      }
   }

   /* If there are any bins which weren't cleared by the loop above,
    * they will be caught (on debug builds at least) by this assert:
    */
   assert(lp_scene_is_empty(scene));

   /* Decrement texture ref counts
    */
   {
      struct resource_ref *ref;
      int i, j = 0;

      for (ref = scene->resources; ref; ref = ref->next) {
         for (i = 0; i < ref->count; i++) {
            if (LP_DEBUG & DEBUG_SETUP)
               debug_printf("resource %d: %p %dx%d sz %d\n",
                            j,
                            (void *) ref->resource[i],
                            ref->resource[i]->width0,
                            ref->resource[i]->height0,
                            llvmpipe_resource_size(ref->resource[i]));
            j++;
            pipe_resource_reference(&ref->resource[i], NULL);
         }
      }

      if (LP_DEBUG & DEBUG_SETUP)
         debug_printf("scene %d resources, sz %d\n",
                      j, scene->resource_reference_size);
   }

   /* Free all scene data blocks:
    */
   {
      struct data_block_list *list = &scene->data;
      struct data_block *block, *tmp;

      for (block = list->head->next; block; block = tmp) {
         tmp = block->next;
	 FREE(block);
      }

      list->head->next = NULL;
      list->head->used = 0;
   }

   lp_fence_reference(&scene->fence, NULL);

   scene->resources = NULL;
   scene->scene_size = 0;
   scene->resource_reference_size = 0;

   scene->has_depthstencil_clear = FALSE;
   scene->alloc_failed = FALSE;

   util_unreference_framebuffer_state( &scene->fb );
}