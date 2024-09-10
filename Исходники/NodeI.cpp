void
NodeI::check()
{
    {
        Lock sync(*this);
        if(_destroy)
        {
            return;
        }
        assert(!_mergeTask);

        if(_state == NodeStateElection || _state == NodeStateReorganization || _coord != _id)
        {
            assert(_checkTask);
            _timer->schedule(_checkTask, _electionTimeout);
            return;
        }

        // Next get the set of nodes that were detected as unreachable
        // from the replica and remove them from our slave list.
        vector<int> dead;
        _observers->getReapedSlaves(dead);
        if(!dead.empty())
        {
            for(vector<int>::const_iterator p = dead.begin(); p != dead.end(); ++p)
            {
                set<GroupNodeInfo>::iterator q = _up.find(GroupNodeInfo(*p));
                if(q != _up.end())
                {
                    if(_traceLevels->election > 0)
                    {
                        Ice::Trace out(_traceLevels->logger, _traceLevels->electionCat);
                        out << "node " << _id << ": reaping slave " << *p;
                    }
                    _up.erase(q);
                }
            }

            // If we no longer have the majority of the nodes under our
            // care then we need to stop our replica.
            if(_up.size() < _nodes.size()/2)
            {
                if(_traceLevels->election > 0)
                {
                    Ice::Trace out(_traceLevels->logger, _traceLevels->electionCat);
                    out << "node " << _id << ": stopping replica";
                }
                // Clear _checkTask -- recovery() will reset the
                // timer.
                assert(_checkTask);
                _checkTask = 0;
                recovery();
                return;
            }
        }
    }

    // See if other groups exist for possible merge.
    set<int> tmpset;
    int max = -1;
    for(map<int, NodePrx>::const_iterator p = _nodes.begin(); p != _nodes.end(); ++p)
    {
        if(p->first == _id)
        {
            continue;
        }
        try
        {
            if(p->second->areYouCoordinator())
            {
                if(p->first > max)
                {
                    max = p->first;
                }
                tmpset.insert(p->first);
            }
        }
        catch(const Ice::Exception& ex)
        {
            if(_traceLevels->election > 0)
            {
                Ice::Trace out(_traceLevels->logger, _traceLevels->electionCat);
                out << "node " << _id << ": call on node " << p->first << " failed: " << ex;
            }
        }
    }

    Lock sync(*this);

    // If the node state has changed while the mutex has been released
    // then bail. We don't schedule a re-check since we're either
    // destroyed in which case we're going to terminate or the end of
    // the election/reorg will re-schedule the check.
    if(_destroy || _state == NodeStateElection || _state == NodeStateReorganization || _coord != _id)
    {
        _checkTask = 0;
        return;
    }

    // If we didn't find any coordinators then we're done. Reschedule
    // the next check and terminate.
    if(tmpset.empty())
    {
        assert(_checkTask);
        _timer->schedule(_checkTask, _electionTimeout);
        return;
    }

    // _checkTask == 0 means that the check isn't scheduled.
    _checkTask = 0;

    if(_traceLevels->election > 0)
    {
        Ice::Trace out(_traceLevels->logger, _traceLevels->electionCat);
        out << "node " << _id << ": highest priority node count: " << max;
    }

    IceUtil::Time delay = IceUtil::Time::seconds(0);
    if(_id < max)
    {
        // Reschedule timer proportial to p-i.
        delay = _mergeTimeout + _mergeTimeout * (max - _id);
        if(_traceLevels->election > 0)
        {
            Ice::Trace out(_traceLevels->logger, _traceLevels->electionCat);
            out << "node " << _id << ": scheduling merge in " << delay.toDuration()
                << " seconds";
        }
    }

    assert(!_mergeTask);
    _mergeTask = new MergeTask(this, tmpset);
    _timer->schedule(_mergeTask, delay);
}