# pallets-env
The standard Pallet environment for the PlanktoScope software distribution

## Introduction

pallet-env is the standard configuration of [Pallet](https://github.com/PlanktoScope/pallets) package deployments for the PlanktoScope software distribution.

## Usage

This Github repository has three release channels, each corresponding to a Git branch: `stable`, `beta`, and `edge`, as well as Git tags for each released version. You should always use either the `stable` branch (recommended so that you will automatically be notified for new stable versions) or a specific Git tag.

You can clone this Pallet environment to your PlanktoScope (or any computer acting as a Docker swarm manager) using [`forklift`](https://github.com/PlanktoScope/forklift). For example, you can run any one of the forklift CLI commands, depending on which release of this Pallet environment you want:
```
// to clone and track the latest release of the edge branch:
forklift env clone github.com/PlanktoScope/pallets-env@edge
// to clone the v0.1.0 release:
forklift env clone github.com/PlanktoScope/pallets-env@v0.1.0
```

Then you can synchronize the Docker swarm stack deployments on your PlanktoScope (or the Docker swarm manager you're running) with your local Pallet environment using the following forklift CLI command:
```
forklift env apply
```

Warning: this will replace all Docker stacks on your Docker swarm with the stacks in this Github repository and delete any Docker stacks not specified by the stacks in this Github repository.

## Licensing

Pallet packages specified by this environment have their own software licenses, as specified in the Pallet repositories where those packages are published. Any source code provided here is covered by the following information, except where otherwise indicated:

Copyright Ethan Li and PlanktoScope project contributors

SPDX-License-Identifier: Apache-2.0 OR BlueOak-1.0.0

You can use the source code provided here either under the [Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0) or under the [Blue Oak Model License 1.0.0](https://blueoakcouncil.org/license/1.0.0); you get to decide. We are making the software available under the Apache license because it's [OSI-approved](https://writing.kemitchell.com/2019/05/05/Rely-on-OSI.html), but we like the Blue Oak Model License more because it's easier to read and understand.
