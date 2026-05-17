cmake_minimum_required(VERSION 3.28)
project(GerenciadordeEstoque C)

set(CMAKE_C_STANDARD 11)

add_executable(GerenciadordeEstoque main.c produto.c log.c menu.c
)
