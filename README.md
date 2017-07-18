# Kemplate: a C++ HTML templating library
## Docker image
* Create the image by running the Makefile command: `make image`
* Image info:
  * Base image: Debian Stretch
  * Libraries: g++, wget, libboost-all-dev, libboost-tools-dev, catch

## Running the test suite
  * After creating the image, run the test suite with: `make test`

## Depot class
  * [TODO]

## Usage
  1. Instantiate a instance of `Kemplate` and pass your template string into the constructor.
  1. Create an instance of `Depot` and `Depot#Store` your strings and lists (std::vectors) in it.
  1. Invoke `Kemplate#Html(Depot dpt)` with your created `Depot` instance and you'll get your interpolated HTML string.
