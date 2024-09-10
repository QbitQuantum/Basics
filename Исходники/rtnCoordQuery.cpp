   INT32 rtnCoordQuery::executeQuery( CHAR *pSrc ,
                                      BSONObj &boQuery ,
                                      BSONObj &boOrderBy ,
                                      const CHAR * pCollectionName ,
                                      netMultiRouteAgent *pRouteAgent ,
                                      pmdEDUCB *cb ,
                                      rtnContextCoord *&pContext )
   {
      SDB_ASSERT( pSrc, "pSrc can't be null!" ) ;
      SDB_ASSERT( pCollectionName, "pCollectionName can't be null!" ) ;
      INT32 rc = SDB_OK ;
      SINT64 contextID = -1 ;
      BOOLEAN isNeedRefresh = FALSE ;
      BOOLEAN hasRetry = FALSE ;
      CoordCataInfoPtr cataInfo ;
      CoordGroupList sendGroupList ;
      MsgOpQuery *pQuery = (MsgOpQuery *)pSrc ;
      SDB_RTNCB *pRtncb = pmdGetKRCB()->getRTNCB() ;
      rc = pRtncb->contextNew( RTN_CONTEXT_COORD,
                               (rtnContext **)&pContext,
                               contextID, cb ) ;
      PD_RC_CHECK( rc, PDERROR, "Failed to allocate context(rc=%d)", rc ) ;

      if ( FLG_QUERY_EXPLAIN & pQuery->flags )
      {
         rc = pContext->open( BSONObj(), -1, 0 ) ;
      }
      else
      {
         rc = pContext->open( boOrderBy, pQuery->numToReturn,
                              pQuery->numToSkip ) ;
      }
      PD_RC_CHECK( rc, PDERROR, "Open context failed(rc=%d)", rc ) ;
      pQuery->header.routeID.value = 0;
      pQuery->header.TID = cb->getTID();
      if ( pQuery->numToReturn > 0 && pQuery->numToSkip > 0 )
      {
         pQuery->numToReturn += pQuery->numToSkip ;
      }
      pQuery->numToSkip = 0 ;

   retry:
      rc = rtnCoordGetCataInfo( cb, pCollectionName,
                                isNeedRefresh, cataInfo ) ;
      PD_RC_CHECK( rc, PDERROR,
                   "Failed to get the catalog info(collection:%s)",
                   pCollectionName ) ;
      pQuery->version = cataInfo->getVersion() ;
      if ( cataInfo->isMainCL() )
      {
         CoordSubCLlist subCLList ;
         CoordGroupSubCLMap groupSubCLMap ;
         rc = cataInfo->getMatchSubCLs( boQuery, subCLList ) ;
         PD_CHECK( SDB_OK == rc, rc, retry_check, PDWARNING,
                   "Failed to get match sub collection(rc=%d)",
                   rc ) ;
         rc = rtnCoordGetSubCLsByGroups( subCLList, sendGroupList,
                                         cb, groupSubCLMap ) ;
         PD_CHECK( SDB_OK == rc, rc, retry_check, PDWARNING,
                   "Failed to get sub-collection info(rc=%d)",
                   rc );
         rc = queryOnMainCL( groupSubCLMap, pQuery, cb, pRouteAgent,
                             sendGroupList, pContext ) ;
         PD_CHECK( SDB_OK == rc, rc, retry_check, PDWARNING,
                   "Query on main collection failed(rc=%d)",
                   rc );
      }
      else
      {
         CoordGroupList groupList ;
         rc = getNodeGroups( cataInfo, boQuery,
                             sendGroupList, groupList ) ;
         PD_CHECK( SDB_OK == rc, rc, retry_check, PDWARNING,
                   "Failed to get match sharding(rc=%d)",
                   rc ) ;
         rc = queryToDataNodeGroup( pSrc, groupList, sendGroupList,
                                    pRouteAgent, cb, pContext ) ;
         PD_CHECK( SDB_OK == rc, rc, retry_check, PDWARNING,
                   "Query on data node failed(rc=%d)",
                   rc ) ;
      }

   retry_check:
      if ( rc != SDB_OK )
      {
         if ( rc != SDB_APP_INTERRUPT && !hasRetry )
         {
            hasRetry = TRUE ;
            isNeedRefresh = TRUE ;
            goto retry ;
         }
         goto error ;
      }
   done:
      return rc ;
   error:
      if ( SDB_CAT_NO_MATCH_CATALOG == rc )
      {
         rc = SDB_OK ;
         goto done ;
      }
      if ( contextID >= 0 )
      {
         pRtncb->contextDelete( contextID, cb ) ;
         contextID = -1 ;
         pContext = NULL ;
      }
      goto done ;
   }