        std::pair<MPI_Request, const K*>* buildTwo(Prcndtnr* B, const MPI_Comm& comm) {
            static_assert(std::is_same<typename Prcndtnr::super&, decltype(*this)>::value || std::is_same<typename Prcndtnr::super::super&, decltype(*this)>::value, "Wrong preconditioner");
            std::pair<MPI_Request, const K*>* ret = nullptr;
            constexpr unsigned short N = std::is_same<typename Prcndtnr::super&, decltype(*this)>::value ? 2 : 3;
            unsigned short allUniform[N + 1];
            allUniform[0] = Subdomain<K>::_map.size();
            const Option& opt = *Option::get();
            unsigned short nu = allUniform[1] = (_co ? _co->getLocal() : static_cast<unsigned short>(opt["geneo_nu"]));
            allUniform[2] = static_cast<unsigned short>(~nu);
            if(N == 3)
                allUniform[3] = nu > 0 ? nu : std::numeric_limits<unsigned short>::max();
            {
                MPI_Op op;
#ifdef __MINGW32__
                MPI_Op_create(&f<N>, 1, &op);
#else
                auto f = [](void* in, void* inout, int*, MPI_Datatype*) -> void {
                    HPDDM_LAMBDA_F(in, input, inout, output, N)
                };
                MPI_Op_create(f, 1, &op);
#endif
                MPI_Allreduce(MPI_IN_PLACE, allUniform, N + 1, MPI_UNSIGNED_SHORT, op, comm);
                MPI_Op_free(&op);
            }
            if(nu > 0 || allUniform[1] != 0 || allUniform[2] != std::numeric_limits<unsigned short>::max()) {
                if(!_co) {
                    _co = new CoarseOperator;
                    _co->setLocal(nu);
                }
                double construction = MPI_Wtime();
                if(allUniform[1] == nu && allUniform[2] == static_cast<unsigned short>(~nu))
                    ret = _co->template construction<1, excluded>(Operator(*B, allUniform[0]), comm);
                else if(N == 3 && allUniform[1] == 0 && allUniform[2] == static_cast<unsigned short>(~allUniform[3]))
                    ret = _co->template construction<2, excluded>(Operator(*B, allUniform[0]), comm);
                else
                    ret = _co->template construction<0, excluded>(Operator(*B, allUniform[0]), comm);
                construction = MPI_Wtime() - construction;
                if(_co->getRank() == 0 && opt.val<int>("verbosity") > 0) {
                    std::stringstream ss;
                    ss << std::setprecision(2) << construction;
                    std::string line = " --- coarse operator transferred and factorized by " + to_string(static_cast<int>(opt["master_p"])) + " process" + (static_cast<int>(opt["master_p"]) == 1 ? "" : "es") + " (in " + ss.str() + "s)";
                    std::cout << line << std::endl;
                    std::cout << std::right << std::setw(line.size()) << "(criterion = " + to_string(allUniform[1] == nu && allUniform[2] == static_cast<unsigned short>(~nu) ? nu : (N == 3 && allUniform[2] == static_cast<unsigned short>(~allUniform[3]) ? -_co->getLocal() : 0)) + " -- topology = " + to_string(static_cast<int>(opt["master_topology"])) + " -- distribution = " + to_string(static_cast<int>(opt["master_distribution"])) + ")" << std::endl;
                    std::cout.unsetf(std::ios_base::adjustfield);
                }
            }
            else {
                delete _co;
                _co = nullptr;
            }
            return ret;
        }