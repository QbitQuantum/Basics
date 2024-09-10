VOID ResumePrune(
    IN      PRPL_SESSION    pSession,
    IN      DWORD           ServerHandle
    )
/*++
    This function returns no errors, since failure to delete old resume handles
    is not considered fatal (and there is very little we can do about this).
--*/
{
    JET_ERR     JetError;

#ifdef RPL_DEBUG
    if ( RG_DebugLevel == (DWORD)(-1)) {
        ResumeList( pSession, "++ResumePrune");
    }
#endif // RPL_DEBUG
    CallR( JetSetCurrentIndex( pSession->SesId, pSession->ResumeTableId, RESUME_INDEX_ServerHandle));
    CallR( JetMakeKey( pSession->SesId, pSession->ResumeTableId, &ServerHandle,
            sizeof( ServerHandle), JET_bitNewKey));
#ifdef NOT_YET
    JetError = JetSeek( pSession->SesId, pSession->ResumeTableId, JET_bitSeekEQ);
#else
    JetError = JetSeek( pSession->SesId, pSession->ResumeTableId, JET_bitSeekEQ | JET_bitSetIndexRange);
#endif
    if ( JetError == JET_errSuccess) {
#ifdef NOT_YET
        CallR( JetMakeKey( pSession->SesId, pSession->ResumeTableId, &ServerHandle,
                sizeof( ServerHandle), JET_bitNewKey));
        CallR( JetSetIndexRange( pSession->SesId, pSession->ResumeTableId,
            JET_bitRangeInclusive | JET_bitRangeUpperLimit));
#endif
        do {
            Call( JetDelete( pSession->SesId, pSession->ResumeTableId));
            JetError = JetMove( pSession->SesId, pSession->ResumeTableId, JET_MoveNext, 0);
        } while ( JetError == JET_errSuccess);
    }
#ifdef RPL_DEBUG
    if ( RG_DebugLevel == (DWORD)(-1)) {
        ResumeList( pSession, "--ResumePrune");
    }
#endif // RPL_DEBUG
}