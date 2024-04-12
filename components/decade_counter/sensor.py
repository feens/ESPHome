import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import sensor
from esphome.const import (
    CONF_PIN,
    ICON_PULSE,
    STATE_CLASS_MEASUREMENT,
)
from esphome.core import CORE

decade_counter_ns = cg.esphome_ns.namespace("decade_counter")
DecadeCounterSensor = decade_counter_ns.class_(
    "DecadeCounterSensor", sensor.Sensor, cg.PollingComponent
)

def validate_pin(value):
    value = pins.internal_gpio_input_pin_schema(value)
    return value

CONF_RESET_PIN = 'reset_pin'
CONF_CLOCK_LAMBDA = 'clock_lambda'
CONF_RESET_LAMBDA = 'reset_lambda'

CONFIG_SCHEMA = cv.All(
    sensor.sensor_schema(
        DecadeCounterSensor,
        icon=ICON_PULSE,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(
        {
            cv.Required(CONF_PIN) : validate_pin,
            cv.Required(CONF_RESET_PIN) : validate_pin,
            cv.Optional(CONF_CLOCK_LAMBDA) : cv.returning_lambda,
            cv.Optional(CONF_RESET_LAMBDA) : cv.returning_lambda,
        },
    )
    .extend(cv.polling_component_schema("60s")),
)



async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)

    pin = await cg.gpio_pin_expression(config[CONF_PIN])
    cg.add(var.set_pin(pin))

    reset_pin = await cg.gpio_pin_expression(config[CONF_RESET_PIN])
    cg.add(var.set_reset_pin(reset_pin))

    if CONF_CLOCK_LAMBDA in config:
        clock_lambda = await cg.process_lambda(
                    config[CONF_CLOCK_LAMBDA],
                    [(int, "clock_count")],
                    return_type=cg.void,
                )
        cg.add(var.set_clock_interrupt_lambda(clock_lambda))
    
    if CONF_RESET_LAMBDA in config:
        reset_lambda = await cg.process_lambda(
                    config[CONF_RESET_LAMBDA],
                    [],
                    return_type=cg.void,
                )
        cg.add(var.set_reset_interrupt_lambda(reset_lambda))