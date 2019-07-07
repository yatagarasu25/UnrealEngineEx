#pragma once
#include "PropertyAccessor.generated.h"


USTRUCT(BlueprintType)
struct UNREALENGINEEX_API FPropertyAccessor
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UObject* Object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UProperty* Property;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FName PropertyName;


public:
	FPropertyAccessor() {}
	FPropertyAccessor(UObject* Object, FName PropertyName)
		: Object(Object)
		, Property(nullptr)
		, PropertyName(PropertyName)
	{
		if (::IsValid(Object))
		{
			Property = Object->GetClass()->FindPropertyByName(PropertyName);
		}
	}


public:
	bool IsValid() const
	{
		return ::IsValid(Object) && ::IsValid(Property);
	}

	template <typename T>
	T GetValue() const
	{
		T* ValuePtr = Property->ContainerPtrToValuePtr<T>(Object);
		return *ValuePtr;
	}

	template <typename T>
	void SetValue(const T& value)
	{
		T* ValuePtr = Property->ContainerPtrToValuePtr<T>(Object);
		*ValuePtr = value;
	}
};
