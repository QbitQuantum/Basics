void
decrypt_file (const gchar *input_file_path, const gchar *pwd)
{
    GError *err = NULL;

    goffset file_size = get_file_size (input_file_path);
    if (file_size == -1) {
        return;
    }
    if (file_size < (goffset) (sizeof (Metadata) + SHA512_DIGEST_SIZE)) {
        g_printerr ("The selected file is not encrypted.\n");
        return;
    }

    GFile *in_file = g_file_new_for_path (input_file_path);
    GFileInputStream *in_stream = g_file_read (in_file, NULL, &err);
    if (err != NULL) {
        g_printerr ("%s\n", err->message);
        // TODO
        return;
    }

    gchar *output_file_path;
    if (!g_str_has_suffix (input_file_path, ".enc")) {
        g_printerr ("The selected file may not be encrypted\n");
        output_file_path = g_strconcat (input_file_path, ".decrypted", NULL);
    }
    else {
        output_file_path = g_strndup (input_file_path, (gsize) g_utf8_strlen (input_file_path, -1) - 4); // remove .enc
    }
    GFile *out_file = g_file_new_for_path (output_file_path);
    GFileOutputStream *out_stream = g_file_append_to (out_file, G_FILE_CREATE_REPLACE_DESTINATION, NULL, &err);
    if (err != NULL) {
        g_printerr ("%s\n", err->message);
        // TODO
        return;
    }

    Metadata *header_metadata = g_new0 (Metadata, 1);
    CryptoKeys *decryption_keys = g_new0 (CryptoKeys, 1);

    gssize rw_len = g_input_stream_read (G_INPUT_STREAM (in_stream), header_metadata, sizeof (Metadata), NULL, &err);
    if (rw_len == -1) {
        g_printerr ("%s\n", err->message);
        // TODO
        return;
    }

    guchar *original_hmac = g_malloc (SHA512_DIGEST_SIZE);
    if (!g_seekable_seek (G_SEEKABLE (in_stream), file_size - SHA512_DIGEST_SIZE, G_SEEK_SET, NULL, &err)) {
        g_printerr ("Couldn't set the position, exiting...\n");
        //TODO
        return;
    }
    rw_len = g_input_stream_read (G_INPUT_STREAM (in_stream), original_hmac, SHA512_DIGEST_SIZE, NULL, &err);
    if (rw_len == -1) {
        g_printerr ("%s\n", err->message);
        // TODO
        return;
    }

    if (!g_seekable_seek (G_SEEKABLE (in_stream), 0, G_SEEK_SET, NULL, &err)) {
        g_printerr ("Couldn't set the position, exiting...\n");
        //TODO
        return;
    }
    GFile *file_encrypted_data = get_g_file_with_encrypted_data (in_stream, file_size);
    if (file_encrypted_data == NULL) {
        // TODO
        return;
    }

    if (!setup_keys (pwd, gcry_cipher_get_algo_keylen (header_metadata->algo), header_metadata, decryption_keys)) {
        g_printerr ("Error during key derivation or during memory allocation\n");
        //TODO
        return;
    }

    if (!compare_hmac (decryption_keys->hmac_key, original_hmac, file_encrypted_data)) {
        g_printerr ("HMAC differs from the one stored inside the file.\nEither the password is wrong or the file has been corrupted.\n");
        // TODO
        return;
    }

    decrypt (header_metadata, decryption_keys, file_encrypted_data, file_size - sizeof (Metadata) - SHA512_DIGEST_SIZE, out_stream);

    g_unlink (g_file_get_path (file_encrypted_data));
    // TODO remove encrypted file? Give option to the user

    multiple_unref (5, (gpointer) &file_encrypted_data,
                    (gpointer) &in_stream,
                    (gpointer) &out_stream,
                    (gpointer) &in_file,
                    (gpointer) &out_file);

    multiple_gcry_free (3, (gpointer) &decryption_keys->crypto_key,
                        (gpointer) &decryption_keys->derived_key,
                        (gpointer) &decryption_keys->hmac_key);

    multiple_free (4, (gpointer) &header_metadata,
                   (gpointer) &output_file_path,
                   (gpointer) &original_hmac,
                   (gpointer) &decryption_keys);
}