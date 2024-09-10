QSpotifyPlaylistContainer::~QSpotifyPlaylistContainer()
{
    g_containerObjects.remove(m_container);
    sp_playlistcontainer_remove_callbacks(m_container, m_callbacks, 0);
    qDeleteAll(m_playlists);
    sp_playlistcontainer_release(m_container);
    delete m_callbacks;
}