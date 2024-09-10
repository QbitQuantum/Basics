bool NewLoginDialog::passwordsMatch(const QString &p1, const QString &p2) {
    return (
                ( p1.length() > PASSWORD_MINIMUM_LENGTH )
                && (p1 == p2)
           );
}