int gt_dlist_unit_test(GtError *err)
{
  GtDlist *dlist;
  GtDlistelem *dlistelem;
  int i, j, size, *data,
      elem_a = 7,
      elem_b = 6,
      elems[MAX_SIZE],
      elems_backup[MAX_SIZE],
      had_err = 0;
  gt_error_check(err);

  /* boundary case: empty dlist */
  dlist = gt_dlist_new(intcompare);
  gt_ensure(had_err, !gt_dlist_size(dlist));
  gt_dlist_delete(dlist);

  dlist = gt_dlist_new(NULL);
  gt_ensure(had_err, !gt_dlist_size(dlist));
  gt_dlist_delete(dlist);

  /* boundary case: dlist containing one element */
  dlist = gt_dlist_new(intcompare);
  gt_dlist_add(dlist, &elem_a);
  gt_ensure(had_err, gt_dlist_size(dlist) == 1);
  gt_ensure(had_err,
         elem_a == *(int*) gt_dlistelem_get_data(gt_dlist_first(dlist)));
  gt_dlist_delete(dlist);

  dlist = gt_dlist_new(NULL);
  gt_dlist_add(dlist, &elem_a);
  gt_ensure(had_err, gt_dlist_size(dlist) == 1);
  gt_ensure(had_err,
         elem_a == *(int*) gt_dlistelem_get_data(gt_dlist_first(dlist)));
  gt_dlist_delete(dlist);

  /* boundary case: dlist containing two elements */
  dlist = gt_dlist_new(intcompare);
  gt_dlist_add(dlist, &elem_a);
  gt_dlist_add(dlist, &elem_b);
  gt_ensure(had_err, gt_dlist_size(dlist) == 2);
  gt_ensure(had_err,
         elem_b == *(int*) gt_dlistelem_get_data(gt_dlist_first(dlist)));
  gt_dlist_delete(dlist);

  dlist = gt_dlist_new(NULL);
  gt_dlist_add(dlist, &elem_a);
  gt_dlist_add(dlist, &elem_b);
  gt_ensure(had_err, gt_dlist_size(dlist) == 2);
  gt_ensure(had_err,
         elem_a == *(int*) gt_dlistelem_get_data(gt_dlist_first(dlist)));
  gt_dlist_delete(dlist);

  for (i = 0; i < NUM_OF_TESTS && !had_err; i++) {
    /* construct the random elements for the list */
    size = gt_rand_max(MAX_SIZE);
    for (j = 0; j < size; j++) {
      elems[j] = gt_rand_max(INT_MAX);
      elems_backup[j] = elems[j];
    }

    /* sort the backup elements */
    qsort(elems_backup, size, sizeof (int), intcompare);

    /* test with compare function */
    dlist = gt_dlist_new(intcompare);
    gt_ensure(had_err, !gt_dlist_size(dlist));
    for (j = 0; j < size && !had_err; j++) {
      gt_dlist_add(dlist, elems + j);
      gt_ensure(had_err, gt_dlist_size(dlist) == j+1);

      for (dlistelem = gt_dlist_first(dlist); dlistelem != NULL;
           dlistelem = gt_dlistelem_next(dlistelem)) {
      }
    }
    j = 0;
    for (dlistelem = gt_dlist_first(dlist); dlistelem != NULL;
         dlistelem = gt_dlistelem_next(dlistelem)) {
      data = gt_dlistelem_get_data(dlistelem);
      gt_ensure(had_err, *data == elems_backup[j]);
      j++;
    }
    /* test gt_dlist_find() */
    for (j = 0; j < size; j++) {
      dlistelem = gt_dlist_find(dlist, elems_backup + j);
      gt_ensure(had_err, dlistelem);
      gt_ensure(had_err,
             *(int*) gt_dlistelem_get_data(dlistelem) == elems_backup[j]);
    }
    /* remove first element */
    if (gt_dlist_size(dlist)) {
      gt_dlist_remove(dlist, gt_dlist_first(dlist));
      if (gt_dlist_size(dlist)) {
        data = gt_dlistelem_get_data(gt_dlist_first(dlist));
        gt_ensure(had_err, *data == elems_backup[1]);
      }
    }
    /* remove last element */
    if (gt_dlist_size(dlist)) {
      gt_dlist_remove(dlist, gt_dlist_last(dlist));
      if (gt_dlist_size(dlist)) {
        data = gt_dlistelem_get_data(gt_dlist_last(dlist));
        gt_ensure(had_err, *data == elems_backup[size - 2]);
      }
    }
    /* XXX: fix this */
#if 0
    /* remove middle element */
    if (gt_dlist_size(dlist) >= 2) {
      dlistelem = gt_dlist_first(dlist);
      for (j = 1; j < gt_dlist_size(dlist) / 2; j++)
        dlistelem = gt_dlistelem_next(dlistelem);
      gt_dlist_remove(dlist, dlistelem);
      dlistelem = gt_dlist_first(dlist);
      for (j = 1; j < gt_dlist_size(dlist) / 2 + 1; j++)
        dlistelem = gt_dlistelem_next(dlistelem);
      data = gt_dlistelem_get_data(gt_dlist_last(dlist));
      gt_ensure(had_err, *data == elems_backup[size / 2 + 1]);
    }
#endif
    gt_dlist_delete(dlist);

    /* test without compare function */
    dlist = gt_dlist_new(NULL);
    gt_ensure(had_err, !gt_dlist_size(dlist));
    for (j = 0; j < size && !had_err; j++) {
      gt_dlist_add(dlist, elems + j);
      gt_ensure(had_err, gt_dlist_size(dlist) == j+1);
    }
    j = 0;
    for (dlistelem = gt_dlist_first(dlist); dlistelem != NULL;
         dlistelem = gt_dlistelem_next(dlistelem)) {
      data = gt_dlistelem_get_data(dlistelem);
      gt_assert(j < MAX_SIZE);
      gt_ensure(had_err, *data == elems[j]);
      j++;
    }
    /* remove first element */
    if (gt_dlist_size(dlist)) {
      gt_dlist_remove(dlist, gt_dlist_first(dlist));
      if (gt_dlist_size(dlist)) {
        data = gt_dlistelem_get_data(gt_dlist_first(dlist));
        gt_ensure(had_err, *data == elems[1]);
      }
    }
    /* remove last element */
    if (gt_dlist_size(dlist)) {
      gt_dlist_remove(dlist, gt_dlist_last(dlist));
      if (gt_dlist_size(dlist)) {
        data = gt_dlistelem_get_data(gt_dlist_last(dlist));
        gt_ensure(had_err, *data == elems[size - 2]);
      }
    }
    gt_dlist_delete(dlist);
  }

  return had_err;
}