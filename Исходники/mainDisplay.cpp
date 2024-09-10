//
// Displays team data.
//
void  displayTeamData( const RaceAnalyzer  &raceData )
{
  cout  <<  endl;

  //
  // Get display parameters from the user
  //

  TeamDisplayParameters  displayParams(raceData);

  displayParams.m_stage    =  getStageNumber( raceData );

  unsigned     displayMax  =  atoi( getSetting("Display max").c_str() );


  //
  // Display the table header
  //
  displayTeamDataHeader( displayParams, displayMax );


  //
  // Get the team names
  //
  RaceAnalyzer::StrSet  teams  =  raceData.teams();



  //
  // Create (or sort) a container of team seconds/name
  //
  RaceAnalyzer::Results  teamResults;

  transform( teams.begin(),
             teams.end(),
             back_inserter(teamResults),
             bind2nd(TeamToTeamResult(displayParams.m_stage), raceData) );


  teamResults.sort();


  //
  // Handle no matching results
  //
  if  ( ! teamResults.size() )
  {
    cout  <<  "*** no teams match the selected criteria ***"  <<  endl;
    return;
  }


  //
  // Pair down the data so there is only as much as the
  // user wants to see.
  //
  if  (displayMax)
  {
    RaceAnalyzer::Results::iterator  iter  =  teamResults.begin();

    advance( iter, displayMax );

    teamResults.erase( iter, teamResults.end() );
  }


  //
  // Display the team data
  //
  for_each( teamResults.begin(),
            teamResults.end(),
            bind2nd(DisplayTeam(), displayParams) );
}