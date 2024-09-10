void NETINFO_LIST::buildPadsFullList()
{
    /*
     * initialize:
     *   m_Pads (list of pads)
     * set m_Status_Pcb = LISTE_PAD_OK;
     * also clear m_Pcb->m_FullRatsnest that could have bad data
     *   (m_Pcb->m_FullRatsnest uses pointer to pads)
     * Be aware NETINFO_ITEM* BOARD::FindNet( const wxString& aNetname )
     * when search a net by its net name does a binary search
     * and expects to have a nets list sorted by an alphabetic case sensitive sort
     * So do not change the sort function used here
     */

    if( m_Parent->m_Status_Pcb & LISTE_PAD_OK )
        return;

    // empty the old list
    m_PadsFullList.clear();
    m_Parent->m_FullRatsnest.clear();

    // Clear variables used in ratsnest computation
    for( MODULE* module = m_Parent->m_Modules;  module;  module = module->Next() )
    {
        for( D_PAD* pad = module->Pads();  pad;  pad = pad->Next() )
        {
            m_PadsFullList.push_back( pad );

            pad->SetSubRatsnest( 0 );
            pad->SetParent( module );
        }
    }

    // Sort pad list per net
    sort( m_PadsFullList.begin(), m_PadsFullList.end(), padlistSortByNetnames );

    m_Parent->m_Status_Pcb = LISTE_PAD_OK;
}