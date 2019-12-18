#include "PublishBP.h"

bool UPublishBP::PublishImageMessage(const TArray<FColor> Data, int Height, int Width)
{
    check(_Implementation->_MessageType == TEXT("sensor_msgs/Image"));

    if (!_State.Advertised)
    {
        if (!Advertise())
        {
            return false;
        }
    }

    TSharedPtr<ROSMessages::sensor_msgs::Image> msg = MakeShareable(new ROSMessages::sensor_msgs::Image);

    ROSMessages::std_msgs::Header HeaderMessage;

	  HeaderMessage.frame_id = FString(TEXT("body"));
	  HeaderMessage.time = FROSTime::Now();
	  msg->header = HeaderMessage;
    msg->height = Height;
	  msg->width = Width;
	  msg->step = Width * 4;
	  msg->encoding = FString(TEXT("bgra8"));
	  msg->data = Data;

    return _Implementation->Publish(msg);
}

void UPublishBP::CreateTopic(const FString& TopicName, FString MessageType, int32 QueueSize)
{
    _State.Blueprint = true;
    _State.BlueprintMessageType = MessageType;

    UROSIntegrationGameInstance* ROSInstance = Cast<UROSIntegrationGameInstance>(GWorld->GetGameInstance());
    if (ROSInstance)
    {
        if (ROSInstance->bConnectToROS && _State.Connected)
        {
            Init(ROSInstance->ROSIntegrationCore, TopicName, MessageType, QueueSize);
        }
    }
    else
    {
        UE_LOG(LogROS, Warning, TEXT("ROSIntegrationGameInstance does not exist."));
    }
}