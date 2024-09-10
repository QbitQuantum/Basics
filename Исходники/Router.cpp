Router::handler_ptr Router::route(const std::string& url) {
  const auto& router = getInstance();
  return router.getHandler(url);
}