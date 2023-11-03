#!/usr/bin/env bash

conan profile detect --force
conan install . --output-folder=build --build=missing
# NOTE do NOT use concanfile.txt just use .

