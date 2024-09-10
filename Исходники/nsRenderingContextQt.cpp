NS_IMETHODIMP nsRenderingContextQt::InvertRect(const nsRect &aRect)
{
  return InvertRect(aRect.x,aRect.y,aRect.width,aRect.height);
}