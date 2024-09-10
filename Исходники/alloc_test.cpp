int main() {

  Allocator a = Allocator();
  
  char *c;
  c = (char *)a.alloc(16);
  // at this point the memory should all be set to 0xDEAD, repeating
  for (size_t i = 0; i < 16; ++i) {
    std::cout << char(*(c + i) + 55);
  }
  std::cout << std::endl;

  *c = 'A';
  
  std::cout << *c << std::endl;

  a.free(c);
  
  return(0);
}