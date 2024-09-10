    ConcurrentEdgeAlgorithm(const size_t nthreads, Graph& graph, FactoryPtr factory)
        : nthreads_(nthreads), graph_(graph), factory_(factory) {

        TRACE("Run in " << nthreads_ << " threads")

        GluedVertexGraph glued_vertex_graph (graph);
        DevisibleTree<GluedVertexGraph> tree (glued_vertex_graph);

        const size_t component_size = tree.GetSize() / nthreads;

        for (size_t thread = 0; thread < nthreads_; ++thread) {
            vector<VertexId> vertices;
            if (thread == nthreads_ - 1) {
                tree.SeparateVertices(vertices, tree.GetSize());
            } else {
                tree.SeparateVertices(vertices, component_size);
            }

            size_t actual_size = vertices.size();
            for (size_t i = 0; i < actual_size; ++i) {
                vertices.push_back(graph.conjugate(vertices[i]));
            }

            ComponentPtr ptr (
                new ConjugateComponent(
                    graph,
                    restricted::PeriodicIdDistributor(graph.GetGraphIdDistributor(),
                            graph.GetGraphIdDistributor()->GetId(),
                            nthreads
                                                     ),
                    vertices.begin(),
                    vertices.end()
                )
            );

            components_.push_back(ptr);
        }

        for (size_t i = 0; i < nthreads_; ++i) {
            RunnerPtr ptr (new Runner(*components_[i], factory->CreateAlgorithm(*components_[i])));
            runners_.push_back(ptr);
        }
    }