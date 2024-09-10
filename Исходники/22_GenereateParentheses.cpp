    vector<string> process(vector<string> &vecStr, int left, int right)
    {
        if (left == 0 && right == 0)
        {
            return vecStr;
        }

        vector<string> vecStrCopy(vecStr);
        vector<string> processResult;
        if (left > 0)
        {
            vector<string> leftBefore = process(vecStrCopy, left-1, right);
            for (int i = 0; i < leftBefore.size(); i++)
            {
                leftBefore[i] += "(";
                processResult.push_back(leftBefore[i]);
            }
        }
        if (right > left && right > 0)
        {
            vector<string> rightBefore = process(vecStrCopy, left, right-1);
            for (int i = 0; i < rightBefore.size(); i++)
            {
                rightBefore[i] += ")";
                processResult.push_back(rightBefore[i]);
            }
        }
        vecStr.swap(processResult);
        return processResult;
    }