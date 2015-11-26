# deeplocalizer
[![wercker status](https://app.wercker.com/status/72f60f68e9fc109d741b99d084f0a593/m "wercker status")](https://app.wercker.com/project/bykey/72f60f68e9fc109d741b99d084f0a593)

This project contains programms to tag bees on beesbook images.

## Build

Make sure you have OpenCV 2.4, Boost 1.58.0 and Qt5 installed.
The code currently depends on Caffe's master branch. Check it out and compile it.
To build the code run:

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The binaries should be now in the `build/source/tagger` directory.

## Run the Tests

Built the code and then run in you build directory:

```
$ ctest
```

## Tagger

This program lets you create a training dataset.

### Create a file of image paths

Create a file with the paths to the images you want to tag.
The content of your file should look like this:
```
Cam_2_20140805143859_2.jpeg
Cam_2_20140805142820_2.jpeg
Cam_2_20140805145011_4.jpeg
```
In every line stands an image to tag.

Use the `find_all_images.sh` script to find all images in a directory.

```
$ ./scripts/find_all_images.sh DIRECTORY > images.txt
```

### preprocess

Some tags are to near to border of the image. The `preprocess` utility program
adds border and can equalize the histogram with the `-use-hist-eq 1` option or
create binary images via `-binary-image 1`.

```
$ preprocess -o OUTPUT_DIRCTORY images.txt
```

The new images will be saved to the OUTPUT_DIRECTORY.

### generate_proposals

The next step is to use the BeesBook pipeline to generate proposals.

Run:
```
$ generate_proposals FILE_WITH_PATHS
```
where `FILE_WITH_PATHS` is the one generated by `preprocess`
`generate_proposals` creates a `.desc` file for every image.

### tagger

Start the actual tagging GUI.
```
$ tagger FILE_WITH_PATHS
```
tagger finds the `.desc` files and updates them as you tag the images.


## Generate Dataset

When you have enough images tagged, you can start to generate a training set:

```
$ generate_dataset -f hdf5 -o hdf5_output --sample-rate 32 FILE_WITH_PATHS
```

This will create an `hdf5_output` directory with maybe multiple `.hdf5` files in
it.
