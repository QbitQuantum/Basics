int main(int argc,char** argv) {
  printf("#ifdef MAIN\n");
  printf("MAP_TYPE maps[] ={\n");
  process("map11.map");    /* place the null map */
  process("map11.map");
  process("map12.map");
  process("map13.map");
  process("map14.map");
  process("map21.map");
  process("map22.map");
  process("map23.map");
  process("map24.map");
  process("map31.map");
  process("map32.map");
  process("map33.map");
  process("map34.map");
  process("radon.map");
  process("generic.map");
  process("village.map");
  process("marduk.map");
  process("nichor.map");
  process("eshter.map");
  printf("  };\n");
  printf("#else\n");
  printf("extern MAP_TYPE maps[];\n");
  printf("#endif\n");
  return 0;
  }