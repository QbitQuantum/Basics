Future<Nothing> NetworkCniIsolatorProcess::_cleanup(
    const ContainerID& containerId,
    const list<Future<Nothing>>& detaches)
{
  CHECK(infos.contains(containerId));

  vector<string> messages;
  foreach (const Future<Nothing>& detach, detaches) {
    if (!detach.isReady()) {
      messages.push_back(
          detach.isFailed() ? detach.failure() : "discarded");
    }
  }

  if (!messages.empty()) {
    return Failure(strings::join("\n", messages));
  }

  const string containerDir =
      paths::getContainerDir(rootDir.get(), containerId.value());

  const string target =
      paths::getNamespacePath(rootDir.get(), containerId.value());

  if (os::exists(target)) {
    Try<Nothing> unmount = fs::unmount(target);
    if (unmount.isError()) {
      return Failure(
          "Failed to unmount the network namespace handle '" +
          target + "': " + unmount.error());
    }
  }

  Try<Nothing> rmdir = os::rmdir(containerDir);
  if (rmdir.isError()) {
    return Failure(
        "Failed to remove the container directory '" +
        containerDir + "': " + rmdir.error());
  }

  infos.erase(containerId);

  return Nothing();
}