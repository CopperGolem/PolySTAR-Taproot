#ifndef CHASSIS_COMMAND_HPP
#define CHASSIS_COMMAND_HPP

#include <functional>
#include <type_traits>

#include "tap/control/command.hpp"

#include "control/drivers/drivers.hpp"

namespace control::chassis
{

// namespace strategies
// {
// class InitializeStrategie;
// class InputStrategie;
// class MovementStrategie;
// class EndStrategie;
// }  // namespace strategies

// struct CommandData
// {
//     src::Drivers* drivers;
//     const ChassisSubsystem* chassis;
//     const char* name;
// };

// struct CommandProperties
// {
//     CommandData commandData;
//     std::unique_ptr<strategies::InitializeStrategie> initializeStrategie;
//     std::unique_ptr<strategies::InputStrategie> inputStrategie;
//     std::unique_ptr<strategies::MovementStrategie> movementStrategie;
//     std::unique_ptr<strategies::EndStrategie> endStrategie;
// };

// class ChassisCommand : public tap::control::Command
// {
// public:
//     ChassisCommand( CommandProperties&& commandProperties );
//     ~ChassisCommand() = default;

//     ChassisCommand( const ChassisCommand& other ) = delete;

//     ChassisCommand& operator=( const ChassisCommand& other ) = delete;

//     void initialize() override;

//     const char *getName() const override;

//     void execute() override;

//     void end( bool interrupted ) override;

//     bool isFinished() const override;

// private:
//     InputData handleInput();

//     void move( const InputData& inputData );

// private:
//     CommandProperties commandProperties_;
// };

template <typename Subsystem>
struct CommandData
{
    src::Drivers* drivers;
    Subsystem* const chassis;
    const char* name;
};

struct InputData
{
    float x;
    float y;
    float r;
};

template <typename T, typename Subsystem>
concept InitializeStrategy = requires(T t, CommandData<Subsystem>& data) {
    { t.initialize(data) } -> std::same_as<void>;
};

template <typename T, typename Subsystem>
concept InputStrategy = requires(T t, CommandData<Subsystem>& data) {
    { t.getInput(data) } -> std::same_as<InputData>;
};

template <typename T, typename Subsystem>
concept ExecutionStrategy =
    requires(T t, CommandData<Subsystem>& data, const InputData& input, bool b) {
        { t.execute(input) } -> std::same_as<void>;
        { t.end(data, b) } -> std::same_as<void>;
        { t.isFinished() } -> std::same_as<bool>;
    };

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
struct Strategies
{
    Init init;
    Input input;
    Execution execution;
};

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
class ChassisCommand : public tap::control::Command
{
public:
    ChassisCommand(
        CommandData<Subsystem>&& commandData,
        Strategies<Subsystem, Init, Input, Execution> strategies,
        std::function<void(CommandData<Subsystem>&)> constructor = [](CommandData<Subsystem>&) {});
    ~ChassisCommand() override = default;

    ChassisCommand(const ChassisCommand& other) = delete;
    ChassisCommand& operator=(const ChassisCommand& other) = delete;

    void initialize() override;

    const char* getName() const override;

    void execute() override;

    void end(bool interrupted) override;

    bool isFinished() const override;

private:
    InputData handleInput();

    void move(const InputData& inputData);

private:
    Strategies<Subsystem, Init, Input, Execution> strategies_;
    CommandData<Subsystem> commandData_;
};

}  // namespace control::chassis

#include "chassis_command_impl.hpp"

#endif