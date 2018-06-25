/*
 * Copyright (C) Kreogist Dev Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */
#include <QApplication>
#include <QStandardPaths>

#include "knconfigure.h"
#include "knconfiguremanager.h"
#include "kndpimanager.h"
#include "knfontmanager.h"
#include "knthememanager.h"
#include "knutil.h"

#include "knglobal.h"

//Initial the instance pointer to null.
KNGlobal *KNGlobal::m_instance=nullptr;

KNGlobal::~KNGlobal()
{
}

KNGlobal *KNGlobal::instance()
{
    //Return the instance pointer.
    return m_instance;
}

void KNGlobal::initial(QObject *parent)
{
    //Check if the singleton instance variable is null. Set the pointer to this
    //object if this is the first constructed object.
    if(m_instance==nullptr)
    {
        m_instance=new KNGlobal(parent);
    }
}

KNConfigure *KNGlobal::userConfigure()
{
    return knConf->configure(KNConfigureManager::User);
}

KNGlobal::KNGlobal(QObject *parent) : QObject(parent),
    m_globalConfigure(nullptr)
{
    //Initial the managers.
    //Gerenate the configure manager.
    KNConfigureManager::initial(this);
    //Generate the DPI manager.
    KNDpiManager::initial(this);
    //Generate the font manager.
    KNFontManager::initial(this);
    //Generate the theme manager.
    KNThemeManager::initial(this);

    //Initial the infrastructure.
    initialInfrastrcture();
}

inline void KNGlobal::initialDefaultDirPath()
{
    /*
     * Initial the default path of the dirs.
     * Kreogist Dir:
     *     Windows: My documents/Kreogist/
     *    Mac OS X: Documents/Kreogist/
     *       Linux: ~/.kreogist/
     * User Data Dir:
     *     Windows: My documents/Kreogist/Flanker
     *    Mac OS X: Documents/Kreogist/Flanker
     *       Linux: ~/.kreogist/flanker
     * Resource Dir:
     *     Windows: Application path
     *    Mac OS X: Application path/../Resources
     *       Linux: ~/.kreogist/flanker
     */
#ifdef Q_OS_WIN //No matter Win32/Win64
    m_dirPath[KreogistDir]=
            KNUtil::simplifiedPath(QStandardPaths::writableLocation(
                                       QStandardPaths::DocumentsLocation)
                                   +"/Kreogist");
    m_dirPath[UserDataDir]=m_dirPath[KreogistDir]+"/Flanker";
    m_dirPath[ResourceDir]=qApp->applicationDirPath();
#endif
#ifdef Q_OS_MACX
    m_dirPath[KreogistDir]=
                KNUtil::simplifiedPath(QStandardPaths::writableLocation(
                                           QStandardPaths::DocumentsLocation)
                                       +"/Flanker");
    m_dirPath[UserDataDir]=m_dirPath[KreogistDir]+"/Flanker";
    m_dirPath[ResourceDir]=
            KNUtil::simplifiedPath(qApp->applicationDirPath()+"/../Resources");
#endif
#ifdef Q_OS_LINUX
    m_dirPath[KreogistDir]=
            KNUtil::simplifiedPath(QStandardPaths::writableLocation(
                                       QStandardPaths::HomeLocation))
            + "/.kreogist";
    m_dirPath[UserDataDir]=m_dirPath[KreogistDir]+"/flanker";
    m_dirPath[ResourceDir]=m_dirPath[UserDataDir];
#endif
}

inline void KNGlobal::initialInfrastrcture()
{
    //Initial the default path.
    initialDefaultDirPath();

    //Initial the configure manager.
    //Set the configure folder path.
    //-- Q: Why set configure path here?
    //   A: Because we won't change the configure path.
    //Because KNConfigureManager will automatically reload the configure, so we
    //don't need to load the configure here.
    knConf->setFolderPath(m_dirPath[UserDataDir]+"/Configure", "");
    //Get the global configure.
    m_globalConfigure=userConfigure()->getConfigure("Global");

    //Initial the font manager.
    //Set the font resource folder.
    knFont->loadCustomFontFolder(m_dirPath[ResourceDir]+"/Fonts");
    //Set the font configure to the font manager.
    knFont->setConfigure(m_globalConfigure);
    //Set the default font.
    knFont->loadDefaultFont();

    //Initial the theme manager.
    //Load the theme in theme folder. It's familiar with the language folder.
#ifdef Q_OS_LINUX
    knTheme->loadThemeFiles("/usr/share/Kreogist/mu/Theme");
#else
    knTheme->loadThemeFiles(m_dirPath[ResourceDir]+"/Theme");
#endif
    //Load the current theme file.
    //Like the language, we will load theme twice. Default first, user next.
    knTheme->setTheme(0);
    //Load the theme in the configure file.
    knTheme->setTheme(m_globalConfigure->data("Theme").toString());
}
