include(FetchContent)
FetchContent_Declare(
    libhid
    GIT_REPOSITORY    https://github.com/tlxxzj/libhid.git
    GIT_TAG           master
)
FetchContent_MakeAvailable(libhid)
