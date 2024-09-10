void SongLoader::LoadRemote() {
  qLog(Debug) << "Loading remote file" << url_;

  // It's not a local file so we have to fetch it to see what it is.  We use
  // gstreamer to do this since it handles funky URLs for us (http://, ssh://,
  // etc) and also has typefinder plugins.
  // First we wait for typefinder to tell us what it is.  If it's not text/plain
  // or text/uri-list assume it's a song and return success.
  // Otherwise wait to get 512 bytes of data and do magic on it - if the magic
  // fails then we don't know what it is so return failure.
  // If the magic succeeds then we know for sure it's a playlist - so read the
  // rest of the file, parse the playlist and return success.

  timeout_timer_->start(timeout_);

  // Create the pipeline - it gets unreffed if it goes out of scope
  std::shared_ptr<GstElement> pipeline(gst_pipeline_new(nullptr),
                                       std::bind(&gst_object_unref, _1));

  // Create the source element automatically based on the URL
  GstElement* source = gst_element_make_from_uri(
      GST_URI_SRC, url_.toEncoded().constData(), nullptr, nullptr);
  if (!source) {
    qLog(Warning) << "Couldn't create gstreamer source element for"
                  << url_.toString();
    return;
  }

  // Create the other elements and link them up
  GstElement* typefind = gst_element_factory_make("typefind", nullptr);
  GstElement* fakesink = gst_element_factory_make("fakesink", nullptr);

  gst_bin_add_many(GST_BIN(pipeline.get()), source, typefind, fakesink,
                   nullptr);
  gst_element_link_many(source, typefind, fakesink, nullptr);

  // Connect callbacks
  GstBus* bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline.get()));
  CHECKED_GCONNECT(typefind, "have-type", &TypeFound, this);
  gst_bus_set_sync_handler(bus, BusCallbackSync, this, NULL);
  gst_bus_add_watch(bus, BusCallback, this);

  // Add a probe to the sink so we can capture the data if it's a playlist
  GstPad* pad = gst_element_get_static_pad(fakesink, "sink");
  gst_pad_add_probe(pad, GST_PAD_PROBE_TYPE_BUFFER, &DataReady, this, NULL);
  gst_object_unref(pad);

  QEventLoop loop;
  loop.connect(this, SIGNAL(LoadRemoteFinished()), SLOT(quit()));

  // Start "playing"
  gst_element_set_state(pipeline.get(), GST_STATE_PLAYING);
  pipeline_ = pipeline;

  // Wait until loading is finished
  loop.exec();
}