# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "CMakeFiles\\RentalPS_GUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\RentalPS_GUI_autogen.dir\\ParseCache.txt"
  "RentalPS_GUI_autogen"
  )
endif()
