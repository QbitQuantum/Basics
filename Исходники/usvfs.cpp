LONG WINAPI VEHandler(PEXCEPTION_POINTERS exceptionPtrs)
{
  if (   (exceptionPtrs->ExceptionRecord->ExceptionCode  < 0x80000000)      // non-critical
      || (exceptionPtrs->ExceptionRecord->ExceptionCode == 0xe06d7363)) {   // cpp exception
    // don't report non-critical exceptions
    return EXCEPTION_CONTINUE_SEARCH;
  }
  /*
  if (((exceptionPtrs->ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE) != 0) ||
      (exceptionPtrs->ExceptionRecord->ExceptionCode == 0xe06d7363)) {
    // don't want to break on non-critical exceptions. 0xe06d7363 indicates a C++ exception. why are those marked non-continuable?
    return EXCEPTION_CONTINUE_SEARCH;
  }
  */

  if (RemoveVectoredExceptionHandler(exceptionHandler) == 0) {
    ::MessageBoxA(nullptr, "Failed to properly report windows exception, not daring to continue", "Critical Error ^ 2", MB_OK);
    return EXCEPTION_CONTINUE_SEARCH;
  }

  auto logger = spdlog::get("usvfs");
  // ensure that the barrier won't keep future hook functions from running in case the process lives
  ON_BLOCK_EXIT([] () {
    HookLib::TrampolinePool::instance().forceUnlockBarrier();
  });

  try {
    std::pair<uintptr_t, uintptr_t> range = winapi::ex::getSectionRange(dllModule);

    uintptr_t exceptionAddress =
        reinterpret_cast<uintptr_t>(exceptionPtrs->ExceptionRecord->ExceptionAddress);

    if ((exceptionAddress < range.first) || (exceptionAddress > range.second)) {
      // exception address outside this dll
      std::wstring modName = winapi::ex::wide::getSectionName(exceptionPtrs->ExceptionRecord->ExceptionAddress);
      if (logger.get() != nullptr) {
        logger->warn("windows exception {0:x} from {1}",
                     exceptionPtrs->ExceptionRecord->ExceptionCode,
                     ush::string_cast<std::string>(modName));
      }
      // re-install exception handler
//      exceptionHandler = ::AddVectoredExceptionHandler(0, VEHandler);
      return EXCEPTION_CONTINUE_SEARCH;
    } else {
      if (logger.get() != nullptr) {
        logger->warn("windows exception {0:x}", exceptionPtrs->ExceptionRecord->ExceptionCode);
      }
    }
  } catch (const std::exception &e) {
    if (logger.get() != nullptr) {
      logger->error("windows exception from unkown module ({})", e.what());
    }
  }

  // remove hooks
  delete manager;
  manager = nullptr;

  createMiniDump(exceptionPtrs);

  return EXCEPTION_CONTINUE_SEARCH;
}