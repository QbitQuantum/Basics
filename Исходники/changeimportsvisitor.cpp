bool ChangeImportsVisitor::add(QmlJS::AST::UiProgram *ast, const Import &import)
{
    setDidRewriting(false);
    if (!ast)
        return false;

    if (ast->headers && ast->headers->headerItem) {
        int insertionPoint = 0;
        if (ast->members && ast->members->member)
            insertionPoint = ast->members->member->firstSourceLocation().begin();
        else
            insertionPoint = m_source.length();
        while (insertionPoint > 0) {
            --insertionPoint;
            const QChar c = m_source.at(insertionPoint);
            if (!c.isSpace() && c != QLatin1Char(';'))
                break;
        }
        replace(insertionPoint+1, 0, QStringLiteral("\n") + import.toImportString());
    } else {
        replace(0, 0, import.toImportString() + QStringLiteral("\n\n"));
    }

    setDidRewriting(true);

    return true;
}