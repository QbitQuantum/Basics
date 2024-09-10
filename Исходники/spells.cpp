bstring effectSpellName(bstring effect) {
    effect = stripColor(effect.toLower());

    if(effect == "silent!") return("silence");
    if(effect == "blessed") return("bless");
    if(effect == "detect-invisible") return("detect-invisibility");
    if(effect == "invisible") return("invisibility");

    return(effect);
}