cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ---------------------------------------------------------

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ---------------------------------------------------------

set(QtFindReplaceDialog_SHARED_HEADERS
	"finddialog.h"
	"findform.h"
	"findreplacedialog.h"
	"findreplaceform.h"
	"findreplace_global.h"
)

set(QtFindReplaceDialog_SOURCES
	"finddialog.cpp"
	"findform.cpp"
	"findreplacedialog.cpp"
	"findreplacedialog.ui"
	"findreplaceform.cpp"
	"findreplaceform.ui"
	${QtFindReplaceDialog_SHARED_HEADERS}
)

if(WIN32)
	set(MY_COMPILE_OPTIONS "/W3")
else()
	set(MY_COMPILE_OPTIONS "-Wall")
endif()

# ---------------------------------------------------------

add_library(QtFindReplaceDialog STATIC ${QtFindReplaceDialog_SOURCES})
set_target_properties(QtFindReplaceDialog PROPERTIES PUBLIC_HEADER "${QtFindReplaceDialog_SHARED_HEADERS}")
target_compile_definitions(QtFindReplaceDialog PUBLIC "-DFINDREPLACESHARED_EXPORT=")
target_compile_definitions(QtFindReplaceDialog PRIVATE "-DFINDREPLACE_LIBRARY")
target_compile_options(QtFindReplaceDialog PUBLIC ${MY_COMPILE_OPTIONS})
target_link_libraries(QtFindReplaceDialog
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(QtFindReplaceDialog SYSTEM INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<INSTALL_INTERFACE:QtFindReplaceDialog/include>  # <prefix>/QtFindReplaceDialog/include
)

install(TARGETS QtFindReplaceDialog
			EXPORT QtFindReplaceDialog
			ARCHIVE DESTINATION "QtFindReplaceDialog/lib"
			PUBLIC_HEADER DESTINATION "QtFindReplaceDialog/include"
)
install(EXPORT QtFindReplaceDialog DESTINATION QtFindReplaceDialog/cmake)
