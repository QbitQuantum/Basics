static void
Instance_DidChangeView(PP_Instance instance,
		       const struct PP_Rect* position,
		       const struct PP_Rect* clip)
{
  if (position->size.width == screenWidth &&
      position->size.height == screenHeight)
    return;  // Size didn't change, no need to update anything.
  Log("change view\n");
  DestroyContext(instance);
  CreateContext(instance, &position->size);
}