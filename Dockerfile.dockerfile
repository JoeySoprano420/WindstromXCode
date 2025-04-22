FROM ubuntu:22.04

RUN apt update && apt install -y \
  build-essential \
  clang \
  llvm \
  lldb \
  curl \
  unzip \
  git \
  g++ \
  cmake \
  libcurl4-openssl-dev \
  libzip-dev \
  libncurses-dev \
  libedit-dev \
  libssl-dev \
  pkg-config \
  python3 \
  pip \
  wget

# Optional: Install VSCode CLI dependencies
RUN apt install -y code

# Create a workspace directory
WORKDIR /workspace
