include(FetchContent)

FetchContent_Declare(
  sfml
  GIT_REPOSITORY https://github.com/SFML/SFML
  GIT_TAG        3.0.1
)

FetchContent_MakeAvailable(sfml)
