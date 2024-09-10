void ImageSource::loadDescription(FileSource& fileSource) {
    if (!url) {
        loaded = true;
    }

    if (req ||  loaded) {
        return;
    }
    const Resource imageResource { Resource::Image, *url, {}, Resource::Necessity::Required };

    req = fileSource.request(imageResource, [this](Response res) {
        if (res.error) {
            observer->onSourceError(*this, std::make_exception_ptr(std::runtime_error(res.error->message)));
        } else if (res.notModified) {
            return;
        } else if (res.noContent) {
            observer->onSourceError(*this, std::make_exception_ptr(std::runtime_error("unexpectedly empty image url")));
        } else {
            try {
                UnassociatedImage image = util::unpremultiply(decodeImage(*res.data));
                baseImpl = makeMutable<Impl>(impl(), std::move(image));
            } catch (...) {
                observer->onSourceError(*this, std::current_exception());
            }
            loaded = true;
            observer->onSourceLoaded(*this);
        }
    });
}