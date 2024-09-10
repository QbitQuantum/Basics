void GD_CORE_API ProjectStripper::StripProjectForLayoutEdition(
    gd::Project& project, const gd::String& layoutName) {
  while (project.GetExternalEventsCount() > 0)
    project.RemoveExternalEvents(project.GetExternalEvents(0).GetName());

  for (unsigned int i = 0; i < project.GetLayoutsCount(); ++i) {
    auto& layout = project.GetLayout(i);
    if (layoutName == layout.GetName()) continue;

    project.GetLayout(i).GetEvents().Clear();
    project.GetLayout(i).GetInitialInstances().Clear();
  }

  for (unsigned int i = 0; i < project.GetExternalEventsCount(); ++i) {
    project.GetExternalEvents(i).GetEvents().Clear();
  }

  for (unsigned int i = 0; i < project.GetExternalLayoutsCount(); ++i) {
    project.GetExternalLayout(i).GetInitialInstances().Clear();
  }
}