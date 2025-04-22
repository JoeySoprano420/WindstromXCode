make clean
make
zip windstrom_v0.1.0_linux.zip windstrom
gh release create v0.1.0 windstrom_v0.1.0_linux.zip --notes "Windstrom v0.1.0 - First official compiler release."
