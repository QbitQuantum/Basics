bool FramebufferObject::isActive() const {
    return ((getActiveObject() == id_) && (id_ != 0));
}