# Copyright (C) Kreogist Dev Team
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

# Add Qt modules, the Qt major version should be greater than 5.
QT += core gui widgets

# Enabled C++ 11 configures.
CONFIG += c++11

INCLUDEPATH += \
    src/sdk

SOURCES += \
    src/main.cpp \
    src/sdk/knthememanager.cpp \
    src/sdk/knglobal.cpp \
    src/core/knpluginmanager.cpp \
    src/sdk/knmainwindow.cpp \
    src/sdk/knutil.cpp \
    src/sdk/knconfigure.cpp \
    src/sdk/knconfiguremanager.cpp \
    src/sdk/kntoolbar.cpp \
    src/sdk/kndpimanager.cpp \
    src/sdk/knfontmanager.cpp \
    src/sdk/knmainmenubutton.cpp \
    src/sdk/kntabbar.cpp \
    src/sdk/kntabbutton.cpp \
    src/sdk/knsimplebutton.cpp \
    src/plugins/knlogicmanager/knlogicmanager.cpp \
    src/plugins/knlogicmanager/sdk/knlogicdocumentview.cpp \
    src/plugins/knlogicmanager/sdk/knlogicdocument.cpp \
    src/plugins/knlogicmanager/sdk/knlogicutil.cpp

HEADERS += \
    src/sdk/knthememanager.h \
    src/sdk/knglobal.h \
    src/core/knpluginmanager.h \
    src/sdk/knmainwindow.h \
    src/sdk/knutil.h \
    src/sdk/knconfigure.h \
    src/sdk/knconfiguremanager.h \
    src/sdk/kntoolbar.h \
    src/sdk/kndpimanager.h \
    src/sdk/knfontmanager.h \
    src/sdk/knmainmenubutton.h \
    src/sdk/kntabbar.h \
    src/sdk/kntabbutton.h \
    src/sdk/knsimplebutton.h \
    src/plugins/knlogicmanager/knlogicmanager.h \
    src/sdk/knlogicmanagerbase.h \
    src/plugins/knlogicmanager/sdk/knlogicdocumentview.h \
    src/plugins/knlogicmanager/sdk/knlogicdocument.h \
    src/plugins/knlogicmanager/sdk/knlogicutil.h

RESOURCES += \
    res/resource.qrc

DISTFILES += \
    res/default_theme.json
