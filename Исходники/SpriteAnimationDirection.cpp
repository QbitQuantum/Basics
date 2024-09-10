/**
 * @brief Returns the size of a frame.
 * @return The size of a frame.
 */
Rectangle SpriteAnimationDirection::get_size() const {

  Debug::check_assertion(nb_frames > 0, "Invalid number of frames");
  return Rectangle(0, 0, frames[0].get_width(), frames[0].get_height());
}