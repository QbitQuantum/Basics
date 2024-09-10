void ImapMessageTest::testMailAddressFormat()
{
    QFETCH( Imap::Message::MailAddress, addr );
    QFETCH( QString, pretty );
    QFETCH( QByteArray, addrspec );
    QFETCH( bool, should2047 );

    QCOMPARE( addr.prettyName(Imap::Message::MailAddress::FORMAT_READABLE), pretty );
    QCOMPARE( addr.asSMTPMailbox(), addrspec );
    
    QByteArray full = addr.asMailHeader();
    QByteArray bracketed;
    bracketed.append(" <").append(addrspec).append(">");
    QVERIFY( full.endsWith(bracketed) );
    full.remove(full.size() - bracketed.size(), bracketed.size());
    
    if (should2047) {
        QVERIFY( full.startsWith("=?") );
        QVERIFY( full.endsWith("?=") );
        QCOMPARE( addr.name, Imap::decodeRFC2047String(full) );
    } else {
        QVERIFY( !full.contains("=?") );
        QVERIFY( !full.contains("?=") );
    }
}