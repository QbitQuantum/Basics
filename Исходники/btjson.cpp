/**
 * The function returns the changed data from the server to synchronize with the web client.
 * Return value is map in JSON format.
 * Map contain the key:
 *  - "Rid": ID response
 * Map can contain the keys:
 *  - "full_update": full data update flag
 *  - "torrents": dictionary contains information about torrents.
 *  - "torrents_removed": a list of hashes of removed torrents
 *  - "categories": list of categories
 *  - "categories_removed": list of removed categories
 *  - "server_state": map contains information about the state of the server
 * The keys of the 'torrents' dictionary are hashes of torrents.
 * Each value of the 'torrents' dictionary contains map. The map can contain following keys:
 *  - "name": Torrent name
 *  - "size": Torrent size
 *  - "progress: Torrent progress
 *  - "dlspeed": Torrent download speed
 *  - "upspeed": Torrent upload speed
 *  - "priority": Torrent priority (-1 if queuing is disabled)
 *  - "num_seeds": Torrent seeds connected to
 *  - "num_complete": Torrent seeds in the swarm
 *  - "num_leechs": Torrent leechers connected to
 *  - "num_incomplete": Torrent leechers in the swarm
 *  - "ratio": Torrent share ratio
 *  - "eta": Torrent ETA
 *  - "state": Torrent state
 *  - "seq_dl": Torrent sequential download state
 *  - "f_l_piece_prio": Torrent first last piece priority state
 * Server state map may contain the following keys:
 *  - "connection_status": connection status
 *  - "dht_nodes": DHT nodes count
 *  - "dl_info_data": bytes downloaded
 *  - "dl_info_speed": download speed
 *  - "dl_rate_limit: download rate limit
 *  - "up_info_data: bytes uploaded
 *  - "up_info_speed: upload speed
 *  - "up_rate_limit: upload speed limit
 *  - "queueing": priority system usage flag
 *  - "refresh_interval": torrents table refresh interval
 */
QByteArray btjson::getSyncMainData(int acceptedResponseId, QVariantMap &lastData, QVariantMap &lastAcceptedData)
{
    QVariantMap data;
    QVariantHash torrents;

    BitTorrent::Session *const session = BitTorrent::Session::instance();

    foreach (BitTorrent::TorrentHandle *const torrent, session->torrents()) {
        QVariantMap map = toMap(torrent);
        map.remove(KEY_TORRENT_HASH);
        torrents[torrent->hash()] = map;
    }

    data["torrents"] = torrents;

    QVariantList categories;
    foreach (const QString &category, session->categories())
        categories << category;

    data["categories"] = categories;

    QVariantMap serverState = getTranserInfoMap();
    serverState[KEY_SYNC_MAINDATA_QUEUEING] = session->isQueueingSystemEnabled();
    serverState[KEY_SYNC_MAINDATA_USE_ALT_SPEED_LIMITS] = session->isAltGlobalSpeedLimitEnabled();
    serverState[KEY_SYNC_MAINDATA_REFRESH_INTERVAL] = session->refreshInterval();
    data["server_state"] = serverState;

    return json::toJson(generateSyncData(acceptedResponseId, data, lastAcceptedData, lastData));
}