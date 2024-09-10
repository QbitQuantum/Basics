/*
 * discard: if true, discard the payloads.  If false, enqueue the work
 */
static adlb_code
steal_payloads(int target, int count,
               int *single_count, int *par_count,
               bool discard)
{
  assert(count > 0);
  MPI_Status status;
  int length = count * (int)sizeof(struct packed_steal_work);
  struct packed_steal_work* wus = malloc((size_t)length);
  valgrind_assert(wus);
  RECV(wus, length, MPI_BYTE, target, ADLB_TAG_RESPONSE_STEAL);
  int single = 0, par = 0;
  for (int i = 0; i < count; i++)
  {
    assert(wus[i].length > 0);
    xlb_work_unit *work = work_unit_alloc((size_t)wus[i].length);
    RECV(work->payload, wus[i].length, MPI_BYTE, target,
         ADLB_TAG_RESPONSE_STEAL);
    if (!discard) {
      xlb_work_unit_init(work, wus[i].type, wus[i].putter,
                    wus[i].answer, wus[i].target, wus[i].length,
                    wus[i].opts);
      xlb_workq_add(work);
    } else {
      xlb_work_unit_free(work);
    }
    if (wus[i].opts.parallelism > 1)
    {
      par++;
    }
    else
    {
      single++;
    }
  }
  free(wus);
  DEBUG("[%i] received batch size %i", xlb_s.layout.rank, count);

  *single_count = single;
  *par_count = par;
  return ADLB_SUCCESS;
}