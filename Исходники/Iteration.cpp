void
js::CloseIterator(JSObject* obj)
{
    if (obj->is<PropertyIteratorObject>()) {
        /* Remove enumerators from the active list, which is a stack. */
        NativeIterator* ni = obj->as<PropertyIteratorObject>().getNativeIterator();

        ni->unlink();

        MOZ_ASSERT(ni->flags & JSITER_ACTIVE);
        ni->flags &= ~JSITER_ACTIVE;

        /*
         * Reset the enumerator; it may still be in the cached iterators
         * for this thread, and can be reused.
         */
        ni->props_cursor = ni->props_array;
    }
}