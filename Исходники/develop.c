static void
auto_apply_presets(dt_develop_t *dev)
{
  const int imgid = dev->image_storage.id;

  if(imgid <= 0) return;
  int run = 0;
  const dt_image_t *cimg = dt_image_cache_read_get(darktable.image_cache, imgid);
  if(!(cimg->flags & DT_IMAGE_AUTO_PRESETS_APPLIED))
    run = 1;

  // flag was already set? only apply presets once in the lifetime of a history stack.
  // (the flag will be cleared when removing it)
  if(!run || cimg->id <= 0)
  {
    dt_image_cache_read_release(darktable.image_cache, cimg);
    return;
  }

  // keep locked, we want to be alone messing with the history of the poor fellow:
  dt_image_t *image = dt_image_cache_write_get(darktable.image_cache, cimg);
  // be extra sure that we don't mess up history in separate threads:
  dt_pthread_mutex_lock(&darktable.db_insert);

  // cleanup
  DT_DEBUG_SQLITE3_EXEC(dt_database_get(darktable.db),
                        "delete from memory.history",
                        NULL, NULL, NULL);
  const char *preset_table[2] = {"presets", "legacy_presets"};
  const int legacy = (image->flags & DT_IMAGE_NO_LEGACY_PRESETS) ? 0 : 1;
  char query[1024];
  snprintf(query, 1024,
           "insert into memory.history select ?1, 0, op_version, operation, op_params, enabled, blendop_params, blendop_version, multi_priority, multi_name "
           "from %s where autoapply=1 and "
           "?2 like model and ?3 like maker and ?4 like lens and "
           "?5 between iso_min and iso_max and "
           "?6 between exposure_min and exposure_max and "
           "?7 between aperture_min and aperture_max and "
           "?8 between focal_length_min and focal_length_max and "
           "(isldr = 0 or isldr=?9) order by writeprotect desc, "
           "length(model), length(maker), length(lens)", preset_table[legacy]);
  // query for all modules at once:
  sqlite3_stmt *stmt;
  DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db), query, -1, &stmt, NULL);
  DT_DEBUG_SQLITE3_BIND_INT(stmt, 1, imgid);
  DT_DEBUG_SQLITE3_BIND_TEXT(stmt, 2, cimg->exif_model, strlen(cimg->exif_model), SQLITE_TRANSIENT);
  DT_DEBUG_SQLITE3_BIND_TEXT(stmt, 3, cimg->exif_maker, strlen(cimg->exif_maker), SQLITE_TRANSIENT);
  DT_DEBUG_SQLITE3_BIND_TEXT(stmt, 4, cimg->exif_lens,  strlen(cimg->exif_lens),  SQLITE_TRANSIENT);
  DT_DEBUG_SQLITE3_BIND_DOUBLE(stmt, 5, fmaxf(0.0f, fminf(1000000, cimg->exif_iso)));
  DT_DEBUG_SQLITE3_BIND_DOUBLE(stmt, 6, fmaxf(0.0f, fminf(1000000, cimg->exif_exposure)));
  DT_DEBUG_SQLITE3_BIND_DOUBLE(stmt, 7, fmaxf(0.0f, fminf(1000000, cimg->exif_aperture)));
  DT_DEBUG_SQLITE3_BIND_DOUBLE(stmt, 8, fmaxf(0.0f, fminf(1000000, cimg->exif_focal_length)));
  // 0: dontcare, 1: ldr, 2: raw
  DT_DEBUG_SQLITE3_BIND_DOUBLE(stmt, 9, 2-dt_image_is_ldr(cimg));

  if(sqlite3_step(stmt) == SQLITE_DONE)
  {
    sqlite3_finalize(stmt);
    int cnt = 0;
    // count what we found:
    DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db),
                                "select count(*) from memory.history",
                                -1, &stmt, NULL);
    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
      // if there is anything..
      cnt = sqlite3_column_int(stmt, 0);
      sqlite3_finalize(stmt);
      // fprintf(stderr, "[auto_apply_presets] imageid %d found %d matching presets (legacy %d)\n", imgid, cnt, legacy);
      // advance the current history by that amount:
      DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db),
                                  "update history set num=num+?1 where imgid=?2",
                                  -1, &stmt, NULL);
      DT_DEBUG_SQLITE3_BIND_INT(stmt, 1, cnt);
      DT_DEBUG_SQLITE3_BIND_INT(stmt, 2, imgid);

      if(sqlite3_step(stmt) == SQLITE_DONE)
      {
        // and finally prepend the rest with increasing numbers (starting at 0)
        sqlite3_finalize(stmt);
        DT_DEBUG_SQLITE3_PREPARE_V2(dt_database_get(darktable.db),
                                    "insert into history select imgid, rowid-1, module, operation, op_params, enabled, "
                                    "blendop_params, blendop_version, multi_priority, multi_name from memory.history",
                                    -1, &stmt, NULL);
        sqlite3_step(stmt);
      }
    }
  }
  sqlite3_finalize(stmt);

  //  first time we are loading the image, try to import lightroom .xmp if any
  if (dev->image_loading)
    dt_lightroom_import(dev->image_storage.id, dev, TRUE);

  image->flags |= DT_IMAGE_AUTO_PRESETS_APPLIED | DT_IMAGE_NO_LEGACY_PRESETS;
  dt_pthread_mutex_unlock(&darktable.db_insert);

  // make sure these end up in the image_cache + xmp (sync through here if we set the flag)
  dt_image_cache_write_release(darktable.image_cache, image, DT_IMAGE_CACHE_SAFE);
  dt_image_cache_read_release(darktable.image_cache, cimg);
}