int main(int argc, char *argv[])
{
    int  num_epochs  = argc>1 ? atoi(argv[1]) : 0;
    bool do_shuffle  = argc>2 ? *argv[2] == 'y' : false;
    FILE *train_file = openfile( argc>3 ? argv[3] : (char*)"perceptron_train.csv");
    FILE *test_file  = openfile( argc>4 ? argv[4] : (char*)"perceptron_test.csv");

    XDATA xtrain, xtest;
    YDATA ytrain, ytest;
    read_data(train_file, xtrain, ytrain);

    if (num_epochs == 0)
        num_epochs = xtrain.size();
	//read in training data and figure out w based on those
    std::vector<float> w = p_train(xtrain, ytrain, num_epochs, do_shuffle);
    fprintf(stdout, "weight vector = %f %f %f %f\n", w[0],w[1],w[2],w[3]);

    int failcount = 0;
	//read in test data
    read_data(test_file,  xtest,  ytest);
    for (int i=0; i<xtest.size(); i++){
		//call classify on test_file and until it fails just keep going
        int y = p_classify(xtest[i], w);
		//if we fail, it means we need to re classify
        if (y != ytest[i]) { 
			//update the weights since we failed
            update_weights(xtest[i], ytest[i], w);
			//change it so that we learned
            y = p_classify(xtest[i], w);
            if (y != ytest[i]) {
				//update failure count so we know that we got better
                failcount++;
            }
        }
    }

    fprintf(stdout, "Failures = %d\nEpochs = %d\n\n", failcount, num_epochs);
    fprintf(stdout, "Failures in training: %d\n", test_fails);
    return 0;
}