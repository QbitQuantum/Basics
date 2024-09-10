void EngineStateManager::requestPopEngine()
{
    if (gameEngineStack.size() > 0)
    {
        Engine* top = getActiveEngine();
        if (top)
        {
            top->exit();
            cleanup.push_back(top);
            gameEngineStack.pop_back();
            top = getActiveEngine();
            if (top) top->enter();
        }
    }
    else
        std::cout << "WARNING: No more engines to pop!\n";
}