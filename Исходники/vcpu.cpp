    int VCPU::print_state(FILE * o) const
    {
        int len = 0;

        if ( ! this->is_online() )
            return len + FPUTS("\tVCPU Offline\n\n", o);

        if ( this->flags & CPU_PV_COMPAT )
            return len + this->print_state_compat(o);

        if ( this->flags & CPU_GP_REGS )
        {
            len += FPRINTF(o, "\tRIP:    %04x:[<%016"PRIx64">] Ring %d\n",
                           this->regs.cs, this->regs.rip, this->regs.cs & 0x3);
            len += FPRINTF(o, "\tRFLAGS: %016"PRIx64" ", this->regs.rflags);
            len += print_rflags(o, this->regs.rflags);
            len += FPUTS("\n\n", o);

            len += FPRINTF(o, "\trax: %016"PRIx64"   rbx: %016"PRIx64"   rcx: %016"PRIx64"\n",
                           this->regs.rax, this->regs.rbx, this->regs.rcx);
            len += FPRINTF(o, "\trdx: %016"PRIx64"   rsi: %016"PRIx64"   rdi: %016"PRIx64"\n",
                           this->regs.rdx, this->regs.rsi, this->regs.rdi);
            len += FPRINTF(o, "\trbp: %016"PRIx64"   rsp: %016"PRIx64"   r8:  %016"PRIx64"\n",
                           this->regs.rbp, this->regs.rsp, this->regs.r8);
            len += FPRINTF(o, "\tr9:  %016"PRIx64"   r10: %016"PRIx64"   r11: %016"PRIx64"\n",
                           this->regs.r9,  this->regs.r10, this->regs.r11);
            len += FPRINTF(o, "\tr12: %016"PRIx64"   r13: %016"PRIx64"   r14: %016"PRIx64"\n",
                           this->regs.r12, this->regs.r13, this->regs.r14);
            len += FPRINTF(o, "\tr15: %016"PRIx64"\n",
                           this->regs.r15);
        }

        if ( this->flags & CPU_CR_REGS )
        {
            len += FPUTS("\n", o);
            len += FPRINTF(o, "\tcr3: %016"PRIx64"\n", this->regs.cr3);
        }

        if ( this->flags & CPU_GP_REGS )
        {
            len += FPUTS("\n", o);

            if ( this->flags & CPU_SEG_REGS )
                len += FPRINTF(o, "\tds: %04"PRIx16"   es: %04"PRIx16"   "
                               "fs: %04"PRIx16"   gs: %04"PRIx16"   "
                               "ss: %04"PRIx16"   cs: %04"PRIx16"\n",
                               this->regs.ds, this->regs.es, this->regs.fs,
                               this->regs.gs, this->regs.ss, this->regs.cs);
            else
                len += FPRINTF(o, "\tss: %04"PRIx16"   cs: %04"PRIx16"\n",
                               this->regs.ss, this->regs.cs);
        }

        len += FPUTS("\n", o);

        len += FPRINTF(o, "\tPause Count: %"PRId32", Flags: 0x%"PRIx32" ",
                       this->pause_count, this->pause_flags);
        len += print_pause_flags(o, this->pause_flags);
        len += FPUTS("\n", o);

        switch ( this->runstate )
        {
        case RST_NONE:
            len += FPRINTF(o, "\tNot running:  Last run on PCPU%"PRIu32"\n", this->processor);
            break;
        case RST_RUNNING:
            len += FPRINTF(o, "\tCurrently running on PCPU%"PRIu32"\n", this->processor);
            break;
        case RST_CTX_SWITCH:
            len += FPUTS("\tBeing Context Switched:  State unreliable\n", o);
            break;
        default:
            len += FPUTS("\tUnknown runstate\n", o);
            break;
        }
        len += FPRINTF(o, "\tStruct vcpu at %016"PRIx64"\n", this->vcpu_ptr);

        len += FPUTS("\n", o);

        if ( this->flags & CPU_GP_REGS &&
             this->flags & CPU_CR_REGS &&
             ( this->paging_support == VCPU::PAGING_NONE ||
               this->paging_support == VCPU::PAGING_SHADOW )
            )
        {
            len += FPRINTF(o, "\tStack at %16"PRIx64":", this->regs.rsp);
            len += print_64bit_stack(o, *this->dompt, this->regs.rsp);

            len += FPUTS("\n\tCode:\n", o);
            len += print_code(o, *this->dompt, this->regs.rip);

            len += FPUTS("\n\tCall Trace:\n", o);
            if ( this->domid == 0 )
            {
                vaddr_t sp = this->regs.rsp;
                vaddr_t top = (this->regs.rsp | (PAGE_SIZE-1))+1;
                uint64_t val;

                len += host.dom0_symtab.print_symbol64(o, this->regs.rip, true);

                try
                {
                    while ( sp < top )
                    {
                        memory.read64_vaddr(*this->dompt, sp, val);
                        len += host.dom0_symtab.print_symbol64(o, val);
                        sp += 8;
                    }
                }
                catch ( const CommonError & e )
                {
                    e.log();
                }
            }
            else
                len += FPUTS("\t  No symbol table for domain\n", o);

            len += FPUTS("\n", o);
        }
        return len;
    }