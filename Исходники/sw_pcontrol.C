ProcDebug::ProcDebug(Process::ptr p) :
   ProcessState(p->getPid()),
   proc(p)
{
}