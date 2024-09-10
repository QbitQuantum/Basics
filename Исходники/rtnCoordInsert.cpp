   // PD_TRACE_DECLARE_FUNCTION ( SDB_RTNCOINS_EXECUTE, "rtnCoordInsert::execute" )
   INT32 rtnCoordInsert::execute( CHAR *pReceiveBuffer,
                                  SINT32 packSize,
                                  pmdEDUCB *cb,
                                  MsgOpReply &replyHeader,
                                  rtnContextBuf *buf )
   {
      INT32 rc = SDB_OK;
      PD_TRACE_ENTRY ( SDB_RTNCOINS_EXECUTE ) ;
      pmdKRCB *pKrcb                   = pmdGetKRCB();
      CoordCB *pCoordcb                = pKrcb->getCoordCB();
      netMultiRouteAgent *pRouteAgent  = pCoordcb->getRouteAgent();
      rtnCoordOperator *pRollbackOperator = NULL;

      MsgHeader *pHeader               = (MsgHeader *)pReceiveBuffer;
      replyHeader.header.messageLength = sizeof( MsgOpReply );
      replyHeader.header.opCode        = MSG_BS_INSERT_RES;
      replyHeader.header.requestID     = pHeader->requestID;
      replyHeader.header.routeID.value = 0;
      replyHeader.header.TID           = pHeader->TID;
      replyHeader.contextID            = -1;
      replyHeader.flags                = SDB_OK;
      replyHeader.numReturned          = 0;
      replyHeader.startFrom            = 0;
      MsgOpInsert *pSrcMsg = (MsgOpInsert *)pReceiveBuffer;
      BOOLEAN isNeedRefreshCata = FALSE;
      GroupObjsMap groupObjsMap;
      BOOLEAN hasSendSomeData = FALSE;
      GroupSubCLMap groupSubCLMap;

      INT32 flag = 0;
      CHAR *pCollectionName = NULL;
      CHAR *pInsertor = NULL;
      INT32 count = 0;
      rc = msgExtractInsert( pReceiveBuffer, &flag,
                             &pCollectionName, &pInsertor, count ) ;
      PD_RC_CHECK( rc, PDERROR, "Failed to parse insert request" );
      pSrcMsg->header.TID = cb->getTID();
      if ( cb->isTransaction() )
      {
         pSrcMsg->header.opCode = MSG_BS_TRANS_INSERT_REQ;
      }
      else
      {
         pSrcMsg->header.opCode = MSG_BS_INSERT_REQ;
      }

      while ( TRUE )
      {
         CoordCataInfoPtr cataInfo;
         rc = rtnCoordGetCataInfo( cb, pCollectionName, isNeedRefreshCata,
                                   cataInfo );
         PD_RC_CHECK( rc, PDERROR,
                      "Failed to get the catalog info(collection name:%s)",
                      pCollectionName );

         pSrcMsg->header.routeID.value = 0;
         pSrcMsg->version = cataInfo->getVersion();

         if ( !cataInfo->isSharded() )
         {
            CoordGroupList groupLst;
            cataInfo->getGroupLst( groupLst );
            PD_CHECK( groupLst.size() > 0, SDB_SYS, error,
                      PDERROR, "invalid catalog-info, no group-info" );
            rc = buildTransSession( groupLst, pRouteAgent, cb );
            PD_RC_CHECK( rc, PDERROR,
                         "Failed to build transaction session(rc=%d)",
                         rc );

            CoordGroupList::iterator iterLst = groupLst.begin();
            rc = insertToAGroup( pReceiveBuffer, iterLst->first, pRouteAgent, cb );
         }//end of if ( !cataInfo->isSharded() )
         else if( !cataInfo->isMainCL() )
         {
            rc = insertToNormalCL( cataInfo, pReceiveBuffer, pInsertor,
                                   count, pRouteAgent, cb, groupObjsMap,
                                   hasSendSomeData ) ;
         }//end of else if( !cataInfo->isMainCL() )
         else
         {
            rc = insertToMainCL( cataInfo, pReceiveBuffer, pInsertor,
                                 count, pRouteAgent, cb, groupSubCLMap ) ;
         }
         if ( SDB_OK != rc )
         {
            if ( !isNeedRefreshCata
                 && ( (!cb->isTransaction() && rtnCoordWriteRetryRC( rc ))
                      || SDB_CLS_COORD_NODE_CAT_VER_OLD == rc
                      || SDB_CLS_NO_CATALOG_INFO == rc
                      || SDB_CAT_NO_MATCH_CATALOG == rc ))
            {
               isNeedRefreshCata = TRUE;
               continue;
            }
            if ( SDB_CLS_COORD_NODE_CAT_VER_OLD == rc )
            {
               rc = SDB_CAT_NO_MATCH_CATALOG;
            }
            PD_RC_CHECK ( rc, PDERROR, "Failed to insert the record to "
                          "data-node, rc = %d", rc ) ;
         }
         break;
      }
      if ( cb->isTransaction() )
      {
         rc = rc ? rc : cb->getTransRC();
      }
      if ( rc )
      {
         goto error;
      }
   done:
      PD_TRACE_EXITRC ( SDB_RTNCOINS_EXECUTE, rc ) ;
      return rc;
   error:
      if ( cb->isTransaction() )
      {
         pRollbackOperator
               = pCoordcb->getProcesserFactory()->getOperator( MSG_BS_TRANS_ROLLBACK_REQ );
         if ( pRollbackOperator )
         {
            pRollbackOperator->execute( pReceiveBuffer, packSize,
                                       cb, replyHeader, NULL );
         }
      }
      replyHeader.flags = rc;
      goto done;
   }