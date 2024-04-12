#pragma once

#include "esphome/core/component.h"
// #include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace cooktop_plug {

class CooktopPlugComponent : public Component, public uart::UARTDevice {
 public:
  void set_power_threshold(float power_threshold) { power_threshold_ = power_threshold; }
  void set_power_sensor(sensor::Sensor *power_sensor) { power_sensor_ = power_sensor; }

  void loop() override;
  float get_setup_priority() const override;
  void dump_config() override;

 protected:
  bool check_byte_();
  void parse_data_();
  uint32_t get_24_bit_uint_(uint8_t start_index);

  uint8_t raw_data_[24];
  uint8_t raw_data_index_{0};
  uint32_t last_transmission_{0};
  sensor::Sensor *power_sensor_{nullptr};
  uint32_t cf_pulses_total_{0};
  uint16_t cf_pulses_last_{0};
  float power_threshold_{0};
  float previous_power_{0};
};

}  // namespace cooktop_plug
}  // namespace esphome