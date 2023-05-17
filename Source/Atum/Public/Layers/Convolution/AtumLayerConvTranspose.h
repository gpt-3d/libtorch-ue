﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvTransposeOptions.h"
#include "IAtumLayerBaseConvolution.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/modules/conv.h>
LIBTORCH_INCLUDES_END

#include "AtumLayerConvTranspose.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose Layer")
class ATUM_API UAtumLayerConvTranspose : public UObject, public IAtumLayerBaseConvolution
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerConvTransposeOptions Options;
	
	UE_NODISCARD
	bool IsCalculatedOutputTensorSizeValid(const TArray<int64>& InputSizes) const noexcept;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerConvTransposeOptions& GetOptions() const noexcept { return Options; }
	
	UE_NODISCARD
	FORCEINLINE FAtumLayerConvTransposeOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 1D Layer")
class ATUM_API UAtumLayerConvTranspose1D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::ConvTranspose1d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose1D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 2D Layer")
class ATUM_API UAtumLayerConvTranspose2D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::ConvTranspose2d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose2D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv Transpose 3D Layer")
class ATUM_API UAtumLayerConvTranspose3D : public UAtumLayerConvTranspose
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::ConvTranspose3d)
	
public:
	UE_NODISCARD_CTOR
	UAtumLayerConvTranspose3D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
