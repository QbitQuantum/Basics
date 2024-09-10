/**
 *	Parse a transform statement.
 *
 *	@return VMStmt *, ptr to a transform stmt if successful.
 */
VMStmt *parse_vm_transform(int transform_type_token)
{
    int			token;
    VMStmtXform	*newstmt =
        (VMStmtXform *) vm_alloc_stmt(sizeof(VMStmtXform), &s_xform_stmt_methods);
    if (newstmt == NULL)
    {
        logmemerror(g_token_buffer);
        return NULL;
    }

    newstmt->transform_type =
        (transform_type_token == TK_ROTATE) ? XFORM_ROTATE :
        (transform_type_token == TK_SCALE) ? XFORM_SCALE :
        XFORM_TRANSLATE;

    /* Parse the transform's expression. */
    if ((newstmt->expr = parse_exprtree()) != NULL)
        if ((token = gettoken()) != OP_SEMICOLON)
            gettoken_ErrUnknown(token, ";");

    return (VMStmt *)newstmt;
}