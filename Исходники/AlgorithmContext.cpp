		void log(const std::string& file, int line, Logger::LogLevel level, const std::string& msg) {
			LOG4CXX_DEBUG(m_frameworkLogger, "Logging to context at level [ " << Logger::enumToString(level) << "]; " << msg);
			std::unique_lock<std::mutex> lock(m_loggerMutex);
			std::vector<Logger*>::iterator iter = m_loggers.begin();
			for ( ; iter!=m_loggers.end(); iter++ ) {
				Logger* logger = *iter;
				logger->log(file, line, level, msg);
			}
			lock.unlock();
		}