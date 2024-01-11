# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ../../../components 
        "C:/esp-idf/examples/common_components/protocol_examples_common"
        "C:/esp-who/components/esp-aws-iot/examples/mqtt/tls_mutual_auth/main/mqtt_demo_mutual_auth.c")
add_compile_options(-fdiagnostics-color=always)
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(human_face_detection_lcd)