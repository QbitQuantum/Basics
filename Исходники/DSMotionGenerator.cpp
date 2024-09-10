REALTYPE DSMotionGenerator::GetDirectionOfMotion(Vector & result){
  if(result.Size()==DesVelV.Size()){
    result = DesVelV;
    result.Normalize();
  }
  else{
    cout<<"MOTION GENERATOR: dimension mismatch when getting direction of motion, resizing vector!"<<endl;
    result.Resize(DesVelV.Size());
    result = DesVelV;
    result.Normalize();
  }
  return DesVelV.Norm();
}