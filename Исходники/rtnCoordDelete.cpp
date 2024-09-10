   //PD_TRACE_DECLARE_FUNCTION ( SDB_RTNCODEL_EXECUTE, "rtnCoordDelete::execute" )
   INT32 rtnCoordDelete::execute( MsgHeader *pMsg,
                                  pmdEDUCB *cb,
                                  INT64 &contextID,
                                  rtnContextBuf *buf )
   {
      INT32 rc = SDB_OK ;
      INT32 rcTmp = SDB_OK ;
      PD_TRACE_ENTRY ( SDB_RTNCODEL_EXECUTE ) ;
      pmdKRCB *pKrcb                   = pmdGetKRCB() ;
      CoordCB *pCoordcb                = pKrcb->getCoordCB() ;
      netMultiRouteAgent *pRouteAgent  = pCoordcb->getRouteAgent() ;

      // process define
      rtnSendOptions sendOpt( TRUE ) ;
      rtnSendMsgIn inMsg( pMsg ) ;
      rtnProcessResult result ;
      ROUTE_RC_MAP nokRC ;
      result._pNokRC = &nokRC ;

      CoordCataInfoPtr cataInfo ;
      MsgRouteID errNodeID ;
      UINT64 deleteNum = 0 ;
      inMsg._pvtData = ( CHAR* )&deleteNum ;
      inMsg._pvtType = PRIVATE_DATA_NUMBERLONG ;

      BSONObj boDeletor ;

      // fill default-reply(delete success)
      MsgOpDelete *pDelMsg             = (MsgOpDelete *)pMsg ;
      INT32 oldFlag                    = pDelMsg->flags ;
      pDelMsg->flags                  |= FLG_DELETE_RETURNNUM ;
      contextID                        = -1 ;

      INT32 flag = 0;
      CHAR *pCollectionName = NULL ;
      CHAR *pDeletor = NULL ;
      CHAR *pHint = NULL ;
      rc = msgExtractDelete( (CHAR*)pMsg, &flag, &pCollectionName,
                             &pDeletor, &pHint ) ;
      if( rc )
      {
         PD_LOG( PDERROR,"Failed to parse delete request, rc: %d", rc ) ;
         pCollectionName = NULL ;
         goto error ;
      }

      try
      {
         boDeletor = BSONObj( pDeletor ) ;
      }
      catch ( std::exception &e )
      {
         PD_RC_CHECK( SDB_INVALIDARG, PDERROR,
                      "Delete failed, received unexpected error:%s",
                      e.what() ) ;
      }

      // add last op info
      MON_SAVE_OP_DETAIL( cb->getMonAppCB(), pMsg->opCode,
                          "Collection:%s, Deletor:%s, Hint:%s, "
                          "Flag:0x%08x(%u)",
                          pCollectionName,
                          boDeletor.toString().c_str(),
                          BSONObj(pHint).toString().c_str(),
                          oldFlag, oldFlag ) ;

      rc = rtnCoordGetCataInfo( cb, pCollectionName, FALSE, cataInfo ) ;
      PD_RC_CHECK( rc, PDERROR, "Delete failed, failed to get the "
                   "catalogue info(collection name: %s), rc: %d",
                   pCollectionName, rc ) ;

   retry:
      do
      {
         pDelMsg->version = cataInfo->getVersion() ;
         pDelMsg->w = 0 ;

         if ( cataInfo->isMainCL() )
         {
            rcTmp = doOpOnMainCL( cataInfo, boDeletor, inMsg, sendOpt,
                                  pRouteAgent, cb, result ) ;
         }
         else
         {
            rcTmp = doOpOnCL( cataInfo, boDeletor, inMsg, sendOpt,
                              pRouteAgent, cb, result ) ;
         }
      }while( FALSE ) ;

      if ( SDB_OK == rcTmp && nokRC.empty() )
      {
         goto done ;
      }
      else if ( checkRetryForCLOpr( rcTmp, &nokRC, inMsg.msg(),
                                    sendOpt._retryTimes,
                                    cataInfo, cb, rc, &errNodeID, TRUE ) )
      {
         nokRC.clear() ;
         ++sendOpt._retryTimes ;
         goto retry ;
      }
      else
      {
         PD_LOG( PDERROR, "Delete failed on node[%s], rc: %d",
                 routeID2String( errNodeID ).c_str(), rc ) ;
         goto error ;
      }

   done:
      if ( oldFlag & FLG_DELETE_RETURNNUM )
      {
         contextID = deleteNum ;
      }
      if ( pCollectionName )
      {
         /// AUDIT
         PD_AUDIT_OP( AUDIT_DML, MSG_BS_DELETE_REQ, AUDIT_OBJ_CL,
                      pCollectionName, rc,
                      "DeletedNum:%u, Deletor:%s, Hint:%s, Flag:0x%08x(%u)",
                      deleteNum, boDeletor.toString().c_str(),
                      BSONObj(pHint).toString().c_str(), oldFlag, oldFlag ) ;
      }
      PD_TRACE_EXITRC ( SDB_RTNCODEL_EXECUTE, rc ) ;
      return rc ;
   error:
      goto done ;
   }