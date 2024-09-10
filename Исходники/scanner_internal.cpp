void
_gmx_sel_lexer_rethrow_exception_if_occurred(yyscan_t scanner)
{
    gmx_sel_lexer_t *state = _gmx_sel_yyget_extra(scanner);
    if (state->exception)
    {
        boost::exception_ptr ex = state->exception;
        state->exception = boost::exception_ptr();
        rethrow_exception(ex);
    }
}