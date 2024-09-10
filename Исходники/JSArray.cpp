// Defined in ES5.1 15.4.5.1
bool JSArray::defineOwnProperty(JSObject* object, ExecState* exec, PropertyName propertyName, const PropertyDescriptor& descriptor, bool throwException)
{
    JSArray* array = jsCast<JSArray*>(object);

    // 3. If P is "length", then
    if (propertyName == exec->propertyNames().length) {
        // All paths through length definition call the default [[DefineOwnProperty]], hence:
        // from ES5.1 8.12.9 7.a.
        if (descriptor.configurablePresent() && descriptor.configurable())
            return reject(exec, throwException, "Attempting to change configurable attribute of unconfigurable property.");
        // from ES5.1 8.12.9 7.b.
        if (descriptor.enumerablePresent() && descriptor.enumerable())
            return reject(exec, throwException, "Attempting to change enumerable attribute of unconfigurable property.");

        // a. If the [[Value]] field of Desc is absent, then
        // a.i. Return the result of calling the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length", Desc, and Throw as arguments.
        if (descriptor.isAccessorDescriptor())
            return reject(exec, throwException, "Attempting to change access mechanism for an unconfigurable property.");
        // from ES5.1 8.12.9 10.a.
        if (!array->isLengthWritable() && descriptor.writablePresent() && descriptor.writable())
            return reject(exec, throwException, "Attempting to change writable attribute of unconfigurable property.");
        // This descriptor is either just making length read-only, or changing nothing!
        if (!descriptor.value()) {
            if (descriptor.writablePresent())
                array->setLengthWritable(exec, descriptor.writable());
            return true;
        }
        
        // b. Let newLenDesc be a copy of Desc.
        // c. Let newLen be ToUint32(Desc.[[Value]]).
        unsigned newLen = descriptor.value().toUInt32(exec);
        // d. If newLen is not equal to ToNumber( Desc.[[Value]]), throw a RangeError exception.
        if (newLen != descriptor.value().toNumber(exec)) {
            exec->vm().throwException(exec, createRangeError(exec, ASCIILiteral("Invalid array length")));
            return false;
        }

        // Based on SameValue check in 8.12.9, this is always okay.
        // FIXME: Nothing prevents this from being called on a RuntimeArray, and the length function will always return 0 in that case.
        if (newLen == array->length()) {
            if (descriptor.writablePresent())
                array->setLengthWritable(exec, descriptor.writable());
            return true;
        }

        // e. Set newLenDesc.[[Value] to newLen.
        // f. If newLen >= oldLen, then
        // f.i. Return the result of calling the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length", newLenDesc, and Throw as arguments.
        // g. Reject if oldLenDesc.[[Writable]] is false.
        if (!array->isLengthWritable())
            return reject(exec, throwException, "Attempting to change value of a readonly property.");
        
        // h. If newLenDesc.[[Writable]] is absent or has the value true, let newWritable be true.
        // i. Else,
        // i.i. Need to defer setting the [[Writable]] attribute to false in case any elements cannot be deleted.
        // i.ii. Let newWritable be false.
        // i.iii. Set newLenDesc.[[Writable] to true.
        // j. Let succeeded be the result of calling the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length", newLenDesc, and Throw as arguments.
        // k. If succeeded is false, return false.
        // l. While newLen < oldLen repeat,
        // l.i. Set oldLen to oldLen – 1.
        // l.ii. Let deleteSucceeded be the result of calling the [[Delete]] internal method of A passing ToString(oldLen) and false as arguments.
        // l.iii. If deleteSucceeded is false, then
        if (!array->setLength(exec, newLen, throwException)) {
            // 1. Set newLenDesc.[[Value] to oldLen+1.
            // 2. If newWritable is false, set newLenDesc.[[Writable] to false.
            // 3. Call the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length", newLenDesc, and false as arguments.
            // 4. Reject.
            if (descriptor.writablePresent())
                array->setLengthWritable(exec, descriptor.writable());
            return false;
        }

        // m. If newWritable is false, then
        // i. Call the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length",
        //    Property Descriptor{[[Writable]]: false}, and false as arguments. This call will always
        //    return true.
        if (descriptor.writablePresent())
            array->setLengthWritable(exec, descriptor.writable());
        // n. Return true.
        return true;
    }

    // 4. Else if P is an array index (15.4), then
    // a. Let index be ToUint32(P).
    if (Optional<uint32_t> optionalIndex = parseIndex(propertyName)) {
        // b. Reject if index >= oldLen and oldLenDesc.[[Writable]] is false.
        uint32_t index = optionalIndex.value();
        // FIXME: Nothing prevents this from being called on a RuntimeArray, and the length function will always return 0 in that case.
        if (index >= array->length() && !array->isLengthWritable())
            return reject(exec, throwException, "Attempting to define numeric property on array with non-writable length property.");
        // c. Let succeeded be the result of calling the default [[DefineOwnProperty]] internal method (8.12.9) on A passing P, Desc, and false as arguments.
        // d. Reject if succeeded is false.
        // e. If index >= oldLen
        // e.i. Set oldLenDesc.[[Value]] to index + 1.
        // e.ii. Call the default [[DefineOwnProperty]] internal method (8.12.9) on A passing "length", oldLenDesc, and false as arguments. This call will always return true.
        // f. Return true.
        return array->defineOwnIndexedProperty(exec, index, descriptor, throwException);
    }

    return array->JSObject::defineOwnNonIndexProperty(exec, propertyName, descriptor, throwException);
}