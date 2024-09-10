void
MetarListModel::fetchMetar(const QString& _icao) {
  __myHttpHandler->fetchData(VatsimDataHandler::getSingleton().getMetarUrl() + "?id=" + _icao.toLower());
  __requests.enqueue(_icao.simplified());
}