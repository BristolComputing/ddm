#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(DDM)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
#
MESSAGE( STATUS "Geant4_USE_FILE:         " ${Geant4_USE_FILE} )
include(${Geant4_USE_FILE})

#----------------------------------------------------------------------------
# Set up ROOT
#
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT REQUIRED)
# MESSAGE( STATUS "ROOT_USE_FILE:         " ${ROOT_USE_FILE} )
# include(${ROOT_USE_FILE})
include_directories(${ROOT_INCLUDE_DIR})

#----------------------------------------------------------------------------
# Locate sources and headers for this project
#
include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Generate ROOT dictionary
#
# ROOT_GENERATE_DICTIONARY(G__DDM DDM.h LINKDEF DDMLinkDef.h)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(DDM DDM.cc ${sources} ${headers})
target_link_libraries(DDM ${Geant4_LIBRARIES} )
target_link_libraries(DDM ${ROOT_LIBRARIES} )

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build DDM. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(DDM_SCRIPTS
    DDM.out
    DDM.in
    optPhoton.mac
    gui.mac
    icons.mac
    run.png
    vis.mac
    defaultParameters.txt
    trialParameters.txt
    testProton.mac
    testArgon.mac
    testParticle.mac
    testMuon.mac
    isoArgon.mac
    isoProton.mac
  )

foreach(_script ${DDM_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS DDM DESTINATION bin)

