		void xnAudioSourcePush3D(xnAudioSource* source, float* ppos, float* pforward, float* pup, float* pvel)
		{
			float4 pos;
			memcpy(&pos, ppos, sizeof(float) * 3);
			float4 forward;
			memcpy(&forward, pforward, sizeof(float) * 3);
			float4 up;
			memcpy(&up, pup, sizeof(float) * 3);
			float4 vel;
			memcpy(&vel, pvel, sizeof(float) * 3);

#ifdef __clang__ //resharper does not know about opencl vectors

			// To evaluate the Doppler effect we calculate the distance to the listener from one wave to the next one and divide it by the sound speed
			// we use 343m/s for the sound speed which correspond to the sound speed in the air.
			// we use 600Hz for the sound frequency which correspond to the middle of the human hearable sounds frequencies.

			auto dopplerShift = 1.0f;

			auto vecListEmit = pos - source->listener->pos;
			auto distListEmit = npLengthF4(vecListEmit);

			// avoid useless calculations.
			if (!(vel.x == 0 && vel.y == 0 && vel.z == 0 && source->listener->velocity.x == 0 && source->listener->velocity.y == 0 && source->listener->velocity.z == 0))
			{
				auto vecListEmitNorm = vecListEmit;
				if (distListEmit > ZeroTolerance)
				{
					auto inv = 1.0f / distListEmit;
					vecListEmitNorm *= inv;
				}

				auto vecListEmitSpeed = vel - source->listener->velocity;
				auto speedDot = vecListEmitSpeed[0] * vecListEmitNorm[0] + vecListEmitSpeed[1] * vecListEmitNorm[1] + vecListEmitSpeed[2] * vecListEmitNorm[2];
				if (speedDot < -SoundSpeed) // emitter and listener are getting closer more quickly than the speed of the sound.
				{
					dopplerShift = MaxValue; //positive infinity
				}
				else
				{
					auto timeSinceLastWaveArrived = 0.0f; // time elapsed since the previous wave arrived to the listener.
					auto lastWaveDistToListener = 0.0f; // the distance that the last wave still have to travel to arrive to the listener.
					const auto DistLastWave = SoundPeriod * SoundSpeed; // distance traveled by the previous wave.
					if (DistLastWave > distListEmit)
						timeSinceLastWaveArrived = (DistLastWave - distListEmit) / SoundSpeed;
					else
						lastWaveDistToListener = distListEmit - DistLastWave;

					auto nextVecListEmit = vecListEmit + SoundPeriod * vecListEmitSpeed;
					auto nextWaveDistToListener = sqrtf(nextVecListEmit[0] * nextVecListEmit[0] + nextVecListEmit[1] * nextVecListEmit[1] + nextVecListEmit[2] * nextVecListEmit[2]);
					auto timeBetweenTwoWaves = timeSinceLastWaveArrived + (nextWaveDistToListener - lastWaveDistToListener) / SoundSpeed;
					auto apparentFrequency = 1 / timeBetweenTwoWaves;
					dopplerShift = apparentFrequency / SoundFreq;
				}
			}

			source->doppler_pitch = dopplerShift;
			auto pitch = source->pitch * dopplerShift;
			pitch = pitch > 4.0f ? 4.0f : pitch < -4.0f ? -4.0f : pitch;
			(*source->playRate)->SetRate(source->playRate, SLpermille(pitch * 1000.0f));

			// After an analysis of the XAudio2 left/right stereo balance with respect to 3D world position, 
			// it could be found the volume repartition is symmetric to the Up/Down and Front/Back planes.
			// Moreover the left/right repartition seems to follow a third degree polynomial function:
			// Volume_left(a) = 2(c-1)*a^3 - 3(c-1)*a^2 + c*a , where c is a constant close to c = 1.45f and a is the angle normalized bwt [0,1]
			// Volume_right(a) = 1-Volume_left(a)

			// As for signal attenuation wrt distance the model follows a simple inverse square law function as explained in XAudio2 documentation 
			// ( http://msdn.microsoft.com/en-us/library/windows/desktop/microsoft.directx_sdk.x3daudio.x3daudio_emitter(v=vs.85).aspx )
			// Volume(d) = 1                    , if d <= ScaleDistance where d is the distance to the listener
			// Volume(d) = ScaleDistance / d    , if d >= ScaleDistance where d is the distance to the listener

			auto attenuationFactor = distListEmit <= 1.0f ? 1.0f : 1.0f / distListEmit;

			// 2. Left/Right balance.
			auto repartRight = 0.5f;
			float4 rightVec = npCrossProductF4(source->listener->forward, source->listener->up);

			float4 worldToList[4];
			npMatrixIdentityF4(worldToList);
			worldToList[0].x = rightVec.x;
			worldToList[0].y = source->listener->forward.x;
			worldToList[0].z = source->listener->up.x;
			worldToList[1].x = rightVec.y;
			worldToList[1].y = source->listener->forward.y;
			worldToList[1].z = source->listener->up.y;
			worldToList[2].x = rightVec.z;
			worldToList[2].y = source->listener->forward.z;
			worldToList[2].z = source->listener->up.z;

			auto vecListEmitListBase = npTransformNormalF4(vecListEmit, worldToList);
			auto vecListEmitListBaseLen = npLengthF4(vecListEmitListBase);
			if(vecListEmitListBaseLen > 0.0f)
			{
				const auto c = 1.45f;
				auto absAlpha = fabsf(atan2f(vecListEmitListBase.y, vecListEmitListBase.x));
				auto normAlpha = absAlpha / (E_PI / 2.0f);
				if (absAlpha > E_PI / 2.0f) normAlpha = 2.0f - normAlpha;
				repartRight = 0.5f * (2 * (c - 1) * normAlpha * normAlpha * normAlpha - 3 * (c - 1) * normAlpha * normAlpha * normAlpha + c * normAlpha);
				if (absAlpha > E_PI / 2.0f) repartRight = 1 - repartRight;
			}

			xnAudioSourceSetPan(source, repartRight - 0.5);
			source->localizationGain = attenuationFactor;
			xnAudioSourceSetGain(source, source->gain);
#endif
		}