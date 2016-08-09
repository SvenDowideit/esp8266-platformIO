# esp8266-platformIO

playing around

## Goal

To have an adhoc mesh of devices that can OTA safely.

So for all supported targets, we need a network, and a way to avoid trusting
other nodes - ie, need to verify all communication payloads that we are going
to use for anything - and drop others fast.

low power waste would be good - ie, turn off network at times - though this would need to be only on leave nodes - and even them they need to be ready to become non-leaves.

if the OTA is done Docker style - we should be able to transmit / request diffs
and those diffs might be "this is only application", or "this is a full OS updates"

that way we can try to reduce the scaryness of an update.

## TODO

1. separate out the esp/wemos specific code.


## interesting links

there seems to be an avahi lib for esp/Arduino
- [1091 ] esp8266_mdns     arduino, espressif    "dunk": mDNS queries and responses on esp8266. Or to describe it another way: An mDNS Client or Bonjour Client library for the esp8266.

so that may be useful in allowing nodes to discover each other, and their cababilities.
