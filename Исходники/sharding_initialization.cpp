Status initializeGlobalShardingState(OperationContext* txn,
                                     const ConnectionString& configCS,
                                     bool allowNetworking) {
    SyncClusterConnection::setConnectionValidationHook(
        [](const HostAndPort& target, const executor::RemoteCommandResponse& isMasterReply) {
            return ShardingNetworkConnectionHook::validateHostImpl(target, isMasterReply);
        });
    auto network =
        executor::makeNetworkInterface(stdx::make_unique<ShardingNetworkConnectionHook>(),
                                       stdx::make_unique<ShardingEgressMetadataHook>());
    auto networkPtr = network.get();
    auto shardRegistry(
        stdx::make_unique<ShardRegistry>(stdx::make_unique<RemoteCommandTargeterFactoryImpl>(),
                                         makeTaskExecutorPool(std::move(network)),
                                         networkPtr,
                                         makeTaskExecutor(executor::makeNetworkInterface()),
                                         configCS));

    try {
        std::unique_ptr<ForwardingCatalogManager> catalogManager =
            stdx::make_unique<ForwardingCatalogManager>(
                getGlobalServiceContext(),
                configCS,
                shardRegistry.get(),
                HostAndPort(getHostName(), serverGlobalParams.port));

        shardRegistry->startup();
        grid.init(
            std::move(catalogManager),
            std::move(shardRegistry),
            stdx::make_unique<ClusterCursorManager>(getGlobalServiceContext()->getClockSource()));

        auto status = grid.catalogManager(txn)->startup(txn, allowNetworking);
        if (!status.isOK()) {
            return status;
        }

        // ShardRegistry::reload may throw, in which case we will just fail the initialization
        if (serverGlobalParams.configsvrMode == CatalogManager::ConfigServerMode::NONE) {
            grid.shardRegistry()->reload(txn);
        }
    } catch (const DBException& ex) {
        return ex.toStatus();
    }

    return Status::OK();
}