/**
@brief Helper function for replace_set()
*/
bool VarReplacer::handleUpdatedClause(XorClause& c, const Var origVar1, const Var origVar2)
{
    uint32_t origSize = c.size();
    std::sort(c.getData(), c.getDataEnd());
    Lit p;
    uint32_t i, j;
    for (i = j = 0, p = lit_Undef; i != c.size(); i++) {
        if (c[i].var() == p.var()) {
            //added, but easily removed
            j--;
            p = lit_Undef;
            if (!solver.assigns[c[i].var()].isUndef())
                c.invert(solver.assigns[c[i].var()].getBool());
        } else if (solver.assigns[c[i].var()].isUndef()) //just add
            c[j++] = p = c[i];
        else c.invert(solver.assigns[c[i].var()].getBool()); //modify xorEqualFalse instead of adding
    }
    c.shrink(i - j);

    //Even if i==j, the clause *has* changed
    c.setChanged();

    #ifdef VERBOSE_DEBUG
    cout << "xor-clause after replacing: ";
    c.plainPrint();
    #endif

    switch (c.size()) {
    case 0:
        solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
        if (!c.xorEqualFalse()) {
            solver.ok = false;
        }
        return true;
    case 1:
        solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
        solver.uncheckedEnqueue(Lit(c[0].var(), c.xorEqualFalse()));
        solver.ok = (solver.propagate<false>().isNULL());
        return true;
    case 2: {
        solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
        c[0] = c[0].unsign() ^ c.xorEqualFalse();
        c[1] = c[1].unsign();
        addBinaryXorClause(c[0], c[1]);
        return true;
    }
    default:
        solver.detachModifiedClause(origVar1, origVar2, origSize, &c);
        solver.attachClause(c);
        return false;
    }

    assert(false);
    return false;
}