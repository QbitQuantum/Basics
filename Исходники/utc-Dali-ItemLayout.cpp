static void UtcDaliItemLayoutGetScrollHints()
{
  ToolkitTestApplication application;

  // Create the ItemView actor
  TestItemFactory factory;
  ItemView view = ItemView::New(factory);

  // Create a grid layout and add it to ItemView
  GridLayoutPtr gridLayout = GridLayout::New();
  view.AddLayout(*gridLayout);

  // Set the orientation of the layout to be horizontal from left to right
  ItemLayoutPtr layout = view.GetLayout(0);

  Vector2 axisScrollHint;

  layout->SetOrientation(ControlOrientation::Up);
  layout->GetXAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::ZERO, Math::MACHINE_EPSILON_1, TEST_LOCATION);
  layout->GetYAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::YAXIS, Math::MACHINE_EPSILON_1, TEST_LOCATION);

  layout->SetOrientation(ControlOrientation::Down);
  layout->GetXAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::ZERO, Math::MACHINE_EPSILON_1, TEST_LOCATION);
  layout->GetYAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::YAXIS, Math::MACHINE_EPSILON_1, TEST_LOCATION);

  layout->SetOrientation(ControlOrientation::Left);
  layout->GetXAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::XAXIS, Math::MACHINE_EPSILON_1, TEST_LOCATION);
  layout->GetYAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::ZERO, Math::MACHINE_EPSILON_1, TEST_LOCATION);

  layout->SetOrientation(ControlOrientation::Right);
  layout->GetXAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::XAXIS, Math::MACHINE_EPSILON_1, TEST_LOCATION);
  layout->GetYAxisScrollHint(axisScrollHint);
  DALI_TEST_EQUALS(axisScrollHint, Vector2::ZERO, Math::MACHINE_EPSILON_1, TEST_LOCATION);
}