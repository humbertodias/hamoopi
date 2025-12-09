#!/bin/bash
# Test script for PALLETEGEN SDL2 version

set -e

echo "=== Testing PALLETEGEN SDL2 Build ==="

# Navigate to the build directory
cd "$(dirname "$0")"

echo "1. Checking if executable exists..."
if [ ! -f "PALLETEGEN" ]; then
    echo "ERROR: PALLETEGEN executable not found!"
    exit 1
fi
echo "✓ Executable found"

echo "2. Checking if executable has correct dependencies..."
ldd PALLETEGEN | grep -q "libSDL2" || (echo "ERROR: SDL2 not linked"; exit 1)
ldd PALLETEGEN | grep -q "libSDL2_image" || (echo "ERROR: SDL2_image not linked"; exit 1)
echo "✓ SDL2 dependencies linked correctly"

echo "3. Checking if required data files exist..."
for file in data/system/EditorBackground.png data/system/SlotVazio.png data/system/StatusOK.png; do
    if [ ! -f "$file" ]; then
        echo "ERROR: Required file $file not found!"
        exit 1
    fi
done
echo "✓ Required data files present"

echo "4. Checking if palette source files exist..."
for i in {0..8}; do
    if [ ! -f "data/pal${i}.png" ]; then
        echo "WARNING: Optional file data/pal${i}.png not found"
    fi
done
echo "✓ Palette source files check complete"

echo ""
echo "=== All Tests Passed ==="
echo "The application is ready to use."
echo "Run with: ./PALLETEGEN"
echo "Note: This is a GUI application and requires a display to run."
