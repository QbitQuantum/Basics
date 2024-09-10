bool SIGfx7CacheControl::insertCacheInvalidate(MachineBasicBlock::iterator &MI,
                                               SIAtomicScope Scope,
                                               SIAtomicAddrSpace AddrSpace,
                                               Position Pos) const {
  bool Changed = false;

  MachineBasicBlock &MBB = *MI->getParent();
  DebugLoc DL = MI->getDebugLoc();

  if (Pos == Position::AFTER)
    ++MI;

  if ((AddrSpace & SIAtomicAddrSpace::GLOBAL) != SIAtomicAddrSpace::NONE) {
    switch (Scope) {
    case SIAtomicScope::SYSTEM:
    case SIAtomicScope::AGENT:
      BuildMI(MBB, MI, DL, TII->get(AMDGPU::BUFFER_WBINVL1_VOL));
      Changed = true;
      break;
    case SIAtomicScope::WORKGROUP:
    case SIAtomicScope::WAVEFRONT:
    case SIAtomicScope::SINGLETHREAD:
      // No cache to invalidate.
      break;
    default:
      llvm_unreachable("Unsupported synchronization scope");
    }
  }

  /// The scratch address space does not need the global memory cache
  /// to be flushed as all memory operations by the same thread are
  /// sequentially consistent, and no other thread can access scratch
  /// memory.

  /// Other address spaces do not hava a cache.

  if (Pos == Position::AFTER)
    --MI;

  return Changed;
}