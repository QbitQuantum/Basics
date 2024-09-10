	/**
	 * Returns the thread utilization.
	 *
	 * @return A value in between zero and one, where zero means the thread was completely idle, and one means the thread was completely busy.
	 */
	static double Utilization() { StackTrace trace(__METHOD__, __FILE__, __LINE__);
		double duration = (DateTime::Utc() - Started).TotalMilliseconds();
		return (duration - Idle.TotalMilliseconds()) / duration;
	}