/*
 * Preparse a big key
 */
int big_key_preparse(struct key_preparsed_payload *prep)
{
	struct path *path = (struct path *)&prep->payload.data[big_key_path];
	struct file *file;
	u8 *enckey;
	u8 *data = NULL;
	ssize_t written;
	size_t datalen = prep->datalen;
	int ret;

	ret = -EINVAL;
	if (datalen <= 0 || datalen > 1024 * 1024 || !prep->data)
		goto error;

	/* Set an arbitrary quota */
	prep->quotalen = 16;

	prep->payload.data[big_key_len] = (void *)(unsigned long)datalen;

	if (datalen > BIG_KEY_FILE_THRESHOLD) {
		/* Create a shmem file to store the data in.  This will permit the data
		 * to be swapped out if needed.
		 *
		 * File content is stored encrypted with randomly generated key.
		 */
		size_t enclen = ALIGN(datalen, crypto_skcipher_blocksize(big_key_skcipher));

		/* prepare aligned data to encrypt */
		data = kmalloc(enclen, GFP_KERNEL);
		if (!data)
			return -ENOMEM;

		memcpy(data, prep->data, datalen);
		memset(data + datalen, 0x00, enclen - datalen);

		/* generate random key */
		enckey = kmalloc(ENC_KEY_SIZE, GFP_KERNEL);
		if (!enckey) {
			ret = -ENOMEM;
			goto error;
		}

		ret = big_key_gen_enckey(enckey);
		if (ret)
			goto err_enckey;

		/* encrypt aligned data */
		ret = big_key_crypt(BIG_KEY_ENC, data, enclen, enckey);
		if (ret)
			goto err_enckey;

		/* save aligned data to file */
		file = shmem_kernel_file_setup("", enclen, 0);
		if (IS_ERR(file)) {
			ret = PTR_ERR(file);
			goto err_enckey;
		}

		written = kernel_write(file, data, enclen, 0);
		if (written != enclen) {
			ret = written;
			if (written >= 0)
				ret = -ENOMEM;
			goto err_fput;
		}

		/* Pin the mount and dentry to the key so that we can open it again
		 * later
		 */
		prep->payload.data[big_key_data] = enckey;
		*path = file->f_path;
		path_get(path);
		fput(file);
		kfree(data);
	} else {
		/* Just store the data in a buffer */
		void *data = kmalloc(datalen, GFP_KERNEL);

		if (!data)
			return -ENOMEM;

		prep->payload.data[big_key_data] = data;
		memcpy(data, prep->data, prep->datalen);
	}
	return 0;

err_fput:
	fput(file);
err_enckey:
	kfree(enckey);
error:
	kfree(data);
	return ret;
}