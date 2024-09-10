X86FuncNode* X86Compiler::addFunc(const FuncPrototype& p) {
  X86FuncNode* func = newFunc(p);

  if (func == NULL) {
    setLastError(kErrorNoHeapMemory);
    return NULL;
  }

  ASMJIT_ASSERT(_func == NULL);
  _func = func;

  addNode(func);                 // Add function node.
  addNode(func->getEntryNode()); // Add function entry.
  HLNode* cursor = getCursor();

  addNode(func->getExitNode());  // Add function exit / epilog marker.
  addNode(func->getEnd());       // Add function end.
  setCursor(cursor);

  return func;
}