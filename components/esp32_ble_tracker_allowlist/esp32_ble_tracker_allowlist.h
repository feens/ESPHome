#pragma once

#include "esphome/core/component.h"
#include "esphome/components/esp32_ble_tracker/esp32_ble_tracker.h"

#ifdef USE_ESP32

namespace esphome {
namespace esp32_ble_tracker_allowlist {

class ESP32BLETrackerAllowlist : public esphome::esp32_ble_tracker::ESP32BLETracker {
    protected:

      /// Start a single scan by setting up the parameters and doing some esp-idf calls.
      void start_scan_(bool first);
};

}
}

#endif
