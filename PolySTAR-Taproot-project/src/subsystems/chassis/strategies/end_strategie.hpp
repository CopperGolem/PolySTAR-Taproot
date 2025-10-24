#ifndef END_STRATEGIE_HPP
#define END_STRATEGIE_HPP

#include "../chassis_command.hpp"

namespace control {

namespace chassis {

namespace strategies {

class EndStrategie
{
public:
    virtual ~EndStrategie() = default;

    virtual void end( const bool interrupted, const CommandData& commandData ) = 0;
};

}

}

}

#endif