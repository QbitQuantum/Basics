KIRQL FASTCALL
KfRaiseIrql (KIRQL	NewIrql)
{
  KIRQL OldIrql;
  ULONG Flags;

  Flags = __readeflags();
  _disable();

  OldIrql = KeGetCurrentIrql ();

  if (NewIrql < OldIrql)
    {
      DPRINT1 ("CurrentIrql %x NewIrql %x\n", KeGetCurrentIrql (), NewIrql);
      ASSERT(FALSE);
    }


  if (NewIrql > DISPATCH_LEVEL)
    {
      APICWrite (APIC_TPR, IRQL2TPR(NewIrql) & APIC_TPR_PRI);
    }
  KeSetCurrentIrql (NewIrql);
  if (Flags & EFLAGS_INTERRUPT_MASK)
    {
      _enable();
    }

  return OldIrql;
}