bool KeyboardRouter::KeyboardControllerFactory::intersects(
        const ControllerFactory& otherFactory) const {
    const KeyboardControllerFactory* otherKeyboardFactory =
            dynamic_cast<const KeyboardControllerFactory*>(&otherFactory);
    if (otherKeyboardFactory) {
        return intersects(*otherKeyboardFactory);
    }
    return false;
}