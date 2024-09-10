 int qiodevice_iostream_write_byte(void *context,
                                   const int byte)
 {
     QIODevice* io = (QIODevice*) context;
     return (io->putChar(byte) ? 0 : 1);
 }