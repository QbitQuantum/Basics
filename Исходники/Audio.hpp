    ~Audio()
    {
      // Invoke the AudioShutdown event. This lets the EventListener objects
      //  release so that they don't try to release after the FMOD Studio
      //  system is released below.
      EventData eventData;
      eventData["Audio"] = this;
      InvokeEvent("AudioShutdown", eventData);

      // Destroy the FMOD Studio system.
      FmodCall(system->release());
    }