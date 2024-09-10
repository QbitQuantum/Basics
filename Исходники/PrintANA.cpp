void CPrintANAProcess::writeToStream(ostream& fout) const
{
    fout << "\\+Process "<< ID() << PROC_ENABLED_STATUS << "\n";
    outputInt(fout, "DisplayBeginColumn", m_nDisplayBeginColumn);
    outputBool(fout, "DisplayAnalysesOnly", m_bDisplayAnalysesOnly);
    USES_CONVERSION;
    fout <<"\\EXEName " << T2CA(m_sEXEName) << '\n';

    fout << "\\-Process "<< ID() << "\n";
}