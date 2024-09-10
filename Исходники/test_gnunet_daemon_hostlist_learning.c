int
main (int argc, char *argv[])
{
  int ret;

  GNUNET_DISK_directory_remove ("/tmp/test-gnunet-hostlist-peer-1");
  GNUNET_DISK_directory_remove ("/tmp/test-gnunet-hostlist-peer-2");
  GNUNET_log_setup ("test-gnunet-daemon-hostlist",
                    "WARNING",
                    NULL);
#if !WINDOWS
  system ("gnunet-peerinfo -s -c test_learning_adv_peer.conf > /dev/null");
  system ("gnunet-peerinfo -s -c test_learning_learn_peer.conf > /dev/null");
#else
  system ("gnunet-peerinfo -s -c test_learning_adv_peer.conf > NUL");
  system ("gnunet-peerinfo -s -c test_learning_learn_peer.conf > NUL");
#endif
  ret = check ();
  GNUNET_DISK_directory_remove ("/tmp/test-gnunet-hostlist-peer-1");
  GNUNET_DISK_directory_remove ("/tmp/test-gnunet-hostlist-peer-2");
  if (GNUNET_YES == GNUNET_DISK_file_test ("hostlists_learn_peer.file"))
  {
    if (0 == UNLINK ("hostlists_learn_peer.file"))
      GNUNET_log (GNUNET_ERROR_TYPE_INFO,
                  "Hostlist file hostlists_learn_peer.file was removed\n");
  }
  return ret;
}