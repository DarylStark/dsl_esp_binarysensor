#include "dsl_esp_binarysensor.h"

namespace dsl
{
    namespace esp
    {
        namespace components
        {
            BinarySensor::BinarySensor(const std::string &name, uint8_t gpio, bool reg_entities /* = true */, sensor_type type /* = Normal */)
                : Component(name), __gpio(gpio), __type(type), __entities_registered(false)
            {
                if (reg_entities)
                    register_entities();
            }

            BinarySensor::~BinarySensor()
            {
                // Remove all created entities
                // entity_manager::entities.erase(_name + ".sensor.low");
                if (__entities_registered)
                    unregister_entities();
            }

            void BinarySensor::setup()
            {
                // Configure the GPIO
                pinMode(__gpio, __type);
            }

            void BinarySensor::loop()
            {
                if (!__entities_registered)
                    return;

                *__state_entity = digitalRead(__gpio) == LOW;
            }

            void BinarySensor::register_entities()
            {
                if (__entities_registered)
                    return;

                std::stringstream name;
                name << _name << ".sensor_state";
                auto [success, entity] = dsl::entities::register_entity(
                    name.str(),
                    dsl::entities::Entity::make_entity(get_state()));
                __state_entity = &entity;

                __entities_registered = true;
            }

            void BinarySensor::unregister_entities()
            {
                if (!__entities_registered)
                    return;

                std::stringstream name;
                name << _name << ".sensor_state";
                dsl::entities::remove_entity(name.str());

                __entities_registered = false;
            }

            bool BinarySensor::get_state() const
            {
                return digitalRead(__gpio) == LOW;
            }
        }
    };
};