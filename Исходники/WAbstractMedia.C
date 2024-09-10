DomElement *WAbstractMedia::createDomElement(WApplication *app)
{
  DomElement *result = 0;

  if (isInLayout()) {
    // It's easier to set WT_RESIZE_JS after the following code,
    // but if it's not set, the alternative content will think that
    // it is not included in a layout manager. Set some phony function
    // now, which will be overwritten later in this method.
    setJavaScriptMember(WT_RESIZE_JS, "function() {}");
  }

  if (app->environment().agentIsIElt(9) ||
      app->environment().agent() == WEnvironment::MobileWebKitAndroid) {
    // Shortcut: IE misbehaves when it encounters a media element
    result = DomElement::createNew(DomElement_DIV);
    if (alternative_)
      result->addChild(alternative_->createSDomElement(app));
  } else {
    DomElement *media = createMediaDomElement();
    DomElement *wrap = 0;
    if (isInLayout()) {
      media->setProperty(PropertyStylePosition, "absolute");
      media->setProperty(PropertyStyleLeft, "0");
      media->setProperty(PropertyStyleRight, "0");
      wrap = DomElement::createNew(DomElement_DIV);
      wrap->setProperty(PropertyStylePosition, "relative");
    }
    result = wrap ? wrap : media;
    if (wrap) {
      mediaId_ = id() + "_media";
      media->setId(mediaId_);
    } else {
      mediaId_ = id();
    }

    updateMediaDom(*media, true);
    // Create the 'source' elements
    for (std::size_t i = 0; i < sources_.size(); ++i) {
      DomElement *src = DomElement::createNew(DomElement_SOURCE);
      src->setId(mediaId_ + "s" + boost::lexical_cast<std::string>(i));
      renderSource(src, *sources_[i], i + 1 >= sources_.size());
      media->addChild(src);
    }
    sourcesRendered_ = sources_.size();
    sourcesChanged_ = false;

    if (wrap) {
      wrap->addChild(media);
    }
  }

  if (isInLayout()) {
    std::stringstream ss;
    ss <<
      """function(self, w, h) {";
    if (!mediaId_.empty()) {
      ss <<
        ""  "v=" + jsMediaRef() + ";"
        ""  "if (v) {"
	""    "if (w >= 0) "
        ""      "v.setAttribute('width', w);"
        ""    "if (h >= 0) "
	""      "v.setAttribute('height', h);"
        ""  "}";
    }
    if (alternative_) {
      ss <<
        """a=" + alternative_->jsRef() + ";"
        ""  "if (a && a." << WT_RESIZE_JS <<")"
        ""    "a." << WT_RESIZE_JS << "(a, w, h);";
    }
    ss
      <<"}";
    setJavaScriptMember(WT_RESIZE_JS, ss.str());
  }

  setId(result, app);
  updateDom(*result, true);

  if (isInLayout()) {
    result->setEvent(PLAYBACKSTARTED_SIGNAL, std::string());
    result->setEvent(PLAYBACKPAUSED_SIGNAL, std::string());
    result->setEvent(ENDED_SIGNAL, std::string());
    result->setEvent(TIMEUPDATED_SIGNAL, std::string());
    result->setEvent(VOLUMECHANGED_SIGNAL, std::string());
  }

  setJavaScriptMember("mediaId", "'" + mediaId_ + "'");

  return result;
}