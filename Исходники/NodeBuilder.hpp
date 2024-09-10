        void doBuildNode(
            const typename NodeTypes<Status, T>::ValueList& valueList,
            const PointList& pointList,
            int depthRemaining,
            bool trueBranch,
            const State& collectedState,
            Node<Status, T>& result)
        {
            typedef typename NodeTypes<Status, T>::ValuePtr ValuePtr;
            typedef typename NodeTypes<Status, T>::ValueList ValueList;

            if (valueList.empty() ||
                    pointList.empty() ||
                    depthRemaining == 0) {
                result = createLeaf<Status, T>(valueList, depthRemaining, collectedState);
                return;
            }
            assert(!valueList.empty());
            if (checker_ && !checkState(
                    *checker_,
                    valueList.front()->first.table(),
                    collectedState)) {
                {
                    boost::unique_lock<MutexType> lock(progressMutex_);
                    ++numLeafsSaved_;
                    numLeafsSavedExp_ += static_cast<int>(exp2(depthRemaining));
                }
                result = createLeaf<Status, T>(ValueList(), depthRemaining, collectedState);
                return;
            }

            std::vector<Point> newFunctorList;
            boost::optional<Point> point;
            State newCollectedState(collectedState);
            if (trueBranch) {
                point = fastFilterPointList(
                        pointList, newFunctorList);
                assert(point);
            } else {
                point = filterPointList(
                        valueList, pointList, newFunctorList);
            }
            if (!point) {
                result = createLeaf<Status, T>(valueList, depthRemaining, collectedState);
                return;
            }
            newCollectedState.addStone(*point);

            ValueList falseValues;
            boost::remove_copy_if(valueList,
                    std::back_inserter(falseValues),
                    [&point](const ValuePtr& value)
                    { return isStone(value->first, *point); });

            assert(falseValues.size() != valueList.size());
            result = DecisionNode<Status, T, Node<Status, T>>(*point);
            buildDecisionChildren<Status, T, PointList>(
                    falseValues, valueList,
                    newFunctorList, depthRemaining - 1,
                    collectedState, newCollectedState,
                    result);

        } // doBuildNode