cmake_minimum_required(VERSION 3.22)
project(08_Localization)

add_executable(main main.c)

add_custom_target(main.pot DEPENDS main
	COMMAND xgettext --keyword=_ main.c -o main.pot
)

add_custom_target(main.po DEPENDS main.pot
	COMMAND msgmerge -U main.po main.pot
)

add_custom_target(main.mo DEPENDS main.po
	COMMAND mkdir -p ru/LC_MESSAGES/
	COMMAND msgfmt main.po -o ru/LC_MESSAGES/main.mo
)

add_custom_target(clean
	COMMAND rm -rf ru *.pot main CMakeFiles CMakeCache.txt cmake_install.cmake Makefile
)