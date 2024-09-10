void goto_symext::dereference(
  exprt &expr,
  statet &state,
  const bool write)
{
  // The expression needs to be renamed to level 1
  // in order to distinguish addresses of local variables
  // from different frames. Would be enough to rename
  // symbols whose address is taken.
  assert(!state.call_stack().empty());
  state.rename(expr, ns, goto_symex_statet::L1);

  // start the recursion!
  guardt guard;
  dereference_rec(expr, state, guard, write);
  // dereferencing may introduce new symbol_exprt
  // (like __CPROVER_memory)
  state.rename(expr, ns, goto_symex_statet::L1);
}