mozilla::TemporaryRef<LibHandle>
LoadedElf::Create(const char *path, void *base_addr)
{
  DEBUG_LOG("LoadedElf::Create(\"%s\", %p) = ...", path, base_addr);

  uint8_t mapped;
  /* If the page is not mapped, mincore returns an error. If base_addr is
   * nullptr, as would happen if the corresponding binary is prelinked with
   * the prelink look (but not with the android apriori tool), no page being
   * mapped there (right?), mincore returns an error, too, which makes
   * prelinked libraries on glibc unsupported. This is not an interesting
   * use case for now, so don't try supporting that case.
   */
  if (mincore(const_cast<void*>(base_addr), PageSize(), &mapped))
    return nullptr;

  RefPtr<LoadedElf> elf = new LoadedElf(path);

  const Ehdr *ehdr = Ehdr::validate(base_addr);
  if (!ehdr)
    return nullptr;

  Addr min_vaddr = (Addr) -1; // We want to find the lowest and biggest
  Addr max_vaddr = 0;         // virtual address used by this Elf.
  const Phdr *dyn = nullptr;
#ifdef __ARM_EABI__
  const Phdr *arm_exidx_phdr = nullptr;
#endif

  Array<Phdr> phdrs(reinterpret_cast<const char *>(ehdr) + ehdr->e_phoff,
                    ehdr->e_phnum);
  for (auto phdr = phdrs.begin(); phdr < phdrs.end(); ++phdr) {
    switch (phdr->p_type) {
      case PT_LOAD:
        if (phdr->p_vaddr < min_vaddr)
          min_vaddr = phdr->p_vaddr;
        if (max_vaddr < phdr->p_vaddr + phdr->p_memsz)
          max_vaddr = phdr->p_vaddr + phdr->p_memsz;
        break;
      case PT_DYNAMIC:
        dyn = &*phdr;
        break;
#ifdef __ARM_EABI__
      case PT_ARM_EXIDX:
        /* We cannot initialize arm_exidx here
           because we don't have a base yet */
        arm_exidx_phdr = &*phdr;
        break;
#endif
    }
  }

  /* If the lowest PT_LOAD virtual address in headers is not 0, then the ELF
   * is either prelinked or a non-PIE executable. The former case is not
   * possible, because base_addr would be nullptr and the mincore test above
   * would already have made us return.
   * For a non-PIE executable, PT_LOADs contain absolute addresses, so in
   * practice, this means min_vaddr should be equal to base_addr. max_vaddr
   * can thus be adjusted accordingly.
   */
  if (min_vaddr != 0) {
    void *min_vaddr_ptr = reinterpret_cast<void *>(
      static_cast<uintptr_t>(min_vaddr));
    if (min_vaddr_ptr != base_addr) {
      LOG("%s: %p != %p", elf->GetPath(), min_vaddr_ptr, base_addr);
      return nullptr;
    }
    max_vaddr -= min_vaddr;
  }
  if (!dyn) {
    LOG("%s: No PT_DYNAMIC segment found", elf->GetPath());
    return nullptr;
  }

  elf->base.Assign(base_addr, max_vaddr);

  if (!elf->InitDyn(dyn))
    return nullptr;

#ifdef __ARM_EABI__
  if (arm_exidx_phdr)
    elf->arm_exidx.InitSize(elf->GetPtr(arm_exidx_phdr->p_vaddr),
                            arm_exidx_phdr->p_memsz);
#endif

  DEBUG_LOG("LoadedElf::Create(\"%s\", %p) = %p", path, base_addr,
    static_cast<void *>(elf));

  ElfLoader::Singleton.Register(elf);
  return elf;
}