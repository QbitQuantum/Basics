MODULE::MODULE( const MODULE& aModule ) :
    BOARD_ITEM( aModule )
{
    m_Pos = aModule.m_Pos;
    m_fpid = aModule.m_fpid;
    m_Layer  = aModule.m_Layer;
    m_Attributs = aModule.m_Attributs;
    m_ModuleStatus = aModule.m_ModuleStatus;
    m_Orient = aModule.m_Orient;
    m_BoundaryBox = aModule.m_BoundaryBox;
    m_CntRot90 = aModule.m_CntRot90;
    m_CntRot180 = aModule.m_CntRot180;
    m_LastEditTime = aModule.m_LastEditTime;
    m_Link = aModule.m_Link;
    m_Path = aModule.m_Path;              //is this correct behavior?

    m_LocalClearance = aModule.m_LocalClearance;
    m_LocalSolderMaskMargin = aModule.m_LocalSolderMaskMargin;
    m_LocalSolderPasteMargin = aModule.m_LocalSolderPasteMargin;
    m_LocalSolderPasteMarginRatio = aModule.m_LocalSolderPasteMarginRatio;
    m_ZoneConnection = aModule.m_ZoneConnection;
    m_ThermalWidth = aModule.m_ThermalWidth;
    m_ThermalGap = aModule.m_ThermalGap;

    // Copy reference and value.
    m_Reference = new TEXTE_MODULE( *aModule.m_Reference );
    m_Reference->SetParent( this );

    m_Value = new TEXTE_MODULE( *aModule.m_Value );
    m_Value->SetParent( this );

    // Copy auxiliary data: Pads
    for( D_PAD* pad = aModule.m_Pads;  pad;  pad = pad->Next() )
    {
        D_PAD* newpad = new D_PAD( *pad );
        assert( newpad->GetNet() == pad->GetNet() );
        newpad->SetParent( this );
        m_Pads.PushBack( newpad );
    }

    // Copy auxiliary data: Drawings
    for( BOARD_ITEM* item = aModule.m_Drawings;  item;  item = item->Next() )
    {
        BOARD_ITEM* newItem;

        switch( item->Type() )
        {
        case PCB_MODULE_TEXT_T:
        case PCB_MODULE_EDGE_T:
            newItem = static_cast<BOARD_ITEM*>( item->Clone() );
            newItem->SetParent( this );
            m_Drawings.PushBack( newItem );
            break;

        default:
            wxLogMessage( wxT( "MODULE::Copy() Internal Err:  unknown type" ) );
            break;
        }
    }

    // Copy auxiliary data: 3D_Drawings info
    for( S3D_MASTER* item = aModule.m_3D_Drawings;  item;  item = item->Next() )
    {
        if( item->GetShape3DName().IsEmpty() )           // do not copy empty shapes.
            continue;

        S3D_MASTER* t3d = new S3D_MASTER( this );
        t3d->Copy( item );
        m_3D_Drawings.PushBack( t3d );
    }

    // Ensure there is at least one item in m_3D_Drawings.
    if( m_3D_Drawings.GetCount() == 0 )
        m_3D_Drawings.PushBack( new S3D_MASTER( this ) ); // push a void item

    m_Doc     = aModule.m_Doc;
    m_KeyWord = aModule.m_KeyWord;

    m_arflag = 0;

    // Ensure auxiliary data is up to date
    CalculateBoundingBox();

    m_initial_comments = aModule.m_initial_comments ?
                            new wxArrayString( *aModule.m_initial_comments ) : 0;
}