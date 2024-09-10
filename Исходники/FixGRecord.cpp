static bool
FixGRecord(NLineReader &reader, TextWriter &writer)
{
  GRecord grecord;
  grecord.Initialize();

  char digest[GRecord::DIGEST_LENGTH + 1];
  grecord.GetDigest(digest);

  char *line;
  while ((line = reader.ReadLine()) != nullptr) {
    if (line[0] == 'G')
      break;

    if (memcmp(line, "HFFTYFRTYPE:XCSOAR,XCSOAR ", 26) == 0) {
      char *v = strstr(line + 25, " 6.5 ");
      if (v != nullptr) {
        static char buffer[1024], *p = buffer;

        size_t n = v + 4 - line;
        memcpy(p, line, n);
        p += n;

        memcpy(p, "fix", 3);
        p += 3;

        strcpy(p, v + 4);

        line = buffer;
      }
    }

    grecord.AppendRecordToBuffer(line);

    if (!writer.WriteLine(line))
      return false;
  }

  grecord.FinalizeBuffer();
  grecord.WriteTo(writer);
  return true;
}