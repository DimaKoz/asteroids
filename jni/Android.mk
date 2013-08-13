LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LS_CPP=$(subst $(1)/,,$(wildcard $(1)/*.cpp))
#LOCAL_CFLAGS    := -DRAPIDXML_NO_EXCEPTIONS
LOCAL_CFLAGS 	:= -fexceptions
LOCAL_CFLAGS 	+= -D GL_GLEXT_PROTOTYPES
LOCAL_CFLAGS	+= -std=c++11
LOCAL_CFLAGS 	+= -D __GXX_EXPERIMENTAL_CXX0X__
#флаг INPUTSERVICE_LOG_EVENTS - добавляет в лог события нажатий
#LOCAL_CFLAGS 	+= -D INPUTSERVICE_LOG_EVENTS
#флаг _USE_EXTENDED_LOG_SHOT - добавляет в лог некоторые параметры SHOT
#LOCAL_CFLAGS 	+= -D _USE_EXTENDED_LOG_SHOT
#флаг _USE_EXTENDED_LOG_DEBRIS - добавляет в лог некоторые параметры DEBRIS
#LOCAL_CFLAGS 	+= -D _USE_EXTENDED_LOG_DEBRIS
#флаг _USE_EXTENDED_LOG_COLLIDER - добавляет в лог некоторые параметры COLLIDER
#LOCAL_CFLAGS 	+= -D _USE_EXTENDED_LOG_COLLIDER
#флаг _USE_EXTENDED_LOG_SHIP - добавляет в лог некоторые параметры SHIP
#LOCAL_CFLAGS 	+= -D _USE_EXTENDED_LOG_SHIP
LOCAL_MODULE    := asteroids
LOCAL_SRC_FILES := $(call LS_CPP,$(LOCAL_PATH))
LOCAL_LDLIBS    := -landroid -llog -lEGL -lGLESv1_CM -lOpenSLES

LOCAL_STATIC_LIBRARIES := android_native_app_glue png

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
$(call import-module,libpng)