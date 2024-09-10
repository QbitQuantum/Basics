	MPuint MPuint::operator-(const MPuint& mpu)
	{
		MPuint out;
		LPuint *a1 = m_data->A, *a2 = mpu.m_data->A, *a3 = out.m_data->A;
		int l1 = m_data->len, l2 = mpu.m_data->len;
		
		out.m_data->len = l1;
		unsigned char rem = 0;
		for (int i = 0; i < l2; i++)
		{
			rem = _subborrow_u64(rem, a1[i], a2[i], a3 + i);
		}
		if (rem == 0)
			memcpy(a3 + l2, a1 + l2, (l1 - l2) * sizeof(LPuint));
		else
		{
			for (int i = l2; i < l1; i++)
			{
				rem = _subborrow_u64(rem, a1[i], 0, a3 + i);
			}
		}
		while (a3[out.m_data->len - 1] == 0)
			out.m_data->len--;
		return out;
	}