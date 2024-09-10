s_routePlanner_return gotoWaypoint(float x, float y, float x_goal, float y_goal, float angle)
{
    float toGoalAngle = getAngleBetweenPoints(x,y,x_goal,y_goal);
    float distance = sqrt(powf(x_goal-x,2) + powf(y_goal-y,2));
    float angleDelta = getRadianAngleDif(angle,toGoalAngle);
    s_routePlanner_return results;
    results.steeringCmd = fLimit(angleDelta*150,-100,100);
    results.finished = 0;
    results.power = __min(distance*20,2000/fAbs(results.steeringCmd));
    results.power = __min(results.power, 100);
    
    if(distance < .5)
    {
        results.power = 0;
        results.finished = 1;
    }
    
    return results;
    
    
}