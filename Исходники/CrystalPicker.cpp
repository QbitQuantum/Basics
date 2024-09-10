glm::i32vec2 CrystalPicker::Vec3ToMatrixPosition(glm::vec3 pos)
{
  return glm::i32vec2(nearbyintf((30 - pos.x) / 43), nearbyint((180 - pos.z) / 43));
}