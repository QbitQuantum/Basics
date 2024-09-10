NS_IMETHODIMP
nsThebesRenderingContext::InvertRect(nscoord aX, nscoord aY, nscoord aWidth, nscoord aHeight)
{
    return InvertRect(nsRect(aX, aY, aWidth, aHeight));
}