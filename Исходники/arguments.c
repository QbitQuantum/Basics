/** Aborta a execucao do programa, imprime informacoes da variavel errno e
 *  exibe uma mensagem de erro customizavel.
 */
void arg_abort_exec_errno(char *error_msg)
{
  perror(error_msg);
  exit(EXIT_FAILURE);
}