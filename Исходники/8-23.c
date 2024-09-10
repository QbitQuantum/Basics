int main() {
  int status;
  if ((status = System("date")) < 0) err_sys("System error");
  pr_exit(status);

  if ((status = System("nosuchcommond")) < 0) err_sys("System error");
  pr_exit(status);

  if ((status = System("who; exit 44")) < 0) err_sys("System error");
  pr_exit(status);
}