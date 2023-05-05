﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumLayerConvOptions.h"
#include "IAtumLayerConv.h"

#include "AtumLayerConv.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Base Conv Layer")
class ATUM_API UAtumLayerBaseConv : public UObject, public IAtumLayerConv
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ATUM|Options", meta = (
		AllowPrivateAccess,
		ShowOnlyInnerProperties
	))
	FAtumLayerConvOptions Options;
	
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;

public:
	UE_NODISCARD
	FORCEINLINE const FAtumLayerConvOptions& GetOptions() const noexcept { return Options; }

	UE_NODISCARD
	FORCEINLINE FAtumLayerConvOptions& GetOptions() noexcept { return Options; }
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 1D Layer")
class ATUM_API UAtumLayerConv1D : public UAtumLayerBaseConv, public TAtumLayer<torch::nn::Conv1dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv1D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 2D Layer")
class ATUM_API UAtumLayerConv2D : public UAtumLayerBaseConv, public TAtumLayer<torch::nn::Conv2dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv2D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Conv 3D Layer")
class ATUM_API UAtumLayerConv3D : public UAtumLayerBaseConv, public TAtumLayer<torch::nn::Conv3dImpl>
{
	GENERATED_BODY()

public:
	UE_NODISCARD_CTOR
	UAtumLayerConv3D() noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;

	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};
