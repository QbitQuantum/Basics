CQueVectU8 *QueVectU8New(I64 min_index=0)
{
  CQueVectU8 *result=MAlloc(sizeof(CQueVectU8));
  result->next=result->last=result;
  result->total_cnt=result->node_cnt=0;
  result->min_index=min_index;
  return result;
}