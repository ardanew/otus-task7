set(TARGET_NAME bulk)
add_executable(${TARGET_NAME} main.cpp 
    iinput.h stdinput.h stdinput.cpp 
    ioutput.h stdoutput.h stdoutput.cpp logoutput.h logoutput.cpp
    icmdprocessor.h cmdprocessor.h cmdprocessor.cpp
    command.h
    basestate.h basestate.cpp limitedstate.h limitedstate.cpp unlimitedstate.h unlimitedstate.cpp
    )
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
install(
    TARGETS ${TARGET_NAME} COMPONENT app
    PERMISSIONS OWNER_WRITE OWNER_READ OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
