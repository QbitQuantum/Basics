void SocketHelperFunctions::unmarshalArrayFromBufferAsTypeIntoExistingMemory(char *&buffer, std::pair<llvm::Type::TypeID, unsigned> typeIDAndBitwidthPointedTo, void* pointerToMemory) {
    int64_t numberOfElements = strtoll(buffer, &buffer, 10);
    buffer++;

    switch (typeIDAndBitwidthPointedTo.first) {
    case llvm::Type::FloatTyID:
        for (int i = 0; i != numberOfElements; i++) {
            ((float*)pointerToMemory)[i] = strtod(buffer, &buffer);
            buffer++;
        }
        break;
    case llvm::Type::DoubleTyID:
        for (int i = 0; i != numberOfElements; i++) {
            ((double*)pointerToMemory)[i] = strtod(buffer, &buffer);
            buffer++;
        }
        break;
    case llvm::Type::X86_FP80TyID:
    case llvm::Type::FP128TyID:
        for (int i = 0; i != numberOfElements; i++) {
            ((long double*)pointerToMemory)[i] = strtold(buffer, &buffer);
            buffer++;
        }
        break;
    case llvm::Type::IntegerTyID:
        switch(typeIDAndBitwidthPointedTo.second) {
        case 8:
            for (int i = 0; i != numberOfElements; i++) {
                ((int8_t*)pointerToMemory)[i] = strtol(buffer, &buffer, 16);
                buffer++;
            }
            break;
        case 16:
            for (int i = 0; i != numberOfElements; i++) {
                ((int16_t*)pointerToMemory)[i] = strtol(buffer, &buffer, 16);
                buffer++;
            }
            break;
        case 32:
            for (int i = 0; i != numberOfElements; i++) {
                ((int32_t*)pointerToMemory)[i] = strtol(buffer, &buffer, 16);
                buffer++;
            }
            break;
        case 64:
            for (int i = 0; i != numberOfElements; i++) {
                ((int64_t*)pointerToMemory)[i] = strtoll(buffer, &buffer, 16);
                buffer++;
            }
            break;
        default:
            for (int i = 0; i != numberOfElements; i++) {
                ((int*)pointerToMemory)[i] = strtol(buffer, &buffer, 16);
                buffer++;
            }
        }
        break;
    default:
        std::cerr << "LLVM TypeID " << typeIDAndBitwidthPointedTo.first << " is not supported as array element.\n";
        exit(1);
    }
    buffer--;

    return;
}