cmake_minimum_required(VERSION 3.10)
project(my_website VERSION 0.1.0)

add_compile_options(
  # -fsanitize=address,undefined
                    -Wall
                    -Wextra
                    -pedantic
                    -Wconversion
                    -Wold-style-cast
                    -Wsign-conversion
                    -Werror=return-type)
# add_link_options(-fsanitize=address,undefined)

add_subdirectory(src)