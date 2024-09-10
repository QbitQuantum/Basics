void HuboPlus::KState::setXform(const Transform3& t) {
  body_pos = t.translation();
  body_rot = t.rotation();
}