cmake_minimum_required(VERSION 3.14)

project(ImageClassifierApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2)

qt_add_executable(ImageClassifierApp
    main.cpp
    backend.cpp
    backend.h
)

qt_add_qml_module(ImageClassifierApp
    URI ImageClassifierApp
    QML_FILES Main.qml
    RESOURCES qml.qrc
)

target_link_libraries(ImageClassifierApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::QuickControls2
)
