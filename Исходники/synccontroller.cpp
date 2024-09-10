// The function returns the changed data from the server to synchronize with the web client.
// Return value is map in JSON format.
// Map contain the key:
//  - "Rid": ID response
// Map can contain the keys:
//  - "full_update": full data update flag
//  - "torrents": dictionary contains information about torrents.
//  - "torrents_removed": a list of hashes of removed torrents
//  - "categories": map of categories info
//  - "categories_removed": list of removed categories
//  - "server_state": map contains information about the state of the server
// The keys of the 'torrents' dictionary are hashes of torrents.
// Each value of the 'torrents' dictionary contains map. The map can contain following keys:
//  - "name": Torrent name
//  - "size": Torrent size
//  - "progress": Torrent progress
//  - "dlspeed": Torrent download speed
//  - "upspeed": Torrent upload speed
//  - "priority": Torrent priority (-1 if queuing is disabled)
//  - "num_seeds": Torrent seeds connected to
//  - "num_complete": Torrent seeds in the swarm
//  - "num_leechs": Torrent leechers connected to
//  - "num_incomplete": Torrent leechers in the swarm
//  - "ratio": Torrent share ratio
//  - "eta": Torrent ETA
//  - "state": Torrent state
//  - "seq_dl": Torrent sequential download state
//  - "f_l_piece_prio": Torrent first last piece priority state
//  - "completion_on": Torrent copletion time
//  - "tracker": Torrent tracker
//  - "dl_limit": Torrent download limit
//  - "up_limit": Torrent upload limit
//  - "downloaded": Amount of data downloaded
//  - "uploaded": Amount of data uploaded
//  - "downloaded_session": Amount of data downloaded since program open
//  - "uploaded_session": Amount of data uploaded since program open
//  - "amount_left": Amount of data left to download
//  - "save_path": Torrent save path
//  - "completed": Amount of data completed
//  - "max_ratio": Upload max share ratio
//  - "max_seeding_time": Upload max seeding time
//  - "ratio_limit": Upload share ratio limit
//  - "seeding_time_limit": Upload seeding time limit
//  - "seen_complete": Indicates the time when the torrent was last seen complete/whole
//  - "last_activity": Last time when a chunk was downloaded/uploaded
//  - "total_size": Size including unwanted data
// Server state map may contain the following keys:
//  - "connection_status": connection status
//  - "dht_nodes": DHT nodes count
//  - "dl_info_data": bytes downloaded
//  - "dl_info_speed": download speed
//  - "dl_rate_limit: download rate limit
//  - "up_info_data: bytes uploaded
//  - "up_info_speed: upload speed
//  - "up_rate_limit: upload speed limit
//  - "queueing": priority system usage flag
//  - "refresh_interval": torrents table refresh interval
//  - "free_space_on_disk": Free space on the default save path
// GET param:
//   - rid (int): last response id
void SyncController::maindataAction()
{
    auto lastResponse = sessionManager()->session()->getData(QLatin1String("syncMainDataLastResponse")).toMap();
    auto lastAcceptedResponse = sessionManager()->session()->getData(QLatin1String("syncMainDataLastAcceptedResponse")).toMap();

    QVariantMap data;
    QVariantHash torrents;

    BitTorrent::Session *const session = BitTorrent::Session::instance();

    for (BitTorrent::TorrentHandle *const torrent : asConst(session->torrents())) {
        QVariantMap map = serialize(*torrent);
        map.remove(KEY_TORRENT_HASH);

        // Calculated last activity time can differ from actual value by up to 10 seconds (this is a libtorrent issue).
        // So we don't need unnecessary updates of last activity time in response.
        if (lastResponse.contains("torrents") && lastResponse["torrents"].toHash().contains(torrent->hash()) &&
                lastResponse["torrents"].toHash()[torrent->hash()].toMap().contains(KEY_TORRENT_LAST_ACTIVITY_TIME)) {
            uint lastValue = lastResponse["torrents"].toHash()[torrent->hash()].toMap()[KEY_TORRENT_LAST_ACTIVITY_TIME].toUInt();
            if (qAbs(static_cast<int>(lastValue - map[KEY_TORRENT_LAST_ACTIVITY_TIME].toUInt())) < 15)
                map[KEY_TORRENT_LAST_ACTIVITY_TIME] = lastValue;
        }

        torrents[torrent->hash()] = map;
    }

    data["torrents"] = torrents;

    QVariantHash categories;
    const auto categoriesList = session->categories();
    for (auto it = categoriesList.cbegin(); it != categoriesList.cend(); ++it) {
        const auto key = it.key();
        categories[key] = QVariantMap {
            {"name", key},
            {"savePath", it.value()}
        };
    }

    data["categories"] = categories;

    QVariantMap serverState = getTranserInfo();
    serverState[KEY_TRANSFER_FREESPACEONDISK] = getFreeDiskSpace();
    serverState[KEY_SYNC_MAINDATA_QUEUEING] = session->isQueueingSystemEnabled();
    serverState[KEY_SYNC_MAINDATA_USE_ALT_SPEED_LIMITS] = session->isAltGlobalSpeedLimitEnabled();
    serverState[KEY_SYNC_MAINDATA_REFRESH_INTERVAL] = session->refreshInterval();
    data["server_state"] = serverState;

    const int acceptedResponseId {params()["rid"].toInt()};
    setResult(QJsonObject::fromVariantMap(generateSyncData(acceptedResponseId, data, lastAcceptedResponse, lastResponse)));

    sessionManager()->session()->setData(QLatin1String("syncMainDataLastResponse"), lastResponse);
    sessionManager()->session()->setData(QLatin1String("syncMainDataLastAcceptedResponse"), lastAcceptedResponse);
}