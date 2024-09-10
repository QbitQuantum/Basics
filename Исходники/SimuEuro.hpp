    SimuEuro(const option &o, long path, unsigned int seed=  int(time(0))) {
        opt=o;
        N= path;
        asset_price.resize(N);
        asset_price.setZero();
        option_value= asset_price;
        
        boost::mt19937 eng(seed);
        boost::normal_distribution<double> normal(0.0, 1.0);
        boost::variate_generator<boost::mt19937&, boost::normal_distribution<double>> rng(eng, normal);
        
        for (long i=0; i< N; i++) {
            asset_price(i)=opt.S* exp((opt.r- opt.q)*opt.T-.5*opt.sigma*opt.sigma*opt.T+ opt.sigma* sqrt(opt.T)* rng());
            
            if(opt.Call) option_value(i)= fmax(asset_price(i)- opt.K,0.0);
            else option_value(i)= fmax(-asset_price(i)+opt.K, 0.0);
        }
        
        mean= option_value.sum()/ option_value.size() * exp(-opt.T*opt.r);
        stdiv= option_value.squaredNorm()/ option_value.size()* exp(-opt.r*opt.T *2);
        stdiv= stdiv- pow(mean,2.0);
        stdiv= sqrt(stdiv/ N);

    };