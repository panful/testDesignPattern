function(BuildTarget path)
    file(GLOB subPaths ${path}/*)

    foreach(subPath ${subPaths})
        get_filename_component(target_name ${subPath} NAME)
        file(GLOB_RECURSE sources ${subPath}/*.cpp ${subPath}/*.h)
        set(target_name "${target_name}")

        # executable
        add_executable(${target_name} ${sources})

        # install
        install(TARGETS ${target_name} RUNTIME DESTINATION .)

    endforeach(subPath ${subPaths})

endfunction(BuildTarget path)
