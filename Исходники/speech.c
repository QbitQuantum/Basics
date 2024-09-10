void
notify_except(dbref first, dbref exception, const char *msg, dbref who)
{
	dbref room, srch;

	if (first != NOTHING) {

		srch = room = DBFETCH(first)->location;

		if (tp_listeners) {
			notify_from_echo(who, srch, msg, 0);

			if (tp_listeners_env) {
				srch = DBFETCH(srch)->location;
				while (srch != NOTHING) {
					notify_from_echo(who, srch, msg, 0);
					srch = getparent(srch);
				}
			}
		}

		DOLIST(first, first) {
			if ((Typeof(first) != TYPE_ROOM) && (first != exception)) {
				/* don't want excepted player or child rooms to hear */
				notify_from_echo(who, first, msg, 0);
			}
		}
	}