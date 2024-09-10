/**
 * Loads the globe from a YAML file.
 * @param node YAML node.
 */
void RuleGlobe::load(const YAML::Node &node)
{
    if (node["data"])
    {
        for (std::list<Polygon*>::iterator i = _polygons.begin(); i != _polygons.end(); ++i)
        {
            delete *i;
        }
        _polygons.clear();
        loadDat(CrossPlatform::getDataFile(node["data"].as<std::string>()));
    }
    if (node["polygons"])
    {
        for (std::list<Polygon*>::iterator i = _polygons.begin(); i != _polygons.end(); ++i)
        {
            delete *i;
        }
        _polygons.clear();
        for (YAML::const_iterator i = node["polygons"].begin(); i != node["polygons"].end(); ++i)
        {
            Polygon *polygon = new Polygon(3);
            polygon->load(*i);
            _polygons.push_back(polygon);
        }
    }
    if (node["polylines"])
    {
        for (std::list<Polyline*>::iterator i = _polylines.begin(); i != _polylines.end(); ++i)
        {
            delete *i;
        }
        _polylines.clear();
        for (YAML::const_iterator i = node["polylines"].begin(); i != node["polylines"].end(); ++i)
        {
            Polyline *polyline = new Polyline(3);
            polyline->load(*i);
            _polylines.push_back(polyline);
        }
    }
    if (node["textures"])
    {
        for (std::map<int, Texture*>::iterator i = _textures.begin(); i != _textures.end(); ++i)
        {
            delete i->second;
        }
        _textures.clear();
        for (YAML::const_iterator i = node["textures"].begin(); i != node["textures"].end(); ++i)
        {
            int id = (*i)["id"].as<int>();
            Texture *texture = new Texture(id);
            texture->load(*i);
            _textures[id] = texture;
        }
    }
    Globe::COUNTRY_LABEL_COLOR = node["countryColor"].as<int>(Globe::COUNTRY_LABEL_COLOR);
    Globe::CITY_LABEL_COLOR = node["cityColor"].as<int>(Globe::CITY_LABEL_COLOR);
    Globe::BASE_LABEL_COLOR = node["baseColor"].as<int>(Globe::BASE_LABEL_COLOR);
    Globe::LINE_COLOR = node["lineColor"].as<int>(Globe::LINE_COLOR);

    if (node["oceanPalette"])
    {
        Globe::OCEAN_COLOR = Palette::blockOffset(node["oceanPalette"].as<int>(Globe::OCEAN_COLOR));
    }
}