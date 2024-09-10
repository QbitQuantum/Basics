/** The init function of the MLAA filter. */
static bool
pp_jimenezmlaa_init_run(struct pp_queue_t *ppq, unsigned int n,
                        unsigned int val, bool iscolor)
{

   struct pipe_box box;
   struct pipe_resource res;
   char *tmp_text = NULL;

   tmp_text = CALLOC(sizeof(blend2fs_1) + sizeof(blend2fs_2) +
                     IMM_SPACE, sizeof(char));

   if (!tmp_text) {
      pp_debug("Failed to allocate shader space\n");
      return FALSE;
   }

   ppq->constbuf = pipe_buffer_create(ppq->p->screen,
                                      PIPE_BIND_CONSTANT_BUFFER,
                                      PIPE_USAGE_DEFAULT,
                                      sizeof(constants));
   if (ppq->constbuf == NULL) {
      pp_debug("Failed to allocate constant buffer\n");
      goto fail;
   }

   pp_debug("mlaa: using %u max search steps\n", val);

   util_sprintf(tmp_text, "%s"
                "IMM FLT32 {    %.8f,     0.0000,     0.0000,     0.0000}\n"
                "%s\n", blend2fs_1, (float) val, blend2fs_2);

   memset(&res, 0, sizeof(res));

   res.target = PIPE_TEXTURE_2D;
   res.format = PIPE_FORMAT_R8G8_UNORM;
   res.width0 = res.height0 = 165;
   res.bind = PIPE_BIND_SAMPLER_VIEW;
   res.usage = PIPE_USAGE_DEFAULT;
   res.depth0 = res.array_size = res.nr_samples = 1;

   if (!ppq->p->screen->is_format_supported(ppq->p->screen, res.format,
                                            res.target, 1, res.bind))
      pp_debug("Areamap format not supported\n");

   ppq->areamaptex = ppq->p->screen->resource_create(ppq->p->screen, &res);
   
   if (ppq->areamaptex == NULL) {
      pp_debug("Failed to allocate area map texture\n");
      goto fail;
   }
   
   u_box_2d(0, 0, 165, 165, &box);

   ppq->p->pipe->texture_subdata(ppq->p->pipe, ppq->areamaptex, 0,
                                 PIPE_TRANSFER_WRITE, &box,
                                 areamap, 165 * 2, sizeof(areamap));

   ppq->shaders[n][1] = pp_tgsi_to_state(ppq->p->pipe, offsetvs, true,
                                         "offsetvs");
   if (iscolor)
      ppq->shaders[n][2] = pp_tgsi_to_state(ppq->p->pipe, color1fs,
                                            false, "color1fs");
   else
      ppq->shaders[n][2] = pp_tgsi_to_state(ppq->p->pipe, depth1fs,
                                            false, "depth1fs");
   ppq->shaders[n][3] = pp_tgsi_to_state(ppq->p->pipe, tmp_text, false,
                                         "blend2fs");
   ppq->shaders[n][4] = pp_tgsi_to_state(ppq->p->pipe, neigh3fs, false,
                                         "neigh3fs");

   FREE(tmp_text);

   return TRUE;

 fail:
   
   FREE(tmp_text);

   /*
    * Call the common free function for destruction of partially initialized
    * resources.
    */
   pp_jimenezmlaa_free(ppq, n);

   return FALSE;
}