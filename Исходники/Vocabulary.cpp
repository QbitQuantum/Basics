void Vocabulary::initWordVectors(){
  this->scoreVector = MatD::Zero(this->scoreDim, this->contextStr.size()-2);
  this->scoreBias = MatD::Zero(1, this->contextStr.size()-2);

  Rand rnd;
  double r = 1.0/this->wordDim;

  this->nounVector = MatD(this->wordDim, this->nounStr.size());
  this->contextVector = MatD(this->wordDim, this->contextStr.size());

  rnd.gauss(this->nounVector, r);
  rnd.gauss(this->contextVector, r);
}