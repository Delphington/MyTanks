cmake_minimum_required(VERSION 3.27)
project(MyTanks)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyTanks main.cpp
        srv/Config.cpp
        model/GameMenu.h
        model/GameMenu.cpp
        item/Player.cpp
        item/Environment.cpp
        srv/CollisionUtils.cpp
        item/Score.cpp
        model/Card.cpp
        item/Bullet.h
        item/Bullet.cpp
        srv/Config.h
)


# Укажите путь к папке с SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR D:/_DELPGINGTON/University/Sem_3/course/SFML/lib/cmake/SFML)


find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(D:/_DELPGINGTON/University/Sem_3/course/SFML/include/SFML)

target_link_libraries(MyTanks sfml-system sfml-window sfml-graphics sfml-audio)