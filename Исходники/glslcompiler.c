int
main(int argc, char *argv[])
{
   GLuint shader = 0;

   ParseOptions(argc, argv);

   if (!CreateContext()) {
      fprintf(stderr, "%s: Failed to create compiler context\n", Prog);
      exit(1);
   }

   if (Options.VertFile) {
      shader = CompileShader(Options.VertFile, GL_VERTEX_SHADER);
   }
   else if (Options.FragFile) {
      shader = CompileShader(Options.FragFile, GL_FRAGMENT_SHADER);
   }

   if (shader) {
      if (Options.OutputFile) {
         fclose(stdout);
         /*stdout =*/ freopen(Options.OutputFile, "w", stdout);
      }
      if (stdout) {
         PrintShaderInstructions(shader, stdout);
      }
      if (Options.OutputFile) {
         fclose(stdout);
      }
   }

   return 0;
}