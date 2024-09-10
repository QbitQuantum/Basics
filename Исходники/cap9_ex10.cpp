bool RecursiveCutStock(Vector<int>& requests, int stock_length, int number_of_stock, int remaning_length)
{
    //Success case, solution found
    if(requests.size() == 0)
        return true;

    if(number_of_stock < 1) //run out of stocks
        return false;

    for (int i = 0; i < requests.size(); ++i)
    {
        int requested_stock = requests[i];

        while(remaning_length < requested_stock)
        {
            number_of_stock--;
            remaning_length = stock_length;

            if(number_of_stock < 1) //run out of stocks
                return false;
        }

        remaning_length -= requested_stock; //apply configuration
        requests.remove(i);

        if(RecursiveCutStock(requests, stock_length, number_of_stock, remaning_length))
            return true;

        remaning_length += requested_stock; //revert the configuration
        requests.add(requested_stock);
    }

    return false; //Return false to proceed the backtrack
}