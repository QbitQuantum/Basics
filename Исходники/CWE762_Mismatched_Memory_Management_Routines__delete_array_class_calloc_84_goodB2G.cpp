CWE762_Mismatched_Memory_Management_Routines__delete_array_class_calloc_84_goodB2G::CWE762_Mismatched_Memory_Management_Routines__delete_array_class_calloc_84_goodB2G(TwoIntsClass * dataCopy)
{
    data = dataCopy;
    /* POTENTIAL FLAW: Allocate memory with a function that requires free() to free the memory */
    data = (TwoIntsClass *)calloc(100, sizeof(TwoIntsClass));
}