package org.yaz4j;

import org.yaz4j.jni.SWIGTYPE_p_ZOOM_options_p;
import org.yaz4j.jni.SWIGTYPE_p_ZOOM_package_p;
import org.yaz4j.jni.yaz4jlib;

public class ConnectionExtended extends Connection {

  public ConnectionExtended(String host, int port) {
    super(host, port);
  }

  public Package getPackage(String type) {
    if (closed) {
      throw new IllegalStateException("Connection is closed.");
    }
    Package pack = null;
    SWIGTYPE_p_ZOOM_options_p options = yaz4jlib.ZOOM_options_create();
    SWIGTYPE_p_ZOOM_package_p yazPackage = yaz4jlib.ZOOM_connection_package(
      zoomConnection, options);
    pack = new Package(yazPackage, this, type);
    return pack;
  }
}
