void scanFile(const char *path) {
    sp<FileSource> file = new FileSource(path);
    CHECK_EQ(file->initCheck(), (status_t)OK);

    ID3 tag(file);
    if (!tag.isValid()) {
        printf("FAIL %s\n", path);
    } else {
        printf("SUCCESS %s\n", path);

        ID3::Iterator it(tag, NULL);
        while (!it.done()) {
            String8 id;
            it.getID(&id);

            CHECK(id.length() > 0);
            if (id[0] == 'T') {
                String8 text;
                it.getString(&text);

                printf("  found text frame '%s': %s\n", id.string(), text.string());
            } else {
                printf("  found frame '%s'.\n", id.string());
            }

            it.next();
        }

        size_t dataSize;
        String8 mime;
        const void *data = tag.getAlbumArt(&dataSize, &mime);

        if (data) {
            printf("found album art: size=%zu mime='%s'\n", dataSize,
                   mime.string());

            hexdump(data, dataSize > 128 ? 128 : dataSize);
        }
    }
}