void
FailedLoginDialog::accept()
{
    LOGL(4, "FailedLoginDialog::accept()");

    if (!ui.proxyFrame->isHidden())
    {
        LastFmSettings& s = The::settings();
        
        s.setProxyHost( ui.proxyHostEdit->text() );
        s.setProxyPort( ui.proxyPortEdit->text().toInt() );
        s.setProxyUser( ui.proxyUsernameEdit->text() );
        s.setProxyPassword( ui.proxyPasswordEdit->text() );
        s.setUseProxy( !s.getProxyHost().isEmpty() );
    }

    LOGL(4, "FailedLoginDialog calling QDialog::accept()");

    QDialog::accept();
}