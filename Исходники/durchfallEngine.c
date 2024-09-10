void vitalDemage(circle *vital, avatar *enemy)
{
    float distance;

    distance = sqrt(pow((vital->coordX - enemy->coordX),2) + pow((vital->coordY - enemy->coordY),2));

    if((distance < vital->radius + enemy->radius)&&(vital->timeDemage.flag))
    {
        vital->life-=10;
        if(vital->life <= 0)
            vital->life = 0;
        setTimer(&vital->timeDemage.time, 100);
    }
}