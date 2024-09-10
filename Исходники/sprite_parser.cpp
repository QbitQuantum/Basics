SpriteParseResult parseSprite(const std::string& image, const std::string& json) {
    Sprites sprites;
    PremultipliedImage raster;

    try {
        raster = decodeImage(image);
    } catch (...) {
        return std::current_exception();
    }

    JSDocument doc;
    doc.Parse<0>(json.c_str());

    if (doc.HasParseError()) {
        std::stringstream message;
        message << "Failed to parse JSON: " << rapidjson::GetParseError_En(doc.GetParseError()) << " at offset " << doc.GetErrorOffset();
        return std::make_exception_ptr(std::runtime_error(message.str()));
    } else if (!doc.IsObject()) {
        return std::make_exception_ptr(std::runtime_error("Sprite JSON root must be an object"));
    } else {
        for (JSValue::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
            const std::string name = { itr->name.GetString(), itr->name.GetStringLength() };
            const JSValue& value = itr->value;

            if (value.IsObject()) {
                const uint16_t x = getUInt16(value, "x", 0);
                const uint16_t y = getUInt16(value, "y", 0);
                const uint16_t width = getUInt16(value, "width", 0);
                const uint16_t height = getUInt16(value, "height", 0);
                const double pixelRatio = getDouble(value, "pixelRatio", 1);
                const bool sdf = getBoolean(value, "sdf", false);

                auto sprite = createSpriteImage(raster, x, y, width, height, pixelRatio, sdf);
                if (sprite) {
                    sprites.emplace(name, sprite);
                }
            }
        }
    }

    return sprites;
}