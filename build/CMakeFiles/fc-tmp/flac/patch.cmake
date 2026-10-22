cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for flac")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/Andrew/dev/cenui/build/_deps/flac-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/Program Files/CMake/bin/cmake.exe]====] [====[-DFLAC_DIR=C:/Users/Andrew/dev/cenui/build/_deps/flac-src]====] [====[-P]====] [====[C:/Users/Andrew/dev/cenui/build/_deps/sfml-src/tools/flac/PatchFLAC.cmake]====]
)

endblock()
