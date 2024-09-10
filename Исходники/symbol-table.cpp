int SymbolTable::print_symbol32(FILE * o, const vaddr_t & addr, bool brackets) const
{
    int len = 0;

    if ( ! this->can_print )
        return 0;

    if ( ! this->is_text_symbol(addr) )
        return 0;

    SymbolTable::const_list_iter after
        = std::upper_bound(this->symbols.begin(), this->symbols.end(), addr, &SymbolTable::symcmp);

    if ( after == this->symbols.begin() ||
         after == this->symbols.end() )
        return 0;

    SymbolTable::const_list_iter before = after;
    before--;

    if ( (*before)->address <= addr && (*after)->address > addr )
    {
        len += FPUTS("\t ", o);
        if ( brackets )
            len += FPRINTF(o, "[%08"PRIx64"]", addr);
        else
            len += FPRINTF(o, " %08"PRIx64" ", addr);

        len += FPRINTF(o, " %s+%#"PRIx64"/%#"PRIx64,
                       (*before)->name,
                       addr - (*before)->address,
                       (*after)->address - (*before)->address );

        if ( ! std::strcmp((*before)->name, "hypercall_page") )
        {
            unsigned int nr = (unsigned int)((addr - (*before)->address)/32);
            len += FPRINTF(o, " (%d, %s)", nr, hypercall_name(nr));
        }

        len += FPUTS("\n", o);
    }
    else
        LOG_WARN("Strange resulting iterators printing symbol 0x%016"PRIx64"\n", addr);

    return len;
}