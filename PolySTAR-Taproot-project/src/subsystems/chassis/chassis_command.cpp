// #include "chassis_command.hpp"

// #include <utility>

// #include "strategies/end_strategie.hpp"
// #include "strategies/initialize_strategie.hpp"
// #include "strategies/input_strategie.hpp"
// #include "strategies/movement_strategie.hpp"

// namespace control {

// namespace chassis {

// ChassisCommand::ChassisCommand( CommandProperties&& commandProperties )
//     : commandProperties_( std::move(commandProperties) )
// {

// }

// void ChassisCommand::initialize() {
//     if ( commandProperties_.initializeStrategie == nullptr ) {
//         return;
//     }
//     commandProperties_.initializeStrategie->initialize( commandProperties_.commandData );
// }

// const char* ChassisCommand::getName() const {
//     return commandProperties_.commandData.name;
// }

// void ChassisCommand::execute() {
//     const InputData inputData = handleInput();
//     move( inputData );
// }

// InputData ChassisCommand::handleInput() {
//     if ( commandProperties_.inputStrategie == nullptr ) {
//         return { 0, 0, 0 };
//     }
//     return commandProperties_.inputStrategie->handleInput( commandProperties_.commandData );
// }

// void ChassisCommand::move( const InputData& inputData ) {
//     if ( commandProperties_.movementStrategie == nullptr ) {
//         return;
//     }
//     commandProperties_.movementStrategie->move( inputData, commandProperties_.commandData );
// }

// void ChassisCommand::end( bool interrupted ) {
//     if ( commandProperties_.endStrategie == nullptr ) {
//         return;
//     }
//     commandProperties_.endStrategie->end( interrupted, commandProperties_.commandData );
// }

// bool ChassisCommand::isFinished() const {
//     return false;
// }

// }

// }
