int main(int argc, char *argv[]) {
  uchar *input_seqfile;
  uchar *temp;
  uint n_seq, x;
  int l;
  FILE *indfile, *strfile, *binfile;

  configure_logmsg(MSG_DEBUG1);
  parse_arguments(&input_seqfile, argc, argv);
  configure_logmsg(verbosity_level);

  logmsg(MSG_INFO,"Output basename set to %s\n",output_basename);

  l = strlen(output_basename);
  MA(temp, (l+6)*sizeof(char));

  strcpy(temp, output_basename);
  strcat(temp, ".ind");
  indfile = openfile(temp, "w", "sequence index file");
  x = INDFILE_MAGIC;
  fwrite(&x, sizeof(uint), 1, indfile);
  
  strcpy(temp, output_basename);
  strcat(temp, ".seq");
  strfile = openfile(temp, "w", "sequence string file");
  x = STRFILE_MAGIC;
  fwrite(&x, sizeof(uint), 1, strfile);

  strcpy(temp, output_basename);
  strcat(temp, ".sbin");
  binfile = openfile(temp, "w", "sequence binary file");
  x = BINFILE_MAGIC;
  fwrite(&x, sizeof(uint), 1, binfile);
  
  n_seq = format_input(input_seqfile, indfile, strfile, binfile);
  fclose(indfile);
  fclose(strfile);
  fclose(binfile);
  logmsg(MSG_INFO,"%d sequences formatted\n",n_seq);

  return 0;
}