void RenderContext::getValues(const Event& event, Variant* values, std::size_t n)
{
  EVT_HANDLE handle = handle_.get();
  DWORD used = 0;
  DWORD properties = 0;
  bool success = EvtRender(
        handle,
        event.getHandle(),
        EvtRenderEventValues,
        n * sizeof(EVT_VARIANT),
        values,
        &used,
        &properties);

  if (!success) {
    throw WinException(L"EvtRender", GetLastError());
  }

  if (n * sizeof(EVT_VARIANT) > used || n != properties) {
    throw WinException(L"RenderContext::getValues", ERROR_BAD_ARGUMENTS);
  }
}