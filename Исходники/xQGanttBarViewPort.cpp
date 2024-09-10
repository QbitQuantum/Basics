void
xQGanttBarViewPort::deleteSelectedItems()
{
#ifdef _DEBUG_
    printf("-> xQGanttBarViewPort::deleteSelectedItems()\n");
#endif

    QPtrList<KGanttItem> list;
    observeList(&list);

    getSelectedItems(_toplevelitem, list);

    for(KGanttItem *subitem = list.first();
            subitem != 0;
            subitem = list.next())
    {
#ifdef _DEBUG_
        printf(" : %s \n", subitem->getText().latin1());
#endif
        connect(subitem, SIGNAL(destroyed(KGanttItem *)),
                this, SLOT(itemDestroyed(KGanttItem *)));
    }

    list.remove(_toplevelitem);

    while(list.count() > 0)
    {
        KGanttItem *item = list.getFirst();
        delete item;
    }

#ifdef _DEBUG_
    printf("<- xQGanttBarViewPort::deleteSelectedItems()\n");
#endif
}