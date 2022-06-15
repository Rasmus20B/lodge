#pragma once

#include "event.hpp"
#include "outputStream.hpp"

namespace lodge {

outputStream printEntry(std::ofstream out, Event *event);

}
