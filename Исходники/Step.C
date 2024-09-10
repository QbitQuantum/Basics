Plan* Step::linkable(Requirement* req, Plan* plan)
{
   ;
   if(!(operators()->additions()->memberOf(req->condition())) 
      || (req->step()->precedes(this, plan->constraints())))

      {
         return 0;
      }
   Link* link = new Link(this,req->step(),  req->condition());
   Constrain* constraint  = new Constrain(this, req->step());


   SLBag<Constrain,ConstComp>* constraints = new SLBag<Constrain, ConstComp>;
   SLBag<Link,LinkComp>* new_link = new SLBag<Link, LinkComp>(*plan->links());
   new_link->addMember(link);
   constraints->addMember(constraint);
   return new Plan(plan->steps(), 
                   link->conflicts(plan)->append(plan->conflicts()), 
                   plan->constraints()->adjoin(constraints), 
                   new_link,
                   plan->requirements()->rest(),
                   plan->operators());
}