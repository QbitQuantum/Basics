/*!
  */
void SimpleRenderer::notifyOfRenderingProgress(
    const uint32 cycle,
    const Clock::duration& time,
    const std::string_view& status) const noexcept
{
  if (progress_callback_) {
    const double cycle_progress = (0 < cycleToFinish())
        ? zisc::cast<double>(cycle) / zisc::cast<double>(cycleToFinish())
        : 0.0;
    const auto time_to_finish = timeToFinish().count();
    const double time_progress = (0 < time_to_finish)
        ? zisc::cast<double>(time.count()) / zisc::cast<double>(time_to_finish)
        : 0.0;
    double progress = zisc::max(cycle_progress, time_progress);
    progress = zisc::clamp(progress, 0.0, 1.0);
    progress_callback_(progress, status);
  }
}