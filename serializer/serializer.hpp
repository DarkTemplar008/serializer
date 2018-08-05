#ifndef SERIALIZER_SERIALIZER_HPP
#define SERIALIZER_SERIALIZER_HPP

#include "config.h"

#include <string>
#include <vector>

#define SERIALIZER_SPACE_BEGIN namespace serializer {
#define SERIALIZER_SPACE_END }

#if ENABLE_QJSON_SERIALIZER
#   include "qjson/serializer.hpp"
#endif

#if ENABLE_JSONCPP_SERIALIZER
#   include "jsoncpp/serializer.hpp"
#endif

#if ENABLE_RAPIDJSON_SERIALIZER
#   include "rapidjson/serializer.hpp"
#endif

#endif
