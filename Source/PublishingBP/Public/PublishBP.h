#include "ROSIntegration/Classes/RI/Topic.h"
#include "ROSIntegrationCore.h"
#include "PublishBP.generated.h"

UCLASS(Blueprintable)
// class ROSINTEGRATION_API UTopic: public UObject
class UPublishBP: public UTopic
{
    GENERATED_UCLASS_BODY()

    public:
      UFUNCTION(BlueprintCallable, Category = "ROS|Topic")
      bool PublishImageMessage(const TArray<FColor> Data, int Height, int Width);

      UFUNCTION(BlueprintCallable, Category = "ROS|Topic")
      void CreateTopic(const FString& TopicName, FString MessageType, int32 QueueSize = 1);
};
