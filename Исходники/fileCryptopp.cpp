/**
 * @brief Writes to file associated with the calling object. If a valid key
 *        is available, data is encrypted (AES-GCM) prior to writing.
 *
 * @param ss const reference to a string stream with data.
 * @param key const reference to a byte vector with the encryption key.
 *
 * @return true, if data was sucessfully written to file.
 */
bool FileCryptopp::writeFile(
    const std::stringstream& ss,
    const std::vector<uint8_t>& key
) {

    // Start a file stream.
    std::ofstream fileStream(_filename, std::ios::binary);

    // Check if file stream is open.
    if (!fileStream.is_open()) {
        return false;
    }

    // Initialize an ostream_iterator to write to the file stream.
    std::ostream_iterator<uint8_t> oit(fileStream);

    // Check if encyption key is provided.
    if (!key.empty()) {
        // Check if encryption key has length equal to default AES key length.
        if (key.size() != FileCryptopp::AESNODE_DEFAULT_KEY_LENGTH_BYTES) {
            // Invalid key.
            std::cout << "Invalid key length";
            return false;
        }

        // Vector to store encrypted bytes of data.
        std::vector<uint8_t> cipherData;

        // Attempt to encrypt input stream ss and load bytes into cipherData.
        if (!encrypt(ss, cipherData, key)) {
            // Failed encryption.
            return false;
        }
        // Write encrypted bytes from cipherData to file as chars.
        std::copy(cipherData.begin(), cipherData.end(), oit);
    } else {
        // Write to file without encryption.
        fileStream << ss.str();
    }

    fileStream.close();
	return true;
}