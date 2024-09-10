 inline std::string PrettyPrint(const Eigen::Affine3d& transform_to_print, const bool add_delimiters, const std::string& separator)
 {
     UNUSED(add_delimiters);
     UNUSED(separator);
     Eigen::Vector3d vector_to_print = transform_to_print.translation();
     Eigen::Quaterniond quaternion_to_print(transform_to_print.rotation());
     return "Affine3d <x: " + std::to_string(vector_to_print.x()) + " y: " + std::to_string(vector_to_print.y()) + " z: " + std::to_string(vector_to_print.z()) + ">, <x: " + std::to_string(quaternion_to_print.x()) + " y: " + std::to_string(quaternion_to_print.y()) + " z: " + std::to_string(quaternion_to_print.z()) + " w: " + std::to_string(quaternion_to_print.w()) + ">";
 }