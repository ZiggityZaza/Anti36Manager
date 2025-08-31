#!/bin/bash
dist="./dist"
src="./src"
entryTSX="$src/main.tsx"
rendererJS="$dist/main.js"

# Make sure TypeScript files are error-free
if npx tsc --noEmit; then
  echo "TypeScript type checking passed."
else
  echo "TypeScript type checking failed."
  exit 1
fi

echo "Clearing up $dist directory again..."
mkdir -p "$dist"
rm -rf "$dist"

echo "Transpiling and bundling TypeScript files in $src directory..."
npx esbuild "$entryTSX" --bundle --platform=node --format=esm --outfile="$rendererJS" --jsx=automatic # Needs checks as itself doesn't (bugged)
# npx tsc

echo "Running $rendererJS..."
npm start