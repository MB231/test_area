script_folder="/home/mbarneko/currentWorking/test_area/cmake_builds/nlohmann_conan_test/build/build/Release/generators"
echo "echo Restoring environment" > "$script_folder/../../../build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
for v in 
do
    is_defined="true"
    value=$(printenv $v) || is_defined="" || true
    if [ -n "$value" ] || [ -n "$is_defined" ]
    then
        echo export "$v='$value'" >> "$script_folder/../../../build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
    else
        echo unset $v >> "$script_folder/../../../build/Release/generators/deactivate_conanrunenv-release-x86_64.sh"
    fi
done

