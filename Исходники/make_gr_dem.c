// Input:
//   meta_parameters *meta_sar--  SAR geometry to subset the DEM
//   const char *demImg       --  DEM data filename
//   const char *demMeta      --  DEM metadata filename
//   int pad                  --  number of lines to add at the top/bottom/left/right
//   double tolerance         --  how accurate the approximation mapping needs to be,
//                                in units of pixels
//   const char *output_name  --  output filename (basename)
//   int test_mode            --  adds checks for the accuracy of the mapping, and
//                                does some unit testing
// Output:
//   no output parameters, the output is the output_name files (.img and .meta)
// Return Value:
//   return TRUE on success, FALSE on fail
//
int make_gr_dem_ext(meta_parameters *meta_sar, const char *demImg, const char *demMeta,
                    int pad, double tolerance, const char *output_name, int test_mode)
{
  if (test_mode)
    test_interp();
  
  asfPrintStatus("Reading DEM...\n");
  meta_parameters *meta_dem = meta_read(demMeta);
  float *demData = read_dem(meta_dem, demImg);
  int dnl = meta_dem->general->line_count;
  int dns = meta_dem->general->sample_count;

  char *outImg = appendExt(output_name, ".img");
  char *output_name_tmp, *outImgTmp;

  // do not do DEM smoothing if the DEM pixel size is better or close to the
  // SAR image's pixel size.
  int do_averaging = TRUE;
  if (meta_dem->general->y_pixel_size - 10 < meta_sar->general->y_pixel_size)
    do_averaging = FALSE;
  asfPrintStatus("Averaging: %s (DEM %f, SAR: %f)\n", do_averaging ? "YES" : "NO",
                 meta_dem->general->y_pixel_size,
                 meta_sar->general->y_pixel_size);
  if (do_averaging) {
    output_name_tmp = appendStr(output_name, "_unsmoothed");
    outImgTmp = appendExt(output_name_tmp, ".img");
  }
  else {
    output_name_tmp = STRDUP(output_name);
    outImgTmp = STRDUP(outImg);
  }

  // add the padding if requested
  meta_parameters *meta_out = meta_copy(meta_sar);
  meta_out->general->line_count += pad*2;
  meta_out->general->sample_count += pad*2;
  meta_out->general->start_line -= pad;
  meta_out->general->start_sample -= pad;

  // fixing up the output metadata.  Note that we must keep the SAR section
  // intact since that specifies our geometry which is the whole point of
  // this exercise.
  strcpy(meta_out->general->basename, meta_dem->general->basename);
  strcpy(meta_out->general->sensor, MAGIC_UNSET_STRING);
  strcpy(meta_out->general->processor, MAGIC_UNSET_STRING);
  strcpy(meta_out->general->mode, MAGIC_UNSET_STRING);
  strcpy(meta_out->general->sensor_name, MAGIC_UNSET_STRING);
  meta_out->general->image_data_type = DEM;
  meta_out->general->radiometry = MAGIC_UNSET_INT;
  strcpy(meta_out->general->acquisition_date, meta_dem->general->acquisition_date);
  meta_out->general->orbit = MAGIC_UNSET_INT;
  meta_out->general->orbit_direction = MAGIC_UNSET_CHAR;
  meta_out->general->frame = MAGIC_UNSET_INT;
  meta_out->general->band_count = 1;
  strcpy(meta_out->general->bands, "DEM");

  int nl = meta_out->general->line_count;
  int ns = meta_out->general->sample_count;

  // finding the right grid size
  int size = find_grid_size(meta_sar, meta_dem, 512, .1*tolerance);

  asfPrintStatus("Creating ground range image...\n");

  float *buf = MALLOC(sizeof(float)*ns*size);
  FILE *fpOut = FOPEN(outImgTmp, "wb");

  // these are for tracking the quality of the bilinear interp
  // not used if test_mode is false
  int num_out_of_tol = 0;
  int num_checked = 0;
  int num_bad = 0;
  double max_err = 0;
  double avg_err = 0;

  int ii, jj;
  for (ii=0; ii<nl; ii += size) {
    int line_lo = ii;
    int line_hi = ii + size;

    for (jj=0; jj<ns; jj += size) {
      double lines[4], samps[4];
      
      int samp_lo = jj;
      int samp_hi = jj + size;

      get_interp_params(meta_sar, meta_dem, line_lo, line_hi, samp_lo, samp_hi,
                        lines, samps);

      int iii, jjj;
      for (iii=0; iii<size; ++iii) {
        for (jjj=0; jjj<size && jj+jjj<ns; ++jjj) {
          int index = iii*ns + jj + jjj;
          assert(index < ns*size);

          double line_out, samp_out;
          xy_interp(ii+iii, jj+jjj, line_lo, line_hi, samp_lo, samp_hi, lines, samps,
                    &line_out, &samp_out);

          // random checking of the quality of our interpolations
          if (test_mode && iii%11==0 && jjj%13==0) {
            double real_line, real_samp; 
            sar_to_dem(meta_sar, meta_dem, ii+iii, jj+jjj, &real_line, &real_samp);

            double err = hypot(real_line - line_out, real_samp - samp_out);

            avg_err += err;
            if (err > max_err)
              max_err = err;

            if (err > tolerance) {
              asfPrintStatus("Out of tolerance at %d,%d: (%f,%f) vs (%f,%f) -> %f\n",
                             ii+iii, jj+jjj, line_out, samp_out, real_line, real_samp,
                             err);
              ++num_out_of_tol;
            }
            if (err > .5) {
              asfPrintStatus("Error is larger than 1 pixel!\n");
              ++num_bad;
            }
            ++num_checked;
          }
          buf[index] = interp_demData(demData, dnl, dns, line_out, samp_out);
        }
      }
    }

    put_float_lines(fpOut, meta_out, ii, size, buf);
    asfPrintStatus("Completed %.1f%%  \r", 100.*ii/(double)nl);
  }
  asfPrintStatus("Completed 100%%   \n");

  if (test_mode) {
    asfPrintStatus("Tolerance was %f\n", tolerance);
    asfPrintStatus("%d/%d checked pixels had error exceeding tolerance. (%.1f%%)\n",
                   num_out_of_tol, num_checked, 100.*num_out_of_tol/(double)num_checked);
    asfPrintStatus("%d/%d checked pixels had error larger than half a pixel. (%.1f%%)\n",
                   num_bad, num_checked, 100.*num_bad/(double)num_checked);
    asfPrintStatus("Maximum error: %f pixels\n", max_err);
    avg_err /= (double)num_checked;
    asfPrintStatus("Average error: %f pixels\n", avg_err);
  }

  FCLOSE(fpOut);
  meta_write(meta_out, outImgTmp);

  meta_free(meta_out);
  meta_free(meta_dem);

  FREE(buf);
  FREE(demData);

  // now apply 3x3 filter
  if (do_averaging) {
    asfPrintStatus("Smoothing with 3x3 kernel ...\n");
    smooth(outImgTmp, outImg, 3, EDGE_TRUNCATE);
  }

  FREE(outImg);
  FREE(outImgTmp);
  FREE(output_name_tmp);

  return FALSE;
}