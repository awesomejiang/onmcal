file(GLOB jsonTranslator_SRC
    "*.cpp"
)

add_executable(jsonTranslator ${jsonTranslator_SRC})

add_custom_target(jsonTranslator_run
    COMMAND jsonTranslator
    DEPENDS jsonTranslator
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)