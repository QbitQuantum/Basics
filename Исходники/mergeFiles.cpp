/*!   Converts multiple files
 *
 *    @param dirPath    - path to directory
 *
 *    @param filename   - name of file, may include wild-cards
 */
int convertDirectory(const wxString &dirPath, const wxString &filename, MyTraverser &converter ) {
   wxDir directory(dirPath);

   fprintf(stdout, "------------------------------------------------------------------\n");
   fprintf(stdout, "   convertDirectory(): \n"
                   "      dirPath = \'%s\'\n"
                   "      filename = \'%s\'\n",
                   (const char *)dirPath.ToAscii(),
                   (const char *)filename.ToAscii() );
//   printf("Processing Pattern %s\n", (const char *)dirPath.ToAscii());
   directory.Traverse(converter, filename, wxDIR_FILES);
   fprintf(stdout, "------------------------------------------------------------------\n");
   return converter.getRc();
}