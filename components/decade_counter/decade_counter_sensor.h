#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/sensor/sensor.h"

#include <cinttypes>

namespace esphome {
namespace decade_counter {

// using clock_lambda_t = std::function<void(std::vector<uint8_t> &)>;

class DecadeCounterSensorStore {
 public:
  void setup(InternalGPIOPin *pin, InternalGPIOPin *reset_pin, optional<std::function<void(int32_t)>> clock_lambda, optional<std::function<void(void)>> reset_lambda) {
  // void setup(InternalGPIOPin *pin, InternalGPIOPin *reset_pin) {
    pin->setup();
    this->pin_ = pin->to_isr();
    pin->attach_interrupt(&DecadeCounterSensorStore::gpio_count_intr, this, gpio::INTERRUPT_RISING_EDGE);

    reset_pin->setup();
    this->reset_pin_ = reset_pin->to_isr();
    reset_pin->attach_interrupt(&DecadeCounterSensorStore::gpio_reset_intr, this, gpio::INTERRUPT_RISING_EDGE);

    this->clock_lambda_ = clock_lambda;
    this->reset_lambda_ = reset_lambda;
  }
  static void gpio_count_intr(DecadeCounterSensorStore *arg);
  static void gpio_reset_intr(DecadeCounterSensorStore *arg);
  int32_t get_count() const { return this->count_; };

 protected:
  ISRInternalGPIOPin pin_;
  ISRInternalGPIOPin reset_pin_;
  volatile int32_t count_{0};
  optional<std::function<void(int32_t)>> clock_lambda_;
  optional<std::function<void(void)>> reset_lambda_;
};

class DecadeCounterSensor : public sensor::Sensor, public PollingComponent {
 public:
  void set_pin(InternalGPIOPin *pin) { pin_ = pin; }
  void set_reset_pin(InternalGPIOPin *reset_pin) { reset_pin_ = reset_pin; }
  void set_clock_interrupt_lambda(std::function<void(int32_t)> &&clock_lambda) { clock_lambda_ = clock_lambda; }
  void set_reset_interrupt_lambda(std::function<void(void)> &&reset_lambda) { reset_lambda_ = reset_lambda; }
  // void setup() override { this->store_.setup(this->pin_, this->reset_pin_); }
  void setup() override { this->store_.setup(this->pin_, this->reset_pin_, this->clock_lambda_, this->reset_lambda_); }
  void update() override;
  float get_setup_priority() const override { return setup_priority::DATA; }
  void dump_config() override;
  
 protected:
  DecadeCounterSensorStore store_;
  InternalGPIOPin *pin_{nullptr};
  InternalGPIOPin *reset_pin_{nullptr};
  std::function<void(int32_t)> clock_lambda_{nullptr};
  std::function<void(void)> reset_lambda_{nullptr};
};

}  // namespace decade_counter
}  // namespace esphome