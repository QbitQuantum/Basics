tmap_sff_header_t *
tmap_sff_header_read(tmap_file_t *fp)
{
  tmap_sff_header_t *h = NULL;
  uint32_t n = 0;

  h = tmap_calloc(1, sizeof(tmap_sff_header_t), "h");

  if(1 != tmap_file_fread(&h->magic, sizeof(uint32_t), 1, fp)
     || 1 != tmap_file_fread(&h->version, sizeof(uint32_t), 1, fp)
     || 1 != tmap_file_fread(&h->index_offset, sizeof(uint64_t), 1, fp)
     || 1 != tmap_file_fread(&h->index_length, sizeof(uint32_t), 1, fp)
     || 1 != tmap_file_fread(&h->n_reads, sizeof(uint32_t), 1, fp)
     || 1 != tmap_file_fread(&h->gheader_length, sizeof(uint16_t), 1, fp)
     || 1 != tmap_file_fread(&h->key_length, sizeof(uint16_t), 1, fp)
     || 1 != tmap_file_fread(&h->flow_length, sizeof(uint16_t), 1, fp)
     || 1 != tmap_file_fread(&h->flowgram_format, sizeof(uint8_t), 1, fp)) {
      tmap_error("tmap_file_fread", Exit, ReadFileError);
  }
  n += 4*sizeof(uint32_t) + sizeof(uint64_t) + 3*sizeof(uint16_t) + sizeof(uint8_t);

  // convert values from big-endian
  h->magic = ntohl(h->magic);
  h->version = ntohl(h->version);
  h->index_offset = ntohll(h->index_offset);
  h->index_length = ntohl(h->index_length);
  h->n_reads = ntohl(h->n_reads);
  h->gheader_length = ntohs(h->gheader_length);
  h->key_length = ntohs(h->key_length);
  h->flow_length = ntohs(h->flow_length);

  if(TMAP_SFF_MAGIC != h->magic) {
      tmap_error("SFF magic number did not match", Exit, ReadFileError);
  }
  if(h->version != TMAP_SFF_VERSION) {
      tmap_error("SFF version number did not match", Exit, ReadFileError);
  }

  h->flow = tmap_string_init(h->flow_length+1);
  h->key = tmap_string_init(h->key_length+1);

  if(h->flow_length != tmap_file_fread(h->flow->s, sizeof(char), h->flow_length, fp)
     || h->key_length != tmap_file_fread(h->key->s, sizeof(char), h->key_length, fp)) {
      tmap_error("tmap_file_fread", Exit, ReadFileError);
  }
  n += sizeof(char)*(h->flow_length + h->key_length);

  // set the length and null-terminator
  h->flow->l = h->flow_length;
  h->key->l = h->key_length;
  h->flow->s[h->flow->l]='\0';
  h->key->s[h->key->l]='\0';

  n += tmap_sff_read_padding(fp, n);

#ifdef TMAP_SFF_DEBUG
  tmap_sff_header_print(stderr, h);
#endif

  if(h->gheader_length != n) {
      tmap_error("SFF global header length did not match", Exit, ReadFileError);
  }

  return h;
}