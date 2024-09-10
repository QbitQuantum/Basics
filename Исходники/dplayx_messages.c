/* DP messaging stuff */
static HANDLE DP_MSG_BuildAndLinkReplyStruct( IDirectPlayImpl *This,
        DP_MSG_REPLY_STRUCT_LIST *lpReplyStructList, WORD wReplyCommandId )
{
  lpReplyStructList->replyExpected.hReceipt       = CreateEventW( NULL, FALSE, FALSE, NULL );
  lpReplyStructList->replyExpected.wExpectedReply = wReplyCommandId;
  lpReplyStructList->replyExpected.lpReplyMsg     = NULL;
  lpReplyStructList->replyExpected.dwMsgBodySize  = 0;

  /* Insert into the message queue while locked */
  EnterCriticalSection( &This->lock );
    DPQ_INSERT( This->dp2->repliesExpected, lpReplyStructList, repliesExpected );
  LeaveCriticalSection( &This->lock );

  return lpReplyStructList->replyExpected.hReceipt;
}