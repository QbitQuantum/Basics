void RunApplication()
{
   // create some qa objects
   QA *top = new QA("topping",
      "What topping would you like?",
      "topping.net",
      "I have a variety of toppings\n - try your favourite combination");
   QA *qty = new QA("quantity",
      "How many pizzas would you like?",
      "howmany.net",
      "I need to know how many pizzas to deliver");

   // Start recogniser running
   StartRecogniser();

   do{
      top->GetSlot();
      if (!terminated && top->status == grounded) qty->GetSlot();
      if (top->status == grounded && qty->status == grounded) {
         Talk("Your order is: \n   "+top->value+"  "+qty->value, "completed");
      }
      top->Reset(); qty->Reset();
      printf("\n\n=====================================\n\n");
   }while(!terminated);

   ShutDown();
}