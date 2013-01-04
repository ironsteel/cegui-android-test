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
        
        

LOCAL_LDFLAGS	:= -Wl,-start-group

LOCAL_CFLAGS := -DDEBUG 


LOCAL_LDLIBS    := -L$(CEGUI_ROOT)/dependencies/lib/$(TARGET_ARCH_ABI) 
LOCAL_LDLIBS    += -L$(CEGUI_ROOT)/systemlibs/$(TARGET_ARCH_ABI) 
LOCAL_LDLIBS    += -L$(CEGUI_ROOT)/lib 
LOCAL_LDLIBS    += -llog -landroid -lEGL -lGLESv1_CM 
LOCAL_LDLIBS    += -lCEGUIOpenGLESRenderer_Static -lCEGUIBase_Static -lCEGUICoreWindowRendererSet_Static -lCEGUICommonDialogs_Static -lCEGUITinyXMLParser_Static -lCEGUIFreeImageImageCodec_Static 
LOCAL_LDLIBS    += -ltinyxml -lfreetype -lFreeImage -lgnustl_static 

LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_STATIC_LIBRARIES := android_native_app_glue 

LOCAL_SHARED_LIBRARIES := iconv

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,cegui-android-libs/iconv)
