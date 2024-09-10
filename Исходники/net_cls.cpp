Future<Nothing> CgroupsNetClsIsolatorProcess::isolate(
    const ContainerID& containerId,
    pid_t pid)
{
  if (!infos.contains(containerId)) {
    return Failure("Unknown container");
  }

  const Info& info = infos.at(containerId);

  Try<Nothing> assign = cgroups::assign(hierarchy, info.cgroup, pid);
  if (assign.isError()) {
    return Failure("Failed to assign container '" +
                   stringify(containerId) + "' to its own cgroup '" +
                   path::join(hierarchy, info.cgroup) +
                   "': " + assign.error());
  }

  return Nothing();
}