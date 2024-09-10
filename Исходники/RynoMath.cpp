	glm::vec3 ryno_math::lerp(glm::vec3 a, glm::vec3 b, F32 value){
		return glm::vec3(lerp(a.x, b.x, value), lerp(a.y, b.y, value), lerp(a.z, b.z, value));
	}