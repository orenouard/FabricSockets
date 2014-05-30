#
# Fabric Core 1.11.3
# HelloWorld EDK Sample
#
# Copyright 2010-2014 Fabric Software Inc. All rights reserved.
#

import os, sys

try:
  fabricEDKPath = os.environ['FABRIC_EDK_DIR']
except:
  print "You must set FABRIC_EDK_DIR in your environment."
  print "Refer to README.txt for more information."
  sys.exit(1)
SConscript(os.path.join(fabricEDKPath, 'SConscript'))
Import('fabricBuildEnv')
  
try:
  netlinkDir = os.environ['NETLINK_DIR']
except:
  print "You must set $NETLINK_DIR in your environment."
  sys.exit(1)  
  
fabricBuildEnv.Append(CPPPATH = [os.path.join(netlinkDir, 'include')])
fabricBuildEnv.Append(LIBS = ['netLink'], LIBPATH=[os.path.join(netlinkDir, 'lib')])
fabricBuildEnv.Append(LIBS = ['Ws2_32'])

extFiles = []
extFiles += Glob('*.cpp')
extFiles += Glob('*.json')
extFiles += ["IPVer.kl", "Protocol.kl", "SocketType.kl", "Socket.kl", "Sockets.kl"]

fabricBuildEnv.Extension('Sockets', extFiles)
