meta_parameters *read_asf_meta(const char *meta_name)
{
  meta_parameters *meta = meta_read(meta_name);

  // If the ASF internal format file is a single-band image with RGB color map
  // in the metadata, then store the color map as an ASF style look-up table
  if (meta->colormap) {
    int i;
    meta_colormap *mc = meta->colormap;
    char lut_file[256];
    char *lut_loc = (char *)MALLOC(sizeof(char)*(strlen(get_asf_share_dir())+128));
    sprintf(lut_loc, "%s%clook_up_tables", get_asf_share_dir(), DIR_SEPARATOR);
    sprintf(lut_file,"%s%c%s", lut_loc, DIR_SEPARATOR, EMBEDDED_ASF_COLORMAP_LUT_FILE);
    FILE *lutFP = (FILE *)FOPEN(lut_file, "wt");
    fprintf(lutFP, "# Look up table type: %s\n", mc->look_up_table);
    fprintf(lutFP, "# Originating source: %s\n", meta_name);
    fprintf(lutFP, "# Index   Red   Green   Blue\n");
    for (i=0; i<mc->num_elements; i++) {
      fprintf(lutFP, "%03d    %03d    %03d    %03d\n",
              i, mc->rgb[i].red, mc->rgb[i].green, mc->rgb[i].blue);
    }
    fprintf(lutFP, "\n");
    FCLOSE(lutFP);
  }

  return meta;
}