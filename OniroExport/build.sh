#!/bin/bash
echo "🔨 Building Unity-HarmonyOS project..."

# Generate from Unity export
python3 ./Tools/ProjectConverter.py

# Build HarmonyOS package
hb build

if [ $? -eq 0 ]; then
    echo "✅ Build successful: out/entry/entry-default-unsigned.hap"
else
    echo "❌ Build failed"
    exit 1
fi