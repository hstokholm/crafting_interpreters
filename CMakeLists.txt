cmake_minimum_required(VERSION 3.18)

# set the project name
project(crafting_interpreters)

# add the executable
add_executable(crafting_interpreters 
  main.cc

  common.h

  chunk.cc
  chunk.h

  debug.cc
  debug.h

  value.cc
  value.h
)

