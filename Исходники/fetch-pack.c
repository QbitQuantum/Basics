static struct ref *do_fetch_pack(struct fetch_pack_args *args,
				 int fd[2],
				 const struct ref *orig_ref,
				 struct ref **sought, int nr_sought,
				 struct shallow_info *si,
				 char **pack_lockfile)
{
	struct ref *ref = copy_ref_list(orig_ref);
	struct object_id oid;
	const char *agent_feature;
	int agent_len;
	struct fetch_negotiator negotiator;
	fetch_negotiator_init(&negotiator, negotiation_algorithm);

	sort_ref_list(&ref, ref_compare_name);
	QSORT(sought, nr_sought, cmp_ref_by_name);

	if ((args->depth > 0 || is_repository_shallow(the_repository)) && !server_supports("shallow"))
		die(_("Server does not support shallow clients"));
	if (args->depth > 0 || args->deepen_since || args->deepen_not)
		args->deepen = 1;
	if (server_supports("multi_ack_detailed")) {
		print_verbose(args, _("Server supports multi_ack_detailed"));
		multi_ack = 2;
		if (server_supports("no-done")) {
			print_verbose(args, _("Server supports no-done"));
			if (args->stateless_rpc)
				no_done = 1;
		}
	}
	else if (server_supports("multi_ack")) {
		print_verbose(args, _("Server supports multi_ack"));
		multi_ack = 1;
	}
	if (server_supports("side-band-64k")) {
		print_verbose(args, _("Server supports side-band-64k"));
		use_sideband = 2;
	}
	else if (server_supports("side-band")) {
		print_verbose(args, _("Server supports side-band"));
		use_sideband = 1;
	}
	if (server_supports("allow-tip-sha1-in-want")) {
		print_verbose(args, _("Server supports allow-tip-sha1-in-want"));
		allow_unadvertised_object_request |= ALLOW_TIP_SHA1;
	}
	if (server_supports("allow-reachable-sha1-in-want")) {
		print_verbose(args, _("Server supports allow-reachable-sha1-in-want"));
		allow_unadvertised_object_request |= ALLOW_REACHABLE_SHA1;
	}
	if (!server_supports("thin-pack"))
		args->use_thin_pack = 0;
	if (!server_supports("no-progress"))
		args->no_progress = 0;
	if (!server_supports("include-tag"))
		args->include_tag = 0;
	if (server_supports("ofs-delta"))
		print_verbose(args, _("Server supports ofs-delta"));
	else
		prefer_ofs_delta = 0;

	if (server_supports("filter")) {
		server_supports_filtering = 1;
		print_verbose(args, _("Server supports filter"));
	} else if (args->filter_options.choice) {
		warning("filtering not recognized by server, ignoring");
	}

	if ((agent_feature = server_feature_value("agent", &agent_len))) {
		agent_supported = 1;
		if (agent_len)
			print_verbose(args, _("Server version is %.*s"),
				      agent_len, agent_feature);
	}
	if (server_supports("deepen-since"))
		deepen_since_ok = 1;
	else if (args->deepen_since)
		die(_("Server does not support --shallow-since"));
	if (server_supports("deepen-not"))
		deepen_not_ok = 1;
	else if (args->deepen_not)
		die(_("Server does not support --shallow-exclude"));
	if (!server_supports("deepen-relative") && args->deepen_relative)
		die(_("Server does not support --deepen"));

	if (!args->no_dependents) {
		mark_complete_and_common_ref(&negotiator, args, &ref);
		filter_refs(args, &ref, sought, nr_sought);
		if (everything_local(args, &ref)) {
			packet_flush(fd[1]);
			goto all_done;
		}
	} else {
		filter_refs(args, &ref, sought, nr_sought);
	}
	if (find_common(&negotiator, args, fd, &oid, ref) < 0)
		if (!args->keep_pack)
			/* When cloning, it is not unusual to have
			 * no common commit.
			 */
			warning(_("no common commits"));

	if (args->stateless_rpc)
		packet_flush(fd[1]);
	if (args->deepen)
		setup_alternate_shallow(&shallow_lock, &alternate_shallow_file,
					NULL);
	else if (si->nr_ours || si->nr_theirs)
		alternate_shallow_file = setup_temporary_shallow(si->shallow);
	else
		alternate_shallow_file = NULL;
	if (get_pack(args, fd, pack_lockfile))
		die(_("git fetch-pack: fetch failed."));

 all_done:
	negotiator.release(&negotiator);
	return ref;
}