import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    CONF_ID,
    CONF_POWER,
    DEVICE_CLASS_POWER,
    UNIT_WATT,
    STATE_CLASS_MEASUREMENT
)

DEPENDENCIES = ["uart"]
CONF_POWER_THRESHOLD = 'power_threshold'

cooktop_plug_ns = cg.esphome_ns.namespace("cooktop_plug")
CooktopPlugComponent = cooktop_plug_ns.class_("CooktopPlugComponent", cg.Component, uart.UARTDevice)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(CooktopPlugComponent),
        cv.Required(CONF_POWER_THRESHOLD) : cv.float_range(
            min=0, min_included=False
        ),
        cv.Required(CONF_POWER): sensor.sensor_schema(
            unit_of_measurement=UNIT_WATT,
            accuracy_decimals=1,
            device_class=DEVICE_CLASS_POWER,
            state_class=STATE_CLASS_MEASUREMENT,
        ),
    }
).extend(uart.UART_DEVICE_SCHEMA)
FINAL_VALIDATE_SCHEMA = uart.final_validate_device_schema(
    "cooktop_plug", baud_rate=4800, require_rx=True
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

    if power_config := config.get(CONF_POWER):
      sens = await sensor.new_sensor(power_config)
      cg.add(var.set_power_sensor(sens))

    cg.add(var.set_power_threshold(config[CONF_POWER_THRESHOLD]))

