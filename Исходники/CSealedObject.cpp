ECode CSealedObject::GetObject(
    /* [in] */ IKey * key,
    /* [in] */ const String& provider,
    /* [out] */ IInterface ** result)
{
    VALIDATE_NOT_NULL(result)
    *result = NULL;
    if (provider == NULL || provider.IsEmpty()) {
        // throw new IllegalArgumentException("provider name empty or NULL");
        return E_ILLEGAL_ARGUMENT_EXCEPTION;
    }
    // try {
        AutoPtr<ICipher> cipher;
        AutoPtr<ICipherHelper> cipherHelper;
        CCipherHelper::AcquireSingleton((ICipherHelper**)&cipherHelper);
        cipherHelper->GetInstance(mSealAlg, provider, (ICipher**)&cipher);

        if ((mParamsAlg != NULL) && (mParamsAlg.GetLength() != 0)) {
            AutoPtr<IAlgorithmParameters> params;
            AutoPtr<IAlgorithmParametersHelper> apHelper;
//TODO: Need CAlgorithmParametersHelper
            // CAlgorithmParametersHelper::AcquireSingleton((IAlgorithmParametersHelper**)&apHelper);
            apHelper->GetInstance(mParamsAlg, (IAlgorithmParameters**)&params);

            params->InitEx(*mEncodedParams);
            cipher->Init(ICipher::DECRYPT_MODE, key, params);
        } else {
            cipher->Init(ICipher::DECRYPT_MODE, key);
        }
        AutoPtr<ArrayOf<Byte> > serialized;
        cipher->DoFinal(mEncryptedContent, (ArrayOf<Byte>**)&serialized);
        ReadSerialized(serialized, result);
        REFCOUNT_ADD(*result)
        return NOERROR;
    // } catch (NoSuchPaddingException e)  {
    //     // should not be thrown because cipher text was made
    //     // with existing padding
    //     throw new NoSuchAlgorithmException(e.toString());
    // } catch (InvalidAlgorithmParameterException e) {
    //     // should not be thrown because cipher text was made
    //     // with correct algorithm parameters
    //     throw new NoSuchAlgorithmException(e.toString());
    // } catch (IllegalBlockSizeException e) {
    //     // should not be thrown because the cipher text
    //     // was correctly made
    //     throw new NoSuchAlgorithmException(e.toString());
    // } catch (BadPaddingException e) {
    //     // should not be thrown because the cipher text
    //     // was correctly made
    //     throw new NoSuchAlgorithmException(e.toString());
    // } catch (IllegalStateException  e) {
    //     // should never be thrown because cipher is initialized
    //     throw new NoSuchAlgorithmException(e.toString());
    // }
}