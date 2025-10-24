#ifndef MOVEMENT_STRATEGIE_HPP
#define MOVEMENT_STRATEGIE_HPP

#include "../chassis_command.hpp"

namespace control {

namespace chassis {

namespace strategies {

class MovementStrategie
{
public:
    virtual ~MovementStrategie() = default;

    virtual void move( const InputData& inputData, const CommandData& commandData ) = 0;
};

}

}

}

#endif