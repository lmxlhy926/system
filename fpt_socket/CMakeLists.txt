
if (WIN32)
    set (PLATFORM_LIBS Ws2_32 mswsock iphlpapi ntdll)
else (WIN32)
    set (PLATFORM_LIBS pthread ${CMAKE_DL_LIBS})
endif (WIN32)

add_library(fpt_socket fptsocket.cpp)
target_link_libraries(fpt_socket ${PLATFORM_LIBS})