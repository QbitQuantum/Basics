int
l3CreateByObjInfo( rsComm_t *rsComm, dataObjInp_t *dataObjInp,
                   dataObjInfo_t *dataObjInfo ) {

    int chkType = 0; // JMC - backport 4774

    // =-=-=-=-=-=-=-
    // extract the host location from the resource hierarchy
    std::string location;
    irods::error ret = irods::get_loc_for_hier_string( dataObjInfo->rescHier, location );
    if ( !ret.ok() ) {
        irods::log( PASSMSG( "l3CreateByObjInfo - failed in get_loc_for_hier_string", ret ) );
        return -1;
    }


    fileCreateInp_t fileCreateInp;
    memset( &fileCreateInp, 0, sizeof( fileCreateInp ) );
    rstrcpy( fileCreateInp.resc_name_, location.c_str(),      MAX_NAME_LEN );
    rstrcpy( fileCreateInp.resc_hier_, dataObjInfo->rescHier, MAX_NAME_LEN );
    rstrcpy( fileCreateInp.objPath,    dataObjInfo->objPath,  MAX_NAME_LEN );
    rstrcpy( fileCreateInp.addr.hostAddr, location.c_str(), NAME_LEN );

    rstrcpy( fileCreateInp.fileName, dataObjInfo->filePath, MAX_NAME_LEN );
    fileCreateInp.mode = getFileMode( dataObjInp );
    // =-=-=-=-=-=-=-
    // JMC - backport 4774
    chkType = getchkPathPerm( rsComm, dataObjInp, dataObjInfo );
    if ( chkType == DISALLOW_PATH_REG ) {
        clearKeyVal( &fileCreateInp.condInput );
        return PATH_REG_NOT_ALLOWED;
    }
    else if ( chkType == NO_CHK_PATH_PERM ) {
        fileCreateInp.otherFlags |= NO_CHK_PERM_FLAG;  // JMC - backport 4758
    }
    rstrcpy( fileCreateInp.in_pdmo, dataObjInfo->in_pdmo, MAX_NAME_LEN );

    //loop until we find a valid filename
    int retryCnt = 0;
    int l3descInx;
    do {
        fileCreateOut_t* create_out = NULL;
        l3descInx = rsFileCreate( rsComm, &fileCreateInp, &create_out );

        // update the dataObjInfo with the potential changes made by the resource - hcj
        if ( create_out != NULL ) {
            rstrcpy( dataObjInfo->rescHier, fileCreateInp.resc_hier_, MAX_NAME_LEN );
            rstrcpy( dataObjInfo->filePath, create_out->file_name, MAX_NAME_LEN );
            free( create_out );
        }

        //update the filename in case of a retry
        rstrcpy( fileCreateInp.fileName, dataObjInfo->filePath, MAX_NAME_LEN );
        retryCnt++;
    }
    while ( getErrno( l3descInx ) == EEXIST &&
            resolveDupFilePath( rsComm, dataObjInfo, dataObjInp ) >= 0 &&
            l3descInx <= 2 && retryCnt < 100 );
    clearKeyVal( &fileCreateInp.condInput );
    return l3descInx;
}