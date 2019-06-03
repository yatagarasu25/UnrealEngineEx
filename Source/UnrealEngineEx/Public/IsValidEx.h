static bool IsValid(FName Name)
{
	return Name != NAME_None && Name.IsValid();
}

template <typename T>
static bool IsValid(TSharedPtr<T> SharedPtr)
{
	return SharedPtr.IsValid();
}

template <typename T>
static bool IsValid(TWeakObjectPtr<T> WeakObjectPtr)
{
	return WeakObjectPtr.IsValid();
}

template <typename T>
static bool IsValid(TScriptInterface<T> ScriptInterface)
{
	return IsValid(ScriptInterface.GetObject());
}

static bool IsValid(FDelegateHandle DelegateHandle)
{
	return DelegateHandle.IsValid();
}

#ifdef UNREALENGINEEX_PropertyAccessor_generated_h
static bool IsValid(const FPropertyAccessor& PropertyAccessor)
{
	return PropertyAccessor.IsValid();
}
#endif

#ifdef ENGINE_BodyInstance_generated_h
static bool IsValid(FBodyInstance* BodyInstance)
{
	return BodyInstance && BodyInstance->IsValidBodyInstance();
}
#endif

template <typename T>
T* Valid(T* v) { return IsValid(v) ? v : nullptr; }

template <typename T>
const T* Valid(const T* v) { return IsValid(v) ? v : nullptr; }

template <typename T, typename U>
T* Valid(U* v) { return IsValid(v) ? Cast<T>(v) : nullptr; }

template <typename T, typename U>
const T* Valid(const U* v) { return IsValid(v) ? Cast<T>(v) : nullptr; }

template <typename T>
T* Valid(TWeakObjectPtr<T> v) { return IsValid(v) ? v.Get() : nullptr; }

template <typename T>
const T* Valid(TWeakObjectPtr<const T> v) { return IsValid(v) ? v.Get() : nullptr; }

template <typename T, typename U>
T* Valid(TWeakObjectPtr<U> v) { return IsValid(v) ? Cast<T>(v.Get()) : nullptr; }

template <typename T, typename U>
const T* Valid(TWeakObjectPtr<const U> v) { return IsValid(v) ? Cast<T>(v.Get()) : nullptr; }
