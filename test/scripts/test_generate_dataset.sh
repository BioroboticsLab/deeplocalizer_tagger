#!/usr/bin/env bash

set -e
set -o xtrace

TEST_PATHFILE="test_pathfile.txt"
TRAIN_PATHFILE="train_pathfile.txt"

IMG="Cam_2_20150828143300_888543_wb.jpeg"
TEST_IMG=$(realpath "../testdata/$IMG")
IMG_TAGGER_DESC=$(realpath "../testdata/$IMG.tagger.json")

DATA_DIR="$(mktemp -d)/test"
echo "Does $TEST_IMG exists?"
test -e $TEST_IMG

cd ../../source/tagger
echo `pwd`
echo $TEST_IMG > $TEST_PATHFILE
mkdir -p /tmp/data

test -e $IMG_TAGGER_DESC

cat $TEST_PATHFILE
./generate_dataset --pathfile ${TEST_PATHFILE}  -f images -o ${DATA_DIR}
echo "Given a pathfile then ./generate_dataset will generate an dataset"
test -e "${DATA_DIR}/"
test -e "${DATA_DIR}/test.txt"

rm -rf $DATA_DIR

