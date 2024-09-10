void CNSToolbar2::MoveButton(int nIndex)
{
    ASSERT(nIndex >= 0 && nIndex <m_nNumButtons);

    COleDataSource * pDataSource = new COleDataSource;


    m_pButtonArray[nIndex]->FillInOleDataSource(pDataSource);

    CToolbarButton *pButton = m_pButtonArray[nIndex];

    // Don't start drag until outside this rect

    RECT rectDragStart;
    pButton->GetClientRect(&rectDragStart);
    pButton->MapWindowPoints(this, &rectDragStart);

    DROPEFFECT effect;
    CToolbarDropSource * pDropSource = new CToolbarDropSource;

    effect=pDataSource->DoDragDrop(DROPEFFECT_COPY | DROPEFFECT_LINK | DROPEFFECT_MOVE | DROPEFFECT_SCROLL | DROPEFFECT_NONE,
                                   &rectDragStart, pDropSource);


    delete pDropSource;
    delete pDataSource;

}