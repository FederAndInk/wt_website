find_package(wt REQUIRED)

add_executable(hello main.cpp)

target_link_libraries(hello PRIVATE Wt::Wt Wt::HTTP)
target_compile_features(hello PRIVATE cxx_std_20)
