  virtual void update(const gdl::Clock& clock, const gdl::Input& input)
  {
    _timeout += static_cast<float>(clock.getElapsed());
    if (_timeout > 3.0f)
      {
	_exploded = true;
	_timeout = 0.0f;
      }
  }