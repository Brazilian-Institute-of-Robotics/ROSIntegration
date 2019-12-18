#pragma once 

#include "ROSBaseMsg.h"
#include "ROSIntegration/Public/std_msgs/Header.h"

namespace ROSMessages {
  namespace sonar_msgs {
    class SonarStamped : public FROSBaseMsg {
    public:
      SonarStamped() {
        _MessageType = "sonar_msgs/SonarStamped";
      }

      ROSMessages::std_msgs::Header header;

      uint num_bins;
      uint num_beams;

      float beams_width;

      float beam_height;
      float bearings;

      TArray<float> data;
    };
  }
}
