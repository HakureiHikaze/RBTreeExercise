cmake_minimum_required(VERSION 3.19)
project(Utilities)
include_directories(../BaseStructure)
add_library(Utilities Utilities.c MT19937.c DrawTree.c StringProducer.c)