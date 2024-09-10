 void Engine::fatalerror(std::string message, std::string title)
 {
     this->message(message,title);
     Shutdown();
 }