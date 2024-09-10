/*!
  return always true, and handle the error in ruby.
  error return is "failed with uid:0x12345678" where 0x12345678 is replaced with given uid
*/
bool LaunchFixture::execute(void * objectInstance, QString actionName, QHash<QString, QString> parameters, QString & stdOut)
{
    bool result = true;

    //TasLogger::logger()->debug("> LaunchFixture::execute:" + actionName);

    if(actionName == "launch_with_uid"){
        bool ok;
        QString temp = parameters.value("UID");
        //TasLogger::logger()->debug("> LaunchFixture::UID: '" + temp + "'");
        TUint uid_i = temp.toUInt(&ok, 0);
        //TasLogger::logger()->debug("  ok: " + QString::number(ok) + " uid: " + QString::number(uid_i));
        TUid uid = TUid::Uid(uid_i);
        //T R A P D starts
        TRAPD(trapErr,
            RApaLsSession session;
            TInt err = session.Connect();
            User::LeaveIfError(err);
            //TasLogger::logger()->debug("  session " );

            CleanupClosePushL(session);
            TApaAppInfo info;
            err = session.GetAppInfo(info,uid);
            User::LeaveIfError(err);
            //TasLogger::logger()->debug("  appinfo " );

            CApaCommandLine* cmdLine = CApaCommandLine::NewLC();
            cmdLine->SetExecutableNameL(info.iFullName);
            cmdLine->SetCommandL(EApaCommandRun);
            User::LeaveIfError(session.StartApp(*cmdLine));
            //TasLogger::logger()->debug("  command line " );
            stdOut.append(QString((QChar*) info.iFullName.Ptr(), info.iFullName.Length()));
            CleanupStack::PopAndDestroy(2);
        );