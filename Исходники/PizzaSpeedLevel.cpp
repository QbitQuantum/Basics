// on "init" you need to initialize your instance
bool PizzaSpeedLevel::init()
{
    // 1. super init first
    if ( !Layer::init() )  return false;

    createStarsBackground("Pictures/bigStar.png",20);
    createStarsBackground("Pictures/smallStar.png",50);

    showInstructions();
    createMenu();
    addRemainingTimeLabel();
    addBackground("Pictures/PizzaSpeedBack.png");
    addSpaceShip("Pictures/PizzaSpeedShip.png");
    addTimeSlider();

    schedule( schedule_selector( PizzaSpeedLevel::update) );
    schedule( schedule_selector(PizzaSpeedLevel::updateRemainingTime));

    return true;
}