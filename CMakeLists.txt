#PRIMER: Learn how to implement modularity :)


project(testproj)

add_executable(testrun)

target_sources(testrun PRIVATE src/main.c src/first.c)

target_include_directories(testrun PRIVATE ${PROJECT_SOURCE_DIR}/include)

