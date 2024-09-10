bool TRACKS_CLEANER::clean_vias()
{
    TRACK* next_track;
    bool modified = false;

    for( TRACK* track = m_Brd->m_Track; track; track = track->Next() )
    {
        // Correct via m_End defects (if any)
        if( track->Type() == PCB_VIA_T )
        {
            if( track->GetStart() != track->GetEnd() )
                track->SetEnd( track->GetStart() );
        }

        if( track->GetShape() != VIA_THROUGH )
            continue;

        // Search and delete others vias at same location
        TRACK* alt_track = track->Next();

        for( ; alt_track != NULL; alt_track = next_track )
        {
            next_track = alt_track->Next();

            if( alt_track->GetShape() != VIA_THROUGH )
                continue;

            if( alt_track->GetStart() != track->GetStart() )
                continue;

            // delete via
            alt_track->UnLink();
            delete alt_track;
            modified = true;
        }
    }

    // Delete Via on pads at same location
    for( TRACK* track = m_Brd->m_Track; track != NULL; track = next_track )
    {
        next_track = track->Next();

        if( track->GetShape() != VIA_THROUGH )
            continue;

        // Examine the list of connected pads:
        // if one pad through is found, the via can be removed
        for( unsigned ii = 0; ii < track->m_PadsConnected.size(); ii++ )
        {
            D_PAD * pad = track->m_PadsConnected[ii];

            if( (pad->GetLayerMask() & ALL_CU_LAYERS) == ALL_CU_LAYERS )
            {
                // redundant: via delete it
                track->UnLink();
                delete track;
                modified = true;
                break;
            }
        }
    }

    return modified;
}