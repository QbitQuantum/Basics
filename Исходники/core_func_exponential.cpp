int test_sqrt()
{
	int Error(0);

#	if GLM_ARCH & GLM_ARCH_SSE2_BIT
	for(float f = 0.1f; f < 30.0f; f += 0.1f)
	{
		float r = _mm_cvtss_f32(_mm_sqrt_ps(_mm_set1_ps(f)));
		float s = std::sqrt(f);
		Error += glm::abs(r - s) < 0.01f ? 0 : 1;
		assert(!Error);
	}
#	endif//GLM_ARCH & GLM_ARCH_SSE2_BIT

	float A = glm::sqrt(10.f);
	glm::vec1 B = glm::sqrt(glm::vec1(10.f));
	glm::vec2 C = glm::sqrt(glm::vec2(10.f));
	glm::vec3 D = glm::sqrt(glm::vec3(10.f));
	glm::vec4 E = glm::sqrt(glm::vec4(10.f));

	return Error;
}