/////////////////////////////////////////////////////////////////////////////
//++
//
//  CBasePropertyPage::BSetPrivateProps
//
//  Description:
//      Set the private properties for this object.
//
//  Arguments:
//      fValidateOnlyIn
//          TRUE = only validate the data.
//
//      fNoNewPropsIn
//          TRUE = exclude properties marked with opfNew.
//
//  Return Value:
//      ERROR_SUCCESS
//          The operation was completed successfully.
//
//      Other Win32 values.
//          Failure.
//
//--
/////////////////////////////////////////////////////////////////////////////
BOOL
CBasePropertyPage::BSetPrivateProps(
      BOOL fValidateOnlyIn   // = FALSE
    , BOOL fNoNewPropsIn     // = FALSE
    )
{
    BOOL            fSuccess   = TRUE;
    CClusPropList   cpl( BWizard() /*bAlwaysAddProp*/ );

    ASSERT( Peo() != NULL );
    ASSERT( Peo()->PodObjData() );

    //
    //  Build the property list.
    //

    try
    {
        fSuccess = BBuildPropList( cpl, fNoNewPropsIn );
    } // try
    catch ( CException * pe )
    {
        pe->ReportError();
        pe->Delete();
        fSuccess = FALSE;
    } // catch: CException

    //
    //  Set the data.
    //

    if ( fSuccess )
    {
        if ( (cpl.PbPropList() != NULL) && (cpl.CbPropList() > 0) )
        {
            DWORD       sc = ERROR_SUCCESS;
            DWORD       dwControlCode;
            DWORD       cbProps;

            switch ( Cot() )
            {
                case CLUADMEX_OT_NODE:
                {
                    CNodeData * pcnd = reinterpret_cast< CNodeData * >( Peo()->PodObjData() );
                    ASSERT( pcnd && (pcnd->GetHNode() != NULL) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_NODE_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_NODE_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterNodeControl(
                                      pcnd->GetHNode()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                case CLUADMEX_OT_GROUP:
                {
                    CGroupData * pcgd = reinterpret_cast< CGroupData * >( Peo()->PodObjData() );
                    ASSERT( pcgd && (pcgd->GetHGroup() != NULL) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_GROUP_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_GROUP_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterGroupControl(
                                      pcgd->GetHGroup()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                case CLUADMEX_OT_RESOURCE:
                {
                    CResData * pcrd = reinterpret_cast< CResData * >( Peo()->PodObjData() );
                    ASSERT( pcrd && (pcrd->GetHResource() != NULL) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterResourceControl(
                                      pcrd->GetHResource()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                case CLUADMEX_OT_RESOURCETYPE:
                {
                    CResTypeData * pcrd = reinterpret_cast< CResTypeData * >( Peo()->PodObjData() );
                    ASSERT( pcrd && (pcrd->StrName().GetLength() > 0) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_RESOURCE_TYPE_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_RESOURCE_TYPE_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterResourceTypeControl(
                                      Hcluster()
                                    , pcrd->StrName()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                case CLUADMEX_OT_NETWORK:
                {
                    CNetworkData * pcnd = reinterpret_cast< CNetworkData * >( Peo()->PodObjData() );
                    ASSERT( pcnd && (pcnd->GetHNetwork() != NULL) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_NETWORK_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_NETWORK_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterNetworkControl(
                                      pcnd->GetHNetwork()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                case CLUADMEX_OT_NETINTERFACE:
                {
                    CNetInterfaceData * pcnd = reinterpret_cast< CNetInterfaceData * >( Peo()->PodObjData() );
                    ASSERT( pcnd && (pcnd->GetHNetInterface() != NULL) );

                    //
                    //  Determine which control code to use.
                    //

                    if ( fValidateOnlyIn )
                    {
                        dwControlCode = CLUSCTL_NETINTERFACE_VALIDATE_PRIVATE_PROPERTIES;
                    } // if: only validating data
                    else
                    {
                        dwControlCode = CLUSCTL_NETINTERFACE_SET_PRIVATE_PROPERTIES;
                    } // else: setting data

                    //
                    //  Set private properties.
                    //

                    sc = ClusterNetInterfaceControl(
                                      pcnd->GetHNetInterface()
                                    , NULL   // hNode
                                    , dwControlCode
                                    , cpl.PbPropList()
                                    , static_cast< DWORD >( cpl.CbPropList() )
                                    , NULL   // lpOutBuffer
                                    , 0      // nOutBufferSize
                                    , &cbProps
                                    );
                    break;
                } // case:

                default:
                    ASSERT( 0 );

            } // switch: object type

            //
            //  Handle errors.
            //

            if ( sc != ERROR_SUCCESS )
            {
                if ( sc == ERROR_INVALID_PARAMETER )
                {
                    if ( ! fNoNewPropsIn )
                    {
                        fSuccess = BSetPrivateProps( fValidateOnlyIn, TRUE /*fNoNewPropsIn*/ );
                    } // if: new props are allowed
                    else
                        fSuccess = FALSE;
                } // if: invalid parameter error occurred
                else
                {
                    fSuccess = FALSE;
                } // else: some other error occurred

                //
                // If an error occurred, display an error message.
                //

                if ( ! fSuccess )
                {
                    DisplaySetPropsError( sc, fValidateOnlyIn ? IDS_ERROR_VALIDATING_PROPERTIES : IDS_ERROR_SETTING_PROPERTIES );
                    if ( sc == ERROR_RESOURCE_PROPERTIES_STORED )
                    {
                        fSuccess = TRUE;
                    } // if: properties only stored
                } // if: error occurred
            } // if: error setting/validating data
        } // if: there is data to set
    } // if: no errors building the property list

    //
    //  Save data locally.
    //

    if ( ! fValidateOnlyIn && fSuccess )
    {
        //
        //  Save new values as previous values.
        //

        try
        {
            DWORD                   cprop;
            const CObjectProperty * pprop;

            for ( pprop = Pprops(), cprop = Cprops() ; cprop > 0 ; pprop++, cprop-- )
            {
                switch ( pprop->m_propFormat )
                {
                    case CLUSPROP_FORMAT_SZ:
                    case CLUSPROP_FORMAT_EXPAND_SZ:
                        ASSERT(pprop->m_value.pstr != NULL);
                        ASSERT(pprop->m_valuePrev.pstr != NULL);
                        *pprop->m_valuePrev.pstr = *pprop->m_value.pstr;
                        break;

                    case CLUSPROP_FORMAT_DWORD:
                    case CLUSPROP_FORMAT_LONG:
                        ASSERT( pprop->m_value.pdw != NULL );
                        ASSERT( pprop->m_valuePrev.pdw != NULL );
                        *pprop->m_valuePrev.pdw = *pprop->m_value.pdw;
                        break;

                    case CLUSPROP_FORMAT_BINARY:
                    case CLUSPROP_FORMAT_MULTI_SZ:
                        ASSERT( pprop->m_value.ppb != NULL );
                        ASSERT( *pprop->m_value.ppb != NULL );
                        ASSERT( pprop->m_value.pcb != NULL );
                        ASSERT( pprop->m_valuePrev.ppb != NULL );
                        ASSERT( *pprop->m_valuePrev.ppb != NULL );
                        ASSERT( pprop->m_valuePrev.pcb != NULL );
                        delete [] *pprop->m_valuePrev.ppb;
                        *pprop->m_valuePrev.ppb = new BYTE[ *pprop->m_value.pcb ];
                        CopyMemory( *pprop->m_valuePrev.ppb, *pprop->m_value.ppb, *pprop->m_value.pcb );
                        *pprop->m_valuePrev.pcb = *pprop->m_value.pcb;
                        break;

                    default:
                        ASSERT( 0 ); // don't know how to deal with this type

                } // switch: property format
            } // for: each property
        } // try
        catch ( CException * pe )
        {
            pe->ReportError();
            pe->Delete();
            fSuccess = FALSE;
        } // catch: CException
    } // if: not just validating and successful so far

    //
    // Indicate we successfully saved the properties.
    //

    if ( ! fValidateOnlyIn && fSuccess )
    {
        m_bSaved = TRUE;
    } // if: successfully saved data

    return fSuccess;

} //*** CBasePropertyPage::BSetPrivateProps