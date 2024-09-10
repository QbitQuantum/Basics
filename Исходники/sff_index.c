uint32_t
sff_index_write(FILE *fp, sff_index_t *idx)
{
  int32_t i;
  uint32_t n = 0;
  uint64_t len = 0;

  if(NULL == idx) {
      return 0;
  }

  // convert values to big-endian
  sff_index_hton(idx);

  // index header
  if(1 != fwrite(&idx->index_magic_number, sizeof(uint32_t), 1, fp)
     || 1 != fwrite(&idx->index_version, sizeof(uint32_t), 1, fp)
     || 1 != fwrite(&idx->num_rows, sizeof(int32_t), 1, fp)
     || 1 != fwrite(&idx->num_cols, sizeof(int32_t), 1, fp)
     || 1 != fwrite(&idx->type, sizeof(int32_t), 1, fp)) {
      ion_error(__func__, "fwrite", Exit, WriteFileError);
  }
  n += sizeof(uint32_t)*2 + sizeof(int32_t)*3;

  // convert values from big-endian
  sff_index_ntoh(idx);

  // offsets
  if(SFF_INDEX_ROW_ONLY == idx->type) {
      len = 1 + idx->num_rows;
  }
  else if(SFF_INDEX_ALL == idx->type) {
      len = 1 + (idx->num_rows * idx->num_cols);
  }
  else {
      ion_error(__func__, "could not understand index type", Exit, OutOfRange);
  }

  // convert values to big-endian
  for(i=0;i<len;i++) {
      idx->offset[i] = htonll(idx->offset[i]);
  }
  // write
  if(len != fwrite(idx->offset, sizeof(uint64_t), len, fp)) {
      ion_error(__func__, "fwrite", Exit, WriteFileError);
  }
  n += sizeof(uint64_t) * len;
  // convert values from big-endian
  for(i=0;i<len;i++) {
      idx->offset[i] = ntohll(idx->offset[i]);
  }

  // padding
  n += ion_write_padding(fp, n);

  return n;
}