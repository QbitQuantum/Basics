bool CBotListArray::Execute(CBotStack* &pj, CBotVar* pVar)
{
    CBotStack*    pile1 = pj->AddStack();
    CBotVar* pVar2;

    CBotInstr* p = m_expr;

    int n = 0;

    for (; p != nullptr ; n++, p = p->GetNext3b())
    {
        if (pile1->GetState() > n) continue;

        pVar2 = pVar->GetItem(n, true);

        if (pVar2 == nullptr)
        {
            pj->SetError(CBotErrOutArray, p->GetToken());
            return false;
        }
        CBotTypResult type = pVar2->GetTypResult();

        if (!p->Execute(pile1, pVar2)) return false;        // evaluate expression

        if (type.Eq(CBotTypPointer)) pVar2->SetType(type);  // keep pointer type

        pile1->IncState();
    }

    return pj->Return(pile1);
}