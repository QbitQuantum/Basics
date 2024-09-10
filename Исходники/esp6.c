static int esp6_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;
	int hdr_len;
	struct ipv6hdr *top_iph;
	struct ipv6_esp_hdr *esph;
	struct crypto_tfm *tfm;
	struct esp_data *esp;
	struct sk_buff *trailer;
	int blksize;
	int clen;
	int alen;
	int nfrags;

	esp = x->data;
	hdr_len = skb->h.raw - skb->data +
		  sizeof(*esph) + esp->conf.ivlen;

	/* Strip IP+ESP header. */
	__skb_pull(skb, hdr_len);

	/* Now skb is pure payload to encrypt */
	err = -ENOMEM;

	/* Round to block size */
	clen = skb->len;

	alen = esp->auth.icv_trunc_len;
	tfm = esp->conf.tfm;
	blksize = ALIGN(crypto_tfm_alg_blocksize(tfm), 4);
	clen = ALIGN(clen + 2, blksize);
	if (esp->conf.padlen)
		clen = ALIGN(clen, esp->conf.padlen);

	if ((nfrags = skb_cow_data(skb, clen-skb->len+alen, &trailer)) < 0) {
		goto error;
	}

	/* Fill padding... */
	do {
		int i;
		for (i=0; i<clen-skb->len - 2; i++)
			*(u8*)(trailer->tail + i) = i+1;
	} while (0);
	*(u8*)(trailer->tail + clen-skb->len - 2) = (clen - skb->len)-2;
	pskb_put(skb, trailer, clen - skb->len);

	top_iph = (struct ipv6hdr *)__skb_push(skb, hdr_len);
	esph = (struct ipv6_esp_hdr *)skb->h.raw;
	top_iph->payload_len = htons(skb->len + alen - sizeof(*top_iph));
	*(u8*)(trailer->tail - 1) = *skb->nh.raw;
	*skb->nh.raw = IPPROTO_ESP;

	esph->spi = x->id.spi;
	esph->seq_no = htonl(++x->replay.oseq);

	if (esp->conf.ivlen)
		crypto_cipher_set_iv(tfm, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));

	do {
		struct scatterlist *sg = &esp->sgbuf[0];

		if (unlikely(nfrags > ESP_NUM_FAST_SG)) {
			sg = kmalloc(sizeof(struct scatterlist)*nfrags, GFP_ATOMIC);
			if (!sg)
				goto error;
		}
		skb_to_sgvec(skb, sg, esph->enc_data+esp->conf.ivlen-skb->data, clen);
		crypto_cipher_encrypt(tfm, sg, sg, clen);
		if (unlikely(sg != &esp->sgbuf[0]))
			kfree(sg);
	} while (0);

	if (esp->conf.ivlen) {
		memcpy(esph->enc_data, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));
		crypto_cipher_get_iv(tfm, esp->conf.ivec, crypto_tfm_alg_ivsize(tfm));
	}

	if (esp->auth.icv_full_len) {
		esp->auth.icv(esp, skb, (u8*)esph-skb->data,
			sizeof(struct ipv6_esp_hdr) + esp->conf.ivlen+clen, trailer->tail);
		pskb_put(skb, trailer, alen);
	}

	err = 0;

error:
	return err;
}