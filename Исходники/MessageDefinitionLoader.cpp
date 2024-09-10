MessageDefinitionLoader::Impl::~Impl() {
  terminate();
  wait();
}