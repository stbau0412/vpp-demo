# Copyright (c) 2018 Cisco and/or its affiliates.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

##############################################################################
# find and add all plugin subdirs
##############################################################################
FILE(GLOB files RELATIVE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/*/CMakeLists.txt
)

set(VPP_EXCLUDED_PLUGINS
  ""
  CACHE
  STRING "Comma-separated list of core plugins excluded from packaging and tests"
)

# create the list of the plugins that we need to exclude from packaging
SET(excluded_plugins "")
STRING(REGEX REPLACE "[,]+" ";" exc_plugins "${VPP_EXCLUDED_PLUGINS}")
foreach (e ${exc_plugins})
  message(WARNING "Excluding plugin due to VPP_EXCLUDED_PLUGINS: '${e}'")
  list(APPEND excluded_plugins ${e})
endforeach()

foreach (f ${files})
  get_filename_component(dir ${f} DIRECTORY)

  # if a plugin is in the list of excluded plugin, do not add that subdirectory
  LIST(FIND excluded_plugins "${dir}" exc_index)
  if(${exc_index} EQUAL "-1")
    add_subdirectory(${dir})
  endif()
endforeach()
