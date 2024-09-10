bool CETDongle::IsAdminHID( QString &strHID )
{
    strHID = strHID.toUpper( );

    return hashAdminHID.contains( strHID );
}