file(GLOB suitCal_SRC
    "*.cpp"
)

add_executable(suitCal ${suitCal_SRC})

target_include_directories(suitCal
  PRIVATE ${LIBMONGOCXX_INCLUDE_DIRS}
  include
)

target_link_libraries(suitCal
  PRIVATE ${LIBMONGOCXX_LIBRARIES}
)

target_compile_definitions(suitCal
  PRIVATE ${LIBMONGOCXX_DEFINITIONS}
)

add_custom_target(suitCal_run
    COMMAND suitCal
    DEPENDS suitCal
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)