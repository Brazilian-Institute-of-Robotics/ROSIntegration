#pragma once

#include <CoreMinimal.h>
#include <UObject/ObjectMacros.h>
#include <UObject/Object.h>
#include "Public/sonar_msgs/SonarStamped.h"
#include "ROSIntegration/Private/Conversion/Messages/BaseMessageConverter.h"
#include "ROSIntegration/Private/Conversion/Messages/std_msgs/StdMsgsHeaderConverter.h"


#include "SonarMsgsSonarStampedConverter.generated.h"


UCLASS()
class PUBLISHINGBP_API USonarMsgsSonarStampedConverter: public UBaseMessageConverter
{
  GENERATED_UCLASS_BODY()

public:
  virtual bool ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg);
  virtual bool ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message);

  static bool _bson_extract_child_sonar(bson_t *b, FString key, ROSMessages::sonar_msgs::SonarStamped *sonar)
  {
    bool KeyFound = false;

    KeyFound = UStdMsgsHeaderConverter::_bson_extract_child_header(b, TEXT("msg.header"), &sonar->header); if (!KeyFound) return false;

    sonar->num_bins = GetInt32FromBSON(key + ".num_bins", b, KeyFound); if (!KeyFound) return false;
    sonar->num_beams = GetInt32FromBSON(key + ".num_beams", b, KeyFound); if (!KeyFound) return false;
    sonar->beams_width = GetDoubleFromBSON(key + ".beams_width", b, KeyFound); if (!KeyFound) return false;
    sonar->beam_height = GetDoubleFromBSON(key + ".beam_height", b, KeyFound); if (!KeyFound) return false;
    sonar->bearings = GetDoubleFromBSON(key + ".bearings", b, KeyFound); if (!KeyFound) return false;

    uint32_t binSize = 0;
    const uint8* ReceivedData = rosbridge2cpp::Helper::get_binary_by_key(TCHAR_TO_UTF8(*(key + ".data")), *b, binSize, KeyFound);
    sonar->data = TArray<float>((float*)ReceivedData, binSize);
    delete ReceivedData;

    return KeyFound;
  }
};
