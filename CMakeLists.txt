target_include_directories(app PRIVATE include proto)
target_sources(app PRIVATE src/*.c proto/*.c)