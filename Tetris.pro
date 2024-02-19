TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = \
    Core \
    DesktopApp \

DesktopApp.depends = Core
