std::pair<char, bool> CSMWorld::ScriptContext::getMemberType (const std::string& name,
    const std::string& id) const
{
    /// \todo invalidate locals cache on change to scripts

    std::string id2 = Misc::StringUtils::lowerCase (id);

    int index = mData.getScripts().searchId (id2);
    bool reference = false;

    if (index==-1)
    {
        // ID is not a script ID. Search for a matching referenceable instead.
        index = mData.getReferenceables().searchId (id2);

        if (index!=-1)
        {
            // Referenceable found.
            int columnIndex = mData.getReferenceables().findColumnIndex (Columns::ColumnId_Script);

            id2 = Misc::StringUtils::lowerCase (mData.getReferenceables().
                getData (index, columnIndex).toString().toUtf8().constData());

            if (!id2.empty())
            {
                // Referenceable has a script -> use it.
                index = mData.getScripts().searchId (id2);
                reference = true;
            }
        }
    }

    if (index==-1)
        return std::make_pair (' ', false);

    std::map<std::string, Compiler::Locals>::iterator iter = mLocals.find (id2);

    if (iter==mLocals.end())
    {
        Compiler::Locals locals;

        Compiler::NullErrorHandler errorHandler;
        std::istringstream stream (mData.getScripts().getRecord (index).get().mScriptText);
        Compiler::QuickFileParser parser (errorHandler, *this, locals);
        Compiler::Scanner scanner (errorHandler, stream, getExtensions());
        scanner.scan (parser);

        iter = mLocals.insert (std::make_pair (id2, locals)).first;
    }

    return std::make_pair (iter->second.getType (Misc::StringUtils::lowerCase (name)), reference);
}