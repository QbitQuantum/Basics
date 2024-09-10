SessionImpl::~SessionImpl ()
{
  try
    {
      Uninitialize ();
    }
  catch (const exception &)
    {
    }
}