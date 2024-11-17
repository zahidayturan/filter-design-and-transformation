# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Filter_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Filter_autogen.dir\\ParseCache.txt"
  "Filter_autogen"
  )
endif()
