			particles[i].size = particles[i].size*sizeMod + sizeGrowth;

			deleteMe = false;
		}
	}

}

void CSimpleParticleSystem::Init(const float3& explosionPos, CUnit *owner GML_PARG_C)
{
	CProjectile::Init(explosionPos, owner GML_PARG_P);

	particles = new Particle[numParticles];

	float3 up = emitVector;
	float3 right = up.cross(float3(up.y,up.z,-up.x));
	float3 forward = up.cross(right);

	for(int i=0; i<numParticles; i++)
	{

		float az = gu->usRandFloat()*2*PI;
		float ay = (emitRot + emitRotSpread*gu->usRandFloat())*(PI/180.0);

		particles[i].decayrate = 1.0f/(particleLife + gu->usRandFloat()*particleLifeSpread);
		particles[i].life = 0;
		particles[i].size = particleSize + gu->usRandFloat()*particleSizeSpread;
		particles[i].pos = pos;

		particles[i].speed = ((up*emitMul.y)*cos(ay)-((right*emitMul.x)*cos(az)-(forward*emitMul.z)*sin(az))*sin(ay)) * (particleSpeed + gu->usRandFloat()*particleSpeedSpread);
	}