Container *AnimationRecipe::setUpAnimationEgg()
{
    Container *animationEggContainer = new Container();
    animationEggContainer->setLayout(new AbsoluteLayout());

    // The egg image
    ImageView *eggImage = ImageView::create("asset:///images/animation/egg_isolated.png");
    eggImage->setLayoutProperties(AbsoluteLayoutProperties::create().x(40));
    eggImage->setObjectName("eggImage");

    // The egg shadow put beneath the egg in Y direction
    ImageView *shadowImage = ImageView::create("asset:///images/animation/egg_isolated_shadow.png");
    shadowImage->setLayoutProperties(AbsoluteLayoutProperties::create().y(150));
    shadowImage->setObjectName("shadowImage");

    // The egg rotates around half the full height (the bottom of the egg),
    // the pivot point is in the middle of the image to start.
    eggImage->setPivotY(203 / 2);

    // The shadow rotates around half its height,
    // the pivot point is in the middle of the image to start.
    shadowImage->setPivotY(-297 / 2);

    // Add the images to the Container.
    animationEggContainer->add(shadowImage);
    animationEggContainer->add(eggImage);

    animationEggContainer->setClipContentToBounds(false);

    return animationEggContainer;
}