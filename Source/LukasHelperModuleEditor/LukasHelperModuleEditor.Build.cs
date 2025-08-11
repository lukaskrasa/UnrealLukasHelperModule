using UnrealBuildTool;

public class LukasHelperModuleEditor : ModuleRules
{
    public LukasHelperModuleEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "BlueprintEditorLibrary",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "UnrealEd",
                "WorldPartitionEditor",
                "DataLayerEditor"
            }
        );
    }
}