#ifndef __AGENT__H
#define __AGENT__H

#include <string>
#include <math.h>
#include "enviro.h"
#include <iostream>

namespace
{
    using namespace enviro;

    class WandererController : public Process, public AgentInterface
    {
    public:
        WandererController() : Process(), AgentInterface(), 
                               UP(false), DOWN(false), LEFT(false), RIGHT(false),
                               MANUAL_MODE(false) {}

        void init() override {
            // Set up keyboard event handlers using safer try/catch approach
            watch("keydown", [&](Event& e) {
                try {
                    std::string k = e.value()["key"];
                    if (k == "ArrowUp") {
                        UP = true;
                    } else if (k == "ArrowDown") {
                        DOWN = true;
                    } else if (k == "ArrowLeft") {
                        LEFT = true;
                    } else if (k == "ArrowRight") {
                        RIGHT = true;
                    } else if (k == "m") {
                        MANUAL_MODE = true;
                        std::cout << "Entering manual control mode\n";
                        std::cout << "Use Arrow keys to control the agent\n";
                    } else if (k == "q") {
                        MANUAL_MODE = false;
                        std::cout << "Returning to autonomous mode\n";
                    }
                } catch (const std::exception& ex) {
                    // If we catch an exception, try to handle the event as a simple string
                    try {
                        std::string k = e.value();
                        if (k == "ArrowUp") {
                            UP = true;
                        } else if (k == "ArrowDown") {
                            DOWN = true;
                        } else if (k == "ArrowLeft") {
                            LEFT = true;
                        } else if (k == "ArrowRight") {
                            RIGHT = true;
                        } else if (k == "m") {
                            MANUAL_MODE = true;
                            std::cout << "Entering manual control mode\n";
                            std::cout << "Use Arrow keys to control the agent\n";
                        } else if (k == "q") {
                            MANUAL_MODE = false;
                            std::cout << "Returning to autonomous mode\n";
                        }
                    } catch (...) {
                        // Failed to process the event, silently ignore
                    }
                }
            });

            watch("keyup", [&](Event& e) {
                try {
                    std::string k = e.value()["key"];
                    if (k == "ArrowUp") {
                        UP = false;
                    } else if (k == "ArrowDown") {
                        DOWN = false;
                    } else if (k == "ArrowLeft") {
                        LEFT = false;
                    } else if (k == "ArrowRight") {
                        RIGHT = false;
                    }
                } catch (const std::exception& ex) {
                    // If we catch an exception, try to handle the event as a simple string
                    try {
                        std::string k = e.value();
                        if (k == "ArrowUp") {
                            UP = false;
                        } else if (k == "ArrowDown") {
                            DOWN = false;
                        } else if (k == "ArrowLeft") {
                            LEFT = false;
                        } else if (k == "ArrowRight") {
                            RIGHT = false;
                        }
                    } catch (...) {
                        // Failed to process the event, silently ignore
                    }
                }
            });
        }

        void start() {}

        void update() {
            if (MANUAL_MODE) {
                // Manual control mode
                handleManualControl();
            } else {
                // Autonomous mode
                handleAutonomousMovement();
            }
        }

        void stop() {}

    private:
        // Control flags
        bool UP, DOWN, LEFT, RIGHT, MANUAL_MODE;

        // Constants
        const double FORWARD_SPEED = 10.0;
        const double BACKWARD_SPEED = -5.0;
        const double ROTATION_RATE = 10.0;
        const double OBSTACLE_THRESHOLD = 50.0;

        void handleManualControl() {
            double forward_speed = 0;
            double rotation_rate = 0;

            // Set movement based on arrow key presses
            if (UP) {
                forward_speed = FORWARD_SPEED;
            } else if (DOWN) {
                forward_speed = BACKWARD_SPEED;
            }

            if (LEFT) {
                rotation_rate = ROTATION_RATE;
            } else if (RIGHT) {
                rotation_rate = -ROTATION_RATE;
            }

            // Prevent collision with obstacles
            if (sensor_value(0) < OBSTACLE_THRESHOLD && forward_speed > 0) {
                // Too close to obstacle while moving forward, stop
                forward_speed = 0;
                std::cout << "Obstacle detected - preventing collision\n";
            }

            // Apply movement
            track_velocity(forward_speed, rotation_rate);
        }

        void handleAutonomousMovement() {
            // Autonomous movement logic
            // Check for obstacles to rotate
            if (sensor_value(0) < OBSTACLE_THRESHOLD) {
                // Turn to avoid obstacle
                double turn_direction = (rand() % 2 == 0) ? ROTATION_RATE : -ROTATION_RATE;
                track_velocity(0, turn_direction);
            } else {
                // Move forward when clear
                track_velocity(FORWARD_SPEED, 0);
            }

            // Check for red block using sensor values
            if (sensor_value(0) < OBSTACLE_THRESHOLD && sensor_reflection_type(0) == "red") {
                std::cout << "Red block detected! Stopping...\n";
                track_velocity(0, 0);
            }
        }
    };

    class Wanderer : public Agent
    {
    public:
        Wanderer(json spec, World &world) : Agent(spec, world)
        {
            add_process(controller);
        }

        WandererController controller;
    };

    DECLARE_INTERFACE(Wanderer);
}

#endif