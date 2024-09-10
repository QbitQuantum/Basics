Status
loginRecoverySet(Login &login,
                 const std::string &recoveryQuestions,
                 const std::string &recoveryAnswers)
{
    std::string LRA = login.store.username() + recoveryAnswers;

    // Load the packages:
    CarePackage carePackage;
    LoginPackage loginPackage;
    ABC_CHECK(carePackage.load(login.paths.carePackagePath()));
    ABC_CHECK(loginPackage.load(login.paths.loginPackagePath()));

    // Load the old keys:
    DataChunk passwordAuth = login.passwordAuth();

    // Update scrypt parameters:
    JsonSnrp snrp;
    ABC_CHECK(snrp.create());
    ABC_CHECK(carePackage.recoveryKeySnrpSet(snrp));
    ABC_CHECK(snrp.create());
    ABC_CHECK(carePackage.questionKeySnrpSet(snrp));

    // Make questionKey (unlocks questions):
    DataChunk questionKey;
    ABC_CHECK(carePackage.questionKeySnrp().hash(questionKey,
              login.store.username()));

    // Encrypt the questions:
    JsonBox questionBox;
    ABC_CHECK(questionBox.encrypt(recoveryQuestions, questionKey));
    ABC_CHECK(carePackage.questionBoxSet(questionBox));

    // Make recoveryKey (unlocks dataKey):
    DataChunk recoveryKey;
    ABC_CHECK(carePackage.recoveryKeySnrp().hash(recoveryKey, LRA));

    // Encrypt dataKey:
    JsonBox recoveryBox;
    ABC_CHECK(recoveryBox.encrypt(login.dataKey(), recoveryKey));
    ABC_CHECK(loginPackage.recoveryBoxSet(recoveryBox));

    // Make recoveryAuth (unlocks the server):
    DataChunk recoveryAuth;
    ABC_CHECK(usernameSnrp().hash(recoveryAuth, LRA));

    // Change the server login:
    ABC_CHECK(loginServerChangePassword(login, passwordAuth, recoveryAuth,
                                        carePackage, loginPackage));

    // Change the on-disk login:
    ABC_CHECK(carePackage.save(login.paths.carePackagePath()));
    ABC_CHECK(loginPackage.save(login.paths.loginPackagePath()));

    return Status();
}