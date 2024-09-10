VectorTileLayer::VectorTileLayer(pbf layer) : data(layer) {
    std::vector<std::string> stacks;

    while (layer.next()) {
        if (layer.tag == 1) { // name
            name = layer.string();
        } else if (layer.tag == 3) { // keys
            keys.emplace_back(layer.string());
            key_index.emplace(keys.back(), keys.size() - 1);
        } else if (layer.tag == 4) { // values
            values.emplace_back(std::move(parseValue(layer.message())));
        } else if (layer.tag == 5) { // extent
            extent = layer.varint();
        } else {
            layer.skip();
        }
    }
}