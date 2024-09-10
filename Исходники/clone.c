int cmd_clone(int argc, const char **argv, const char *prefix)
{
	int is_bundle = 0, is_local;
	struct stat buf;
	const char *repo_name, *repo, *work_tree, *git_dir;
	char *path, *dir;
	int dest_exists;
	const struct ref *refs, *remote_head;
	const struct ref *remote_head_points_at;
	const struct ref *our_head_points_at;
	struct ref *mapped_refs;
	struct strbuf key = STRBUF_INIT, value = STRBUF_INIT;
	struct strbuf branch_top = STRBUF_INIT, reflog_msg = STRBUF_INIT;
	struct transport *transport = NULL;
	char *src_ref_prefix = "refs/heads/";
	int err = 0;

	struct refspec *refspec;
	const char *fetch_pattern;

	junk_pid = getpid();

	packet_trace_identity("clone");
	argc = parse_options(argc, argv, prefix, builtin_clone_options,
			     builtin_clone_usage, 0);

	if (argc > 2)
		usage_msg_opt(_("Too many arguments."),
			builtin_clone_usage, builtin_clone_options);

	if (argc == 0)
		usage_msg_opt(_("You must specify a repository to clone."),
			builtin_clone_usage, builtin_clone_options);

	if (option_mirror)
		option_bare = 1;

	if (option_bare) {
		if (option_origin)
			die(_("--bare and --origin %s options are incompatible."),
			    option_origin);
		option_no_checkout = 1;
	}

	if (!option_origin)
		option_origin = "origin";

	repo_name = argv[0];

	path = get_repo_path(repo_name, &is_bundle);
	if (path)
		repo = xstrdup(absolute_path(repo_name));
	else if (!strchr(repo_name, ':'))
		die(_("repository '%s' does not exist"), repo_name);
	else
		repo = repo_name;
	is_local = path && !is_bundle;
	if (is_local && option_depth)
		warning(_("--depth is ignored in local clones; use file:// instead."));

	if (argc == 2)
		dir = xstrdup(argv[1]);
	else
		dir = guess_dir_name(repo_name, is_bundle, option_bare);
	strip_trailing_slashes(dir);

	dest_exists = !stat(dir, &buf);
	if (dest_exists && !is_empty_dir(dir))
		die(_("destination path '%s' already exists and is not "
			"an empty directory."), dir);

	strbuf_addf(&reflog_msg, "clone: from %s", repo);

	if (option_bare)
		work_tree = NULL;
	else {
		work_tree = getenv("GIT_WORK_TREE");
		if (work_tree && !stat(work_tree, &buf))
			die(_("working tree '%s' already exists."), work_tree);
	}

	if (option_bare || work_tree)
		git_dir = xstrdup(dir);
	else {
		work_tree = dir;
		git_dir = xstrdup(mkpath("%s/.git", dir));
	}

	if (!option_bare) {
		junk_work_tree = work_tree;
		if (safe_create_leading_directories_const(work_tree) < 0)
			die_errno(_("could not create leading directories of '%s'"),
				  work_tree);
		if (!dest_exists && mkdir(work_tree, 0755))
			die_errno(_("could not create work tree dir '%s'."),
				  work_tree);
		set_git_work_tree(work_tree);
	}
	junk_git_dir = git_dir;
	atexit(remove_junk);
	sigchain_push_common(remove_junk_on_signal);

	setenv(CONFIG_ENVIRONMENT, mkpath("%s/config", git_dir), 1);

	if (safe_create_leading_directories_const(git_dir) < 0)
		die(_("could not create leading directories of '%s'"), git_dir);

	set_git_dir_init(git_dir, real_git_dir, 0);
	if (real_git_dir)
		git_dir = real_git_dir;

	if (0 <= option_verbosity) {
		if (option_bare)
			printf(_("Cloning into bare repository %s...\n"), dir);
		else
			printf(_("Cloning into %s...\n"), dir);
	}
	init_db(option_template, INIT_DB_QUIET);

	/*
	 * At this point, the config exists, so we do not need the
	 * environment variable.  We actually need to unset it, too, to
	 * re-enable parsing of the global configs.
	 */
	unsetenv(CONFIG_ENVIRONMENT);

	git_config(git_default_config, NULL);

	if (option_bare) {
		if (option_mirror)
			src_ref_prefix = "refs/";
		strbuf_addstr(&branch_top, src_ref_prefix);

		git_config_set("core.bare", "true");
	} else {
		strbuf_addf(&branch_top, "refs/remotes/%s/", option_origin);
	}

	strbuf_addf(&value, "+%s*:%s*", src_ref_prefix, branch_top.buf);

	if (option_mirror || !option_bare) {
		/* Configure the remote */
		strbuf_addf(&key, "remote.%s.fetch", option_origin);
		git_config_set_multivar(key.buf, value.buf, "^$", 0);
		strbuf_reset(&key);

		if (option_mirror) {
			strbuf_addf(&key, "remote.%s.mirror", option_origin);
			git_config_set(key.buf, "true");
			strbuf_reset(&key);
		}
	}

	strbuf_addf(&key, "remote.%s.url", option_origin);
	git_config_set(key.buf, repo);
	strbuf_reset(&key);

	if (option_reference)
		setup_reference(git_dir);

	fetch_pattern = value.buf;
	refspec = parse_fetch_refspec(1, &fetch_pattern);

	strbuf_reset(&value);

	if (is_local) {
		refs = clone_local(path, git_dir);
		mapped_refs = wanted_peer_refs(refs, refspec);
	} else {
		struct remote *remote = remote_get(option_origin);
		transport = transport_get(remote, remote->url[0]);

		if (!transport->get_refs_list || !transport->fetch)
			die(_("Don't know how to clone %s"), transport->url);

		transport_set_option(transport, TRANS_OPT_KEEP, "yes");

		if (option_depth)
			transport_set_option(transport, TRANS_OPT_DEPTH,
					     option_depth);

		transport_set_verbosity(transport, option_verbosity, option_progress);

		if (option_upload_pack)
			transport_set_option(transport, TRANS_OPT_UPLOADPACK,
					     option_upload_pack);

		refs = transport_get_remote_refs(transport);
		if (refs) {
			mapped_refs = wanted_peer_refs(refs, refspec);
			transport_fetch_refs(transport, mapped_refs);
		}
	}

	if (refs) {
		clear_extra_refs();

		write_remote_refs(mapped_refs);

		remote_head = find_ref_by_name(refs, "HEAD");
		remote_head_points_at =
			guess_remote_head(remote_head, mapped_refs, 0);

		if (option_branch) {
			struct strbuf head = STRBUF_INIT;
			strbuf_addstr(&head, src_ref_prefix);
			strbuf_addstr(&head, option_branch);
			our_head_points_at =
				find_ref_by_name(mapped_refs, head.buf);
			strbuf_release(&head);

			if (!our_head_points_at) {
				warning(_("Remote branch %s not found in "
					"upstream %s, using HEAD instead"),
					option_branch, option_origin);
				our_head_points_at = remote_head_points_at;
			}
		}
		else
			our_head_points_at = remote_head_points_at;
	}
	else {
		warning(_("You appear to have cloned an empty repository."));
		our_head_points_at = NULL;
		remote_head_points_at = NULL;
		remote_head = NULL;
		option_no_checkout = 1;
		if (!option_bare)
			install_branch_config(0, "master", option_origin,
					      "refs/heads/master");
	}

	if (remote_head_points_at && !option_bare) {
		struct strbuf head_ref = STRBUF_INIT;
		strbuf_addstr(&head_ref, branch_top.buf);
		strbuf_addstr(&head_ref, "HEAD");
		create_symref(head_ref.buf,
			      remote_head_points_at->peer_ref->name,
			      reflog_msg.buf);
	}

	if (our_head_points_at) {
		/* Local default branch link */
		create_symref("HEAD", our_head_points_at->name, NULL);
		if (!option_bare) {
			const char *head = skip_prefix(our_head_points_at->name,
						       "refs/heads/");
			update_ref(reflog_msg.buf, "HEAD",
				   our_head_points_at->old_sha1,
				   NULL, 0, DIE_ON_ERR);
			install_branch_config(0, head, option_origin,
					      our_head_points_at->name);
		}
	} else if (remote_head) {
		/* Source had detached HEAD pointing somewhere. */
		if (!option_bare) {
			update_ref(reflog_msg.buf, "HEAD",
				   remote_head->old_sha1,
				   NULL, REF_NODEREF, DIE_ON_ERR);
			our_head_points_at = remote_head;
		}
	} else {
		/* Nothing to checkout out */
		if (!option_no_checkout)
			warning(_("remote HEAD refers to nonexistent ref, "
				"unable to checkout.\n"));
		option_no_checkout = 1;
	}

	if (transport) {
		transport_unlock_pack(transport);
		transport_disconnect(transport);
	}

	if (!option_no_checkout) {
		struct lock_file *lock_file = xcalloc(1, sizeof(struct lock_file));
		struct unpack_trees_options opts;
		struct tree *tree;
		struct tree_desc t;
		int fd;

		/* We need to be in the new work tree for the checkout */
		setup_work_tree();

		fd = hold_locked_index(lock_file, 1);

		memset(&opts, 0, sizeof opts);
		opts.update = 1;
		opts.merge = 1;
		opts.fn = oneway_merge;
		opts.verbose_update = (option_verbosity > 0);
		opts.src_index = &the_index;
		opts.dst_index = &the_index;

		tree = parse_tree_indirect(our_head_points_at->old_sha1);
		parse_tree(tree);
		init_tree_desc(&t, tree->buffer, tree->size);
		unpack_trees(1, &t, &opts);

		if (write_cache(fd, active_cache, active_nr) ||
		    commit_locked_index(lock_file))
			die(_("unable to write new index file"));

		err |= run_hook(NULL, "post-checkout", sha1_to_hex(null_sha1),
				sha1_to_hex(our_head_points_at->old_sha1), "1",
				NULL);

		if (!err && option_recursive)
			err = run_command_v_opt(argv_submodule, RUN_GIT_CMD);
	}

	strbuf_release(&reflog_msg);
	strbuf_release(&branch_top);
	strbuf_release(&key);
	strbuf_release(&value);
	junk_pid = 0;
	return err;
}