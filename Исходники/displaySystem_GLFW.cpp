void mouse_button_callback(GLFWwindow* window, int key, int action, int mods)
{
    ServiceManager* sm = SystemManager::instance()->getServiceManager();
    sm->lockEvents();
    Event* evt = sm->writeHead();

    Event::Type et = Event::Down;
    if (action == GLFW_RELEASE) et = Event::Up;

    evt->reset(et, Service::Pointer);

    uint keyFlagsToRemove = 0;

    HANDLE_KEY_FLAG(GLFW_MOUSE_BUTTON_1, Button1);
    HANDLE_KEY_FLAG(GLFW_MOUSE_BUTTON_2, Button2);
    HANDLE_KEY_FLAG(GLFW_MOUSE_BUTTON_3, Button3);

    evt->setFlags(sKeyFlags);
    sKeyFlags &= ~keyFlagsToRemove;
    sm->unlockEvents();
}