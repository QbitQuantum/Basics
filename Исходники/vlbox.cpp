void wxVListBox::DoHandleItemClick(int item, int flags)
{
    // has anything worth telling the client code about happened?
    bool notify = false;

    if ( HasMultipleSelection() )
    {
        // select the iteem clicked?
        bool select = true;

        // NB: the keyboard interface we implement here corresponds to
        //     wxLB_EXTENDED rather than wxLB_MULTIPLE but this one makes more
        //     sense IMHO
        if ( flags & ItemClick_Shift )
        {
            if ( m_current != wxNOT_FOUND )
            {
                if ( m_anchor == wxNOT_FOUND )
                    m_anchor = m_current;

                select = false;

                // only the range from the selection anchor to new m_current
                // must be selected
                if ( DeselectAll() )
                    notify = true;

                if ( SelectRange(m_anchor, item) )
                    notify = true;
            }
            //else: treat it as ordinary click/keypress
        }
        else // Shift not pressed
        {
            m_anchor = item;

            if ( flags & ItemClick_Ctrl )
            {
                select = false;

                if ( !(flags & ItemClick_Kbd) )
                {
                    Toggle(item);

                    // the status of the item has definitely changed
                    notify = true;
                }
                //else: Ctrl-arrow pressed, don't change selection
            }
            //else: behave as in single selection case
        }

        if ( select )
        {
            // make the clicked item the only selection
            if ( DeselectAll() )
                notify = true;

            if ( Select(item) )
                notify = true;
        }
    }

    // in any case the item should become the current one
    if ( DoSetCurrent(item) )
    {
        if ( !HasMultipleSelection() )
        {
            // this has also changed the selection for single selection case
            notify = true;
        }
    }

    if ( notify )
    {
        // notify the user about the selection change
        SendSelectedEvent();
    }
    //else: nothing changed at all
}