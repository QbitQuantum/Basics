static bool
vc4_tile_blit(struct pipe_context *pctx, const struct pipe_blit_info *info)
{
        struct vc4_context *vc4 = vc4_context(pctx);
        bool msaa = (info->src.resource->nr_samples > 1 ||
                     info->dst.resource->nr_samples > 1);
        int tile_width = msaa ? 32 : 64;
        int tile_height = msaa ? 32 : 64;

        if (util_format_is_depth_or_stencil(info->dst.resource->format))
                return false;

        if (info->scissor_enable)
                return false;

        if ((info->mask & PIPE_MASK_RGBA) == 0)
                return false;

        if (info->dst.box.x != info->src.box.x ||
            info->dst.box.y != info->src.box.y ||
            info->dst.box.width != info->src.box.width ||
            info->dst.box.height != info->src.box.height) {
                return false;
        }

        int dst_surface_width = u_minify(info->dst.resource->width0,
                                         info->dst.level);
        int dst_surface_height = u_minify(info->dst.resource->height0,
                                         info->dst.level);
        if (is_tile_unaligned(info->dst.box.x, tile_width) ||
            is_tile_unaligned(info->dst.box.y, tile_height) ||
            (is_tile_unaligned(info->dst.box.width, tile_width) &&
             info->dst.box.x + info->dst.box.width != dst_surface_width) ||
            (is_tile_unaligned(info->dst.box.height, tile_height) &&
             info->dst.box.y + info->dst.box.height != dst_surface_height)) {
                return false;
        }

        /* VC4_PACKET_LOAD_TILE_BUFFER_GENERAL uses the
         * VC4_PACKET_TILE_RENDERING_MODE_CONFIG's width (determined by our
         * destination surface) to determine the stride.  This may be wrong
         * when reading from texture miplevels > 0, which are stored in
         * POT-sized areas.  For MSAA, the tile addresses are computed
         * explicitly by the RCL, but still use the destination width to
         * determine the stride (which could be fixed by explicitly supplying
         * it in the ABI).
         */
        struct vc4_resource *rsc = vc4_resource(info->src.resource);

        uint32_t stride;

        if (info->src.resource->nr_samples > 1)
                stride = align(dst_surface_width, 32) * 4 * rsc->cpp;
        else if (rsc->slices[info->src.level].tiling == VC4_TILING_FORMAT_T)
                stride = align(dst_surface_width * rsc->cpp, 128);
        else
                stride = align(dst_surface_width * rsc->cpp, 16);

        if (stride != rsc->slices[info->src.level].stride)
                return false;

        if (info->dst.resource->format != info->src.resource->format)
                return false;

        if (false) {
                fprintf(stderr, "RCL blit from %d,%d to %d,%d (%d,%d)\n",
                        info->src.box.x,
                        info->src.box.y,
                        info->dst.box.x,
                        info->dst.box.y,
                        info->dst.box.width,
                        info->dst.box.height);
        }

        struct pipe_surface *dst_surf =
                vc4_get_blit_surface(pctx, info->dst.resource, info->dst.level);
        struct pipe_surface *src_surf =
                vc4_get_blit_surface(pctx, info->src.resource, info->src.level);

        vc4_flush_jobs_reading_resource(vc4, info->src.resource);

        struct vc4_job *job = vc4_get_job(vc4, dst_surf, NULL);
        pipe_surface_reference(&job->color_read, src_surf);

        /* If we're resolving from MSAA to single sample, we still need to run
         * the engine in MSAA mode for the load.
         */
        if (!job->msaa && info->src.resource->nr_samples > 1) {
                job->msaa = true;
                job->tile_width = 32;
                job->tile_height = 32;
        }

        job->draw_min_x = info->dst.box.x;
        job->draw_min_y = info->dst.box.y;
        job->draw_max_x = info->dst.box.x + info->dst.box.width;
        job->draw_max_y = info->dst.box.y + info->dst.box.height;
        job->draw_width = dst_surf->width;
        job->draw_height = dst_surf->height;

        job->tile_width = tile_width;
        job->tile_height = tile_height;
        job->msaa = msaa;
        job->needs_flush = true;
        job->resolve |= PIPE_CLEAR_COLOR;

        vc4_job_submit(vc4, job);

        pipe_surface_reference(&dst_surf, NULL);
        pipe_surface_reference(&src_surf, NULL);

        return true;
}