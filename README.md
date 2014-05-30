FabricSockets
=============

Simple sockets extension for Fabric Engine, based on Netlink Sockets C++ library


building
A scons script is provided, it's a modification of the default Fabric Engine SConscript provided in the EDK.

Currently EDK.h must be modified to build on windows, add # include <winsock2.h> just before # include <windows.h> at line 89.

A static build of netlink sockets (http://sourceforge.net/projects/netlinksockets/) is required
To inform scons where to find the Fabric Engine includes as well as the thirdparty libraries, you need to set the following environment variables:
FABRIC_EDK_DIR: Should point to Fabric Engine's EDK folder.
NETLINK_DIR: Should point to the netLink root folder.

testing
python test.py will test simple hostname and hostip functions

python server.py and client.py test a simple TCP echo server. Start the server on one Fabric Engine instance then the client on another (on the same machine or edit "localhost" in client.y with the server name)

license
The license used for this extensions is the MIT license. You can find it in the root folder of the repository.
