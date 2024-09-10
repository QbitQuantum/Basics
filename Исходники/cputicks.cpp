uint32_t CpuTicks::now() {
  do {
    uint32_t hiResOk = CpuTicks_hiResOk;

    if (hiResOk == 1) {
      LARGE_INTEGER now;
      if (!::QueryPerformanceCounter(&now))
        break;
      return (int64_t)(double(now.QuadPart) / CpuTicks_hiResFreq);
    }

    if (hiResOk == 0) {
      LARGE_INTEGER qpf;
      if (!::QueryPerformanceFrequency(&qpf)) {
        _InterlockedCompareExchange((LONG*)&CpuTicks_hiResOk, 0xFFFFFFFF, 0);
        break;
      }

      LARGE_INTEGER now;
      if (!::QueryPerformanceCounter(&now)) {
        _InterlockedCompareExchange((LONG*)&CpuTicks_hiResOk, 0xFFFFFFFF, 0);
        break;
      }

      double freqDouble = double(qpf.QuadPart) / 1000.0;

      CpuTicks_hiResFreq = freqDouble;
      _InterlockedCompareExchange((LONG*)&CpuTicks_hiResOk, 1, 0);

      return static_cast<uint32_t>(
        static_cast<int64_t>(double(now.QuadPart) / freqDouble) & 0xFFFFFFFF);
    }
  } while (0);

  // Bail to a less precise GetTickCount().
  return ::GetTickCount();
}