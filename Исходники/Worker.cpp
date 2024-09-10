    void parseRasterTile(std::unique_ptr<RasterBucket> bucket,
                         const std::shared_ptr<const std::string> data,
                         std::function<void(RasterTileParseResult)> callback) {
        PremultipliedImage image;

        try {
            image = decodeImage(*data);
        } catch (...) {
            callback(RasterTileParseResult("error parsing raster image"));
            return;
        }

        bucket->setImage(std::move(image));

        callback(RasterTileParseResult(std::move(bucket)));
    }