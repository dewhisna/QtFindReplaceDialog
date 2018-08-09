cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# ---------------------------------------------------------

find_package(Qt5Widgets)

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
add_definitions(
	"-DFINDREPLACESHARED_EXPORT="
)

# ---------------------------------------------------------

add_library(QtFindReplaceDialog STATIC ${QtFindReplaceDialog_SOURCES})
set_target_properties(QtFindReplaceDialog PROPERTIES PUBLIC_HEADER ${QtFindReplaceDialog_SHARED_HEADERS})
target_compile_options(QtFindReplaceDialog PUBLIC "-Wall")
qt5_use_modules(QtFindReplaceDialog Core Widgets)

install(TARGETS QtFindReplaceDialog
			ARCHIVE DESTINATION "lib"
			PUBLIC_HEADER DESTINATION "include"
)
