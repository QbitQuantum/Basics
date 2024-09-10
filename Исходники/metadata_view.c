/* update all values to reflect mouse over image id or no data at all */
static void _metadata_view_update_values(dt_lib_module_t *self)
{
  dt_lib_metadata_view_t *d = (dt_lib_metadata_view_t *)self->data;
  int32_t mouse_over_id = dt_control_get_mouse_over_id();

  if (mouse_over_id == -1)
  {
    const dt_view_t *cv = dt_view_manager_get_current_view(darktable.view_manager);
    if(cv->view((dt_view_t*)cv) == DT_VIEW_DARKROOM)
    {
      mouse_over_id = darktable.develop->image_storage.id;
    }
    else
    {
      sqlite3_stmt *stmt;
      DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db), "select imgid from selected_images limit 1", -1, &stmt, NULL);
      if(sqlite3_step(stmt) == SQLITE_ROW)
        mouse_over_id = sqlite3_column_int(stmt, 0);
      sqlite3_finalize(stmt);
    }
  }

  if(mouse_over_id >= 0)
  {
    char value[512];
    char pathname[PATH_MAX];
    const dt_image_t *img = dt_image_cache_read_get(darktable.image_cache, mouse_over_id);
    if(!img) goto fill_minuses;
    if(img->film_id == -1)
    {
      dt_image_cache_read_release(darktable.image_cache, img);
      goto fill_minuses;
    }

    /* update all metadata */

    dt_image_film_roll(img, value, sizeof(value));
    _metadata_update_value(d->metadata[md_internal_filmroll], value);
    const int tp = 512;
    char tooltip[tp];
    snprintf(tooltip, tp, _("double click to jump to film roll\n%s"), value);
    g_object_set(G_OBJECT(d->metadata[md_internal_filmroll]), "tooltip-text", tooltip, (char *)NULL);

    snprintf(value,sizeof(value),"%d", img->id);
    _metadata_update_value(d->metadata[md_internal_imgid], value);

    snprintf(value,sizeof(value),"%d", img->group_id);
    _metadata_update_value(d->metadata[md_internal_groupid], value);

    _metadata_update_value(d->metadata[md_internal_filename], img->filename);

    snprintf(value,sizeof(value),"%d", img->version);
    _metadata_update_value(d->metadata[md_internal_version], value);

    gboolean from_cache = FALSE;
    dt_image_full_path(img->id, pathname, sizeof(pathname), &from_cache);
    _metadata_update_value(d->metadata[md_internal_fullpath], pathname);

    snprintf(value, sizeof(value), "%s", (img->flags & DT_IMAGE_LOCAL_COPY)?_("yes"):_("no"));
    _metadata_update_value(d->metadata[md_internal_local_copy], value);

    // TODO: decide if this should be removed for a release. maybe #ifdef'ing to only add it to git compiles?

    // the bits of the flags
    {
      #define EMPTY_FIELD '.'
      #define FALSE_FIELD '.'
      #define TRUE_FIELD '!'

      char *tooltip = NULL;
      char *flag_descriptions[] = { N_("unused"),
                                    N_("unused/deprecated"),
                                    N_("ldr"),
                                    N_("raw"),
                                    N_("hdr"),
                                    N_("marked for deletion"),
                                    N_("auto-applying presets applied"),
                                    N_("legacy flag. set for all new images"),
                                    N_("local copy"),
                                    N_("has .txt"),
                                    N_("has .wav")
      };
      char *tooltip_parts[13] = { 0 };
      int next_tooltip_part = 0;

      memset(value, EMPTY_FIELD, sizeof(value));

      int stars = img->flags & 0x7;
      char *star_string = NULL;
      if(stars == 6)
      {
        value[0] = 'x';
        tooltip_parts[next_tooltip_part++] = _("image rejected");
      }
      else
      {
        value[0] = '0' + stars;
        tooltip_parts[next_tooltip_part++] = star_string = g_strdup_printf(ngettext("image has %d star", "image has %d stars", stars), stars);
      }


      if(img->flags & 8)
      {
        value[1] = TRUE_FIELD;
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[0]);
      }
      else
        value[1] = FALSE_FIELD;

      if(img->flags & DT_IMAGE_THUMBNAIL_DEPRECATED)
      {
        value[2] = TRUE_FIELD;
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[1]);
      }
      else
        value[2] = FALSE_FIELD;

      if(img->flags & DT_IMAGE_LDR)
      {
        value[3] = 'l';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[2]);
      }

      if(img->flags & DT_IMAGE_RAW)
      {
        value[4] = 'r';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[3]);
      }

      if(img->flags & DT_IMAGE_HDR)
      {
        value[5] = 'h';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[4]);
      }

      if(img->flags & DT_IMAGE_REMOVE)
      {
        value[6] = 'd';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[5]);
      }

      if(img->flags & DT_IMAGE_AUTO_PRESETS_APPLIED)
      {
        value[7] = 'a';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[6]);
      }

      if(img->flags & DT_IMAGE_NO_LEGACY_PRESETS)
      {
        value[8] = 'p';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[7]);
      }

      if(img->flags & DT_IMAGE_LOCAL_COPY)
      {
        value[9] = 'c';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[8]);
      }

      if(img->flags & DT_IMAGE_HAS_TXT)
      {
        value[10] = 't';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[9]);
      }

      if(img->flags & DT_IMAGE_HAS_WAV)
      {
        value[11] = 'w';
        tooltip_parts[next_tooltip_part++] = _(flag_descriptions[10]);
      }

      value[12] = '\0';

      tooltip = g_strjoinv("\n", tooltip_parts);

      _metadata_update_value(d->metadata[md_internal_flags], value);
      g_object_set(G_OBJECT(d->metadata[md_internal_flags]), "tooltip-text", tooltip, (char *)NULL);

      g_free(star_string);
      g_free(tooltip);

      #undef EMPTY_FIELD
      #undef FALSE_FIELD
      #undef TRUE_FIELD
    }

    /* EXIF */
    _metadata_update_value_end(d->metadata[md_exif_model], img->exif_model);
    _metadata_update_value_end(d->metadata[md_exif_lens], img->exif_lens);
    _metadata_update_value_end(d->metadata[md_exif_maker], img->exif_maker);

    snprintf(value, sizeof(value), "F/%.1f", img->exif_aperture);
    _metadata_update_value(d->metadata[md_exif_aperture], value);

    if(img->exif_exposure <= 0.5) snprintf(value, sizeof(value), "1/%.0f", 1.0/img->exif_exposure);
    else                          snprintf(value, sizeof(value), "%.1f''", img->exif_exposure);
    _metadata_update_value(d->metadata[md_exif_exposure], value);

    snprintf(value, sizeof(value), "%.0f mm", img->exif_focal_length);
    _metadata_update_value(d->metadata[md_exif_focal_length], value);

    if (isnan(img->exif_focus_distance) || fpclassify(img->exif_focus_distance) == FP_ZERO)
    {
      _metadata_update_value(d->metadata[md_exif_focus_distance], NODATA_STRING);
    }
    else
    {
      snprintf(value, sizeof(value), "%.2f m", img->exif_focus_distance);
      _metadata_update_value(d->metadata[md_exif_focus_distance], value);
    }

    snprintf(value, sizeof(value), "%.0f", img->exif_iso);
    _metadata_update_value(d->metadata[md_exif_iso], value);

    _metadata_update_value(d->metadata[md_exif_datetime], img->exif_datetime_taken);

    snprintf(value, sizeof(value), "%d", img->height);
    _metadata_update_value(d->metadata[md_exif_height], value);
    snprintf(value, sizeof(value), "%d", img->width);
    _metadata_update_value(d->metadata[md_exif_width], value);

    /* XMP */
    GList *res;
    if((res = dt_metadata_get(img->id, "Xmp.dc.title", NULL))!=NULL)
    {
      snprintf(value, sizeof(value), "%s", (char*)res->data);
      _filter_non_printable(value, sizeof(value));
      g_list_free_full(res, &g_free);
    }
    else
      snprintf(value, sizeof(value), NODATA_STRING);
    _metadata_update_value(d->metadata[md_xmp_title], value);

    if((res = dt_metadata_get(img->id, "Xmp.dc.creator", NULL))!=NULL)
    {
      snprintf(value, sizeof(value), "%s", (char*)res->data);
      _filter_non_printable(value, sizeof(value));
      g_list_free_full(res, &g_free);
    }
    else
      snprintf(value, sizeof(value), NODATA_STRING);
    _metadata_update_value(d->metadata[md_xmp_creator], value);

    if((res = dt_metadata_get(img->id, "Xmp.dc.rights", NULL))!=NULL)
    {
      snprintf(value, sizeof(value), "%s", (char*)res->data);
      _filter_non_printable(value, sizeof(value));
      g_list_free_full(res, &g_free);
    }
    else
      snprintf(value, sizeof(value), NODATA_STRING);
    _metadata_update_value(d->metadata[md_xmp_rights], value);

    /* geotagging */
    /* latitude */
    if(isnan(img->latitude))
    {
      _metadata_update_value(d->metadata[md_geotagging_lat], NODATA_STRING);
    }
    else
    {
#ifdef HAVE_MAP
      if(dt_conf_get_bool("plugins/lighttable/metadata_view/pretty_location"))
      {
        gchar *latitude = osd_latitude_str(img->latitude);
        _metadata_update_value(d->metadata[md_geotagging_lat], latitude);
        g_free(latitude);
      }
      else
      {
#endif
        gchar NS = img->latitude<0?'S':'N';
        snprintf(value, sizeof(value), "%c %09.6f", NS, fabs(img->latitude));
        _metadata_update_value(d->metadata[md_geotagging_lat], value);
#ifdef HAVE_MAP
      }
#endif
    }
    /* longitude */
    if(isnan(img->longitude))
    {
      _metadata_update_value(d->metadata[md_geotagging_lon], NODATA_STRING);
    }
    else
    {
#ifdef HAVE_MAP
      if(dt_conf_get_bool("plugins/lighttable/metadata_view/pretty_location"))
      {
        gchar *longitude = osd_longitude_str(img->longitude);
        _metadata_update_value(d->metadata[md_geotagging_lon], longitude);
        g_free(longitude);
      }
      else
      {
#endif
        gchar EW = img->longitude<0?'W':'E';
        snprintf(value, sizeof(value), "%c %010.6f", EW, fabs(img->longitude));
        _metadata_update_value(d->metadata[md_geotagging_lon], value);
#ifdef HAVE_MAP
      }
#endif
    }

    /* release img */
    dt_image_cache_read_release(darktable.image_cache, img);

  }

  return;

  /* reset */
fill_minuses:
  for(int k=0; k<md_size; k++)
    _metadata_update_value(d->metadata[k],NODATA_STRING);

}