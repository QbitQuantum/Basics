void CSMTools::ScriptCheckStage::perform (int stage, CSMDoc::Messages& messages)
{
    mId = mDocument.getData().getScripts().getId (stage);

    if (mDocument.isBlacklisted (
        CSMWorld::UniversalId (CSMWorld::UniversalId::Type_Script, mId)))
        return;

    mMessages = &messages;

    try
    {
        const CSMWorld::Data& data = mDocument.getData();

        mFile = data.getScripts().getRecord (stage).get().mId;
        std::istringstream input (data.getScripts().getRecord (stage).get().mScriptText);

        Compiler::Scanner scanner (*this, input, mContext.getExtensions());

        Compiler::FileParser parser (*this, mContext);

        scanner.scan (parser);
    }
    catch (const Compiler::SourceException&)
    {
        // error has already been reported via error handler
    }
    catch (const std::exception& error)
    {
        CSMWorld::UniversalId id (CSMWorld::UniversalId::Type_Script, mId);

        messages.push_back (std::make_pair (id,
            std::string ("Critical compile error: ") + error.what()));
    }

    mMessages = 0;
}