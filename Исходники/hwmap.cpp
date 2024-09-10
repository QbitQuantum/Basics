void HWMap::SendToClientFirst()
{
    SendIPC(QString("eseed %1").arg(m_seed).toUtf8());
    SendIPC(QString("e$template_filter %1").arg(templateFilter).toUtf8());
    SendIPC(QString("e$mapgen %1").arg(m_mapgen).toUtf8());
    if (!m_script.isEmpty())
    {
        SendIPC(QString("escript Scripts/Multiplayer/%1.lua").arg(m_script).toUtf8());
    }

    switch (m_mapgen)
    {
        case MAPGEN_MAZE:
            SendIPC(QString("e$maze_size %1").arg(m_maze_size).toUtf8());
            break;

        case MAPGEN_DRAWN:
        {
            QByteArray data = m_drawMapData;
            while(data.size() > 0)
            {
                QByteArray tmp = data;
                tmp.truncate(200);
                SendIPC("edraw " + tmp);
                data.remove(0, 200);
            }
            break;
        }
        default:
            ;
    }

    SendIPC("!");
}