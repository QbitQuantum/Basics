void decompress(File *in, File *out)
{
    uint32_t fileSize, length = 0;
	uint16_t encoderNodeCount;
	uint16_t ch, *xList, *zList;
	Encoder_Node *root, *p;

	decoder_readHead(&fileSize, &encoderNodeCount, &xList, &zList, in);
	root = decoder_rebuildEncoder(xList, zList, 0, 0, encoderNodeCount);

	ch = Fgetc(in);
	p = root;
	while (!Feof(in)) {
		int8_t bit;

		while (((bit=FgetBit(ch)) != (int8_t)-1) && length < fileSize) {
			if (bit == (int8_t)0)
				p = p->left;
			else
				p = p->right;

			if (p->left == NULL && p->right == NULL) {
				Fputc(p->ch, out);
				p = root;
				++length;
			}
		}

		ch = Fgetc(in);
	}

	free(xList);
	free(zList);
	encoder_freeEncoder(root);
}