#include "ConstructorDestructor.h"

AtExitFunctionEntry AtExitFunctions[AtExitMaxEntries];
int AtExitFunctionCount = 0;

void DeinitializeObjects()
{
    __cxa_finalize(nullptr);
}

int __cxa_atexit(void (*destructorFunction)(void*), void* objectPointer, void* dsoHandle)
{
    if (AtExitFunctionCount >= AtExitMaxEntries)
    {
        // Error code is anything non-zero.
        return -1;
    }

    // Add the entry to our descructor list.
    AtExitFunctions[AtExitFunctionCount].DestructorFunction = destructorFunction;
    AtExitFunctions[AtExitFunctionCount].ObjectPointer = objectPointer;
    AtExitFunctions[AtExitFunctionCount].DsoHandle = dsoHandle;
    AtExitFunctions[AtExitFunctionCount].HasBeenCalled = false;

    AtExitFunctionCount++;

    // Success code is 0.
    return 0;
}

void __cxa_finalize(void* dsoHandle)
{
    // If dso is null than we call all destructor functions.
    if (dsoHandle == nullptr)
    {
        for (int i = AtExitFunctionCount - 1; i >= 0; --i)
        {
            if (!AtExitFunctions[AtExitFunctionCount].HasBeenCalled)
            {
                // Call the destructor function passing in the object pointer.
                AtExitFunctions[AtExitFunctionCount].DestructorFunction(AtExitFunctions[AtExitFunctionCount].ObjectPointer);
            }
        }
    }
    // Otherwise we must only call destructor functions who's dso matches the dso passed in.
    else
    {
        for (int i = AtExitFunctionCount - 1; i >= 0; --i)
        {
            if (!AtExitFunctions[AtExitFunctionCount].HasBeenCalled && AtExitFunctions[AtExitFunctionCount].DsoHandle == dsoHandle)
            {
                // Call the destructor function passing in the object pointer.
                AtExitFunctions[AtExitFunctionCount].DestructorFunction(AtExitFunctions[AtExitFunctionCount].ObjectPointer);
            }
        }
    }
}