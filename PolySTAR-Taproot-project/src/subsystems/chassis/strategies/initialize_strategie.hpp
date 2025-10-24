#ifndef INITIALIZE_STRATEGIE_HPP
#define INITIALIZE_STRATEGIE_HPP

#include "../chassis_command.hpp"

namespace control {

namespace chassis {

namespace strategies {

class InitializeStrategie
{
public:
    virtual ~InitializeStrategie() = default;

    virtual void initialize( const CommandData& commandData ) = 0;
};

}

}

}

#endif