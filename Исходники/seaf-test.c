static int
test_merge_conflicts ()
{
    SeafRepo *repo;
    char *head, *remote;
    char *file_a, *file_b, *file_bb, *file_c, *file_d, *file_e, *file_f;
    FILE *fp_a, *fp_b, *fp_c, *fp_d;
    GError *error = NULL;
    char cmd[1024];
    int ret;
    char buf[64];

    printf ("\n=== test merge conflicts\n\n");

    repo = create_repo ("merge-conflicts");

    first_commit (repo);

    sleep (2);

    printf ("*** creating branch \"test\"\n");
    /* create branch "test". */
    if (seafile_branch_add (repo->id, "test", NULL, &error) < 0) {
        fprintf (stderr, "Failed to create branch: %s.\n", error->message);
        return -1;
    }

    /* create a new commit on branch "local". */

    file_a = g_build_filename (repo->worktree, "test-a", NULL);
    file_b = g_build_filename (repo->worktree, "test-b", NULL);
    file_bb = g_build_filename (repo->worktree, "test-b/b", NULL);
    file_c = g_build_filename (repo->worktree, "c/test-c", NULL);
    file_d = g_build_filename (repo->worktree, "a", NULL);
    file_e = g_build_filename (repo->worktree, "golden-gate.jpg", NULL);
    file_f = g_build_filename (repo->worktree, "a/stanford-cs.jpg", NULL);

    /* modify an existing file, to test modify/modify conflict. */
    fp_a = g_fopen (file_a, "wb");
    if (!fp_a) {
        fprintf (stderr, "Failed to open %s: %s\n", file_a, strerror(errno));
        return -1;
    }
    fprintf (fp_a, "xyzxyz\nxyzxyz");
    fclose (fp_a);

    /* delete a file and create a directory with the same name,
     * to test d/f conflict.
     */
    g_unlink (file_b);

    if (g_mkdir (file_b, 0777) < 0) {
        fprintf (stderr, "Failed to create %s: %s\n", file_b, strerror(errno));
        return -1;
    }
    fp_b = g_fopen (file_bb, "w+b");
    if (!fp_b) {
        fprintf (stderr, "Failed to open %s: %s\n", file_bb, strerror(errno));
        return -1;
    }
    fprintf (fp_b, "1234\n1234\n");
    fclose (fp_b);

    /* modify another file, to test modify/delete conflict. */
    fp_c = g_fopen (file_c, "wb");
    if (!fp_c) {
        fprintf (stderr, "Failed to open %s: %s\n", file_c, strerror(errno));
        return -1;
    }
    fprintf (fp_c, "something else.\n");
    fclose (fp_c);

    /* delete a directory and create a file with the same name,
     * to test d/f conflict.
     */
    snprintf (cmd, 1024, "rm -r %s", file_d);
    ret = system (cmd);
    if (ret < 0 || WEXITSTATUS(ret) != 0) {
        fprintf (stderr, "Failed to remove %s\n", file_d);
        return -1;
    }
    fp_d = g_fopen (file_d, "w+b");
    if (!fp_d) {
        fprintf (stderr, "Failed to open %s: %s\n", file_d, strerror(errno));
        return -1;
    }
    fprintf (fp_d, "1234\n1234\n");
    fclose (fp_d);

    sleep (2);

    if (seaf_repo_index_add (repo, "") < 0) {
        fprintf (stderr, "Failed to add on branch local\n");
        return -1;
    }

    printf ("*** creating new commit on local\n");
    head = seaf_repo_index_commit (repo, "merge test 1.", FALSE, NULL, &error);
    if (!head) {
        fprintf (stderr, "Failed to commit on branch test\n");
        return -1;
    }

    printf ("*** checking out branch test.\n");
    /* switch to branch "test". */
    if (seafile_checkout (repo->id, "test", &error) < 0) {
        fprintf (stderr, "Failed to checkout branch test\n");
        fprintf (stderr, "Checkout error messages:\n%s", error->message);
        return -1;
    }

    sleep (2);

    /* create a new commit on branch "test". */

    /* modify/modify conflict. */
    fp_a = g_fopen (file_a, "w+b");
    if (!fp_a) {
        fprintf (stderr, "Failed to open %s: %s\n", file_a, strerror(errno));
        return -1;
    }
    fprintf (fp_a, "abcabc\nabcabc");
    fclose (fp_a);

    /* df conflict occurs only when files are changed. */
    fp_b = g_fopen (file_b, "wb");
    if (!fp_b) {
        fprintf (stderr, "Failed to open %s: %s\n", file_b, strerror(errno));
        return -1;
    }
    fprintf (fp_b, "12345678");
    fclose (fp_b);    

    /* modify/delete conflict. */
    g_unlink (file_c);

    /* df conflict occurs only when files are changed. */
    snprintf (cmd, 1024, "cp %s %s", file_e, file_f);
    ret = system (cmd);
    if (ret < 0 || WEXITSTATUS(ret) != 0) {
        fprintf (stderr, "Failed to cp %s to %s\n", file_e, file_f);
        return -1;
    }

    sleep (2);

    if (seaf_repo_index_add (repo, "") < 0) {
        fprintf (stderr, "Failed to add on branch test\n");
        return -1;
    }

    printf ("*** creating new commit on branch test.\n");
    remote = seaf_repo_index_commit (repo, "merge test 2.", FALSE, NULL, &error);
    if (!remote) {
        fprintf (stderr, "Failed to commit on branch test\n");
        return -1;
    }

    printf ("*** checking out branch local.\n");
    /* switch back to branch "local". */
    if (seafile_checkout (repo->id, "local", &error) < 0) {
        fprintf (stderr, "Failed to checkout branch local\n");
        fprintf (stderr, "Checkout error messages:\n%s", error->message);
        return -1;
    }

    sleep (2);

    printf ("*** merging test to local.\n");
    /* merge branch "test". */
    if (seafile_merge (repo->id, "test", &error) == 0) {
        fprintf (stderr, "This merge is supposed to fail!!\n");
        return -1;
    }
    fprintf (stderr, "Merge error messages:\n%s", error->message);

    printf ("*** check merge conflict results.\n");

    if (g_access (file_f, F_OK) != 0) {
        fprintf (stderr, "Bug: %s should exist.\n", file_a);
        return -1;
    }

    if (g_access (file_c, F_OK) != 0) {
        fprintf (stderr, "Bug: %s should exist.\n", file_c);
        return -1;
    }
	time_t t = time(NULL);
	strftime(buf, 64, "--plt_%Y-%m-%d", localtime(&t));

    char *file_a_local = g_strconcat (file_a, buf, NULL);
    char *file_a_test = g_strconcat (file_a, "", NULL);
    if (check_file_content (file_a_local, "xyzxyz\nxyzxyz", 13) < 0)
        return -1;
    if (check_file_content (file_a_test, "abcabc\nabcabc", 13) < 0)
        return -1;

    char *file_d_local = g_strconcat (file_d, buf, NULL);
    if (check_file_content (file_d_local, "1234\n1234\n", 10) < 0)
        return -1;
    if (check_dir (file_d) < 0) {
        return -1;
    }

    char *dir_b_test = g_strconcat (file_b, buf, NULL);
    if (check_file_content (file_b, "12345678", 8) < 0)
        return -1;
    if (check_dir (dir_b_test) < 0) {
        return -1;
    }

    printf ("\n=== Successfully handle merge conflict.\n\n");
    return 0;
}