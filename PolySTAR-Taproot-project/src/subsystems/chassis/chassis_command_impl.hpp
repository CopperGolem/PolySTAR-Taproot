#ifndef CHASSIS_COMMAND_IMPL_HPP
#define CHASSIS_COMMAND_IMPL_HPP

#include <utility>

#include "chassis_command.hpp"

namespace control::chassis
{

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
ChassisCommand<Subsystem, Init, Input, Execution>::ChassisCommand(
    CommandData<Subsystem>&& commandData,
    Strategies<Subsystem, Init, Input, Execution> strategies)
    : strategies_{strategies},
      commandData_{std::move(commandData)}
{
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
void ChassisCommand<Subsystem, Init, Input, Execution>::initialize()
{
    strategies_.init.initialize(commandData_);
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
const char* ChassisCommand<Subsystem, Init, Input, Execution>::getName() const
{
    return commandData_.name;
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
void ChassisCommand<Subsystem, Init, Input, Execution>::execute()
{
    const InputData inputData = handleInput();
    move(inputData);
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
void ChassisCommand<Subsystem, Init, Input, Execution>::end(bool interrupted)
{
    strategies_.execution.end(commandData_, interrupted);
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
bool ChassisCommand<Subsystem, Init, Input, Execution>::isFinished() const
{
    return strategies_.execution.isFinished();
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
InputData ChassisCommand<Subsystem, Init, Input, Execution>::handleInput()
{
    return strategies_.input.getInput(commandData_);
}

template <
    typename Subsystem,
    InitializeStrategy<Subsystem> Init,
    InputStrategy<Subsystem> Input,
    ExecutionStrategy<Subsystem> Execution>
void ChassisCommand<Subsystem, Init, Input, Execution>::move(const InputData& inputData)
{
    strategies_.execution.execute(inputData);
}

}  // namespace control::chassis

#endif