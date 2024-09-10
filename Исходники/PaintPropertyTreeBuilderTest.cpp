TEST_F(PaintPropertyTreeBuilderTest, EffectNodesAcrossStackingContext)
{
    setBodyInnerHTML(
        "<div id='nodeWithOpacity' style='opacity: 0.6'>"
        "  <div id='childWithStackingContext' style='position:absolute;'>"
        "    <div id='grandChildWithOpacity' style='opacity: 0.4'/>"
        "  </div"
        "</div>");

    LayoutObject& nodeWithOpacity = *document().getElementById("nodeWithOpacity")->layoutObject();
    ObjectPaintProperties* nodeWithOpacityProperties = nodeWithOpacity.objectPaintProperties();
    EXPECT_EQ(0.6f, nodeWithOpacityProperties->effect()->opacity());
    EXPECT_EQ(nullptr, nodeWithOpacityProperties->effect()->parent());
    EXPECT_EQ(nullptr, nodeWithOpacityProperties->transform());

    LayoutObject& childWithStackingContext = *document().getElementById("childWithStackingContext")->layoutObject();
    EXPECT_EQ(nullptr, childWithStackingContext.objectPaintProperties());

    LayoutObject& grandChildWithOpacity = *document().getElementById("grandChildWithOpacity")->layoutObject();
    ObjectPaintProperties* grandChildWithOpacityProperties = grandChildWithOpacity.objectPaintProperties();
    EXPECT_EQ(0.4f, grandChildWithOpacityProperties->effect()->opacity());
    EXPECT_EQ(nodeWithOpacityProperties->effect(), grandChildWithOpacityProperties->effect()->parent());
    EXPECT_EQ(nullptr, grandChildWithOpacityProperties->transform());
}