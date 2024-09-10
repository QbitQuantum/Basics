FT_Error
TA_sfnt_build_glyph_instructions(SFNT* sfnt,
                                 FONT* font,
                                 FT_Long idx)
{
  FT_Face face = sfnt->face;
  FT_Error error;

  FT_Byte* ins_buf;
  FT_UInt ins_len;
  FT_Byte* bufp;
  FT_Byte* p;

  SFNT_Table* glyf_table = &font->tables[sfnt->glyf_idx];
  glyf_Data* data = (glyf_Data*)glyf_table->data;
  /* `idx' is never negative */
  GLYPH* glyph = &data->glyphs[idx];

  TA_GlyphHints hints;

  FT_UInt num_hints_records;
  Hints_Record* hints_records;

  Recorder recorder;

  FT_Int32 load_flags;
  FT_UInt size;


  /* XXX: right now, we abuse this flag to control */
  /*      the global behaviour of the auto-hinter */
  load_flags = font->fallback_script << 30;
  load_flags |= 1 << 28; /* vertical hinting only */
  if (font->increase_x_height)
    load_flags |= 1 << 29;
  if (!font->pre_hinting)
    load_flags |= FT_LOAD_NO_SCALE;

  /* computing the segments is resolution independent, */
  /* thus the pixel size in this call is arbitrary */
  error = FT_Set_Pixel_Sizes(face, 20, 20);
  if (error)
    return error;

  ta_loader_register_hints_recorder(font->loader, NULL, NULL);
  error = ta_loader_load_glyph(font->loader, face, (FT_UInt)idx, load_flags);
  if (error)
    return error;

  /* do nothing if we have an empty glyph */
  if (!face->glyph->outline.n_contours)
    return FT_Err_Ok;

  hints = &font->loader->hints;

  /* do nothing if the setup delivered the dummy module only */
  if (!hints->num_points)
    return FT_Err_Ok;

  /* we allocate a buffer which is certainly large enough */
  /* to hold all of the created bytecode instructions; */
  /* later on it gets reallocated to its real size */
  ins_len = hints->num_points * 1000;
  ins_buf = (FT_Byte*)malloc(ins_len);
  if (!ins_buf)
    return FT_Err_Out_Of_Memory;

  /* initialize array with an invalid bytecode */
  /* so that we can easily find the array length at reallocation time */
  memset(ins_buf, INS_A0, ins_len);

  num_hints_records = 0;
  hints_records = NULL;

  /* handle composite glyph */
  if (font->loader->gloader->base.num_subglyphs)
  {
    bufp = TA_font_build_subglyph_shifter(font, ins_buf);
    if (!bufp)
    {
      error = FT_Err_Out_Of_Memory;
      goto Err;
    }

    goto Done1;
  }

  /* only scale the glyph if the dummy hinter has been used */
  if (font->loader->metrics->clazz == &ta_dummy_script_class)
  {
    /* since `TA_init_recorder' hasn't been called yet, */
    /* we manually initialize the `glyph' field */
    recorder.glyph = glyph;

    bufp = TA_sfnt_build_glyph_scaler(sfnt, &recorder, ins_buf);
    if (!bufp)
    {
      error = FT_Err_Out_Of_Memory;
      goto Err;
    }

    goto Done1;
  }

  error = TA_init_recorder(&recorder, face->glyph->outline.n_contours,
                           font, glyph, hints);
  if (error)
    goto Err;

  bufp = TA_sfnt_build_glyph_segments(sfnt, &recorder, ins_buf);
  if (!bufp)
  {
    error = FT_Err_Out_Of_Memory;
    goto Err;
  }

  /* now we loop over a large range of pixel sizes */
  /* to find hints records which get pushed onto the bytecode stack */

#ifdef DEBUGGING
  {
    int num_chars, i;


    num_chars = fprintf(stderr, "glyph %ld\n", idx);
    for (i = 0; i < num_chars - 1; i++)
      putc('=', stderr);
    fprintf(stderr, "\n\n");

  }
#endif

  /* we temporarily use `ins_buf' to record the current glyph hints, */
  /* leaving two bytes at the beginning so that the number of actions */
  /* can be inserted later on */
  ta_loader_register_hints_recorder(font->loader,
                                    TA_hints_recorder,
                                    (void*)&recorder);

  for (size = font->hinting_range_min;
       size <= font->hinting_range_max;
       size++)
  {
    TA_rewind_recorder(&recorder, bufp, size);

    error = FT_Set_Pixel_Sizes(face, size, size);
    if (error)
      goto Err;

    /* calling `ta_loader_load_glyph' uses the */
    /* `TA_hints_recorder' function as a callback, */
    /* modifying `hints_record' */
    error = ta_loader_load_glyph(font->loader, face, idx, load_flags);
    if (error)
      goto Err;

    /* append the point hints data collected in `TA_hints_recorder' */
    TA_build_point_hints(&recorder, hints);

    /* store the number of actions in `ins_buf' */
    *bufp = HIGH(recorder.hints_record.num_actions);
    *(bufp + 1) = LOW(recorder.hints_record.num_actions);

    if (TA_hints_record_is_different(hints_records,
                                     num_hints_records,
                                     bufp, recorder.hints_record.buf))
    {
#ifdef DEBUGGING
      {
        fprintf(stderr, "  size %d:\n", size);

        ta_glyph_hints_dump_edges(_ta_debug_hints);
        ta_glyph_hints_dump_segments(_ta_debug_hints);
        ta_glyph_hints_dump_points(_ta_debug_hints);

        fprintf(stderr, "  hints record:\n");
        for (p = bufp; p < recorder.hints_record.buf; p += 2)
          fprintf(stderr, " %2d", *p * 256 + *(p + 1));
        fprintf(stderr, "\n");
      }
#endif

      error = TA_add_hints_record(&hints_records,
                                  &num_hints_records,
                                  bufp, recorder.hints_record);
      if (error)
        goto Err;
    }
  }

  if (num_hints_records == 1 && !hints_records[0].num_actions)
  {
    /* since we only have a single empty record we just scale the glyph, */
    /* overwriting the data from `TA_sfnt_build_glyph_segments' */
    bufp = TA_sfnt_build_glyph_scaler(sfnt, &recorder, ins_buf);
    if (!bufp)
    {
      error = FT_Err_Out_Of_Memory;
      goto Err;
    }

    /* clear the rest of the temporarily used part of `ins_buf' */
    p = bufp;
    while (*p != INS_A0)
      *(p++) = INS_A0;

    goto Done;
  }

  /* in most cases, the output of `TA_sfnt_build_glyph_segments' */
  /* is shorter than the previously stored data, */
  /* so clear the rest of the temporarily used part of `ins_buf' */
  /* before appending the hints records */
  p = bufp;
  while (*p != INS_A0)
    *(p++) = INS_A0;

  bufp = TA_sfnt_emit_hints_records(sfnt,
                                    hints_records, num_hints_records,
                                    bufp);

Done:
  TA_free_hints_records(hints_records, num_hints_records);
  TA_free_recorder(&recorder);

  /* we are done, so reallocate the instruction array to its real size */
  if (*bufp == INS_A0)
  {
    /* search backwards */
    while (*bufp == INS_A0)
      bufp--;
    bufp++;
  }
  else
  {
    /* search forwards */
    while (*bufp != INS_A0)
      bufp++;
  }

Done1:
  ins_len = bufp - ins_buf;

  if (ins_len > sfnt->max_instructions)
    sfnt->max_instructions = ins_len;

  glyph->ins_buf = (FT_Byte*)realloc(ins_buf, ins_len);
  glyph->ins_len = ins_len;

  return FT_Err_Ok;

Err:
  TA_free_hints_records(hints_records, num_hints_records);
  TA_free_recorder(&recorder);
  free(ins_buf);

  return error;
}