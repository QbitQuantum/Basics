void AbstractFunction::resolveAddress()
{
    auto & currentState = state();

    if (currentState.initialized)
        return;

    currentState.address = getProcAddress(m_name);
    currentState.initialized = true;
}