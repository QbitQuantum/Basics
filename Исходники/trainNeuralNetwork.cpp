int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    bool use_mmap_file, randomize;
    param myParam;
    try {
      // program options //
      CmdLine cmd("Trains a two-layer neural probabilistic language model.", ' ' , "0.3\n","");

      // The options are printed in reverse order

      ValueArg<string> unigram_probs_file("", "unigram_probs_file", "Unigram model (deprecated and ignored)." , false, "", "string", cmd);

      ValueArg<int> num_threads("", "num_threads", "Number of threads. Default: maximum.", false, 0, "int", cmd);

      ValueArg<double> final_momentum("", "final_momentum", "Final value of momentum. Default: 0.9.", false, 0.9, "double", cmd);
      ValueArg<double> initial_momentum("", "initial_momentum", "Initial value of momentum. Default: 0.9.", false, 0.9, "double", cmd);
      ValueArg<bool> use_momentum("", "use_momentum", "Use momentum (hidden layer weights only). 1 = yes, 0 = no. Default: 0.", false, 0, "bool", cmd);

      ValueArg<double> normalization_init("", "normalization_init", "Initial normalization parameter. Default: 0.", false, 0.0, "double", cmd);
      ValueArg<bool> normalization("", "normalization", "Learn individual normalization factors during training. 1 = yes, 0 = no. Default: 0.", false, 0, "bool", cmd);

      ValueArg<bool> mmap_file("", "mmap_file", "Use memory mapped files. This is useful if the entire data cannot fit in memory. prepareNeuralLM can generate memory mapped files", false, 0, "bool", cmd);

      ValueArg<bool> arg_randomize("", "randomize", "Randomize training instances for better training. 1 = yes, 0 = no. Default: 1.", false, true, "bool", cmd);

      ValueArg<int> num_noise_samples("", "num_noise_samples", "Number of noise samples for noise-contrastive estimation. Default: 100.", false, 100, "int", cmd);

      ValueArg<double> L2_reg("", "L2_reg", "L2 regularization strength (hidden layer weights only). Default: 0.", false, 0.0, "double", cmd);

      ValueArg<double> learning_rate("", "learning_rate", "Learning rate for stochastic gradient ascent. Default: 1.", false, 1., "double", cmd);

      ValueArg<double> conditioning_constant("", "conditioning_constant", "Constant to condition the RMS of the expected square of the gradient in ADADELTA. Default: 10E-3.", false, 10E-3, "double", cmd);

      ValueArg<double> decay("", "decay", "Decay for ADADELTA. Default: 0.95", false, 0.95, "double", cmd);
      ValueArg<double> adagrad_epsilon("", "adagrad_epsilon", "Constant to initialize the L2 squared norm of the gradients with.\
          Default: 10E-3", false, 10E-3, "double", cmd);
      ValueArg<int> validation_minibatch_size("", "validation_minibatch_size", "Minibatch size for validation. Default: 64.", false, 64, "int", cmd);
      ValueArg<int> minibatch_size("", "minibatch_size", "Minibatch size (for training). Default: 1000.", false, 1000, "int", cmd);

      ValueArg<int> num_epochs("", "num_epochs", "Number of epochs. Default: 10.", false, 10, "int", cmd);

      ValueArg<double> init_range("", "init_range", "Maximum (of uniform) or standard deviation (of normal) for initialization. Default: 0.01", false, 0.01, "double", cmd);
      ValueArg<bool> init_normal("", "init_normal", "Initialize parameters from a normal distribution. 1 = normal, 0 = uniform. Default: 0.", false, 0, "bool", cmd);

      ValueArg<string> loss_function("", "loss_function", "Loss function (log, nce). Default: nce.", false, "nce", "string", cmd);
      ValueArg<string> activation_function("", "activation_function", "Activation function (identity, rectifier, tanh, hardtanh). Default: rectifier.", false, "rectifier", "string", cmd);
      ValueArg<int> num_hidden("", "num_hidden", "Number of hidden nodes. Default: 100.", false, 100, "int", cmd);

      ValueArg<bool> share_embeddings("", "share_embeddings", "Share input and output embeddings. 1 = yes, 0 = no. Default: 0.", false, 0, "bool", cmd);
      ValueArg<int> output_embedding_dimension("", "output_embedding_dimension", "Number of output embedding dimensions. Default: 50.", false, 50, "int", cmd);
      ValueArg<int> input_embedding_dimension("", "input_embedding_dimension", "Number of input embedding dimensions. Default: 50.", false, 50, "int", cmd);
      ValueArg<int> embedding_dimension("", "embedding_dimension", "Number of input and output embedding dimensions. Default: none.", false, -1, "int", cmd);

      ValueArg<int> vocab_size("", "vocab_size", "Vocabulary size. Default: auto.", false, 0, "int", cmd);
      ValueArg<int> input_vocab_size("", "input_vocab_size", "Vocabulary size. Default: auto.", false, 0, "int", cmd);
      ValueArg<int> output_vocab_size("", "output_vocab_size", "Vocabulary size. Default: auto.", false, 0, "int", cmd);
      ValueArg<int> ngram_size("", "ngram_size", "Size of n-grams. Default: auto.", false, 0, "int", cmd);

      ValueArg<string> model_prefix("", "model_prefix", "Prefix for output model files." , false, "", "string", cmd);
      ValueArg<string> words_file("", "words_file", "Vocabulary." , false, "", "string", cmd);
      ValueArg<string> parameter_update("", "parameter_update", "parameter update type.\n Stochastic Gradient Descent(SGD)\n \
          ADAGRAD(ADA)\n \
          ADADELTA(ADAD)" , false, "SGD", "string", cmd);
      ValueArg<string> input_words_file("", "input_words_file", "Vocabulary." , false, "", "string", cmd);
      ValueArg<string> output_words_file("", "output_words_file", "Vocabulary." , false, "", "string", cmd);
      ValueArg<string> validation_file("", "validation_file", "Validation data (one numberized example per line)." , false, "", "string", cmd);
      ValueArg<string> train_file("", "train_file", "Training data (one numberized example per line)." , true, "", "string", cmd);

      ValueArg<string> model_file("", "model_file", "Model file.", false, "", "string", cmd);


      cmd.parse(argc, argv);

      // define program parameters //
      use_mmap_file = mmap_file.getValue();
      randomize = arg_randomize.getValue();
      myParam.model_file = model_file.getValue();
      myParam.train_file = train_file.getValue();
      myParam.validation_file = validation_file.getValue();
      myParam.input_words_file = input_words_file.getValue();
      myParam.output_words_file = output_words_file.getValue();
      if (words_file.getValue() != "")
        myParam.input_words_file = myParam.output_words_file = words_file.getValue();

      myParam.model_prefix = model_prefix.getValue();

      myParam.ngram_size = ngram_size.getValue();
      myParam.vocab_size = vocab_size.getValue();
      myParam.input_vocab_size = input_vocab_size.getValue();
      myParam.output_vocab_size = output_vocab_size.getValue();
      if (vocab_size.getValue() > 0) {
        myParam.input_vocab_size = myParam.output_vocab_size = vocab_size.getValue();
      }
      myParam.num_hidden = num_hidden.getValue();
      myParam.activation_function = activation_function.getValue();
      myParam.loss_function = loss_function.getValue();

      myParam.num_threads = num_threads.getValue();

      myParam.num_noise_samples = num_noise_samples.getValue();

      myParam.input_embedding_dimension = input_embedding_dimension.getValue();
      myParam.output_embedding_dimension = output_embedding_dimension.getValue();
      if (embedding_dimension.getValue() >= 0) {
        myParam.input_embedding_dimension = myParam.output_embedding_dimension = embedding_dimension.getValue();
      }

      myParam.minibatch_size = minibatch_size.getValue();
      myParam.validation_minibatch_size = validation_minibatch_size.getValue();
      myParam.num_epochs= num_epochs.getValue();
      myParam.learning_rate = learning_rate.getValue();
      myParam.conditioning_constant = conditioning_constant.getValue();
      myParam.decay = decay.getValue();
      myParam.adagrad_epsilon = adagrad_epsilon.getValue();
      myParam.use_momentum = use_momentum.getValue();
      myParam.share_embeddings = share_embeddings.getValue();
      myParam.normalization = normalization.getValue();
      myParam.initial_momentum = initial_momentum.getValue();
      myParam.final_momentum = final_momentum.getValue();
      myParam.L2_reg = L2_reg.getValue();
      myParam.init_normal= init_normal.getValue();
      myParam.init_range = init_range.getValue();
      myParam.normalization_init = normalization_init.getValue();
      myParam.parameter_update = parameter_update.getValue();

      cerr << "Command line: \n";
      cerr << boost::algorithm::join(vector<string>(argv, argv+argc), " ") << '\n';

      const string sep(" Value: ");
      cerr << train_file.getDescription() << sep << train_file.getValue() << '\n';
      cerr << validation_file.getDescription() << sep << validation_file.getValue() << '\n';
      cerr << input_words_file.getDescription() << sep << input_words_file.getValue() << '\n';
      cerr << output_words_file.getDescription() << sep << output_words_file.getValue() << '\n';
      cerr << model_prefix.getDescription() << sep << model_prefix.getValue() << '\n';

      cerr << ngram_size.getDescription() << sep << ngram_size.getValue() << '\n';
      cerr << input_vocab_size.getDescription() << sep << input_vocab_size.getValue() << '\n';
      cerr << output_vocab_size.getDescription() << sep << output_vocab_size.getValue() << '\n';
      cerr << mmap_file.getDescription() << sep << mmap_file.getValue() << '\n';

      if (embedding_dimension.getValue() >= 0)
      {
        cerr << embedding_dimension.getDescription() << sep << embedding_dimension.getValue() << '\n';
      }
      else
      {
        cerr << input_embedding_dimension.getDescription() << sep << input_embedding_dimension.getValue() << '\n';
        cerr << output_embedding_dimension.getDescription() << sep << output_embedding_dimension.getValue() << '\n';
      }
      cerr << share_embeddings.getDescription() << sep << share_embeddings.getValue() << '\n';
      if (share_embeddings.getValue() && input_embedding_dimension.getValue() != output_embedding_dimension.getValue())
      {
        cerr << "error: sharing input and output embeddings requires that input and output embeddings have same dimension\n";
        exit(1);
      }

      cerr << num_hidden.getDescription() << sep << num_hidden.getValue() << '\n';

      if (string_to_activation_function(activation_function.getValue()) == InvalidFunction)
      {
        cerr << "error: invalid activation function: " << activation_function.getValue() << '\n';
        exit(1);
      }
      cerr << activation_function.getDescription() << sep << activation_function.getValue() << '\n';

      if (string_to_loss_function(loss_function.getValue()) == InvalidLoss)
      {
        cerr << "error: invalid loss function: " << loss_function.getValue() << '\n';
        exit(1);
      }
      cerr << loss_function.getDescription() << sep << loss_function.getValue() << '\n';

      cerr << init_normal.getDescription() << sep << init_normal.getValue() << '\n';
      cerr << init_range.getDescription() << sep << init_range.getValue() << '\n';

      cerr << num_epochs.getDescription() << sep << num_epochs.getValue() << '\n';
      cerr << minibatch_size.getDescription() << sep << minibatch_size.getValue() << '\n';
      if (myParam.validation_file != "") {
       cerr << validation_minibatch_size.getDescription() << sep << validation_minibatch_size.getValue() << '\n';
      }
      cerr << learning_rate.getDescription() << sep << learning_rate.getValue() << '\n';
      cerr << L2_reg.getDescription() << sep << L2_reg.getValue() << '\n';

      cerr << num_noise_samples.getDescription() << sep << num_noise_samples.getValue() << '\n';

      cerr << normalization.getDescription() << sep << normalization.getValue() << '\n';
      if (myParam.normalization){
        cerr << normalization_init.getDescription() << sep << normalization_init.getValue() << '\n';
      }

      cerr << use_momentum.getDescription() << sep << use_momentum.getValue() << '\n';
      if (myParam.use_momentum)
      {
        cerr << initial_momentum.getDescription() << sep << initial_momentum.getValue() << '\n';
        cerr << final_momentum.getDescription() << sep << final_momentum.getValue() << '\n';
      }

      cerr << num_threads.getDescription() << sep << num_threads.getValue() << '\n';

      if (unigram_probs_file.getValue() != "")
      {
        cerr << "Note: --unigram_probs_file is deprecated and ignored.\n";
      }
    }
    catch (TCLAP::ArgException &e)
    {
      cerr << "error: " << e.error() <<  " for arg " << e.argId() << '\n';
      exit(1);
    }

    myParam.num_threads = setup_threads(myParam.num_threads);
    int save_threads;

    //unsigned seed = std::time(0);
    unsigned seed = 1234; //for testing only
    boost::random::mt19937 rng(seed);

    /////////////////////////READING IN THE TRAINING AND VALIDATION DATA///////////////////
    /////////////////////////////////////////////////////////////////////////////////////

    // Read training data

    vector<int> training_data_flat;
    vec * training_data_flat_mmap;
    data_size_t training_data_size; //num_tokens;
    ip::managed_mapped_file mmap_file;
    if (use_mmap_file == false) {
      cerr<<"Reading data from regular text file \n";
      readDataFile(myParam.train_file, myParam.ngram_size, training_data_flat, myParam.minibatch_size);
      training_data_size = training_data_flat.size()/myParam.ngram_size;
    } else {
      cerr<<"Using mmaped file\n";
      mmap_file = ip::managed_mapped_file(ip::open_only,myParam.train_file.c_str());
      training_data_flat_mmap = mmap_file.find<vec>("vector").first;
      cerr<<"Size of mmaped vector is "<<training_data_flat_mmap->size()<<'\n';
      training_data_size = training_data_flat_mmap->size()/myParam.ngram_size;
      //randomly shuffle the data for better learning. The shuffling will
      //be different for a standard stl vector
      // Randomly shuffle training data to improve learning
      if (randomize == true) {
        cerr<<"Randomly shuffling data...";
        data_size_t counter =0;
        while (counter < training_data_size) {
          data_size_t upper_limit = counter+5000000;
          long int vector_size = 5000000;
          if (counter + 10000000 >= training_data_size) {
            upper_limit = training_data_size;
            vector_size = training_data_size - counter;
          }
          vector<int> temp(vector_size*myParam.ngram_size,0);
          for (int i=0;i<vector_size;i++){
           for (int k=0;k<myParam.ngram_size;k++) {
             temp[i*myParam.ngram_size+k] = training_data_flat_mmap->at((i+counter)*myParam.ngram_size+k);
           }
          }
          /*
          for (data_size_t i=upper_limit; i>counter; i--)
          {
            if (i %500000 == 0) {
              cerr<<"Shuffled "<<training_data_size-1<<" instances...";
            }
            data_size_t j = boost::random::uniform_int_distribution<data_size_t>(0, i-1)(rng);
            for (int k=0;k<myParam.ngram_size;k++) {
              int temp_val = training_data_flat_mmap->at(i*myParam.ngram_size+k);
              training_data_flat_mmap->at(i*myParam.ngram_size+k) =
                training_data_flat_mmap->at(j*myParam.ngram_size+k);
              training_data_flat_mmap->at(j*myParam.ngram_size+k) = temp_val;
            }
          }
          */
          for (data_size_t i=vector_size-1; i>0; i--)
          {
            if (i %500000 == 0) {
              cerr<<".";
            }
            data_size_t j = boost::random::uniform_int_distribution<data_size_t>(0, i-1)(rng);
            for (int k=0;k<myParam.ngram_size;k++) {
              int temp_val = temp.at(i*myParam.ngram_size+k);
              temp.at(i*myParam.ngram_size+k) =
                temp.at(j*myParam.ngram_size+k);
              temp.at(j*myParam.ngram_size+k) = temp_val;
            }
          }
          //Putting it back
          for (int i=0;i<vector_size;i++){
           for (int k=0;k<myParam.ngram_size;k++) {
             training_data_flat_mmap->at((i+counter)*myParam.ngram_size+k) = temp[i*myParam.ngram_size+k];
           }
          }
          counter = upper_limit;
        }
        /*
        for (data_size_t i=training_data_size-1; i>0; i--)
        {
          if (i %500000 == 0) {
            cerr<<"Shuffled "<<training_data_size-1<<" instances...";
          }
          data_size_t j = boost::random::uniform_int_distribution<data_size_t>(0, i-1)(rng);
          for (int k=0;k<myParam.ngram_size;k++) {
            int temp_val = training_data_flat_mmap->at(i*myParam.ngram_size+k);
            training_data_flat_mmap->at(i*myParam.ngram_size+k) =
              training_data_flat_mmap->at(j*myParam.ngram_size+k);
            training_data_flat_mmap->at(j*myParam.ngram_size+k) = temp_val;
          }
        }
        */
      cerr<<'\n';
      }
    }
    //cerr<<"Num tokens "<<num_tokens<<'\n';
    //data_size_t training_data_size = num_tokens / myParam.ngram_size;
    cerr << "Number of training instances: "<< training_data_size << '\n';

    Matrix<int,Dynamic,Dynamic> training_data;
    //(training_data_flat.data(), myParam.ngram_size, training_data_size);

    #ifdef MAP
    cerr<<"Setting up eigen map\n";
    if (use_mmap_file == false) {
      training_data = Map< Matrix<int,Dynamic,Dynamic> >(training_data_flat.data(), myParam.ngram_size, training_data_size);
    } else {
      training_data = Map< Matrix<int,Dynamic,Dynamic> >(training_data_flat_mmap->data().get(), myParam.ngram_size, training_data_size);
    }
    cerr<<"Created eigen map\n";
    #else
    if (use_mmap_file == false) {
      training_data = Map< Matrix<int,Dynamic,Dynamic> >(training_data_flat.data(), myParam.ngram_size, training_data_size);
    }
    #endif
    // If neither --input_vocab_size nor --input_words_file is given, set input_vocab_size to the maximum word index
    if (myParam.input_vocab_size == 0 and myParam.input_words_file == "")
    {
        myParam.input_vocab_size = training_data.topRows(myParam.ngram_size-1).maxCoeff()+1;
    }

    // If neither --output_vocab_size nor --output_words_file is given, set output_vocab_size to the maximum word index
    if (myParam.output_vocab_size == 0 and myParam.output_words_file == "")
    {
        myParam.output_vocab_size = training_data.row(myParam.ngram_size-1).maxCoeff()+1;
    }
    if (use_mmap_file == false && randomize == true) {
      cerr<<"Randomly shuffling data...\n";
      // Randomly shuffle training data to improve learning
      for (data_size_t i=training_data_size-1; i>0; i--)
      {
        data_size_t j = boost::random::uniform_int_distribution<data_size_t>(0, i-1)(rng);
        training_data.col(i).swap(training_data.col(j));
      }
    }

    // Read validation data
    vector<int> validation_data_flat;
    int validation_data_size = 0;

    if (myParam.validation_file != "")
    {
      readDataFile(myParam.validation_file, myParam.ngram_size, validation_data_flat);
      validation_data_size = validation_data_flat.size() / myParam.ngram_size;
      cerr << "Number of validation instances: " << validation_data_size << '\n';
    }

    Map< Matrix<int,Dynamic,Dynamic> > validation_data(validation_data_flat.data(), myParam.ngram_size, validation_data_size);

    ///// Read in vocabulary file. We don't actually use it; it just gets reproduced in the output file

    vector<string> input_words;
    if (myParam.input_words_file != "")
    {
        readWordsFile(myParam.input_words_file, input_words);
  if (myParam.input_vocab_size == 0)
      myParam.input_vocab_size = input_words.size();
    }

    vector<string> output_words;
    if (myParam.output_words_file != "")
    {
        readWordsFile(myParam.output_words_file, output_words);
  if (myParam.output_vocab_size == 0)
      myParam.output_vocab_size = output_words.size();
    }

    ///// Construct unigram model and sampler that will be used for NCE

    vector<data_size_t> unigram_counts(myParam.output_vocab_size);
    for (data_size_t train_id=0; train_id < training_data_size; train_id++)
    {
        int output_word;
        if (use_mmap_file == false) {
          output_word = training_data(myParam.ngram_size-1, train_id);
        } else {
        //cerr<<"mmap word is "<<training_data_flat_mmap->at((train_id+1)*myParam.ngram_size - 1)<<'\n';
          output_word = training_data_flat_mmap->at((train_id+1)*myParam.ngram_size - 1);
        }
    //cerr<<"output word is "<<output_word<<'\n';
      unigram_counts[output_word] += 1;
    }
    multinomial<data_size_t> unigram (unigram_counts);

    ///// Create and initialize the neural network and associated propagators.
    model nn;
    // IF THE MODEL FILE HAS BEEN DEFINED, THEN
    // LOAD THE NEURAL NETWORK MODEL
    if (myParam.model_file != ""){
      nn.read(myParam.model_file);
      cerr<<"reading the model\n";
    } else {
      nn.resize(myParam.ngram_size,
          myParam.input_vocab_size,
          myParam.output_vocab_size,
          myParam.input_embedding_dimension,
          myParam.num_hidden,
          myParam.output_embedding_dimension);

      nn.initialize(rng,
          myParam.init_normal,
          myParam.init_range,
          -log(myParam.output_vocab_size),
          myParam.parameter_update,
          myParam.adagrad_epsilon);
      nn.set_activation_function(string_to_activation_function(myParam.activation_function));
    }
    loss_function_type loss_function = string_to_loss_function(myParam.loss_function);

    propagator prop(nn, myParam.minibatch_size);
    propagator prop_validation(nn, myParam.validation_minibatch_size);
    SoftmaxNCELoss<multinomial<data_size_t> > softmax_loss(unigram);
    // normalization parameters
    vector_map c_h, c_h_running_gradient;

    ///////////////////////TRAINING THE NEURAL NETWORK////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

    data_size_t num_batches = (training_data_size-1)/myParam.minibatch_size + 1;
    cerr<<"Number of training minibatches: "<<num_batches<<'\n';

    int num_validation_batches = 0;
    if (validation_data_size > 0)
    {
        num_validation_batches = (validation_data_size-1)/myParam.validation_minibatch_size+1;
  cerr<<"Number of validation minibatches: "<<num_validation_batches<<'\n';
    }

    double current_momentum = myParam.initial_momentum;
    double momentum_delta = (myParam.final_momentum - myParam.initial_momentum)/(myParam.num_epochs-1);
    double current_learning_rate = myParam.learning_rate;
    double current_validation_ll = 0.0;

    int ngram_size = myParam.ngram_size;
    int input_vocab_size = myParam.input_vocab_size;
    int output_vocab_size = myParam.output_vocab_size;
    int minibatch_size = myParam.minibatch_size;
    int validation_minibatch_size = myParam.validation_minibatch_size;
    int num_noise_samples = myParam.num_noise_samples;

    if (myParam.normalization)
    {
      for (data_size_t i=0;i<training_data_size;i++)
      {
          Matrix<int,Dynamic,1> context = training_data.block(0,i,ngram_size-1,1);
          if (c_h.find(context) == c_h.end())
          {
              c_h[context] = -myParam.normalization_init;
          }
      }
    }

    for (int epoch=0; epoch<myParam.num_epochs; epoch++)
    {
        cerr << "Epoch " << epoch+1 << '\n';
        cerr << "Current learning rate: " << current_learning_rate << '\n';

        if (myParam.use_momentum)
      cerr << "Current momentum: " << current_momentum << '\n';
  else
            current_momentum = -1;

  cerr << "Training minibatches: ";

  double log_likelihood = 0.0;

  int num_samples = 0;
  if (loss_function == LogLoss)
      num_samples = output_vocab_size;
  else if (loss_function == NCELoss)
      num_samples = 1+num_noise_samples;

  Matrix<double,Dynamic,Dynamic> minibatch_weights(num_samples, minibatch_size);
  Matrix<int,Dynamic,Dynamic> minibatch_samples(num_samples, minibatch_size);
  Matrix<double,Dynamic,Dynamic> scores(num_samples, minibatch_size);
  Matrix<double,Dynamic,Dynamic> probs(num_samples, minibatch_size);

        for(data_size_t batch=0;batch<num_batches;batch++)
        {
            if (batch > 0 && batch % 10000 == 0)
            {
          cerr << batch <<"...";
            }

            if (batch > 0 && batch % 500000 == 0)
            {
                cerr << '\n';
                compute_validation_perplexity(ngram_size, output_vocab_size, validation_minibatch_size, validation_data_size, num_validation_batches, myParam, prop_validation, validation_data, current_learning_rate, current_validation_ll);
                cerr << "Current learning rate: " << current_learning_rate << '\n';
            }

            data_size_t minibatch_start_index = minibatch_size * batch;

      int current_minibatch_size = min(static_cast<data_size_t>(minibatch_size), training_data_size - minibatch_start_index);
      #ifdef MAP
      Matrix<int,Dynamic,Dynamic> minibatch = training_data.middleCols(minibatch_start_index, current_minibatch_size);
      #else
      //ALTERNATIVE OPTION IF YOU'RE NOT USING eigen map interface on the mmapped file
      Matrix<int,Dynamic,Dynamic> minibatch;// = training_data.middleCols(minibatch_start_index, current_minibatch_size);
    //cerr<<"Minibatch start index "<<minibatch_start_index<<'\n';
    //cerr<<"Minibatch size "<<current_minibatch_size<<'\n';
            if (use_mmap_file == true) {
            minibatch.setZero(ngram_size,current_minibatch_size);
            //now reading the ngrams from the mmaped file
              for (int k=0; k<ngram_size; k++){
                for (data_size_t index = 0 ; index<current_minibatch_size; index++) {
          data_size_t current_index = index + minibatch_start_index;
          //cerr<<"the value in the mmap file "<<index<<" "<<k<<" is "<<training_data_flat_mmap->at(current_index*ngram_size+k)<<'\n';
                  minibatch(k,index) = training_data_flat_mmap->at(current_index*ngram_size+k);
                }
              }
            } else {
              minibatch = training_data.middleCols(minibatch_start_index, current_minibatch_size);
            }
      #endif
            double adjusted_learning_rate = current_learning_rate/minibatch_size;
            //cerr<<"Adjusted learning rate: "<<adjusted_learning_rate<<'\n';

            /*
            if (batch == rand() % num_batches)
            {
                cerr<<"we are checking the gradient in batch "<<batch<<'\n';
                /////////////////////////CHECKING GRADIENTS////////////////////////////////////////
                gradientChecking(myParam,minibatch_start_index,current_minibatch_size,word_nodes,context_nodes,hidden_layer_node,hidden_layer_to_output_node,
                              shuffled_training_data,c_h,unif_real_vector,eng_real_vector,unif_int_vector,eng_int_vector,unigram_probs_vector,
                              q_vector,J_vector,D_prime);
            }
            */

            ///// Forward propagation

            prop.fProp(minibatch.topRows(ngram_size-1));

      if (loss_function == NCELoss)
      {
        ///// Noise-contrastive estimation

        // Generate noise samples. Gather positive and negative samples into matrix.

        start_timer(3);

        minibatch_samples.block(0, 0, 1, current_minibatch_size) = minibatch.bottomRows(1);

        for (int sample_id = 1; sample_id < num_noise_samples+1; sample_id++)
            for (int train_id = 0; train_id < current_minibatch_size; train_id++)
                minibatch_samples(sample_id, train_id) = unigram.sample(rng);

        stop_timer(3);

        // Final forward propagation step (sparse)
        start_timer(4);
        if (prop.skip_hidden)
            prop.output_layer_node.param->fProp(prop.first_hidden_activation_node.fProp_matrix,
                    minibatch_samples, scores);
        else
            prop.output_layer_node.param->fProp(prop.second_hidden_activation_node.fProp_matrix,
                    minibatch_samples, scores);
        stop_timer(4);

        // Apply normalization parameters
        if (myParam.normalization)
        {
            for (int train_id = 0;train_id < current_minibatch_size;train_id++)
            {
          Matrix<int,Dynamic,1> context = minibatch.block(0, train_id, ngram_size-1, 1);
          scores.col(train_id).array() += c_h[context];
            }
        }

        double minibatch_log_likelihood;
        start_timer(5);
        softmax_loss.fProp(scores.leftCols(current_minibatch_size),
               minibatch_samples,
               probs, minibatch_log_likelihood);
        stop_timer(5);
        log_likelihood += minibatch_log_likelihood;

        ///// Backward propagation

        start_timer(6);
        softmax_loss.bProp(probs, minibatch_weights);
        stop_timer(6);

        // Update the normalization parameters

        if (myParam.normalization)
        {
          for (int train_id = 0;train_id < current_minibatch_size;train_id++)
          {
            Matrix<int,Dynamic,1> context = minibatch.block(0, train_id, ngram_size-1, 1);
            c_h[context] += adjusted_learning_rate * minibatch_weights.col(train_id).sum();
          }
        }

        // Be careful of short minibatch
        prop.bProp(minibatch.topRows(ngram_size-1),
             minibatch_samples.leftCols(current_minibatch_size),
             minibatch_weights.leftCols(current_minibatch_size),
             adjusted_learning_rate,
             current_momentum,
             myParam.L2_reg,
             myParam.parameter_update,
             myParam.conditioning_constant,
             myParam.decay);
      }
      else if (loss_function == LogLoss)
      {
        ///// Standard log-likelihood
        start_timer(4);
        if (prop.skip_hidden)
            prop.output_layer_node.param->fProp(prop.first_hidden_activation_node.fProp_matrix, scores);
        else
            prop.output_layer_node.param->fProp(prop.second_hidden_activation_node.fProp_matrix, scores);
        stop_timer(4);

        double minibatch_log_likelihood;
        start_timer(5);
        SoftmaxLogLoss().fProp(scores.leftCols(current_minibatch_size),
                   minibatch.row(ngram_size-1),
                   probs,
                   minibatch_log_likelihood);
        stop_timer(5);
        log_likelihood += minibatch_log_likelihood;

        ///// Backward propagation

        start_timer(6);
        SoftmaxLogLoss().bProp(minibatch.row(ngram_size-1).leftCols(current_minibatch_size),
                   probs.leftCols(current_minibatch_size),
                   minibatch_weights);
        stop_timer(6);

        prop.bProp(minibatch.topRows(ngram_size-1).leftCols(current_minibatch_size),
             minibatch_weights,
             adjusted_learning_rate,
             current_momentum,
             myParam.L2_reg,
             myParam.parameter_update,
             myParam.conditioning_constant,
             myParam.decay);
          }
      }
  cerr << "done.\n";

  if (loss_function == LogLoss)
  {
      cerr << "Training log-likelihood: " << log_likelihood << '\n';
            cerr << "         perplexity:     "<< exp(-log_likelihood/training_data_size) << '\n';
  }
  else if (loss_function == NCELoss)
      cerr << "Training NCE log-likelihood: " << log_likelihood << '\n';

        current_momentum += momentum_delta;

  #ifdef USE_CHRONO
  cerr << "Propagation times:";
  for (int i=0; i<timer.size(); i++)
    cerr << " " << timer.get(i);
  cerr << '\n';
  #endif

  if (myParam.model_prefix != "")
  {
      cerr << "Writing model\n";
      if (myParam.input_words_file != "")
          nn.write(myParam.model_prefix + "." + lexical_cast<string>(epoch+1), input_words, output_words);
      else
          nn.write(myParam.model_prefix + "." + lexical_cast<string>(epoch+1));
  }

        if (epoch % 1 == 0 && validation_data_size > 0)
        {
            compute_validation_perplexity(ngram_size, output_vocab_size, validation_minibatch_size, validation_data_size, num_validation_batches, myParam, prop_validation, validation_data, current_learning_rate, current_validation_ll);
        }

    }
    return 0;
}