//..
// Our verification program simply instantiate several 'MyGenericContainer'
// templates with the two test types above, and checks that the allocator
// slot is as expected:
//..
    int usageExample()
    {
        bslma::TestAllocator ta0;
        bslma::TestAllocator ta1;
//..
// With 'MyTestTypeWithNoBslmaAllocatorTraits', the slot should never be set.
//..
        MyTestTypeWithNoBslmaAllocatorTraits x;

        allocSlot = &ta0;
        MyGenericContainer<MyTestTypeWithNoBslmaAllocatorTraits> x0(x);
        ASSERT(&ta0 == allocSlot);

        allocSlot = &ta0;
        MyGenericContainer<MyTestTypeWithNoBslmaAllocatorTraits> x1(x, &ta1);
        ASSERT(&ta0 == allocSlot);
//..
// With 'MyTestTypeWithBslmaAllocatorTraits', the slot should be set to the
// allocator argument, or to 0 if not specified:
//..
        MyTestTypeWithBslmaAllocatorTraits y;

        allocSlot = &ta0;
        MyGenericContainer<MyTestTypeWithBslmaAllocatorTraits> y0(y);
        ASSERT(0 == allocSlot);

        allocSlot = &ta0;
        MyGenericContainer<MyTestTypeWithBslmaAllocatorTraits> y1(y, &ta1);
        ASSERT(&ta1 == allocSlot);

        return 0;
    }