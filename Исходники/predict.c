void do_predict(FILE *input, FILE *output, struct model* model_)
{
	int correct = 0;
	int total = 0;

	int nr_class=get_nr_class(model_);
	double *prob_estimates=NULL;
	int j, n;
	int nr_feature=get_nr_feature(model_);
	if(model_->bias>=0)
		n=nr_feature+1;
	else
		n=nr_feature;

	if(flag_predict_probability)
	{
		int *labels;

		if(model_->param.solver_type!=L2_LR)
		{
			fprintf(stderr, "probability output is only supported for logistic regression\n");
			return;
		}

		labels=(int *) malloc(nr_class*sizeof(int));
		get_labels(model_,labels);
		prob_estimates = (double *) malloc(nr_class*sizeof(double));
		fprintf(output,"labels");		
		for(j=0;j<nr_class;j++)
			fprintf(output," %d",labels[j]);
		fprintf(output,"\n");
		free(labels);
	}
	while(1)
	{
		int i = 0;
		int c;
		double target;
		int target_label, predict_label;

		if (fscanf(input,"%lf",&target)==EOF)
			break;
		target_label=(int)target;

		while(1)
		{
			if(i>=max_nr_attr-2)	// need one more for index = -1
			{
				max_nr_attr *= 2;
				x = (struct feature_node *) realloc(x,max_nr_attr*sizeof(struct feature_node));
			}

			do {
				c = getc(input);
				if(c=='\n' || c==EOF) goto out2;
			} while(isspace(c));
			ungetc(c,input);
			if (fscanf(input,"%d:%lf",&x[i].index,&x[i].value) < 2)
			{
				fprintf(stderr,"Wrong input format at line %d\n", total+1);
				exit(1);
			}
			// feature indices larger than those in training are not used
			if(x[i].index<=nr_feature)
				++i;
		}

out2:
		if(model_->bias>=0)
		{
			x[i].index = n;
			x[i].value = model_->bias;
			i++;
		}
		x[i].index = -1;

		if(flag_predict_probability)
		{
			int j;
			predict_label = predict_probability(model_,x,prob_estimates);
			fprintf(output,"%d ",predict_label);
			for(j=0;j<model_->nr_class;j++)
				fprintf(output,"%g ",prob_estimates[j]);
			fprintf(output,"\n");
		}
		else
		{
			predict_label = predict(model_,x);
			fprintf(output,"%d\n",predict_label);
		}

		if(predict_label == target_label)
			++correct;
		++total;
	}
	printf("Accuracy = %g%% (%d/%d)\n", (double)correct/total*100,correct,total);
	if(flag_predict_probability)
		free(prob_estimates);
}