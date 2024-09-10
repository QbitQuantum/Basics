  void GboxInstance::DidChangeView(const pp::Rect& position,
                                  const pp::Rect& clip) {
    if (position.size().width() == width() &&
        position.size().height() == height())
      return;  // Size didn't change, no need to update anything.

    // Create a new device context with the new size.
    DestroyContext();
    CreateContext(position.size());
    // Delete the old pixel buffer and create a new one.
    ScopedMutexLock scoped_mutex(&pixel_buffer_mutex_);
    delete pixel_buffer_;
    pixel_buffer_ = NULL;
    if (graphics_2d_context_ != NULL) {
      pixel_buffer_ = new pp::ImageData(this,
                                        PP_IMAGEDATAFORMAT_BGRA_PREMUL,
                                        graphics_2d_context_->size(),
                                        false);
    }
  }