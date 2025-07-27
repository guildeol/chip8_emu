include(FetchContent)

FetchContent_Declare(
  sdl
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(sdl)
