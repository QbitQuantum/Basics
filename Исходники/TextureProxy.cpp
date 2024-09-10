TextureProxy::TextureProxy(const Proxy<res::Image> &image, vid::opengl::TextureFormat format, vid::opengl::TextureFlags flags, const math::Vector<2, bool> &clamp) :
    BasicProxy<vid::opengl::Texture>(MakeSignature(image, format, flags, clamp)),
    image(image), format(format), flags(flags), clamp(clamp) {}