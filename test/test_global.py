# -*- coding: utf-8 -*-
# Copyright (C) 2011 Rosen Diankov <rosen.diankov@gmail.com>
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
from openravepy import *
from numpy import *
from itertools import izip, combinations
import os, shutil
import nose
from common_test_openrave import *

_multiprocess_can_split_ = True

@with_destroy
def test_pluginloading():
    RaveInitialize(load_all_plugins=False)
    assert(RaveLoadPlugin('ikfastsolvers'))
    assert(RaveLoadPlugin('libikfastsolvers'))
    env=Environment()
    assert(RaveCreateProblem(env,'ikfast') is not None)

def test_createplugin():
    curdir = os.getcwd()
    try:
        assert(os.system('openrave-createplugin.py myplugin --problem=MyTestProblem') == 0)
        os.chdir('myplugin')
        os.mkdir('build')
        os.chdir('build')
        assert(os.system('cmake ..') == 0)
        assert(os.system('make') == 0)
        os.chdir('..')
        assert(os.system('python testplugin.py') == 0)
    finally:
        os.chdir(curdir)
        try:
            shutil.rmtree('myplugin')
        except:
            pass
        
    try:
        assert(os.system('openrave-createplugin.py myprogram --usecore') == 0)
        os.chdir('myprogram')
        os.mkdir('build')
        os.chdir('build')
        assert(os.system('cmake ..') == 0)
        assert(os.system('make') == 0)
        os.chdir('..')
        assert(os.system('./build/myprogram') == 0)
    finally:
        os.chdir(curdir)
        shutil.rmtree('myprogram')
        