 bool ProcessInfo::MemWrite(ptr address, const void* buffer, ptr size)
 {
     return !!WriteProcessMemory(this->hProcess, reinterpret_cast<void*>(address), buffer, size, nullptr);
 }