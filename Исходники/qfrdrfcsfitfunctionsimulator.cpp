void QFRDRFCSFitFunctionSimulator::replotFitFunction() {
    JKQTPdatastore* ds=ui->pltFunction->getDatastore();
    QScopedPointer<QFFitFunction> ffunc(getFitFunction(NULL));

    if (!ffunc) return;

    try {
        ui->pltFunction->set_doDrawing(false);
        ui->pltFunction->clearGraphs();
        ds->clear();
        updateTau();
        if (tauN) {


            /////////////////////////////////////////////////////////////////////////////////
            // retrieve fit parameters and errors. run calcParameters to fill in calculated parameters and make sure
            // we are working with a complete set of parameters
            /////////////////////////////////////////////////////////////////////////////////

            double* fullParams=(double*)qfCalloc(ffunc->paramCount(), sizeof(double));
            double* errors=(double*)qfCalloc(ffunc->paramCount(), sizeof(double));
            double Nparticle=0;
            bool hasNParticle=false;
            for (int p=0; p<ffunc->paramCount(); p++) {
                QFFitFunction::ParameterDescription d=ffunc->getDescription(p);
                QString id=d.id;
                if (params.contains(id)) {
                    fullParams[p]=params[id].value;
                    errors[p]=params[id].error;
                } else {
                    fullParams[p]=d.initialValue;
                    /*double value=0;
                    if (overrideFitFunctionPreset(id, value)) d.initialValue=value;*/

                    errors[p]=0;
                }
            }
            ffunc->calcParameter(fullParams, errors);
            used_params.clear();
            for (int p=0; p<ffunc->paramCount(); p++) {
                QFFitFunction::ParameterDescription d=ffunc->getDescription(p);
                QString id=d.id.toLower();
                bool visible=ffunc->isParameterVisible(ffunc->getParameterNum(id), fullParams);
                if (visible) {
                    if (id=="n_particle") {
                        Nparticle=fullParams[p];
                        hasNParticle=true;
                    }
                    if (id=="1n_particle" && !hasNParticle) {
                        Nparticle=1.0/fullParams[p];
                        hasNParticle=true;
                    }
                    used_params[id]=fullParams[p];
                }
            }

            used_params["tau_min"]=ui->edtMinTau->value();
            used_params["tau_max"]=ui->edtMaxTau->value();
            used_params["runs"]=ui->spinRuns->value();
            used_params["noise_enabled"]=ui->chkNoise->isChecked();
            used_params["model_function"]=ffunc->id();

            csv="";

            // evaluate correlation function and determine small-lag amplitude
            double tau0avg=0;
            for (int r=0; r<runs; r++) {
                for (int i=0; i<tauN; i++) {
                    corr[r*tauN+i]=ffunc->evaluate(tau[i], fullParams);
                }
                tau0avg=tau0avg+corr[r*tauN];
            }
            tau0avg=tau0avg/double(runs);
            if (!hasNParticle) Nparticle=1.0/tau0avg;

            // calc noise
            if (ui->chkNoise->isChecked()) {
                MTRand rng;
                if (ui->cmbNoiseModel->currentIndex()==0) {
                    double I=ui->spinAvgCountRate->value()*1000.0;
                    double I2=sqr(I);
                    double NN=Nparticle;
                    if (NN<=0) NN=1.0;
                    for (int r=0; r<runs; r++) {
                        double corr0=corr[r*tauN];
                        for (int i=0; i<tauN; i++) {
                            double corrT=corr[r*tauN+i];
                            double M=ui->spinMeasDuration->value()/tau[i];
                            double m=tau[0]/tau[i];
                            double var=((1.0+sqr(corr0))*(1.0+sqr(corrT))/(1.0-sqr(corr0))+2.0*m*sqr(corrT))/M/NN/NN+(2.0*(1.0+sqr(corrT))/NN/I+(1.0+corrT/NN)/I2)/M;
                            corr[r*tauN+i]=corr[r*tauN+i]+rng.randNorm(0,1)*sqrt(var);
                        }
                    }
                    used_params["noise_model"]=QString("Koppel");
                    used_params["noise_intensity_kHz"]=I;
                    used_params["noise_measurement_duration"]=ui->spinMeasDuration->value();
                } else if (ui->cmbNoiseModel->currentIndex()==1) {
                    for (int r=0; r<runs; r++) {
                        for (int i=0; i<tauN; i++) {
                            corr[r*tauN+i]=corr[r*tauN+i]+rng.randNorm(0, 1)*(ui->spinNoiseLevel->value()/100.0*tau0avg);
                        }
                    }
                    used_params["noise_model"]=QString("gaussian");
                    used_params["noise_level"]=ui->spinNoiseLevel->value();
                } else if (ui->cmbNoiseModel->currentIndex()==2) {
                    for (int r=0; r<runs; r++) {
                        for (int i=0; i<tauN; i++) {
                            corr[r*tauN+i]=corr[r*tauN+i]+(rng.rand()*2.0-1.0)*ui->spinNoiseLevel->value()/100.0*tau0avg;
                        }
                    }
                    used_params["noise_model"]=QString("uniform");
                    used_params["noise_level"]=ui->spinNoiseLevel->value();
                } else if (ui->cmbNoiseModel->currentIndex()==3) {
                    for (int r=0; r<runs; r++) {
                        for (int i=0; i<tauN; i++) {
                            corr[r*tauN+i]=corr[r*tauN+i]+rng.randNorm(0, 1)*(ui->spinNoiseLevel->value()/100.0*corr[r*tauN+i]);
                        }
                    }
                    used_params["noise_model"]=QString("local gaussian");
                    used_params["noise_level"]=ui->spinNoiseLevel->value();
                } else if (ui->cmbNoiseModel->currentIndex()==4) {
                    for (int r=0; r<runs; r++) {
                        for (int i=0; i<tauN; i++) {
                            corr[r*tauN+i]=corr[r*tauN+i]+(rng.rand()*2.0-1.0)*ui->spinNoiseLevel->value()/100.0*corr[r*tauN+i];
                        }
                    }
                    used_params["noise_model"]=QString("local uniform");
                    used_params["noise_level"]=ui->spinNoiseLevel->value();
                }
            }


            for (int i=0; i<tauN; i++) {
                csv=csv+CDoubleToQString(tau[i]);
                for (int r=0; r<runs; r++) {
                    csv=csv+", "+CDoubleToQString(corr[r*tauN+i]);
                }
                csv=csv+"\n";
            }


            size_t c_tau = ds->addCopiedColumn(tau, tauN, "tau");

            for (int r=0; r<runs; r++) {
                size_t c_fit = ds->addCopiedColumn(&(corr[r*tauN]), tauN, QString("function_r%1").arg(r));
                /////////////////////////////////////////////////////////////////////////////////
                // plot fit model and additional function graphs
                /////////////////////////////////////////////////////////////////////////////////
                JKQTPxyLineGraph* g_fit=new JKQTPxyLineGraph(ui->pltFunction->get_plotter());
                g_fit->set_drawLine(true);
                g_fit->set_title(tr("run %1").arg(r));
                g_fit->set_xColumn(c_tau);
                g_fit->set_yColumn(c_fit);
                ui->pltFunction->addGraph(g_fit);
            }
        }

        ui->pltFunction->zoomToFit();
        ui->pltFunction->set_doDrawing(true);
        ui->pltFunction->update_plot();
    } catch(std::exception& E) {
        services->log_error(tr("error during plotting, error message: %1\n").arg(E.what()));
    }

}