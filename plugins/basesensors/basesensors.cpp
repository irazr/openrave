// Copyright (C) 2006-2008 Rosen Diankov (rdiankov@cs.cmu.edu)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include "plugindefs.h"
#include "baselaser.h"
#include "baseflashlidar3d.h"
#include "basecamera.h"
#include <rave/plugin.h>

static list< boost::shared_ptr<void> > s_listRegisteredReaders;
InterfaceBasePtr CreateInterfaceValidated(InterfaceType type, const std::string& interfacename, std::istream& sinput, EnvironmentBasePtr penv)
{
    if( s_listRegisteredReaders.size() == 0 ) {
        s_listRegisteredReaders.push_back(penv->RegisterXMLReader(PT_Sensor,"baselaser2d",BaseLaser2DSensor::CreateXMLReader));
        s_listRegisteredReaders.push_back(penv->RegisterXMLReader(PT_Sensor,"basespinninglaser2d",BaseSpinningLaser2DSensor::CreateXMLReader));
        s_listRegisteredReaders.push_back(penv->RegisterXMLReader(PT_Sensor,"baseflashlidar3d",BaseFlashLidar3DSensor::CreateXMLReader));
        s_listRegisteredReaders.push_back(penv->RegisterXMLReader(PT_Sensor,"basecamera",BaseCameraSensor::CreateXMLReader));
    }
    switch(type) {
    case PT_Sensor:
        if( interfacename == "baselaser2d" )
            return InterfaceBasePtr(new BaseLaser2DSensor(penv));
        else if( interfacename == "basespinninglaser2d" )
            return InterfaceBasePtr(new BaseSpinningLaser2DSensor(penv));
        else if( interfacename == "baseflashlidar3d" )
            return InterfaceBasePtr(new BaseFlashLidar3DSensor(penv));
        else if( interfacename == "basecamera" )
            return InterfaceBasePtr(new BaseCameraSensor(penv));
        break;
    default:
        break;
    }
    return InterfaceBasePtr();
}

void GetPluginAttributesValidated(PLUGININFO& info)
{
    info.interfacenames[OpenRAVE::PT_Sensor].push_back("BaseLaser2D");
    info.interfacenames[OpenRAVE::PT_Sensor].push_back("BaseSpinningLaser2D");
    info.interfacenames[OpenRAVE::PT_Sensor].push_back("BaseFlashLidar3D");
    info.interfacenames[OpenRAVE::PT_Sensor].push_back("BaseCamera");
}

RAVE_PLUGIN_API void DestroyPlugin()
{
    s_listRegisteredReaders.clear();
}