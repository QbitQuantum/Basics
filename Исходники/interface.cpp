static Value* invoke(const char* iid, int number, InterfaceMethod** self, ListValue* list)
{
    if (!self)
    {
        throw getErrorInstance("TypeError");
    }

    Reflect::Interface interface = es::getInterface(iid);
    Reflect::Method method(interface.getMethod(number));
    PRINTF("invoke %s.%s(%p)\n", interface.getName().c_str(), method.getName().c_str(), self);

    // Set up parameters
    Any argv[9];
    Any* argp = argv;
    int ext = 0;    // extra parameter count

    // Set this
    *argp++ = Any(reinterpret_cast<intptr_t>(self));

    // In the following implementation, we assume no out nor inout attribute is
    // used for parameters.

    Reflect::Type returnType = method.getReturnType();
    switch (returnType.getType())
    {
    case Reflect::kAny:
        // Any op(void* buf, int len, ...);
        // FALL THROUGH
    case Reflect::kString:
        // const char* op(xxx* buf, int len, ...);
        *argp++ = Any(reinterpret_cast<intptr_t>(heap));
        *argp++ = Any(sizeof(heap));
        break;
    case Reflect::kSequence:
        // int op(xxx* buf, int len, ...);
        *argp++ = Any(reinterpret_cast<intptr_t>(heap));
        ++ext;
        *argp++ = Any(static_cast<int32_t>(((*list)[0])->toNumber()));
        break;
    case Reflect::kArray:
        // void op(xxx[x] buf, ...);
        *argp++ = Any(reinterpret_cast<intptr_t>(heap));
        break;
    }

    Reflect::Parameter param = method.listParameter();
    for (int i = ext; param.next(); ++i, ++argp)
    {
        Reflect::Type type(param.getType());
        Value* value = (*list)[i];
        switch (type.getType())
        {
        case Reflect::kAny:
            // Any variant, ...
            switch (value->getType()) {
            case Value::BoolType:
                *argp = Any(static_cast<bool>(value->toBoolean()));
                break;
            case Value::StringType:
                *argp = Any(value->toString().c_str());
                break;
            case Value::NumberType:
                *argp = Any(static_cast<double>(value->toNumber()));
                break;
            case Value::ObjectType:
                if (InterfacePointerValue* unknown = dynamic_cast<InterfacePointerValue*>(value))
                {
                    *argp = Any(unknown->getObject());
                }
                else
                {
                    // XXX expose ECMAScript object
                    *argp = Any(static_cast<Object*>(0));
                }
                break;
            default:
                *argp = Any();
                break;
            }
            argp->makeVariant();
            break;
        case Reflect::kSequence:
            // xxx* buf, int len, ...
            // XXX Assume sequence<octet> now...
            *argp++ = Any(reinterpret_cast<intptr_t>(value->toString().c_str()));
            value = (*list)[++i];
            *argp = Any(static_cast<int32_t>(value->toNumber()));
            break;
        case Reflect::kString:
            *argp = Any(value->toString().c_str());
            break;
        case Reflect::kArray:
            // void op(xxx[x] buf, ...);
            // XXX expand data
            break;
        case Reflect::kObject:
            if (InterfacePointerValue* unknown = dynamic_cast<InterfacePointerValue*>(value))
            {
                *argp = Any(unknown->getObject());
            }
            else
            {
                *argp = Any(static_cast<Object*>(0));
            }
            break;
        case Reflect::kBoolean:
            *argp = Any(static_cast<bool>(value->toBoolean()));
            break;
        case Reflect::kPointer:
            *argp = Any(static_cast<intptr_t>(value->toNumber()));
            break;
        case Reflect::kShort:
            *argp = Any(static_cast<int16_t>(value->toNumber()));
            break;
        case Reflect::kLong:
            *argp = Any(static_cast<int32_t>(value->toNumber()));
            break;
        case Reflect::kOctet:
            *argp = Any(static_cast<uint8_t>(value->toNumber()));
            break;
        case Reflect::kUnsignedShort:
            *argp = Any(static_cast<uint16_t>(value->toNumber()));
            break;
        case Reflect::kUnsignedLong:
            *argp = Any(static_cast<uint32_t>(value->toNumber()));
            break;
        case Reflect::kLongLong:
            *argp = Any(static_cast<int64_t>(value->toNumber()));
            break;
        case Reflect::kUnsignedLongLong:
            *argp = Any(static_cast<uint64_t>(value->toNumber()));
            break;
        case Reflect::kFloat:
            *argp = Any(static_cast<float>(value->toNumber()));
            break;
        case Reflect::kDouble:
            *argp = Any(static_cast<double>(value->toNumber()));
            break;
        default:
            break;
        }
    }

    // Invoke method
    Register<Value> value;
    unsigned methodNumber = interface.getInheritedMethodCount() + number;
    int argc = argp - argv;
    switch (returnType.getType())
    {
    case Reflect::kAny:
        {
            Any result = apply(argc, argv, (Any (*)()) ((*self)[methodNumber]));
            switch (result.getType())
            {
            case Any::TypeVoid:
                value = NullValue::getInstance();
                break;
            case Any::TypeBool:
                value = BoolValue::getInstance(static_cast<bool>(result));
                break;
            case Any::TypeOctet:
                value = new NumberValue(static_cast<uint8_t>(result));
                break;
            case Any::TypeShort:
                value = new NumberValue(static_cast<int16_t>(result));
                break;
            case Any::TypeUnsignedShort:
                value = new NumberValue(static_cast<uint16_t>(result));
                break;
            case Any::TypeLong:
                value = new NumberValue(static_cast<int32_t>(result));
                break;
            case Any::TypeUnsignedLong:
                value = new NumberValue(static_cast<uint32_t>(result));
                break;
            case Any::TypeLongLong:
                value = new NumberValue(static_cast<int64_t>(result));
                break;
            case Any::TypeUnsignedLongLong:
                value = new NumberValue(static_cast<uint64_t>(result));
                break;
            case Any::TypeFloat:
                value = new NumberValue(static_cast<float>(result));
                break;
            case Any::TypeDouble:
                value = new NumberValue(static_cast<double>(result));
                break;
            case Any::TypeString:
                if (const char* string = static_cast<const char*>(result))
                {
                    value = new StringValue(string);
                }
                else
                {
                    value = NullValue::getInstance();
                }
                break;
            case Any::TypeObject:
                if (Object* unknown = static_cast<Object*>(result))
                {
                    ObjectValue* instance = new InterfacePointerValue(unknown);
                    instance->setPrototype(getGlobal()->get(es::getInterface(Object::iid()).getName())->get("prototype"));   // XXX Should use IID
                    value = instance;
                }
                else
                {
                    value = NullValue::getInstance();
                }
                break;
            default:
                value = NullValue::getInstance();
                break;
            }
        }
        break;
    case Reflect::kBoolean:
        value = BoolValue::getInstance(static_cast<bool>(apply(argc, argv, (bool (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kOctet:
        value = new NumberValue(static_cast<uint8_t>(apply(argc, argv, (uint8_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kShort:
        value = new NumberValue(static_cast<int16_t>(apply(argc, argv, (int16_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kUnsignedShort:
        value = new NumberValue(static_cast<uint16_t>(apply(argc, argv, (uint16_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kLong:
        value = new NumberValue(static_cast<int32_t>(apply(argc, argv, (int32_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kUnsignedLong:
        value = new NumberValue(static_cast<uint32_t>(apply(argc, argv, (uint32_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kLongLong:
        value = new NumberValue(static_cast<int64_t>(apply(argc, argv, (int64_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kUnsignedLongLong:
        value = new NumberValue(static_cast<uint64_t>(apply(argc, argv, (uint64_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kFloat:
        value = new NumberValue(static_cast<float>(apply(argc, argv, (float (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kDouble:
        value = new NumberValue(apply(argc, argv, (double (*)()) ((*self)[methodNumber])));
        break;
    case Reflect::kPointer:
        value = new NumberValue(static_cast<intptr_t>(apply(argc, argv, (intptr_t (*)()) ((*self)[methodNumber]))));
        break;
    case Reflect::kString:
        {
            heap[0] = '\0';
            Any result = apply(argc, argv, (const char* (*)()) ((*self)[methodNumber]));
            if (const char* string = static_cast<const char*>(result))
            {
                value = new StringValue(string);
            }
            else
            {
                value = NullValue::getInstance();
            }
        }
        break;
    case Reflect::kSequence:
        {
            // XXX Assume sequence<octet> now...
            int32_t count = apply(argc, argv, (int32_t (*)()) ((*self)[methodNumber]));
            if (count < 0)
            {
                count = 0;
            }
            heap[count] = '\0';
            value = new StringValue(heap);
        }
        break;
    case Reflect::kObject:
        if (Object* unknown = apply(argc, argv, (Object* (*)()) ((*self)[methodNumber])))
        {
            ObjectValue* instance = new InterfacePointerValue(unknown);
            // TODO: check Object and others
            instance->setPrototype(getGlobal()->get(es::getInterface(returnType.getQualifiedName().c_str()).getName())->get("prototype"));   // XXX Should use IID
            value = instance;
        }
        else
        {
            value = NullValue::getInstance();
        }
        break;
    case Reflect::kVoid:
        apply(argc, argv, (int32_t (*)()) ((*self)[methodNumber]));
        value = NullValue::getInstance();
        break;
    }
    return value;
}