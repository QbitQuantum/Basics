	float sqrtResult = sqrt(inSqrt);

	plus = (-b + sqrtResult) * divTwoA;
	minus = (-b - sqrtResult) * divTwoA;
}
*/


float dotProduct(float ax, float ay, float az, float bx, float by, float bz) {
	return ax*bx + ay*by + az*bz;
}

void raySphereForRelativeSphereVectorized(float *__restrict__ relativePositionX, float *__restrict__ relativePositionY, float *__restrict__ relativePositionZ, float *__restrict__ directionX, float *__restrict__ directionY, float *__restrict__ directionZ, float *__restrict__ r, float *__restrict__ intersect, float *__restrict__ plus, float *__restrict__ minus) {
    const unsigned BATCHSIZE = 16;

    float *alignedRelativePositionX = static_cast<float*>(__builtin_assume_aligned(relativePositionX, 32));
	float *alignedRelativePositionY = static_cast<float*>(__builtin_assume_aligned(relativePositionY, 32));
	float *alignedRelativePositionZ = static_cast<float*>(__builtin_assume_aligned(relativePositionZ, 32));

	float *alignedDirectionX = static_cast<float*>(__builtin_assume_aligned(directionX, 32));
	float *alignedDirectionY = static_cast<float*>(__builtin_assume_aligned(directionY, 32));
	float *alignedDirectionZ = static_cast<float*>(__builtin_assume_aligned(directionZ, 32));

	float *alignedIntersect = static_cast<float*>(__builtin_assume_aligned(intersect, 32));


	float *alignedPlus = static_cast<float*>(__builtin_assume_aligned(plus, 32));
	float *alignedMinus = static_cast<float*>(__builtin_assume_aligned(minus, 32));

	float *alignedR = static_cast<float*>(__builtin_assume_aligned(r, 32));
