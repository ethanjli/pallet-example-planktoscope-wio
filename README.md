# pallet-example-planktoscope-wio
A Forklift pallet demo with a software add-on to the PlanktoScope's standard pallet, for an
additional hardware module.

## Introduction

pallet-example-planktoscope-wio is a
[Forklift](https://github.com/ethanjli/pallet-example-planktoscope-wio) pallet which adds an add-on
to [github.com/PlanktoScope/pallet-standard](https://github.com/PlanktoScope/pallet-standard); the
add-on listens for MQTT messages over the PlanktoScope API and sends text to `/dev/ttyACM0`,
which ideally should be a USB device that receives and prints serial data.

Currently, this pallet is a fork of PlanktoScope/pallet-standard; in the future, once
Forklift implements functionality for layering of pallets, this pallet will be layered over
PlanktoScope/pallet-standard

## Usage

### Prerequisites

You will need to run this pallet on a PlanktoScope running the v2024.0.0-beta.0 version of
the PlanktoScope OS, or a later version.

### Deployment

Run:

```
forklift plt switch github.com/ethanjli/pallet-example-planktoscope-wio@main
```

Then reboot your PlanktoScope.

This pallet will cause your PlanktoScope to also run a program which writes text to `/dev/ttyACM0`.
If you plug in a [Wio Terminal](https://www.seeedstudio.com/Wio-Terminal-p-4509.html) running the
Arduino sketch in the `wio-firmware` subdirectory, then each time you use the Node-RED dashboard to
start or stop the pump, the Wio Terminal should print a message indicating the action you took.

### Forking

To make your own copy of this repository for experimentation, you should fork this repository to a
new repository. Then, update the `path` fields of the `forklift-pallet.yml` and
`forklift-repository.yml` files to match the path of your new repository.

## Licensing

Forklift packages deployed by this pallet have their own software licenses, as specified in the
definitions of those packages. Any source code provided with this Forklift pallet is covered by the
following information, except where otherwise indicated:

Copyright Ethan Li and Forklift project contributors

SPDX-License-Identifier: Apache-2.0 OR BlueOak-1.0.0

You can use the source code provided here either under the
[Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0)
or under the [Blue Oak Model License 1.0.0](https://blueoakcouncil.org/license/1.0.0);
you get to decide. We are making the software available under the Apache license because it's
[OSI-approved](https://writing.kemitchell.com/2019/05/05/Rely-on-OSI.html),
but we like the Blue Oak Model License more because it's easier to read and understand.
