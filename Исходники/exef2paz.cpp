int main(int argc, char** argv) {
  if (argc != 3) {
    fprintf(stderr, "exef2paz v1.22 by asmodean\n\n");
    fprintf(stderr, "usage: %s <input.paz> <game index>\n\n", argv[0]);
    fprintf(stderr, "\t 0 = ef - the latter tale\n", argv[0]);
    fprintf(stderr, "\t 1 = eden*\n", argv[0]);
    return -1;
  }

  string        in_filename(argv[1]);
  unsigned long game_index = atol(argv[2]);

  if (game_index >= GAME_COUNT) {
    fprintf(stderr, "Unknown game index: %d\n", game_index);
    return -1;
  }

  string prefix(as::stringtol(as::get_file_prefix(in_filename, true)));

  game_info_t game_info = GAME_INFO[game_index];
  key_info_t  keys;

  for (unsigned long i = 0; !game_info.keys[i].prefix.empty(); i++)
  {
    if (prefix == game_info.keys[i].prefix)
    {
      keys = game_info.keys[i];
    }
  }

  if (keys.prefix.empty()) {
    fprintf(stderr, "%s: don't know encryption key.\n", in_filename.c_str());
    return -1;
  }

  // Hard to recognize individual sound files because they lack extension
  bool is_audio = prefix == "bgm" || prefix == "se" || prefix == "voice" || prefix == "PMvoice";
  bool is_mov   = prefix == "mov";

  int fd = as::open_or_die(in_filename, O_RDONLY | O_BINARY);  

  PAZHDR hdr;
  read(fd, &hdr, sizeof(hdr));  

  char simple_key = hdr.toc_len >> 24;

  lseek(fd, 0, SEEK_SET);
  read_unobfuscate(fd, simple_key, &hdr, sizeof(hdr));  

  Blowfish bf;  

  unsigned char* toc_buff = new unsigned char[hdr.toc_len];
  read_unobfuscate(fd, simple_key, toc_buff, hdr.toc_len);
  bf.Set_Key(keys.toc_key, sizeof(keys.toc_key));
  bf.Decrypt(toc_buff, hdr.toc_len);  

  PAZHDR2*       hdr2 = (PAZHDR2*) toc_buff;
  unsigned char* p    = (unsigned char*) (hdr2 + 1);

  unsigned char* mov_seed = NULL;

  if (is_mov)
  {
    mov_seed = p;
    p += 256;
  }

  for (unsigned long i = 0; i < hdr2->entry_count; i++)
  {
    string filename = (char*) p;
    p += filename.length() + 1;

    PAZENTRY* entry = (PAZENTRY*) p;
    p += sizeof(*entry);    

    unsigned long  len  = entry->padded_length;
    unsigned char* buff = new unsigned char[len];
    lseek(fd, entry->offset, SEEK_SET);
    read_unobfuscate(fd, simple_key, buff, len);

    string crud;

    if (filename.find(".png") != string::npos)
    {
      crud = game_info.crud.png;
    }
    else if (filename.find(".ogg") != string::npos || is_audio)
    {
      crud = game_info.crud.ogg;
    }
    else if (filename.find(".sc") != string::npos)
    {
      crud = game_info.crud.sc;
    }
    else if (filename.find(".avi") != string::npos)
    {
      crud = game_info.crud.avi;
    }

    string seed = as::stringtol(filename) + as::stringf(" %08X ", entry->length) + crud;

    if (is_mov)
    {
      decrypt_mov(mov_seed, seed, buff, len);
    }
    else
    {
      bf.Set_Key(keys.dat_key, sizeof(keys.dat_key));
      bf.Decrypt(buff, len);

      if (!crud.empty()) {
        unobfuscate3(seed, buff, len);
      }
    }

    as::make_path(filename);
    as::write_file(filename, buff, entry->length);

    delete [] buff;
  }

  delete [] toc_buff;

  close(fd);

  return 0;
}