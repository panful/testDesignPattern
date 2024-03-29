function(BuildTarget path)
    file(GLOB subPaths ${path}/*)
    foreach(subPath ${subPaths})
        string(REGEX MATCH "([^/]+)/([0-9]+)_([^/]+)$" match_result ${subPath})
        if(match_result)
            file(GLOB __subPath ${subPath}/*)
            foreach(subProj ${__subPath})
                get_filename_component(target_name ${subProj} NAME)
                file(GLOB_RECURSE target_sources ${subProj}/*.cpp ${subProj}/*.h)
                if(target_sources)
                    set(target_name ${CMAKE_MATCH_2}_${target_name})
                    add_executable(${target_name} ${target_sources})
                    install(TARGETS ${target_name} RUNTIME DESTINATION .)
                endif(target_sources)
            endforeach(subProj ${__subPath})
        endif(match_result)
    endforeach(subPath ${subPaths})
endfunction(BuildTarget path)
