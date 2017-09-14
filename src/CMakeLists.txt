file(GLOB_RECURSE LibIMEWeb_SRCS *.cpp *.h)

set(LibIMEWeb_SRCS
    ${LibIMEWeb_SRCS}
    ${TEMPLATES_SRC}
)

# Create the application
add_library(LibIMEWeb SHARED ${LibIMEWeb_SRCS})

# Link to Cutelyst
target_link_libraries(LibIMEWeb
    Cutelyst::Core
    Cutelyst::StaticSimple
    Cutelyst::View::JSON
    Qt5::Core
    Qt5::Network
    LibIME::Pinyin
)

