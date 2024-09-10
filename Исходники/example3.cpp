VOID removeMemTainted(UINT64 addr)
{
  addressTainted.remove(addr);
  std::cout << std::hex << "\t\t\t" << addr << " is now freed" << std::endl;
}