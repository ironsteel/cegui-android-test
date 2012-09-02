# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := native-activity
LOCAL_C_INCLUDES := include \
        $(CEGUI_ROOT)/include

LOCAL_SRC_FILES := src/main.cpp \
        src/CEGUIAndroidLogger.cpp        

LOCAL_LDFLAGS	:= -Wl,-start-group


LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv1_CM -lfreetype 

LOCAL_CPP_FEATURES := rtti exceptions

LOCAL_STATIC_LIBRARIES := CEGUIOpenGLESRenderer CEGUIBase  CEGUICoreWindowRendererSet CEGUICommonDialogs CEGUITinyXMLParser CEGUIFreeImageImageCodec android_native_app_glue freeimage

LOCAL_SHARED_LIBRARIES := iconv tinyxml 
include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,cegui-android-libs/cegui-base)
$(call import-module,cegui-android-libs/opengles)
$(call import-module,cegui-android-libs/iconv)
$(call import-module,cegui-android-libs/tinyxml)
$(call import-module,cegui-android-libs/free-image-codec)
$(call import-module,cegui-android-libs/cegui-windows)
$(call import-module,cegui-android-libs/freeimage)
$(call import-module,cegui-android-libs/common-dialogs)
$(call import-module,tinyxml/lib)

