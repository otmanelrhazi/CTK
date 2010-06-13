#
# DCMTK
#

SET(DCMTK_DEPENDS)
ctkMacroShouldAddExternalProject(DCMTK_LIBRARIES add_project)
IF(${add_project})
  
  # Sanity checks
  IF(DEFINED DCMTK_DIR AND NOT EXISTS ${DCMTK_DIR})
    MESSAGE(FATAL_ERROR "DCMTK_DIR variable is defined but corresponds to non-existing directory")
  ENDIF()
  
  IF(NOT DEFINED DCMTK_DIR)
    SET(proj DCMTK)
#     MESSAGE(STATUS "Adding project:${proj}")
    SET(DCMTK_DEPENDS ${proj})

    ExternalProject_Add(${proj}
        DOWNLOAD_COMMAND ""
        CMAKE_GENERATOR ${gen}
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Utilities/${proj}
        CMAKE_ARGS
          ${ep_common_args}
          -DDCMTK_BUILD_APPS:BOOL=ON # Build also dmctk tools (movescu, storescp, ...)
        )
    SET(DCMTK_DIR ${ep_install_dir})

    ExternalProject_Add_Step(${proj} force_rebuild
      COMMENT "Force ${proj} re-build"
      DEPENDERS build    # Steps that depend on this step
      ALWAYS 1
      WORKING_DIRECTORY ${ep_build_dir}/${proj}
      )
  ENDIF()
ENDIF()
