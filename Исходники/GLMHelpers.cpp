//  Helper function returns the positive angle (in radians) between two 3D vectors
float angleBetween(const glm::vec3& v1, const glm::vec3& v2) {
    return acosf((glm::dot(v1, v2)) / (glm::length(v1) * glm::length(v2)));
}