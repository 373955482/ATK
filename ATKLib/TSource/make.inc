##
## unit_test/private/skycam_info_test/make.inc
##
## History:
##    2013/09/9 - [hmx] Created file
##
## Copyright (C) 2011-2016, Skylight, Inc.
##
## All rights reserved. No Part of this file may be reproduced, stored
## in a retrieval system, or transmitted, in any form, or by any means,
## electronic, mechanical, photocopying, recording, or otherwise,
## without the prior consent of Skylight, Inc.
##

ifeq ($(BUILD_SKL_ATK), y)


CPU = arm
HTKCC = arm-linux-gnueabihf-gcc
HTKCF = /usr/local/linaro-multilib-2014.06-gcc4.9/bin

LOCAL_PATH	:= $(call my-dir)
AIR_LIB_DIR		= $(FAKEROOT_DIR)/usr/lib
###
include $(CLEAR_VARS)

LOCAL_TARGET	:= TSource
LOCAL_SRCS	:=  $(wildcard $(LOCAL_PATH)/*.cpp) \


LOCAL_CFLAGS	:= -I$(LOCAL_PATH) \
				   -I$(AMB_TOPDIR)/prebuild/third-party/$(AMBARELLA_CPU_ARCH)/alsa-lib/include \
				   -I$(AMB_TOPDIR)/app/utility/ATK/ATKLib \
				   -I$(AMB_TOPDIR)/app/utility/ATK/HTKLib \
                 $(HTKCF) -D'ARCH="$(CPU)"' -I. -DUNIX -DATK\
                 -D_cplusplus -D_XOPEN_SOURCE=500 -D_REENTRANT\
				 $(HTKCF) -D'ARCH="$(CPU)"' -I. -I$(hlib) -I$(alib) -DUNIX -DATK -D_cplusplus -D_XOPEN_SOURCE=500 -D_REENTRANT
				  
LOCAL_LIBS 		= libAHTK.a
LOCAL_LDFLAGS	:= -L$(AMB_TOPDIR)/prebuild/third-party/$(AMBARELLA_CPU_ARCH)/alsa-lib/usr/lib -lasound -lm \
                   -lpthread \
				   -L$(FAKEROOT_DIR)/usr/lib -lAHTK \

include $(BUILD_APP)

.PHONY: $(LOCAL_TARGET)

$(LOCAL_TARGET): PRIVATE_PATH:=$(LOCAL_PATH)
$(LOCAL_TARGET): $(LOCAL_MODULE)
	@mkdir -p $(AIR_LIB_DIR)/
	@cp -dpRf $< $(AIR_LIB_DIR)/
	@echo "Build $@ Done."

$(call add-target-into-build, $(LOCAL_TARGET))

endif

