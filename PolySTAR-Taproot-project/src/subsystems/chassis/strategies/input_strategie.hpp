#ifndef INPUT_STRATEGIE_HPP
#define INPUT_STRATEGIE_HPP

#include "../chassis_command.hpp"

namespace control {

namespace chassis {

namespace strategies {

class InputStrategie
{
public:
    virtual ~InputStrategie() = default;

    virtual InputData handleInput( const CommandData& commandData ) = 0;
};

}

}

}

#endif