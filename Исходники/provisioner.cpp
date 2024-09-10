Future<ProvisionInfo> ProvisionerProcess::provision(
    const ContainerID& containerId,
    const Image& image)
{
  if (!stores.contains(image.type())) {
    return Failure(
        "Unsupported container image type: " +
        stringify(image.type()));
  }

  // Get and then provision image layers from the store.
  return stores.get(image.type()).get()->get(image, defaultBackend)
    .then(defer(self(),
                &Self::_provision,
                containerId,
                image,
                defaultBackend,
                lambda::_1));
}