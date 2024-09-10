void Bonus (Score_t* score)
{
     if (GetAsyncKeyState ('1') && score->points >= 50) {HP+=1.0; score->points -= 50;};
}