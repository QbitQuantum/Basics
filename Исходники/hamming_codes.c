int main(){
  struct binary_byte binary;
  int i = 0;

  binary = charToByte('Z');

  printf("Testing %c is %d:\nIn binary: ", 'Z', 'Z');

  for(i = 7; i >= 0; i--){
    printf("%d ", binary.data[i]);
  }

  printf("\nDecoded: %c\n", byteToChar(binary));
}