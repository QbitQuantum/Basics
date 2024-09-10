void PairwiseRegistrationDialog::showResults(const Eigen::Matrix4f &transformation, float rmsError, int corrNumber)
{
	std::stringstream temp;
	Eigen::Matrix4f T = transformation;
	temp.str("");
	temp << T;
	TTextEdit->setText(QString::fromStdString(temp.str()));
	Eigen::Matrix3f R = T.block(0,0,3,3);
	float c = (R * R.transpose()).diagonal().mean();
	c = qSqrt(c);
	cLineEdit->setText(QString::number(c));
	R /= c;
	temp.str("");
	temp << R;
	RTextEdit->setText(QString::fromStdString(temp.str()));
	Eigen::Vector3f t = T.block(0,3,3,1);
	temp.str("");
	temp << t;
	tLineEdit->setText(QString::fromStdString(temp.str()));
	Eigen::AngleAxisf angleAxis(R);
	angleLineEdit->setText( QString::number(angleAxis.angle()) );
	temp.str("");
	temp << angleAxis.axis();
	axisLineEdit->setText(QString::fromStdString(temp.str()));

	corrNumberLineEdit->setText(QString::number(corrNumber));
	errorLineEdit->setText(QString::number(rmsError));
}