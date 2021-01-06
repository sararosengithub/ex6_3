cmake_minimum_required(VERSION 3.17)
project(ex6)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex6 main.cpp anomaly_detection_util.cpp CLI.cpp CLI.h commands.h HybridAnomalyDetector.cpp HybridAnomalyDetector.h minCircle.cpp minCircle.h Server.cpp Server.h SimpleAnomalyDetector.cpp timeseries.cpp timeseries.h MainTrain.cpp)