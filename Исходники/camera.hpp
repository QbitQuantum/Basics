 /**
  * @brief Returns the translation part of the view matrix as a vector.
  * @return The translation part of the view matrix.
  */
 Eigen::Vector3f getTranslationMatrix (void) const
 {
     return view_matrix.translation();
 }    