/* readonly attribute nsIDOMSVGAnimatedLength y1; */
NS_IMETHODIMP SVGLinearGradientElement::GetY1(nsIDOMSVGAnimatedLength * *aY1)
{
  *aY1 = Y1().get();
  return NS_OK;
}