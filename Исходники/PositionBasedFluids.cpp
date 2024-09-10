// ----------------------------------------------------------------------------------------------
bool PositionBasedFluids::solveDensityConstraint(
	const unsigned int particleIndex,
	const unsigned int numberOfParticles,
	const Vector3r x[],	
	const Real mass[],
	const Vector3r boundaryX[],
	const Real boundaryPsi[],
	const unsigned int numNeighbors,
	const unsigned int neighbors[],
	const Real density0,
	const bool boundaryHandling,
	const Real lambda[],
	Vector3r &corr)
{
	// Compute position correction
	corr.setZero();
	for (unsigned int j = 0; j < numNeighbors; j++)
	{
		const unsigned int neighborIndex = neighbors[j];
		if (neighborIndex < numberOfParticles)		// Test if fluid particle
		{
			const Vector3r gradC_j = -mass[neighborIndex] / density0 * CubicKernel::gradW(x[particleIndex] - x[neighborIndex]);
			corr -= (lambda[particleIndex] + lambda[neighborIndex]) * gradC_j;
		}
		else if (boundaryHandling)
		{
			// Boundary: Akinci2012
			const Vector3r gradC_j = -boundaryPsi[neighborIndex - numberOfParticles] / density0 * CubicKernel::gradW(x[particleIndex] - boundaryX[neighborIndex - numberOfParticles]);
			corr -= (lambda[particleIndex]) * gradC_j;
		}
	}

	return true;
}