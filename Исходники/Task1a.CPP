CTaskStk *TaskStkNew(I64 stk_size,CTask *task)
{
    CTaskStk *temps=MAlloc(stk_size+offset(CTaskStk.stk_base),task);
    temps->next_stk=NULL;
    temps->stk_ptr=NULL;
    temps->stk_size=MSize(temps)-offset(CTaskStk.stk_base);
    return temps;
}