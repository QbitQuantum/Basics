void InputFilter::setEnabled (lua_State *L, bool v)
{
    ensureAlive();
    if (enabled == v) return;
    enabled = v;
    if (enabled) {
        // If enabling, release all masked buttons below.
        BindingSet masked;
        for (auto i=buttonCallbacks.begin(), i_=buttonCallbacks.end() ; i != i_ ; ++i) {
            masked.insert(i->first);
        }
        IFMap::iterator i = ifmap.find(this->order);
        i++;
        for ( ; i != ifmap.end(); ++i) {
            i->second->flushSet(L, masked);
        }
    } else {
        // If disabling, release all local buttons.
        flushAll(L);
    }

    enabled = v;
    update_grabbed();
}