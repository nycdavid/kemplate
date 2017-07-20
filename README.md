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

## Parser class
#### The `Parser` class is Kemplate's main parsing engine. It's responsible for reading through template strings and detecting what text eventually gets replaced via interpolation.
  * Parsing lists
  * Parsing cells
    * A "Cell" is Kemplate jargon for a single-string interpolation.
    * Cell interpolations are detected in the usual "Mustache" way, that is, by wrapping a data key in a double-set of opening and closing curly braces like: `{{my_name}}`
    * Cell keys must:
      * __NOT__ contain whitespace. An entry like `{{the best name}}` will be ignored. An entry wrapped in whitespace (`{{ like_this   }}`) **will** be picked up, though.

## Usage
  1. Instantiate a instance of `Kemplate` and pass your template string into the constructor.
  1. Create an instance of `Depot` and `Depot#Store` your strings and lists (std::vectors) in it.
  1. Invoke `Kemplate#Html(Depot dpt)` with your created `Depot` instance and you'll get your interpolated HTML string.
