OP_ERROR
GusdSOP_usdimport::_Cook(OP_Context& ctx)
{
    fpreal t = ctx.getTime();

    UT_String traversal;
    evalString( traversal, "import_traversal", 0, t );

    ErrorChoice errorMode = static_cast<ErrorChoice>(evalInt("missingframe", 0, t ));

    auto lockedMgr = getLockedErrorManager();
    GusdUT_ErrorManager errMgr(*lockedMgr);
    GusdUT_ErrorContext errContext(errMgr, 
        errorMode == MISSINGFRAME_WARN ? UT_ERROR_WARNING : UT_ERROR_ABORT);

    const GusdUSD_Traverse* trav = NULL;
    if(traversal != _NOTRAVERSE_NAME) {
        const auto& table = GusdUSD_TraverseTable::GetInstance();
        trav = table.FindTraversal(traversal);
        
        if(!trav) {
            UT_WorkBuffer buf;
            buf.sprintf("Failed locating traversal '%s'", traversal.c_str());
            return errContext.AddError(buf.buffer());
        }
    }
    return getInput(0) ? _ExpandPrims(ctx, trav, errContext)
                       : _CreateNewPrims(ctx, trav, errContext);
}                           