TEST_F(Matrix4Test, transpose)
{
	Matrix4 m1;
	Matrix4 transposed;

	for(int i=0; i<16; i++)
	{
		m1.m_data[i] = i;
		transposed.m_data[i] = i;
	}

	transposed.transpose();

	bool passed = true;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(m1.m_data[i*4 + j] != transposed.m_data[j*4 + i])
			{
				passed = false;
			}
		}
	}

	ASSERT_EQ(passed,true);
}