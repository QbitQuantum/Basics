bool MapiProfiles::add(const QString &profile, const QString &username, const QString &password, const QString &domain, const QString &server)
{
    if (!init()) {
        return false;
    }

    // It seams that the QByteArray returned by QString::toUtf8() are not backed up.
    // calling toUtf8() several times will destroy the data. Therefore I copy them
    // all to temporary objects in order to preserve them throughout the whole method
    QByteArray baProfile(profile.toUtf8());
    QByteArray baUser(username.toUtf8());
    QByteArray baPass(password.toUtf8());
    QByteArray baDomain(domain.toUtf8());
    QByteArray baServer(server.toUtf8());

    const char *profile8 = baProfile.constData();
    qDebug() << "New profile is:"<<profile8;

    if (MAPI_E_SUCCESS != CreateProfile(m_context, profile8, baUser.constData(), baPass.constData(), 0)) {
        error() << "cannot create profile:" << mapiError();
        return false;
    }

    // TODO get workstation as parameter (was is it needed for anyway?)
    char hostname[256] = {};
    gethostname(&hostname[0], sizeof(hostname) - 1);
    hostname[sizeof(hostname) - 1] = 0;
    QString workstation = QString::fromLatin1(hostname);

    if (!attributeAdd(profile8, "binding", server)) {
        return false;
    }
    if (!attributeAdd(profile8, "workstation", workstation)) {
        return false;
    }
    if (!attributeAdd(profile8, "domain", domain)) {
        return false;
    }
// What is seal for? Seams to have something to do with Exchange 2010
// 	mapi_profile_add_string_attr(m_context, profile.toUtf8().constData(), "seal", (seal == true) ? "true" : "false");

// TODO Get langage from parameter if needed
// 	const char* locale = (const char *) (language) ? mapi_get_locale_from_language(language) : mapi_get_system_locale();
    const char *locale = mapi_get_system_locale();
    if (!locale) {
        error() << "cannot find system locale:" << mapiError();
        return false;
    }

    uint32_t cpid = mapi_get_cpid_from_locale(locale);
    uint32_t lcid = mapi_get_lcid_from_locale(locale);
    if (!cpid || !lcid) {
        error() << "invalid Locale supplied or unknown system locale" << locale << ", deleting profile..." << mapiError();
        if (!remove(profile)) {
            return false;
        }
        return false;
    }

    if (!attributeAdd(profile8, "codepage", QString::number(cpid))) {
        return false;
    }
    if (!attributeAdd(profile8, "language", QString::number(lcid))) {
        return false;
    }
    if (!attributeAdd(profile8, "method", QString::number(lcid))) {
        return false;
    }

    struct mapi_session *session = NULL;
    if (MAPI_E_SUCCESS != MapiLogonProvider(m_context, &session, profile8, password.toUtf8(), PROVIDER_ID_NSPI)) {
        error() << "cannot get logon provider, deleting profile..." << mapiError();
        if (!remove(profile)) {
            return false;
        }
        return false;
    }

    int retval = ProcessNetworkProfile(session, username.toUtf8().constData(), profileSelectCallback, NULL);
    if (retval != MAPI_E_SUCCESS && retval != 0x1) {
        error() << "cannot process network profile, deleting profile..." << mapiError();
        if (!remove(profile)) {
            return false;
        }
        return false;
    }
    return true;
}