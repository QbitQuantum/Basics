void ARMGNULDBackend::scanLocalReloc(Relocation& pReloc,
                                     const LDSymbol& pInputSym,
                                     MCLinker& pLinker,
                                     const MCLDInfo& pLDInfo,
                                     const Output& pOutput)
{
  // rsym - The relocation target symbol
  ResolveInfo* rsym = pReloc.symInfo();

  updateAddend(pReloc, pInputSym, pLinker.getLayout());

  switch(pReloc.type()){

    // Set R_ARM_TARGET1 to R_ARM_ABS32
    // Ref: GNU gold 1.11 arm.cc, line 9892
    case llvm::ELF::R_ARM_TARGET1:
       pReloc.setType(llvm::ELF::R_ARM_ABS32);
    case llvm::ELF::R_ARM_ABS32:
    case llvm::ELF::R_ARM_ABS32_NOI: {
      // If buiding PIC object (shared library or PIC executable),
      // a dynamic relocations with RELATIVE type to this location is needed.
      // Reserve an entry in .rel.dyn
      if(isPIC(pLDInfo, pOutput)) {
        // create .rel.dyn section if not exist
        if(NULL == m_pRelDyn)
          createARMRelDyn(pLinker, pOutput);
        m_pRelDyn->reserveEntry(*m_pRelocFactory);
        // set Rel bit
        rsym->setReserved(rsym->reserved() | 0x1u);
        }
      return;
    }

    case llvm::ELF::R_ARM_ABS16:
    case llvm::ELF::R_ARM_ABS12:
    case llvm::ELF::R_ARM_THM_ABS5:
    case llvm::ELF::R_ARM_ABS8:
    case llvm::ELF::R_ARM_BASE_ABS:
    case llvm::ELF::R_ARM_MOVW_ABS_NC:
    case llvm::ELF::R_ARM_MOVT_ABS:
    case llvm::ELF::R_ARM_THM_MOVW_ABS_NC:
    case llvm::ELF::R_ARM_THM_MOVT_ABS: {
      // Update value keep in relocation place if we meet a section symbol
      if(rsym->type() == ResolveInfo::Section) {
        pReloc.target() = pLinker.getLayout().getOutputOffset(
                            *pInputSym.fragRef()) + pReloc.target();
      }

      // If building PIC object (shared library or PIC executable),
      // a dynamic relocation for this location is needed.
      // Reserve an entry in .rel.dyn
      if(isPIC(pLDInfo, pOutput)) {
        checkValidReloc(pReloc, pLDInfo, pOutput);
        // create .rel.dyn section if not exist
        if(NULL == m_pRelDyn)
          createARMRelDyn(pLinker, pOutput);
        m_pRelDyn->reserveEntry(*m_pRelocFactory);
        // set Rel bit
        rsym->setReserved(rsym->reserved() | 0x1u);
      }
      return;
    }
    case llvm::ELF::R_ARM_GOTOFF32:
    case llvm::ELF::R_ARM_GOTOFF12: {
      // A GOT section is needed
      if(NULL == m_pGOT)
        createARMGOT(pLinker, pOutput);
      return;
    }

    // Set R_ARM_TARGET2 to R_ARM_GOT_PREL
    // Ref: GNU gold 1.11 arm.cc, line 9892
    case llvm::ELF::R_ARM_TARGET2:
      pReloc.setType(llvm::ELF::R_ARM_GOT_PREL);
    case llvm::ELF::R_ARM_GOT_BREL:
    case llvm::ELF::R_ARM_GOT_PREL: {
      // A GOT entry is needed for these relocation type.
      // return if we already create GOT for this symbol
      if(rsym->reserved() & 0x6u)
        return;
      if(NULL == m_pGOT)
        createARMGOT(pLinker, pOutput);
      m_pGOT->reserveEntry();
      // If building PIC object, a dynamic relocation with
      // type RELATIVE is needed to relocate this GOT entry.
      // Reserve an entry in .rel.dyn
      if(isPIC(pLDInfo, pOutput)) {
        // create .rel.dyn section if not exist
        if(NULL == m_pRelDyn)
          createARMRelDyn(pLinker, pOutput);
        m_pRelDyn->reserveEntry(*m_pRelocFactory);
        // set GOTRel bit
        rsym->setReserved(rsym->reserved() | 0x4u);
        return;
      }
      // set GOT bit
      rsym->setReserved(rsym->reserved() | 0x2u);
      return;
    }

    case llvm::ELF::R_ARM_BASE_PREL: {
      // FIXME: Currently we only support R_ARM_BASE_PREL against
      // symbol _GLOBAL_OFFSET_TABLE_
      if(rsym != m_pGOTSymbol->resolveInfo()) {
        llvm::report_fatal_error(llvm::Twine("Do not support relocation '") +
                                 llvm::Twine("R_ARM_BASE_PREL' against symbol '") +
                                 llvm::Twine(rsym->name()) +
                                 llvm::Twine(".'"));
      }
      return;
    }
    case llvm::ELF::R_ARM_COPY:
    case llvm::ELF::R_ARM_GLOB_DAT:
    case llvm::ELF::R_ARM_JUMP_SLOT:
    case llvm::ELF::R_ARM_RELATIVE: {
      // These are relocation type for dynamic linker, shold not
      // appear in object file.
      llvm::report_fatal_error(llvm::Twine("unexpected reloc ") +
                               llvm::Twine((int)pReloc.type()) +
                               llvm::Twine(" in object file"));
      break;
    }
    default: {
      break;
    }
  } // end switch
}