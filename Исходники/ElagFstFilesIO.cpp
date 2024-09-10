void LEXIC_trans_write(Elag_fst_file_out * fstf, int to) {

  unichar label[8];
  int idx;

  u_strcpy(label, "<MOT>");

  idx=get_value_index(label,fstf->labels);

  u_fprintf(fstf->f, "%d %d ", idx, to);

  u_strcpy(label, "<!MOT>");

  idx=get_value_index(label,fstf->labels);

  u_fprintf(fstf->f, "%d %d ", idx, to);
}