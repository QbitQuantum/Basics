/* This is used by cow_dir too. */
int merge_dir_lists(region_t r,
		    struct filesys_obj *dir1,
		    struct filesys_obj *dir2,
		    seqt_t *result,
		    int *err)
{
  int count1, count2;
  seqt_t got;
  seqf_t buf;
  seqf_t *array1, *array2;
  int i;

  region_t r2 = region_make();

  count1 = dir1->vtable->list(dir1, r2, &got, err);
  if(count1 < 0) { region_free(r2); return -1; }
  array1 = region_alloc(r2, count1 * sizeof(seqf_t));
  buf = flatten(r, got);
  for(i = 0; i < count1; i++) {
    int inode, type;
    seqf_t name;
    int ok = 1;
    m_int(&ok, &buf, &inode);
    m_int(&ok, &buf, &type);
    m_lenblock(&ok, &buf, &name);
    if(ok) {
      array1[i] = name;
    }
    else { region_free(r2); *err = EIO; return -1; }
  }

  count2 = dir2->vtable->list(dir2, r2, &got, err);
  if(count2 < 0) { region_free(r2); return -1; }
  array2 = region_alloc(r2, count2 * sizeof(seqf_t));
  buf = flatten(r, got);
  for(i = 0; i < count2; i++) {
    int inode, type;
    seqf_t name;
    int ok = 1;
    m_int(&ok, &buf, &inode);
    m_int(&ok, &buf, &type);
    m_lenblock(&ok, &buf, &name);
    if(ok) {
      array2[i] = name;
    }
    else { region_free(r2); *err = EIO; return -1; }
  }

  /* Sort the sequences to make it easy to merge them. */
  qsort(array1, count1, sizeof(seqf_t), sort_seqf_compare);
  qsort(array2, count2, sizeof(seqf_t), sort_seqf_compare);

  /* Merge the two sequences. */
  {
    cbuf_t buf = cbuf_make(r, 100);
    int count = 0;
    int i1 = 0, i2 = 0;
    while(1) {
      int comp;
      if(i1 < count1 && i2 < count2) {
	comp = seqf_compare(array1[i1], array2[i2]);
      }
      else if(i1 < count1) comp = -1;
      else if(i2 < count2) comp = 1;
      else break;

      cbuf_put_int(buf, 0); /* d_ino */
      cbuf_put_int(buf, 0); /* d_type */
      if(comp < 0) {
	cbuf_put_int(buf, array1[i1].size);
	cbuf_put_seqf(buf, array1[i1]);
	i1++;
      }
      else if(comp > 0) {
	cbuf_put_int(buf, array2[i2].size);
	cbuf_put_seqf(buf, array2[i2]);
	i2++;
      }
      else {
	cbuf_put_int(buf, array1[i1].size);
	cbuf_put_seqf(buf, array1[i1]);
	i1++;
	i2++;
      }
      count++;
    }
    *result = seqt_of_cbuf(buf);
    region_free(r2);
    return count;
  }
}