void Throw()
{
   for (Janitor* jan = JumpBase::jl->janitor; jan; jan = jan->NextJanitor)
      jan->CleanUp();
   JumpItem* jx = JumpBase::jl->ji;    // previous jumpbase;
   if ( !jx ) { Terminate(); }         // jl was initial JumpItem
   JumpBase::jl = jx;                  // drop down a level; cannot be in front
                                       // of previous line
   Tracer::last = JumpBase::jl->trace;
   longjmp(JumpBase::jl->env, 1);
}