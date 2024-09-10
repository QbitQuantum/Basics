void* SimpleParticle::operator new(size_t count)
{
	assert(count <= sizeof(SimpleParticle));
	return particlePool.malloc();
}