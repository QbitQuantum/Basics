 void checkResult(base::Time estimatedTime, base::Time estimatedPeriod)
 {
     addResultToPlot(estimatedTime, estimatedPeriod);
     BOOST_CHECK_SMALL((estimatedTime - realTime).toSeconds(), actualPeriod.toSeconds() / 10);
 }