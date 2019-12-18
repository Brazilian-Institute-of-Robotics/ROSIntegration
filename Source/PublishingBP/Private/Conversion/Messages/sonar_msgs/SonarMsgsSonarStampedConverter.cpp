#include "SonarMsgsSonarStampedConverter.h"


USonarMsgsSonarStampedConverter::USonarMsgsSonarStampedConverter(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
  _MessageType = "sonar_msgs/SonarStamped";
}

bool USonarMsgsSonarStampedConverter::ConvertIncomingMessage(const ROSBridgePublishMsg* message, TSharedPtr<FROSBaseMsg> &BaseMsg) 
{
  auto p = new ROSMessages::sonar_msgs::SonarStamped;
  BaseMsg = TSharedPtr<FROSBaseMsg>(p);
  return _bson_extract_child_sonar(message->full_msg_bson_, "msg", p);
}

bool USonarMsgsSonarStampedConverter::ConvertOutgoingMessage(TSharedPtr<FROSBaseMsg> BaseMsg, bson_t** message)
{
  auto SonarStamped = StaticCastSharedPtr<ROSMessages::sonar_msgs::SonarStamped>(BaseMsg);

  *message = BCON_NEW(
    "header", "{",
    "seq", BCON_INT32(SonarStamped->header.seq),
    "stamp", "{",
    "secs", BCON_INT32(SonarStamped->header.time._Sec),
    "nsecs", BCON_INT32(SonarStamped->header.time._NSec),
    "}",
    "frame_id", BCON_UTF8(TCHAR_TO_UTF8(*SonarStamped->header.frame_id)),
    "}",
    "num_bins", BCON_INT32(SonarStamped->num_bins),
    "num_beams", BCON_INT32(SonarStamped->num_beams),
    "beams_width", BCON_DOUBLE(SonarStamped->beams_width),
    "beam_height", BCON_DOUBLE(SonarStamped->beam_height),
    "bearings", BCON_DOUBLE(SonarStamped->bearings)
  );
  _bson_append_float_tarray(*message, "data", SonarStamped.Get()->data);

  return true;
}