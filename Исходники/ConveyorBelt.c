ConveyorBelt* makeConveyorBelt(char *filename) {
  return readFile(filename, MAX_CONVEYOR_SIZE, BUFSIZE);
}