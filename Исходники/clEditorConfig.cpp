wxArrayString clEditorConfig::ProcessSection(wxString& strLine)
{
    eEditorConfigState state = kEC_STATE_NORMAL;

    clEditorConfigTreeNode* tree = new clEditorConfigTreeNode;
    std::vector<clEditorConfigTreeNode*> trees;
    trees.push_back(tree);

    wxString curpattern;
    while(!strLine.IsEmpty()) {
        switch(state) {
        case kEC_STATE_NORMAL: {
            wxChar ch = strLine.at(0);
            strLine.Remove(0, 1);
            switch(ch) {
            case '{':
                state = kEC_STATE_IN_CURLYGRP;
                break;
            case '[':
                state = kEC_STATE_IN_SQUAREGRP;
                break;
            case ',':
                // new pattern
                if(!curpattern.IsEmpty()) {
                    tree->Add(curpattern);

                    tree = new clEditorConfigTreeNode;
                    trees.push_back(tree);
                    curpattern.clear();
                }
                break;
            default:
                curpattern << ch;
                break;
            }
            break;
        }
        case kEC_STATE_IN_CURLYGRP: {
            // if we got something so far, add it before we continue
            if(!curpattern.IsEmpty()) {
                tree->Add(curpattern);
                curpattern.clear();
            }

            // read the buffer until we hit the closing brace
            wxString buffer;
            if(!ReadUntil('}', strLine, buffer)) {
                return wxArrayString();
            }
            state = kEC_STATE_NORMAL;
            wxArrayString groupPatterns = ProcessSection(buffer);
            tree->Add(groupPatterns);
            break;
        }
        case kEC_STATE_IN_SQUAREGRP: {
            wxString buffer;
            if(!ReadUntil(']', strLine, buffer)) {
                return wxArrayString();
            }
            state = kEC_STATE_NORMAL;
            break;
        }
        }
    }

    // Remainder
    if(!curpattern.IsEmpty()) {
        tree->Add(curpattern);
    }

    wxArrayString res;
    for(size_t i = 0; i < trees.size(); ++i) {
        wxArrayString patterns;
        trees.at(i)->GetPatterns(patterns);
        res.insert(res.end(), patterns.begin(), patterns.end());
        delete trees.at(i);
    }

    // Loop over the array and change "**" => "*"
    for(size_t i = 0; i < res.size(); ++i) {
        res.Item(i).Replace("**", "*");
    }
    return res;
}