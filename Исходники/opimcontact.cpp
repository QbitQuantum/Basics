        void OPimContact::removeEmail( const QString &v )
{
    QString e = v.simplifyWhiteSpace();
    QString def = defaultEmail();
    QString emailsStr = find( Qtopia::Emails );
    QStringList emails = emailList();

    // otherwise, must first contain it
    if ( !emailsStr.contains( e ) )
        return ;

    // remove it
    //odebug << " removing email from list " << e << "" << oendl;
    emails.remove( e );
    // reset the string
    emailsStr = emails.join( emailSeparator() ); // Sharp's brain dead separator
    replace( Qtopia::Emails, emailsStr );

    // if default, then replace the default email with the first one
    if ( def == e )
    {
        //odebug << "removeEmail is default; setting new default" << oendl;
        if ( !emails.count() )
            clearEmails();
        else // setDefaultEmail will remove e from the list
            setDefaultEmail( emails.first() );
    }
}