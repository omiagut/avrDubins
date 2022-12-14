#############################################################################
# Makefile for building: courbesDubins
# Generated by qmake (2.01a) (Qt 4.8.7) on: dim. oct. 9 18:59:42 2022
# Project:  ../courbesDubins/courbesDubins.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile ../courbesDubins/courbesDubins.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I../courbesDubins -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I../courbesDubins -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = ../courbesDubins/main.cpp \
		../courbesDubins/mainwindow.cpp \
		../courbesDubins/courbes/cercle.cpp \
		../courbesDubins/courbes/courbe.cpp \
		../courbesDubins/courbes/parametres.cpp \
		../courbesDubins/vue.cpp \
		../courbesDubins/scene.cpp \
		../courbesDubins/graph.cpp moc_mainwindow.cpp \
		moc_vue.cpp \
		moc_scene.cpp
OBJECTS       = main.o \
		mainwindow.o \
		cercle.o \
		courbe.o \
		parametres.o \
		vue.o \
		scene.o \
		graph.o \
		moc_mainwindow.o \
		moc_vue.o \
		moc_scene.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		../courbesDubins/courbesDubins.pro
QMAKE_TARGET  = courbesDubins
DESTDIR       = 
TARGET        = courbesDubins

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9][^0-9]*\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: ../courbesDubins/courbesDubins.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile ../courbesDubins/courbesDubins.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_phonon.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug -o Makefile ../courbesDubins/courbesDubins.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/courbesDubins1.0.0 || $(MKDIR) .tmp/courbesDubins1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/courbesDubins1.0.0/ && $(COPY_FILE) --parents ../courbesDubins/mainwindow.h ../courbesDubins/courbes/cercle.h ../courbesDubins/courbes/courbe.h ../courbesDubins/courbes/parametres.h ../courbesDubins/vue.h ../courbesDubins/scene.h ../courbesDubins/graph.h .tmp/courbesDubins1.0.0/ && $(COPY_FILE) --parents ../courbesDubins/main.cpp ../courbesDubins/mainwindow.cpp ../courbesDubins/courbes/cercle.cpp ../courbesDubins/courbes/courbe.cpp ../courbesDubins/courbes/parametres.cpp ../courbesDubins/vue.cpp ../courbesDubins/scene.cpp ../courbesDubins/graph.cpp .tmp/courbesDubins1.0.0/ && (cd `dirname .tmp/courbesDubins1.0.0` && $(TAR) courbesDubins1.0.0.tar courbesDubins1.0.0 && $(COMPRESS) courbesDubins1.0.0.tar) && $(MOVE) `dirname .tmp/courbesDubins1.0.0`/courbesDubins1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/courbesDubins1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_vue.cpp moc_scene.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_vue.cpp moc_scene.cpp
moc_mainwindow.cpp: ../courbesDubins/scene.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h \
		../courbesDubins/graph.h \
		../courbesDubins/vue.h \
		../courbesDubins/mainwindow.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../courbesDubins/mainwindow.h -o moc_mainwindow.cpp

moc_vue.cpp: ../courbesDubins/vue.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../courbesDubins/vue.h -o moc_vue.cpp

moc_scene.cpp: ../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h \
		../courbesDubins/graph.h \
		../courbesDubins/scene.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) ../courbesDubins/scene.h -o moc_scene.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: ../courbesDubins/main.cpp ../courbesDubins/mainwindow.h \
		../courbesDubins/scene.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h \
		../courbesDubins/graph.h \
		../courbesDubins/vue.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../courbesDubins/main.cpp

mainwindow.o: ../courbesDubins/mainwindow.cpp ../courbesDubins/mainwindow.h \
		../courbesDubins/scene.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h \
		../courbesDubins/graph.h \
		../courbesDubins/vue.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o ../courbesDubins/mainwindow.cpp

cercle.o: ../courbesDubins/courbes/cercle.cpp ../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/parametres.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o cercle.o ../courbesDubins/courbes/cercle.cpp

courbe.o: ../courbesDubins/courbes/courbe.cpp ../courbesDubins/courbes/courbe.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o courbe.o ../courbesDubins/courbes/courbe.cpp

parametres.o: ../courbesDubins/courbes/parametres.cpp ../courbesDubins/courbes/parametres.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o parametres.o ../courbesDubins/courbes/parametres.cpp

vue.o: ../courbesDubins/vue.cpp ../courbesDubins/vue.h \
		../courbesDubins/courbes/parametres.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o vue.o ../courbesDubins/vue.cpp

scene.o: ../courbesDubins/scene.cpp ../courbesDubins/scene.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h \
		../courbesDubins/graph.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o scene.o ../courbesDubins/scene.cpp

graph.o: ../courbesDubins/graph.cpp ../courbesDubins/graph.h \
		../courbesDubins/courbes/parametres.h \
		../courbesDubins/courbes/cercle.h \
		../courbesDubins/courbes/courbe.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o graph.o ../courbesDubins/graph.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_vue.o: moc_vue.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_vue.o moc_vue.cpp

moc_scene.o: moc_scene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_scene.o moc_scene.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

