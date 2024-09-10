static void
free_debug_insn_changes (struct value_data *vd, unsigned int regno)
{
  struct queued_debug_insn_change *cur, *next;
  for (cur = vd->e[regno].debug_insn_changes; cur; cur = next)
    {
      next = cur->next;
      --vd->n_debug_insn_changes;
      queued_debug_insn_change_pool.remove (cur);
    }
  vd->e[regno].debug_insn_changes = NULL;
}