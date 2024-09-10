int main(int argc, char* argv[]) {
  char *ptr = (char *)malloc(3);

  offset = 1;

  __builtin_assume_aligned(ptr + 2, 0x8000, offset);
  // CHECK: {{.*}}alignment-assumption-{{.*}}.cpp:[[@LINE-1]]:32: runtime error: assumption of 32768 byte alignment (with offset of 1 byte) for pointer of type 'char *' failed
  // CHECK: 0x{{.*}}: note: offset address is {{.*}} aligned, misalignment offset is {{.*}} byte

  free(ptr);

  return 0;
}