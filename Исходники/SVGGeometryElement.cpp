void SVGGeometryElement::toClipPath(Path& path) const {
  path = asPath();
  path.transform(calculateAnimatedLocalTransform());

  ASSERT(layoutObject());
  ASSERT(layoutObject()->style());
  path.setWindRule(layoutObject()->style()->svgStyle().clipRule());
}