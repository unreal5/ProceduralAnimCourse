// Fill out your copyright notice in the Description page of Project Settings.


#include "ControlRig/MyControlRig.h"
#include "Units/RigUnitContext.h"
#include "Math/ControlRigMathLibrary.h"
#include "Units/Collision/RigUnit_WorldCollision.h"
#include "Units/Highlevel/Hierarchy/RigUnit_TwoBoneIKSimple.h"


FRigUnit_SetFinalLegIK_Execute()
{
	auto RigHierarchy = ExecuteContext.Hierarchy;
	for (auto Foot : FeetArray)
	{
		auto FootTransform = RigHierarchy->GetGlobalTransform(Foot);


		auto Calf = RigHierarchy->GetFirstParent(Foot);

		auto Thigh = RigHierarchy->GetFirstParent(Calf);

		FVector PrimaryAxis = FVector::Zero();
		FVector SecondaryAxis = FVector::Zero();

		if (Foot.Name.IsEqual(FName("foot_r")))
		{
			PrimaryAxis.X = 1;
			SecondaryAxis.Y = -1;
		}
		else
		{
			PrimaryAxis.X = -1;
			SecondaryAxis.Y = 1;
		}
		FRigUnit_TwoBoneIKSimplePerItem TwoBoneIK;
		TwoBoneIK.ItemA = Thigh;
		TwoBoneIK.ItemB = Calf;
		TwoBoneIK.EffectorItem = Foot;
		TwoBoneIK.Effector = FootTransform;
		TwoBoneIK.PoleVector = FVector{0.f, 5000.f, 0.f};
		TwoBoneIK.PoleVectorKind = EControlRigVectorKind::Direction;
		TwoBoneIK.PrimaryAxis = PrimaryAxis;
		TwoBoneIK.SecondaryAxis = SecondaryAxis;
		TwoBoneIK.SecondaryAxisWeight = 1.f;
		TwoBoneIK.bEnableStretch = false;
		TwoBoneIK.StretchStartRatio = 0.75f;
		TwoBoneIK.StretchMaximumRatio = 1.25f;
		TwoBoneIK.Weight = 1.f;
		TwoBoneIK.ItemALength = 0.f;
		TwoBoneIK.ItemBLength = 0.f;
		TwoBoneIK.bPropagateToChildren = true;

		TwoBoneIK.ExecuteContext = ExecuteContext;
		TwoBoneIK.Execute();

		FQuat Rotation = FQuat::MakeFromEuler(FVector{0.f, 0.f, 45.f});
		FVector Translation = FVector::XAxisVector;
		auto result = Rotation.RotateVector(Translation);
	}
}

FRigUnit_RotateAroundPoint_Execute()
{
	Result.SetScale3D(TransformToRotate.GetScale3D());
	/** 获取四元数A与另一个四元数B相乘的结果（A * B）。
	在组合四元数时，顺序很重要：C = A * B 将产生一个四元数 C，该四元数在逻辑上首先应用 B，然后应用 A 到任何后续变换（先右后左）。
	*/
	Result.SetRotation(RotationAmount * TransformToRotate.GetRotation());
	const auto ABVector = TransformToRotate.GetLocation() - PointToRotateAround;
	const auto ModifiedVector = RotationAmount.RotateVector(ABVector);
	Result.SetLocation(ModifiedVector + PointToRotateAround);
}
