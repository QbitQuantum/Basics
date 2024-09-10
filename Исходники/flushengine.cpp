vespalib::string
FlushEngine::flushNextTarget(const vespalib::string & name)
{
    std::pair<FlushContext::List,bool> lst = getSortedTargetList();
    if (lst.second) {
        // Everything returned from a priority strategy should be flushed
        flushAll(lst.first);
        _executor.sync();
        prune();
        std::lock_guard<std::mutex> strategyGuard(_strategyLock);
        _priorityStrategy.reset();
        _strategyCond.notify_all();
        return "";
    }
    if (lst.first.empty()) {
        LOG(debug, "No target to flush.");
        return "";
    }
    FlushContext::SP ctx = initNextFlush(lst.first);
    if ( ! ctx) {
        LOG(debug, "All targets refused to flush.");
        return "";
    }
    if ( name == ctx->getName()) {
        LOG(info, "The same target %s out of %ld has been asked to flush again. "
                  "This might indicate flush logic flaw so I will wait 100 ms before doing it.",
                  name.c_str(), lst.first.size());
        std::this_thread::sleep_for(100ms);
    }
    _executor.execute(std::make_unique<FlushTask>(initFlush(*ctx), *this, ctx));
    return ctx->getName();
}