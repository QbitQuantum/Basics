/*
 * Class:     edu_biu_scapi_midLayer_asymmetricCrypto_encryption_CryptoPPRSAOaep
 * Method:    initRSADecryptor
 * Signature: ([B[B[B)J
 */
JNIEXPORT void JNICALL Java_edu_biu_scapi_midLayer_asymmetricCrypto_encryption_CryptoPPRSAOaep_initRSADecryptor
  (JNIEnv *env, jobject, jlong decryptor, jbyteArray modulus, jbyteArray pubExp, jbyteArray privExp) {
	  
	  Integer n, e, d;
	  Utils utils;

	  // get the Integers values for the RSA permutation 
	  n = utils.jbyteArrayToCryptoPPInteger(env, modulus);
	  e = utils.jbyteArrayToCryptoPPInteger(env, pubExp);
	  d = utils.jbyteArrayToCryptoPPInteger(env, privExp);

	  //create pointer to InvertibleRSAFunction object
	  InvertibleRSAFunction* invRsaFunc = new InvertibleRSAFunction;

	  //initialize the trapdoor object with the RSA values
	  invRsaFunc->Initialize(n, e, d);

	  RSA::PrivateKey privateKey(*invRsaFunc);
	  
	  ((RSAES_OAEP_SHA_Decryptor * ) decryptor)->AccessKey().AssignFrom(privateKey);
}