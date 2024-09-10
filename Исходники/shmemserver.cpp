void ShmemServer::handle_conn()
{
#ifndef NDEBUG
    std::cout << "DEBUG" << ": got IR" << std::endl;
#endif
    // initialize backend with received IR
    auto backend = parseIRtoBackend((char *) shmemptr);
    *(long *)shmemptr = TimeDiffOpt.count();
    *(((long *)shmemptr) + 1) = TimeDiffInit.count();
    // signal to client: got IR, ready to get calls, time measures in shmem
    sem_post(shmem_sem);

    while (1) {
        sem_wait(shmem_force_order_sem);
        // wait for call
        sem_wait(shmem_sem);
        sem_post(shmem_force_order_sem);
#ifndef NDEBUG
        std::cout << "DEBUG" << ": got call \n";
#endif
        // check for exit symbol
        if (((char *)shmemptr)[0] == ';') {
#ifndef NDEBUG
            std::cout << "DEBUG" << ": found exit symbol \n";
#endif
            break;
        }

        llvm::Function* calledFunction = nullptr;
        std::vector<llvm::GenericValue> args;
        std::list<std::vector<llvm::GenericValue>::size_type> indexesOfPointersInArgs;
        llvm::GenericValue result = handleCall(backend.get(), (char *) shmemptr, calledFunction, args, indexesOfPointersInArgs);

        auto shmempos = shmemptr;
        // write measured time to memory
        *(long *)shmempos = TimeDiffLastExecution.count();
        shmempos = (long *)shmempos + 1;

        // write changes to args and result back to shared memory
        for (const auto& indexOfPtr : indexesOfPointersInArgs) {
            auto paramType = calledFunction->getFunctionType()->getParamType(indexOfPtr);
            while (paramType->getTypeID() == llvm::Type::ArrayTyID || paramType->getTypeID() == llvm::Type::PointerTyID)
                paramType = llvm::cast<llvm::SequentialType>(paramType)->getElementType();

            if (paramType->getTypeID() == llvm::Type::IntegerTyID) {
                ShmemHelperFunctions::marshallArrayOfSizeAndTypeIntoMemory(args[indexOfPtr].PointerVal, args[indexOfPtr+1].IntVal.getSExtValue(), std::pair<llvm::Type::TypeID, unsigned>(paramType->getTypeID(), ((llvm::IntegerType*)paramType)->getBitWidth()), shmempos);
            } else
                ShmemHelperFunctions::marshallArrayOfSizeAndTypeIntoMemory(args[indexOfPtr].PointerVal, args[indexOfPtr+1].IntVal.getSExtValue(), std::pair<llvm::Type::TypeID, unsigned>(paramType->getTypeID(), 0U), shmempos);

            free(args[indexOfPtr].PointerVal);
        }

        switch (calledFunction->getReturnType()->getTypeID()) {
            case llvm::Type::VoidTyID:
                // void return
                break;
            case llvm::Type::FloatTyID:
                *(float *)shmempos  = result.FloatVal;
                break;
            case llvm::Type::DoubleTyID:
                *(double *)shmempos = result.DoubleVal;
                break;
            case llvm::Type::X86_FP80TyID: {
                char tmpHexString[64];
                llvm::APFloat(llvm::APFloat::x87DoubleExtended, result.IntVal).convertToHexString(tmpHexString, 0U, false, llvm::APFloat::roundingMode::rmNearestTiesToEven);
                *(long double *)shmempos = strtold(tmpHexString, nullptr);
                break;
            }
            case llvm::Type::FP128TyID: {
                char tmpHexString[64];
                llvm::APFloat(llvm::APFloat::IEEEquad, result.IntVal).convertToHexString(tmpHexString, 0U, false, llvm::APFloat::roundingMode::rmNearestTiesToEven);
                *(long double *)shmempos = strtold(tmpHexString, nullptr);
                break;
             }
            case llvm::Type::IntegerTyID: // Note: LLVM does not differentiate between signed/unsiged int types
                switch (result.IntVal.getBitWidth()) {
                    case 8:
                        *(uint8_t *)shmempos = (uint8_t) result.IntVal.getZExtValue();
                        break;
                    case 16:
                        *(uint16_t *)shmempos = (uint16_t) result.IntVal.getZExtValue();
                        break;
                    case 32:
                        *(uint32_t *)shmempos = (uint32_t) result.IntVal.getZExtValue();
                        break;
                    case 64:
                        *(uint64_t *)shmempos = (uint64_t) result.IntVal.getZExtValue();
                        break;
                    default:
                        error(std::string("ERROR, integer bitwidth of " + std::to_string(result.IntVal.getBitWidth()) + " not supported").c_str());
                 }
                break;
            default:
            error(std::string("ERROR, LLVM TypeID " + std::to_string(calledFunction->getReturnType()->getTypeID()) + " of result of function \"" + calledFunction->getName().str() + "\" is not supported").c_str());
        }

#ifndef NDEBUG
        std::cout << "DEBUG" << ": signaling 'result is ready' to client \n";
#endif

        sem_post(shmem_sem);
    }
}