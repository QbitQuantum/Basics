    void handle_modify(DBClientBase *client, DBOperation *operation)
    {
        // First, we have to format our findandmodify.
        BSONObjBuilder sets;
        bool has_sets = false;
        BSONObjBuilder unsets;
        bool has_unsets = false;
        for(auto it  = operation->set_fields().begin();
            it != operation->set_fields().end(); ++it) {
            stringstream fieldname;
            fieldname << "fields." << it->first->get_name();
            if(it->second.empty()) {
                unsets << fieldname.str() << true;
                has_unsets = true;
            } else {
                DatagramPtr dg = Datagram::create();
                dg->add_data(it->second);
                DatagramIterator dgi(dg);
                sets << fieldname.str() << bamboo2bson(it->first->get_type(), dgi)["_"];
                has_sets = true;
            }
        }

        BSONObjBuilder updates_b;
        if(has_sets) {
            updates_b << "$set" << sets.obj();
        }
        if(has_unsets) {
            updates_b << "$unset" << unsets.obj();
        }
        BSONObj updates = updates_b.obj();

        // Also format any criteria for the change:
        BSONObjBuilder query_b;
        query_b << "_id" << operation->doid();
        for(auto it  = operation->criteria_fields().begin();
            it != operation->criteria_fields().end(); ++it) {
            stringstream fieldname;
            fieldname << "fields." << it->first->get_name();
            if(it->second.empty()) {
                query_b << fieldname.str() << BSON("$exists" << false);
            } else {
                DatagramPtr dg = Datagram::create();
                dg->add_data(it->second);
                DatagramIterator dgi(dg);
                query_b << fieldname.str() << bamboo2bson(it->first->get_type(), dgi)["_"];
            }
        }
        BSONObj query = query_b.obj();

        m_log->trace() << "Performing updates to " << operation->doid()
                       << ": " << updates << endl;
        m_log->trace() << "Query is: " << query << endl;

        BSONObj result;
        bool success;
        try {
            success = client->runCommand(
                          m_db,
                          BSON("findandmodify" << "astron.objects"
                               << "query" << query
                               << "update" << updates),
                          result);
        } catch(mongo::DBException &e) {
            m_log->error() << "Unexpected error while modifying "
                           << operation->doid() << ": " << e.what() << endl;
            operation->on_failure();
            return;
        }

        m_log->trace() << "Update result: " << result << endl;

        BSONObj obj;
        if(!success || result["value"].isNull()) {
            // Okay, something didn't work right. If we had criteria, let's
            // try to fetch the object without the criteria to see if it's a
            // criteria mismatch or a missing DOID.
            if(!operation->criteria_fields().empty()) {
                try {
                    obj = client->findOne(m_obj_collection,
                                         BSON("_id" << operation->doid()));
                } catch(mongo::DBException &e) {
                    m_log->error() << "Unexpected error while modifying "
                                   << operation->doid() << ": " << e.what() << endl;
                    operation->on_failure();
                    return;
                }
                if(!obj.isEmpty()) {
                    // There's the problem. Now we can send back a snapshot:
                    DBObjectSnapshot *snap = format_snapshot(operation->doid(), obj);
                    if(snap && operation->verify_class(snap->m_dclass)) {
                        operation->on_criteria_mismatch(snap);
                        return;
                    } else {
                        // Something else weird happened with our snapshot;
                        // either the class wasn't recognized or it was the
                        // wrong class. Either way, an error has been logged,
                        // and we need to fail the operation.
                        operation->on_failure();
                        return;
                    }
                }
            }

            // Nope, not that. We're missing the DOID.
            m_log->error() << "Attempted to modify unknown DOID: "
                           << operation->doid() << endl;
            operation->on_failure();
            return;
        }

        // If we've gotten to this point: Hooray! The change has gone
        // through to the database.
        // Let's, however, double-check our changes. (Specifically, we should
        // run verify_class so that we know the frontend is happy with what
        // kind of object we just modified.)
        obj = result["value"].Obj();
        try {
            string dclass_name = obj["dclass"].String();
            const dclass::Class *dclass = g_dcf->get_class_by_name(dclass_name);
            if(!dclass) {
                m_log->error() << "Encountered unknown database object: "
                               << dclass_name << "(" << operation->doid() << ")" << endl;
            } else if(operation->verify_class(dclass)) {
                // Yep, it all checks out. Complete the operation:
                operation->on_complete();
                return;
            }
        } catch(mongo::DBException &e) { }

        // If we've gotten here, something is seriously wrong. We've just
        // mucked with an object without knowing the consequences! What have
        // we done?! We've created an abomination in the database! Kill it!
        // Kill it with fire!

        // All we really can do to mitigate this is scream at the user (which
        // the above verification has already done by now) and revert the
        // object back to how it was when we found it.
        // NOTE: This DOES have the potential for data loss, because we're
        // wiping out any changes that conceivably could have happened
        // between the findandmodify and now. In dev environments, (which we
        // are probably in right now, if other components are making
        // outlandish requests like this) this shouldn't be a huge issue.
        m_log->trace() << "Reverting changes made to " << operation->doid() << endl;
        try {
            client->update(
                m_obj_collection,
                BSON("_id" << operation->doid()),
                obj);
        } catch(mongo::DBException &e) {
            // Wow, we REALLY fail at life.
            m_log->error() << "Could not revert corrupting changes to "
                           << operation->doid() << ": " << e.what() << endl;
        }
        operation->on_failure();
    }