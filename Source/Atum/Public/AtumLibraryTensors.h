﻿// © 2023 Kaya Adrian.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h" // ReSharper disable once CppUnusedIncludeDirective
#include "Tensors/IAtumTensor.h"

#include "AtumLibraryTensors.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Tensor Library")
class ATUM_API UAtumLibraryTensors : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Serialize Array", CustomThunk, meta = (
		ArrayParm = "Target",
		CompactNodeTitle = "Serialize",
		Keywords = "ATUM Cast Serialise Serialize Target Any Wildcard Array Out Bytes"
	))
	static void K2_SerializeArray(const TArray<UProperty*>& Target, TArray<uint8>& OutBytes) noexcept;
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Deserialize Array", CustomThunk, meta = (
		ArrayParm = "TargetTypeProvider",
		ArrayTypeDependentParams = "OutTarget",
		CompactNodeTitle = "Deserialize",
		Keywords = "ATUM Cast Deserialise Deserialize Any Wildcard Bytes Target Type Provider Out"
	))
	static void K2_DeserializeArray(
		const TArray<uint8>& Bytes,
		const TArray<UProperty*>& TargetTypeProvider,
		TArray<UProperty*>& OutTarget
	) noexcept;

public:
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Constructor", DisplayName = "Make Empty Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Empty Tensor",
		Keywords = "ATUM Constructor Make Empty Tensor Class Sizes"
	))
	static UObject* Empty(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) TSubclassOf<UObject> Class,
		const TArray<int64>& Sizes
	) noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Constructor", DisplayName = "Make Eye Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Eye Tensor",
		Keywords = "ATUM Constructor Make Eye Tensor Class Size"
	))
	static UObject* Eye(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) TSubclassOf<UObject> Class,
		int64 Size
	) noexcept;

	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Constructor", DisplayName = "Make Ones Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Ones Tensor",
		Keywords = "ATUM Constructor Make Ones Tensor Class Sizes"
	))
	static UObject* Ones(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) TSubclassOf<UObject> Class,
		const TArray<int64>& Sizes
	) noexcept;

	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Constructor", DisplayName = "Make Random Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Random Tensor",
		Keywords = "ATUM Constructor Make Random Tensor Class Sizes"
	))
	static UObject* Random(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) TSubclassOf<UObject> Class,
		const TArray<int64>& Sizes
	) noexcept;

	UE_NODISCARD
	UFUNCTION(BlueprintCallable, Category = "ATUM|Constructor", DisplayName = "Make RandN Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "RandN Tensor",
		Keywords = "ATUM Constructor Make Normally Distributed Random Tensor Class Sizes"
	))
	static UObject* RandN(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) TSubclassOf<UObject> Class,
		const TArray<int64>& Sizes
	) noexcept;
	
	UE_NODISCARD
	UFUNCTION(BlueprintPure, Category = "ATUM|Cast", DisplayName = "To String", CustomThunk, meta = (
		BlueprintAutocast,
		CompactNodeTitle = "->",
		Keywords = "ATUM Cast Tensor To String"
	))
	static FORCEINLINE FString Conv_TensorToString(const TScriptInterface<const IAtumTensor>& Tensor)
	{ return Tensor->ToString(); }

	static void GenericArray_Serialize(
		const uint8* TargetAddress,
		const FArrayProperty* TargetProperty,
		TArray<uint8>& OutBytes
	) noexcept;

	static void GenericArray_Deserialize(
		const TArray<uint8>& Bytes,
		uint8* OutTargetAddress,
		const FArrayProperty* OutTargetProperty
	) noexcept;

private:
	DECLARE_FUNCTION(execK2_SerializeArray) noexcept;
	DECLARE_FUNCTION(execK2_DeserializeArray) noexcept;
	DECLARE_FUNCTION(execConv_TensorToString);
};