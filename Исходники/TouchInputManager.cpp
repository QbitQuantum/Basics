void TouchInputManager::activateDebug(Entity camera) {
    for (int i=0; i<MAX_TOUCH_POINT; i++) {
        debugState[i] = theEntityManager.CreateEntity(HASH("debug_input", 0x0));
        ADD_COMPONENT(debugState[i], Transformation);
        ADD_COMPONENT(debugState[i], Anchor);
        ANCHOR(debugState[i])->parent = camera;
        ANCHOR(debugState[i])->z = 0.9999f - TRANSFORM(camera)->z;
        ADD_COMPONENT(debugState[i], Rendering);
        RENDERING(debugState[i])->show = 1;
    }
}