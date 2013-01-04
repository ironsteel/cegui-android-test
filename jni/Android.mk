LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := native-activity
LOCAL_C_INCLUDES := include \
        $(CEGUI_ROOT)/cegui/include

LOCAL_SRC_FILES := src/main.cpp \
        src/CEGUITestApplication.cpp \
        src/GLESApplication.cpp \
        src/CEGUIAndroidLogger.cpp \
        src/AndroidResourceProvider.cpp   
        

LOCAL_CFLAGS    := -DDEBUG 
LOCAL_CFLAGS    += -fexceptions -frtti -D___ANDROID___ -DANDROID 

LOCAL_LDFLAGS	:= -Wl,-start-group
LOCAL_LDLIBS    := -L$(CEGUI_ROOT)/dependencies/lib/$(TARGET_ARCH_ABI) 
LOCAL_LDLIBS    += -L$(CEGUI_ROOT)/android/systemlibs/$(TARGET_ARCH_ABI) 
LOCAL_LDLIBS    += -L$(CEGUI_ROOT)/android/lib 
LOCAL_LDLIBS    += -L$(NDK_ROOT)/sources/cxx-stl/gnu-libstdc++/libs/$(TARGET_ARCH_ABI)
LOCAL_LDLIBS    += -llog -landroid -lEGL -lGLESv1_CM
LOCAL_LDLIBS    += -lCEGUIOpenGLESRenderer_Static -lCEGUIBase_Static -lCEGUICoreWindowRendererSet_Static -lCEGUICommonDialogs_Static -lCEGUITinyXMLParser_Static -lCEGUIFreeImageImageCodec_Static 
LOCAL_LDLIBS    += -ltinyxml -lfreetype -lFreeImage -lgnustl_static



LOCAL_STATIC_LIBRARIES := android_native_app_glue 
LOCAL_SHARED_LIBRARIES := iconv
include $(BUILD_SHARED_LIBRARY)

$(call import-module, iconv-prebuild)
$(call import-module, android/native_app_glue)

