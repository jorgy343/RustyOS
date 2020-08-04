#pragma once

constexpr int AtExitMaxEntries = 128;

struct AtExitFunctionEntry
{
    void (*DestructorFunction)(void*);
    void* ObjectPointer;
    void* DsoHandle;
    bool HasBeenCalled;
};

/// Registers a DSO object for later cleanup. Calls to this function may be automatically made
/// by the compiler/linker. Users should generally not call this function.
/// 
/// @param[in] destructorFunction The destructor function to call to clean up the DSO object.
/// @param[in] objectPointer The pointer to the object to pass into destructorFunction.
/// @param[in] dso The DSO object handle to identify the registered DSO object.
/// 
/// @return Returns 0 on success and non-zero on failure.
extern "C" int __cxa_atexit(void (*destructorFunction)(void*), void* objectPointer, void* dsoHandle);

/// Cleans up registered DSO objects. Calls to this function may be automatically made by the
/// compiler/linker or called directly by the user.
/// 
/// @param[in] dso The registered DSO object to cleanup or nullptr to clean up all registered DSO objects.
extern "C" void __cxa_finalize(void* dsoHandle);

/// Cleans up all global and static objects that have requested to be cleaned up. This function is
/// compiler independant and called by the user.
extern "C" void DeinitializeObjects();