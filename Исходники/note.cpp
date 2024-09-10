/**
 * Checks if note text can be decrypted
 */
bool Note::canDecryptNoteText() {
    QString encryptedNoteText = getEncryptedNoteText();

    if (encryptedNoteText == "") {
        return false;
    }

    // decrypt the note text
    BotanWrapper botanWrapper;
    botanWrapper.setPassword(cryptoPassword);
    botanWrapper.setSalt(BOTAN_SALT);
    QString decryptedNoteText = botanWrapper.Decrypt(encryptedNoteText);

    // fallback to SimpleCrypt
    if (decryptedNoteText == "") {
        SimpleCrypt *crypto = new SimpleCrypt(static_cast<quint64>(cryptoKey));
        decryptedNoteText = crypto->decryptToString(encryptedNoteText);
    }

    return decryptedNoteText != "";
}