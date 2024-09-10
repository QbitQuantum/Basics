 FatalConditionHandler::FatalConditionHandler() {
     isSet = true;
     // 32k seems enough for Catch to handle stack overflow,
     // but the value was found experimentally, so there is no strong guarantee
     guaranteeSize = 32 * 1024;
     exceptionHandlerHandle = nullptr;
     // Register as first handler in current chain
     exceptionHandlerHandle = AddVectoredExceptionHandler(1, handleVectoredException);
     // Pass in guarantee size to be filled
     SetThreadStackGuarantee(&guaranteeSize);
 }