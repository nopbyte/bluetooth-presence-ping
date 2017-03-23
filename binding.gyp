{
  "targets": [
    {
      "target_name": "addon",
      'libraries': [ '-lbluetooth' ],
      "sources": [ "node_bridge.cpp","ping.c"],
      "defines": [ "SERVER" ]
    }
  ]
}
