#pragma once


#include "Modules/ModuleInterface.h"
#include "Modules/ModuleManager.h"



class FComponentExModule : public IModuleInterface
{
public:
	static inline FComponentExModule& Get() { return FModuleManager::LoadModuleChecked<FComponentExModule>("ComponentEx"); }
	static inline bool IsAvailable() { return FModuleManager::Get().IsModuleLoaded("ComponentEx"); }

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};



#ifdef ENGINE_Actor_generated_h
#include "ActorEx.h"
#endif

#ifdef ENGINE_SkeletalMesh_generated_h
#include "SkeletalMeshEx.h"
#endif



struct FComponentEx
{
	COMPONENTEX_API static void SetActorEnabled(class AActor* Actor, bool bIsEnabled);
};
