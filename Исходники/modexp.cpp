int main(int argc, char *argv[]) {
  
  uint64_t result=0;
  
  if (argc != 4) {
    printf ("\nUsage: modexp <base> <exponent> <modulus>\n");
    return 0;
  }
  
  result = modexp (_strtoui64(argv[1], NULL, 10), 
    _strtoui64(argv[2], NULL, 10),
    _strtoui64(argv[3], NULL, 10)); 

  printf ("\n%llu = %s ^ %s %% %s", 
    result, argv[1], argv[2], argv[3]);
  return 0;
}