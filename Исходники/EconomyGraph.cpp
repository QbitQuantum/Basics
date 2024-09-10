//see do_history_linegraph in oldgui/screen.cpp
void EconomyGraph::updateData(){
    int i;
    float f;
    int w = getConfig()->monthgraphW;
    //thats the value oldgui uses, so saved data has same scale as new.
    int h = 64; //MONTHGRAPH_H; 

    for (i = w - 1; i > 0; i--) {
	    monthgraph_pop[i] = monthgraph_pop[i-1];
	    monthgraph_ppool[i] = monthgraph_ppool[i-1];
	    monthgraph_nojobs[i] = monthgraph_nojobs[i-1];
	    monthgraph_starve[i] = monthgraph_starve[i-1];
    }
    if (tpopulation > 0)
    {
	monthgraph_pop[0] = ((int) (log ((tpopulation / NUMOF_DAYS_IN_MONTH)
					 + 1.f) * h / 15)) - 5;
	if (monthgraph_pop[0] < 0)
	    monthgraph_pop[0] = 0;
	f = ((float) tstarving_population 
	     / ((float) tpopulation + 1.0)) * 100.0;
	if (tpopulation > 3000)	/* double the scale if pop > 3000 */
	    f += f;
	if (tpopulation > 6000)	/* double it AGAIN if pop > 6000 */
	    f += f;
	monthgraph_starve[0] = (int) f;
	/* max out at 32 */
	if (monthgraph_starve[0] >= h)
	    monthgraph_starve[0] = h - 1;
	f = ((float) tunemployed_population
	     / ((float) tpopulation + 1.0)) * 100.0;
	if (tpopulation > 3000)	/* double the scale if pop > 3000 */
	    f += f;
	if (tpopulation > 6000)	/* double it AGAIN if pop > 6000 */
	    f += f;
	monthgraph_nojobs[0] = (int) f;
	/* max out at 32  */
	if (monthgraph_nojobs[0] >= h)
	    monthgraph_nojobs[0] = h - 1;
	monthgraph_ppool[0] = ((int) (sqrt (people_pool + 1.f) * h) / 35);
	if (monthgraph_ppool[0] < 0)
	    monthgraph_ppool[0] = 0;
	if (monthgraph_ppool[0] >= h)
	    monthgraph_ppool[0] = h - 1;
    }
    
    //sustainability check from do_sust_barchart
    if (sust_dig_ore_coal_count >= SUST_ORE_COAL_YEARS_NEEDED
        && sust_port_count >= SUST_PORT_YEARS_NEEDED
        && sust_old_money_count >= SUST_MONEY_YEARS_NEEDED
        && sust_old_population_count >= SUST_POP_YEARS_NEEDED
        && sust_old_tech_count >= SUST_TECH_YEARS_NEEDED
        && sust_fire_count >= SUST_FIRE_YEARS_NEEDED)
    {
        if (sustain_flag == 0){
	        ok_dial_box ("sustain.mes", GOOD, 0L);
            sustain_flag = 1;
        }
    } else {
        sustain_flag = 0;
    }

    
    //sustain_flag == 1 means player had a sustainable economy
    //total_evacuated >0 means player evacuated at least some people
    if( !housed_population && !people_pool ){ //no people left
        if( !nobodyHomeDialogShown ){
            std::string message;
            if( sustain_flag == 1 || total_evacuated >0  ){
                message ="";
            } else {
                message = _("You lose.");
            }
            try{
                new Dialog( MSG_DIALOG, "allgone.xml", message );
            } catch(std::exception& e) {
                std::cerr << "Problem with ok_dial_box: " << e.what() << "\n";
                std::ostringstream text;
                text << "ok_dial_box:' allgone.xml" << "' + \"" << message << "\"\n";
                updateMessageText( text.str() );
            }
            nobodyHomeDialogShown = true;
        }
    } else if( nobodyHomeDialogShown ){ //reset flag if there are people
        nobodyHomeDialogShown = false;
    }
   

    Component* root = this;
    while( root->getParent() ){
        root = root->getParent();
    }

    // Initialisation can not be done in constructor because the SwitchEconomyGraph-Button does not exist then.
    if( switchEconomyGraphButton == NULL ){
        switchEconomyGraphButton = getCheckButton( *root, "SwitchEconomyGraph" );
        switchEconomyGraphText = switchEconomyGraphButton->getCaptionText();
        switchEconomyGraphParagraph = dynamic_cast<Paragraph*>(switchEconomyGraphButton->getCaption());
        redStyle = yellowStyle = normalStyle = switchEconomyGraphParagraph->getStyle();
        yellowStyle.text_color.parse("yellow");
        redStyle.text_color.parse("red");
    }
 
    // set tab Button colour
    if( switchEconomyGraphParagraph ){
        if( monthgraph_starve[0] > 0 ){ // people are starving: RED
            switchEconomyGraphParagraph->setText(switchEconomyGraphText, redStyle);
        } else if( monthgraph_nojobs[0] > 0 ){ // people are unemployed: YELLOW
            switchEconomyGraphParagraph->setText(switchEconomyGraphText, yellowStyle);
        } else {
            switchEconomyGraphParagraph->setText(switchEconomyGraphText, normalStyle);
        }
    }
    
    //redraw
    setDirty();
}