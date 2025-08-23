#!/bin/bash
dist="./dist"
src="./src"
entryJs="$dist/index.js"

echo "Clearing up $dist directory again..."
mkdir -p "$dist"
rm -rf "$dist"

echo "Transpiling and bundling TypeScript files in $src directory..."
# npx esbuild src/index.ts --bundle --platform=node --outfile="$entryJs"
npx tsc

echo "Running $entryJs..."
npm start
# node "$entryJs"