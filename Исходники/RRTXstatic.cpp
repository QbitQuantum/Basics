ompl::base::PlannerStatus ompl::geometric::RRTXstatic::solve(const base::PlannerTerminationCondition &ptc)
{
    checkValidity();
    base::Goal *goal = pdef_->getGoal().get();
    auto *goal_s = dynamic_cast<base::GoalSampleableRegion *>(goal);

    // Check if there are more starts
    if (pis_.haveMoreStartStates() == true)
    {
        // There are, add them
        while (const base::State *st = pis_.nextStart())
        {
            auto *motion = new Motion(si_);
            si_->copyState(motion->state, st);
            motion->cost = opt_->identityCost();
            nn_->add(motion);
        }

        // And assure that, if we're using an informed sampler, it's reset
        infSampler_.reset();
    }
    // No else

    if (nn_->size() == 0)
    {
        OMPL_ERROR("%s: There are no valid initial states!", getName().c_str());
        return base::PlannerStatus::INVALID_START;
    }

    // Allocate a sampler if necessary
    if (!sampler_ && !infSampler_)
    {
        allocSampler();
    }

    OMPL_INFORM("%s: Starting planning with %u states already in datastructure", getName().c_str(), nn_->size());

    if (!si_->getStateSpace()->isMetricSpace())
        OMPL_WARN("%s: The state space (%s) is not metric and as a result the optimization objective may not satisfy "
                  "the triangle inequality. "
                  "You may need to disable rejection.",
                  getName().c_str(), si_->getStateSpace()->getName().c_str());

    const base::ReportIntermediateSolutionFn intermediateSolutionCallback = pdef_->getIntermediateSolutionCallback();

    Motion *solution = lastGoalMotion_;

    Motion *approximation = nullptr;
    double approximatedist = std::numeric_limits<double>::infinity();
    bool sufficientlyShort = false;

    auto *rmotion = new Motion(si_);
    base::State *rstate = rmotion->state;
    base::State *xstate = si_->allocState();
    base::State *dstate;

    Motion *motion;
    Motion *nmotion;
    Motion *nb;
    Motion *min;
    Motion *c;
    bool feas;

    unsigned int rewireTest = 0;
    unsigned int statesGenerated = 0;

    base::Cost incCost, cost;

    if (solution)
        OMPL_INFORM("%s: Starting planning with existing solution of cost %.5f", getName().c_str(),
                    solution->cost.value());

    if (useKNearest_)
        OMPL_INFORM("%s: Initial k-nearest value of %u", getName().c_str(),
                    (unsigned int)std::ceil(k_rrt_ * log((double)(nn_->size() + 1u))));
    else
        OMPL_INFORM(
            "%s: Initial rewiring radius of %.2f", getName().c_str(),
            std::min(maxDistance_, r_rrt_ * std::pow(log((double)(nn_->size() + 1u)) / ((double)(nn_->size() + 1u)),
                                                     1 / (double)(si_->getStateDimension()))));

    while (ptc == false)
    {
        iterations_++;

        // Computes the RRG values for this iteration (number or radius of neighbors)
        calculateRRG();

        // sample random state (with goal biasing)
        // Goal samples are only sampled until maxSampleCount() goals are in the tree, to prohibit duplicate goal
        // states.
        if (goal_s && goalMotions_.size() < goal_s->maxSampleCount() && rng_.uniform01() < goalBias_ &&
            goal_s->canSample())
            goal_s->sampleGoal(rstate);
        else
        {
            // Attempt to generate a sample, if we fail (e.g., too many rejection attempts), skip the remainder of this
            // loop and return to try again
            if (!sampleUniform(rstate))
                continue;
        }

        // find closest state in the tree
        nmotion = nn_->nearest(rmotion);

        if (intermediateSolutionCallback && si_->equalStates(nmotion->state, rstate))
            continue;

        dstate = rstate;

        // find state to add to the tree
        double d = si_->distance(nmotion->state, rstate);
        if (d > maxDistance_)
        {
            si_->getStateSpace()->interpolate(nmotion->state, rstate, maxDistance_ / d, xstate);
            dstate = xstate;
        }

        // Check if the motion between the nearest state and the state to add is valid
        if (si_->checkMotion(nmotion->state, dstate))
        {
            // create a motion
            motion = new Motion(si_);
            si_->copyState(motion->state, dstate);
            motion->parent = nmotion;
            incCost = opt_->motionCost(nmotion->state, motion->state);
            motion->cost = opt_->combineCosts(nmotion->cost, incCost);

            // Find nearby neighbors of the new motion
            getNeighbors(motion);

            // find which one we connect the new state to
            for (auto it = motion->nbh.begin(); it != motion->nbh.end();)
            {
                nb = it->first;
                feas = it->second;

                // Compute cost using nb as a parent
                incCost = opt_->motionCost(nb->state, motion->state);
                cost = opt_->combineCosts(nb->cost, incCost);
                if (opt_->isCostBetterThan(cost, motion->cost))
                {
                    // Check range and feasibility
                    if ((!useKNearest_ || distanceFunction(motion, nb) < maxDistance_) &&
                        si_->checkMotion(nb->state, motion->state))
                    {
                        // mark than the motino has been checked as valid
                        it->second = true;

                        motion->cost = cost;
                        motion->parent = nb;
                        ++it;
                    }
                    else
                    {
                        // Remove unfeasible neighbor from the list of neighbors
                        it = motion->nbh.erase(it);
                    }
                }
                else
                {
                    ++it;
                }
            }

            // Check if the vertex should included
            if (!includeVertex(motion))
            {
                si_->freeState(motion->state);
                delete motion;
                continue;
            }

            // Update neighbor motions neighbor datastructure
            for (auto it = motion->nbh.begin(); it != motion->nbh.end(); ++it)
            {
                it->first->nbh.emplace_back(motion, it->second);
            }

            // add motion to the tree
            ++statesGenerated;
            nn_->add(motion);
            if (updateChildren_)
                motion->parent->children.push_back(motion);

            // add the new motion to the queue to propagate the changes
            updateQueue(motion);

            bool checkForSolution = false;

            // Add the new motion to the goalMotion_ list, if it satisfies the goal
            double distanceFromGoal;
            if (goal->isSatisfied(motion->state, &distanceFromGoal))
            {
                goalMotions_.push_back(motion);
                checkForSolution = true;
            }

            // Process the elements in the queue and rewire the tree until epsilon-optimality
            while (!q_.empty())
            {
                // Get element to update
                min = q_.top()->data;
                // Remove element from the queue and NULL the handle so that we know it's not in the queue anymore
                q_.pop();
                min->handle = nullptr;

                // Stop cost propagation if it is not in the relevant region
                if (opt_->isCostBetterThan(bestCost_, mc_.costPlusHeuristic(min)))
                    break;

                // Try min as a parent to optimize each neighbor
                for (auto it = min->nbh.begin(); it != min->nbh.end();)
                {
                    nb = it->first;
                    feas = it->second;

                    // Neighbor culling: removes neighbors farther than the neighbor radius
                    if ((!useKNearest_ || min->nbh.size() > rrg_k_) && distanceFunction(min, nb) > rrg_r_)
                    {
                        it = min->nbh.erase(it);
                        continue;
                    }

                    // Calculate cost of nb using min as a parent
                    incCost = opt_->motionCost(min->state, nb->state);
                    cost = opt_->combineCosts(min->cost, incCost);

                    // If cost improvement is better than epsilon
                    if (opt_->isCostBetterThan(opt_->combineCosts(cost, epsilonCost_), nb->cost))
                    {
                        if (nb->parent != min)
                        {
                            // changing parent, check feasibility
                            if (!feas)
                            {
                                feas = si_->checkMotion(nb->state, min->state);
                                if (!feas)
                                {
                                    // Remove unfeasible neighbor from the list of neighbors
                                    it = min->nbh.erase(it);
                                    continue;
                                }
                                else
                                {
                                    // mark than the motino has been checked as valid
                                    it->second = true;
                                }
                            }
                            if (updateChildren_)
                            {
                                // Remove this node from its parent list
                                removeFromParent(nb);
                                // add it as a children of min
                                min->children.push_back(nb);
                            }
                            // Add this node to the new parent
                            nb->parent = min;
                            ++rewireTest;
                        }
                        nb->cost = cost;

                        // Add to the queue for more improvements
                        updateQueue(nb);

                        checkForSolution = true;
                    }
                    ++it;
                }
                if (updateChildren_)
                {
                    // Propagatino of the cost to the children
                    for (auto it = min->children.begin(), end = min->children.end(); it != end; ++it)
                    {
                        c = *it;
                        incCost = opt_->motionCost(min->state, c->state);
                        cost = opt_->combineCosts(min->cost, incCost);
                        c->cost = cost;
                        // Add to the queue for more improvements
                        updateQueue(c);

                        checkForSolution = true;
                    }
                }
            }

            // empty q and reset handles
            while (!q_.empty())
            {
                q_.top()->data->handle = nullptr;
                q_.pop();
            }
            q_.clear();

            // Checking for solution or iterative improvement
            if (checkForSolution)
            {
                bool updatedSolution = false;
                for (auto &goalMotion : goalMotions_)
                {
                    if (opt_->isCostBetterThan(goalMotion->cost, bestCost_))
                    {
                        if (opt_->isFinite(bestCost_) == false)
                        {
                            OMPL_INFORM("%s: Found an initial solution with a cost of %.2f in %u iterations (%u "
                                        "vertices in the graph)",
                                        getName().c_str(), goalMotion->cost.value(), iterations_, nn_->size());
                        }
                        bestCost_ = goalMotion->cost;
                        updatedSolution = true;
                    }

                    sufficientlyShort = opt_->isSatisfied(goalMotion->cost);
                    if (sufficientlyShort)
                    {
                        solution = goalMotion;
                        break;
                    }
                    else if (!solution || opt_->isCostBetterThan(goalMotion->cost, solution->cost))
                    {
                        solution = goalMotion;
                        updatedSolution = true;
                    }
                }

                if (updatedSolution)
                {
                    if (intermediateSolutionCallback)
                    {
                        std::vector<const base::State *> spath;
                        Motion *intermediate_solution =
                            solution->parent;  // Do not include goal state to simplify code.

                        // Push back until we find the start, but not the start itself
                        while (intermediate_solution->parent != nullptr)
                        {
                            spath.push_back(intermediate_solution->state);
                            intermediate_solution = intermediate_solution->parent;
                        }

                        intermediateSolutionCallback(this, spath, bestCost_);
                    }
                }
            }

            // Checking for approximate solution (closest state found to the goal)
            if (goalMotions_.size() == 0 && distanceFromGoal < approximatedist)
            {
                approximation = motion;
                approximatedist = distanceFromGoal;
            }
        }

        // terminate if a sufficient solution is found
        if (solution && sufficientlyShort)
            break;
    }

    bool approximate = (solution == nullptr);
    bool addedSolution = false;
    if (approximate)
        solution = approximation;
    else
        lastGoalMotion_ = solution;

    if (solution != nullptr)
    {
        ptc.terminate();
        // construct the solution path
        std::vector<Motion *> mpath;
        while (solution != nullptr)
        {
            mpath.push_back(solution);
            solution = solution->parent;
        }

        // set the solution path
        auto path = std::make_shared<PathGeometric>(si_);
        for (int i = mpath.size() - 1; i >= 0; --i)
            path->append(mpath[i]->state);

        // Add the solution path.
        base::PlannerSolution psol(path);
        psol.setPlannerName(getName());
        if (approximate)
            psol.setApproximate(approximatedist);
        // Does the solution satisfy the optimization objective?
        psol.setOptimized(opt_, bestCost_, sufficientlyShort);
        pdef_->addSolutionPath(psol);

        addedSolution = true;
    }

    si_->freeState(xstate);
    if (rmotion->state)
        si_->freeState(rmotion->state);
    delete rmotion;

    OMPL_INFORM("%s: Created %u new states. Checked %u rewire options. %u goal states in tree. Final solution cost "
                "%.3f",
                getName().c_str(), statesGenerated, rewireTest, goalMotions_.size(), bestCost_.value());

    return {addedSolution, approximate};
}