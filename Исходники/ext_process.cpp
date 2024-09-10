void f_passthru(const String& command, VRefParam return_var /* = null */) {
  ShellExecContext ctx;
  FILE *fp = ctx.exec(command.c_str());
  if (!fp) return;

  char buffer[1024];
  while (true) {
    int len = read(fileno(fp), buffer, sizeof(buffer) - 1);
    if (len == -1 && errno == EINTR) continue;
    if (len <= 0) break; // break on error or EOF
    buffer[len] = '\0';
    echo(String(buffer, len, CopyString));
  }
  int ret = ctx.exit();
  if (WIFEXITED(ret)) ret = WEXITSTATUS(ret);
  return_var = ret;
}