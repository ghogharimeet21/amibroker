cmake_minimum_required(VERSION 3.0)
set( PROJ_NAME QT )

project( ${PROJ_NAME} )
set(CMAKE_CXX_STANDARD 17)
if( NOT MSVC )
	message( WARNING "${PROJ_NAME} CMake file was created for use with MSVC: build MAY NOT WORK" )
endif()

file(GLOB SRC_C_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.c)
file(GLOB SRC_CPP_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
file(GLOB HEADER_H_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
file(GLOB HEADER_HPP_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.hpp)
file(GLOB RESOURCE_FILES LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.rc)
find_package(Protobuf REQUIRED)
find_package(Boost REQUIRED COMPONENTS random)
find_package(OpenSSL REQUIRED)
find_package(websocketpp REQUIRED)
find_package(fmt CONFIG REQUIRED)
# Generate the Protobuf files
# Include directories
include_directories(${Boost_INCLUDE_DIRS}
${OPENSSL_INCLUDE_DIR} ${Protobuf_INCLUDE_DIRS} ${websocketpp_INCLUDE_DIRS})
add_library( ${PROJ_NAME} SHARED 
	${SRC_C_FILES} ${SRC_CPP_FILES} 
	${HEADER_FILES} ${HEADER_HPP_FILES}
	${RESOURCE_FILES}
	temp_files/MyClass.cpp
)

target_compile_definitions( ${PROJ_NAME} PRIVATE
	_AFXDLL _USRDLL _CRT_SECURE_NO_WARNINGS 
	_WIN32_WINNT=0x0501 WINVER=0x0501
)

target_compile_options( ${PROJ_NAME} PRIVATE /Zc:forScope- )
target_link_libraries(${PROJ_NAME} PRIVATE 
	protobuf::libprotobuf 
	${Boost_LIBRARIES} 
	${OPENSSL_LIBRARIES} 
	websocketpp::websocketpp 
	Boost::random
	fmt::fmt
)
