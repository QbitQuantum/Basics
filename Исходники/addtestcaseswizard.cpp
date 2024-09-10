bool AddTestCasesWizard::compareFileName(const QString &a, const QString &b)
{
    return a.length() < b.length() || a.length() == b.length() && QString::localeAwareCompare(a, b) < 0;
}