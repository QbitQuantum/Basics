void TParticleData::ForcesCircle(std::vector<PxVec3>* forces, CParticlesEmitter* emitter)
{
	float r = emitter->m_shape_emitter.radius;
	auto forces_vec = *forces;
	for (int idx = 0; idx < forces_vec.size(); idx++) {
		PxVec3 dir = positionBuffer[idx] - positionInitBuffer[idx];
		float w = 2 * PI / sinf(shader_ctes_globals.world_time);
		float a = w*w*r;
		dir.normalize();
		forces_vec[idx] = dir * a;
	}

	*forces = forces_vec;
}