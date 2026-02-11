# Setup the C++ Environment
```cpp
sudo dnf -y update

sudo dnf -y groupinstall "Development Tools"

sudo dnf -y install cmake git openssl-devel libxml2-devel zlib-devel
```

# Verify the version
```cpp
gcc --version
g++ --version
cmake --version
```
