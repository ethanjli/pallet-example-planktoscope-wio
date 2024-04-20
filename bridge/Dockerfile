FROM docker.io/library/python:3.9.18-slim-bullseye

RUN useradd --create-home pi
# For now, we don't drop root because dirs are made as root by the hardware controller:
# USER pi:pi
RUN mkdir -p /home/pi/bridge
WORKDIR /home/pi/bridge

# Install Python dependencies

# Note: cmake is needed to install ninja which is needed to install pyproject.toml-based projects.
# We must remove it in the same RUN command as where we installed it, if we want to keep it out of
# the container image.
COPY --chown=pi:pi pyproject.toml poetry.lock .
RUN \
  export PATH="/home/pi/.local/bin:$PATH" && \
  pip install --no-cache-dir poetry==1.7.1 --extra-index-url https://www.piwheels.org/simple && \
  poetry install --no-root --only main --compile && \
  poetry --no-interaction cache list && \
  poetry --no-interaction cache clear pypi --all && \
  poetry --no-interaction cache clear piwheels --all && \
  rm -rf /root/.cache/pypoetry/artifacts && \
  rm -rf /root/.cache/pypoetry/cache && \
  pip cache purge && \
  rm -rf /root/.cache/pip

# Set up application

# Note: we must explicitly set chown if we drop root, or else files will be copied with root
# permissions.
COPY --chown=pi:pi main.py .
ENTRYPOINT ["/usr/local/bin/poetry", "run", "python", "-u", "-m", "main"]
