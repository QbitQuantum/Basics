JSValue collectMatches(VM& vm, ExecState* exec, JSString* string, const String& s, RegExpConstructor* constructor, RegExp* regExp, const FixEndFunc& fixEnd)
{
    auto scope = DECLARE_THROW_SCOPE(vm);

    MatchResult result = constructor->performMatch(vm, regExp, string, s, 0);
    if (!result)
        return jsNull();
    
    static unsigned maxSizeForDirectPath = 100000;
    
    JSArray* array = constructEmptyArray(exec, nullptr);
    if (UNLIKELY(vm.exception()))
        return jsUndefined();

    auto iterate = [&] () {
        size_t end = result.end;
        size_t length = end - result.start;
        array->push(exec, JSRopeString::createSubstringOfResolved(vm, string, result.start, length));
        if (!length)
            end = fixEnd(end);
        result = constructor->performMatch(vm, regExp, string, s, end);
    };
    
    do {
        if (array->length() >= maxSizeForDirectPath) {
            // First do a throw-away match to see how many matches we'll get.
            unsigned matchCount = 0;
            MatchResult savedResult = result;
            do {
                if (array->length() + matchCount >= MAX_STORAGE_VECTOR_LENGTH) {
                    throwOutOfMemoryError(exec, scope);
                    return jsUndefined();
                }
                
                size_t end = result.end;
                matchCount++;
                if (result.empty())
                    end = fixEnd(end);
                
                // Using RegExpConstructor::performMatch() instead of calling RegExp::match()
                // directly is a surprising but profitable choice: it means that when we do OOM, we
                // will leave the cached result in the state it ought to have had just before the
                // OOM! On the other hand, if this loop concludes that the result is small enough,
                // then the iterate() loop below will overwrite the cached result anyway.
                result = constructor->performMatch(vm, regExp, string, s, end);
            } while (result);
            
            // OK, we have a sensible number of matches. Now we can create them for reals.
            result = savedResult;
            do
                iterate();
            while (result);
            
            return array;
        }
        
        iterate();
    } while (result);
    
    return array;
}