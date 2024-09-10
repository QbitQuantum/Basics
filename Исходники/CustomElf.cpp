TemporaryRef<LibHandle>
CustomElf::Load(Mappable *mappable, const char *path, int flags)
{
  DEBUG_LOG("CustomElf::Load(\"%s\", 0x%x) = ...", path, flags);
  if (!mappable)
    return nullptr;
  /* Keeping a RefPtr of the CustomElf is going to free the appropriate
   * resources when returning nullptr */
  RefPtr<CustomElf> elf = new CustomElf(mappable, path);
  /* Map the first page of the Elf object to access Elf and program headers */
  Mappable1stPagePtr ehdr_raw(mappable);
  if (ehdr_raw == MAP_FAILED)
    return nullptr;

  const Ehdr *ehdr = Ehdr::validate(ehdr_raw);
  if (!ehdr)
    return nullptr;

  /* Scan Elf Program Headers and gather some information about them */
  std::vector<const Phdr *> pt_loads;
  Addr min_vaddr = (Addr) -1; // We want to find the lowest and biggest
  Addr max_vaddr = 0;         // virtual address used by this Elf.
  const Phdr *dyn = nullptr;

  const Phdr *first_phdr = reinterpret_cast<const Phdr *>(
                           reinterpret_cast<const char *>(ehdr) + ehdr->e_phoff);
  const Phdr *end_phdr = &first_phdr[ehdr->e_phnum];
#ifdef __ARM_EABI__
  const Phdr *arm_exidx_phdr = nullptr;
#endif

  for (const Phdr *phdr = first_phdr; phdr < end_phdr; phdr++) {
    switch (phdr->p_type) {
      case PT_LOAD:
        debug_phdr("PT_LOAD", phdr);
        pt_loads.push_back(phdr);
        if (phdr->p_vaddr < min_vaddr)
          min_vaddr = phdr->p_vaddr;
        if (max_vaddr < phdr->p_vaddr + phdr->p_memsz)
          max_vaddr = phdr->p_vaddr + phdr->p_memsz;
        break;
      case PT_DYNAMIC:
        debug_phdr("PT_DYNAMIC", phdr);
        if (!dyn) {
          dyn = phdr;
        } else {
          ERROR("%s: Multiple PT_DYNAMIC segments detected", elf->GetPath());
          return nullptr;
        }
        break;
      case PT_TLS:
        debug_phdr("PT_TLS", phdr);
        if (phdr->p_memsz) {
          ERROR("%s: TLS is not supported", elf->GetPath());
          return nullptr;
        }
        break;
      case PT_GNU_STACK:
        debug_phdr("PT_GNU_STACK", phdr);
// Skip on Android until bug 706116 is fixed
#ifndef ANDROID
        if (phdr->p_flags & PF_X) {
          ERROR("%s: Executable stack is not supported", elf->GetPath());
          return nullptr;
        }
#endif
        break;
#ifdef __ARM_EABI__
      case PT_ARM_EXIDX:
        /* We cannot initialize arm_exidx here
           because we don't have a base yet */
        arm_exidx_phdr = phdr;
        break;
#endif
      default:
        DEBUG_LOG("%s: Program header type #%d not handled",
                  elf->GetPath(), phdr->p_type);
    }
  }

  if (min_vaddr != 0) {
    ERROR("%s: Unsupported minimal virtual address: 0x%08" PRIxAddr,
        elf->GetPath(), min_vaddr);
    return nullptr;
  }
  if (!dyn) {
    ERROR("%s: No PT_DYNAMIC segment found", elf->GetPath());
    return nullptr;
  }

  /* Reserve enough memory to map the complete virtual address space for this
   * library.
   * As we are using the base address from here to mmap something else with
   * MAP_FIXED | MAP_SHARED, we need to make sure these mmaps will work. For
   * instance, on armv6, MAP_SHARED mappings require a 16k alignment, but mmap
   * MAP_PRIVATE only returns a 4k aligned address. So we first get a base
   * address with MAP_SHARED, which guarantees the kernel returns an address
   * that we'll be able to use with MAP_FIXED, and then remap MAP_PRIVATE at
   * the same address, because of some bad side effects of keeping it as
   * MAP_SHARED. */
  elf->base.Assign(MemoryRange::mmap(nullptr, max_vaddr, PROT_NONE,
                                     MAP_SHARED | MAP_ANONYMOUS, -1, 0));
  if ((elf->base == MAP_FAILED) ||
      (mmap(elf->base, max_vaddr, PROT_NONE,
            MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0) != elf->base)) {
    ERROR("%s: Failed to mmap", elf->GetPath());
    return nullptr;
  }

  /* Load and initialize library */
  for (std::vector<const Phdr *>::iterator it = pt_loads.begin();
       it < pt_loads.end(); ++it)
    if (!elf->LoadSegment(*it))
      return nullptr;

  /* We're not going to mmap anymore */
  mappable->finalize();

  report_mapping(const_cast<char *>(elf->GetName()), elf->base,
                 (max_vaddr + PAGE_SIZE - 1) & PAGE_MASK, 0);

  elf->l_addr = elf->base;
  elf->l_name = elf->GetPath();
  elf->l_ld = elf->GetPtr<Dyn>(dyn->p_vaddr);
  ElfLoader::Singleton.Register(elf);

  if (!elf->InitDyn(dyn))
    return nullptr;

  if (elf->has_text_relocs) {
    for (std::vector<const Phdr *>::iterator it = pt_loads.begin();
         it < pt_loads.end(); ++it)
      mprotect(PageAlignedPtr(elf->GetPtr((*it)->p_vaddr)),
               PageAlignedEndPtr((*it)->p_memsz),
               p_flags_to_mprot((*it)->p_flags) | PROT_WRITE);
  }

  if (!elf->Relocate() || !elf->RelocateJumps())
    return nullptr;

  if (elf->has_text_relocs) {
    for (std::vector<const Phdr *>::iterator it = pt_loads.begin();
         it < pt_loads.end(); ++it)
      mprotect(PageAlignedPtr(elf->GetPtr((*it)->p_vaddr)),
               PageAlignedEndPtr((*it)->p_memsz),
               p_flags_to_mprot((*it)->p_flags));
  }

  if (!elf->CallInit())
    return nullptr;

#ifdef __ARM_EABI__
  if (arm_exidx_phdr)
    elf->arm_exidx.InitSize(elf->GetPtr(arm_exidx_phdr->p_vaddr),
                            arm_exidx_phdr->p_memsz);
#endif

  elf->stats("oneLibLoaded");
  DEBUG_LOG("CustomElf::Load(\"%s\", 0x%x) = %p", path, flags,
            static_cast<void *>(elf));
  return elf;
}