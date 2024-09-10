int main()
{
    const string plainText =
            "MOST GOOD PROGRAMMERS DO PROGRAMMING NOT BECAUSE "
            "THEY EXPECT TO GET PAID OR GET ADULATION BY THE PUBLIC "
            "BUT BECAUSE IT IS FUN TO PROGRAM"; // Quote by Linus Torvalds

    cout << "Plain message: " << endl
         << plainText << endl << endl;

    /*************************************************************************/

    const int privateKey = 5;

    cout << "Private key: " << endl
         << privateKey << endl << endl;

    string cipherText = CaesarCipher::encrypt(plainText, privateKey);
    cout << "Ciphered message: " << endl
         << cipherText << endl << endl;

    string decipheredText = CaesarCipher::decrypt(cipherText, privateKey);
    cout << "Deciphered message using known key: " << endl
         << decipheredText << endl << endl;

    /*************************************************************************/

    CaesarCipher mCipher;
    string autoDecryptedText = mCipher.decrypt(cipherText);

    cout << "Deciphered message using auto key finder: " << endl
         << autoDecryptedText << endl << endl;

    cout << "Possible key used: "
         << mCipher.getPossiblePrivateKey() << endl;

    return 0;
}