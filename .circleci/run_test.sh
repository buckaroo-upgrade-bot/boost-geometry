#!/bin/bash

if [ "$#" -lt 2 ]; then
	echo 'Intended usage'
    echo '    run_test TEST_NAME TEST_DIR'
    echo ''
    echo '$BOOST_DIR and $COVERAGE_DIR must be defined.'
    exit
fi

TEST_NAME=$1
TEST_DIR=$2

cd $BOOST_DIR

./b2 -j2 cxxflags="--coverage" linkflags="--coverage" libs/geometry/$TEST_DIR

cd ..

mkdir $COVERAGE_DIR/$TEST_NAME

files=$(find $BOOST_DIR/bin.v2/ -name "*.gcda")
for file in $files; do
  filen=${file##*/}
  filen=${filen%.*}
  dirn=${file%/*}
  dstfilen=$filen
  while [ -f $COVERAGE_DIR/$dstfilen.gcda ]; do
    dstfilen=$filen.$RANDOM
  done
  mv $dirn/$filen.gcda $COVERAGE_DIR/$TEST_NAME/$dstfilen.gcda
  mv $dirn/$filen.gcno $COVERAGE_DIR/$TEST_NAME/$dstfilen.gcno
done

