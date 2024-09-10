cibar_t *cibar_open(FILE *f)
{
  cibar_internal_file_entry_t *entries;
  char *strings;
  uint8_t *data;
  cibar_internal_t cb;
  cibar_t *out;
  int i;

  if (!f)
    return NULL;

  /* Read the header */
  fread(&cb, sizeof(cibar_internal_t), 1, f);

  if (cb.magic != 0x12344321)
    {
      printf("cibar: Wrong magic: 0x%08x\n", cb.magic);
      goto error_1;
    }

  /* Allocate structures */
  if ( !(entries = (cibar_internal_file_entry_t*)malloc(sizeof(cibar_internal_file_entry_t) * cb.n_file_entries)) )
    goto error_1;
  if ( !(strings = (char*)malloc( cb.strtab_length )) )
    goto error_2;
  if ( !(data = (uint8_t*)malloc( cb.data_length )) )
    goto error_3;
  if ( !(out = (cibar_t*)malloc( sizeof(cibar_t) + sizeof(cibar_file_entry_t) * cb.n_file_entries)) )
    goto error_4;

  /* Read the rest of the file */
  if (fread(entries, 1, sizeof(cibar_internal_file_entry_t) * cb.n_file_entries, f) !=
      sizeof(cibar_internal_file_entry_t) * cb.n_file_entries)
    goto error_4;
  if (fread(strings, 1, cb.strtab_length, f) != cb.strtab_length)
    goto error_4;
  if (fread(data, 1, cb.data_length, f) != cb.data_length)
    goto error_4;

  /* Fill in the out stucture */
  out->n_files = cb.n_file_entries;
  out->strings = strings;
  out->data = data;
  for (i = 0; i < cb.n_file_entries; i++)
    {
      cibar_file_entry_t *p = &out->files[i];

      p->cibar = out;
      p->data = data + entries[i].data_offset;
      p->data_size = entries[i].data_size;
      p->name = strings + entries[i].strtab_offset;
    }

  free(entries);

  return out;
 error_4:
  free(data);
 error_3:
  free(strings);
 error_2:
  free(entries);
 error_1:
  return NULL;
}