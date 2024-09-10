void GarbledCct::gen_next_gate(const Gate &current_gate)
{
	__m128i current_zero_key;

	if (current_gate.m_tag == Circuit::GEN_INP)
	{
		__m128i a[2];

		// zero_key = m_prng.rand(Env::k());
		static Bytes tmp;

		tmp = m_prng.rand(Env::k());
		tmp.resize(16, 0);
		current_zero_key = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[0] = m_M[2*m_gen_inp_ix+0].to_bytes().hash(Env::k());
		tmp = m_M[2*m_gen_inp_ix+0].to_bytes().hash(Env::k());
		tmp.resize(16, 0);
		a[0] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[1] = m_M[2*m_gen_inp_ix+1].to_bytes().hash(Env::k());
		tmp = m_M[2*m_gen_inp_ix+1].to_bytes().hash(Env::k());
		tmp.resize(16, 0);
		a[1] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[0] ^= zero_key; a[1] ^= zero_key ^ R;
		a[0] = _mm_xor_si128(a[0], current_zero_key);
		a[1] = _mm_xor_si128(a[1], _mm_xor_si128(current_zero_key, m_R));

		uint8_t bit = m_gen_inp_mask.get_ith_bit(m_gen_inp_ix);

		// m_o_bufr += a[bit];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), a[bit]);
		m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

		// m_o_bufr += a[1-bit];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), a[1-bit]);
		m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

		m_gen_inp_ix++;
	}
	else if (current_gate.m_tag == Circuit::EVL_INP)
	{
		__m128i a[2];

		// zero_key = m_prng.rand(Env::k());
		static Bytes tmp;

		tmp = m_prng.rand(Env::k());
		tmp.resize(16, 0);
		current_zero_key = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[0] = (*m_ot_keys)[2*m_evl_inp_ix+0];
		tmp = (*m_ot_keys)[2*m_evl_inp_ix+0];
		tmp.resize(16, 0);
		a[0] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[1] = (*m_ot_keys)[2*m_evl_inp_ix+1];
		tmp = (*m_ot_keys)[2*m_evl_inp_ix+1];
		tmp.resize(16, 0);
		a[1] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));

		// a[0] ^= zero_key; a[1] ^= zero_key ^ R;
		a[0] = _mm_xor_si128(a[0], current_zero_key);
		a[1] = _mm_xor_si128(a[1], _mm_xor_si128(current_zero_key, m_R));

		// m_o_bufr += a[0];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), a[0]);
		m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

		// m_o_bufr += a[1];
		_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), a[1]);
		m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

		m_evl_inp_ix++;
	}
	else
	{
		const vector<uint64_t> &inputs = current_gate.m_input_idx;
		assert(inputs.size() == 1 || inputs.size() == 2);

#ifdef FREE_XOR
		if (is_xor(current_gate))
		{
			current_zero_key = inputs.size() == 2?
				_mm_xor_si128(m_w[inputs[0]], m_w[inputs[1]]) : _mm_load_si128(m_w+inputs[0]);
		}
		else
#endif
		if (inputs.size() == 2) // 2-arity gates
		{
			uint8_t bit;
			__m128i aes_key[2], aes_plaintext, aes_ciphertext;
			__m128i X[2], Y[2], Z[2];
			static Bytes tmp(16, 0);

			aes_plaintext = _mm_set1_epi64x(m_gate_ix);

			X[0] = _mm_load_si128(m_w+inputs[0]);
			Y[0] = _mm_load_si128(m_w+inputs[1]);

			X[1] = _mm_xor_si128(X[0], m_R); // X[1] = X[0] ^ R
			Y[1] = _mm_xor_si128(Y[0], m_R); // Y[1] = Y[0] ^ R

			const uint8_t perm_x = _mm_extract_epi8(X[0], 0) & 0x01; // permutation bit for X
			const uint8_t perm_y = _mm_extract_epi8(Y[0], 0) & 0x01; // permutation bit for Y
			const uint8_t de_garbled_ix = (perm_y<<1)|perm_x;

			// encrypt the 0-th entry : (X[x], Y[y])
			aes_key[0] = _mm_load_si128(X+perm_x);
			aes_key[1] = _mm_load_si128(Y+perm_y);

			KDF256((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask); // clear extra bits so that only k bits left
			bit = current_gate.m_table[de_garbled_ix];

#ifdef GRR
			// GRR technique: using zero entry's key as one of the output keys
			_mm_store_si128(Z+bit, aes_ciphertext);
			Z[1-bit] = _mm_xor_si128(Z[bit], m_R);
			current_zero_key = _mm_load_si128(Z);
#else
			tmp = m_prng.rand(Env::k());
			tmp.resize(16, 0);
			Z[0] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));
			Z[1] = _mm_xor_si128(Z[0], m_R);

			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());
#endif

			// encrypt the 1st entry : (X[1-x], Y[y])
			aes_key[0] = _mm_xor_si128(aes_key[0], m_R);

			KDF256((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);
			bit = current_gate.m_table[0x01^de_garbled_ix];
			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

			// encrypt the 2nd entry : (X[x], Y[1-y])
			aes_key[0] = _mm_xor_si128(aes_key[0], m_R);
			aes_key[1] = _mm_xor_si128(aes_key[1], m_R);

			KDF256((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);
			bit = current_gate.m_table[0x02^de_garbled_ix];
			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());

			// encrypt the 3rd entry : (X[1-x], Y[1-y])
			aes_key[0] = _mm_xor_si128(aes_key[0], m_R);

			KDF256((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);
			bit = current_gate.m_table[0x03^de_garbled_ix];
			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());
		}
		else // 1-arity gates
		{
			uint8_t bit;
			__m128i aes_key, aes_plaintext, aes_ciphertext;
			__m128i X[2], Z[2];
			static Bytes tmp;

			tmp.assign(16, 0);

			aes_plaintext = _mm_set1_epi64x(m_gate_ix);

			X[0] = _mm_load_si128(m_w+inputs[0]);
			X[1] = _mm_xor_si128(X[0], m_R);

			const uint8_t perm_x = _mm_extract_epi8(X[0], 0) & 0x01;

			// 0-th entry : X[x]
			aes_key = _mm_load_si128(X+perm_x);
			KDF128((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)&aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);
			bit = current_gate.m_table[perm_x];

#ifdef GRR
			_mm_store_si128(Z+bit, aes_ciphertext);
			Z[1-bit] = _mm_xor_si128(Z[bit], m_R);
			current_zero_key = _mm_load_si128(Z);
#else
			tmp = m_prng.rand(Env::k());
			tmp.resize(16, 0);
			Z[0] = _mm_loadu_si128(reinterpret_cast<__m128i*>(&tmp[0]));
			Z[1] = _mm_xor_si128(Z[0], m_R);

			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());
#endif

			// 1-st entry : X[1-x]
			aes_key = _mm_xor_si128(aes_key, m_R);

			KDF128((uint8_t*)&aes_plaintext, (uint8_t*)&aes_ciphertext, (uint8_t*)&aes_key);
			aes_ciphertext = _mm_and_si128(aes_ciphertext, m_clear_mask);
			bit = current_gate.m_table[0x01^perm_x];
			aes_ciphertext = _mm_xor_si128(aes_ciphertext, Z[bit]);
			_mm_storeu_si128(reinterpret_cast<__m128i*>(&tmp[0]), aes_ciphertext);
			m_o_bufr.insert(m_o_bufr.end(), tmp.begin(), tmp.begin()+Env::key_size_in_bytes());
		}

		if (current_gate.m_tag == Circuit::EVL_OUT)
		{
			m_o_bufr.push_back(_mm_extract_epi8(current_zero_key, 0) & 0x01); // permutation bit
		}
		else if (current_gate.m_tag == Circuit::GEN_OUT)
		{
			m_o_bufr.push_back(_mm_extract_epi8(current_zero_key, 0) & 0x01); // permutation bit

//			// TODO: C[ix_0] = w[ix0] || randomness, C[ix_1] = w[ix1] || randomness
//			m_o_bufr += (key_pair[0] + m_prng.rand(Env::k())).hash(Env::k());
//			m_o_bufr += (key_pair[1] + m_prng.rand(Env::k())).hash(Env::k());
		}
	}

	_mm_store_si128(m_w+current_gate.m_idx, current_zero_key);

	m_gate_ix++;
}