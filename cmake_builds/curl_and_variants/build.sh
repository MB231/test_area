cd build
#cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake .. -G "Unix Makefiles" -DCMAKE_TOOLCHAIN_FILE=/home/mbarneko/currentWorking/test_area/cmake_builds/nlohmann_conan_test/build/build/Release/generators/conan_toolchain.cmake -DCMAKE_POLICY_DEFAULT_CMP0091=NEW -DCMAKE_BUILD_TYPE=Release

cmake --build . && ./test
