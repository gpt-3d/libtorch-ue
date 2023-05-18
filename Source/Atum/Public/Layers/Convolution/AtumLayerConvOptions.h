﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvPaddingMode.h"
#include "Layers/IAtumLayer.h"

#include "AtumLayerConvOptions.generated.h"

class UAtumLayerConv;


USTRUCT(BlueprintType, DisplayName = "ATUM Conv Layer Options")
struct ATUM_API FAtumLayerConvOptions : public FAtumLayerOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 InChannels;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 OutChannels;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> KernelSize;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Stride;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Padding;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	int64 Groups;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	bool bBias;
	
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	TArray<int64> Dilation;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (AllowPrivateAccess))
	EAtumConvPaddingMode PaddingMode;
	
protected:
	UE_NODISCARD_CTOR
	FAtumLayerConvOptions() noexcept;
	
public:
	UE_NODISCARD_CTOR
	explicit FAtumLayerConvOptions(uint64 Dimensions) noexcept;
	
	template <uint64 Dimensions>
	requires (1u <= Dimensions && Dimensions <= 3u)
	UE_NODISCARD
	FORCEINLINE explicit operator torch::nn::ConvOptions<Dimensions>() const noexcept;
	
	friend UAtumLayerConv;
	friend UScriptStruct;
};


template <uint64 Dimensions>
requires (1u <= Dimensions && Dimensions <= 3u)
FAtumLayerConvOptions::operator torch::nn::ConvOptions<Dimensions>() const noexcept
{
	return torch::nn::ConvOptions<Dimensions>(
		InChannels,
		OutChannels,
		at::IntArrayRef(KernelSize.GetData(), Dimensions)
	).stride(at::IntArrayRef(Stride.GetData(), Dimensions))
	.padding(at::IntArrayRef(Padding.GetData(), Dimensions))
	.groups(Groups)
	.bias(bBias)
	.dilation(at::IntArrayRef(Dilation.GetData(), Dimensions))
	.padding_mode(AtumEnums::Cast<Dimensions>(PaddingMode));
}
