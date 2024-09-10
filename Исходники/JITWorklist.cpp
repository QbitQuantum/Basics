JITWorklist::JITWorklist()
{
    createThread("JIT Worklist Worker Thread", [this] () { runThread(); });
}