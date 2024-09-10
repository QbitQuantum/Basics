/*
 *	StartTransactionCommand
 */
void
StartTransactionCommand(void)
{
	TransactionState s = CurrentTransactionState;

	switch (s->blockState)
	{
			/*
			 * if we aren't in a transaction block, we just do our usual
			 * start transaction.
			 */
		case TBLOCK_DEFAULT:
			StartTransaction();
			break;

			/*
			 * We should never experience this -- if we do it means the
			 * BEGIN state was not changed in the previous
			 * CommitTransactionCommand().	If we get it, we print a
			 * warning and change to the in-progress state.
			 */
		case TBLOCK_BEGIN:
			elog(WARNING, "StartTransactionCommand: unexpected TBLOCK_BEGIN");
			s->blockState = TBLOCK_INPROGRESS;
			break;

			/*
			 * This is the case when are somewhere in a transaction block
			 * and about to start a new command.  For now we do nothing
			 * but someday we may do command-local resource
			 * initialization.
			 */
		case TBLOCK_INPROGRESS:
			break;

			/*
			 * As with BEGIN, we should never experience this if we do it
			 * means the END state was not changed in the previous
			 * CommitTransactionCommand().	If we get it, we print a
			 * warning, commit the transaction, start a new transaction
			 * and change to the default state.
			 */
		case TBLOCK_END:
			elog(WARNING, "StartTransactionCommand: unexpected TBLOCK_END");
			s->blockState = TBLOCK_DEFAULT;
			CommitTransaction();
			StartTransaction();
			break;

			/*
			 * Here we are in the middle of a transaction block but one of
			 * the commands caused an abort so we do nothing but remain in
			 * the abort state.  Eventually we will get to the "END
			 * TRANSACTION" which will set things straight.
			 */
		case TBLOCK_ABORT:
			break;

			/*
			 * This means we somehow aborted and the last call to
			 * CommitTransactionCommand() didn't clear the state so we
			 * remain in the ENDABORT state and maybe next time we get to
			 * CommitTransactionCommand() the state will get reset to
			 * default.
			 */
		case TBLOCK_ENDABORT:
			elog(WARNING, "StartTransactionCommand: unexpected TBLOCK_ENDABORT");
			break;
	}

	/*
	 * We must switch to TopTransactionContext before returning. This is
	 * already done if we called StartTransaction, otherwise not.
	 */
	Assert(TopTransactionContext != NULL);
	MemoryContextSwitchTo(TopTransactionContext);
}