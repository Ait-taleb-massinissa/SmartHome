idf_component_register(SRCS "../Dashboard/log_buffer.c" "../Dashboard/Server.c" "../Synchronisation/EventGroupe.c"  "../Actionneurs/ServoMoteur/Servo.c" "../Synchronisation/Queues.c" "../Dashboard/wifi.c"  "main.c"
                    "../Capteurs/Temperature/TempSensor.c"
                    "../Capteurs/Lumiere/LightSensor.c"
                    "../Capteurs/Eau/WaterSensor.c"
                    "../Capteurs/Moisissure/MoistureSensor.c"
                    "../Capteurs/Gaz/gas_sensor.c"
                    "../Actionneurs/Relais/Relay.c"
                    "../Actionneurs/StepMoteur/StepMotor.c"
                    "../Actionneurs/LED/led.c"
                    "../Capteurs/Mouvement/Mouvement.c"
                    "../Capteurs/rfid/rfid.c"

                    INCLUDE_DIRS ".")
