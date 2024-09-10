NS_IMETHODIMP ExternalWrapper::Init(nsIDOMWindow* suppliedWindow,
    PRBool *_retval) {
#else
NS_IMETHODIMP ExternalWrapper::Init(nsIDOMWindow* suppliedWindow,
    bool *_retval) {
#endif //GECKO_VERSION

  Debug::log(Debug::Debugging) << "Plugin initialized from hosted.html"
      << Debug::flush;
  *_retval = false;
  nsCOMPtr<nsIDOMWindow> computedWindow;
  if (getWindowObject(getter_AddRefs(computedWindow))) {
    Debug::log(Debug::Debugging) << " passed window=" << suppliedWindow
        << ", computed=" << computedWindow << Debug::flush;
    domWindow = computedWindow;
  } else {
    Debug::log(Debug::Warning) << " using supplied window object"
        << Debug::flush;
    // TODO(jat): remove this
    domWindow = suppliedWindow;
  }
  if (getTopWindow(domWindow, getter_AddRefs(topWindow), url)) {
    *_retval = true;
  }
  return NS_OK;
}