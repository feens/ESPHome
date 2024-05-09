#include "esp32_ble_tracker_allowlist.h"
#include "esphome/core/log.h"
#include "esphome/core/application.h"


#ifdef USE_ESP32

// bt_trace.h
#undef TAG

namespace esphome {
namespace esp32_ble_tracker_allowlist {

    static const char *const TAG = "esp32_ble_tracker";

    ESP32BLETrackerAllowlist *global_esp32_ble_tracker = nullptr;  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

    // float ESP32BLETracker::get_setup_priority() const { return setup_priority::AFTER_BLUETOOTH; }


    void ESP32BLETrackerAllowlist::start_scan_(bool first) {
        // if (!this->parent_->is_active()) {
        //     ESP_LOGW(TAG, "Cannot start scan while ESP32BLE is disabled.");
        //     return;
        // }
        // // The lock must be held when calling this function.
        // if (xSemaphoreTake(this->scan_end_lock_, 0L)) {
        //     ESP_LOGE(TAG, "start_scan called without holding scan_end_lock_");
        //     return;
        // }

        // ESP_LOGD(TAG, "Starting scan...");
        // if (!first) {
        //     for (auto *listener : this->listeners_)
        //     listener->on_scan_end();
        // }
        // this->already_discovered_.clear();
        // this->scan_params_.scan_type = this->scan_active_ ? BLE_SCAN_TYPE_ACTIVE : BLE_SCAN_TYPE_PASSIVE;
        // this->scan_params_.own_addr_type = BLE_ADDR_TYPE_PUBLIC;
        // this->scan_params_.scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL;
        // this->scan_params_.scan_interval = this->scan_interval_;
        // this->scan_params_.scan_window = this->scan_window_;

        // esp_err_t err = esp_ble_gap_set_scan_params(&this->scan_params_);
        // if (err != ESP_OK) {
        //     ESP_LOGE(TAG, "esp_ble_gap_set_scan_params failed: %d", err);
        //     return;
        // }
        // err = esp_ble_gap_start_scanning(this->scan_duration_);
        // if (err != ESP_OK) {
        //     ESP_LOGE(TAG, "esp_ble_gap_start_scanning failed: %d", err);
        //     return;
        // }
        // this->scanner_idle_ = false;

        // this->set_timeout("scan", this->scan_duration_ * 2000, []() {
        //     ESP_LOGE(TAG, "ESP-IDF BLE scan never terminated, rebooting to restore BLE stack...");
        //     App.reboot();
        // });

    };

}  // namespace esp32_ble_tracker_allowlist
}  // namespace esphome

#endif