// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ControlRig.h"
#include "MyControlRig.generated.h"


USTRUCT(meta = (DisplayName = "SetFinalLegIK", Category = "用户自定义函数"))
struct PROCEDURALANIMCOURSE_API FRigUnit_SetFinalLegIK : public FRigUnitMutable
{
	GENERATED_BODY()

	FRigUnit_SetFinalLegIK()
	{
	}

	RIGVM_METHOD()
	virtual void Execute() override;

	UPROPERTY(meta = (Input))
	TArray<FRigElementKey> FeetArray;

	//UPROPERTY(meta = (Output))
	//float Result;
};

USTRUCT(meta = (DisplayName = "RotateAroundPoint", Category = "用户自定义函数"))
struct PROCEDURALANIMCOURSE_API FRigUnit_RotateAroundPoint : public FRigUnitMutable
{
	GENERATED_BODY()

	FRigUnit_RotateAroundPoint() : FRigUnitMutable(), TransformToRotate(FTransform::Identity),
	                               PointToRotateAround(FVector::ZeroVector), RotationAmount(FQuat::Identity)
	{
	}

	RIGVM_METHOD()
	virtual void Execute() override;

	UPROPERTY(meta = (Input))
	FTransform TransformToRotate;

	UPROPERTY(meta = (Input))
	FVector PointToRotateAround;

	UPROPERTY(meta = (Input))
	FQuat RotationAmount;

	UPROPERTY(meta = (Output))
	FTransform Result;
};
