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

operator server(io String string) {
	String hostname = hostname();
  report("KL: Host Name: " + hostname);
  String hostip = hostip(hostname);
  report("KL: Host Ip: " + hostip);

  Socket server("localhost", 5000, Protocol("TCP"), IPVer("IP4"), 1);

  report("Created socket " + server.socketType().asString() + " from " + server.hostFrom() + ":" + server.portFrom()
        + " " + server.protocol().asString() + " " + server.ipVer().asString() + " blocking: " + server.blocking());

  Socket client();
  report("Client connected: "+client.isValid());
  client = server.accept();
  if (client.isValid())
  {
    report("Connected " + client.socketType().asString()
           + " from " + client.hostFrom() + ":" + client.portFrom()
           + " to " + client.hostTo() + ":" + client.portTo()
           + " " + client.protocol().asString() + " " + client.ipVer().asString() + " blocking: " + client.blocking());
    String message = "";
    while (getLastError() == "")
    {
    	message = client.read();
      if (message != "")
    	 report("KL: Socket server received message from client: " + message);
      if (message == "exit")
        break;
    }
  }
  else
  {
    setError("KL: Server didn't get a client connection");
  }

  server.disconnect();
  string = hostname + " : " + hostip;
  report("KL: Socket server returned: " + string);
  report("KL: Leave entry");
}
"""
op = fabricClient.DG.createOperator("op")
op.setSourceCode(opSource)
op.setEntryPoint("server")

b = fabricClient.DG.createBinding()
b.setOperator(op)
b.setParameterLayout(['self.string'])

node = fabricClient.DG.createNode("node")
node.addMember("string", "String")
node.bindings.append(b)
node.evaluate()
print "Python got: " + node.getData("string", 0)

fabricClient.close()
