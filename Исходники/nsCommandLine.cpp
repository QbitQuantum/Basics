NS_IMETHODIMP
nsCommandLine::GetLength(int32_t *aResult)
{
  *aResult = int32_t(mArgs.Length());
  return NS_OK;
}