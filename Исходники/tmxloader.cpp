bool
TMXLoader::Private::processLayer(XMLElement &e)
{
	const char *l_name;
	float l_opacity = 1.f;
	int l_visible = 1;

	if ((!(l_name = e.Attribute("name")))) {
		MMWARNING("Layer element is missing one or more required attributes.");
		return(false);
	}

	MMIGNORE e.QueryFloatAttribute("opacity", &l_opacity);
	MMIGNORE e.QueryIntAttribute("visible", &l_visible);

	XMLElement *l_data = e.FirstChildElement(TMXLAYER_DATA_NODE);

	if (!l_data) {
		MMWARNING("Layer element is missing data element.");
		return(false);
	}

	const char *l_data_encoding;
	const char *l_data_compression;

	if (!(l_data_encoding = l_data->Attribute("encoding")) ||
	    !(l_data_compression = l_data->Attribute("compression"))) {
		MMWARNING("Layer data element is missing one or more required attributes.");
		return(false);
	}
	const char *l_data_raw = XMLUtil::SkipWhiteSpace(l_data->GetText());
	size_t l_data_raw_len = strlen(l_data_raw);

	/* right-side data trim */
	while (l_data_raw_len > 0 && isspace(l_data_raw[l_data_raw_len - 1]))
		--l_data_raw_len;

	if (!l_data_raw_len) {
		MMWARNING("Zero size layer data encountered.");
		return(false);
	}

	char *l_data_array = 0;

#define TMXDATA_ENCODING_BASE64 "base64"
	if (0 == strcmp(l_data_encoding, TMXDATA_ENCODING_BASE64)) {
		char *l_decoded_data;
		size_t l_decoded_data_size =
		    Core::Base64::Decode(l_data_raw, l_data_raw_len, &l_decoded_data);

#define TMXDATA_COMPRESSION_ZLIB "zlib"
		if (0 == strcmp(l_data_compression, TMXDATA_COMPRESSION_ZLIB)) {
			char *l_inflated_data;
			if (0 < Core::Zlib::Inflate(l_decoded_data, l_decoded_data_size,
			    static_cast<size_t>(map_size.width * map_size.height * 4), &l_inflated_data))
				l_data_array = l_inflated_data;
		}
#define TMXDATA_COMPRESSION_GZIP "gzip"
		else if (0 == strcmp(l_data_compression, TMXDATA_COMPRESSION_GZIP)) {
			char *l_inflated_data;
			if (0 < Core::Gzip::Inflate(l_decoded_data, l_decoded_data_size,
			    static_cast<size_t>(map_size.width * map_size.height * 4), &l_inflated_data))
				l_data_array = l_inflated_data;
		}

		delete[] l_decoded_data;
	}

#define TMXDATA_ENCODING_CSV "csv"
	else if (0 == strcmp(l_data_encoding, TMXDATA_ENCODING_CSV)) {
		// TODO(gamaral)
		assert(0 && "CSV data encoding is currently unimplemented");
		return(false);
	}

	if (!l_data_array)
		return(false);

	Game::TilemapSceneLayer *l_layer = new Game::TilemapSceneLayer(l_name, scene);
	l_layer->setData(reinterpret_cast<uint32_t *>(l_data_array));
	l_layer->setOpacity(l_opacity);
	l_layer->setSize(map_size);
	l_layer->setTileSize(tile_size);
	l_layer->setScale(scale);
	l_layer->setVisibility(1 == l_visible);

	/* process properties */
	XMLElement *l_properties = e.FirstChildElement(TMXPROPERTIES_NODE);
	XMLElement *l_property = l_properties ? l_properties->FirstChildElement(TMXPROPERTIES_PROPERTY_NODE) : 0;
	if (l_property)
	do {
		const char *l_pname = l_property->Attribute("name");
		const char *l_value = l_property->Attribute("value");
		if (!l_pname)
			continue;

		/* scale property */
		if (0 == strcmp(l_pname, "scale")) {
			if (!l_value) {
				MMWARNING("Skipping incomplete scale property.");
				continue;
			}

			Math::Size2f l_scale = l_layer->scale();
			if (0 == MMSTRCASECMP(l_value, "screen")) {
				const Math::Size2f &l_vsize = Graphics::Viewport::Size();
				const Math::Size2i &l_wsize = Graphics::Viewport::WindowSize();

				/*
				 * calculate pixels per viewport coordinate ratio
				 * scale ratio = vSize (vcoord)) / wSize (pixels)
				 */
				l_scale = l_vsize / l_wsize.cast<float>();
				l_layer->setScale(l_scale);

				continue;
			}
			else if (2 == sscanf(l_value, "%fx%f", &l_scale.width, &l_scale.height)) {
				l_layer->setScale(l_scale);
				continue;
			} else if (1 == sscanf(l_value, "%f", &l_scale.width)) {
				l_scale.height = l_scale.width;
				l_layer->setScale(l_scale);
				continue;
			}

			MMERROR("Invalid scale value encountered.");
			continue;
		}
		else l_layer->setProperty(l_name, l_value ? l_value : std::string());

	} while ((l_property = l_property->NextSiblingElement(TMXPROPERTIES_PROPERTY_NODE)));

	/* attach tilesets */
	TilesetCollection::iterator l_tileset_i;
	for (l_tileset_i = tilesets.begin(); l_tileset_i != tilesets.end(); ++l_tileset_i)
		l_layer->attachTileset(l_tileset_i->first, l_tileset_i->second);

	layers.push_back(l_layer);

	return(true);
}