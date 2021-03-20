

include $(TOPDIR)/rules.mk

PKG_NAME:=mtk-mt76x8-oled
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7628
#PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/mtk-mt76x8-oled
  SECTION:=YunYinIot
  CATEGORY:=YunYinIot
  TITLE:=mtk-mt76x8-oled
  DEPENDS:= +libpthread +librt +libstdcpp +kmod-i2c-core +kmod-i2c-ralink 
endef

define Package/mtk-mt76x8-oled/description
  ssd1306 i2c oled for mt76x8
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

#TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

#LIBS:=-ltxdevicesdk -lpthread -ldl -lstdc++ -ltxdevicesdk

#MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)" \
	LDFAGS="$(LIBS)"
#define Build/Compile
#		$(call Build/Compile/Default,)
#		$(TARGET_CC) smartlink.c -o smartlink -O0 -g3 -I"./include" -L"./lib" -ltxdevicesdk -lpthread -ldl -lstdc++
#		$(TARGET_CC) $(TARGET_CFLAGS) -Wall -Werror -o $(PKG_BUILD_DIR)/ap_client src/ap_client.c
#endef


define Package/mtk-mt76x8-oled/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/oled $(1)/bin
endef


$(eval $(call BuildPackage,mtk-mt76x8-oled))
