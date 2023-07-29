# pallets-env
The standard configuration of Pallet package deployments for the PlanktoScope software distribution

## Introduction

pallets-env is a [Forklift](https://github.com/PlanktoScope/forklift) environment specifying the standard configuration of [Pallet](https://github.com/PlanktoScope/pallets) package deployments for the PlanktoScope software distribution.

## Usage

### Deployment

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

### Development

You should clone this Github repository to your local file system. For example, you can clone the latest unstable version (on the `edge` branch) of the [`github.com/PlanktoScope/pallets-env`](https://github.com/PlanktoScope/pallets-env) environment using the command:

```
git clone https://github.com/PlanktoScope/pallets-env
```

Then you will need to download/install forklift. Once you have forklift, you can run subcommands under the `forklift dev env` command; if forklift is in your system path, you can simply run commands within the directory containing your development environment, or any subdirectory of it. For example, if your development environment is at `/home/pi/dev/pallets-env`, you can run the following commands to see some information about your development environment:

```
cd /home/pi/dev/pallets-env
forklift dev env show
```

You can also use the `forklift dev env add-repo` command to add additional Pallet repositories to your development environment, and to change the versions of Pallet repositories already added to your development environment.

You can also run commands like `forklift dev env cache-repo` and `sudo -E forklift dev env apply` (with appropriate values in the `--cwd` flag if necessary) to download the Pallet repositories specified by your development environment into your local cache and deploy the packages provided by those repositories according to the configuration in your development environment. This is useful if, for example, you want to make some experimental changes to your development environment and test them on your local machine before committing and pushing those changes onto GitHub.

Finally, you can run the `forklift dev env check` command to check the environment for any problems, such as resource constraint violations.

For more details and usage information, refer to the [readme for forklift](https://github.com/PlanktoScope/forklift#readme).

## Licensing

Pallet packages specified by this environment have their own software licenses, as specified in the Pallet repositories where those packages are published. Any source code provided here is covered by the following information, except where otherwise indicated:

Copyright Ethan Li and PlanktoScope project contributors

SPDX-License-Identifier: Apache-2.0 OR BlueOak-1.0.0

You can use the source code provided here either under the [Apache 2.0 License](https://www.apache.org/licenses/LICENSE-2.0) or under the [Blue Oak Model License 1.0.0](https://blueoakcouncil.org/license/1.0.0); you get to decide. We are making the software available under the Apache license because it's [OSI-approved](https://writing.kemitchell.com/2019/05/05/Rely-on-OSI.html), but we like the Blue Oak Model License more because it's easier to read and understand.
