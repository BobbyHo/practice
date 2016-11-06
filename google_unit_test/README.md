Steps to setup Google Test Framework in my Linux workstation (running Ubtuntu):

1) sudo apt-get install libgtest-dev

2) sudo apt-get install cmake # install cmake
   cd /usr/src/gtest
   sudo cmake CMakeLists.txt
   sudo make
 
   # copy or symlink libgtest.a and libgtest_main.a to your /usr/lib folder
   sudo cp *.a /usr/lib

3) Create TEST functions:
   TEST(FindNumOccurance, General)
{
    // create test arrays
    int arr1[1] = {1};

    EXPECT_EQ(1, find_target_number_occurance(arr1, 0, 0, 1));
    ...//more EXPECT function
}

4) Create CMakeLists.txt:
For example:
  cmake_minimum_required(VERSION 2.6)
 
  #Locate GTest
  find_package(GTest REQUIRED)
  include_directories(${GTEST_INCLUDE_DIRS})
 
  #Link runTests with what we want to test and the GTest and pthread library
  add_executable(runTests recursion.cpp)
  target_link_libraries(runTests ${GTEST_LIBRARIES} pthread

5) Compile and run tests:
- cmake CMakeLists.txt
- The following files should be created after running cmake:
  CMakeCache.txt  CMakeFiles  cmake_install.cmake Makefile
- run "make":
  make

- run the google unit test: 
  ./runTests

