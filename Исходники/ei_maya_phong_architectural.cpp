	color getPhong(
		const normal& i_N, const vector& i_V, const float cosinePower, 
		const eiBool i_keyLightsOnly, const eiBool unshadowed)
	{
		color C = 0.0f;
		vector R = reflect( normalize(i_V), normalize(i_N) );
		LightSampler	sampler(this, P, i_N, PI/2.0f );


			float isKeyLight = 1;
			//if( i_keyLightsOnly != 0 )
			//{
			//	lightsource( "iskeylight", isKeyLight );
			//}
			if( isKeyLight != 0 )
			{
				const float nonspecular = 0.0f;
				//lightsource( "__nonspecular", nonspecular );
				if( nonspecular < 1 )
				{
					//SAMPLE_LIGHT_2(color, C, 0.0f,
					//	C += Cl()*pow(max<float>(0.0f,R%Ln),cosinePower)*(1.0f-nonspecular);
					//);
					while (sampler.sample())
					{
						vector Ln = normalize(L);
						C += Cl*pow(max<float>(0.0f,R%Ln),cosinePower)*(1.0f-nonspecular);
					}
				}
			}

		return C;
	}