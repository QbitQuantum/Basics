int PFSLoader::Open(FILE *fp) {
  struct_header s3d_header;
  struct_directory_header s3d_dir_header;
  struct_directory s3d_dir;
  struct_data_block s3d_data;
  struct_fn_header *s3d_fn_header;
  struct_fn_entry *s3d_fn_entry;

  uint32 *offsets;

  char *temp, *temp2;
  int i, j, pos, inf, tmp, running = 0;

  fread(&s3d_header, sizeof(struct_header), 1, fp);
  if(s3d_header.magicCookie[0] != 'P' || s3d_header.magicCookie[1] != 'F' || s3d_header.magicCookie[2] != 'S' || s3d_header.magicCookie[3] != ' ')
    return 0;

  this->fp = fp;

  fseek(fp, s3d_header.offset, SEEK_SET);
  fread(&s3d_dir_header, sizeof(struct_directory_header), 1, fp);
  
  this->count = s3d_dir_header.count - 1;
  this->filenames = new char *[s3d_dir_header.count];
  this->files = new uint32[s3d_dir_header.count - 1];
  offsets = new uint32[s3d_dir_header.count - 1];

  for(i = 0; i < (int)s3d_dir_header.count; ++i) {
    fread(&s3d_dir, sizeof(struct_directory), 1, fp);

    if(s3d_dir.crc == ntohl(0xC90A5861)) {
      pos = ftell(fp);
      fseek(fp, s3d_dir.offset, SEEK_SET);
      temp = new char[s3d_dir.size];
      memset(temp, 0, s3d_dir.size);
      inf = 0;
      while(inf < (int)s3d_dir.size) {
        fread(&s3d_data, sizeof(struct_data_block), 1, fp);
        temp2 = new char[s3d_data.deflen];
        fread(temp2, s3d_data.deflen, 1, fp);
        decompress(temp2, temp + inf, s3d_data.deflen, s3d_data.inflen);
        delete[] temp2;
        inf += s3d_data.inflen;
      }
      fseek(fp, pos, SEEK_SET);
      s3d_fn_header = (struct_fn_header *) temp;
      pos = sizeof(struct_fn_header);
      for(j = 0; j < (int)s3d_fn_header->fncount; ++j) {
        s3d_fn_entry = (struct_fn_entry *) &temp[pos];
        this->filenames[j] = new char[s3d_fn_entry->fnlen + 1];
        this->filenames[j][s3d_fn_entry->fnlen] = 0;
        memcpy(this->filenames[j], &temp[pos + sizeof(struct_fn_entry)], s3d_fn_entry->fnlen);
        pos += sizeof(struct_fn_entry) + s3d_fn_entry->fnlen;
      }
    }

    else {
      this->files[running] = ftell(fp) - 12;
      offsets[running] = s3d_dir.offset;
      ++running;
    }

  }

  for(i = s3d_dir_header.count - 2; i > 0; i--) {
    for(j = 0; j < i; j++) {
      if(offsets[j] > offsets[j+1]) {
        tmp = offsets[j];
        offsets[j] = offsets[j + 1];
        offsets[j + 1] = tmp;
        tmp = this->files[j];
        this->files[j] = this->files[j + 1];
        this->files[j + 1] = tmp;
      }
    }
  }

  return 1;
}