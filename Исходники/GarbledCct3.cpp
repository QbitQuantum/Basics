void GarbledCct3::evl_next_gen_inp_com(const Bytes &row, size_t kx)
{
	Bytes out(m_gen_inp_decom[0].size());

	for (size_t jx = 0; jx < Env::circuit().gen_inp_cnt(); jx++)
	{
		if (row.get_ith_bit(jx)) { out ^= m_gen_inp_decom[jx]; }
	}

	byte bit = out.get_ith_bit(0);

	static Bytes tmp;

	Bytes::iterator it = m_i_bufr_ix + bit*Env::key_size_in_bytes();

	__m128i aes_key, aes_plaintext, aes_ciphertext, out_key;

	tmp.assign(out.begin(), out.begin()+Env::key_size_in_bytes());
	tmp.resize(16, 0);
	aes_key = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

	aes_plaintext = _mm_set1_epi64x((uint64_t)kx);

	KDF128((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)&aes_key);
	aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);

	tmp.assign(it, it+Env::key_size_in_bytes());
	tmp.resize(16, 0);
	out_key = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));
	out_key = _mm_xor_si128(out_key, aes_ciphertext);

	bit = _mm_extract_epi8(out_key, 0) & 0x01;
	m_gen_inp_hash.set_ith_bit(kx, bit);

	m_i_bufr_ix += 2*Env::key_size_in_bytes();

//	tmp.resize(16);
//	_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), out_key);
//	std::cout << "EVL " << m_gen_inp_hash_ix << " : " << tmp.to_hex() << std::endl;

	m_gen_inp_hash_ix++;
}