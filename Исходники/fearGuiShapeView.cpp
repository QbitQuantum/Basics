bool ShapeView::onAdd()
{
   RectF rect;
   float width, height;

   if (Parent::onAdd())
   {
      active = true;
      camera = new TSPerspectiveCamera(
         RectI(Point2I(0, 0),       Point2I(0, 0)),
         RectF(Point2F(0.0f, 0.0f), Point2F(0.0f, 0.0f)),
         256.0f, 1.0E8f);

      scene = new TSSceneLighting;
      scene->setAmbientIntensity(ColorF(0.7f, 0.7f, 0.7f));

      light = new TSLight;
      light->setType(TS::Light::LightDirectional);
      light->setIntensity(1.0f, 1.0f, 1.0f);
      scene->installLight(light);

      return (true);
   }

   return (false);
}