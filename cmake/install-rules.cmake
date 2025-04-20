install(
    TARGETS ray-tracing-one-weekend_exe
    RUNTIME COMPONENT ray-tracing-one-weekend_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
