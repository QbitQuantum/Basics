WORD WaitCo(word arg)
{ Coroutine	*current	= CurrentCo;

  Dbg(("WaitCo: CurrentCo is %x, parent is %x", CurrentCo, CurrentCo->Parent));
  CurrentCo	= current->Parent;
  Arg		= arg;

  Dbg(("WaitCo: saving current state in %x", current->JmpBuf));
  if (_setjmp(current->JmpBuf, 0) == 0)
   { Dbg(("WaitCo: jumping to parent coroutine via %x", CurrentCo->JmpBuf));
     _longjmp(CurrentCo->JmpBuf, 1);
   }
  else
   return(Arg);
}