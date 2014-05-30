#
# Fabric Core 1.11.3
# HelloWorld EDK Sample
#
# Copyright 2010-2014 Fabric Software Inc. All rights reserved.
#

import os
if 'FABRIC_EXTS_PATH' in os.environ:
  os.environ['FABRIC_EXTS_PATH'] = os.pathsep.join(['.', os.environ['FABRIC_EXTS_PATH']])
else:
  os.environ['FABRIC_EXTS_PATH'] = '.'

import FabricEngine.Core as fabric
fabricClient = fabric.createClient();

opSource = """
require Sockets;

operator client(io String string) {
	String hostname = hostname();
  report("KL: Host Name: " + hostname);
  String hostip = hostip(hostname);
  report("KL: Host Ip: " + hostip);

  Socket socket("localhost", 5000, Protocol("TCP"), IPVer("IP4"));
  if (getLastError() == "")
	{
	  String message = "";
	  for (Index i=1; i<10; i+=1)
	  {
	  	message = ("KL client message " + i);
	  	report("KL: Socket client sending: " + message);
	  	socket.send(message);
	  }
		socket.send("exit");
	}
	else
	{
		report("KL: Socket client error: " + getLastError());
	}
	string = hostname + " : " + hostip;
	report("KL: Socket server returned: " + string);
	report("KL: Leave entry");
}
"""
op = fabricClient.DG.createOperator("op")
op.setSourceCode(opSource)
op.setEntryPoint("client")

b = fabricClient.DG.createBinding()
b.setOperator(op)
b.setParameterLayout(['self.string'])

node = fabricClient.DG.createNode("node")
node.addMember("string", "String")
node.bindings.append(b)
node.evaluate()
print "Python got: " + node.getData("string", 0)

fabricClient.close()
