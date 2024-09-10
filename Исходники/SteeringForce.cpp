Vec2 SteeringForce::Pursuit(const Vehicle *evader)
{
    //如果逃避者在前面，而且面对着智能体
    //那么我们可以正好靠近逃避者
    Vec2 ToEvader = evader->getPosition() - m_pVehicle->getPosition();
    
    double RelativeHeading = m_pVehicle->getHeading().dot(evader->getHeading());
    if (ToEvader.dot(m_pVehicle->getHeading())>0&&RelativeHeading<-0.95) {
        return Seek(evader->getPosition());
    }
    
    //预测逃避者的位置
    
    double LookAheadTime = ToEvader.length()/(m_pVehicle->getMaxSpeed()+evader->getVeloctity().length());
    LookAheadTime +=TurnaroundTime(m_pVehicle,evader->getPosition());
    return  Seek(evader->getPosition()+evader->getVeloctity()*LookAheadTime);
    
}