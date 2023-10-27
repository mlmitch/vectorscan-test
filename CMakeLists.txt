cmake_minimum_required(VERSION 3.21)

include(FetchContent)

project(test C CXX)

FetchContent_Declare(BOOST
  URL https://boostorg.jfrog.io/artifactory/main/release/1.83.0/source/boost_1_83_0.tar.gz
  URL_HASH SHA512=231acce3021ef790ee0355e620faf375439c3f2ece0facac681acfc7be60a792c8404bd8c5920cd68c0d9dbcf8b8ac923afdd8d6e8f653306eef974b070e4490
)
FetchContent_MakeAvailable(BOOST)
set(BOOST_ROOT ${boost_SOURCE_DIR}) 

FetchContent_Declare(HYPERSCAN
    URL https://github.com/VectorCamp/vectorscan/archive/refs/tags/vectorscan/5.4.10.1.zip
    URL_HASH SHA512=f784b3b8e3cddc5b488d977a6f76e803a9251cc2716f712cd2e182c15e2468f320b7f74877900d535899dce29237c1ab473f13a957f072fafccdf67b76b3e519
)
FetchContent_MakeAvailable(HYPERSCAN)
include_directories(${hyperscan_SOURCE_DIR}/src)

set (CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} test.cpp)
target_link_libraries(${PROJECT_NAME} hs)
