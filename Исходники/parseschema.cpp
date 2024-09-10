QString
mkvar(const QString &s) {
    return s.toUpper().replace('-', '_').replace(':', '_');
}