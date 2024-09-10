void GUI::removeQuestionPrompt()
{
    if(movingBlocked)
        movingBlocked = false;
    removeMenu("questionPrompt");
}