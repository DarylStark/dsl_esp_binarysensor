#ifndef __DSL_ESP_BINARY_SENSOR_H__
#define __DSL_ESP_BINARY_SENSOR_H__

#include <Arduino.h>
#include <sstream>
#include <dsl_entity_manager.h>
#include <dsl_esp_component.h>

namespace dsl
{
    namespace esp
    {
        namespace components
        {

            class BinarySensor : public Component
            {
            public:
                enum sensor_type
                {
                    Normal = 1,
                    Pullup = 5,
                    Pulldown = 9
                };

            private:
                uint8_t __gpio;
                sensor_type __type;
                bool __entities_registered;
                dsl::entities::Entity *__state_entity;

            public:
                BinarySensor(const std::string &name, uint8_t gpio, bool reg_entities = true, sensor_type type = Normal);
                ~BinarySensor();

                void setup() override;
                void loop() override;

                void register_entities();
                void unregister_entities();

                bool get_state() const;
            };
        };
    }
};

#endif /* __DSL_ESP_BINARY_SENSOR_H__ */