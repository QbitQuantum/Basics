void CBotStack::GetRunPos(const char* &FunctionName, int &start, int &end)
{
    CBotProgram*    prog = m_prog;                        // Current program

    CBotInstr*        funct = NULL;                        // function found
    CBotInstr*        instr = NULL;                        // the highest intruction

    CBotStack*        p = this;

    while (p->m_next != NULL)
    {
        if ( p->m_instr != NULL ) instr = p->m_instr;
        if ( p->m_bFunc == 1 ) funct = p->m_instr;
        if ( p->m_next->m_prog != prog ) break ; 

        if (p->m_next2 && p->m_next2->m_state != 0) p = p->m_next2 ;
        else                                        p = p->m_next;
    }

    if ( p->m_instr != NULL ) instr = p->m_instr;
    if ( p->m_bFunc == 1 ) funct = p->m_instr;

    if ( funct == NULL ) return;

    CBotToken* t = funct->GetToken();
    FunctionName = t->GetString();

//    if ( p->m_instr != NULL ) instr = p->m_instr;

    t = instr->GetToken();
    start = t->GetStart();
    end      = t->GetEnd();
}