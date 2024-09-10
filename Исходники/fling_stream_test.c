int main(int argc, char **argv) {
  char *me = argv[0];
  char *lslash = strrchr(me, '/');
  char root[1024];
  int port = grpc_pick_unused_port_or_die();
  char *args[10];
  int status;
  pid_t svr, cli;
  /* seed rng with pid, so we don't end up with the same random numbers as a
     concurrently running test binary */
  srand((unsigned)getpid());
  /* figure out where we are */
  if (lslash) {
    memcpy(root, me, (size_t)(lslash - me));
    root[lslash - me] = 0;
  } else {
    strcpy(root, ".");
  }
  /* start the server */
  svr = fork();
  if (svr == 0) {
    gpr_asprintf(&args[0], "%s/fling_server", root);
    args[1] = "--bind";
    gpr_join_host_port(&args[2], "::", port);
    args[3] = "--no-secure";
    args[4] = 0;
    execv(args[0], args);

    gpr_free(args[0]);
    gpr_free(args[2]);
    return 1;
  }
  /* wait a little */
  sleep(2);
  /* start the client */
  cli = fork();
  if (cli == 0) {
    gpr_asprintf(&args[0], "%s/fling_client", root);
    args[1] = "--target";
    gpr_join_host_port(&args[2], "127.0.0.1", port);
    args[3] = "--scenario=ping-pong-stream";
    args[4] = "--no-secure";
    args[5] = 0;
    execv(args[0], args);

    gpr_free(args[0]);
    gpr_free(args[2]);
    return 1;
  }
  /* wait for completion */
  printf("waiting for client\n");
  if (waitpid(cli, &status, 0) == -1) return 2;
  if (!WIFEXITED(status)) return 4;
  if (WEXITSTATUS(status)) return WEXITSTATUS(status);
  printf("waiting for server\n");
  kill(svr, SIGINT);
  if (waitpid(svr, &status, 0) == -1) return 2;
  if (!WIFEXITED(status)) return 4;
  if (WEXITSTATUS(status)) return WEXITSTATUS(status);
  return 0;
}