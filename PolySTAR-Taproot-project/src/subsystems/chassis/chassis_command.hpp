#ifndef CHASSIS_COMMAND_HPP
#define CHASSIS_COMMAND_HPP

#include <memory>

#include "tap/control/command.hpp"

#include "chassis_subsystem.hpp"
#include "control/drivers/drivers.hpp"

namespace control {

namespace chassis {

namespace strategies {
    class InitializeStrategie;
    class InputStrategie;
    class MovementStrategie;
    class EndStrategie;
}

struct InputData {
    float x;
    float y;
    float r;
};

struct CommandData {
    src::Drivers* drivers;
    const ChassisSubsystem* chassis;
    const char* name;
};

struct CommandProperties {
    CommandData commandData;
    std::unique_ptr<strategies::InitializeStrategie> initializeStrategie;
    std::unique_ptr<strategies::InputStrategie> inputStrategie;
    std::unique_ptr<strategies::MovementStrategie> movementStrategie;
    std::unique_ptr<strategies::EndStrategie> endStrategie;
};

class ChassisCommand : public tap::control::Command 
{
public:
    ChassisCommand( CommandProperties&& commandProperties );
    ~ChassisCommand() = default;

    ChassisCommand( const ChassisCommand& other ) = delete;

    ChassisCommand& operator=( const ChassisCommand& other ) = delete;

    void initialize() override;

    const char *getName() const override;

    void execute() override;

    void end( bool interrupted ) override;

    bool isFinished() const override;

private:
    InputData handleInput();

    void move( const InputData& inputData );
    
private:
    CommandProperties commandProperties_;
};

}

}


#endif