void
mlib_s_ImageBlendLine(
    mlib_work_image * param,
    mlib_u8 *dp,
    __m128i * buffz,
    __m128i * buffd)
{
	mlib_blend blend = param->blend;
	mlib_s32 chan_d = param->chan_d;
	mlib_s32 chan_s = param->channels;
	mlib_d64 alp = (param->alpha) * (1.0 / 255);
	mlib_s32 width = GetElemSubStruct(current, width);
	mlib_u8 *tdp = dp;
	mlib_s32 width2, y_step, next_step = 2;
	mlib_s32 alp_ind = param->alp_ind, mask255;
	__m128i aa, dalp, done;
	__m128i mzero, mask_7fff, mask_8000, amask, amask256, amaskffff;
	__m128i d_rnd;
	mlib_s32 i, j;

	if (!alp_ind) {
		d_rnd = _mm_set1_epi16(0x0080);

		tdp = (void *)dp;
		if (chan_d == 3)
			tdp = (void *)buffd;

		for (i = 0; i < width / 2; i++) {
			__m128i dd;

			dd = buffz[i];
			dd = _mm_adds_epu16(dd, d_rnd);
			dd = _mm_srli_epi16(dd, 8);
			dd = _mm_packus_epi16(dd, dd);
			_mm_storel_epi64((void *)(tdp + 8 * i), dd);
		}
		if (width & 1) {
			__m128i dd;

			dd = buffz[i];
			dd = _mm_adds_epu16(dd, d_rnd);
			dd = _mm_srli_epi16(dd, 8);
			dd = _mm_packus_epi16(dd, dd);
			*(mlib_s32 *)(tdp + 8 * i) = *(mlib_s32 *)&dd;
		}

		if (chan_d == 3) {
			mlib_s_ImageChannelExtract_U8_43L_D1((void *)buffd, dp,
			    width);
		}
		return;
	}

	width2 = (width + 1) / 2;

	mzero = _mm_setzero_si128();
	mask_7fff = _mm_set1_epi16(0x7FFF);
	mask_8000 = _mm_set1_epi16(0x8000);
	done = _mm_set1_epi16(1 << 15);
	if (alp_ind == -1) {
		mask255 = 0xFF;
		amask = _mm_setr_epi32(0xff00, 0, 0xff00, 0);
		amaskffff = _mm_setr_epi32(0xffff, 0, 0xffff, 0);
		amask256 = _mm_setr_epi32(0x0100, 0, 0x0100, 0);
	} else {
		mask255 = 0xFF000000;
		amask = _mm_setr_epi32(0, 0xff000000, 0, 0xff000000);
		amaskffff = _mm_setr_epi32(0, 0xffff0000, 0, 0xffff0000);
		amask256 = _mm_setr_epi32(0, 0x01000000, 0, 0x01000000);
	}
	dalp = _mm_set1_epi16((1 << 15) * alp + 0.5);

	if (chan_s == 3) {
		if (chan_d == 3) {
			mlib_d64 alp = (param->alpha) * (1.0 / 255);
			mlib_s32 ialp;
			mlib_u8 *pz;
			__m128i emask;
			__m128i dalp, ralp, ss, dd, s0, s1, d0, d1, dr;

			mlib_s_ImageChannelExtract_S16_43L_D1((void *)buffz,
			    (void *)buffd, width);

			ialp = alp * (1 << 15);
			dalp = _mm_set1_epi16(ialp);
			ralp = _mm_set1_epi16((1 << 15) - ialp);
			emask = mlib_emask_m128i[(3 * width) & 15].m128i;

			pz = (void *)buffd;
			tdp = dp;
			for (i = 0; i <= 3 * width - 16; i += 16) {
				s0 = _mm_load_si128((__m128i *) (pz + 2 * i));
				s1 = _mm_load_si128((__m128i *) (pz + 2 * i +
				    16));
				dd = _mm_loadu_si128((__m128i *) (tdp + i));
				d0 = _mm_unpacklo_epi8(mzero, dd);
				d1 = _mm_unpackhi_epi8(mzero, dd);
				d0 = _mm_add_epi16(_mm_mulhi_epu16(s0, dalp),
				    _mm_mulhi_epu16(d0, ralp));
				d1 = _mm_add_epi16(_mm_mulhi_epu16(s1, dalp),
				    _mm_mulhi_epu16(d1, ralp));
				d0 = _mm_srli_epi16(d0, 7);
				d1 = _mm_srli_epi16(d1, 7);
				dr = _mm_packus_epi16(d0, d1);
				_mm_storeu_si128((__m128i *) (tdp + i), dr);
			}

			if (i < 3 * width) {
				s0 = _mm_load_si128((__m128i *) (pz + 2 * i));
				s1 = _mm_load_si128((__m128i *) (pz + 2 * i +
				    16));
				dd = _mm_loadu_si128((__m128i *) (tdp + i));
				d0 = _mm_unpacklo_epi8(mzero, dd);
				d1 = _mm_unpackhi_epi8(mzero, dd);
				d0 = _mm_add_epi16(_mm_mulhi_epu16(s0, dalp),
				    _mm_mulhi_epu16(d0, ralp));
				d1 = _mm_add_epi16(_mm_mulhi_epu16(s1, dalp),
				    _mm_mulhi_epu16(d1, ralp));
				d0 = _mm_srli_epi16(d0, 7);
				d1 = _mm_srli_epi16(d1, 7);
				dr = _mm_packus_epi16(d0, d1);

				dr = _mm_or_si128(_mm_and_si128(emask, dr),
				    _mm_andnot_si128(emask, dd));

				_mm_storeu_si128((__m128i *) (tdp + i), dr);
			}
		} else if (blend == MLIB_BLEND_GTK_SRC) {
			mlib_u8 *buffi = (mlib_u8 *)buffz + 1;

			for (i = 0; i < width; i++) {
				tdp[0] = buffi[0];
				tdp[1] = buffi[2];
				tdp[2] = buffi[4];
				tdp[alp_ind] = 255;
				tdp += 4;
				buffi += 8;
			}
		} else {
			mlib_d64 _w0 = param->alpha;
			mlib_d64 _w1s = 1.0 - _w0 * (1.0 / 255);
			__m128i buff[1];
			__m128i done;
			__m128i dalp, ralp, ss, dd, s0, s1, d0, d1, a0, a1, r0,
			    r1, rr, dr;
			__m128i wi, aa, amask;
			__m128 af, w0, w1, w1s, w, rw, w0r, w1r, scale;

			done = _mm_set1_epi16(1 << 15);
			amask = _mm_set1_epi32(mask255);

			w0 = _mm_set_ps1(_w0);
			w1s = _mm_set_ps1(_w1s);
			scale = _mm_set_ps1(1 << 15);

			if (alp_ind == -1) {
				tdp--;
				for (i = 0; i < width / 4; i++) {
					BLEND34_SRC_OVER(0);
					_mm_storeu_si128((__m128i *) tdp, dr);
					tdp += 16;
				}
				if (width & 3) {
					BLEND34_SRC_OVER(0);
					buff[0] = dr;
				}
			} else {
				for (i = 0; i < width / 4; i++) {
					BLEND34_SRC_OVER(3);
					_mm_storeu_si128((__m128i *) tdp, dr);
					tdp += 16;
				}
				if (width & 3) {
					BLEND34_SRC_OVER(3);
					buff[0] = dr;
				}
			}
			for (i = 0; i < (width & 3); i++) {
				((mlib_s32 *)tdp)[i] = ((mlib_s32 *)buff)[i];
			}
		}
	} else if (chan_d == 3) {
		if (blend != MLIB_BLEND_GTK_SRC) {
			if (alp_ind == -1) {
				tdp--;
			}
			for (i = 0; i < width; i++) {
				((mlib_s32 *)buffd)[i] =
				    *(mlib_s32 *)(tdp + 3 * i);
			}

			if (alp_ind == -1) {
				for (i = 0; i < width2; i++) {
					__m128i a0, s0, d0, dd;

					BLEND43_SRC_OVER(0);
				}
				mlib_s_ImageChannelExtract_U8_43R_D1((void *)
				    buffd, dp, width);
			} else {
				for (i = 0; i < width2; i++) {
					__m128i a0, s0, d0, dd;

					BLEND43_SRC_OVER(0xff);
				}
				mlib_s_ImageChannelExtract_U8_43L_D1((void *)
				    buffd, dp, width);
			}
		} else {
			mlib_u8 *buffi = (mlib_u8 *)buffz + 1;

			if (alp_ind == -1)
				buffi += 2;
			for (i = 0; i < width; i++) {
				tdp[0] = buffi[0];
				tdp[1] = buffi[2];
				tdp[2] = buffi[4];
				tdp += 3;
				buffi += 8;
			}
		}
	} else {	/* if (chan_d == 4) */

		if (alp_ind == -1) {
			tdp--;
		}
		if (blend == MLIB_BLEND_GTK_SRC) {
			mlib_u8 *p_alp = (mlib_u8 *)buffz + 1;
			mlib_s32 tail = ((mlib_s32 *)tdp)[width];

			if (alp_ind != -1)
				p_alp += 6;
			for (i = 0; i < width2; i++) {
				__m128i a0, a1, aa, ss, d0, dd;

				ss = buffz[i];
				a0 = _mm_loadl_epi64((void *)((mlib_d64 *)
				    mlib_m_tbl_255DivAlpha + p_alp[0]));
				a1 = _mm_loadl_epi64((void *)((mlib_d64 *)
				    mlib_m_tbl_255DivAlpha + p_alp[8]));
				aa = _mm_unpacklo_epi64(a0, a1);
				aa = _mm_or_si128(amask256,
				    _mm_andnot_si128(amaskffff, aa));
				d0 = _mm_mulhi_epu16(ss, aa);
				dd = _mm_packus_epi16(d0, d0);
				_mm_storel_epi64((void *)(tdp + 8 * i), dd);
				p_alp += 16;
			}

			((mlib_s32 *)tdp)[width] = tail;
		} else {
			mlib_blend blend = param->blend;
			mlib_d64 alp = (param->alpha) * (1.0 / 255);
			__m128i buff[1];
			__m128i done;
			__m128i ss, dd, s0, s1, d0, d1, a0, a1, r0, r1, rr, dr;
			__m128i wi, aa, amask, a16mask, zero_mask_i;
			__m128 dalp, div255, alpha, fone;
			__m128 af, sf, w0, w1, w1s, w, rw, w0r, w1r, scale;
			__m128 zero_mask, f_rnd;
			mlib_m128 s0u, s1u, s2u, s3u;

			done = _mm_set1_epi16(1 << 14);
			amask = _mm_set1_epi32(mask255);
			a16mask = _mm_set1_epi32(0xFFFF);

			dalp = _mm_set_ps1(alp * (1.0 / 256));
			fone = _mm_set_ps1(1.0);
			div255 = _mm_set_ps1(1.0 / 255);
			scale = _mm_set_ps1(1 << 8);
			alpha = _mm_set_ps1((float)(param->alpha) + 0.5);
			f_rnd = _mm_set_ps1(0.6);

			if (blend == MLIB_BLEND_GTK_SRC_OVER2) {
				if (alp_ind == -1) {
					for (i = 0; i < width / 4; i++) {
						BLEND44(SRC_OVER2, 0);
						_mm_storeu_si128((__m128i *)
						    tdp, dr);
						tdp += 16;
					}
					if (width & 3) {
						BLEND44(SRC_OVER2, 0);
						buff[0] = dr;
					}
				} else {
					for (i = 0; i < width / 4; i++) {
						BLEND44(SRC_OVER2, 3);
						_mm_storeu_si128((__m128i *)
						    tdp, dr);
						tdp += 16;
					}
					if (width & 3) {
						BLEND44(SRC_OVER2, 3);
						buff[0] = dr;
					}
				}
			} else {
				if (alp_ind == -1) {
					for (i = 0; i < width / 4; i++) {
						BLEND44(SRC_OVER, 0);
						_mm_storeu_si128((__m128i *)
						    tdp, dr);
						tdp += 16;
					}
					if (width & 3) {
						BLEND44(SRC_OVER, 0);
						buff[0] = dr;
					}
				} else {
					for (i = 0; i < width / 4; i++) {
						BLEND44(SRC_OVER, 3);
						_mm_storeu_si128((__m128i *)
						    tdp, dr);
						tdp += 16;
					}
					if (width & 3) {
						BLEND44(SRC_OVER, 3);
						buff[0] = dr;
					}
				}
			}

			for (i = 0; i < (width & 3); i++) {
				((mlib_s32 *)tdp)[i] = ((mlib_s32 *)buff)[i];
			}
		}
	}
}