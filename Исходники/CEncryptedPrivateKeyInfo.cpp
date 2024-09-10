ECode CEncryptedPrivateKeyInfo::GetKeySpec(
    /* [in] */ IKey * decryptKey,
    /* [in] */ IProvider * provider,
    /* [out] */ IPKCS8EncodedKeySpec ** spec)
{
    VALIDATE_NOT_NULL(spec)
    *spec = NULL;
    if (decryptKey == NULL) {
        // throw new NullPointerException("decryptKey == NULL");
        return E_NULL_POINTER_EXCEPTION;
    }
    if (provider == NULL) {
        // throw new NullPointerException("provider == NULL");
        return E_NULL_POINTER_EXCEPTION;
    }
    // try {
        AutoPtr<ICipher> cipher;
        AutoPtr<ICipherHelper> helper;
        helper->GetInstance(mAlgName, provider, (ICipher**)&cipher);
        if (mAlgParameters == NULL) {
            cipher->Init(ICipher::DECRYPT_MODE, decryptKey);
        } else {
            cipher->Init(ICipher::DECRYPT_MODE, decryptKey, mAlgParameters);
        }
        AutoPtr<ArrayOf<Byte> > decryptedData;
        cipher->DoFinal(mEncryptedData, (ArrayOf<Byte>**)&decryptedData);
        // try {
//TODO: Need Org::Apache::Harmony::Security
            // sASN1PrivateKeyInfo->Verify(decryptedData);
        // } catch (IOException e1) {
        //     throw invalidKey();
        // }
//TODO: Need CPKCS8EncodedKeySpec
        // CPKCS8EncodedKeySpec::New(decryptedData, spec);
        return NOERROR;
    // } catch (NoSuchPaddingException e) {
    //     throw new NoSuchAlgorithmException(e.getMessage());
    // } catch (InvalidAlgorithmParameterException e) {
    //     throw new NoSuchAlgorithmException(e.getMessage());
    // } catch (IllegalStateException e) {
    //     throw new InvalidKeyException(e.getMessage());
    // } catch (IllegalBlockSizeException e) {
    //     throw new InvalidKeyException(e.getMessage());
    // } catch (BadPaddingException e) {
    //     throw new InvalidKeyException(e.getMessage());
    // }
}