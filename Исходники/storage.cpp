boost::optional<TClientInfo> TClientInfoStorage::Get(const std::string& login) {
    boost::optional<string> strData = Storage->Get(login);
    if (!strData.is_initialized()) {
        return boost::optional<TClientInfo>();
    }
    TClientInfoData data;
    if (!data.ParseFromString(Decompress(*strData))) {
        throw UException("failed to parse storage data");
    }
    TClientInfo result;
    result.Login = data.login();
    result.EncryptedPrivateKey = data.encryptedprivatekey();
    result.LoginPasswordHash = data.loginpasswordhash();
    result.PublicKey = data.publickey();
    for (size_t i = 0; i < data.friends_size(); ++i) {
        const TFriendInfoData& frnd = data.friends(i);
        TFriendInfo& friendInfo = result.Friends[frnd.login()];
        friendInfo.Login = frnd.login();
        friendInfo.EncryptedKey = frnd.encryptedkey();
        friendInfo.Type = frnd.type();
        friendInfo.AuthStatus = (EAuthStatus)frnd.authstatus();
        friendInfo.PublicKey = frnd.publickey();
        friendInfo.ServerPublicKey = frnd.serverpublickey();
        if (frnd.has_offlinekey()) {
            assert(frnd.has_offlinekeysignature());
            friendInfo.OfflineKey = frnd.offlinekey();
            friendInfo.OfflineKeySignature = frnd.offlinekeysignature();
        }
    }
    return result;
}