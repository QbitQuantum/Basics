void Transformer::transform() {
  // convert translation and rotation from local to global coords
  Eigen::Quaterniond refq = ref_.get_rotation();
  Eigen::Vector3d global_t(refq * t_);
  Eigen::Quaterniond global_q(pick_positive(refq * q_ * refq.conjugate()));
  // get rb centroid as a translation
  Eigen::Vector3d centroid(Referential(m_, target_).get_centroid());
  // transform each rigid member
  RigidBody d(m_, target_);
  ParticleIndexes pis(d.get_member_particle_indexes());
  for (unsigned i = 0; i < pis.size(); i++) {
    XYZ xyz(m_, pis[i]);
    Eigen::Vector3d coords;
    coords << xyz.get_x(), xyz.get_y(), xyz.get_z();
    Eigen::Vector3d newcoords = global_q * (coords - centroid) + centroid
                                    + global_t;
    xyz.set_x(newcoords(0));
    xyz.set_y(newcoords(1));
    xyz.set_z(newcoords(2));
  }
  // update rigid body
  d.set_reference_frame_from_members(pis);
}