ompl::base::PlannerStatus ompl::geometric::RRTstar::solve(const base::PlannerTerminationCondition &ptc)
{
    checkValidity();
    base::Goal                  *goal   = pdef_->getGoal().get();
    base::GoalSampleableRegion  *goal_s = dynamic_cast<base::GoalSampleableRegion*>(goal);

    bool symCost = opt_->isSymmetric();

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
            startMotions_.push_back(motion);
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

    //Allocate a sampler if necessary
    if (!sampler_ && !infSampler_)
    {
        allocSampler();
    }

    OMPL_INFORM("%s: Starting planning with %u states already in datastructure", getName().c_str(), nn_->size());

    if ((useTreePruning_ || useRejectionSampling_ || useInformedSampling_ || useNewStateRejection_) && !si_->getStateSpace()->isMetricSpace())
        OMPL_WARN("%s: The state space (%s) is not metric and as a result the optimization objective may not satisfy the triangle inequality. "
                  "You may need to disable pruning or rejection."
                  , getName().c_str(), si_->getStateSpace()->getName().c_str());

    const base::ReportIntermediateSolutionFn intermediateSolutionCallback = pdef_->getIntermediateSolutionCallback();

    Motion *solution       = lastGoalMotion_;

    Motion *approximation  = nullptr;
    double approximatedist = std::numeric_limits<double>::infinity();
    bool sufficientlyShort = false;

    auto *rmotion        = new Motion(si_);
    base::State *rstate    = rmotion->state;
    base::State *xstate    = si_->allocState();

    std::vector<Motion*>       nbh;

    std::vector<base::Cost>    costs;
    std::vector<base::Cost>    incCosts;
    std::vector<std::size_t>   sortedCostIndices;

    std::vector<int>           valid;
    unsigned int               rewireTest = 0;
    unsigned int               statesGenerated = 0;

    if (solution)
        OMPL_INFORM("%s: Starting planning with existing solution of cost %.5f", getName().c_str(), solution->cost.value());

    if (useKNearest_)
        OMPL_INFORM("%s: Initial k-nearest value of %u", getName().c_str(), (unsigned int)std::ceil(k_rrg_ * log((double)(nn_->size() + 1u))));
    else
        OMPL_INFORM("%s: Initial rewiring radius of %.2f", getName().c_str(), std::min(maxDistance_, r_rrg_*std::pow(log((double)(nn_->size() + 1u))/((double)(nn_->size() + 1u)), 1/(double)(si_->getStateDimension()))));

    // our functor for sorting nearest neighbors
    CostIndexCompare compareFn(costs, *opt_);

    while (ptc == false)
    {
        iterations_++;

        // sample random state (with goal biasing)
        // Goal samples are only sampled until maxSampleCount() goals are in the tree, to prohibit duplicate goal states.
        if (goal_s && goalMotions_.size() < goal_s->maxSampleCount() && rng_.uniform01() < goalBias_ && goal_s->canSample())
            goal_s->sampleGoal(rstate);
        else
        {
            // Attempt to generate a sample, if we fail (e.g., too many rejection attempts), skip the remainder of this loop and return to try again
            if (!sampleUniform(rstate))
                continue;
        }

        // find closest state in the tree
        Motion *nmotion = nn_->nearest(rmotion);

        if (intermediateSolutionCallback && si_->equalStates(nmotion->state, rstate))
            continue;

        base::State *dstate = rstate;

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
            auto *motion = new Motion(si_);
            si_->copyState(motion->state, dstate);
            motion->parent = nmotion;
            motion->incCost = opt_->motionCost(nmotion->state, motion->state);
            motion->cost = opt_->combineCosts(nmotion->cost, motion->incCost);

            // Find nearby neighbors of the new motion
            getNeighbors(motion, nbh);

            rewireTest += nbh.size();
            ++statesGenerated;

            // cache for distance computations
            //
            // Our cost caches only increase in size, so they're only
            // resized if they can't fit the current neighborhood
            if (costs.size() < nbh.size())
            {
                costs.resize(nbh.size());
                incCosts.resize(nbh.size());
                sortedCostIndices.resize(nbh.size());
            }

            // cache for motion validity (only useful in a symmetric space)
            //
            // Our validity caches only increase in size, so they're
            // only resized if they can't fit the current neighborhood
            if (valid.size() < nbh.size())
                valid.resize(nbh.size());
            std::fill(valid.begin(), valid.begin() + nbh.size(), 0);

            // Finding the nearest neighbor to connect to
            // By default, neighborhood states are sorted by cost, and collision checking
            // is performed in increasing order of cost
            if (delayCC_)
            {
                // calculate all costs and distances
                for (std::size_t i = 0 ; i < nbh.size(); ++i)
                {
                    incCosts[i] = opt_->motionCost(nbh[i]->state, motion->state);
                    costs[i] = opt_->combineCosts(nbh[i]->cost, incCosts[i]);
                }

                // sort the nodes
                //
                // we're using index-value pairs so that we can get at
                // original, unsorted indices
                for (std::size_t i = 0; i < nbh.size(); ++i)
                    sortedCostIndices[i] = i;
                std::sort(sortedCostIndices.begin(), sortedCostIndices.begin() + nbh.size(),
                          compareFn);

                // collision check until a valid motion is found
                //
                // ASYMMETRIC CASE: it's possible that none of these
                // neighbors are valid. This is fine, because motion
                // already has a connection to the tree through
                // nmotion (with populated cost fields!).
                for (std::vector<std::size_t>::const_iterator i = sortedCostIndices.begin();
                     i != sortedCostIndices.begin() + nbh.size();
                     ++i)
                {
                    if (nbh[*i] == nmotion || si_->checkMotion(nbh[*i]->state, motion->state))
                    {
                        motion->incCost = incCosts[*i];
                        motion->cost = costs[*i];
                        motion->parent = nbh[*i];
                        valid[*i] = 1;
                        break;
                    }
                    else valid[*i] = -1;
                }
            }
            else // if not delayCC
            {
                motion->incCost = opt_->motionCost(nmotion->state, motion->state);
                motion->cost = opt_->combineCosts(nmotion->cost, motion->incCost);
                // find which one we connect the new state to
                for (std::size_t i = 0 ; i < nbh.size(); ++i)
                {
                    if (nbh[i] != nmotion)
                    {
                        incCosts[i] = opt_->motionCost(nbh[i]->state, motion->state);
                        costs[i] = opt_->combineCosts(nbh[i]->cost, incCosts[i]);
                        if (opt_->isCostBetterThan(costs[i], motion->cost))
                        {
                            if (si_->checkMotion(nbh[i]->state, motion->state))
                            {
                                motion->incCost = incCosts[i];
                                motion->cost = costs[i];
                                motion->parent = nbh[i];
                                valid[i] = 1;
                            }
                            else valid[i] = -1;
                        }
                    }
                    else
                    {
                        incCosts[i] = motion->incCost;
                        costs[i] = motion->cost;
                        valid[i] = 1;
                    }
                }
            }

            if (useNewStateRejection_)
            {
                if (opt_->isCostBetterThan(solutionHeuristic(motion), bestCost_))
                {
                    nn_->add(motion);
                    motion->parent->children.push_back(motion);
                }
                else // If the new motion does not improve the best cost it is ignored.
                {
                    si_->freeState(motion->state);
                    delete motion;
                    continue;
                }
            }
            else
            {
                // add motion to the tree
                nn_->add(motion);
                motion->parent->children.push_back(motion);
            }

            bool checkForSolution = false;
            for (std::size_t i = 0; i < nbh.size(); ++i)
            {
                if (nbh[i] != motion->parent)
                {
                    base::Cost nbhIncCost;
                    if (symCost)
                        nbhIncCost = incCosts[i];
                    else
                        nbhIncCost = opt_->motionCost(motion->state, nbh[i]->state);
                    base::Cost nbhNewCost = opt_->combineCosts(motion->cost, nbhIncCost);
                    if (opt_->isCostBetterThan(nbhNewCost, nbh[i]->cost))
                    {
                        bool motionValid;
                        if (valid[i] == 0)
                        {
                            motionValid = si_->checkMotion(motion->state, nbh[i]->state);
                        }
                        else
                        {
                            motionValid = (valid[i] == 1);
                        }

                        if (motionValid)
                        {
                            // Remove this node from its parent list
                            removeFromParent (nbh[i]);

                            // Add this node to the new parent
                            nbh[i]->parent = motion;
                            nbh[i]->incCost = nbhIncCost;
                            nbh[i]->cost = nbhNewCost;
                            nbh[i]->parent->children.push_back(nbh[i]);

                            // Update the costs of the node's children
                            updateChildCosts(nbh[i]);

                            checkForSolution = true;
                        }
                    }
                }
            }

            // Add the new motion to the goalMotion_ list, if it satisfies the goal
            double distanceFromGoal;
            if (goal->isSatisfied(motion->state, &distanceFromGoal))
            {
                goalMotions_.push_back(motion);
                checkForSolution = true;
            }

            // Checking for solution or iterative improvement
            if (checkForSolution)
            {
                bool updatedSolution = false;
                for (auto & goalMotion : goalMotions_)
                {
                    if (opt_->isCostBetterThan(goalMotion->cost, bestCost_))
                    {
                        if (opt_->isFinite(bestCost_) == false)
                        {
                            OMPL_INFORM("%s: Found an initial solution with a cost of %.2f in %u iterations (%u vertices in the graph)", getName().c_str(), goalMotion->cost.value(), iterations_, nn_->size());
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
                    else if (!solution ||
                         opt_->isCostBetterThan(goalMotion->cost,solution->cost))
                    {
                        solution = goalMotion;
                        updatedSolution = true;
                    }
                }

                if (updatedSolution)
                {
                    if (useTreePruning_)
                    {
                        pruneTree(bestCost_);
                    }

                    if (intermediateSolutionCallback)
                    {
                        std::vector<const base::State *> spath;
                        Motion *intermediate_solution = solution->parent; // Do not include goal state to simplify code.

                        //Push back until we find the start, but not the start itself
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
        std::vector<Motion*> mpath;
        while (solution != nullptr)
        {
            mpath.push_back(solution);
            solution = solution->parent;
        }

        // set the solution path
        auto *geoPath = new PathGeometric(si_);
        for (int i = mpath.size() - 1 ; i >= 0 ; --i)
            geoPath->append(mpath[i]->state);

        base::PathPtr path(geoPath);
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

    OMPL_INFORM("%s: Created %u new states. Checked %u rewire options. %u goal states in tree. Final solution cost %.3f", getName().c_str(), statesGenerated, rewireTest, goalMotions_.size(), bestCost_.value());

    return base::PlannerStatus(addedSolution, approximate);
}