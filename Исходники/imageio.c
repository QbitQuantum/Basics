// internal function: to avoid exif blob reading + 8-bit byteorder flag + high-quality override
int dt_imageio_export_with_flags(const uint32_t imgid, const char *filename,
                                 dt_imageio_module_format_t *format, dt_imageio_module_data_t *format_params,
                                 const int32_t ignore_exif, const int32_t display_byteorder,
                                 const gboolean high_quality, const gboolean upscale, const int32_t thumbnail_export,
                                 const char *filter, const gboolean copy_metadata,
                                 dt_colorspaces_color_profile_type_t icc_type, const gchar *icc_filename,
                                 dt_iop_color_intent_t icc_intent,
                                 dt_imageio_module_storage_t *storage,
                                 dt_imageio_module_data_t *storage_params, int num, int total)
{
  dt_develop_t dev;
  dt_dev_init(&dev, 0);
  dt_dev_load_image(&dev, imgid);

  const int buf_is_downscaled
      = (thumbnail_export && dt_conf_get_bool("plugins/lighttable/low_quality_thumbnails"));

  dt_mipmap_buffer_t buf;
  if(buf_is_downscaled)
    dt_mipmap_cache_get(darktable.mipmap_cache, &buf, imgid, DT_MIPMAP_F, DT_MIPMAP_BLOCKING, 'r');
  else
    dt_mipmap_cache_get(darktable.mipmap_cache, &buf, imgid, DT_MIPMAP_FULL, DT_MIPMAP_BLOCKING, 'r');

  const dt_image_t *img = &dev.image_storage;

  if(!buf.buf || !buf.width || !buf.height)
  {
    fprintf(stderr, "allocation failed???\n");
    dt_control_log(_("image `%s' is not available!"), img->filename);
    goto error_early;
  }

  const int wd = img->width;
  const int ht = img->height;
  const float max_scale = upscale ? 100.0 : 1.0;

  int res = 0;

  dt_times_t start;
  dt_get_times(&start);
  dt_dev_pixelpipe_t pipe;
  res = thumbnail_export ? dt_dev_pixelpipe_init_thumbnail(&pipe, wd, ht)
                         : dt_dev_pixelpipe_init_export(&pipe, wd, ht, format->levels(format_params));
  if(!res)
  {
    dt_control_log(
        _("failed to allocate memory for %s, please lower the threads used for export or buy more memory."),
        thumbnail_export ? C_("noun", "thumbnail export") : C_("noun", "export"));
    goto error;
  }

  //  If a style is to be applied during export, add the iop params into the history
  if(!thumbnail_export && format_params->style[0] != '\0')
  {
    GList *style_items = dt_styles_get_item_list(format_params->style, TRUE, -1);
    if(!style_items)
    {
      dt_control_log(_("cannot find the style '%s' to apply during export."), format_params->style);
      goto error;
    }

    // remove everything above history_end
    GList *history = g_list_nth(dev.history, dev.history_end);
    while(history)
    {
      GList *next = g_list_next(history);
      dt_dev_history_item_t *hist = (dt_dev_history_item_t *)(history->data);
      free(hist->params);
      free(hist->blend_params);
      free(history->data);
      dev.history = g_list_delete_link(dev.history, history);
      history = next;
    }

    // Add each params
    for(GList *iter = style_items; iter; iter = g_list_next(iter))
    {
      dt_style_item_t *s = (dt_style_item_t *)iter->data;

      for(GList *module = dev.iop; module; module = g_list_next(module))
      {
        dt_iop_module_t *m = (dt_iop_module_t *)module->data;

        if(!strcmp(m->op, s->operation))
        {
          dt_dev_history_item_t *h = malloc(sizeof(dt_dev_history_item_t));
          dt_iop_module_t *style_module = m;

          if((format_params->style_append && !(m->flags() & IOP_FLAGS_ONE_INSTANCE)) || m->multi_priority != s->multi_priority)
          {
            // dt_dev_module_duplicate() doesn't work here, it's trying too hard to be clever
            style_module = (dt_iop_module_t *)calloc(1, sizeof(dt_iop_module_t));
            if(style_module && !dt_iop_load_module(style_module, m->so, m->dev))
            {
              style_module->instance = m->instance;
              style_module->multi_priority = s->multi_priority;
              snprintf(style_module->multi_name, sizeof(style_module->multi_name), "%s", s->name);
              dev.iop = g_list_insert_sorted(dev.iop, style_module, sort_plugins);
            }
            else
            {
              free(h);
              goto error;
            }
          }

          h->params = s->params;
          h->blend_params = s->blendop_params;
          h->enabled = s->enabled;
          h->module = style_module;
          h->multi_priority = s->multi_priority;
          g_strlcpy(h->multi_name, s->name, sizeof(h->multi_name));

          if(m->legacy_params && (s->module_version != m->version()))
          {
            void *new_params = malloc(m->params_size);
            m->legacy_params(m, h->params, s->module_version, new_params, labs(m->version()));

            free(h->params);
            h->params = new_params;
          }

          dev.history_end++;
          dev.history = g_list_append(dev.history, h);

          // make sure that dt_style_item_free doesn't free data we still use
          s->params = NULL;
          s->blendop_params = NULL;

          break;
        }
      }
    }
    g_list_free_full(style_items, dt_style_item_free);
  }

  dt_dev_pixelpipe_set_icc(&pipe, icc_type, icc_filename, icc_intent);
  dt_dev_pixelpipe_set_input(&pipe, &dev, (float *)buf.buf, buf.width, buf.height, buf.iscale);
  dt_dev_pixelpipe_create_nodes(&pipe, &dev);
  dt_dev_pixelpipe_synch_all(&pipe, &dev);

  if(filter)
  {
    if(!strncmp(filter, "pre:", 4)) dt_dev_pixelpipe_disable_after(&pipe, filter + 4);
    if(!strncmp(filter, "post:", 5)) dt_dev_pixelpipe_disable_before(&pipe, filter + 5);
  }

  dt_dev_pixelpipe_get_dimensions(&pipe, &dev, pipe.iwidth, pipe.iheight, &pipe.processed_width,
                                  &pipe.processed_height);

  dt_show_times(&start, "[export] creating pixelpipe", NULL);

  // find output color profile for this image:
  int sRGB = 1;
  if(icc_type == DT_COLORSPACE_SRGB)
  {
    sRGB = 1;
  }
  else if(icc_type == DT_COLORSPACE_NONE)
  {
    GList *modules = dev.iop;
    dt_iop_module_t *colorout = NULL;
    while(modules)
    {
      colorout = (dt_iop_module_t *)modules->data;
      if(colorout->get_p && strcmp(colorout->op, "colorout") == 0)
      {
        const dt_colorspaces_color_profile_type_t *type = colorout->get_p(colorout->params, "type");
        sRGB = (!type || *type == DT_COLORSPACE_SRGB);
        break; // colorout can't have > 1 instance
      }
      modules = g_list_next(modules);
    }
  }
  else
  {
    sRGB = 0;
  }

  // get only once at the beginning, in case the user changes it on the way:
  const gboolean high_quality_processing
      = ((format_params->max_width == 0 || format_params->max_width >= pipe.processed_width)
         && (format_params->max_height == 0 || format_params->max_height >= pipe.processed_height))
            ? FALSE
            : high_quality;

  const int width = format_params->max_width;
  const int height = format_params->max_height;
  const double scalex = width > 0 ? fminf(width / (double)pipe.processed_width, max_scale) : 1.0;
  const double scaley = height > 0 ? fminf(height / (double)pipe.processed_height, max_scale) : 1.0;
  const double scale = fminf(scalex, scaley);

  const int processed_width = scale * pipe.processed_width + .5f;
  const int processed_height = scale * pipe.processed_height + .5f;

  const int bpp = format->bpp(format_params);

  dt_get_times(&start);
  if(high_quality_processing)
  {
    /*
     * if high quality processing was requested, downsampling will be done
     * at the very end of the pipe (just before border and watermark)
     */
    dt_dev_pixelpipe_process_no_gamma(&pipe, &dev, 0, 0, processed_width, processed_height, scale);
  }
  else
  {
    // else, downsampling will be right after demosaic

    // so we need to turn temporarily disable in-pipe late downsampling iop.

    // find the finalscale module
    dt_dev_pixelpipe_iop_t *finalscale = NULL;
    {
      GList *nodes = g_list_last(pipe.nodes);
      while(nodes)
      {
        dt_dev_pixelpipe_iop_t *node = (dt_dev_pixelpipe_iop_t *)(nodes->data);
        if(!strcmp(node->module->op, "finalscale"))
        {
          finalscale = node;
          break;
        }
        nodes = g_list_previous(nodes);
      }
    }

    if(finalscale) finalscale->enabled = 0;

    // do the processing (8-bit with special treatment, to make sure we can use openmp further down):
    if(bpp == 8)
      dt_dev_pixelpipe_process(&pipe, &dev, 0, 0, processed_width, processed_height, scale);
    else
      dt_dev_pixelpipe_process_no_gamma(&pipe, &dev, 0, 0, processed_width, processed_height, scale);

    if(finalscale) finalscale->enabled = 1;
  }
  dt_show_times(&start, thumbnail_export ? "[dev_process_thumbnail] pixel pipeline processing"
                                         : "[dev_process_export] pixel pipeline processing",
                NULL);

  uint8_t *outbuf = pipe.backbuf;

  // downconversion to low-precision formats:
  if(bpp == 8)
  {
    if(display_byteorder)
    {
      if(high_quality_processing)
      {
        const float *const inbuf = (float *)outbuf;
        for(size_t k = 0; k < (size_t)processed_width * processed_height; k++)
        {
          // convert in place, this is unfortunately very serial..
          const uint8_t r = CLAMP(inbuf[4 * k + 2] * 0xff, 0, 0xff);
          const uint8_t g = CLAMP(inbuf[4 * k + 1] * 0xff, 0, 0xff);
          const uint8_t b = CLAMP(inbuf[4 * k + 0] * 0xff, 0, 0xff);
          outbuf[4 * k + 0] = r;
          outbuf[4 * k + 1] = g;
          outbuf[4 * k + 2] = b;
        }
      }
      // else processing output was 8-bit already, and no need to swap order
    }
    else // need to flip
    {
      // ldr output: char
      if(high_quality_processing)
      {
        const float *const inbuf = (float *)outbuf;
        for(size_t k = 0; k < (size_t)processed_width * processed_height; k++)
        {
          // convert in place, this is unfortunately very serial..
          const uint8_t r = CLAMP(inbuf[4 * k + 0] * 0xff, 0, 0xff);
          const uint8_t g = CLAMP(inbuf[4 * k + 1] * 0xff, 0, 0xff);
          const uint8_t b = CLAMP(inbuf[4 * k + 2] * 0xff, 0, 0xff);
          outbuf[4 * k + 0] = r;
          outbuf[4 * k + 1] = g;
          outbuf[4 * k + 2] = b;
        }
      }
      else
      { // !display_byteorder, need to swap:
        uint8_t *const buf8 = pipe.backbuf;
#ifdef _OPENMP
#pragma omp parallel for default(none) schedule(static)
#endif
        // just flip byte order
        for(size_t k = 0; k < (size_t)processed_width * processed_height; k++)
        {
          uint8_t tmp = buf8[4 * k + 0];
          buf8[4 * k + 0] = buf8[4 * k + 2];
          buf8[4 * k + 2] = tmp;
        }
      }
    }
  }
  else if(bpp == 16)
  {
    // uint16_t per color channel
    float *buff = (float *)outbuf;
    uint16_t *buf16 = (uint16_t *)outbuf;
    for(int y = 0; y < processed_height; y++)
      for(int x = 0; x < processed_width; x++)
      {
        // convert in place
        const size_t k = (size_t)processed_width * y + x;
        for(int i = 0; i < 3; i++) buf16[4 * k + i] = CLAMP(buff[4 * k + i] * 0x10000, 0, 0xffff);
      }
  }
  // else output float, no further harm done to the pixels :)

  format_params->width = processed_width;
  format_params->height = processed_height;

  if(!ignore_exif)
  {
    int length;
    uint8_t *exif_profile = NULL; // Exif data should be 65536 bytes max, but if original size is close to that,
                                  // adding new tags could make it go over that... so let it be and see what
                                  // happens when we write the image
    char pathname[PATH_MAX] = { 0 };
    gboolean from_cache = TRUE;
    dt_image_full_path(imgid, pathname, sizeof(pathname), &from_cache);
    // last param is dng mode, it's false here
    length = dt_exif_read_blob(&exif_profile, pathname, imgid, sRGB, processed_width, processed_height, 0);

    res = format->write_image(format_params, filename, outbuf, icc_type, icc_filename, exif_profile, length, imgid,
                              num, total);

    free(exif_profile);
  }
  else
  {
    res = format->write_image(format_params, filename, outbuf, icc_type, icc_filename, NULL, 0, imgid, num, total);
  }

  dt_dev_pixelpipe_cleanup(&pipe);
  dt_dev_cleanup(&dev);
  dt_mipmap_cache_release(darktable.mipmap_cache, &buf);

  /* now write xmp into that container, if possible */
  if(copy_metadata && (format->flags(format_params) & FORMAT_FLAGS_SUPPORT_XMP))
  {
    dt_exif_xmp_attach(imgid, filename);
    // no need to cancel the export if this fail
  }

  if(!thumbnail_export && strcmp(format->mime(format_params), "memory")
    && !(format->flags(format_params) & FORMAT_FLAGS_NO_TMPFILE))
  {
#ifdef USE_LUA
    //Synchronous calling of lua intermediate-export-image events
    dt_lua_lock();

    lua_State *L = darktable.lua_state.state;

    luaA_push(L, dt_lua_image_t, &imgid);

    lua_pushstring(L, filename);

    luaA_push_type(L, format->parameter_lua_type, format_params);
 
    if (storage)
      luaA_push_type(L, storage->parameter_lua_type, storage_params);
    else
      lua_pushnil(L);

    dt_lua_event_trigger(L, "intermediate-export-image", 4);
  
    dt_lua_unlock();
#endif

    dt_control_signal_raise(darktable.signals, DT_SIGNAL_IMAGE_EXPORT_TMPFILE, imgid, filename, format,
                            format_params, storage, storage_params);
  }

  return res;

error:
  dt_dev_pixelpipe_cleanup(&pipe);
error_early:
  dt_dev_cleanup(&dev);
  dt_mipmap_cache_release(darktable.mipmap_cache, &buf);
  return 1;
}