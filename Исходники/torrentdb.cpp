void _execute_update_stats(scoped_ptr<ScopedDbConnection> const& scoped_conn, stats_update_t const& params) {
    char ih_hex[41];
    to_hex((char const*)&params.info_hash[0], sha1_hash::size, ih_hex);

    DBClientBase* conn = scoped_conn->get();
    if (conn->isFailed()) {
        log_util::error() << "mongodb connection failed trying to update stats (torrent: " << ih_hex << ", inc_completed: " << params.increment_completed << ")" << endl;
    } else {
#ifdef _DEBUG
        log_util::debug() << "torrentdb::_execute_update_stats: Running mongodb update query (" << ih_hex << ")" << endl;
#endif

        mongo::Date_t now = terasaur::date::get_now_mongo();
        mongo::Query query = QUERY("info_hash" << ih_hex);
        BSONObj update_bson;

        if (params.increment_completed) {
#ifdef _DEBUG
        log_util::debug() << "torrentdb::_execute_update_stats: increment completed true" << endl;
#endif
            update_bson = BSON("$set" << BSON("seeds" << params.seeds << "peers" << params.peers << "updated" << now)
                               << "$inc" << BSON( "completed" << 1));
        } else {
#ifdef _DEBUG
        log_util::debug() << "torrentdb::_execute_update_stats: increment completed false" << endl;
#endif
            update_bson = BSON("$set" << BSON("seeds" << params.seeds << "peers" << params.peers << "updated" << now));
        }

#ifdef _DEBUG
        log_util::debug() << "torrentdb::_execute_update_stats: query: " << query << endl;
        log_util::debug() << "torrentdb::_execute_update_stats: update bson: " << update_bson << endl;
        log_util::debug() << "torrentdb::_execute_update_stats: calling mongodb update()" << endl;
#endif
        conn->update(_param_map["torrentdb_ns"], query, update_bson);

#ifdef _DEBUG
        log_util::debug() << "torrentdb::_execute_update_stats: calling mongodb getLastError()" << endl;
#endif
        string err = conn->getLastError();
        bool success = err.empty();
        if (success == false) {
            log_util::error() << "torrentdb::_execute_update_stats: mongodb update returned error (" << err << ")" << endl;
        }
#ifdef _DEBUG
        else {
            log_util::debug() << "torrentdb::_execute_update_stats: mongodb update successful" << endl;
        }
#endif
    }

#ifdef _DEBUG
    log_util::debug() << "torrentdb::_execute_update_stats: returning" << endl;
#endif
}