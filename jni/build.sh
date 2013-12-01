#!/bin/bash
# Preserve the old dir
NDK_OLD_MODULE=$NDK_MODULE_PATH

#Let android import module command search also in cegui deps dir 
export NDK_MODULE_PATH=$NDK_MODULE_PATH:$CEGUI_ROOT/dependencies

ndk-build clean
# build
ndk-build -j4  NDK_DEBUG=1 

# Restore the old module path dir
export NDK_MODULE_PATH=$NDK_OLD_MODULE 
