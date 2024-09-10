TEST(MoreAdvancedComponent, MoreAdvancedComponent)
{
   // Create component instances and compose them.
   SimComponent *parentComponent = new SimComponent();
   SimpleComponent *simpleComponent = new SimpleComponent();
   MoreAdvancedComponent *moreAdvComponent = new MoreAdvancedComponent();
   // CodeReview note that the interface pointer isn't initialized in a ctor
   //  on the components, so it's bad memory against which you might
   //  be checking in testDependentInterface [3/3/2007 justind]
   parentComponent->addComponent( simpleComponent );
   parentComponent->addComponent( moreAdvComponent );

   simpleComponent->registerObject();
   moreAdvComponent->registerObject();

   // Put a break-point here, follow the onAdd call, and observe the order in
   // which the SimComponent::onAdd function executes. You will see the interfaces
   // get cached, and the dependent interface query being made.
   parentComponent->registerObject();

   // If the MoreAdvancedComponent found an interface, than the parentComponent
   // should have returned true, from onAdd, and should therefore be registered
   // properly with the Sim
   EXPECT_TRUE( parentComponent->isProperlyAdded() )
      << "Parent component not properly added!";

   // Now lets test the interface. You can step through this, as well.
   EXPECT_TRUE( moreAdvComponent->testDependentInterface() )
      << "Dependent interface test failed.";

   // CodeReview is there a reason we can't just delete the parentComponent here? [3/3/2007 justind]
   //
   // Clean up
   parentComponent->removeComponent( simpleComponent );
   parentComponent->removeComponent( moreAdvComponent );

   parentComponent->deleteObject();
   moreAdvComponent->deleteObject();
   simpleComponent->deleteObject();
};