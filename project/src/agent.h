#ifndef __AGENT__H
#define __AGENT__H

#include <string>
#include <math.h>
#include "enviro.h"
#include <iostream>

namespace
{

    using namespace enviro;

    class MovingForward : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            track_velocity(10, 0);
            
            // Check for obstacles to rotate
            if (sensor_value(0) < 40)
            {
                emit(Event(tick_name));
            }
            
            // Check for red block using sensor values
            if (sensor_value(0) < 30 && sensor_color(0) == "red")
            {
                std::cout << "Red block detected! Stopping...\n";
                emit(Event("stop"));
            }
        }
        void exit(const Event &e) {}
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Rotating : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) { rate = rand() % 2 == 0 ? 2 : -2; }
        void during()
        {
            track_velocity(0, rate);
            if (sensor_value(0) > 140)
            {
                emit(Event(tick_name));
            }
        }
        void exit(const Event &e) {}
        double rate;
        void set_tick_name(std::string s) { tick_name = s; }
        std::string tick_name;
    };

    class Stopped : public State, public AgentInterface
    {
    public:
        void entry(const Event &e) {}
        void during()
        {
            track_velocity(0, 0);
        }
        void exit(const Event &e) {}
    };

    class WandererController : public StateMachine, public AgentInterface
    {

    public:
        WandererController() : StateMachine()
        {

            set_initial(moving_forward);
            tick_name = "tick_" + std::to_string(rand() % 1000); // use an agent specific generated
                                                                 // event name in case there are
                                                                 // multiple instances of this class
            add_transition(tick_name, moving_forward, rotating);
            add_transition(tick_name, rotating, moving_forward);
            add_transition("stop", moving_forward, stopped);
            moving_forward.set_tick_name(tick_name);
            rotating.set_tick_name(tick_name);
        }

        MovingForward moving_forward;
        Rotating rotating;
        Stopped stopped;
        std::string tick_name;
    };

    class Wanderer : public Agent
    {

    public:
        Wanderer(json spec, World &world) : Agent(spec, world)
        {
            add_process(wc);
        }

        WandererController wc;
    };

    DECLARE_INTERFACE(Wanderer);

}

#endif