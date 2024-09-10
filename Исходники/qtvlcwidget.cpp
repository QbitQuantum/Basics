 // This callback is called by VLC to get OpenGL functions.
 static void* get_proc_address(void* data, const char* current)
 {
     VLCVideo* that = static_cast<VLCVideo*>(data);
     QOpenGLContext *ctx = that->mWidget->context();
     return reinterpret_cast<void*>(ctx->getProcAddress(current));
 }