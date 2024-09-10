void PHPCodeCompletion::Open(const wxFileName& workspaceFile)
{
    Close();
    m_lookupTable.Open(workspaceFile.GetPath());

    // Cache the symbols into the OS caching, this is done by simply reading the entire file content and
    // then closing it
    wxFileName fnDBFile(workspaceFile.GetPath(), "phpsymbols.db");
    fnDBFile.AppendDir(".codelite");
    JobQueueSingleton::Instance()->PushJob(new PHPSymbolsCacher(this, fnDBFile.GetFullPath()));
}