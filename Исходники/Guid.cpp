void cguid::toString( wxString& strGUID  )
{
    strGUID.Printf( _( "%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X" ),
                    m_id[0], m_id[1], m_id[2], m_id[3],
                    m_id[4], m_id[5], m_id[6], m_id[7],
                    m_id[8], m_id[9], m_id[10], m_id[11],
                    m_id[12], m_id[13], m_id[14], m_id[15] );
}