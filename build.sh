#!/bin/bash

BIN_DIR="bin"
TESTS_DIR="tests"
SOURCE_FILES="bethyw.cpp input.cpp areas.cpp area.cpp measure.cpp"
MAIN_FILE="main.cpp"
EXECUTABLE="./${BIN_DIR}/bethyw"

set -x
cd "${0%/*}"

if [ $# -gt 1 ]; then
  echo "Unknown arguments!" "Only one argument accepted, and must begin with test"
  exit
elif [ $# -eq 1 ]; then
  if [[ $1 == test* ]]; then
    SOURCE_FILES="${SOURCE_FILES} ./${TESTS_DIR}/$1.cpp"
    MAIN_FILE="./${BIN_DIR}/catch.o"
    EXECUTABLE="./${BIN_DIR}/bethyw-test"

    # Do we need to compile Catch2?
    if [ ! -f ./${BIN_DIR}/catch.o ]; then
      g++ --std=c++11 -c ./lib_catch_main.cpp -o ./${BIN_DIR}/catch.o
    fi
  fi
fi

mkdir -p ${BIN_DIR}
rm ${EXECUTABLE} 2> /dev/null
g++ --std=c++14 -pedantic -Wall ${SOURCE_FILES} ${MAIN_FILE} -o ${EXECUTABLE}