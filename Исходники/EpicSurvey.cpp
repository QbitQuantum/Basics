TSharedRef< FEpicSurvey > FEpicSurvey::Create()
{
	TSharedRef< FUICommandList > ActionList = MakeShareable( new FUICommandList() );

	TSharedRef< FEpicSurvey > EpicSurvey = MakeShareable( new FEpicSurvey( ActionList ) );
	EpicSurvey->Initialize();
	return EpicSurvey;
}