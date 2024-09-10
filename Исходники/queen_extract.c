int main(int argc, char** argv)
{
  int result = -1;
  Cookie cookie;

  memset(&cookie, 0, sizeof(Cookie));

  next_file(&cookie);

  for (;;)
  {
    uint8_t name_size;
    char* name = NULL;

#if 0
    printf("Volume %i, offset 0x%08lx\n", cookie.index, ftell(cookie.input_file));
#endif
    
    if (sizeof(name_size) != reader(&name_size, sizeof(name_size), &cookie))
      break;

    name = malloc(MAX_FILENAME_SIZE);

    if (MAX_FILENAME_SIZE != reader(name, MAX_FILENAME_SIZE, &cookie))
    {
      fprintf(stderr, "read name failed\n");
      break;
    }

    name[name_size] = '\0';
    printf("extracting: %s\n", name);

    cookie.output_file = fopen(name, "w");

    result = dynamite_explode(reader, writer, &cookie);

    FCLOSE(cookie.output_file);

    if (DYNAMITE_SUCCESS != result)
    {
      fprintf(stderr, "Error %i\n", result);
      break;
    }
  }

  FCLOSE(cookie.input_file);
  FCLOSE(cookie.output_file);
  return result;
}