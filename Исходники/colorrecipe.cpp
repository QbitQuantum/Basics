/* This function creates a Container, inside this Container we have another Container that
 * shows a rectangle with the specified Color. That Color is also used in the Label.
 */
Container* ColorRecipe::createLabel(bb::cascades::Color myColor, const char* name)
{

    // Container that specific that we want our controllers from left to right.
    Container *groupContainer = new Container();
    groupContainer->setLayout(StackLayout::create().direction(LayoutDirection::LeftToRight).top(4));

    // Then we add a Label, the Label is padded and Color is set by calling setColor.
    Label *label = new Label();
    label->setText(name);

    label->textStyle()->setBase(SystemDefaults::TextStyles::bodyText());
    label->textStyle()->setFontWeight(FontWeight::Bold);
    label->textStyle()->setColor(myColor) ;
    label->setLayoutProperties(StackLayoutProperties::create().vertical(VerticalAlignment::Center));

    // The rectangle Container, setting Color here is made by the background property.
    Container *colorContainer = new Container();
    colorContainer->setBackground(myColor);
    colorContainer->setLayoutProperties(
            StackLayoutProperties::create().vertical(VerticalAlignment::Fill).spaceQuota(1.0));
    colorContainer->setLeftMargin(10);

    // Finally we add the created Containers to the grouping Container.
    groupContainer->add(label);
    groupContainer->add(colorContainer);

    // And we return it!
    return groupContainer;
}