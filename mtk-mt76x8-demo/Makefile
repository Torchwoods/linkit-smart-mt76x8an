include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk

PKG_NAME:=mtk-mt76x8-demo
PKG_VERSION:=1.0

define Package/mtk-mt76x8-demo
	SECTION:=YunYinIot
	CATEGORY:=YunYinIot
	#DEPENDS:= 如果需要依赖其他软件包，在这里添加
	TITLE:=package demo
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

define Package/mtk-mt76x8-demo/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/helloOpenWrt $(1)/bin/
endef

define Package/mtk-mt76x8-demo/preinst
	#!/bin/sh
	echo 'before install $(PKG_NAME)'
endef

$(eval $(call BuildPackage,mtk-mt76x8-demo))

