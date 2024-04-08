#include "decade_counter_sensor.h"
#include "esphome/core/log.h"

namespace esphome {
namespace decade_counter {

static const char *const TAG = "decade_counter";

void IRAM_ATTR DecadeCounterSensorStore::gpio_count_intr(DecadeCounterSensorStore *arg) {
  const uint32_t now = micros();
  arg->count_++;
  if (arg->clock_lambda_.has_value())  // call lambda function if available
    (*arg->clock_lambda_)(arg->count_);
}
void IRAM_ATTR DecadeCounterSensorStore::gpio_reset_intr(DecadeCounterSensorStore *arg) {
  arg->count_ = 0;
}

void DecadeCounterSensor::dump_config() {
  LOG_SENSOR("", "Decade Counter", this);
  LOG_PIN("  Pin: ", this->pin_);
  LOG_PIN("  Reset Pin: ", this->reset_pin_);
  LOG_UPDATE_INTERVAL(this);
}

void DecadeCounterSensor::update() {
  uint32_t count = this->store_.get_count();
  ESP_LOGD(TAG, "'%s': Retrieved counter: %i", this->get_name().c_str(), count);
  this->publish_state(count);
}

}  // namespace decade_counter
}  // namespace esphome