int main(int argc, char **argv) {
  Execve("/bin/ls", argv, environ);
  exit(0);
}