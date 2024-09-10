/* 文字列の出力 */
LOCAL	W	output_string(W fd, W len, TC *tc, W hankaku)
{
	W	err, n, pos;
	UH	sjis;
	UB	*buf;

	if (len < 1) {
		err = ER_OK;
		goto fin0;
	}

	/* 入力サイズを超えることは決してない */
	buf = malloc(len);
	if (buf == NULL) {
		P(("output_string: malloc NULL\n"));
		err = ER_NOMEM;
		goto fin0;
	}

	len /= 2;
	pos = 0;
	while (len-- > 0) {
		switch (*tc) {
		case	TAB:
			buf[pos++] = TAB;
			break;

		case	LF:
		case	CR:
			buf[pos++] = CR;
			buf[pos++] = LF;
			break;

		default:
			/* 言語ID */
			if ((*tc & 0xff00) == 0xfe00) {
				LangState = *tc;
				break;
			}

			/* 日本語以外の言語が指定されている場合 */
			if (LangState != LANGJP) {
				sjis = _mbcjistojms(0);
				buf[pos++] = sjis >> 8;
				buf[pos++] = sjis;
				break;
			}

			/* 半角化可能な物は半角で出力 */
			if (hankaku) {
				n = zen2han(*tc, &buf[pos]);
				if (n > 0) {
					pos += n;
					break;
				}
			}

			/* 全角 */
			sjis = _mbcjistojms(*tc);
			buf[pos++] = sjis >> 8;
			buf[pos++] = sjis;
			break;
		}

		tc++;
	}