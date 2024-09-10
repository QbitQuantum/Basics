    double ParallelOptimize::optimize(stereo_base::Depth &result, const int max_iter) const {
        typedef CompactLabelSpace Space;
        typedef ParallelFusionPipeline<Space> Pipeline;

        bool victorMethod = true;
        result.initialize(width, height, -1);
        const int kFusionSize = 4;

        ParallelFusionOption pipelineOption;
        pipelineOption.num_threads = num_threads + 1;
        pipelineOption.max_iteration = model->nLabel / num_threads / kFusionSize * max_iter;
        const int kLabelPerThread = model->nLabel / pipelineOption.num_threads;

        Pipeline::GeneratorSet generators((size_t)pipelineOption.num_threads);
        Pipeline::SolverSet solvers((size_t)pipelineOption.num_threads);
        vector<Space> initials((size_t)pipelineOption.num_threads);
        vector<ThreadOption> threadOptions((size_t)pipelineOption.num_threads);

        vector<vector<int> > labelSubSpace;
        splitLabel(labelSubSpace);

        const int kPix = model->width * model->height;

        //slave threads
        const int kOtherThread = std::min(num_threads-1, 1);
        for(auto i=0; i<pipelineOption.num_threads - 1; ++i){
            const int startid = labelSubSpace[i].front();
            initials[i].init(kPix, vector<int>(1, startid));
            threadOptions[i].kTotal = kFusionSize + kOtherThread;
            threadOptions[i].kOtherThread = kOtherThread;
            threadOptions[i].solution_exchange_interval = 1;
            if(multiway) {
                generators[i] = shared_ptr<ProposalGenerator<Space> >(new MultiwayStereoGenerator(kPix, labelSubSpace[i]));
                solvers[i] = shared_ptr<FusionSolver<Space> >(new MultiwayStereoSolver(model));
            }else{
                generators[i] = shared_ptr<ProposalGenerator<Space> >(new SimpleStereoGenerator(kPix, labelSubSpace[i]));
                solvers[i] = shared_ptr<FusionSolver<Space> >(new SimpleStereoSolver(model));
            }

            printf("Initial energy on thread %d: %.5f\n", i, solvers[i]->evaluateEnergy(initials[i]));
        }

        //monitor thread
        threadOptions.back().is_monitor = true;
        solvers.back() = shared_ptr<FusionSolver<Space> >(new SimpleStereoMonitor(model));
        generators.back() = shared_ptr<ProposalGenerator<Space> >(new DummyGenerator());

        StereoPipeline parallelFusionPipeline(pipelineOption);
        float t = (float)getTickCount();
        printf("Start runing parallel optimization\n");
        parallelFusionPipeline.runParallelFusion(initials, generators, solvers, threadOptions);
        t = ((float)getTickCount() - t) / (float)getTickFrequency();

        SolutionType<Space > solution;
        parallelFusionPipeline.getBestLabeling(solution);

        printf("Done! Final energy: %.5f, running time: %.3fs\n", solution.first, t);

        std::dynamic_pointer_cast<SimpleStereoMonitor>(solvers.back())->dumpData(file_io.getDirectory() + "/temp");

        dumpOutData(parallelFusionPipeline, file_io.getDirectory()+"/temp/plot_"+method);

        for(auto i=0; i<model->width * model->height; ++i){
            result.setDepthAtInd(i, solution.second(i,0));
        }
        return solution.first;
    }