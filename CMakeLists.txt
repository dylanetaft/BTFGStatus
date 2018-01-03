cmake_minimum_required(VERSION 2.6)
set(CMAKE_VERBOSE_MAKEFILE ON)
project (BTFGStatus)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

set(Poco_LIB_HINTS
	/usr/local/lib
)
set(Poco_INCLUDE_HINTS
	/usr/local/include/Poco
)

include_directories (
	${BTFGStatus_SOURCE_DIR} 
	/usr/local/include/Poco 
)



set (BIN_DIR ${BTFGStatus_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror=non-virtual-dtor")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")


add_executable(BTFGStatus
main.cpp
)


## Link libraries
find_library(POCO_FOUNDATION PocoFoundation HINTS ${Poco_LIB_HINTS} 
	NO_DEFAULT_PATH
)
find_library(POCO_NET PocoNet HINTS ${Poco_LIB_HINTS} 
	NO_DEFAULT_PATH
)
find_library(POCO_JSON PocoJSONd HINTS ${Poco_LIB_HINTS} 
	NO_DEFAULT_PATH
)
target_link_libraries(BTFGStatus ${POCO_FOUNDATION} ${POCO_NET} ${POCO_JSON})


install(TARGETS BTFGStatus DESTINATION ${BIN_DIR})