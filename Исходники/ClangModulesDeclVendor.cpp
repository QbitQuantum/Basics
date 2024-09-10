void
StoringDiagnosticConsumer::DumpDiagnostics (Stream &error_stream)
{
    for (IDAndDiagnostic &diag : m_diagnostics)
    {
        switch (diag.first)
        {
            default:
                error_stream.PutCString(diag.second.c_str());
                error_stream.PutChar('\n');
                break;
            case clang::DiagnosticsEngine::Level::Ignored:
                break;
        }
    }
}