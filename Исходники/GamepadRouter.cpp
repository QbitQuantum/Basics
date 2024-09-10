bool GamepadRouter::GamepadControllerFactory::intersects(
        const ControllerFactory& otherFactory) const {
    const GamepadControllerFactory* otherGamepadFactory =
            dynamic_cast<const GamepadControllerFactory*>(&otherFactory);
    if (otherGamepadFactory) {
        return intersects(*otherGamepadFactory);
    }
    return false;
}