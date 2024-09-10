/*
 * encrypt(keySize,password,original_message,encrypted_message, mode, padding)
 * - encrypts a message using AES Algorithm
 *
 * Parameters:
 *    keySize : Size of key to use in AES Algorithm
 *    password: Key to encrypt plaintext message.
 *    original_message: Plaintext message before calculating AES Algorithm
 *    encrypted_message: Ciphertext message after calculating AES Algorithm
 *    mode: cipher mode, two ways: ECB
 *    padding: padding mode to fill blocks, tree ways PKCS5, ZEROS, X923
 *
 * Examples:
 *  AES.encrypt(128,"libelium","Libelium",encrypted_message,ECB,PKCS5)
 *
 */
uint8_t WaspAES::encrypt(	uint16_t keySize
							, char* password
							, char original_message[]
							, uint8_t* encrypted_message
							, uint8_t mode
							, uint8_t padding)
{
	// Calculate length of the original message
	uint16_t original_length;
	original_length = strlen(original_message);

	return encrypt(	keySize,
					password,
					(uint8_t*) original_message,
					original_length,
					encrypted_message,
					mode,
					padding);	
}