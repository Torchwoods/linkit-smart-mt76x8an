include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mtk-mt76x8-linkwatch
PKG_VERSION:=2016-02-17
PKG_RELEASE=1

include $(INCLUDE_DIR)/package.mk

define Package/mtk-mt76x8-linkwatch
  SECTION:=YunYinIot
  CATEGORY:=YunYinIot
  TITLE:=mtk-mt76x8-linkwatch
endef

define Build/Configure
endef

define Package/mtk-mt76x8-linkwatch/description
	Manual link dhcp link updater for bridged wan
endef

define Build/Compile
        true
endef

define Package/mtk-mt76x8-linkwatch/install
	$(INSTALL_DIR) $(1)/usr/sbin/
	$(INSTALL_BIN) ./files/linkwatch $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/linkwatch.init $(1)/etc/init.d/linkwatch
endef

$(eval $(call BuildPackage,mtk-mt76x8-linkwatch))
